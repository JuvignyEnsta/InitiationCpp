#include <type_traits>
#include <iostream>
#include <vector>
#include <utility>

template<std::size_t... dims>
void displayDimensions( std::integer_sequence<std::size_t, dims...> )
{   ((std::cout << "[" << dims << "]"),...);    }

template<typename CArray, int dim, std::size_t... dims>
auto get_dimensions( std::integer_sequence<std::size_t,dims...> ) {
    if constexpr (dim > 0) {
        return get_dimensions<CArray, dim-1>( std::integer_sequence<std::size_t, 
                                              std::extent_v<CArray,dim>, dims...>{} );
    } else { return std::integer_sequence<std::size_t, std::extent_v<CArray,0>, dims...>{}; }
}
template<typename CArray> void displayCArray( CArray const& t_array ) {
    if constexpr ( std::is_bounded_array_v<CArray> ) {
        constexpr auto ndims = std::rank_v<CArray>;
        auto dimensions = get_dimensions<CArray, ndims-1>(std::integer_sequence<std::size_t>{});
        std::cout << "Tableau"; displayDimensions(dimensions);
    } else { std::cout << "Tableau à dimension indéfinie" << std::endl;  }
}

int main()
{
    double tableau[5][3][2];
    double tableau2[] = {1.,2.,3.};

    displayCArray(tableau);
    displayCArray(tableau2);
    return EXIT_SUCCESS;
}
