#include "main.h"
#include "FSM.h"

FSM* fsmInit(){
    FSM* fsm = (FSM *)malloc(sizeof(FSM));
    fsm->currState=0;
    fsm->prevState=0;
    fsm->couldBeSignedInt=1;
    return fsm;
} 
void fsmDestroy(FSM* fsm){
    free(fsm);
}
void addToLexemeBuffer(lexemeBuffer *lexBuff, char symbol){
    lexBuff->lexeme[lexBuff->index] = symbol;
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
        fsm->couldBeSignedInt=0;
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
            fsm->couldBeSignedInt=0;
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
             fsm->couldBeSignedInt=1;
             break;

        //case condition to check for digits
        case 48 ... 57:
            if(fsm->currState==0 || fsm->currState==5 || fsm->currState==7){
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
            fsm->couldBeSignedInt=0;
            break;


        //case condition to check for the dot operator
        case 46:
            if(fsm->currState!=4){
                fsm->prevState=fsm->currState;
                fsm->currState=6; //dot is treated as an operator if the lexeme in the buffer is not a numeric constant
            }
            else{
                fsm->prevState=5;
                fsm->currState=5;
            }
            fsm->couldBeSignedInt=0;
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
            if(fsm->couldBeSignedInt==1){
                fsm->prevState=7;
                fsm->currState=7;
                fsm->couldBeSignedInt=0;
                fsm->symbolChain.operatorCount=1;
            }   
            else{
                if(fsm->currState==6){
                    fsm->symbolChain.operatorCount+=1;
                }
                else{
                    fsm->symbolChain.operatorCount=1;
                }
                fsm->prevState=fsm->currState;
                fsm->currState=6;
            }
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
            if(fsm->currState!=6){
                fsm->prevState=fsm->currState;
                fsm->currState=6;
                fsm->symbolChain.operatorCount=1;
            }
            else{
                fsm->prevState=6;
                fsm->currState=6;
                fsm->symbolChain.operatorCount+=1;
            }
            fsm->couldBeSignedInt=0;

            break;


        //case condition to check for whitespace, newline and tab characters
        case 9:
        case 10:
        case 32:
            
            break;

    }
}

void fsmReset(FSM * fsm){
    fsm->currState=0;
    fsm->prevState=0;
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
        else{
            printf("  :  Keyword\n");
        }
    }
    else if(prevState == 4){
                    printf("  :  Constant\n");
    }
    else if(prevState==6 ||prevState==7){
        printf("  :  Operator\n");
    }
}

void printTokenForCurrState(FSM *fsm){
    uchar currState = fsm->currState;
    if(currState==3){
        printf("  :  Punctuator\n");
    }
    else if(currState==6){
        printf("  :  Operator\n");
    }
}

//prints delimiter and token when delimiting character is found, changes fsm state back to 0. If symbol is not delimiting, it adds to lexemeBuffer
void stabilizeState(FSM *fsm, lexemeBuffer *lexBuff, fileReadBuffer *fileBuff){  
    if(fsm->currState==3){
        addToLexemeBuffer(lexBuff,fileBuff->inputSymbol[0]);
        printBufferContents(lexBuff);
        printTokenForCurrState(fsm);
        resetLexemeBuffer(lexBuff);
        fsmReset(fsm);   //state should be set to zero after delimiting character is printed
    }
    else if(fsm->currState==6){
        addToLexemeBuffer(lexBuff, fileBuff->inputSymbol[0]);
        //write custom logic to print the operator chain
    }
    else{
        addToLexemeBuffer(lexBuff,fileBuff->inputSymbol[0]);
    }
}

void performStateOperation(FSM *fsm, lexemeBuffer *lexBuff, fileReadBuffer *fileBuff){
    uchar currState=fsm->currState;
    uchar prevState=fsm->prevState;
    if(currState==9){
        fprintf(stderr, "Error : Invalid Token\n");
        exit(1);
    }
    //the below condition will be set when a delimiting character is encountered(punctuators, operators , string and char literals)
    if(currState!=prevState){
        if(prevState==5){
            //following block of code generates token for numeric constant
            lexBuff->index-=1;
            printBufferContents(lexBuff);
            fsm->prevState=4;
            printTokenForPrevState(fsm,lexBuff);
            resetLexemeBuffer(lexBuff);
            //following block of code generates token for '.' operator
            addToLexemeBuffer(lexBuff, '.');
            fsm->prevState=6;
            printBufferContents(lexBuff);
            printTokenForPrevState(fsm, lexBuff);
            resetLexemeBuffer(lexBuff);
        }
        else if(prevState==7){
            //following block of code generates token for '+' or '-' operator
            printBufferContents(lexBuff);
            printTokenForPrevState(fsm,lexBuff);
            resetLexemeBuffer(lexBuff);
        }
        else if(prevState==6){
            printBufferContents(lexBuff);
            printTokenForPrevState(fsm,lexBuff);
            resetLexemeBuffer(lexBuff);
        }
        else{
            printBufferContents(lexBuff);
            printTokenForPrevState(fsm, lexBuff);
            resetLexemeBuffer(lexBuff);
        }
        stabilizeState(fsm, lexBuff, fileBuff);
    }
    else{
        addToLexemeBuffer(lexBuff,fileBuff->inputSymbol[0]);
    }
}
