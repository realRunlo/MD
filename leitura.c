/*
    Gonçalo Pereira & José Gomes
    funções de leitura
*/

#include "leitura.h"
#include <stdlib.h>
#include <string.h>
#include <pthread.h>




//ler o tamanho do bloco id e a sequencia de bits dos valores e guardar numa lista de blocos
void lerCodsSimbs(FILE* fp,char ** codigos,int *tamaho) {
    char bit, flag = 'R';
    char seq[16];
    int simb,i;


    fscanf(fp, "%d",tamaho); //lê tamanho do bloco
    fgetc(fp);//le o @ 

    for (simb = 0; flag != '@'; simb++) {
        bit = fgetc(fp);
        flag = bit;

        //está a ler bit a bit não há forma melhor
        if (bit != ';' && bit != '@') {
            for (bit, i = 0; bit != ';'; i++) {
                if (bit != ';')
                    seq[i] = bit;
                bit = fgetc(fp);
            }
            seq[i] = '\0';
            codigos[simb] = seq;
            printf("Simbolo %d : %s\n",simb,codigos[simb]);
        }
        


    }

}



//lê ficheiro .cod
void lerCod(char* filename) {
    //0 rle false,1 rle true
    int nBlocos,id;
    char tipo;
    int tamanho;
  
    FILE* fp;

    //inicia estrutura de sequência de códigos
    fp = fopen(filename, "r");

    fgetc(fp);
    fscanf(fp, "%c", &tipo); //guardar o tipo do ficheiro rle|n
    printf("%c\n", tipo);
    fgetc(fp);
    fscanf(fp, "%d", &nBlocos);//guardar num de blocos
    printf("%d\n", nBlocos);
    fgetc(fp);//le o @ 
    char **codigos = malloc(sizeof(char*)*nBlocos);

    for (id = 1; id <= nBlocos; id++) // lêr blocos a bloco
        lerCodsSimbs(fp,codigos[id],&tamanho);


    printf("oi");
    fclose(fp);
}

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






