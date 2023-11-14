#include <iostream>
#include <memory>

struct Point
{
    double x,y;

    ~Point() { std::cout << "destruction point " << x << ", " << y << std::endl; }
};

std::shared_ptr<Point> buildPoint(double t_x, double t_y)
{
    return std::make_shared<Point>(Point{t_x,t_y});
}

std::ostream& operator << ( std::ostream& out, Point const& p )
{
    out << "{ " << p.x << ", " << p.y << " }";
    return out;
}

struct Arete
{
    std::shared_ptr<Point> deb{nullptr}, fin{nullptr};
};

std::ostream& operator << ( std::ostream& out, Arete const& a )
{
    out << *a.deb << " -- " << *a.fin;
    return out;
}

int main()
{
    auto pt_point = buildPoint(1.,2.);
    std::cout << "pt_point : " << *pt_point << std::endl;

    Arete a1{.deb=buildPoint(-1.,0.), .fin=buildPoint(0.,0.)};
    Arete a2{a1.fin, buildPoint(1.,0.)};

    std::cout << "a1 : " << a1 << ", a2 : " << a2 << std::endl;

    a2.deb->y += 1;
    std::cout << "a1 : " << a1 << ", a2 : " << a2 << std::endl;
    a1.fin->x -= 1;
    a1.deb->x -= 1;
    std::cout << "a1 : " << a1 << ", a2 : " << a2 << std::endl;

    a1.fin = a1.deb;
    a1.deb = buildPoint(0.,-1.);
    std::cout << "a1 : " << a1 << ", a2 : " << a2 << std::endl;

    return EXIT_SUCCESS;
}
