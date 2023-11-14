#include <cmath>
#include <string>
#include <iostream>
#include <iomanip>

int main( int nargs, char *argv[] )
{
    if (nargs != 2)
    {
        std::cerr << "Nombre d'itérations nécessaire en argument !" << std::endl;
        return EXIT_FAILURE;
    }
    auto nIter = std::stol(argv[1]);

    double Sn = 0.;
    for (long k=0; k < nIter; ++k )
    {
        Sn += 4*( std::pow(-1.,k)/(2.*k+1.) * 
                  ( 4./std::pow(5.,2.*k+1) - 1./std::pow(239., 2.*k+1.)));
        std::cout << "S_" << k << " = " << std::setprecision(14) << Sn << std::endl;
    }

    return EXIT_SUCCESS;
}