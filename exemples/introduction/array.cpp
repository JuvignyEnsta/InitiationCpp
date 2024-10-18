#include <cstdlib>
#include <iostream>
#include <array>

int main()
{
    std::array<int, 3> indice1;
    for (auto ind : indice1) std::cout << ind << " ";
    std::cout << std::endl;

    indice1.fill(-1);
    indice1[1] = 0;
    for (auto ind : indice1) std::cout << ind << " ";

    std::cout << std::endl;
    std::array e1{1.,0.,0.};
    std::array<double, 3> e2{0.,1.,0.};

    std::array<std::array<double,3>,3> I = { e1, e2, {0.,0.,1.} };

    for (auto const & row : I)
    {
        for (auto coef : row)
        {
            std::cout << coef << "\t";
        }
        std::cout << std::endl;
    }

    return EXIT_SUCCESS;
}