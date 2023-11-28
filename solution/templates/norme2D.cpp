#include <array>
#include <iostream>
#include <cmath>
#include <complex>
using namespace std::complex_literals;

template<typename K>
auto norm2D( std::array<K,2> const& u )
{
    return std::sqrt(u[0]*u[0]+u[1]*u[1]);
}

template<typename K>
auto norm2D( std::array<std::complex<K>,2> const& u )
{
    return std::sqrt((std::conj(u[0])*u[0]+std::conj(u[1])*u[1]).real());
}

int main()
{
    std::cout << "||(1.,1.)|| = " << norm2D(std::array{1.,1.}) << std::endl;
    std::cout << "||(1.+1.i,1.-1.i)|| = " << norm2D(std::array{1.+1.i,1.-1.i}) << std::endl;

    return EXIT_SUCCESS;
}