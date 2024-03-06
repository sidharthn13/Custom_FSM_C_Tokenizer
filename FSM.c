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
            break;
        //case condition to check for alphabets
        case 65 ... 90:
        case 97 ... 122:
            if(fsm->currState == 0 || fsm->currState == 1 || fsm->currState == 2){
                fsm->prevState=fsm->currState;
                fsm->currState=2;
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
            fsm->prevState=fsm->currState;
            fsm->currState=3;
            break;
        //case condition to check for digits
        case 48 ... 47:
            if(fsm->currState == 0 || fsm->currState == 4 || (fsm->currState == 7 && fsm->tokenAttribute.operatorCount==1)){
                fsm->prevState = fsm->currState;
                fsm->currState = 4;
                break;
            }
        //case condition to check for the dot operator
        case 46:
            if(fsm->currState != 4){
                fsm->prevState = fsm->currState;
                fsm->currState = 8;
                break;
            }
            fsm->flags.isDecimal=1;
            break;
        //case condition to check for string literal
        case 34:
            if(fsm->currState != 5){
                fsm->prevState = fsm->currState;
                fsm->currState = 5;
                break;
            }
            fsm->prevState = 5;
            fsm->currState =0;
            break;
        //case condition to check for char literal 
        case 39:
            if(fsm->currState != 6){
                fsm->prevState = fsm->currState;
                fsm->currState = 6;
                break;
            }
            if(fsm->tokenAttribute.charCount > 1){
                fsm->currState = 9;
                break;
            }
        //case condition to check for + and - 
        case 43:
        case 45:
            if(fsm->currState == 0){
                fsm->prevState = 0;
                fsm->currState = 7;
                fsm->tokenAttribute.operatorCount = 1;
                break;
            }
            if(fsm->currState == 7 || fsm->currState == 8){
                fsm->tokenAttribute.operatorCount += 1;
                break;
            }
            fsm->prevState = fsm->currState;
            fsm->currState = 8;
            break;
        //case condition to check for other operators
        case 33:
        case 37:
        case 38:
        case 42:
        case 47:
        case 60:
        case 61:
        case 62:
        case 63:
        case 94:
        case 98:
        case 124:
        case 126:
            if(fsm->currState!=8){
                fsm->prevState=fsm->currState;
                fsm->currState = 8;
                fsm->tokenAttribute.operatorCount=1;
                break;
            }
            fsm->tokenAttribute.operatorCount = 1;
            break;
        //case condition to check for whitespace, newline and tab characters
        case 9:
        case 10:
        case 32:
            fsm->prevState = fsm->currState;
            fsm->currState = 10;
    }
}
