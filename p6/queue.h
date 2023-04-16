/** 
    @file queue.h
    @author
    Header file for queue, a generic implementation of a linked list.
*/

#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>

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

#endif
