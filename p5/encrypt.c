#include "aes.h"
#include "field.h"
#include "io.h"

int main(int argc, char *argv[])
{
  if (argc != 4) {
    fprintf(stderr, "usage: encrypt <key-file> <input-file> <output-file>\n");
    exit(1);
  }
  int keySize = 0;
  byte *key = readBinaryFile(argv[1], &keySize);

  if (keySize != 16) {
    fprintf(stderr, "Bad key file: %s\n", argv[1]);
    free(key);
    exit(1);
  }

  int inputSize = 0;
  byte *input = readBinaryFile(argv[2], &inputSize);

  if (inputSize == 0 || inputSize % BLOCK_SIZE != 0) {
    fprintf(stderr, "Bad plaintext file length: %s\n", argv[2]);
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
  writeBinaryFile(argv[3], input, inputSize);

  free(input);
  free(key);

  return EXIT_SUCCESS;
}