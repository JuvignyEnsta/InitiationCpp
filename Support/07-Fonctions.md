# Les fonctions

Les fonctions sont des blocs de code réutilisables qui effectuent une tâche spécifique. En C++, elles jouent un rôle crucial dans l'organisation et la structuration du code. Les fonctions permettent de diviser un programme en petites unités logiques, ce qui améliore la lisibilité, la maintenabilité et la réutilisation du code.

Une fonction en C++ se compose généralement des éléments suivants :

- Un type de retour (ou `void` si la fonction ne renvoie rien)
- Un nom
- Une liste de paramètres (qui peut être vide)
- Un corps contenant les instructions à exécuter

Les fonctions peuvent accepter des arguments, effectuer des opérations et renvoyer des résultats. Elles sont essentielles pour implémenter le concept de modularité dans la programmation C++.

## Déclaration d'une fonction

La syntaxe pour déclarer une fonction est la suivante :

```cpp
type nom(liste_de_paramètres);
```

Il est bien sûr possible de ne passer aucun argument à la fonction. Dans ce cas, on ouvre et ferme les parenthèses sans rien entre elles. Si la fonction ne retourne rien, on utilise le mot-clé `void` (équivalent à une procédure en Fortran).

Exemples de déclarations de fonctions :

```cpp
void affiche_menu();
int somme(int a, int b);
double solve_linear_system(double a, double b);// Résoud a.x + b = 0
```

Il est autorisé en C++ de déclarer plusieurs fonctions portant le même nom mais avec des listes de paramètres différentes. On parle alors de **surcharge de fonction**.

Exemple :

```cpp
int max(int a, int b);
double max(int a, int b);// Erreur de compilation car fonction avec même nom et liste de paramètres
int max(int a, int b, int c);   // OK
double max(double a, double b); // OK
```

La déclaration des fonctions se fait en général dans un fichier d'en-tête (`.h` ou `.hpp`) et l'implémentation dans un fichier source (`.cpp`).

## Mise en œuvre d'une fonction

La mise en oeuvre d'une fonction consiste à mettre en oeuvre l'algorithme permettant de réaliser la tâche définie par la fonction.

La mise en œuvre d'une fonction se fait en utilisant la syntaxe suivante :

```cpp
type nom(liste_de_paramètres) 
{
    // corps de la fonction
}
```

En général, la mise en œuvre d'une fonction se fait dans un fichier source (`.cpp`) et non dans le fichier d'en-tête sauf si la fonction est une fonction **inline** (voir plus loin).

Exemple :

```cpp
int max(int a, int b) {
    return a > b ? a : b;
}
```

Depuis C++ 11, il est possible de définir une fonction sous forme fonctionnelle :

```cpp
// Déclaration de la fonction
auto max(int a, int b) -> int;
...
// Définition de la fonction
auto max(int a, int b) -> int {
    return a > b ? a : b;
}
...
// Appel de la fonction
int x = max(3, 4);
```

## Passage par valeur, par référence et par pointeur

Par défaut, les paramêtres d'une fonction sont passés par valeur. Cela signifie que la valeur du paramètre est copiée dans une variable locale à la fonction. Toute modification du paramètre au sein de la fonction n'aura aucun effet sur la variable passée en argument.

Par exemple :

```cpp
void swap(int a, int b) {
    int tmp = a;
    a = b;
    b = tmp;
}
...
int x = 3, y = 4;
swap(x, y); // x et y n'ont pas été modifiées !
```

Pour pallier à cet inconvénient, il est possible de passer un paramètre par référence. Dans ce cas, une référence sur la variable passée en argument est créée et reliée à ce paramètre. Toute modification du paramètre au sein de la fonction sera répercutée sur la variable passée en argument.

En reprenant l'exemple précédent, on peut définir la fonction `swap` de la façon suivante :

```cpp
void swap(int& a, int& b) {
    int tmp = a;
    a = b;
    b = tmp;
}
...
int x = 3, y = 4;
swap(x, y); // x et y ont été modifiées et bien échangées !
```

Pour des structures volumineuses, il est préférable de passer un paramêtre par référence, constante si on ne souhaite pas pouvoir modifier la structure.

Exemple :

```cpp
auto solve(MatricePleine const& A, Vecteur const& b) -> Vecteur;
```

Un autre avantage du passage par référence constante est qu'on peut passer directement une valeur littérale en argument :

```cpp
auto y = solve(A, Vecteur(A.dimension(), 1.0));
```

## Paramètres par défaut

Il est possible en C++ de définir des paramètres possédant une valeur par défaut. Dans ce cas, si l'argument n'est pas passé lors de l'appel de la fonction, la valeur par défaut sera utilisée.

Si un paramètre possède une valeur par défaut, tous les paramètres situés à sa droite doivent également posséder une valeur par défaut.

A l'appel de la fonction, les paramètres sans valeur par défaut doivent tous être passés. De plus, si un paramètre possédant une valeur par défaut est définie avec une valeur, tous les paramètres situés à sa gauche doivent également être définis avec une valeur.

Exemple :

```cpp
std::complex<double> monopole( double kWave, double radius, double min_radius = 0.01, double phase = 0.0 )
{
    double min_rad = std::max(min_radius, radius);
    return std::polar(1./min_rad, kWave * min_rad + phase);    
}
...
std::complex<double> z1 = monopole(1.0, 0.01); // min_radius = 0.01, phase = 0.0
std::complex<double> z2 = monopole(1.0, 0.01, 0.02); // min_radius = 0.02, phase = 0.0
std::complex<double> z3 = monopole(1.0, 0.01, 0.02, std::numbers::pi/2); // min_radius = 0.02, phase = pi/2
```

## Surcharge des fonctions et des opérateurs

Plusieurs fonctions ou opérateurs peuvent être définis avec le même nom si leur liste de paramètres est différente, c'est à dire :

- le nombre de paramètres est différent
- le type de certains paramètres est différent

Cette possibilité est offerte par le compilateur C++ qui est capable de distinguer les différentes versions de la fonction en fonction du nombre et du type des paramètres passés.

Exemple :

```cpp
int max(int a, int b);
int max(int a, int b, int c);
double max(double a, double b);
```

**Attention** : le nombre et le type des données retournées ne sont pas pris en compte dans la surcharge.

Il est également possible de surcharger les opérateurs suivants :

- `[]` : opérateur de sélection de membre
- `()` : appel de fonction
- `->` : opérateur d'accès à un membre par un pointeur
- `=` : opérateur d'affectation
- `<<` : opérateur de flux de sortie
- `>>` : opérateur de flux d'entrée
- `+`, `-`, `*`, `/`, `%` : opérateurs arithmétiques
- `+=`, `-=`, `*=`, `/=`, `%=` : opérateurs d'affectation combinés
- `==`, `!=`, `<`, `<=`, `>`, `>=` : opérateurs de comparaison
- `&&`, `||`, `!`, `~` : opérateurs logiques
- `&`, `|`, `^`, `<<`, `>>` : opérateurs bitwise
- `,` : opérateur de séquence
- `++`, `--` : opérateurs d'incrémentation et de décrémentation (pré et post)

**Note** : Pour les opérateurs `++` et `--`, on peut définir deux versions : une version préfixée et une version post-fixée. Pour la post-incrémentation, il faut ajouter un paramètre de type `int` à la fonction (de façon artificielle). Soit :

```cpp
Type& operator++(); // Préincrémentation
Type operator++(int); // Postincrémentation
```

On peut ainsi définir des opérateurs pour de nouveaux types. Par exemple, on peut définir l'opérateur `+` pour un type `Vecteur` afin de pouvoir additionner deux vecteurs :

```cpp
// Déclaration
Vecteur operator+(Vecteur const& u, Vecteur const& v);
...
// Définition
Vecteur operator+(Vecteur const& u, Vecteur const& v) 
{
    ...
}
...
// Appel
Vecteur u(3), v(3), w;
Vecteur w = u + v;
```

## Contrats de fonctions et assertions

Le contrat d'une fonction est un concept fondamental en programmation qui définit les responsabilités mutuelles entre la fonction et son appelant. C'est comme un accord tacite qui spécifie ce que la fonction promet de faire et ce qu'elle attend en retour.

Le contrat d'une fonction peut être décomposé en trois parties :

**Préconditions** : conditions qui doivent être vraies avant l'exécution de la fonction. Cela comprend le domaine de définition de la fonction.

**Postconditions** : conditions qui doivent être vraies après l'exécution de la fonction. Cela comprend le domaine de validité des résultats produits par la fonction.

**Invariant** : conditions qui doivent être vraies pendant toute la durée de vie de la fonction. Cela comprend le domaine de validité des variables internes à la fonction.

**Exemple** : Racine carrée d'un nombre réel.

- En entrée, le paramètre doit être positif ou nul.
- En sortie, la fonction renvoie un nombre réel positif ou nul.

En C++, le contrat d'une fonction peut être exprimé en utilisant des assertions. Les assertions sont des expressions booléennes qui doivent être vraies au moment de l'exécution de la fonction. Si une assertion est fausse, le programme est interrompu et un message d'erreur est affiché.

Les assertions sont généralement utilisées pour vérifier les préconditions et les postconditions des fonctions. Les préconditions sont des conditions qui doivent être vraies avant l'exécution de la fonction, tandis que les postconditions sont des conditions qui doivent être vraies après l'exécution de la fonction.

Les assert sont définis dans l'en-tête `<cassert>`. Provenant du langage C, les asserts ne sont pas préfixés par l'espace de nommage `std`.

Lorsqu'on produit du binaire en production, on peut désactiver les asserts en utilisant l'option `-DNDEBUG` lors de la compilation.

Exemple de mise en oeuvre du contrat pour la fonction `sqrt` :

```cpp
double sqrt(double x) {
    assert(x >= 0.0); // Précondition
    double result = std::sqrt(x);
    assert(result >= 0.0); // Postcondition
    return result;
}
```

Parfois, les préconditions et les postconditions peuvent être trop complexes pour être exprimées sous forme d'assertions. Dans ce cas, on peut utiliser des variantes plus sophistiquées de contrats de fonctions. Il faut toutefois s'assurer que ces tests soient désactivables en mode production, surtout si ces tests sont coûteux en temps de calcul (par exeme, vérifier qu'un tableau est bien trié). On utilisera pour cela des macros comme dans le modèle suivant :

```cpp
#if defined(DEBUG)
#  define CONTRACT_CHECK(condition) \
    if (!(condition)) { \
        std::cerr << "Contract check failed: " << #condition << std::endl; \
        std::abort(); \
    }
#else
#  define CONTRACT_CHECK(condition) ((void)0) // Emet l'instruction NOP (no operation) pour le processeur
#endif

double sqrt(double x) {
    CONTRACT_CHECK(x >= 0.0); // Précondition
    double result = std::sqrt(x);
    CONTRACT_CHECK(result >= 0.0); // Postcondition
    return result;
}
```

Dans cet exemple, la macro `CONTRACT_CHECK` est définie en fonction de la constante `DEBUG`. Si `DEBUG` est définie, la macro est équivalente à l'instruction `assert`. Si `DEBUG` n'est pas définie, la macro ne fait rien.

Parfois, une précondition ou une postcondition peut être difficile à exprimer dans un langage de programmation. Par exemple, dans une fonction de tri, comment vérifier que la fonction de comparaison vérifie bien une relation d'ordre total ? Une telle affirmation ne peut être démontrée formellement dans un langage de programmation. Dans ce cas, il faut se contenter d'une vérification empirique et des tests unitaires et rajouter un commentaire dans la documentation de la fonction pour informer l'utilisateur de la fonction de cette contrainte.

**Remarque** : Les préconditions et les postconditions font partie de la documentation de la fonction. Elles doivent donc être annotées dans la documentation (Doxygen ou autre).

