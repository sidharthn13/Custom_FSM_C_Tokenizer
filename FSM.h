#include "main.h"
#include "lookupTables.h"

//struct definition:
typedef struct FSM{
    uchar prevState;
    uchar currState;
    union{
        uchar operatorCount;
        uchar charCount;
    }tokenAttribute;
    union{
        uchar isDecimal;
        uchar isChar;
    }flags;
}FSM;

//function prototypes:
FSM* fsmInit(); //initialises the FSM with prev and curr state set to 0
void fsmDestroy(FSM* fsm); //deallocates the memory memory for fsm
void fsmUpdateState(FSM *fsm, lexemeBuffer *lexBuff, fileReadBuffer *fileBuff);
void fsmReset(FSM * fsm);
void addToLexemeBuffer(lexemeBuffer *lexBuff, fileReadBuffer *fileBuff);
void resetLexemeBuffer(lexemeBuffer *lexBuff);
void printBufferContents(lexemeBuffer *lexBuff);
void printTokenForPrevState(FSM * fsm, lexemeBuffer *lexBuff);
void printTokenForCurrState(FSM *fsm);
void stabilizeState(FSM *fsm, lexemeBuffer *lexBuff, fileReadBuffer *fileBuff);
void performStateOperation(FSM *fsm, lexemeBuffer *lexBuff, fileReadBuffer *fileBuff);
