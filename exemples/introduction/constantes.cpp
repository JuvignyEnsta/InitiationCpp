#include <numbers>
#include <iostream>
#include <iomanip>
#include <limits>

int main()
{
    long double π_lf = std::numbers::pi_v<long double>;
    std::cout << std::setprecision((std::numeric_limits<long double>::digits10+1)) << "π = " << π_lf << std::endl; 
    double πˉ¹ = std::numbers::inv_pi;
    double e   = std::numbers::e;
    double φ   = std::numbers::phi;
    std::cout << std::setprecision((std::numeric_limits<double>::digits10+1)) << "φ = " << φ << std::endl;
    return EXIT_SUCCESS;
}
