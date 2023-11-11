#include "plain_matrix.hpp"
using namespace algebre;

int main()
{
    PlainMatrix A0;
    PlainMatrix A1({5,5});
    for (std::size_t irow=0; irow < 5; ++irow)
        for (std::size_t jcol=0; jcol < 5; ++jcol)
#           if __cplusplus > 202002L
            A1[irow,jcol] = (irow+jcol)%5+1.;
#           else 
            A1[{irow,jcol}] = (irow+jcol)%5+1.;
#           endif
    std::cout << "A1 :\n" << std::string(A1) << std::endl;
    PlainMatrix A2({11,3});
    for (auto iter = A2.begin(); iter != A2.end(); ++iter )
    {
        (*iter) = (iter.position().icol+iter.position().irow)%9 + 1;
    }
    std::cout << "A2 :\n" << std::string(A2) << std::endl;
    PlainMatrix A3({2,2}, {0.,1.,1.,0.});
    std::cout << "A3 :\n" << std::string(A3) << std::endl;

    Vecteur u3(std::vector{1.,2.});
    Vecteur v3 = A3 * u3;
    std::cout << "A3." << std::string(u3) << " = " << std::string(v3) <<std::endl;

    return EXIT_SUCCESS;
}