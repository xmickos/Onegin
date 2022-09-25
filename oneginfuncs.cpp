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


int compar(strinfo* str1, strinfo* str2){

    // TODO: Refactor

    return(strcmp(str1->adress, str2->adress));
}

void readingfromfile(FILE* logfile, char* filereadname, char** buffer, long int* readedcount, int *numofstrings_readed){

    if(logfile == nullptr){
        printf("LINE %d:  (!) logfile is nullptr!\n", __LINE__);
        return;
    }

    if(numofstrings_readed == nullptr){
        fprintf(logfile, "LINE %d:  (!) numofstrings_readed is nullptr!\n", __LINE__);
        return;
    }

    fprintf(logfile, "LINE %d:  numofstrings_readed = %d, size = %d\n", __LINE__, *numofstrings_readed, sizeof(numofstrings_readed));

    if(filereadname == nullptr){
        fprintf(logfile, "LINE %d:  (!) filereadname is nullptr!\n", __LINE__);
        return;
    }

    FILE* fr = fopen(filereadname, "r");
    int filesize = 0;
    struct stat buff;

    if(fr == nullptr){
        fprintf(logfile, "\nLINE %d:   (!) Can`t open the file to read.\n", __LINE__);
        return;
    }

    //Ввод:
        //Выяснение размера файла:
    stat(filereadname, &buff);
    filesize = buff.st_size;

    fprintf(logfile, "LINE %d:  filesize == %d\n", __LINE__, filesize);

    if(filesize > 0){
        *buffer = (char*)calloc((size_t)(filesize + 1), sizeof(char*));

        if(*buffer == nullptr){
            fprintf(logfile, "\nLINE %d:  (!) Calloc returned nullptr!\n", __LINE__);
            return;
        }

        printf("sizeof(filesize) = %lu\n", sizeof(filesize));
        printf("filesize = %d, (size_t)(filesize) = %lu", filesize, (size_t)(filesize));
    }
    else {
        fprintf(logfile, "LINE %d:    \n(!)  filesize < 0\n", __FILE__);
        return;
    }

        //Ввод строк из файла:
    if((*readedcount = (int)fread(*buffer, sizeof(char), (size_t)filesize, fr)) <= 0){
        fprintf(logfile, "LINE: %d:  (!) Fail with fread, readedcount = %d\n", __FILE__, readedcount);
        return;
    }

    *(*buffer + *readedcount + 1) = '\0';
    
    *numofstrings_readed = 0;

    for(int index = 0; index < *readedcount; index++) {
        if(*(*buffer + index) == '\n' || *(*buffer + index) == '\0') {
            (*numofstrings_readed)++;
        }
    }

    fprintf(logfile, "LINE %d:  readedcount = %ld\n", __LINE__, *readedcount);

    fprintf(logfile, "LINE %d:  numofstrings_readed == %d\n", __LINE__, *numofstrings_readed);
    fprintf(logfile, "LINE %d:  buffer = %p\n", __LINE__, *buffer);
    
    fclose(fr);
}


strinfo* structsforming(FILE* logfile, char** buffer, long int readedcount, int numofstrings_readed, int* numofstrings_computed){
    strinfo* strings_adressed = (struct strinfo*)calloc((size_t)numofstrings_readed, sizeof(strinfo));

    if(strings_adressed == nullptr){
        fprintf(logfile, "LINE %d:  (!) strings_adressed is nullptr!\n", __LINE__);
        return nullptr;
    }

    if(*buffer == nullptr) {
    fprintf(logfile, "LINE %d:    (!) buffer is nullptr!\n", __LINE__);
    return nullptr;
    }

    if(numofstrings_computed == nullptr){
        fprintf(logfile, "LINE %d:  (!) numofstrings_computed is nullptr!\n");
        return nullptr;
    }

    fprintf(logfile, "LINE %d:  readedcount = %ld, numofstrings_computd = %d\n",__LINE__, readedcount, *numofstrings_computed);

    strings_adressed[(*numofstrings_computed)].adress = *buffer;
    int curr_len = 0; // i -> curr_len
    int bufferindex = 0;

    fprintf(logfile, "LINE %d:  buffer = %p == %c\n", __LINE__, *buffer, **buffer);
    fprintf(logfile, "\n\nLINE %d:\n\ninfos[numofstrings_computed].adress:\n", __LINE__);

    while (isspace ((int)*(*buffer + bufferindex))) bufferindex++;

    while(bufferindex + curr_len < readedcount){

        // TODO: Refactor. Consider using nested loops

        curr_len++;

        if(*(*buffer + bufferindex + curr_len) == '\n' || *(*buffer + bufferindex + curr_len) == '\0'){

            (*numofstrings_computed)++;
            strings_adressed[*numofstrings_computed].length = curr_len;
            strings_adressed[*numofstrings_computed].adress = *buffer + bufferindex;
            *(*buffer + bufferindex + curr_len) = '\0';
            bufferindex += curr_len;
            curr_len = 0;

            fprintf(logfile, "\nLINE %d:  length is %d,  strings_adressed[%d].adress is: %s ",__LINE__, strings_adressed[*numofstrings_computed].length, *numofstrings_computed, strings_adressed[*numofstrings_computed].adress);

            while (bufferindex < readedcount && (!isalpha(*(*buffer + bufferindex)))) bufferindex++;
            // while (bufferindex < readedcount && (*(*buffer + bufferindex) == '\0' || isspace ((int)*(*buffer + bufferindex)) || *(*buffer + bufferindex) == '(' || *(*buffer + bufferindex) == ')' || !isalpha(*(*buffer + bufferindex)))) bufferindex++;
        }
    }

    fprintf(logfile, "\nLINE %d:  numofstrings_computed = %d\n",__LINE__, *numofstrings_computed);
    return strings_adressed;
}


void outputinfile(FILE* logfile, char* filewritename, strinfo* strings_adressed, int numofstrings_computed){
    if(logfile == nullptr){
        fprintf(logfile, "LINE %d:  (!) logfile is nullptr!\n", __LINE__);
        return;
    }
    if(filewritename == nullptr){
        fprintf(logfile, "LINE %d:  (!) filewritename is nullptr!\n", __LINE__);
        return;
    }
    if(strings_adressed == nullptr){
        fprintf(logfile, "LINE %d:  (!) strings_adressed is nullptr!\n", __LINE__);
        return;
    }


    FILE* fw = fopen(filewritename, "w");

    if(fw == nullptr){
        fprintf(logfile, "LINE %d:  (!) fw is nullptr!\n", __LINE__);
        return;
    }

    fprintf(logfile, "LINE %d:  numofstrings_computed is %d\n", __LINE__, numofstrings_computed);

    for(int i = 0; i < numofstrings_computed; i++) {
        // fprintf(logfile, "LINE %d: strings_adressed[%d] = %s\n",__LINE__, i, strings_adressed[i].adress);
        fputs(strings_adressed[i].adress, fw);
        fputc((int)'\n', fw);
    }

    fclose(fw);
}
