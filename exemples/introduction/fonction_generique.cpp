#include <array>
#include <vector>
#include <iostream>

void axpy( auto alpha, auto const& x, auto& y )
{
    for (std::size_t i=0; i<x.size(); ++i) y[i] += alpha*x[i];
}

int main()
{
    std::array fx = { 1.f, 2.f, 3.f, 4.f };
    std::array fy = { 0.f,-1.f,-2.f,-3.f };
    axpy( -2.f, fx, fy );
    std::cout << "fy : ";
    for (auto const& v : fy ) std::cout << v << " ";
    std::cout << std::endl;

    std::vector dx = { 1., 2., 3., 4. };
    std::vector dy = { 0.,-1.,-2.,-3. };
    axpy(-2.f, dx, dy);
    std::cout << "dy : ";
    for (auto const& v : dy ) std::cout << v << " ";
    std::cout << std::endl;

    return EXIT_SUCCESS;
}