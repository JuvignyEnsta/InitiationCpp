#include <format>
#include <iostream>
#include <string>

// Le code ne compile pour l'instant qu'avec MSVC 16.10 et supérieur !

int main()
{
    auto phrase = std::format("On n'est pas sérieux quand on a {} ans. Foin des {} et de la {}.", 
                              17, "bocks", "limonade");

    std::cout << phrase << std::endl;

    return EXIT_SUCCESS;
}

