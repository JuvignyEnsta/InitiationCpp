#include <iostream>

template<unsigned n> constexpr long long u = u<n-2> - u<n-1>;
template<> constexpr long long u<1> = 1ULL;
template<> constexpr long long u<2> = 2ULL;

int main()
{
    std::cout << u<32> << std::endl;

    return EXIT_SUCCESS;
}