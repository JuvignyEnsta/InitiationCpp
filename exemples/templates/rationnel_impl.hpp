#include "rationnel.hpp"
#include <assert.h>
#include <stdexcept>

using arithmetic::Rationnel;

namespace
{
// Calcul du pgcd par algorithme d'Euclide
template<typename Integer> Integer pgcd( Integer p, Integer q)
{
    if (p == 0LL) return q;
    if (q == 0LL) return p;
    if (p<0) p = -p;
    if (q<0) q = -q;
    if (p < q) std::swap(p,q);
    // On utilise l'algorithme d'Euclide pour calculer le pgcd :
    while (q != 0LL)
    {
        Integer t = q;
        q = p%q;
        p = t;
    }
    assert(p>0);
    return p;
}

template<typename Integer> Rationnel<Integer> 
approximation_Rationnelle(double x, 
                          const Rationnel<Integer>& pn, 
                          const Rationnel<Integer>& qn, double tol )
{
    auto [pnum, pdénom] = pn.valeurs();
    auto [qnum, qdénom] = qn.valeurs();
    Rationnel<Integer> median{ Integer(pnum + qnum), Integer(pdénom + qdénom)};
    double y = double(median);
    if (std::abs(x-y) < tol) return median;
    if (y < x) return approximation_Rationnelle(x, median, qn, tol);
    else return approximation_Rationnelle(x, pn, median, tol);
}

}// Fin espace de nommage anonyme

template<typename Integer>
arithmetic::Rationnel<Integer>::Rationnel( Integer t_numérateur, Integer t_dénominateur)
    :   m_valeur{t_numérateur, t_dénominateur}
{
    if (t_dénominateur <= 0) 
        throw std::runtime_error("Le dénominateur doit être strictement positif");
    if (t_dénominateur != 1)
    {
        auto p = pgcd(t_numérateur, t_dénominateur);
        this->m_valeur.numérateur /= p; this->m_valeur.dénominateur /= p;
    }
    assert(this->m_valeur.dénominateur > 0);
}

// On explore l'arbre de Stern-Brocot pour trouver une approximation de x par un Rationnel
// irréductible dont le quotien reste relativement petit. 
template<typename Integer>
arithmetic::Rationnel<Integer>::Rationnel( double real, double epsilon)
    :   m_valeur{0, 1}
{
    double x = std::abs(real);
    Rationnel p0{Integer(x)};
    Rationnel q0{Integer(x+1)};

    Rationnel p = ::approximation_Rationnelle(x, p0, q0, epsilon);
    this->m_valeur.numérateur = p.numérateur();
    this->m_valeur.dénominateur = p.dénominateur();
}

template<typename Integer> Rationnel<Integer>& 
arithmetic::Rationnel<Integer>::operator += ( const Rationnel<Integer>& p)
{
    assert(this->m_valeur.dénominateur != 0LL);
    assert(p.m_valeur.dénominateur     != 0LL);
    Rationnel<Integer> q(*this);
    this->m_valeur.numérateur = q.m_valeur.numérateur*p.m_valeur.dénominateur + q.m_valeur.dénominateur*p.m_valeur.numérateur;
    this->m_valeur.dénominateur = q.m_valeur.dénominateur*p.m_valeur.dénominateur;
    auto gcd = pgcd(this->m_valeur.numérateur, this->m_valeur.dénominateur);
    this->m_valeur.numérateur /= gcd; this->m_valeur.dénominateur /= gcd;
    assert(this->m_valeur.dénominateur > 0);
    return *this;
}

template<typename Integer> Rationnel<Integer>& 
arithmetic::Rationnel<Integer>::operator -= ( const Rationnel& p)
{
    assert(this->m_valeur.dénominateur != 0LL);
    assert(p.m_valeur.dénominateur     != 0LL);
    Rationnel q(*this);
    this->m_valeur.numérateur = q.m_valeur.numérateur*p.m_valeur.dénominateur - 
                                q.m_valeur.dénominateur*p.m_valeur.numérateur;
    this->m_valeur.dénominateur = q.m_valeur.dénominateur*p.m_valeur.dénominateur;
    Integer gcd = pgcd(this->m_valeur.numérateur, this->m_valeur.dénominateur);
    this->m_valeur.numérateur /= gcd; this->m_valeur.dénominateur /= gcd;
    assert(this->m_valeur.dénominateur > 0);
    return *this;
}

template<typename Integer> Rationnel<Integer>& 
arithmetic::Rationnel<Integer>::operator *= ( const Rationnel& p)
{
    assert(this->m_valeur.dénominateur != 0LL);
    assert(p.m_valeur.dénominateur     != 0LL);
    if ( (p.m_valeur.numérateur == 0LL) || (this->m_valeur.numérateur == 0LL) )
        *this = {Integer(0),Integer(1)};
    else
    {
        Rationnel q(*this);
        auto p1 = pgcd(p.m_valeur.numérateur, this->m_valeur.dénominateur);
        auto p2 = pgcd(this->m_valeur.numérateur, p.m_valeur.dénominateur);
        this->m_valeur.numérateur /= p2;
        this->m_valeur.numérateur *= (p.m_valeur.numérateur/p1);
        this->m_valeur.dénominateur /= p1;
        this->m_valeur.dénominateur *= (p.m_valeur.dénominateur/p2);
    }
    assert(this->m_valeur.dénominateur > 0);
    return *this;
}

template<typename Integer> Rationnel<Integer>& 
arithmetic::Rationnel<Integer>::operator /= ( const Rationnel& p)
{
    assert(this->m_valeur.dénominateur != 0);
    assert(p.m_valeur.dénominateur     != 0);
    if (p.m_valeur.numérateur == 0)
    {
        throw std::runtime_error("Division par zéro !");
    }
    if ( this->m_valeur.numérateur == 0 )
        *this = {Integer(0),Integer(1)};
    else
    {
        Rationnel q(*this);
        auto p1 = pgcd(p.m_valeur.dénominateur, this->m_valeur.dénominateur);
        auto p2 = pgcd(this->m_valeur.numérateur, p.m_valeur.numérateur);
        this->m_valeur.numérateur /= p2;
        this->m_valeur.numérateur *= (p.m_valeur.dénominateur/p1);
        this->m_valeur.dénominateur /= p1;
        this->m_valeur.dénominateur *= (p.m_valeur.numérateur/p2);
    }
    if (this->m_valeur.dénominateur < 0)
    {
        this->m_valeur.numérateur = -this->m_valeur.numérateur;
        this->m_valeur.dénominateur = -this->m_valeur.dénominateur;
    }
    return *this;
}

template<typename Integer> Rationnel<Integer> 
arithmetic::Rationnel<Integer>::operator + ( const Rationnel& p) const
{
    assert(this->m_valeur.dénominateur != 0);
    assert(p.m_valeur.dénominateur     != 0);

    Rationnel<Integer> s(Integer(this->m_valeur.numérateur*p.m_valeur.dénominateur + this->m_valeur.dénominateur*p.m_valeur.numérateur), 
                         Integer(this->m_valeur.dénominateur*p.m_valeur.dénominateur)
               );
    auto gcd = pgcd(s.m_valeur.numérateur, s.m_valeur.dénominateur);
    s.m_valeur.numérateur /= gcd; s.m_valeur.dénominateur /= gcd;

    assert(s.m_valeur.dénominateur > 0);
    return s;
}

template<typename Integer> Rationnel<Integer>
arithmetic::Rationnel<Integer>::operator - ( const Rationnel& p) const
{
    assert(this->m_valeur.dénominateur != 0LL);
    assert(p.m_valeur.dénominateur     != 0LL);

    Rationnel s{Integer(this->m_valeur.numérateur*p.m_valeur.dénominateur - this->m_valeur.dénominateur*p.m_valeur.numérateur), 
                Integer(this->m_valeur.dénominateur*p.m_valeur.dénominateur)
               };
    auto gcd = pgcd(s.m_valeur.numérateur, s.m_valeur.dénominateur);
    s.m_valeur.numérateur /= gcd; s.m_valeur.dénominateur /= gcd;

    assert(s.m_valeur.dénominateur > 0);
    return s;    
}

template<typename Integer> Rationnel<Integer>
arithmetic::Rationnel<Integer>::operator * ( const Rationnel& p ) const
{
    assert(this->m_valeur.dénominateur != 0);
    assert(p.m_valeur.dénominateur     != 0);
    if ( (p.m_valeur.numérateur == 0) || (this->m_valeur.numérateur == 0) )
        return {Integer(0),Integer(1)};
    auto p1 = pgcd(p.m_valeur.numérateur, this->m_valeur.dénominateur);
    auto p2 = pgcd(this->m_valeur.numérateur, p.m_valeur.dénominateur);

    assert((this->m_valeur.dénominateur/p1)*(p.m_valeur.dénominateur/p2) > 0);
    return Rationnel<Integer>(Integer((this->m_valeur.numérateur/p2)*(p.m_valeur.numérateur/p1)), 
                              Integer((this->m_valeur.dénominateur/p1)*(p.m_valeur.dénominateur/p2)) );
}

template<typename Integer>  Rationnel<Integer> 
arithmetic::Rationnel<Integer>::operator / ( const Rationnel& p) const
{
    assert(this->m_valeur.dénominateur != 0);
    assert(p.m_valeur.dénominateur     != 0);
    if (p.m_valeur.numérateur == 0)
    {
        throw std::runtime_error("Division par zéro !");
    }
    if ( this->m_valeur.numérateur == 0 )
        return {Integer(0),Integer(1)};
    auto p1 = pgcd(p.m_valeur.dénominateur, this->m_valeur.dénominateur);
    auto p2 = pgcd(this->m_valeur.numérateur, p.m_valeur.numérateur);
    auto num   = (this->m_valeur.numérateur/p2) * (p.m_valeur.dénominateur/p1);
    auto dénom = (this->m_valeur.dénominateur/p1) * (p.m_valeur.numérateur/p2);
    if (dénom < 0) 
    {
        num   = -num;
        dénom = -dénom;
    }

    assert(dénom > 0);
    return { Integer(num), Integer(dénom) };
}

template<typename Integer>  Rationnel<Integer>
arithmetic::Rationnel<Integer>::operator  - () const
{
    return {Integer(-this->m_valeur.numérateur), Integer(this->m_valeur.dénominateur)};
}

template<typename Integer>  decltype(Integer(1)<=>Integer(2)) 
arithmetic::Rationnel<Integer>::operator <=> ( const Rationnel& p) const
{
    assert(this->m_valeur.dénominateur != 0);
    assert(p.m_valeur.dénominateur     != 0);

    if ( (this->m_valeur.numérateur == p.m_valeur.numérateur) && (this->m_valeur.dénominateur == p.m_valeur.dénominateur) ) 
        return std::strong_ordering::equal;
    if (this->m_valeur.numérateur * p.m_valeur.dénominateur <  p.m_valeur.numérateur * this->m_valeur.dénominateur) 
        return std::strong_ordering::less;
    assert(this->m_valeur.numérateur * p.m_valeur.dénominateur >  p.m_valeur.numérateur * this->m_valeur.dénominateur);
    return std::strong_ordering::greater;

}