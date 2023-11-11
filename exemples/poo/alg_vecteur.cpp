#include <cassert>
#include <cmath>
#include "alg_vecteur.hpp"
using namespace algebre;
using namespace std::string_literals;

Vecteur::Vecteur( std::vector<double> const& t_coefs ) : m_coefs(t_coefs) {}
// --------------------------------------------------------------------------------------------------------------------
Vecteur::Vecteur( std::vector<double> && t_coefs ) : m_coefs(t_coefs)     {}
// --------------------------------------------------------------------------------------------------------------------
Vecteur::Vecteur( std::size_t t_dimension ) : m_coefs(t_dimension) {}
// --------------------------------------------------------------------------------------------------------------------
Vecteur::Vecteur( std::size_t t_dimension, double t_fillingCoef) : m_coefs(t_dimension, t_fillingCoef) {}
// --------------------------------------------------------------------------------------------------------------------
Vecteur::Vecteur( std::istream& t_input, std::ios::openmode mode )
{
    std::size_t dim;
    if (mode == std::ios::binary)
    {
        t_input.read((char *)&dim, sizeof(std::size_t));
        m_coefs.resize(dim);
        t_input.read((char *)m_coefs.data(), dim*sizeof(double));
    }
    else
    {
        t_input >> dim;
        m_coefs.resize(dim);
        for (auto& coef : m_coefs) t_input >> coef;
    }
}
// ====================================================================================================================
double& Vecteur::operator [] ( std::size_t i )
{
    assert(i < dimension());
    return m_coefs[i];
}
// --------------------------------------------------------------------------------------------------------------------
double const& Vecteur::operator[] ( std::size_t i ) const
{
    assert(i < dimension());
    return m_coefs[i];    
}
// ====================================================================================================================
Vecteur& Vecteur::operator += ( Vecteur const& u )
{
    assert(dimension() == u.dimension());
    for (std::size_t ind=0; ind<dimension(); ++ind) m_coefs[ind] += u[ind];
    return *this;
}
// --------------------------------------------------------------------------------------------------------------------
Vecteur Vecteur::operator +  ( Vecteur const& u) const
{
    assert(dimension() == u.dimension());
    Vecteur w(dimension());
    for (std::size_t ind=0; ind<dimension(); ++ind) w[ind] = m_coefs[ind] + u[ind];
    return w;
}
// --------------------------------------------------------------------------------------------------------------------
Vecteur&& Vecteur::operator +  ( Vecteur && u ) const
{
    assert(dimension() == u.dimension());
    for (std::size_t ind=0; ind<dimension(); ++ind) u[ind] += m_coefs[ind];
    return std::move(u);
}
// --------------------------------------------------------------------------------------------------------------------
Vecteur& Vecteur::operator -= ( Vecteur const& u)
{
    assert(dimension() == u.dimension());
    for (std::size_t ind=0; ind<dimension(); ++ind) m_coefs[ind] -= u[ind];
    return *this;
}
// --------------------------------------------------------------------------------------------------------------------
Vecteur  Vecteur::operator - ( Vecteur const& u ) const
{
    assert(dimension() == u.dimension());
    Vecteur w(dimension());
    for (std::size_t ind=0; ind<dimension(); ++ind) w[ind] = m_coefs[ind] - u[ind];
    return w;
}
// --------------------------------------------------------------------------------------------------------------------
Vecteur&& Vecteur::operator -  ( Vecteur && u ) const
{
    assert(dimension() == u.dimension());
    for (std::size_t ind=0; ind<dimension(); ++ind) u[ind] = m_coefs[ind] - u[ind];
    return std::move(u);
}
// --------------------------------------------------------------------------------------------------------------------
Vecteur Vecteur::operator - ( ) const
{
    Vecteur w(dimension());
    for (std::size_t ind=0; ind<dimension(); ++ind) w[ind] = -m_coefs[ind];
    return w;
}
// --------------------------------------------------------------------------------------------------------------------
Vecteur& Vecteur::operator *= ( double alpha   )
{
    for (auto& coef : m_coefs) coef *= alpha;
    return *this;
}
// --------------------------------------------------------------------------------------------------------------------
double Vecteur::operator |  ( Vecteur const& u ) const
{
    assert(dimension() == u.dimension());
    double sum = 0.;
    for (std::size_t i = 0; i<dimension(); ++i) sum += m_coefs[i] * u[i];
    return sum;
}
// ====================================================================================================================
Vecteur Vecteur::homothetie ( double alpha ) const
{
    Vecteur w(dimension());
    for (std::size_t i=0; i<dimension(); ++i) w[i] = alpha*m_coefs[i];
    return w;
}
// --------------------------------------------------------------------------------------------------------------------
std::ostream& Vecteur::write( std::ostream& out, std::ios::openmode mode ) const
{
    std::size_t dim = dimension();
    if (mode == std::ios::binary)
    {
        out.write((char *)&dim, sizeof(std::size_t));
        out.write((char *)m_coefs.data(), dim*sizeof(double));
    }
    else {
        out << dim << std::endl;
        for (auto const& val : m_coefs) out << val << " ";
    }
    return out;
}
// --------------------------------------------------------------------------------------------------------------------
Vecteur::operator std::string() const
{
    auto dim = dimension();
    std::string repr("< ");
    for (std::size_t i=0; i<std::min(10ULL,dim); ++i)
    {
        repr += std::to_string(m_coefs[i]) + " "s;
    }
    if (dim > 20) repr += "... "s;

    for (std::size_t i=std::max(10ULL,dim-10); i<dim; ++i)
    {
        repr += std::to_string(m_coefs[i]) + " "s;
    }
    repr += ">"s;
    return repr;
}
// --------------------------------------------------------------------------------------------------------------------
double Vecteur::normL2() const { return std::sqrt((*this)|(*this)); }
// --------------------------------------------------------------------------------------------------------------------
double Vecteur::normalizeInplace()
{
    double nrmL2 = normL2();
    if (nrmL2 < 1.E-14) throw std::domain_error("Impossible normalisé, vecteur nul !");
    for (auto& val : m_coefs) val /= nrmL2;
    return nrmL2;
}
// --------------------------------------------------------------------------------------------------------------------
std::pair<double,Vecteur> Vecteur::normalize() const
{
    double nrmL2 = normL2();
    if (nrmL2 < 1.E-14) throw std::domain_error("Impossible normalisé, vecteur nul !");
    Vecteur w(dimension());
    for (std::size_t i=0; i<dimension(); ++i) w[i] = m_coefs[i]/nrmL2;
    return {nrmL2, w};    
}
