//macro definitions for map size:
#define KEYWORD_MAP_SIZE 32

//defining bucket struct for keyword map:
typedef struct mapNode{
    char* value;
    struct mapNode* chainedNode;
}mapNode;

//declaring keyword map initialised in the stack of main function in main file:
mapNode* keywordMap[KEYWORD_MAP_SIZE];

//function prototypes:
uchar keywordHashFunction(char* string);
mapNode* createMapNode(char* str);
void addToMap(mapNode* map[], mapNode* mapEntry);
void keywordMapInit();
mapNode* getFromMap(mapNode* map[], char* str);