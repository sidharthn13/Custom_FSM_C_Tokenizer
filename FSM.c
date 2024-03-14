#include "main.h"
#include "FSM.h"
// initialises the FSM with prev and curr state set to 0
FSM *fsmInit()
{
    FSM *fsm = (FSM *)malloc(sizeof(FSM));
    fsm->currState = 0;
    fsm->prevState = 0;
    fsm->couldBeSignedInt = 1;
    return fsm;
}
// deallocates the memory memory for fsm
void fsmDestroy(FSM *fsm)
{
    free(fsm);
}
void addToLexemeBuffer(lexemeBuffer *lexBuff, char symbol)
{
    lexBuff->lexeme[lexBuff->index] = symbol;
    lexBuff->index += 1;
}
void resetLexemeBuffer(lexemeBuffer *lexBuff)
{
    lexBuff->index = 0;
}
void printBufferContents(lexemeBuffer *lexBuff)
{
    for (uchar i = 0; i < lexBuff->index; i++)
    {
        printf("%c", lexBuff->lexeme[i]);
    }
}
// The following function updates the state of the FSM based on the current input symbol read from source file
void fsmUpdateState(FSM *fsm, lexemeBuffer *lexBuff, fileReadBuffer *fileBuff)
{
    uchar inputSymbol = fileBuff->inputSymbol[0];
    switch (inputSymbol)
    {
    // case condition to check for underscore
    case 95:
        if (fsm->currState == 0)
        {
            fsm->prevState = 1;
            fsm->currState = 1;
        }
        else if (fsm->currState == 4)
        {
            fsm->prevState = 4;
            fsm->currState = 9;
        }
        else if (fsm->currState == 2)
        {
            fsm->currState = 1;
            fsm->prevState = 1;
        }
        else if(fsm->currState == 8){
            fsm->prevState = -8;
            fsm->currState = 8;
        }
        else
        {
            fsm->prevState = fsm->currState;
            fsm->currState = 1;
        }
        fsm->couldBeSignedInt = 0;
        break;
    // case condition to check for alphabets
    case 65 ... 90:
    case 97 ... 122:
        if (fsm->currState == 0)
        {
            fsm->currState = 2;
            fsm->prevState = 2;
        }
        else if (fsm->currState == 4)
        {
            fsm->prevState = 4;
            fsm->currState = 9;
        }
        else if (fsm->currState == 1)
        {
            fsm->prevState = 1;
            fsm->currState = 1;
        }
        else if(fsm->currState == 8){
            fsm->prevState = -8;
            fsm->currState = 8;
        }
        else
        {
            fsm->prevState = fsm->currState;
            fsm->currState = 2;
        }
        fsm->couldBeSignedInt = 0;
        break;
    // case condition to check for punctuators
    case 40:
    case 41:
    case 44:
    case 58:
    case 59:
    case 91:
    case 93:
    case 123:
    case 125:
        if(fsm->currState == 8){
            fsm->prevState = -8;
            fsm->currState = 8;
        }
        else{
            fsm->prevState = fsm->currState;
            fsm->currState = 3;
            fsm->couldBeSignedInt = 1;
        }
        break;
    // case condition to check for digits
    case 48 ... 57:
        if (fsm->currState == 0 || fsm->currState == 5 || fsm->currState == 7)
        {
            fsm->currState = 4;
            fsm->prevState = 4;
        }
        else if (fsm->currState == 1 || fsm->currState == 2)
        {
            fsm->currState = 1;
            fsm->prevState = 1;
        }
        else if(fsm->currState == 8){
            fsm->prevState = -8;
            fsm->currState = 8;
        }
        else
        {
            fsm->prevState = fsm->currState;
            fsm->currState = 4;
        }
        fsm->couldBeSignedInt = 0;
        break;
    // case condition to check for the dot operator
    case 46:
        if(fsm->currState == 8){
            fsm->prevState = -8;
            fsm->currState = 8;
        }
        else if (fsm->currState != 4)
        {
            fsm->prevState = fsm->currState;
            fsm->currState = 6; // dot is treated as an operator if the lexeme in the buffer is not a numeric constant
        }
        else
        {
            fsm->prevState = 5;
            fsm->currState = 5;
        }
        fsm->couldBeSignedInt = 0;
        break;
    // case condition to check for string literal
    case 34:
        if(fsm->currState !=8 ){
            fsm->prevState = fsm->currState;
            fsm->currState = 8;
        }
        else{
            fsm->prevState = -8;
            fsm->currState = -9;
        }
        break;

    // case condition to check for char literal
    case 39:

        break;

    // case condition to check for + and -
    case 43:
    case 45:
        if(fsm->currState == 8){
            fsm->prevState = -8;
            fsm->currState = 8;
            break;
        }
        if (fsm->couldBeSignedInt == 1)
        {
            fsm->prevState = 7;
            fsm->currState = 7;
            fsm->couldBeSignedInt = 0;
        }
        else
        {
            if (fsm->currState == 7)
            {
                fsm->prevState = 6;
                fsm->currState = 6;
            }
            else{
            fsm->prevState = fsm->currState;
            fsm->currState = 6;
            }
        }
        break;
    // case condition to check for other operators
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
        if(fsm->currState == 8){
            fsm->prevState = -8;
            fsm->currState = 8;
        }
        else if (fsm->currState != 6 && fsm->currState != 7)
        {
            fsm->prevState = fsm->currState;
            fsm->currState = 6;
        }
        else
        {
            fsm->prevState = 6;
            fsm->currState = 6;
        }
        fsm->couldBeSignedInt = 0;
        break;
    // case condition to check for whitespace, newline and tab characters
    case 9:
    case 10:
    case 32:
        if(fsm->currState == 8){
            fsm->prevState = -8;
            fsm->currState = 8;
        }
        break;
    }
}
void fsmReset(FSM *fsm)
{
    fsm->currState = 0;
    fsm->prevState = 0;
}
void printTokenForPrevState(FSM *fsm, lexemeBuffer *lexBuff)
{
    uchar prevState = fsm->prevState;
    if (prevState == 1)
    {
        printf("  :  Identifier\n");
    }
    else if (prevState == 2)
    {
        lexBuff->lexeme[lexBuff->index] = '\0';
        if (getFromMap(keywordMap, lexBuff->lexeme, KEYWORD_MAP_SIZE) == NULL)
        {
            printf("  :  Identifier\n");
        }
        else
        {
            printf("  :  Keyword\n");
        }
    }
    else if (prevState == 4)
    {
        printf("  :  Numeric Constant\n");
    }
    else if (prevState == 6 || prevState == 7)
    {
        printf("  :  Operator\n");
    }
}
void printTokenForCurrState(FSM *fsm)
{
    uchar currState = fsm->currState;
    if (currState == 3)
    {
        printf("  :  Punctuator\n");
    }
    else if (currState == 6)
    {
        printf("  :  Operator\n");
    }
}
/* The following function prints delimiter and token when delimiting character is found,
changes fsm state back to 0. If symbol is not delimiting, it adds to lexemeBuffer*/
void stabilizeState(FSM *fsm, lexemeBuffer *lexBuff, fileReadBuffer *fileBuff)
{
    if (fsm->currState == 3)
    {     
        addToLexemeBuffer(lexBuff, fileBuff->inputSymbol[0]);
        printBufferContents(lexBuff);
        printTokenForCurrState(fsm);
        resetLexemeBuffer(lexBuff);
        fsmReset(fsm); // state should be set to zero after delimiting character is printed
    }
    /* The following block is used to check if current state is -9. The implicit conversion of unsigned char to 
    integer data type happens when the comparison operator is used. When unsigned char -9 is type converted into 
    signed int and read using %d format specifier, the value is 247 */
    else if(fsm->currState == 247){ 
        addToLexemeBuffer(lexBuff, fileBuff->inputSymbol[0]);
        printBufferContents(lexBuff);
        printf("  :  String Constant\n");
        resetLexemeBuffer(lexBuff);
        fsmReset(fsm); // state should be set to zero after delimiting character is printed
    }
    else
    {
        addToLexemeBuffer(lexBuff, fileBuff->inputSymbol[0]);
    }
}
// The following function goes through the operator chain in the lexeme buffer and then prints all valid operators
void segmentOperatorChain(uchar startIndex, char operatorChain[], uchar chainLength)
{
    char buffer[] = {'\0', '\0', '\0', '\0'};
    if (startIndex > chainLength)
    {
        return;
    }
    for (int i = startIndex; i <= startIndex + 2; i++)
    {
        if (i < chainLength)
        {
            buffer[i - startIndex] = operatorChain[i];
        }
    }
    if (startIndex + 2 <= chainLength && getFromMap(operatorMap, buffer, 32))
    {
        printf("%s  :  Operator\n", buffer);
        segmentOperatorChain(startIndex + 3, operatorChain, chainLength);
        return;
    }
    buffer[2] = '\0';
    if (startIndex + 1 <= chainLength && getFromMap(operatorMap, buffer, 32))
    {
        printf("%s  :  Operator\n", buffer);
        segmentOperatorChain(startIndex + 2, operatorChain, chainLength);
        return;
    }
    buffer[1] = '\0';
    if (startIndex <= chainLength && getFromMap(operatorMap, buffer, 32), buffer)
    {
        printf("%s  :  Operator\n", buffer);
        segmentOperatorChain(startIndex + 1, operatorChain, chainLength);
        return;
    }
}
void performStateOperation(FSM *fsm, lexemeBuffer *lexBuff, fileReadBuffer *fileBuff)
{
    uchar currState = fsm->currState;
    uchar prevState = fsm->prevState;
    if (currState == 9)
    {
        fprintf(stderr, "Error : Invalid Token\n");
        exit(1);
    }
    // the below condition will be set when a delimiting character is encountered(punctuators, operators , string and char literals)
    if (currState != prevState)
    {
        if (prevState == 5)
        {
            // following block of code generates token for numeric constant
            lexBuff->index -= 1;
            printBufferContents(lexBuff);
            fsm->prevState = 4;
            printTokenForPrevState(fsm, lexBuff);
            resetLexemeBuffer(lexBuff);
            // following block of code generates token for '.' operator
            addToLexemeBuffer(lexBuff, '.');
            fsm->prevState = 6;
            printBufferContents(lexBuff);
            printTokenForPrevState(fsm, lexBuff);
            resetLexemeBuffer(lexBuff);
        }
        else if (prevState == 7)
        {
            // following block of code generates token for '+' or '-' operator
            printBufferContents(lexBuff);
            printTokenForPrevState(fsm, lexBuff);
            resetLexemeBuffer(lexBuff);
        }
        else if (prevState == 6)
        {
            segmentOperatorChain(0, lexBuff->lexeme, lexBuff->index);
            resetLexemeBuffer(lexBuff);
        }
        else if(prevState == -8){
            // addToLexemeBuffer(lexBuff, fileBuff->inputSymbol[0]);
            printBufferContents(lexBuff);
            resetLexemeBuffer(lexBuff);
        }
        else
        {
            printBufferContents(lexBuff);
            printTokenForPrevState(fsm, lexBuff);
            resetLexemeBuffer(lexBuff);
        }
        stabilizeState(fsm, lexBuff, fileBuff);
    }
    else
    {
        addToLexemeBuffer(lexBuff, fileBuff->inputSymbol[0]);
    }
}
