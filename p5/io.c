/**
  @file io.c
  @author Jeremiah Knizley
  file responsible for handing binary input and output.
  Reads binary information from a file, and writes it to a file.
*/
#include "io.h"


byte *readBinaryFile(char const *filename, int *size) 
{
  FILE *bstream = fopen(filename, "rb");
  if (key == NULL) {
    fprintf(stderr, "Can't open file: %s", filename);
    exit(1);
  }
  char *values = (char *)malloc(1 * sizeof(char));
  int memLength = 1;
  int num = 0;
  char current;
  while((current = fgetc(bstream)) != EOF) {
    *(values + num) = current;
    num++;
    if (num == memLength) {
      memLength *=2;
      values = realloc(values, memLength);
    }
  }
  for (int i = 0; i < num; i++) {
    printf("%c", *(values + i));
  }
  *size = num;
  fclose(bstream);
  return values;
}

void writeBinaryFile(char const *filename, byte *data, int size)
{
  FILE *ostream = fopen(filename, "wb");
  if (ostream == NULL) {
    printf(stderr, "Can't open file: %s", filename);
    exit(1);
  }

  fwrite(data, sizeof(byte), size, ostream);
}
