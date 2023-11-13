---
title: Introduction au C++
---
# Introduction

## Qu'est-ce que le C++ ?

### Un peu d'histoire

On ne peut parler de l'histoire du C++ sans parler de l'histoire du C dont le C++ est au départ "une amélioration", et il est également impossible de parler de l'histoire du C sans parler de l'histoire du système d'exploitation UNIX.

En 1969, la première version du système UNIX voit le jour dans les laboratoires Bell, dans le New Jersey, conçu pour une machine appelée coquettement DEC PDP-7. Le langage utilisé pour écrire ce système d'exploitation était l'assembleur. Or l'assembleur est un langage dépendant du processeur orchestrant la machine et trop proche du matériel informatique utilisé ce qui empêche un bon suivi et évolution des logiciels.

Peu après l'apparition d'UNIX, Ken Thompson créa un nouveau langage de programmation, qu'il baptisa **B**, lui-même inspiré du langage BCPL (Basic Combined Programming Language, développé par Martin Richards). Le but du langage B était de créer un langage plus simple que le BCPL, lui-même étant déjà une simplification du langage CPL. Mais ce but ne fut que trop bien atteint, et le B s'avéra être un peu trop simple et trop dépendant de l'architecture.

Peu après l'apparition du B, une nouvelle machine fut introduite sur le marché par DEC : le PDP-11. UNIX et B ont tout de suite été transférés vers cette nouvelle architecture, doté d'un processeur plus rapide que le PDP-7. Mais réécrire UNIX en assembleur (les assembleurs étant dépendant des processeurs ou des familles de processeurs employés) était une tâche trop ardue, et on envisagea de le réécrire en B. On buta alors sur le problème que le langage B était relativement lent, dû au fait qu'il s'agissait d'un langage interprété (comme Python ou le Java aujourd'hui).

C'est pour cette raison qu'en 1971, on commença à travailler sur le successeur du langage B, nommé naturellement langage C. On s'accorde pour dire que Dennis Ritchie fut le véritable créateur du C. La puissance du C était véritable : ce langage n'avait pas été fait spécifiquement pour un type de machine, ou pour un système particulier. Cela en faisait un langage hautement portable. De plus, son rayon d'action s'étend du bas niveau de la machine (le C peut générer du code aussi rapide que du code assembleur), au haut niveau des langages orientés problèmes. Virtuellement, on peut donc tout faire avec du C : du pilote de matériel jusqu'au logiciel de gestion, en passant par les jeux.

Le C devint vite tellement populaire que tout le monde voulait en faire sa propre version avec ses propres "améliorations". Si bien que les différents compilateurs devinrent rapidement incompatibles les uns avec les autres, et on avait perdu une grande part de la portabilité du C. L'idée vint alors qu'il fallait créer un standard pour le langage C. C'est un comité de l'ANSI (American National Standards Institute) qui mit au point ce standard en 1983, et depuis, la plupart des compilateurs (Borland, Microsoft, Intel, GNU, NVIDIA,...) se sont pliés à ce standard, si bien qu'un programme écrit en ANSI C est en principe compilable presque partout.

Le langage C possédait donc de nombreux avantages. Mais il lui manquait certaines caractérisrique des langages dit modernes : la programmation orientée objet, la programmation fonctionnelle, \ldots

Le Dr. Bjarne Stroustrup, ingénieur de recherche au Bell Laboratories, décida au début des années 80 de créer un langage orienté objet performant  dont l'apprentissage devait être moindre. Pour cela, il décida de créer son langage comme une extension d'un langage de programmation populaire. A cette époque, le langage de programmation le plus populaire chez les professionels était le langage C. Aussi le Dr. Stroustrup décida de créer son langage orienté objet comme une extension du langage C dont il préserva la compatibilité  et le baptisa naturellement C++.  Pour la programmation orienté objet, il s'inspira de deux langages orientés objets de l'époque : les langages Simula67 et Algol68. Afin de toucher un large public, il décida également d'en faire un langage ouvert et gratuit, ce qui contribua grandement au succès du C++ (au dépend d'autres langages plus "propres" comme Eiffel). Il est à remarquer que dans ses premières versions, le compilateur C++ n'était qu'un traducteur du langage C++ vers le langage C !

Mais, de la même façon que le langage C, l'évolution du langage C++ commença rapidement à diverger entre les éditeurs de compilateur. Dans le courant de l'année 1994 les comités de normalisation ISO et ANSI ont donc publié une version préliminaire officielle du C++ X3 JI 6/WG21. La dernière version préliminaire fut publiée en décembre 1996. A part quelques points de détail, elle comportait l'essentiel de ce qui allait être la version définitive, datée du 27 septembre 1998 notée **norme ISO/IEC 14882:1998(E)**. On se réfère à ce standard en parlant du C++ 98.

Pendant de nombreuses années, le standard resta figée. Une première mise à jour, essentiellement pour
corriger quelques problèmes liés au standard 98 (en particuliers des omissions dans la norme) fut effectuée en 2003 (**standard ISO/IEC 14882:2003, C++ 03**).  La vraie évolution du langage eu lieu avec la sortie d'un nouveau standard le 12 Août 2011 (**standard ISO/IEC 14882:2011, C++ 11**) qui apporta un grand nombre de nouveautés et changea définitivement la manière de programme en C++. Depuis, le standard est mis à jour tous les trois ans, en rajoutant de nouvelles fonctionnalités permettant de repousser les limites du langage sans pour autant apporter une révolution aussi grande. que celle de 2011 Il existe donc actuellement un standard datant du 18 Août 2014 ( C++ 14 ) qui apporte quelques améliorations au C++ 11, une autre de Mars 2017 (C++ 17) qui corrige certains défauts du C++14  en enlevant certaines fonctionnalités mal définies du langage et en rajoutant beaucoup de nouveautés, et finalement la version actuelle publié par l'ISO (avec un peu de retard dû au COVID\ldots) en Décembre 2020 qui rajoute un grand nombre de nouveautés au langage. La prochaine version du standard devrait donc apparaître à la fin de cette année (2023).

Notons qu'un des grands efforts effectués lors de l'adoption des nouvelles normes est de permettre une programmation plus simple et concise de certaines notions du C++.

### Caractéristiques du langage C++

Le C++ est un langage :
  - **compilé** : il n'existe pas en standard d'interpréteur du langage C++. Il faut donc dans un premier temps utiliser un compilateur qui lit les fichiers sources et les transforment en langage machine (dans des fichiers dit objets) directement compréhensible par le processeur de la machine sur laquelle il a été compilé puis créer éventuellement un exécutable directement exploitable sur le système d'exploitation sur lequel il a été créé. Il n'est pas possible d'utiliser directement un code compilé pour un processeur incompatible avec celui pour lequel on a compilé et il n'est  pas possible d'exécuter directement un exécutable créer pour un autre système d'exploitation.
  - **performant** : Aujourd'hui, le C++ est un langage aussi, voir plus performant que le langage C. Il est le langage le plus rapide actuellement (battu récemment par le lnagage Rust pour certaines applications)
  - **multi-paradigmes** : le langage C++ permet d'utiliser différents paradigmes de programmation, à savoir :
    - *La programmation structurée* : Comme en C, on décompose le problème en fonctions agissant sur des structures de données;
    - *La programmation orientée objet* : On se concentre sur la gestion des données, à savoir comment les gérer (protocole) et la façon de les gérer (interface);
    - *La programmation fonctionnelle* : On décompose le problème en un ensemble de fonctions (dans un sens proche des mathématique) qu'on manipule (en les composant, etc.) afin de créer l'application visée.
  A noter qu'il est fortement déconseillé lors d'un projet informatique de se limiter à un seul paradigme de programmation. Un paradigme sera sûrement plus adapté qu'un autre pour une partie du projet mais pas nécessairement pour une autre partie. Il faut donc rester pragmatique et savoir utiliser le bon paradigme de programmation pour aborder le plus simplement et efficacement possible le problème à résoudre.
 
  Une des autres forces du langage C++ (par rapport au C en particuliers), est d'être doté d'une bibliothèque standard très riche (un peu comme le langage python) qui permet de gagner un temps appréciable pour l'élaboration d'un programme. On verra au fur et à mesure du cours certaines parties de cette bibliothèque (il faudrait plusieurs semaines pour aborder tout ce que propose cette bibliothèque !).

En revanche, l'héritage du C fait que le langage C++ est un langage complexe à apprendre et impossible à maitriser à 100%. Le créateur du C++,
le dr. Bjarne Stroustrup a lui-même estimé qu'il ne connaissait qu'environ 70% du langage. Il est donc illusoire de vouloir totalement maîtriser ce langage. Il est plutôt conseillé d'apprendre petit à petit à maîtriser des parties du langage qui vous permettront de résoudre efficacement les problèmes que vous rencontrer.

## Compiler des sources en C++

### Les compilateurs disponibles (et gratuits !)

**Sous Linux** :
  - *Le compilateur gnu g++* : le compilateur *g++* n'est pas installé par défaut (contrairement à gcc). Il est néanmoins disponible dans les paquets proposer par votre distribution (voir la documentation de votre distribution pour installer g++). Sur les machines ONERA, il est possible de charger un module contenant une version relativement récente des compilateurs gnu (qui contient une version récente de gcc et de g++)
  - *Le compilateur clang* : Un compilateur aussi performant (voir plus) que le compilateur gnu. Le compilateur clang est accompagné de nombreux outils, dont un pour formater votre code d'une manière très précise et un permettant de vérifier les erreurs de compilation à la volée. Ces deux outils sont interfaçables avec des éditeurs de code (vim, vscode, etc.)
  - *Le compilateur intel* : Un compilateur pendant longtemps payant mais devenu gratuit depuis qu'il est livré avec OneAPI. A remarquer que dans les versions récentes des compilateurs intels, il ne faut plus utiliser *icpc* bien trop bogué mais *icpx* qui est  son remplaçant, basé sur le compilateur clang. *icpc* est prévu pour disparaître de oneAPI dans la prochaine version qui sortira au dernier trimestre 2023. Les compilateurs intels récents sont disponibles sur les postes linux de l'ONERA et les grands calculateurs. Ils sont très performants et offrent une micro librairie vectorisée pour certaines fonctions intrinsiques (trigonométriques, exponentielles, etc.) utilisée lors de la compilation de code et permettant un gain significatif des performances.
  - *Le compilateur NVIDIA* : Basé sur le compilateur PGI (Portland Group) racheté par NVIDIA, ce compilateur est un peu en retrait des autres compilateurs en ce qui concerne  la norme du C++  pris en compte par ce compilateur. Cependant, il offre l'avantage de pouvoir à l'aide de directives de compilation OpenACC d'effectuer des calculs sur un GPU NVIDIA (ce point n'est pas abordé dans ce cours).

**Mac OS** : Pour avoir accès à des compilateurs C++, il faut installer *Homebrew* qui est un environnement gratuit. Vous pouvez alors avoir accès à clang (fournit également avec XCode) et g++.

**Windows** : Plusieurs options s'offrent à vous :
  - Utiliser Microsoft Visual C++ community : Permet d'avoir un IDE pour programmer. La compilateur est de bonne facture mais sa version gratuite (community) ne permet pas de produire un code optimisé. En ce qui concerne les postes windows, il est possible de demander à la DSI de l'installer;
  - CodeBlock : Un IDE fournit avec g++ et qui comme Microsoft Visual C++ permet de créer des projets C++. Code block est fourni par défaut sur les postes Windows de l'ONERA;
  - MSYS 2 :  MSys est à proprement parler un ensemble d'outils offrant un environnement *à la UNIX* pour Windows (terminal, makefile, compilateurs, éditeurs, bibliothèques, latex, gimp, etc. ) pouvant être installé avec uniquement des droits utilisateurs. Les compilateurs fournis (C, C++, fortran, rust, ada, etc.)  permettent de compiler des sources et de produire des bibliothèques et des exécutables pour le système d'exploitation Windows. Cet environnement est basé sur une distribution Linux (Arch Linux). On peut gérer les différents outils comme sous de nombreux linux à l'aide d'un gestionnaire de paquets qui propose les dernières versions de g++ ou de clang. En revanche, il faut avoir une petite base du shell pour  faire fonctionner tout cela sans problème. A recommander à ceux habitués à un environnement UNIX !

**Android** : Dans le google store, on peut trouver des IDEs primaires fournis avec des  compilateurs gratuits C++ fonctionant sous téléphone portable et tablette androïd. Ces compilateurs sont tous basés sur la version de g++ pour ARM.

**Web** : Un site web permettant de pouvoir compiler et d'exécuter des codes simples (largement suffisant pour le TP !) peut être trouver à  la page suivante :
    https://www.onlinegdb.com/online_c++_compiler

## Les différentes phases de compilation

Bien que ces phases ne soient pas toujours perceptibles par l'utilisateur, elles ont lieu effectivement :

  1. La phase de **précompilation** : Le compilateur va analyser votre source et dans une certaine mesure l'interprétée (on verra qu'en C++ on peut contrôler à l'aide du langage cette phase d'interprétation pour exécuter une partie du code durant cette phase). C'est là aussi que le compilateur va pouvoir remplacer certaines parties du code selon certaines directives de compilation qu'on aura écrit dans le code (macros, directives de pré-processings). Le compilateur *in fine* va donc produire un nouveau source qui aura pris en compte les directives de compilation et les résultats de la partie du code interprété.
  2. La phase de **compilation** :  A partir du nouveau source généré par la pré-compilation, le compilateur va analyser le code écrit pour le transformer dans un pseudo-assembleur (qui dépend du compilateur employé) en pouvant selon les options passées au compilateur optimiser la taille ou la rapidité d'exécution du source analysé.
  3. La phase de **post-compilation** : A partir du pseudo-assembleur généré, selon la machine cible  pour lequel le fichier source est compilé,  le compilateur C++ génère du source assembleur en adéquation avec le langage machine compris par le processeur de la machine cible puis transforme ce source assembleur en fichier binaire (langage machine) et rajoute éventuellement d'autres instructions binaires permettant de faire exécuter le code (si on veut un exécutable) sur le système d'exploitation employé.

## Invocation des compilateurs

Sauf mention contraire, tous les exemples seront donnés en invoquant le compilateur gnu g++. Cependant, mis à part le compilateur Visual C++, tous les compilateurs présentent les mêmes options et il suffira dans la grande majorité des cas de remplacer g++ par le nom de votre compilateur préféfé.

Pour Visual C++, les options sont accessibles via la configuration du projet dans le menu projet de l'IDE.

Tous les exemples donnés ici se feront avec g++, mais sauf mention contraire,  il suffira simplement de remplacer g++ par votre compilateur préféré,  à l’exception de visual c++ qui en ligne ne possède pas les mêmes options.  Cependant, on peut s’affranchir pour ce dernier de cette étape en compilant directement à partir de l’interface proposée par l’IDE de Visual C++.

Nous ne verrons ici que principales options utiles lorsqu'on utilise un compilateur. Les exemples donnés feront un usage direct du compilateur C++ mais dans la pratique l'utilisation du compilateur se fera à l'aide d'un *outil de production* : Makefile, gestionnaire de projet, ...

L'usage le plus simple d'un compilateur est de créer un exécutable directement à partir d'un fichier source :

    g++ -o <nom de  l'exécutable à créer> <nom fichier source à compiler>

---
*Exemple* : Dans le répertoire Exemple/Basic, compilons le fichier hello_world.cpp et créons à partir de ce fichier l'exécutable HelloWorld.exe :

        g++ -o HelloWorld.exe hello_world.cpp
---

Malheureusement, de nombreuses autres options risquent d'être nécessaires dans la majorité des cas.

### Cas où le projet contient plusieurs fichiers sources

### Création du code binaire final : exécutable, bibliothèque statique ou dynamique  ?

### Choix de la norme C++ à utiliser pour la compilation

En premier lieu, on peut légitement se poser la question de la norme C++ utilisée par défaut par notre compilateur et comment modifier la version de la norme à employer.

La norme C++ utilisée par défaut par votre compilateur sera en général dépendante de la version du compilateur que vous utiliserez (plus la version de votre compilateur sera récente, plus la norme C++ utilisée sera récente également). Actuellement, les dernières version de g++ et de clang++ utilisent par défaut le C++ 17.

La principale raison pour laquelle un compilateur ne prend pas par défaut la dernière version de la norme C++ est qu'il faut en général plusieurs années pour que cette version de la norme soit dans la plus grande partie mise en oeuvre dans le compilateur, et ce dernier va donc proposer la norme aboutie la plus récente. Il faut avoir conscience que créer un compilateur C++ avec les normes actuelles est loin d'être un exercice trivial !

  *Comment changer la norme C++ utilisée par votre compilateur ?*
 
L'option **-std** permet   de modifier la norme employée par le compilateur. Cela permet en particuliers d'accèder à une version de la norme C++ plus récente que celle par défaut utilisé par le compilateur. Par contre, il faut dans ce cas faire attention à ce que la fonctionnalité utilisée, apportée par une norme plus récente que la norme par défaut soit bien mis en oeuvre par le compilateur employé. Cela permet également de pouvoir tester des fonctionnalités qui doivent arriver dans la prochaine version : par exemple il est possible avec les compilateurs les plus récents de tester certaines fonctionnalités de la norme C++ 23 qui doit être définitivement adoptée à la fin de cette année.

A contrario, demander au compilateur de se conformer à une version plus ancienne de la norme peut vous assurer une meilleure portabilité de votre code, en particuliers sur des machines possédant des compilateurs C++ plus anciens.

Voici les options à fournir pour les différentes versions de la norme :

  - **-std=c++98** pour que le compilateur s'assure que vos sources soient conformes à la norme C++ 98 du C++
  - **-std=c++11** pour que le compilateur s'assure que vos sources soient conformes à la norme C++ 11 du C++
  - **-std=c++14** pour que le compilateur s'assure que vos sources soient conformes à la norme C++ 14 du C++
  - **-std=c++17** pour que le compilateur s'assure que vos sources soient conformes à la norme C++ 17 du C++
  - **-std=c++20** pour que le compilateur s'assure que vos sources soient conformes à la norme C++ 20 du C++
  - **-std=c++0x** pour commencer à utiliser la prochaine norme C++ à sortir par rapport à la date de parution du compilateur. **A VERIFIER**

### Les options à utiliser pendant la phase de développement

On peut scinder ces options en deux grands groupes :
    -

### Les options à utiliser pendant la phase de débogagge

Durant la phase de développement, il est conseillé d'utiliser au maximum les options de compilation permettant de vérifier la qualité de votre code et de détecter de potentiels bogues:

- *-g* : Permet de conserver les noms symboliques des fonctions et des variables afin de pouvoir utiliser un logiciel de débogage qui pourra ainsi interroger le code pour vérifier l'état des variables, l'endroit où on se trouve dans le code source et la pile d'appel.
- *-Wall* : Active tous les messages d'alertes (warning) pointant les éventuelles maladresses ou bogues potentiels dans le code, dont :

  - Les variables utilisées mais non initialisées;
  - Les conversions d'entiers non compatibles;

Pour g++ ( et clang++ ), on a de plus :

- *-Weffc++* : Vérifie que vous suivez certaines règles de codage établi par **Scott Meyer** dans son livre **EFfective C++** qui permet de minimiser les bogues et avoir un code efficace;
- *-pedantic* : S'assure que vous suivez bien *stricto sensu* la norme du C++ (dépendra de la norme que vous avez préciser vouloir utiliser)
- *-D_GLIBCXX_DEBUG* : Permet d'utiliser la version de développement de la bibliothèque standard du C++, ce qui permet de détecter des bogues tels que des indices non valides pour les tableaux...

Il existe d'autres options qu'on utilisera de manière plus sporadique permettant :

- De détecter les fuites mémoires
- Les concurrences mémoires dans un code multithreadé
- etc.

Ces options dépendent des compilateurs. Pour g++ et clang++ sous Linux,on pourra regarder la famille d'options commençant par *-fsanitize...* qui permettent de détecter des problèmes à l'exécution, dont :

- *-fsanitize=address* : pour détecter si on cherche à accèder à un tableau après l'avoir détruit en mémoire ou bien si à la sortie du code, un tableau n'a pas été détruit en mémoire ou encore si on accède à des adresses mémoires qui ne sont pas allouées;
- *-fsanitize=thread* : pour détecter des conditions de conflits mémoires (*dara race*) lorsqu'on utilise le multithreading;
- *-fsanitize=undefined* : pour détecter des comportements indéfinis (division par zéro, obtenir la valeur référencée par un pointeur nul, pour une fonction retournant une valeur ne pas retourner de valeur,...)

Il existe plusieurs dizaines de vérifications différentes avec cet argument ! Notons que ces tests ne marchent pas sous Windows du fait que la bibliothèque *san* n'a pas été porté sur cet OS (Pour Mac OS X, je ne sais pas).

**Remarque** : L'exécution de votre code sera relativement lent avec ces options lors de la phase de développement, mais elle vous permettra   de détecter un nombre conséquent de bogues potentiels. 

### Les options à utiliser pendant la phase d'optimisation

Le but ici est d'avoir le code le plus compact et rapide possible.
On veut en outre éliminer certains tests effectuer lors de la phase de développement :

- *-O2* ou *-O3* : Demande au compilateur d'optimiser votre code afin d'en accélérer l'exécution. *-O2* optimise votre code tout en garantissant que l'ordre des opérations du code source soient respecté. *-O3* quant à lui optimise votre code en se permettant de modifier l'ordre des opérations, ce qui ne garantit donc pas une solution identique à celle obtenue lors de la phase de développement. En pratique, si on détecte que l'option *-O3* pose des problèmes (ce qui arrive tout de même très très rarement), ou si l'ordre des opérations est primordiale, on baissera le niveau d'optimisation à *-O2*
- *-march=native* ou *-march=<type d'architecture de processeur visé>* : Optimise et produit du code pour l'architecture de processeur visé. Si on a spécifié *native* au lieu de l'architecture, le compilateur détectera le type d'architecture du processeur de l'ordinateur sur lequel il compile et optimisera et produira du code en fonction de l'architecture locale. **Attention** : Sur certains calculateurs parallèle de l'ONERA (sator), l'architecture des n{\oe}uds d'exploitation sur lequels on compile le code est plus récent que l'architecture des n{\oe}uds de calcul (sur lequel on exécute le code !)
- *-DNDEBUG* : Permet de ne pas tenir compte de certains testes de débogage mis dans le code. En particulier, permet d'ignorer toutes les assertions mises dans votre code (voir plus loin dans le cours).

Pour des projets conséquents et de manière générale, il est conseillé d'utiliser un outil pour la compilation du code permettant de détecter les dépendances entre vos différents fichiers et de ne recompiler que le strict minimum  nécessaire pour conserver un code cohérent. Pour cela, de nombreux outils existent tels que :

- Makefile
- Ninja
- Scons
- ...

On peut également utiliser un gestionnaire de projet, soit intégré dans un IDE comme Visual C++, ou bien encore *CMakefile* qui est supporté par toutes les plateformes existantes.


## Des bonnes pratiques de programmation

Lorsqu'on programme, on passe un certain temps à écrire du code, mais on passe beaucoup plus de temps à **lire**
du code que soi-même ou d'autres ont écrit. Il est donc important d'avoir un code clair et agréable à lire.

On peut faire l'analogie entre l'écriture d'un code et l'écriture d'un texte. Lorsque le texte est mal écrit et mal présenté, qu'il contient des fautes d'orthographe, que les phrases sont mal structurées et que les idées ne sont pas organisées, ce texte est très difficile à lire et donc à comprendre. Il en va de même pour le code : un code brouillon est très diffile et fatiguant à comprendre... de plus, les bogues s'y cachent beaucoup plus facilement.

Considérons le code (en C) suivant :

    int k(int i)
    {
        int rsflkj = 1; if (i==1) return rsflkj; else rsflkj = i;
                    return rsflkj * k(i-1);
    }

Arrivez-vous du premier coup d'{\oe}il à savoir ce que fait cette fonction ? C'est la fonction factorielle. Elle serait bien plus simple à comprendre avec un code bien écrit, non ?

Il est donc très important de respecter certaines bonnes pratiques de programmation qui s'appliquent naturellement à la
rédaction d'algorithmes pour rendre le plus agréable possible la lecture de code.

Cette section n'a pas vocation à vous inventorier toutes les bonnes pratiques de programmation, ce n'est pas la vocation première de ce cours, mais vous donne déjà quelques éléments essentiels là-dessus (on reparlera également de bonnes pratiques dans divers chapitres de ce cours).

### Contrat--Interface contre mise en {\oe}uvre d'un algorithme

Le **contrat** caractèrise l'**interface** d'un algorithme, c'est-à-dire qu'il explique le plus clairement possible ce que l'algorithme est capable de produire comme sorties étant donné ce qu'on lui fournit en entrée. On y spécifiera les conditions en entrée de l'algorithme (les pré-conditions) qui vont décrire les valeurs que peuvent prendre les données fournies en entrées pour que l'algorithme soit capable de fonctionner, et les conditions en sortie de l'algorithme (post-conditions) qui nous renseignera sur ce que l'on peut attendre à obtenir comme résultats.

Par conséquent, lorsqu'on consulte le contrat d'un algorithme, on est renseigné sur ce à quoi on peut s'attendre, ainsi que sur les limites de l'algorithme que l'on va utiliser, sans pour autant avoir besoin de comprendre comment l'algorithme est mise en oeuvre. Il nous appartient de composer avec ces informations.

Le contrat permet donc de savoir très exactement ce que l'algorithme est capable de faire, mais il ne dit rien sur **comment** l'algorithme va s'y prendre pour résoudre le problème.

### Précondition et post-condition

Les préconditions et les postconditions sont des conditions faisant partie du contrat relatif à un algorithme.

Les *préconditions* sont des conditions vérifiant que les données connues à l'entrée de l'algorithme appartiennent bien au domaine de définition de l'algorithme et qu'elles sont cohérentes entre elles.

Les *post-conditions* sont des conditions vérifiant que les données en sortie appartiennent bien à l'image de l'algorithme ou du moins ont des valeurs cohérentes et attendues par rapport à ce que fait l'algorithme.

Ainsi par exemple, prenons un algorithme calculant la racine carrée d'un nombre réel :

- L'unique pré-condition de cette fonction est que le nombre réel soit positif ou nul;
- L'unique pré-condition de cette fonction est que la racine carrée retournée soit positive ou nul;

Si on traduit cela en C ou C++, on utilisera les assertions que l'on trouve dans la bibliothèque *assert.h* (en C) ou *cassert* en C++. Les assertions sont des fonctions demandant en entrée une condition. Si cette condition à l'exécution est vérifiée,
le programme continue son exécution, sinon le programme s'arrête sur l'assertion et affiche la ligne et le fichier où l'assertion n'a pas été vérifiée. Les assertions ne sont activées que si l'option *-DNDEBUG* a été omise, sinon elles sont ignorées par le compilateur. Ainsi, pour notre racine carrée, nous traduirons la pré-condition et la post-condition par :

    #include <assert.h> // assert.h accepté aussi en C++, mais on préfère #include <cassert>

    double sqrt(double x)
    {
        assert(x>=0); // Pré-condition

        sq = ...           // Calcul de la racine qu'on stocke dans sq

        assert(sq >= 0); // Post-condition

        return sq;
    }

La simple lecture du code nous indique donc les valeurs valides pour cette fonction et les conditions sur les valeurs de retour.

Les préconditions et les postconditions peuven être des conditions demandant eux-mêmes un algorithme permettant de vérifier l'état ou les états de valeurs en entrées ou en sortie.

Ainsi, prenons un algorithme de tri sur des valeurs contenus dans un tableau dont on ne connaît pas a priori les types (en Python, cela arrive souvent, en C++ nous verrons que nous aurons également souvent ce cas de figure avec les templates). Les pré-conditions et les post-conditions sont :

- *Pré-conditions* :

  - Que les valeurs dans le tableau puisse être comparer deux à deux à l'aide d'un opérateur de comparaison;
  - Que cet opérateur de comparaison définisse une relation d'ordre (au sens mathématiques du terme);
- *Post-conditions* :

  - Que les valeurs du tableau en sortie soit une permutation des valeurs du tableau en entrée;
  -  Que les valeurs du tableau en sortie vérifie la relation d'ordre en parcourant linéairement le tableau;

On voit que les préconditions et les post-conditions sont moins triviales ici que pour la racine carrée.

La première pré-condition en C++ sera de toute façon vérifiée automatiquement par le compilateur (en Python, on peut vérifier cette pré-condition pendant le tri).

La deuxième pré-condition est impossible à vérifier par le compilateur ou les assertions. C'est donc au programmeur ici de
s'assurer que l'opérateur de comparaison employée définit bien une relation d'ordre.

Pour les post-conditions, la première post-condition est loin d'être triviale à mettre en oeuvre : soit on utilise un check-sum qui nous assure partiellement que la post-condition est vérifiée, soit en C++ on peut utiliser une fonction déjà
définie dans la bibliothèque standard (Dans la bibliothèque *algorithm*, il existe une fonction *is_permutation* qui vérifie
qu'un tableau de valeurs est bien la permutation d'un autre tableau de valeurs).

Quant à la seconde post-condition, il suffit de parcourir linéairement tout le tableau en sortie pour vérifier que les éléments consécutifs vérifient bien la relation d'ordre.

Remarquons que dans cet exemple, les pré et post-conditions sont loin d'être triviales et ont un coup en temps de calcul qui peut être non négligeable. Cependant, en C et C++, rappelons que ce coût ne sera effectif que lorsqu'on sera en phase de développement (*-DDEBUG*) mais ne sera plus présent lors de la production finale du code (où on utilisera l'option *-DNDEBUG*).

Même si le code produit durant la phase de développement sera plus lent, une bonne utilisation des pré et post conditions peut réduire drastiquement le temps de développement en permettant de détecter assez tôt des bogues potentiels. Il ne faut pas oublier que la relecture du code et la phase de "débogage" sont des parties du développement qui prennent la plus grosse partie du temps de mise en oeuvre.

### Qu'est ce qui caractérise un code "bien écrit"

Un code mettant en oeuvre un algorithme est bien écrit si il a les propriétés suivantes :

- Être facile à lire, par soi-même mais aussi par les autres;
- Avoir une organisation logique et évidente;
- Être explicite, montrer clairement les intentions du développeur;
- Être soigné et robuste au temps qui passe.

Regardons en détail chacune de ces caractéristiques :

**Le code doit être facile à lire**

Pour que le code soit facile à lire, il faut d'une part qu'il soit bien structuré et bien présenté, et d'autre part,
que les noms des variables et des fonctions soient choisis avec soin.

Pour ce qui est de la structure et de la présentation, il est important, particulièrement en C et C++, de respecter une
règle fixe d'indentation en veillant à ce que des blocs d'instructions se trouvant au même niveau doivent être précédés
du même nombre d'espaces, ce qui nous conduit naturellement à bien **indenter** notre code.

Par exemple, si on regarde le code C ci--dessous, il est évident que le manque d'indentation ne facilite par la lecture et la compréhension du code, n'est-ce-pas ?

    void m(int n, float* A, float* B, float* C) {
    int i,j,k;
    for (i = 0; i < n; ++i ){
    float a = 0.;
    for (j = 0; j < n; ++j ){
    for (k = 0; k < n; ++k ){
    a += A[i+k*n]*B[k+j*n];
    }
    C[i+j*n] += a;
    }

Pour ce qui est du choix des noms des choses (variables, fonctions, structures, etc.), nous en reparlerons un peu plus loin.

**Le code doit avoir une organisation logique et évidente**

Ce point est plus délicat car nous avons souvent des solutions différentes pour résoudre le même problème. Il est donc normal qu'un code qui semble logique à quelqu'un, semble "tordu" à son voisin.

Etant conscient de cela, il faut vous efforcer de trouver des solutions logiques et simples aux problèmes que vous devez résoudre et d'éviter d'emprunter des chemins plus compliqués qui ne feraient que semer la confusion.

Par exemple, pour afficher les nombres de un à dix, il suffit de faire une boucle qui fait évoluer un compteur entre un et dix et qui affiche ce compteur à chaque itération.  La solution qui consisterait à faire une boucle qui fait évoluer un compteur entre neuf et zéro et qui afficher à chaque itération la valeur *10-compteur* fonctionne aussi mai est à proscrire car elle est moins "simple".

De même, lors de la déclaration d'une fonction, éviter si possible d'avoir des paramètres redondants ou qui peuvent se déduire d'autres paramètres dans la liste de vos paramètres, cela vous évitera en particuliers d'avoir des incohérences entre les divers paramètres de votre fonction.

Par exemple, pour orthogonaliser un vecteur par rapport à un autre vecteur :

    void orthonogalise(double u[3], double nrmu, double v[3])
    {
        double dotuv = u[0]*v[0]+u[1]*v[1]+u[2]*v[2];
        v[0] = v[0] - dotuv*u[0]/(nrmu*nrmu);
        v[1] = v[1] - dotuv*u[0]/(nrmu*nrmu);
        v[2] = v[2] - dotuv*u[0]/(nrmu*nrmu);
    }

Le paramètre donnant la norme de $u$ est redondante avec les coefficients de *u* et il y a un risque que la valeurs
passée ne soit pas celle de *u*, ce qui amènera l'algorithme a faire un calcul faux !

Quitte à faire un peu plus de calcul, il est donc préférable de ne passer que les deux vecteurs *u* et *v* !

    void orthonogalise(double u[3], double v[3])
    {
        double sqr_nrm_u = u[0]*u[0]+u[1]*u[1]+u[2]*u[2]; // Calcul ||u||²

        assert(sqr_nrm_u > 1.E-14); // Pre-condition verifiant que le vecteur u n'est pas nul

        double dotuv = u[0]*v[0]+u[1]*v[1]+u[2]*v[2];
        v[0] = v[0] - dotuv*u[0]/sqr_nrm_u;
        v[1] = v[1] - dotuv*u[0]/sqr_nrm_u;
        v[2] = v[2] - dotuv*u[0]/sqr_nrm_u;

        assert(std::abs(v[0]*u[0]+v[1]*u[1]+v[2]*u[2]) < 1.E-14);
    }

**Le code doit être explicite**

Lorsqu'on écrit des algorithmes ou que l'on développe des programmes, on est parfois tenté de prendre
des raccourcis car "on sait" que telle ou telle méthode permet de faire telle ou telle chose bien pratique.

Il n'est pas interdit de prendre des raccourcis, mais il faut toujours prendre le soin de l'expliquer, au moins
au travers des commentaires, pourquoi on fait cela. C'est important à la fois pour permettre aux autres
de comprendre pourquoi votre solution est astucieuse\ldots mais aussi pour vous, au cas où vous ne vous
souveniez plus de "pourquoi vous avez fait ça".

Par exemple, si vous devez afficher une matrice de dimension *M x M*, la procédure usuelle est de faire deux
boucles imbriquées permettant d'afficher chacun des éléments de la matrice. Or, si vous savez que votre matrice
est triangulaire, vous allez probablement vouloir optimiser votre double boucle d'affichage. C'est naturellement
une bonne idée... mais pensez bien à rappeler dans le commentaire pourquoi vous procédez de la sorte.

**Le code doit être soigné et robuste au temps qui passe**

Lorsqu'on écrit un code, on a la fâcheuse tendance à s'arrêter dès que celui-ci fonctionne. C'est un tort !
Le code doit être entretenu. Cela signifie qu'il faut relire son code après l'avoir terminé, vérifié que l'on a bien
supprimé les éléments obsolètes, vérifier que les commentaires sont à jour et cohérents avec le code conservé, etc.

Cette opération de "maintenance" du code est cruciale, mais elle est pourtant souvent négligée par beaucoup, ce qui
peut poser des problèmes, notamment lorsque vous rencontrez un bogue.

L'exemple le plus classique est le suivant : Vous mettez un oeuvre une fonction *tri* pour trier des éléments d'un tableau.
Vous n'êtes pas satisfaits du comportement de cette méthode lorsque vous l'utilisez depuis votre programme principal. Vous mettez en oeuvre une nouvelle fonction *tri_rapide* qui utiliser une autre stratégie pour trier les éléments du tableau.
Cette méthode marche mieux. Vous l'utilisez donc dans votre programme principal. Votre programme fonctionne et vous passez à autre chose, sans penser à intégrer proprement vos modifications dans votre programme. Quelques jours plus tard, vous reprenez
votre code et vous observez un bogue. Vous pensez que cela vient du tri effectué, et vous allez donc observer ce qui se passe dans *tri*. Après quelques heures de recherche, vous êtes furieux contre vous-même car vous réalisez que la méthode *tri* n'est plus utilisée dans votre code...

Croyez-le ou non, mais les problèmes de ce type arrivent beaucoup plus souvent qu'on ne le pense... surtout quand on cherche à faire vite.

Avant de passer au point suivant, un autre exemple de code illustrant ce qui se passe très souvent. Voyez-vous le problème :

    void une_fonction(bool continuer)
    {
        // La boucle s'arrête si i est négatif ou si continuer prend la valeur false
        int i = 0, j = 4;
        while (continuer)
        {
            std::cout << "Mon code marche" << std::endl;
            // i += 1;
            j += 1;
            if (j>10) continuer = true;
        }
    }

Comme vous pouvez le voir, le premier commentaire ne correspond plus du tout à ce que fait l'algorithme et obsurcit plutôt
la compréhension du code plutôt qu'il l'éclaire ! Ce premier commentaire devait sûrement être pertinent dans les premières
versions du code mais au fur et à mesure de l'évolution de ce dernier, ne correspond plus du tout à ce que fait l'algorithme !

**C'est bien joli tout ça, mais coder proprement ça prend du temps !**

Faux ! Il ne faut pas confondre vitesse et précipitation.

On a souvent tendance à penser que l'on perd énormément de temps à soigner son code, à le structurer correctement,
à le reorganiser et à le documenter, mais c'est faux. Au contraire, on gagne du temps à faire tout cela.

Voici quelquels arguments pour en convaincre :

- Si vous adoptez les bonnes pratiques dès le début, vous faites déjà 50\% du travail;
- Si le code est bien écrit, il est plus facile, et donc plus rapide à relire, et n'oubliez pas
  que vous passez plus de temps à lire votre code qu'à l'écrire... donc quand votre code est propre, vous vous faites
  gagner du temps;
- Si le code est logique et bien structuré, il sera plus facile de retrouver les bogues qu'il contient, et donc de
  l'améliorer...

Ce sont donc autant de raisons qui devraient vous convaincre qu'il est important d'être organisé, clair, méthodique et
rigoureux quand vous développez.

### De l'importance des commentaires

Les commentaires sont essentiels pour "éclairer" votre code. Un commentaire est un texte qui est ignoré par le compilateur
lorsqu'il crée l'exécutable, mais qui peut être lu par le développeur lorsqu'il lit le programme.

Bien que les commentaires soient essentiels, il ne faut pas en abuser.

Un bon commentaire peut :

- Faciliter la lecture du code;
- Apporter une indication sur un choix de conception;
- Expliquer une motivation qui ne serait pas évidente;
- Donner un exemple pour permettre de mieux comprendre ce que fait le code.

Quelques exemples de mauvais commentaires :

- Un commentaire qui décrit un morceau de code qui n'existe plus;
- Un commentaire qui explique une évidence;
- Un commentaire sur plusieurs lignes pour expliquer une chose simple;
- Un commentaire sur l'historique des modifications d'un fichier. C'est parfois utile, mais dans la
  plupart des cas, il vaut mieux confier cette tâche à votre gestionnaire de versions qui fera le travail
  pour vous.

Amusez-vous à trouver pourquoi tous les commentaires ci--dessous sont des mauvais commentaires :

    i = 0; // On initialise la variable i à zéro
    i = i + 1; // On incrémente de un la variable i
    // On additionne a et b et on stocke le résultat dans c
    c = a + b;
    // Ci--dessous, on fait une double boucle pour afficher la matrice :
    for (i = 0; i < 10; ++i )
        std::cout << "valeur : " << i << " ";
    // Fin du for
    std::cout << std::endl; // Retour à la ligne
    /*
        Et maintenant, on va s'occuper de retourner la valeur de i. On utilise pour cela
        l'instruction return  à laquelle on passe la valeur de i
    */
    return i;

**Remarque** : Si vous vous sentez obligé de commenter la fin d'un bloc d'instructions, c'est que
probablement votre bloc d'instruction est trop long et que vous pouvez certainement fragmenter votre code
en éléments plus simples.

**Attention** : Les commentaires ne doivent pas palier un manque de clarté de votre code. Si
vous avez besoin de commentaires pour cela, c'est probablement que vous pouvez améliorer votre code pour le rendre plus
lisible. Essayez donc de le reécrire, au moins partiellement, en l'améliorant.

Comme nous l'avons déjà évoqué, les commentaires, comme le code, doivent être maintenus, c'est à dire qu'ils doivent
évoluer avec le code, et disparaître si le code correspondant disparaît. Par conséquent, il faut veiller au bon dosage
de vos commentaires, de sorte à ne pas alourdir inutilement votre travail de maintenance. Et puis, pour citer
Guido Von Rossum, le créateur du langage Python, "Les interfaces, c'est comme les blagues, si on doit les expliquer, c'est qu'elles sont ratées !". Donc si on doit commenter l'utilisation d'une fonction avec un grand nombre de commentaire, c'est
que la fonction fait soit trop de chose, soit est inutilement compliquée !

Enfin, une bonne pratique est d'utilisé des outils tels que |doctest| qui vous permettent d'écrire des petits tests pour vos fonctions tout en les documentant. Les avantages de cette pratique sont d'une part que cela vous "force" à tester votre code,
et qu'il permet en même temps d'en avoir une documentation "par l'exemple" qui sera forcément cohérente avec le code et à jour
(sinon les tests ne fonctionneraient pas).

### Comment nommer les choses ?

Les noms que vous choisissez pour vos variables vont grandement contribuer à la lisibilité de votre code.

Par exemple, vous conviendrez que le code suivant est peu clair :

    gfdjkgldfj = 4;
    ezgiofdgfdljkrljl = 1;
    gfdjkgldfj = ezgiofdgfdljkrljl + gfdjkgldfj;

tandis que le code suivant

    x = 4;
    x += 1;

est bien plus clair et fait exactement la même chose !

La première règle est donc de choisir des noms de variables prononçables et faciles à retenir.

Vous devez également choisir des noms de variables explicites pour vous mais aussi pour les autres.

Par exemple, *a* est bien moins explicite que *adresseClient*. De même, *lf* est moins explicite que
*largeurFenetre*. Pensez également que vous serez probablement amenés à chercher vos variables dans votre code
avec un outil de recherche. À votre avis, combien d'occurences de *a* allez vous trouver ? Et combien
d'occurences de *adresseClients* ?

Evitez également de choisir des noms de variables qui induisent un contre-sens. Par exemple, si vous écrivez
*matrice = 8*, on pourrait penser que la variable est une matrice, or il s'agit clairement d'un entier. Au moment
de l'affectation, il est facile de se rendre compte du type de la variable, mais maintenant, imaginez que vous
rencontriez au beau mileu de votre code la ligne suivant :

    matrice = 4 * matrice;

Comment allez vous interpréter cette instruction ?

Evitez également les noms de variables qui n'ont pas de sens, comme *plop*, surtout si vous en utilisez plusieurs
dans la même portion de code. Vous risquez de vous perdre dans les noms, et donc d'introduire inutilement des
bogues dans votre code.

Ne trichez pas non plus quand vous choisissez des noms de variables. Par exemple, en C, on ne peut pas nommer une variable
*case* ou *volatile* car ce sont des mots réservés du langage. Si vous pensez avoir besoin de ces mots pour nommer vos
variables, ne trichez pas en écrivant *ccase* ou 
*vvolatile*, vous risqueriez de vous perdre dans vos propres astuces.

Enfin, essayez d'être cohérents losque vous choisissez vos noms de variables. Par exemple, si vous décidez d'utiliser
le français pour nommer vos variables, utilisez le français tout du long, n'alternez pas avec l'anglais.
*longueurPath* et *lengthChemin* sont des noms pour le moins curieux !

### En conclusion

Pour revenir sur la première fonction (la fonction factorielle) présentée au début de cette section, on pourrait l'écrire
proprement de la manière suivante :

    long fact(long n)
    {
        assert(n>=0); // Pré-condition

        if (n == 0) // Cas particuliers : 0! = 1
        return 1;

        long resultat = n * fact(n-1); // n! = n * (n-1)!

        assert(resultat > 0);          // Post-condition
        return resultat;
    }

La fonction possède un nom évoquant la fonction factorielle. La pré-condition indique que $n$ doit être positif pour que la fonction soit valide. La post-condition indique que le résultat de la factorielle est une valeurs entière supérieure ou égale à un ! Avec peu de commentaires, des assertions et un choix adéquat du nom des choses, le code devient bien plus clair et facile à lire.
