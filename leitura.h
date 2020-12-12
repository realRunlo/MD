#include<stdio.h>
#include "dados.h"

#ifndef ___leitura_h___
#define ___leitura_h___

typedef struct argLeBloco{
    
    char * filename;
    int Offset;
    char * bloco;
    int tamanho;

}argLB;

BLOCOS* lerCodsSimbs(FILE *fp,BLOCOS * bL ,int id);
BLOCOS * lerCod(char *filename);
void lerRle(char* filename);
void editaNome(char * filename,char * nfile);
//lê o necessário de um ficgeiro freq
int *lerFreq(char *filename,int *nBlocos);
//lê um bloco binário dado um tamanho N
void leBloco(argLB *arg);
void descompBlocoRle(FILE *fp,char *bloco,int  tamanho);
void fRle(char * filename,char * filenameFreq);
int calculaOffset(int *tamanhos,int i);



#endif // ___leitura_h___