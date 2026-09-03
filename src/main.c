#include "compiler_native.h"
#include "logging.h"
#include "tokenizer.h"
#include <stdio.h>
#include <stdlib.h>

static char *RemoveComment(const char *buffer, int size, int *output_size) {
  /* TODO: Remove Comments like this */
  return NULL;
}

static int GetFileSize(FILE *file) {
  fseek(file, 0L, SEEK_END);
  int size = ftell(file);
  rewind(file);
  return size;
}

int main(int argc, char *argv[]) {
  if (argc == 1) {
    printf("Need input file\n");
  }
  FILE *file_in = fopen(argv[1], "rb");
  if (!file_in) {
    InvokeRuntimeError("Cannot Open Input File");
  }
  FILE *file_out = fopen("output.asm", "wb");
  if (!file_out) {
    fclose(file_in);
    InvokeRuntimeError("Cannot Open Output File");
  }
  int file_in_size = GetFileSize(file_in);
  char *file_in_buffer = malloc(file_in_size);
  if (!file_in_buffer) {
    fclose(file_in);
    fclose(file_out);
    InvokeRuntimeError("Cannot Allocate Memory");
  }
  fread(file_in_buffer, 1, file_in_size, file_in);
  int cleaned_input_buffer_size = 0;
  char *cleaned_input_buffer =
      RemoveComment(file_in_buffer, file_in_size, &cleaned_input_buffer_size);
  TokensArray_t *TokenArray = malloc(sizeof(TokensArray_t));
  TokenArray->count = 0;
  CompilerStatus tokenizer_status;
  Tokenize(file_in_buffer, file_in_size, TokenArray, &tokenizer_status);

  Tokens_t temp_arr;
  for (int i = 0; i < (TokenArray->count - 1); i++) {
    temp_arr = TokenArray->array[i];
    printf("%d: type: %d at %d\n", i, temp_arr.type, temp_arr.at_line);
  }

  fclose(file_in);
  fclose(file_out);
  free(file_in_buffer);
  return 0;
}
