#include <cassert>
#include <algorithm>
#include <cmath>
#include "sparse_matrix.hpp"
using namespace algebre;
using namespace std::string_literals;

SparseMatrix::iterator::iterator( SparseMatrix& t_spMatrix )
    : m_matrix(t_spMatrix)
{}
// --------------------------------------------------------------------------------------------------------------------
SparseMatrix::iterator::iterator( SparseMatrix& t_spMatrix, std::size_t t_pt_icol )
    : m_matrix(t_spMatrix),
      m_pt_icol(t_pt_icol)
{
    while ((t_spMatrix.m_beg_rows[m_irow+1] < t_pt_icol) && (m_irow < t_spMatrix.dimensions().nrows))
        ++m_irow;
}
// --------------------------------------------------------------------------------------------------------------------
SparseMatrix::iterator::iterator( iterator const& iter )
    : m_matrix(iter.m_matrix),
      m_irow(iter.m_irow),
      m_pt_icol(iter.m_pt_icol)
{}
// ====================================================================================================================
auto SparseMatrix::iterator::operator = ( iterator const& iter ) -> iterator& 
{
    assert(&m_matrix == &iter.m_matrix);
    if (this != &iter)
    {
        m_irow = iter.m_irow;
        m_pt_icol = iter.m_pt_icol;
    }
    return *this;
}
// --------------------------------------------------------------------------------------------------------------------
bool SparseMatrix::iterator::operator != ( iterator const& iter )
{
    return ( (&m_matrix != &iter.m_matrix) ||
             (m_irow    != iter.m_irow)    ||
             (m_pt_icol != iter.m_pt_icol) );
}
// --------------------------------------------------------------------------------------------------------------------
auto  SparseMatrix::iterator::operator ++ (   ) -> iterator&
{
    ++ m_pt_icol;
    if (m_matrix.m_beg_rows[m_irow+1] <= m_pt_icol) ++m_irow;
    return *this;
}
// --------------------------------------------------------------------------------------------------------------------
auto SparseMatrix::iterator::operator  ++ (int) -> iterator
{
    iterator oldIter = *this;
    ++ m_pt_icol;
    if (m_matrix.m_beg_rows[m_irow+1] <= m_pt_icol) ++m_irow;
    return oldIter;
}
// --------------------------------------------------------------------------------------------------------------------
double& SparseMatrix::iterator::operator *()
{
    return m_matrix.m_coefficients[m_pt_icol];
}
// ====================================================================================================================
SparseMatrix::const_iterator::const_iterator( SparseMatrix const& t_spMatrix )
    : m_matrix(t_spMatrix)
{}
// --------------------------------------------------------------------------------------------------------------------
SparseMatrix::const_iterator::const_iterator( SparseMatrix const& t_spMatrix, std::size_t t_pt_icol )
    : m_matrix(t_spMatrix),
      m_pt_icol(t_pt_icol)
{
    while ((t_spMatrix.m_beg_rows[m_irow+1] < t_pt_icol) && (m_irow < t_spMatrix.dimensions().nrows))
        ++m_irow;
}
// --------------------------------------------------------------------------------------------------------------------
SparseMatrix::const_iterator::const_iterator( const_iterator const& iter )
    : m_matrix(iter.m_matrix),
      m_irow(iter.m_irow),
      m_pt_icol(iter.m_pt_icol)
{}
// ====================================================================================================================
auto SparseMatrix::const_iterator::operator = ( const_iterator const& iter ) -> const_iterator& 
{
    assert(&m_matrix == &iter.m_matrix);
    if (this != &iter)
    {
        m_irow = iter.m_irow;
        m_pt_icol = iter.m_pt_icol;
    }
    return *this;
}
// --------------------------------------------------------------------------------------------------------------------
bool SparseMatrix::const_iterator::operator != ( const_iterator const& iter )
{
    return ( (&m_matrix != &iter.m_matrix) ||
             (m_irow    != iter.m_irow)    ||
             (m_pt_icol != iter.m_pt_icol) );
}
// --------------------------------------------------------------------------------------------------------------------
auto  SparseMatrix::const_iterator::operator ++ (   ) -> const_iterator&
{
    ++ m_pt_icol;
    if (m_matrix.m_beg_rows[m_irow+1] <= m_pt_icol) ++m_irow;
    return *this;
}
// --------------------------------------------------------------------------------------------------------------------
auto SparseMatrix::const_iterator::operator  ++ (int) -> const_iterator
{
    const_iterator oldIter = *this;
    ++ m_pt_icol;
    if (m_matrix.m_beg_rows[m_irow+1] <= m_pt_icol) ++m_irow;
    return oldIter;
}
// --------------------------------------------------------------------------------------------------------------------
double const& SparseMatrix::const_iterator::operator *()
{
    return m_matrix.m_coefficients[m_pt_icol];
}
// ====================================================================================================================
SparseMatrix::SparseMatrix( DimensionType const& t_dimensions )
    : m_dimensions(t_dimensions),
      m_beg_rows(t_dimensions.nrows+1, 0)
{}
// --------------------------------------------------------------------------------------------------------------------
SparseMatrix::SparseMatrix( DimensionType const& t_dimensions, std::list<EltType> const& elts )
    : m_dimensions(t_dimensions),
      m_beg_rows(t_dimensions.nrows+1)
{
    auto compare = [](EltType const& e1, EltType const& e2) {
            if (e1.indices.irow < e2.indices.irow ) return true;
            if (( (e1.indices.irow == e2.indices.irow )) && 
                (e1.indices.icol < e2.indices.icol    )) return true;
            return false;
        };
    std::list<EltType> lstElts(elts);
    if (!std::is_sorted(lstElts.begin(), lstElts.end(), compare))
    {
        lstElts.sort(compare);
    }
    m_ind_columns.reserve(elts.size());
    m_coefficients.reserve(elts.size());

    std::vector<std::size_t> nbEltsPerRow(t_dimensions.nrows,0);
    for (auto const& e : lstElts)
    {
        nbEltsPerRow[e.indices.irow] += 1;
        m_ind_columns.emplace_back(e.indices.icol);
        m_coefficients.emplace_back(e.coef);
    }
    m_beg_rows[0] = 0;
    for (std::size_t i=1; i<=m_dimensions.nrows; ++i) m_beg_rows[i] = m_beg_rows[i-1]+nbEltsPerRow[i-1];
    assert(m_beg_rows[m_dimensions.nrows] == lstElts.size());
}
// --------------------------------------------------------------------------------------------------------------------
SparseMatrix::SparseMatrix( DimensionType const& t_dimensions, std::list<EltType>     && elts )
    : m_dimensions(t_dimensions),
      m_beg_rows(t_dimensions.nrows+1)
{
    auto compare = [](EltType const& e1, EltType const& e2) {
            if (e1.indices.irow < e2.indices.irow ) return true;
            if (( (e1.indices.irow == e2.indices.irow )) && 
                (e1.indices.icol < e2.indices.icol    )) return true;
            return false;
        };
    std::list<EltType> lstElts(std::move(elts));
    if (!std::is_sorted(lstElts.begin(), lstElts.end(), compare))
    {
        lstElts.sort(compare);
    }
    m_ind_columns.reserve(elts.size());
    m_coefficients.reserve(elts.size());

    std::vector<std::size_t> nbEltsPerRow(t_dimensions.nrows,0);
    for (auto const& e : lstElts)
    {
        nbEltsPerRow[e.indices.irow] += 1;
        m_ind_columns.emplace_back(e.indices.icol);
        m_coefficients.emplace_back(e.coef);
    }
    m_beg_rows[0] = 0;
    for (std::size_t i=1; i<=m_dimensions.nrows; ++i) m_beg_rows[i] = m_beg_rows[i-1]+nbEltsPerRow[i-1];
    assert(m_beg_rows[m_dimensions.nrows] == lstElts.size());
}
// --------------------------------------------------------------------------------------------------------------------
SparseMatrix::SparseMatrix( DimensionType const& t_dimensions, std::vector<std::size_t> const& t_beg_rows,
                            std::vector<std::size_t> const& t_ind_cols )
    : m_dimensions(t_dimensions),
      m_beg_rows(t_beg_rows),
      m_ind_columns(t_ind_cols),
      m_coefficients(m_ind_columns.size())
{
    assert(m_beg_rows[m_dimensions.nrows] == m_ind_columns.size());
}
// --------------------------------------------------------------------------------------------------------------------
SparseMatrix::SparseMatrix( DimensionType const& t_dimensions, std::vector<std::size_t> && t_beg_rows,
                            std::vector<std::size_t> && t_ind_cols )
    : m_dimensions(t_dimensions),
      m_beg_rows(std::move(t_beg_rows)),
      m_ind_columns(std::move(t_ind_cols)),
      m_coefficients(m_ind_columns.size())
{
    assert(m_beg_rows[m_dimensions.nrows] == m_ind_columns.size());
}
// --------------------------------------------------------------------------------------------------------------------
SparseMatrix::SparseMatrix( DimensionType const& t_dimensions, std::vector<std::size_t> const& t_beg_rows,
                            std::vector<std::size_t> const& t_ind_cols, std::vector<double> const& t_coefs )
    : m_dimensions(t_dimensions),
      m_beg_rows(t_beg_rows),
      m_ind_columns(t_ind_cols),
      m_coefficients(t_coefs)
{
    assert(m_beg_rows[m_dimensions.nrows] == m_ind_columns.size());
    assert(m_beg_rows[m_dimensions.nrows] == m_coefficients.size());
}
// --------------------------------------------------------------------------------------------------------------------
SparseMatrix::SparseMatrix( DimensionType const& t_dimensions, std::vector<std::size_t> && t_beg_rows,
                            std::vector<std::size_t> && t_ind_cols, std::vector<double> && t_coefs )
    : m_dimensions(t_dimensions),
      m_beg_rows(std::move(t_beg_rows)),
      m_ind_columns(std::move(t_ind_cols)),
      m_coefficients(std::move(t_coefs))
{
    assert(m_beg_rows[m_dimensions.nrows] == m_ind_columns.size());
    assert(m_beg_rows[m_dimensions.nrows] == m_coefficients.size());
}
// ====================================================================================================================
Vecteur SparseMatrix::operator * ( Vecteur const& u ) const
{
    assert(u.dimension() == m_dimensions.ncols);
    Vecteur w(m_dimensions.nrows);
    for (std::size_t irow = 0; irow < m_dimensions.nrows; ++irow)
    {
        w[irow] = 0.;
        for (std::size_t pt_row = m_beg_rows[irow]; pt_row < m_beg_rows[irow+1]; ++pt_row )
            w[irow] += m_coefficients[pt_row]*u[m_ind_columns[pt_row]];
    }
    return w;
}
// --------------------------------------------------------------------------------------------------------------------
#if __cplusplus > 202002L
double SparseMatrix::operator[] (std::size_t i, std::size_t j) const
{
    for (std::size_t pt_row = m_beg_rows[i]; pt_row < m_beg_rows[i+1]; ++pt_row)
    {
        if (m_ind_columns[pt_row] == j) return m_coefficients[pt_row];
        if (m_ind_columns[pt_row] > j ) break; 
    }
    return 0;
}
#else
double SparseMatrix::operator[] ( std::pair<std::size_t,std::size_t> const& inds) const
{
    std::size_t i = inds.first, j = inds.second;
    for (std::size_t pt_row = m_beg_rows[i]; pt_row < m_beg_rows[i+1]; ++pt_row)
    {
        if (m_ind_columns[pt_row] == j) return m_coefficients[pt_row];
        if (m_ind_columns[pt_row] > j ) break; 
    }
    return 0;
}
#endif
// --------------------------------------------------------------------------------------------------------------------
auto SparseMatrix::dimensions() const -> DimensionType
{
    return m_dimensions;
}
// --------------------------------------------------------------------------------------------------------------------
double SparseMatrix::frobeniusNorm() const
{
    double sum = 0;
    for (auto const& val : m_coefficients) sum += val*val;
    return std::sqrt(sum);
}
// --------------------------------------------------------------------------------------------------------------------
std::ostream& 
SparseMatrix::write(std::ostream& out,std::ios::openmode mode) const
{
    if (mode & std::ios::binary)
    {
        out.write((char const*)&m_dimensions, sizeof(m_dimensions));
        out.write((char const *)m_beg_rows.data(), m_beg_rows.size()*sizeof(std::size_t));
        out.write((char const *)m_ind_columns.data(), m_ind_columns.size()*sizeof(std::size_t));
        out.write((char const *)m_coefficients.data(), m_coefficients.size()*sizeof(double));
    }
    else
    {
        out << m_dimensions.nrows << " " << m_dimensions.ncols << std::endl;
        for (auto const &val : m_beg_rows) out << val << " ";
        out << std::endl;
        for (auto const &val : m_ind_columns) out << val << " ";
        out << std::endl;
        for (auto const &val : m_coefficients) out << val << " ";
    }
    return out;
}
// --------------------------------------------------------------------------------------------------------------------
SparseMatrix::operator std::string() const
{
    SparseMatrix const& A(*this);
    std::string repr;
    if (m_dimensions.nrows == 0) return "[]"s;
    // Affichage première ligne :
    if (m_dimensions.nrows == 1)
        repr += "[ ";
    else
        repr += "┌ "s;
    for (std::size_t j=0; j<std::min(5ULL,m_dimensions.ncols); ++j)
    {
#       if __cplusplus > 202002L
        repr += std::to_string(A[0,j]) + " "s;
#       else
        repr += std::to_string(A[{0,j}]) + " "s;
#       endif
    }
    if (m_dimensions.ncols > 10) repr += "... "s;

    for (std::size_t j=std::max(5ULL,m_dimensions.ncols-5); j < m_dimensions.ncols; ++j)
    {
#       if __cplusplus > 202002L
        repr += std::to_string(A[0,j]) + " "s;
#       else
        repr += std::to_string(A[{0,j}]) + " "s;
#       endif
    }
    if (m_dimensions.nrows == 1)
        repr += "]";
    else
        repr += "┐\n"s;
    std::size_t nbStrCols = repr.size() - 7;
    for (std::size_t i=1; i<std::min(5ULL,m_dimensions.nrows-1); ++i)
    {
        repr += "│ "s;
        for (std::size_t j=0; j<std::min(5ULL,m_dimensions.ncols); ++j)
        {
#           if __cplusplus > 202002L
            repr += std::to_string(A[i,j]) + " "s;
#           else 
            repr += std::to_string(A[{i,j}]) + " "s;
#           endif
        }
        if (m_dimensions.ncols > 10) repr += "... "s;
        for (std::size_t j=std::max(5ULL,m_dimensions.ncols-5); j < m_dimensions.ncols; ++j)
        {
#           if __cplusplus > 202002L
            repr += std::to_string(A[i,j]) + " "s;
#           else
            repr += std::to_string(A[{i,j}]) + " "s;
#           endif
        }
        repr += "│\n"s;
    }
    if (m_dimensions.nrows > 10) repr += "┆"s + std::string(nbStrCols, ' ') + "┆\n";
    for (std::size_t i=std::max(5ULL,m_dimensions.nrows-5); i < m_dimensions.nrows-1; ++i)
    {
        repr += "│ "s;
        for (std::size_t j=0; j<std::min(5ULL,m_dimensions.ncols); ++j)
        {
#           if __cplusplus > 202002L
            repr += std::to_string(A[i,j]) + " "s;
#           else 
            repr += std::to_string(A[{i,j}]) + " "s;
#           endif
        }
        if (m_dimensions.ncols > 10) repr += "... "s;
        for (std::size_t j=std::max(5ULL,m_dimensions.ncols-5); j < m_dimensions.ncols; ++j)
        {
#           if __cplusplus > 202002L
            repr += std::to_string(A[i,j]) + " "s;
#           else 
            repr += std::to_string(A[{i,j}]) + " "s;
#           endif
        }
        repr += "│\n"s;
    }
    // Dernière ligne :
    if (m_dimensions.nrows > 1)
    {
        std::size_t i = m_dimensions.nrows-1;
        repr += "└ "s;
        for (std::size_t j=0; j<std::min(5ULL,m_dimensions.ncols); ++j)
        {
#           if __cplusplus > 202002L
            repr += std::to_string(A[i,j]) + " "s;
#           else 
            repr += std::to_string(A[{i,j}]) + " "s;
#           endif
        }
        if (m_dimensions.ncols > 10) repr += "... "s;
        for (std::size_t j=std::max(5ULL,m_dimensions.ncols-5); j < m_dimensions.ncols; ++j)
        {
#           if __cplusplus > 202002L
            repr += std::to_string(A[i,j]) + " "s;
#           else 
            repr += std::to_string(A[{i,j}]) + " "s;
#           endif
        }
        repr += "┘"s;
    }
    return repr;
}
