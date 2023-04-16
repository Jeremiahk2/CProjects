/**
   @file types.c
   @author
   Implementation of linked list nodes for int values, real values
   (doubles) and string values.
*/

#include "types.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

/** Function used as the print method for an integer node. */
static void printIntNode( Node const *n )
{
  printf( "%d", * (int *) ( n->data ) );
}

/** Function used as the comparison method for an integer nodes. */
static bool equalsIntNode( Node const *a, Node const *b )
{
  return b->print == printIntNode &&
    * ( (int *) a->data ) == * ( (int *) b->data );
}

Node *makeIntNode( char const *init )
{
  // This isn't really a working implementation.  It doesn't parse the
  // input string.  Instead, it just always returns a node for the
  // value 5.  It shows how to make a new new node for an integer, how
  // to print them and how to compare them, but you'll need to finish
  // the implementation.
  
  // Allocate space for the node plus a little more for its value.
  Node *n = (Node *) malloc( sizeof( Node ) + sizeof( int ) );

  // Fill in the node's int (just 5 for now)
  * (int *) n->data = 5;

  // Fill in pointers for its methods defined above.
  n->print = printIntNode;
  n->equals = equalsIntNode;
  return n;
}

Node *makeRealNode( char const *init )
{
  // Add code to actually parse the init string and create a
  // real value node if it's in the right format.
  return NULL;
}

Node *makeStringNode( char const *init )
{
  // Add code to actually parse the init string and create a
  // string value node if it's in the right format.
  return NULL;
}
