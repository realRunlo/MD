/*
    Gonçalo Pereira & José Gomes
    funções utilitárias e de descodificação/descompressão
*/

#ifndef ___logica_h___
#define ___logica_h___

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
    int * codigos;
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

void editaNome(char* filename, char* nFilename);
int calculaOffset(int* tamanhos, int i);
int binToInt(char* seq, int tamanho);
void descompBlocoRle(argDB* arg);
//void blocoToBin(char* bloco, char* binBloco, int * tamanhos);
void descodShaf(char * filename, int **codigos, int *tamanhos);


#endif // ___logica_h___