# Programmation orientée objet


## Introduction à la programmation orientée objet

La programmation orientée objet (POO) est un paradigme de programmation qui a révolutionné le développement logiciel depuis son émergence dans les années 1960. Cette approche de programmation est basée sur le concept d'"objets", qui sont des entités contenant des données et du code. L'idée fondamentale est de structurer les programmes autour de ces objets plutôt que de les organiser comme une séquence d'instructions ou de fonctions.

### Historique de la POO

L'histoire de la POO remonte aux années 1960 avec le langage Simula, développé par Ole-Johan Dahl et Kristen Nygaard. Simula a introduit les concepts de classes et d'objets, posant ainsi les bases de la POO. Cependant, c'est dans les années 1970 que la POO a vraiment pris son essor avec le développement de Smalltalk par Alan Kay et son équipe à Xerox PARC. Smalltalk a popularisé de nombreux concepts clés de la POO, tels que l'encapsulation, l'héritage et le polymorphisme.

Dans les années 1980 et 1990, la POO a gagné en popularité avec l'émergence de langages comme C++ (une extension orientée objet du C) et Java. Ces langages ont contribué à répandre l'utilisation de la POO dans l'industrie du logiciel. Aujourd'hui, de nombreux langages modernes, tels que Python, Ruby, C#, et bien sûr C++, supportent la programmation orientée objet.

### Intérêts de la POO

La programmation orientée objet présente plusieurs avantages significatifs :

1. **Modularité** : La POO permet de diviser un programme en modules indépendants (les objets), ce qui facilite la gestion de projets complexes.

2. **Réutilisabilité** : Les classes et les objets peuvent être réutilisés dans différents programmes, ce qui permet d'économiser du temps et des efforts de développement.

3. **Flexibilité et extensibilité** : Grâce à l'héritage et au polymorphisme, il est facile d'étendre et de modifier les fonctionnalités existantes sans affecter le code existant.

4. **Encapsulation** : La POO permet de cacher les détails internes de l'implémentation, ce qui améliore la sécurité et réduit la complexité pour l'utilisateur de la classe.

5. **Maintenance facilitée** : La structure modulaire et l'encapsulation rendent le code plus facile à comprendre, à déboguer et à maintenir.

6. **Modélisation du monde réel** : La POO permet de modéliser des systèmes complexes de manière plus naturelle, en représentant les entités du monde réel comme des objets avec leurs propres attributs et comportements.

7. **Abstraction** : La POO permet de créer des représentations abstraites de concepts, ce qui facilite la gestion de la complexité dans les grands systèmes.

En conclusion, la programmation orientée objet est devenue un paradigme fondamental dans le développement logiciel moderne. Elle offre une approche puissante et flexible pour concevoir et implémenter des systèmes complexes, tout en favorisant la création de code plus propre, plus maintenable et plus réutilisable. Dans le contexte du C++, la POO est un outil essentiel qui permet aux développeurs de tirer pleinement parti de la puissance et de la flexibilité du langage.


## Limites et problèmes potentiels de la POO

Bien que la programmation orientée objet (POO) offre de nombreux avantages, elle présente également certaines limites et peut poser des problèmes dans certains contextes. Voici quelques-unes des principales critiques et difficultés associées à la POO :

### Modélisation inadaptée pour certains problèmes

1. **Problèmes naturellement fonctionnels** : La POO peut s'avérer mal adaptée pour modéliser des problèmes qui sont intrinsèquement fonctionnels. Par exemple, les algorithmes mathématiques complexes ou les transformations de données pures sont souvent plus naturellement et efficacement exprimés dans un paradigme fonctionnel.

2. **Surmodélisation** : Il y a un risque de créer des hiérarchies de classes trop complexes pour des problèmes simples, ce qui peut conduire à une "sur-ingénierie" du code.

### Problèmes d'optimisation et de performance

1. **Overhead mémoire** : Les objets peuvent consommer plus de mémoire que nécessaire en raison de l'encapsulation et des métadonnées associées aux classes.

2. **Coût des appels de méthodes virtuelles** : Dans les langages comme C++, les appels de méthodes virtuelles peuvent introduire un léger surcoût en termes de performance.

3. **Antagonisme avec les architectures multi-cœurs** : Comme l'a souligné Scott Meyers, expert en C++, la POO peut être en conflit avec les architectures modernes multi-cœurs :

   - **Localité des données** : Les objets encapsulent les données, ce qui peut nuire à la localité des données et réduire l'efficacité des caches CPU.

   - **Parallélisme** : Les objets mutables avec état interne peuvent compliquer la parallélisation du code, nécessitant des mécanismes de synchronisation complexes.

4. **Inefficacité des caches** : La dispersion des données liée à l'encapsulation peut conduire à une utilisation sous-optimale des caches CPU, réduisant les performances globales.

### Complexité et maintenabilité

1. **Couplage** : Une mauvaise conception peut conduire à un couplage fort entre les classes, rendant le système difficile à modifier et à maintenir.

2. **Courbe d'apprentissage** : La POO introduit de nombreux concepts abstraits qui peuvent être difficiles à maîtriser pour les débutants.

3. **Difficulté de refactoring** : Les hiérarchies de classes complexes peuvent être difficiles à refactoriser sans introduire de régressions.

### Alternatives et approches complémentaires

Face à ces limitations, plusieurs approches alternatives ou complémentaires ont émergé :

1. **Programmation fonctionnelle** : Favorise l'immutabilité et les fonctions pures, ce qui peut faciliter la parallélisation et l'optimisation.

2. **Programmation orientée données** : Se concentre sur l'organisation des données pour une meilleure efficacité mémoire et une meilleure utilisation des caches.

3. **Programmation générique** : Permet une abstraction sans le coût runtime de la POO, particulièrement utile en C++ avec les templates.

4. **Approches hybrides** : Combinent différents paradigmes pour tirer le meilleur parti de chacun selon le contexte.

En conclusion, bien que la POO reste un paradigme puissant et largement utilisé, il est important de reconnaître ses limites et de choisir l'approche la plus appropriée en fonction du problème à résoudre et des contraintes du système.

## Étapes pour construire un code orienté objet

La construction d'un code orienté objet nécessite une approche méthodique. Voici les principales étapes à suivre :

1. **Analyse du problème**
   - Identifiez clairement le problème à résoudre
   - Définissez les exigences fonctionnelles et non-fonctionnelles

2. **Identification des objets et des classes**
   - Listez les entités principales du domaine du problème
   - Regroupez ces entités en classes potentielles

3. **Définition des attributs et des méthodes**
   - Pour chaque classe, déterminez :
     - Les attributs (données) qu'elle doit contenir
     - Les méthodes (comportements) qu'elle doit implémenter

4. **Établissement des relations entre les classes**
   - Identifiez les relations d'héritage, de composition, d'agrégation, etc.
   - Créez un diagramme de classes pour visualiser ces relations

5. **Conception de l'interface des classes**
   - Définissez les signatures des méthodes publiques
   - Appliquez le principe d'encapsulation en décidant ce qui doit être public, protégé ou privé

6. **Implémentation des classes**
   - Codez les classes une par une
   - Commencez par les classes de base avant de passer aux classes dérivées

7. **Création des objets et écriture du code client**
   - Instanciez les objets nécessaires
   - Écrivez le code qui utilise ces objets pour résoudre le problème

8. **Tests et débogage**
   - Testez chaque classe individuellement (tests unitaires)
   - Testez les interactions entre les classes (tests d'intégration)

9. **Refactoring et optimisation**
   - Identifiez les parties du code qui peuvent être améliorées
   - Appliquez les principes SOLID et les design patterns si nécessaire

10. **Documentation**
    - Documentez le code, les classes et leurs interactions
    - Créez un guide d'utilisation si nécessaire

En suivant ces étapes, vous pouvez construire un code orienté objet solide et maintenable. N'oubliez pas que ce processus est souvent itératif, et il peut être nécessaire de revenir à des étapes précédentes au fur et à mesure que votre compréhension du problème s'approfondit.


## Définition d'une classe en C++

En C++, une classe est définie à l'aide du mot-clé `class`.

Voici un exemple de la déclaration d'une classe simple en C++ et de son utilisation :

```cpp
class Vecteur // Nom de la classe
{// Début de la définition de la classe
public: // Section accessible publiquement
    // Constructeurs
    Vecteur() = default; // Constructeur par défaut
    void set_as_point(); // Méthode publique

    double x, y, z; // Attributs publics
private:
    bool is_point() const; // Méthode privée
    double w; // Attribut privé
}; // Fin de la définition de la classe
...
Vecteur u; // Instanciation d'un objet de type Vecteur
u.x = 3.0; // Accès à l'attribut public x de l'objet u
u.y = 4.0; // Accès à l'attribut public y de l'objet u
u.z = 5.0; // Accès à l'attribut public z de l'objet u
u.set_as_point(); // Appel de la méthode publique set_as_point de l'objet u
```

Le mot-clé `public:` définit la section accessible publiquement de la classe. Les membres déclarés dans cette section sont accessibles depuis n'importe quel code pouvant accéder à l'objet.

Le mot-clé `private:` définit la section accessible en privé de la classe. Les membres déclarés dans cette section ne sont accessibles qu'à partir des méthodes de la classe.

### Les constructeurs

Le constructeur par défaut `Vecteur() = default;` est un constructeur sans paramètre qui est généré automatiquement par le compilateur si aucun constructeur n'est défini par l'utilisateur. Il permet par défaut à réserver la mémoire nécessaire pour l'objet mais ne fait rien d'autre.

Les constructeurs sont des méthodes spéciales de la classe qui ont le même nom que la classe et qui sont appelés automatiquement lors de la création de l'objet selon les paramètres passés.

Reprenons l'exemple précédent et ajoutons plusieurs constructeurs :

```cpp
class Vecteur
{
public:
    Vecteur() = default; // Constructeur par défaut
    Vecteur(double cx, double cy, double cz); // Constructeur avec paramètres
    Vecteur(std::initializer_list<double> lst); // Constructeur avec liste d'initialisation
    Vecteur(double cx); // Constructeur avec un seul paramètre pour x
    Vecteur(const Vecteur& other); // Constructeur par copie
    Vecteur(Vecteur&& other); // Constructeur par déplacement
    // et d'autres constructeurs si on en a besoin. 
    //Note : il est interdit de définir plusieurs constructeurs avec les mêmes paramètres.
};
```

Ces différents constructeurs permettent de créer un objet `Vecteur` de différentes manières :

- Sans aucun paramètre
- Avec 3 paramètres
- Avec une liste d'initialisation
- Avec un seul paramètre pour x
- Par copie d'un autre vecteur

Exemple :

```cpp
Vecteur u(1.0, 2.0, 3.0); // Utilisation du constructeur avec 3 paramètres
Vecteur v = {4.0, 5.0, 6.0}; // Utilisation du constructeur avec liste d'initialisation
Vecteur w(v); // Utilisation du constructeur par copie
Vecteur z = u; // Utilisation du constructeur par copie (équivalent à Vecteur z(u);)
Vecteur t = std::move(u); // Utilisation du constructeur par déplacement
```

### Règles d'utilisation des constructeurs

- Un constructeur par défaut est défini si aucun constructeur n'est défini par l'utilisateur. Il consiste à réserver la mémoire nécessaire pour l'objet mais ne fait rien d'autre.
- Un constructeur de copie par défaut est défini si aucun constructeur par copie ou déplacement est défini. Il fait une copie bit à bit de l'objet passé en paramètre.
- Si la classe contient un attribut non copiable, le constructeur de copie par défaut n'est pas défini.

Notons que depuis le C++ 11, il est possible d'appeler un constructeur depuis un autre constructeur.

**Conseil de programmation** : Il est préférable de définir un constructeur par défaut, un constructeur de copie et un constructeur par déplacement, quitte à les déclarer `default` ou `delete` (voir plus loin).

### Constructeurs par défaut et supprimés

Les seuls constructeurs pouvant être définis par défaut ou suppriméssont le constructeur par défaut, le constructeur de copie et le constructeur par déplacement.

Pour déclarer un constructeur par défaut ou supprimé, on rajoute `= default` ou `= delete` respectivement.

Le comportement d'un constructeur déclaré par défaut dépend du constructeur qu'il remplace :

- Si c'est le constructeur par défaut, il ne fera que réserver la mémoire nécessaire pour l'objet et initialiser les attributs dont on a définit une valeur par défaut.

- Si c'est le constructeur de copie, il fera une copie membre à membre de l'objet passé en paramètre.

- Si c'est le constructeur par déplacement, il fera un déplacement membre à membre de l'objet passé en paramètre.

Un constructeur supprimé ne peut être appelé sous aucune forme.

### Mise en oeuvre d'un constructeur

Un constructeur peut être défini soit en ligne dans la déclaration de la classe, soit en dehors de la déclaration de la classe.

On déclarera donc la classe et ses constructeurs dans le fichier `.h` ou `.hpp` et on définira le corps des constructeurs dans le fichier `.cpp`.

Ainsi, pour reprendre l'exemple précédent, on déclarera la classe dans le fichier `.hpp` et on définira le corps des constructeurs dans le fichier `.cpp`.

Dans le fichier `vecteur.hpp` :

```cpp
class Vecteur
{
public:
    Vecteur() = default;
    // Déclaration et mise en oeuvre du constructeur avec liste d'initialisation en ligne
    Vecteur(std::initializer_list<double> lst) : m_data{lst} {}
    Vecteur(double cx, double cy, double cz); // Seulement la déclaration
private:
    std::array<double, 3> m_data;
};
```

Dans le fichier `vecteur.cpp` :

```cpp
#include "vecteur.hpp"

Vecteur::Vecteur(double cx, double cy, double cz) : m_data{} 
{
    m_data[0] = cx;
    m_data[1] = cy;
    m_data[2] = cz;
}
```

### Mise en oeuvre des constructeurs de copie et de déplacement

Si les constructeurs de copie ou de déplacement par défaut ne conviennent pas (ce qui n'arrive presque jamais en pratique), il est possible de les définir pour une classe donnée.

Par exemple, imaginons que nous voulons compter le nombre d'objets de type `Vecteur` instanciés (créés) :

```cpp
int nb_vecteurs{0};

class Vecteur
{
public:
    Vecteur()
    { ++nb_vecteurs; }
    ...
    Vecteur( Vecteur const& u );
    // Pour le constructeur par déplacement, on peut prendre la mise en oeuvre par défaut
    Vecteur( Vecteur&& u ) = default;
    ...
private:
    std::array<double,3> m_data;
};
...
Vecteur::Vecteur( Vecteur const& u ) : m_data{u.m_data}
{
    ++ nb_vecteurs;
}
```

### Le destructeur

Un destructeur est une méthode spéciale de la classe qui est appelée automatiquement lors de la destruction de l'objet. Elle peut être déclarée `= default` mais pas `= delete` (Le destructeur doit toujours exister pour toutes les classes). Dans ce cas, le destructeur par défaut se contente d'appeler le destructeur de chacun des membres de l'objet.

De même, un seul destructeur est définie par classe. Le destructeur ne possède aucun paramètre et ne retourne rien. Il se distingue des constructeurs par le fait qu'il est précédé par le symbole `~`.

En pratique, il est très rare de redéfinir le destructeur sauf si on doit libérer des ressources qui ne sont pas contrôler par le c++, comme supprimer une connection avec un serveur ou un appareil de mesure.

### Gestion des exceptions dans les constructeurs

Lorsqu'on veut rattraper une exception dans un constructeur, il faut encapsuler le corps du constructeur dans un bloc try-catch :

Par exemple :

```cpp
class Matrix
{
public:
    ...
    Matrix( int nrows, int ncols );
    ...
private:
    std::vector<double> m_data;
};
...
Matrix::Matrix( int nrows, int ncols ) try 
    : m_data( nrows * ncols )
{
    ...
}
catch( std::bad_alloc& e )
{
    ...
    throw std::bad_alloc(err.what());
}
```

Néanmoins, rattraper une exception dans un constructeur n'est pas très utile, car on ne pourra que la reinterprété et la propager.

Notons que l'objet est considéré comme ne pas exister durant le traitement de l'exception, on ne peut donc pas utiliser l'objet dans le bloc catch. En fait, l'objet n'existe que si le constructeur s'achève normalement.

Du coup, comment faire si on veut rattraper une exception émise par un membre qui peut être optionel de l'objet ?

Il faut dans ce cas utilise l'idiome Pimpl (Pointer to IMPLementation) : on déclare un pointeur sur l'implémentation privée de la classe dans la classe publique et on alloue l'implémentation dans le constructeur.

Par exemple, imaginons que nous voulons créer un capteur de pression et de température qui peut aussi posséder d'autres capteurs optionnels(de déplacement, de vitesse, etc...) :

Dans le fichier `CapteurPression.hpp` :

```cpp
class CapteurPression
{
public:
    CapteurPression();
    ...
private:
    PressureSensor m_pressure;
    ThermalSensor  m_thermal ;
    class OptionalSensors;
    std::unique_ptr<OptionalSensors> m_ptr_optional;
};
```

La classe OptionalSensors sera définie dans un fichier `OptionalSensors.cpp` et sera invisible de l'extérieur de la classe `CapteurPression`. Un pointeur sur une classe qui n'est que déclarée est appelée un pointeur opaque.

Dans le fichier `CapteurPression.cpp` :

```cpp
#include "CapteurPression.hpp"

class CapteurPression::OptionalSensors
{
public:
    Clock m_clock;
    HydroSensor m_hydro;
};
...
CapteurPression::CapteurPression() : m_ptr_optional{nullptr}
{
    // Puisque le pointeur est déjà initialisé à nullptr, on peut se permettre un try catch interne pour la création de l'objet OptionalSensors
    try
    {
        m_ptr_optional = std::make_unique<OptionalSensors>();
    }
    catch(...)
    {
        m_ptr_optional.reset();
        throw;
    }
}
```

## Les méthodes

Les méthodes en C++ sont des fonctions membres d'une classe. Elles définissent le comportement et les opérations que les objets de cette classe peuvent effectuer. Voici quelques points clés sur les méthodes en C++ :

1. Déclaration : Les méthodes sont déclarées à l'intérieur de la définition de la classe.

2. Définition : Elles peuvent être définies soit à l'intérieur de la classe, soit à l'extérieur en utilisant l'opérateur de résolution de portée (`::`).

3. Accès aux membres : Les méthodes ont accès à tous les membres de la classe, y compris les membres privés.

4. Types de méthodes : Il existe différents types de méthodes, comme les constructeurs, les destructeurs, les accesseurs (getters), les mutateurs (setters), et les méthodes ordinaires.

5. Méthodes const : Les méthodes déclarées const ne peuvent pas modifier l'état de l'objet.

6. Méthodes statiques : Elles appartiennent à la classe plutôt qu'à une instance spécifique et peuvent être appelées sans créer un objet de la classe.

Les méthodes sont essentielles dans la programmation orientée objet car elles encapsulent le comportement des objets et permettent l'interaction avec les données membres de la classe de manière contrôlée.

Lors de la mise en oeuvre d'une méthode, l'accès aux membres et autres méthode de la classe peut se faire au travers du pointeur `this` qui est passé automatiquement à la méthode et pointe sur l'objet pour lequel la méthode a été appelée.

Par exemple, pour reprendre l'exemple précédent, on pourrait écrire une méthode qui normalise un vecteur :

```cpp
class Vecteur
{
public:
    ...
    double normalize(); // Normalise et renvoie l'ancienne norme du vecteur
    ...
};
...
double Vecteur::normalize()
{
    double norme = std::sqrt(m_valeurs[0] * m_valeurs[0] + m_valeurs[1] * m_valeurs[1] + m_valeurs[2] * m_valeurs[2]);
    m_valeurs[0] /= norme;
    m_valeurs[1] /= norme;
    m_valeurs[2] /= norme;
    return norme;
}
...
Vecteur u;
...
double n = u.normalize(); // Appel de la méthode normalize pour l'objet u
```

### Les méthodes utilisables par les objets constants

Les méthodes déclarées `const` ne peuvent modifier aucun membre de l'objet. Elles peuvent donc être appelées par des objets constants.

Rajouter un `const` à la fin de la déclaration de la méthode permet de garantir que l'objet ne sera pas modifié par la méthode.

Si néanmoins on souhaite qu'une méthode constante puisse modifier un membre (qui ne sera pas visible de l'extérieur de la classe), on peut utiliser le mot clé `mutable`.

Exemple où on utilise un proxy pour calculer la norme d'un vecteur :

```cpp
class Vecteur
{
public:
    ...
    double norme() const;
    ...
private:
    std::array<double, 3> m_valeurs;
    mutable double m_norme{-1};// Conserve la norme calculée. 
    //Si on modifie un coefficient du vecteur, la norme n'est plus
    //valide et doit être recalculée (on remet m_norme à -1)
};
...
double Vecteur::norme() const
{
    if (m_norme == -1)
        m_norme = std::sqrt(m_valeurs[0] * m_valeurs[0] + m_valeurs[1] * m_valeurs[1] + m_valeurs[2] * m_valeurs[2]);
    return m_norme;
}
```

### Les opérateurs

Il est possible de définir des opérateurs pour les objets de la classe. Cela permet de redéfinir le comportement des opérateurs usuels pour les objets de la classe.

Pour cela, il faut définir une méthode de la classe qui sera appelée lors d'une opération utilisant l'opérateur.

Par exemple, pour reprendre l'exemple précédent, on pourrait définir l'opérateur `+=` pour l'objet `Vecteur` :

```cpp
class Vecteur
{
public:
    ...
    Vecteur& operator+=(Vecteur const& u);
    ...
};
...
Vecteur& Vecteur::operator+=(Vecteur const& u)
{
    for (int i = 0; i < 3; ++i)
        m_valeurs[i] += u.m_valeurs[i];
    return *this;
}
...
Vecteur u, v;
...
u += v; // Appel de l'opérateur +=  
```

Notons deux choses sur le code précédent :

1. La méthode retourne un pointeur sur l'objet courant (`*this`) pour permettre les opérations en chaîne.

2. L'opérateur `+=` n'attends qu'un seul paramètre, celui à droite de l'opérateur, celui de gauche étant l'objet courant.

Lorsqu'on définit un opérateur unaire, on ne définit aucun paramètre, l'objet sur lequel on applique l'opérateur étant accessible via `this`.

Exemple avec l'addition et l'opérateur unaire `-` :

```cpp
class Vecteur
{
public:
    ...
    Vecteur operator+(Vecteur const& u) const;
    Vecteur operator-() const;
    ...
};
...
Vecteur Vecteur::operator+(Vecteur const& u) const
{
    Vecteur res;
    for (int i = 0; i < 3; ++i)
        res.m_valeurs[i] = m_valeurs[i] + u.m_valeurs[i];
    return res;
}

Vecteur Vecteur::operator-() const
{
    Vecteur res;
    for (int i = 0; i < 3; ++i)
        res.m_valeurs[i] = -m_valeurs[i];
    return res;
}
...
Vecteur u, v, w;
...
w = u + v; // Appel de l'opérateur +
w = -v; // Appel de l'opérateur unaire -
```

Il existe deux opérateurs particuliers :

1. L'opérateur d'affectation `=`.

2. L'opérateur de déplacement `=`.

### L'opérateur d'affectation

L'opérateur d'affectation `=` doit être défini en interne à la classe.

Il doit renvoyer une référence sur l'objet courant pour permettre les opérations en chaîne.

Il doit être défini par une méthode non constante.

Cet opérateur est mis en oeuvre par défaut si on ne le déclare pas :

- Si tous les membres sont copiables, l'opérateur par défaut copie chaque membre de l'objet source vers l'objet cible.
- Si un membre de classe est non copiable, l'opérateur par défaut est supprimé ou on doit le définir nous même.
- **Attention** : si un des membres de la classe est un pointeur de base sur une zone mémoire,  l'opérateur par défaut ne copie que l'adresse mémoire et non le contenu de la zone mémoire pointée. On doit donc définir un opérateur d'affectation personnalisé pour assurer une copie correcte des données.
- Si on doit définir nous même l'opérateur d'affectation, il faut s'assurer que l'objet ne cherche pas à s'affecter à lui même. En effet, si on a :

```cpp
a = a;
```

alors l'opérateur d'affectation par défaut ne fonctionnera pas. On doit donc écrire (par exemple pour le type `Vecteur` définit précédemment) :

```cpp
class Vecteur
{
public:
    ...
    Vecteur& operator=(Vecteur const& u);
    ...
};
...
Vecteur& Vecteur::operator=(Vecteur const& u)
{
    if (this != &u) // On vérifie que l'objet n'est pas affecté à lui même
    {
        for (int i = 0; i < 3; ++i)
            m_valeurs[i] = u.m_valeurs[i];
    }
    return *this;
}
```

Il est possible de déclarer l'opérateur `=` comme `delete` pour empêcher l'utilisation de l'opérateur d'affectation.

De même, on peut spécifier qu'on souhaite utiliser l'opérateur d'affectation par défaut avec `= default`.

---

**Conseil** : toujours définir l'opérateur d'affectation et l'opérateur de déplacement, même s'il sont générés par défaut. Cela fait parti de la documentation de la classe.

---

### L'opérateur de déplacement

L'opérateur de déplacement `=` est similaire à l'opérateur d'affectation mais il est utilisé pour les objets temporaires (résultat d'une fonction par exemple) et permet de transférer les ressources d'un objet à un autre sans copie.

Il doit renvoyer une référence sur l'objet courant pour permettre les opérations en chaîne.

Il doit être défini par une méthode non constante.

Cet opérateur est mis en oeuvre par défaut si on ne le déclare pas et si on ne déclare par l'opérateur d'affectation.

Pour le reste, l'opérateur de déplacement est similaire à l'opérateur d'affectation.

Exemple avec l'opérateur de déplacement `=` pour le type `Vecteur` définit précédemment :

```cpp
class Vecteur
{
public:
    ...
    Vecteur& operator=(Vecteur&& u);
    ...
};
...
Vecteur& Vecteur::operator=(Vecteur&& u)
{
    if (this != &u) // On vérifie que l'objet n'est pas déplacé sur lui même
    {
        m_valeurs = std::move(u.m_valeurs);
    }
    return *this;
}
...
Vecteur u, v;
...
u = std::move(v); // Appel de l'opérateur =
```

---

**Conseil** : toujours définir l'opérateur de déplacement, même s'il est généré par défaut. Cela fait parti de la documentation de la classe.

---

### Opérateurs de flux

Il est possible de définir des opérateurs de flux pour les objets de la classe. Cela permet de redéfinir le comportement des opérateurs de flux usuels pour les objets de la classe.

Pour cela, il faut définir une méthode de la classe qui sera appelée lors d'une opération utilisant l'opérateur.

Il faut définir l'opérateur comme `friend` pour pouvoir accéder aux membres privés de la classe.

Par exemple, pour reprendre l'exemple précédent, on pourrait définir l'opérateur `<<` pour l'objet `Vecteur` :

```cpp
class Vecteur
{
public:
    ...
    friend std::ostream& operator<<(std::ostream& os, Vecteur const& u);
    ...
};
...
std::ostream& operator<<(std::ostream& os, Vecteur const& u)
{
    os << "(" << u.m_valeurs[0] << ", " << u.m_valeurs[1] << ", " << u.m_valeurs[2] << ")";
    return os;
}
...
Vecteur u;
...
std::cout << u << std::endl; // Appel de l'opérateur <<
```

Si vous ne voulez pas utiliser le mot clé `friend`, vous pouvez créer une méthode `display` dans la classe `Vecteur` et redéfinir l'opérateur `<<` en ligne en dehors de la classe :

```cpp
class Vecteur
{
public:
    ...
    void display(std::ostream& os) const;
    ...
};
...
void Vecteur::display(std::ostream& os) const
{
    os << "(" << m_valeurs[0] << ", " << m_valeurs[1] << ", " << m_valeurs[2] << ")";
}
//
inline std::ostream& operator<<(std::ostream& os, Vecteur const& u)
{
    u.display(os);
    return os;
}
...
std::cout << u << std::endl; // Appel de l'opérateur <<
```

On peut aussi définir l'opérateur `>>` pour l'objet vecteur. Cependant, comment créer un nouveau vecteur avec l'opérateur `>>` ?

L'idée est de définir un constructeur de vecteur qui prend une entrée de flux en paramètre puis déclaré en ligne l'opérateur `>>` en dehors de la classe.

```cpp
class Vecteur
{
public:
    ...
    Vecteur(std::istream& is);
    ...
};
...
Vecteur::Vecteur(std::istream& is)
{
    is >> m_valeurs[0] >> m_valeurs[1] >> m_valeurs[2];
}

//
inline std::istream& operator>>(std::istream& is, Vecteur& u)
{
    u = Vecteur(is);
    return is;
}
...
std::cin >> u; // Appel du constructeur de vecteur
```

### Opérateur d'accession et de modification

Il est possible de définir un opérateur d'accession et de modification pour les objets de la classe. Cela permet de modifier les données d'un objet en utilisant l'opérateur `[]`.

Cet opérateur doit être déclarer en deux versions :

- Une version constante qui permet de lire les données de l'objet.
- Une version non constante qui permet de modifier les données de l'objet.

Cet opérateur prend un paramètre en entrée qui est l'indice de l'élément à accéder (cet indice peut être de n'importe quel type, entier, chaîne de caractères, etc.).

Le C++ 23 permet d'avoir plus que un paramètre en entrée pour l'opérateur `[]` ce qui permet de gérer des tableaux multidimensionnels (cependant, certains compilateurs ne supportent pas encore cette extension).

Exemple d'accès à un élément de la classe `Vecteur` :

```cpp
class Vecteur
{
public:
    ...
    double& operator[](int i);
    double const& operator[](int i) const;
    ...
};
...
double& Vecteur::operator[](int i)
{
    return m_valeurs[i];
}
double const& Vecteur::operator[](int i) const
{
    return m_valeurs[i];
}
...
Vecteur u;
...
u[0] = 1; // Appel de l'opérateur [] en écriture
double a = u[0]; // Appel de l'opérateur [] en lecture
```

#### Que faire si on veut gérer les tableaux multidimensionnels ?

Si notre compilateur ne supporte pas l'extension du C++ 23 pour les tableaux multidimensionnels, on peut soit :

- Redéfinir l'opérateur `[]` pour prendre en entrée un tuple ou un tableau d'indices.
- Ou créer une classe `Indice` qui contient les indices en entrée et qui surcharge l'opérateur `[]` pour pouvoir utiliser un seul paramètre en entrée.
- Utiliser l'opérateur d'évaluation `()` qui permet d'avoir un nombre de paramètres variables en entrée.

Exemple d'accès à des coefficients d'une matrice à l'aide de l'opérateur `()` :

```cpp
class Matrice
{
public:
    Matrice(int nrows, int ncols) 
        :   m_coefficients(nrows * ncols), 
            m_nrows(nrows), 
            m_ncols(ncols) 
    {}
    ...
    double& operator()(int i, int j)
    {
        return m_coefficients[i * m_ncols + j];
    }
    double const& operator()(int i, int j) const
    {
        return m_coefficients[i * m_ncols + j];
    }
    ...
private:
    std::vector<double> m_coefficients{};
    int m_nrows{0};
    int m_ncols{0};
};
...
double& Matrice::operator()(int i, int j)
{
    assert(i >= 0 && i < m_nrows);
    assert(j >= 0 && j < m_ncols);
    return m_coefficients[i * m_ncols + j];
}
double const& Matrice::operator()(int i, int j) const
{
    assert(i >= 0 && i < m_nrows);
    assert(j >= 0 && j < m_ncols);
    return m_coefficients[i * m_ncols + j];
}
...
Matrice u(3, 3);
...
u(0, 0) = 1; // Appel de l'opérateur ()
double a = u(0, 1); // Appel de l'opérateur ()
```

### Opérateurs de conversion

Il est possible de définir des opérateurs de conversion pour les objets de la classe. Cela permet de convertir un objet de la classe en un autre type.

Pour cela, il faut définir une méthode de la classe qui sera appelée lors d'une opération utilisant l'opérateur.

Par exemple, pour reprendre l'exemple précédent, on pourrait définir l'opérateur de conversion en `std::vector<double>` pour l'objet `Vecteur` :

```cpp
class Vecteur
{
public:
    ...
    operator std::vector<double>() const;
    ...
};

Vecteur::operator std::vector<double>() const
{
    return std::vector<double>(m_valeurs.begin(), m_valeurs.end());
}
...
Vecteur u;
...
std::vector<double> v = static_cast<std::vector<double>>(u); // Appel de l'opérateur de conversion
```

**Remarque** : Une conversion implique toujours une copie des données. Si on ne veut pas que la conversion crée une copie, on peut définir un opérateur de conversion en retour de référence.

```cpp
class Vecteur
{
public:
    ...
    std::vector<double> const& operator()() const;
    ...
};

std::vector<double> const& Vecteur::operator()() const
{
    return m_valeurs;
}
```

Les convertions sont par défaut implicites. C'est à dire que le compilateur peut les utiliser sans que l'utilisateur en soit informé.

Pour éviter cela, on peut déclarer l'opérateur de conversion comme `explicit` ce qui empêche le compilateur d'utiliser l'opérateur de conversion implicitement.

```cpp
class Vecteur
{
public:
    ...
    explicit operator std::vector<double>() const;
    ...
};
...
Vecteur u;
...
std::vector<double> v = u; // Erreur de compilation
std::vector<double> v = static_cast<std::vector<double>>(u); // Ok
```

---

**Conseil** : Lorsqu'un opérateur de conversion effectue une copie, il est préférable de déclarer l'opérateur comme `explicit` pour empêcher des copies inutiles.

---

### Opérateurs d'incrémentation et de décrémentation

Il est possible de définir des opérateurs d'incrémentation et de décrémentation pour les objets de la classe. Cela permet de modifier les données d'un objet en utilisant les opérateurs `++` et `--`.

Comme pour les opérateurs d'incrémentation et décrémentation externes, on peut définir deux versions de l'opérateur :

- Une version pour la préincrémentation et la predécrémentation.
- Une version pour la postincrémentation et la postdécrémentation. Comme pour l'opérateur extérieur à la classe, on ajoute un paramètre de type `int` en entrée.

Ces opérateurs doivent renvoyer une référence sur l'objet courant pour permettre les opérations en chaîne.

Par exemple, imaginons que nous définissions une classe `Indice` qui permet de gérer les indices d'une matrice. On pourrait définir les opérateurs d'incrémentation et de décrémentation de la manière suivante :

```cpp
class Matrix
{
public:
    /**
     * @brief Classe interne pour gérer les indices d'une matrice.
     * @details Cette classe est utilisée pour gérer les indices d'une matrice.
     * @param mat La matrice à laquelle appartient l'indice.
     * @param i La ligne de l'indice.
     * @param j La colonne de l'indice.
     */
    class Indice
    {
    public:
        Indice(Matrix& mat) 
            :   m_mat(mat)
        {}
        Indice(Matrix& mat, int i, int j) 
            :   i_row(i),
                j_col(j),
                m_mat(mat)
        {}
        Indice(Indice const& i) = default;
        ...
        Indice& operator=(Indice const& i) = default;
        ...
        // Préincrémentation
        Indice& operator++()
        {
            ++j_col;
            if (j_col >= m_mat.m_ncols)
            {
                j_col = 0;
                ++i_row;
            }
            return *this;
        }
        // Postincrémentation
        Indice operator++(int)
        {
            Indice tmp(*this);
            ++(*this);
            return tmp;
        }
        ...
        int i_row{0}, j_col{0};
    private:
        Matrix& m_mat;
    };
    ...
    double& operator[](Indice i)
    {
        assert(i.i_row >= 0 && i.i_row < m_nrows);
        assert(i.j_col >= 0 && i.j_col < m_ncols);
        return m_coefficients[i.i_row * m_ncols + i.j_col];
    }
    double const& operator[](Indice i) const
    {
        assert(i.i_row >= 0 && i.i_row < m_nrows);
        assert(i.j_col >= 0 && i.j_col < m_ncols);
        return m_coefficients[i.i_row * m_ncols + i.j_col];
    }
    ...
private:
    std::vector<double> m_coefficients{};
    int m_nrows{0};
    int m_ncols{0};
};
```

## Les itérateurs

Les itérateurs sont des objets qui permettent de parcourir les éléments d'un conteneur de façon séquentielle en cachant les détails du conteneur.

Cela permet de factoriser un grand nombre d'algorithme sans ce soucier du détail de mise en oeuvre de tous les conteneurs. En pariculiers, beaucoup de fonctionnalités proposées par la STL (librairie standard du C++) sont basées sur les itérateurs.

De plus, afin d'utiliser une boucle `for` sous la forme :

```cpp
for (auto coef : conteneur) { ... }
```

il faut que la classe que représente `conteneur` ait une méthode `begin` qui renvoie un itérateur sur le premier élément du conteneur et une méthode `end` qui renvoie un itérateur sur la fin du conteneur.

Pour des classes simples comme un vecteur, il est courant de définir nos propres itérateurs en simplement renommant un itérateur de la STL. Par exemple :

```cpp
class Vecteur
{
public:
    using iterator = std::vector<double>::iterator;
    using const_iterator = std::vector<double>::const_iterator;
    ...
    iterator begin() { return m_valeurs.begin(); }
    iterator end() { return m_valeurs.end(); }

    const_iterator begin() const { return m_valeurs.begin(); }  
    const_iterator end() const { return m_valeurs.end(); }
    const_iterator cbegin() const { return m_valeurs.cbegin(); }
    const_iterator cend() const { return m_valeurs.cend(); }

private:
    std::vector<double> m_valeurs;
};
...
Vecteur u;
...
for (auto coef : u) { ... }
```

Remarquons qu'on a défini deux type d'itérateurs :

- `iterator` : Un itérateur non constant pour pouvoir modifier les éléments du vecteur.
- `const_iterator` : Un itérateur constant pour pouvoir lire uniquement les éléments du vecteur (sans les modifier).

Les méthodes `begin` et `cbegin` renvoient respectivement un itérateur non constant (quand le vecteur est non constant) et constant sur le premier élément du conteneur.

Les méthodes `end` et `cend` renvoient respectivement un itérateur non constant ( quand le vecteur est non constant) et constant sur la fin du conteneur.

Parfois, redéfinir les itérateurs à partir des itérateurs de la STL ne permet pas de bien définir les itérateurs de notre classe.

Reprenons notre exemple de matrice et imaginons que nous voulons définir un itérateur qui permet de parcourir les éléments de la matrice ligne par ligne.

Il nous faudra donc que notre itérateur :

- puisse se déplacer d'un élément à l'autre en gérant les sauts de ligne lorsque l'on arrive à la fin d'une ligne.
- puisse fournir les indices de ligne et de colonne de l'élément courant.
- puisse être incrémenté (et décrémenté si on veut un itérateur bidirectionnel).
- puisse être comparé à un autre itérateur (égalité et différence).
- puisse retourner la valeur de l'élément courant en référence
- puisse être constant ou non constant

L'idée lors de la création de l'itérateur est de pouvoir faire référence à la matrice sur laquelle il parcourt les éléments.

Voici une mise en oeuvre possible :

```cpp
class Matrice
{
public:
    /**
     * @brief Itérateur pour parcourir les éléments de la matrice.
     * @details Cette classe est utilisée pour parcourir les éléments de la matrice.
     * @param mat La matrice à laquelle appartient l'itérateur.
     * @param i La ligne de l'itérateur.
     * @param j La colonne de l'itérateur.
     */
    class iterator
    {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = double;
        using difference_type = std::ptrdiff_t;
        using pointer = double*;
        using reference = double&;

        iterator(Matrice& mat, int i, int j)
            :   m_mat(mat),
                m_i(i),
                m_j(j)
        {}

        reference operator*() const { return m_mat.data()[m_i * m_mat.ncols() + m_j]; }
        pointer operator->() const { return &m_mat.data()[m_i * m_mat.ncols() + m_j]; }

        iterator& operator++() { ++m_j; if (m_j >= m_mat.ncols()) { m_j = 0; ++m_i; } return *this; }
        iterator operator++(int) { iterator tmp(*this); ++(*this); return tmp; }

        bool operator==(iterator const& other) const { return m_i == other.m_i && m_j == other.m_j; }
        bool operator!=(iterator const& other) const { return !(*this == other); }

    private:
        Matrice& m_mat;
        int m_i{0}, m_j{0};
    };

    /**
     * @brief Itérateur constant pour parcourir les éléments de la matrice.
     * @details Cette classe est utilisée pour parcourir les éléments constants de la matrice.
     * @param mat La matrice à laquelle appartient l'itérateur.
     * @param i La ligne de l'itérateur.
     * @param j La colonne de l'itérateur.
     */
    class const_iterator
    {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = double;
        using difference_type = std::ptrdiff_t;
        using pointer = double const*;
        using reference = double const&;

        const_iterator(Matrice const& mat, int i, int j)
            :   m_mat(mat),
                m_i(i),
                m_j(j)
        {}

        reference operator*() const { return m_mat.data()[m_i * m_mat.ncols() + m_j]; }
        pointer operator->() const { return &m_mat.data()[m_i * m_mat.ncols() + m_j]; }

        const_iterator& operator++() { ++m_j; if (m_j >= m_mat.ncols()) { m_j = 0; ++m_i; } return *this; }
        const_iterator operator++(int) { const_iterator tmp(*this); ++(*this); return tmp; }

        bool operator==(const_iterator const& other) const { return m_i == other.m_i && m_j == other.m_j; }
        bool operator!=(const_iterator const& other) const { return !(*this == other); }

    private:
        Matrice const& m_mat;
        int m_i{0}, m_j{0};
    };

    Matrice(int nrows, int ncols);
    ...
    int nrows() const { return m_nrows; }
    int ncols() const { return m_ncols; }
    double* data() { return m_coefficients.data(); }
    double const* data() const { return m_coefficients.data(); }
    ...
    iterator begin() { return iterator(*this, 0, 0); }
    iterator end() { return iterator(*this, m_nrows, 0); }
    const_iterator begin() const { return const_iterator(*this, 0, 0); }
    const_iterator end() const { return const_iterator(*this, m_nrows, 0); }
    const_iterator cbegin() const { return const_iterator(*this, 0, 0); }
    const_iterator cend() const { return const_iterator(*this, m_nrows, 0); }

private:
    std::vector<double> m_coefficients;
    int m_nrows{0};
    int m_ncols{0};
};
```

---

**Remarque** : on peut voir dans les entêtes des itérateurs les types `iterator_category`, `value_type`, `difference_type`, `pointer` et `reference` :

- `iterator_category` : fournit le type de l'itérateur (forward, bidirectional, random access, etc.). Cela permet de définir le comportement des itérateurs qui peut être utilisé par la STL.
- `value_type` : le type des éléments sur lesquels on itère.
- `difference_type` : un type entier qui représente la différence entre deux itérateurs.
- `pointer` : un type pointeur sur le type des éléments.
- `reference` : un type référence sur le type des éléments.

Ces types sont définis dans l'entête `<iterator>` et pousse les programmeurs à définir les itérateurs de manière standard quelque soit le code.

---

## Attributs et méthodes de classe

On peut définir des attributs et méthodes de classe de la manière suivante :

```cpp
class Vecteur
{
public:
    // Compte le nombre de vecteurs créés
    static int m_nb_vecteurs;
    ...
    Vecteur(int n)
        :   m_valeurs(n, 0.)
    {
        ++m_nb_vecteurs;
    }
    ...
    ~Vecteur()
    {
        --m_nb_vecteurs;
    }
    ...
};
```

Une attribut statique est un attribut de classe qui est partagé par tous les objets de la classe. Ce sont des variables globales qui ont pour portée la classe dans laquelle elles sont définies.

De même, on peut définir une méthode de classe, c'est à dire une méthode qui est partagée par tous les objets de la classe. Ce sont des fonctions qui ont pour portée la classe dans laquelle elles sont définies.

```cpp
class Vecteur
{
public:
    ...
    static int nb_vecteurs() { return m_nb_vecteurs; }
private:
    static int m_nb_vecteurs;
    ...
};
```

L'avantage de définir des méthodes de classe et de pouvoir nommer plusieurs fonctions avec le même nom et les mêmes paramètres mais avec une portée de classe différente est que l'on peut utiliser le nom de la méthode sans avoir besoin de l'instancier.

```cpp
Vecteur u(10);
Vecteur v(20);
std::cout << "Nombre de vecteurs : " << Vecteur::nb_vecteurs() << std::endl;
```

## L'héritage

L'héritage est un concept fondamental en programmation orientée objet, et particulièrement en C++. Il permet de créer une nouvelle classe (appelée classe dérivée ou sous-classe) à partir d'une classe existante (appelée classe de base ou superclasse). Cette notion est essentielle pour plusieurs raisons :

1. Réutilisation du code : L'héritage permet de réutiliser le code de la classe de base dans la classe dérivée, évitant ainsi la duplication de code et facilitant la maintenance.

2. Extension des fonctionnalités : On peut ajouter de nouvelles fonctionnalités à la classe dérivée tout en conservant celles de la classe de base.

3. Polymorphisme : L'héritage est à la base du polymorphisme, permettant de traiter des objets de classes dérivées comme des objets de la classe de base.

4. Hiérarchie de classes : Il permet de créer une structure hiérarchique de classes, reflétant souvent la structure logique du problème à résoudre.

5. Abstraction : On peut créer des classes de base abstraites, définissant une interface commune pour un groupe de classes dérivées.

On peut voir l'héritage comme une relation "est-un" entre des classes. Par exemple, une matrice carrée est une matrice et possède donc toutes les propriétés d'une matrice quelconque plus bien sûr d'autres propriétés suppléméntaires (le déterminant par exemple).

Il n'existe pas une seule hiérarchie possible de classe pour un projet, et cette hiérarchie devra plutôt être guidée par la logique et la performance voulue pour l'application visée.

En C++, l'héritage se déclare en utilisant le symbole ':' suivi du type d'héritage (public, protected, ou private) et du nom de la classe de base. Dans ce cours, on ne s'intéressera qu'à l'héritage public, les autres types d'héritage étant rarement utilisés.

```cpp
class Matrice
{
public:
    ...
};

class MatriceCarree : public Matrice
{
public:
    ...
    double determinant() const;
    ...
};
```

On peut alors utiliser la classe `MatriceCarree` comme une classe `Matrice` mais avec des fonctionnalités supplémentaires.

```cpp
MatriceCarree A;

// On peut utiliser A comme une Matrice quelconque
Matrice& M = A;

// On peut aussi utiliser les méthodes spécifiques à MatriceCarree
A.determinant();
```

### Constructeurs et destructeurs

Quand une classe B hérite d'une classe A, le constructeur de B doit initialiser le constructeur de A. De même, le destructeur de B doit appeler le destructeur de A.

Les constructeurs et le destructeur par défaut de la classe B font par défaut ce travail.

Par exemple en reprenant les classes `Matrice` et `MatriceCarree` précédentes (en rajoutant une matrice rectangulaire):

```cpp
class Matrice
{
public:
    /**
     * @brief Constructeur de la classe Matrice.
     * @param size le nombre de coefficients de la matrice.
     */
    Matrice(std::size_t size ) : m_coefficients(size, 0.) {}
    ...
    double* data() { return m_coefficients.data(); }
    double const* data() const { return m_coefficients.data(); }
    ...
private:
    std::vector<double> m_coefficients;
};

/**
 * @brief Classe dérivée de Matrice pour les matrices carrées.
 * @details Cette classe hérite de la classe Matrice et ajoute un attribut pour stocker la dimension de la matrice.
 */
class MatriceCarree : public Matrice
{
public:
    MatriceCarree(int n) : Matrice(n*n), m_dim(n) {}
    ...
private:
    std::size_t m_dim;
};

class MatriceRectangulaire : public Matrice
{
public:
    MatriceRectangulaire(int nrows, int ncols) : Matrice(nrows*ncols), m_nrows(nrows), m_ncols(ncols) {}
    ...
private:
    std::size_t m_nrows;
    std::size_t m_ncols;
};
```

Voici un diagramme (UML) qui illustre l'héritage mis en place entre les classes Matrice, MatriceCarree et MatriceRectangulaire :

```raw
┎───────────────┒
┃    Matrice    ┃
┗───────────────┛
       Δ
       │
       │   ┎───────────────┒
       │───┃ MatriceCarree ┃
       │   ┗───────────────┛
       │
       │
       │   ┎──────────────────────┒
       └───┃ MatriceRectangulaire ┃
           ┗──────────────────────┛
```

UML est un langage de modélisation graphique qui permet de représenter les classes, les relations entre les classes et les autres éléments d'un système. Plusieurs logiciels existent pour pouvoir gérer des diagrammes UML, donc certains gratuits (comme Draw.io ou Lucidchart) ou payants (comme Microsoft Visio ou StarUML).

### Les fonctions virtuelles

Les fonctions virtuelles sont des fonctions qui permettent de définir une interface commune pour un groupe de classes dérivées. Elles sont déclarées dans la classe de base et redéfinies dans les classes dérivées.

Supposons que nous avons une classe Quadrilatere avec des classes derivees Carre, Rectangle et Trapeze.

```raw
┎──────────────────────┒
┃    Quadrilatere      ┃
┗──────────────────────┛
       Δ
       │
       │   ┎───────────────┒
       │───┃    Carre      ┃
       │   ┗───────────────┛
       |   ┎───────────────┒
       |───┃   Rectangle   ┃
       |   ┗───────────────┛
       │   ┎───────────────┒
       └───┃    Trapeze    ┃
           ┗───────────────┛
```

On voudrait pouvoir calculer la surface de ces quadrilatères en fonction de leur type et pouvoir calculer cette aire avec un objet de type Quadrilatère.

On pourrait penser qu'écrire le code suivant suffit :

```cpp
class Quadrilatere
{
public:
    double surface() const { return 0.; }
};

class Carre : public Quadrilatere
{
public:
    Carre(double cote) : m_cote(cote) {}
    ...
    double surface() const { return m_cote * m_cote; }
private:
    double m_cote;
};

class Rectangle : public Quadrilatere
{
public:
    Rectangle(double longueur, double largeur) 
        : m_longueur(longueur), 
          m_largeur(largeur) 
    {}
    ...
    double surface() const { return m_longueur * m_largeur; }
private:
    double m_longueur;
    double m_largeur;
};

class Trapeze : public Quadrilatere
{
public:
    Trapeze(double grand_cote, double petit_cote, double hauteur) 
        : m_grand_cote(grand_cote), 
          m_petit_cote(petit_cote), 
          m_hauteur(hauteur) 
    {}
    ...
    double surface() const { return (m_grand_cote + m_petit_cote) * m_hauteur / 2; }
private:
    double m_grand_cote;
    double m_petit_cote;
    double m_hauteur;
};  
```

On pourrait penser que le code suivant permet de calculer la surface du carré pris comme un quadrilatère :

```cpp
Carre c(2);
Quadrilatere& q = c;
std::cout << "Surface : " << q.surface() << std::endl;
```

Mais le résultat affiché est 0.

Pourquoi ? Il faut comprendre que le C++ est un langage accès sur l'optimisation du code. Si on ne lui spécifie pas qu'il doit tenir compute du "vrai" type du quadrilatère, C++ optimisera le code en regardant le type appelant la méthode surface et en décidant à la compilation la fonction à appelé : ici la méthode surface de la classe Quadrilatere.

Pour signaler au C++ que l'appel sera décidé à l'exécution en fonction du vrai type du quadrilatère (Carré, Rectangle ou Trapeze), on utilise le mot clé `virtual` dans la déclaration de la méthode dans la classe de base.

```cpp
class Quadrilatere
{
public:
    virtual double surface() const { return 0; }
};
...
```

On peut alors utiliser le mot clé `override` dans les classes dérivées pour s'assurer que la méthode est bien redéfinie (il est facile en C++ d'oublier un const pour la méthode ou pour un des paramètres et définir une nouvelle fonction au lieu de surcharger (redéfinir) une fonction virtuelle).

```cpp
class Carre : public Quadrilatere
{
public:
    double surface() const override { return m_cote * m_cote; }
    ...
```

On peut alors utiliser le code suivant pour calculer la surface du carré pris comme un quadrilatère :

```cpp
Carre c(2);
Quadrilatere& q = c;
std::cout << "Surface : " << q.surface() << std::endl;
```

Cette fois-ci, le résultat affiché est 4.

### Les classes abstraites

Les classes abstraites sont des classes qui ne peuvent être instanciées. Elles servent à définir une interface commune pour un groupe de classes dérivées.

L'idée d'une classe abstraite est de pouvoir définir des fonctions virtuelles qui ne seront pas mise en oeuvre dans la classe mère mais dans les classes dérivées. Pour cela, on va définir dans la classe mère des méthodes virtuelles pures reconnaissables par un `= 0` dans la déclaration.

Ainsi, pour notre exemple sur les quadrilatères, on peut définir Quadrilatère comme une  classe abstraite suivante :

```cpp
class Quadrilatere
{
public:
    virtual double surface() const = 0;
};
```

On dit simplement ici que nous ne savons pas à ce stage calculer la surface d'un quadrilatère mais que nous le saurons faire dans les classes dérivées.

Il est imposible d'instancier un objet de type Quadrilatere car la méthode surface() est déclarée comme étant purement virtuelle.

```cpp
Quadrilatere q; // Erreur de compilation
```
---

**Attention** : Si une classe dérivée ne redéfinie pas toutes les méthodes virtuelles pures de sa classe de base, alors cette classe dérivée ne peut pas être instanciée et est elle-même considérée comme une classe abstraite.

---

---

**Remarque** : Pour que le mécanisme des méthodes dérivées fonctionne en C++, il est important de passer les objets par référence ou par pointeur. De toute façon, puisqu'il est impossible d'avoir une instance d'une classe abstraite, il est nécessaire de passer les objets par référence ou par pointeur sous peine d'erreur de compilation.

---

Notons également qu'il est possible lors de la redéfinition d'une méthode virtuelle de renvoyer un type différent de celui de la classe de base. Ceci est possible dans la mesure où le type renvoyé hérite de la classe de base du type renvoyé dans la classe de base.

### La conception par contrat (supplément)

Revenons sur notre exemple des quadrilatères. Vous avez pu vous faire la remarque qu'un Carré est un Rectangle et donc que Carré aurait pu hériter de Rectangle.

Le Rectangle doit posséder une longueur et une largeur. Mais le Carré possède une longueur et une largeur égales. Imaginons que la classe Rectangle possède une méthode `set_dimensions` qui prend deux paramètres afin de redimensionner la longueur et la largeur du rectangle. Dans ce cas, par héritage, on pourra redimensionner la largeur et la longueur du carré, mais cela n'a pas de sens.

Inversement, on pourrait dire que le Rectangle est un carré généralisé. Mais cela semble peu naturel mais si cela résoud le point précédent.

Pour résoudre ce problème, on peut utiliser la conception par contrat. La conception par contrat est une approche de la programmation qui vise à garantir la validité des objets et des classes en vérifiant les préconditions et postconditions. Elle permet de s'assurer que les objets sont dans un état valide avant et après l'utilisation de leurs méthodes.

On peut définir des préconditions sur les paramètres des méthodes afin de s'assurer que les objets sont dans un état valide avant l'utilisation de la méthode. On peut aussi définir des postconditions sur les valeurs de retour des méthodes afin de s'assurer que les objets sont dans un état valide après l'utilisation de la méthode.

Pour un héritage cohérent, on devra vérifier les propriétés suivantes sur les préconditions et postconditions :

- Une classe dérivée ne doit pas avoir des préconditions plus contraignantes que sa classe de base.
- Une classe dérivée ne doit pas avoir des postconditions moins contraignantes que sa classe de base.

Cette méthode a été intégré dans des langages comme Eiffel par l'inventeur de cette méthode, Bertrand Meyer. Mais il est possible de l'utiliser dans d'autres langages de programmation, comme C++, en utilisant des outils comme les assertions et les contrats dans le futur (prévu au départ pour le C++ 20 mais repoussé à une version ultérieure...).

### Virtualité du destructeur

Il est important de définir le destructeur comme étant une méthode virtuelle pour garantir que le destructeur de la classe dérivée est appelé lors de la destruction d'un objet. En effet, si le destructeur n'est pas virtuel, le destructeur de la classe de base sera appelé et non celui de la classe dérivée.

```cpp
class MaClasse
{
public:
    ~MaClasse() { ... }
};

class MaClasseDerivee : public MaClasse
{
public:
    ~MaClasseDerivee() { ... }
};
// On alloue un objet de type MaClasseDerivee mais on le stocke dans un pointeur de type MaClasse
MaClasse* ptr = new MaClasseDerivee();
delete ptr; // Appel du destructeur de MaClasse
```

Pour résoudre ce problème, il est important de déclarer le destructeur de la classe de base comme étant virtuel.

```cpp
class MaClasse
{
public:
    virtual ~MaClasse() { ... }
};
```

Ainsi, le destructeur de MaClasseDerivee sera appelé lors de la destruction de l'objet.

```cpp
MaClasse* ptr = new MaClasseDerivee();
delete ptr; // Appel du destructeur de MaClasseDerivee
```

### Héritage et opérateurs d'affectation

Les opérateurs d'affectation sont difficilement virtualisables.

Reprenons notre exemple des quadrilatères. Imaginons que nous voulons pouvoir copier un quadrilatère. On pourrait penser qu'il suffit de définir un opérateur d'affectation virtuel dans la classe de base et le redéfinir dans les classes dérivées.

```cpp
class Quadrilatere
{
public:
    ...
    virtual Quadrilatere& operator = ( Quadrilatere const& ) = 0;
    ...
};

class Carre : public Quadrilatere
{
public:
    ...
    override Carre& operator = ( Quadrilatere const& );
    ...
};
```

Si la redéfinition d'une fonction virtuelle permet de renvoyer ici un Carré au lieu d'un Quadrilatère, il est obligatoire d'avoir en paramètre un Quadrilatère.

Cela a une conséquence importante : il devient possible de copier un Rectangle par exemple dans un Carre, ce qui n'a pas de sens.

Il est possible de détecter le "vrai" type du paramètre passé dans l'opérateur d'affectation en utilisant la fonction `dynamic_cast` qui "tente" de convertir un objet de base en objet dérivé (et renvoyer une exception en cas d'échec)
et agir en conséquence pour la copie, mais cela nous mène très vite a des problèmes combinatoires exponentiels.

La seule solution possible : s'inspirer de Java ou de Python et de définir une méthode clone (comme dans Java) ou copy (comme dans Python)
pour pouvoir recopier un objet sans se soucier du type d'objet.

```cpp
class Quadrilatere
{
public:
    ...
    virtual Quadrilatere* copy() const = 0;
    ...
};

class Carre : public Quadrilatere
{
public:
    Carre( Carre const& ) = default;
    ...
    Carre* copy() const override { return new Carre(*this); }
    ...
};
```

On peut alors utiliser cette méthode pour recopier un objet sans se soucier du type d'objet.

```cpp
Carre c1(2);
Carre* c2 = c1.copy();
...
delete c2;// Pour détruire c2
```

On peut améliorer le code en retournant un pointeur intelligent pour la copie qu'un pointeur de base mais cela impose un comportement prédéfini sur le pointeur (partagé ou unique) ce qui n'est pas toujours souhaitable.

De même, les opérateurs arithmétiques posent les mêmes problèmes que les opérateurs d'affectation.

## Pour aller plus loin

Le lecteur intéressé et sounaitant aller plus loin dans la programmation en c++ pourra également se pencher sur les points suivant qui n'ont pas été abordés dans le cours :

- L'héritage multiple (qui pose pas mal de problèmes en C++ et qu'il vaut mieux éviter dans un premier temps)
- Les classes finales (qui permettent de définir une classe qui ne peut être utilisée comme une classe de base) (abordé dans la présentation mais pas dans ce papier)
- Reconnaître le type d'un objet à l'exécution (avec `dynamic_cast` ou `typeid`). Certaines personnes disent qu'utiliser ces fonctionnalités indique un problème de conception dans votre code, mais le débat est ouvert.


