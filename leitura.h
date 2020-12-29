/*
    Gonçalo Pereira & José Gomes
    funções de leitura
*/
#include "logica.h"
#include <stdio.h>

#ifndef ___leitura_h___
#define ___leitura_h___
/* 
    estretura para passagem de argumentos para multi threading na leitura paralela
*/


//lê o necessário de um ficgeiro freq
int* lerFreq(char* filename, int* nBlocos);
//lê um bloco binário dado um tamanho N
void leBloco(argLB* arg);
void lerCodNblocos(char* filenameCod, int * nBlocos);
void lerCodigos(char* filenameCod, int** codigos, int* tamanhos);
char **lerShaf(char* filenameShaf,int *tamanhosShaf,char **blocos);



#endif // ___leitura_h___