# Les premiers pas en C++

## Notre premier programme : le programme hello world !

Décorticons le programme C++ suivant :

```cpp
#include <iostream>

int main()
{
    std::cout << "Hello world !" << std::endl;
    return EXIT_SUCCESS;
}
```

### Utilisation de la bibliothèque standard

Le langage C est considéré comme un langage de bas niveau, c'est à dire un langage minimaliste dont la conception avait initialement pour but de pouvoir programmer un système d'exploitation. Sans l'utilisation de bibliothèque (standard ou autre), il est par exemple impossible d'afficher un message sur une console ou dans une fenêtre. Pour afficher par exemple, il faut utiliser une "bibliothèque", c'est à dire une collection de nouvelles fonctions et de nouveaux types qui pourront être utilisés dans votre programme.

Le langage C++ permettant des mécanismes facilitant la programmation, il est considéré comme un langage intermédiaire. Néanmoins, rien n'est prévu dans le langage lui-même pour par exemple afficher un message sur un console. Comme pour le langage C, il faut également utiliser une bibliothèque pour afficher un message sur une console.

Les bibliothèques :

- sont disponibles pour tous les programmes C++. Il se peut cependant que certaines bibliothèques ne sont disponibles que pour des systèmes d'exploitations spécifiques;
- peuvent être écrites par quelqu'un d'autre (un éditeur de logiciel, une entreprise, etc.). Vous pouvez (sous réserve de droits juridiques) les utiliser dans votre code pour rajouter de nouvelles fonctionnalités au langage C++;
- peuvent être écrites par vous-mêmes et peuvent être utilisées pour différents projets.

Une bibliothèque c++ vous proposera pour cela un ou plusieurs fichiers d'entêtes (*header*), c'est à dire un fichier texte décrivant (déclarant) de nouveaux types de variables et de nouvelles fonctions, et la plupart du temps un fichier binaire qu'il faudra "lier" à l'exécutable.

Dans nos sources (fichiers textes c++), pour utiliser une bibliothèque, il faudra inclure un ou plusieurs fichiers d'entêtes proposés par la bibliothèque à l'aide de l'instruction :
```cpp
#include <nom d'un fichier d'entête>
```
et cela autant de fois qu'il faut include différents fichiers d'entêtes.

Lors de la phase de compilation qui permet de former le binaire définitif de l'exécutable ou de la bibliothèque que l'on construit, il faut rajouter éventuellement le binaire proposé par la bibliothèque si ce dernier existe.

Par exemple, supposons que nous voulons utiliser une bibliothèque nommée SDL2 qui comprend un fichier d'entête *SDL.h* et un fichier binaire *libSDL.so* :

- Dans le code source, il faut rajouter au début du (ou des) fichier(s) utilisant la bibliothèque SDL2 :

```cpp
#include <SDL.h>
```

- Lors de la création binaire de notre exécutable (ou de notre bibliothèque), on lie nos fichiers objets (ou sources) avec la bibliothèque SDL :

```shell
g++ -o monexecutable fich1.o fich2.o fich3.cpp -lSDL
```

Il existe une bibliothèque particulière, la *bibliothèque standard* qui est livrée avec tous les compilateurs C++ existant, disponible *de facto* sur tous les systèmes d'exploitation et donc le binaire est automatiquement rajouter à votre binaire lors de l'édition des liens. Cette bibliothèque propose un très grand nombre de nouvelles fonctionnalités dont la plupart des algorithmes classiques comme le tri, la recherche d'une valeur, etc.

Ainsi

```cpp 
#include <iostream>
```

permet de rajouter le fichier d'entête *iostream* de la bibliothèque standard qui offre parmis ses nouvelles fonctionnalités la possibilité d'afficher des messages sur des consoles.

### La fonction main

Il existe en C/C++ une fonction portant le nom particulier *main*. Il ne peut exister dans tout le code, pour un exécutable donné, qu'une seule fonction *main* qui servira de point d'entrée pour l'exécution du code. Il n'est pas nécessaire de définir cette fonction lorsqu'on construit une bibliothèque.

La fonction *main* ne peut prendre que deux formes différentes :

- Une forme sans arguments :

  ```cpp
  int main()
  {
    ...    
  }
  ```

  qui permet de lancer un simple exécutable sans passage d'arguments;

- Une forme avec gestion d'éventuels arguments passés à l'exécution :

  ```cpp
  int main(int nargs, char* argv[])
  {
      ...
  }
  ```

  permettant de passer une liste d'arguments à l'exécutable.
  - *nargs* donne le nombre d'arguments passés à la fonction, **exécutable compris**.
  - *argv* donne sous forme d'un tableau de chaîne de caractères les arguments passés, le premier élément de ce tableau contenant le nom de l'exécutable (*note* : les indices pour les tableaux commencent à zéro !)

  **Par exemple** :

  ```sh
  ls -l -a -t
  ```

  lance l'exécutable *ls* avec les trois arguments. On aura donc :

   ```python
   nargs = 4
   argv  = [ "ls", "-l", "-a", "-t" ]
   ```

### Retour de la fonction main

La plupart des systèmes d'exploitation attendent qu'un exécutable renvoit un entier signalant si l'exécutable a terminé son exécution avec succès ou à cause d'un problème quelconque. En général, la valeur renvoyée n'est pas très importante, sauf si l'exécutable est invoquée dans un script et que l'on teste son succès ou non.

La valeur à renvoyer pour le succès ou non de l'exécution dépend du système d'exploitation. On utilise donc des *macros* définis dans le fichier d'entête *cstdlib* de la bibliothèque standard qui sont remplacés lors de la première phase de compilation par un texte ou une valeur qui définit la macro :

- EXIT_SUCCESS pour signaler au système d'exploitation que l'exécution a réussi
- EXIT_FAILURE pour signaler au système d'exploitation que l'exécution a rencontré un problème.

Le mot clef *return* permet de retourner une valeur en quittant une fonction (dont la fontion *main*).

### Affichage d'un message sur la console

Pour afficher un message sur la console, il faut utiliser le fichier d'entête *iostream* et utiliser la *valeur* prédéfinie *std::cout* représentant la console (*cout* = Console Output)

L'affichage se fait à l'aide de la notion de *flot*. On utilise pour cela le symbole *<<* qui "redirige" une valeur (entier, chaîne de caractères, réel, etc. ) vers la console (représentée par *std::cout*).

La *valeur* prédéfinie *std::endl* provoque un retour à la ligne au niveau de la console (*endl* = End Line)

Ainsi

```cpp
std::cout << "Hello world !" << std::endl; 
```

affiche le message *Hello world !*, puis retourne à la ligne, à l'exécution de cette ligne de programme.

