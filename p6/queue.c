/**
  @file queue.c
  @author Jeremiah Knizley
  File responsible for queue functions and operations
*/
#include "queue.h"

Queue *makeQueue()
{
  Queue *queue = (Queue *)malloc(sizeof(Queue));
  queue->head = NULL;           //May need to malloc this (probably not)
  queue->tail = &(queue->head); //This too (more likely)
  return queue;
}

void enqueue(Queue *q, Node *n)
{
  if (q->head == NULL) {
    q->head = n;
    q->tail = &(q->head->next);
  }
  else {
    *(q->tail) = n;
    q->tail = &(n->next);
  }
}

Node *dequeue(Queue *q)
{
  if (q->head == NULL) {
    return NULL;
  }
  Node *oldHead = q->head;                 //Get copy of current head for returning.
  q->head = q->head->next;              //Set our new head as the queue's head.
  return oldHead;
}

bool promote(Queue *q, Node const *example)
{
  //If the first node is the one we want
  if (example->equals(example, q->head)) {
    return true;
  }
  Node **link = &(q->head);
  //Find the node before the one we want.
  while (*link && !(example->equals(example, (*link)->next))) {
    link = &(*link)->next;
  }
  //If we didn't find it, return false.
  if (*link == NULL) {
    return false;
  }
  //If we did find it, move it to the front.
  Node *found = (*link)->next;     //Keep the node
  (*link)->next = found->next;     //Skip over the node (remove it from the list)
  found->next = q->head;           //Set the node's next value as head  
  q->head = found;                 //Set head as the node.
  return true;
}     

void freeQueue(Queue *q)
{
  while (q->head) {
    Node *n = q->head;
    q->head = n->next;
    free( n );
  }
  free(q);
}