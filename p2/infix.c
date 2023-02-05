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
  the main part of the program. 
  Parses an expression written in base 10 or base 12 and returns a numerical answer
*/
int main()
{
  long left = parse_exp();
  long next;
  char operator = skip_space();
  while (operator != EOF) {
    next = parse_exp();
    if (operator == '+') {
      left = plus(left, next)
    }
    if (operator == '-') {
      left = minus(left, next);
    }
    operator = skip_space();
  }
  return left;

}

static long parse_exp()
{
  long value = parse_value();
  char next = getchar();
  bool exponentFound = false;
  long exponent;
  if ( next == '^' ) {
    exponent = parse_value();
    value = exponential(value, exponent);
  }
  return value;

  
}

static long parse_mul_div()
{

  long current = parse_exp();
  //the current value of everything to the left of the current expression
  long left = 1;
  // char next = skip_space();
  // ungetc(next, stdin);
  char next = '*';

  while (next != '+' && next != '-' && next != EOF) {
    if (next == '*') {
      left = times(current, left);
    }
    if (next == '/') {
      left = times(left, current);
    }
    next = skip_space();
    char trash = skip_space();
    ungetc(trash, stdin);
    current = parse_exp();
  }
  ungetc(next, stdin);
  return left;
}