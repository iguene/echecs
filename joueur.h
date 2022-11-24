#ifndef JOUEUR_H_INCLUDED
#define JOUEUR_H_INCLUDED

//affichage pour joueur
void quelpiecechoisi(int tab[][8], int li, int ci);

//deplacements pieces
int deplacementroi(int tab[][8], int li, int ci, int ld, int cd);
int deplacementreine(int tab[][8], int li, int ci, int ld, int cd);
int deplacementtour(int tab[][8], int li, int ci, int ld, int cd);
int deplacementcavalier(int tab[][8], int li, int ci, int ld, int cd);
int deplacementfou(int tab[][8], int li, int ci, int ld, int cd);
int deplacementpion(int tab[][8], int li, int ci, int ld, int cd);
int checkpiece(int tab[][8], int li, int ci, int ld, int cd);

//pseudo game boucle (on y revient pour chaque attente avec le joueur)
void tourjoueur(int tab[][8]);

#endif // JOUEUR_H_INCLUDED
