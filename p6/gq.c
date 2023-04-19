#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#include "input.h"
#include "queue.h"
#include "types.h"

#define MAKEINTNODE 0

#define MAKEREALNODE 1

#define MAKESTRINGNODE 2

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
    if (command == NULL) {
      free(command);
      freeQueue(queue);
      quit = true;
    }
    else {
      printf("%s\n", command);
      int pos;        //The current position.
      char first[strlen(command) + 1];
      sscanf(command, "%s%n", first, &pos);

      if (strcmp(first, "enqueue") == 0) {
        char second[strlen(command) + 1];

        char trash;
        int numSpaces;
        sscanf(command + pos, " %c%n", &trash, &numSpaces);
        numSpaces--;

        strcpy(second, command + pos + numSpaces);
        Node *new = nodeMakers[MAKEINTNODE](second);
        if (new != NULL) {
          enqueue(queue, new);
        }
        else {
          new = nodeMakers[MAKEREALNODE](second);
          if (new != NULL) {
            enqueue(queue, new);
          }
          else {
            new = nodeMakers[MAKESTRINGNODE](second);
            if (new != NULL) {
              enqueue(queue, new);
            }
            else {
              printf("Invalid command\n");
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

        char trash;
        int numSpaces;
        sscanf(command + pos, " %c%n", &trash, &numSpaces);
        numSpaces--;

        strcpy(second, command + pos + numSpaces);
        Node *new = nodeMakers[MAKEINTNODE](second);

        if (new == NULL) {
          new = nodeMakers[MAKEREALNODE](second);
          if (new == NULL) {
            new = nodeMakers[MAKESTRINGNODE](second);
          }
        }
        bool promoted = promote(queue, new);
        if (!promoted) {
          printf("Invalid command\n");
        }
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
      else {
        printf("Invalid command\n\n");
      }
      free(command);
    }
  }
}
