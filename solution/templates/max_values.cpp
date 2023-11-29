#include <iostream>

template<typename T1> auto max_values( T1 const& v1) -> T1
{
    return v1;   
}

template<typename T1, typename... Ts> auto max_values( T1 const& v1, Ts const&... vs ) -> decltype((v1+...+vs))
{
    auto val = max_values(vs...);
    return v1 > val ? v1 : val;
}

int main()
{
    std::cout << "Max of {3.14} = "
              << max_values(3.14) << std::endl;

    std::cout << "Max of {3.14, 5} = "
              << max_values(3.14, 5) << std::endl;

    std::cout << "Max of {5, 2, 3.14, 12, -7.2f, 8LL, -7L} = "
              << max_values(5, 2, 3.14,  12, -7.2f, 8LL, -7L) << std::endl;
    return EXIT_SUCCESS;
}