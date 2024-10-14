# Gestion des erreurs

## Les assertions

Nous avons déjà vu les assertions dans le chapître consacré aux contrats des fonctions. 

De manière générale, les assertions peuvent servir pour détecter des erreurs de programmation mais elles ne permettent pas de gérer des erreurs qui interviennent lors de l'exécution du programme et qui ne sont pas dues à des erreurs de programmation (disque dur plein, etc.).

## Stratégie de gestion des erreurs

La gestion des erreurs doit être considérée en amont de la conception du programme lors de la phase de spécification, au moment de l'élaboration des différents scénarios d'utilisation du programme.

On doit à ce moment là se poser les questions suivantes :

- Quelles sont les erreurs pouvant survenir et quelles sont leurs causes ?
- Pour chaque erreur, quelles sont les conséquences de cette erreur (pour l'utilisateur, pour le programme) ? Doit-on arrêter le programme ou tenter de le récupérer ? Afficher un simple message d'erreur ou un message plus complet ?
- Comment gérer ces erreurs dans le code ? Comment remonter un erreur d'une fonction à la fonction appelante ? etc.

Comme en C, il est possible de gérer à la main les erreurs en renvoyant des codes d'erreur sous forme d'entier. Cependant il n'est pas possible de retourner un code d'erreur dans certains cas :

- Lors de la construction d'un objet (voir la programmation objet)
- Lors de l'utilisation d'une surcharge d'opérateur

De plus, la gestion des codes d'erreurs est assez lourde :

- Mettre en place un mécanisme pour remonter les erreurs
- S'assurer que chaque erreur à un code différent
- Associer un message à chaque code d'erreur

C'est pourquoi, en C++, on a introduit un mécanisme de gestion des erreurs basé sur les exceptions.

Cependant, **attention**, la gestion des erreurs à l'aide des exceptions ne règle pas tous les problèmes de conception.

## Les exceptions

Comme leurs noms l'indiquent, les exceptions sont des événements **exceptionnels** qui doivent être gérés par le programme.

Le principe de fonctionnement des exceptions est le suivant :

- Lorsqu'une erreur survient, l'exécution du programme est interrompue et une exception est levée (émission d'une erreur).
- L'exception est ensuite gérée par une fonction appelante qui peut choisir de la capturer et de la traiter.
- Si l'exception n'est pas capturée, elle est propagée à la fonction appelante jusqu'à ce qu'elle soit interceptée ou si elle n'est pas interceptée, le programme se termine.

**Exemple de situation où une exception peut être levée :**

| Type d'erreur | Traitement possible |
| -------------- | ------------------- |
| Disque dur plein | Sauvegarder sur un disque dur auxiliaire |
| Impossible d'accéder à un serveur | tenter de se connecter à un serveur miroir. Si échec, on affiche un message et on arrête le programme |
| Erreur matérielle d'un périphérique | Impossible de rattraper. On affiche un message et on arrête le programme |

Lorsqu'une exception est levée, le type de l'erreur peut aller du simple entier, de la chaîne de caractères jusqu'à des objets plus complexes comme des valeurs de type `std::exception`.

Il existe déjà plusieurs types d'exceptions déjà prédéfinis dans la bibliothèque standard comme `std::runtime_error` ou `std::logic_error` qu'on trouve dans l'en-tête `<stdexcept>`.

### Mise en oeuvre des exceptions en C++

- On utilise le mot clé `throw` pour lever une exception
- On utilise le mot clé `try` pour délimiter le bloc de code où sera interceptée l'exception
- On utilise le mot clé `catch` pour intercepter un type d'exception et pour définir la gestion de cette exception
- Plusieurs `catch` peuvent être utilisés pour gérer différents types d'exceptions
- Une fois une exception interceptée et traitée, le programme continue son exécution.

**Exemple :**

```cpp
// Fonction émettant l'exception
std::complex<double> green(double k, double r)
{
if (r <= 1.E-10 ) throw "Distance trop petite"s;
return std::polar(1./r, k*r);
}

// Partie du code traitant l'exception émise par la fonction green
try {
    double r = std::sqrt(x*x + y*y + z*z);
    auto kernel = green(k, r);
}
catch(std::string& err ) {
    std::cerr << "Impossible de calculer le noyau. Raison : " << err << std::endl;
    throw err;
}
```

### Les exceptions standards

La composante standard de C++ propose un ensemble d'exceptions qui sont définies la plupart dans l'en-tête `<stdexcept>` :

- `std::exception` : classe de base de toutes les exceptions
- `std::runtime_error` : exception levée lors d'une erreur de programmation
- `std::logic_error` : exception levée lors d'une erreur logique
- `std::bad_alloc` : exception levée lors d'une erreur d'allocation de mémoire
- `std::bad_cast` : exception levée lors d'un problème lors d'un cast
- `std::bad_typeid` : exception levée lors d'un problème lors de l'utilisation de l'opérateur `typeid`
- `std::out_of_range` : exception levée lors d'un accès à une collection en dehors des limites de cette collection
- `std::overflow_error` : exception levée lors d'un dépassement de capacité
- `std::underflow_error` : exception levée lors d'un dépassement de capacité en dessous de 0
- `std::domain_error` : exception levée lorsqu'une fonction mathématique est appliquée à un domaine invalide
- `std::length_error` : exception levée lorsqu'une condition de longueur est violée
- `std::invalid_argument` : exception levée lorsqu'une fonction reçoit un argument invalide
- `std::out_of_bounds` : exception levée lorsqu'un accès à une collection est en dehors des limites de cette collection

Puisque toutes les exceptions ci-dessus héritent de `std::exception`, elles peuvent toutes être interceptées par un bloc `catch(std::exception& e)` qui est un bloc générique capturant n'importe quelle exception (pour la notion d'héritage, voir la programmation objet).

Lors de l'émission d'une de ces exceptions, l'objet `e` encapsule un message d'erreur qui peut être récupéré grâce à la méthode `what()` retournant une chaîne de caractères. Ce message est défini lors de l'instanciation de l'exception.

**Exemple :**

```cpp
// Fonction émettant des exceptions
std::complex<double> green(double k, double r) {
    if (k <= 0)
        throw std::range_error("k doit etre positif");
    if (r <= 1.E-10 )
        throw std::domain_error("Rayon trop petit");
    return std::polar(1./r, k*r);
}
...
// Partie du code traitant les exceptions émises par la fonction green
try {
    double r = std::sqrt(x*x + y*y + z*z);
    auto kernel = green(k, r);
}
catch(std::domain_error& err ) {
    std::cerr << "Erreur domaine de définition :" << err.what() << std::endl;
}
catch(std::exception& err ) {
    std::cerr << "Erreur calcul noyau :" << err.what() << std::endl;
}
```

## Bonnes et mauvaises pratiques des exceptions

Le mécanisme des exceptions est très puissant mais il faut l'utiliser avec parcimonie car ce mécanisme est coûteux en temps d'exécution.

Comme son nom l'indique, les exceptions sont des événements exceptionnels et doivent être utilisées pour des situations exceptionnelles.

Puisqu'elles sont coûteuses en temps d'exécution, il faut éviter de les utiliser au sein d'une boucle ou d'une partie critique en temps d'exécution du programme.

**Exemple à éviter :**

```cpp
for (int i = 0; i < n; ++i) {
    try {
        // Code à risque
    }
    catch (std::exception& e) {
        std::cerr << "Erreur : " << e.what() << std::endl;
    }
}
```

**Exemple à privilégier :**

```cpp
try {
    for (int i = 0; i < n; ++i) {
        // Code à risque
    }
}
catch (std::exception& e) {
    std::cerr << "Erreur : " << e.what() << std::endl;
}
```

