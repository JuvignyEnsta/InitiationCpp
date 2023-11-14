#include <iostream>
#include <string>
#include <cmath>
#include <cstdio>

int main( int nargs, char *argv[] )
{
    if (nargs < 4 )
    {
        std::cerr << "Le programme attend trois réels a,b et c" << std::endl;
        return EXIT_FAILURE; 
    }
    double a = std::stod(argv[1]);
    double b = std::stod(argv[2]);
    double c = std::stod(argv[3]);

    //printf("a = %d, b = %d et c = %d\n", a, b, c);
    //fprintf(stderr, "a = %d, b = %d et c = %d\n", a, b, c);
    std::cout  << "a = " << a << ", b = " << b << ", c = " << c << std::endl;

    if (a == 0) {
        std::cerr << "a doit être non nul, sinon équation linéaire." << std::endl;
        return EXIT_FAILURE;
    }

    double delta = b*b - 4*a*c;
    if (delta < 0) {
        std::cout << "Discriminant négatif. Pas de solution dans ℝ" << std::endl;
        return EXIT_SUCCESS;
    }

    double x1 = (-b + std::sqrt(delta))/(2*a);
    double x2 = (-b - std::sqrt(delta))/(2*a);

    std::cout << "Solution de l'équation " << a << "x² + " << b << "x + " << c << " = 0 : "
              << x1 << " et " << x2 << std::endl;
    return EXIT_SUCCESS;
}