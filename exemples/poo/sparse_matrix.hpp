#ifndef _ALGEBRE_SPARSE_MATRIX_HPP_
#define _ALGEBRE_SPARSE_MATRIX_HPP_
#include <list>
#include "matrix.hpp"

namespace algebre
{
class SparseMatrix : public Matrix
{
public:
    struct EltType
    {
        IndiceType indices;
        double     coef;
    };
    class iterator
    {
    public:
        iterator( SparseMatrix& t_spMatrix );
        iterator( SparseMatrix& t_spMatrix, std::size_t t_pt_icol );
        iterator( iterator const& iter );
        ~iterator() = default;

        iterator& operator = ( iterator const& iter );
        bool operator != ( iterator const& iter );
        iterator& operator ++ (   );
        iterator operator  ++ (int);
        double& operator *();
        IndiceType position() const { return {m_irow, m_matrix.m_ind_columns[m_pt_icol]}; }
    private:
        SparseMatrix& m_matrix;
        std::size_t m_irow{0}, m_pt_icol{0};
    };

    class const_iterator
    {
    public:
        const_iterator( SparseMatrix const& t_spMatrix );
        const_iterator( SparseMatrix const& t_spMatrix, std::size_t t_pt_icol );
        const_iterator( const_iterator const& iter );
        ~const_iterator() = default;

        const_iterator& operator = ( const_iterator const& iter );
        bool operator != ( const_iterator const& iter );
        const_iterator& operator ++ (   );
        const_iterator  operator ++ (int);
        double const& operator *();
        IndiceType position() const { return {m_irow, m_matrix.m_ind_columns[m_pt_icol]}; }
    private:
        SparseMatrix const& m_matrix;
        std::size_t m_irow{0}, m_pt_icol{0};
    };

    friend class iterator;
    friend class const_iterator;

    SparseMatrix() = default;
    SparseMatrix( DimensionType const& t_dimensions );
    SparseMatrix( DimensionType const& t_dimensions, std::list<EltType> const& elts );
    SparseMatrix( DimensionType const& t_dimensions, std::list<EltType>     && elts );
    SparseMatrix( DimensionType const& t_dimensions, std::vector<std::size_t> const& t_beg_rows,
                  std::vector<std::size_t> const& t_ind_cols );
    SparseMatrix( DimensionType const& t_dimensions, std::vector<std::size_t> && t_beg_rows,
                  std::vector<std::size_t> && t_ind_cols );
    SparseMatrix( DimensionType const& t_dimensions, std::vector<std::size_t> const& t_beg_rows,
                  std::vector<std::size_t> const& t_ind_cols, std::vector<double> const& t_coefs );
    SparseMatrix( DimensionType const& t_dimensions, std::vector<std::size_t> && t_beg_rows,
                  std::vector<std::size_t> && t_ind_cols, std::vector<double> && t_coefs );
    SparseMatrix( SparseMatrix const& ) = default;
    SparseMatrix( SparseMatrix     && ) = default;
    virtual ~SparseMatrix() = default;

          iterator begin()        { return       iterator(*this); }
    const_iterator begin () const { return const_iterator(*this); }
    const_iterator cbegin() const { return const_iterator(*this); }

          iterator end()        { return       iterator(*this, m_ind_columns.size()); }
    const_iterator end () const { return const_iterator(*this, m_ind_columns.size()); }
    const_iterator cend() const { return const_iterator(*this, m_ind_columns.size()); }

    virtual Vecteur operator * ( Vecteur const& u ) const override;
#   if __cplusplus > 202002L
    double operator[] (std::size_t i, std::size_t j) const;
#   else
    double operator[] (std::pair<std::size_t, std::size_t> const& ) const;
#   endif
    virtual DimensionType dimensions() const override;

    virtual double frobeniusNorm() const override;
    
    virtual std::ostream& 
    write(std::ostream& out,std::ios::openmode mode = std::ios::openmode(0)) const override;
    
    virtual operator std::string() const override;

private:
    DimensionType            m_dimensions;
    std::vector<std::size_t> m_beg_rows{}, m_ind_columns{};
    std::vector<double>      m_coefficients{};
};
}

#endif