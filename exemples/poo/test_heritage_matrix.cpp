#include "plain_matrix.hpp"
#include "sparse_matrix.hpp"
using namespace algebre;

void iterate( Matrix const& A, Vecteur const& u )
{
    Vecteur v(u);
    for (int i = 0; i < 10; ++i )
    {
        v = A*v;
        std::cout << "v_" << i+1 << " = " << std::string(v) << std::endl;
    }
}

int main()
{
    Vecteur u({1.,4.,9.,16.});
    PlainMatrix A( {4,4}, { 2.,-1., 0., 0.,
                           -1., 2.,-1., 0.,
                            0.,-1., 2.,-1.,
                            0., 0.,-1., 2. });
    iterate(A, u);
    SparseMatrix B( {4,4}, std::list{  SparseMatrix::EltType{ {0,0},  2},
                                                            { {0,1}, -1},
                                                            { {1,0}, -1},
                                                            { {1,1},  2},
                                                            { {1,2}, -1},
                                                            { {2,1}, -1},
                                                            { {2,2},  2},
                                                            { {2,3}, -1},
                                                            { {3,2}, -1},
                                                            { {3,3},  2} });
    iterate(B,u);
    return EXIT_SUCCESS;
}