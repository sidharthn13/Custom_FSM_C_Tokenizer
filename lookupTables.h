//macro definitions for map size:
#define KEYWORD_MAP_SIZE 32

//defining bucket struct for keyword map:
typedef struct mapNode{
    char value[10];
    struct mapNode* chainedNode;
}mapNode;

//declaring keyword map initialised in main file and letting the linker know data present in this particular mem location is shared:
extern mapNode* keywordMap[KEYWORD_MAP_SIZE];

//function prototypes:
uchar keywordHashFunction(char* string);
mapNode* createMapNode(char* str);
void addToMap(mapNode* map[], mapNode* mapEntry);
void keywordMapInit();
mapNode* getFromMap(mapNode* map[], char* str, uchar sizeOfMap);