/**
   @file types.c
   @author Jeremiah Knizley
   Implementation of linked list nodes for int values, real values
   (doubles) and string values.
*/

#include "types.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
/** The upper bound on the number of matches for int and real parses. (Exclusive) */
#define UPBNDMATCHES 2
/**
  Function used to print out the data in Integer nodes.
  @param n the node containing the integer
*/
static void printIntNode( Node const *n )
{
  printf( "%d", * (int *) ( n->data ) );
}

/**
  Function used to compare Integer Nodes.
  @param a the first node to compare (should be the main (known) integer node)
  @param b the second node to compare. Can be any kind of node.
  @return the equality of the two nodes. True if equal, false if not
*/
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

  //Check for a period which means it's a double.
  int doubleMatches = sscanf(init, "%[0-9]%[.]", first, period);
  if (doubleMatches > 1) {
    free(n);
    return NULL;
  }

  //Check for ANYTHING after the int.
  // int pos;
  int trash;
  char moreTrash[strlen(init) + 1];
  int extraMatches = sscanf(init, "%d %s", &trash, moreTrash);
  if (extraMatches == UPBNDMATCHES) {
    free(n);
    return NULL;
  }

  //Check for an int.
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

/**
  Function used to print out the data in real nodes. Prints out to 3 decimal places.
  @param n the node containing the real number (double)
*/
static void printRealNode( Node const *n )
{
  printf( "%.3lf", * (double *) ( n->data ) );
}

/**
  Function used to compare Real Nodes.
  @param a the first node to compare (should be the main (known) Real node)
  @param b the second node to compare. Can be any kind of node.
  @return the equality of the two nodes. True if equal, false if not
*/
static bool equalsRealNode( Node const *a, Node const *b )
{
  return b->print == printRealNode &&
    * ( (double *) a->data ) == * ( (double *) b->data );
}

Node *makeRealNode( char const *init )
{
  Node *n = (Node *) malloc( sizeof( Node ) + sizeof( double ) );

  //Check for anything after the double.
  double trash;
  char moreTrash[strlen(init) + 1];
  int extraMatches = sscanf(init, "%lf %s", &trash, moreTrash);
  if (extraMatches == UPBNDMATCHES) {
    free(n);
    return NULL;
  }

  //Check for doubles.
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

/**
  Function used to print out the data in string nodes
  @param n the node containing the string
*/
static void printStringNode( Node const *n )
{
  printf("%s", n->data);
}

/**
  Function used to compare String Nodes.
  @param a the first node to compare (should be the main (known) string node)
  @param b the second node to compare. Can be any kind of node.
  @return the equality of the two nodes. True if equal, false if not
*/
static bool equalsStringNode( Node const *a, Node const *b )
{
  return b->print == printStringNode && (strcmp(a->data, b->data) == 0);
}

Node *makeStringNode( char const *init )
{
  // Add code to actually parse the init string and create a
  // string value node if it's in the right format.
  Node *n = (Node *) malloc( sizeof( Node ) + strlen(init) + 1 );

  if (*init != '\"') {
    free(n);
    return NULL;
  }

  //Check if it's the empty string.
  if (strcmp("\"\"", init) == 0) {
    strcpy(n->data, "");
  }
  //Grab the string inside the quotation marks.
  else {
    int matches = sscanf(init + 1, "%[^\"]", n->data);
  if (matches == 0) {
    free(n);
    return NULL;
  }
  }

  n->next = NULL;
  n->print = printStringNode;
  n->equals = equalsStringNode;
  return n;
}
