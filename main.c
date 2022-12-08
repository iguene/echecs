#include <stdio.h>
#include <stdlib.h>
#include "joueur.h"
#include "adversaire.h"
#include "arbitre.h"
#include "echecmat.h"
#include "joueur2.h"
#include "echecetmatjoueur2.h"


int main()
{
    /*
    int echiquier[8][8]={{-5,-4,-3,-10,-19,-3,-4,-5},
                         {-1,-1,-1,-1  ,-1 ,-1,-1,-1},
                         { 0, 0, 0, 0  ,0 , 0, 0 , 0},
                         { 0, 0, 0, 0  ,0 , 0, 0 , 0},
                         { 0, 0, 0, 0  ,0 , 0, 0 , 0},
                         { 0, 0, 0, 0  ,0 , 0, 0 , 0},
                         { 1, 1, 1, 1  ,1 , 1, 1, 1},
                         { 5, 4, 3, 10 ,19, 3, 4, 5}};

    aide();

    queladversaire();

    tourjoueur(echiquier);
    */

    int echiquier[8][8]={{ 0, 0, 0, 0,  0,  0,  0 , 0},
                         { 0, 0, 0, 0,  0,  0,  0 , 0},
                         { 0, 0, 0, 0  ,0 , 0, 0 , 0},
                         { 0, 0, 0, 0  ,0 , 0, 0 , 0},
                         { 0, 0, 0, 0  ,0 , 0, 0 , 0},
                         { 0, 0, 0, 0  ,0 , 0, 0 , 0},
                         { 0, 1, 0, 0  ,1 , 0, 0, 0},
                         { 0, 0, 0, 0,  0,  0,  0 , 0}};

    tourIA(echiquier);



    return 0;
}
