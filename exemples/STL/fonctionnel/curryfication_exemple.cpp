#include <functional>
#include <cmath>
#include <iostream>
#include <list>

double normeEuclidienne( double x, double y, double z ) {   return std::sqrt(x*x+y*y+z*z);   }

int main()
{
    using namespace std::placeholders;
auto norme2D = std::bind(normeEuclidienne,_1, _2, 0.);
std::cout << "||(3,4)|| = " << norme2D(3.,4.) << std::endl;
auto invminus = std::bind(std::minus<double>(), _2, _1);
std::cout << "invminus(3,4) = " << invminus(3,4) << std::endl;

    std::list pList{2.,3.,5.,7.};
    auto popFunc = std::bind(&std::list<double>::pop_front, &pList);
    popFunc();
    using pushbackType = void (std::list<double>::*)(const double&);
    auto pushFunc = std::bind(static_cast<pushbackType>(&std::list<double>::push_back), &pList, _1);
    pushFunc(11.);
    for (auto const& value : pList) std::cout << value << " ";
    std::cout << std::endl;

    return EXIT_SUCCESS; 
}
