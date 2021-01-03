/*
    Gonçalo Pereira & José Gomes
    funções utilitárias e de descodificação/descompressão
*/

#ifndef ___logica_h___
#define ___logica_h___
#include <stdio.h>
#include <stdlib.h>

typedef struct printMessage {
    char* ficheiroRLE;
    char* ficheiroSHAF;
    int timer;
    int nBlocos;
    int* tamRLE;
    int* tamSHAF;
    int* tamDescompRLE;
    int* tamDescompSHAF;
    
}pMessage;

extern pMessage mensagem;

typedef struct codeArray {
    int simbolo;
    int tamanho;
}cArray;

typedef struct argDescompBloco {

    char* filename;
    int offset;
    char* bloco;
    int tamanho;

}argDB;

typedef struct argLeBloco {

    char* filename;
    int offset;
    char* bloco;
    int tamanho;
    int *tamDescomp;

}argLB;

typedef struct argDescodSahf{
    char *filename;
    char * bloco;
    int tamanho;
    int tamanhoDescod;
    int offset;
    cArray * codigos;
    char tipo;
}argDS;

typedef union
{
  struct
  {
    unsigned char bit1 : 1;
    unsigned char bit2 : 1;
    unsigned char bit3 : 1;
    unsigned char bit4 : 1;
    unsigned char bit5 : 1;
    unsigned char bit6 : 1;
    unsigned char bit7 : 1;
    unsigned char bit8 : 1;
  }u;
  unsigned char byte;
}acederB;

void cortaSufixo(char *filename,char * nFilename,int nCorte);
int calculaOffset(int* tamanhos, int i);
int binToInt(char* seq, int tamanho);
void descompBlocoRle(argDB* arg);
void descodShaf(argDS * arg);
void exeNormal(char *filenameShaf);
void exeS(char *filenameShaf);
void exeR(char *filenameRle);
int get_maxBits (int *symbols, FILE *fp_cod );



#endif // ___logica_h___