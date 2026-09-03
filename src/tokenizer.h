#ifndef TOKENIZER_H
#define TOKENIZER_H

#include "compiler_native.h"
#include <stdint.h>

enum {
  TOKEN_KEYWORD,
  TOKEN_SYMBOL,
  TOKEN_STRING,
  TOKEN_NUMBER,
  TOKEN_PAR_OPEN,
  TOKEN_PAR_CLOSE,
  TOKEN_SEMICOLON,
  TOKEN_COLON,
  TOKEN_COMMA,
  TOKEN_EQUAL
};

typedef struct Tokens_t {
  uint8_t type;
  char introduction_char;
  char secondary_char;
  char *string;
  int at_line;
} Tokens_t;

typedef struct TokensArray_t {
  Tokens_t *array;
  int count;
} TokensArray_t;

int Tokenize(const char *buffer, int buffer_size, TokensArray_t *token_array,
             CompilerStatus *status);

#endif
