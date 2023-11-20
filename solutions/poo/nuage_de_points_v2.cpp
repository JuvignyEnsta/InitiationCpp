#include <stdexcept>
#include "nuage_de_points_v2.hpp"
using namespace std::string_literals;

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

NuageDePoints::NuageDePoints( std::istream& input )
{
    std::size_t nbPts;
    input >> nbPts;
    m_points.reserve(nbPts);
    for (std::size_t ind = 0; ind < nbPts; ++ind )
    {
        double x,y;
        input >> x >> y;
        m_points.emplace_back( std::array{x,y} );
    }
}

NuageDePoints::operator std::string() const
{
    std::string repr("Nombre points : ");
    repr += std::to_string(size()) + "\n[ ";
    repr += "[ ("s + std::to_string(m_points[0][0]) + ", "s
                   + std::to_string(m_points[0][1]) +"),...,("
                   + std::to_string(m_points[size()-1][0]) + ", "s
                   + std::to_string(m_points[size()-1][1]) + ") ]"s;
    return repr;
}

std::ostream& 
NuageDePoints::write( std::ostream& output ) const
{
    output << size() << std::endl;
    for (auto const& pt : m_points )
    {
        output << pt[0] << " " << pt[1] << std::endl;
    }
    return output;
}

auto NuageDePoints::barycentre() const -> Point
{
    Point bary{0.,0.};
    for (auto const& pt : m_points )
        {
            bary[0] += pt[0];
            bary[1] += pt[1];
        }
    bary[0] /= size();
    bary[1] /= size();
    return bary;
}
