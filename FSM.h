#include "typeDefinitions.h"

//struct definition:
typedef struct FSM{
    uchar prevState;
    uchar currState;
    union{
        uchar operatorCount;
        uchar strLiteralCount;
        uchar charLiteralCount;
    }tokenAttribute;
    union{
        uchar isDecimal;
        uchar isChar;
    }flags;
}FSM;

//function prototypes:
FSM* fsmInit(); //initialises the FSM with prev and curr state set to 0
void fsmDestroy(FSM* fsm); //deallocates the memory memory for fsm