#ifndef _NUAGE_DE_POINTS_HPP_
#define _NUAGE_DE_POINTS_HPP_
#include <array>
#include <vector>
#include <iostream>
#include <cstdint>

class NuageDePoints
{
public:
    using Point = std::array<double,2>;

    NuageDePoints() : m_points()
    {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
    }

    NuageDePoints( NuageDePoints const& u ) : m_points(u.m_points)
    {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
    } 
    NuageDePoints( NuageDePoints     && u ) : m_points(std::move(u.m_points))
    {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
    }

    NuageDePoints( std::uint32_t t_size ) try : m_points(t_size)
    {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
    }
    catch(std::bad_alloc& err)
    {
        throw err;
    }

    NuageDePoints( std::uint32_t t_début, std::uint32_t t_fin, 
                   NuageDePoints const& t_nuage );
    
    NuageDePoints( std::initializer_list<Point> const& t_points );

    ~NuageDePoints()
    {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
    }
private:
    std::vector<Point> m_points{};
};

#endif