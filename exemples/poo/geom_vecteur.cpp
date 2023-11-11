#include <cassert>
#include <stdexcept>
#include "geom_vecteur.hpp"
using namespace geometry;
using namespace std::string_literals;

Vecteur::Vecteur( std::initializer_list<double> const& t_init_vals)
{
    std::size_t size = t_init_vals.size();
    assert( size <= 4);
    auto iter = t_init_vals.begin();
    x = *iter;
    ++iter;
    if (size > 1) { y = *iter; ++iter; }
    if (size > 2) { z = *iter; ++iter; }
    if (size > 3) { w = *iter; ++iter; }
}
// --------------------------------------------------------------------------------------------------------------------
Vecteur::Vecteur( std::istream& inp )
{
    inp >> x >> y >> z >> w;
}
// --------------------------------------------------------------------------------------------------------------------
Vecteur::Vecteur( double cx ) : x(cx), y(cx), z(cx)
{}
// --------------------------------------------------------------------------------------------------------------------
Vecteur::Vecteur( Vecteur const& u ) : x(u.x), y(u.y), z(u.z), w(u.w)
{}
// ====================================================================================================================
Vecteur& Vecteur::operator  = ( Vecteur const& u)
{
    if (this != &u) // Pour empêcher un vecteur de se copier sur lui-même !
    {
        x = u.x; y = u.y; z = u.z; w = u.w;
    }
    return *this;
}
// --------------------------------------------------------------------------------------------------------------------
Vecteur& Vecteur::operator += ( Vecteur const& u)
{
    if (isPoint() && u.isPoint())
        throw std::logic_error("Impossible de sommer deux points !");
    if (!isPoint() && u.isPoint())
        throw std::logic_error("Impossible de sommer un point à un vecteur !");
    x += u.x; y += u.y; z += u.z; w = std::max(w,u.x);
    return *this;
}
// --------------------------------------------------------------------------------------------------------------------
Vecteur Vecteur::operator +  ( Vecteur const& u) const
{
    if (isPoint() && u.isPoint())
        throw std::logic_error("Impossible de sommer deux points !");
    if (!isPoint() && u.isPoint())
        throw std::logic_error("Impossible de sommer un point à un vecteur !");
    return {x+u.x, y+u.y, z+u.z, std::max(w,u.w)};
}
// --------------------------------------------------------------------------------------------------------------------
Vecteur& Vecteur::operator -= ( Vecteur const& u)
{
    if (isPoint() && u.isPoint())
        throw std::logic_error("Impossible de soustraire deux points !");
    if (!isPoint() && u.isPoint())
        throw std::logic_error("Impossible de soustriare un point à un vecteur !");
    x -= u.x; y -= u.y; z -= u.z; w = std::max(w,u.x);
    return *this;
}
// --------------------------------------------------------------------------------------------------------------------
Vecteur  Vecteur::operator -  ( Vecteur const& u) const
{
    if (isPoint() && u.isPoint())
        throw std::logic_error("Impossible de soustraire deux points !");
    if (!isPoint() && u.isPoint())
        throw std::logic_error("Impossible de soustraire un point à un vecteur !");
    return {x-u.x, y-u.y, z-u.z, std::max(w,u.w)};
}
// --------------------------------------------------------------------------------------------------------------------
Vecteur Vecteur::operator - () const
{
    return {-x, -y, -z, w};
}
// ====================================================================================================================
void Vecteur::setAsPoint()  { w = 1; }
// --------------------------------------------------------------------------------------------------------------------
void Vecteur::setAsVector() { w = 0; }
// --------------------------------------------------------------------------------------------------------------------
bool Vecteur::isPoint() const { return w==1; }
// --------------------------------------------------------------------------------------------------------------------
std::ostream& Vecteur::print( std::ostream& out ) const
{
    out << x << " " << y << " " << z << " " << w;
    return out;
}
// --------------------------------------------------------------------------------------------------------------------
Vecteur::operator std::string() const
{
    std::string repr;
    if (isPoint()) repr = "{ "; else repr = "< ";
    repr += std::to_string(x) + ", "s + std::to_string(y) + ", "s + std::to_string(z);
    if (isPoint()) repr += " }"; else repr += " >";
    return repr;
}
