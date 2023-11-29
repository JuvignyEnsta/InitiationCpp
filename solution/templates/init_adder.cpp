#include<iostream>

template<typename... Ts> auto adder10( Ts const& ... args )
{
    return (10+...+args);
}

int main()
{
    std::cout << "10+1+2+3+4+10.3 = " << adder10(1,2,3,4,10.3) << std::endl;
    return EXIT_SUCCESS;
}