#include <stdexcept>
#include "nuage_de_points_v1.hpp"

NuageDePoints::NuageDePoints( std::uint32_t t_début, std::uint32_t t_fin, 
                              NuageDePoints const& t_nuage ) try :
    m_points(t_fin-t_début)
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    for (std::size_t ind = 0; ind < m_points.size(); ++ind )
        m_points[ind] = t_nuage.m_points[ind+t_début];
}
catch(std::bad_alloc& err)
{
    if (t_fin < t_début) {
        throw std::logic_error("Index de fin plus petit qu'index début");
    }
    else throw err;
}
//
NuageDePoints::NuageDePoints( std::initializer_list<Point> const& t_points )
    :   m_points(t_points)
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}

