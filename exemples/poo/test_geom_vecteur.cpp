#include <sstream>
#include "geom_vecteur.hpp"

int main()
{
    geometry::Vecteur u0;
    geometry::Vecteur u1({1., 2., 0., 1.});
    geometry::Vecteur u2( 1., 2., 3.);
    geometry::Vecteur u3( u1 );

    std::ostringstream sout;
    sout << u2;
    std::istringstream sinp(sout.str());
    geometry::Vecteur u4(sinp);

    std::cout << "u1 : " << u1 << std::endl;
    std::cout << "str(u1) : " << std::string(u1) << std::endl;

    std::cout << "u2 : " << u2 << std::endl;
    std::cout << "str(u2) : " << std::string(u2) << std::endl;
    std::cout << "u4 : " << std::string(u4) << std::endl;

    std::cout << "u1 + u2 = " << std::string(u1+u2) << std::endl;
    std::cout << "u4 + u2 = " << std::string(u4+u2) << std::endl;
    std::cout << "-u1 = " << std::string(-u1) << std::endl;
    std::cout << "-u2 = " << std::string(-u2) << std::endl;

    try
    {
        u2 += u1;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    return EXIT_SUCCESS;
}
