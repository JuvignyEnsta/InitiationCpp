/**
 * Exemple inspiré de l'exemple donné par Eric Nieber dans sa librairie range v3.0
 * mais adapté pour le C++ 20
 */
#include <iostream>
#include <tuple>
#include <ranges>
#include <algorithm>
#include <vector>

void premiereversion()
{
    auto entiers = std::ranges::views::iota(1);
    for ( auto value : entiers | std::ranges::views::take(10) )
        std::cout << value << " ";
    std::cout << std::endl;
}

void secondeversion()
{
    auto entiers = std::ranges::views::iota(1);
    auto entiersfiltre = entiers | std::views::filter([](int n){ return n % 2 == 0; })  
                                 | std::views::transform([] (int n) { return n*n+1; });

    for ( auto value : entiersfiltre | std::ranges::views::take(10) )
        std::cout << value << " ";
    std::cout << std::endl;
}

void secondeprimeversion()
{
    std::vector tabtab{ std::vector{1.,2.,5.}, std::vector{2.,5.,7.,9.},
                        std::vector{2.,5.   }, std::vector{3.,7.,8.}    };
    auto flatten = tabtab | std::views::join;
    for ( auto elts : flatten ) std::cout << elts << " ";
    std::cout <<std::endl;
}

void troisiemeversion()
{
    auto paires = std::ranges::views::iota(1) | std::views::transform(  [](int z) 
                   {    return std::ranges::views::iota(1,z) 
                             | std::views::transform( [=](int x){ return std::pair{x,z}; } );
                   } ) | std::views::join;

    for (auto pairvalue : paires | std::ranges::views::take(11) )
        std::cout << pairvalue.first << "," << pairvalue.second << " ";
    std::cout << std::endl;
}

void quatriemeversion()
{
    auto triplets = std::ranges::views::iota(1) 
                 | std::views::transform([](int z) { 
                    return std::ranges::views::iota(1,z) | std::views::transform([=](int x) {
                        return std::ranges::views::iota(1,x) | 
                               std::views::transform( [=](int y){ return std::make_tuple(y,x,z); } );
                        }) | std::views::join;
                  } ) | std::views::join;
                  
    for (auto v : triplets | std::ranges::views::take(10) )
        std::cout << std::get<0>(v) << "," << std::get<1>(v) << "," << std::get<2>(v) << " ";
    std::cout << std::endl;
}

void cinquiemeversion()
{
    auto triplets = std::ranges::views::iota(1) 
                 | std::views::transform([](int z) { 
                    return std::ranges::views::iota(1,z) | std::views::transform([=](int x) {
                        return std::ranges::views::iota(1,x) | 
                               std::views::transform( [=](int y){ if (x*x+y*y==z*z) 
                                                                    return std::make_tuple(y,x,z); 
                                                                  else 
                                                                    return std::make_tuple(0,0,0); } );
                        }) | std::views::join;
                  } ) | std::views::join;
                  
    for (auto vals : triplets | std::ranges::views::take(200) )
        std::cout << "[" << std::get<0>(vals) << "," << std::get<1>(vals) 
                  << "," << std::get<2>(vals) << "] ";
    std::cout << std::endl;
}

void sixiemeversion()
{
    auto triplets = std::ranges::views::iota(1) 
                 | std::views::transform([](int z) { 
                    return std::ranges::views::iota(1,z) | std::views::transform([=](int x) {
                        return std::ranges::views::iota(1,x) | 
                               std::views::transform( [=](int y){ if (x*x+y*y==z*z) 
                                                                    return std::make_tuple(y,x,z); 
                                                                  else 
                                                                    return std::make_tuple(0,0,0); } );
                        }) | std::views::join;
                  } ) | std::views::join | 
                        std::views::filter([](std::tuple<int,int,int> t){ return std::get<0>(t) != 0; });
                  
    for (auto vals : triplets | std::ranges::views::take(100) )
        std::cout << std::get<0>(vals) << "² + " << std::get<1>(vals) << "² = " 
                  << std::get<2>(vals) << "²" << std::endl;
}

int main(){

    std::cout << "Première version : " << std::endl;
    premiereversion();

    std::cout << "Seconde version : " << std::endl;
    secondeversion();

    std::cout << "Seconde version prime : " << std::endl;
    secondeprimeversion();

    std::cout << "Troisième version : " << std::endl;
    troisiemeversion();

    std::cout << "Quatrième version : " << std::endl;
    quatriemeversion();

    std::cout << "Cinquième version : " << std::endl;
    cinquiemeversion();

    std::cout << "Sixième version : " << std::endl;
    sixiemeversion();

    return EXIT_SUCCESS;
}
