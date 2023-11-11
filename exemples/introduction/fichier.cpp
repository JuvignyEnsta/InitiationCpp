#include <fstream>
#include <iostream>
#include <vector>

std::ostream& operator << ( std::ostream& out, std::vector<double> const& u )
{
    for (auto const& val : u ) out << val << " ";
    return out;
}

int main()
{
    constexpr std::size_t N = 100;
    std::size_t dim;
    std::vector<double> u(N);
    for (std::size_t i=0; i<N; ++i) u[i] = i+1.;

    std::ofstream outFmt("sortie.txt");
    outFmt << u.size() << std::endl;
    outFmt << u;
    outFmt.close();

    std::vector<double> v;
    std::ifstream inFmt("sortie.txt");
    inFmt >> dim;
    v.resize(dim);
    for (auto& val : v ) inFmt >> val;
    inFmt.close();

    std::ofstream outBin("sortie.dat");
    outBin << u.size();
    outBin.write((char *)u.data(), u.size() * sizeof(double));
    outBin.close();

    std::vector<double> w;
    std::ifstream inBin("sortie.dat");
    inBin >> dim;
    w.resize(dim);
    inBin.read((char *)w.data(), dim * sizeof(double));
    inBin.close();

    std::cout << "u : [ " << u << "]" << std::endl;
    std::cout << "v : [ " << v << "]" << std::endl;
    std::cout << "w : [ " << w << "]" << std::endl;

    return EXIT_SUCCESS;
}