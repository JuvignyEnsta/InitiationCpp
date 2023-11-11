#ifndef _GEOM_VECTEUR_HPP_
#define _GEOM_VECTEUR_HPP_
#include <iostream>
#include <initializer_list>
#include <string>

namespace geometry {
class Vecteur
{
public:
    double x{0},y{0},z{0};
    Vecteur() = default;
    Vecteur( std::initializer_list<double> const& t_init_vals);
    Vecteur( double t_cx, double t_cy, double t_cz ) : 
        x(t_cx), y(t_cy), z(t_cz)
    {}
    Vecteur( std::istream& inp );

    Vecteur( double t_cx );
    Vecteur( Vecteur const& );
    Vecteur( Vecteur     && ) = delete;
    ~Vecteur()                = default;

    Vecteur& operator  = ( Vecteur const& );
    Vecteur& operator  = ( Vecteur     && ) = delete;
    Vecteur& operator += ( Vecteur const& );
    Vecteur  operator +  ( Vecteur const& ) const;
    Vecteur& operator -= ( Vecteur const& );
    Vecteur  operator -  ( Vecteur const& ) const;
    Vecteur  operator -  ()                   const;


    void setAsPoint();
    void setAsVector();
    bool isPoint() const;
    std::ostream& print( std::ostream& out ) const;

    explicit operator std::string() const;

private:
    double w{0};
};

inline std::ostream& operator << ( std::ostream& out, Vecteur const& u )
{  return u.print(out);  }
}
#endif