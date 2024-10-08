/**
  @file ident.c
  @author Jeremiah Knizley
  Contains main, responsible for parsing command-line arguments, matching an identifier
  and returning lines containing that identifier, as well as any context lines and line numbers requested
  */

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "io.h"
#include "syntax.h"

/** Number of arguments required on the command line. */
#define REQUIRED_ARGS 2
/** length of the option strings on the command line. */
#define OPTION_LENGTH 2
/** Numerical base 10 */
#define BASE_TEN 10

/** Lines of context to show around an identifier. */
static int context = 0;

/** True if we're printing line numbers. */
static bool numbers = false;
  
/** True if we're showing operators (for the extra credit). */
//static bool operators = false; //NOT OPERATIONAL


/**
  Parses through the optional command-line arguments, -n and -c. 
  If these options are present, the function will set numbers and context to their appropriate values
  @param argc the number of arguments
  @param argv array of char pointers (strings)
  */
static void processArgs(int argc, char *argv[])
{
  //Declared outside loop because it's needed for more than one iteration
  bool contextual = false;
  //Loop through the argv array
  for (int i = 0; i < argc; i++) {
    //if the previous iteration was the context argument, this argument should be the numerical one.
    //So we parse this string for ints and continue to the next string.
    if (contextual) {
      context = atoi(argv[i]);
      //if the number of context lines is negative or 0 (invalid string), it's an error
      if (context <= 0) {
        fprintf(stderr, "usage: ident [-c <context>] [-n] <file> <identifier>\n");
        exit(1);
      }
      //Reset contextual to false for new iteration, continue to next string.
      contextual = false;
      continue;
    }
    //Bounds checking for upcoming if statements. If the length is 0 or 1, continue to the next string.
    //This is placed here becaue the previous if statement allows any length of string for the number.
    if (strlen(argv[i]) < OPTION_LENGTH) {
      continue;
    }
    if (*argv[i] == '-') {
      //If the string is just -n, numbers is true
      if (*(argv[i] + 1) == 'n' && strlen(argv[i]) == REQUIRED_ARGS) {
        numbers = true;
      }
      // if the string is -c, context is true, and the next argument should be a number.
      else if (*(argv[i] + 1) == 'c' && strlen(argv[i]) == REQUIRED_ARGS) {
        contextual = true;
      }
      //If there is a dash but something besides n or c follow it, it's invalid.
      else {
        fprintf(stderr, "usage: ident [-c <context>] [-n] <file> <identifier>\n");
        exit(1);
      }
    }
  }
}

/**
  Main part of the program. 
  Takes command line arguments in the form:
  ./ident -c (optional) (num context lines)(optional) -n (optional) (filename) (identifier)
  -c flags context lines
  -n flags line numbers
  Returns the lines that contain the identifier
  @param argc number of command-line arguments
  @param argv the array of command-line arguments
  @return exit status*/
int main( int argc, char *argv[]) 
{
  //If there aren't enough arguments, error. we use argc - 1 because argc starts at 0.
  if (argc - 1 < REQUIRED_ARGS) {
    fprintf(stderr, "usage: ident [-c <context>] [-n] <file> <identifier>\n");
    exit(1);
  }
  //Process the arguments 
  processArgs(argc, argv);
  //open the file

  FILE *stream = fopen(argv[argc - REQUIRED_ARGS], "r");
  //If the file couldn't be found, error
  if (stream == NULL) {
    fprintf(stderr, "Can't open file: %s\n", argv[argc - REQUIRED_ARGS]);
    exit(1);
  }
  //If the identifier isn't valid, error
  if (!validIdentifier(argv[argc - REQUIRED_ARGS])) {
    fprintf(stderr, "Invalid identifier: %s\n", argv[argc - REQUIRED_ARGS]);
    fclose(stream);
    exit(1);
  }

  // get number of lines for for loop.
  int numLines = countLines(stream);
  int width = 0;
  int count = numLines;
  while (count != 0) {
    width++;
    count /= BASE_TEN;
  }
  //Two dimensional array containing strings
  char history[context][LINE_LIMIT + 1];
  //Initialize all first characters of each string to be a newline marking a string that hasn't been initialized yet
  //Could also do this with NULL, but this might cause problems later since we can't use malloc
  for (int i = 0; i < context; i++) {
    history[i][0] = '\n';
  }
  //Initialize this to numLines so that it's value won't mess up anything on first few iterations
  int identIndex = numLines;
  for (int i = 0; i < numLines; i++) {
    char line[LINE_LIMIT + 1];
    //Get the next line
    readLine(stream, line);
    //Initialize color to be full of 0's
    int color[LINE_LIMIT] = {};
    //Check if the line has any identifiers
    bool identified = markIdentifier(argv[argc - 1], line, color);
    //If it does, print it with the correct color
    if (identified) {
      //Print history (in default color), then clear history
      for (int j = 0; j < context; j++) {
        if (history[j][0] != '\n') {
          if (numbers) {
            printf("%*d: ", width, i + 1 - context + j);
          }
          printf("%s\n", history[j]);
          history[j][0] = '\n';
        }
      }
      //print the actual identified line
      if (numbers) {
        printf("%*d: ", width, i + 1);
      }
      printLine(line, color);
      identIndex = i;
    }
    //Print it anyway if it's within the context.
    else if (i > identIndex && i - identIndex <= context) {
      //This SHOULD print it in default color if it wasn't identified
      if (numbers) {
        printf("%*d: ", width, i + 1);
      }
      printLine(line, color);
    }
    else {
      bool added = false;
      for (int j = 0; j < context; j++) {
        //If there is an opening in history, put the line there
        if (history[j][0] == '\n') {
          strcpy(*(history + j), line);
          added = true;
          break;
        }
      }
      //If not, shift the lines down and add it to the top.
      if (!added && context != 0) {
        for (int j = 0; j < context - 1; j++) {
          strcpy(*(history + j), *(history + j + 1));
        }
        strcpy(*(history + context - 1), line);
      }
    }
  }
  //Remember to close!
  fclose(stream);
  return EXIT_SUCCESS;
}
