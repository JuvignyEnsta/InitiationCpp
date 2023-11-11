#include <vector>
#include <iostream>
#include <cstdint>

int main(int nargs, char* argv[])
{
    int nbPrimes = 10;
    if (nargs > 1) nbPrimes = std::stoi(argv[1]);
    if (nbPrimes <= 0)
    {
        std::cout << "Passer en argument un entier strictement positif !" << std::endl;
        return EXIT_FAILURE;
    }
    std::vector<std::int64_t> primes;
    primes.reserve(nbPrimes);
    primes.emplace_back(2);
    if (nbPrimes > 1) primes.emplace_back(3);
    std::int64_t k = 1;
    while (primes.size() < nbPrimes)
    {
        std::int64_t p1 = 6*k-1;
        std::int64_t p2 = 6*k+1;
        k = k + 1;
        for (auto p : primes)
        {
            if ( (p1 > 0 ) and (p1%p == 0) ) p1 = 0;
            if ( (p2 > 0 ) and (p2%p == 0) ) p2 = 0;
            if ( (p1 == 0) and (p2   == 0) ) break;
        }
        if (p1 > 0) primes.push_back(p1);
        if ( (p2 > 0) and (primes.size() < nbPrimes) ) primes.push_back(p2);
    }
    std::cout << "Voici les " << nbPrimes << " premiers nombres premiers :  " << std::endl;
    for (auto p : primes ) std::cout << p << " ";
    std::cout << std::endl;
    return EXIT_SUCCESS;
}