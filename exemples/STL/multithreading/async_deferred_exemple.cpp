#include <iostream>
#include <future>
#include <vector>
#include <array>
#include <random>
#include <cmath>
#include <functional>
#include <cstdint>

/**
Exemple d'utilisation de std::async avec une politique d'évaluation paresseuse pour faire une programmation
par tâche (séquentielle).
*/

using Point = std::array<double,3>;

double computeDistances( Point const& t_target, std::future<Point> t_barycenter )
{
    std::cout << "Je calcule les distances" << std::endl;
    auto barycenter = t_barycenter.get();
    Point target2Bary{ barycenter[0] - t_target[0],
                       barycenter[1] - t_target[1],
                       barycenter[2] - t_target[2] };
    return std::sqrt(target2Bary[0]*target2Bary[0] + target2Bary[1]*target2Bary[1] + target2Bary[2]*target2Bary[2]);
}

auto generateMasses( std::int64_t nbMasses ) -> std::vector<Point>
{
    std::cout << "Je calcule les points dans l'espace" << std::endl;
    std::vector<Point> masses; masses.reserve(nbMasses);
    std::random_device rd1;
    std::mt19937 rd(rd1());
    std::uniform_real_distribution<double> distrib(-1., 1.);
    for ( std::int64_t iMass = 0; iMass < nbMasses; ++iMass )
    {
        masses.emplace_back(std::array{distrib(rd),distrib(rd),distrib(rd)});
    }
    return masses;
}

Point computeBarycenter( std::future<std::vector<Point>>  t_masses )
{
    std::cout << "Je calcule le barycentre" << std::endl;
    Point bary{0.,0.,0.};
    auto masses  = t_masses.get();
    for ( auto m : masses )
        {
            bary[0] += m[0];
            bary[1] += m[1];
            bary[2] += m[2];
        }
    bary[0] /= masses.size();
    bary[1] /= masses.size();
    bary[2] /= masses.size();
    return bary;
}

int main()
{
    constexpr std::int64_t nbBodies = 10'000'000;
    std::cout << "Appel calcul des masses" << std::endl;
    auto masses = std::async(std::launch::deferred, generateMasses, nbBodies);
    std::cout << "Appel calcul du barycentre" << std::endl;
    auto bary   = std::async(std::launch::deferred, computeBarycenter, std::move(masses));
    std::cout << "Appel calcul des distances" << std::endl;
    Point target{ 2., 0., 0.};
    auto fdist   = std::async(std::launch::deferred, computeDistances, target, std::move(bary));

    std::cout << "Distance des points à la cible \n " << fdist.get() << std::endl;
    return EXIT_SUCCESS;
}
