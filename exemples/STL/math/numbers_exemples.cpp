#include <numbers>
#include <iostream>
#include <iomanip>

int main()
{
    std::cout << std::setprecision(20)  << std::numbers::e << " vs " << std::numbers::e_v<float> << std::endl; 
    std::cout << std::setprecision(20)  << std::numbers::log2e << " vs " << std::numbers::log2e_v<float> << std::endl; 
    std::cout << std::setprecision(20)  << std::numbers::pi << " vs " << std::numbers::pi_v<float> << std::endl; 

    return EXIT_SUCCESS;
}