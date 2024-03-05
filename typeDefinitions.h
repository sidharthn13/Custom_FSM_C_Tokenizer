#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef unsigned char uchar;

#ifndef BUFFER_DEFINITIONS
#define BUFFER_DEFINITIONS
typedef struct lexemeBuffer{
    char lexeme[35];
    uchar index;
}lexemeBuffer;

typedef struct fileReadBuffer{
    FILE *fileStream;
    char inputSymbol[1];
}fileReadBuffer;
#endif

