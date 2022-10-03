#include "onegin.hpp"

// TODO: check includes – da
// TODO: remove logging if not debug – da 
// TODO: do not pass buffer by ptr – da

int main(){
    int numofstrings_readed = 0;
    char* filereadname = "hamlet.txt";
    char* filewritename = "sortedhamlet.txt";
    long int readedcount = 0;
    char* buffer = nullptr;
    int numofstrings_computed = 0;

    #ifdef NDEBUG

    FILE *logfile = fopen("logi.txt", "w");

    buffer = readingfromfile(logfile, filereadname, &readedcount, &numofstrings_readed);


    #else 

    buffer = readingfromfile(nullptr, filereadname, &readedcount, &numofstrings_readed);

    #endif

    //Ввод из файла: 

    #ifdef NDEBUG

    if(buffer == nullptr){
        fprintf(logfile, "LINE %d:  (!) buffer is nullptr! buffer = %p\n", __LINE__, buffer);
        return -1;
    }

    strinfo* strings_adressed = structsforming(logfile, buffer, readedcount, numofstrings_readed, &numofstrings_computed);

    #else
    strinfo* strings_adressed = structsforming(nullptr, buffer, readedcount, numofstrings_readed, &numofstrings_computed);

    #endif


    #ifdef NDEBUG

    if(strings_adressed == nullptr){
        fprintf(logfile, "LINE %d:  (!) strings_adressed is nullptr!\n", __LINE__);
        return -1;
    }

    fprintf(logfile, "LINE %d:  numofstrings_computed is %d\n", __LINE__, numofstrings_computed);

    #endif

    //Работа:
        //Сортировка с начала:
    qsort(strings_adressed, numofstrings_computed + 1, sizeof(strinfo),(int(*) (const void *, const void *)) forwardscompar);
    
    #ifdef NDEBUG

    fprintf(logfile, "LINE %d:  After the qsort\n\n", __LINE__);

    for(int i = 0; i <= numofstrings_computed; i++) fprintf(logfile, "\nLINE %d:  length is %d,  strings_adressed[%d].adress is: %s ",__LINE__, strings_adressed[i].length, i, strings_adressed[i].adress);
    
    //Вывод: 
    fprintf(logfile, "\nLINE %d:  numofstring_computed = %d\n", __LINE__, numofstrings_computed);

    outputinfile(logfile, filewritename, strings_adressed, numofstrings_computed, 1, nullptr);

    #else

    outputinfile(nullptr, filewritename, strings_adressed, numofstrings_computed, 1, nullptr);

    #endif
    
    //Сортировка сзади:
    qsort(strings_adressed, numofstrings_computed + 1, sizeof(strinfo), (int(*) (const void*, const void*))backwardscompar);

    //Вывод в файл backwards sort`a:

    #ifdef NDEBUG

    fprintf(logfile, "LINE %d: BACKWARDS SORT:\n", __LINE__);
    
    outputinfile(logfile, filewritename, strings_adressed, numofstrings_computed, -1, nullptr);

    #else 

    outputinfile(nullptr, filewritename, strings_adressed, numofstrings_computed, -1, nullptr);

    #endif

    #ifdef NDEBUG


    outputinfile(logfile, filewritename, strings_adressed, numofstrings_computed, 0, buffer);

    #else

    outputinfile(nullptr, filewritename, strings_adressed, numofstrings_computed, 0, buffer);

    #endif

    #ifdef NDEBUG

    fclose(logfile);

    #endif

    return 0;
}


/*
 * TODO:
 * 0) Don't open files early - da
 * 1) Fopen shouldn't be in main - da
 * 2) Naming - da
 * 3) Remove redundant variables - da
 * 4) Read about flagss
 * 5) Open -> read -> close file in one function - da
 * 6) Throw away empty lines - da
 * 7) Can't work normally = cringe - da
 * 8) Split into files - da
 */
