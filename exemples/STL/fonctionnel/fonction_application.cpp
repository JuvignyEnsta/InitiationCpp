#include<functional>
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <random>
#include <iterator>

int main()
{
    std::vector valeurs{2.,3.,5.,7.,11.,13.};
    
    auto sum  = std::accumulate(valeurs.begin(), valeurs.end(), 0., std::plus<double>());
    auto prod = std::accumulate(valeurs.begin(), valeurs.end(), 1., std::multiplies<double>());
    std::vector<bool> flags;
    std::transform(valeurs.begin(), valeurs.end(), std::back_inserter(flags), [](double x){ return (int(x)%2==0);});
    auto has_even = std::accumulate(flags.begin(), flags.end(), false, std::logical_or<bool>());
    std::cout << "sum : " << sum << ", prod = " << prod << std::endl;
    std::cout << std::boolalpha << "A une valeur paire ? " << has_even << std::endl;

    std::transform(valeurs.begin(), valeurs.end(), valeurs.begin(), std::negate<double>());
    std::copy(valeurs.begin(), valeurs.end(), std::ostream_iterator<double>(std::cout, ";"));
    std::cout <<std::endl;
    std::copy_if(valeurs.begin(), valeurs.end(), std::ostream_iterator<double>(std::cout,"/"), [](double x){ return (int(x-1)%6) == 0; } );
    std::cout << std::endl;

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(valeurs.begin(), valeurs.end(),g);
    std::copy(valeurs.begin(), valeurs.end(), std::ostream_iterator<double>(std::cout, ";")); std::cout << std::endl;
    std::sort(valeurs.begin(), valeurs.end(), std::greater<double>());
    std::copy(valeurs.begin(), valeurs.end(), std::ostream_iterator<double>(std::cout, ";")); std::cout << std::endl;

    std::cout << std::boolalpha << "Aucun element div. par 4 ? " << std::none_of(valeurs.begin(),valeurs.end(),[](double x){ return (int(x)%4 == 0); }) << std::endl;

    return EXIT_SUCCESS;
}