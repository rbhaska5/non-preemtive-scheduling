#include "threads.h"

//creating semaphore structure
typedef struct Semaphore{
  int counter;
  TCB_t *SemQueue;     //queue of TCBs
}Semaphore_t;

Semaphore_t *CreateSem(int InputValue){
  Semaphore_t *newSem;
  newSem = (Semaphore_t*)(malloc(sizeof(Semaphore_t)));  //malloc a semaphore structure
  newSem->counter = InputValue;
  newSem->SemQueue =  newQueue();
  return newSem;
}

//p function using semaphore
void P(Semaphore_t * sem){
  TCB_t *x;
  //TCB_t *Prev_Thread;
  sem->counter--;
  //printf("P - counter value = %d\n",sem->counter);
  //printf("in P\n" );
  if(sem->counter<0){   //if the value is less than 0, block thread
    // x = DelQueue(ReadyQ);
    // printf("in p - before add queue\n");
    // //sleep(1);
    // AddQueue(&(sem->SemQueue),x);
    // printf("in p - after add queue\n");
    // //sleep(1);
    // temp = (*ReadyQ)->context;
    // swapcontext(&(x->context),&(temp->context));
    // printf("in p - swap context done\n");
    //sleep(1);
    //-----------------------------------------
    x = Curr_Thread;
    Curr_Thread = DelQueue(&ReadyQ);
    AddQueue(&(sem->SemQueue),x);
    swapcontext(&(x->context),&(Curr_Thread->context));
  }
}

//v function using semaphore
void V(Semaphore_t * sem){
  //printf("entered V func\n");
  TCB_t *x;
  sem->counter++;
  //printf("V - counter value = %d\n",sem->counter);
  if(sem->counter <= 0){   //if the value <= 0 , take PCB from semaphore and add it to Runq
    x = DelQueue(&(sem->SemQueue));
    //printf("in V - before add queue\n");
    //sleep(1);
    AddQueue(&ReadyQ,x);
    // printf("in V - after add queue\n");
    //sleep(1);
  }
  yield();
  //sleep(1);
  // printf("yield done in V\n");
}
