#include <any>
#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
using namespace std::string_literals;
#if defined(__clang__) || defined(__GNUC__)
#include <cxxabi.h>
std::string demangle( const char* mangled )
{
    int status;
    char* c_demangled = abi::__cxa_demangle( mangled , nullptr, nullptr, &status);
    std::string ret(c_demangled);
    free(c_demangled);
    return ret;
}
#else
std::string demangle( const char* mangled )
{
    return std::string(mangled);
}
#endif

int main()
{
    std::any a_variable; a_variable = 3;
    std::cout<<demangle(a_variable.type().name())<<" : "<<std::any_cast<int>(a_variable)<<std::endl;
    a_variable = std::vector<double>{2.,3.,5.,7.,11.};
    std::cout << demangle(a_variable.type().name()) << " : " 
              << std::any_cast<std::vector<double>>(a_variable)[0] << std::endl;
    std::cout << std::boolalpha << "a_variable contient un vecteur de double ? "
              << (typeid(std::vector<double>) == a_variable.type()) << std::endl;
    try { a_variable = "tintin"s; std::cout << std::any_cast<float>(a_variable) << std::endl; } 
    catch(const std::bad_any_cast& e) { std::cout << e.what() << std::endl; }
    a_variable.reset();
    if (a_variable.has_value())
        std::cout<<demangle(a_variable.type().name())<<" : "<<std::any_cast<int>(a_variable)<<std::endl;
    std::cout << "type de a = void ? " << (a_variable.type() == typeid(void)) << std::endl;

    std::vector<std::any> tableau(3);
    tableau[0] = "Tintin"s;
    tableau[1] = 3.14;
    tableau[2] = 4;
    for ( auto const& value : tableau )
    {
        if (value.type() == typeid(std::string))
            std::cout << std::any_cast<std::string>(value) << " ";
        else if (value.type() == typeid(int))
            std::cout << std::any_cast<int>(value) << " ";
        else if (value.type() == typeid(double))
            std::cout << std::any_cast<double>(value) << " ";
    }
    std::cout << std::endl;
    return EXIT_SUCCESS; 
}
