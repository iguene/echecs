#include <stdio.h>
#include <stdlib.h>
#include "joueur.h"
#include "adversaire.h"
#include "arbitre.h"
#include "echecmat.h"
#include "joueur2.h"

int choix = 1;

void queladversaire()
{
    printf(" \n\n Entrez 1 pour affronter une IA ou 2 pour affronter un joueur 2 : ");
    scanf("%d", &choix);

    if(choix == 1)
    {
        printf("\n\n Match contre l'IA \n\n");
    } else if(choix == 2)
    {
        printf("\n\n Match entre joueur 1 et joueur 2 \n\n");
    } else
    {
        queladversaire();
    }
}

void quelpiecechoisi(int tab[][8], int li, int ci)
{
    if(tab[li][ci] == 1)
    {
        printf("\n\n Vous avez choisi un pion de coordonees : %d ; %d \n\n", li, ci);
    } else if(tab[li][ci] == 3)
    {
        printf("\n\n Vous avez choisi un fou de coordonees : %d ; %d \n\n", li, ci);
    } else if(tab[li][ci] == 4)
    {
        printf("\n\n Vous avez choisi un cavalier de coordonees : %d ; %d \n\n", li, ci);
    } else if(tab[li][ci] == 5)
    {
        printf("\n\n Vous avez choisi une tour de coordonees : %d ; %d \n\n", li, ci);
    } else if(tab[li][ci] == 10)
    {
        printf("\n\n Vous avez choisi une reine de coordonees : %d ; %d \n\n", li, ci);
    } else if(tab[li][ci] == 19)
    {
        printf("\n\n Vous avez choisi le roi de coordonees : %d ; %d \n\n", li, ci);
    }
}


int deplacementroi(int tab[][8], int li, int ci, int ld, int cd)
{
    int canroc;
    if(tab[ld+1][cd+1] == -19 || tab[ld+1][cd] == -19 || tab[ld+1][cd-1] == -19 || tab[ld][cd+1] == -19 || tab[ld][cd-1] == -19 || tab[ld-1][cd-1] == -19 || tab[ld-1][cd] == -19 || tab[ld-1][cd+1] == -19)
    {
        printf("\n\n Ce coup n'est pas legal \n"); //le roi ne peut pas s'approcher de l'autre roi
        return 0;
    }
    if(tab[ld][cd] == 5 && ld == 7 && ld == li && cd == ci+3)
    {
        if((tab[li][ci+1]==0 &&tab[li][ci+2]==0) ) //roc
        {
            canroc = roc_ok_ou_pas(0);
            if(canroc == 1)
            {
                tab[li][ci] = 0;
                tab[ld][cd] = 0;
                tab[li][ci+1] = 5;
                tab[li][ci+2] = 19;
            } else
            {
                printf("\n\n Vous n'avez plus le droit de roc \n");
                return 0;
            }
        }
    } else if((ld == li+1 || ld == li-1) && cd == ci)
    {
        tab[li][ci] = 0;
        tab[ld][cd] = 19;
        roc_ok_ou_pas(2); //le roi a bougé donc enleve le roi au roc

    } else if (ld == li && (cd == ci+1 || cd == ci-1))
    {
        tab[li][ci] = 0;
        tab[ld][cd] = 19;
        roc_ok_ou_pas(2);

    } else if((ld == li + 1 || ld == li - 1) && (cd == ci-1 || cd == ci+1 ))
    {
        tab[li][ci] = 0;
        tab[ld][cd] = 19;
        roc_ok_ou_pas(2);
    } else
    {
        printf("\n\n Ce coup n'est pas legal \n");
        return 0;
    }

    return 1;
}


int deplacementreine(int tab[][8], int li, int ci, int ld, int cd)
{
    int i, vide = 1;
    if(li>ld && ci < cd) //diagonale bas gauche à haut droite
    {
        for(i=1; i<li - ld; i++)
        {
            if (tab[li-i][ci+i] != 0)
            {
                vide = 0; // il y a une case pas vide
            }
        }
        if(vide == 1) // il y a que des case vides entre les deux cases
        {
            tab[li][ci] = 0;
            tab[ld][cd] = 10;
        } else
        {
            printf("\n\n Ce coup n'est pas legal \n");
            return 0;
        }
    } else if(li < ld && ci > cd) //diagonale haut droite à bas gauche
    {
        for(i=1; i<ld - li; i++)
        {
            if (tab[li+i][ci-i] != 0)
            {
                vide = 0; // il y a une case pas vide
            }
        }
        if(vide == 1) // il y a que des case vides entre les deux cases
        {
            tab[li][ci] = 0;
            tab[ld][cd] = 10;
        } else
        {
            printf("\n\n Ce coup n'est pas legal \n");
            return 0;
        }
    } else if(li > ld && ci > cd) //diagonale bas droite à haut gauche
    {
        for(i=1; i<li - ld; i++)
        {
            if (tab[li-i][ci-i] != 0)
            {
                vide = 0; // il y a une case pas vide
            }
        }
        if(vide == 1) // il y a que des case vides entre les deux cases
        {
            tab[li][ci] = 0;
            tab[ld][cd] = 10;
        } else
        {
            printf("\n\n Ce coup n'est pas legal \n");
            return 0;
        }
    } else if(li < ld && ci < cd) //diagonale haut gauche à bas droite
    {
        for(i=1; i<ld - li; i++)
        {
            if (tab[li+i][ci+i] != 0)
            {
                vide = 0; // il y a une case pas vide
            }
        }
        if(vide == 1) // il y a que des case vides entre les deux cases
        {
            tab[li][ci] = 0;
            tab[ld][cd] = 10;
        } else
        {
            printf("\n\n Ce coup n'est pas legal \n");
            return 0;
        }
    } else if(ld == li && cd > ci) // déplacement gauche à droite
    {
        for(i=1; i<cd-ci; i++)
        {
            if(tab[li][ci+i] != 0)
            {
                vide = 0; // il y a une case pas vide entre les deux cases donc c'est pas legal
            }
        }
        if(vide == 1)
        {
            tab[li][ci] = 0;
            tab[ld][cd] = 10;
        } else
        {
            printf("\n\n Ce coup n'est pas legal \n");
            return 0;
        }
    } else if(ld == li && cd < ci) // déplacement droite à gauche
    {
        for(i=1; i<ci-cd; i++)
        {
            if(tab[li][ci-i] != 0)
            {
                vide = 0; // il y a une case pas vide entre les deux cases donc c'est pas legal
            }
        }
        if(vide == 1)
        {
            tab[li][ci] = 0;
            tab[ld][cd] = 10;
        } else
        {
            printf("\n\n Ce coup n'est pas legal \n");
            return 0;
        }
    } else if(ld > li && cd == ci) // déplacement haut en bas
    {
        for(i=1; i<ld-li; i++)
        {
            if(tab[li+i][ci] != 0)
            {
                vide = 0; // il y a une case pas vide entre les deux cases donc c'est pas legal
            }
        }
        if(vide == 1)
        {
            tab[li][ci] = 0;
            tab[ld][cd] = 10;
        } else
        {
            printf("\n\n Ce coup n'est pas legal \n");
            return 0;
        }
    } else if(ld < li && cd == ci) // déplacement bas en haut
    {
        for(i=1; i<li-ld; i++)
        {
            if(tab[li-i][ci] != 0)
            {
                vide = 0; // il y a une case pas vide entre les deux cases donc c'est pas legal
            }
        }
        if(vide == 1)
        {
            tab[li][ci] = 0;
            tab[ld][cd] = 10;
        } else
        {
            printf("\n\n Ce coup n'est pas legal \n");
            return 0;
        }
    } else
    {
        printf("\n\n Ce coup n'est pas legal \n");
        return 0;
    }

    return 1;
}

int deplacementtour(int tab[][8], int li, int ci, int ld, int cd)
{
    int i, vide = 1;
    if(ld == li && cd > ci) // déplacement gauche à droite
    {
        for(i=1; i<cd-ci; i++)
        {
            if(tab[li][ci+i] != 0)
            {
                vide = 0; // il y a une case pas vide entre les deux cases donc c'est pas legal
            }
        }
        if(vide == 1)
        {
            tab[li][ci] = 0;
            tab[ld][cd] = 5;
        } else
        {
            printf("\n\n Ce coup n'est pas legal \n");
            return 0;
        }
    } else if(ld == li && cd < ci) // déplacement droite à gauche
    {
        for(i=1; i<ci-cd; i++)
        {
            if(tab[li][ci-i] != 0)
            {
                vide = 0; // il y a une case pas vide entre les deux cases donc c'est pas legal
            }
        }
        if(vide == 1)
        {
            tab[li][ci] = 0;
            tab[ld][cd] = 5;
        } else
        {
            printf("\n\n Ce coup n'est pas legal \n");
            return 0;
        }
    } else if(ld > li && cd == ci) // déplacement haut en bas
    {
        for(i=1; i<ld-li; i++)
        {
            if(tab[li+i][ci] != 0)
            {
                vide = 0; // il y a une case pas vide entre les deux cases donc c'est pas legal
            }
        }
        if(vide == 1)
        {
            tab[li][ci] = 0;
            tab[ld][cd] = 5;
        } else
        {
            printf("\n\n Ce coup n'est pas legal \n");
            return 0;
        }
    } else if(ld < li && cd == ci) // déplacement bas en haut
    {
        for(i=1; i<li-ld; i++)
        {
            if(tab[li-i][ci] != 0)
            {
                vide = 0; // il y a une case pas vide entre les deux cases donc c'est pas legal
            }
        }
        if(vide == 1)
        {
            tab[li][ci] = 0;
            tab[ld][cd] = 5;
        } else
        {
            printf("\n\n Ce coup n'est pas legal \n");
            return 0;
        }
    } else
    {
        printf("\n\n Ce coup n'est pas legal \n");
        return 0;
    }

    return 1; // coup effectué
}

int deplacementcavalier(int tab[][8], int li, int ci, int ld, int cd)
{
    if((ld == li - 2 || ld == li+2) && (cd == ci - 1 || cd == ci + 1))
    {
        tab[li][ci] = 0;
        tab[ld][cd] = 4;
    } else if((ld == li - 1 || ld == li+1) && (cd == ci - 2 || cd == ci + 2))
    {
        tab[li][ci] = 0;
        tab[ld][cd] = 4;
    } else
    {
        printf("\n\n Ce coup n'est pas legal \n");
        return 0;
    }

    return 1; // coup effectué
}

int deplacementfou(int tab[][8], int li, int ci, int ld, int cd)
{
    int i, vide = 1;
    if(li>ld && ci < cd) //diagonale bas gauche à haut droite
    {
        for(i=1; i<li - ld; i++)
        {
            if (tab[li-i][ci+i] != 0)
            {
                vide = 0; // il y a une case pas vide
            }
        }
        if(vide == 1) // il y a que des case vides entre les deux cases
        {
            tab[li][ci] = 0;
            tab[ld][cd] = 3;
        } else
        {
            printf("\n\n Ce coup n'est pas legal \n");
            return 0;
        }
    } else if(li < ld && ci > cd) //diagonale haut droite à bas gauche
    {
        for(i=1; i<ld - li; i++)
        {
            if (tab[li+i][ci-i] != 0)
            {
                vide = 0; // il y a une case pas vide
            }
        }
        if(vide == 1) // il y a que des case vides entre les deux cases
        {
            tab[li][ci] = 0;
            tab[ld][cd] = 3;
        } else
        {
            printf("\n\n Ce coup n'est pas legal \n");
            return 0;
        }
    } else if(li > ld && ci > cd) //diagonale bas droite à haut gauche
    {
        for(i=1; i<li - ld; i++)
        {
            if (tab[li-i][ci-i] != 0)
            {
                vide = 0; // il y a une case pas vide
            }
        }
        if(vide == 1) // il y a que des case vides entre les deux cases
        {
            tab[li][ci] = 0;
            tab[ld][cd] = 3;
        } else
        {
            printf("\n\n Ce coup n'est pas legal \n");
            return 0;
        }
    } else if(li < ld && ci < cd) //diagonale haut gauche à bas droite
    {
        for(i=1; i<ld - li; i++)
        {
            if (tab[li+i][ci+i] != 0)
            {
                vide = 0; // il y a une case pas vide
            }
        }
        if(vide == 1) // il y a que des case vides entre les deux cases
        {
            tab[li][ci] = 0;
            tab[ld][cd] = 3;
        } else
        {
            printf("\n\n Ce coup n'est pas legal \n");
            return 0;
        }
    } else
    {
        printf("\n\n Ce coup n'est pas legal \n");
        return 0;
    }
    return 1; //le coup s'est effectué

}

int deplacementpion(int tab[][8], int li, int ci, int ld, int cd)
{

    if(cd == ci && ld==li-1 && tab[ld][cd]==0)
    {
        tab[li][ci] = 0;
        if(ld == 0) // si pion blanc atteint pion adverse en avancant alors il devient une reine
        {
            tab[ld][cd] = 10;
        } else // sinon il change pas
        {
            tab[ld][cd] = 1;
        }
    } else if (cd == ci && ld==li-2 && li == 6 && tab[ld][cd]==0 && tab[li-1][ci] == 0)
    {
        tab[li][ci] = 0;
        tab[ld][cd] = 1;
    } else if((cd == ci+1 || cd == ci-1) && ld==li-1 && tab[ld][cd]<0)
    {
        tab[li][ci] = 0;
        if(ld == 0)
        {
            tab[ld][cd] = 10;
        } else
        {
            tab[ld][cd] = 1;
        }

    } else
    {
        printf("\n\n Ce coup n'est pas legal \n");
        return 0;
    }
    return 1; //déplacement effectué
}



int checkpiece(int tab[][8], int li, int ci, int ld, int cd) //tour si = 0 blanc sinon noir
{
    int r;

    if(tab[li][ci] == 1) // la pièce choisi est un pion blanc
    {
        r = deplacementpion(tab, li, ci, ld, cd);

    } else if(tab[li][ci] == 1) // la pièce choisi est un pion noir
    {
        r = deplacementpion(tab, li, ci, ld, cd);

    } else if(tab[li][ci] == 3) // la pièce choisi est un fou
    {
        r = deplacementfou(tab, li, ci, ld, cd);

    } else if(tab[li][ci] == 4) // la pièce choisi est un cavalier
    {
        r = deplacementcavalier(tab, li, ci, ld, cd);

    } else if(tab[li][ci] == 5) // la pièce choisi est une tour
    {
        r = deplacementtour(tab, li, ci, ld, cd);

    } else if(tab[li][ci] == 10) // la pièce choisi est une reine
    {
        r = deplacementreine(tab, li, ci, ld, cd);

    } else if(tab[li][ci] == 19) // la pièce choisi est un roi
    {
        r = deplacementroi(tab, li, ci, ld, cd);
    }

    return r; //si r = 1, le déplacement s'est effectué, sinon non

}

//alternative equivalent game boucle si en echec
void tourjoueurechec(int tab[][8], int a) //le a sert pour l'altération de phrase et parce que pas besoin de verif echec et mat a chaque fois
{
    int tabdebase[8][8];
    int i, j, v, ve;

    for(i=0; i<8; i++)
    {
        for(j=0; j<8; j++)
        {
            tabdebase[i][j] = tab[i][j];
        }

    }

    affichageplateau(tabdebase);

    if (a == 0)
    {
        ve = verifechecetmat(tab);
        if(ve == 0)
        {
            return printf("\n\n Victoire des Noirs par echec et mat ! \n\n ");
        }
    }


    if(a == 0)
    {
        printf("\n\n Blanc en ECHEC \n\n");
    } else
    {
        printf("\n\n ATTENTION : Coup illegal des Blancs, vous seriez toujours en echec \n\n");
    }

    int li, //ligne de la case initial
        ci, //colonne de la case initial
        ld, //ligne de la case de destination
        cd; //colonne de la case de destination

    printf(" \n Choisissez ligne case : ");
    scanf("%d", &li);
    if (li > 7 || li < 0)
    {
        printf(" \n Cette ligne n'existe pas \n");
        tourjoueur(tab);
    } else
    {
        printf(" \n Choisissez colonne case : ");
        scanf("%d", &ci);
        if(ci > 7 || ci < 0)
        {
            printf(" \n Cette colonne n'existe pas\n");
            tourjoueur(tab);
        } else if(tab[li][ci]<1)
        {
            printf("\n Cette case ne vous appartient pas\n");
            tourjoueur(tab);
        } else
        {
            quelpiecechoisi(tab, li, ci);
            printf("\n Choississez ligne de destination : ");
            scanf("%d", &ld);
            if(ld > 7 || ld < 0)
            {
                printf(" \n Cette ligne n'existe pas\n");
                tourjoueur(tab);
            } else
            {
                printf(" \n Choisissez colonne de destination : ");
                scanf("%d", &cd);
                if(cd > 7 || cd < 0)
                {
                    printf(" \n Cette colonne n'existe pas\n");
                    tourjoueur(tab);
                } else if (tab[ld][cd] > 0 &&(tab[li][ci]!=19 && tab[ld][cd] != 5)&& ld == 7 && ld == li && cd == ci+3) //deuxieme condition laisse l'appelle de fonction vers le roi pour voir le roc
                {
                    printf("\n Vous avez deja une piece sur cette case\n");
                    tourjoueur(tab);
                } else
                {
                    checkpiece(tab, li, ci, ld, cd);
                }
            }
        }
    }

    v = verifechec(tab);
    if(v == 1)
    {
        return tourjoueurechec(tabdebase, 1); //le coup n'est pas validé, tjr en echec

    } else // le coup sort de l'echec donc il est validé et recopié dans le tableau de base
    {
        for(i=0; i<8; i++)
        {
            for(j=0; j<8; j++)
            {
                tabdebase[i][j] = tab[i][j];
            }
        }
        // adversaire
        if(choix == 1)
        {
            return tourIA(tab);
        } else
        {
            return tourjoueur2(tab); // adversaire
        }
    }

}

//equivalent game boucle
void tourjoueur(int tab[][8])
{
    int v, r, i, j;
    int tabdebase[8][8]; // pour garder une copie de la table avant le changement, là pour éviter de sauvegarder un potentiel echec soi même
    for(i=0; i<8; i++)
    {
        for(j=0; j<8; j++)
        {
            tabdebase[i][j] = tab[i][j];
        }

    }

    v = verifechec(tab);
    if(v == 1)
    {
        return tourjoueurechec(tab, 0);
    }
    affichageplateau(tab);

    printf(" \n--- Tour des Blancs ---\n");

    int li, //ligne de la case initial
        ci, //colonne de la case initial
        ld, //ligne de la case de destination
        cd; //colonne de la case de destination

    printf(" \n Choisissez ligne case : ");
    scanf("%d", &li);
    if (li > 7 || li < 0)
    {
        printf(" \n Cette ligne n'existe pas \n");
        tourjoueur(tab);
    } else
    {
        printf(" \n Choisissez colonne case : ");
        scanf("%d", &ci);
        if(ci > 7 || ci < 0)
        {
            printf(" \n Cette colonne n'existe pas\n");
            tourjoueur(tab);
        } else if(tab[li][ci]<1)
        {
            printf("\n Cette case ne vous appartient pas\n");
            tourjoueur(tab);
        } else
        {
            quelpiecechoisi(tab, li, ci);
            printf("\n Choississez ligne de destination : ");
            scanf("%d", &ld);
            if(ld > 7 || ld < 0)
            {
                printf(" \n Cette ligne n'existe pas\n");
                tourjoueur(tab);
            } else
            {
                printf(" \n Choisissez colonne de destination : ");
                scanf("%d", &cd);
                if(cd > 7 || cd < 0)
                {
                    printf(" \n Cette colonne n'existe pas\n");
                    tourjoueur(tab);
                } else if (tab[ld][cd] > 0 &&(tab[li][ci]!=19 && tab[ld][cd] != 5)&& ld == 7 && ld == li && cd == ci+3) //deuxieme condition laisse l'appelle de fonction vers le roi pour voir le roc
                {
                    printf("\n Vous avez deja une piece sur cette case\n");
                    tourjoueur(tab);
                } else
                {
                    r = checkpiece(tab, li, ci, ld, cd);
                }
            }
        }
    }

    if(r == 1) // le coup est validé
    {
        v = verifechec(tab);
        if(v == 1) // déplacement est validé mais on se mettrait en echec tout seul -> pas autorisé
        {
            printf("\n\n ATTENTION : Coup pas autorise car vous vous seriez mis tout seul en echec \n\n");
            return tourjoueur(tabdebase);
        } // sinon coup strictement validé, envoyer adversaire
        if(choix == 1)
        {
            return tourIA(tab);
        } else
        {
            return tourjoueur2(tab);
        }

    } else
    {
        return tourjoueur(tabdebase); //coup pas validé
    }
}

