#include <iostream>
#include <complex>
using namespace std::complex_literals;

template<typename K> auto pow( K const& val, unsigned n )
{
    K val_n = K(1);
    for (unsigned i=0; i<n; ++i)
        val_n *= val;
    return val_n;
}

int main()
{
    std::cout << "3^3 = " << pow(3,3) << std::endl;
    std::cout << "101^0 = " << pow(101,0) << std::endl;
    std::cout << "1.1^4 = " << pow(1.1, 4) << std::endl;
    std::cout << "(1.-1.i)^2 = " <<  pow(1.-1.i, 2) << std::endl;

    return EXIT_SUCCESS;
}