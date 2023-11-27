# Déclaration et initialisation des variables

## Syntaxe

Une variable peut être déclarée sans ou avec initialisation et il est bien sûr possible de modifier la valeur d'une variable dans des blocs d'instructions, à condition que la variable ne soit pas constante.

Puisque le C++ est un langage fortement type, une variable doit être typée à sa déclaration. Son type ne pourra pas changer tout le long du programme...

La déclaration peut se faire à peu prêt n'importe où dans le code. La syntaxe pour déclarer une variable est :

  - **Sans initialisation** : 
    ```cpp
    Type var;
    Type var1, var2, ..., varN;
    ```
  - **Avec initialisation** :
    ```cpp
    Type var1 = valeur1; // Première façon 
    Type var2{valeur2};  // Seconde  façon
    Type var13 = val13, var14 = val14, ..., var1N = val1N;
    Type var23{val23}, var24{val24}, ..., var2N{val2N};
    ```

**Note** : Il est également possible de remplacer les `{}` par des `()`. 

Pour modifier une variable déjà déclarée, il faut utiliser le symbole `=` :
```cpp
var1 = var2; // var1 prend la même valeur que var2
```

Le C++ (comme le C), si on ne se sert d'aucune bibliothèque, propose les types suivants :

  - Les caractères `char` : Un caractère est encadré par deux simples quotes.
    ```cpp
    char c = 'a';
    ```
  - Les chaînes de caractères `char *` : une chaîne de caractère est délimitée par des doubles quotes
    ```cpp
    char * phrase = "Guère épais !";
    ```
    Nous verrons qu'en C++ il est préférable d'utiliser un autre type de chaîne de caractère proposé par la bibliothèque standard.
  - Les entiers signés `short, int, long, long long` et non signés `unsigned short, unsigned, unsigned long, unsigned long long`. Là encore, nous verrons qu'il est préférable d'utiliser des entiers redéfinis dans la bibliothèque standard du C++
  - Des réels simples précision (32 bits : `float`), doubles précisions (64 bits : `double`) et doubles longs (128 bits : `long double`)
  - Le type booléen `bool` qui ne peut prendre que deux valeurs `true` (vrai) et `false` (faux).

## Les booléens

Le type `bool` décrit une valeur booléenne qui peut prendre que deux valeurs :
  - `true` : valeur signifiant que le booléen est *vrai*
  - `false`: valeur signifiant que le booléen est *faux*

Il est possible d'effectuer des calculs booléens sur les valeurs booléennes :

 - **Et logique** entre deux booléens: Symbole `&&` ou `and`. Renvoit vrai si les deux booléens sont vrais, renvoit faux sinon
 - **Ou logique** entre deux booléens: Symbole `||` ou `or`. Renvoit faux si les deux booléens sont faux, renvoit vrai sinon;
 - **Ou exclusif logique** entre deux booléens : symbole `^` ou `xor`. Ne renvoit vrai que si un booléen est vrai et l'autre faux, renvoit faux sinon.

Exemple de code utilisant des booléens :
```cpp
bool b1 = true;
bool b2 = false;
bool b3 = b1 and b2; // b3 = false
bool b4 = b1 or  b2; // b4 = true
b3 = b1 xor b2;      // b3 = true
```

Il est possible d'afficher un booléen à l'écran. Par défaut, le C++ affiche `0` quand le booléen est faux, et `1` quand il est vrai. On peut cependant demander au C++ d'écrire littéralement `true` ou `false` en utilisant `std::boolalpha`. Si on veut revenir à l'affichage par défaut on utilisera `std::noboolalpha`

```cpp
bool b1 = true, b2 = false;
std::cout << b1 << " " << b2 << std::endl;
std::cout << std::boolalpha << b1 << " " << std::noboolalpha
          << b2 << std::endl;
```

affichera

    1 0
    true 0

## Les entiers

Les entiers comme leurs noms indiquent représentent des valeurs *entières* positives et également négatives pour certains types.

La mémoire étant limitée et le nombre d'entiers possibles infinis, il est bien sûr impossible de représenter tous les entiers sur un ordinateur. 

Le C++ possède des types d'entiers dont le nombre d'octets occupés en mémoire est fixé par le langage. Les bornes inférieure et supérieure pour un type sont donc d'avance connues et une des problématiques de l'ingénieur est de s'assurer que le type choisi pour représenter ses entiers contient la plage de valeurs que peut valoir ses entiers dans son programme.

Les entiers en mémoire sont représentés sous la forme *binaire*, c'est à dire en base deux. Chaque octet contenant 8 bits (un bit est une partie de l'octet pouvant seulement prendre les valeurs 0 ou 1), il est possible pour un type d'entiers uniquement positifs ou nuls représentés sur *n* octets d'écrire un entier en base deux sur *8.n* bits. Il est donc possible de définir pour ce type d'entier des valeurs comprises entre 0 et $2^{8n}$ où $n$ est le nombre d'octets.

Si le type d'entier peut représenter des valeurs négatives ou nulles, le processeur réserve un bit *s* dit *bit de signature* permettant de définir si l'entier est positif (*s=0*) ou négatif (*s=1*). Si l'entier est négatif, on choisit pour représentation de sa valeur *le complément à un* permettant de faciliter pour le processeur l'addition d'un nombre positif et négatif. Un nombre négatif sur *n* octets avec cette représentation peut avoir une valeur comprise entre $-2^{8n-1}$ et $2^{8n-1}-1$

Il existe dans le langage même cinq types différents d'entiers signés :

| **Type** |  **Intervalle** | **Remarque** |
|:-------:|:-------:|:----:|
|`signed char`| $[-128;127]$ | |
|`short` | $[-32768;32767]$ | |
|`int` | $[-32768;32767]$ ou $[-2^{31};2^{31}-1]$ | Dépend du système et/ou du processeur |
|`long` | $[-2^{31};2^{31}-1]$ ou $[-2^{63};2^{63}-1]$ | Dépend du système et/ou du processeur |
|`long long` | $[-2^{63};2^{63}-1]$ | |

et de même pour les entiers non signés :

| **Type** |  **Intervalle** | **Remarque** |
|:-------:|:-------:|:----:|
|`unsigned char`| $[0;255]$ | |
|`unsigned short` | $[0;65535]$ | |
|`unsigned` | $[0;65535]$ ou $[0;2^{32}-1]$ | Dépend du système et/ou du processeur |
|`unsigned long` | $[0;2^{32}-1]$ ou $[0;2^{64}-1]$ | Dépend du système et/ou du processeur |
|`unsigned long long` | $[0;2^{64}-1]$ | |

*Remarque* : Il est possible de déclarer un entier de type *char*, cependant cela est vivement déconseillé car il n'est pas spécifié dans la norme qu'un entier de type *char* doit être signé ou non signé !

On peut remarquer que pour le type *int* et le type *long*, les valeurs représentées vont dépendre du type de processeur ou du système d'exploitation utilisé. Cela peut mener à des dépassements d'entiers (on cherche à calculer un entier qui n'est pas représentable par le type d'entier employé). Ainsi le code pourra bien marcher sur un os donné (linux par exemple ou *long* est représenté sur huit octets et ne pas marcher sous windows ou *long* est représenté sur quatre octets).

C'est pourquoi il est important d'utiliser une extension des types d'entier proposée par la composante `cstdint` de la `std`.

On pourra à l'aide de cette composante utiliser un type d'entier dont le nombre de bits est contenu dans le nom : 

  - `std::int8_t`  pour un entier signé représenté sur un octet;
  - `std::int16_t` pour un entier signé représenté sur deux octets;
  - `std::int32_t` pour un entier signé représenté sur quatre octets;
  - `std::int64_t` pour un entier signé représenté sur huit octets.
  - `std::uint8_t` pour un entier non signé représenté sur un octet;
  - `std::uint16_t` pour un entier non signé représenté sur deux octets;
  - `std::uint32_t` pour un entier non signé représenté sur quatre octets;
  - `std::uint64_t` pour un entier non signé représenté sur huit octets.

Il existe également un entier représentant le type d'entier le plus volumineux géré par le processeur utilisé pour compiler : `std::size_t`.

### Opérations sur les entiers

Les opérations possibles sur les entiers sont :

  - l'addition : `k = i + j;`
  - l'addition *sur place* : `i += j;` qui affecte ici à $i$ la somme de $i+j$;
  - la soustraction : `k = i - j`;
  - la soustraction *sur place* : `i -= j;` qui retrance la valeur contenue dans $j$ à la valeur contenue dans $i$;
  - la multiplication : `k = i * j;`
  - la multiplication *sur place* : `i  *= j;` qui affecte à $i$ le résultat de $i * j$;
  - la division entière : `k = i / j;`
  - la division entière *sur place* : `i /= j;` qui affecte à $i$ le résultat de la division entière de $i$ par $j$;
  - le modulo : `k = i % j;` reste de la division entière de $i$ par $j$;
  - le module *sur place* : `i %= j;` qui affecte à $i$ le reste de la division entière de $i$ par $j$;
  - la pré-incrémentation : `++i;` qui consiste à incrémenter de un la valeur de $i$ et de retourner la **nouvelle** valeur pour résultat. Ainsi dans le code suivant :
    ```cpp
    int i = 3;
    int j = ++i;
    ```
    $i$ vaudra $4$ et $j$ vaudra $4$;
  - la post-incrémentation : `i++;` qui consiste à incrémenter de un la valeur de $i$ et de retourner l'**ancienne** valeur pour résultat. Ainsi, dans le code suivant :
    ```cpp
    int i = 3;
    int j = i++;
    ```
    $i$ vaudra $4$ et $j$ vaudra $3$;
  - La pré-décrémentation : `--i;` qui consiste à décrémenter de un la valeur de $i$ et de retourner la **nouvelle** valeur pour résultat.
  Ainsi, dans le code suivant :
    ```cpp
    int i = 3;
    int j = --i;
    ```
    $i$ vaudra $2$ et $j$ vaudra $2$;
  - La post-décrémentation : `i--;` qui consiste à décrémenter de un la valeur de $i$ et de retourner l'**ancienne** valeur pour résultat.
  Ainsi, dans le code suivant :
    ```cpp
    int i = 3;
    int j = i--;
    ```
    $i$ vaudra $2$ et $j$ vaudra $3$;

Il est également possible de transformer une chaîne de caractère représentant un entier sous forme de chiffre en un entier à l'aide des fonctions 
  - `std::stoi(s)` pour transformer en `int` la chaîne de caractère $s$ passée en argument;
  - `std::stol` pour transformer en `long` la chaîne de caractère $s$ passée en argument; 
  - `std::stoll` pour transformer en `long long` la  chaîne de caractère $s$ passée en argument; 
  - `std::stou`, std::stoul, std::stoull`

**Exemple de programme utilisant des entiers**

```cpp
#include <iostream>

int main( int nargs, char *argv[])
{
  int x = std::stoi(argv[1]);
  int y = std::stoi(argv[2]);
  std::cout << x << " + " << y << x+y << std::endl;
  std::cout << x << " - " << y << x-y << std::endl;
  std::cout << x << " * " << y << x*y << std::endl;
  if (y != 0)
  {
    std::cout << x << " / " << y << x/y << std::endl;
    std::cout << x << " % " << y << x%y << std::endl;
  }
  return EXIT_SUCCESS;
}
```

