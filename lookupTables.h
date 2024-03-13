// macro definitions for map size:
#define KEYWORD_MAP_SIZE 32
#define OPERATOR_MAP_SIZE 33

// defining bucket struct for keyword map:
#ifndef LOOKUP_TABLE_NODE_SAFETY
#define LOOKUP_TABLE_NODE_SAFETY
typedef struct mapNode
{
    char value[10];
    struct mapNode *chainedNode;
} mapNode;
#endif

/*  Declaring maps defined in main file and letting the linker know that the variables
defined in another source file is used here(sharing of variables between files):  */
extern mapNode *keywordMap[KEYWORD_MAP_SIZE];
extern mapNode *operatorMap[OPERATOR_MAP_SIZE];

// function prototypes:
uchar hashFunction(char *string);
mapNode *createMapNode(char *str);
void addToMap(mapNode *map[], mapNode *mapEntry);
void keywordMapInit();
void operatorMapInit();
mapNode *getFromMap(mapNode *map[], char *str, uchar sizeOfMap);