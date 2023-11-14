#include <complex>
#include <array>
#include <vector>
#include <iostream>
#include <cmath>
#include <numbers>
#include <algorithm>

using namespace std::complex_literals;


std::ostream& operator << ( std::ostream& out, std::vector<auto> const u )
{
    out << "[ ";
    for ( auto const& v : u ) out << v << " ";
    out << "]";
    return out;
}

int main()
{
    auto f = [] ( auto const& x )
             {
                return (x*x*x-3.*x*x+2.)/(std::norm(x)+1.);
             };

    std::complex c = 0.1 - 0.1i;

    auto m = [c](std::complex<double> const& z) { return z*z + c; };

    constexpr int N = 10;
    std::vector<double> R; R.reserve(N);
    for ( int i = 0; i < N; ++i ) R.emplace_back(std::cos(i*std::numbers::pi/N));

    std::cout << "R = " << R << std::endl;

    std::vector<std::complex<double>> Z(10);
    Z[0] = c;
    for (int i = 1; i < N; ++i ) Z[i] = m(Z[i-1]);

    std::cout << "Z = " << Z << std::endl;

    std::sort(R.begin(), R.end(), [f]( double x, double y ) { return f(x) < f(y); } );
    std::cout << "R = " << R << std::endl;
    for (auto v : R ) std::cout << f(v) << " ";
    std::cout << std::endl;

    std::sort(Z.begin(), Z.end(), [f]( std::complex<double> const& x, std::complex<double> const& y ) 
                                  { return std::norm(f(x)) < std::norm(f(y)); } );
    std::cout << "Z = " << Z << std::endl;
    for (auto v : Z ) std::cout << std::abs(f(v)) << " ";
    std::cout << std::endl;


    return EXIT_SUCCESS;
}