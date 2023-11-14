#include <iostream>
#include <cstdint>

std::uint64_t factoriel( std::uint64_t n )
{
    if (n==0) return 1ULL;
    return n * factoriel(n-1);
}

int main()
{
    std::cout << factoriel(10) << std::endl;
    return EXIT_SUCCESS;
}