#include <thread>
#include <iostream>
#include <chrono>
#include <vector>
#include <cassert>

void plain_counter(int& counter)
{
    for (unsigned long i=0; i<1'000'000UL; ++i)
        ++counter;
    for (unsigned long i=0; i<1'000'000UL; ++i)
        --counter;
}

void atomic_counter(std::atomic_int32_t& counter)
{
    for (unsigned long i=0; i<1'000'000UL; ++i)
        ++counter;
    for (unsigned long i=0; i<1'000'000UL; ++i)
        --counter;
}

void volatile_counter(int volatile& counter)
{
    for (unsigned long i=0; i<1'000'000UL; ++i)
        ++counter;
    for (unsigned long i=0; i<1'000'000UL; ++i)
        --counter;
}


int main()
{
    constexpr unsigned long nbSamples = 20;
    auto nbThreads = std::thread::hardware_concurrency();
    std::vector<std::thread> threads; threads.reserve(nbThreads);
    std::cout << "Performance avec un entier par défaut : " << std::endl;
    double averagePlainTime = 0.;
    int pcounter = 0; plain_counter(pcounter);
    assert(pcounter == 0);
    for (unsigned long iSample{0ULL}; iSample < nbSamples; ++iSample)
    {
        threads.resize(0);
        auto begPlain = std::chrono::high_resolution_clock::now();
        int counter = 0;
        for (unsigned iThread=0; iThread<nbThreads; ++iThread) threads.emplace_back(plain_counter, std::ref(counter));
        for (unsigned iThread=0; iThread<nbThreads; ++iThread) threads[iThread].join();
        auto endPlain = std::chrono::high_resolution_clock::now();
        assert(counter==0);
        std::chrono::duration<double> dureePlain = endPlain - begPlain;
        double dt = dureePlain.count();
        averagePlainTime += dt;
        std::cout << "\tTemps : " << dt << "s." << std::endl;
    }
    std::cout << "--------------------------------------------------------" << std::endl;
    std::cout << "Temps moyen passé : " << averagePlainTime/nbSamples << "s." << std::endl;

    std::cout << "Performance avec un entier atomique : " << std::endl;
    double averageAtomicTime = 0.;
    std::atomic_int32_t acounter = 0; atomic_counter(acounter);
    assert(acounter == 0);
    for (unsigned long iSample{0ULL}; iSample < nbSamples; ++iSample)
    {
        threads.resize(0);
        auto begAtomic = std::chrono::high_resolution_clock::now();
        std::atomic_int32_t counter = 0;
        for (unsigned iThread=0; iThread<nbThreads; ++iThread) threads.emplace_back(atomic_counter, std::ref(counter));
        for (unsigned iThread=0; iThread<nbThreads; ++iThread) threads[iThread].join();
        auto endAtomic = std::chrono::high_resolution_clock::now();
        assert(counter==0);
        std::chrono::duration<double> dureeAtomic = endAtomic - begAtomic;
        double dt = dureeAtomic.count();
        averageAtomicTime += dt;
        std::cout << "\tTemps : " << dt << "s." << std::endl;
    }
    std::cout << "--------------------------------------------------------" << std::endl;
    std::cout << "Temps moyen passé : " << averageAtomicTime/nbSamples << "s." << std::endl;

    std::cout << "Performance avec un entier volatile : " << std::endl;
    double averageVolatileTime = 0.;
    int volatile vcounter = 0; volatile_counter(vcounter);
    assert(vcounter == 0);
    for (unsigned long iSample{0ULL}; iSample < nbSamples; ++iSample)
    {
        threads.resize(0);
        auto begPlain = std::chrono::high_resolution_clock::now();
        volatile int counter = 0;
        for (unsigned iThread=0; iThread<nbThreads; ++iThread) threads.emplace_back(volatile_counter, std::ref(counter));
        for (unsigned iThread=0; iThread<nbThreads; ++iThread) threads[iThread].join();
        auto endPlain = std::chrono::high_resolution_clock::now();
        assert(counter==0);
        std::chrono::duration<double> dureePlain = endPlain - begPlain;
        double dt = dureePlain.count();
        averageVolatileTime += dt;
        std::cout << "\tTemps : " << dt << "s." << std::endl;
    }
    std::cout << "--------------------------------------------------------" << std::endl;
    std::cout << "Temps moyen passé : " << averageVolatileTime/nbSamples << "s." << std::endl;
    
    return EXIT_SUCCESS;
}
