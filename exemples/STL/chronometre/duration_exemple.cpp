#include <chrono>
#include <iostream>
#include <vector>
#include <numeric>

int main(){
    for ( std::size_t size = 10; size < 1'000'000; size += 10'000)
    {
        auto start = std::chrono::high_resolution_clock::now();
        std::vector<double> tab(size, 1.);
        [[maybe_unused]] auto sum = std::accumulate(tab.begin(), tab.end(), 0.);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> diffsec = end - start;
        std::chrono::duration<double,std::micro> diffmsec = end - start;
        std::chrono::duration<float, std::ratio<1,24>> frame = end - start;
        std::cout << "Temps traitement avec taille " << size << " => "
                  << diffsec.count() << " secondes soit " << diffmsec.count() << "msec" 
                  << "soit " << 1./frame.count() << " images par seconde" << std::endl;  
    }
    return EXIT_SUCCESS;
}
