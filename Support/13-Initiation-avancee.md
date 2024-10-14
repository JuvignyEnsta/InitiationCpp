# Initiation avancée

## Déduction du type de retour d'une fonction

Le C++ offre deux possibilités :

- Le type de retour est spécifié explicitement : on peut renvoyer la valeur de retour sous forme de liste d'initialisation. Par exemple :

```cpp
auto e1() -> std::array<double, 3> { return {1.0, 0.0, 0.0}; }
```

- On déclare en `auto` le type de retour sans préciser le type sous forme fonctionnelle (C++ 14) :

```cpp
auto e1() { return std::array{1.0, 0.0, 0.0}; }
```

Laisser déduire le type de retour par le C++ est nécessaire lorsqu'on veut renvoyer certaines valeurs comme les fonctions lambdas qui n'ont pas un seul type défini.

Par contre, attention pour la déduction automatique du type de retour, le C++ ne peut pas déduire le type de retour si on fait un return conditionnel ne possédant pas le même type selon la condtion :

```cpp
// La fonction suivante ne compile pas
auto esqrt( double x ) {
    if (x >= 0.0) {
        return std::sqrt(x); // On retourne un double
    } else {
        return 0; // On retourne un entier !
    }
}
```

Pour que cette fonction compile, il faut donc modifier le deuxième return :

```cpp
// Cette fois ci, la fonction compile !
auto esqrt( double x ) -> double {
    if (x >= 0.0) {
        return std::sqrt(x);
    } else {
        return 0.0;
    }
}
```

## Retourner plusieurs valeurs d'une fonction

Il arrive souvent qu'on ait besoin de retourner plusieurs valeurs d'une fonction.

### Passage des valeurs de sortie en paramètres

En C ou en C++ avant le C++ 11, on devait passer par référence ou par pointeur (partagé ou unique) les valeurs de sortie en paramètre de la fonction.

Si on passe une des valeurs de sortie par pointeur, il faut penser à initialiser le pointeur avant de faire l'appel de la fonction et ne pas passer un pointeur nul.

L'autre problème de cette approche est qu'on ne sépare pas clairement les paramètres en entrée et les paramètres en sortie.

**Exemple passage par référence d'un paramètre en sortie** :

```cpp
int division_euclidienne( int a, int b, int& reste )
{
    int resultat = a / b;
    reste = a - b * resultat;
    return resultat;
}
...
int quotient, reste;
quotient = division_euclidienne( 10, 3, reste );// reste en entrée ? (non), en sortie ? (oui)
```

**Même example avec passe par pointeur du paramètre de sortie** :

```cpp
int division_euclidienne( int a, int b, int* reste )
{
    int resultat = a / b;
    *reste = a - b * resultat;
    return resultat;
}
...
int quotient, reste;
quotient = division_euclidienne( 10, 3, &reste ); // Le & indique que reste est un paramètre en sortie, mais fragilité du code (reste peut être un pointeur nul)
```

### Retourner plusieurs valeurs avec des tableaux statiques

Lorsque les divers valeurs à retourner sont de même type, on peut utiliser un tableau statique de type `std::array` possédant les `N` valeurs à retourner.
Depuis le C++ 17, on peut recevoir directement les valeurs contenues dans le tableau statique directement dans des variables déclarées avec le mot clé `auto`.

En reprenant l'exemple précédent, on peut écrire :

```cpp
std::array<int, 2> division_euclidienne( int a, int b )
{
    return { a / b, a - b * (a / b) };
}
...
auto [quotient, reste] = division_euclidienne( 10, 3 );
```

Bien sûr, cette technique permet de retourner plus de deux valeurs par une fonction. Par exemple, écrivons et utilisons une fonction quie retourne les racines cubiques d'un complexe :

```cpp
std::array<std::complex<double>, 3> racines_cubiques( const std::complex<double>& z )
{
    constexpr double pi_2s3 = 2.0 * std::numbers::pi / 3.0;
    constexpr double pi_4s3 = 4.0 * std::numbers::pi / 3.0;
    double argument = std::arg( z )/3.0;
    double modules  = std::cbrt( std::abs( z ) );// std::cbrt = racine cubique
    return {
        std::polar( modules, argument ),
        std::polar( modules, argument + pi_2s3 ),
        std::polar( modules, argument + pi_4s3 )
    };
}
...
auto [z1, z2, z3] = racines_cubiques( 1. + 1.i );
```

### Retourner plusieurs valeurs avec des tuples ou des paires

Lorsque les différentes valeurs à retourner sont de types différents, on ne peut plus utiliser des tableaux statiques. 

Lorsqu'on a à retourner deux valeurs de types différents, on peut utiliser une `std::pair` proposé par la bibliothèque standard dans `<utility>`. Par exemple :

```cpp
std::pair<double,std::size_t> trouve_localise_max( const std::vector<double>& v )
{
    int index_max = 0;
    for ( std::size_t i = 1; i < v.size(); ++i ) {
        if ( v[i] > v[index_max] ) {
            index_max = i;
        }
    }
    return { v[index_max], index_max };
}
...
auto [max, index_max] = trouve_localise_max( { 1.0, 2.0, 3.0, 2.0, 1.0 } );
```

Lorsqu'on doit retourner plus de deux valeurs de types différents, on peut utiliser une `std::tuple` proposé par la bibliothèque standard dans `<tuple>`. Ce type est similaire au tuple existant dans le langage Python.

La déclaration d'un `std::tuple` est assez lourd à écrire. On préférera dans ce cas utiliser la déclaration implicite avec le mot clé `auto`.

Pour créer le tuple, il existe une fonction `std::make_tuple` dans `<tuple>` qui permet de construire le tuple de manière concise.

Par exemple, écrivons une fonction convertissant un double en une fraction rationnelle :

```cpp
auto double_en_rationnel( double x, int max_iter )
{
    std::int64_t dividende, diviseur;
    assert(x >= 0);
    std::int64_t partie_entiere = static_cast<std::int64_t>(x);
    double reste = x - partie_entiere;
    if (std::abs(reste) < 1e-14) {
        return std::make_tuple( partie_entiere, 1LL, 0.0 );
    }
    if (max_iter == 0) {
        return std::make_tuple( partie_entiere, 1LL, reste );
    }
    auto [p,q,r] = double_en_rationnel( 1.0 / reste, max_iter - 1 );
    dividende = p * partie_entiere + q;
    diviseur = p;
    reste = std::abs(x -double(dividende)/double(diviseur));
    return std::make_tuple( dividende, diviseur, reste );
}
...
auto [num, den, err] = double_en_rationnel( 3.141592653589793, 10 );
```

Néanmoins, toutes les solutions présentées jusqu'ici présentent un désavantage : elles n'expriment pas clairement les valeurs retournées par la fonction.

Une autre solution bien plus expressive existe, c'est de retourner une structure dont les champs sont les valeurs à retourner. Il se trouve qu'en C++ 17, on peut toujours ranger les valeurs retournées dans la structure dans des variables déclarées avec le mot clé `auto`.

Ainsi, pour reprendre l'exemple de la conversion d'un double en une fraction rationnelle, on peut écrire :

```cpp
struct FractionRationnelle {
    std::int64_t numérateur;
    std::int64_t dénominateur;
    double erreur;
};

FractionRationnelle double_en_rationnel( double x, int max_iter )
{
    std::int64_t dividende, diviseur;
    assert(x >= 0);
    std::int64_t partie_entiere = static_cast<std::int64_t>(x);
    double reste = x - partie_entiere;
    if (std::abs(reste) < 1e-14) {
        return {partie_entiere, 1LL, 0.0};
    }
    if (max_iter == 0) {
        return {partie_entiere, 1LL, reste};
    }
    auto [p,q,r] = double_en_rationnel( 1.0 / reste, max_iter - 1 );
    dividende = p * partie_entiere + q;
    diviseur = p;
    reste = std::abs(x -double(dividende)/double(diviseur));
    return {dividende, diviseur, reste};
}
...
auto [num, den, err] = double_en_rationnel( 3.141592653589793, 10 );
auto rationnel = double_en_rationnel{ std::sqrt(2), 20 };
std::cout << rationnel.numérateur << "/" << rationnel.dénominateur << " ± " << rationnel.erreur << std::endl;
```

### Compléments sur les liaisons structurées en C++ 17

Le fait de pouvoir stocker dans des variables indépendantes des valeurs stockées dans une structure est très pratique. Cette fonctionnalité est appelée liaisons structurées (structured bindings en anglais).

Avant C++ 17, on pouvait également utiliser des liaisons structurées mais uniquement en utilisant les fonctions std::tie et std::ignore (toujours valable en C++ 17).

Ces fonctions sont toujours utiles après C++ 17 car elles sont plus souples que la décompression de liaisons structurées à l'aide du mot clé `auto`.

Par exemple, pour reprendre l'exemple de la conversion d'un double en une fraction rationnelle, on peut écrire :

```cpp
auto [num, den, err] = double_en_rationnel( 3.141592653589793, 10 );
```

mais si on ne veut conserver qu'une partie des valeurs, on peut bien sûr utiliser une variable nommée `_` pour ignorer une valeur de retour et écrire :

```cpp
auto [num, den, _] = double_en_rationnel( 3.141592653589793, 10 );
```

Cependant, si on veut ignorer plusieurs valeurs de retour, on ne peut pas utiliser `_` plusieurs fois :

```cpp
// Erreur de compilation
auto [num, _, _] = double_en_rationnel( 3.141592653589793, 10 );
```

Par contre, en utilisant `std::tie`, on doit préalablement déclarer les variables dans lesquelles on souhaite stocker les valeurs de retour et les passer à `std::tie` si bien qu'on peut les reutiliser plusieurs fois. De plus, on peut utiliser `std::ignore` pour ignorer des valeurs de retour autant de fois que voulu.

Ainsi, pour reprendre l'exemple de la conversion d'un double en une fraction rationnelle, on peut écrire :

```cpp
std::int64_t num, den;
double err;
std::tie(num, den, err) = double_en_rationnel( 3.141592653589793, 10 );
// On ne s'intéresse ici uniquement à l'erreur de l'approximation
std::tie(std::ignore, std::ignore, err) = double_en_rationnel( 3.141592653589793, 10 );
```

## Retour par déplacement contre retour par copie

La règle de retour par déplacement est une optimisation du C++ qui permet de ne pas faire une copie inutile des objets retournés. La règle est la suivante :

- Le retour par valeur d'une variable locale provoque un retour par déplacement.
- Le retour par valeur d'une variable globale provoque un retour par copie.
- Le retour par valeur d'une variable statique provoque un retour par copie (NB : nous n'avons pas encore vu les variables statiques mais ce sont des variables globales liées au bloc courant).

Exemple :

```cpp
std::vector<double> operator + ( std::vector<double> const& u, std::vector<double> const& v ) {
    assert( u.size() == v.size() );
    std::vector<double> w(u.size());
    for ( std::size_t i = 0; i < u.size(); ++i ) {
        w[i] = u[i] + v[i];
    }
    return w;// w est retourné par déplacement
}
//
std::vector<double> operator += ( std::vector<double>& u, std::vector<double> const& v ) {
    assert( u.size() == v.size() );
    for ( std::size_t i = 0; i < u.size(); ++i ) {
        u[i] += v[i];
    }
    return u;// u est retourné par copie ! On a un coût de copie supplémentaire en O(n)
}
```

Pour éviter le coût de la copie, on peut utiliser un retour par référence mais attention à ne pas retourner une référence sur une variable locale qui sera détruite à la fin de la fonction.

Pour le cas de l'addition inplace, on peut bien sûr écrire :

```cpp
std::vector<double>& operator += ( std::vector<double>& u, std::vector<double> const& v ) {
    assert( u.size() == v.size() );
    for ( std::size_t i = 0; i < u.size(); ++i ) {
        u[i] += v[i];
    }
    return u;// u est retourné par référence
}
...
vector<double> u1, u2;
...
u1 += u2;// La référence retournée ne sert à rien ici (mais pas de coût)
auto& res = (u1 += u2);// Ici pas de copie, res fait référence à la valeur possédée par u1
auto res2 = (u1 += u2);// Ici on fait une copie, res2 est une autre variable qui possède une autre valeur que u1
```

## Paramètres nommés

Nous avons déjà vu qu'en C++ 20, il est possible d'initialiser une structure en nommant certains paramètres de la structure.

On peut utiliser cette propriété pour les fonctions en indiquant un nom aux paramètres. C'est d'ailleurs l'approche que fait Vulkan dans son API par exemple.

Exemple pour écrire une fonction axpy (blas 1) :

```cpp
/**
 * @brief Paramètres de la fonction axpy
 */
struct AxpyParameters {
    double alpha{1};// Coefficient alpha
    std::size_t n{0};// Nombre d'éléments à traiter
    std::vector<double>& x;// Tableau x. Vu que c'est une référence, il faudra initialiser x obligatoirement
    int incx{1}; // Incrément dans le tableau x
    int offset_x{0};// Offset dans le tableau x
    std::vector<double>& y;// Tableau y. Même remarque que pour x
    int incy{1};// Incrément dans le tableau y
    int offset_y{0};// Offset dans le tableau y
};
//
/**
 * @brief Fonction axpy
 * @param[in] params Paramètres de la fonction
 */
void axpy( AxpyParameters const& params ) {
    assert( params.n > 0 );
    assert( params.x.size() >= (params.offset_x + (params.n - 1) * params.incx) );
    assert( params.y.size() >= (params.offset_y + (params.n - 1) * params.incy) );
    //
    for ( std::size_t i = 0; i < params.n; ++i ) {
        params.y[params.offset_y + i * params.incy] += params.alpha * params.x[params.offset_x + i * params.incx];
    }
}
...
std::vector<double> x, y;
...
axpy( { .alpha = 2.0, .n = x.size(), .x = x, .y = y } );// Attention à l'ordre des paramètres !
```

## Fonctions génériques en C++ 20

Devoir écrire une fonction plusieurs fois pour différents types de données est pénible et source d'erreurs.

Depuis C++ 20, on peut déclarer les paramètres avec le type `auto` ce qui permet de définir des fonctions génériques. C'est à l'appel que le type sera déduit.

Il est également possible grâce aux concepts de définir des contraintes sur les types des paramètres (par exemple que ce soit un scalaire ou un tableau), mais cela ne sera pas abordé dans ce cours.

Exemple de fonction générique :

```cpp
// Fonction générique effectuant l'opération y = alpha * x + y
void axpy( auto alpha, auto const& x, auto& y ) {
    for ( std::size_t i = 0; i < x.size(); ++i ) {
        y[i] += alpha * x[i];
    }
}
...
std::array fx = { 1.f, 2.f, 3.f, 4.f };
std::array fy = { 0.f, -1.f, -2.f, -3.f };
axpy( 2.f, fx, fy ); // Appel de axpy avec des std::array contenant des floats
std::vector dx = { 1.0, 2.0, 3.0, 4.0 };
std::vector dy = { 0.0, -1.0, -2.0, -3.0 };
axpy( 2.0, dx, dy ); // Appel de axpy avec des std::vector contenant des doubles
...
axpy( 2.f, 1.f, -3.f );// Erreur de compilation car les floats ne permettent pas d'être indexés.
```

## Les fonctions constexpr

Les fonctions constexpr sont des fonctions qui peuvent être évaluées à la compilation. Elles sont très utiles pour initialiser des constantes élaborées.

Pour être appelées à la compilation, les valeurs passées à ces fonctions doivent être connues à la compilation (macros ou constexpr) ainsi que la variable recevant la valeur de retour. Dans le cas contraire, elles seront évaluées à l'exécution comme toutes les autres fonctions.

A partir de C++ 26 (à venir), il est prévu que toutes les fonctions mathématiques de `<cmath>` soient constexpr. Néanmoins, des compilateurs comme GCC supportent déjà cette fonctionnalité.

Exemple :

```cpp
constexpr double cteExp(int n)
{
    if (n == 0) {
        return 1.0;
    }
    if (n%2 == 0) {
        double v = cteExp(n/2);
        return v * v;
    }
    return cteExp(n-1) * std::numbers::e;
}
...
constexpr double e2 = cteExp(2);// Evalué à la compilation
double e2_bis = cteExp(2);// Evalué à l'exécution
double x = 3.0;
double e3 = cteExp(x);// Evalué à l'exécution
```

Néanmoins, on aimerait que la mise en oeuvre d"une fonction soit différente si elle est évaluée à la compilation ou à l'exécution. Pour cela, on peut utiliser la syntaxe `if consteval` introduite en C++ 23.

**Syntaxe** : `if consteval { ... partie évaluée à la compilation } else { ... partie évaluée à l'exécution }`

Exemple de l'exponentielle vue précédemment avec `if consteval` :

```cpp
constexpr double cteExp(int n) {
    if consteval {
        if (n == 0) {
            return 1.0;
        }
        if (n%2 == 0) {
            double v = cteExp(n/2);
            return v * v;
        }
        return cteExp(n-1) * std::numbers::e;
    } 
    else 
    {
        return std::exp(n);
    }
}
...
constexpr double e2 = cteExp(2);// Evalué à la compilation avec appel récursif
double e2_bis = cteExp(2);// Evalué à l'exécution avec appel à std::exp
double x = 3.0; 
double e3 = cteExp(x);// Evalué à l'exécution avec appel à std::exp
```

Il arrive également qu'on ne souhaite pas qu'une fonction constexpr puisse être évaluée à l'exécution. Pour cela, on peut utiliser le mot clé `consteval` qui interdit toute évaluation à l'exécution.

En revenant sur l'exemple de l'exponentielle, on peut écrire :

```cpp
consteval double cteExp(int n) {
    if (n == 0) {
        return 1.0;
    }
    if (n%2 == 0) {
        double v = cteExp(n/2);
        return v * v;
    }
    return cteExp(n-1) * std::numbers::e;
}
...
constexpr double e2 = cteExp(2);// Evalué à la compilation
double e2_bis = cteExp(2);// Erreur de compilation
```

## Les fonctions lambda

Les fonctions lambda sont un concept puissant introduit en C++11 qui permet de créer des fonctions anonymes directement à l'endroit où elles sont utilisées. Elles offrent une syntaxe concise pour définir des fonctions locales, ce qui les rend particulièrement utiles dans certaines situations.

L'intérêt principal des fonctions lambda réside dans leur capacité à :

1. Simplifier le code : Elles permettent de définir des fonctions courtes et simples sans avoir à les déclarer séparément.

2. Améliorer la lisibilité : En plaçant la logique directement là où elle est utilisée, le code devient souvent plus facile à comprendre.

3. Capturer le contexte : Les lambdas peuvent accéder aux variables de leur environnement, ce qui les rend très flexibles.

4. Faciliter la programmation fonctionnelle : Elles sont idéales pour être utilisées avec des algorithmes de la bibliothèque standard qui prennent des fonctions en paramètres.

**Syntaxe** : `[ capturer ] ( paramètres ) -> type_de_retour { corps }`

Comme pour le C++ 20, à partir du C++ 14, il est possible de déclarer les paramètres avec le type `auto` :

```cpp
double eval_polynome( double x ) { return 3*x*x*x - 4*x*x + x - 5; }
...
// Fonction lambda retournant une autre fonction lambda définissant la composition de deux fonctions
auto compose = []( auto f, auto g ) { return [f, g]( auto x ) { return f(g(x)); }; };
//
auto f = compose(eval_polynome, cos);
double x = std::numbers::pi;
std::cout << "f(pi) = " << f(x) << std::endl;
```

Voici un exemple simple pour illustrer l'utilisation d'une fonction lambda avec un service de tri de la bibliothèque standard :

```cpp
std::vector<std::array<double, 10>> tab_of_arrays;
...
// Trie les tableaux de 10 éléments selon leur norme euclidienne
std::sort( tab_of_arrays.begin(), tab_of_arrays.end(), 
    []( auto const& a, auto const& b ) 
    { 
        double sq_norm_a = 0, sq_norm_b = 0;
        for ( std::size_t i = 0; i < a.size(); ++i ) {
            sq_norm_a += a[i] * a[i];
            sq_norm_b += b[i] * b[i];
        }
        return sq_norm_a < sq_norm_b;
    } );
```

### La capture

La capture est un mécanisme puissant des fonctions lambda en C++ qui permet d'accéder aux variables de l'environnement extérieur à la lambda. Elle offre une grande flexibilité dans la manière dont ces variables sont accessibles à l'intérieur de la fonction lambda.

Il existe plusieurs façons de capturer des variables :

1. Capture par valeur `[x]` : Une copie de la variable est créée et utilisée dans la lambda.
2. Capture par référence `[&x]` : La variable originale est utilisée directement dans la lambda.
3. Capture implicite par valeur `[=]` : Toutes les variables utilisées sont capturées par valeur.
4. Capture implicite par référence `[&]` : Toutes les variables utilisées sont capturées par référence.
5. Capture mixte `[x, &y]` : Certaines variables sont capturées par valeur, d'autres par référence.

Voici un exemple illustrant ces différents types de capture :

```cpp
int x = 42, y = 24;
auto lambda1 = [x]() { return x; };// Capture par valeur
auto lambda2 = [&x]() { return x; };// Capture par référence
auto lambda3 = [=]() { return x+y; };// Capture implicite par valeur
auto lambda4 = [&]() { return x+y; };// Capture implicite par référence
auto lambda5 = [x, &y]() { return x+y; };// Capture mixte
auto lambda6 = [&, x]() { return x+y; };// Capture implicite par référence hormis x
```

Une lambda possède son propre type. Pour stocker une lambda dans une variable, il faut donc déclarer un type implicite à l'aide du mot clé `auto`.

Exemple d'utilisation d'une lambda fonction avec une capture par référence en reprenant l'exemple de la norme maximale d'un tableau de vecteurs :

```cpp
double max_norm = 0.;
std::vector<std::array<double, 10>> tab_of_arrays;
...
// Trie les tableaux de 10 éléments selon leur norme euclidienne et conserve la norme maximale
std::sort( tab_of_arrays.begin(), tab_of_arrays.end(), 
    [&max_norm]( auto const& a, auto const& b ) 
    { 
        double sq_norm_a = 0, sq_norm_b = 0;
        for ( std::size_t i = 0; i < a.size(); ++i ) {
            sq_norm_a += a[i] * a[i];
            sq_norm_b += b[i] * b[i];
        }
        max_norm = std::max( { max_norm, sq_norm_a, sq_norm_b } );
        return sq_norm_a < sq_norm_b;
    } );
```

