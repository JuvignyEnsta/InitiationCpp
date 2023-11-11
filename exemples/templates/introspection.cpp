#include <array>
#include <utility>
#include <iostream>

class A
{
public:
    A(int i) : m_val(i) {}
    ~A() {}

    std::ostream& serialize(std::ostream& out) const 
    { 
        out << "A -> Serialize " << m_val << std::endl; 
        return out;
    }
private:
    int m_val;
};

class B
{
public:
    B(double x) : m_val(x) {}
    ~B() {}

    std::ostream& fmtSave(std::ostream& out) const 
    { 
        out << "B -> fmtSave " << m_val << std::endl; 
        return out;
    }
private:
    double m_val;
};

template<typename K> struct has_serialize {
    template<typename C> static constexpr decltype(std::declval<C>().serialize(std::cout), bool()) 
    test(int) { return true; }

    template<typename C> static constexpr bool test(...) { return false; }
    static constexpr bool value = test<K>(int());
};

template<typename K> std::ostream& save( K const& obj, std::ostream& out) {
    if constexpr (has_serialize<K>::value)
    {
        return obj.serialize(out);
    }
    else
    {
        return obj.fmtSave(out);
    }
}

int main()
{
    A a(1);
    B b(2.);

    save(a,std::cout);
    save(b,std::cout);

    return EXIT_SUCCESS;
}