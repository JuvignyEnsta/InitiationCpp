#ifndef _ALGEBRE_MATRIX_HPP_
#define _ALGEBRE_MATRIX_HPP_
#include <iomanip>
#include <iostream>
#include "alg_vecteur.hpp"

namespace algebre
{
class Matrix
{
public:
    struct DimensionType
    {
        std::size_t nrows{0}, ncols{0};
    };
    struct IndiceType
    {
        std::size_t irow{0}, icol{0};
    };

    Matrix() = default;
    Matrix( Matrix const& ) = default;
    Matrix( Matrix     && ) = default;
    virtual ~Matrix()       = default;

    Matrix& operator = ( Matrix const& ) = delete;
    Matrix& operator = ( Matrix     && ) = delete;
    virtual Vecteur operator * ( Vecteur const& u ) const = 0;
    virtual DimensionType dimensions() const = 0;

    virtual double frobeniusNorm() const = 0;

    virtual std::ostream& 
    write(std::ostream& out,std::ios::openmode mode = std::ios::openmode(0)) const = 0;

    virtual operator std::string() const = 0;
};

inline std::ostream& operator << ( std::ostream& out, Matrix const& t_matrix )
{
    return t_matrix.write(out);
}

}

#endif