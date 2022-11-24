#ifndef ECHECMAT_H_INCLUDED
#define ECHECMAT_H_INCLUDED

int sortieecheccavalier(int tab[][8], int copietab[][8], int n, int m);
int sortieechecreine(int tab[][8], int copietab[][8], int i, int j);
int sortieechectour(int tab[][8], int copietab[][8], int i, int j);
int sortieechecfou(int tab[][8], int copietab[][8], int i, int j);
int sortieechecpion(int tab[][8], int copietab[][8], int i, int j);
int sortieechecroi(int tab[][8], int copietab[][8], int i, int j);

int verifechecetmat(int tab[][8]);

#endif // ECHECMAT_H_INCLUDED
