#ifndef _ALGEBRE_PLAIN_MATRIX_HPP_
#define _ALGEBRE_PLAIN_MATRIX_HPP_
#include <vector>
#include <cassert>
#include <iomanip>
#include "matrix.hpp"

namespace algebre
{
class PlainMatrix : public Matrix
{
public:
    class iterator
    {
    public:
        iterator( PlainMatrix& t_plMatrix );
        iterator( PlainMatrix& t_plMatrix, IndiceType const& t_position );
        iterator( iterator const& iter );
        ~iterator() = default;

        iterator& operator = ( iterator const& iter );
        bool operator != ( iterator const& iter );
        iterator& operator ++ (   );
        iterator operator  ++ (int);
        double& operator *();
        IndiceType position() const { return m_position; }
    private:
        PlainMatrix& m_matrix;
        IndiceType   m_position;
    };

    class const_iterator
    {
    public:
        const_iterator( PlainMatrix const& t_plMatrix );
        const_iterator( PlainMatrix const& t_plMatrix, IndiceType const& t_position );
        const_iterator( const_iterator const& iter );
        ~const_iterator() = default;

        const_iterator& operator = ( const_iterator const& iter );
        bool operator != ( const_iterator const& iter );
        const_iterator& operator ++ (   );
        const_iterator  operator ++ (int);
        double const& operator *();
        IndiceType position() const { return m_position; }
    private:
        PlainMatrix const& m_matrix;
        IndiceType   m_position;
    };

    PlainMatrix() = default;
    PlainMatrix( DimensionType const& t_dimensions );
    PlainMatrix( DimensionType const& t_dimensions, std::vector<double> const& t_coefs );
    PlainMatrix( DimensionType const& t_dimensions, std::vector<double>     && t_coefs );
    PlainMatrix( PlainMatrix const& ) = default;
    PlainMatrix( PlainMatrix     && ) = default;
    virtual ~PlainMatrix           () = default;

    iterator begin() { return iterator(*this); }
    const_iterator begin () const { return const_iterator(*this); }
    const_iterator cbegin() const { return const_iterator(*this); }

    iterator end() { return iterator(*this, IndiceType{dimensions().nrows,0}); }
    const_iterator end () const { return const_iterator(*this,   IndiceType{dimensions().nrows,0}); }
    const_iterator cend() const { return const_iterator(*this, IndiceType{dimensions().nrows,0}); }

    virtual Vecteur operator * ( Vecteur const& u ) const override;
#   if __cplusplus > 202002L
    double      & operator[] (std::size_t i, std::size_t j)      ;
    double const& operator[] (std::size_t i, std::size_t j) const;
#   else
    double      & operator[] (std::pair<std::size_t, std::size_t> const& indices );
    double const& operator[] (std::pair<std::size_t, std::size_t> const& indices ) const;
#   endif
    virtual DimensionType dimensions() const override;
    virtual double frobeniusNorm() const override;
    
    virtual std::ostream& 
    write(std::ostream& out,std::ios::openmode mode = std::ios::openmode(0)) const override;
    
    virtual operator std::string() const override;

private:
    Matrix::DimensionType m_dimensions;
    std::vector<double>   m_coefficients;
};
}

#endif