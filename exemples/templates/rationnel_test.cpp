#include "rationnel.hpp"
#include <cmath>
#include <limits>
#include <iomanip>
#include <numbers>
#include <complex>
#include <cstdint>

using arithmetic::Rationnel;

int main()
{
    Rationnel<long long> sqrt2{std::sqrt(2.), 1.E-14};
    std::cout << "Approximation de √(2) = " << std::string(sqrt2)  << " = " 
              << std::setprecision(std::numeric_limits<double>::digits10+1)
              << double(sqrt2) << " <> " << std::sqrt(2.) << std::endl << std::flush;

    double πs3 = std::numbers::pi/3;

    std::cout << "cos( π/3 ) = " << std::cos(πs3) << std::endl;
    std::cout << "cos( π/3 ) = " <<  std::string(Rationnel<std::int32_t>{std::cos(πs3)}) << std::endl << std::flush;

    Rationnel<long long> p5(1,7);

    Rationnel p1{1LL,7LL};
    Rationnel p2{5LL,14LL};

    std::cout << "p1 = " << std::string(p1) << " et p2 = " << std::string(p2) << std::endl << std::flush;

    std::cout << "p1/p2 = " << std::string(p1/p2) << std::endl << std::flush;

    if (p1+p2 == Rationnel{1LL,2LL})
    {
        std::cout << "ok, ";
    }
    else
    {
        std::cout << "Addition fausse ! ";
    }
    std::cout << "p1 + p2 = " << std::string(p1+p2) << std::endl << std::flush;

    std::cout << "p2 - p1 = " << std::string(p2-p1) << std::endl << std::flush;
    std::cout << "p1 - p2 = " << std::string(p1-p2) << std::endl << std::flush;
    std::cout << "p1/(p1-p2) = " << std::string(p1/(p1-p2)) << std::endl << std::flush;
    std::cout << "2*p1/(p1-p2) = " << std::string(2LL*p1/(p1-p2)) << std::endl << std::flush;

    // Approximation de e^{iπ/3} à 10^{-3} près par des rationnels pour la partie réelle et imaginaire :
    std::complex<Rationnel<long long>> z1(Rationnel<long long>(1LL,2LL), 
                                          Rationnel<long long>(std::sqrt(3.)/2.,1.E-3));
    std::cout << "z1 = " << std::string(z1.real()) << " + " << std::string(z1.imag()) << ".i" << std::endl << std::flush;
    std::cout << "z1.real²+z1.imag² = " << std::string(z1.real()*z1.real()+z1.imag()*z1.imag()) << " = "
              << double(z1.real()*z1.real()+z1.imag()*z1.imag()) << std::endl << std::flush;

    return EXIT_SUCCESS;
}