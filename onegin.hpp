#ifndef ONEGIN_HPP
#define ONEGIN_HPP

#include <stdio.h>
#include <string.h>
#include <malloc.h> 
#include <stat.h>
#include <stdlib.h>
#include <ctype.h>

// #define NDEBUG

struct strinfo{
    char* adress = nullptr;
    int length   = -1;
};

int forwardscompar(strinfo* str1, strinfo* str2);

char* readingfromfile(FILE* logfile, char* filereadname, long int* readedcount, int *numofstrings_readed);

strinfo* structsforming(FILE* logfile, char* buffer, long int readedcount, int numofstrings_readed, int* numofstrings_computed);

void outputinfile(FILE* logfile, char* filewritename, strinfo* strings_adressed, int numofstrings_computed);

int backwardscompar(strinfo* str1, strinfo* str2);

void outputinfile(FILE* logfile, char* filewritename, strinfo* strings_adressed, int numofstrings_computed, int sort_direction, char* buffer);

#endif // ONEGIN_HPP
