
#include <stdio.h>
#include <stdlib.h>
#include "joueur.h"
#include "adversaire.h"
#include "arbitre.h"
#include "echecmat.h"
#include "echecetmatjoueur2.h"
#include "joueur2.h"

int sortieecheccavaliernoir(int tab[][8], int copietab[][8], int n, int m)
{
    int v, i, j; //desolé flemme de changer nom variable du pavé
    i = n;
    j = m;
    if(n+2 < 8 && m-1 >= 0)
    {
        if(tab[n+2][m-1] > 0)
        {
            copietab[i][j] = 0;
            copietab[i+2][j-1] = -4;
            v = verifechecnoir(copietab);
            if (v == 0) //si v == 0 alors le joueur n'est plus en echec, donc ce coup permet de ne pas être echec et mat
            {
                return 1; //couppossible = 1
            }
            recopietab(tab, copietab);
        }
    }
    if(n+2 < 8 && m+1 < 8)
    {
        if(tab[n+2][m+1] > 0)
        {
            copietab[i][j] = 0;
            copietab[i+2][j+1] = -4;
            v = verifechecnoir(copietab);
            if (v == 0) //si v == 0 alors le joueur n'est plus en echec, donc ce coup permet de ne pas être echec et mat
            {
                return 1; //couppossible = 1
            }
            recopietab(tab, copietab);
        }
    }
    if(n-2 >=0 && m-1 >= 0)
    {
        if(tab[n-2][m-1] > 0)
        {
            copietab[i][j] = 0;
            copietab[i-2][j-1] = -4;
            v = verifechecnoir(copietab);
            if (v == 0) //si v == 0 alors le joueur n'est plus en echec, donc ce coup permet de ne pas être echec et mat
            {
                return 1; //couppossible = 1
            }
            recopietab(tab, copietab);
        }
    }
    if(n-2 >= 0 && m+1 < 8)
    {
        if(tab[n-2][m+1] > 0)
        {
            copietab[i][j] = 0;
            copietab[i-2][j+1] = -4;
            v = verifechecnoir(copietab);
            if (v == 0) //si v == 0 alors le joueur n'est plus en echec, donc ce coup permet de ne pas être echec et mat
            {
                return 1; //couppossible = 1
            }
            recopietab(tab, copietab);
        }
    }
    if(n-1 >=0 && m+2 < 8)
    {
        if(tab[n-1][m+2] > 0)
        {
            copietab[i][j] = 0;
            copietab[i-1][j+2] = -4;
            v = verifechecnoir(copietab);
            if (v == 0) //si v == 0 alors le joueur n'est plus en echec, donc ce coup permet de ne pas être echec et mat
            {
                return 1; //couppossible = 1
            }
            recopietab(tab, copietab);
        }
    }
    if(n+1 < 8 && m+2 < 8)
    {
        if(tab[n+1][m+2] > 0)
        {
            copietab[i][j] = 0;
            copietab[i+1][j+2] = -4;
            v = verifechecnoir(copietab);
            if (v == 0) //si v == 0 alors le joueur n'est plus en echec, donc ce coup permet de ne pas être echec et mat
            {
                return 1; //couppossible = 1
            }
            recopietab(tab, copietab);
        }
    }
    if(n-1 >=0 && m-2 >= 0)
    {
        if(tab[n-1][m-2] > 0)
        {
            copietab[i][j] = 0;
            copietab[i-1][j-2] = -4;
            v = verifechecnoir(copietab);
            if (v == 0) //si v == 0 alors le joueur n'est plus en echec, donc ce coup permet de ne pas être echec et mat
            {
                return 1; //couppossible = 1
            }
            recopietab(tab, copietab);
        }
    }
    if(n+1 < 8 && m-2 >= 0)
    {
        if(tab[n+1][m-2] > 0)
        {
            copietab[i][j] = 0;
            copietab[i+1][j-2] = -4;
            v = verifechecnoir(copietab);
            if (v == 0) //si v == 0 alors le joueur n'est plus en echec, donc ce coup permet de ne pas être echec et mat
            {
                return 1; //couppossible = 1
            }
            recopietab(tab, copietab);
        }
    }
    return 0; // le cavalier ne permet pas de sortir de l'echec
}

int sortieechecreinenoir(int tab[][8], int copietab[][8], int i, int j)
{
    int v, b = 1; //b pour les boucles

    while(tab[i][j+b] >= 0 && j+b < 7)
    {
        copietab[i][j] = 0;
        copietab[i][j+b] = -10;
        v = verifechecnoir(copietab);
        if (v == 0) //si v == 0 alors le joueur n'est plus en echec, donc ce coup permet de ne pas être echec et mat
        {
            return 1; //couppossible = 1
        }
        recopietab(tab, copietab);
        b++;
    }
    b = 1;
     while(tab[i][j-b] >= 0 && j-b > 0)
    {
        copietab[i][j] = 0;
        copietab[i][j-b] = -10;
        v = verifechecnoir(copietab);
        if (v == 0) //si v == 0 alors le joueur n'est plus en echec, donc ce coup permet de ne pas être echec et mat
        {
            return 1; //couppossible = 1
        }
        recopietab(tab, copietab);
        b++;
    }
    b = 1;
     while(tab[i+b][j] >= 0 && i+b < 7)
    {
        copietab[i][j] = 0;
        copietab[i+b][j] = -10;
        v = verifechecnoir(copietab);
        if (v == 0) //si v == 0 alors le joueur n'est plus en echec, donc ce coup permet de ne pas être echec et mat
        {
            return 1; //couppossible = 1
        }
        recopietab(tab, copietab);
        b++;
    }
    b = 1;
    while(tab[i-b][j] >= 0 && i-b > 0)
    {
        copietab[i][j] = 0;
        copietab[i-b][j] = -10;
        v = verifechecnoir(copietab);
        if (v == 0) //si v == 0 alors le joueur n'est plus en echec, donc ce coup permet de ne pas être echec et mat
        {
            return 1; //couppossible = 1
        }
        recopietab(tab, copietab);
        b++;
    }
    b = 1;
    while(tab[i][j+b] >= 0 && i+b < 7)
    {
        copietab[i][j] = 0;
        copietab[i][j+b] = -10;
        v = verifechecnoir(copietab);
        if (v == 0) //si v == 0 alors le joueur n'est plus en echec, donc ce coup permet de ne pas être echec et mat
        {
            return 1; //couppossible = 1
        }
        recopietab(tab, copietab);
        b++;
    }
    b = 1;
     while(tab[i][j-b] >= 0 && i-b > 0)
    {
        copietab[i][j] = 0;
        copietab[i][j-b] = -10;
        v = verifechecnoir(copietab);
        if (v == 0) //si v == 0 alors le joueur n'est plus en echec, donc ce coup permet de ne pas être echec et mat
        {
            return 1; //couppossible = 1
        }
        recopietab(tab, copietab);
        b++;
    }
    b = 1;
     while(tab[i+b][j] >= 0 && i+b < 7)
    {
        copietab[i][j] = 0;
        copietab[i+b][j] = -10;
        v = verifechecnoir(copietab);
        if (v == 0) //si v == 0 alors le joueur n'est plus en echec, donc ce coup permet de ne pas être echec et mat
        {
            return 1; //couppossible = 1
        }
        recopietab(tab, copietab);
        b++;
    }
    b = 1;
    while(tab[i-b][j] >= 0 && i-b > 0)
    {
        copietab[i][j] = 0;
        copietab[i-b][j] = -10;
        v = verifechecnoir(copietab);
        if (v == 0) //si v == 0 alors le joueur n'est plus en echec, donc ce coup permet de ne pas être echec et mat
        {
            return 1; //couppossible = 1
        }
        recopietab(tab, copietab);
        b++;
    }
    recopietab(tab, copietab);
    return 0; // cette reine ne permet pas de sortie de l'echec
}

int sortieechectournoir(int tab[][8], int copietab[][8], int i, int j)
{
    int v, b = 1; //b pour les boucles

    while(tab[i][j+b] >= 0 && j+b < 7)
    {
        copietab[i][j] = 0;
        copietab[i][j+b] = -5;
        v = verifechecnoir(copietab);
        if (v == 0) //si v == 0 alors le joueur n'est plus en echec, donc ce coup permet de ne pas être echec et mat
        {
            return 1; //couppossible = 1
        }
        recopietab(tab, copietab);
        b++;
    }
    b = 1;
     while(tab[i][j-b] >= 0 && j-b > 0)
    {
        copietab[i][j] = 0;
        copietab[i][j-b] = -5;
        v = verifechecnoir(copietab);
        if (v == 0) //si v == 0 alors le joueur n'est plus en echec, donc ce coup permet de ne pas être echec et mat
        {
            return 1; //couppossible = 1
        }
        recopietab(tab, copietab);
        b++;
    }
    b = 1;
     while(tab[i+b][j] >= 0 && i+b < 7)
    {
        copietab[i][j] = 0;
        copietab[i+b][j] = -5;
        v = verifechecnoir(copietab);
        if (v == 0) //si v == 0 alors le joueur n'est plus en echec, donc ce coup permet de ne pas être echec et mat
        {
            return 1; //couppossible = 1
        }
        recopietab(tab, copietab);
        b++;
    }
    b = 1;
    while(tab[i-b][j] >= 0 && i-b > 0)
    {
        copietab[i][j] = 0;
        copietab[i-b][j] = -5;
        v = verifechecnoir(copietab);
        if (v == 0) //si v == 0 alors le joueur n'est plus en echec, donc ce coup permet de ne pas être echec et mat
        {
            return 1; //couppossible = 1
        }
        recopietab(tab, copietab);
        b++;
    }
    recopietab(tab, copietab);
    return 0; // cette tour ne permet pas de sortie de l'echec
}


int sortieechecfounoir(int tab[][8], int copietab[][8], int i, int j)
{
    int v, b = 1; //b pour les boucles

    while(tab[i+b][j+b] >= 0 && i+b < 7 && j+b < 7)
    {
        copietab[i][j] = 0;
        copietab[i+b][j+b] = -3;
        v = verifechecnoir(copietab);
        if (v == 0) //si v == 0 alors le joueur n'est plus en echec, donc ce coup permet de ne pas être echec et mat
        {
            return 1; //couppossible = 1
        }
        recopietab(tab, copietab);
        b++;
    }
    b = 1;
    while(tab[i+b][j-b] >= 0 && i+b < 7 && j-b > 0)
    {
        copietab[i][j] = 0;
        copietab[i+b][j-b] = -3;
        v = verifechecnoir(copietab);
        if (v == 0) //si v == 0 alors le joueur n'est plus en echec, donc ce coup permet de ne pas être echec et mat
        {
            return 1; //couppossible = 1
        }
        recopietab(tab, copietab);
        b++;
    }
    b = 1;
    while(tab[i-b][j+b] >= 0 && i-b > 0 && j+b < 7)
    {
        copietab[i][j] = 0;
        copietab[i-b][j+b] = -3;
        v = verifechecnoir(copietab);
        if (v == 0) //si v == 0 alors le joueur n'est plus en echec, donc ce coup permet de ne pas être echec et mat
        {
            return 1; //couppossible = 1
        }
        recopietab(tab, copietab);
        b++;
    }
    b = 1;
    while(tab[i-b][j-b] >= 0 && i-b > 0 && j-b > 0)
    {
        copietab[i][j] = 0;
        copietab[i-b][j-b] = -3;
        v = verifechecnoir(copietab);
        if (v == 0) //si v == 0 alors le joueur n'est plus en echec, donc ce coup permet de ne pas être echec et mat
        {
            return 1; //couppossible = 1
        }
        recopietab(tab, copietab);
        b++;
    }

    recopietab(tab, copietab);
    return 0; // ce fou ne permet pas de sortie de l'echec
}


int sortieechecpionnoir(int tab[][8], int copietab[][8], int i, int j)
{
    int v;
    if(i == 1 && tab[i+2][j] == 0 && tab[i+1][j] == 0)
    {
        copietab[i][j] = 0;
        copietab[i+2][j] = -1;
        v = verifechecnoir(copietab);
        if (v == 0) //si v == 0 alors le joueur n'est plus en echec, donc ce coup permet de ne pas être echec et mat
        {
            return 1; //couppossible = 1
        }
        recopietab(tab, copietab);
    }

    if(tab[i+1][j]==0)
    {
        copietab[i][j] = 0;
        copietab[i+1][j] = -1;
        v = verifechecnoir(copietab);
        if (v == 0) //si v == 0 alors le joueur n'est plus en echec, donc ce coup permet de ne pas être echec et mat
        {
            return 1; //couppossible = 1
        }
        recopietab(tab, copietab);
    }

    if(j+1 < 8 && i+1 < 8)
    {
        if(tab[i+1][j+1] > 0)
        {
            copietab[i][j] = 0;
            copietab[i-1][j+1] = -1;
            v = verifechecnoir(copietab);
            if (v == 0) //si v == 0 alors le joueur n'est plus en echec, donc ce coup permet de ne pas être echec et mat
            {
                return 1; //couppossible = 1
            }
            recopietab(tab, copietab);
        }
    }
    if(j-1 >= 0 && i+1 < 8)
    {
        if(tab[i+1][j-1] > 0)
        {
            copietab[i][j] = 0;
            copietab[i+1][j-1] = -1;
            v = verifechecnoir(copietab);
            if (v == 0) //si v == 0 alors le joueur n'est plus en echec, donc ce coup permet de ne pas être echec et mat
            {
                return 1; //couppossible = 1
            }
            recopietab(tab, copietab);
        }
    }
    return 0; // ce pion ne permet pas de sortie de l'echec
}

int sortieechecroinoir(int tab[][8], int copietab[][8], int i, int j)
{
    int v;

    if (i+1 < 8 && j+1 < 8)
    {
        if(tab[i+1][j+1] > -1)
        {
            copietab[i][j] = 0;
            copietab[i+1][j+1] = -19;
            v = verifechecnoir(copietab);
            if (v == 0) //si v == 0 alors le joueur n'est plus en echec, donc ce coup permet de ne pas être echec et mat
            {
                return 1; //couppossible = 1
            }
            recopietab(tab, copietab);
        }
    }
    if (i-1 >= 0 && j-1 >= 0)
    {
        if(tab[i-1][j-1] > -1)
        {
            copietab[i][j] = 0;
            copietab[i-1][j-1] = -19;
            v = verifechecnoir(copietab);
            if (v == 0) //si v == 0 alors le joueur n'est plus en echec, donc ce coup permet de ne pas être echec et mat
            {
                return 1; //couppossible = 1
            }
            recopietab(tab, copietab);
        }
    }
    if (i+1 < 8 && j-1 >= 0)
    {
        if(tab[i+1][j-1] > -1)
        {
            copietab[i][j] = 0;
            copietab[i+1][j-1] = -19;
            v = verifechecnoir(copietab);
            if (v == 0) //si v == 0 alors le joueur n'est plus en echec, donc ce coup permet de ne pas être echec et mat
            {
                return 1; //couppossible = 1
            }
            recopietab(tab, copietab);
        }
    }
    if (i-1 >= 0 && j+1 < 8)
    {
        if(tab[i-1][j+1] > -1)
        {
            copietab[i][j] = 0;
            copietab[i-1][j+1] = -19;
            v = verifechecnoir(copietab);
            if (v == 0) //si v == 0 alors le joueur n'est plus en echec, donc ce coup permet de ne pas être echec et mat
            {
                return 1; //couppossible = 1
            }
            recopietab(tab, copietab);
        }
    }
    if (j+1 < 8)
    {
        if(tab[i][j+1] > -1)
        {
            copietab[i][j] = 0;
            copietab[i][j+1] = -19;
            v = verifechecnoir(copietab);
            if (v == 0) //si v == 0 alors le joueur n'est plus en echec, donc ce coup permet de ne pas être echec et mat
            {
                return 1; //couppossible = 1
            }
            recopietab(tab, copietab);
        }
    }
    if (i+1 < 8)
    {
        if(tab[i+1][j] > -1)
        {
            copietab[i][j] = 0;
            copietab[i+1][j] = -19;
            v = verifechecnoir(copietab);
            if (v == 0) //si v == 0 alors le joueur n'est plus en echec, donc ce coup permet de ne pas être echec et mat
            {
                return 1; //couppossible = 1
            }
            recopietab(tab, copietab);
        }
    }
    if (i-1 >= 0)
    {
        if(tab[i-1][j] > -1)
        {
            copietab[i][j] = 0;
            copietab[i-1][j] = -19;
            v = verifechecnoir(copietab);
            if (v == 0) //si v == 0 alors le joueur n'est plus en echec, donc ce coup permet de ne pas être echec et mat
            {
                return 1; //couppossible = 1
            }
            recopietab(tab, copietab);
        }
    }
    if (j-1 >= 0)
    {
        if(tab[i][j-1] > -1)
        {
            copietab[i][j] = 0;
            copietab[i][j-1] = -19;
            v = verifechecnoir(copietab);
            if (v == 0) //si v == 0 alors le joueur n'est plus en echec, donc ce coup permet de ne pas être echec et mat
            {
                return 1; //couppossible = 1
            }
            recopietab(tab, copietab);
        }
    }

    return 0;
}

int verifechecetmatnoir(int tab[][8])
{
    int couppossible = 0;
    int i, j;
    int copietab[8][8];

    recopietab(tab, copietab);

    for(i=0; i < 8; i++)
    {
        for(j=0; j < 8; j++)
        {
            if(tab[i][j] == -1)
            {
                couppossible = sortieechecpionnoir(tab, copietab, i, j);
                if (couppossible == 1)
                {
                    return 1;
                }
            } else if(tab[i][j] == -3)
            {
                couppossible = sortieechecfounoir(tab, copietab, i, j);
                if (couppossible == 1)
                {
                    return 1;
                }
            } else if(tab[i][j] == -4)
            {
                couppossible = sortieecheccavaliernoir(tab, copietab, i, j);
                if (couppossible == 1)
                {
                    return 1;
                }
            } else if(tab[i][j] == -5)
            {
                couppossible = sortieechectournoir(tab, copietab, i, j);
                if (couppossible == 1)
                {
                    return 1;
                }
            } else if(tab[i][j] == -10)
            {
                couppossible = sortieechecreinenoir(tab, copietab, i, j);
                if (couppossible == 1)
                {
                    return 1;
                }
            } else if(tab[i][j] == -19)
            {
                couppossible = sortieechecroinoir(tab, copietab, i, j);
                if (couppossible == 1)
                {
                    return 1;
                }
            }
        }
    }

    return 0; // echec et mat
}
