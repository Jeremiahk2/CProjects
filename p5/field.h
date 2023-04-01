/**
*/

#ifndef _FIELD_H_
#define _FIELD_H_

/** Type used for our field, an unsigned byte. */
typedef unsigned char byte;

/** Number of bits in a byte. */
#define BBITS 8

byte fieldAdd(byte a, byte b);

byte fieldSub(byte a, byte b);

byte fieldMul(byte a, byte b);

#endif
