#ifndef _ALGEBRE_VECTEUR_HPP_
#define _ALGEBRE_VECTEUR_HPP_
#include <vector>
#include <iostream>
#include <string>

namespace algebre
{
/**
 * @brief Vecteur au sens algébrique (dimension N)
 * 
 */
class Vecteur
{
public:
    ///+ Définition des itérateurs sur les coefficients du vecteur
    //@{
    using iterator = std::vector<double>::iterator; ///+ Itérateur sur un vecteur non constant
    using const_iterator = std::vector<double>::const_iterator;///+ Itérateur sur un vecteur constant
    //@}

    ///+ Constructeurs et destructeur 
    //@{
    ///+ Constructeur par défaut
    Vecteur() = default;
    /**
     * @brief Constructeur initialisant un vecteur à partir d'une liste d'initialisation
     * 
     * @param t_coefs 
     */
    Vecteur( std::vector<double>           const& t_coefs );
    Vecteur( std::vector<double>               && t_coefs );
    Vecteur( std::size_t t_dimension );
    Vecteur( std::size_t t_dimension, double t_fillingCoef);
    Vecteur( std::istream& t_input, std::ios::openmode mode = std::ios::openmode(0) );
    Vecteur( Vecteur const& ) = default;
    Vecteur( Vecteur     && ) = default;
    ~Vecteur()                = default;
    //@}

    iterator        begin()       { return m_coefs.begin(); }
    const_iterator  begin() const { return m_coefs.cbegin(); }
    const_iterator cbegin() const { return m_coefs.cbegin(); }
    iterator          end()       { return m_coefs.end(); }
    const_iterator    end() const { return m_coefs.cend(); }
    const_iterator   cend() const { return m_coefs.cend(); }
    std::size_t dimension() const { return m_coefs.size(); }
    double& operator [] ( std::size_t i );
    double const& operator[] ( std::size_t i ) const;
    double*       data()       { return m_coefs.data(); }
    double const* data() const { return m_coefs.data(); }

    Vecteur& operator = ( Vecteur const&  ) = default;
    Vecteur& operator = ( Vecteur     &&  ) = default;
    Vecteur& operator += ( Vecteur const& );
    Vecteur  operator +  ( Vecteur const& ) const;
    Vecteur&&operator +  ( Vecteur     && ) const;
    Vecteur& operator -= ( Vecteur const& );
    Vecteur  operator -  ( Vecteur const& ) const;
    Vecteur&&operator -  ( Vecteur     && ) const;
    Vecteur  operator -  (                ) const;
    Vecteur& operator *= ( double alpha   );
    double   operator |  ( Vecteur const& ) const;

    Vecteur homothetie   ( double alpha   ) const;
    std::ostream& write( std::ostream& out, std::ios::openmode mode = std::ios::openmode(0) ) const;
    explicit operator std::string() const;
    double normL2() const;
    double normalizeInplace();
    std::pair<double,Vecteur> normalize() const;

private:
    std::vector<double> m_coefs{};
};
inline std::ostream& operator <<( std::ostream& out, Vecteur const& u )
{
    return u.write(out);
}
//
inline Vecteur operator * ( double alpha, Vecteur const& u ) {
    return u.homothetie(alpha);
}
}

#endif