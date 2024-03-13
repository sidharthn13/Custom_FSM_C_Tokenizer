#include "main.h"
#include "lookupTables.h"
// struct definition:
typedef struct FSM
{
    uchar prevState;
    uchar currState;
    uchar couldBeSignedInt; //used as a flag. 1 means the operator could be a sign. 0 means it is not a sign
    uchar charCount;
} FSM;
// function prototypes:
FSM *fsmInit();
void fsmDestroy(FSM *fsm);
void fsmUpdateState(FSM *fsm, lexemeBuffer *lexBuff, fileReadBuffer *fileBuff);
void fsmReset(FSM *fsm);
void addToLexemeBuffer(lexemeBuffer *lexBuff, char symbol);
void resetLexemeBuffer(lexemeBuffer *lexBuff);
void printBufferContents(lexemeBuffer *lexBuff);
void printTokenForPrevState(FSM *fsm, lexemeBuffer *lexBuff);
void printTokenForCurrState(FSM *fsm);
void segmentOperatorChain(uchar startIndex, char operatorChain[], uchar chainLength);
void stabilizeState(FSM *fsm, lexemeBuffer *lexBuff, fileReadBuffer *fileBuff);
void performStateOperation(FSM *fsm, lexemeBuffer *lexBuff, fileReadBuffer *fileBuff);
