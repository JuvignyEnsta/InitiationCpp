#include <iostream>
#include <array>
#include <cstddef>

struct Point
{   double x,y,z;    }; // alignof => 8 octets


struct alignas(alignof(long double)) BigPoint 
{ double x,y,z;  }; // alignof(BigPoint) == 16 octets

template<typename T> void testAlignement()    {
    std::array<T,10> tableau; std::byte* pt1stElt = (std::byte*)&tableau[0], *pt2ndElt = (std::byte*)&tableau[1];
    std::cout << "Alignement mémoire : " << alignof(T) << std::endl;   
    std::cout << "Adresse du tableau : " << (void*)tableau.data() << ", adresse du 1er élt : " << (void*)&tableau[0]
              << ", Adresse du 2e élt: " << (void*)&tableau[1] << " Distance entre 1er et 2e elt : " << std::distance(pt1stElt,pt2ndElt) << std::endl;
}

int main()   {
    testAlignement<char>();
    testAlignement<double>();
    testAlignement<long double>();
    testAlignement<Point>();
    testAlignement<BigPoint>();

    return EXIT_SUCCESS;
}