#define TRACE
//#define MOVABLE_OPERATORS
#include <vector>
#include <cassert>
#include <iostream>
#include <utility>

template<typename K> class Vector
{
public:
    Vector( std::size_t t_dim ) : m_coefs(t_dim)
    {
#      if defined(TRACE)
       std::cout << __PRETTY_FUNCTION__ << std::endl;
#      endif
    }
    Vector( std::vector<K> const& coefs ) : m_coefs(coefs)
    {
#      if defined(TRACE)
       std::cout << __PRETTY_FUNCTION__ << std::endl;
#      endif
    }
    Vector( std::vector<K>&& coefs ) : m_coefs(std::move(coefs))
    {
#      if defined(TRACE)
       std::cout << __PRETTY_FUNCTION__ << std::endl;
#      endif
    }
    Vector( Vector const& ) = delete;
    Vector( Vector     && u) : m_coefs(std::move(u.m_coefs))
    {
#      if defined(TRACE)
       std::cout << __PRETTY_FUNCTION__ << std::endl;
#      endif
    }
    ~Vector()
    {
#      if defined(TRACE)
       std::cout << __PRETTY_FUNCTION__ << std::endl;
#      endif
    }

    Vector& operator = ( Vector const& ) = delete;
    Vector& operator = ( Vector     && u)
    {
#       if defined(TRACE)
        std::cout << __PRETTY_FUNCTION__ << std::endl;
#       endif
        if (this != &u)
        {
            m_coefs = std::move(u.m_coefs);
        }
        return *this;
    }

    std::size_t dim() const { return m_coefs.size(); }

    Vector operator + ( Vector const& u ) const {
#      if defined(TRACE)
       std::cout << __PRETTY_FUNCTION__ << std::endl;
#      endif
        assert(dim() == u.dim());
        Vector w(u.dim());
        for (std::size_t i=0; i<dim(); ++i) w[i] = u[i] + m_coefs[i];
        return w;
    }
#if defined(MOVABLE_OPERATORS)
    Vector&& operator + ( Vector && u ) const {
#      if defined(TRACE)
       std::cout << __PRETTY_FUNCTION__ << std::endl;
#      endif
        assert(dim() == u.dim());
        for (std::size_t i=0; i<dim(); ++i) u[i] += m_coefs[i];
        return std::move(u);
    }
#endif

    Vector operator - ( Vector const& u ) const {
#      if defined(TRACE)
       std::cout << __PRETTY_FUNCTION__ << std::endl;
#      endif
        assert(dim() == u.dim());
        Vector w(u.dim());
        for (std::size_t i=0; i<dim(); ++i) w[i] = m_coefs[i] - u[i];
        return w;
    }

#if defined(MOVABLE_OPERATORS)
    Vector&& operator - ( Vector && u ) const {
#      if defined(TRACE)
       std::cout << __PRETTY_FUNCTION__ << std::endl;
#      endif
        assert(dim() == u.dim());
        for (std::size_t i=0; i<dim(); ++i) u[i] = m_coefs[i] - u[i];
        return std::move(u);
    }
#endif
    K operator | ( Vector const& u ) const 
    {
#      if defined(TRACE)
       std::cout << __PRETTY_FUNCTION__ << std::endl;
#      endif
        assert(dim() == u.dim());
        K sum(0);
        for ( std::size_t i=0; i<dim(); ++i) sum += m_coefs[i]*u[i];
        return sum;
    }

    Vector homothetie( K const& alpha ) const
    {
#      if defined(TRACE)
       std::cout << __PRETTY_FUNCTION__ << std::endl;
#      endif
        Vector w(dim());
        for (std::size_t i=0; i<dim(); ++i) w[i] = alpha*m_coefs[i];
        return w;
    }

    K& operator[] ( std::size_t i )
    {
        assert(i < dim());
        return m_coefs[i];
    }

    K const& operator[] ( std::size_t i ) const
    {
        assert(i < dim());
        return m_coefs[i];
    }
private:
    std::vector<K> m_coefs;
};

template<typename K> std::ostream& operator << ( std::ostream& out, Vector<K> const& u )
{
    out << "< ";
    for (std::size_t i=0; i<u.dim(); ++i ) out << u[i] << " ";
    out << ">";
    return out;
}

template<typename K> Vector( std::vector<K> const& ) -> Vector<K>;
template<typename K> Vector( std::vector<K>     && ) -> Vector<K>;

template<typename K> Vector<K> operator * ( K const& alpha, Vector<K> const& u )
{   return u.homothetie(alpha); }

int main()
{
    Vector u(std::vector{ 1., 2., 3., 4.});
    Vector v(std::vector{ -1.,1.,-1.,1.} );

    auto w = v - (u|v)*u;

    std::cout << "w = " << w << std::endl;
    return EXIT_SUCCESS;
}