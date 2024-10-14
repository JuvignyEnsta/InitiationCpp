/**
 * Plusieurs façon d'écrire une fonction renvoyant plusieurs valeurs
 * La première fonction choisie est la division euclidienne qui doit renvoyer
 * le résultat entier du quotient et le reste associé.
 */
#include <tuple>
#include <iostream>
#include <cmath>
#include <complex>
#include <cassert>
#include <cstdint>
#if __cplusplus >= 201709L
#include <numbers>
#endif

using namespace std::complex_literals;


int division_euclidienne_1( int p, int q, int* reste)
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    int résultat = p/q;
    *reste = p - résultat*q;
    return résultat;
}

std::array<int,2> division_euclidienne_2(int p, int q)
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    int résultat = p/q;
    return {résultat, p - résultat*q};
}

std::pair<int,int> division_euclidienne_3(int p, int q)
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    int résultat = p/q;
    return {résultat, p - résultat*q};
}

void racines_cubique_1(std::complex<double> z, std::complex<double>* z1, 
                       std::complex<double>* z2, std::complex<double>* z3)
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
#   if __cplusplus >= 201709L
    const double deux_pi_sur_trois = 2*std::numbers::pi/3.;
#   else
    const double deux_pi_sur_trois = 2.*std::acos(-1)/3.;
#   endif
    double argument = std::arg(z)/3.;
    double module   = std::cbrt(std::abs(z));

    *z1 = module * std::exp(std::complex<double>{0.,argument                      });
    *z2 = module * std::exp(std::complex<double>{0.,argument +   deux_pi_sur_trois});
    *z3 = module * std::exp(std::complex<double>{0.,argument + 2*deux_pi_sur_trois});
}

std::array<std::complex<double>,3> racines_cubique_2(std::complex<double> z)
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
#   if __cplusplus >= 201709L
    const double π_2s3 = 2*std::numbers::pi/3.;
    const double π_4s3 = 4*std::numbers::pi/3.;
#   else
    const double π_2s3 = 2*std::acos(-1)/3.;
    const double π_4s3 = 4.*std::acos(-1)/3.;
#   endif
    double argument = std::arg(z)/3.;
    double module   = std::cbrt(std::abs(z));// std::cbrt => Racine cubique

    return {
        module * std::exp(1.i*argument), module * std::exp(1.i*(argument + π_2s3)),
        module * std::exp(1.i*(argument + π_4s3))
    };
}

double trouve_et_localise_valeur_maximale_1( int n, const double * values, int* index)
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    *index = 0;
    double value_max = values[0];
    for ( int i = 1; i < n; ++i )
    {
        if (value_max < values[i])
        {
            value_max = values[i];
            *index    = i;
        }
    }
    return value_max;
}

std::pair<double,int> trouve_et_localise_valeur_maximale_2( int n, const double * values)
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    int index = 0;
    int value_max = values[0];
    for ( int i = 1; i < n; ++i )
    {
        if (value_max < values[i])
        {
            value_max = values[i];
            index    = i;
        }
    }
    return {value_max,index};
}

double convertion_en_fraction_1(double valeur, int nombre_iter_max, 
                                std::int64_t* dividende, std::int64_t* diviseur)
{
    assert(valeur>=0.);
    std::int64_t partie_entière = std::int64_t(valeur);
    double reste = valeur - partie_entière;
    if (nombre_iter_max == 0)
    {
        *dividende = partie_entière;
        *diviseur  = 1L;
        return reste;
    }
    std::int64_t p, q;
    reste = convertion_en_fraction_1(1./reste, nombre_iter_max-1, &p, &q);
    *dividende = partie_entière*p+q;
    *diviseur  = p;
    reste = std::abs(valeur-double(*dividende)/double(*diviseur));
    return reste;
}

auto convertion_en_fraction_2(double valeur, int nombre_iter_max)
{
    std::int64_t dividende, diviseur;
    assert(valeur>=0.);
    std::int64_t partie_entière = std::int64_t(valeur);
    double reste = valeur - partie_entière;
    if (std::abs(reste)<1.E-14)
    {
        return std::make_tuple(partie_entière, 1LL, 0.);
    }
    if (nombre_iter_max == 0)
    {
        dividende = partie_entière;
        diviseur  = 1L;
        return std::make_tuple(dividende, diviseur, reste);
    }
    auto [p,q,r] = convertion_en_fraction_2(1./reste, nombre_iter_max-1);
    dividende = partie_entière*p+q;
    diviseur  = p;
    reste = std::abs(valeur-double(dividende)/double(diviseur));
    return std::make_tuple(dividende, diviseur, reste);
}


int main()
{
    std::cout << "Fonction renvoyant deux entiers (division euclidienne) : " << std::endl;
    {
        std::cout << "\tPremière façon  : ";
        int quotient, reste;
        quotient = division_euclidienne_1(7, 3, &reste);
        std::cout << "\t7 = 3 x " << quotient << " + " << reste << std::endl;
    }
    {
        std::cout << "\tDeuxième façon : ";
        auto [quotient, reste] = division_euclidienne_2(7, 3);
        std::cout << "\t7 = 3 x " << quotient << " + " << reste << std::endl;
    }
    {
        std::cout << "\tTroisième façon : ";
        auto [quotient, reste] = division_euclidienne_3(7, 3);
        std::cout << "\t7 = 3 x " << quotient << " + " << reste << std::endl;
    }
    std::cout << "Fonction renvoyant trois complexes (les racines cubiques) : " << std::endl;
    {
        std::cout << "\tPremière façon : ";
        std::complex<double> z1, z2, z3;
        racines_cubique_1(1.+1.i, &z1, &z2, &z3);
        std::cout << "\tRacines cubiques de 1+i : " << z1.real() << "+" << z1.imag() << "i, "
                  << z2.real() << "+" << z2.imag() << "i, " << z3.real() << "+" << z3.imag() << "i"
                  << std::endl;
    }
    {
        std::cout << "\tDeuxième façon : ";
        auto [z1,z2,z3] = racines_cubique_2(1.+1.i);
        std::cout << "\tRacines cubiques de 1+i : " << z1.real() << "+" << z1.imag() << "i, "
                  << z2.real() << "+" << z2.imag() << "i, " << z3.real() << "+" << z3.imag() << "i"
                  << std::endl;
    }
    std::cout << "Trouve et localise la valeur max et son index dans un tableau : " << std::endl;
    double valeurs[11] = { -1., 3., 5., 7., 2., 9., -1., 8., 6., -11., 3.};
    {
        std::cout << "\tPremière façon : ";
        int index;
        int valeur = trouve_  et_localise_valeur_maximale_1(11, valeurs, &index);
        std::cout << "\tTrouvé la valeur " << valeur << " sur l'index " << index << std::endl;
    }
    {
        std::cout << "\tDeuxième façon : ";
        auto [valeur,index] = trouve_et_localise_valeur_maximale_2(11, valeurs);
        std::cout << "\tTrouvé la valeur " << valeur << " sur l'index " << index << std::endl;        
    }
    std::cout << "Approximation d'un réel par un rationel avec erreur : " << std::endl;
    {
        std::cout << "\tFaçon C avec des pointeurs : ";
        std::int64_t dividende, diviseur;
        double erreur = convertion_en_fraction_1(std::sqrt(2.), 8, &dividende, &diviseur);
        std::cout << "\t√2 peut être approchée par : " << dividende << "/" << diviseur
                  << " avec une erreur relative de " << erreur/std::sqrt(2.) << std::endl;
    }
    {
        std::cout << "\tFaçon C++ avec un tuple : ";
        auto [dividende,diviseur,erreur] = convertion_en_fraction_2(std::sqrt(2.), 20);
        std::cout << "\t√2 peut être approchée par : " << dividende << "/" << diviseur
                  << " avec une erreur relative de " << erreur/std::sqrt(2.) << std::endl;
        std::tie(dividende,diviseur,erreur) = convertion_en_fraction_2(std::sqrt(3.), 20);
        std::cout << "\t√3 peut être approchée par : " << dividende << "/" << diviseur
                  << " avec une erreur de " << erreur/std::sqrt(3.) << std::endl;
        std::tie(dividende,diviseur,erreur) = convertion_en_fraction_2(4./3., 3);
        std::cout << "\t1.333.....3 peut être approchée par : " << dividende << "/" << diviseur
                  << " avec une erreur de " << erreur/std::sqrt(3.) << std::endl;
    }
    {
	    std::cout << "\tSi on veut ignorer certaines valeurs de retour : ";
        // _ est un nom de variable valide en C++ qui permet d'ignorer une valeur de retour
        auto [dividende, diviseur, _] = convertion_en_fraction_2(std::sqrt(2.), 20);
        // Cependant, on ne peut plus utiliser _ pour ignorer plusieurs valeur de retour
        // auto [dividende2, _, _] = convertion_en_fraction_2(std::sqrt(2.), 20); // Erreur de compilation
        // En revanche, on peut utiliser plusieurs fois std::ignore dans std::tie
        std::tie(dividende, std::ignore, std::ignore) = convertion_en_fraction_2(std::sqrt(2.), 20);
    }
    return EXIT_SUCCESS;    
}
