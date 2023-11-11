#include <iostream>
#include <cstdint>
#include <complex>
using namespace std::complex_literals;

int main()
{
    using dcomplex=std::complex<double>;
    dcomplex z;
    std::uint32_t uval32 = 3;
 
    z = (dcomplex)uval32;
    std::cout << "z = " << z << std::endl;

    z = dcomplex(uval32);
    std::cout << "z = " << z << std::endl;

    z = static_cast<dcomplex>(uval32);
    std::cout << "z = " << z << std::endl;

    z = 3. -2.i;
    uval32 = (std::uint32_t&)z;
    std::cout << "uval32 = " << uval32 << std::endl;

#   if defined(NOCOMPILING)
    uval32 = static_cast<std::uint32_t&>(z);
    std::cout << "uval32 = " << uval32 << std::endl;
#   endif

    return EXIT_SUCCESS;
}
