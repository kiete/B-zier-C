# B-zier-C
## Origine du projet
Ce projet est issu d'un devoir universitaire en deuxième année de licence à **l'Université Grenoble Alpes**. Il à été rendu en mars 2019 mais continue d'être amélioré
## Fonctionnement du programme
Ce programme récupère une image au format PBM et la transforme en une successions de courbes de Bézier. Pour l'appeler il suffit d'utiliser la commande `./test_trace_eps.c source seuil degré`.
- Source: chemin d'une image PBM valide
- Seuil: Seuil de précision du procédé
- Degré: Chiffre de 1 à 3 précisant le nombre de degrés qu'aura la courbe résultante
## Choix entrepris
### Stockage des données
Pour le stockage des données, nous sommes confrontés à un grand volume de données simples (Des types points). Nous avons donc choisi, pour accélérer l’algorithme d’utiliser les tableaux
à taille variable

### Algorithme de conversion
Tout d'abord nous convertissons l'image PBM en une suite de contours de segments, puis nous avons été amenés à utiliser l'algorithme de **Douglas-Peucker**, il procède ainsi :
- Un algorithme fait une approximation en courbes de Bézier pour relier le premier et le dernier point du contour, tout en restant proche des autres points.
- Il calcule la distance du point le plus éloigné à la courbe
- Si d > Seuil, il divise la section en deux et chaque moitié repart à l'étape 1. Sinon il conserve la courbe.

### Du Bézier 3 dans Bézier 2
Nous savions en nous attaquant à simplification par courbes de Bézier 2 que le format EPS
permettait d’afficher uniquement les courbes de Bézier de degré 3. Nous avons donc choisi de travailler sur une courbe de degré 2 puis de la convertir en courbe de degré 3 uniquement pour le stockage. Sans aucun gain de qualité.

## Des problèmes ?
### Issue №1 : Bounding Box
Nous avons, à l’heure actuelle des soucis sur les grandes images, en effet nous obtenons avec une Bounding Box non approprié à l’image. Souci que nous n’avons pas encore réussi à résoudre.
