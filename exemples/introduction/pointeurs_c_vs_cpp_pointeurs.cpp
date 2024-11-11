#include <memory>
#include <iostream>
#include <complex>
#include <vector>
using namespace std::complex_literals;

int main()
{
    using dcomplex = std::complex<double>;

    std::vector<dcomplex> tableau{ 1.+1.i, 2.-1.i, 3.+4.i, 4.-2.i, -2.+3.i };
    dcomplex* pt_coefs = tableau.data();

    for (std::size_t i = 0; i < tableau.size(); ++i )
    {
        std::cout << pt_coefs[i] << " "; 
    }
    std::cout << std::endl;

    pt_coefs++;
    std::cout << *pt_coefs << std::endl;
    pt_coefs += 2;
    std::cout << *pt_coefs << std::endl;
    pt_coefs += 5; // Aïe
    std::cout << *pt_coefs << std::endl;

    pt_coefs -= 8;
    std::cout << *pt_coefs << std::endl;


    return EXIT_SUCCESS;
}