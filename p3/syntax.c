/**
  @file syntax.c
  @author Jeremiah Knizley
  This file is responsible for determining identifiers from strings
  */

#include "syntax.h"
#include <string.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "io.h"
/**
  Returns true if the parameter string is a legal identifier.
  @param ident the identifier to be used when parsing.
  @return bool true if the identifier is valid, false if not.
  */
bool validIdentifier(char ident[] )
{
  if (ident[0] >= '0' && ident[0] <= '9') {
    return false;
  }
  return true;
}

/**
  Finds occurrences of the target identifier in a line of text from the input file.
  @param word the identifier to be used
  @param line the line to parse
  @param color the color array that holds information about which characters will be which color.
  */
bool markIdentifier(char word[], char line[], int color[])
{
  // If it's not valid, exit and print the invalid word to stderr
  if (!validIdentifier(word)) {
    fprintf(stderr, "Invalid identifier: %s\n", word);
    exit(1);
  }
  //Need foundAtAll for returning because found may be true at some point, but then turned to false later.
  bool foundAtAll = false;
  for (int i = 0; line[i]; i++) {
    //The string has not been found so we set it to false
    bool found = false;
    //If the current character equals the starting character of the identifier
    if (line[i] == word[0]) {
      //Set this true so that it can be falsified later
      found = true;
      //If the character before this one isn't empty, it's not an identifier
      if (i > 0 && line[i - 1] != ' ') {
        found = false;
      }
      //parse through word comparing it to line
      int j;
      for (j = 0; word[j]; j++) {
        // i + j to get the index in line
        if (i + j > strlen(line)) {
          //If we've been taken out of bounds, set found to false and break
          found = false;
          break;
        }
        //if the current location in line doesn't match word, set found to false and break.
        if (line[i + j] != word[j]) {
          found = false;
          break;
        }
      }
      if (i + j < strlen(line) && line[i + j] != ' ' && line[i + j] != '\0') {
        found = false;
      }
    }
    //If we did match the identifier, set foundAtAll true for returning, and cycle through
    //the color array for word's length at the current point in line, putting values as IDENT_COLOR
    if (found) {
      foundAtAll = true;
      for (int k = 0; word[k]; k++) {
        //No need for bounds checking since that was done before
        color[i + k] = IDENT_COLOR;
      }
    }
  }
  return foundAtAll;
}