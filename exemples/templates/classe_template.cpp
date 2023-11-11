#include <iostream>

class A {
public:
    template<typename K> A( K const& valeur );

    template<typename K> K f( K const& valeur );
};

template<typename K>
A::A( K const& valeur )
{
    std::cout << __PRETTY_FUNCTION__ << std::endl; 
}

template<typename K>
K A::f( K const& valeur ) {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    return valeur;
}

template<typename K1> class B {
public:
    template<typename K2> B( K2 const& valeur );

    template<typename K2> K2 f( K2 const& valeur );
};

template<typename K1> template<typename K2> 
B<K1>::B( K2 const& valeur )
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}

template<typename K1> template<typename K2> K2
B<K1>::f( K2 const& valeur  )
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    return valeur;
}

int main()
{
    A a1(3);
    A a2(3.);
    a1.f(3.);
    a2.f(3);

    B<int> b1(3.);
    B<int> b2(3);
    b1.template f<double>(3.);
    b2.f(3);

    return EXIT_SUCCESS;
}