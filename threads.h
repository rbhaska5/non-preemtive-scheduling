#include "q.h"

TCB_t *Curr_Thread;
TCB_t *ReadyQ;

int counter = 0;

//function to print thread_id
int threadID(TCB_t *item){
  int temp;
  temp = item->thread_id;
  return temp;
}

void start_thread(void (*function)(void)){
  char *stack = (char *) malloc(8192*sizeof(char));   //allocating stack of size 8192
  TCB_t *tcb = (TCB_t *) malloc(sizeof(TCB_t));       //allocating memory to tcb
  init_TCB(tcb, function, (void *) stack, 8192);
  tcb->thread_id = ++counter;                         //adding thread_id
  AddQueue(&ReadyQ,tcb);

}

void run() {
    Curr_Thread = DelQueue(&ReadyQ);
    ucontext_t parent;
    getcontext(&parent);
    swapcontext(&parent, &(Curr_Thread->context));
}

void yield(){
    TCB_t *Prev_Thread;
    AddQueue(&ReadyQ, Curr_Thread);
    Prev_Thread = Curr_Thread;
    Curr_Thread = DelQueue(&ReadyQ);
    //printf("\n-----in yield function-------\n");
    //printf("previous thread = %d;\t",threadID(Prev_Thread));
    //printf("current thread = %d \n\n",threadID(Curr_Thread));
    swapcontext(&(Prev_Thread->context), &(Curr_Thread->context));   //swapping context from previous thread to thread pointed to current thread
}
