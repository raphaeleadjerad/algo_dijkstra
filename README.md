# Dijkstra Algorithm : Optimisation d'un trajet sur un graphe


Le graphe est composé des noeuds `Xij` et d'arrêtes reliant ces noeuds.
Dans l'algorithme, nous utilisons des sets (STL) permettant de stocker les
noeuds par lesquels on est déjà passés. Le set est un conteneur qui stocke des
éléments uniques, la valeur d'un élément est elle-même, sa clef. Les valeurs du
set ne peuvent pas être modifiées une fois présentes dans le conteneur. 
Pour simplifier l'explication de l'algorithme, nous assimilerons notre procédure à
celle de plusieurs tableaux munis de coûts. Deux tableaux sont utilisés.
Le premier tableau est le "tableau des coûts", il est constitué de trois
lignes:

- sur la première ligne: on trouve la liste des noeuds (nommés par un
numéro) ;
- sur la deuxième ligne: on trouve le coût attribué à chacun des noeuds ;
- sur la troisième ligne: on affiche une variable vrai ou faux, qui indique
si ce noeud a déjà été parcouru.

Le second tableau est le "tableau des prédécesseurs", il est à une dimension
et contient les prédécesseurs de chaque noeud: il s'agit du "noeud-père"
qui précède le noeud en question dans le chemin parcouru.

## Exemple de résultat 

```
Nous partons du noeud 0
Ou voulez vous aller ? Entrez un noeud entre 0 et 25
24
Le cout total de votre trajet est :1464
Vous passez par les noeuds
7  18  12  6  0 
Votre chemin est le suivant :
vous passez par le noeud 0
vous passez par le noeud 6
vous passez par le noeud 12
vous passez par le noeud 18
vous passez par le noeud 24
Vous etes arrives
```
