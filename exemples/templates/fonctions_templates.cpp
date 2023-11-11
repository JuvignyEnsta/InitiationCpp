#include <list>
#include <cmath>
#include <array>
#include <vector>
#include <cassert>
#include <cstdint>
#include <complex>
#include <iostream>
#include <stdexcept> 
#include <type_traits>

using namespace std::complex_literals;

template<typename K> auto sum( std::vector<K> const &u )
{
    K s(0);
    for (auto const& valeur : u ) s += valeur;
    return s; 
}

template<typename Iterator> auto sum( Iterator const &itBeg, Iterator const &itEnd )
{
    std::remove_reference_t<decltype(*itBeg)> s = 0;
    for (Iterator it = itBeg; it != itEnd; ++it ) s += *it;
    return s;
}

template<std::size_t dim> 
auto sqNorm( std::array<double,dim> const &u ) 
{
  double s = 0; 
  for (std::size_t i=0; i < dim; ++i ) s += u[i]*u[i]; 
  return s; 
}

template<typename K, std::size_t dim> 
auto norm( std::array<K,dim> const &u ) 
{
  K s = 0; 
  for (std::size_t i=0; i < dim; ++i ) s += u[i]*u[i]; 
  return std::sqrt(s); 
}

template<typename K, int dim=3> auto createCanonicalBase()
{
    std::vector<std::array<K,dim>> base; base.reserve(dim);
    for (int i=0; i<dim; ++i)
    {
        std::array<K,dim> ei;
        ei.fill(0); ei[i] = 1;
        base.push_back(ei);
    }
    return base;
}

template<typename K> 
auto dot( std::vector<K> const& u, std::vector<K> const& v ) {
    std::cout << "(K)";
    assert(u.size() == v.size()); 
    typename std::vector<K>::value_type sum = 0;
    for (std::size_t i=0; i< u.size(); ++i ) sum += u[i]*v[i];
    return sum;
}

template<typename K>
auto dot( std::vector<std::complex<K>> const& u,
          std::vector<std::complex<K>> const& v ) {
    std::cout << "(complex<K>)";
    assert(u.size() == v.size());
    std::complex<K> sum = 0.;
    for (std::size_t i=0; i<u.size(); ++i) sum += std::conj(u[i])*v[i];
    return sum;
}

// J'ai reprogrammé la fonction BLAS pour ne pas avoir à faire un lien hasardeux
double ddot_(int n, double const* u, int incu, double const* v, int incv)
{
    double sum = 0.;
    for (int i=0; i<n; ++i )
        sum += u[i*incu]*v[i*incv];
    return sum;
}

auto dot( std::vector<double> const& u, std::vector<double> const& v) {
    std::cout << "(double)";
    return ddot_(u.size(), u.data(), 1, v.data(), 1);
}

template<typename K1, typename K2> 
auto prod( std::vector<K1> const& u, std::vector<K2> const& v )
{
    assert(u.size() == v.size());
    std::vector<decltype(std::conj(u[0])*v[0])> res(u.size());
    for (std::size_t i=0; i<u.size(); ++i) res[i] = std::conj(u[i])*v[i];
    return res;
}

template<typename K2> 
auto prod( std::vector<double> const& u, std::vector<K2> const& v )
{
    assert(u.size() == v.size());
    std::vector<decltype(K2(0)*1.)> res(u.size());
    for (std::size_t i=0; i<u.size(); ++i) res[i] = u[i]*v[i];
    return res;
}

template<typename EvalFctType> auto
computeVector( int dim, EvalFctType const& evalFct ) -> std::vector<decltype(evalFct(0))>
{
    std::vector<decltype(evalFct(0))> u(dim);
    for (std::size_t i=0; i<dim; ++i)
        u[i] = evalFct(i);
    return u;
}

template<typename K> std::ostream& 
operator << (std::ostream& out, std::vector<K> const& u)
{
    out << "[ ";
    for (auto const& val : u ) out << val << " ";
    out << " ]";
    return out; 
}



int main()
{
    std::vector<double>     u{1.,2., 3., 4., 5.};
    std::list<std::int64_t> l{1 ,2 , 3 , 4 , 5 };

    auto vsum  = sum(u);
    auto vsum2 = sum(u.begin(), u.end());
    auto lsum = sum(l.begin(), l.end());

    std::cout << "vsum : " << vsum << ", vsum2 : " << vsum2 << " et lsum : " << lsum << std::endl;

    std::cout << sqNorm( std::array{1., 3., 2., 5. } ) << std::endl; 

    std::cout << norm( std::array{1L, 2L, 3L, 4L} ) << std::endl;;

    auto base3D = createCanonicalBase<double>();
    std::cout << "Base canonique en 3D : " << std::endl;
    for (auto const& v : base3D)
    {
        for (auto const& val : v) std::cout << val << " ";
        std::cout << std::endl;
    }
    std::cout << "Base canonique en 2D : " << std::endl;
    auto base2D = createCanonicalBase<int,2>();
    for (auto const& v : base2D)
    {
        for (auto const& val : v) std::cout << val << " ";
        std::cout << std::endl;
    }

    std::cout << "dot({1,2,3},{3,2,1}) = " << dot( std::vector{1,2,3}, {3,2,1}) 
              << std::endl;
    std::cout << "dot({1.,2.,3.},{3.,2.,1.}) = " << dot( std::vector{1.,2.,3.}, {3.,2.,1.}) 
              << std::endl;
    std::cout << "dot({1.+i, 1.-i, 2.+3.i}, {1.+i, 1.-i, 2.+3.i}) = "
              << dot(std::vector{1.+1.i, 1.-1.i, 2.+3.i}, 
                                {1.+1.i, 1.-1.i, 2.+3.i}) << std::endl;

    std::cout << "prod({1.+i, 1.-i, 2.+3.i}, {1.+i, 1.-i, 2.+3.i}) = "
              << prod(std::vector{1.+1.i, 1.-1.i, 2.+3.i}, 
                      std::vector{1.+1.i, 1.-1.i, 2.+3.i}) << std::endl;

    std::cout << "prod({1.,-1., 2.}, {1.+i, 1.-i, 2.+3.i}) = "
              << prod(std::vector{1., 1., 2.}, 
                      std::vector{1.+1.i, 1.-1.i, 2.+3.i}) << std::endl;

    auto u1 = computeVector(5, [](int i){ return 1.5*i; } );
    std::cout << "u1 : " << u1 << std::endl;

    struct Kernel {
        double kWave;
        std::vector<double>  radius;
        std::complex<double> operator () (int i) const
        {
            return std::polar(1./radius[i], kWave*radius[i]);
        }
    };
    Kernel kernelFct{ 1.1, std::vector{1.,3.,5.,7.,13.}};
    auto u2 = computeVector( kernelFct.radius.size(), kernelFct );
    std::cout << "u2 : " << u2 << std::endl;

    return EXIT_SUCCESS;
}