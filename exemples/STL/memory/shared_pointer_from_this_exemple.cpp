#include <memory>
#include <iostream>

namespace Expression 
{
struct Node : public std::enable_shared_from_this<Node> {
    virtual ~Node() = default;
    virtual std::ostream& display(std::ostream& out) const = 0;
    std::shared_ptr<Node> getptr() { return shared_from_this(); }
};

class Addition : public Node  {
public:
    static std::shared_ptr<Node> create() { return std::shared_ptr<Addition>(new Addition()); }
    virtual ~Addition() = default;
    std::ostream& display(std::ostream& out) const override 
    {   out << "+"; return out;   }
private:
    Addition() = default;     };

struct Multiplication : public Node {
public:
    static std::shared_ptr<Node> create() { return std::shared_ptr<Multiplication>(new Multiplication()); }
    virtual ~Multiplication() = default;
    std::ostream& display(std::ostream& out) const override 
    {   out << "*"; return out;   }
private:
    Multiplication() = default;    };

}

std::ostream& operator << ( std::ostream& out, Expression::Node const& expr )
{
    return expr.display(out);
}

int main()
{
    auto ptrAdd = Expression::Addition::create();
    auto ptrMul = Expression::Multiplication::create();
    auto ptrExp = ptrAdd->getptr();
    std::cout << "ptrAdd : " << *ptrAdd << ", ptrMul : " << *ptrMul << ", ptrExp : " << *ptrExp << std::endl; 

    return EXIT_SUCCESS;
}
