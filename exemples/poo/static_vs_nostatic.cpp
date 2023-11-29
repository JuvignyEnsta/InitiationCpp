#include <iostream>

class A
{
private:
    static int counter;
public:

    A()
    {
        counter += 1;
    }
    A( A const& a ) : i(a.i)
    {
        counter += 1;
    }
    ~A() { counter -= 1; }

    int i;

    void f() const;
    static void displayCounter() { std::cout << "Nombre d'instances de A : " << counter << std::endl; }
};

int A::counter = 0;

void A::f() const
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    std::cout << "i = " << this->i << std::endl;
}


int main()
{
    A a, b; a.i = 3; b.i = 4;

    A::displayCounter();

    {
        A c;
        A::displayCounter();
    }

    A::displayCounter();

    return EXIT_SUCCESS;
}