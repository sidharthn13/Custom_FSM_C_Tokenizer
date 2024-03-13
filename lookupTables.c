#include "main.h"
#include "lookupTables.h"
uchar hashFunction(char* str){
    uchar index = 0;
    for(uchar i = 0; str[i]!='\0' ; i++){
        index += (uchar)str[i];
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
    uchar index = hashFunction(mapEntry->value);
    if(map[index] == NULL){  
        map[index] = mapEntry;
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
//Initializes a hashtable with list of all keywords in C programming:
void keywordMapInit(){
    char* keywords[KEYWORD_MAP_SIZE] = {"auto","break","case","char","const","continue","default","do","double","else",
    "enum","extern","float","for","goto","if","int","long","register","return","short","signed","sizeof","static","struct",
    "switch","typedef","union","unsigned","void","volatile","while"}; 
    for(int i = 0; i < KEYWORD_MAP_SIZE; i++){
        mapNode *mapEntry = createMapNode(keywords[i]);
        addToMap(keywordMap,mapEntry); 
    }
}
//Initializes a hashtable with list of all operators in C programming:
void operatorMapInit(){
    char* operators[OPERATOR_MAP_SIZE] = {"+", "-", "*", "/", "%", "=", "+=", "-=", "*=", "/=", "%=", 
                        "<<=", ">>=", "&=", "|=", "^=", "++", "--", "==", "!=", ">", 
                        "<", ">=", "<=", "&&", "||", "&", "|", "^", "~", "<<", ">>", "->"};
    for(int i = 0; i < OPERATOR_MAP_SIZE; i++){
        mapNode *mapEntry = createMapNode(operators[i]);
        addToMap(operatorMap, mapEntry);
    }
}
mapNode* getFromMap(mapNode* map[], char* str, uchar sizeOfMap){
    uchar index = hashFunction(str);
    //The following if block is used to prevent undefined behaviour associated with array index out of bound access
    if(index < 0 || index >= sizeOfMap){   
        return NULL;
    }
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