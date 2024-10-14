#include <iostream>
#include <vector>
#include <cassert>

/**
 * @brief Une matrice de taille n_rows x n_cols
 */
class Matrix 
{
public:

    /**
     * @brief Un indice de la matrice
     */
    class Indice
    {
    public:
        /**
         * @brief Constructeur de l'indice
         * @param A la matrice
         * @param i la ligne
         * @param j la colonne
         */
        Indice( Matrix& A, int i, int j )
            : i_row{i}, j_col{j}, m_mat{A}
        {}

        /**
         * @brief Incrémente l'indice (pré incrémentation)
         * @return l'indice incrémenté
         */
        Indice& operator++()
        {
            ++j_col;
            if ( j_col == m_mat.cols )
            {
                j_col = 0;
                ++i_row;
            }
            return *this;
        }

        /**
         * @brief Décrémente l'indice (pré décrémentation)
         * @return l'indice décrémenté
         */
        Indice& operator--()
        {
            --j_col;
            if ( j_col == -1 )
            {
                j_col = m_mat.cols - 1;
                --i_row;
            }
            return *this;
        }

        /**
         * @brief Incrémente l'indice (post incrémentation)
         * @return  l'indice avant décrémentation
         */
        Indice operator++( int )
        {
            Indice tmp = *this;
            ++(*this);
            return tmp;
        }

        /**
         * @brief Décrémente l'indice (post décrémentation)
         * @return  l'indice avant décrémentation
         */
        Indice operator--( int )
        {   
            Indice tmp = *this;
            --(*this);
            return tmp;
        }

        int i_row{0}, j_col{0};
    private:
        Matrix& m_mat;
    };

    /** 
     * @brief Construit une matrice de taille n_rows x n_cols   
     * @param n_rows le nombre de lignes
     * @param n_cols le nombre de colonnes
     */
    Matrix( int n_rows, int n_cols) :
        data(n_rows * n_cols),
        rows(n_rows),
        cols(n_cols)
    {}

    Matrix( int n_rows, int n_cols, double val ) :
        data(n_rows * n_cols, val),
        rows(n_rows),
        cols(n_cols)
    {}

    double& operator[] ( Indice i ) 
    {
        return data[i.i_row * cols + i.j_col];
    }

    const double& operator[] ( Indice i ) const
    {
        return data[i.i_row * cols + i.j_col];
    }

    double& operator() ( int i, int j )
    {
        assert( (i>=0) && (i < rows) );
        return data[i * cols + j ];
    }
private:
    std::vector<double> data;
    int rows;
    int cols;
};

int main()
{
    Matrix A(3, 3, 0.0);
    A(0,0) = 1.0; A(1,1) = 1.0; A(2,2) = 1.0;
    Matrix::Indice i(A, 0, 0);

    for ( Matrix::Indice i{A,0,0}; i.i_row < 3; ++i )
    {
        std::cout << A[i] << " ";
    }
    std::cout << std::endl;

    return EXIT_SUCCESS;
}