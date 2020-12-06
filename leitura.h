#include<stdio.h>
#include "dados.h"

#ifndef ___leitura_h___
#define ___leitura_h___



BLOCOS* lerCodsSimbs(FILE *fp,BLOCOS * bL ,int id);
BLOCOS * lerCod(char *filename);
void lerRle(char* filename);
void editaNome(char * filename,char * nfile);


#endif // ___leitura_h___