#ifndef _POO_TRIANGULARMESH_HPP_
#define _POO_TRIANGULARMESH_HPP_
#include <vector>
#include <memory>
#include <cstdint>
#include <array>

namespace meshes
{
class TriangularMesh
{
public:
    using index = std::uint32_t;
    using Vertex= std::array<double,3>;

    TriangularMesh() = default;
    TriangularMesh( std::vector<index> const& t_elt2nds, 
                    std::vector<Vertex> const& t_vertices );
    TriangularMesh( TriangularMesh const& ) = default;
    TriangularMesh( TriangularMesh     && ) = default;
    ~TriangularMesh() = default;

    class Vertices;

    Vertex getNode( index i ) const;
private:
    std::vector<index> m_elt2nodes{};
    std::shared_ptr<Vertices> m_pt_vertices = nullptr;
};
}

#endif