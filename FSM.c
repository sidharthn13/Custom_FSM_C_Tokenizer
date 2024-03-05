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
void addToLexemeBuffer(lexemeBuffer *lexBuff, fileReadBuffer *fileBuff){
    lexBuff->lexeme[lexBuff->index] = fileBuff->inputSymbol[0];
    lexBuff->index += 1;
}
void printBufferContents(lexemeBuffer *lexBuff){
    for(uchar i = 0; i<= lexBuff->index ; i++){
        printf("%c",lexBuff->lexeme[i]);
    }
    printf(" : ");
    lexBuff->index = 0;
}
void printDelimiter(fileReadBuffer *fileBuff){
    printf("%c", fileBuff->inputSymbol[0]);
}
void fsmUpdateState(FSM *fsm, lexemeBuffer *lexBuff, fileReadBuffer *fileBuff){
    uchar inputSymbol = fileBuff->inputSymbol[0];
    switch(inputSymbol){
        //case condition to check for underscore
        case 95:
            fsm->prevState=fsm->currState;
            fsm->currState=1;
            addToLexemeBuffer(lexBuff, fileBuff);
            break;
        //case condition to check for alphabets
        case 65 ... 90:
        case 97 ... 122:
            if(fsm->currState == 0 || fsm->currState == 1 || fsm->currState == 2){
                fsm->prevState=fsm->currState;
                fsm->currState=2;
                addToLexemeBuffer(lexBuff, fileBuff);
            }
            break;
        //case condition to check for punctuators
        case 40:
        case 41:
        case 44:
        case 58:
        case 59:
        case 91:
        case 93:
        case 123:
        case 125:
            printBufferContents(lexBuff);
            printDelimiter(fileBuff);
            fsm->prevState=fsm->currState;
            fsm->currState=0;
            break;



    }
}
