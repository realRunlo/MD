/*
    Gonçalo Pereira & José Gomes
    funções utilitárias e de descodificação/descompressão
*/
#include "leitura.h"
#include "escrita.h"
#include "logica.h"
#include <string.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

pMessage mensagem;

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
    - Estrutura argDescompBloco
    Imprime no ficheiro TXT o conteúdo descomprimido de um bloco.
*/
void descompBlocoRle(argDB* arg){
    
    FILE* fpTXT = fopen(arg->filename, "w");
    if (arg->offset != 0) {
        fseek(fpTXT, arg->offset, 0);
    }
    char letra, nreps;

    for (int i = 0; i < arg->tamanho; i++) {
        if (arg->bloco[i] != 0) {                      // Se não for o inicio de uma sequencia
            fprintf(fpTXT, "%c", arg->bloco[i]);       // Impressão da letra
        }
        else {
            letra = arg->bloco[++i];                 // Letra a ser repetida
            nreps = arg->bloco[++i];                 // Número de repetições
            for (int c = 0; c < nreps; c++) {
                fprintf(fpTXT, "%c", letra);        // Impressão da sequência
            }
        }
    }
    fclose(fpTXT);
    free(arg->bloco);
    free(arg);
}

/*
    Função descodShaf
    Recebe
    - Estrutura argDescodBloco
    Imprime no ficheiro TXT o conteúdo descodificado de um bloco.
*/

void descodShaf(argDS * arg) {
     FILE * fpTXT;
    if((arg->tipo)=='N'){
        fpTXT = fopen(arg->filename, "w");
    }else
    {
        fpTXT = fopen(arg->filename, "wb");
    }
    
    fseek(fpTXT, arg->offset, 0);
    int codigo = 0, c = 0, bitcounter = 0;
    for (int i = 0; i < arg->tamanho; i++){
        char simbolo = -1;
        acederB  caracter; 
        cArray elemento;
        caracter.byte = arg->bloco[i];

        codigo = 2 * codigo + caracter.u.bit8;
        bitcounter++;
        elemento = arg->codigos[codigo];
        simbolo = elemento.simbolo;
        if(simbolo!=-1 && elemento.tamanho == bitcounter){
            fprintf(fpTXT,"%c",simbolo);
            codigo = 0;
            bitcounter = 0;
            if (++c == arg->tamanhoDescod) break;
        }
        codigo = 2 * codigo + caracter.u.bit7;
        bitcounter++;
        elemento = arg->codigos[codigo];
        simbolo = elemento.simbolo;
        if(simbolo!=-1 && elemento.tamanho == bitcounter){
            fprintf(fpTXT,"%c",simbolo);
            codigo = 0;
            bitcounter = 0;
            if (++c == arg->tamanhoDescod) break;
        }
        codigo = 2 * codigo + caracter.u.bit6;
        bitcounter++;
        elemento = arg->codigos[codigo];
        simbolo = elemento.simbolo;
        if(simbolo!=-1 && elemento.tamanho == bitcounter){
            fprintf(fpTXT,"%c",simbolo);
            codigo = 0;
            bitcounter = 0;
            if (++c == arg->tamanhoDescod) break;
        }
        codigo = 2 * codigo + caracter.u.bit5;
        bitcounter++;
        elemento = arg->codigos[codigo];
        simbolo = elemento.simbolo;
        if(simbolo!=-1 && elemento.tamanho == bitcounter){
            fprintf(fpTXT,"%c",simbolo);
            codigo = 0;
            bitcounter = 0;
            if (++c == arg->tamanhoDescod) break;
        }
        codigo = 2 * codigo + caracter.u.bit4;
        bitcounter++;
        elemento = arg->codigos[codigo];
        simbolo = elemento.simbolo;
        if(simbolo!=-1 && elemento.tamanho == bitcounter){
            fprintf(fpTXT,"%c",simbolo);
            codigo = 0;
            bitcounter = 0;
            if (++c == arg->tamanhoDescod) break;
        }
        codigo = 2 * codigo + caracter.u.bit3;
        bitcounter++;
        elemento = arg->codigos[codigo];
        simbolo = elemento.simbolo;
        if(simbolo!=-1 && elemento.tamanho == bitcounter){
            fprintf(fpTXT,"%c",simbolo);
            codigo = 0;
            bitcounter = 0;
            if (++c == arg->tamanhoDescod) break;
        }
        codigo = 2 * codigo + caracter.u.bit2;
        bitcounter++;
        elemento = arg->codigos[codigo];
        simbolo = elemento.simbolo;
        if(simbolo!=-1 && elemento.tamanho == bitcounter){
            fprintf(fpTXT,"%c",simbolo);
            codigo = 0;
            bitcounter = 0;
            if (++c == arg->tamanhoDescod) break;
        }
        codigo = 2 * codigo + caracter.u.bit1;
        bitcounter++;
        elemento = arg->codigos[codigo];
        simbolo = elemento.simbolo;
        if(simbolo!=-1 && elemento.tamanho == bitcounter){
            fprintf(fpTXT,"%c",simbolo);
            codigo = 0;
            bitcounter = 0;
            if (++c == arg->tamanhoDescod) break;
        }        
    }
    fclose(fpTXT);

    free(arg->bloco);
    free(arg->codigos);
    free(arg);
}

/*
    Função binToInt
    Recebe
    - String seq, sequência de bits a traduzir para decimal
    - Tamanho da sequência de bits.
    Devolve a tradução decimal de uma sequência de bits.
*/

int binToInt(char* seq, int tamanho) {
    int decimal = 0;
    for (int i = 0; i < tamanho; i++) {
        if (seq[tamanho - i - 1] == '1') {
            decimal += pow(2, i);
        }
    }
    return decimal;
}

/*
    Função exeNormal
    Recebe
    - Nome de um ficheiro .shaf
    Executa a descodificação shaf num ficheiro e se necessário a descompressão rle. O ficheiro resultante é do formato .txt
*/

void exeNormal(char* filenameShaf) {
    clock_t tempo = clock();
    char* filenameCod = (char*)malloc(sizeof(char) * strlen(filenameShaf) - 1);
    char tipo, cod[5] = ".cod\0";
    char* filenameNR;

    cortaSufixo(filenameShaf, filenameCod, 6);   //cortar sufixo .shaf\0

    strcat(filenameCod, cod);                    //adiciona .cod\0            

    filenameNR = processaShaf(filenameCod, filenameShaf, &tipo);  //ou escreve o original ou vai escrver um rle,dava jeito ser returnado onde escrveu
    if (tipo == 'R') {
        processaRle(filenameNR, filenameCod);

        mensagem.timer = (clock() - tempo) * 1000 / CLOCKS_PER_SEC;
        mensagemFim(mensagem.timer, mensagem.tamSHAF, mensagem.tamDescompRLE, mensagem.nBlocos, mensagem.ficheiroRLE);
    }
    else {
        mensagem.timer = (clock() - tempo) * 1000 / CLOCKS_PER_SEC;
        mensagemFim(mensagem.timer, mensagem.tamSHAF, mensagem.tamDescompSHAF, mensagem.nBlocos, mensagem.ficheiroSHAF);
    }
}

/*
    Função exeS
    Recebe
    - Nome de um ficheiro .shaf
    Executa a descodificação shaf num ficheiro. O ficheiro resultante é do formato .txt ou .rle
*/

void exeS(char *filenameShaf){
    clock_t tempo = clock();
    char *filenameCod = (char*)malloc(sizeof(char) * strlen(filenameShaf) - 1 );
    char tipo,cod[5] = ".cod\0";
    char* filenameNR;

    cortaSufixo(filenameShaf,filenameCod,6);   //cortar sufixo .shaf\0
 
    strcat(filenameCod,cod);                    //adiciona .cod\0          
   
    filenameNR = processaShaf(filenameCod,filenameShaf,&tipo);  //ou escreve o original ou vai escrver um rle,dava jeito ser returnado onde escrveu

    mensagem.timer = (clock() - tempo) * 1000 / CLOCKS_PER_SEC;
    mensagemFim(mensagem.timer, mensagem.tamSHAF, mensagem.tamDescompSHAF, mensagem.nBlocos, mensagem.ficheiroSHAF);
}

/*
    Função exeR
    Recebe
    - Nome de um ficheiro .rle
    Executa a descompressão rle. O ficheiro resultante é do formato .txt
*/

void exeR(char* filenameRle) {
    clock_t tempo = clock();
    char* filenameFreq = (char*)malloc(sizeof(char) * strlen(filenameRle) + 4);
    char tipo, freq[6] = ".freq\0";
    int i;

    for (i = 0; filenameRle[i] != '\0'; i++){
        filenameFreq[i] = filenameRle[i];
    }
    filenameFreq[i] = '\0';

    strcat(filenameFreq,freq);   //adiciona sufixo .freq

    processaRle(filenameRle,filenameFreq);
    
    mensagem.timer = (clock() - tempo) * 1000 / CLOCKS_PER_SEC;
    mensagemFim(mensagem.timer, mensagem.tamRLE, mensagem.tamDescompRLE, mensagem.nBlocos, mensagem.ficheiroRLE);
}

/*
    Função get_maxBits
    Recebe
    - Lista de simbolos
    - Apontador para um ficheiro .cod
    Devolve o tamanho do maior código de um determinado bloco.
*/

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

