#include <iostream>
#include <complex>
using namespace std::complex_literals;

#if 0
template<unsigned n> constexpr double pow(double const& t_val )
{
    double val_n = t_val * pow<n-1>(t_val);
    return val_n;
}
template<> constexpr double pow<0>(double const& t_val )
{
    return 1.;
}
# else
template<unsigned n> constexpr double pow(double const& t_val )
{
    if constexpr (n==0)
    {
        return 1.;
    }
    else 
    {
        double val_n = t_val * pow<n-1>(t_val);
        return val_n;
    }
}
#endif

template<unsigned long val, unsigned n> constexpr unsigned long power = val * power<val,n-1>;
template<unsigned long val> constexpr unsigned long power<val,0> = 1ULL;




int main()
{
    std::cout << "3^3 = " << pow<3>(3) << std::endl;
    std::cout << "101^0 = " << pow<0>(101) << std::endl;
    std::cout << "1.1^4 = " << pow<4>(1.1) << std::endl;
    std::cout << "(1.-1.i)^2 = " <<  pow<2>(-1) << std::endl;

    std::cout << "3^4 = " << power<3UL,4> << std::endl;
    return EXIT_SUCCESS;
}