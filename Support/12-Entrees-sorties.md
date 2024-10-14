# Entrées-Sorties

Les entrées-sorties en C++ sont conçues pour être à la fois puissantes et flexibles tout en restant accessibles aux débutants. Voici les points clés à comprendre :

1. Abstraction des flux : Le C++ utilise le concept de "flux" (stream) pour gérer les entrées-sorties. Un flux est une abstraction qui représente une séquence de données, qu'il s'agisse d'entrée (lecture) ou de sortie (écriture).

2. Uniformité : Que vous travailliez avec la console, des fichiers ou même des chaînes de caractères en mémoire, l'interface de programmation reste largement la même. Cela simplifie l'apprentissage et l'utilisation.

3. Opérateurs surchargés : Le C++ utilise les opérateurs << (insertion) et >> (extraction) pour les opérations d'entrée-sortie. Cette approche rend le code plus lisible et intuitif.

4. Bibliothèque standard : La bibliothèque standard C++ fournit des classes prêtes à l'emploi pour gérer différents types d'entrées-sorties, comme iostream pour la console et fstream pour les fichiers.

5. Gestion des erreurs : Les flux en C++ intègrent des mécanismes pour détecter et gérer les erreurs d'entrée-sortie, permettant une programmation robuste.

6. Extensibilité : Le système est conçu pour être facilement étendu, permettant de créer des flux personnalisés pour des besoins spécifiques.

En comprenant ces principes, même les débutants peuvent rapidement commencer à utiliser les entrées-sorties en C++ de manière efficace et élégante.

## Les flux console

Ces flux consoles peuvent être accessibles via la composante `<iostream>` de la bibliothèque standard.

Les flux console sont gérés par les représentants de trois flux différents :

- `std::cin` est utilisé pour les entrées utilisateur au clavier;
- `std::cout` est utilisé pour les sorties standard sur un terminal;
- `std::cerr` est utilisé pour les sorties d'erreur sur un terminal;
- `std::clog` est similaire à `std::cout` mais il est généralement utilisé pour les messages de log.

Pour `std::cin`, on utilise l'opérateur `>>` pour l'extraction de données :

Pour les trois autres flux, on utilise l'opérateur `<<` pour l'insertion de données.

**Exemple** :

```cpp
std::string nom;
std::cout << "Entrez votre nom : ";
std::cin >> nom;
std::cout << "Bonjour, " << nom << "!" << std::endl;
```

## Les flux fichiers

Les flux fichiers sont gérés par la composante `<fstream>` de la bibliothèque standard.

Pour ouvrir un flux ficher en écriture, on utilise la classe `std::ofstream`.
La syntaxe pour ouvrir un fichier est dans sa forme la plus basique :

```cpp
std::ofstream fichier("nom_du_fichier.txt");
```

Dans ce cas, si le fichier existe, il sera écrasé. Le fichier sera écrit en mode texte (formaté). On écrit les données avec l'opérateur `<<` de la même manière que pour `std::cout`. Par exemple, pour écrire un vecteur de doubles dans un fichier :

```cpp
std::vector<double> u;
...
std::ofstream fichier("sortie.txt");
if (fichier.is_open() == false) {
    std::cerr << "Erreur lors de l'ouverture du fichier" << std::endl;
    return EXIT_FAILURE;
}
fichier << u.size() << std::endl;
for (auto const& val : u) {
    fichier << val << " ";
}
fichier.close();
```

On peut rajouter des modes d'ouverture (binaire, append, etc.) en rajoutant un second paramètre à l'instanciation de la classe `std::ofstream` :

```cpp
std::ofstream fichier("nom_du_fichier.txt", mode);
```

L'écriture dans un fichier en mode binaire se fera au travers de la méthode `write` de la classe `std::ofstream` qui prend une zone mémoire (sous forme de `char *`) et la taille de la zone mémoire à écrire.

Par exemple, pour écrire un vecteur de doubles dans un fichier binaire, on fera :

```cpp
std::ofstream fichier("sortie.bin", std::ios::binary);
if (fichier.is_open() == false) {
    std::cerr << "Erreur lors de l'ouverture du fichier" << std::endl;
    return EXIT_FAILURE;
}
fichier.write(reinterpret_cast<char const*>(u.data()), u.size() * sizeof(double));
fichier.close();
```

La fonction `sizeof` retourne la taille en octets pris en mémoire pour un type ou une variable.

La fonction `reinterpret_cast` est une opération de casting qui permet de convertir un pointeur de type `T *` en un pointeur de type `char *`. Cette conversion est nécessaire car la méthode `write` attend un pointeur de type `char *`.

Pour lire dans un fichier, on utilise la classe `std::ifstream`. La syntaxe est similaire à celle de `std::ofstream` avec l'opérateur `>>` pour l'extraction de données. Si le mode n'est pas spécifié, le fichier sera lu en mode texte (formaté).

Par exemple, pour lire un vecteur de doubles dans un fichier texte, on fera :

```cpp
std::vector<double> u;
std::ifstream fichier("entree.txt");
if (fichier.is_open() == false) {
    std::cerr << "Erreur lors de l'ouverture du fichier" << std::endl;
    return EXIT_FAILURE;
}
size_t n;
fichier >> n;
u.resize(n);
for (size_t i = 0; i < n; ++i) {
    fichier >> u[i];
}
fichier.close();
```

Pour lire dans un fichier en mode binaire, on fera :

```cpp
std::ifstream fichier("entree.bin", std::ios::binary);
if (fichier.is_open() == false) {
    std::cerr << "Erreur lors de l'ouverture du fichier" << std::endl;
    return EXIT_FAILURE;
}
fichier.read(reinterpret_cast<char*>(u.data()), u.size() * sizeof(double));
fichier.close();
```

La méthode `read` de la classe `std::ifstream` est similaire à la méthode `write` de la classe `std::ofstream`. Elle prend une zone mémoire (sous forme de `char *`) et la taille de la zone mémoire à lire.

## Ecrire dans une chaîne de caractères

Pour écrire dans une chaîne de caractères, on utilise la méthode `str` de la classe `std::ostringstream` qu'on trouvera dans la composante `<sstream>`.

```cpp
std::ostringstream oss;
oss << "Bonjour, " << nom << "!" << std::endl;
std::string message = oss.str();
```

## Formatage des nombres réels

Comme pour les entiers, on utilisera la composante `<iomanip>` pour formater les nombres réels à l'aide de :

- `std::setw(n)` pour définir la largeur de la zone de sortie;
- `std::setprecision(n)` pour définir le nombre de chiffres significatifs;
- `std::setfill(c)` pour définir le caractère de remplissage;
- `std::left`, `std::right` et `std::internal` pour définir l'alignement du texte.

Par exemple, le programme suivant :

```cpp
constexpr long double pi{std::numbers::pi_v<long double>};
std::cout << std::setw(19) << std::setprecision(0) << pi << std::endl;
std::cout << std::setw(19) << std::setfill('_') << std::setprecision(4) << pi << std::endl;
std::cout << std::setw(4) << std::setprecision(4) << pi << std::endl;
std::cout << std::setprecision(20) << pi << std::endl;
```

affichera :

```raw
                    3
________________3.142
3.142
3.1415926535897932385
```

