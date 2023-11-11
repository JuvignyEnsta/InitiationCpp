#include <string>
#include <iostream>
using namespace std::string_literals;

int main()
{
  std::string chaineVide;
  std::string simpleLigne{"Une simple ligne"};
  std::string uneChaineUTF8{"π = 3.14"};

  std::cout << uneChaineUTF8 << std::endl;

  std::cout << "Une chaine contenant avant les deux points :"s.size() << std::endl;
  return EXIT_SUCCESS;
}
