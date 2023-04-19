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
    char first[strlen(command) + 1];
    sscanf(command, "%s%n", first, &pos);

    if (strcmp(first, "enqueue") == 0) {
      char second[strlen(command) + 1];
      strcpy(second, command + pos + 1);
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
      printf("\n");
    }
    else if (strcmp(first, "dequeue") == 0) {
      Node *rtn = dequeue(queue);
      rtn->print(rtn);

      free(rtn);

      printf("\n");
      printf("\n");
    }
    else if (strcmp(first, "promote") == 0) {
      char second[strlen(command) + 1];
      strcpy(second, command + pos + 1);
      Node *new = makeIntNode(second);

      if (new == NULL) {
        new = makeRealNode(second);
        if (new == NULL) {
          new = makeStringNode(second);
        }
      }
      promote(queue, new);
      free(new);
      printf("\n");
    }
    else if (strcmp(first, "length") == 0) {
      int length = 0;
      Node *link = queue->head;
      while (link) {
        length++;
        link = link->next;
      }
      printf("%d\n", length);
      printf("\n");
    }
    else if (strcmp(first, "quit") == 0) {
      quit = true;
      freeQueue(queue);
    }
    free(command);
  }
}