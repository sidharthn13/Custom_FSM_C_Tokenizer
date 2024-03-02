#include "typeDefinitions.h"
#include "lookupTables.h"

uchar keywordHashFunction(char* str){
    uchar index = 0;
    for(uchar i = 0; str[i]!='\0' ; i++){
        index += (int)str[i];
    }
    index = (0.3456*index)*31;
    return index%31;
}

mapNode* createMapNode(char* str){
    mapNode* mapEntry = (mapNode *)malloc(sizeof(mapNode));
    strcpy(mapEntry->value, str);
    mapEntry->chainedNode = NULL;
    return mapEntry;
}

void addToMap(mapNode* map[], mapNode* mapEntry){
    uchar index = keywordHashFunction(mapEntry->value);
    if(map[index] == NULL){  //this is where the bug is being generated 
        printf("the contents of the global map array at index %hu is NULL\n", index);
        map[index] = mapEntry;
        printf("the contents of the mapNode is : %s\n",mapEntry->value);
        return;
    }
    mapNode *currEntry = map[index];
    while(1){
        if(currEntry->chainedNode == NULL){
            currEntry->chainedNode = mapEntry;
            break;
        }
        currEntry = currEntry->chainedNode;
    }
    return;
}

void keywordMapInit(){
    //list of all keywords in C programming:


    char* keywords[KEYWORD_MAP_SIZE] = {
    "auto",
    "break",
    "case",
    "char",
    "const",
    "continue",
    "default",
    "do",
    "double",
    "else",
    "enum",
    "extern",
    "float",
    "for",
    "goto",
    "if",
    "int",
    "long",
    "register",
    "return",
    "short",
    "signed",
    "sizeof",
    "static",
    "struct",
    "switch",
    "typedef",
    "union",
    "unsigned",
    "void",
    "volatile",
    "while"
    }; 
    for(int i = 0; i < KEYWORD_MAP_SIZE; i++){
        printf("the keyword is : %s \n", keywords[i]);
        mapNode *mapEntry = createMapNode(keywords[i]);
        addToMap(keywordMap,mapEntry); 
    }
}

mapNode* getFromMap(mapNode* map[], char* str){
    uchar index = keywordHashFunction(str);
    if(map[index]==NULL){
        return NULL;
    }
    mapNode *currentNode = map[index];
    if(strcmp(currentNode->value,str)==0){
        return currentNode;
    }
    while(currentNode->chainedNode != NULL){
        currentNode = currentNode->chainedNode;
        if(strcmp(currentNode->value,str)==0){
        return currentNode;
    }
    }
    return NULL;
}