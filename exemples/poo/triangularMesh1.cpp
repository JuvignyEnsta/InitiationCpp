#include <array>
#include "triangularMesh1.hpp"
using namespace meshes;

class TriangularMesh::Vertices
{
public:
    Vertices()  = default;
    Vertices( std::vector<TriangularMesh::Vertex> const& t_vertices );
    Vertices( Vertices const& ) = delete;
    Vertices( Vertices     && ) = default;
    ~Vertices() = default;

    Vertex operator[] ( index i ) const
    { return { m_coords[0][i], m_coords[1][i], m_coords[2][i]}; }
private:
    std::array<std::vector<double>,3> m_coords;
};

TriangularMesh::Vertices::Vertices( 
    std::vector<TriangularMesh::Vertex> const& t_vertices )
{
    m_coords[0] = std::vector<double>(t_vertices.size());
    m_coords[1] = std::vector<double>(t_vertices.size());
    m_coords[2] = std::vector<double>(t_vertices.size());
    for (std::size_t ind=0; ind < t_vertices.size(); ++ind )
    {
        m_coords[0][ind] = t_vertices[ind][0];
        m_coords[1][ind] = t_vertices[ind][1];
        m_coords[2][ind] = t_vertices[ind][2];
    }
}
// ==============================================================================
TriangularMesh::TriangularMesh( std::vector<index> const& t_elt2nds, 
                                std::vector<Vertex> const& t_vertices )
    :   m_elt2nodes(t_elt2nds),
        m_pt_vertices(std::make_shared<Vertices>(t_vertices))
{}

TriangularMesh::Vertex 
TriangularMesh::getNode( index i ) const
{
    return (*m_pt_vertices)[i];
}
