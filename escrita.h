/*
    Gonçalo Pereira & José Gomes
    funções de orocessamento e escrita
*/



#ifndef ___escrita_h___
#define ___escrita_h___


/* 
    estretura para passagem de argumentos para multi threading na escrita paralela
*/



void processaRle(char* filename, char* filenameFreq);
void mensagemFim(int tempo,int *tamanhos,int* tamDescomp,int nBlocos);
void processaCod(char * filenameCod, char * filenameShaf);


#endif // ___escrita_h___