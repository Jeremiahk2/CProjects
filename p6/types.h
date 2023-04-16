/**
   @file types.h
   @author
   Header for types exposing functions for creating linked list nodes
   of various types.
*/

#ifndef TYPES_H
#define TYPES_H

#include "queue.h"

/** Make a node containing an integer value.
    @param init String to parse to get the integer value of this node.
    @return pointer to the new node.
*/
Node *makeIntNode( char const *init );

/** Make a node containing a real number value.
    @param init String to parse to get the double value of this node.
    @return pointer to the new node.
*/
Node *makeRealNode( char const *init );

/** Make a node containing an arbitrary string value.
    @param init String to parse to get the string value of this node.
    @return pointer to the new node.
*/
Node *makeStringNode( char const *init );

#endif
