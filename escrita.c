/*
    Gonçalo Pereira & José Gomes
    funções de orocessamento e escrita
*/
#include "leitura.h"
#include "escrita.h"
#include "logica.h"
#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>




/*
    Função leRle
    Recebe
    - nome do ficheiro rle
    - nome do ficheiro rle.freq
    Imprime no ficheiro TXT o conteúdo descomprimido do bloco.
*/

void processaRle(char* filenameRle, char* filenameFreq) {
    FILE* fpRLE;
    FILE* fpTXT;
    char* originalFilename = (char*)malloc(sizeof(char) * strlen(filenameRle) - 3);
    char* bloco;
    int nBlocos;
    int* tamanhos;


    editaNome(filenameRle, originalFilename);

    fpTXT = fopen(originalFilename, "w");

    tamanhos = lerFreq(filenameFreq, &nBlocos);          // Array com o número de blocos

    char** blocos = (char**)malloc(sizeof(char*) * nBlocos);
    for (int i = 0; i < nBlocos; i++) {
        blocos[i] = (char*)malloc(sizeof(char) * (tamanhos[i]));      //alocar espaço tamanho do bloco
    }

    pthread_t* thread = (pthread_t*)malloc(sizeof(pthread_t) * nBlocos);
    int* tamDescomp = (int*)malloc(sizeof(int)*nBlocos);


    for (int i = 0; i < nBlocos; i++) {
        argLB* arg = (argLB*)malloc(sizeof(argLB));
        arg->filename = filenameRle;
        arg->offset = calculaOffset(tamanhos, i);
        arg->bloco = blocos[i];
        arg->tamanho = tamanhos[i];
        arg->tamDescomp = &tamDescomp[i];
        pthread_create(&thread[i], NULL, (void*)leBloco, (void*)arg);
    }

    for(int i=0,rt;i<nBlocos;){
         rt = pthread_join(thread[i],NULL);
         if (rt == 0) {
             argDB* arg = (argDB*)malloc(sizeof(argDB));
             arg->filename = originalFilename;
             arg->offset = calculaOffset(tamDescomp, i);
             arg->bloco = blocos[i];
             arg->tamanho = tamanhos[i];
             pthread_create(&thread[i], NULL, (void*)descompBlocoRle, (void*)arg);
             i++;
         }
    }

    for (int i = 0, rt; i < nBlocos;) {
        rt = pthread_join(thread[i], NULL);
        if (rt == 0)
            i++;
    }

    // dar free a toda a memória alocada ???!?!?!?

    fclose(fpTXT);
}

void processaCod(char* filenameCod, char* filenameShaf) {
    FILE* fpRLE;
    FILE* fpTXT;
    char* originalFilename = (char*)malloc(sizeof(char) * strlen(filenameCod) - 3);
    char* bloco;
    int nBlocos;
    int* tamanhos;


    editaNome(filenameCod, originalFilename);

    fpTXT = fopen(originalFilename, "w");

    tamanhos = lerCodFile(filenameCod, &nBlocos);          // Array com o número de blocos

    int** codigos = (int**)malloc(sizeof(int*) * nBlocos);
    int matrix[2][256];
    for (int i = 0; i < nBlocos; i++) {
        codigos[i] = (int*)malloc(sizeof(int) * 256);      //alocar espaço para os 256 codigos
    }

    lerCodigos(filenameCod, codigos, tamanhos);

    tamanhos = lerFreq(filenameShaf, &nBlocos);

    descodShaf(filenameShaf, codigos, tamanhos);

    //leBlocoCod(filenameCod,11);

    fclose(fpTXT);
}

void descodShaf(char * filename, int **codigos, int *tamanhos) {
    FILE* fpSHAF = fopen(filename, "rb");
    FILE* fpTXT = fopen("aaa.txt", "w");
    char letra, nreps;
    char* bloco = (char*)malloc(sizeof(char) * tamanhos[0]);

    fread(bloco, sizeof(char), tamanhos[0], fpSHAF);

    char* binBloco = (char*)malloc(sizeof(char) * tamanhos[0] * 8);
    
    blocoToBin(bloco, binBloco, tamanhos); // mudar para struct que acede aos bits

}


// mudar para struct que acede aos bits
void blocoToBin(char* bloco, char* binBloco, int * tamanhos) {
    int n = 0;
    for (int i = 0; i < tamanhos[0]; i++) {
        char * c = fromASCIItoBin(bloco[i], binBloco); 
        for (int j = 0; j < 8; j++) {
            binBloco[n++] = c[j];
        }
    }
}

void lerCodigos(char* filenameCod, int** codigos, int* tamanhos) {
    char bit, flag = 'R';
    char seq[16];
    int codPosicao=0, codTamanho = 0, i, counter = 0;
    FILE* fpCOD = fopen(filenameCod, "r");
    for (int i = 0; i < 4;) {
        if (fgetc(fpCOD) == '@') i++;
    }

    for (int i = 0; i < 256;) {
        bit = getc(fpCOD);
        printf("%c\n", bit);
        if (bit == ';' || bit == '@'){
            if (codTamanho != 0) {
                printf("%d no spot %d\n", binToInt(seq, codTamanho), codPosicao);
                codigos[0][binToInt(seq, codTamanho)] = codPosicao;
                codTamanho = 0;
            }
            i++;
            codPosicao++;
        }
        else {
            seq[codTamanho++] = bit;
        }
    }
}




int* lerCodFile(char* filenameCod, int * nBlocos) {
    char tipo, c = 'R';
    int i = 0;
    FILE* fpCod;

    fpCod = fopen(filenameCod, "r");

    fgetc(fpCod);                              //le o @ 
    fscanf(fpCod, "%c", &tipo);                  //guardar o tipo do ficheiro rle|n
    fgetc(fpCod);                              //le o @ 
    fscanf(fpCod, "%d", nBlocos);                //guardar num de blocos
    fgetc(fpCod);                              //le o @ 

    int* tamanhos = (int*)malloc(sizeof(int) * (*nBlocos));

    do {
        fscanf(fpCod, "%d", &tamanhos[i]);
        fgetc(fpCod);
        while (c != '@') {
            c = fgetc(fpCod);
        }
        c = 'R';
        i++;
    } while (i < *nBlocos);

    fclose(fpCod);
    return tamanhos;
}

/*
    Função mensagemFim
    Recebe
    - tempo de execução
    - array com os tamanhos antes
    - array com tamanhos depois descompressão
    - número de blocos
    Imprime na consola mensagem no fim de execução do modulo
*/
void mensagemFim(int tempo,int *tamanhos,int* tamDescomp,int nBlocos){
    printf("====================SUCESSO====================\n");
    printf("Gonçalo Pereira & José Gomes,a93168,  , MIEI/CD\n");
    printf("Modulo: D (descodificação)\n");
    printf("Número de blocos: %d\n",nBlocos);
    for(int i=0;i<nBlocos;i++){
        printf("Tamanho antes/depois do ficheiro gerado (bloco %d): %d/%d\n",i+1,tamanhos[i],tamDescomp[i]);
    }
    printf("Tempo de execução do modulo (milissegundos): %d\n",tempo);
    printf("Ficheiro gerado: %s");



}