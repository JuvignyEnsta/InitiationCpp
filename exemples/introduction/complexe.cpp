#include <numbers>
#include <iostream>
#include <complex>
using namespace std::complex_literals;
int main()
{
    std::complex z1{1.,2.};
    std::complex fz = 3.f - 2.if;
    std::complex z2 = 3. - 4.i;
    std::complex lz = 3.l - 4.il;

    std::cout << "fz = " << fz << std::endl; 
    std::cout << "z2 = " << z2 << std::endl; 
    std::cout << "lz = " << lz << std::endl; 

    std::complex z3 = std::polar(2., std::numbers::pi/3.);
    std::cout << "z3 = " << z3 << std::endl; 
    double arg = std::arg(z3);
    double mod = std::abs(z3);
    std::cout << "z3 = " << mod << ".e^{i" << arg << "}" << std::endl;

    std::complex z4 = z2 * z3; 
    std::cout << "z4 = " << z4.real() << " + " << z4.imag() << " i" << std::endl;
    z4 = z2 * std::conj(z3);
    std::cout << "z4 = " << z4.real() << " + " << z4.imag() << " i" << std::endl;

    return EXIT_SUCCESS;
}