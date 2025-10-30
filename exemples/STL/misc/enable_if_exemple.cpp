#include <type_traits>
#include <concepts>
#include <array>
#include <vector>
#include <cstdlib>

template<typename T, std::enable_if_t<std::is_integral<T>::value,bool> = true >
void incrementCounter( T& t_counter )
{   ++t_counter;    }

struct T {
    enum { int_t, float_t } type;
    template <typename Integer,
              std::enable_if_t<std::is_integral<Integer>::value, bool> = true
    >
    T(Integer) : type(int_t) {}
 
    template <typename Floating,
              std::enable_if_t<std::is_floating_point<Floating>::value, bool> = true
    >
    T(Floating) : type(float_t) {} // OK
};

template<typename T, int ndims, std::enable_if_t<(ndims>0),int> = 0>
class NdArray {
public:
    NdArray( std::array<std::size_t, ndims> const& t_ndims )
        :   m_dimensions(t_ndims)    {
        std::size_t nbCoefs = 1;
        for ( std::size_t indDim = 0; indDim<ndims; ++indDim )
            nbCoefs *= t_ndims[indDim];
        std::vector<T>(nbCoefs).swap(m_coefficients);
    }
    template<std::size_t indice0, std::size_t... indicesn, 
             std::enable_if_t<(sizeof...(indicesn)<ndims),bool> =true> 
    constexpr std::size_t globalIndex(std::size_t index = 0)    {
        std::size_t globIndex = indice0*m_dimensions[index];
        if constexpr (sizeof...(indicesn) > 0) globIndex += globalIndex<indicesn...>(index+1);
        return globIndex;
    }

    template<std::size_t... indices, 
             std::enable_if_t<(sizeof...(indices)==ndims),bool> =true>
    T const& get() const {   return m_coefficients[globalIndex<indices...>()];    }

    template<std::size_t... indices, 
             std::enable_if_t<(sizeof...(indices)==ndims),bool> =true>
    T& get() {   return m_coefficients[globalIndex<indices...>()];    }

private:
    std::vector<T> m_coefficients{};
    std::array<std::size_t,ndims> m_dimensions{};
};

int main()
{
    int counter = 0;
    incrementCounter(counter);
    float fcounter = 0.f;
    //incrementCounter(fcounter); // Erreur de compilation

    T(3);
    T(3.4);

    NdArray<double,2> A({4,4});
    A.get<0,0>() = 1.;
    //A.get<0,3,2>() = 2.;
    //A.get<1>() = 3.;

    NdArray<double,1> u({4});

    //NdArray<double,0> v({});
    return EXIT_SUCCESS;
};
