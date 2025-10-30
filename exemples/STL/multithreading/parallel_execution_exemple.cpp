#include <execution>
#include <algorithm>
#include <chrono>
#include <random>
#include <iostream>

template<typename ExecutionPolicy>
void performanceDuTri( ExecutionPolicy&& policy, std::string const& label, 
                       std::vector<std::size_t> tableau) {
    auto start = std::chrono::high_resolution_clock::now();
    std::sort(policy, tableau.begin(), tableau.end());
    auto end   = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> dt = end - start;
    std::cout << "Durée du tri " << label << " : " << dt.count() << std::endl;
}

int main()
{
    std::default_random_engine generator;
    std::uniform_int_distribution<std::size_t> distribution(1ULL,1'000'000ULL);
    std::vector<std::size_t> tableau(1'000'000);
    for ( auto& val : tableau ) val = distribution(generator);
    performanceDuTri( std::execution::seq, "séquentiel",tableau);
    performanceDuTri( std::execution::par, "parallèle", tableau);
    performanceDuTri( std::execution::unseq, "non séquencé", tableau);
    performanceDuTri( std::execution::par_unseq, "parallèle non séquencé", tableau);
    return EXIT_SUCCESS;

}