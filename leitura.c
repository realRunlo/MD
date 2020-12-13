#include "leitura.h"
#include <string.h>
#include <pthread.h>



//ler o tamanho do bloco id e a sequencia de bits dos valores e guardar numa lista de blocos
BLOCOS* lerCodsSimbs(FILE* fp, BLOCOS* bL, int id) {
    char bit, flag = 'R';
    BLOCOS* b;
    SEQBINL* l = NULL;
    char seq[16];
    char* seqL;
    int simb, tam, i;


    fscanf(fp, "%d", &tam); //lê tamanho do bloco
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
            seqL = seq;
            l = addSeqL(simb, seqL, l);
        }


    }


    b = addBloco(id, tam, l, bL);


    return b;
}



//lê ficheiro .cod
BLOCOS* lerCod(char* filename) {
    //0 rle false,1 rle true
    int nBlocos, tam, i;
    char tipo;
    BLOCOS* pBlocos;
    FILE* fp;

    //inicia uma estrutua de blocos
    pBlocos = initBlocos();

    //inicia estrutura de sequência de códigos
    fp = fopen(filename, "r");

    fgetc(fp);
    fscanf(fp, "%c", &tipo); //guardar o tipo do ficheiro rle|n
    printf("%c\n", tipo);
    fgetc(fp);
    fscanf(fp, "%d", &nBlocos);//guardar num de blocos
    printf("%d\n", nBlocos);
    fgetc(fp);//le o @ 

    for (i = 1; i <= nBlocos; i++) // lêr blocos a bloco
        pBlocos = lerCodsSimbs(fp, pBlocos, i);

    fclose(fp);

    return pBlocos;

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

/*
    Função descompBlocoRle
    Recebe
    - Apontador para o ficheiro TXT
    - String com o conteúdo do bloco a descomprimir
    - Tamanho do bloco em Bytes
    Imprime no ficheiro TXT o conteúdo descomprimido do bloco.
*/
//void descompBlocoRle(FILE* fpTXT, char* bloco, int tamanho) {
void descompBlocoRle(argDB* arg){
    FILE* fpTXT = fopen(arg->filename, "w");
    fseek(fpTXT, arg->offset, 0);
    char letra, nreps;
    for (int i = 0; i < arg->tamanho; i++) {
        if (arg->bloco[i] != 0)                         // Se não for o inicio de uma sequencia
            fprintf(fpTXT, "%c", arg->bloco[i]);       // Impressão da letra
        else {
            letra = arg->bloco[++i];                 // Letra a ser repetida
            nreps = arg->bloco[++i];                 // Número de repetições

            for (int c = 0; c < nreps; c++) {
                fprintf(fpTXT, "%c", letra);        // Impressão da sequência
            }
        }
    }
}

/*
    Função leRle
    Recebe
    - nome do ficheiro rle
    - nome do ficheiro rle.freq
    Imprime no ficheiro TXT o conteúdo descomprimido do bloco.
*/

void leRle(char* filenameRle, char* filenameFreq) {
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
    fclose(fpTXT);
}

/*
    Função editaNome
    Recebe
    - String com de um ficheiro codificado .cod/.rle
    - Apontador onde vai ser guardado o nome do ficheiro original (.txt)
    Corta o .cod/.rle do nome do ficheiro
*/
void editaNome(char* filename, char* nFilename) {
    int flag = 0;

    for (int i = 0; flag < 2; i++) {

        if (filename[i] == '.')flag++;

        if (flag < 2) {
            nFilename[i] = filename[i];
        }
        else
            nFilename[i] = '\0';
    }
}

/*
    Função calculaOffset
    Recebe
    - apontador para array que contêm os tamanhos dos vários blocos
    - indice do bloco atual
    Calcula a soma dos tamanhos até o bloco de indice i
*/
int calculaOffset(int* tamanhos, int i) {
    int offSet = 0;
    for (int j = 0; j < i; j++) {
        offSet += tamanhos[j];
    }
    return offSet;
}

