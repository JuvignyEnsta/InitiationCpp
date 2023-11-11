#include <forward_list>
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
    std::forward_list<std::int64_t> primes;
    primes.emplace_front(2);
    if (nbPrimes > 1) primes.emplace_front(3);
    std::int64_t k = 1;
    std::int64_t foundPrimes = 2;
    while (foundPrimes < nbPrimes)
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
        if (p1 > 0) 
        {
            primes.push_front(p1);
            foundPrimes ++;
        }
        if ( (p2 > 0) and (foundPrimes < nbPrimes) ) 
        {
            primes.push_front(p2);
            foundPrimes ++;
        }
    }
    std::cout << "Voici les " << nbPrimes << " premiers nombres premiers :  " << std::endl;
    for (auto p : primes ) std::cout << p << " ";
    std::cout << std::endl;
    return EXIT_SUCCESS;
}