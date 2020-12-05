#include "dados.h"

//inicia uma lista de sequencias
SEQBINL * initSeqL(){
    SEQBINL * s;
    s = malloc(sizeof(SEQBINL));
    return s;
}
//inicia blocos ligados
BLOCOS * initBlocos(){
    BLOCOS * b;
    b = malloc(sizeof(BLOCOS));
    return b;
}

//adiciona um bloco à lista de blocos
BLOCOS * addBloco(int id,int tam,SEQBINL * l,BLOCOS * b){
    //novo bloco
    BLOCO * NB;
    NB = malloc(sizeof(BLOCO));
    NB->id = id;
    NB->tamanho = tam;
    NB->seqL = l;

    //ligação dos blocos
    b->prox = NB;

    return b;
}


SEQBINL * addSeqL(int simb,char *seq,SEQBINL* l){
    SEQBIN * NL;
    NL = malloc(sizeof(SEQBIN));
    NL->simb = simb;
    NL->seq = seq;

    //ligação das seq
    l->prox = NL;

}






