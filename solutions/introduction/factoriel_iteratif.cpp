#include <iostream>
#include <cstdint>

std::uint64_t factoriel( std::uint64_t n )
{
    if (n==0) return 1;
    std::uint64_t res = 1;
    for (std::uint64_t i=1; i<=n; ++i)
    {
        res *= i;
    }
    return res;
}

int main()
{
    std::cout << factoriel(10) << std::endl;
    std::cout << factoriel(100) << std::endl;

    return EXIT_SUCCESS;
}