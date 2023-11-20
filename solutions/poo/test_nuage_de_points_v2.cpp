#include <cstdlib>
#include <fstream>
#include "nuage_de_points_v2.hpp"

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

    NuageDePoints nuage6({ Point{-1.,0.}, Point{-1.,-1.}, Point{0.,-1.} });

    NuageDePoints nuage7 = nuage5 + nuage6;

    NuageDePoints::Point tr{0., 1.};
    nuage7 += tr;

    // Afficher le nuage 7 sous forme chaîne de caractère :
    std::cout << "Nuage 7 : " << std::string(nuage7) << std::endl;

    // Sauvegarer le nuage dans un fichier :
    std::ofstream fich("sortie.dat");
    fich << nuage7;
    fich.close();

    // Relive nuage à partir d'un fichier :
    std::ifstream input("sortie.dat");
    NuageDePoints nuage8(input);
    for (int index = 0; auto const& pt : nuage8)
    {
        std::cout << index+1 << " : " << pt[0] << ", " << pt[1] << std::endl;
    }
    auto barycentre = nuage8.barycentre();
    std::cout << "Barycentre du nuage  : " << barycentre[0] << ", " << barycentre[1] << std::endl;

    std::cout << "Nombre de points dans nuage8 : " << nuage8.size() << std::endl;

    return EXIT_SUCCESS;
}
