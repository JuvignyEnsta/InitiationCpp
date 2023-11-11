#include <cmath>
#include <string>
#include "plain_matrix.hpp"

using namespace algebre;
using namespace std::string_literals;

PlainMatrix::iterator::iterator( PlainMatrix& t_plMatrix )
    : m_matrix(t_plMatrix)
{}
// --------------------------------------------------------------------------------------------------------------------
PlainMatrix::iterator::iterator( PlainMatrix& t_plMatrix, IndiceType const& t_position )
    : m_matrix(t_plMatrix),
      m_position(t_position)
{}
// --------------------------------------------------------------------------------------------------------------------
PlainMatrix::iterator::iterator( iterator const& iter ) 
    :   m_matrix(iter.m_matrix),
        m_position(iter.m_position)
{}
// ====================================================================================================================
auto PlainMatrix::iterator::operator = ( iterator const& iter ) -> iterator&
{
    assert(&m_matrix == &iter.m_matrix);
    if (this != &iter) {
        m_position = iter.m_position;
    }
    return *this;
}
// --------------------------------------------------------------------------------------------------------------------
bool PlainMatrix::iterator::operator != ( iterator const& iter )
{
    return ( (iter.m_position.icol != m_position.icol) || 
             (iter.m_position.irow != m_position.irow) ||
             (&iter.m_matrix       !=&m_matrix       ) );
}
// --------------------------------------------------------------------------------------------------------------------
auto PlainMatrix::iterator::operator ++ () -> iterator&
{
    ++m_position.icol;
    if (m_position.icol >= m_matrix.dimensions().ncols)
    {
        m_position.icol = 0;
        ++m_position.irow;
    }
    return *this;
}
// --------------------------------------------------------------------------------------------------------------------
auto PlainMatrix::iterator::operator ++ (int) -> iterator
{
    iterator itOld = *this;
    m_position.icol += 1;
    if (m_position.icol >= m_matrix.dimensions().ncols)
    {
        m_position.icol = 0;
        ++m_position.irow;
    }
    return itOld;
}
// --------------------------------------------------------------------------------------------------------------------
auto PlainMatrix::iterator::operator *() -> double&
{ 
#   if __cplusplus > 202002L
    return m_matrix[m_position.irow, m_position.icol]; 
#   else
    return m_matrix[{m_position.irow, m_position.icol}];
#   endif
}
// #####################################################################################################################
PlainMatrix::const_iterator::const_iterator( PlainMatrix const& t_plMatrix )
    : m_matrix(t_plMatrix)
{}
// --------------------------------------------------------------------------------------------------------------------
PlainMatrix::const_iterator::const_iterator( PlainMatrix const& t_plMatrix, IndiceType const& t_position )
    : m_matrix(t_plMatrix),
      m_position(t_position)
{}
// --------------------------------------------------------------------------------------------------------------------
PlainMatrix::const_iterator::const_iterator( const_iterator const& iter ) 
    :   m_matrix(iter.m_matrix),
        m_position(iter.m_position)
{}
// ====================================================================================================================
auto PlainMatrix::const_iterator::operator = ( const_iterator const& iter ) -> const_iterator&
{
    assert(&m_matrix == &iter.m_matrix);
    if (this != &iter) {
        m_position = iter.m_position;
    }
    return *this;
}
// --------------------------------------------------------------------------------------------------------------------
bool PlainMatrix::const_iterator::operator != ( const_iterator const& iter )
{
    return ( (iter.m_position.icol != m_position.icol) ||
             (iter.m_position.irow != m_position.irow) ||
             (&iter.m_matrix       !=&m_matrix       ) );
}
// --------------------------------------------------------------------------------------------------------------------
auto PlainMatrix::const_iterator::operator ++ () -> const_iterator&
{
    ++m_position.icol;
    if (m_position.icol >= m_matrix.dimensions().ncols)
    {
        m_position.icol = 0;
        ++m_position.irow;
    }
    return *this;
}
// --------------------------------------------------------------------------------------------------------------------
auto PlainMatrix::const_iterator::operator ++ (int) -> const_iterator
{
    const_iterator itOld = *this;
    m_position.icol += 1;
    if (m_position.icol >= m_matrix.dimensions().ncols)
    {
        m_position.icol = 0;
        ++m_position.irow;
    }
    return itOld;
}
// --------------------------------------------------------------------------------------------------------------------
auto PlainMatrix::const_iterator::operator *() -> double const&
{ 
#   if __cplusplus > 202002L
    return m_matrix[m_position.irow, m_position.icol];
#   else
    return m_matrix[{m_position.irow, m_position.icol}];
#   endif
}
// #####################################################################################################################
PlainMatrix::PlainMatrix( DimensionType const& t_dimensions )
    : m_dimensions(t_dimensions),
      m_coefficients(t_dimensions.ncols * t_dimensions.nrows)
{}
// --------------------------------------------------------------------------------------------------------------------
PlainMatrix::PlainMatrix( DimensionType const& t_dimensions, std::vector<double> const& t_coefs )
    : m_dimensions(t_dimensions),
      m_coefficients(t_coefs)
{
    assert(t_dimensions.ncols * t_dimensions.nrows == t_coefs.size());
}
// --------------------------------------------------------------------------------------------------------------------
PlainMatrix::PlainMatrix( DimensionType const& t_dimensions, std::vector<double> && t_coefs )
    : m_dimensions(t_dimensions),
      m_coefficients(std::move(t_coefs))
{
    assert(t_dimensions.ncols * t_dimensions.nrows == m_coefficients.size());
}
// ====================================================================================================================
Vecteur PlainMatrix::operator * ( Vecteur const& u ) const
{
    assert(u.dimension() == dimensions().ncols);
    Vecteur res(dimensions().nrows);
    for (std::size_t i=0; i<dimensions().nrows; ++i)
    {
        res[i] = 0;
        for (std::size_t j=0; j<dimensions().ncols; ++j)
            res[i] += m_coefficients[i*dimensions().ncols + j] * u[j];
    }
    return res;
}
// --------------------------------------------------------------------------------------------------------------------
#if __cplusplus > 202002L
double& PlainMatrix::operator[] (std::size_t i, std::size_t j)
{
    return m_coefficients[i + j*m_dimensions.nrows];//Stockage en mode Fortran
}
// --------------------------------------------------------------------------------------------------------------------
double const& PlainMatrix::operator[] (std::size_t i, std::size_t j) const
{
    return m_coefficients[i + j*m_dimensions.nrows];//Stockage en mode Fortran
}
#else 
double& 
PlainMatrix::operator[] (std::pair<std::size_t, std::size_t> const& indices )
{
    std::size_t i = indices.first, j = indices.second;
    return m_coefficients[i + j*m_dimensions.nrows];//Stockage en mode Fortran
}
// --------------------------------------------------------------------------------------------------------------------
double const& 
PlainMatrix::operator[] (std::pair<std::size_t, std::size_t> const& indices ) const
{
    std::size_t i = indices.first, j = indices.second;
    return m_coefficients[i + j*m_dimensions.nrows];//Stockage en mode Fortran
}
#endif
// --------------------------------------------------------------------------------------------------------------------
auto PlainMatrix::dimensions() const -> DimensionType
{
    return m_dimensions;
}
// --------------------------------------------------------------------------------------------------------------------
double PlainMatrix::frobeniusNorm() const
{
    double sum = 0.;
    for (auto value : m_coefficients) sum += value*value;
    return std::sqrt(sum);
}
// --------------------------------------------------------------------------------------------------------------------
std::ostream& PlainMatrix::write(std::ostream& out,std::ios::openmode mode) const
{
    if (mode & std::ios::binary)
    {
        out.write((char const*)&m_dimensions, sizeof(m_dimensions));
        out.write((char const*)m_coefficients.data(), m_coefficients.size()*sizeof(double));
    }
    else
    {
        out << m_dimensions.nrows << " " << m_dimensions.ncols << std::endl;
        for (std::size_t i = 0; i < m_dimensions.nrows; ++i )
        {
            for (std::size_t j = 0; j < m_dimensions.ncols; ++j)
#               if __cplusplus > 202002L
                out << (*this)[i,j] << " ";
#               else
                out << (*this)[{i,j}] << " ";
#               endif
        }
        out << std::endl;
    }
    return out;
}
// --------------------------------------------------------------------------------------------------------------------
PlainMatrix::operator std::string() const
{
    std::string repr;
    if (m_dimensions.nrows == 0) return "[]"s;
    // Affichage première ligne :
    if (m_dimensions.nrows == 1)
        repr += "[ ";
    else
        repr += "┌ "s;
    for (std::size_t j=0; j<std::min(5ULL,m_dimensions.ncols); ++j)
    {
        repr += std::to_string(m_coefficients[j*m_dimensions.nrows]) + " "s;
    }
    if (m_dimensions.ncols > 10) repr += "... "s;

    for (std::size_t j=std::max(5ULL,m_dimensions.ncols-5); j < m_dimensions.ncols; ++j)
    {
        repr += std::to_string(m_coefficients[j*m_dimensions.ncols]) + " "s;
    }
    if (m_dimensions.nrows == 1)
        repr += "]";
    else
        repr += "┐\n"s;
    std::size_t nbStrCols = repr.size() - 7;
    for (std::size_t i=1; i<std::min(5ULL,m_dimensions.nrows-1); ++i)
    {
        repr += "│ "s;
        for (std::size_t j=0; j<std::min(5ULL,m_dimensions.ncols); ++j)
        {
            repr += std::to_string(m_coefficients[i+j*m_dimensions.nrows]) + " "s;
        }
        if (m_dimensions.ncols > 10) repr += "... "s;
        for (std::size_t j=std::max(5ULL,m_dimensions.ncols-5); j < m_dimensions.ncols; ++j)
        {
            repr += std::to_string(m_coefficients[i+j*m_dimensions.ncols]) + " "s;
        }
        repr += "│\n"s;
    }
    if (m_dimensions.nrows > 10) repr += "┆"s + std::string(nbStrCols, ' ') + "┆\n";
    for (std::size_t i=std::max(5ULL,m_dimensions.nrows-5); i < m_dimensions.nrows-1; ++i)
    {
        repr += "│ "s;
        for (std::size_t j=0; j<std::min(5ULL,m_dimensions.ncols); ++j)
        {
            repr += std::to_string(m_coefficients[i+j*m_dimensions.nrows]) + " "s;
        }
        if (m_dimensions.ncols > 10) repr += "... "s;
        for (std::size_t j=std::max(5ULL,m_dimensions.ncols-5); j < m_dimensions.ncols; ++j)
        {
            repr += std::to_string(m_coefficients[i+j*m_dimensions.ncols]) + " "s;
        }
        repr += "│\n"s;
    }
    // Dernière ligne :
    if (m_dimensions.nrows > 1)
    {
        std::size_t i = m_dimensions.nrows-1;
        repr += "└ "s;
        for (std::size_t j=0; j<std::min(5ULL,m_dimensions.ncols); ++j)
        {
            repr += std::to_string(m_coefficients[i+j*m_dimensions.nrows]) + " "s;
        }
        if (m_dimensions.ncols > 10) repr += "... "s;
        for (std::size_t j=std::max(5ULL,m_dimensions.ncols-5); j < m_dimensions.ncols; ++j)
        {
            repr += std::to_string(m_coefficients[i+j*m_dimensions.ncols]) + " "s;
        }
        repr += "┘"s;
    }
    return repr;
}
