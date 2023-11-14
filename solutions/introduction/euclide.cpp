#include <iostream>
#include <cassert>
#include <string>

long pgcd( long a, long b )
{
    // Préconditions
    assert(a>=0);
    assert(b>=0);

    while (b != 0)
    {
        long t = b;
        b = a % b;
        a = t;
    }
    // Postcondition
    assert(a >= 0);
    return a;
}

int main(int nargs, char *argv[])
{
    if (nargs != 3)
    {
        std::cerr << "Veuillez rentrer deux entiers" << std::endl;
        return EXIT_FAILURE;
    }
    auto a = std::stol(argv[1]);
    auto b = std::stol(argv[2]);

    auto c = pgcd(a,b);
    std::cout << "PGCD(" << a << ", " << b << ") = " << c << std::endl;

    return EXIT_SUCCESS;
}