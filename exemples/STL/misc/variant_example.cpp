#include <iostream>
#include <variant>
#include <string>
using namespace std::string_literals;

int main()
{
    std::variant<double, int, std::string> unionVariable;
    static_assert(std::variant_size_v<decltype(unionVariable)> == 3);

    std::visit([](auto var) { std::cout << var; }, unionVariable);
    std::cout << "\nIndex du type utilisé : " << unionVariable.index() << std::endl;

    unionVariable = 3.14;
    std::visit([](auto var) { std::cout << var; }, unionVariable);
    std::cout << "\nIndex du type utilisé : " << unionVariable.index() << std::endl;

    unionVariable = 3;
    std::visit([](auto var) { std::cout << var; }, unionVariable);
    std::cout << "\nIndex du type utilisé : " << unionVariable.index() << std::endl;

    unionVariable = "Tintin"s;
    std::visit([](auto var) { std::cout << var; }, unionVariable);
    std::cout << "\nIndex du type utilisé : " << unionVariable.index() << std::endl;

    if (const auto intPtr (std::get_if<int>(&unionVariable)); intPtr)
        std::cout << "int : " << *intPtr << std::endl;

    if (const auto strPtr (std::get_if<std::string>(&unionVariable)); strPtr)
        std::cout << "std::string : " << *strPtr << std::endl;

    if (std::holds_alternative<int>(unionVariable)) std::cout << "Contient un entier." << std::endl;
    if (std::holds_alternative<std::string>(unionVariable)) std::cout << "Contient un std::string." << std::endl;

    try {
        auto f = std::get<double>(unionVariable);
        std::cout << "J'ai bien un réel : " << f << std::endl;
    } catch(std::bad_variant_access&)
    {   std::cout << "Impossible d'afficher un réel." << std::endl;    }

    return EXIT_SUCCESS;
}