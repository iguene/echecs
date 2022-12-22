#include <stdio.h>
#include <stdlib.h>
#include "joueur.h"
#include "adversaire.h"
#include "arbitre.h"
#include "echecmat.h"
#include "joueur2.h"
#include "echecetmatjoueur2.h"
#include <limits.h>

#define PRONFONDEURMAX 2

//IA AVEC MINIMAX (fonction minimax en avant dernier)



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

//-------------------------------------- INTERFACE DE LA STRUCTURE COUP -----------------------------------------------------------------

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
    if(l!= NULL)
    {
        printf("\n%d,%d -> %d,%d", l->li, l->ci, l->ld, l->cd);
        return affichagelistecoups(l->frere);
    }
}

coup *suppression_tete(coup *l)
{
    if(l == NULL)
    {
        return NULL;
    }
    if(l->frere == NULL)
    {
        return NULL;
    }
    coup *l2;
    l2 = l->frere;
    free(l);
    return l2;
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

//--------------------------------------------------------------------------------------------------------------------------------------------------



//----------------- Pour changer un tableau selon un coup et restaurer de le tableau au coup précédent pour le minimax------------------------------

void montagecoupdanstab(coup *c, int tab[][8])
{
    changetabcoup(tab,c->li , c->ci, c->ld, c->cd, tab[c->li][c->ci]);
}

void demontagecoupdanstab(coup *c, int tab[][8])
{
    changetabcoup(tab, c->ld, c->cd, c->li , c->ci, tab[c->ld][c->cd]);
}

//---------------------------------------------------------------------------------------------------------------------------------------------------


//----------------- Verification qu'une position est en echec et mat en une fonction pour le minimax-------------------------------------------------

int positionechecmat(int tab[][8], int tour)
{
    int v, ve;
    if(tour == 1)
    {
        v = verifechecnoir(tab);
        if (v == 1)
        {
            ve = verifechecetmatnoir(tab);
            if (ve == 0)
            {
                return 1;
            }
        }
    } else if(tour == -1)
    {
        v = verifechec(tab);
        if (v == 1)
        {
            ve = verifechecetmat(tab);
            if (ve == 0)
            {
                return 1;
            }
        }
    }
    return 0;
}


//---------------------------------------------------------------------------------------------------------------------------------------------------

//----------------- Donne le plus grand entier entre deux ou le plus petit entier entre deux pour le minimax ----------------------------------------

int plusgrand(int a, int b)
{
    if(a < b)
    {
        return b;
    } else
    {
        return a;
    }
}

int pluspetit(int a, int b)
{
    if(a > b)
    {
        return b;
    } else
    {
        return a;
    }
}


//---------------------------------------------------------------------------------------------------------------------------------------------------



//----------------- Ajouts de tout les coups possibles selon un echiquier donnée et le tour dans une liste pour le minimax---------------------------



void listecoupsroinoir(int tab[][8], int copietab[][8], int li, int ci, coup *liste)
{
    coup *c = NULL;
    int legal;
    int ld, cd, sapproche;

    if(li+1 < 8)
    {
        if(tab[li+1][ci] > -1)
        {
            ld = li+1;
            cd = ci;
            sapproche = roisapproche(tab, -1, ld, cd);
            if(sapproche == 1)
            {
                legal = 0; // peut pas s'approcher du roi
            } else
            {
                c = creationcoup(li, ci, ld, cd);
                changetabcoup(copietab, li, ci, ld, cd, -19);
                legal = verifechec(copietab);
                if(legal == 0) //coup legal, provoque pas d'échec ou sort de l'échec
                {
                    liste = ajoutefrere(liste, c);
                }
                recopietab(tab, copietab);
            }
        }
    }

    if(li-1 >= 0)
    {
        if(tab[li-1][ci] > -1)
        {
            ld = li-1;
            cd = ci;
            sapproche = roisapproche(tab, -1, ld, cd);
            if(sapproche == 1)
            {
                legal = 0; // peut pas s'approcher du roi
            } else
            {
                c = creationcoup(li, ci, ld, cd);
                changetabcoup(copietab, li, ci, ld, cd, -19);
                legal = verifechec(copietab);
                if(legal == 0) //coup legal, provoque pas d'échec ou sort de l'échec
                {
                    liste = ajoutefrere(liste, c);
                }
                recopietab(tab, copietab);
            }
        }
    }

    if(ci-1 >= 0)
    {
        if(tab[li][ci-1] > -1)
        {
            ld = li;
            cd = ci-1;
            sapproche = roisapproche(tab, -1, ld, cd);
            if(sapproche == 1)
            {
                legal = 0; // peut pas s'approcher du roi
            } else
            {
                c = creationcoup(li, ci, ld, cd);
                changetabcoup(copietab, li, ci, ld, cd, -19);
                legal = verifechec(copietab);
                if(legal == 0) //coup legal, provoque pas d'échec ou sort de l'échec
                {
                    liste = ajoutefrere(liste, c);
                }
                recopietab(tab, copietab);
            }
        }
    }

    if(ci+1 < 8)
    {
        if(tab[li][ci+1] > -1)
        {
            ld = li;
            cd = ci+1;
            sapproche = roisapproche(tab, -1, ld, cd);
            if(sapproche == 1)
            {
                legal = 0; // peut pas s'approcher du roi
            } else
            {
                c = creationcoup(li, ci, ld, cd);
                changetabcoup(copietab, li, ci, ld, cd, -19);
                legal = verifechec(copietab);
                if(legal == 0) //coup legal, provoque pas d'échec ou sort de l'échec
                {
                    liste = ajoutefrere(liste, c);
                }
                recopietab(tab, copietab);
            }
        }
    }

    if(li-1 >= 0 && ci-1 >=0)
    {
        if(tab[li-1][ci-1] > -1)
        {
            ld = li-1;
            cd = ci-1;
            sapproche = roisapproche(tab, -1, ld, cd);
            if(sapproche == 1)
            {
                legal = 0; // peut pas s'approcher du roi
            } else
            {
                c = creationcoup(li, ci, ld, cd);
                changetabcoup(copietab, li, ci, ld, cd, -19);
                legal = verifechec(copietab);
                if(legal == 0) //coup legal, provoque pas d'échec ou sort de l'échec
                {
                    liste = ajoutefrere(liste, c);
                }
                recopietab(tab, copietab);
            }
        }
    }

    if(li+1 < 8 && ci-1 >=0)
    {
        if(tab[li+1][ci-1] > -1)
        {
            ld = li+1;
            cd = ci-1;
            sapproche = roisapproche(tab, -1, ld, cd);
            if(sapproche == 1)
            {
                legal = 0; // peut pas s'approcher du roi
            } else
            {
                c = creationcoup(li, ci, ld, cd);
                changetabcoup(copietab, li, ci, ld, cd, -19);
                legal = verifechec(copietab);
                if(legal == 0) //coup legal, provoque pas d'échec ou sort de l'échec
                {
                    liste = ajoutefrere(liste, c);
                }
                recopietab(tab, copietab);
            }
        }
    }

    if(li+1 < 8 && ci+1 < 8)
    {
        if(tab[li+1][ci+1] > -1)
        {
            ld = li+1;
            cd = ci+1;
            sapproche = roisapproche(tab, -1, ld, cd);
            if(sapproche == 1)
            {
                legal = 0; // peut pas s'approcher du roi
            } else
            {
                c = creationcoup(li, ci, ld, cd);
                changetabcoup(copietab, li, ci, ld, cd, -19);
                legal = verifechec(copietab);
                if(legal == 0) //coup legal, provoque pas d'échec ou sort de l'échec
                {
                    liste = ajoutefrere(liste, c);
                }
                recopietab(tab, copietab);
            }
        }
    }


    if(li-1 >= 0 && ci+1 < 8)
    {
        if(tab[li-1][ci+1] > -1)
        {
            ld = li-1;
            cd = ci+1;
            sapproche = roisapproche(tab, -1, ld, cd);
            if(sapproche == 1)
            {
                legal = 0; // peut pas s'approcher du roi
            } else
            {
                c = creationcoup(li, ci, ld, cd);
                changetabcoup(copietab, li, ci, ld, cd, -19);
                legal = verifechec(copietab);
                if(legal == 0) //coup legal, provoque pas d'échec ou sort de l'échec
                {
                    liste = ajoutefrere(liste, c);
                }
                recopietab(tab, copietab);
            }
        }
    }

}

void listecoupsroiblanc(int tab[][8], int copietab[][8], int li, int ci, coup *liste)
{
    coup *c = NULL;
    int legal;
    int ld, cd, sapproche;


    if(li+1 < 8)
    {
        if(tab[li+1][ci] < 1)
        {
            ld = li+1;
            cd = ci;
            sapproche = roisapproche(tab, 1, ld, cd);
            if(sapproche == 1)
            {
                legal = 0; // peut pas s'approcher du roi
            } else
            {
                c = creationcoup(li, ci, ld, cd);
                changetabcoup(copietab, li, ci, ld, cd, 19);
                legal = verifechec(copietab);
                if(legal == 0) //coup legal, provoque pas d'échec ou sort de l'échec
                {
                    liste = ajoutefrere(liste, c);
                }
                recopietab(tab, copietab);
            }
        }
    }

    if(li-1 >= 0)
    {
        if(tab[li-1][ci] < 1)
        {
            ld = li-1;
            cd = ci;
            sapproche = roisapproche(tab, 1, ld, cd);
            if(sapproche == 1)
            {
                legal = 0; // peut pas s'approcher du roi
            } else
            {
                c = creationcoup(li, ci, ld, cd);
                changetabcoup(copietab, li, ci, ld, cd, 19);
                legal = verifechec(copietab);
                if(legal == 0) //coup legal, provoque pas d'échec ou sort de l'échec
                {
                    liste = ajoutefrere(liste, c);
                }
                recopietab(tab, copietab);
            }
        }
    }

    if(ci-1 >= 0)
    {
        if(tab[li][ci-1] < 1)
        {
            ld = li;
            cd = ci-1;
            sapproche = roisapproche(tab, 1, ld, cd);
            if(sapproche == 1)
            {
                legal = 0; // peut pas s'approcher du roi
            } else
            {
                c = creationcoup(li, ci, ld, cd);
                changetabcoup(copietab, li, ci, ld, cd, 19);
                legal = verifechec(copietab);
                if(legal == 0) //coup legal, provoque pas d'échec ou sort de l'échec
                {
                    liste = ajoutefrere(liste, c);
                }
                recopietab(tab, copietab);
            }
        }
    }

    if(ci+1 < 8)
    {
        if(tab[li][ci+1] < 1)
        {
            ld = li;
            cd = ci+1;
            sapproche = roisapproche(tab, 1, ld, cd);
            if(sapproche == 1)
            {
                legal = 0; // peut pas s'approcher du roi
            } else
            {
                c = creationcoup(li, ci, ld, cd);
                changetabcoup(copietab, li, ci, ld, cd, 19);
                legal = verifechec(copietab);
                if(legal == 0) //coup legal, provoque pas d'échec ou sort de l'échec
                {
                    liste = ajoutefrere(liste, c);
                }
                recopietab(tab, copietab);
            }
        }
    }

    if(li-1 >= 0 && ci-1 >=0)
    {
        if(tab[li-1][ci-1] < 1)
        {
            ld = li-1;
            cd = ci-1;
            sapproche = roisapproche(tab, 1, ld, cd);
            if(sapproche == 1)
            {
                legal = 0; // peut pas s'approcher du roi
            } else
            {
                c = creationcoup(li, ci, ld, cd);
                changetabcoup(copietab, li, ci, ld, cd, 19);
                legal = verifechec(copietab);
                if(legal == 0) //coup legal, provoque pas d'échec ou sort de l'échec
                {
                    liste = ajoutefrere(liste, c);
                }
                recopietab(tab, copietab);
            }
        }
    }

    if(li+1 < 8 && ci-1 >= 0)
    {
        if(tab[li+1][ci-1] < 1)
        {
            ld = li+1;
            cd = ci-1;
            sapproche = roisapproche(tab, 1, ld, cd);
            if(sapproche == 1)
            {
                legal = 0; // peut pas s'approcher du roi
            } else
            {
                c = creationcoup(li, ci, ld, cd);
                changetabcoup(copietab, li, ci, ld, cd, 19);
                legal = verifechec(copietab);
                if(legal == 0) //coup legal, provoque pas d'échec ou sort de l'échec
                {
                    liste = ajoutefrere(liste, c);
                }
                recopietab(tab, copietab);
            }
        }
    }

    if(li+1 < 8 && ci+1 < 8)
    {
        if(tab[li+1][ci+1] < 1)
        {
            ld = li+1;
            cd = ci+1;
            sapproche = roisapproche(tab, 1, ld, cd);
            if(sapproche == 1)
            {
                legal = 0; // peut pas s'approcher du roi
            } else
            {
                c = creationcoup(li, ci, ld, cd);
                changetabcoup(copietab, li, ci, ld, cd, 19);
                legal = verifechec(copietab);
                if(legal == 0) //coup legal, provoque pas d'échec ou sort de l'échec
                {
                    liste = ajoutefrere(liste, c);
                }
                recopietab(tab, copietab);
            }
        }
    }


    if(li-1 >= 0 && ci+1 < 8)
    {
        if(tab[li-1][ci+1] < 1)
        {
            ld = li-1;
            cd = ci+1;
            sapproche = roisapproche(tab, 1, ld, cd);
            if(sapproche == 1)
            {
                legal = 0; // peut pas s'approcher du roi
            } else
            {
                c = creationcoup(li, ci, ld, cd);
                changetabcoup(copietab, li, ci, ld, cd, 19);
                legal = verifechec(copietab);
                if(legal == 0) //coup legal, provoque pas d'échec ou sort de l'échec
                {
                    liste = ajoutefrere(liste, c);
                }
                recopietab(tab, copietab);
            }
        }
    }

}


void listecoupstour(int tab[][8], int copietab[][8], int li, int ci, coup *liste, int tour, int valeur)
{
    coup *c = NULL;
    int legal;
    int i = 1, bordure = 1;


    //déplacement verticale vers bas

    if(li+i < 8)
    {
        while(tab[li+i][ci] == 0 && bordure == 1 )
        {
            c = creationcoup(li, ci, li+i, ci);
            changetabcoup(copietab, li, ci, li+i, ci, valeur*tour);
            if (tour == - 1)
            {
                legal = verifechecnoir(copietab);
            } else
            {
                legal = verifechec(copietab);
            }
            if(legal == 0) //coup legal, provoque pas d'échec ou sort de l'échec
            {
                liste = ajoutefrere(liste, c);
            }
            recopietab(tab, copietab);
            i++;
            if(li+i > 7) // pour éviter de faire un segmentation fault genre tab[8][7] ça existe pas le tableau va de [0][0] à [7][7]
            {
                bordure = 0; //sort de la boucle
            }
        }
    }
    if(tour == 1 && li+i <= 7)
    {
        if(tab[li+i][ci] < 0)
        {
            c = creationcoup(li, ci, li+i, ci);
            changetabcoup(copietab, li, ci, li+i, ci, valeur*tour);
            legal = verifechec(copietab);
            if(legal == 0) //coup legal, provoque pas d'échec ou sort de l'échec
            {
                liste = ajoutefrere(liste, c);
            }
            recopietab(tab, copietab);
        }
    } else if(tour == -1 && li+i <= 7)
    {
        if(tab[li+i][ci] > 0)
        {
            c = creationcoup(li, ci, li+i, ci);
            changetabcoup(copietab, li, ci, li+i, ci, valeur*tour);
            legal = verifechecnoir(copietab);
            if(legal == 0) //coup legal, provoque pas d'échec ou sort de l'échec
            {
                liste = ajoutefrere(liste, c);
            }
            recopietab(tab, copietab);
        }
    }

    i = 1;
    bordure = 1;

    //-------------------------------------------------------------------------------------

    //déplacement verticale vers haut

    if(li-i >= 0)
    {
        while(tab[li-i][ci] == 0 && bordure == 1 )
        {
            c = creationcoup(li, ci, li-i, ci);
            changetabcoup(copietab, li, ci, li-i, ci, valeur*tour);
            if (tour == - 1)
            {
                legal = verifechecnoir(copietab);
            } else
            {
                legal = verifechec(copietab);
            }
            if(legal == 0) //coup legal, provoque pas d'échec ou sort de l'échec
            {
                liste = ajoutefrere(liste, c);
            }
            recopietab(tab, copietab);
            i++;
            if(li-i < 0)
            {
                bordure = 0; //sort de la boucle
            }
        }
    }
    if(tour == 1 && li-i >= 0)
    {
        if(tab[li-i][ci] < 0)
        {
            c = creationcoup(li, ci, li-i, ci);
            changetabcoup(copietab, li, ci, li-i, ci, valeur*tour);
            legal = verifechec(copietab);
            if(legal == 0) //coup legal, provoque pas d'échec ou sort de l'échec
            {
                liste = ajoutefrere(liste, c);
            }
            recopietab(tab, copietab);
        }
    } else if(tour == -1 && li-i >= 0)
    {
        if(tab[li-i][ci] > 0)
        {
            c = creationcoup(li, ci, li-i, ci);
            changetabcoup(copietab, li, ci, li-i, ci, valeur*tour);
            legal = verifechecnoir(copietab);
            if(legal == 0) //coup legal, provoque pas d'échec ou sort de l'échec
            {
                liste = ajoutefrere(liste, c);
            }
            recopietab(tab, copietab);
        }
    }

    i = 1;
    bordure = 1;

    //-------------------------------------------------------------------------------------

    //déplacement horizontale vers droite

    if(ci+i < 8)
    {
        while(tab[li][ci+i] == 0 && bordure == 1 )
        {
            c = creationcoup(li, ci, li, ci+i);
            changetabcoup(copietab, li, ci, li, ci+i, valeur*tour);
            if (tour == - 1)
            {
                legal = verifechecnoir(copietab);
            } else
            {
                legal = verifechec(copietab);
            }
            if(legal == 0) //coup legal, provoque pas d'échec ou sort de l'échec
            {
                liste = ajoutefrere(liste, c);
            }
            recopietab(tab, copietab);
            i++;
            if(ci+i > 7)
            {
                bordure = 0; //sort de la boucle
            }
        }
    }
    if(tour == 1 && ci+i <= 7)
    {
        if(tab[li][ci+i] < 0)
        {
            c = creationcoup(li, ci, li, ci+i);
            changetabcoup(copietab, li, ci, li, ci+i, valeur*tour);
            legal = verifechec(copietab);
            if(legal == 0) //coup legal, provoque pas d'échec ou sort de l'échec
            {
                liste = ajoutefrere(liste, c);
            }
            recopietab(tab, copietab);
        }
    } else if(tour == -1 && ci+i <= 7)
    {
        if(tab[li][ci+i] > 0)
        {
            c = creationcoup(li, ci, li, ci+i);
            changetabcoup(copietab, li, ci, li, ci+i, valeur*tour);
            legal = verifechecnoir(copietab);
            if(legal == 0) //coup legal, provoque pas d'échec ou sort de l'échec
            {
                liste = ajoutefrere(liste, c);
            }
            recopietab(tab, copietab);
        }
    }

    i = 1;
    bordure = 1;

    //-------------------------------------------------------------------------------------

    //déplacement horizontale vers gauche

    if(ci-i >= 0)
    {
        while(tab[li][ci-i] == 0 && bordure == 1 )
        {
            c = creationcoup(li, ci, li, ci-i);
            changetabcoup(copietab, li, ci, li, ci-i, valeur*tour);
            if (tour == - 1)
            {
                legal = verifechecnoir(copietab);
            } else
            {
                legal = verifechec(copietab);
            }
            if(legal == 0) //coup legal, provoque pas d'échec ou sort de l'échec
            {
                liste = ajoutefrere(liste, c);
            }
            recopietab(tab, copietab);
            i++;
            if(ci-i < 0)
            {
                bordure = 0; //sort de la boucle
            }
        }
    }

    if(tour == 1 && ci-i >= 0)
    {
        if(tab[li][ci-i] < 0)
        {
            c = creationcoup(li, ci, li, ci-i);
            changetabcoup(copietab, li, ci, li, ci-i, valeur*tour);
            legal = verifechec(copietab);
            if(legal == 0) //coup legal, provoque pas d'échec ou sort de l'échec
            {
                liste = ajoutefrere(liste, c);
            }
            recopietab(tab, copietab);
        }
    } else if(tour == -1 && ci-i >= 0)
    {
        if(tab[li][ci-i] > 0)
        {
            c = creationcoup(li, ci, li, ci-i);
            changetabcoup(copietab, li, ci, li, ci-i, valeur*tour);
            legal = verifechecnoir(copietab);
            if(legal == 0) //coup legal, provoque pas d'échec ou sort de l'échec
            {
                liste = ajoutefrere(liste, c);
            }
            recopietab(tab, copietab);
        }
    }
    recopietab(tab, copietab);

}

void listecoupscavalier(int tab[][8], int copietab[][8], int li, int ci, coup *liste, int tour)
{
    coup *c = NULL;
    int legal;

    if(li+2 < 8)
    {
        if(ci+1 < 8)
        {
            if(tour == 1 && tab[li+2][ci+1] < 1)
            {
                c = creationcoup(li, ci, li+2, ci+1);
                changetabcoup(copietab, li, ci, li+2, ci+1, 4);
                legal = verifechec(copietab);
                if(legal == 0) //coup legal, provoque pas d'échec ou sort de l'échec
                {
                    liste = ajoutefrere(liste, c);
                }
                recopietab(tab, copietab);
            } else if(tour == -1 && tab[li+2][ci+1] > -1)
            {
                c = creationcoup(li, ci, li+2, ci+1);
                changetabcoup(copietab, li, ci, li+2, ci+1, -4);
                legal = verifechecnoir(copietab);
                if(legal == 0) //coup legal, provoque pas d'échec ou sort de l'échec
                {
                    liste = ajoutefrere(liste, c);
                }
                recopietab(tab, copietab);
            }
        }
        if(ci-1 >= 0)
        {
            if(tour == 1 && tab[li+2][ci-1] < 1)
            {
                c = creationcoup(li, ci, li+2, ci-1);
                changetabcoup(copietab, li, ci, li+2, ci-1, 4);
                legal = verifechec(copietab);
                if(legal == 0) //coup legal, provoque pas d'échec ou sort de l'échec
                {
                    liste = ajoutefrere(liste, c);
                }
                recopietab(tab, copietab);
            } else if(tour == -1 && tab[li+2][ci-1] > -1)
            {
                c = creationcoup(li, ci, li+2, ci-1);
                changetabcoup(copietab, li, ci, li+2, ci-1, -4);
                legal = verifechecnoir(copietab);
                if(legal == 0) //coup legal, provoque pas d'échec ou sort de l'échec
                {
                    liste = ajoutefrere(liste, c);
                }
                recopietab(tab, copietab);
            }
        }
    }

    if(li-2 >= 0)
    {
        if(ci+1 < 8)
        {
            if(tour == 1 && tab[li-2][ci+1] < 1)
            {
                c = creationcoup(li, ci, li-2, ci+1);
                changetabcoup(copietab, li, ci, li-2, ci+1, 4);
                legal = verifechec(copietab);
                if(legal == 0) //coup legal, provoque pas d'échec ou sort de l'échec
                {
                    liste = ajoutefrere(liste, c);
                }
                recopietab(tab, copietab);
            } else if(tour == -1 && tab[li-2][ci+1] > -1)
            {
                c = creationcoup(li, ci, li-2, ci+1);
                changetabcoup(copietab, li, ci, li-2, ci+1, -4);
                legal = verifechecnoir(copietab);
                if(legal == 0) //coup legal, provoque pas d'échec ou sort de l'échec
                {
                    liste = ajoutefrere(liste, c);
                }
                recopietab(tab, copietab);
            }
        }
        if(ci-1 >= 0)
        {
            if(tour == 1 && tab[li-2][ci-1] < 1)
            {
                c = creationcoup(li, ci, li-2, ci-1);
                changetabcoup(copietab, li, ci, li-2, ci-1, 4);
                legal = verifechec(copietab);
                if(legal == 0) //coup legal, provoque pas d'échec ou sort de l'échec
                {
                    liste = ajoutefrere(liste, c);
                }
                recopietab(tab, copietab);
            } else if(tour == -1 && tab[li-2][ci-1] > -1)
            {
                c = creationcoup(li, ci, li-2, ci-1);
                changetabcoup(copietab, li, ci, li-2, ci-1, -4);
                legal = verifechecnoir(copietab);
                if(legal == 0) //coup legal, provoque pas d'échec ou sort de l'échec
                {
                    liste = ajoutefrere(liste, c);
                }
                recopietab(tab, copietab);
            }
        }
    }

    if(li+1 < 8)
    {
        if(ci+2 < 8)
        {
            if(tour == 1 && tab[li+1][ci+2] < 1)
            {
                c = creationcoup(li, ci, li+1, ci+2);
                changetabcoup(copietab, li, ci, li+1, ci+2, 4);
                legal = verifechec(copietab);
                if(legal == 0) //coup legal, provoque pas d'échec ou sort de l'échec
                {
                    liste = ajoutefrere(liste, c);
                }
                recopietab(tab, copietab);
            } else if(tour == -1 && tab[li+1][ci+2] > -1)
            {
                c = creationcoup(li, ci, li+1, ci+2);
                changetabcoup(copietab, li, ci, li+1, ci+2, -4);
                legal = verifechecnoir(copietab);
                if(legal == 0) //coup legal, provoque pas d'échec ou sort de l'échec
                {
                    liste = ajoutefrere(liste, c);
                }
                recopietab(tab, copietab);
            }
        }
        if(ci-2 >= 0)
        {
            if(tour == 1 && tab[li+1][ci-2] < 1)
            {
                c = creationcoup(li, ci, li+1, ci-2);
                changetabcoup(copietab, li, ci, li+1, ci-2, 4);
                legal = verifechec(copietab);
                if(legal == 0) //coup legal, provoque pas d'échec ou sort de l'échec
                {
                    liste = ajoutefrere(liste, c);
                }
                recopietab(tab, copietab);
            } else if(tour == -1 && tab[li+1][ci-2] > -1)
            {
                c = creationcoup(li, ci, li+1, ci-2);
                changetabcoup(copietab, li, ci, li+1, ci-2, -4);
                legal = verifechecnoir(copietab);
                if(legal == 0) //coup legal, provoque pas d'échec ou sort de l'échec
                {
                    liste = ajoutefrere(liste, c);
                }
                recopietab(tab, copietab);
            }
        }
    }


    if(li-1 >= 0)
    {
        if(ci+2 < 8)
        {
            if(tour == 1 && tab[li-1][ci+2] < 1)
            {
                c = creationcoup(li, ci, li-1, ci+2);
                changetabcoup(copietab, li, ci, li-1, ci+2, 4);
                legal = verifechec(copietab);
                if(legal == 0) //coup legal, provoque pas d'échec ou sort de l'échec
                {
                    liste = ajoutefrere(liste, c);
                }
                recopietab(tab, copietab);
            } else if(tour == -1 && tab[li-1][ci+2] > -1)
            {
                c = creationcoup(li, ci, li-1, ci+2);
                changetabcoup(copietab, li, ci, li-1, ci+2, -4);
                legal = verifechecnoir(copietab);
                if(legal == 0) //coup legal, provoque pas d'échec ou sort de l'échec
                {
                    liste = ajoutefrere(liste, c);
                }
                recopietab(tab, copietab);
            }
        }
        if(ci-2 >= 0)
        {
            if(tour == 1 && tab[li-1][ci-2] < 1)
            {
                c = creationcoup(li, ci, li-1, ci-2);
                changetabcoup(copietab, li, ci, li-1, ci-2, 4);
                legal = verifechec(copietab);
                if(legal == 0) //coup legal, provoque pas d'échec ou sort de l'échec
                {
                    liste = ajoutefrere(liste, c);
                }
                recopietab(tab, copietab);
            } else if(tour == -1 && tab[li-1][ci-2] > -1)
            {
                c = creationcoup(li, ci, li-1, ci-2);
                changetabcoup(copietab, li, ci, li-1, ci-2, -4);
                legal = verifechecnoir(copietab);
                if(legal == 0) //coup legal, provoque pas d'échec ou sort de l'échec
                {
                    liste = ajoutefrere(liste, c);
                }
                recopietab(tab, copietab);
            }
        }
    }
    recopietab(tab, copietab);
}

void listecoupsfou(int tab[][8], int copietab[][8], int li, int ci, coup *liste, int tour, int valeur) //valeur 3 si c'est pour liste de coups du fou et valeur 10 reine
{
    coup *c = NULL;
    int legal;
    int i = 1, j = 1, bordure = 1;

    //liste coups diagonale haut gauche à bas droite ---------------------------------------

    if(li+i < 8 && ci+j < 8)
    {
        while(tab[li+i][ci+j] == 0 && bordure == 1 )
        {
            c = creationcoup(li, ci, li+i, ci+j);
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
                liste = ajoutefrere(liste, c);
            }
            recopietab(tab, copietab);
            i++;
            j++;
            if(li+i > 7 || ci+j > 7) // pour éviter de faire un segmentation fault genre tab[8][7] ça existe pas le tableau va de [0][0] à [7][7]
            {
                bordure = 0; //sort de la boucle
            }
        }
    }
    if(tour == 1 && li+i <= 7 && ci+j <= 7)
    {
        if(tab[li+i][ci+j] < 0)
        {
            c = creationcoup(li, ci, li+i, ci+j);
            changetabcoup(copietab, li, ci, li+i, ci+j, valeur*tour);
            legal = verifechec(copietab);
            if(legal == 0) //coup legal, provoque pas d'échec ou sort de l'échec
            {
                liste = ajoutefrere(liste, c);
            }
            recopietab(tab, copietab);
        }
    } else if(tour == -1 && li+i <= 7 && ci+j <= 7)
    {
        if(tab[li+i][ci+j] > 0)
        {
            c = creationcoup(li, ci, li+i, ci+j);
            changetabcoup(copietab, li, ci, li+i, ci+j, valeur*tour);
            legal = verifechecnoir(copietab);
            if(legal == 0) //coup legal, provoque pas d'échec ou sort de l'échec
            {
                liste = ajoutefrere(liste, c);
            }
            recopietab(tab, copietab);
        }
    }

    i = 1;
    j = 1;
    bordure = 1;

    //---------------------------------------------------------------------------------------------

    //liste coups diagonale bas droite à haut gauche ---------------------------------------

    if(li-i >= 0 && ci-j >=0)
    {
        while(tab[li-i][ci-j] == 0 && bordure == 1 )
        {
            c = creationcoup(li, ci, li-i, ci-j);
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
                liste = ajoutefrere(liste, c);
            }
            recopietab(tab, copietab);
            i++;
            j++;
            if(li-i < 0 || ci-j < 0)
            {
                bordure = 0;
            }
        }
    }
    if(tour == 1 && li-i >= 0 && ci-j >= 0)
    {
        if(tab[li-i][ci-j] < 0)
        {
            c = creationcoup(li, ci, li-i, ci-j);
            changetabcoup(copietab, li, ci, li-i, ci-j, valeur*tour);
            legal = verifechec(copietab);
            if(legal == 0) //coup legal, provoque pas d'échec ou sort de l'échec
            {
                liste = ajoutefrere(liste, c);
            }
            recopietab(tab, copietab);
        }
    } else if(tour == -1 && li-i >= 0 && ci-j >= 0)
    {
        if(tab[li-i][ci-j] > 0)
        {
            c = creationcoup(li, ci, li-i, ci-j);
            changetabcoup(copietab, li, ci, li-i, ci-j, valeur*tour);
            legal = verifechecnoir(copietab);
            if(legal == 0) //coup legal, provoque pas d'échec ou sort de l'échec
            {
                liste = ajoutefrere(liste, c);
            }
            recopietab(tab, copietab);
        }
    }

    i = 1;
    j = 1;
    bordure = 1;

    //---------------------------------------------------------------------------------------------

     //liste coups diagonale bas gauche à haut droite ---------------------------------------

    if(li-i >= 0 && ci+j < 8)
    {
        while(tab[li-i][ci+j] == 0 && bordure == 1 )
        {
            c = creationcoup(li, ci, li-i, ci+j);
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
                liste = ajoutefrere(liste, c);
            }
            recopietab(tab, copietab);
            i++;
            j++;
            if(li-i < 0 || ci+j > 7)
            {
                bordure = 0;
            }
        }
    }

    if(tour == 1 && li-i >= 0 && ci+j <= 7)
    {
        if(tab[li-i][ci+j] < 0)
        {
            c = creationcoup(li, ci, li-i, ci+j);
            changetabcoup(copietab, li, ci, li-i, ci+j, valeur*tour);
            legal = verifechec(copietab);
            if(legal == 0) //coup legal, provoque pas d'échec ou sort de l'échec
            {
                liste = ajoutefrere(liste, c);
            }
            recopietab(tab, copietab);
        }
    } else if(tour == -1 && li-i >= 0 && ci+j <= 7)
    {
        if(tab[li-i][ci+j] > 0)
        {
            c = creationcoup(li, ci, li-i, ci+j);
            changetabcoup(copietab, li, ci, li-i, ci+j, valeur*tour);
            legal = verifechecnoir(copietab);
            if(legal == 0) //coup legal, provoque pas d'échec ou sort de l'échec
            {
                liste = ajoutefrere(liste, c);
            }
            recopietab(tab, copietab);
        }
    }

    i = 1;
    j = 1;
    bordure = 1;

    //liste coups diagonale haut droite à bas gauche  ---------------------------------------

    if(li+i < 8 && ci-j >= 0)
    {
        while(tab[li+i][ci-j] == 0 && bordure == 1 )
        {
            c = creationcoup(li, ci, li+i, ci-j);
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
                liste = ajoutefrere(liste, c);
            }
            recopietab(tab, copietab);
            i++;
            j++;
            if(li+i > 7 || ci-j < 0)
            {
                bordure = 0;
            }
        }
    }
    if(tour == 1 && li+i <= 7 && ci-j >= 0)
    {
        if(tab[li+i][ci-j] < 0)
        {
            c = creationcoup(li, ci, li+i, ci-j);
            changetabcoup(copietab, li, ci, li+i, ci-j, valeur*tour);
            legal = verifechec(copietab);
            if(legal == 0) //coup legal, provoque pas d'échec ou sort de l'échec
            {
                liste = ajoutefrere(liste, c);
            }
            recopietab(tab, copietab);
        }
    } else if(tour == -1 && li+i <= 7 && ci-j >= 0)
    {
        if(tab[li+i][ci-j] > 0)
        {
            c = creationcoup(li, ci, li+i, ci-j);
            changetabcoup(copietab, li, ci, li+i, ci-j, valeur*tour);
            legal = verifechecnoir(copietab);
            if(legal == 0) //coup legal, provoque pas d'échec ou sort de l'échec
            {
                liste = ajoutefrere(liste, c);
            }
            recopietab(tab, copietab);
        }
    }
    recopietab(tab, copietab);

}

void listecoupspionnoir(int tab[][8], int copietab[][8], int li, int ci, coup *liste)
{
    coup *c = NULL;
    int legal;
    if(li+1 < 8)
    {
        if(tab[li+1][ci] == 0)
        {
            c = creationcoup(li, ci, li+1, ci);
            changetabcoup(copietab, li, ci, li+1, ci, -1);
            legal = verifechecnoir(copietab); //appel de verification echec pour noir
            if(legal == 0) //coup legal, provoque pas d'échec ou sort de l'échec
            {
                liste = ajoutefrere(liste, c);
            }
            recopietab(tab, copietab);
        }
    }

    if(ci-1 >= 0 && li+1 < 8)
    {
        if(tab[li+1][ci-1] > 0)
        {
            c = creationcoup(li, ci, li+1, ci-1);
            changetabcoup(copietab, li, ci, li+1, ci-1, -1);
            legal = verifechec(copietab);
            if(legal == 0)
            {
                liste = ajoutefrere(liste, c);
            }
            recopietab(tab, copietab);
        }
    }

    if(ci+1 < 8 && li+1 < 8)
    {
        if(tab[li+1][ci+1] > 0)
        {
            c = creationcoup(li, ci, li+1, ci+1);
            changetabcoup(copietab, li, ci, li+1, ci+1, -1);
            legal = verifechec(copietab);
            if(legal == 0)
            {
                liste = ajoutefrere(liste, c);
            }
            recopietab(tab, copietab);
        }
    }

    if(li == 1)
    {
        if(tab[li+1][ci] == 0 && tab[li+2][ci] == 0 && li == 1)
        {
            c = creationcoup(li, ci, li+2, ci);
            changetabcoup(copietab, li, ci, li+2, ci, -1);
            legal = verifechec(copietab);
            if(legal == 0)
            {
                liste = ajoutefrere(liste, c);
            }
            recopietab(tab, copietab);
        }
    }

}

//ajout liste des coups possibles pour un pion blanc
void listecoupspionblanc(int tab[][8], int copietab[][8], int li, int ci, coup *liste)
{
    coup *c = NULL;
    int legal;
    if(li-1 >= 0)
    {
        if(tab[li-1][ci]==0)
        {
            c = creationcoup(li, ci, li-1, ci);
            changetabcoup(copietab, li, ci, li-1, ci, 1);
            legal = verifechec(copietab); //appel de verification echec pour blanc
            if(legal == 0) //coup legal, provoque pas d'échec ou sort de l'échec
            {
                liste = ajoutefrere(liste, c);
            }
            recopietab(tab, copietab);
        }
    }
    if(tab[li-1][ci]==0)
    {
        c = creationcoup(li, ci, li-1, ci);
        changetabcoup(copietab, li, ci, li-1, ci, 1);
        legal = verifechec(copietab); //appel de verification echec pour blanc
        if(legal == 0) //coup legal, provoque pas d'échec ou sort de l'échec
        {
            liste = ajoutefrere(liste, c);
        }
        recopietab(tab, copietab);
    }

    if(ci-1 >= 0 && li-1 >= 0)
    {
        if(tab[li-1][ci-1] < 0)
        {
            c = creationcoup(li, ci, li-1, ci-1);
            changetabcoup(copietab, li, ci, li-1, ci-1, 1);
            legal = verifechec(copietab);
            if(legal == 0)
            {
                liste = ajoutefrere(liste, c);
            }
            recopietab(tab, copietab);
        }
    }

    if(ci+1 < 8 && li-1 >= 0)
    {
        if(tab[li-1][ci+1] < 0)
        {
            c = creationcoup(li, ci, li-1, ci+1);
            changetabcoup(copietab, li, ci, li-1, ci+1, 1);
            legal = verifechec(copietab);
            if(legal == 0)
            {
                liste = ajoutefrere(liste, c);
            }
            recopietab(tab, copietab);
        }
    }

    if(li == 6)
    {
        if(tab[li-1][ci] == 0 && tab[li-2][ci] == 0)
        {
            c = creationcoup(li, ci, li-2, ci);
            changetabcoup(copietab, li, ci, li-2, ci, 1);
            legal = verifechec(copietab);
            if(legal == 0)
            {
                liste = ajoutefrere(liste, c);
            }
            recopietab(tab, copietab);
        }
    }

}

void listecoupsreine(int tab[][8], int copietab[][8], int li, int ci, coup *liste, int tour)
{
    listecoupsfou(tab, copietab, li, ci, liste, tour, 10);
    listecoupstour(tab, copietab, li, ci, liste, tour, 10);
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

            } else if(tab[i][j] == 3 && tour == 1)
            {
                listecoupsfou(tab, copietab, i, j, liste, tour, 3);

            } else if(tab[i][j] == -3 && tour == -1)
            {
                listecoupsfou(tab, copietab, i, j, liste, tour, 3);

            } else if(tab[i][j] == 4 && tour == 1)
            {
                listecoupscavalier(tab, copietab, i, j, liste, tour);

            } else if(tab[i][j] == -4 && tour == -1)
            {
                listecoupscavalier(tab, copietab, i, j, liste, tour);

            } else if(tab[i][j] == 5 && tour == 1)
            {
                listecoupstour(tab, copietab, i, j, liste, tour, 5);

            } else if(tab[i][j] == -5 && tour == -1)
            {
                listecoupstour(tab, copietab, i, j, liste, tour, 5);

            } else if(tab[i][j] == 10 && tour == 1)
            {
                listecoupsreine(tab, copietab, i, j, liste, tour);

            } else if(tab[i][j] == -10 && tour == -1)
            {
                listecoupsreine(tab, copietab, i, j, liste, tour);

            } else if(tab[i][j] == 19 && tour == 1)
            {
                listecoupsroiblanc(tab, copietab, i, j, liste);
            }  else if(tab[i][j] == -19 && tour == -1)
            {
                listecoupsroinoir(tab, copietab, i, j, liste);
            }
        }
    }

}


//---------------------------------------------------------------------------------------------------------------------------------------------------

//Fonction d'évalutation d'un échiquier pour le minimax

int eval(int tab[][8], int tour)
{

    int note = 0, valeur, i, j, v = 0, ve = 0;

    // Ajoute des points selon les pièces présentes dans l'échiquier
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

            note += valeur * 10;
        }
    }

    //Ajoute des points si on a des pièces au centre de léchiquier

    if(tab[3][3] > 0)
    {
        note += 3;
    } else if (tab[3][3] < 0)
    {
        note -= 3;
    }

    if(tab[3][4] > 0)
    {
        note += 3;
    } else if (tab[3][4] < 0)
    {
        note -= 3;
    }

    if(tab[4][3] > 0)
    {
        note += 3;
    } else if (tab[4][3] < 0)
    {
        note -= 3;
    }

    if(tab[4][4] > 0)
    {
        note += 3;
    } else if (tab[4][4] < 0)
    {
        note -= 3;
    }

    //Ajoute des points selon le nombre de coups possibles pour un echiquier

    int compteur = 0;;
    coup *liste = NULL;
    coup *c;
    liste = creationcoup(0, 0, 0, 0);
    creationlistecoup(tab, 1, liste);
    liste = suppression_tete(liste);
    c = liste;

    while(c != NULL)
    {
        compteur++;
        c = c->frere;
    }

    liberation_rec(liste);
    note += compteur;

    compteur = 0;
    liste = creationcoup(0, 0, 0, 0);
    creationlistecoup(tab, -1, liste);
    liste = suppression_tete(liste);
    c = liste;

    while(c != NULL)
    {
        compteur++;
        c = c->frere;
    }

    liberation_rec(liste);
    note -= compteur;


    //Donne une une très très grande note si l'adversaire est mat ou ajoute quelques points si il est simplement en echec

    if(tour == 1)
    {
        v = verifechecnoir(tab);
        if (v == 1)
        {
            note -= 2;
            ve = verifechecetmatnoir(tab);
            if (ve == 0)
            {
                note = 100000;
            }
        }
    } else if(tour == -1)
    {
        v = verifechec(tab);
        if (v == 1)
        {
            note += 2;
            ve = verifechecetmat(tab);
            if (ve == 0)
            {
                note = -100000;
            }
        }
    }


    return note;
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------


int minimax(int profondeur, int tour, int tab[][8], int alpha, int beta)
{
    int a = positionechecmat(tab, tour);
    if(profondeur == 0 || a == 1)
    {
        int e = eval(tab, tour);
        return e;
    }

    coup *liste = NULL;
    liste = creationcoup(0, 0, 0, 0);
    creationlistecoup(tab, tour, liste);
    liste = suppression_tete(liste);

    coup *c;
    c = liste;


    int evaluation;
    int meilleurvaleur;

    int taboriginal[8][8];
    recopietab(tab, taboriginal);

    if(tour == 1) // maximisation
    {
        meilleurvaleur = INT_MIN;
        while(c != NULL)
        {
            montagecoupdanstab(c, tab);
            evaluation = minimax(profondeur-1, -1, tab, alpha, beta);
            recopietab(taboriginal, tab);

            if(evaluation > meilleurvaleur)
            {
                meilleurvaleur = evaluation;
            }

            alpha = plusgrand(alpha, evaluation);
            if(beta <= alpha)
            {
                break; //cut alpha beta pruning
            }

            c = c->frere;
        }
        liberation_rec(liste);


    } else //minimisation
    {
        meilleurvaleur = INT_MAX;
        while(c != NULL)
        {
            montagecoupdanstab(c, tab);
            evaluation = minimax(profondeur-1, 1, tab, alpha, beta);
            recopietab(taboriginal, tab);

            if(evaluation < meilleurvaleur)
            {
                meilleurvaleur = evaluation;
            }

            beta = pluspetit(alpha, evaluation);
            if(beta <= alpha)
            {
                break; //cut alpha beta pruning
            }

            c = c->frere;
        }
        liberation_rec(liste);


    }

    return meilleurvaleur;
}



void tourIA(int tab[][8])
{
    //D'abord vérifier si la partie n'est pas déjà en echec et mat
    int v, ve;
    v = verifechecnoir(tab);
    if (v == 1)
    {
        ve = verifechecetmatnoir(tab);
        if (ve == 0)
        {
            return printf("\n\n Victoire des blancs par echec et mat ! \n\n ");
        }
    }

    coup *meilleurcoup = creationcoup(0, 0, 0, 0);
    coup *liste = creationcoup(0, 0, 0, 0);
    creationlistecoup(tab, -1, liste);
    liste = suppression_tete(liste);
    coup *c = liste;

    int resultat, meilleurresultat = INT_MAX;

    int taboriginal[8][8];
    recopietab(tab, taboriginal);

    while(c != NULL)
    {
        montagecoupdanstab(c, tab);
        resultat = minimax(PRONFONDEURMAX-1, 1, tab, INT_MIN, INT_MAX);
        recopietab(taboriginal, tab);


        if(resultat < meilleurresultat)
        {
            meilleurresultat = resultat;
            meilleurcoup->li = c->li;
            meilleurcoup->ci = c->ci;
            meilleurcoup->ld = c->ld;
            meilleurcoup->cd = c->cd;
        }
        c = c->frere;

    }

    liberation_rec(liste);

    /*
    printf("\n %d", meilleurresultat);
    printf("\n Le meilleur coup est : %d, %d, %d, %d", meilleurcoup->li, meilleurcoup->ci ,meilleurcoup->ld , meilleurcoup->cd);
    */


    montagecoupdanstab(meilleurcoup, tab);

    tourjoueur(tab);

}
