#include "typeDefinitions.h"
#include "FSM.h"
#include "lookupTables.h"



void main(){
    mapNode* keywordMap[KEYWORD_MAP_SIZE] = {NULL}; //allocating memory in stack for faster lookups
    FSM* fsm = fsmInit(); 
    keywordMapInit();
    mapNode *lookupResult = getFromMap(keywordMap,"if");
    printf("the result of the lookup is : %s\n", lookupResult->value);
}
