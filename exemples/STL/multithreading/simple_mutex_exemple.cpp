#include <thread>
#include <iostream>
#include <vector>
#include <cmath>
#include <cstdint>
#include <chrono>

bool isPrime( std::uint64_t p )
{
    int maxEntier = std::sqrt(double(p))+1; 
    if ((p==2) || (p==3)) return true;
    for (int i=1; (6*i-1)<maxEntier; ++i)
        if ( (p%(6*i-1)==0) || (p%(6*i+1)==0) ) return false;
    return true;
}

void searchTwinPrimesSeq( std::uint64_t max, std::vector<std::pair<std::uint64_t, std::uint64_t>>& twins )
{
    std::uint64_t maxIndex = (max-1)/6;
    std::uint64_t begLoop  = 1;
    std::uint64_t endLoop  = begLoop + maxIndex;
    for (std::uint64_t index=begLoop; index<endLoop; ++index)
        if (isPrime(6*index-1) && isPrime(6*index+1))
            {
                twins.emplace_back(std::pair{6*index-1,6*index+1});
            }
}


void searchTwinPrimes(unsigned nbThreads, unsigned idThread, std::uint64_t max,
                      std::vector<std::pair<std::uint64_t, std::uint64_t>>& twins )
{
    static std::mutex updateTwins;
    std::uint64_t maxIndex = (max-1)/6+1;
    std::uint64_t begLoop = idThread + 1;
    std::uint64_t endLoop = maxIndex + 1;
    
    for (std::uint64_t index=begLoop; index<endLoop; index += nbThreads)
        if (isPrime(6*index-1) && isPrime(6*index+1))
            {
                updateTwins.lock();
                twins.emplace_back(std::pair{6*index-1,6*index+1});
                updateTwins.unlock();
            }
}

int main()
{
    std::uint64_t maxEntierTest = 10'000'000ULL;

    std::vector<std::pair<std::uint64_t,std::uint64_t>> twinPrimesSeq { std::pair{2ULL,3ULL} };
    auto startSeq = std::chrono::high_resolution_clock::now();
    searchTwinPrimesSeq( maxEntierTest, twinPrimesSeq );
    auto endSeq   = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> dtSeq = endSeq - startSeq;
    std::cout << "Trouvé " << twinPrimesSeq.size() << " premiers jumeaux"
              << " en " << dtSeq.count() << " secondes." << std::endl;  

    auto nbThreads = std::thread::hardware_concurrency();
    std::vector<std::thread> threads; threads.reserve(nbThreads);

    std::vector<std::pair<std::uint64_t,std::uint64_t>> twinPrimes { std::pair{2ULL,3ULL} };
    
    auto startPar = std::chrono::high_resolution_clock::now();
    for (unsigned i=0; i<nbThreads; ++i)
        threads.emplace_back(searchTwinPrimes, unsigned(nbThreads), i, maxEntierTest, std::ref(twinPrimes));

    for (unsigned i=0; i<nbThreads; ++i)
        threads[i].join();
    auto endPar   = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> dtPar = endPar - startPar;

    std::cout << "Trouvé " << twinPrimes.size() << " premiers jumeaux"
              << " en " << dtPar.count() << " secondes." << std::endl;  

    return EXIT_SUCCESS;
}
