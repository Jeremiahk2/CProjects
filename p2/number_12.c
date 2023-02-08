#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "number.h"
#include "operation.h"

/**
  @file number_12.c
  @author Jeremiah Knizley
  The number_12.c file is responsible for parsing and printing values in base 12
*/

/**
  Reads characters from standard input. 
  When it reaches a character that is not whitespace or EOF,
  it returns the code for that character and exits.
  @return the integer value of the next character found.
*/
int skip_space()
{
  bool charFound = false;
  char current = EOF;
  while (!charFound) {
    current = getchar();
    if ( current != ' ' ) {
      charFound = true;
    }
  }
  return (int)current;
}
/**
  parses the next value in the input using base 12 parsing.
  numbers must be on one line, negative numbers are accepted
  @return the value of the number parsed in base 12, ex. EEE = 1727
*/
long parse_value()
{
  long value = 0;
  value = skip_space();
  //EOF and \n are not equivalent but for our purposes, \n really does mean end of file.
  if (value == EOF || value == '\n') {
    return EOF;
  }
  bool negative = false;
  if (value == '-') {
    value = getchar();
    //for base 12, E and X are acceptable numbers
    if (value == 'E') {
      value = E;
    }
    else if (value == 'X') {
      value = X;
    }
    else if (value >= '0' && value <= '9') {
      value = minus(value, CHAR0);
    }
    //Make it negative
    value = times(value, -1);
    negative = true;
  }
  else if ((value >= '0' && value <= '9') || value == 'E' || value == 'X') {
    if (value == 'E') {
      value = E;
    }
    else if (value == 'X') {
      value = X;
    }
    else {
      value = minus(value, CHAR0);
    }
  }
  else {
    //Anything that is not 0-9, E, or X should fail.
    exit(FAIL_INPUT);
  }
  char next = skip_space();
  //need a long value here to clean up operations later
  long numNext = 0;
  while ((next >= '0' && next <= '9') || next == 'E' || next == 'X') {
    if (next == 'E') {
      numNext = E;
    }
    else if (next == 'X') {
      numNext = X;
    }
    else {
      numNext = minus(next, CHAR0);
    }
    value = times(value, BASE12);
    if (negative) {
      //if it's negative, we need to minus in order to get the new digit in.
      value = minus(value, numNext);
    }
    else {
      value = plus(value, numNext);
    }
    next = getchar();
  }
  //unget the next character, because it's probably an operator.
  ungetc( next, stdin );
  return value;
}

/**
  prints a value written in base 12 into the output.
  Negative values are accepted
  @param val the value to be printed into the output. 
*/
void print_value( long val )
{
  //need special case for 0 because in order to stop recursion, val will have to be 0 later.
  if (val == 0) {
    putchar('0');
  }
  else {
    if (val < 0) {
      //Cannot do this on LONG_MIN due to overflow
      if (val != LONG_MIN) {
        //this won't run on the first iteration if val is LONG_MIN, but it will run at the beginning of the second, which does the same thing.
        putchar('-');
        //if the value is 0, we make it positive so this dash doesn't print on recursive operations
        val = times(val, -1);
      }
    }
    long digit;
    if (val == (LONG_MIN)) {
      //Special case for LONG_MIN, this makes the first digit negative, and on the next
      //recursive call, this won't run because now LONG_MIN is small enough to make positive.
      digit = times( -1, (val % BASE12));
    }
    else {
      digit = val % BASE12;
    }

    char newChar;
    if (digit == X) {
      newChar = 'X';
    }
    else if (digit == E) {
      newChar = 'E';
    }
    else {
      newChar = (char)plus(digit, CHAR0);
    }
    val = divide(val, BASE12);
    if (val != 0) {
      //recursive call, this will go until val is 0, meaning we are out of input
      print_value(val);
    }
    //the value in THIS recursive instance hasn't been printed yet, so now we print it.
    putchar(newChar);
  }
}
