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
void resetLexemeBuffer(lexemeBuffer *lexBuff){
    lexBuff->index = 0;
}
void printBufferContents(lexemeBuffer *lexBuff){
    for(uchar i = 0; i< lexBuff->index ; i++){
        printf("%c",lexBuff->lexeme[i]);
    }
}
void printTokenForPrevState(FSM * fsm, lexemeBuffer *lexBuff){
    uchar prevState = fsm->prevState;
    if(prevState == 1){
        printf("  :  Identifier\n");
                        }
    else if(prevState==2){
        lexBuff->lexeme[lexBuff->index] = '\0';
        if(getFromMap(keywordMap,lexBuff->lexeme, KEYWORD_MAP_SIZE)==NULL){
            printf("  :  Identifier\n");
                }
        else{printf("  :  Keyword\n");}
                        }
    else if(prevState == 4){
                    printf("  :  Constant\n");
                        }
}
void fsmUpdateState(FSM *fsm, lexemeBuffer *lexBuff, fileReadBuffer *fileBuff){
    uchar inputSymbol = fileBuff->inputSymbol[0];
    switch(inputSymbol){
        //case condition to check for underscore
        case 95:
         if(fsm->currState == 0){
            fsm->prevState=1;
            fsm->currState=1;
         }
         else if(fsm->currState == 4){
            fsm->prevState = 4;
            fsm ->currState = 9;
         }
         else if(fsm->currState == 2){
            fsm->currState = 1;
            fsm->prevState =1;
         }
         else{
            fsm->prevState = fsm->currState;
            fsm ->currState = 1;
         }
         break;
            
        //case condition to check for alphabets
        case 65 ... 90:
        case 97 ... 122:
            if(fsm->currState == 0){
                fsm->currState = 2;
                fsm->prevState=2;
            }
            else if(fsm->currState == 4){
                fsm->prevState = 4;
                fsm ->currState = 9;
            }
            else if(fsm->currState == 1){
                fsm->prevState = 1;
                fsm->currState = 1;
            }
            else{
                fsm->prevState = fsm->currState;
                fsm->currState = 2;
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
             fsm->prevState = fsm->currState;
             fsm->currState = 3;
             break;

        //case condition to check for digits
        case 48 ... 57:
            if(fsm->currState==0){
                fsm->currState=4;
                fsm->prevState=4;
            }
            else if(fsm->currState==1 || fsm->currState==2){
                fsm->currState=1;
                fsm->prevState=1;
            }
            else{
                fsm->prevState=fsm->currState;
                fsm->currState=4;
            }
              break;


        //case condition to check for the dot operator
        case 46:

            break;

            
        //case condition to check for string literal
        case 34:
            
            break;


        //case condition to check for char literal 
        case 39:
            
            break;


        //case condition to check for + and - 
        case 43:
        case 45:

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
        case 124:
        case 126:

            break;


        //case condition to check for whitespace, newline and tab characters
        case 9:
        case 10:
        case 32:
            
            break;

    }
}

void printTokenForCurrState(FSM * fsm){
    uchar currState = fsm->currState;
    if(currState == 3){
        printf(":  Punctuator\n");
    }
}

//changes state to zero, prints delimiter and token when delimiting character is found
void stabilizeState(FSM *fsm, lexemeBuffer *lexBuff, fileReadBuffer *fileBuff){  
    if(fsm->currState == 3){
        addToLexemeBuffer(lexBuff,fileBuff);
        printBufferContents(lexBuff);
        printTokenForCurrState(fsm);
        resetLexemeBuffer(lexBuff);
        fsm->currState=0;   //state should be set to zero after delimiting character is printed
        fsm->prevState=0;
    }
    //else if block can be used for operators , strings and characters
}

void performStateOperation(FSM *fsm, lexemeBuffer *lexBuff, fileReadBuffer *fileBuff){
    uchar currState = fsm->currState;
    uchar prevState = fsm->prevState;
    if(currState == 9){
        fprintf(stderr, "Error : Invalid Token\n");
        exit(1);
    }
    //the below condition will be set when a delimiting character is encountered(punctuators, operators , string and char literals)
    if(currState != prevState){
        printBufferContents(lexBuff);
        printTokenForPrevState(fsm, lexBuff);
        resetLexemeBuffer(lexBuff);
        stabilizeState(fsm, lexBuff, fileBuff);
    }
    else{
        addToLexemeBuffer(lexBuff,fileBuff);
    }


    // switch(currState){
    //     case 1:
    //     case 2:
    //     case 4:
    //     case 7:
    //         addToLexemeBuffer(lexBuff,fileBuff);
    //         break;
    //     case 3:
    //         printBufferContents(lexBuff);
    //         printTokenForPrevState(fsm, lexBuff);
    //         resetLexemeBuffer(lexBuff);
    //         fsm->currState = 0;
    //         printf("%c  :  Punctuator\n", fileBuff->inputSymbol[0]);
    //         break;
    //      case 8:

    // }
}
