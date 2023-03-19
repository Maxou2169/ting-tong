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