
#include "leitura.h"
#include <string.h>

//ler o tamanho do bloco id e a sequencia de bits dos valores e guardar numa lista de blocos
BLOCOS * lerCodsSimbs(FILE *fp,BLOCOS * bL ,int id){
    char bit,flag='R';
    BLOCOS * b; 
    SEQBINL* l;
    char seq[16];
    char * seqL;
    int simb,tam,i;
    
    
    fscanf(fp,"%d",&tam); //lê tamanho do bloco
    printf("TAMANHO: %d\n",tam);
    fgetc(fp);//le o @ 

    for(simb=0;flag!='@';simb++){
        bit = fgetc(fp);
        flag = bit;

        if(bit!=';' && bit!='@'){
            for(bit,i=0;bit!=';';i++){
            if(bit!=';')
                seq[i]=bit;
            bit = fgetc(fp);
            }
            seq[i] = '\0';
            seqL = seq;
            l = addSeqL(simb,seqL,l);
            printf("%s\n",seq);
        }
       
                              
    }
        
   
   
    b = addBloco(id,tam,l,bL);
    

    return b;
}



//lê ficheiro .cod
BLOCOS * lerCod(char *filename){
//0 rle false,1 rle true
int nBlocos,tam,i;
char tipo;
BLOCOS * pBlocos;
FILE *fp;

//inicia uma estrutua de blocos
pBlocos = initBlocos();

//inicia estrutura de sequência de códigos
fp = fopen(filename,"r");

fgetc(fp);
fscanf(fp,"%c",&tipo); //guardar o tipo do ficheiro rle|n
printf("%c\n",tipo);
fgetc(fp);
fscanf(fp,"%d",&nBlocos);//guardar num de blocos
printf("%d\n",nBlocos);
fgetc(fp);//le o @ 

for(i=1;i<=nBlocos;i++) // lêr blocos a bloco
    pBlocos = lerCodsSimbs(fp,pBlocos,i);

fclose(fp);

return pBlocos;

}


  