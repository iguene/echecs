#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "joueur.h"
#include "adversaire.h"
#include "arbitre.h"
#include "echecmat.h"
#include "joueur2.h"
/*
//tente de réunir les conditions du minimax : faut faire une listes de tout les coups possible pour chaque joueur sur plusieurs profondeurs

typedef struct coup
{
    int li; //ligne case initial
    int ci; //colonne case initial
    int ld; //ligne case destination
    int cd; //colonnne case initial
    struct coup *frere;
    struct coup *fils;
}coup;

coup *creationcoup(int li, int ci, int ld, int cd)
{
    coup *c;
    c = (coup*) malloc(sizeof(coup));
    c->li = li;
    c->ci = ci;
    c->ld = ld;
    c->cd = cd;
    c->frere = NULL;
    c->fils = NULL;
    return c;
}

coup *ajoutefrere(coup *ainee, coup *cadet)
{
    if(ainee == NULL)
    {
        return cadet;
    }
    ainee = ajoutefrere(ainee->frere, cadet);
    return ainee;
}
*/
/*
coup creationlistecoup(int tab[][8], int tour) //si tour == 0 alors liste des coups du joueur sinon liste de l'ia
{

}
*/
/*

int eval(int tab[][8])
{
    int note = 0, valeur, i, j;

    for(i = 0; i < 8; i++)
    {
        for(j = 0; j < 8; j++)
        {
            if(tab[i][j] == 4) // pour mettre la valeur des cavaliers à égal à celle des fous comme elle devrait l'être mais comment dans le tableau faut différencier...
            {
                valeur = 3;
            } else if (tab[i][j] == -4)
            {
                valeur = -3;
            } else
            {
                valeur = tab[i][j];
            }

            note += valeur * 10; //*nbdeplacementpossible(tab, i, j);
        }
    }

    return note;
}
*/

void tourIA(int tab[][8])
{

}
