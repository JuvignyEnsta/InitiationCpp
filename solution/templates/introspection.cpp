#include <iostream>
#include <utility>
#include <list>
#include <vector>

template<typename K> struct isContainer
{
    template<typename C> static constexpr decltype(std::declval<C>().size(),std::declval<C>().begin(),bool()) test(int) { return true; }
    template<typename C> static constexpr bool test(...) { return false; }

    static constexpr bool value = test<K>(int());
};

template<typename K, bool a> struct restrictorFlag {     };
template<typename K> struct restrictorFlag<K,true> { using value_type = typename K::value_type; };//std::remove_reference_t<decltype(*std::declval<K>().begin())>;   };

template<typename Conteneur> struct hasDirectAccess
{
    template<typename C> static constexpr decltype(std::declval<C>()[0],bool()) test(int) { return true; }
    template<typename C> static constexpr bool test(...) { return false; }

    static constexpr bool value = test<Conteneur>(int());
};

template<typename Conteneur> typename restrictorFlag<Conteneur,isContainer<Conteneur>::value>::value_type
median( Conteneur const& c )
{
    if constexpr(hasDirectAccess<Conteneur>::value)
    {
        return c[c.size()/2];
    }
    else
    {
        auto iter = c.begin();
        iter = std::next(iter, c.size()/2);
        return *iter;
    }
}

int main()
{
    std::cout << std::boolalpha << "int is Container ? " << isContainer<int>::value << std::endl; 
    std::cout << std::boolalpha << "std::list<int> is Container ? " << isContainer<std::list<int>>::value << std::endl; 
    std::cout << std::boolalpha << "std::vector<int> is Container ? " << isContainer<std::vector<int>>::value << std::endl; 

    std::cout << std::boolalpha << "int is direct access Container ? " << hasDirectAccess<int>::value << std::endl; 
    std::cout << std::boolalpha << "std::list<int> is Container ? " << hasDirectAccess<std::list<int>>::value << std::endl; 
    std::cout << std::boolalpha << "std::vector<int> is Container ? " << hasDirectAccess<std::vector<int>>::value << std::endl; 

    std::cout << "median of {1,2,3,4,5} -> " << median(std::vector{1,2,3,4,5}) << std::endl;
    std::cout << "median of {1,2,3,4,5} -> " << median(std::list{1,2,3,4,5}) << std::endl;
    std::cout << "median of {1,2,3,4,5} -> " << median(std::initializer_list{1,2,3,4,5}) << std::endl;
    //std::cout << "median of 1 -> " << median(1) << std::endl;


    return EXIT_SUCCESS;
}
