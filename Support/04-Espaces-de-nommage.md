# Les espaces de nommage

## La base

Un espace de nommage permet de regrouper des fonctions ou des types par regroupement logiques, par exemple par "métier" ou encore pour permettre d'éviter des collisions entre des noms.

Imaginons un projet où une première équipe s'occupe de l'aspect géométrique du code (métier géométrie) et une seconde équipe s'occupe de l'aspect algébrique du code (métier algèbre).

La première équipe décide de créer un nouveau type qu'ils nomment *Vecteur* (géométrique).

Le seconde équipe décide de créer un nouveau type qu'ils nomment *Vecteur* (algébrique).

On voit bien que si par malheur un utilisateur a besoin à la fois d'un vecteur géométrique et un vecteur algébrique dans le même code, il va se retrouver avec le même nom pour deux types différents.

L'espace de nommage permet de définir une portée pour différentes déclarations (fonctions, types, etc.), ce qui veut dire que par défaut, pour accéder à ses déclarations, il faut préfixer le nom utilisé par l'espace de nommage suivi par ::

**Exemple**

```cpp
namespace géométrie
{
    struct Vecteur {// Définition d'un type Vecteur géométrique
        ...
    };
}

namespace algèbre
{
    struct Vecteur {// Définition d'un type Vecteur algébrique
        ...
    };
}
...
géométrie::Vecteur u; // Remarquer que Vecteur est préfixée de l'espace de nommage et de ::
algèbre::Vecteur v;
```

En déclarant les nouveaux types ou fonctions dans des espaces de nommage correspondant aux métiers, on peut ainsi éviter des conflits de nom.

```cpp
namespace géométrie
{
    struct Vecteur {// Définition d'un type Vecteur géométrique 3D
        ...
    };
}
namespace algébre
{
    struct Vecteur {// Définition d'un type Vecteur     algébrique
        ...
    };
}
...
géométrie::Vecteur u; // Un vecteur géométrique 3D
algèbre::Vecteur   v; // Un vecteur algébrique
```

Les types et les fonctions appartenant à un espace de nommage peuvent être répartis dans plusieurs fichiers différents, du moment qu'on donne bien le même espace de nommage pour tous. Il est donc facile d'étendre les types et fonctions appartenant à un espace de nommage.

Il est possible d'imbriquer des espaces de nommage :

```cpp
namespace math
{
    namespace géométrie
    {
        struct Vecteur { ... };
        ...
    }
    namespace algébre
    {
        struct Vecteur { ... };
        ...
    }
}
...
math::géométrie::Vecteur u;
```

En C++ 17, il est possible de nommé directement un espace de nommage imbriqué :

```cpp
namespace math::géométrie
{
    struct Vecteur { ... };
    ...
}
...
math::géométrie::Vecteur u;
```

**Remarque** : La grande majorité des types et fonctions déclarées dans la bibliothèque standard appartiennent à l'espace de nommage `std`

Par exemple, `cout` est déclaré dans l'espace de nommage `std`, c'est pourquoi dans l'exemple du code *Hello World*, on l'a utilisé sous la forme `std::cout`.

Dans le but d'allèger le code, on peut spéficifer soit en global, soit dans une fonction ou dans la définition d'un type qu'on veut utiliser des types et fonctions inclus dans un espace de nommage sans devoir spécifier cet espace de nommage à chaque fois. Pour cela on utilise l'instruction

```cpp
using namespace <nom_de_l'espace_de_nommage>;
```

Par exemple, si on veut utiliser les fonctions et types définis dans la bibliothèque standard sans les préfixer par `std::`, il est tout à fait possible d'écrire après les includes en début de code :

```cpp
using namespace std;
```

Si on souhaite uniquement qu'on puisse omettre le préfixe de l'espace de nommage que pour  quelques types ou fonctions, on peut pour chacun écrire l'instruction suivante :

```cpp
using <nom_espace_nommage>::<nom_type_ou_fonction>;
```

Par exemple, si on veut seulement que `cout` ne soit pas préfixé par `std::`, il suffit de mettre en début de fichier (après les include) :

```cpp
using std::cout;
```

**Remarque** : On peut aussi alléger uniquement l'écriture d'une fonction et non de toutes les fonctions d'un fichier source, il suffit d'utiliser les `using` à l'intérieur de cette fontion plutôt qu'en début de fichier.

Voici une version de *Hello world* où on ne préfixe pas `cout` par `std::` :

```cpp
#include <iostream>

int main()
{
    using std::cout;
    cout << "Hello world !" << std::endl;
    return EXIT_SUCCESS;
}
```

## Espace de nommage en ligne

Il est possible de rajouter le mot clef `inline` avant l'espace de nommage. On définit ainsi un espace de nommage en ligne.

Un espace de nommage en ligne revient à créer un espace de nommage suivit d'un using de cet espace de nommage ! Ainsi :

```cpp
inline namespace A
{
    void f();
}

f(); // OK, car A inline
A::f(); // OK car f appartient à l'espace de nommage A
```

### Usage des espaces de nommage en ligne

**Le premier usage** des espaces de nommage en ligne est de pouvoir maintenir plusieurs versions d'une même interface, chaque version étant déclarée dans son propre espace de nommage et en définissant quelle version est la version "par défaut" en déclarant en ligne l'espace de nommage contenant cette version.

Ainsi en ne préfixant pas une fonction par sa version, on prendra la version par défaut, et sinon la version correspondant à la version qu'on a préfixée.

Dans l'exemple ci--dessous, `algébre::Matrix` sera représenté par le type défini dans l'espace de nommage `v2_0`. Si on veut explicitement utiliser l'ancienne version (pour valider la nouvelle version par exemple), on utilisera `algébre::v2_0::Matrix` :

```cpp
namespace algébre
{
    namespace v1_95
    {
        struct Matrix {
            ...
        };
    }

    inline namespace v2_0
    {
        struct Matrix {
            ...
        };
    }
}
...
algébre::Matrix A; // Version 2.0 du type matrice
algébre::v1_95::MAtrix A1; // Version 1.95 du type matrice
```

-------------------------
**Usage avancé**
-------------------------

**Note** : *Dans un premier temps, vous pouvez sautez cette section qui demande déjà de connaître la généricité en C++ (templates). Vous y reviendrez lorsque vous serez utiliser les templates.*

L'usage des espaces de nommage en ligne pourrait dans l'exemple précédent être remplacé par des `using namespace`. On rajoute de plus une macro pour pouvoir facilement basculer entre la version 1.95 et la version 2 :

```cpp
namespace algébre
{
    namespace v1_95
    {
        struct Matrix {
            ...
        };
    }

    namespace v2_0
    {
        struct Matrix {
            ...
        };
    }
#   if defined(USE_OLD_VERSION)
    using namespace v1_95;
#   else
    using namespace v2_0;
#   endif
}
...
algébre::Matrix A; // Version 2.0 du type matrice
algébre::v1_95::MAtrix A1; // Version 1.95 du type matrice
```

Cependant, le standard C++ stipule qu'une spécialisation d'un template doit être défini dans le même espace de nommage que la définition du template qu'il spécialise.

Supposons que notre structure matrice est une structure template et que nous voulons spécialiser au niveau de l'espace de nommage `algèbre` avec un réel double précision.

```cpp
namespace algébre
{
namespace v1_95
{
    template<typename K>
    struct Matrix {
        ...
        Vector operator * ( Vector const& u )
        {
            Vector v(u.dim(),K(0));
            for (std::size_t iRow=0; iRow < u.dim(); ++iRow)
            {
                for(std::size_t jCol=0; jCol<u.dim(); ++jCol)
                    v[iRow] += coefs[iRow+jCol*u.dim()]*u[jCol];
            }
            return v;
        }
        ...
    };
}

namespace v2_0
{
    template<typename K>
    struct Matrix {
        ...
        Vector operator * ( Vector const& u )
        {
            Vector v(u.dim(),K(0));
            for (std::size_t iRow=0; iRow < u.dim(); ++iRow)
            {
                for(std::size_t jCol=0; jCol<u.dim(); ++jCol)
                    v[iRow] += coefs[iRow*u.dim()+jCol]*u[jCol];
            }
            return v;
        };
    }
#   if defined(USE_OLD_VERSION)
    using namespace v1_95;
#   else
    using namespace v2_0;
#   endif
    template<> struct Matrix<double>
    {
        Vector operator * ( Vector const& u )
        {
            Vector v(u.dim(),0.);
            dgemv( ... );// Appel au BLAS
            return v;
        };

    };
}
```

Malheureusement, ce code ne compile pas puisque comme dit plus haut, la spécialisation d'un template doit se faire dans le même espace de nommage que la déclaration du template.

On pourrait spécialiser chaque version du template dans les deux versions, mais cela demandera de dupliquer du code.

Seule solution pour ne pas dupliquer du code, utiliser les espaces de nommage en ligne qui du coup permettra de définir une des deux versions au même niveau que la spécialisation !

```cpp
namespace algébre
{
#if defined(USE_OLD_VERSION)
inline
#endif
namespace v1_95
{
    template<typename K>
    struct Matrix {
        ...
        Vector operator * ( Vector const& u )
        {
            Vector v(u.dim(),K(0));
            for (std::size_t iRow=0; iRow < u.dim(); ++iRow)
            {
                for(std::size_t jCol=0; jCol<u.dim(); ++jCol)
                    v[iRow] += coefs[iRow+jCol*u.dim()]*u[jCol];
            }
            return v;
        }
        ...
    };
}

#if !defined(USE_OLD_VERSION)
inline
#endif
namespace v2_0
{
    template<typename K>
    struct Matrix {
        ...
        Vector operator * ( Vector const& u )
        {
            Vector v(u.dim(),K(0));
            for (std::size_t iRow=0; iRow < u.dim(); ++iRow)
            {
                for(std::size_t jCol=0; jCol<u.dim(); ++jCol)
                    v[iRow] += coefs[iRow*u.dim()+jCol]*u[jCol];
            }
            return v;
        };
    }
}

template<> struct Matrix<double>
{
    ...
    Vector operator * ( Vector const& u )
    {
        Vector v(u.dim(),0.);
        dgemv( ... );// Appel au BLAS
        return v;
    };
    ...
};
}
```

## Aliasing d'espace de nommage

Il est possible localement dans un fichier ou une fonction de renommer un espace de nommage. Cela est en particuliers utile lorsque l'espace de nommage est long (car imbriqué par exemple)

La syntaxe pour cela ait :

```cpp
namespace nouveau_nom = ancien_nom;
```

Par exemple :

- sans aliasing d'espace de nommage :

  ```cpp
  namespace mathématiques::algèbre
  {
  struct Vecteur { ... };
  struct Matrice { ... };
  ...
  }
  ...
  mathématiques::algèbre::Vecteur u;
  mathématiques::algèbre::Matrice A;
  ```

- avec aliasing d'espace de nommage

  ```cpp
  namespace mathématiques::algèbre
  {
  struct Vecteur { ... };
  struct Matrice { ... };
  ...
  }
  ...
  namespace alg = mathématiques::algèbre;
  alg::Vecteur u;
  alg::Matrice A;
  ```

## Espace de nommage anonyme

Un espace de nommage anonyme est une espace de nommage sans nom. Toutes fonctions et tous types déclarés dans un espace de nommage anonyme ne sera visible que dans le fichier dans lequel l'espace de nommage anonyme est déclaré. Cela permet de cacher des détails de mise en oeuvre (des fonctions qui ne servent que pour d'autres fontions définies dans le fichier) qui ne sont pas normalement visibles dans la table des symboles créé dans le fichier binaire produit.

```cpp
namespace {
// Fonction visible uniquement dans le fichier présent
void fonction_aide( ... ) { ... }
}
...
// Fonction publique définie dans le même fichier que
// l'espace de nommage anonyme
void fonction_publique( ... )
{
    ...
    // qui appelle la fonction d'aide définie dans l'espace de
    // nommage anonyme
    fonction_aide( ... );
    ...
}
```

Notons qu'un espace de nommage anonyme peut être inline afin de pouvoir spécialiser un template en dehors de l'espace de nommage anonyme.

