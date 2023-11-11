#include "sparse_matrix.hpp"
using namespace algebre;

int main()
{
    SparseMatrix A0;
    SparseMatrix A1( {10, 10} );
    SparseMatrix A2( {4,4}, std::list{ SparseMatrix::EltType{ {0,0},  2},
                                                            { {0,1}, -1},
                                                            { {1,0}, -1},
                                                            { {1,1},  2},
                                                            { {1,2}, -1},
                                                            { {2,1}, -1},
                                                            { {2,2},  2},
                                                            { {2,3}, -1},
                                                            { {3,2}, -1},
                                                            { {3,3},  2} });
    std::cout << "A2 brut : " << A2 << std::endl;
    std::cout << "A2      :\n" << std::string(A2) << std::endl;
    Vecteur u({1.,4.,9.,16.});
    std::cout << "u : " << std::string(u) << std::endl;
    std::cout << "A2.u : " << std::string(A2*u) << std::endl;
    return EXIT_SUCCESS;
}