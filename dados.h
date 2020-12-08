#include <stdio.h>
#include <stdlib.h>

#ifndef ___dados_h___
#define ___dados_h___


//sequência binária de um dado simbolo
typedef struct seqBin{
    //o simb que codifica
    int simb;
    //sequencia binária
    char *seq;
}SEQBIN;

//sequência binária de todos os simbolos adicionados
typedef struct seqBinL{

    SEQBIN s;
    SEQBIN * prox;

}SEQBINL;

//estrutura de um bloco
typedef struct bloco{
    //identifica o bloco
    int id;
    //identifica o tamanho do bloco
    int tamanho;
    //codificação desse bloco
    SEQBINL * seqL;

}BLOCO;

//estrutura ligada de blocos
typedef struct blocos{

    //bloco
    BLOCO bloco;
    //bloco seguinte
    BLOCO * prox;

}BLOCOS;



SEQBINL * initSeqL();
BLOCOS * initBlocos();
BLOCOS * addBloco(int id,int tam,SEQBINL * l,BLOCOS * b);
SEQBINL * addSeqL(int simb,char * seq,SEQBINL* l);



#endif // ___dados_h___