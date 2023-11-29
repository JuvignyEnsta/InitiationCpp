#include <iostream>
#include <string>

using namespace std::string_literals;

std::string concatenate1( std::string const& s1 )
{
    return s1;
}

template<typename... Ts> std::string concatenate1( std::string const& s1, Ts const& ... args )
{
    return s1 + " "s + concatenate1(args...);
}

template<typename... Ts> std::string concatenate2( Ts const& ... args )
{
    return ((args + " "s) + ...);
}

int main()
{
    auto phrase = concatenate1("Tintin"s, "et"s, "milou"s);
    std::cout << phrase << std::endl;

    phrase = concatenate2("Tintin", "et", "milou");
    std::cout << phrase << std::endl;
    
    return EXIT_SUCCESS;
}
