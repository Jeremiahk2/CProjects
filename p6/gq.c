#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#include "input.h"
#include "queue.h"
#include "types.h"
/**
  @file gq.c
  @author Jeremiah Knizley
  Main part of the gq program.
  Takes in user input that is supposed to be used to maintain a queue.
  The queue can contain the following three types: int, real, and string
  usage: ./gq
*/


/** The index in the nodeMakers array that contains the makeIntNode function pointer */
#define MAKEINTNODE 0
/** The index in the nodeMakers array that contains the makeRealNode function pointer */
#define MAKEREALNODE 1
/** The index in the nodeMakers array that contains the makeStringNode function pointer */
#define MAKESTRINGNODE 2

/** List of all the node creation functions.  This is a chain of
    responsibility; we can keep trying these functions until we find
    one that knows how to parse the init string. */
static Node *(*nodeMakers[])( char const *init ) = {
  makeIntNode,
  makeRealNode,
  makeStringNode
};
/**
  Main part of the program. Responds to user input. Valid commands are:
  enqueue <value> (add a value to the end of the queue)
  dequeue (remove the value at the front of the queue and print it out)
  promote <value> (move the value to the front of the queue)
  length (get the length of the queue)
  quit (quit the program)
  @return exit status
*/
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
  return EXIT_SUCCESS;
}
