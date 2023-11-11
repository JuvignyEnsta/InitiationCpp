#include <iostream>
#include <vector>
#include <array>
#include <string>
using namespace std::string_literals;

template<typename HeadType, typename... Args> std::ostream& 
print0(std::ostream& out, HeadType const& head, Args const& ... args ) {
    out << head;
    //((out << " " << args)...);// Donne erreur de compilation !
    ((out << " " << args),...); // Utilise en fait les folds expressions
    return out;
}

template<typename HeadType, typename... Args> std::ostream& 
print1(std::ostream& out, HeadType const& head, Args const& ... args ) {
    out << head;
    [[maybe_unused]] auto tmp = { ( out << " " << args,0)... };
    return out;
}

template<typename HeadType, typename... Args> std::ostream& 
print2(std::ostream& out, HeadType const& head, Args const& ... args ) {
    out << head;
    out << " " << (args,...);
    return out;
}

template<typename... Ts> void f(Ts... args)
{
    std::array<int,sizeof...(args)> indices{args...};
    int tot = 0;
    for (auto const& i : indices) tot += i;
    std::cout << "tot = " << tot << std::endl;
}

template<typename... Ts> auto adder( Ts const& ...args)
{
    return (args + ...);
}

template<typename... Ts> auto concatenate( Ts const& ...args)
{
    return ((args + " "s) + ...);
}


int main()
{
    int a = (3.14,4);
    std::cout << (3.14,4) << std::endl;
    std::cout << "a = " << a << std::endl;

    f(1,2,3,4);

    print0(std::cout, "Message", 3, "tintin", 3.14, "Fin\n");
    print1(std::cout, "Message", 3, "tintin", 3.14, "Fin\n");
    print2(std::cout, "Message", 3, "tintin", 3.14, "Fin\n");

    std::cout << "adder(1) = " << adder(1) << std::endl;
    std::cout << "adder(1.1,2.2) = " << adder(1.1,2.2) << std::endl;
    std::cout << "adder(1,2,3,4,5) = " << adder(1,2,3,4,5) << std::endl;

    auto phrase = concatenate("Tintin","et","milou","en","balade");
    std::cout << phrase << std::endl;
    return EXIT_SUCCESS;
    }