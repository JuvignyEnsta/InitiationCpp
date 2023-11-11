#include <numbers>
#include <iostream>
#include <iomanip>

int main()
{
    constexpr long double pi{std::numbers::pi_v<long double>};
    std::cout << std::setw(19) << std::setprecision(0) << pi << std::endl;
    std::cout << std::setw(19) << std::setfill('_')  << std::setprecision(4) << pi << std::endl;
    std::cout << std::setw(4) << std::setprecision(4) << pi << std::endl;
    std::cout << std::setprecision(20) << pi << std::endl;

    return EXIT_SUCCESS;
}