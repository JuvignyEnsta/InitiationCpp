#include <sstream>
#include "alg_vecteur.hpp"

int main()
{
    int dim = 100;
    algebre::Vecteur u0;
    algebre::Vecteur u1(dim);
    for (std::size_t ind=0; auto& coef : u1) { ++ind; coef = ind; }
    std::cout << "u1 = " << u1 << std::endl;
    std::cout << "std::string(u1) = " << std::string(u1) << std::endl;
    algebre::Vecteur u2(dim, 1.);
    u2 += u1;
    std::ostringstream sout; sout << u2;
    std::istringstream sinp(sout.str());
    algebre::Vecteur u3(sinp);
    std::cout << "std::string(u3) = " << std::string(u3) << std::endl;
    std::cout << "(u1|u3) = " << (u1|u3) << std::endl;

    std::cout << "(u1|u1) = " << (u1|u1) << std::endl;
    u1.normalizeInplace();
    std::cout << "(u1|u1) = " << (u1|u1) << std::endl;
    auto [nrm,v] = (u3 - (u1|u3)*u1).normalize();
    std::cout << "(u1|v) = " << (u1|v) << std::endl;

    return EXIT_SUCCESS;
}