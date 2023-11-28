/**
 * @file   rationnel.hpp
 * @author Xavier Juvigny (xavier.juvigny@onera.fr)
 * @brief  Classe gérant les rationnels
 * @version 0.1
 * @date 2023-11-07
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef _ARITHMETIC_RATIONNEL_HPP_
#define _ARITHMETIC_RATIONNEL_HPP_
#include <cstdint>
#include <iostream>
#include <string>

namespace arithmetic
{
/***********************************************************************************************
 * @brief      Classe représentant des nombres rationnels                                      *
 **********************************************************************************************/
template<typename Integer> class Rationnel
{
public:
    /// @brief Structure contenant le numérateur et le dénominateur;
    struct ValeurStruct {
        Integer numérateur, dénominateur;
    };
    ///+ Constructeur et destructeurs
    //@{
    /** Constructeur par défaut */
    Rationnel() = default;

    /** \brief Défini un rationnel
     * 
     * Définit un rationnel à partir d'un numérateur
     * et d'un dénominateur fourni en paramètre. 
     * Si le dénominateur est omis, il sera égal par défaut
     * à un (on a définit un entier)
     * 
     * @param[in] numérateur    Entier quelconque
     * @param[in] dénominateur  Entier strictement positif
    */
    Rationnel( Integer numérateur, Integer dénominateur = 1LL);

    template<typename Integer2>
    Rationnel( Integer2 numérateur, Integer2 dénominateur = Integer2(1))
        : Rationnel(Integer(numérateur), Integer(dénominateur))
    {}
    // Approche un réel par une fraction à epsilon près
    /**
     * @brief Construit un rationnel approchant un réel
     * 
     * L'approximation se fait avec une précision epsilon 
     * donnée (\f$10^{-14}\f$ par défaut). L'algorithme
     * utilisé garantit les entiers les plus petits permettant
     * une telle approximation.
     * 
     * @param real    Le réel à approcher
     * @param epsilon La marge d'erreur tolérée
     */
    explicit Rationnel( double real, double epsilon = 1.E-14 );
    ///+ @brief Constructeur de copie
    Rationnel( const Rationnel& ) = default;
    /// @brief Constructeur de déplacement
    Rationnel(      Rationnel&& ) = default;
    /// @brief Destructeur par défaut
    ~Rationnel() = default;
    //@}

    ///+ Définitions des opérateurs sur les rationnels
    //@{
    ///+ Opérateur de copie
    Rationnel& operator = ( const Rationnel& ) = default;
    ///+ Opérateur de déplacement
    Rationnel& operator = (      Rationnel&& ) = default;
    /**
     * @brief Opérateur d'addition "sur place" (inplace)
     * 
     * @return rationnel& Une référence sur le rationnel courant
     */
    Rationnel& operator += ( const Rationnel& );
    /**
     * @brief Opérateur de soustraction "sur place" (inplace)
     * 
     * @return rationnel& 
     */
    Rationnel& operator -= ( const Rationnel& );
    Rationnel& operator *= ( const Rationnel& );
    Rationnel& operator /= ( const Rationnel& );
    Rationnel operator +   ( const Rationnel& ) const;
    Rationnel operator -   ( const Rationnel& ) const;
    Rationnel operator *   ( const Rationnel& ) const;
    Rationnel operator /   ( const Rationnel& ) const;
    Rationnel operator -() const;
    // Opérateur spatial (spaceship operator) pour les comparaisons (C++ 20)
    decltype(Integer(1)<=>Integer(2)) operator <=> ( const Rationnel& ) const;
    bool operator == ( const Rationnel& q) const
    {
        return ((m_valeur.numérateur == q.numérateur()) && (m_valeur.dénominateur == q.dénominateur()));
    }// Pour dire qu'on utilise l'opérateur <=> sinon faut le redéfinir

    // Opérateur convertissant le rationnel en un réel flottant
    explicit operator double() const { return double(m_valeur.numérateur)/m_valeur.dénominateur; }
    explicit operator std::string() const 
    { 
        return "(" + std::to_string(this->m_valeur.numérateur) + "/" + std::to_string(this->m_valeur.dénominateur) + ")"; 
    }
    //@}

    //# Accesseurs et modifieurs
    //@{
    ValeurStruct const& valeurs() const 
    {   return m_valeur; } 
    Integer numérateur() const { return m_valeur.numérateur; }
    Integer dénominateur() const { return m_valeur.dénominateur; }
    //@}

private:
    ValeurStruct m_valeur{0.,1.};
};
}

template<typename Integer> inline
arithmetic::Rationnel<Integer> operator + ( Integer val, 
                                            const arithmetic::Rationnel<Integer>& p)
{
    return p + val;
}

template<typename Integer> inline
arithmetic::Rationnel<Integer> operator - ( Integer val, 
                                            const arithmetic::Rationnel<Integer>& p)
{   return -(p - val);  }

template<typename Integer> inline
arithmetic::Rationnel<Integer> operator * ( Integer val, 
                                            const arithmetic::Rationnel<Integer>& p)
{   return p * val; }

template<typename Integer> inline
arithmetic::Rationnel<Integer> operator / ( Integer val, 
                                            const arithmetic::Rationnel<Integer>& p)
{   return arithmetic::Rationnel<Integer>(val)/p; }

template<typename Integer> inline
std::ostream& operator << ( std::ostream& out, 
                            const arithmetic::Rationnel<Integer>& p)
{
    auto [pn,pd] = p.valeurs();
    out << pn << " " << pd;
    return out;
}
#endif