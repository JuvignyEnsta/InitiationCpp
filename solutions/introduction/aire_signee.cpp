#include <iostream>
#include <array>

int main()
{
    using Point   = std::array<double,2>;// Définition du type Point par aliasing de type
    using Vecteur = std::array<double,2>;
    using Triangle = std::array<Point,3>;

    Point p{-1.,0.};
    Triangle T{ Point{-1.,-1.}, 
                     { 1.,-1.},
                     { 0., 1.} };
    Vecteur u1{ T[0][0]-p[0], T[0][1]-p[1] };
    Vecteur u2{ T[1][0]-p[0], T[1][1]-p[1] };
    Vecteur u3{ T[2][0]-p[0], T[2][1]-p[1] };

    double s1 = u1[0]*u2[1] - u1[1]*u2[0];
    double s2 = u2[0]*u3[1] - u2[1]*u3[0];
    double s3 = u3[0]*u1[1] - u3[1]*u1[0];

    if ( (s1*s2 > 0) && (s1*s3 > 0) ) std::cout << "p est dans le triangle" << std::endl;
    else std::cout << "p n'est pas dans le triangle" << std::endl;

    return EXIT_SUCCESS;
}