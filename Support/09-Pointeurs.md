# Pointeurs

Les pointeurs représentent une simple adresse en mémoire.

En C et C++, les pointeurs sont natifs au langage et ont la syntaxe suivante :

```cpp
Type *p;
```

qui désigne un pointeur `p` sur un objet de type `Type`. Il est néanmoins déconseillé d'utiliser ces pointeurs et plutôt utiliser les pointeurs intelligents fournis par la bibliothèque standard de C++.

A noter qu'il existe un pointeur spécial : le pointeur `nullptr` de type `nullptr_t` qui représente un pointeur non valide (ne pointant sur aucune valeur).

On accède à la valeur pointée par un pointeur avec l'opérateur `*` :

```cpp
Type v = *p;
```

Il est possible de faire de l'arithmétique de pointeur mais uniquement sur les pointeurs natifs :

```cpp
p = p + 5; // le nouveau p pointe sur le 6ème élément de type après l'ancien p
```

## Les pointeurs intelligents

### Les pointeurs partagés

Pour utiliser les pointeurs partagés, il faut inclure l'en-tête `<memory>` :

```cpp
#include <memory>
```

Ces pointeurs permettent de partager la valeur pointée entre plusieurs pointeurs :

- On créer un nouveau pointeur sur une valeur en réservant la mémoire nécessaire et en l'initialisant avec la valeur à l'aide de `std::make_shared<Type>(args...)`;
- On peut copier un pointeur partagé dans d'autres pointeurs partagés. Un compteur interne aux pointeurs partagés est incrémenté à chaque copie;
- Lorsqu'un pointeur partagé est détruit ou va pointer sur une autre valeur, le compteur interne est décrémenté. Lorsque ce compteur tombe à 0, la mémoire allouée est libérée et la valeur pointée est détruite.

**Exemple d'utilisation** : gestion d'un graphe dynamique où on peut rajouter ou supprimer des arcs dynamiquement.

**Exemple de code** :

```cpp
auto pt_value = std::make_shared<std::complex<double>>( 1., -3.); // Pointeur sur valeur complexe 1.-3.i
auto pt_val2 = pt_value;// pt_value et pt_val2 pointent sur la même valeur.
pt_value = nullptr; // pt_value ne pointent plus sur une valeur.
pt_val2 = std::make_shared<std::complex<double>>(0.,1.); // pt_val2 pointe sur une nouvelle valeur
// La valeur complexe (1.-3.i) est détruite car plus aucun pointeur ne la pointe.
```

### Les pointeurs uniques

Pour utiliser les pointeurs uniques, il faut inclure l'en-tête `<memory>` :

```cpp
#include <memory>
```

Ces pointeurs sont similaires aux pointeurs partagés mais ne permettent la possession de la valeur pointée que par un seul pointeur. Lorsqu'un pointeur unique est détruit, la valeur pointée est automatiquement détruite.

La gestion des pointeurs uniques étant moins lourde que celle des pointeurs partagés, ils sont plus performants que les pointeurs partagés (et même aussi performants que les pointeurs natifs).

**Mode de fonctionnement** :

- On créer un nouveau pointeur sur une valeur en réservant la mémoire nécessaire et en l'initialisant avec la valeur à l'aide de `std::make_unique<Type>(args...)`;
- On peut déplacer un pointeur unique dans un autre pointeur unique mais pas le copier.
- Lorsqu'un pointeur unique est détruit ou pointe sur une autre valeur, la valeur anciennement pointée est automatiquement détruite.

**Exemple d'utilisation** : gérer un contexte, une fenêtre graphique, etc.

**Exemple de code** :

```cpp
auto pt_value = std::make_unique<std::complex<double>>( 1., -3.); // Pointeur sur valeur complexe 1.-3.i
auto pt_val2 = std::move(pt_value); // pt_value ne pointe plus sur une valeur. pt_val2 pointe sur la valeur (1.-3.i)
pt_val2 = std::make_unique<std::complex<double>>(0.,1.); // pt_val2 pointe sur une nouvelle valeur (0.+1.i)
// La valeur complexe (1.-3.i) est détruite car plus aucun pointeur ne la pointe.
```

