#include <iostream>
#include <cstdint>

int main(int nargs, char *argv[])
{
    if (nargs != 2)
    {
        std::cerr << "Donnez la valeur initiale de la suite u_n" << std::endl;
        return EXIT_FAILURE;
    }

    std::int32_t u_n = std::stol(argv[1]);
    std::int32_t niters = 0;
    while (u_n != 1L)
    {
        if (u_n % 2 == 0)
            u_n /= 2;
        else 
            u_n = 3*u_n + 1;
        std::cout << "u_" << niters << " = " << u_n << std::endl;
        // u_n = u_n % 2 == 0 ? u_n/2 : 3*u_n + 1;
        ++niters;
    }
    std::cout << "Longueur de vol : " << niters << std::endl;
    return EXIT_SUCCESS;
}