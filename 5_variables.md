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

