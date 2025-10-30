#include <cstdlib>
#include <random>
#include <iostream>
#include <functional>

int main()
{
    std::random_device rd;
    auto generator = std::mt19937(rd());
    auto d20 = std::bind(std::uniform_int_distribution<std::uint8_t>(1,20),generator);
    for ( int i=0; i<10; ++i )
        std::cout << "Je jette un dé 20 : " << int(d20()) << std::endl;

    auto proba = std::uniform_real_distribution<double>(0.,1.);
    for (int i=0; i<10; ++i)
        std::cout << "Tu as " << proba(generator) << " chances de réussir !" << std::endl;

    return EXIT_SUCCESS;
}