#include "aes.h"
#include "field.h"
#include "io.h"

/** the number of arguments the program should have */
#define NUM_ARGS 4
/** The index in argv where the key file name should be */
#define KEY_FILE 1
/** The index in argv where the input file name should be */
#define INPUT_FILE 2
/** The index in argv where the output file name should be */
#define OUTPUT_FILE 3

int main(int argc, char *argv[])
{
  if (argc != NUM_ARGS) {
    fprintf(stderr, "usage: encrypt <key-file> <input-file> <output-file>\n");
    exit(1);
  }
  int keySize = 0;
  byte *key = readBinaryFile(argv[KEY_FILE], &keySize);

  if (key == NULL) {
    fprintf(stderr, "Can't open file: %s\n", argv[KEY_FILE]);
    free(key);
    exit(1);
  }

  if (keySize != BLOCK_SIZE) {
    fprintf(stderr, "Bad key file: %s\n", argv[KEY_FILE]);
    free(key);
    exit(1);
  }

  int inputSize = 0;
  byte *input = readBinaryFile(argv[INPUT_FILE], &inputSize);

  if (input == NULL) {
    fprintf(stderr, "Can't open file: %s\n", argv[INPUT_FILE]);
    free(input);
    free(key);
    exit(1);
  }

  if (inputSize == 0 || inputSize % BLOCK_SIZE != 0) {
    fprintf(stderr, "Bad plaintext file length: %s\n", argv[INPUT_FILE]);
    free(key);
    free(input);
    exit(1);
  }

  for (int i = 0; i < inputSize / BLOCK_SIZE; i++) {
    byte block[BLOCK_SIZE];
    for (int j = 0; j < BLOCK_SIZE; j++) {
      block[j] = input[i * BLOCK_SIZE + j];
    }
    encryptBlock(block, key);
    for (int j = 0; j < BLOCK_SIZE; j++) {
      input[i * BLOCK_SIZE + j] = block[j];
    }
  }
  writeBinaryFile(argv[OUTPUT_FILE], input, inputSize);

  free(input);
  free(key);

  return EXIT_SUCCESS;
}
