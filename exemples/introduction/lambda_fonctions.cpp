#include <iostream>
#include <cmath>
#include <numbers>

double evalPol( double x )
{
    return 3*x*x*x - 4.*x*x + x - 5;
}

int main()
{
    auto compose = [] (auto const& f, auto const& g) {
        return [f, g]( double x ) {
            return f(g(x));
        };
    };

    auto f = compose(evalPol, cos);
    double x = std::numbers::pi;
    std::cout << "f(pi) = " << f(x) << std::endl;

    return EXIT_SUCCESS;
}
