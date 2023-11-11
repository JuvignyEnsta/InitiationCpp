#include <iostream>

int main()
{
    char c  = '#';
    std::cout << "c = " << c << std::endl;
    c = 97;
    std::cout << "c = " << c << std::endl;

    for (char c = 32; c < 127; ++c)
        std::cout << c << " ";
    std::cout << std::endl;

    return EXIT_SUCCESS;
}
