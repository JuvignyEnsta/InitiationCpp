# Programmation générique et templates

## Introduction

La programmation générique est un paradigme de programmation qui permet d'écrire du code flexible et réutilisable, capable de fonctionner avec différents types de données sans avoir à être réécrit pour chaque type spécifique. Cette approche vise à créer des algorithmes et des structures de données qui sont indépendants des types qu'ils manipulent.

**Historique** :

- Les concepts de la programmation générique ont émergé dans les années 1970, avec les travaux de David Musser et Alexander Stepanov sur les algorithmes génériques.
- En 1979, Ada devient le premier langage largement utilisé à supporter la programmation générique avec ses "génériques".
- C++ introduit les templates en 1990, marquant un tournant majeur dans l'adoption de la programmation générique.
- Java ajoute le support des génériques en 2004 avec Java 5.
- D'autres langages comme C#, Rust, et Swift ont depuis intégré des fonctionnalités de programmation générique.

*L'intérêt de la programmation générique est multiple* :

1. Réutilisabilité du code : Un seul algorithme peut être utilisé pour différents types de données, réduisant la duplication de code.

2. Sûreté de type : Les erreurs de type sont détectées à la compilation plutôt qu'à l'exécution, améliorant la robustesse du code.

3. Performance : Le code générique peut être optimisé par le compilateur pour chaque type spécifique, offrant des performances similaires au code écrit manuellement pour chaque type.

4. Abstraction : Elle permet de se concentrer sur la logique de l'algorithme plutôt que sur les détails spécifiques à un type.

5. Facilité de maintenance : Moins de code signifie moins de bugs potentiels et une maintenance plus aisée.

6. Expressivité : Elle permet d'exprimer des concepts complexes de manière claire et concise.

En C++, la programmation générique est principalement réalisée à travers l'utilisation de templates, qui permettent de définir des fonctions et des classes paramétrées par des types. Cette approche a révolutionné la façon dont les bibliothèques sont conçues et implémentées, notamment avec la Standard Template Library (STL).

La programmation générique continue d'évoluer, avec des concepts comme les concepts en C++20, qui permettent de spécifier plus précisément les contraintes sur les types génériques, améliorant ainsi la lisibilité du code et la qualité des messages d'erreur.

Exemples de généricité :

- Ecrire une fonction de tri sur une collection d'objets comparables à l'aide d'une fonction de comparaison dont l'accés peut se faire aléatoirement
- Ecrire une fonction qui retourne le plus grand élément d'une collection d'objets comparables

## La généricité en C++

Il conviendra de distinguer deux types de généricité :

- La généricité fonctionnelle qui permet de définir des fonctions génériques qui peuvent fonctionner avec différents types de données.
- La généricité de type qui permet de définir des classes et des structures génériques qui peuvent fonctionner avec différents types de données.

### Généricité fonctionnelle

La généricité fonctionnelle permet de définir des fonctions génériques qui peuvent fonctionner avec différents types de données.

Avant le C++, en C, on pouvait définir des fonctions génériques à l'aide de macros. Une macro est une portion de code qui est remplacée par le préprocesseur avant la compilation. Une macro peut prendre des arguments, qui sont remplacés par des valeurs ou des expressions lors de l'expansion de la macro à l'appel de cette dernière.

Par exemple :

```c
#define MAX(a, b) ((a) > (b) ? (a) : (b))
...
c = MAX(1, 3.5);// MAX(1, 3.5) est remplacé par ((1) > (3.5) ? (1) : (3.5))
```

Cependant les macros sont sources de nombreux bogues difficiles parfois à trouver. Par exemple, que penser de la ligne de code suivant :

```c
int i = 1, j = 3;
int c = MAX(i++, j);// i vaut 3 et c vaut 3 à la fin de ce fragment de code
```

Pour la généricité, la solution la plus général est d'utiliser un langage à balise ou un DSL (Domain Specific Language), mais cela va au delà du cadre de ce cours et ne concerne pas spécifiquement le langage C++.

En C++, on peut définir des fonctions génériques à l'aide de patrons (templates).

Le mot clef utilisé est `template` suivi d'un chevron ouvrant `<`, d'une liste de paramètres templates, d'un chevron fermant `>` puis de la déclaration de la fonction et de son corps.

Les paramètres templates contiennent soit des paramètres servant de types, soit des types scalaires servant de valeurs pour la généricité.

Exemple :

```cpp
template <typename T>
T max(T a, T b) {
    return a > b ? a : b;
}
```

Dans l'exemple ci-dessus, le paramètre template `T` est un type générique qui peut être utilisé pour n'importe quel type de données.

On peut utiliser cette fonction de la manière suivante :

```cpp
int a = 1, b = 2;
int c = max(a, b);// Appel max<int>(a,b) et c vaut 2
double d = max(1.5, 2.5);// Appel max<double>(1.5,2.5) et d vaut 2.5
```

On peut également utiliser des paramètres templates pour des types scalaires :

```cpp
template <int N>
int power(int x) {
    int result = 1;
    for (int i = 0; i < N; i++) {
        result *= x;
    }
    return result;
}
...
int a = 2;
int b = power<3>(a);// Appel power<3>(2) et b vaut 8
```

L'intérêt d'écrire la fonction `power` de la manière ci-dessus est que le paramètre `N` est connu à la compilation et le compilateur peut donc optimiser le code contrairement au cas où le paramètre `N` serait passer comme un paramètre classique à la fonction.

Revenons sur l'exemple de la fonction `max` :

```cpp
template <typename T>
T max(T a, T b) {
    return a > b ? a : b;
}
...
auto c = max(1, 3.4);// ERREUR : aucune conversion implicite entre int et double n'est faite. Le C++ ne sait pas quel type générique utiliser !
```

On peut également spécifier le type générique à utiliser si on souhaite forcer le type générique à utiliser :

```cpp
auto c = max<double>(1, 3.4);// Appel max<double>(1,3.4) et c vaut 3.4
```

Mais pour plus de simplicité, on peut modifier la déclaration de la fonction comme suit :

```cpp
template <typename T1, typename T2>
auto max(const T1& a, const T2& b) {
    return a > b ? a : b;
}
...
auto c = max(1, 3.4);// Appel max<int, double>(1,3.4) et c vaut 3.4. 1 est promut en double dans l'opérateur ternaire
auto l = max('a', 'b');// Appel max<char, char>(a,b) et l vaut b
auto s = max("tintin", "milou");// Appel max<const char*, const char*>(a,b).
//s peut valoir "tintin" ou "milou" !!!! 
```

Bien que notre fonction max fonctionne pour divers types de données hétérogènes, un problème subsiste pour les chaînes de caractères. En effet, une simple comparaison avec l'opérateur > ne fait que comparer les adresses des chaines de caractères. La fonction renverra donc la chaine de caractères dont l'adresse est la plus grande.

Pour résoudre le problème de la fonction max pour les chaines de caractères, il est possible de spécialiser la fonction max pour les chaines de caractères :

```cpp
template <>
const char* max<const char*>(const char* a, const char* b) {
    return std::strcmp(a, b) > 0 ? a : b;
}
...
auto s = max("tintin", "milou");// s vaut "tintin" grâce à la spécialisation
```

Il est possible dans les paramètres template de mélanger des types et des valeurs. :

```cpp
template <typename T, int N>
T power(T x) {
    T result = 1;
    for (int i = 0; i < N; i++) {
        result *= x;
    }
    return result;
}
...
int a = 2;
int b = power<int, 3>(a);// Appel power<int, 3>(2) et b vaut 8
```

**Il existe beaucoup de subtilités quand on utilise les templates.**

Par exemple, considérons le code suivant :

```cpp
template <typename Iterator>
auto sum( Iterator const& it_begin, Iterator const& it_end ) 
{
    decltype(*it_begin) sum = 0;
    for (Iterator it = it_begin; it != it_end; ++it) 
    {
        sum += *it;
    }
    return sum;
}
...
std::vector<double> v = {1, 2, 3, 4, 5};
double s = sum(v.begin(), v.end());// ERREUR DE COMPILATION:
```

Le mot clef `decltype` est utilisé pour déterminer le type de l'expression comprise entre les parenthèses.

Le code précédent ne compile pas. Pourquoi ?

Il se trouve que l'expression `*it_begin` évalue le type retourné par cette expresion comme une référence sur un double. Ainsi, le type `decltype(*it_begin)` correspond à `double&`. Or, la variable `sum` est initialisée à zéro, ce qui est interdit de faire pour une référence (qui doit faire référence à une autre variable !).

Pour ce cas précis, la STL fournit des utilitaires permettant de résoudre ce problème.

```cpp
template <typename Iterator>
auto sum( Iterator const& it_begin, Iterator const& it_end ) 
{
    std::remove_reference_t<decltype(*it_begin)> sum = 0;
    for (Iterator it = it_begin; it != it_end; ++it) 
    {
        sum += *it;
    }
    return sum;
}
...
std::vector<double> v = {1, 2, 3, 4, 5};
double s = sum(v.begin(), v.end());// OK
```

Le mot clef `std::remove_reference_t` est utilisé pour supprimer le qualifiant de référence du type retourné par l'expression `*it_begin`. Ainsi, le type `std::remove_reference_t<decltype(*it_begin)>` correspond à `double`.

## Paramètre templates par défaut

Il est possible de définir des paramètres templates par défaut. Cela permet de ne spécifier un paramètre template que lorsque l'on souhaite une valeur différente de la valeur par défaut.

```cpp
/**
 * @brief Crée une base canonique de R^dim
 * @tparam T le type des composantes de la base
 * @tparam dim la dimension de l'espace
 * @return un tableau de dim vecteurs formant une base canonique de R^dim
 */
template<typename T, int dim = 3> auto create_canonical_base()
{
    std::vector<std::array<T, dim>> base; base.resize(dim);
    for (int i = 0; i < dim; ++i)
    {
        std::array<T, dim> vec;
        vec.fill(0);
        vec[i] = 1;
        base.push_back(vec);
    }
    return base;
}
...
auto base2D = create_canonical_base<double,2>();// base2D est un vecteur de 2 vecteurs de double formant une base canonique de R^2
auto base3D = create_canonical_base<double>();// base3D est un vecteur de 3 vecteurs de double formant une base canonique de R^3
```

**Remarque** : Dans l'exemple précédent, le C++ ne peut pas déduire la valeur des paramètres templates car la fonction n'admet aucun paramètre permettant de les déduire. On est donc obligé ici de spécifier les valeurs des paramètres templates.

## Cas du passage des fonctions lambda en paramètre d'une fonction

On a vu que les fonctions lambda possède chacun un type propre non accessible en dehors de leur portée. Il est donc impossible de les passer en paramètre à une fonction classique puisqu'on ne connaît pas a priori le type de la fonction lambda qui sera passé en paramètre.

On a vu qu'en C++ 20, cela peut se régler en déclarant le paramètre correspondant à la fonction lambda de type implicite `auto`.

Avant cela (et en C++ 20 également), on n'a pas le choix que de passer par un template. Par exemple :

```cpp
/**
 * @brief Crée un vecteur de taille dim dont les composantes sont calculées à l'aide de la fonction lambda eval_fct
 * @tparam EvalFctType le type de la fonction lambda
 * @param dim la taille du vecteur
 * @param eval_fct la fonction lambda
 * @return un vecteur de taille dim dont les composantes sont calculées à l'aide de la fonction lambda eval_fct
 * 
 * La fonction eval_fct doit avoir un paramètre de type int et retourner un type défini par le template EvalFctType
 */
template<typename EvalFctType> auto compute_vector(int dim, EvalFctType const& eval_fct)
{
    std::vector<eval_fct(0)> vec(dim);
    for (int i = 0; i < dim; ++i)
    {
        vec[i] = eval_fct(i);
    }
    return vec;
}
...
auto vec = compute_vector(10, [](int i) { return i * 2; });
```

**Remarque** : On a déclaré le paramètre template `EvalFctType` de type `const&` pour éviter de copier la fonction lambda. En effet, les fonctions lambda sont des objets lourds qui peuvent être coûteux en termes de performance lors de la copie.

A l'aide de cette technique, on peut également passer des foncteurs (des objets possédant une fonction operator()) à la fonction `compute_vector`.

```cpp
template<typename EvalFctType> auto compute_vector(int dim, EvalFctType const& eval_fct)
{
    std::vector<eval_fct(0)> vec(dim);
    for (int i = 0; i < dim; ++i)
    {
        vec[i] = eval_fct(i);
    }
    return vec;
}
...
struct Kernel
{
    double k_wave; std::vector<double> radius;
    std::complex<double> operator()(int i) const
    {
        return std::polar(1./radius[i], k_wave*radius[i]);
    }
};
Kernel kernel{ 1.1, std::vector{1., 3., 5., 7.} };
auto vec = compute_vector(kernel.radius.size(), kernel);
```

## Retour sur les spécialisations templates

Si les paramètres templates ne portent que sur des types associés aux types des arguments passés à la fonction, on peut spécialiser le template sans spécifier le type spécifique. Exemple avec le produit scalaire optimisé avec le BLAS 1 pour les doubles :

```cpp
template<typename K> auto dot( std::vector<K> const& u, std::vector<K> const& v )
{
    assert(u.size() == v.size());
    K sum = 0;
    for (int i = 0; i < u.size(); ++i)
    {
        sum += u[i] * v[i];
    }
    return sum;
}
//
template<> auto dot<double>( std::vector<double> const& u, std::vector<double> const& v )
{
    assert(u.size() == v.size());
    return cblas_ddot(u.size(), u.data(), 1, v.data(), 1);
}
```

Lorsque les paramètres templates possèdent des valeurs scalaires, il faudra spécifier les valeurs et les types de la spécialisation template
pour la fonction.
Par exemple, considérons le code suivant :

```cpp
// Définition de la factorielle récursive
template<long n> constexpr **long fact() { return n * fact<n-1>(); }
template<> constexpr long fact<0>() { return 1L; }
...
// L'évaluation de la factorielle se fait à la compilation
std::cout << fact<10>() << std::endl;
```

---

**Remarque** : on n'a pas besoin de template pour que la factorielle soit évaluée à la compilation. On aurait pu l'écrire en constexpr avec une boucle classique.

```cpp
constexpr long fact(long n)
{
    long result = 1;
    for (long i = 2; i <= n; ++i) { result *= i; }
    return result;
}
```

---

Cette technique d'évaluation à la compilation à l'aide des templates peut se faire pour des algorithmes bien plus complexes et est souvent utilisé dans les bibliothèques de calcul numérique comme Eigen par exemple.

### Spécialisation partielle de templates

La spécialisation partielle de templates permet de spécialiser un template uniquement pour une partie de ses paramètres templates ou en spécialisant certains paramètres templates (sans pour autant en donner un type bien défini)

Par exemple, pour une spécialisation partielle du produit scalaire pour les complexes :

```cpp
template<typename K> auto dot( std::vector<K> const& u, std::vector<K> const& v )
{
    assert(u.size() == v.size());
    K sum = 0;
    for (int i = 0; i < u.size(); ++i)
    {
        sum += u[i] * v[i];
    }
    return sum;
}
// On spécialise partiellement la fonction dot pour le cas où K est un type complexe
template<typename K> auto dot<std::complex<K>>( std::vector<std::complex<K>> const& u, std::vector<std::complex<K>> const& v )
{
    assert(u.size() == v.size());
    std::complex<double> sum = 0;
    for (int i = 0; i < u.size(); ++i)
    {
        sum += std::conj(u[i]) * v[i];
    }
    return sum;
}
```

On peut également spécialiser partiellementun template pour un type donné :

