#include <memory>
#include <complex>
#include <array>

int main()
{
    using dcomplex = std::complex<double>;
    using Point    = std::array<double,2>;
    std::shared_ptr<dcomplex> pt_complex = std::make_shared<dcomplex>(1., -3.);
    std::shared_ptr<Point> pt_p = std::make_shared<Point>(Point{1.,2.});
    
}