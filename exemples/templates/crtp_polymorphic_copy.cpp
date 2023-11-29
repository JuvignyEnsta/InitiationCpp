#include <iostream>
#include <memory>

class Shape 
{// Base class has a pure virtual function for cloning
public:
    virtual ~Shape() {};
    virtual std::shared_ptr<Shape> clone() const = 0; 
};

template <typename Derived> class Shape_CRTP : public Shape 
{
public: // This CRTP class implements clone() for Derived
    virtual std::shared_ptr<Shape> clone() const override
    { 
        return std::make_shared<Derived>(static_cast<Derived const&>(*this)); 
    } 
};

// Nice macro which ensures correct CRTP usage
#define Derive_Shape_CRTP(Type) class Type: public Shape_CRTP<Type>

Derive_Shape_CRTP(Square) { // class Square: public Shape_CRTP<Square> {
public:
    Square() = default;
    Square( Square const& ) { std::cout << __PRETTY_FUNCTION__ << std::endl; }
};

Derive_Shape_CRTP(Circle) {// class Circle: public Shape_CRTP<Circle> {
public:
    Circle() = default;
    Circle( Circle const& ) { std::cout << __PRETTY_FUNCTION__ << std::endl; }

};

void dup( std::shared_ptr<Shape> pt_shape )
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    auto toto = pt_shape->clone();
}

int main()
{
    auto  pt_sq = std::make_shared<Square>();
    auto  pt_ci = std::make_shared<Circle>();

    dup(pt_sq);
    dup(pt_ci);

    return EXIT_SUCCESS; 
}