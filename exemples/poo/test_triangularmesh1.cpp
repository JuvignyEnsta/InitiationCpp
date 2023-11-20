#include <iostream>
#include "triangularMesh1.hpp"
using namespace meshes;

int main()
{
    using index = TriangularMesh::index;
    using Vertex= TriangularMesh::Vertex;
    TriangularMesh m( std::vector<index>{ 0, 1, 2, 2, 3 ,0}, 
                      std::vector{ Vertex{0.,0.,0.}, {1.,0.,0.}, 
                                         {1.,1.,0.}, {0.,1.,0.} });
    auto v = m.getNode(1);
    std::cout << v[0] << ", " << v[1] << ", " << v[2] << std::endl;

    return EXIT_SUCCESS;
}