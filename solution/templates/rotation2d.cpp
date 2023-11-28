#include <array>
#include <iostream>
#include <cmath>
#include <numbers>

template<typename K>
using Vector = std::array<K,2>;

template<typename K>
class Rotation2D
{
public:
    Rotation2D( K const& angle );
    Rotation2D( Rotation2D const& ) = default;
    Rotation2D( Rotation2D     && ) = default;
    ~Rotation2D()                   = default;

    Rotation2D& operator = ( Rotation2D const& ) = default;
    Rotation2D& operator = ( Rotation2D     && ) = default;

    Vector<K> operator * ( Vector<K> const& u ) const 
    {
        return Vector<K>{ m_coefs[0][0] * u[0] + m_coefs[0][1] * u[1],
                          m_coefs[1][0] * u[0] + m_coefs[1][1] * u[1] };
    }
private:
    std::array<std::array<K,2>,2> m_coefs;
};

template<typename K>
Rotation2D<K>::Rotation2D( K const& angle )
{
    m_coefs[0][0] =  std::cos(angle);
    m_coefs[1][1] =  std::cos(angle);
    m_coefs[0][1] = -std::sin(angle);
    m_coefs[1][0] =  std::sin(angle);
}

int main()
{
    Rotation2D rot1( std::numbers::pi/3. );
    Vector<double> u{ 1., 1.};
    std::cout << "u = " << u[0] << " "<< u[1] << std::endl;
    Vector<double> v = rot1 * u;
    std::cout << "v = " << v[0] << " "<< v[1] << std::endl;
    return EXIT_SUCCESS;
}