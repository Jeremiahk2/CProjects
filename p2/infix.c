#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "number.h"
#include "operation.h"

/**
  @file infix.c
  @author Jeremiah Knizley
  This file performs base 10 or base 12 calculations in a given expression 
*/

/**
  parses an expression. Expressions can be a single number or a number raised to an exponent
  @return the expression in long form
*/
static long parse_exp()
{
  long value = parse_value();
  char next = skip_space();
  long exponent;
  if ( next == '^' ) {
    exponent = parse_value();
    value = exponential(value, exponent);
  }
  else {
    ungetc(next, stdin);
  }
  return value;

  
}
/**
  parses a sequence of multiplication or division operations between terms like 53 * 19 / 39
  Also works on a number with no operators
  @return the result of the operation.
*/
static long parse_mul_div()
{
  //default values for left and next, that way left doesn't change on the first iteration.
  long left = 1;
  char next = '*';

  while (next != '+' && next != '-' && next != EOF && next != '\n') {
    long current = parse_exp();
    if (next == '*') {
      left = times(current, left);
    }
    else if (next == '/') {
      left = divide(left, current);
    }
    else {
      exit(FAIL_INPUT);
    }
    next = (char) skip_space();
    char trash = (char) skip_space();
    ungetc(trash, stdin);
  }
  ungetc(next, stdin);
  return left;
}

/**
  the main part of the program. 
  Parses an expression written in base 10 or base 12 and prints a numerical answer
  ex. 10 * 10 * 10 in base 10 results in 1000, and EEE + 1 results in 1000 being printed
  @return int the exit status
*/
int main()
{
  long left;
  left = parse_mul_div();
  long next;
  char operator = (char) skip_space();
  while (operator != EOF && operator != '\n') { //for parenthesis make this a method, but make it so that it ends with ).
    next = parse_mul_div();
    if (operator == '+') {
      left = plus(left, next);
    }
    else if (operator == '-') {
      left = minus(left, next);
    }
    else {
      exit(FAIL_INPUT);
    }
    operator = (char) skip_space();
  }
  print_value(left);
  putchar('\n');
  return EXIT_SUCCESS;

}