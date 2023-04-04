/**
  @file io.h
  @author Jeremiah Knizley
  Header file for io.c.
  Contains all methods
  */

#ifndef _IO_H_
#define _IO_H

#include <stdlib.h>
#include <stdio.h>
#include "field.h"
#include <string.h>
#include <stdbool.h>

/**
  Returns a list of bytes (characters) collected from the given file
  This list is NOT null terminated, hence why size is also modified.
  @param filename the file with the bytes in it
  @param size the size of the byte array. Will contain updated size on completion
  @return an array of bytes read from the file
*/
byte *readBinaryFile(char const *filename, int *size);

/**
  Writes the data to the given file.
  @param filename the file to write to
  @param data the data to write to the file
  @param size the size of the data array
*/
void writeBinaryFile(char const *filename, byte *data, int size);

#endif