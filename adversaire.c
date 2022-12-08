#include <stdio.h>
#include <stdlib.h>
#include "joueur.h"
#include "adversaire.h"
#include "arbitre.h"
#include "echecmat.h"
#include "joueur2.h"
#include "echecetmatjoueur2.h"

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
    printf("\n%d,%d ->%d,%d", l->li, l->ci, l->ld, l->cd);
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
    ainee->frere = ajoutefrere(ainee->frere, cadet);
    return ainee;
}



void listecoupsroi(int tab[][8], int copietab[][8], int li, int ci, coup *liste, int tour)
{

}

void listecoupsreine(int tab[][8], int copietab[][8], int li, int ci, coup *liste, int tour)
{

}

void listecoupstour(int tab[][8], int copietab[][8], int li, int ci, coup *liste, int tour)
{

}

void listecoupscavalier(int tab[][8], int copietab[][8], int li, int ci, coup *liste, int tour)
{

}

void listecoupsfou(int tab[][8], int copietab[][8], int li, int ci, coup *liste, int tour, int valeur) //valeur 3 si c'est pour liste de coups du fou et valeur 10 reine
{
    coup *coup;
    int legal;
    int i = 1, j = 1, bordure = 1;;

    //liste coups diagonale haut gauche à bas droite ---------------------------------------

    while(tab[li+i][ci+j] == 0 && bordure == 1 )
    {
        coup = creationcoup(li, ci, li+i, ci+j);
        changetabcoup(copietab, li, ci, li+i, ci+j, valeur*tour);
        if (tour == - 1)
        {
            legal = verifechecnoir(copietab);
        } else
        {
            legal = verifechec(copietab);
        }
        if(legal == 0) //coup legal, provoque pas d'échec ou sort de l'échec
        {
            liste = ajoutefrere(liste, coup);
        }
        recopietab(tab, copietab);
        i++;
        j++;
        if(li+i > 7 || ci+j > 7) // pour éviter de faire un segmentation fault genre tab[8][7] ça existe pas le tableau va de [0][0] à [7][7]
        {
            bordure = 0; //sort de la boucle
        }
    }
    if(tour == 1 && li < 7 && ci < 7)
    {
        if(tab[li+i][ci+j] < 0)
        {
            coup = creationcoup(li, ci, li+i, ci+j);
            changetabcoup(copietab, li, ci, li+i, ci+j, valeur*tour);
            legal = verifechec(copietab);
            if(legal == 0) //coup legal, provoque pas d'échec ou sort de l'échec
            {
                liste = ajoutefrere(liste, coup);
            }
            recopietab(tab, copietab);
        }
    } else if(tour == -1 && li < 7 && ci < 7)
    {
        if(tab[li+i][ci+j] > 0)
        {
            coup = creationcoup(li, ci, li+i, ci+j);
            changetabcoup(copietab, li, ci, li+i, ci+j, valeur*tour);
            legal = verifechecnoir(copietab);
            if(legal == 0) //coup legal, provoque pas d'échec ou sort de l'échec
            {
                liste = ajoutefrere(liste, coup);
            }
            recopietab(tab, copietab);
        }
    }

    i = 1;
    j = 1;
    bordure = 1;

    //---------------------------------------------------------------------------------------------

    //liste coups diagonale bas droite à haut gauche ---------------------------------------

    while(tab[li-i][ci-j] == 0 && bordure == 1 )
    {
        coup = creationcoup(li, ci, li-i, ci-j);
        changetabcoup(copietab, li, ci, li-i, ci-j, valeur*tour);
        if (tour == - 1)
        {
            legal = verifechecnoir(copietab);
        } else
        {
            legal = verifechec(copietab);
        }
        if(legal == 0) //coup legal, provoque pas d'échec ou sort de l'échec
        {
            liste = ajoutefrere(liste, coup);
        }
        recopietab(tab, copietab);
        i++;
        j++;
        if(li-i < 0 || ci-j < 0)
        {
            bordure = 0;
        }
    }
    if(tour == 1 && li > 0 && ci > 0)
    {
        if(tab[li-i][ci-j] < 0)
        {
            coup = creationcoup(li, ci, li-i, ci-j);
            changetabcoup(copietab, li, ci, li-i, ci-j, valeur*tour);
            legal = verifechec(copietab);
            if(legal == 0) //coup legal, provoque pas d'échec ou sort de l'échec
            {
                liste = ajoutefrere(liste, coup);
            }
            recopietab(tab, copietab);
        }
    } else if(tour == -1 && li > 0 && ci > 0)
    {
        if(tab[li-i][ci-j] > 0)
        {
            coup = creationcoup(li, ci, li-i, ci-j);
            changetabcoup(copietab, li, ci, li-i, ci-j, valeur*tour);
            legal = verifechecnoir(copietab);
            if(legal == 0) //coup legal, provoque pas d'échec ou sort de l'échec
            {
                liste = ajoutefrere(liste, coup);
            }
            recopietab(tab, copietab);
        }
    }

    i = 1;
    j = 1;
    bordure = 1;

    //---------------------------------------------------------------------------------------------

     //liste coups diagonale bas gauche à haut droite ---------------------------------------

    while(tab[li-i][ci+j] == 0 && bordure == 1 )
    {
        coup = creationcoup(li, ci, li-i, ci+j);
        changetabcoup(copietab, li, ci, li-i, ci+j, valeur*tour);
        if (tour == - 1)
        {
            legal = verifechecnoir(copietab);
        } else
        {
            legal = verifechec(copietab);
        }
        if(legal == 0) //coup legal, provoque pas d'échec ou sort de l'échec
        {
            liste = ajoutefrere(liste, coup);
        }
        recopietab(tab, copietab);
        i++;
        j++;
        if(li-i < 0 || ci+j > 7)
        {
            bordure = 0;
        }
    }
    if(tour == 1 && li > 0 && ci < 7)
    {
        if(tab[li-i][ci+j] < 0)
        {
            coup = creationcoup(li, ci, li-i, ci+j);
            changetabcoup(copietab, li, ci, li-i, ci+j, valeur*tour);
            legal = verifechec(copietab);
            if(legal == 0) //coup legal, provoque pas d'échec ou sort de l'échec
            {
                liste = ajoutefrere(liste, coup);
            }
            recopietab(tab, copietab);
        }
    } else if(tour == -1 && li > 0 && ci < 7)
    {
        if(tab[li-i][ci+j] > 0)
        {
            coup = creationcoup(li, ci, li-i, ci+j);
            changetabcoup(copietab, li, ci, li-i, ci+j, valeur*tour);
            legal = verifechecnoir(copietab);
            if(legal == 0) //coup legal, provoque pas d'échec ou sort de l'échec
            {
                liste = ajoutefrere(liste, coup);
            }
            recopietab(tab, copietab);
        }
    }

    i = 1;
    j = 1;
    bordure = 1;

    //liste coups diagonale haut droite à bas gauche  ---------------------------------------

    while(tab[li+i][ci-j] == 0 && bordure == 1 )
    {
        coup = creationcoup(li, ci, li+i, ci-j);
        changetabcoup(copietab, li, ci, li+i, ci-j, valeur*tour);
        if (tour == - 1)
        {
            legal = verifechecnoir(copietab);
        } else
        {
            legal = verifechec(copietab);
        }
        if(legal == 0) //coup legal, provoque pas d'échec ou sort de l'échec
        {
            liste = ajoutefrere(liste, coup);
        }
        recopietab(tab, copietab);
        i++;
        j++;
        if(li+i > 7 || ci-j < 0)
        {
            bordure = 0;
        }
    }
    if(tour == 1 && li < 7 && ci > 0)
    {
        if(tab[li+i][ci-j] < 0)
        {
            coup = creationcoup(li, ci, li+i, ci-j);
            changetabcoup(copietab, li, ci, li+i, ci-j, valeur*tour);
            legal = verifechec(copietab);
            if(legal == 0) //coup legal, provoque pas d'échec ou sort de l'échec
            {
                liste = ajoutefrere(liste, coup);
            }
            recopietab(tab, copietab);
        }
    } else if(tour == -1 && li < 7 && ci > 0)
    {
        if(tab[li+i][ci-j] > 0)
        {
            coup = creationcoup(li, ci, li+i, ci-j);
            changetabcoup(copietab, li, ci, li+i, ci-j, valeur*tour);
            legal = verifechecnoir(copietab);
            if(legal == 0) //coup legal, provoque pas d'échec ou sort de l'échec
            {
                liste = ajoutefrere(liste, coup);
            }
            recopietab(tab, copietab);
        }
    }

}

void listecoupspionnoir(int tab[][8], int copietab[][8], int li, int ci, coup *liste)
{
    coup *coup;
    int legal;
    if(tab[li+1][ci]==0)
    {
        coup = creationcoup(li, ci, li+1, ci);
        changetabcoup(copietab, li, ci, li+1, ci, -1);
        legal = verifechecnoir(copietab); //appel de verification echec pour noir
        if(legal == 0) //coup legal, provoque pas d'échec ou sort de l'échec
        {
            liste = ajoutefrere(liste, coup);
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
            liste = ajoutefrere(liste, coup);
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
            liste = ajoutefrere(liste, coup);
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
            liste = ajoutefrere(liste, coup);
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
        changetabcoup(copietab, li, ci, li-1, ci, 1);
        legal = verifechec(copietab); //appel de verification echec pour blanc
        if(legal == 0) //coup legal, provoque pas d'échec ou sort de l'échec
        {
            liste = ajoutefrere(liste, coup);
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
            liste = ajoutefrere(liste, coup);
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
            liste = ajoutefrere(liste, coup);
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
            liste = ajoutefrere(liste, coup);
        }
        recopietab(tab, copietab);
    }

}

/*Fait la liste des coups pour un échiquier*/
void creationlistecoup(int tab[][8], int tour, coup *liste) //si tour == 1 alors liste des coups du joueur sinon si -1 alors liste de l'ia
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
                listecoupspionnoir(tab, copietab, i, j, liste);

            } else if(tab[i][j] == 3)
            {
                listecoupsfou(tab, copietab, i, j, liste, tour, 3);

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
    coup *liste = NULL;

    liste = creationcoup(0, 0, 0, 0);

    creationlistecoup(tab, 1, liste);

    affichagelistecoups(liste);

    liberation_rec(liste);

}
