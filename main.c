#include "typeDefinitions.h"
#include "FSM.h"
#include "lookupTables.h"

mapNode* keywordMap[KEYWORD_MAP_SIZE] = {NULL}; /*allocating memory in stack for faster lookups(have to be defined outside
the scope of the main function if data present in this particular memory location has to be accessible from multiple C source file)*/

void main(){
    FSM* fsm = fsmInit(); 
    keywordMapInit();
    mapNode *lookupResult = getFromMap(keywordMap,"brea",KEYWORD_MAP_SIZE);
    printf("the result of the lookup is : %s\n", lookupResult->value);
}
