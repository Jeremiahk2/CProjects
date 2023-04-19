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

  char first[strlen(init) + 1];
  char period[strlen(init) + 1];
  int doubleMatches = sscanf(init, "%[0-9]%[.]", first, period);
  if (doubleMatches > 1) {
    free(n);
    return NULL;
  }
  int matches = sscanf(init, "%d", (int *)n->data);
  if (matches == 0) {
    free(n);
    return NULL;
  }
  // // Fill in the node's int (just 5 for now)
  // * (int *) n->data = 5;    //I THINK what is happening here is that we are casting n->data to a int pointer, and then dereferencing it to assign it.

  // Fill in pointers for its methods defined above.
  n->print = printIntNode;
  n->equals = equalsIntNode;
  n->next = NULL;
  return n;
}

/** Function used as the print method for an real node. */
static void printRealNode( Node const *n )
{
  printf( "%.3lf", * (double *) ( n->data ) );
}

/** Function used as the comparison method for real nodes. */
static bool equalsRealNode( Node const *a, Node const *b )
{
  return b->print == printRealNode &&
    * ( (double *) a->data ) == * ( (double *) b->data );
}

Node *makeRealNode( char const *init )
{
  Node *n = (Node *) malloc( sizeof( Node ) + sizeof( double ) );
  int matches = sscanf(init, "%lf", (double *)n->data);
  if (matches == 0) {
    free(n);
    return NULL;
  }
  n->next = NULL;
  n->print = printRealNode;
  n->equals = equalsRealNode;
  return n;
}

/** Function used as the print method for an integer node. */
static void printStringNode( Node const *n )
{
  printf("%s", n->data);
}

/** Function used as the comparison method for an integer nodes. */
static bool equalsStringNode( Node const *a, Node const *b )
{
  return b->print == printRealNode &&
    (strcmp(a->data, b->data) == 0);
}

Node *makeStringNode( char const *init )
{
  // Add code to actually parse the init string and create a
  // string value node if it's in the right format.
  Node *n = (Node *) malloc( sizeof( Node ) + sizeof( init ) );
  int matches = sscanf(init, "%s", n->data);
  if (matches == 0) {
    free(n);
    return NULL;
  }

  n->next = NULL;
  n->print = printStringNode;
  n->equals = equalsStringNode;
  return n;
}
