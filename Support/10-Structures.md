# Les structures

Les structures sont un concept fondamental en C et C++ qui permettent de regrouper plusieurs variables de types différents sous un même nom. Elles offrent un moyen pratique et puissant d'organiser des données connexes en une seule unité logique.

Voici les points clés à comprendre sur les structures :

1. Définition : Une structure est un type de données composé qui permet de combiner des éléments de types différents.

2. Syntaxe de base : En C et C++, on définit une structure avec le mot-clé `struct`, suivi du nom de la structure et d'une liste de membres entre accolades.

3. Membres : Les variables déclarées à l'intérieur d'une structure sont appelées membres ou champs.

4. Accès aux membres : On accède aux membres d'une structure à l'aide de l'opérateur point (.) pour les variables de structure, ou de l'opérateur flèche (->) pour les pointeurs de structure.

5. Initialisation : Les structures peuvent être initialisées lors de leur déclaration, soit membre par membre, soit en utilisant des initialiseurs désignés (en C) ou des listes d'initialisation (en C++).

6. Flexibilité : Les structures peuvent contenir des membres de types variés, y compris d'autres structures, des tableaux, ou des pointeurs.

7. Utilisation en C++ : En C++, les structures peuvent également contenir des fonctions membres, des constructeurs et des destructeurs, les rapprochant ainsi des classes.

Les structures sont particulièrement utiles pour représenter des entités complexes dans vos programmes, comme des coordonnées, des données d'employés, ou des configurations de jeu. Elles permettent d'améliorer la lisibilité et l'organisation du code en regroupant des données liées.

Dans les sections suivantes, nous explorerons en détail la syntaxe et l'utilisation des structures en C et C++, ainsi que les différences subtiles entre ces deux langages concernant ce concept.

## Déclarer une structure

La syntaxe de déclaration d'une structure est la suivante :

```cpp
struct NomDeLaStructure {
    Type1 NomDuMembre1;
    Type2 NomDuMembre2;
    // ...
    void methode1(args1);
    ...

};
```

**Note** : Les méthodes sont détaillées dans le cours sur la POO. Une structure en C++ n'est en fait qu'une classe dont les membres sont publics par défaut (voir la partie sur la POO).

Exemple : définition d'une structure représentant une matrice :

```cpp
struct Matrice {
    int nombre_de_lignes;
    int nombre_de_colonnes;
    std::vector<double> coefficients;
};
...
Matrice A; // Déclare une variable A de type Matrice
```

Il est possible de créer des structures récursives à condition que l'autoréférence soit un pointeur (voir la partie sur les pointeurs).

Exemple :

```cpp
struct Noeud {
    int valeur;
    std::unique_ptr<Noeud> suivant;
};
```

## Manipuler une structure : accès aux membres

L'accès aux membres d'une structure se fait :

- à l'aide de l'opérateur point (.) pour les variables de structure,
- à l'aide de l'opérateur flèche (->) pour les pointeurs de structure.

Exemple :

```cpp
Matrice A;
A.nombre_de_lignes = 3;

auto pt_mat = std::make_unique<Matrice>();
pt_mat->nombre_de_lignes = 3;
```

## Initialiser une structure

Depuis C++ 11, il est possible (et recommandé) d'initialiser les membres d'une structure directement lors de leur déclaration :

```cpp
struct Matrice {
    int nombre_de_lignes{0};
    int nombre_de_colonnes{0};
    std::vector<double> coefficients{};
};
```

Ainsi, les membres non initialisés sont automatiquement initialisés à leur valeur par défaut lors de la construction d'une variable du type de la structure.

Plusieurs approches sont possibles sinon pour initialiser les membres d'une structure :

- Initialisation membre par membre :

Exemple:

```cpp
Matrice A;
A.nombre_de_lignes = 100;
A.nombre_de_colonnes = 100;
A.coefficients = std::move(std::vector<double>(10000));
```

- Par liste d'initialisation (en C++ 11) :

```cpp
Matrice A{100, 100, std::vector<double>(10000)};
```

- Par attributs nommés (en C++ 20) :

```cpp
Matrice A{
    .nombre_de_lignes = 100,
    .nombre_de_colonnes = 100,
    .coefficients = std::vector<double>(10000)
};
```

En initialisation par attributs nommés, l'ordre des arguments est important mais il n'est pas nécessaire de spécifier tous les attributs. Ceux qui ne sont pas spécifiés sont initialisés avec leur valeur par défaut (si elle existe).

