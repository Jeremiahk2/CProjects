/** 
    @file queue.h
    @author
    Header file for queue, a generic implementation of a linked list.
*/

#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>
#include <stdlib.h>

/** Node containing an arbitrary value. */
typedef struct NodeStruct {
  /** Pointer to a function that prints the value in this node.
      @param n Pointer to the node containing the value to print. */
  void (*print)( struct NodeStruct const *n );

  /** Compare the value in the two given nodes, returning true
      if it's considered equivalent.
      @param a Pointer to the left-hand node to compare (the one
      containing this compare function)
      @param b Poitner to the right-hand node to compare.
      @return pointer to a new queue. */
  bool (*equals)( struct NodeStruct const *a,
                  struct NodeStruct const *b );

  /** Pointer to the next node on the queue. */
  struct NodeStruct *next;
  
  /** Contents of the node.  Whenever we allocate a node, we reserve some
      extra space at the end for holding the contents.  This field evaluates
      to a pointer to the start of that extra space. */
  char data[];
} Node;

/** Representation of a queue of generic values. */
typedef struct {
  /** Pointer to the first node in the queue. */
  Node *head;
  
  /** Address of the null pointer at the end of this queue, either
      pointing to the head pointer or pointing to the next pointer
      inside the last node. */
  Node **tail;
} Queue;

/**
  Makes an empty, dynamically allocated queue, initializing its fields.
  @return a pointer to the queue
*/
Queue *makeQueue();

/**
  Adds the given node to the back of the given queue
  @param q the queue to add the node to
  @param n the node to add to the queue
  */
void enqueue(Queue *q, Node *n);

/**
  Removes the node at the front of the given queue
  @param q the queue to remove the node from
  @return the node that was removed, or NULL if the queue is empty.
*/
Node *dequeue(Queue *q);

/**
  Finds the first node in the queue with a value that matches paramater example.
  Moves the node that matches example to the front of the queue
  @param q the queue to search in
  @param example the node to compare with.
  @return true if a node is found, false if not.
*/
bool promote(Queue *q, Node const *example);

/**
  Frees all the memory used to store the given queue, including the memory for each of the nodes.
  */
void freeQueue(Queue *q);

#endif
