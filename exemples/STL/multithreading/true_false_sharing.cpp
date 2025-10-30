#include <iostream>
#include <thread>
#include <new>
#include <chrono>
#include <iomanip>

#ifdef __cpp_lib_hardware_interference_size
    using std::hardware_constructive_interference_size;
    using std::hardware_destructive_interference_size;
#else
    // 64 bytes on x86-64 │ L1_CACHE_BYTES │ L1_CACHE_SHIFT │ __cacheline_aligned │ ...
    constexpr std::size_t hardware_constructive_interference_size = 64;
    constexpr std::size_t hardware_destructive_interference_size = 64;
#endif

std::mutex printMutex;
constexpr unsigned maxWriteIterations = 10'000'000u;
auto now = []() { return std::chrono::high_resolution_clock::now(); };

// Permet d'aligner la structure afin qu'elle tient dans une ligne de cache
struct alignas(hardware_constructive_interference_size) InterneLigneCache_t {
    std::atomic_uint64_t x{};
    std::atomic_uint64_t y{};
} interneLigneCache;

// Permet que les deux membres de la structure ne soient pas dans la même ligne de cache.
struct EnDehorsLigneCache_t {
    alignas(hardware_destructive_interference_size) std::atomic_uint64_t x{};
    alignas(hardware_destructive_interference_size) std::atomic_uint64_t y{};
} enDehorsLigneCache;

template<bool modifyX>
void fonctionUneLigneCache() {
    const auto start = now();
    for (std::uint64_t count{0}; count != maxWriteIterations; ++count)
        if constexpr (modifyX)
           interneLigneCache.x.fetch_add(1, std::memory_order_relaxed);
        else
           interneLigneCache.y.fetch_add(1, std::memory_order_relaxed);
    const std::chrono::duration<double, std::milli> elapsed { now() - start };
    std::lock_guard lk{printMutex};
    std::cout << "Temps passé avec une ligne de cache " << elapsed.count() << " ms\n";
    interneLigneCache.x = elapsed.count();
    interneLigneCache.y = elapsed.count();
}

template<bool modifyX>
void fonctionDeuxLignesCache() {
    const auto start = now();
    for (std::uint64_t count{0}; count != maxWriteIterations; ++count)
        if constexpr (modifyX)
           enDehorsLigneCache.x.fetch_add(1, std::memory_order_relaxed);
        else
           enDehorsLigneCache.y.fetch_add(1, std::memory_order_relaxed);
    const std::chrono::duration<double, std::milli> elapsed { now() - start };
    std::lock_guard lk{printMutex};
    std::cout << "Temps passé avec deux lignes de cache " << elapsed.count() << " ms\n";
    enDehorsLigneCache.x = elapsed.count();
    enDehorsLigneCache.y = elapsed.count();
}

int main() {
    std::cout << "__cpp_lib_hardware_interference_size "
#   ifdef __cpp_lib_hardware_interference_size
        " = " << __cpp_lib_hardware_interference_size << '\n';
#   else
        "is not defined, use " << hardware_destructive_interference_size << " as fallback\n";
#   endif
 
    std::cout
        << "hardware_destructive_interference_size == "
        << hardware_destructive_interference_size << '\n'
        << "hardware_constructive_interference_size == "
        << hardware_constructive_interference_size << "\n\n";
 
    std::cout
        << std::fixed << std::setprecision(2)
        << "sizeof( InterneLigneCache_t ) == " << sizeof( InterneLigneCache_t ) << '\n'
        << "sizeof( EnDehorsLigneCache_t ) == " << sizeof( EnDehorsLigneCache_t ) << "\n\n";
 
    constexpr int max_runs{4};
 
    int moyenne_uneLigneCache{0};
    for (auto i{0}; i != max_runs; ++i) {
        std::thread th1{fonctionUneLigneCache<0>};
        std::thread th2{fonctionUneLigneCache<1>};
        th1.join(); th2.join();
        moyenne_uneLigneCache += interneLigneCache.x;
    }
    std::cout << "Average T1 time: " << (moyenne_uneLigneCache / max_runs) << " ms\n\n";

    int moyenne_deuxLignesCache{0};
    for (auto i{0}; i != max_runs; ++i) {
        std::thread th1{fonctionDeuxLignesCache<0>};
        std::thread th2{fonctionDeuxLignesCache<1>};
        th1.join(); th2.join();
        moyenne_deuxLignesCache += enDehorsLigneCache.x;
    }
    std::cout << "Average T2 time: " << (moyenne_deuxLignesCache / max_runs) << " ms\n\n";
 
    std::cout << "Ratio T1/T2:~ " << 1.*moyenne_uneLigneCache/moyenne_deuxLignesCache << '\n';

    return EXIT_SUCCESS;
}
