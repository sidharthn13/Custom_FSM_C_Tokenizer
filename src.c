void main(){
    typedef struct FSM{
        unsigned char currState;
        unsigned char prevState;
    }FSM;
    FSM *fsm = (FSM *)malloc(sizeof(FSM));
    fsm->currState = 0;
    fsm->prevState = 0;
    printf("\nthe fsm states are: %d , %d", fsm->currState, fsm->prevState);
}