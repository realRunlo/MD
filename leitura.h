/*
    Gonçalo Pereira & José Gomes
    funções de leitura
*/

#include <stdio.h>

#ifndef ___leitura_h___
#define ___leitura_h___



typedef struct argLeBloco {

    char* filename;
    int offset;
    char* bloco;
    int tamanho;
    int *tamDescomp;

}argLB;

typedef struct argDescompBloco {

    char* filename;
    int offset;
    char* bloco;
    int tamanho;

}argDB;

void lerCodsSimbs(FILE* fp, char ** codigos,int *tamaho);
void lerCod(char* filename);
void editaNome(char* filename, char* nfile);
//lê o necessário de um ficgeiro freq
int* lerFreq(char* filename, int* nBlocos);
//lê um bloco binário dado um tamanho N
void leBloco(argLB* arg);
void descompBlocoRle(argDB* arg);
int calculaOffset(int* tamanhos, int i);



#endif // ___leitura_h___