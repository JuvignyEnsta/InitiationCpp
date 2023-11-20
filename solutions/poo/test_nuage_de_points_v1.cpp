#include <cstdlib>
#include "nuage_de_points_v1.hpp"

int main()
{
    using Point = NuageDePoints::Point;
    NuageDePoints nuage1(10);
    NuageDePoints nuage2(nuage1);
    NuageDePoints nuage3;
    NuageDePoints nuage4(2, 5, nuage1);
    NuageDePoints nuage5({ Point{1.,0.}, Point{1.,1.}, Point{0.,1.} });

    try 
    {
        NuageDePoints nuage(1'000'000'000LL);
    }
    catch(std::bad_alloc& err)
    {
        std::cout << "Pas pu réserver 1'000'000'000 de points " << std::endl;
        std::cout << "Erreur : " << err.what() << std::endl;
    }

    try
    {
        NuageDePoints nuage4(5, 2, nuage1);
    }
    catch(std::logic_error& err)
    {
        std::cout << "Problème passage paramètre :  " << err.what() << std::endl;
    }
    catch(std::bad_alloc& err)
    {
        std::cout << "Pas pu réserver points partiels " << std::endl;
        std::cout << "Erreur : " << err.what() << std::endl;        
    }
    return EXIT_SUCCESS;
}
