/*
    Gonçalo Pereira & José Gomes
    funções utilitárias e de descodificação/descompressão
*/
#include "leitura.h"
#include "escrita.h"
#include <string.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

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

void cortaSufixo(char *filename,char * nFilename,int nCorte){
    int N,i;
    for(N=0;filename[N]!='\0';N++);

    for(i=0;i<=N-nCorte;i++){
        nFilename[i] = filename[i];
    }
    nFilename[i] = '\0';
    
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

void descodShaf(argDS * arg) {
 
    FILE* fpTXT = fopen(arg->filename,"w");  
    
    fseek(fpTXT, arg->offset, 0);
    int codigo = 0, c = 0;
    for (int i = 0; i < arg->tamanho; i++){
        char simbolo;
        acederB  caracter; 
        caracter.byte = arg->bloco[i];
        codigo = 2 * codigo + caracter.u.bit8;
        simbolo = arg->codigos[codigo];
        if(simbolo!=-1){
            fprintf(fpTXT,"%c",simbolo);
            codigo = 0;
            if (++c == arg->tamanhoDescod) break;
        }
        codigo = 2 * codigo + caracter.u.bit7;
        simbolo = arg->codigos[codigo];
        if(simbolo!=-1){
            fprintf(fpTXT,"%c",simbolo);
            codigo = 0;
            if (++c == arg->tamanhoDescod) break;
        }
        codigo = 2 * codigo + caracter.u.bit6;
        simbolo = arg->codigos[codigo];
        if(simbolo!=-1){
            fprintf(fpTXT,"%c",simbolo);
            codigo = 0;
            if (++c == arg->tamanhoDescod) break;
        }
        codigo = 2 * codigo + caracter.u.bit5;
        simbolo = arg->codigos[codigo];
        if(simbolo!=-1){
            fprintf(fpTXT,"%c",simbolo);
            codigo = 0;
            if (++c == arg->tamanhoDescod) break;
        }
        codigo = 2 * codigo + caracter.u.bit4;
        simbolo = arg->codigos[codigo];
        if(simbolo!=-1){
            fprintf(fpTXT,"%c",simbolo);
            codigo = 0;
            if (++c == arg->tamanhoDescod) break;
        }
        codigo = 2 * codigo + caracter.u.bit3;
        simbolo = arg->codigos[codigo];
        if(simbolo!=-1){
            fprintf(fpTXT,"%c",simbolo);
            codigo = 0;
            if (++c == arg->tamanhoDescod) break;
        }
        codigo = 2 * codigo + caracter.u.bit2;
        simbolo = arg->codigos[codigo];
        if(simbolo!=-1){
            fprintf(fpTXT,"%c",simbolo);
            codigo = 0;
            if (++c == arg->tamanhoDescod) break;
        }
        codigo = 2 * codigo + caracter.u.bit1;
        simbolo = arg->codigos[codigo];
        if(simbolo!=-1){
            fprintf(fpTXT,"%c",simbolo);
            codigo = 0;
            if (++c == arg->tamanhoDescod) break;
        }    
        
    }
    
   // blocoToBin(bloco, binBloco, tamanhos); // mudar para struct que acede aos bits
}


int binToInt(char* seq, int tamanho) {
    int decimal = 0;
    for (int i = 0; i < tamanho; i++) {
        if (seq[tamanho - i - 1] == '1') {
            decimal += pow(2, i);
        }
    }
    return decimal;
}

// mudar para struct que acede aos bits
/*
void blocoToBin(char* bloco, char* binBloco, int * tamanhos) {
    int n = 0;
    for (int i = 0; i < tamanhos[0]; i++) {
        char * c = fromASCIItoBin(bloco[i], binBloco); 
        for (int j = 0; j < 8; j++) {
            binBloco[n++] = c[j];
        }
    }
}*/

//esta execução só aplica processaShaf e processaRle ou seja o ficheiro resultante é original
void exeNormal(char *filenameShaf){
    char *filenameCod = (char*)malloc(sizeof(char) * strlen(filenameShaf) - 1 );
    char tipo,cod[5] = ".cod\0";
    char* filenameNR;

    cortaSufixo(filenameShaf,filenameCod,6);   //cortar sufixo .shaf\0

    printf("Shaf cortado: %s\n",filenameCod);
    
    
    strcat(filenameCod,cod);                    //adiciona .cod\0

    printf("Ficheiro .cod :%s\n",filenameCod);               
    
    filenameNR = processaShaf(filenameCod,filenameShaf,&tipo);  //ou escreve o original ou vai escrver um rle,dava jeito ser returnado onde escrveu

    printf("Shaf processado,ficheiro gerado=> %s\n",filenameNR);  //o ficheiro resultante do processa shaf

    if (tipo =='R'){
        processaRle(filenameNR,filenameCod);   
        printf("Descompressao rle aplicada\n");       
    }

}

//esta execução só aplica processaShaf ou seja o que é gerado ou é original ou um rle
void exeS(char *filenameShaf){
    char *filenameCod = (char*)malloc(sizeof(char) * strlen(filenameShaf) - 1 );
    char tipo,cod[5] = ".cod\0";
    char* filenameNR;

    cortaSufixo(filenameShaf,filenameCod,6);   //cortar sufixo .shaf\0

    printf("Shaf cortado: %s\n",filenameCod);
    
    
    strcat(filenameCod,cod);                    //adiciona .cod\0

    printf("Ficheiro .cod :%s\n",filenameCod);               
    
    filenameNR = processaShaf(filenameCod,filenameShaf,&tipo);  //ou escreve o original ou vai escrver um rle,dava jeito ser returnado onde escrveu

    printf("Shaf processado,ficheiro gerado=> %s\n",filenameNR);  //o ficheiro resultante do processa shaf

}

void exeR(char *filenameRle){
    char *filenameFreq = (char*)malloc(sizeof(char) * strlen(filenameRle) + 4 );
    char tipo,freq[6] = ".freq\0";
    int i;
  
    for(i=0;filenameRle[i]!='\0';i++)
            filenameFreq[i] = filenameRle[i];
    filenameFreq[i] = '\0';

    strcat(filenameFreq,freq);   //adiciona sufixo .freq

    processaRle(filenameRle,filenameFreq);

}

