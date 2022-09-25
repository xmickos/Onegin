#include <stdio.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <malloc.h> 
#include <stat.h>
#include <stdlib.h>
#include <ctype.h>

struct strinfo{
    char* adress = nullptr;
    int length = -1;
};

int compar(strinfo* str1, strinfo* str2);

void readingfromfile(FILE* logfile, char* filereadname, char** buffer, long int* readedcount, int *numofstrings_readed);

strinfo* structsforming(FILE* logfile, char** buffer, long int readedcount, int numofstrings_readed, int* numofstrings_computed);

void outputinfile(FILE* logfile, char* filewritename, strinfo* strings_adressed, int numofstrings_computed);