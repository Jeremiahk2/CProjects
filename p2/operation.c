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

long plus( long a, long b ) 
{
  long result = a + b;
  if ( result <= 0 && a > 0 && b > 0 ) {
    exit(FAIL_OVERFLOW);
  }
  if ( result >= 0 && a < 0 && b < 0 ) {
    exit(FAIL_OVERFLOW);
  }
  return result;
}

long minus( long a, long b ) 
{
  long result = a - b;
  if ( result >= 0 && a < 0 && b > 0 ) {
    exit(FAIL_OVERFLOW);
  }
  if ( result <= 0 && a > 0 && b < 0 ) {
    exit(FAIL_OVERFLOW);
  }
  return result;
}

long times( long a, long b ) 
{
  if ( a == 0 || b == 0 ) {
    return 0;
  }
  if (b == -1) {
    if (a == LONG_MAX) {
      exit(FAIL_OVERFLOW);
    }
    else {
      return a * b;
    }
  }
  if ( a > 0 && b > 0 ) {
    long x = LONG_MAX / b;
    if (a > x) {
      exit(FAIL_OVERFLOW);
    }
  }
  if (a > 0 && b < 0 ) {
    long x = LONG_MIN / b;
    if ( a > x ) {
      exit(FAIL_OVERFLOW);
    }
  }
  if ( a < 0 && b < 0 ) {
    long x = LONG_MAX / b;
    if ( a < x ) {
      exit(FAIL_OVERFLOW);
    }
  }
  if ( a < 0 && b > 0 ) {
    long x = LONG_MIN / b;
    if ( a < x ) {
      exit(FAIL_OVERFLOW);
    }
  }
  return a * b;
}

long exponential (long a, long b )
{
  if (b < 0) {
    exit(FAIL_DIV0); //no tests for this?
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

long divide( long a, long b )
{
  if (b == 0) {
    exit(FAIL_EXPONENT);
  }
  if (a == LONG_MAX && b == -1) {
    exit(FAIL_DIV0);
  }
  return a / b;
}
