#include <iostream>

namespace géométrie
{
    void afficheContexte() { std::cout << "géométrie" << std::endl; }
}

namespace algébre
{
    void afficheContexte() { std::cout << "algébre" << std::endl; }
}

namespace version1
{
    void afficheVersion() { std::cout << "version 1 " << std::endl; }
}

inline namespace version2
{
    void afficheVersion() { std::cout << "version 2 " << std::endl; }
}

// utilisation avancée des espaces de nommage en ligne avec les templates (voir cours sur les templates)
namespace A 
{
    inline namespace B 
    {
        template<typename K> void f(K const& ) { std::cout << __PRETTY_FUNCTION__ << std::endl; }

        namespace C
        {
            void g() { std::cout << __PRETTY_FUNCTION__ << std::endl; }
        }

        inline namespace D
        {
            void h() { std::cout << __PRETTY_FUNCTION__ << std::endl; }
        }
    }
    // Spécialisation de la fonction templatée dans B :
    template<> void f(int const& ) { std::cout << "f(int) spécialisé" << std::endl; }
}

int main()
{
    géométrie::afficheContexte();
    algébre::afficheContexte();

    afficheVersion();

    std::cout << "A::f(3.15)" << std::endl;
    A::f(3.15);
    std::cout << "A::B::f(3)" << std::endl;
    A::B::f(3);
    std::cout << "A::B::f(3.14)" << std::endl;
    A::B::f(3.14);
    std::cout << "A::f(4)" << std::endl;
    A::f(4);

    A::C::g();

    A::h();
    return EXIT_SUCCESS;
}