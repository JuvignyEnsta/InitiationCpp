#include <source_location>
#include <iostream>
#include <cstdlib>



int une_fonction() {
    std::source_location location = std::source_location::current();
    std::cout << "Je suis dans la fonction " << location.function_name() << std::endl;
    std::cout << "A la ligne : " << std::source_location::current().line() << std::endl;
    return int(std::source_location::current().column());
}

int main() {
    std::source_location location = std::source_location::current();
    std::cout << "Je suis dans le fichier " << location.file_name() << std::endl;
    int col = une_fonction();
    std::cout << "Retour à la colonne " << col << std::endl;

    return EXIT_SUCCESS;
}
