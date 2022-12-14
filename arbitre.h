#ifndef ARBITRE_H_INCLUDED
#define ARBITRE_H_INCLUDED

//affichage
void recopietab(int tab[][8], int copietab[][8]);
void affichageplateau(int tab[][8]);
void aide();

int roc_ok_ou_pas(int n);
int roisapproche(int tab[][8], int tour, int ld, int cd);

int verifpionechec(int tab[][8], int n, int m);
int verifcavalierechec(int tab[][8], int n, int m);
int veriftourechec(int tab[][8], int n, int m);
int veriffouechec(int tab[][8], int n, int m);
int verifreineechec(int tab[][8], int i, int j);
int verifechec(int tab[][8]);

int verifpionechecnoir(int tab[][8], int n, int m);
int verifcavalierechecnoir(int tab[][8], int n, int m);
int veriftourechecnoir(int tab[][8], int n, int m);
int veriffouechecnoir(int tab[][8], int n, int m);
int verifreineechecnoir(int tab[][8], int i, int j);
int verifechecnoir(int tab[][8]);



#endif // ARBITRE_H_INCLUDED
