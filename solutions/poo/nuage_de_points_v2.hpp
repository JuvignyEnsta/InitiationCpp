#ifndef _NUAGE_DE_POINTS_HPP_
#define _NUAGE_DE_POINTS_HPP_
#include <array>
#include <vector>
#include <iostream>
#include <cstdint>
#include <cassert>
#include <string>
#include <fstream>

class NuageDePoints
{
public:
    using Point = std::array<double,2>;
    using iterator = std::vector<Point>::iterator;
    using const_iterator = std::vector<Point>::const_iterator;

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

    NuageDePoints( std::istream& input );

    ~NuageDePoints()
    {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
    }

    NuageDePoints& operator = ( NuageDePoints const& ) = default;
    NuageDePoints& operator = ( NuageDePoints     && ) = default;

    std::size_t size() const { return m_points.size(); }

    Point& operator[] ( std::size_t index )
    { assert(index < this->size()); return m_points[index]; }

    Point const& operator[] ( std::size_t index ) const
    { assert(index < this->size()); return m_points[index]; }

    NuageDePoints operator + ( NuageDePoints const& nuage )
    {
        NuageDePoints fusion(*this);
        fusion.m_points.insert(fusion.m_points.end(), 
                               nuage.m_points.begin(), nuage.m_points.end());
        return fusion;
    }

    NuageDePoints& operator += ( Point const& tr )
    {
        for (auto& pt : m_points ) {
            pt[0] += tr[0]; pt[1] += tr[1];
        }
        return *this;
    }

    explicit operator std::string() const;

    std::ostream& write( std::ostream& output ) const;

    iterator begin() { return m_points.begin(); }
    const_iterator begin() const { return m_points.begin(); }
    const_iterator cbegin() { return m_points.cbegin(); }

    iterator end() { return m_points.end(); }
    const_iterator end() const { return m_points.end(); }
    const_iterator cend() { return m_points.cend(); }

    Point barycentre() const;
private:
    std::vector<Point> m_points{};
};

inline
std::ostream& operator << ( std::ostream& out, NuageDePoints const& nuage )
{
    return nuage.write(out);
}

#endif