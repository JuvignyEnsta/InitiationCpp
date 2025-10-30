#include <cstdlib>
#include <cstddef>
#include <iostream>
#include <memory>
#include <execution>
#include <algorithm>
#include <array>
#include <numeric>
#include <cassert>

struct Point {
    Point( double x, double y, double z, double w ) : coordinates{x,y,z,w} {}
    ~Point() = default;
    std::array<double,4> coordinates{};
};

std::ostream& operator << ( std::ostream& out, Point const& point )
{
    out << "(" << point.coordinates[0] << ", " << point.coordinates[1] << ", "
        << point.coordinates[2] << ", " << point.coordinates[3] << ")";
    return out;
}

int main()
{
    std::array<std::byte, 4096> bufferMemory; 
    void* memoireAlignee = bufferMemory.data(); std::size_t espace_restant=4096;
    Point* poolPoints = (Point*)std::align(128,bufferMemory.size()-128, memoireAlignee, espace_restant);
    assert( (poolPoints != nullptr) && (poolPoints == memoireAlignee));
    auto vecteur = std::construct_at(poolPoints, 3.4, 1.5, 2.6, 3.14);

    std::cout << *vecteur << std::endl;

    std::destroy_at(vecteur);

    std::array<int,10> sequence; std::iota(sequence.begin(),sequence.end(),0);
    std::for_each(std::execution::par, sequence.begin(), sequence.end(), [=](int i){ std::construct_at(poolPoints+i, 3.4*i, 1.5*i, 2.6*i, 3.14*i); } );

    for ( int i = 0; i < 10; ++i )
    {
        auto& ptVecteur = poolPoints[i];
        std::cout << ptVecteur << "\t";
    }
    std::cout << std::endl;

    std::destroy_n(std::execution::par, poolPoints, 10);

    return EXIT_SUCCESS;
}