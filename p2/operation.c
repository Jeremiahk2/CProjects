#include <stdio.h>
#include <stdlib.h>
#include "operation.h"

/**
  @file operation.c
  @author Jeremiah Knizley
  File for performing various mathematical operations
  such as adding, subtracting, multiplying, dividing, and exponentials
  while detecting overflow
*/

/**
  Adds together a and b while detecting overflow
  @param a the number to be added with b
  @param b the number to be added with a
  @return long the result of the operation
*/
long plus( long a, long b ) 
{
  long result = a + b;
  if ( result <= 0 && a > 0 && b > 0 ) {
    exit(100);
  }
  if ( result >= 0 && a < 0 && b < 0 ) {
    exit(100);
  }
  return result;
}

/**
  Subtracts b from A while detecting overflow
  @param a the number that will subtract b from itself
  @param b the number to be subtracted from a
  @return long the result of the operation
*/
long minus( long a, long b ) 
{
  long result = a - b;
  if ( result >= 0 && a < 0 && b > 0 ) {
    exit(100);
  }
  if ( result <= 0 && a > 0 && b < 0 ) {
    exit(100);
  }
  return result;
}

/**
  Multiplies together a and b while detecting overflow
  @param a the number to be multiplied with b
  @param b the number to be multiplied with a
  @return long the result of the operation
*/
long times( long a, long b ) 
{
  if ( a == 0 || b == 0 ) {
    return 0;
  }
  if (b == -1) {
    if (a == LONG_MAX) {
      exit(100);
    }
    else {
      return a * b;
    }
  }
  if ( a > 0 && b > 0 ) {
    long x = LONG_MAX / b;
    if (a > x) {
      exit(100);
    }
  }
  if (a > 0 && b < 0 ) {
    long x = LONG_MIN / b;
    if ( a > x ) {
      exit(100);
    }
  }
  if ( a < 0 && b < 0 ) {
    long x = LONG_MAX / b;
    if ( a < x ) {
      exit(100);
    }
  }
  if ( a < 0 && b > 0 ) {
    long x = LONG_MIN / b;
    if ( a < x ) {
      exit(100);
    }
  }
  return a * b;
}

/**
  raises a to the power of b and returns the result while detecting overflow
  @param a the base number to be exponentiated
  @param b the exponent of a, must be positive
  @return long the result of the operation
*/
long exponential (long a, long b )
{
  if (b < 0) {
    exit(103); //no tests for this?
  }
  if ( a == 0 && b != 0 ) {
    return 0;
  }
  if (b == 0) {
    return 1;
  }
  long result = a;
  for (int i = 0; i < b - 1; i++) {
    result = times(result, a);
  }
  return result;
}

/**
  divides a by b and returns the result while detecting overflow
  @param a the number that will be divided by b
  @param b the number that divides a
  @return long the result of the operation
*/
long divide( long a, long b )
{
  if (b == 0) {
    exit(101);
  }
  if (a == LONG_MAX && b == -1) {
    exit(100);
  }
  return a / b;
}