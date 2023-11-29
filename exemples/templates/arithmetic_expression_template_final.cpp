# include <iostream>
# include <vector>
# include <typeinfo>
# include <utility>
# include <cmath>

template<typename Derived> struct expr
{
    auto operator()() { return static_cast<Derived&>(*this)(); }
};
// Terminaisons de l'arbre AST
// ---------------------------
template<typename K>
struct constante_ : public expr<constante_<K>>
{
    struct tag {};
    constante_( const K& cte ) : m_cte(cte)
    {}
    const K& get() const { return m_cte; } 
    auto operator() () const { return [=](auto visitor) { return visitor(tag{},m_cte); }; }    
private:
    K m_cte;
};
template<typename K, typename...Args> constante_<K> constante(Args&&... args) { return {K(std::forward<Args>(args)...)}; }

template<typename K>
struct variable_ : public expr<variable_<K>>
{
    struct tag {};
    variable_() : m_value() {}
    variable_(const K& val ) : m_value(val) {}
    auto operator = ( const K& val ) {
        m_value = val;
        return *this;
    }
    K& get() & { return m_value; }
    K&& get() && { return m_value; }
    auto operator() () const { return [&](auto visitor) { return visitor(tag{},this->m_value); }; }
    
private:
    K m_value; 
};
template<typename K, typename...Args> variable_<K> variable(Args&&... args) { return {K(std::forward<Args>(args)...)}; }

// Traits pour aider à l'expression des templates
// ----------------------------------------------
template<typename K> struct expr_traits
{
    using type = K;
};
template<> struct expr_traits<double>
{
    using type=constante_<double>;
};
template<> struct expr_traits<float>
{
    using type = constante_<float>;
};
template<> struct expr_traits<int>
{
    using type=constante_<int>;
};
template<> struct expr_traits<long>
{
    using type=constante_<long>;
};

// Opérations binaires
// -------------------
template<typename Expr1, typename Expr2, typename Tag>
struct binary_op_ : public expr<binary_op_<Expr1,Expr2,Tag>>
{
    binary_op_( const Expr1& e1, const Expr2& e2 ) : m_expr1(e1), m_expr2(e2)
    {}
    const Expr1& left () const { return m_expr1; }
    const Expr2& right() const { return m_expr2; }

    auto operator() () const { return [&](auto visitor) { return visitor(Tag{},m_expr1()(visitor),m_expr2()(visitor)); }; }
    
private:
    Expr1 m_expr1;
    Expr2 m_expr2;    
};

struct sum_op_tag{};
template<typename Expr1, typename Expr2> struct sum_op_ : public binary_op_<Expr1,Expr2,sum_op_tag>
{
    sum_op_( Expr1&& e1, Expr2&& e2 ) : binary_op_<Expr1,Expr2,sum_op_tag>(e1,e2) {}    
};
template<typename Expr1, typename Expr2> sum_op_<typename expr_traits<Expr1>::type,
                                                 typename expr_traits<Expr2>::type> operator +( const Expr1& e1, const Expr2& e2) {
    return {typename expr_traits<Expr1>::type(e1),typename expr_traits<Expr2>::type(e2)};
}

struct sub_op_tag{};
template<typename Expr1, typename Expr2> struct sub_op_ : public binary_op_<Expr1,Expr2,sub_op_tag>
{                                     
    sub_op_( const Expr1& e1, const Expr2& e2 ) : binary_op_<Expr1,Expr2,sub_op_tag>(e1,e2) {}    
};
template<typename Expr1, typename Expr2> sub_op_<typename expr_traits<Expr1>::type,
                                                 typename expr_traits<Expr2>::type> operator -( const Expr1& e1, const Expr2& e2) {
    return {typename expr_traits<Expr1>::type(e1),typename expr_traits<Expr2>::type(e2)};
}

struct mul_op_tag{};
template<typename Expr1, typename Expr2> struct mul_op_ : public binary_op_<Expr1,Expr2,mul_op_tag>
{
    mul_op_( const Expr1& e1, const Expr2& e2 ) : binary_op_<Expr1,Expr2,mul_op_tag>(e1,e2) {}    
};
template<typename Expr1, typename Expr2> mul_op_<typename expr_traits<Expr1>::type,
                                                 typename expr_traits<Expr2>::type> operator *( const Expr1& e1, const Expr2& e2) {
    return {typename expr_traits<Expr1>::type(e1),typename expr_traits<Expr2>::type(e2)};
}

struct div_op_tag{};
template<typename Expr1, typename Expr2> struct div_op_ : public binary_op_<Expr1,Expr2,div_op_tag>
{                                     
    div_op_( const Expr1& e1, const Expr2& e2 ) : binary_op_<Expr1,Expr2,div_op_tag>(e1,e2) {}    
};
template<typename Expr1, typename Expr2> div_op_<typename expr_traits<Expr1>::type,
                                                 typename expr_traits<Expr2>::type> operator /( const Expr1& e1, const Expr2& e2) {
    return {typename expr_traits<Expr1>::type(e1),typename expr_traits<Expr2>::type(e2)};
}

//Unary expression
//--------------------
template<typename Expr, typename Tag>
struct unary_op_ : public expr<unary_op_<Expr,Tag>>
{
    unary_op_( const Expr& e ) : m_expr(e)
    {}
    const Expr& get() const { return m_expr; }

    auto operator() () const { return [&](auto visitor) { return visitor(Tag{},m_expr()(visitor)); }; }
    
private:
    Expr m_expr;
};

struct usub_op_tag{};
template<typename Expr> struct usub_op_ : public unary_op_<Expr,usub_op_tag>
{                                     
    usub_op_( const Expr& e ) : unary_op_<Expr,usub_op_tag>(e) {}    
};
template<typename Expr> usub_op_<typename expr_traits<Expr>::type> operator -( const Expr& e) {
    return {typename expr_traits<Expr>::type(e)};
}

struct sqrt_tag{};
template<typename Expr> struct sqrt_ : public unary_op_<Expr,sqrt_tag>
{                                     
    sqrt_( const Expr& e ) : unary_op_<Expr,sqrt_tag>(e) {}
};
template<typename Expr> sqrt_<typename expr_traits<Expr>::type> sqrt(const Expr& e) {
    return {typename expr_traits<Expr>::type(e)};
}

// Visitors
// -----------
struct scalar_evaluator {
    template<typename K>
    auto operator() (typename constante_<K>::tag, const K& v ){ return v; }
    template<typename K>
    const K& operator() (typename variable_<K>::tag, const K& v ){ return v; }
    template<typename K1, typename K2>
    auto operator() (sum_op_tag, const K1& e1, const K2& e2 ) { return e1+e2; }
    template<typename Expr1, typename Expr2>
    auto operator() (sub_op_tag, const Expr1& e1, const Expr2& e2) { return e1-e2; }
    template<typename Expr1, typename Expr2>
    auto operator() (mul_op_tag, const Expr1& e1, const Expr2& e2) { return e1*e2; }
    template<typename Expr1, typename Expr2>
    auto operator() (div_op_tag, const Expr1& e1, const Expr2& e2) { return e1/e2; }
    template<typename Expr>
    auto operator() (usub_op_tag, const Expr& e) { return -e; }
    template<typename Expr>
    auto operator() (sqrt_tag, const Expr& e ) { return std::sqrt(e); }
};

template<typename K>
struct complex {
    K re, im;
    complex(const K& v) : re(v),im(0) {}
    complex(const K& x, const K& y) : re(x), im(y) {}
};

struct complex_evaluator {
    template<typename K>
    auto operator() ( typename constante_<K>::tag, const K& v) { return v; }
    template<typename K>
    K operator() ( typename variable_<K>::tag, const K& v) { return v; }
    template<typename K>
    complex<K> operator() (sum_op_tag, const complex<K>& e1, const complex<K>& e2 ) { return {e1.re+e2.re,e1.im+e2.im}; }
    template<typename K>
    complex<K> operator() (sum_op_tag, const complex<K>& e1, const K& e2 ) { return {e1.re+e2,e1.im}; }
    template<typename K>
    complex<K> operator() (sub_op_tag, const complex<K>& e1, const complex<K>& e2) { return {e1.re-e2.re,e1.im-e2.im}; }
    template<typename K>
    complex<K> operator() (sub_op_tag, const complex<K>& e1, const K& e2) { return {e1.re-e2,e1.im}; }
    template<typename K>
    complex<K> operator() (mul_op_tag, const complex<K>& e1, const complex<K>& e2) { return {e1.re*e2.re-e1.im*e2.im,e1.re*e2.im+e1.im*e2.re}; }
    template<typename K>
    complex<K> operator() (mul_op_tag, const complex<K>& e1, const K& e2) { return {e1.re*e2,e1.im*e2}; }
    template<typename K>
    complex<K> operator() (div_op_tag, const complex<K>& e1, const complex<K>& e2) { K nrm2 = e2.re*e2.re+e2.im*e2.im; return {(e1.re*e2.re+e1.im*e1.im)/nrm2,(e1.im*e2.re-e1.re*e2.im)/nrm2}; }
    template<typename K>
    complex<K> operator() (div_op_tag, const complex<K>& e1, const K& e2) { return {e1.re/e2,e1.im/e2}; }
    template<typename K>
    complex<K> operator() (usub_op_tag, const K& e) { return -e; }
/*template<typename Expr>
  complex<K> operator() (sqrt_tag, const Expr& e ) { return std::sqrt(e); }*/
};

struct vector_evaluator {
    
};


#if defined(TESTING)
// tests
// -----------
int main()
{
    //auto t = constante<std::vector<double>>(std::initializer_list<double>{1.,2.,3.,4.});
    //std::cout << "Vecteur constant : ";
    ///for ( auto& c : t.get() ) std::cout << c << " ";
    //std::cout << std::endl;
    auto n = constante<std::size_t>(100UL);
    std::cout << n.get() << std::endl;
    auto v = variable<double>();
    v= 3.14;
    std::cout << v.get() << std::endl;
    auto s = n + v/2.5 - 4.*v;
    std::cout << "type of s : " << typeid(s()).name() << std::endl;
    scalar_evaluator s_eval;
    auto x = s()(s_eval);
    std::cout << "x = " << x << std::endl;
    auto z = variable<complex<double>>(complex<double>{1.,1.});
    auto t = z + (z*z)/2.;
    auto zr = t()(complex_evaluator{});
    std::cout << "z retourne : " << zr.re << " + " << zr.im << "i" << std::endl;
    return 0;
}
#endif
