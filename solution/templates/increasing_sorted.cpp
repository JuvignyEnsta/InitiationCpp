#include <iostream>

template<typename T> bool isIncreasingSorted( T const& v )
{
    return true;
}

template<typename T1, typename T2> bool isIncreasingSorted( T1 const& v1, T2 const& v2 )
{
    return v1 <= v2;
}

template<typename T1, typename T2, typename... Ts> bool isIncreasingSorted( T1 const& v1, T2 const& v2, Ts const&... vs)
{
    return isIncreasingSorted(v2, vs...) && (v1 <= v2);
}


int main()
{
    std::cout << "is increasing {1., 2, 4L, 6.f, 10} -> " << std::boolalpha << isIncreasingSorted(1., 2, 4L, 6.f, 10) << std::endl;
    std::cout << "is increasing {1., 4L, 2, 6.f, 10} -> " << std::boolalpha << isIncreasingSorted(1., 4L, 2, 6.f, 10) << std::endl;

    return EXIT_SUCCESS;
}