#include <iostream>
#include <optional>
#include <utility>
#include <concepts>

template<std::integral I> std::pair<I,std::optional<I>> divmod( I const& a, I const& b ) {
    std::pair<I, std::optional<I>> resultat;
    resultat.first = a/b;
    I residu   = a - resultat.first*b;
    if (residu != 0) resultat.second = residu;
    return resultat;
}

int main()
{
    auto res1 = divmod(7,3);
    std::cout << "7/3 = " << res1.first;
    if (res1.second.has_value()) std::cout << "[" << res1.second.value() <<"]";
    res1 = divmod(24,3);
    std::cout << "\n24/3 = " << res1.first;
    if (res1.second.has_value())
        std::cout << "[" << res1.second.value() <<"]";
    std::cout << std::endl;

    return EXIT_SUCCESS;
}