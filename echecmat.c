#include <stdio.h>
#include <stdlib.h>
#include "joueur.h"
#include "adversaire.h"
#include "arbitre.h"
#include "echecmat.h"
#include "joueur2.h"
#include "echecetmatjoueur2.h"

//verification de si les blancs sont en echec et mat

int sortieecheccavalier(int tab[][8], int copietab[][8], int n, int m)
{
    int v, i, j; //desolé flemme de changer nom variable du pavé
    i = n;
    j = m;
    if(n+2 < 8 && m-1 >= 0)
    {
        if(tab[n+2][m-1] < 0)
        {
            copietab[i][j] = 0;
            copietab[i+2][j-1] = 4;
            v = verifechec(copietab);
            if (v == 0) //si v == 0 alors le joueur n'est plus en echec, donc ce coup permet de ne pas être echec et mat
            {
                return 1; //couppossible = 1
            }
            recopietab(tab, copietab);
        }
    }
    if(n+2 < 8 && m+1 < 8)
    {
        if(tab[n+2][m+1] < 0)
        {
            copietab[i][j] = 0;
            copietab[i+2][j+1] = 4;
            v = verifechec(copietab);
            if (v == 0) //si v == 0 alors le joueur n'est plus en echec, donc ce coup permet de ne pas être echec et mat
            {
                return 1; //couppossible = 1
            }
            recopietab(tab, copietab);
        }
    }
    if(n-2 >=0 && m-1 >= 0)
    {
        if(tab[n-2][m-1] < 0)
        {
            copietab[i][j] = 0;
            copietab[i-2][j-1] = 4;
            v = verifechec(copietab);
            if (v == 0) //si v == 0 alors le joueur n'est plus en echec, donc ce coup permet de ne pas être echec et mat
            {
                return 1; //couppossible = 1
            }
            recopietab(tab, copietab);
        }
    }
    if(n-2 >= 0 && m+1 < 8)
    {
        if(tab[n-2][m+1] < 0)
        {
            copietab[i][j] = 0;
            copietab[i-2][j+1] = 4;
            v = verifechec(copietab);
            if (v == 0) //si v == 0 alors le joueur n'est plus en echec, donc ce coup permet de ne pas être echec et mat
            {
                return 1; //couppossible = 1
            }
            recopietab(tab, copietab);
        }
    }
    if(n-1 >=0 && m+2 < 8)
    {
        if(tab[n-1][m+2] < 0)
        {
            copietab[i][j] = 0;
            copietab[i-1][j+2] = 4;
            v = verifechec(copietab);
            if (v == 0) //si v == 0 alors le joueur n'est plus en echec, donc ce coup permet de ne pas être echec et mat
            {
                return 1; //couppossible = 1
            }
            recopietab(tab, copietab);
        }
    }
    if(n+1 < 8 && m+2 < 8)
    {
        if(tab[n+1][m+2] < 0)
        {
            copietab[i][j] = 0;
            copietab[i+1][j+2] = 4;
            v = verifechec(copietab);
            if (v == 0) //si v == 0 alors le joueur n'est plus en echec, donc ce coup permet de ne pas être echec et mat
            {
                return 1; //couppossible = 1
            }
            recopietab(tab, copietab);
        }
    }
    if(n-1 >=0 && m-2 >= 0)
    {
        if(tab[n-1][m-2] < 0)
        {
            copietab[i][j] = 0;
            copietab[i-1][j-2] = 4;
            v = verifechec(copietab);
            if (v == 0) //si v == 0 alors le joueur n'est plus en echec, donc ce coup permet de ne pas être echec et mat
            {
                return 1; //couppossible = 1
            }
            recopietab(tab, copietab);
        }
    }
    if(n+1 < 8 && m-2 >= 0)
    {
        if(tab[n+1][m-2] < 0)
        {
            copietab[i][j] = 0;
            copietab[i+1][j-2] = 4;
            v = verifechec(copietab);
            if (v == 0) //si v == 0 alors le joueur n'est plus en echec, donc ce coup permet de ne pas être echec et mat
            {
                return 1; //couppossible = 1
            }
            recopietab(tab, copietab);
        }
    }
    return 0; // le cavalier ne permet pas de sortir de l'echec
}

int sortieechecreine(int tab[][8], int copietab[][8], int i, int j)
{
    int v, b = 1, bordure = 1; //b pour les boucles

    if(j+b < 8)
    {
        while(tab[i][j+b] <= 0 && bordure == 1)
        {
            copietab[i][j] = 0;
            copietab[i][j+b] = 10;
            v = verifechec(copietab);
            if (v == 0) //si v == 0 alors le joueur n'est plus en echec, donc ce coup permet de ne pas être echec et mat
            {
                return 1; //couppossible = 1
            }
            recopietab(tab, copietab);
            b++;
            if(j+b == 8)
            {
                bordure = 0;
            }
        }
    }
    b = 1;
    bordure = 1;
    if(j-b >= 0)
    {
         while(tab[i][j-b] <= 0 && bordure == 1)
        {
            copietab[i][j] = 0;
            copietab[i][j-b] = 10;
            v = verifechec(copietab);
            if (v == 0) //si v == 0 alors le joueur n'est plus en echec, donc ce coup permet de ne pas être echec et mat
            {
                return 1; //couppossible = 1
            }
            recopietab(tab, copietab);
            b++;
            if(j-b < 0)
            {
                bordure = 0;
            }
        }
    }
    b = 1;
    bordure = 1;
    if(i+b < 8)
    {
         while(tab[i+b][j] <= 0 && bordure == 1)
        {
            copietab[i][j] = 0;
            copietab[i+b][j] = 10;
            v = verifechec(copietab);
            if (v == 0) //si v == 0 alors le joueur n'est plus en echec, donc ce coup permet de ne pas être echec et mat
            {
                return 1; //couppossible = 1
            }
            recopietab(tab, copietab);
            b++;
            if(i+b == 8)
            {
                bordure = 0;
            }
        }
    }
    b = 1;
    bordure = 1;
    if(i-b >= 0)
    {
        while(tab[i-b][j] <= 0 && bordure == 1)
        {
            copietab[i][j] = 0;
            copietab[i-b][j] = 10;
            v = verifechec(copietab);
            if (v == 0) //si v == 0 alors le joueur n'est plus en echec, donc ce coup permet de ne pas être echec et mat
            {
                return 1; //couppossible = 1
            }
            recopietab(tab, copietab);
            b++;
            if(i-b < 0)
            {
                bordure = 0;
            }
        }
    }
    b = 1;
    bordure = 1;
    if(i+b < 8 && j+b < 8)
    {
        while(tab[i+b][j+b] <= 0 && bordure == 1)
        {
            copietab[i][j] = 0;
            copietab[i+b][j+b] = 10;
            v = verifechec(copietab);
            if (v == 0) //si v == 0 alors le joueur n'est plus en echec, donc ce coup permet de ne pas être echec et mat
            {
                return 1; //couppossible = 1
            }
            recopietab(tab, copietab);
            b++;
            if(i+b == 8 || j+b == 8)
            {
                bordure = 0;
            }
        }
    }
    b = 1;
    bordure = 1;
    if(i-b >= 0 && j-b >= 0)
    {
        while(tab[i-b][j-b] <= 0 && bordure == 1)
        {
            copietab[i][j] = 0;
            copietab[i-b][j-b] = 10;
            v = verifechec(copietab);
            if (v == 0) //si v == 0 alors le joueur n'est plus en echec, donc ce coup permet de ne pas être echec et mat
            {
                return 1; //couppossible = 1
            }
            recopietab(tab, copietab);
            b++;
            if(i-b < 0 || j-b < 0)
            {
                bordure = 0;
            }
        }
    }
    b = 1;
    bordure = 1;
    if(i-b >= 0 && j+b < 8)
    {
        while(tab[i-b][j+b] <= 0 && bordure == 1)
        {
            copietab[i][j] = 0;
            copietab[i-b][j+b] = 10;
            v = verifechec(copietab);
            if (v == 0) //si v == 0 alors le joueur n'est plus en echec, donc ce coup permet de ne pas être echec et mat
            {
                return 1; //couppossible = 1
            }
            recopietab(tab, copietab);
            b++;
            if(i-b < 0 || j+b == 8)
            {
                bordure = 0;
            }
        }
    }
    b = 1;
    bordure = 1;
    if(j-b >= 0 && i+b < 8)
    {
        while(tab[i+b][j-b] <= 0 && bordure == 1)
        {
            copietab[i][j] = 0;
            copietab[i+b][j-b] = 10;
            v = verifechec(copietab);
            if (v == 0) //si v == 0 alors le joueur n'est plus en echec, donc ce coup permet de ne pas être echec et mat
            {
                return 1; //couppossible = 1
            }
            recopietab(tab, copietab);
            b++;
            if(j-b < 0 || i+b == 8)
            {
                bordure = 0;
            }
        }
    }

    return 0; // cette reine ne permet pas de sortie de l'echec
}

int sortieechectour(int tab[][8], int copietab[][8], int i, int j)
{
    int v, b = 1, bordure = 1; //b pour les boucles

    if(j+b < 8)
    {
        while(tab[i][j+b] <= 0 && bordure == 1)
        {
            copietab[i][j] = 0;
            copietab[i][j+b] = 5;
            v = verifechec(copietab);
            if (v == 0) //si v == 0 alors le joueur n'est plus en echec, donc ce coup permet de ne pas être echec et mat
            {
                return 1; //couppossible = 1
            }
            recopietab(tab, copietab);
            b++;
            if(j+b == 8)
            {
                bordure = 0;
            }
        }
    }
    b = 1;
    bordure = 1;
    if(j-b >= 0)
    {
         while(tab[i][j-b] <= 0 && bordure == 1)
        {
            copietab[i][j] = 0;
            copietab[i][j-b] = 5;
            v = verifechec(copietab);
            if (v == 0) //si v == 0 alors le joueur n'est plus en echec, donc ce coup permet de ne pas être echec et mat
            {
                return 1; //couppossible = 1
            }
            recopietab(tab, copietab);
            b++;
            if(j-b < 0)
            {
                bordure = 0;
            }
        }
    }
    b = 1;
    bordure = 1;
    if(i+b < 8)
    {
         while(tab[i+b][j] <= 0 && bordure == 1)
        {
            copietab[i][j] = 0;
            copietab[i+b][j] = 5;
            v = verifechec(copietab);
            if (v == 0) //si v == 0 alors le joueur n'est plus en echec, donc ce coup permet de ne pas être echec et mat
            {
                return 1; //couppossible = 1
            }
            recopietab(tab, copietab);
            b++;
            if(i+b == 8)
            {
                bordure = 0;
            }
        }
    }
    b = 1;
    bordure = 1;
    if(i-b >= 0)
    {
        while(tab[i-b][j] <= 0 && bordure == 1)
        {
            copietab[i][j] = 0;
            copietab[i-b][j] = 5;
            v = verifechec(copietab);
            if (v == 0) //si v == 0 alors le joueur n'est plus en echec, donc ce coup permet de ne pas être echec et mat
            {
                return 1; //couppossible = 1
            }
            recopietab(tab, copietab);
            b++;
            if(i-b < 0)
            {
                bordure = 0;
            }
        }
    }
    return 0; // cette tour ne permet pas de sortie de l'echec
}


int sortieechecfou(int tab[][8], int copietab[][8], int i, int j)
{
    int v, b = 1, bordure = 1; //b pour les boucles

    if(i+b < 8 && j+b < 8)
    {
        while(tab[i+b][j+b] <= 0 && bordure == 1)
        {
            copietab[i][j] = 0;
            copietab[i+b][j+b] = 3;
            v = verifechec(copietab);
            if (v == 0) //si v == 0 alors le joueur n'est plus en echec, donc ce coup permet de ne pas être echec et mat
            {
                return 1; //couppossible = 1
            }
            recopietab(tab, copietab);
            b++;
            if(i+b == 8 || j+b == 8)
            {
                bordure = 0;
            }
        }
    }
    b = 1;
    bordure = 1;
    if(i-b >= 0 && j-b >= 0)
    {
        while(tab[i-b][j-b] <= 0 && bordure == 1)
        {
            copietab[i][j] = 0;
            copietab[i-b][j-b] = 3;
            v = verifechec(copietab);
            if (v == 0) //si v == 0 alors le joueur n'est plus en echec, donc ce coup permet de ne pas être echec et mat
            {
                return 1; //couppossible = 1
            }
            recopietab(tab, copietab);
            b++;
            if(i-b < 0 || j-b < 0)
            {
                bordure = 0;
            }
        }
    }
    b = 1;
    bordure = 1;
    if(i-b >= 0 && j+b < 8)
    {
        while(tab[i-b][j+b] <= 0 && bordure == 1)
        {
            copietab[i][j] = 0;
            copietab[i-b][j+b] = 3;
            v = verifechec(copietab);
            if (v == 0) //si v == 0 alors le joueur n'est plus en echec, donc ce coup permet de ne pas être echec et mat
            {
                return 1; //couppossible = 1
            }
            recopietab(tab, copietab);
            b++;
            if(i-b < 0 || j+b == 8)
            {
                bordure = 0;
            }
        }
    }
    b = 1;
    bordure = 1;
    if(j-b >= 0 && i+b < 8)
    {
        while(tab[i+b][j-b] <= 0 && bordure == 1)
        {
            copietab[i][j] = 0;
            copietab[i+b][j-b] = 3;
            v = verifechec(copietab);
            if (v == 0) //si v == 0 alors le joueur n'est plus en echec, donc ce coup permet de ne pas être echec et mat
            {
                return 1; //couppossible = 1
            }
            recopietab(tab, copietab);
            b++;
            if(j-b < 0 || i+b == 8)
            {
                bordure = 0;
            }
        }
    }
    return 0; // ce fou ne permet pas de sortie de l'echec
}


int sortieechecpion(int tab[][8], int copietab[][8], int i, int j)
{
    int v;
    if(i == 6 && tab[i-2][j] == 0 && tab[i-1][j] == 0)
    {
        copietab[i][j] = 0;
        copietab[i-2][j] = 1;
        v = verifechec(copietab);
        if (v == 0) //si v == 0 alors le joueur n'est plus en echec, donc ce coup permet de ne pas être echec et mat
        {
            return 1; //couppossible = 1
        }
        recopietab(tab, copietab);
    }

    if(tab[i-1][j]==0)
    {
        copietab[i][j] = 0;
        copietab[i-1][j] = 1;
        v = verifechec(copietab);
        if (v == 0) //si v == 0 alors le joueur n'est plus en echec, donc ce coup permet de ne pas être echec et mat
        {
            return 1; //couppossible = 1
        }
        recopietab(tab, copietab);
    }
    if(j+1 < 8 && i-1 >=0)
    {
        if(tab[i-1][j+1] < 0)
        {
            copietab[i][j] = 0;
            copietab[i-1][j+1] = 1;
            v = verifechec(copietab);
            if (v == 0) //si v == 0 alors le joueur n'est plus en echec, donc ce coup permet de ne pas être echec et mat
            {
                return 1; //couppossible = 1
            }
            recopietab(tab, copietab);
        }
    }
    if(j-1 >= 0 && i-1 >= 0)
    {
        if(tab[i-1][j-1] < 0)
        {
            copietab[i][j] = 0;
            copietab[i-1][j-1] = 1;
            v = verifechec(copietab);
            if (v == 0) //si v == 0 alors le joueur n'est plus en echec, donc ce coup permet de ne pas être echec et mat
            {
                return 1; //couppossible = 1
            }
            recopietab(tab, copietab);
        }
    }
    return 0; // ce pion ne permet pas de sortie de l'echec
}

int sortieechecroi(int tab[][8], int copietab[][8], int i, int j)
{
    int v;

    if (i+1 < 8 && j+1 < 8)
    {
        if(tab[i+1][j+1] < 1)
        {
            copietab[i][j] = 0;
            copietab[i+1][j+1] = 19;
            v = verifechec(copietab);
            if (v == 0) //si v == 0 alors le joueur n'est plus en echec, donc ce coup permet de ne pas être echec et mat
            {
                return 1; //couppossible = 1
            }
            recopietab(tab, copietab);
        }
    }
    if (i-1 >= 0 && j-1 >= 0)
    {
        if(tab[i-1][j-1] < 1)
        {
            copietab[i][j] = 0;
            copietab[i-1][j-1] = 19;
            v = verifechec(copietab);
            if (v == 0) //si v == 0 alors le joueur n'est plus en echec, donc ce coup permet de ne pas être echec et mat
            {
                return 1; //couppossible = 1
            }
            recopietab(tab, copietab);
        }
    }
    if (i+1 < 8 && j-1 >= 0)
    {
        if(tab[i+1][j-1] < 1)
        {
            copietab[i][j] = 0;
            copietab[i+1][j-1] = 19;
            v = verifechec(copietab);
            if (v == 0) //si v == 0 alors le joueur n'est plus en echec, donc ce coup permet de ne pas être echec et mat
            {
                return 1; //couppossible = 1
            }
            recopietab(tab, copietab);
        }
    }
    if (i-1 >= 0 && j+1 < 8)
    {
        if(tab[i-1][j+1] < 1)
        {
            copietab[i][j] = 0;
            copietab[i-1][j+1] = 19;
            v = verifechec(copietab);
            if (v == 0) //si v == 0 alors le joueur n'est plus en echec, donc ce coup permet de ne pas être echec et mat
            {
                return 1; //couppossible = 1
            }
            recopietab(tab, copietab);
        }
    }
    if (j+1 < 8)
    {
        if(tab[i][j+1] < 1)
        {
            copietab[i][j] = 0;
            copietab[i][j+1] = 19;
            v = verifechec(copietab);
            if (v == 0) //si v == 0 alors le joueur n'est plus en echec, donc ce coup permet de ne pas être echec et mat
            {
                return 1; //couppossible = 1
            }
            recopietab(tab, copietab);
        }
    }
    if (i+1 < 8)
    {
        if(tab[i+1][j] < 1)
        {
            copietab[i][j] = 0;
            copietab[i+1][j] = 19;
            v = verifechec(copietab);
            if (v == 0) //si v == 0 alors le joueur n'est plus en echec, donc ce coup permet de ne pas être echec et mat
            {
                return 1; //couppossible = 1
            }
            recopietab(tab, copietab);
        }
    }
    if (i-1 >= 0)
    {
        if(tab[i-1][j] < 1)
        {
            copietab[i][j] = 0;
            copietab[i-1][j] = 19;
            v = verifechec(copietab);
            if (v == 0) //si v == 0 alors le joueur n'est plus en echec, donc ce coup permet de ne pas être echec et mat
            {
                return 1; //couppossible = 1
            }
            recopietab(tab, copietab);
        }
    }
    if (j-1 >= 0)
    {
        if(tab[i][j-1] < 1)
        {
            copietab[i][j] = 0;
            copietab[i][j-1] = 19;
            v = verifechec(copietab);
            if (v == 0) //si v == 0 alors le joueur n'est plus en echec, donc ce coup permet de ne pas être echec et mat
            {
                return 1; //couppossible = 1
            }
            recopietab(tab, copietab);
        }
    }

    return 0;
}

int verifechecetmat(int tab[][8])
{
    int couppossible = 0;
    int i, j;
    int copietab[8][8];

    recopietab(tab, copietab);

    for(i=0; i < 8; i++)
    {
        for(j=0; j < 8; j++)
        {
            if(tab[i][j] == 1)
            {
                couppossible = sortieechecpion(tab, copietab, i, j);
                if (couppossible == 1)
                {
                    return 1;
                }
            } else if(tab[i][j] == 3)
            {
                couppossible = sortieechecfou(tab, copietab, i, j);
                if (couppossible == 1)
                {
                    return 1;
                }
            } else if(tab[i][j] == 4)
            {
                couppossible = sortieecheccavalier(tab, copietab, i, j);
                if (couppossible == 1)
                {
                    return 1;
                }
            } else if(tab[i][j] == 5)
            {
                couppossible = sortieechectour(tab, copietab, i, j);
                if (couppossible == 1)
                {
                    return 1;
                }
            } else if(tab[i][j] == 10)
            {
                couppossible = sortieechecreine(tab, copietab, i, j);
                if (couppossible == 1)
                {
                    return 1;
                }
            } else if(tab[i][j] == 19)
            {
                couppossible = sortieechecroi(tab, copietab, i, j);
                if (couppossible == 1)
                {
                    return 1;
                }
            }
        }
    }

    return 0; // echec et mat
}
