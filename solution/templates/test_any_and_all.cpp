#include <iostream>

template<typename ... Ts> bool testAny( Ts const& ... predicats )
{
    return (false || ... || predicats);
}

template<typename ... Ts> bool testAll( Ts const& ... predicats )
{
    return (true && ... && predicats);
}

int main()
{
    std::cout << "testAny( (1<0), (2>3), (1<=4), (2>5) ) -> " << std::boolalpha << testAny((1<0), (2>3), (1<=4), (2>5)) << std::endl;
    std::cout << "testAny( (1<0), (2>3), (1<=-1), (2>5) ) -> " << std::boolalpha << testAny((1<0), (2>3), (1<=-1), (2>5)) << std::endl;

    std::cout << "testAll( (1<0), (2>3), (1<=4), (2>5) ) -> " << std::boolalpha << testAll((1<0), (2>3), (1<=4), (2>5)) << std::endl;
    std::cout << "testAll( (1<3), (5>3), (1<=-1), (7>5) ) -> " << std::boolalpha << testAny((1<3), (5>3), (1<=-1), (7>5)) << std::endl;
    return EXIT_SUCCESS;
}