#ifndef JOUEUR2_H_INCLUDED
#define JOUEUR2_H_INCLUDED
//affichage pour joueur
void quelpiecechoisinoir(int tab[][8], int li, int ci);

//deplacements pieces
int deplacementroinoir(int tab[][8], int li, int ci, int ld, int cd);
int deplacementreinenoir(int tab[][8], int li, int ci, int ld, int cd);
int deplacementtournoir(int tab[][8], int li, int ci, int ld, int cd);
int deplacementcavaliernoir(int tab[][8], int li, int ci, int ld, int cd);
int deplacementfounoir(int tab[][8], int li, int ci, int ld, int cd);
int deplacementpionnoir(int tab[][8], int li, int ci, int ld, int cd);
int checkpiecenoir(int tab[][8], int li, int ci, int ld, int cd);

//pseudo game boucle (on y revient pour chaque attente avec le joueur)
void tourjoueur2echec(int tab[][8], int a);
void tourjoueur2(int tab[][8]);


#endif // JOUEUR2_H_INCLUDED
