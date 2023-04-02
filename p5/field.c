/**
  @file field.c
  @author Jeremiah Knizley
  File for dealing with bitwise operations.
  Namely, adding, subtracting, and multiplying.
  These functions are carried using the 8-bit Galois field used by AES.
*/

#include "field.h"

byte fieldAdd(byte a, byte b)
{
  return a ^ b;
}

byte fieldSub(byte a, byte b)
{
  return a ^ b;
}

byte fieldMul(byte a, byte b)
{
  short phaseOne[BBITS] = {};
  //Cycle through, shifting each time we find a one in the a byte.
  unsigned char mask = 1;
  for (int i = 0; i < BBITS; i++) {
    if ((b & mask) == mask) {
      phaseOne[i] = a << i;
    }
    mask = mask * 2;
  }
  //Compile the phaseOne 16-bit values together int one short.
  short compilation = phaseOne[0];
  for (int i = 1; i < BBITS; i++) {
    compilation = compilation ^ phaseOne[i];
  }
  short reducerShift = BBITS - 1;
  unsigned short reducer = 0x11B << reducerShift;
  for (int i = 0; i <= reducerShift; i++) {
    int shift = BBITS + reducerShift - i;
    if ((compilation >> shift) == (reducer >> shift)) {
      compilation = compilation ^ reducer;
    }
    reducer = reducer >> 1;
  }
  return compilation;
}