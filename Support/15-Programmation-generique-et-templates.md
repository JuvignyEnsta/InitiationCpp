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

##  La généricité en C++

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
template<typename K> auto 
dot( std::vector<std::complex<K>> const& u, std::vector<std::complex<K>> const& v )
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

On peut également spécialiser partiellement un template pour un type donné :

```cpp
template<typename K1, typename K2> auto 
prod(std::vector<K1> const& u, std::vector<K2> const& v) 
{
    std::vector<decltype(std::conj(u[0])*v[0])> res(u.size());
    for (std::size_t i=0; i<u.size(); ++i) res[i] = std::conj(u[i])*v[i];
    return res; 
}
template<typename K2> auto 
prod( std::vector<double> const& u, std::vector<K2> const& v )
{
    std::vector<decltype(K2(0)*1.)> res(u.size());
    for (std::size_t i=0; i<u.size(); ++i) res[i] = u[i]*v[i];
    return res; 
}
```

#### Règles sur les spécialisations partielles

Les spécialisations partielles permettent de spécialiser partiellement :

- une fonction  
- une expression constante
- une classe ou une structure (voir plus loin dans le cours)

Cette spécialisation peut se faire :

- Soit selon un paramètre de type
- Une valeur énumérable (entiers, etc.)

On ne peut pas :

- définir une valeur en fonction d'un autre paramètre template :

```c++
// Le code suivant ne compile pas !!!!
template<int I, int J> void f(...)
{
    ...
};
template<int I> void f<I,2*I>(...)// Erreur, dépendance entre les deux paramètres
{
    ...
}
```

- effectuer une spécialisation partielle sur une valeur en paramètre template si le type de cette valeur dépend d'un autre paramètre :

```c++
template<typename T, T value> void f(...)
{
    ...
}
template<typename T,1> void f(...)// Erreur de compilation
{
    ...
}
```

### Spécialisation et expressions constantes (constexpr)

Les expressions évaluées à la compilation (constexpr) peuvent également posséder des paramètres templates depuis le C++ 14. Cela permet ainsi de définir des valeurs qui seront associées
à des types génériques (par exemple pour les réels, la valeur max représentable, etc.) mais aussi pouvoir calculer des expressions constantes en utilisant des templates.

Par exemple, pour calculer des factorielles à la compilation, on peut, mais ce n'est pas obligatoire, utiliser les templates :

```c++
// Définition d'une factorielle par récursion :
template<typename Integer, long long n>
constexpr Integer factoriel = Integer(n) * factoriel<Integer,n-1>;

// Spécialisation template pour l'arrêt de la récursion :
template<typename Integer> constexpr Integer factoriel<Integer,0> = Integer(1);

...

std::cout << factoriel<double,20> << std::endl;
```

### Mécanisme général mis en oeuvre dans les compilateurs pour les spécialisation (SFINAE)

Le langage C++ est réputé pour sa puissance et sa flexibilité, notamment grâce à son système de templates qui permet la programmation générique. L'un des mécanismes clés qui rendent cette flexibilité possible est le SFINAE, acronyme de Substitution Failure Is Not An Error (l'échec de substitution n'est pas une erreur). Ce concept joue un rôle essentiel dans la surcharge de fonctions et la spécialisation des templates, permettant au compilateur de gérer élégamment les cas où une substitution de type échoue sans provoquer d'erreur de compilation.

####  Qu'est-ce que le SFINAE ?

Le SFINAE est une règle du langage C++ qui stipule que lors de l'instanciation de templates, si une substitution de type échoue, cette défaillance n'est pas considérée comme une erreur. Au lieu de cela, le compilateur exclut simplement cette instanciation particulière de la résolution de surcharge et continue à chercher d'autres correspondances possibles. Cela permet d'écrire du code plus générique et adaptable, en offrant des alternatives en fonction des types fournis.

####  Fonctionnement du SFINAE dans la surcharge des fonctions et des templates

Lorsqu'un programme utilise des fonctions surchargées ou des templates, le compilateur doit déterminer quelle version de la fonction appeler en fonction des arguments fournis. Le SFINAE intervient lorsque certaines surcharges ne sont pas applicables à cause d'échecs de substitution de types. Plutôt que de générer une erreur, le compilateur ignore ces surcharges non valides et continue sa recherche parmi les autres options disponibles.

**Exemple concret**

Considérons le code suivant pour illustrer le fonctionnement du SFINAE :

```cpp

#include <iostream>
#include <type_traits>

template <typename T>
typename std::enable_if<std::is_integral<T>::value>::type
func(T t) {
    std::cout << "Type intégral : " << t << std::endl;
}

template <typename T>
typename std::enable_if<std::is_floating_point<T>::value>::type
func(T t) {
    std::cout << "Type flottant : " << t << std::endl;
}

int main() {
    func(42);       // Appelle la version pour les types intégraux
    func(3.14);     // Appelle la version pour les types flottants
    // func("texte"); // Provoquerait une erreur si décommenté
    return 0;
}
```

Explication de l'exemple

- **Templates avec** `std::enable_if` : Les deux fonctions func sont différenciées par l'utilisation de std::enable_if, qui active ou désactive une fonction en fonction d'une condition évaluée à la compilation
- *Pour un type intégral* : `std::is_integral<T>::value` est vrai. La première fonction est instanciée (créée). La seconde fonction est ignorée car la condition dans `std::enable_if` échoue (la substitution échoue, mais ce n'est pas une erreur grâce au SFINAE).
- *Pour un type flottant* : `std::is_floating_point<T>::value` est vrai. La seconde fonction est instanciée. La première fonction est ignorée (de la même manière que la première fonction pour les entiers)
- *Pour une chaîne de caractères* : Les deux conditions échouent. Aucune fonction n'est viable. Le compilateur génère une erreur indiquant qu'il ne trouve pas de fonction correspondante.

#### Rôle du SFINAE dans les règles de spécialisation

Le SFINAE est essentiel pour créer des spécialisations de templates qui ne s'appliquent qu'à certains types, sans affecter les autres. Il permet d'écrire des fonctions ou des classes génériques qui peuvent avoir des comportements spécifiques en fonction des propriétés des types template.

Par exemple, on peut créer une fonction qui n'est disponible que pour les types supportant certaines opérations, comme l'addition ou la comparaison. Cela améliore la robustesse du code en empêchant les utilisations inappropriées et en fournissant des messages d'erreur plus clairs.

#### Comment le SFINAE gère les échecs de substitution sans erreur de compilation ?

Lors de la compilation, si une instanciation de template échoue à cause d'une substitution de type invalide, le SFINAE empêche cette erreur de provoquer l'échec de la compilation entière. Au lieu de cela, le compilateur exclut simplement cette instanciation de la résolution de surcharge. Cela signifie que le programmeur peut fournir plusieurs versions d'une fonction template, et le compilateur choisira celle qui correspond **le mieux** aux types des arguments, en ignorant silencieusement les autres.

#### Conclusion

Le SFINAE est un mécanisme puissant qui enrichit la programmation générique en C++. Il permet d'écrire du code flexible et adaptable, capable de gérer une variété de types tout en maintenant la sécurité et l'efficacité du code. En comprenant et en maîtrisant le SFINAE, les développeurs peuvent exploiter pleinement les capacités des templates et des surcharges de fonctions, créant ainsi des bibliothèques et des applications plus robustes et modulaires.

## Généricité structurelle

De la même manière que pour les fonctions, il est possible de définir des structures, des classes ou des unions qui dépendront de paramètres templates. **Syntaxe** :

```cpp
template<paramètres templates> class|union|struct;
```

**Tous** les attributs, méthodes, structures ,... définies au sein d'une classe (ou structure) template peuvent être déclarées et définies en utilisant les paramètres templates liées à la classe.

Les **constructeurs** seront déclarées et définies en portant le nom de la classe, mais *sans les paramètres templates*.

La définition des méthodes et des constructeurs peuvent être soit définies dans la déclaration de la classe, soit en dehors. Les méthodes définies en dehors de la classe doivent rappeler la portée de la classe avec les paramètres templates :

```cpp
template<typename K> class A
{
    ...
    K une_methode( K const& un_parametre ) const;
    ...
};
...
template<typename K> K
A<K>::une_methode( K const& un_parametre ) const
{
    ...
}
```

Les chevrons `<` et `>` servent à spécifier que c'est la classe qui possède un paramètre template et non la méthode de la classe.

#### Instancier une classe template

Comme pour les fonctions templates, pour instancier un objet à partir de la classe template, il faut qu'on ait accès à toutes les déclarations et définitions des méthodes et de la classe elle-même.

En pratique, lorsqu'on écrit une classe template, dans un premier temps, toutes les déclarations et définitions des méthodes seront écrites dans un fichier d'entête (header).

Lors de l'instanciation de la classe template, il est nécessaire de préciser tous les paramètres templates qui ne n'ont pas de valeurs par défaut.

**Exemple de déclaration et de l'instanciation d'une classe template**

```cpp
// Déclaration Vecteur géométrique dans un espace à dim dimensions contenant des coefficients de type K
template<typename K, int dim> class Vecteur
{
public:
    Vecteur() = default;
    ...
private:
    std::array<K, dim> m_coefs;
};
...
Vecteur<double,3> u; // On instancie un vecteur de réels double précision en 3D
```

Deux instanciations ayant reçu des valeurs différentes pour paramètres templates sont de type différents. Ainsi,

```cpp
Vecteur<double,3> u1;
Vecteur<float ,3> u2;
Vecteur<double,2> u3;
```

sont tous de type différents, car ils ont des valeurs différentes pour les paramètres templates.

Lorsque, dans une méthode, on instancie un objet de même type que la classe template où est défini la méthode, il n'est pas obligatoire de passer des valeurs aux paramètres template. Dans ce cas, l'objet sera l'instance de la classe ayant les mêmes paramètres templates que la classe contenant la méthode.

Par exemple :

```cpp
template<typename K, int dim> class Vecteur 
{
public:
    ...
    Vecteur operator + ( Vecteur const& u );
    ...
};
...
template<typename K, int dim> auto
Vecteur<K,dim>::operator + ( Vecteur const& u ) -> Vecteur
{
    Vecteur res;
    ...
    return res;
}
```

L'opérateur `+` définit ci-dessus reçoit un vecteur de même type que l'objet ayant appelé cet opérateur, et retourne également un vecteur de même type. Lorsqu'on veut recevoir une instance de la classe mais avec des paramètres différents, il faut alors spécifier les paramètres.

#### Constructeurs et méthodes templates

Il est possible de définir des méthodes, opérateurs et constructeurs templates au sein d'une classe (qui n'est pas
obligatoirement elle-même template).

Seule restriction, il est interdit de définir des méthodes virtuelles templates (pour des raisons internes au traitement des méthodes virtuelles par les compilateurs C++).

Exemple de méthode template dans une classe non template :

```cpp
class Polynome
{
public:
    ...
    // Evalue le polynome en la valeur x (qui peut être un double, un complexe, une matrice carrée, etc.)
    template<typename K> auto operator() ( K const& x ) const;
private:
    std::vector<double> m_monome_coefs;
};
...
// Définition : notons que cette fonction doit aussi se retrouver dans le header...
template<typename K> auto
Polynome::operator() ( K const& x ) const
{
    ...
}
...
Matrix A(...);
Polynome P(...);
Matrix B = P(A);// Appel de l'opérateur ()
```

Exemple de méthode template dans une classe template :

```cpp
template<typename K> 
class Polynome
{
public:
    ...
    // Le paramètre de la méthode ne doit pas porter le même nom que le paramètre de la classe
    template<typename K2> auto operator() ( K2 const& x );
};
...
template<typename K> template<typename K1> auto
Polynome<K>::operator() ( K1 const& x )
{
    ...
}
...
Matrix A(...)
Polynome<int> P(...);
Matrix B = P(A);
```

## Fonctions et templates variadiques

###  Les fonctions variadiques en C

Les fonctions variadiques sont des fonctions capables d'accepter un nombre variable d'arguments. En langage C, elles permettent aux programmeurs de créer des fonctions flexibles qui peuvent traiter différents nombres et types d'arguments. Une utilisation courante des fonctions variadiques est la fonction standard printf, qui peut recevoir un format de chaîne suivi d'un nombre arbitraire de variables à afficher.

#### Qu'est-ce qu'une fonction variadique ?

Une fonction variadique est une fonction qui peut accepter un nombre indéfini d'arguments lors de son appel. Cela est particulièrement utile lorsque le nombre d'arguments nécessaires ne peut pas être déterminé à l'avance ou lorsque vous souhaitez fournir une interface plus flexible.

#### Comment fonctionnent les fonctions variadiques ?

Pour créer et utiliser des fonctions variadiques en C, il est nécessaire de comprendre quelques concepts clés :

- **Déclaration de la fonction variadique** : Elle inclut au moins un paramètre fixe, suivi de trois points de suspension `...` pour indiquer que des arguments supplémentaires peuvent être passés.
- **Utilisation de la bibliothèque `<stdarg.h>`** : Elle fournit les macros nécessaires pour manipuler les arguments variadiques.
- Macros principales :
  - `va_list` : Type de variable utilisé pour gérer les arguments variadiques.
  - `va_start` : Initialise la variable de type va_list pour parcourir les arguments.
  - `va_arg` : Récupère l'argument courant et passe au suivant.
  - `va_end` : Termine le parcours des arguments variadiques.

#### Exemple concret

**But** : Créer une fonction `somme()` qui calcule la somme d'un nombre variable d'entiers.

```c
#include <stdio.h>
#include <stdarg.h>

// Déclaration et définition de la fonction variadique
int somme(int num_args, ...) {
    int total = 0;
    va_list args;

    // Initialisation de la liste d'arguments
    va_start(args, num_args);

    // Parcours des arguments
    for (int i = 0; i < num_args; i++) {
        int valeur = va_arg(args, int);
        total += valeur;
    }

    // Nettoyage
    va_end(args);

    return total;
}

int main() {
    int resultat1 = somme(3, 10, 20, 30);
    int resultat2 = somme(5, 1, 2, 3, 4, 5);

    printf("La première somme est : %d\n", resultat1);
    printf("La deuxième somme est : %d\n", resultat2);

    return 0;
}
```

*Explication de l'exemple* :

- `int somme(int num_args, ...)` : La fonction somme est déclarée avec un paramètre fixe num_args qui indique le nombre d'arguments entiers qui suivront.
- `va_list args;` : Déclare une variable args pour accéder aux arguments variadiques.
- `va_start(args, num_args);` : Initialise args pour parcourir les arguments, en partant du paramètre juste avant `...`, ici num_args.
- Boucle for : Utilise va_arg(args, int) pour accéder successivement à chaque argument de type int.
- `va_end(args);` : Libère les ressources associées à args.

#### Dans quels cas les fonctions variadiques sont-elles utiles ?

- **Fonctions de formatage** : Comme `printf` et `scanf`, qui doivent gérer un nombre variable d'arguments en fonction d'une chaîne de formatage.
- **Fonctions utilitaires** : Pour la journalisation, le débogage ou la création de messages d'erreur personnalisés.
- **API flexibles** : Lorsqu'une fonction doit accepter différents types ou nombres d'arguments pour offrir une interface utilisateur plus souple.

#### Précautions à prendre lors de l'utilisation des fonctions variadiques

1. **Gestion des types d'arguments**
    - *Pas de vérification de type automatique* : Le compilateur ne peut pas vérifier les types des arguments variadiques, ce qui peut conduire à des erreurs si les types attendus ne correspondent pas aux types passés.
    - *Utilisation cohérente des types* : Il est crucial de s'assurer que les arguments passés sont du type attendu lors de l'extraction avec `va_arg`.

2. **Sécurité et fiabilité**
    - *Risques de dépassement de tampon* : Une mauvaise gestion des arguments peut entraîner des vulnérabilités de sécurité, notamment des dépassements de tampon.
    - *Comportement indéfini* : Accéder à plus d'arguments que ceux réellement passés ou utiliser un type incorrect avec `va_arg` peut provoquer un comportement imprévisible du programme.

3. **Performance**
    - *Surcharge du processeur* : Les fonctions variadiques peuvent être moins performantes en raison du surcoût lié à la manipulation des arguments variables.

4. **Lisibilité du code**
    - *Complexité accrue* : Le code peut devenir plus difficile à lire et à maintenir, surtout si la fonction variadique est complexe.

#### Bonnes pratiques pour l'utilisation des fonctions variadiques

- *Inclure un paramètre de comptage* : Toujours avoir un argument qui spécifie le nombre d'arguments variadiques, comme `num_args` dans l'exemple.
- *Utiliser une chaîne de formatage* : Comme dans `printf`, qui indique non seulement le nombre mais aussi le type des arguments attendus.
- *Validation des arguments* : Mettre en place des mécanismes pour vérifier la validité des arguments avant de les utiliser.
- *Documentation claire* : Documenter soigneusement la fonction pour que les utilisateurs sachent exactement comment l'appeler correctement.

#### Autre exemple : Fonction de journalisation personnalisée

**But** : Créer une fonction `log_message()` qui enregistre des messages avec un niveau de gravité variable.

```c
#include <stdio.h>
#include <stdarg.h>

void log_message(const char *niveau, const char *format, ...) 
{
    va_list args;
    va_start(args, format);

    printf("[%s] ", niveau);
    vprintf(format, args);
    printf("\n");

    va_end(args);
}

int main() 
{
    log_message("INFO", "Démarrage du programme %s", "MonProgramme");
    log_message("AVERTISSEMENT", "Mémoire faible : %d%% utilisée", 85);
    log_message("ERREUR", "Impossible d'ouvrir le fichier %s", "data.txt");

    return 0;
}
```

**Explication de l'exemple** :

- `void log_message(const char *niveau, const char *format, ...)` : La fonction accepte un niveau de message, une chaîne de formatage et des arguments variadiques pour le contenu du message.
- `vprintf(format, args);` : Utilise `vprintf` pour afficher la chaîne formatée avec les arguments variadiques.

    Appels de la fonction : Différents niveaux de messages sont enregistrés avec des informations variées.

#### Risques potentiels et solutions

1. **Incohérence des types**
    - *Risque* : Si le type d'argument passé ne correspond pas au type attendu, le programme peut planter ou produire des résultats incorrects.

    - *Solution* : Utiliser des chaînes de formatage explicites et vérifier soigneusement les types lors de l'appel de la fonction.
1. **Arguments manquants ou excessifs**
    - *Risque* : Fournir trop ou pas assez d'arguments peut entraîner un comportement indéfini.
    - *Solution* : Inclure un mécanisme de comptage des arguments ou utiliser des sentinelles (valeurs spéciales indiquant la fin des arguments).

**Exemple avec sentinelle** :

```c
#include <stdio.h>
#include <stdarg.h>

void afficher_nombres(int premier, ...) {
    va_list args;
    va_start(args, premier);

    int nombre = premier;
    while (nombre != -1) { // -1 est la sentinelle
        printf("%d ", nombre);
        nombre = va_arg(args, int);
    }

    va_end(args);
    printf("\n");
}

int main() {
    afficher_nombres(10, 20, 30, 40, -1);
    return 0;
}
```

#### Alternatives aux fonctions variadiques

- **Listes ou tableaux** : Passer un pointeur vers un tableau ou une liste contenant les arguments.
- **Structures** : Regrouper les arguments dans une structure pour une meilleure gestion des types.
- **Macros variadiques (C99 et plus)** : Utiliser des macros qui acceptent un nombre variable d'arguments pour des cas spécifiques.

#### Conclusion sur les fonctions variadiques en C

Les fonctions variadiques en langage C sont un outil puissant pour créer des fonctions flexibles et polyvalentes. Elles permettent de gérer des situations où le nombre et le type d'arguments peuvent varier. Cependant, elles nécessitent une manipulation soigneuse pour éviter les erreurs de type, les fuites de mémoire et les problèmes de sécurité. En suivant les bonnes pratiques et en étant conscient des risques potentiels, les programmeurs peuvent tirer pleinement parti des fonctions variadiques pour créer des programmes efficaces et robustes.

#### Résumé des points clés

- **Déclaration avec `...`** : Indique que la fonction accepte des arguments variadiques.
- **Utilisation de `<stdarg.h>`** : Fournit les outils nécessaires pour manipuler les arguments.
- **Macros essentielles** :
  - `va_list` : Pour déclarer une variable de liste d'arguments.
  - `va_start` : Pour initialiser la liste d'arguments.
  - `va_arg` : Pour accéder à chaque argument.
  - `va_end` : Pour nettoyer la liste d'arguments.
- **Précautions** : Toujours vérifier les types et le nombre d'arguments pour éviter les comportements indéfinis.

En maîtrisant les fonctions variadiques, vous pouvez améliorer la flexibilité et la convivialité de vos programmes en C, tout en maintenant un code sûr et fiable.

## Initiation aux templates variadiques en C++

Les templates variadiques, introduits avec le standard C++11, sont une extension puissante du système de templates en C++. Ils permettent de créer des fonctions (et des classes) capables d'accepter un nombre variable de paramètres de types différents, tout en bénéficiant de la vérification de type à la compilation. Cette fonctionnalité surpasse les limitations des fonctions variadiques traditionnelles en C, offrant ainsi plus de sécurité et de flexibilité.

### Avantages des templates variadiques en C++ par rapport aux fonctions variadiques en C

Les templates variadiques en C++ surmontent les limitations des fonctions variadiques en C en offrant :

- **Vérification de type à la compilation** : Le compilateur connaît les types de tous les arguments, ce qui permet de détecter les erreurs de type avant l'exécution.
- **Flexibilité accrue** : Possibilité de travailler avec un nombre variable de paramètres de types différents sans sacrifier la sécurité.
- **Lisibilité et maintenabilité** : Un code plus clair et plus facile à maintenir grâce à l'utilisation de concepts de haut niveau.

### Paquets de paramètres templates et paquets d'arguments

#### Paquets de paramètres templates (template parameter packs)

Un paquet de paramètres templates est une façon de déclarer un nombre variable de paramètres templates. Il est déclaré en utilisant l'opérateur ```...``` après le nom du paramètre.

**Syntaxe** :

```c++
template<typename... Types>
```

Ici, `Types` est un paquet de paramètres templates qui peut contenir zéro ou plusieurs types.

#### Paquets d'arguments (argument packs)

Un paquet d'arguments est une collection d'arguments correspondant aux paramètres templates du paquet. Lors de l'appel de la fonction ou de l'instanciation du template, les arguments fournis forment le paquet d'arguments.

**Exemple** :

```c++
template<typename... Types>
void fonction(Types... args) 
{
    // Corps de la fonction
}
```

- ```Types...``` est le paquet de paramètres templates.
- ```args...``` est le paquet d'arguments correspondant aux valeurs passées à la fonction.

Le compilateur, lors de l'appel de la fonction, initialisera `Types` avec les types des
divers arguments passés lors de l'appel (dans l'ordre de passage de gauche à droite des
paramètres) et initialisera `args` avec les divers valeurs passées à la fonction.

**Exemple** :

```c++
fonction('a', 3.5, 2); // Types = [char, double, int], args = ['a', 3.5, 2]
fonction(); // Types = [], args = ()
fonction(1); // Types = [int], args = (1)
```

#### Déploiement des paramètres variadiques dans une fonction

Nous avons vu jusqu'ici comment déclarer une fonction utilisant des templates variadiques.
Lors de la mise en oeuvre de la fonction, on devra "déployer" les différentes valeurs
contenues dans le paquet d'arguments.

Il existe plusieurs méthodes pour déployer et manipuler les paramètres variadiques dans une fonction en C++.

1. **Récursion sur les templates**
    C'est la méthode la plus classique.
    Elle consiste à définir une fonction template qui traite un argument et appelle récursivement elle-même avec le reste des arguments jusqu'à ce qu'il n'y ait plus d'arguments.
    *Exemple* :

    ```c++
    # include <iostream>

    // Cas de base : aucun argument
    void afficher() 
    {
        std::cout << "Fin de la liste." << std::endl;
    }

    // Fonction template variadique
    template<typename T, typename... Reste>
    void afficher(T premier, Reste... reste) 
    {
        std::cout << premier << " ";
        afficher(reste...); // Appel récursif avec le reste des arguments
    }

    int main() 
    {
        afficher(1, 2.5, "texte", 'c');
        return 0;
    }
    ```

    **Explication** :

    - **Cas de base** : La fonction afficher() sans arguments termine la récursion.
    - **Appel récursif** : La fonction ```afficher(T premier, Reste... reste)``` affiche le premier argument `premier` de type `T` puis s'appelle récursivement avec les arguments restants contenus dans ```reste```

2. **Expansion de pack avec l'initialisation de liste**
    Cette méthode utilise l'expansion de paquet dans le contexte d'une initialisation de liste pour appliquer une opération à chaque argument du paquet.

    *Exemple* :

    ```c++
    # include <iostream>

    template<typename... Args>
    void afficher(Args... args) 
    {
        // L'expression '(std::cout << args << " ", 0)' est évaluée pour chaque 'args'
        std::initializer_list<int>{ (std::cout << args << " ", 0)... };
        std::cout << std::endl;
    }

    int main() 
    {
        afficher(1, 2.5, "texte", 'c');
        return 0;
    }
    ```

    **Explication** :

    - **Expansion du paquet** : L'expression `(expression(args))...` déploie le paquet d'arguments comme `expression(arg1),expression(arg2),..., expression(argn)`.
    - **Liste d'initialisation** : Utilisée uniquement pour exécuter une expression pour chaque élément du paquet.

### Fold expressions (à partir de C++17)

#### Introduction sur les fold expressions

Avec l'arrivée de C++17, les fold expressions ont été introduites pour simplifier et rendre plus lisible le traitement des paramètres variadiques dans les templates. Elles permettent d'appliquer une opération binaire sur tous les éléments d'un paquet de paramètres (parameter pack), éliminant ainsi la nécessité d'écrire du code récursif ou d'utiliser des techniques complexes pour déployer ces paramètres.

#### Qu'est-ce qu'une fold expression ?

Une fold expression est une expression qui permet d'appliquer une opération binaire (comme +, *, &&, ||, etc.) sur tous les éléments d'un paquet de paramètres variadiques. Elle "plie" le paquet de paramètres en une seule valeur en appliquant l'opération spécifiée.

#### Syntaxe des fold expressions

Il existe quatre formes de fold expressions :

- **Unary Left Fold (plis unaires à gauche)**
    Syntaxe : ```( ... op pack )```
- **Unary Right Fold (plis unaires à droite)**
    Syntaxe : ```( pack op ... )```
- **Binary Left Fold (plis binaires à gauche) avec une valeur initiale**
    Syntaxe : ```( init op ... op pack )```
- **Binary Right Fold (plis binaires à droite) avec une valeur initiale**
    Syntaxe : ```( pack op ... op init )```

où

- `op` représente l'opérateur binaire utilisé.
- `pack` est le paquet de paramètres variadiques.
- `init` est une valeur initiale utilisée dans les plis binaires.

#### Détails des différentes formes de fold expressions

1. **Unary Left Fold**
    Applique l'opérateur de gauche à droite.

    **Syntaxe** :

    ```c++
    ( ... op pack )
    ```

    **Expansion** :

    Pour un paquet pack contenant les éléments `e1, e2, e3, ..., en`, l'expression se déploie en :

    ```c++
    ((...((e1 op e2) op e3) op ...) op en)
    ```

    **Exemple** :

    ```c++
    template<typename... Args>
    auto sum(Args... args) 
    {
        return (... + args); // Unary Left Fold
    }
    ...
    int main()
    {
        sum(1.3,2.3,4.3); // Déploie dans la fonction en : (1.3+2.3)+4.3
        ...
    }
    ```

2. **Unary Right Fold**
    Applique l'opérateur de droite à gauche.

    **Syntaxe** :

    ```c++
    ( pack op ... )
    ```

    **Expansion** :
    Déployé en :

    ```c++
    (e1 op (e2 op (... op en)))
    ```

    Exemple :

    ```c++
    template<typename... Args>
    auto diff(Args... args) 
    {
        return (args - ...); // Unary Right Fold
    }
    ...
    int main()
    {
        diff(1.3,2.3,4.3); // Déploie dans la fonction en : 1.3 - (2.3-4.3)
        ...
    }
    ```

3. **Binary Left Fold**
    Inclut une valeur initiale et applique l'opérateur de gauche à droite.

    **Syntaxe** :

    ```c++
    ( init op ... op pack )
    ```

    **Expansion** :

    ```c++
    (((init op e1) op e2) op ...) op en
    ```

    **Exemple** :

    ```c++
    template<typename... Args>
    auto sum_with_init(int init, Args... args) 
    {
        return (init + ... + args); // Binary Left Fold
    }
    ...
    int main()
    {
        sum_with_init(-3., 1.,2.,3.,4.,5.); // Effectue le calcul ((((-3.+1.) + 2.) + 3.) + 4.) + 5.
        ...
    }
    ```

4. **Binary Right Fold**
    Inclut une valeur initiale et applique l'opérateur de droite à gauche.

    **Syntaxe** :

    ```c++
    ( pack op ... op init )
    ```

    **Expansion** :

    ```c++
    e1 op (e2 op (... op (en op init)))
    ```

    **Exemple** :

    ```c++
    template<typename... Args>
    auto append_strings(Args... args)
    {
        return (args + ... + std::string("\n")); // Binary Right Fold
    }
    ...
    int main()
    {
        // append_string déploie les arguments en : "tintin" + (" et " + ("milou" + "\n"))
        std::cout << append_string("tintin", " et ", "milou");
        ...
    }
    ```

#### Exemples concrets

1. **Somme de valeurs numériques**
    *Code* :

    ```c++
    #include <iostream>

    template<typename... Args>
    auto somme(Args... args) 
    {
        return (... + args); // Unary Left Fold
    }

    int main() 
    {
        auto result = somme(1, 2, 3, 4.5);
        std::cout << "La somme est : " << result << std::endl;
        return EXIT_SUCCESS;
    }
    ```

    **Explication** :

    - `somme(Args... args)` : Fonction template qui accepte un nombre variable d'arguments.
    - ```(... + args)``` : Applique l'opérateur + successivement à tous les arguments.
    - **Résultat** : Calcule la somme de tous les arguments passés.

2. **Calcul du produit**
    *Code* :

    ```c++
    #include <iostream>

    template<typename... Args>
    auto produit(Args... args) 
    {
        return (args * ...); // Unary Right Fold
    }

    int main() 
    {
        auto result = produit(2, 3, 4);
        std::cout << "Le produit est : " << result << std::endl;
        return 0;
    }
    ```

    **Explication** :

    ```(args * ...)``` : Multiplie les arguments de droite à gauche.

#### Cas particuliers et précautions

1. **Paquets vides**

    Si le paquet de paramètres est vide, le comportement dépend du type de fold expression utilisé.

    - **Unary Fold sans valeur initiale** : Provoque une erreur si le paquet est vide.
    - **Binary Fold avec valeur initiale** : Utilise simplement la valeur initiale.

2. **Opérateurs non associatifs**

    Lorsque vous utilisez des opérateurs non associatifs (comme la soustraction ou la division), le choix entre un pli à gauche et un pli à droite affecte le résultat.

    **Exemple avec la soustraction** :

    ```c++
    #include <iostream>

    template<typename... Args>
    auto soustraction_gauche(Args... args) 
    {
        return (... - args); // Unary Left Fold
    }

    template<typename... Args>
    auto soustraction_droite(Args... args) 
    {
        return (args - ...); // Unary Right Fold
    }

    int main() 
    {
        std::cout << "Pli gauche : " << soustraction_gauche(10, 3, 2) << std::endl; // ((10 - 3) - 2) = 5
        std::cout << "Pli droit : " << soustraction_droite(10, 3, 2) << std::endl;  // (10 - (3 - 2)) = 9
        return 0;
    }
    ```

    **Explication** :

    - **Pli gauche** : Applique l'opération de gauche à droite.
    - **Pli droit** : Applique l'opération de droite à gauche.
    - **Résultats différents** : En raison de la non-associativité de la soustraction.

#### Application pratique des fold expressions

- **Fusion de conteneurs**
    Ajouter plusieurs éléments à un conteneur depuis plusieurs sources.

    **Code** :

    ```c++
    #include <vector>

    template<typename Container, typename... Args>
    void ajouter_elements(Container& conteneur, Args... args) 
    {
        (conteneur.push_back(args), ...);
    }

    int main() 
    {
        std::vector<int> vec;
        ajouter_elements(vec, 1, 2, 3, 4);
        // vec contient maintenant 1, 2, 3, 4
        return 0;
    }
    ```

#### Avantages des fold expressions

- **Simplicité et lisibilité** : Le code est plus concis et facile à comprendre.
- **Élimination de la récursion** : Plus besoin d'écrire des fonctions récursives pour déployer les paquets de paramètres.
- **Performance** : Le compilateur peut optimiser les fold expressions plus efficacement.
- **Moins d'erreurs** : Réduction des risques liés aux techniques de métaprogrammation complexes.

#### Bonnes pratiques

- **Choix du type de pli** : Utiliser le pli gauche ou droit approprié en fonction de l'opérateur et du résultat attendu.
- **Gestion des paquets vides** : Prévoir le cas où le paquet de paramètres pourrait être vide, notamment en utilisant des valeurs initiales si nécessaire.
- **Attention aux opérateurs non associatifs** : Comprendre comment l'associativité affecte le résultat.
- **Utilisation d'opérateurs adaptés** : S'assurer que l'opérateur utilisé est compatible avec les types des arguments.

#### Limitations et considérations

- **Compatibilité du compilateur** : Les fold expressions nécessitent un compilateur supportant C++17 ou supérieur.
- **Complexité des expressions** : Bien que les fold expressions simplifient le code, des expressions trop complexes peuvent nuire à la lisibilité.
- **Erreurs de compilation peu explicites** : En cas d'erreur, les messages du compilateur peuvent être difficiles à interpréter.

#### Conclusion

Les fold expressions en C++17 représentent une avancée significative dans la manipulation des templates variadiques. Elles simplifient le code, améliorent la lisibilité et permettent d'écrire des fonctions génériques plus efficacement. En comprenant les différentes formes de fold expressions et en étant attentif aux détails tels que l'associativité des opérateurs et la gestion des paquets vides, les développeurs peuvent tirer pleinement parti de cette fonctionnalité puissante du langage C++.

Résumé des points clés :

- **Quatre formes de fold expressions** : Unary Left, Unary Right, Binary Left, Binary Right.
- **Syntaxe simple** : Utilisation de ... pour déployer le paquet de paramètres avec un opérateur binaire.
- **Avantages** : Code plus concis, élimination de la récursion, meilleure performance.
- **Applications** : Calculs arithmétiques, opérations logiques, manipulation de conteneurs, métaprogrammation.
- **Précautions** : Gestion des paquets vides, choix de l'opérateur et du type de pli, attention aux opérateurs non associatifs.

En intégrant les fold expressions dans vos programmes C++, vous pouvez écrire du code plus propre, plus efficace et plus moderne, tout en exploitant pleinement les capacités offertes par le standard C++17.

### Introduction aux templates variadiques pour les classes

Les templates variadiques pour les classes permettent de définir des types génériques capables de manipuler un nombre quelconque de types. Cela est particulièrement utile dans les situations suivantes :

- **Création de conteneurs hétérogènes** : Comme les tuples ou les variants, qui peuvent stocker des valeurs de différents types.
- **Méta-programmation** : Réaliser des calculs ou des transformations à la compilation en manipulant des types.
- **API génériques** : Fournir des interfaces flexibles acceptant divers types sans duplication de code.

#### Déclaration d'une classe template variadique

La syntaxe pour déclarer une classe ou une structure template variadique est la suivante :

```c++
template<typename... Types>
class MaClasse {
    // Corps de la classe
};
```

où

```typename... Types``` : Types est un paquet de paramètres templates (template parameter pack) qui peut contenir zéro ou plusieurs types.

#### Exemple : Implémentation d'un Tuple

Un tuple est un conteneur qui peut stocker un ensemble d'éléments de types différents. Le standard C++ fournit std::tuple, mais nous allons voir comment l'implémenter nous-mêmes pour comprendre le fonctionnement des templates variadiques.

1. **Implémentation simplifiée d'un Tuple**

    ```c++
    #include <iostream>

    // Cas de base : tuple vide
    template<>
    class Tuple<> {};

    // Cas général : tuple non vide
    template<typename Head, typename... Tail>
    class Tuple<Head, Tail...> : private Tuple<Tail...> 
    {
    public:
        Tuple(Head h, Tail... t) : Tuple<Tail...>(t...), head_(h) {}

        Head head_;
    };

    // Fonction pour accéder au N-ième élément
    template<size_t index, typename TupleType>
    struct TupleElement;

    // Spécialisation pour index = 0
    template<typename Head, typename... Tail>
    struct TupleElement<0, Tuple<Head, Tail...>> 
    {
        using Type = Head;

        static Type& get(Tuple<Head, Tail...>& tuple) 
        {
            return tuple.head_;
        }
    };

    // Spécialisation pour index > 0
    template<size_t index, typename Head, typename... Tail>
    struct TupleElement<index, Tuple<Head, Tail...>> 
    {
        using Type = typename TupleElement<index - 1, Tuple<Tail...>>::Type;

        static Type& get(Tuple<Head, Tail...>& tuple) 
        {
            return TupleElement<index - 1, Tuple<Tail...>>::get(static_cast<Tuple<Tail...>&>(tuple));
        }
    };

    // Fonction utilitaire pour simplifier l'accès
    template<size_t index, typename... Types>
    typename TupleElement<index, Tuple<Types...>>::Type& get(Tuple<Types...>& tuple) 
    {
        return TupleElement<index, Tuple<Types...>>::get(tuple);
    }

    int main() 
    {
        Tuple<int, double, std::string> monTuple(42, 3.14, "Hello");

        std::cout << "Premier élément : " << get<0>(monTuple) << std::endl;
        std::cout << "Deuxième élément : " << get<1>(monTuple) << std::endl;
        std::cout << "Troisième élément : " << get<2>(monTuple) << std::endl;

        return 0;
    }
    ```

    **Explication** :

    - **Décomposition du paquet de paramètres** : On sépare le premier type ```Head``` des types restants ```Tail....```
    - **Héritage récursif** : Chaque Tuple hérite de ```Tuple<Tail...>```, créant une hiérarchie de classes imbriquées.
    - **Accès aux éléments** : On utilise des structures spécialisées (```TupleElement```) pour accéder aux éléments en fonction de leur index. L'utilisation de structures templates est rendue obligatoire par le fait qu'on peut effectuer des spécialisations partielles bien plus facilement qu'avec une fonction.

#### Les paquets de paramètres templates et les paquets d'arguments

1. **Paquets de paramètres templates**
    - **Déclaration** : Utiliser ```typename... Types``` pour indiquer que la classe accepte un nombre variable de types.
    - **Décomposition** : On peut décomposer les paquets en un type et le reste : ```typename Head, typename... Tail```.

2. **Paquets d'arguments**

    - **Constructeurs** : On peut définir des constructeurs qui acceptent un nombre variable d'arguments correspondants aux types du paquet.
    - **Propagation des arguments** : Utiliser la syntaxe ```...``` pour passer les arguments restants : ```Tail... t```.

#### Autre exemple : Classe ```Variant```

Un ```Variant``` est une classe qui peut contenir une valeur de l'un parmi plusieurs types possibles.

1. **Implémentation simplifiée d'un Variant**

    ```c++
    #include <iostream>
    #include <type_traits>

    template<typename... Types>
    class Variant;

    template<typename T, typename... Rest>
    class Variant<T, Rest...> 
    {
    public:
        Variant() {}

        // Constructeur pour T
        Variant(T value) 
        {
            data_ = new T(value);
            typeIndex_ = getTypeIndex<T>();
        }

        // Constructeur pour les autres types
        template<typename U>
        Variant(U value) 
        {
            static_assert(contains<U>(), "Type non supporté");
            data_ = new U(value);
            typeIndex_ = getTypeIndex<U>();
        }

        ~Variant() 
        {
            deleteData();
        }

        // Méthode pour vérifier si le type est supporté
        template<typename U>
        static constexpr bool contains() 
        {
            //std::is_same renvoit vrai si les deux paramétres templates sont de même type
            return std::disjunction<std::is_same<U, T>, std::is_same<U, Rest>...>::value;
        }

        // Obtenir l'index du type
        template<typename U>
        static constexpr size_t getTypeIndex() 
        {
            return getTypeIndexHelper<U, T, Rest...>();
        }

    private:
        void* data_ = nullptr;
        size_t typeIndex_ = -1;

        void deleteData() 
        {
            if (data_) 
            {
                // Appeler le destructeur approprié
                // (Gestion simplifiée pour cet exemple)
                delete static_cast<T*>(data_);
            }
        }

        // Helper pour obtenir l'index du type
        template<typename U, typename First, typename... Others>
        static constexpr size_t getTypeIndexHelper() 
        {
            if constexpr (std::is_same<U, First>::value) 
            {
                return sizeof...(Rest) - sizeof...(Others);
            } else if constexpr (sizeof...(Others) > 0) 
            {
                return getTypeIndexHelper<U, Others...>();
            } else {
                return -1;
            }
        }
    };

    int main() 
    {
        Variant<int, double, std::string> v = 3.14;
        // Utilisation du variant (exemple simplifié)
        return 0;
    }
    ```

    **Explication** :

    - **Gestion des types** : Utilise des traits de type pour vérifier si un type est supporté et pour obtenir son index.
    - **Stockage des données** : Les données sont stockées sous forme de pointeur void*, avec une gestion simplifiée pour l'exemple.
    - **Destructeur** : Assure la libération correcte de la mémoire allouée.

#### Manipulation avancée des paquets de types

- **Récursion sur les types**
    On peut appliquer des opérations sur chaque type du paquet en utilisant la récursion template.

    **Exemple** : Vérifier si tous les types sont intégralement numériques (type entier)

    ```cpp
    template<typename... Types>
    struct AreAllIntegral;

    template<>
    struct AreAllIntegral<> : std::true_type {};

    template<typename T, typename... Rest>
    struct AreAllIntegral<T, Rest...> : std::conditional_t<
                                           std::is_integral<T>::value,
                                           AreAllIntegral<Rest...>,
                                           std::false_type
                                        > {};

    int main() 
    {
        std::cout << std::boolalpha;
        std::cout << "Tous intégraux ? " << AreAllIntegral<int, long, char>::value << std::endl; // true
        std::cout << "Tous intégraux ? " << AreAllIntegral<int, double, char>::value << std::endl; // false
        return 0;
    }
    ```

    **Explication** :
      - **Cas de base** : Si le paquet est vide, on retourne true.
      - **Récursion** : On vérifie si le premier type est intégral, puis on applique récursivement la même vérification sur les types restants.

#### Utilisation des Fold Expressions dans les classes

Les fold expressions, introduites avec C++17, simplifient la manipulation des paquets de paramètres.

- **Exemple : Calculer la somme des tailles des types**

    ```cpp
    template<typename... Types>
    struct TotalSize 
    {
        static constexpr size_t value = (sizeof(Types) + ...);
    };

    int main() 
    {
         std::cout << "Taille totale : " << TotalSize<int, double, char>::value << " octets" << std::endl;
        return 0;
    }
    ```

    **Explication** :
        - **Fold expression** : ```(sizeof(Types) + ...)``` calcule la somme des sizeof de chaque type dans le paquet.
        - **Résultat** : Donne la taille totale en octets des types spécifiés.

#### Autre exemple pratique

**Concaténation de chaînes à la compilation**

```cpp
#include <string>

template<typename... Strings>
std::string concatene(Strings... strs) {
    return (std::string{} + ... + strs);
}

int main() {
    auto resultat = concatene("Bonjour, ", "le ", "monde !");
    std::cout << resultat << std::endl; // Affiche "Bonjour, le monde !"
    return 0;
}
```

**Explication** :

- **Fold expression** : ```(std::string{} + ... + strs)``` concatène toutes les chaînes passées en arguments.
- **Flexibilité** : Accepte un nombre quelconque de chaînes à concaténer.

#### Bonnes pratiques pour les structures variadiques

- **Prévoir les cas de base** : Toujours fournir une spécialisation pour le cas où le paquet de paramètres est vide.
- **Utiliser les traits de type** : Faciliter les vérifications de types et améliorer la sécurité du code.
- **Limiter la complexité** : Les templates variadiques peuvent devenir complexes ; il est important de commenter le code et de le structurer clairement.
- **Utiliser les fonctionnalités modernes** : Les fold expressions et les utilitaires de la bibliothèque standard simplifient grandement le code.

#### Limitations et considérations

- **Messages d'erreur complexes** : Les erreurs dans les templates variadiques peuvent générer des messages d'erreur difficiles à interpréter.
- **Temps de compilation accru** : Une utilisation intensive des templates peut augmenter le temps de compilation.
- **Compatibilité du compilateur** : S'assurer que le compilateur utilisé supporte les fonctionnalités du standard C++ utilisé (C++11, C++14, C++17, etc.).

#### Conclusion

Les templates variadiques pour les classes et les structures en C++ permettent de créer des types génériques très puissants et flexibles. Ils ouvrent la porte à des techniques de métaprogrammation avancées, rendant possible la génération de code à la compilation pour des besoins spécifiques. En maîtrisant ces concepts, vous pourrez concevoir des bibliothèques et des applications plus robustes, modulaires et performantes.

**Résumé des points clés** :

- **Déclaration de classes template variadiques** : Utiliser ```template<typename... Types>``` pour accepter un nombre variable de types.
- **Manipulation des paquets de types** : Décomposition avec ```typename Head, typename... Tail```, et recombinaison des types.
- **Utilisation de la récursion template** : Pour appliquer des opérations sur chaque type du paquet.
- **Fold expressions** : Simplifient le traitement des paquets de types avec des opérations binaires.
- **Bonnes pratiques** : Prévoir les cas de base, utiliser les traits de type, et maintenir un code clair et lisible.

