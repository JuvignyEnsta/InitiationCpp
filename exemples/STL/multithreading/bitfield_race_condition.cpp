#include <thread>
#include <iostream>
#include <cassert>
#include <cstdint>

/**
   Normalement, le compilateur C++ garantit que si deux threads individuellement modifient chacun un membre différent de la structure,
   il n'y a pas de race-condition. Pour cela, il copie le minimum d'octets ou bien il fait un padding afin que les deux membres soient
   séparés d'un certain nombre d'octets afin de garantir qu'il n'y a pas de race conditon.
   Ici, on est assez vicieux, puisque pour réduire la taille de la structure, on a décidé de définir un entier sur 9 bits et en entier
   sur 7 bits qui sont normalement compactés sur 16 bits d'après le standard (deux bitfields adjacents forment un même objet).
*/
struct S
{
    int a:9;
    int b:7;
};

/**
   Ici, rien de tel, car le compilateur garantit bien que les deux membres peuvent être initialisés séparément sans effet de bord.
*/
struct S2
{
    std::int16_t a;
    std::int8_t  b;
};

int main()
{
    std::mutex m;
    constexpr int nbSamples = 20'000;
    S s{.a=10,.b=11};
    assert(s.a==10);
    assert(s.b==11);
    s.a = -1;
    s.b =  4;
    assert(s.a==-1);
    assert(s.b== 4);
    int nbSuccess = 0;
    for ( int iSample=0;iSample<nbSamples;++iSample )
    {
        S s{.a=10,.b=11};
        
        std::thread t1([&s,&m](){ std::lock_guard g(m); s.a = -1; });
        std::thread t2([&s,&m](){ std::lock_guard g(m); s.b =  4; });
        t1.join(); t2.join();
        if ( (s.a==-1) && (s.b == 4) ) ++nbSuccess;
    }
    std::cout << "Initialisation réussie " << nbSuccess << "/" << nbSamples << " fois." << std::endl;

    nbSuccess = 0;
    for ( int iSample=0;iSample<nbSamples;++iSample )
    {
        S2 s{.a=10,.b=11};
        std::thread t1([&s](){ s.a = -1; });
        std::thread t2([&s](){ s.b =  4; });
        t1.join(); t2.join();
        if ( (s.a==-1) && (s.b == 4) ) ++nbSuccess;
    }
    std::cout << "Initialisation réussie " << nbSuccess << "/" << nbSamples << " fois." << std::endl;

    return EXIT_SUCCESS;
}
