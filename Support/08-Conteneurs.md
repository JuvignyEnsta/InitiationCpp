# Les conteneurs

## Définition

Un conteneur est un objet qui gère une collection d'objets (de valeurs).

Exemple : Un tableau, une liste, un arbre, etc.

## Propriétés communes

Tous les conteneurs ont les propriétés suivantes :

- **Réservation de mémoire** : Un conteneur doit réserver de la place pour stocker ses éléments.
- **Accès aux éléments** : Un conteneur doit permettre d'accéder facilement à ses éléments en lecture et écriture.
- **Itérateurs** : Un conteneur doit fournir des itérateurs sur ses éléments. Un itérateur est un objet qui permet de parcourir les éléments d'un conteneur.
- **Libération de la mémoire** : Un conteneur doit libérer la mémoire qu'il alloue pour ses éléments lorsqu'il n'est plus nécessaire.

## Les itérateurs

Les itérateurs sont des objets qui permettent de parcourir les éléments d'un conteneur. Ils permettent de parcourir les éléments d'un conteneur de manière très simple et efficace.

Le C++ distingue plusieur type d'itérateurs :

| Type d'itérateur | Lecteur | Ecriture | Suivant | Précédent | Début | Fin |
|------------------|--------|----------|---------|-----------|--------|-----|
| iterator         | Oui    | Oui      | Oui     | Non       | c.begin() | c.end() |
| const_iterator   | Oui    | Non      | Oui     | Non       | c.cbegin() | c.cend() |
| reverse_iterator | Oui    | Oui      | Non     | Oui       | c.rbegin() | c.rend() |
| const_reverse_iterator | Oui    | Non      | Non     | Oui       | c.crbegin() | c.crend() |

- Les méthodes de type `end` pointent après le dernier élément du conteneur.
- L'opérateur `++` permet de passer à la valeur suivante (ou précédente si `reverse`).
- L'opérateur `!=` permet de tester si deux itérateurs ne pointent pas sur la même valeur.
- La valeur pointée est obtenue avec l'opérateur `*`.

Exemple :

```cpp
for (auto iter = c.begin(); iter != c.end(); ++iter) {
  *iter = 1;
}
```

Selon le type de conteneur, les itérateurs peuvent être également de type :

- **Uni-directionnel** : on ne peut utiliser que l'opérateur `++`.
- **Bidirectionnel** : on peut utiliser les opérateurs `++` et `--`.
- **Aléatoire** : on peut utiliser les opérateurs `++`, `--`, `+=`, `-=`, `[]`.

Exemple d'utilisation d'un itérateur aléatoire sur un tableau :

```cpp
for (auto iter = tab.begin(); iter != tab.end(); iter += 2) ...
```

## Boucle `for` sur un conteneur

Depuis C++ 11, il existe pour les conteneurs (tout type possédant des méthodes `begin` et `end`) trois formes de boucle :

- Première forme : pour lire les valeurs d'un conteneur

```cpp
for (typeContenu itValue : conteneur ) { ... typeContenu a = itValue; ... }
```

- Deuxième forme : pour lire/écrire les valeurs d'un conteneur

```cpp
for (typeContenu &itValue : conteneur ) { ... itValue = 2; ... }
```

- Troisième forme : pour lire ou/et écrire les valeurs d'un conteneur + indices (C++ 20)

```cpp
for (type var = value; typeContenu &itValue : conteneur ) { ... itValue = 2; ...; ++var }
```

## Aparte sur les déplacements et les copies

Depuis le C++ 11, il est possible soit de copier un objet, soit de le déplacer.

- La copie est une opération coûteuse car elle implique la duplication de l'objet.
- Le déplacement est une opération qui peut être peu coûteuse car il consiste simplement à transférer la ressource de l'objet source à l'objet destination.

Par défaut, l'opérateur `=` fait une copie. Pour faire un déplacement, il faut utiliser l'opérateur `move` à droite de l'affectation.

Par exemple, si on considère un tableau dynamique `tab` de type `std::vector<int>`, 

- l'instruction `std::vector<int> tab2 = tab;` fait une copie de `tab` dans `tab2`. Le temps pris est proportionnel à la taille de `tab`.
- Si on veut déplacer `tab` dans `tab2`, il faut utiliser `tab2 = std::move(tab);`. Le temps pris est alors constant car cela consiste simplement à échanger les pointeurs des deux vecteurs.

Un déplacement ne doit être utilisé que lorsque le conteneur source n'est plus nécessaire. En effet, il ne faut pas tenter d'utiliser un conteneur après un déplacement car ses ressources ont été transférées à un autre objet et il reste dans un état invalide.

Un déplacement a lieu automatiquement au retour d'une fonction qui retourne par valeur un objet qui lui est local.

On peut également spécifier qu'un paramètre d'une fonction est passé par déplacement en utilisant le mot clé `&&`.

Exemple :

```cpp
std::list<double> calcule_tache_prioritaire()
{
    std::list<double> taches;
    ...
    return taches; // taches sera déplacé dans la fonction appelante
}
...
void executer_tache_prioritaire(Tache&& tache)
{ // On perdra tache après l'appel de la fonction
    ...
}
...
// La liste retournée par calcule_tache_prioritaire sera déplacée dans tache_prioritaire
auto tache_prioritaire = calcule_tache_prioritaire();

```

## Les conteneurs standards

### La liste d'initialisation

**Type** : `std::initializer_list<Type>`

**Description** : Représente un ensemble de valeurs de type `Type` servant à :

- initialiser d'autres conteneurs avec des valeurs constantes;
- initialiser une structure (voir plus loin) (peut être des valeurs de types hétérogènes);
- Définir un ensemble de valeurs temporaires.

Une liste d'initialisation est toujours passée par déplacement.

Une liste d'initialisation est définie par des valeurs de même type entre accolades `{}`. Exemple :

```cpp
std::initializer_list<int> liste = {1, 2, 3, 4, 5};
```

En particuliers, cela permet de pouvoir itérer sur un ensemble de valeurs de même type :

```cpp
std::uint64_t prod = 1;
for (auto prime : {2, 3, 5, 7, 11, 13, 17, 19}) {
    prod *= prime;
}
```

### Les tableaux statiques

En C/C++, il existe un type natif pour les tableaux statiques : `Type[N]`. Mais il est déconseillé de l'utiliser car il n'offre pas les mêmes fonctionnalités qu'un tableau statique défini par la STL.

**Type** : `std::array<Type, N>` où `Type` est le type des éléments et `N` le nombre d'éléments. Pour l'utiliser, il faut inclure le fichier d'en-tête `<array>`.

**Description** : Représente un tableau statique de `N` éléments de type `Type`. Ce type est plus sûr et aussi bien optimisé que le type natif `Type[N]`.

**Initialisation** : plusieurs façons d'initialiser un tableau statique :

- `std::array<int, 3> tab;` (les éléments ne sont pas initialisés)
- `std::array<int, 3> tab = {1, 2, 3};` : Initialise les trois éléments
- `std::array tab{1,2,3};` : le C++ déduit de la liste d'initialisation que `N = 3` et `Type = int`
- `std::array<int, 3> tab = {1};` (les 2 autres éléments sont initialisés par défaut)
- `std::array<int, 3> tab{1, 2, 3};` (même syntaxe que pour un tableau natif)

**Accès aux éléments** : `tab[i]` ou `tab.at(i)`. Attention, les indices commencent à 0 :

- `tab[i]` est plus rapide que `tab.at(i)` mais ne vérifie pas si l'indice est valide.
- `tab.at(i)` vérifie si l'indice est valide et lève une exception `std::out_of_range` si l'indice est invalide.
- `tab.front()` retourne le premier élément du tableau.
- `tab.back()` retourne le dernier élément du tableau.
- `tab.data()` retourne un pointeur sur le premier élément du tableau.

**Autres fonctionnalités** :

- `tab.size()` retourne le nombre d'éléments du tableau.
- `tab.empty()` retourne `true` si le tableau ne contient aucun élément.
- `tab.fill(val)` remplit le tableau avec la valeur `val`.
- `tab.swap(tab2)` échange le contenu de `tab` et `tab2` (attention, la complexité dans ce cas est linéaire !).

Il est également possible de comparer lexicographiquement deux tableaux statiques :

- `tab == tab2` retourne `true` si les deux tableaux sont égaux.
- `tab != tab2` retourne `true` si les deux tableaux sont différents.
- `tab < tab2` retourne `true` si `tab` est strictement plus petit que `tab2`.

**Remarque** : Lors du développement, avec le compilateur g++, il est conseillé de rajouter l'option `-D_GLIBCXX_DEBUG` pour déboguer les accès en dehors des limites des tableaux (vrai pour tous les conteneurs de la STL).

### Les tableaux dynamiques

**Type** : `std::vector<Type>` où `Type` est le type des éléments. Pour l'utiliser, il faut inclure le fichier d'en-tête `<vector>`.

**Description** : Représente un tableau dynamique de taille variable utilisant un espace mémoire contiguë et des techniques de gestion de la mémoire dynamique élaborées.

Pour les tableaux dynamiques, il faut bien comprendre deux notions distinctes :

- **Taille** : le nombre d'éléments effectivement présents dans le tableau. La méthode `size()` retourne la taille du tableau.
- **Capacité** : la taille maximale du tableau, c'est-à-dire le nombre d'éléments que le tableau peut contenir avant d'avoir besoin d'allouer plus de mémoire. La méthode `capacity()` retourne la capacité du tableau.

La taille et la capacité peuvent être différentes : `u.capacity() >= u.size()`.

La méthode `reserve(n)` permet de réserver de la place pour stocker `n` éléments :

- Si `n` est inférieur ou égal à la capacité actuelle, la capacité reste inchangée.
- Si `n` est supérieur à la capacité actuelle, la capacité est augmentée et les éléments du tableau sont potentiellement déplacés vers une nouvelle zone de mémoire.

La méthode `shrink_to_fit()` permet de libérer la mémoire inutilisée.

**Initialisation** :

- `std::vector<int> tab;` (le tableau est initialisé avec 0 élément)
- `std::vector<int> tab = {1, 2, 3};` (initialise les trois éléments)
- `std::vector tab{1, 2, 3};` : le C++ (à partir de C++ 17) déduit de la liste d'initialisation que `Type = int` et réserve la place pour les 3 éléments qu'il copie
- `std::vector<int> tab(n);` (initialise le tableau avec `n` éléments non initialisés)
- `std::vector<int> tab(n, val);` (initialise le tableau avec `n` éléments initialisés à `val`)

**Rajout/suppression d'éléments** :

- `tab.push_back(val)` ajoute `val` à la fin du tableau (copie).
- `tab.pop_back()` supprime le dernier élément du tableau.
- `tab.insert(pos, val)` insère `val` à la position `pos` (copie).
- `tab.erase(pos)` supprime l'élément à la position `pos`.
- `tab.erase(first, last)` supprime les éléments dans l'intervalle `[first, last)`.
- `tab.emplace(pos, args)` insère un élément construit sur place à la position `pos`.
- `tab.emplace_back(args)` ajoute un élément construit sur place à la fin du tableau.

**Accès aux éléments** :

- `tab[i]` retourne l'élément à la position `i` (sans vérification de la validité de l'indice).
- `tab.at(i)` retourne l'élément à la position `i` (avec vérification de la validité de l'indice et lève une exception `std::out_of_range` si l'indice est invalide).
- `tab.front()` retourne le premier élément du tableau.
- `tab.back()` retourne le dernier élément du tableau.
- `tab.data()` retourne un pointeur sur le premier élément du tableau.
- `tab.empty()` retourne `true` si le tableau ne contient aucun élément.

**Remarque** : Le déplacement d'un tableau dynamique est une opération peu coûteuse car il consiste simplement à échanger les pointeurs des deux vecteurs (complexité constante).

Exemple d'utilisation d'un tableau dynamique :

```cpp
std::vector<std::int64_t> primes;
primes.reserve(nbPrimes);
primes.emplace_back(2);
if (nbPrimes > 1) primes.emplace_back(3);
std::int64_t k = 1;
while (primes.size() < nbPrimes) {
    std::int64_t p1 = 6*k-1;
    std::int64_t p2 = 6*k+1;
    k = k + 1;
    for (auto p : primes) {
        if ( (p1 > 0 ) and (p1%p == 0) ) p1 = 0;
        if ( (p2 > 0 ) and (p2%p == 0) ) p2 = 0;
        if ( (p1 == 0) and (p2 == 0) ) break;
    }
    if (p1 > 0) primes.push_back(p1);
    if ( (p2 > 0) and (primes.size() < nbPrimes) ) primes.push_back(p2);
}
std::cout << "Voici les " << nbPrimes << " premiers nombres premiers : " << std::endl;
for (auto p : primes ) std::cout << p << " ";
std::cout << std::endl;
```

### Les listes

Il existe deux types de listes en C++ :

- `std::list<Type>` : liste doublement chaînée.
- `std::forward_list<Type>` : liste simplement chaînée (C++ 11).

**Méthodes communes** :

- `l.front()` retourne le premier élément de la liste.
- `l.push_front(val)` ajoute `val` au début de la liste (copie).
- `l.pop_front()` supprime le premier élément de la liste.
- `l.emplace_front(args)` insère un élément construit sur place au début de la liste.
- `l.empty()` retourne `true` si la liste ne contient aucun élément.
- `l.clear()` supprime tous les éléments de la liste.
- `l.swap(l2)` échange le contenu de `l` et `l2` (complexité constante).
- `l.merge(l2)` fusionne la liste `l2` dans la liste `l` (les deux listes doivent être triées).
- `l.remove(val)` supprime tous les éléments égaux à `val`.
- `l.remove_if(pred)` supprime tous les éléments pour lesquels `pred(elem)` est vrai.
- `l.sort()` trie la liste.
- `l.sort(comp)` trie la liste avec le comparateur `comp`.
- `l.unique()` supprime les éléments consécutifs identiques.
- `l.reverse()` inverse la liste.

#### la liste doublement chaînée

Pour l'utiliser, il faut inclure le fichier d'en-tête `<list>`.

**Initialisation** :

- `std::list<int> l;` (la liste est initialisée avec 0 élément)
- `std::list<int> l = {1, 2, 3};` (initialise les trois éléments)
- `std::list l{1, 2, 3};` : le C++ (à partir de C++ 17) déduit de la liste d'initialisation que `Type = int` et réserve la place pour les 3 éléments qu'il copie.

**Services propres à la liste doublement chaînée** :

- `l.back()` retourne le dernier élément de la liste.
- `l.push_back(val)` ajoute `val` à la fin de la liste (copie).
- `l.pop_back()` supprime le dernier élément de la liste.
- `l.emplace_back(args)` insère un élément construit sur place à la fin de la liste.
- `l.emplace(pos, args)` insère un élément construit sur place à la position `pos`.

- `l.insert(pos, val)` insère `val` à la position `pos` (copie).
- `l.insert(pos, n, val)` insère `n` éléments val à la position `pos` (copie).
- `l.insert(pos, first, last)` insère les éléments de l'intervalle `[first, last)` à la position `pos` (copie).
- `l.insert(pos, il)` insère les éléments de la liste d'initialisation `il` à la position `pos` (copie).

Comme pour les tableaux, on peut également utiliser les opérateurs `==`, `!=`, `<`, `<=`, `>`, `>=` pour comparer deux listes.

Exemple d'utilisation d'une liste doublement chaînée :

```cpp
std::list<std::int64_t> primes;
primes.emplace_back(2);
if (nbPrimes > 1) primes.emplace_back(3);
std::int64_t k = 1;
while (primes.size() < nbPrimes)
{
    std::int64_t p1 = 6*k-1;
    std::int64_t p2 = 6*k+1;
    k = k + 1;
    for (auto p : primes)
    {
        if ( (p1 > 0 ) and (p1%p == 0) ) p1 = 0;
        if ( (p2 > 0 ) and (p2%p == 0) ) p2 = 0;
        if ( (p1 == 0) and (p2   == 0) ) break;
    }
    if (p1 > 0) primes.push_back(p1);
    if ( (p2 > 0) and (primes.size() < nbPrimes) ) primes.push_back(p2);
}
std::cout << "Voici les " << nbPrimes << " premiers nombres premiers :  " << std::endl;
for (auto p : primes ) std::cout << p << " ";
std::cout << std::endl;
```

#### Les listes simplement chaînées

Pour l'utiliser, il faut inclure le fichier d'en-tête `<forward_list>`.
Sa simplicité en fait un conteneur plus efficace pour les listes à accès séquentiel que la liste doublement chaînée.

**Initialisation** :

- `std::forward_list<int> l;` (la liste est initialisée avec 0 élément)
- `std::forward_list<int> l = {1, 2, 3};` (initialise les trois éléments)
- `std::forward_list l{1, 2, 3};` : le C++ (à partir de C++ 17) déduit de la liste d'initialisation que `Type = int` et réserve la place pour les 3 éléments qu'il copie.

**Services propres aux listes simplement chaînées** :

- `l.before_begin()` retourne un itérateur positionné avant le début de la liste.
- `l.cbefore_begin()` retourne un itérateur constant positionné avant le début de la liste.
- `l.emplace_after(pos, args)` insère un élément construit sur place après la position `pos`.
- `l.erase_after(pos)` supprime l'élément après la position `pos`.
- `l.erase_after(first, last)` supprime les éléments après la position `first` et avant la position `last`.
- `l.emplace_after(pos, args)` insère un élément construit sur place après la position `pos`.

On peut là aussi utiliser les opérateurs `==`, `!=`, `<`, `<=`, `>`, `>=` pour comparer deux listes simplement chaînées.

Exemple d'utilisation d'une liste simplement chaînée :

```cpp
std::forward_list<std::int64_t> primes;
primes.emplace_front(2);
if (nbPrimes > 1) primes.emplace_front(3);
std::int64_t k = 1;
std::int64_t foundPrimes = 2;
while (foundPrimes < nbPrimes)
{
    std::int64_t p1 = 6*k-1;
    std::int64_t p2 = 6*k+1;
    k = k + 1;
    for (auto p : primes)
    {
        if ( (p1 > 0 ) and (p1%p == 0) ) p1 = 0;
        if ( (p2 > 0 ) and (p2%p == 0) ) p2 = 0;
        if ( (p1 == 0) and (p2   == 0) ) break;
    }
    if (p1 > 0) 
    {
        primes.push_front(p1);
        foundPrimes ++;
    }
    if ( (p2 > 0) and (foundPrimes < nbPrimes) ) 
    {
        primes.push_front(p2);
        foundPrimes ++;
    }
}
std::cout << "Voici les " << nbPrimes << " premiers nombres premiers : " << std::endl;
for (auto p : primes ) std::cout << p << " ";
std::cout << std::endl;
```

### Les dictionnaires

Deux types de dictionnaires existent en C++ :

- `std::map<Key, T>` : dictionnaire où les éléments sont associés à des clés de type `Key` qui possèdent un ordre naturel et dont les éléments sont de type `T`.
  - Pour l'utiliser, il faut inclure le fichier d'en-tête `<map>`.
  - Insérer une valeur est en `O(log(n))`
  - Accéder à une valeur est en `O(log(n))`.
- `std::unordered_map<Key, T>` : dictionnaire où les éléments de type `T` sont associés à des clés de type `Key` qui sont hashables et dont les éléments sont sans ordre particulier.
  - Pour l'utiliser, il faut inclure le fichier d'en-tête `<unordered_map>`.
  - Insérer une valeur est en `O(1)` en moyenne.
  - Accéder à une valeur est en `O(1)` en moyenne.

Si les deux dictionnaires proposent des fonctionnalités similaires, il faut remarquer que le `std::unordered_map` est bien plus efficace en termes de temps d'exécution mais demande des clefs que l'on puisse hasher.

Exemple d'utilisation d'un dictionnaire :

```cpp
std::map<std::string,std::int32_t> badges = { {"John", 12304}, {"Eric", 3204}, {"Mathew", 1320} };
badges["Paul"] = 14503;
auto iter = badges.find("Marie");
if (iter == badges.end())
    std::cout << "Marie n'existe pas" << std::endl;
else
    std::cout << "Le badge de Marie est le " << iter->second << std::endl;
iter = badges.find("Eric");
if (iter == badges.end())
    std::cout << "Eric n'existe pas" << std::endl;
else
    std::cout << "Le badge d'Eric est le " << iter->second << std::endl;
for (auto const& values : badges )
    std::cout << values.first << " a pour badge " << values.second << std::endl;
```

### Les ensembles (A faire)