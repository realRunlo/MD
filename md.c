/*
    Gonçalo Pereira & José Gomes
    Main
*/
#include <stdlib.h>
#include "escrita.h"
#include "leitura.h"
#include <time.h>
#include <unistd.h>

/*
    INPUT: ficheiro(.shaf ou.rle)  nada|s|r
*/
int main(int argc, char **argv){
//processaRle(argv[1],argv[2]);
//exeNormal(argv[1]);
//exeR(argv[1]);
exeS(argv[1]);
/*

    FILE *fp = fopen("Shakespeare.txt.shaf","rb");
    char c;
    int nBlocos,tamanhoLido=0,i=0,l;
    
    fgetc(fp);              //le @
    fscanf(fp,"%d",&nBlocos);   //le numero de blocos
    fgetc(fp);              //le @
    int tamanhos[nBlocos];

    char **blocos = (char**)malloc(sizeof(char) * (nBlocos));
    do{
        fscanf(fp,"%d",&tamanhos[i]); 
        printf("Tamanho bloco %d : %d\n",i,tamanhos[i]);
        fgetc(fp);   
        blocos[i] = (char *)malloc(sizeof(char)*tamanhos[i]);

        while(tamanhoLido < tamanhos[i]){
            l = fread(blocos[i]+tamanhoLido,sizeof(char),tamanhos[i]-tamanhoLido,fp);
            printf("output fread: %d\n",l);
            tamanhoLido = tamanhoLido + l;
            //printf("%d : %d\n",tamanhoLido,tamanhos[i]);
            if(tamanhoLido < tamanhos[i]){
                c = fgetc(fp);
                /*
                if(feof(fp)){
                    printf("EOF");
                 }
                printf("%d\n",c);
                blocos[i][++tamanhoLido] = c;
                fseek(fp,1,SEEK_CUR);
            }
            
        }
        fgetc(fp); //@
    tamanhoLido=0;
    i++;
    }while(i<nBlocos);
        
*/
return 0;
}


