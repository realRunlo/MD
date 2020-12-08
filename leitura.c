
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
    fgetc(fp);//le o @ 

    for(simb=0;flag!='@';simb++){
        bit = fgetc(fp);
        flag = bit;

//está a ler bit a bit não há forma melhor
        if(bit!=';' && bit!='@'){
            for(bit,i=0;bit!=';';i++){
            if(bit!=';')
                seq[i]=bit;
            bit = fgetc(fp);
            }
            seq[i] = '\0';
            seqL = seq;
            l = addSeqL(simb,seqL,l);
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

int * lerFreq(char *filename,int * nBlocos){

    char tipo,c;
    int i=0;
    FILE *fp;
    fp = fopen(filename,"r");

    fgetc(fp);//le o @ 
    fscanf(fp,"%c",&tipo); //guardar o tipo do ficheiro rle|n
    fgetc(fp);//le o @ 
    fscanf(fp,"%d",nBlocos);//guardar num de blocos
    fgetc(fp);//le o @ 
   
    int *tamanhos = (int *) malloc(sizeof(int)*(*nBlocos));
    
    do{
        fscanf(fp,"%d",&tamanhos[i]);
        fgetc(fp);
        while(c!='@'){
            c = fgetc(fp);
         }
        c='R';
     i++;
    } while(i<*nBlocos);

    fclose(fp);
    printf("saiu\n");

    return tamanhos;
}



//le um bloco binario de tamanho N e devolve onde o mesmo está guardado
char * leBloco(FILE *fp,int n){
    printf("ler bloco\n");

    char *BUFFER = (char *) malloc(sizeof(char)*n);

    fread(BUFFER,sizeof(char),n,fp);
    for(int i=0;i<n;i++)
        printf("%c",BUFFER[i]);

    printf("bloco lido\n");
    return BUFFER;
}

void descompBlocoRle(FILE *fp,char *bloco,int tamanho){
char letra,nreps;

    for(int i=0;i<tamanho;i++){

        if(bloco[i]!=0)
            fprintf(fp,"%c",bloco[i]);
        else{
            letra = bloco[i];
            i++;
            nreps = bloco[i];
            for(int c=0;c<nreps;c++){
                fprintf(fp,"%c",letra);
            }

        } 
    }
}
void fRle(char * filenameRle,char * filenameFreq){
    FILE * fp;
    FILE * fp2;
    char originalFilename[strlen(filenameRle)-3];
    char * bloco;
    int nBlocos;
    int *tamanhos;
 
    editaNome(filenameRle,originalFilename);
  
    fp = fopen(filenameRle,"rb");
    if(fp)printf("abriu\n");else printf("erro");
    
    fp2 = fopen(originalFilename,"w");
    if(fp2)printf("abriu\n");else printf("erro");
   

    tamanhos = lerFreq(filenameFreq,&nBlocos);
  
    for(int i=0;i<nBlocos;i++){
        printf("ciclo\n");
        bloco = leBloco(fp,tamanhos[i]);
        descompBlocoRle(fp2,bloco,tamanhos[i]);
    }
    
   fclose(fp);
   fclose(fp2);

}

//cortar o .cod do filename
void editaNome(char * filename,char *nFilename){
    
    int flag=0;
    
    for(int i=0;flag<2;i++){
        
        
        if(filename[i]=='.')flag++;

        if(flag<2){
            nFilename[i] = filename[i];
        }   
        else
           nFilename[i] = '\0';

        
    } 
    
   


}


