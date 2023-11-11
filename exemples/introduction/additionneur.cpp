#include <iostream>
int main( int nargs, char *argc[]) {
    int x = std::stoi(argc[1]);
    int y = std::stoi(argc[2]);
    std::cout << x << " + " << y << " = " << x+y << std::endl;
    return EXIT_SUCCESS;
}
