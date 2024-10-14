# Les variables

## Déclaration de variables

Les variables sont des emplacements mémoire permettant de stocker des valeurs. Chaque variable possède un type qui détermine la nature des valeurs que la variable peut stocker.

On peut déclarer une variable à n'importe quel endroit d'un bloc d'instructions. La portée d'une variable est la partie du programme où la variable est visible.

La portée d'une variable peut être limitée à un bloc d'instructions (portée locale) ou être étendue à tout le fichier (portée globale).

La syntaxe générale pour déclarer une variable est la suivante :

```cpp
type nom_de_la_variable;
```

Il est possible de déclarer plusieurs variables du même type en utilisant la syntaxe suivante :

```cpp
type nom_de_la_variable_1, nom_de_la_variable_2, ...;
```

Il est possible d'initialiser une variable lors de sa déclaration :

```cpp
type nom_de_la_variable = valeur_initiale;
type nom_de_la_variable(valeur_initiale);
type nom_variable1{valeur1}, nom_variable2{valeur2}, ...;
```

Le C++ dispose d'un certain nombre de types prédéfinis :

- Les types numériques entiers : ```int```, ```short int```, ```long int```, ```unsigned int```, ```unsigned short int```, ```unsigned long int```
- Les types numériques flottants : ```float```, ```double```, ```long double```
- Les caractères : ```char```, ```wchar_t```
- Les booléens : ```bool```
- les chaînes de caractères basiques : ```char*```, ```const char*```
- Les pointeurs : ```type*```

Remarquons qu'il est préférable d'éviter d'utiliser les chaînes de caractères basiques au profit des types définis dans l'espace de nommage *std* comme *std::string* (voir plus loin).

### Noms des variables

Toute variable doit commencer par une lettre, le caractère de soulignement ```_``` ou un caractère d'un sous-ensemble de caractères Unicode (voir [cppreference](https://en.cppreference.com/w/cpp/language/identifiers)). Les lettres majuscules et minuscules sont distinctes. Il est interdit de nommer une variable avec un mot réservé du langage.

Les autres caractères composant le nom d'une variable peuvent être :

- Des chiffres ```0-9```
- Une lettre latine minuscule ou majuscule
- Un caractère Unicode
- Le caractère de soulignement ```_```

Exemples de noms de variables valides :

```cpp
int x;
int _y;
double π;
int n²;
int _;
char 你好;
int version_1_2_3;
```

Exemples de noms de variables invalides :

```cpp
int 1x;
int x y;
double un$;
int return;
```

### Portée des variables

La portée d'une variable détermine la partie du programme où la variable est visible. La portée d'une variable peut être limitée à un bloc d'instructions (portée locale) ou être étendue à tout le fichier (portée globale).

### Les caractères

Un caractère représente une "lettre" ou un symbole. En C++, le type ```char``` représente un caractère. Pour initialiser une variable de type ```char```, on peut utiliser une constante de type ```char``` encadrée par des apostrophes ```'``` ou une constante de type ```int``` représentant le code Unicode du caractère.

```cpp
char c1 = 'a';
char c2 = 97; // 97 est le code Unicode de 'a'
```

Pour utiliser le caractère ```'```, il faut utiliser le caractère antislash ```\```.

```cpp
char c1 = '\'';
char c2 = '"';
```

Il existe plusieurs caractères spéciaux :

- ```\n``` : Retour à la ligne
- ```\t``` : Tabulation
- ```\r``` : Retour en début de ligne
- ```\0``` : Caractère nul

Le type ```char``` est codé sur un octet et ne peut donc représenter que 256 caractères différents. Il n'est donc pas possible d'initialiser un caractère avec un caractère codé en UTF-8.

### Les chaînes de caractères

Nous avons vu précédemment qu'il était possible d'utiliser le type ```char*``` pour déclarer une chaîne de caractères. Cependant, il vaut mieux éviter d'utiliser ce type et préférer utiliser les types définis dans l'espace de nommage *std* comme *std::string*.

En effet, les chaînes de caractères définies dans l'espace de nommage *std* gèrent nativement les caractères encodés en UTF-8 contrairement au type ```char*``` qui ne peut utiliser que les caractères codés sur un octet. De plus, les chaînes de caractères définies dans l'espace de nommage *std* proposent un grand nombre d'opérateurs et de fonctions utiles pour la manipulation de chaînes de caractères ce qui rend leur utilisation plus simple, plus sûre et plus performante.

Pour utiliser les chaînes de caractères définies dans l'espace de nommage *std*, il faut inclure le fichier d'en-tête ```<string>```.

La déclaration d'une chaîne de caractères est la suivante :

```cpp
#include <string>
...
std::string nom_de_la_variable;
```

On peut initialiser une chaîne de caractères d'une des manières suivantes :

```cpp
std::string nom_de_la_variable = "Bonjour";
std::string nom_de_la_variable("Bonjour");
std::string nom_de_la_variable{"Bonjour"};
```

Depuis le C++ 11, il est également possible d'initialiser une chaîne de caractères littérale (raw string):

```cpp
std::string nom_de_la_variable = R"(Ceci est
une "chaîne de
     caractères")";
```

Dans ce cas, les caractères spéciaux ne sont pas interprétés et la chaîne de caractères contient tous les caractères spéciaux tels quels. La délimitation de la chaîne de caractères est assurée par la parenthèse ouvrante ```(``` et la parenthèse fermante ```)```.

Pour délimiter la chaîne de caractères, on peut définir des délimiteurs personnalisés. Par exemple :

```cpp
std::string nom_de_la_variable = R"delimiter(Ceci est
une "chaîne de
caractères" délimitée par "delimiter")delimiter";
```

Dans ce cas, la chaîne de caractères est délimitée par les chaînes de caractères ```delimiter(``` et ```)delimiter```.

#### Opérateurs sur les chaînes de caractères

Plusieurs services sont définis pour les chaînes de caractères définies dans l'espace de nommage *std* :

- L'opérateur d'accès à un caractère : ```[]```
Exemple :

```cpp
std::string s = "Bonjour";
char c = s[0]; // c contient 'B'
```

*Remarque :* Comme tous les conteneurs du C++, les indices des chaînes de caractères commencent à 0.

- L'opérateur permettant d'accéder à une sous-chaîne de caractères : ```substr```
Exemple :

```cpp
std::string s = "Bonjour";
std::string sous_chaine = s.substr(0, 5); // sous_chaine contient "Bonjo"
```

- Les opérateurs de concaténation : ```+```, ```+=``` 
Exemple :

```cpp
std::string s1 = "Bonjour";
std::string s2 = " tout le monde";
std::string s3 = s1 + s2; // s3 contient "Bonjour tout le monde"
```

- Les opérateurs de comparaison : ```==```, ```!=```, ```<```, ```<=```, ```>```, ```>=```
Exemple :

```cpp
std::string s1 = "Bonjour";
std::string s2 = "Bonsoir";
if (s1 == s2)
    std::cout << "Les deux chaînes sont identiques" << std::endl;
```

#### Fonctions sur les chaînes de caractères

Plusieurs fonctions sont définies dans l'espace de nommage *std* pour manipuler les chaînes de caractères :

- La fonction permettant de connaître la longueur d'une chaîne de caractères : ```size```, ```length```
Exemple :

```cpp
std::string s = "Bonjour";
std::cout << s.size() << std::endl;
```

- La fonction permettant de comparer deux chaînes de caractères : ```compare```
Exemple :

```cpp
std::string s1 = "Bonjour";
std::string s2 = "Bonsoir";
if (s1.compare(s2) == 0)
    std::cout << "Les deux chaînes sont identiques" << std::endl;
```

- La fonction permettant de concaténer deux chaînes de caractères : ```operator+```, ```append```
Exemple :

```cpp
std::string s1 = "Bonjour";
std::string s2 = " tout le monde";
s1.append(s2);
```

- La fonction permettant de rechercher une sous-chaîne de caractères dans une chaîne : ```find```
Exemple :

```cpp
std::string s = "Bonjour tout le monde";
std::size_t position = s.find("tout");
```

- La fonction permettant de remplacer une sous-chaîne de caractères par une autre sous-chaîne : ```replace```
Exemple :

```cpp
std::string s = "Bonjour tous le monde";
s.replace(8, 4, "tout");
```

#### Suffixe pour les chaînes de caractères

Les suffixes pour les chaînes de caractères sont définis dans l'espace de nommage *std* :

```cpp
#include <string>
using namespace std::string_literals;
```

Les suffixes suivants sont reconnus pour les chaînes de caractères :

- ```s``` : Chaîne de caractères
- ```ws``` : Chaîne de caractères wide

Pour utiliser un suffixe, il suffit de le placer à la fin de la chaîne de caractères.

Exemple :

```cpp
#include <string>
using namespace std::string_literals;
...
int lgth = "123456"s.length();
```

### Les entiers

Plusieurs types d'entiers sont définis dans le langage :

- Les entiers signés : ```int```, ```short int```, ```long int```, ```long long int```
- Les entiers non signés : ```unsigned int```, ```unsigned short int```, ```unsigned long int```, ```unsigned long long int```

Le tableau suivant présente les tailles et limites des différents types d'entiers signés :

| Type       | Taille   | Plage de valeurs       |
|------------|----------|------------------------|
| ```signed char```  | 1 octet  | -128 à 127 |
| ```int```  | 2 ou 4 octets  | -$2^{15}$ à $2^{15}-1$ ou -$2^{31}$ à $2^{31}-1$ |
| ```short int``` | 2 octets  | -$2^{15}$ à $2^{15}-1$ |
| ```long int``` | 4 ou 8 octets  | -$2^{31}$ à $2^{31}-1$ ou -$2^{63}$ à $2^{63}-1$ |
| ```long long int``` | 8 octets | -$2^{63}$ à $2^{63}-1$ |

Pour les entiers de type ```int``` et ```long int```, la taille dépend de la plateforme. Sous Windows, un ```long int``` est représenté sur 32 bits. Sous Linux, un ```long int``` est représenté sur 64 bits.

Le tableau suivant présente les tailles et limites des différents types d'entiers non signés :

| Type       | Taille   | Plage de valeurs       |
|------------|----------|------------------------|
| ```unsigned char```  | 1 octet  | 0 à 255 |
| ```unsigned int```  | 2 ou 4 octets  | 0 à $2^{16}-1$ ou 0 à $2^{32}-1$ |
| ```unsigned short int``` | 2 octets  | 0 à $2^{16}-1$ |
| ```unsigned long int``` | 4 ou 8 octets  | 0 à $2^{32}-1$ ou 0 à $2^{64}-1$ |
| ```unsigned long long int``` | 8 octets | 0 à $2^{64}-1$ |  

On retrouve le même comportement pour les tailles que pour les types signés.

Notons que le type ```char``` peut représenter un entier mais la norme du C++ ne garantit pas que ce soit un type signé ou non signé.

### Contrôle de la taille des entiers

Le C++ est livré avec une composante de la bibliothèque standard permettant de contrôler la taille des entiers. Pour utiliser cette composante, il faut inclure le fichier d'en-tête ```<cstdint>```.

Cette composante définit des types entiers signés et non signés garantissant une taille spécifique indépendamment de la plateforme.

La syntaxe pour déclarer une variable de type entier signé est la suivante :

```cpp
std::int8_t nom_de_la_variable_1_octet;
std::int16_t nom_de_la_variable_2_octets;
std::int32_t nom_de_la_variable_4_octets;
std::int64_t nom_de_la_variable_8_octets;
```

La syntaxe est similaire pour les types non signés :

```cpp
std::uint8_t nom_de_la_variable_1_octet;
std::uint16_t nom_de_la_variable_2_octets;
std::uint32_t nom_de_la_variable_4_octets;
std::uint64_t nom_de_la_variable_8_octets;
```

Il existe également un entier non signé représentant l'étendue maximale de la plateforme pour lequel on compile le code :

```cpp
std::size_t taille;
```

qui représente un entier 64 bits pour une plateforme 64 bits et un entier 32 bits pour une plateforme 32 bits.

### Opérations sur les entiers

Les opérations possibles sur les entiers sont les suivantes :

- Les opérateurs arithmétiques : ```+```, ```-```, ```*```, ```/``` (division entière)
Exemple :

```cpp
int a = 10;
int b = 3;
int c = a / b; // c contient 3
```

- Le modulo : ```%```
Exemple :

```cpp
int a = 10;
int b = 3;
int c = a % b; // c contient 1
```

- Les opérateurs inplaces : ```+=```, ```-=```, ```*=```, ```/=```, ```%=```
Exemple :

```cpp
int a = 10;
a += 1; // a contient 11
```

- La pré- et post-incrémentation : ```++```
Exemple :

```cpp
int a = 10;
++a; // a contient 11 // Pré-incrémentation
a++; // a contient 12 // Post-incrémentation
```

La pré-incrémentation rajoute 1 à la variable avant de retourner sa valeur et la post-incrémentation retourne la valeur de la variable avant de l'incrémenter de 1. La pré-incrémentation est donc plus performante que la post-incrémentation.

- La pré- et post-décrémentation : ```--```
Exemple :

```cpp
int a = 10;
--a; // a contient 9 // Pré-décrémentation
a--; // a contient 8 // Post-décrémentation
```

La pré-décrémentation retire 1 à la variable avant de retourner sa valeur et la post-décrémentation retourne la valeur de la variable avant de lui retirer 1. La pré-décrémentation est donc plus performante que la post-décrémentation.

- Les opérateurs de comparaison : ```==```, ```!=```, ```<```, ```<=```, ```>```, ```>=```
Exemple :

```cpp
int a = 10;
int b = 3;
bool c = a == b; // c contient false
```

- Les opérateurs logiques : ```&&```, ```||```, ```!```
Exemple : 

```cpp
int a = 10;
int b = 3;
bool c = (a == b) || (a > b); // c contient true
```

- Transformer une chaîne de caractères en entier : ```std::stoi```, ```std::stol```, ```std::stoll```
Exemple :

```cpp
std::string s = "12345";
int a = std::stoi(s); // a contient 12345
```

### Formatage d'affichage des entiers

Afin de contrôler l'affichage des entiers en sortie, on utilise les services proposés par la composante ```<iomanip>``` de la bibliothèque standard.

En particuliers :

- La fonction ```std::setw``` permet de définir la largeur de la zone d'affichage.
- La fonction ```std::setfill``` permet de définir le caractère de remplissage pour la zone d'affichage.

Exemple :

```cpp
#include <iomanip>
...
int a = 123;
std::cout << std::setw(5) << std::setfill('0') << a << std::endl;
```

Ce code affiche la valeur de la variable *a* dans une zone d'affichage de largeur 5 en remplissant avec des zéros si nécessaire sur la gauche.

## Les flottants

Le C/C++ propose trois types de flottants :

- ```float``` : nombre à virgule flottante simple précision (32 bits)
- ```double``` : nombre à virgule flottante double précision (64 bits)
- ```long double``` : nombre à virgule flottante quadruple précision (128 bits en principe mais en fait 80 bits)

Les opérations arithmétiques sur les flottants sont similaires à celles des entiers. A savoir :

- Les opérateurs arithmétiques : ```+``` (somme), ```-``` (différence), ```*``` (produit), ```/``` (division)
- Les opérateurs inplaces : ```+=``` (somme), ```-=``` (différence), ```*=``` (produit), ```/=``` (division)
- Les opérateurs de comparaison : ```==``` (égalité), ```!=``` (différent), ```<``` (inférieur), ```<=``` (inférieur ou égal), ```>``` (supérieur), ```>=``` (supérieur ou égal)

La composante ```<cmath>``` de la bibliothèque standard propose les fonctions mathématiques usuelles pour les trois types de flottants. A savoir :

- Les fonctions trigonométriques :
  - ```std::sin```, ```std::cos```, ```std::tan```
  - ```std::asin```, ```std::acos```, ```std::atan```
  - ```std::atan2``` (arc tangente de y/x)
- Les fonctions de conversion :
  - ```std::floor```(partie entière inférieure),
  - ```std::ceil```(partie entière supérieure),
  - ```std::round```(arrondi)
- Les fonctions de puissance :
  - ```std::pow```
  - ```std::pow10``` (puissance de 10)
- Les fonctions racines :
  - ```std::sqrt```(racine carrée),
  - ```std::cbrt```(racine cubique)
- Les fonction exponentielles :
  - ```std::exp``` (exponentielle),
  - ```std::exp2```(exponentielle de base 2),
  - ```std::expm1```(exponentielle moins 1)
- Les fonctions logarithmes :
  - ```std::log```(logarithme népérien),
  - ```std::log10```(logarithme décimal),
  - ```std::log2```(logarithme de base 2),
  - ```std::log1p```(logarithme de 1 plus la valeur)
- Les fonctions hyperboliques :
  - ```std::sinh```,
  - ```std::cosh```,
  - ```std::tanh```
- La fonction valeur absolue : ```std::abs```
- Les fonctions maximales : ```std::max```
- Les fonctions minimales : ```std::min```
- La fonction FMA (multiply-add) : ```std::fma```
- Les fonctions significande et exposant : ```std::frexp```, ```std::ldexp```
- La fonction reste : ```std::remainder```
- La fonction copie de signe : ```std::copysign```
- La fonction modulo généralisé : ```std::fmod```

Depuis le C++ 17, la composante ```<cmath>``` propose les fonctions mathématiques suivantes :

- Les polynômes :
  - ```std::legendre``` (Legendre),
  - ```std::hermite``` (Hermite),
  - ```std::laguerre``` (Laguerre),
  - ```std::assoc_laguerre``` (Laguerre associé),
  - ```std::assoc_legendre``` (Legendre associé),
  - ```std::chebyshev_t``` (Tchebychev),
  - ```std::chebyshev_u``` (Tchebychev)
- Les fonctions elliptiques :
  - ```std::comp_ellint_1``` (commeplexe intégrale elliptique de première espèce),
  - ```std::comp_ellint_2``` (commeplexe intégrale elliptique de seconde espèce)
- Les fonctions gamma :
  - ```std::lgamma``` (logarithme de la fonction gamma),
  - ```std::lgamma_r``` (logarithme de la fonction gamma avec signe),
  - ```std::tgamma``` (fonction gamma)
- Les fonctions de bessel :
  - ```std::j0``` (Bessel de première espèce d'ordre 0),
  - ```std::j1``` (Bessel de première espèce d'ordre 1),
  - ```std::jn``` (Bessel de première espèce d'ordre n),
  - ```std::y0``` (Bessel de seconde espèce d'ordre 0),
  - ```std::y1``` (Bessel de seconde espèce d'ordre 1),
  - ```std::yn``` (Bessel de seconde espèce d'ordre n)
- Les fonctions d'erreur :
  - ```std::erf``` (fonction d'erreur),
  - ```std::erfc``` (complémentaire de la fonction d'erreur),
  - ```std::erfc_inv``` (inverse de la fonction d'erreur complémentaire),
  - ```std::erfc_scaled``` (fonction d'erreur complémentaire à grande précision)

### Les suffixes pour les flottants

Le C/C++ propose les suffixes suivants pour les flottants :

- ```f``` : flottant simple précision
- ```l``` : flottant long précision

Sans suffixe, le flottant est de type double.

Exemple :

```cpp
float a = 1.2345f;
double b = 1.2345;
long double c = 1.2345l;
```

### Les nombres flottants spéciaux

Depuis le C++11, la composante ```<limits>``` de la bibliothèque standard propose les constantes suivantes :

- ```std::numeric_limits<Real>::quiet_NaN()``` : NaN (Not a Number) qui ne met pas le processeur dans l'état d'erreur. Le comparateur ```==``` retourne toujours ```false```.
- ```std::numeric_limits<Real>::signaling_NaN()``` : NaN signalant qui met le processeur dans l'état d'erreur. Le comparateur ```==``` retourne toujours ```false```.
- ```std::numeric_limits<Real>::infinity()``` : Infinité. Il est toujours supérieur à tout nombre fini.
- ```std::numeric_limits<Real>::denorm_min()``` : Plus petit nombre dénormalisé.

où ```Real``` est un type de flottant (```float```, ```double``` ou ```long double```).

Exemple :

```cpp
#include <limits>
#include <iostream>
int main() 
{
    double x = std::numeric_limits<double>::quiet_NaN();
    std::cout << std::boolalpha <<"Nan==NaN? "<< x==std::numeric_limits<double>::quiet_NaN() <<std::endl;
    std::cout << "x n'est pas un nombre ? " << std::isnan(x) << std::endl;
    float finf = std::numeric_limits<float>::infinity(), fsup = std::numeric_limits<float>::max();
    std::cout << fx << " < ∞ ? :" << (fx < finf) << std::endl;
    return EXIT_SUCCESS; 
}
```

### Les constantes prédéfinies en C++ 20

Depuis C++20, la composante ```<numbers>``` de la bibliothèque standard propose les constantes suivantes (en double précision):

- ```std::numbers::pi``` : Constante π
- ```std::numbers::e``` : Constante e
- ```std::numbers::sqrt2``` : Racine de 2
- ```std::numbers::sqrt3``` : Racine de 3
- ```std::numbers::phi``` : Nombre d'or
- ```std::numbers::inv_sqrt3``` : Inverse de la racine de 3
- ```std::numbers::egamma``` : Constante d'Euler-Mascheroni
- ```std::numbers::log2e``` : Logarithme en base 2 de e
- ```std::numbers::log10e``` : Logarithme en base 10 de e
- ```std::numbers::ln2``` : Logarithme népérien de 2
- ```std::numbers::ln10``` : Logarithme népérien de 10

On peut également obtenir ces constantes en simple ou long double précision en précisant le type entre chevrons ```<``` et ```>```.

Exemple :

```cpp
long double x = std::numbers::pi<long double>;
```

## Les nombres complexes

Les nombres complexes ne sont pas un type primitif du C++. Ils sont représentés par la classe ```std::complex``` définie dans l'en-tête ```<complex>```.

Il est possible de définir des nombres complexes dont le type de base est choisi par le programmeur. Par exemple :

```cpp
std::complex<float> z1; // z1 = 0 + 0i
std::complex<double> z2(1.2, 3.4); // z2 = 1.2 + 3.4i
std::complex<long double> z3(z2); // z3 = 1.2 + 3.4i
std::complex<long> z4(1L, 4L); // z4 = 1 + 4i (nombre de Gauss)
```

L'initialisation d'un nombre complexe peut se faire de deux manières différentes :

- Initialisation classique (C++ 98) : ```std::complex<T> z(r, i);``` où *r* est la partie réelle et *i* la partie imaginaire.
- Initialisation par les fonctions membres ```real``` et ```imag``` : ```std::complex<T> z; z.real(r); z.imag(i);```
Exemple :

```cpp
std::complex<double> z(1.2, 3.4);
```

Depuis le C++ 17, il n'est plus nécessaire de préciser le type de base du nombre complexe.
Exemple :

```cpp
std::complex z(1.2, 3.4);     // double précision
std::complex zf(1.2f, 3.4f);  // simple précision
std::complex zld(1.2l, 3.4l); // long double précision
```

- Initialisation "naturelle" : il faut préalablement utiliser l'espace de nommage ```std::complex_literals``` et utiliser un suffixe pour la partie imaginaire.
Exemple :

```cpp
using namespace std::complex_literals;
std::complex<double> z = 1.0 + 2.0i;
std::complex<float> zf = 1.0f + 2.0if;
std::complex<long double> zld = 1.0l + 2.0il;
```

### Opérations sur les nombres complexes

Les opérations arithmétiques usuelles sont définies pour les nombres complexes. A savoir :

- Les opérateurs arithmétiques : ```+```, ```-```, ```*```, ```/```
- Les opérateurs inplaces : ```+=```, ```-=```, ```*=```, ```/=```
- Les opérateurs de comparaison : ```==``` (égalité), ```!=``` (différent)

Le type ```std::complex``` propose les services suivants :

- La fonction ```real``` retourne la partie réelle du nombre complexe.
Exemple :

```cpp
std::complex<double> z(1.2, 3.4);
double re = z.real(); // re contient 1.2
```

- La fonction ```imag``` retourne la partie imaginaire du nombre complexe.
Exemple :

```cpp
std::complex<double> z(1.2, 3.4);
double im = z.imag(); // im contient 3.4
```

- La fonction ```abs``` retourne le module du nombre complexe.
Exemple :

```cpp
std::complex<double> z(1.2, 3.4);
double mod = std::abs(z); // mod contient 3.65519
```

- La fonction ```arg``` retourne l'argument du nombre complexe.
Exemple :

```cpp
std::complex<double> z(1.2, 3.4);
double arg = std::arg(z); // arg contient 1.24904
```

- La fonction ```conj``` retourne le conjugué du nombre complexe.
Exemple :

```cpp
std::complex<double> z(1.2, 3.4);
std::complex<double> zconj = std::conj(z); // zconj contient 1.2 - 3.4i
```

- Le carré du module : ```std::norm```
Exemple :

```cpp
std::complex<double> z(1.2, 3.4);
double norm = std::norm(z); // norm contient 13
```

- La racine carrée : ```std::sqrt```
Exemple :

```cpp
std::complex<double> z(1.2, 3.4);
std::complex<double> sqrtz = std::sqrt(z); // sqrtz contient 1.84932 + 0.76537i
```

- La fonction ```exp``` : ```std::exp```
Exemple :

```cpp
std::complex<double> z(1.2, 3.4);
std::complex<double> expz = std::exp(z); // expz contient -13.1284 + 1.04274i
```

- Initialiser un nombre complexe à l'aide d'un module et d'un argument : ```std::polar```
Exemple :

```cpp
std::complex<double> z = std::polar(1.0, 1.0); // z contient 0.540302 + 0.841471i
```

- La fonction ```pow``` : ```std::pow```
Exemple :

```cpp
std::complex<double> z = std::pow(std::complex<double>(1.0, 1.0), 2.0); // z contient -1 + 0i
```

- La fonction racine carrée : ```std::sqrt```
Exemple :

```cpp
std::complex<double> z = std::sqrt(std::complex<double>(1.0, 1.0)); // z contient 1.09868 + 0.45509i
```

- Les fonctions trigonométriques : ```std::sin```, ```std::cos```, ```std::tan```
- Les fonctions trigonométriques inverses : ```std::asin```, ```std::acos```, ```std::atan```
- Les fonctions hyperboliques : ```std::sinh```, ```std::cosh```, ```std::tanh```
- Les fonctions hyperboliques inverses : ```std::asinh```, ```std::acosh```, ```std::atanh```
- Les fonctions logarithmiques : ```std::log``` (logarithme népérien), ```std::log10``` (logarithme décimal), ```std::log1p``` (logarithme de 1 plus la valeur)
- Les fonctions exponentielles : ```std::exp``` (exponentielle), ```std::exp2``` (exponentielle de base 2), ```std::expm1``` (exponentielle moins 1)

## Renommage de type

Depuis le C++ 11, il est possible de renommer un type avec l'opérateur ```using```.

Exemple :

```cpp
using cfloat = std::complex<float>;
```

ce qui permet d'éviter de préciser à chaque fois le type de base du nombre complexe.

Un autre avantage de renommer un type est que l'on peut facilement changer le type de base du nombre complexe en modifiant uniquement la déclaration ```using```.

Exemple :

```cpp
using complexe = std::complex<float>;
complexe z(1.0, 2.0); // z est un nombre complexe de type float
```

Il suffit de modifier la déclaration ```using``` pour changer le type de base du nombre complexe.

Exemple :

```cpp
using complexe = std::complex<double>;
complexe z(1.0, 2.0); // z est un nombre complexe de type double
```

## Déclaration implicite de type

On peut remarquer lors de la déclaration d'une variable que le compilateur peut déduire le type de la variable à partir de la valeur initiale.

Par exemple :

```cpp
std::complex z{1.,2.};
std::complex z2 = z * z; // Puisque z est un nombre complexe, z2 est aussi un nombre complexe
```

L'utilisation de l'opérateur ```auto``` permet de déclarer une variable dont le type est déduit par le compilateur à partir de la valeur initiale.

En reprenant l'exemple précédent :

```cpp
std::complex z{1.,2.};
auto z2 = z * z; // C++ déduit que z2 est un nombre complexe de type std::complex<double>
```

L'utilisation de ```auto``` permet de simplifier l'écriture du code et de rendre le programme plus lisible.

Par exemple, en C++ 98, si on voulait parcourir un tableau dynamique contenant des doubles, on écrirait :

```cpp
std::vector<double> v(10);
...
for (std::vector<double>::iterator it = v.begin(); it != v.end(); ++it) {
    // ...
}
```

A partir de C++ 11, on peut simplifier cette écriture en utilisant la déclaration implicite de type :

```cpp
std::vector<double> v(10);
...
for (auto it = v.begin(); it != v.end(); ++it) {
    // ...
}
```

## Valeurs constantes et expressions constantes

C++ permet de définir des valeurs constantes au moment de la compilation. Il suffit pour cela d'utiliser le mot-clé ```const``` avant ou après la déclaration du type de la variable.

Exemple :

```cpp
const int a = 123;
a = 456; // Erreur à la compilation
```

Sauf si la valeur déclarée constante est une simple valeur littérale, la valeur constante sera évaluée à l'exécution :

```cpp
double const pis3 = 3.14159265358979323846 / 3; // pis3 vaut 1.04719755119646657182
```

En revanche, si on déclare une constante avec le mot-clé ```constexpr```, la valeur constante sera évaluée à la compilation :

```cpp
double const pis3 = 3.14159265358979323846 / 3; // pis3 vaut 1.04719755119646657182
double const cos_pis3 = std::cos(pis3); // cos_pis3 vaut 0.5 évalué à l'exécution
```

Depuis C++ 11, il est possible de définir des constantes avec le mot-clé ```constexpr```. Une constante définie avec ```constexpr``` est une constante évaluée à la compilation.

Exemple :

```cpp
constexpr double a00 = 1., a10 = 2., a01 = 3., a11 = 4.;
constexpr auto det = a00 * a11 - a10 * a01; // det vaut -2 évalué à la compilation
```

Si une partie de l'expression ```constexpr``` n'est pas une constante, la valeur ne sera pas évaluée à la compilation :

```cpp
double const x = 2;
double const y = -1.5;
constexpr auto interp = a00 + a10 * x + a01 * y + a11 * x * y; // interp n'est pas évalué à la compilation
```

## Les références

Les références sont l'une des fonctionnalités les plus puissantes et utiles du C++. Elles offrent un moyen sûr et efficace de manipuler des données sans avoir à copier leur contenu ou à utiliser des pointeurs. Pensez à une référence comme à un "alias" ou un "surnom" pour une variable existante.

### Qu'est-ce qu'une référence ?

Une référence est essentiellement une autre façon de nommer une variable existante. Lorsque vous créez une référence, vous ne créez pas une nouvelle variable distincte, mais plutôt un nouveau nom pour accéder à la même donnée.

Imaginez que vous ayez un ami nommé Robert. Tout le monde l'appelle "Bob". Que vous l'appeliez Robert ou Bob, vous parlez toujours de la même personne. C'est exactement comme ça que fonctionnent les références en C++.

### Pourquoi utiliser des références ?

Les références sont utiles pour plusieurs raisons :

1. **Efficacité** : Passer des arguments par référence à une fonction évite de copier de grandes quantités de données.
2. **Modification directe** : Elles permettent de modifier directement la variable originale dans une fonction.
3. **Syntaxe propre** : Elles offrent une syntaxe plus propre que les pointeurs pour de nombreuses opérations.

### Comment déclarer et utiliser une référence

Pour déclarer une référence, on utilise le symbole `&` après le type de la variable. Voici un exemple simple :

```cpp
int original = 42;
int& reference = original;

std::cout << original << std::endl;   // Affiche 42
std::cout << reference << std::endl;  // Affiche aussi 42

reference = 100;  // Modifie la valeur de 'original'
std::cout << original << std::endl;   // Affiche maintenant 100
```

Dans cet exemple, `reference` est une référence à `original`. Toute modification de `reference` affecte directement `original`, car elles font référence à la même donnée en mémoire.

Les références sont un outil puissant en C++, et nous explorerons leurs utilisations plus avancées dans les sections suivantes.

Il est possible de déclarer une référence constante en ajoutant le mot-clé ```const``` avant le type de la variable.

Exemple :

```cpp
const int& reference = original;
```

On fait ainsi référence à une variable sans pouvoir la modifier au travers de la référence :

```cpp
reference = 100; // Erreur à la compilation car référence constante
```

## Les conversions de type

Il arrive souvent qu'on veuille convertir une valeur d'un type à un autre. C++ propose plusieurs moyens de réaliser ce type de conversion.

- La conversion implicite : elle est autorisée lorsqu'il n'y a pas de perte d'information et c'est le compilateur qui la réalise automatiquement.
Exemple :

```cpp
int a = 3;
double b = a; // Conversion implicite de int à double
```

- La conversion explicite impérative à la "C" : on convertit explicitement la valeur du type source au type cible sans vérification. Syntaxe : ```(type_cible)valeur_source```
Exemple :

```cpp
int a = 3;
double b = (double)a; // Conversion explicite de int à double
```

- La conversion explicite impérative à la C++ : même chose qu'au dessus mais avec une syntaxe légèrement modifiée : ```type_cible(valeur_source)```
Exemple :

```cpp
int a = 3;
double b = double(a); // Conversion explicite de int à double
```

- la convertion statique. Le c++ vérifie que la conversion est possible à la compilation. Syntaxe : ```static_cast<type_cible>(valeur_source)```
Exemple :

```cpp
int a = 3;
double b = static_cast<double>(a); // Conversion explicite de int à double
```

- la conversion dynamique. La conversion est réalisée à l'exécution. Syntaxe : ```dynamic_cast<type_cible>(valeur_source)```. Cette conversion ne peut fonctionner que si la valeur source est un pointeur ou une référence polymorphique (voir le cours sur la POO).
Exemple :

```cpp
Base* ptr = new Derived();
Derived* derv = dynamic_cast<Derived*>(ptr);
```

Exemples de conversions autorisées et non autorisées :

```cpp
sing dcomplex=std::complex<double>;
dcomplex z;
std::uint32_t uval32 = 3;
z = (dcomplex)uval32;// Valide, z vaut 3. + 0.i
z = dcomplex(uval32);// Valide, z vaut 3. + 0.i
z = static_cast<dcomplex>(uval32);// Valide, z vaut 3. + 0.i
z = 3. -2.i;
uval32 = (std::uint32_t)z;// Impossible. Erreur de compilation !
uval32 = (std::uint32_t&)z;// Possible mais non valide, uval32 vaut 0 !
uval32 = static_cast<std::uint32_t&>(z);// Possible mais non valide, erreur de compilation !
```

Il vaut mieux toujours utiliser les conversions statiques plutôt que les conversions implicites ou les conversions à la "C".


