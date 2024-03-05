#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef unsigned char uchar;

#ifndef BUFFER_DEFINITIONS_HEADER_SAFETY
#define BUFFER_DEFINITIONS_HEADER_SAFETY
typedef struct lexemeBuffer{
    char lexeme[35];
    uchar index;
}lexemeBuffer;

typedef struct fileReadBuffer{
    FILE *fileStream;
    char inputSymbol[1];
}fileReadBuffer;
#endif

