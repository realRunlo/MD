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
    char* originalFilename = (char*)malloc(sizeof(char) * strlen(filenameRle) - 3);
    char* bloco;
    int nBlocos;
    int* tamanhos;


    editaNome(filenameRle, originalFilename);


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

}

void processaCod(char* filenameCod, char* filenameShaf) {
    FILE* fpRLE;
    FILE* fpTXT;
    char* originalFilename = (char*)malloc(sizeof(char) * strlen(filenameCod) - 3);
    char ** blocos;
    int nBlocos;
    int* tamanhosCod;
    int* tamanhosShaf;
    


    editaNome(filenameCod, originalFilename);

    fpTXT = fopen(originalFilename, "w");

    lerCodNblocos(filenameCod, &nBlocos);          // ler numero de blocos

    int** codigos = (int**)malloc(sizeof(int*) * nBlocos);

    for (int i = 0; i < nBlocos; i++) {
        codigos[i] = (int*)malloc(sizeof(int) * 256);      //alocar espaço para os 256 codigos
    }
    for(int i=0;i<nBlocos;i++){
        for(int j=0;j<256;j++){
            codigos[i][j] = -1;
        }
    }

    lerCodigos(filenameCod, codigos, tamanhosCod);

    blocos = lerShaf(filenameShaf,tamanhosShaf,blocos);  
    /*argDS *arg;
    arg->filename = originalFilename;
    arg->offset = calculaOffset(tamDescomp, i);
    arg->bloco = blocos[i];
     arg->tamanho = tamanhos[i];

    descodShaf();

    //leBlocoCod(filenameCod,11);
*/
    fclose(fpTXT);
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