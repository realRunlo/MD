/*
    Gonçalo Pereira & José Gomes
    funções de orocessamento e escrita
*/



#ifndef ___escrita_h___
#define ___escrita_h___




void processaRle(char* filename, char* filenameFreq);
void mensagemFim(int tempo,int *tamanhos,int* tamDescomp,int nBlocos);

void processaCod(char * filenameCod, char * filenameShaf);
int* lerCodFile(char* filenameCod, int* nBlocos);
void lerCodigos(char* filenameCod, int** codigos, int* tamanhos);


#endif // ___escrita_h___