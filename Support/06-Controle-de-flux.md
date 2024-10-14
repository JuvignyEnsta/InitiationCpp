# Les instructions de contrôle de flux

## Branchements conditionnels

### Instructions ```if```, ```else if``` et ```else```

En C/C++, les instructions de branchements conditionnels sont réalisées avec les instructions ```if```, ```else if``` et ```else``` :

```cpp
if (condition) {
    // instructions
} else if (condition) {
    // instructions
} else {
    // instructions
}
```

Les conditions sont obligatoirement exprimées entre parenthèses. Si la condition est composée de plusieurs expressions, elles doivent être reliées par des opérateurs logiques, chaque condition étant elle-même entre parenthèses.

Les opérations logiques usuelles sont :

- ```&&``` pour l'opérateur logique "et"
- ```||``` pour l'opérateur logique "ou"
- ```!``` pour l'opérateur logique "non"

Par exemple, si on veut tester si un entier i est impair et divisible par trois, on le divisera par trois et sinon on retranchera un à cet entier :

```cpp
if (i % 3 == 0) 
{
    i /= 3;
} 
else 
{
    i -= 1;
}
```

Bien que déconseillé, il est possible d'omettre les accolades si l'on ne fait qu'une seule instruction dans le bloc conditionnel :

```cpp
if (i % 3 == 0) i /= 3; else i -= 1;
```

Dans les cas simples comme celui-ci, il est préférable pour des raisons de lisibilité et d'efficacité d'utiliser l'opérateur ternaire ```(condition ? expr1 : expr2)``` qui renvoie ```expr1``` si la condition est vraie et ```expr2``` sinon :

```cpp
i = (i % 3 == 0) ? i / 3 : i - 1;
```

qui est équivalent à l'exemple précédent.

### Sélecteurs ```switch``` et ```case```

Lorsqu'on veut chaîner plusieurs conditions, on peut simplifier le code avec l'instruction ```switch``` dont la syntaxe est la suivante :

```cpp
switch (var) {
    case val1:
        // instructions
        break;
    case val2:
        // instructions
        break;
    ...
    default:
        // instructions
}
```

La variable ```var``` est évaluée une seule fois et comparée à chaque ```case```. Si une valeur ```case``` correspond à la valeur de ```var```, les instructions associées sont exécutées. Si aucune valeur ```case``` ne correspond à la valeur de ```var```, les instructions associées au ```default``` sont exécutées.

Le mot-clé ```break``` est nécessaire à la fin de chaque ```case``` pour éviter les "chutes" (fallthrough) dans les instructions associées aux autres ```case``` sauf si cela est intentionnel.

Par exemple, supposons qu'une variable entière ```imenu``` représente la sélection d'une opération dans un menu et qu'on veuille effectuer une opération différente en fonction de la valeur de ```imenu``` :

```cpp
switch (imenu) {
    case 1:
        // instructions
        break;
    case 2:
        // instructions
        break;
    ...
    default:
        std::cerr << "Opération inconnue" << std::endl;
}   
```

## Les boucles

### La boucle ```for```

La boucle ```for``` est la plus couramment utilisée en C/C++. Sa syntaxe est la suivante :

```cpp
for (init ; condition ; increment) 
{
    // instructions
}
```

La variable à initialiser peut soit être déclarée dans la boucle ```for``` soit être une variable déjà déclarée en dehors de la boucle. L'initialisation est optionnelle.

La condition est optionnelle et si elle est omise, elle est considérée comme toujours vraie. La boucle se répéte tant que la condition est vraie.

L'incrément est optionnel mais si présent, il doit permettre à la condition d'être fausse à un moment donné pour que la boucle puisse se terminer.

Exemple simple de parcours d'un tableau :

```cpp
int tab[] = {1, 2, 3, 4, 5};
for (int i = 0; i < 5; i++) {
    std::cout << tab[i] << std::endl;
}
```

La condition et l'incrément peuvent être des expressions quelconques. Par exemple, pour rechercher le premier bit non nul d'un entier ```n``` (de droite à gauche), on pourra écrire :

```cpp
int bit;
for (bit = 0; (n & (1 << bit)) == 0; bit++);
```

Dans l'exemple précédent, l'instruction ```(1 << bit)``` décale le bit 1 de ```bit``` positions vers la gauche. L'opérateur ```&``` appliqué à ```n``` et à ```(1 << bit)``` permet de tester si le bit numéro ```bit``` de ```n``` est nul ou non.

Voici une illustration du décalage de bit à gauche de la valeur 1 :

```raw
00000000 00000000 00000000 00000001  (1<<0) => 1
00000000 00000000 00000000 00000010  (1<<1) => 2
00000000 00000000 00000000 00000100  (1<<2) => 4
00000000 00000000 00000000 00001000  (1<<3) => 8
...
```

Remarquons que le bloc d'instructions associé à la boucle ```for``` peut être vide.

Voici un autre exemple de boucle ```for``` non trivial qui permet de calculer la puissance n-ième d'un nombre entier :

```cpp
int res;     // résultat
int x = ...; // valeur à élever à la puissance n
int n = ...; // exposant
for (res = 1; n > 0; n--) res *= x;
```

Au sein d'une boucle ```for```, on peut utiliser les instructions de saut ```continue``` et ```break```:

- ```continue``` permet de sauter le reste de la boucle et de passer à l'itération suivante.
- ```break``` permet de sortir de la boucle.

Par exemple, pour tester si un nombre est premier, on pourra écrire :

```cpp
bool est_premier = (n%2 == 0) ? false : (n%3 == 0) ? false : true;
for (int i=1; (6*i-1 < std::sqrt(n)) && est_premier; ++i)
{
    if (n%(6*i-1) == 0)
    {
        est_premier = false;
        break;
    }
    if (n%(6*i+1) == 0) est_premier = false;
}
```

Rermarque : il est tout à fait autorisé d'enchaîner les opérateurs ternaires en C/C++.

Nous verrons un autre syntaxe de boucle utilisant l'instruction ```for``` lorsqu'on utilisera des conteneurs.

### La boucle ```while```

La boucle ```while``` en C++ permet d'exécuter un bloc d'instructions tant qu'une condition est vraie. Sa syntaxe est la suivante :

```cpp
while (condition) {
    // instructions
}
```

Si la condition est fausse à l'entrée dans la boucle, le bloc d'instructions associé à la boucle ```while``` n'est pas exécuté.

Exemple d'une boucle while qui itère sur la suite de syracuse en démarrant à un entier n valant 7 :

```cpp
int n = 7;
while (n != 1) 
{
    std::cout << n << std::endl;
    n = (n%2 == 0) ? n/2 : 3*n+1;
}
```

### La boucle ```do while```

La boucle ```do while``` est semblable à la boucle ```while``` mais la condition est évaluée après l'exécution du bloc d'instructions. Sa syntaxe est la suivante :

```cpp
do {
    // instructions
} while (condition);
```

La condition est évaluée après l'exécution du bloc d'instructions, la boucle est donc exécutée au moins une fois.

Exemple demandant un choix à l'utilisateur jusqu'à ce que la valeur choisie soit entre 1 et 5 :

```cpp
int choix;
do 
{
    std::cout << "Choix : "; 
    std::cin.clear(); // Permet d'effacer un reliquat d'input précédent
    std::cin >> choix;
} while (choix < 1 || choix > 5);
```

Pour les deux formes de boucles ```while``` et ```do while```, il est possible d'utiliser les instructions de saut ```continue``` et ```break```. De plus, il est possible de mettre pour condition la valeur ```true``` pour une boucle infinie.

