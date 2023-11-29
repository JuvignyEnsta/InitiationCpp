#include <fstream>
#include "polynome.hpp"
#include <complex>

using namespace std::complex_literals;

int main()
{
    Polynome<double> p1({1.,2.,1});
    std::cout << std::string(p1) << std::endl;
    std::cout << std::string(p1.derivee()) << std::endl;
    std::cout << std::string(p1.primitive()) << std::endl;

    Polynome<double> p2({1.,3.,3.,1.});

    auto p3 = p1 + p2;
    std::cout << std::string(p1) << " + " << std::string(p2) << " = " << std::string(p3) << std::endl;
    p3 = p1 - p2;
    std::cout << std::string(p1) << " - " << std::string(p2) << " = " << std::string(p3) << std::endl;
    p3 = p1 * p2;
    std::cout << std::string(p1) << " * " << std::string(p2) << " = " << std::string(p3) << std::endl;
    std::cout << p3 << std::endl;

    std::ofstream fichOut("polynome.txt");
    fichOut << p3;
    fichOut.close();

    std::ifstream fichInp("polynome.txt");
    Polynome<double> p4(fichInp);
    std::cout << "p4 : " << std::string(p4) << std::endl;

    std::cout << "p4(1+i) = " << p4(1.+1.i) << std::endl; 
    return EXIT_SUCCESS;
}