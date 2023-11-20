# Syntaxes de base du langage C++

## Les commentaires

Les commentaires sont une partie essentielle d'un code permettant de le *documenter* :
 - Pour expliquer le rôle d'une fonction (ce qu'elle fait)
 - Expliquer quel algorithme est utilisé ou quelle astuce a été appliquée sur un morceau de code
 - Ecrire une documentation de développement de notre code (pouvant être extraite par un outil comme *doxygen*)

En C++, il existe deux formes de commentaire :

  - **multi-ligne** : un commentaire peut être écrit sur plusieurs lignes. Dans ce cas, on débute le commentaire par le *marqueur* /* et on le finit avec le *premier*
  marqueur */ rencontré;
  ```cpp
  /* Ceci est l'exemple
     d'un commentaire multiligne.
  */
  ```
  Bien que pratique dans un certain nombre de situation (commenter une zone de code par exemple), les commentaires multilignes peuvent s'avèrer problématique à l'usage si on les imbrique par inadvertance :
  
  ```cpp
  /* Imaginons qu'on veut commenter une zone du programme en utilisant le commentaire sur plusieurs lignes, car c'est bien plus pratique que de commenter ligne par ligne.
  /* Malheureusement, dans la zone commentée, j'avais déjà fait un commentaire multi-lignes :-( */
    Je crois être encore dans le commentaire externe, mais non car je viens de rencontrer le marqueur de fin de commentaire... Le marqueur qui suit ne sert
    à rien.
  */ 
  ```
   - **mono-ligne** : On peut écrire un commentaire sur une seule ligne en débutant le commentaire par le marqueur //. La fin du commentaire est marquée par le retour à la ligne
   ```cpp
   // Ceci est un commentaire sur une seule ligne.
   ```
   L'avantage de ce type de commentaire est de pouvoir être imbriqué dans un commentaire multi-ligne ou "recommenté" avec un commantaire monoligne :
   ```cpp
   /* Je veux commenté une zone de mon programme
   // pas de problème pour un commentaire monoligne
   */
   // // Et là, j'ai commenté en monoligne un commentaire monoligne. Pas de problème non plus !
   ```

## Les blocs d'instructions

Les blocs d'instructions sont un ensemble d'instructions donné, délimitées par les symboles { et }. Toute déclaration (variable, nouveau type ) faite dans un bloc d'instruction ne sera visible que dans ce bloc d'instructions.

Un bloc d'instruction peut contenir un autre bloc d'instruction. Les variables déclarées dans le bloc d'instruction externe seront visibles par le bloc d'instructions internes.

Une variable ou un type déclaré en dehors de tout bloc d'instruction seront visibles partout. Une variable déclarée en dehors de tout bloc d'instruction est appelée une  **variable globale**. Il est généralement conseillé, sauf cas particuliers, d'éviter de déclarer des variables globales qui peuvent facilement amener à des effets de bord (on utilise la variable globale sans se rendre compte que sa valeur a été modifiée par ailleurs).

```cpp
{// Début d'un bloc d'instruction
    ...
    {// Début d'un bloc d'instruction interne
        ...
    }// Fin du bloc d'instruction interne
    ...
    [// Début d'un second bloc d'instruction interne
     // Ne voit pas les déclarations faites dans le premier bloc d'instruction 
     // interne
        ...
    ]
    ...
}
```

Les blocs d'instructions délimiteront également les fonctions, les boucles et les branchements conditionnels. 