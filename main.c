#include "typeDefinitions.h"
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
    fileReadBuffer fileBuff;
    fileBuff.fileStream = fopen("src.c", "rb");
    while(!feof(fileBuff.fileStream)){
        int res = fread(fileBuff.inputSymbol, 1, 1, fileBuff.fileStream);
        printf("%c", fileBuff.inputSymbol[0]);
    }
    
    // mapNode *lookupResultKeyword = getFromMap(keywordMap,"break",KEYWORD_MAP_SIZE);
    // printf("the result of the lookup is : %s\n", lookupResultKeyword->value);
    // mapNode *lookupResultOper = getFromMap(operatorMap, "+-+", OPERATOR_MAP_SIZE);
    // printf("the result of the lookup is : %s\n", lookupResultOper->value);
}
