# Ting-Tong, a simple tennis game

## Comment s'en servir

En version texte comme en version graphique, chaque joueur à 5 touches:
 - Joueur 1
    - Z : Devant
    - Q : gauche
    - S : derrière
    - D : droite
    - E : Faire un coup
 - Joueur 2
    - O : devant
    - K : gauche
    - L : derrière
    - M : droite
    - P : faire un coup

Pour quitter le programme, faire ECHAP en version graphique, T en version texte (ou Ctrl-C).

## Programming conventions
- Toutes les classes ont une fonction `bool test()` qui est publique
- Les protections contre la double inclusion sont de la forme du nom du fichier avec les `.` transformés en `_`
- Les fonctions sont nommées suivant la convention `snake_case`

## Quelques notes et points importants

### Classe Balle
- Il y a maintenant des valeurs par défaut sur tous les éléments de la balle, pour éviter les problèmes de division par 0 sur des `Balle::descente` non définis ou autre
- Il faut donc bien penser à personnaliser ces valeurs à chaque fois

### Classe Terrain
- Le centre du terrain est en (0,0)
- Il est de taille 8 de large, 24 de long (au total)
- Il y a des "bordures" en 10 de long, 30 de large

### Classe affichage
- On fait un "scale" entre les coordonnées du terrain et celle de la fenêtre