#include <iostream>
#include <future>
#include <vector>
#include <array>
#include <random>
#include <cmath>
#include <functional>
#include <cstdint>
#include <complex>
#include <chrono>

using namespace std::complex_literals;

struct Point 
{
    double x,y,z;
    Point() = default;
    Point( double t_x, double t_y, double t_z )
        :   x(t_x), y(t_y), z(t_z)
    {}
    Point( Point const& ) = default;
    Point( Point     && ) = default;
    ~Point()              = default;

    Point& operator = ( Point const& ) = default;
    Point& operator = ( Point     && ) = default;    
};

struct Vector 
{
    double x,y,z;
    Vector() = default;
    Vector( Point const& p1, Point const& p2 )
        :   x(p2.x-p1.x),
            y(p2.y-p1.y),
            z(p2.z-p1.z)
    {}
    Vector( double t_x, double t_y, double t_z )
        :   x(t_x), y(t_y), z(t_z)
    {}
    Vector( Vector const& ) = default;
    Vector( Vector     && ) = default;
    ~Vector()               = default;

    Vector& operator = ( Vector const& ) = default;
    Vector& operator = ( Vector     && ) = default;

    double nrmL2() const {
        return std::sqrt(x*x+y*y+z*z);
    }
};

double distance( Point const& p1, Point const& p2 )
{
    Vector p1p2(p1,p2);
    return p1p2.nrmL2();
}

/**
Exemple d'utilisation de std::async avec une politique d'évaluation paresseuse pour faire une programmation
par tâche (séquentielle).
*/

auto generateMasses( Point const& t_center, std::int64_t nbMasses ) -> std::vector<Point>
{
#   if defined(TRACE)    
    std::cout << __PRETTY_FUNCTION__ << std::endl;
#   endif
    std::vector<Point> masses; masses.reserve(nbMasses);
    std::mt19937 rd;
    //std::random_device rd;
    std::uniform_real_distribution<double> distrib(-1., 1.);
    for ( std::int64_t iMass = 0; iMass < nbMasses; ++iMass )
    {
        masses.emplace_back(distrib(rd)+t_center.x,distrib(rd)+t_center.y,distrib(rd) + t_center.z);
    }
#   if defined(TRACE)    
    std::cout << "Fin de " << __PRETTY_FUNCTION__ << std::endl;
#   endif
    return masses;
}

std::vector<double> computeDistances( std::shared_future<std::vector<Point>> const& t_emetteurs,
                                      std::shared_future<std::vector<Point>> const& t_cibles )
{
#   if defined(TRACE)    
    std::cout << __PRETTY_FUNCTION__ << std::endl;
#   endif
    auto const& emetteurs = t_emetteurs.get();
    auto const& cibles = t_cibles.get();
    std::vector<double> distances; distances.reserve( emetteurs.size() * cibles.size() );
    for (auto const& e : emetteurs)
    {
        for (auto const& t : cibles)
        {
            distances.emplace_back(Vector(e,t).nrmL2());
        }
    }
#   if defined(TRACE)    
    std::cout << "Fin de " << __PRETTY_FUNCTION__ << std::endl;
#   endif
    return distances;
}

auto greenKernel( double k, std::shared_future<std::vector<double>> const& t_dist ) 
            -> std::vector<std::complex<double>>
{
#   if defined(TRACE)    
    std::cout << __PRETTY_FUNCTION__ << std::endl;
#   endif
    auto const dist = t_dist.get();
    std::vector<std::complex<double>> matrix; matrix.reserve(dist.size());
    for (auto const& d : dist)
    {
        matrix.emplace_back(std::cos(k*d)/d + 1.i*std::sin(k*d)/d);
    }
#   if defined(TRACE)    
    std::cout << "Fin de " << __PRETTY_FUNCTION__ << std::endl;
#   endif
    return matrix;
}

std::complex<double> uAut( std::uint32_t dim, std::shared_future<std::vector<std::complex<double>>> const& ker )
{
    std::vector<std::complex<double>> u(dim);
    auto const& kernel = ker.get();
    for ( std::uint32_t i=0; i<dim; ++i)
    {
        u[i] = 0.+0.i;
        for (std::uint32_t j=0; j<dim; ++j)
            u[i] += kernel[i*dim+j];
    }
    std::complex<double> sum(0.+0.i);
    for (auto const& z : u) sum += z;
    return sum;
}

template<typename LaunchPolicy>
void doComputation( LaunchPolicy policy )
{
    constexpr std::int64_t nbBodies = 2'000;
    auto begChrono = std::chrono::high_resolution_clock::now();
    std::vector<std::shared_future<std::vector<Point>>> b; b.reserve(8);
    for (auto centre : { Point{-2., -2., -2.}, Point{-2., -2., +2.},
                                Point{-2., +2., -2.}, Point{-2., +2., +2.},
                                Point{+2., -2., -2.}, Point{+2., -2., +2.},
                                Point{+2., +2., -2.}, Point{+2., +2., +2.}
                              })
    {
        b.emplace_back(std::async(policy,generateMasses, centre, nbBodies).share());
    }

    constexpr std::uint32_t nbBlocks = 4*7;
    std::vector<std::shared_future<std::vector<double>>> distances; distances.reserve(nbBlocks);
    for (std::uint32_t i=0; i<8; ++i)
        for (std::uint32_t j=i+1; j<8; ++j)
            distances.emplace_back(std::async(policy,computeDistances, b[i], b[j]).share());

    std::vector<std::shared_future<std::vector<std::complex<double>>>> kernels; kernels.reserve(nbBlocks);
    for (std::uint32_t i=0; i<nbBlocks; ++i)
    {
        kernels.emplace_back(std::async(policy,greenKernel,1., distances[i]).share());
    }

    std::array<std::shared_future<std::complex<double>>,nbBlocks> result;
    for (std::uint32_t i=0; i<nbBlocks; ++i)
        result[i] = std::async(policy, uAut, nbBodies, kernels[i]).share();
    std::cout << "Résultat : ";
    for (auto const& v : result)
    std::cout << v.get() << " " << std::flush;
    std::cout << std::endl;
    auto endChrono = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> durée = endChrono - begChrono;
    std::cout << "Temps de calcul : " << durée.count() << "s." << std::endl << std::flush;
}

int main()
{
    std::cout << "async avec deferred : " << std::endl;
    doComputation( std::launch::deferred );    
    std::cout << "async avec multithread : " << std::endl;
    doComputation( std::launch::async );    
    std::cout << "async avec deferred + multithread : " << std::endl;
    doComputation( std::launch::deferred | std::launch::async );    
    return EXIT_SUCCESS;
}
