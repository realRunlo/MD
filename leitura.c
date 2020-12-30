/*
    Gonçalo Pereira & José Gomes
    funções de leitura
*/

#include "leitura.h"
#include <stdlib.h>
#include <string.h>
#include <pthread.h>



/*
    Função lerFreq
    Recebe
    - Apontador para o ficheiro de frequências .freq
    - Número de blocos no ficheiro.
    Devolve
    - Array com os tamanhos dos blocos em bytes
*/
int* lerFreq(char* filenameFREQ, int* nBlocos) {
    char tipo, c = 'R';
    int i = 0;
    FILE* fpFREQ;

    fpFREQ = fopen(filenameFREQ, "r");

    fgetc(fpFREQ);                              //le o @ 
    fscanf(fpFREQ, "%c", &tipo);                  //guardar o tipo do ficheiro rle|n
    fgetc(fpFREQ);                              //le o @ 
    fscanf(fpFREQ, "%d", nBlocos);                //guardar num de blocos
    fgetc(fpFREQ);                              //le o @ 

    int* tamanhos = (int*)malloc(sizeof(int) * (*nBlocos));

    do {
        fscanf(fpFREQ, "%d", &tamanhos[i]);
        fgetc(fpFREQ);
        while (c != '@') {
            c = fgetc(fpFREQ);
        }
        c = 'R';
        i++;
    } while (i < *nBlocos);

    fclose(fpFREQ);
    return tamanhos;
}



/*
    Função leBloco
    Recebe
    - Apontador para estrtura de argumentos
    Lê bloco de bytes 

*/
void leBloco(argLB* arg) {
    FILE* fp;
    fp = fopen(arg->filename, "rb");
    fseek(fp, arg->offset, 0);                                      //aponta para o bloco a ler

    fread(arg->bloco, sizeof(char), (arg->tamanho), fp);            // Leitura do bloco

    char nreps;
    int tamDescomp=0;
        for (int i = 0; i < arg->tamanho; i++) {
        if (arg->bloco[i] != 0)                         // Se não for o inicio de uma sequencia
            tamDescomp++;
        else {
            i++;                                        // Letra a ser repetida
            nreps = arg->bloco[++i];                    // Número de repetições
            tamDescomp += nreps;
        }
    }
    *(arg->tamDescomp) = tamDescomp;
    
}


void lerCodNblocos(char* filenameCod, int * nBlocos) {
    FILE* fpCod;

    fpCod = fopen(filenameCod, "r");

    fgetc(fpCod);                              //le o @ 
    fgetc(fpCod);                 //guardar o tipo do ficheiro rle|n
    fgetc(fpCod);                              //le o @ 
    fscanf(fpCod, "%d", nBlocos);                //guardar num de blocos 
}

void lerCodigos(char* filenameCod, int** codigos, int* tamanhos) {
    char c = 'R', tipo;
    char seq[16];
    int nBlocos,codPosicao=0, codTamanho = 0, i=0, counter = 0;
    FILE* fpCOD = fopen(filenameCod, "r");

    fgetc(fpCOD);                              //le o @ 
    fscanf(fpCOD, "%c", &tipo);                  //guardar o tipo do ficheiro rle|n
    fgetc(fpCOD);                              //le o @ 
    fscanf(fpCOD, "%d",&nBlocos);                //guardar num de blocos
    fgetc(fpCOD);                              //le o @ 

    do {
        fscanf(fpCOD, "%d", &tamanhos[i]);
        fgetc(fpCOD);                           //le o @ 
        while (c != '@') {
            c = fgetc(fpCOD);
            if (c == ';' || c == '@'){
                if (codTamanho != 0) {
                    codigos[i][binToInt(seq, codTamanho)] = codPosicao;
                    codTamanho = 0;
                }
                codPosicao++;
            }
            else {
                 seq[codTamanho++] = c;
            }
            
        }
        c = 'R';
        i++;
        codPosicao=0;
    } while (i < nBlocos);
   
}
void lerOffsetsShaf(char* filenameShaf,int **tam){

}
char **lerShaf(char* filenameShaf,int *tamanhosShaf) {
    int nBlocos,i=0;
    char c;
    FILE * fp = fopen(filenameShaf,"r");
    fgetc(fp);              //le @
    fscanf(fp,"%d",&nBlocos);   //le numero de blocos
    fgetc(fp);              //le @

    char **blocos = (char**)malloc(sizeof(char) * (nBlocos));

    do{
        fscanf(fp,"%d",&tamanhosShaf[i]); 
        fgetc(fp);              //le @ 
        blocos[i] = (char*)malloc(sizeof(char)*(tamanhosShaf[i]));
        fread(blocos[i],sizeof(char),tamanhosShaf[i],fp);
        getc(fp);
        
        i++;
    }while(i<nBlocos);
    
    return blocos;
}






