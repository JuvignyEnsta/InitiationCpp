#include <vector>
#include <iostream>
#include <array>
#include <memory>
#include <cstdint>

struct Matrice 
{
    std::int32_t        numberOfRows;
    std::vector<double> coefficients;
};

struct OctTreeNode
{
  std::array<double,6> boundingBox{0., 0., 0., 0., 0., 0.};
  std::array<std::shared_ptr<OctTreeNode>,8> children{nullptr,nullptr,nullptr,nullptr,
                                     nullptr,nullptr,nullptr,nullptr};
};

int main()
{
    constexpr int dim = 10;

    Matrice mat1;
    mat1.numberOfRows = dim;
    mat1.coefficients = std::move(std::vector<double>(dim*dim,0.));

    Matrice mat2{ dim, std::vector<double>(dim*dim,0.)};

    Matrice mat3{ .numberOfRows = 10 };

        

    return EXIT_SUCCESS;
}