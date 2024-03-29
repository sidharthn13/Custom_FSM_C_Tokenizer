#include "main.h"
#include "FSM.h"
#include "lookupTables.h"

/* Allocating memory in stack for faster lookups(have to be defined outside
the scope of the main function if data present in this particular memory
location has to be accessible from multiple C source file using extern keyword) */
mapNode *keywordMap[KEYWORD_MAP_SIZE] = {NULL};
mapNode *operatorMap[OPERATOR_MAP_SIZE] = {NULL};
void main(int argc, char *argv[])
{
    FSM *fsm = fsmInit();
    keywordMapInit();
    operatorMapInit();
    lexemeBuffer lexBuff;
    lexBuff.index = 0;
    fileReadBuffer fileBuff;
    fileBuff.fileStream = fopen(argv[1], "rb");
    if (!fileBuff.fileStream)
    {
        fprintf(stderr, "Error : Could not open file. Make sure file exists and valid path is provided...\n");
        exit(1);
    }
    printf("File successfully opened...\nThe parsed lexemes and their corresponding tokens are :\n\n");
    while (!feof(fileBuff.fileStream))
    {
        fileBuff.inputSymbol[0] = fgetc(fileBuff.fileStream);
        fsmUpdateState(fsm, &lexBuff, &fileBuff);
        performStateOperation(fsm, &lexBuff, &fileBuff);
    }
    fsmDestroy(fsm);
}
