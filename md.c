#include "leitura.h"


int main(int argc, char **argv){
//INPUT: ficheiro(.shaf ou.rle)  nada|s|r
//printf("%s %s",argv[1],argv[2]);

fRle(argv[1],argv[2]);


/*int *tamanhos;
int nb;
tamanhos=lerFreq(argv[1],&nb);
printf("%d\n",nb);
printf("%d\n",tamanhos[0]);
printf("%d",tamanhos[1]);
*/

return 0;
}


