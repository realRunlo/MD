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
    Função cortaSufixo
    Recebe
    - um apontador para uma string origem
    - um apontador para uma string destino
    - número de caracteres a cortar da string origem do fim para o inicio
    Corta a string origem e guarda a nova string na string destino
*/
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
 
     FILE * fpTXT;
    if((arg->tipo)=='N'){
        fpTXT = fopen(arg->filename, "w");
    }else
    {
        printf("Escrita binária\n");
        fpTXT = fopen(arg->filename, "wb");
    }
    
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


int get_maxBits (int *symbols, FILE *fp_cod ){
    int maxBits = 0, id_bits = 0, symbol = 0, block_not_over = 1; //true
    char c, c_ant = '@';
    while (block_not_over) { // Enquanto o bloco não acabar.
        c = fgetc(fp_cod);
        if (c == ';' || c == '@') {
            if (c_ant == '0' || c_ant == '1'){
                // Leu um código para aquele símbolo.
                symbols[symbol] = 1; //true.
                if(maxBits < id_bits) maxBits = id_bits; // Encontrou um código com o maior número de bits até agora.
                }
                // Não leu um código para aquele símbolo.
                else symbols[symbol] = 0; //false.
                if (c == '@') block_not_over = 0; //false.
                // O Bloco terminou
                else {
                    // O Bloco não terminou, logo adiciona 1 ao índice de simbolos e reseta o índice de bits.
                    symbol++;
                    id_bits = 0;
                }
            }
        if (c == '0' || c == '1') id_bits++; //Adiciona 1 ao índice de bits.
        c_ant = c;
    }
    return maxBits; // Retorna o maior número de bits encontrado. 
}

