#include <vector>
#include <iostream>
#include <array>
#include <cassert>

using Polynome = std::vector<double>;

Polynome creerPolynome( int n )
{
    assert(n >= 0);
    return Polynome(n+1, 0.);
}

Polynome creerPolynome( std::initializer_list<double> const & t_coefs )
{
    assert(t_coefs.size() > 0);
    return Polynome(t_coefs);
}

std::size_t degrePolynome( Polynome const& p )
{
    assert(p.size() > 0);
    return p.size()-1;
}

double eval( Polynome const& p, double x )
{
    double xn = 1;
    double res = 0.;
    for (auto coef : p)
    {
        res += coef * xn;
        xn *= x;
    }
    return res;
}

Polynome operator + ( Polynome const& p1, Polynome const& p2 )
{
    Polynome r( std::max(p1.size(),p2.size()) );
    for (std::size_t deg = 0; deg < std::min(p1.size(),p2.size()); ++deg )
        r[deg]= p1[deg] + p2[deg];

    for (std::size_t deg = std::min(p1.size(),p2.size()); deg < p1.size(); ++deg )
        r[deg] = p1[deg];

    for (std::size_t deg = std::min(p1.size(),p2.size()); deg < p2.size(); ++deg )
        r[deg] = p2[deg];

    return r;
}

std::ostream& operator << ( std::ostream& out, Polynome const& p )
{
    out << "(" << p[0];
    for (std::size_t deg=1; deg < p.size(); ++deg )
        out << " + " << p[deg] << ".x^" << deg;
    out << " )";
    return out;
}

Polynome operator * ( Polynome const& p1, Polynome const& p2 )
{
    Polynome r(p1.size() + p2.size() -1, 0. );

    for ( std::size_t deg1 = 0; deg1 < p1.size(); ++deg1 )
    {
        for (std::size_t deg2 = 0; deg2 < p2.size(); ++deg2 )
        {
            r[deg1+deg2] += p1[deg1]*p2[deg2];
        }
    }
    return r;
}

int main()
{   //                           1 + x - x²
    Polynome p1 = creerPolynome({1., 1., -1.});
    //                           -1 +2x - x²
    Polynome p2 = creerPolynome({-1.,2.,-1.});

    auto r = p1 + p2;

    std::cout << p1 << " + " << p2 << " = " << r << std::endl;

    r = p1 * p2;

    std::cout << p1 << " * " << p2 << " = " << r << std::endl;

    return EXIT_SUCCESS;
}