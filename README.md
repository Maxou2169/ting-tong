# Ting-Tong, a simple tennis game

## Comment s'en servir

Installer avec vore gestionnaire de paquets favori la librairie SDL2 (plus précisément SDL2, SDL2_Image et SDL2_TTF)
Compiler en faisant `make` à la racine, puis executer en faisant `./bin/ting-tong`

Il faut interragir avec les menus à la souris pour personnaliser le jeu avec différents joueurs et terrains

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
- `data/` : Les fichiers image du jeu (c'est ici que sont les fichiers de configuration aussi)
- `bin/` : Le dossier qui stocke les différents binaires compilés (le dossier sera créé automatique par le Makefile)
- `doc/` : Le dossier qui stockera les fichiers générés par Doxygen à la création de la doc
- `obj/` : Le dossier qui stockera les différents fichiers étape de compilation (le dossier est créé automatiquement par le Makefile)
- `src/` : Le dossier des sources, il continent un dossier `includes/` qui contiendra les différents `.h`

### Fichiers de configuration 

Il y a deux fichiers de configuration pour ce programme, `data/players.cfg` et `data/terrains.cfg`
Ces fichiers sont l'équivalent d'un format clef-valeurs : `clef` RETOUR A LA LIGNE `valeur`.
Le fichier `data/players.cfg` prends comme clefs les noms des joueurs (affichés dans les menus et dans le tableau de score), et en valeur l'image à afficher (chemin relatif depuis la racine, type `data/joueur.png`). Exemple avec `Nadal \n data/nadal.png`
Le fichier `data/terrains.cfg` prends comme clefs les noms des terrains, et en valeurs le chemin de l'image du terrain puis le chemin du logo du tournoi.
Exemple avec `Wimbledon \n data/wimbledon_terrain.png data/wimbledon_logo.png`

Le comportement du programme n'est pas garanti en cas d'oubli des fichiers de configuration et/ou des images pointées par ceux-ci.

### Constantes définies dans le programme

Plusieurs constantes ont été définies dans le programme, elles ont été réfléchies pour garantir une expérrience optimale.
Ces constantes sont :
 - `HITBOX_X` dans *coup.cpp* -> La largeur de la hitbox autour d'un joueur, en unités du terrain
 - `HITBOX_Y` dans *coup.cpp* -> La hauteur de la hitbox autour d'un joueur, en unités du terrain
 - `COEFF_VITESSE` dans *coup.cpp* -> Le flottant par lequel la vitesse de la balle est multiplié à chaque coup
 - `EPSILON` dans *joueur.h* -> Une macro définie pour les comparaisons = entre floats
 - `PAS_X_JOUEUR` dans *joueur.cpp* -> Le déplacement latéral d'un joueur à chaque pas, en unités du terrain
 - `PAS_Y_JOUEUR` dans *joueur.cpp* -> Le déplacement vertical d'un joueur à chaque pas, en unités du terrain

### Classe Balle
- Il y a maintenant des valeurs par défaut sur tous les éléments de la balle, pour éviter les problèmes de division par 0 sur des `Balle::descente` non définis ou autre
- Il faut donc bien penser à personnaliser ces valeurs à chaque fois

### Classe Terrain
- Le centre du terrain est en (0,0)
- Il est de taille 8 de large, 24 de long (au total)
- Il y a des "bordures" en 10 de long, 30 de large

### Classe affichage
- On fait un "scale" entre les coordonnées du terrain et celle de la fenêtre