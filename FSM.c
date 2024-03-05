#include "main.h"
#include "FSM.h"

FSM* fsmInit(){
    FSM* fsm = (FSM *)malloc(sizeof(FSM));
    fsm->currState=0;
    fsm->prevState=0;
    return fsm;
} 
void fsmDestroy(FSM* fsm){
    free(fsm);
}
void fsmUpdateState(FSM *fsm, lexemeBuffer *lexBuff, fileReadBuffer *fileBuff){
    printf("current state = %d\n", fsm->currState);
}
