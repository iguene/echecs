#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "joueur.h"
#include "adversaire.h"
#include "arbitre.h"
#include "echecmat.h"
#include "joueur2.h"

//tente de réunir les conditions du minimax : faut faire une listes de tout les coups possible pour chaque joueur sur plusieurs profondeurs

typedef struct coup
{
    int li; //ligne case initial
    int ci; //colonne case initial
    int ld; //ligne case destination
    int cd; //colonnne case initial
    struct coup *frere;
}coup;

//modifie l'échiquier selon un coup (faut lui donner une copie ! sinon il va modifier l'échiquier en jeu)
void changetabcoup(int tab[][8], int li, int ci, int ld, int cd, int valpiece)
{
    if(valpiece == 1 && ld == 0) //pour les transformations en reine de pions
    {
        tab[li][ci] = 0;
        tab[ld][cd] = 10;
    } else if (valpiece == -1 && ld == 7)
    {
        tab[li][ci] = 0;
        tab[ld][cd] = -10;
    } else //cas général
    {
        tab[li][ci] = 0;
        tab[ld][cd] = valpiece;
    }

}

coup *creationcoup(int li, int ci, int ld, int cd)
{
    coup *c;
    c = (coup*) malloc(sizeof(coup));
    c->li = li;
    c->ci = ci;
    c->ld = ld;
    c->cd = cd;
    c->frere = NULL;
    return c;
}

void affichagelistecoups(coup *l)
{
    printf(" \n %d,%d ->%d,%d", l->li, l->ci, l->ld, l->cd);
    if(l->frere != NULL)
    {
        affichagelistecoups(l->frere);
    }
}

void liberation_rec(coup *l)
{
    if(l!=NULL)
    {
        if(l->frere!=NULL)
        {
            liberation_rec(l->frere);
        }
        free(l);
    }
}


/*ajoute un coup en fin de liste*/
coup *ajoutefrere(coup *ainee, coup *cadet)
{
    if(ainee == NULL)
    {
        return cadet;
    }
    ainee = ajoutefrere(ainee->frere, cadet);
    return ainee;
}



void listecoupsroi()
{

}

void listecoupsreine()
{

}

void listecoupstour()
{

}

void listecoupscavalier()
{

}

void listecoupsfou()
{

}

void listecoupspionnoir(int tab[][8], int copietab[][8], int li, int ci, coup *liste)
{
    coup *coup;
    int legal;
    if(tab[li+1][ci]==0)
    {
        coup = creationcoup(li, ci, li+1, ci);
        //faut vérifier que le coup est légal avant de l'ajouter c'est à dire qu'il ne mets pas le roi en échec
        changetabcoup(copietab, li, ci, li+1, ci, -1);
        legal = verifechec(copietab); //appel de verification echec pour blanc
        if(legal == 0) //coup legal, provoque pas d'échec ou sort de l'échec
        {
            ajoutefrere(liste, coup);
        }
        recopietab(tab, copietab);
    }

    if(tab[li+1][ci-1] > 0)
    {
        coup = creationcoup(li, ci, li+1, ci-1);
        changetabcoup(copietab, li, ci, li+1, ci-1, -1);
        legal = verifechec(copietab);
        if(legal == 0)
        {
            ajoutefrere(liste, coup);
        }
        recopietab(tab, copietab);
    }

    if(tab[li+1][ci+1] > 0)
    {
        coup = creationcoup(li, ci, li+1, ci+1);
        changetabcoup(copietab, li, ci, li+1, ci+1, -1);
        legal = verifechec(copietab);
        if(legal == 0)
        {
            ajoutefrere(liste, coup);
        }
        recopietab(tab, copietab);
    }

    if(tab[li+1][ci] == 0 && tab[li+2][ci] == 0 && li == 1)
    {
        coup = creationcoup(li, ci, li+2, ci);
        changetabcoup(copietab, li, ci, li+2, ci, -1);
        legal = verifechec(copietab);
        if(legal == 0)
        {
            ajoutefrere(liste, coup);
        }
        recopietab(tab, copietab);
    }
}

//ajout liste des coups possibles pour un pion blanc
void listecoupspionblanc(int tab[][8], int copietab[][8], int li, int ci, coup *liste)
{
    coup *coup;
    int legal;
    if(tab[li-1][ci]==0)
    {
        coup = creationcoup(li, ci, li-1, ci);
        //faut vérifier que le coup est légal avant de l'ajouter c'est à dire qu'il ne mets pas le roi en échec
        changetabcoup(copietab, li, ci, li-1, ci, 1);
        legal = verifechec(copietab); //appel de verification echec pour blanc
        if(legal == 0) //coup legal, provoque pas d'échec ou sort de l'échec
        {
            ajoutefrere(liste, coup);
        }
        recopietab(tab, copietab);
    }

    if(tab[li-1][ci-1] < 0)
    {
        coup = creationcoup(li, ci, li-1, ci-1);
        changetabcoup(copietab, li, ci, li-1, ci-1, 1);
        legal = verifechec(copietab);
        if(legal == 0)
        {
            ajoutefrere(liste, coup);
        }
        recopietab(tab, copietab);
    }

    if(tab[li-1][ci+1] < 0)
    {
        coup = creationcoup(li, ci, li-1, ci+1);
        changetabcoup(copietab, li, ci, li-1, ci+1, 1);
        legal = verifechec(copietab);
        if(legal == 0)
        {
            ajoutefrere(liste, coup);
        }
        recopietab(tab, copietab);
    }

    if(tab[li-1][ci] == 0 && tab[li-2][ci] == 0 && li == 6)
    {
        coup = creationcoup(li, ci, li-2, ci);
        changetabcoup(copietab, li, ci, li-2, ci, 1);
        legal = verifechec(copietab);
        if(legal == 0)
        {
            ajoutefrere(liste, coup);
        }
        recopietab(tab, copietab);
    }

}

/*Fait la liste des coups pour un échiquier*/
void creationlistecoup(int tab[][8], int tour, coup *liste) //si tour == 0 alors liste des coups du joueur sinon si -1 alors liste de l'ia
{
    int i, j;

    int copietab[8][8];

    recopietab(tab, copietab);

    for(i = 0; i < 8; i++)
    {
        for(j = 0; j < 8; j++)
        {
            if(tab[i][j] == 1 && tour == 1)
            {
                listecoupspionblanc(tab, copietab, i, j, liste);

            } else if(tab[i][j] == -1 && tour == -1)
            {
                //listecoupspionnoir();

            } else if(tab[i][j] == 3)
            {
                //listecoupsfou();

            } else if(tab[i][j] == 4)
            {
                //listecoupscavalier();

            } else if(tab[i][j] == 5)
            {
                //listecoupstour();

            } else if(tab[i][j] == 10)
            {
                //listecoupsreine();

            } else if(tab[i][j] == 19)
            {
                //listecoupsroi();
            }
        }
    }
}


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

void tourIA(int tab[][8])
{
    coup *liste;

}
