#include <stdio.h>
#include <stdlib.h>
#include "joueur.h"
#include "adversaire.h"
#include "arbitre.h"
#include "echecmat.h"

void recopietab(int tab[][8], int copietab[][8])
{
    int i, j;
    for(i=0; i < 8; i++)
    {
        for(j=0; j < 8; j++)
        {
            copietab[i][j] = tab[i][j];
        }
    }
}

int rocblanc = 1; //pas de roc blanc (debut de partie)
int rocnoir = 1; //pas de roc noir (debut de partie)

void affichageplateau(int tab[][8])
{

    int i, j;

    printf("\n\n --------------------------------- \n\n Echiquier : \n\n");
    for(i=0; i<8; i++)
    {
        for(j=0; j<8; j++)
        {
            if(tab[i][j]<0)
            {
                printf(" %d ", tab[i][j]);
            } else if (tab[i][j]<= -10 || tab[i][j] >=10)
            {
                printf("  %d", tab[i][j]);
            } else
            {
                printf("  %d ", tab[i][j]);
            }
        }

        printf("\n");
    }
    printf("\n\n --------------------------------- \n\n");
}

int roc_ok_ou_pas(int n)
{

    if(n == 0)//demande des blanc de roc
    {
        if (rocblanc ==1)
        {
            rocblanc = 0;
            return 1; //laisser faire
        } else
        {
            return 0; //peux pas roc
        }
    } else if(n == 1)//demande des noirs de roc
    {
        if (rocnoir ==1)
        {
            rocnoir = 0;;
            return 1; //laisser faire
        } else
        {
            return 0; //peux pas roc
        }
    } else if(n == 2) //roiblanc a bougé
    {
        rocblanc = 0;
    } else if(n == 3) //roinoir a bougé
    {
        rocnoir = 0;
    }
    return 0;
}



int verifpionechec(int tab[][8], int n, int m)
{
    if(n+1 < 8 && m+1 < 8)
    {
        if(tab[n+1][m+1] == 19)
        {
            return 1; //le roi adverse est en echec par le pion
        }
    }
    if(n+1 < 8 && m-1 >= 0)
    {
        if(tab[n+1][m-1] == 19)
        {
            return 1; //le roi adverse est en echec par le pion
        }
    }
    return 0;
}

int verifcavalierechec(int tab[][8], int n, int m)
{
    if(n+2 < 8)
    {
        if(m-1 >= 0)
        {
            if(tab[n+2][m-1] == 19)
            {
                return 1;
            }
        }
        if(m+1 < 8)
        {
            if(tab[n+2][m+1] == 19)
            {
                return 1;
            }
        }
    }

    if(n-2 >= 0)
    {
        if(m-1 >= 0)
        {
            if(tab[n-2][m-1] == 19)
            {
                return 1;
            }
        }
        if(m+1 < 8)
        {
            if(tab[n-2][m+1] == 19)
            {
                return 1;
            }
        }
    }

    if(m-2 >= 0)
    {
        if(n-1 >= 0)
        {
            if(tab[n-1][m-2] == 19)
            {
                return 1;
            }
        }
        if(n+1 < 8)
        {
            if(tab[n-1][m-2] == 19)
            {
                return 1;
            }
        }
    }

    if(m+2 < 8)
    {
        if(n-1 >= 0)
        {
            if(tab[n-1][m+2] == 19)
            {
                return 1;
            }
        }
        if(n+1 < 8)
        {
            if(tab[n+1][m+2] == 19)
            {
                return 1;
            }
        }
    }


    return 0; // le cavalier ne mets pas le roi en echec
}

int veriftourechec(int tab[][8], int n, int m)
{
    int i = 1;
    while(tab[n][m+i] == 0 && m+i < 7)
    {
        i++;
    }
    if(tab[n][m+i] == 19)
    {
        return 1;
    } else
    {
        i = 1;
    }

     while(tab[n][m-i] == 0 && m-i > 0)
    {
        i++;
    }
    if(tab[n][m-i] == 19)
    {
        return 1;
    } else
    {
        i = 1;
    }

     while(tab[n+i][m] == 0 && n+i < 7)
    {
        i++;
    }
    if(tab[n+i][m] == 19)
    {
        return 1;
    } else
    {
        i = 1;
    }

    while(tab[n-i][m] == 0 && n-i > 0)
    {
        i++;
    }
    if(tab[n-i][m] == 19)
    {
        return 1;
    } else
    {
        i = 1;
    }

    return 0; //la tour n'attaque pas le roi

}

int veriffouechec(int tab[][8], int n, int m)
{
    int i = 1, j = 1;
    while(tab[n+i][m+j] == 0 && n+i < 7 && m+j < 7)
    {
        i++;
        j++;
    }
    if(tab[n+i][m+j] == 19)
    {
        return 1;
    } else
    {
        i = 1;
        j = 1;
    }

    while(tab[n+i][m-j] == 0 && n+i < 7 && m-j > 0)
    {
        i++;
        j++;
    }
    if(tab[n+i][m-j] == 19)
    {
        return 1;
    } else
    {
        i = 1;
        j = 1;
    }

    while(tab[n-i][m+j] == 0 && n-i > 0 && m+j < 7)
    {
        i++;
        j++;
    }
    if(tab[n-i][m+j] == 19)
    {
        return 1;
    } else
    {
        i = 1;
        j = 1;
    }

    while(tab[n-i][m-j] == 0 && n-i > 0 && m-j > 0)
    {
        i++;
        j++;
    }
    if(tab[n+i][m+j] == 19)
    {
        return 1;
    } else
    {
        i = 1;
        j = 1;
    }

    return 0; //le fou ne mets pas le roi adverse en echec
}

int verifreineechec(int tab[][8], int i, int j)
{
    int v;
    v = veriffouechec(tab, i, j);
    if (v == 0)
    {
        v = veriftourechec(tab, i, j);
    }
    return v;
}

int verifechec(int tab[][8])
{
    int i, j, v;

    for(i = 0; i < 8; i++)
    {
        for(j=0; j<8; j++)
        {
            if(tab[i][j] == -1)
            {
                v = verifpionechec(tab, i, j);
                if(v == 1)
                {
                    break;
                }
            } else if (tab[i][j] == -3)
            {
                v = veriffouechec(tab, i, j);
                if(v == 1)
                {
                    break;
                }
            } else if (tab[i][j] == -4)
            {
                v = verifcavalierechec(tab, i, j);
                if(v == 1)
                {
                    break;
                }
            } else if (tab[i][j] == -5)
            {
                v = veriftourechec(tab, i, j);
                if(v == 1)
                {
                    break;
                }
            } else if (tab[i][j] == -10)
            {
                v = verifreineechec(tab, i, j);
                if(v == 1)
                {
                    break;
                }
            }
        }
    }
    return v; //si v == 1 alors le joueur est en échec

}



void aide()
{
    int i;

    printf("\n\n Numerotation index colonne pour la saisi : \n \n");
    for(i=0; i<8; i++)
    {
        printf(" %d ", i);
    }
    printf("\n\n Numerotation index ligne pour la saisi : \n \n");
    for(i=0; i<8; i++)
    {
        printf(" %d\n", i);
    }
}
