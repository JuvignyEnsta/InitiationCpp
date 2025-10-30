#include <random>
#include <iostream>

int main()
{
    std::random_device rd;
    auto generator = std::mt19937(rd());

    std::bernoulli_distribution b(0.25);
    for (int i=0; i<10; ++i) std::cout << b(generator) << " ";
    std::cout << std::endl;

    std::binomial_distribution<> bi(4, 0.5);
    for (int i=0; i<10; ++i)
        std::cout << bi(generator) << " ";
    std::cout << std::endl;

    std::geometric_distribution<> g;
    for (int i=0; i<10; ++i)
        std::cout << g(generator) << " ";
    std::cout << std::endl;

    return EXIT_SUCCESS;
}
