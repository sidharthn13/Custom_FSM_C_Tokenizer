#include "main.h"
#include "FSM.h"
#include "lookupTables.h"
mapNode* keywordMap[KEYWORD_MAP_SIZE] = {NULL}; /*allocating memory in stack for faster lookups(have to be defined outside
the scope of the main function if data present in this particular memory location has to be accessible from multiple C source file)*/
mapNode* operatorMap[OPERATOR_MAP_SIZE] = {NULL};
void main(){
    FSM* fsm = fsmInit(); 
    keywordMapInit();    //Initialize hashmap containing keywords
    operatorMapInit();  //Initialize hashmap containing operators
    lexemeBuffer lexBuff;
    lexBuff.index=0;
    fileReadBuffer fileBuff;
    fileBuff.fileStream = fopen("src.c", "rb");
    while(!feof(fileBuff.fileStream)){
        fileBuff.inputSymbol[0] = fgetc(fileBuff.fileStream);
        fsmUpdateState(fsm, &lexBuff, &fileBuff);
        performStateOperation(fsm, &lexBuff, &fileBuff);
    }
}
