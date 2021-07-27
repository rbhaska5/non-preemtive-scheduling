#include<stdio.h>
#include "TCB.h"

//function returns a pointer to new q-element
TCB_t *NewItem(){
  TCB_t *queue_item = (TCB_t *)malloc(sizeof(TCB_t));  //memory allocation using malloc
  return queue_item;
}

//function creates an empty queue and head pointer is set to null
TCB_t *newQueue(){
  TCB_t *head = malloc(sizeof(TCB_t));
  head = NULL;
  return head;
}

//function to add queue item, to queue pointed by head pointer
void AddQueue(TCB_t **head,TCB_t *item){

//if queue is an empty queue
  if(*head == NULL){
    printf("empty queue....\n");
    *head = item;  //queue has no elements, head pointer will now point the new queue item
    item->prev = item;
    item->next = item;
  }

  //queue is not empty, add elements
  else{
    //printf("adding elements to queue, not an empty queue\n");
    TCB_t *last_element;
    last_element = (*head)->prev;     //previous of head is the last element
    last_element->next = item;        //next of last element - place the new item
    item->prev = last_element;        //previous of new item - last element of queue
    item->next = *head;               //next of item - points to head
    (*head)->prev = item;             //previous of head after addition - item
  }

}

//function to delete an item from head
TCB_t *DelQueue(TCB_t **head){
  TCB_t *temp;

  //if queue is empty (head pointer - NULL), cannot delete - flag error i.e, exit from function
  if(*head == NULL){
    printf("empty queue, cannot delete an item\n");
    //exit(0);
    return 0;
  }

  //if queue has only one element
  else if((*head)->prev == *head && (*head)->next==*head){
    (*head)->prev = NULL;
    (*head)->next = NULL;
    temp = *head;
    *head = NULL;
  }

  //deleting element from queue, when queue has more than one queue items
  else if((*head)->prev!=*head){
    TCB_t *last_element;
    last_element = (*head)->prev;
    temp = *head;
    *head = (*head)->next;
    last_element->next = *head;
    (*head)->prev = last_element;
  }

  return temp;
}
