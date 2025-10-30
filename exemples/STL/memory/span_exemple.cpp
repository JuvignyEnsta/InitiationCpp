#include <span>
#include <iostream>
#include <vector>

template<typename T, std::size_t N>
void displayMemoryZone( std::span<T,N> const& zone ) {
    for ( auto const& value: zone )
        std::cout << value << " ";
    std::cout << std::endl;
}

int main() {
    double tableauC[] = {2.,3.,5.,7., 11.};
    std::vector tableauV{2.,3.,5.,7.,11.};

    double* cppDynamicTab = new double[5];
    cppDynamicTab[0] = 2.; cppDynamicTab[1] = 3.; cppDynamicTab[2] = 5.;
    cppDynamicTab[3] = 7.; cppDynamicTab[4] = 11.;
    std::span<double> zoneCpp(cppDynamicTab, 5);
    auto subZone = zoneCpp.subspan(1, 3);

    displayMemoryZone( std::span{tableauC} );
    displayMemoryZone( std::span{tableauV} );
    displayMemoryZone( zoneCpp );
    displayMemoryZone( subZone );

    return EXIT_SUCCESS;
}
