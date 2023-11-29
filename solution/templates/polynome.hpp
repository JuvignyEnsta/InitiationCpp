#ifndef _POLYNOME_HPP_
#define _POLYNOME_HPP_
#include <cassert>
#include <vector>
#include <cstdint>
#include <iostream>
#include <string>
using namespace std::string_literals;

template<typename K>
class Polynome 
{
public:
    Polynome() = default;
    Polynome( std::int32_t deg  ) : m_monomes(deg+1)
    {}
    Polynome( std::vector<K> const& t_coefs ) : m_monomes(t_coefs)
    {}
    Polynome( std::vector<K>&& t_coefs) : m_monomes(std::move(t_coefs))
    {}
    Polynome( std::istream& input );
    Polynome( Polynome const& ) = default;
    Polynome( Polynome     && ) = default;

    ~Polynome() = default;

    std::int32_t degree() const 
    { 
        return m_monomes.size() > 0 ? m_monomes.size() - 1 : -1; 
    }

    K& operator [] ( std::size_t i ) 
    {
        assert(i < m_monomes.size());
        return m_monomes[i];
    }

    K const& operator [] ( std::size_t i )  const
    {
        assert(i < m_monomes.size());
        return m_monomes[i];
    }

    Polynome operator + (Polynome const& p) const
    {
        Polynome r(std::max(degree(), p.degree()));
        for (std::int32_t deg = 0; deg <= std::min(degree(), p.degree()); ++deg )
            r[deg] = m_monomes[deg] + p[deg];
        for (std::int32_t deg = std::min(degree(), p.degree())+1; deg <= degree(); ++deg)
            r[deg] = m_monomes[deg];
        for (std::int32_t deg = std::min(degree(), p.degree())+1; deg <= p.degree(); ++deg)
            r[deg] = p[deg];
        return r;
    }

    Polynome operator - (Polynome const& p) const
    {
        Polynome r(std::max(degree(), p.degree()));
        for (std::int32_t deg = 0; deg <= std::min(degree(), p.degree()); ++deg )
            r[deg] = m_monomes[deg] - p[deg];
        for (std::int32_t deg = std::min(degree(), p.degree())+1; deg <= degree(); ++deg)
            r[deg] = m_monomes[deg];
        for (std::int32_t deg = std::min(degree(), p.degree())+1; deg <= p.degree(); ++deg)
            r[deg] = -p[deg];
        return r;
    }

    Polynome operator * ( Polynome const& p ) const
    {
        Polynome r(std::vector<K>(degree()+p.degree()+1, K(0)));
        for ( std::int32_t deg1 = 0; deg1 <= degree(); ++deg1)
            for (std::int32_t deg2=0; deg2 <= p.degree(); ++deg2)
                r.m_monomes[deg1+deg2] += m_monomes[deg1]*p[deg2];
        return r;
    }

    Polynome derivee() const 
    {
        if (degree() == -1) return Polynome{};
        if (degree() ==  0) return Polynome(std::vector<K>(K(0)));
        Polynome dP(degree()-1);
        for (std::int32_t deg=0; deg <= dP.degree(); ++deg )
            dP[deg] = (deg+K(1))*m_monomes[deg+1];
        return dP;
    }

    Polynome primitive() const 
    {
        if (degree() == -1) return Polynome(std::vector<K>(K(0)));
        Polynome pP(degree()+1);
        pP[0] = K(0);
        for (std::int32_t deg=0; deg <= degree(); ++deg )
        {
            pP[deg+1] = K(1)/(deg+K(1)) * m_monomes[deg];
        }
        return pP;
    }

    Polynome& operator = ( Polynome const& ) = default;
    Polynome& operator = ( Polynome     && ) = default;

    explicit operator std::string() const;
    std::ostream& write(std::ostream& ) const;

    template<typename K2> auto
    operator() ( K2 const& x ) const
    {
        K2 res(m_monomes[degree()]);
        for (std::int32_t d = degree()-1; d >= 0; --d)
            res = res * x + m_monomes[d];
        return res;
    }

private:
    std::vector<K> m_monomes;
};

template<typename R>
Polynome<R>::Polynome( std::istream& input )
{
    std::int32_t deg;
    input >> deg;
    m_monomes.resize(deg+1);
    for ( std::int32_t i = 0; i <= deg; ++i ) input >> m_monomes[i];
}

template<typename K>
Polynome<K>::operator std::string() const
{
    std::string sout;
    if (not m_monomes.empty())
    {
        sout += std::to_string(m_monomes[0]);
        for ( std::int32_t deg = 1; deg<= degree(); ++deg )
        {
            if (m_monomes[deg] > 0)
                sout += " + "s;
            else sout += " - "s;
            sout += std::to_string(m_monomes[deg]) + ".x^{"s + std::to_string(deg) + "}"s ;
        }
    }
    return sout;
}

template<typename K> std::ostream& 
Polynome<K>::write(std::ostream& out) const
{
    out << degree() << std::endl;
    for (auto const& coef : m_monomes ) out << coef << " ";
    return out;
}

template<typename K>
inline std::ostream& operator << (std::ostream& out, Polynome<K> const& P )
{
    return P.write(out);
}


#endif