# Ting-Tong, a simple tennis game

## Comment s'en servir

Compiler en faisant `make` à la racine, puis executer en faisant `./bin/ting-tong`

Il faut interragir avec les menus à la souris pour personnaliser avec les différentes 

En version texte comme en version graphique, chaque joueur à 5 touches:
 - Joueur 1 (celui du bas)
    - Z : Devant
    - Q : gauche
    - S : derrière
    - D : droite
    - E : Faire un coup
 - Joueur 2 (celui du haut)
    - O : devant
    - K : gauche
    - L : derrière
    - M : droite
    - P : faire un coup

Pour quitter le programme, faire ECHAP (ou appuyer sur la croix) en version graphique, T en version texte (ou Ctrl-C).

## Quelques notes et points importants

### Organisation des fichiers
- `data/` : Les fichiers image du jeu (c'est ici qu'iraient les sauvegardes s'il y en avait)
- `bin/` : Le dossier qui stocke les différents binaires compilés (le dossier sera créé automatique par le Makefile)
- `doc/` : Le dossier qui stockera les fichiers générés par Doxygen à la création de la doc
- `obj/` : Le dossier qui stockera les différents fichiers étape de compilation (le dossier est créé automatiquement par le Makefile)
- `src/` : Le dossier des sources, il continent un dossier `includes/` qui contiendra les différents `.h`

### Constantes définies dans le programme

Plusieurs constantes ont été définies dans le programme, elles ont été réfléchies pour garantir une expérrience optimale.
Ces constantes sont :
 - `HITBOX_X` dans *coup.cpp* -> La largeur de la hitbox autour d'un joueur, en unités du terrain
 - `HITBOX_Y` dans *coup.cpp* -> La hauteur de la hitbox autour d'un joueur, en unités du terrain
 - `COEFF_VITESSE` dans *coup.cpp* -> Le flottant par lequel la vitesse de la balle est multiplié à chaque coup
 - `EPSILON` dans *joueur.h* -> Une macro définie pour les comparaisons = entre floats
### Classe Balle
- Il y a maintenant des valeurs par défaut sur tous les éléments de la balle, pour éviter les problèmes de division par 0 sur des `Balle::descente` non définis ou autre
- Il faut donc bien penser à personnaliser ces valeurs à chaque fois

### Classe Terrain
- Le centre du terrain est en (0,0)
- Il est de taille 8 de large, 24 de long (au total)
- Il y a des "bordures" en 10 de long, 30 de large

### Classe affichage
- On fait un "scale" entre les coordonnées du terrain et celle de la fenêtre