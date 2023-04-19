#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#include "input.h"
#include "queue.h"
#include "types.h"

/** List of all the node creation functions.  This is a chain of
    responsibility; we can keep trying these functions until we find
    one that knows how to parse the init string. */
static Node *(*nodeMakers[])( char const *init ) = {
  makeIntNode,
  makeRealNode,
  makeStringNode
};

int main() 
{
  Queue *queue = makeQueue();
  bool quit = false;
  while (!quit) {
    printf("cmd> ");
    char *command = readLine(stdin); //The whole command.
    printf("%s\n", command);
    int pos;        //The current position.
    int matches = sscanf(command, "enqueue%n", &pos);
    if (matches > 0) {
      char second[strlen(command) + 1];
      sscanf(command + pos, "%s", second);
      Node *new = makeIntNode(second);
      if (new != NULL) {
        enqueue(queue, new);
      }
      else {
        new = makeRealNode(second);
        if (new != NULL) {
          enqueue(queue, new);
        }
        else {
          new = makeStringNode(second);
          if (new != NULL) {
            enqueue(queue, new);
          }
        }
      }
    }
    matches = sscanf(command, "dequeue%n", &pos);
    if (matches > 0) {
      Node *rtn = dequeue(queue);
      rtn->print(rtn);
    }
    matches = sscanf(command, "promote%n", &pos);
    if (matches > 0) {
      char second[strlen(command) + 1];
      sscanf(command + pos, "%s", second);
      Node *new = makeIntNode(second);
      if (new != NULL) {
        enqueue(queue, new);
      }
      else {
        new = makeRealNode(second);
        if (new != NULL) {
          enqueue(queue, new);
        }
        else {
          new = makeStringNode(second);
          if (new != NULL) {
            enqueue(queue, new);
          }
        }
      }
      promote(queue, new);
    }
    matches = sscanf(command, "length");
    if (matches > 0) {
      int length = 0;
      Node **link = &(queue->head);
      //Find the node before the one we want.
      while (*link) {
        length++;
        link = &(*link)->next;
      }
      printf("%d\n", length);
    }
    matches = sscanf(command, "quit");
    if (matches > 0) {
      quit = true;
    }
  }
}