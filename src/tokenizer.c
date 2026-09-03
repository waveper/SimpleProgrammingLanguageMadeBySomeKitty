#include "tokenizer.h"
#include "compiler_native.h"
#include <complex.h>
#include <stdlib.h>

static const char *valid_introduction_char = "feirw";
static const char list_of_valid_secondary_char[][6] = {
    {'f', 3, 'n', 'c', 'r'},      {'e', 1, 'l'},
    {'i', 4, 'n', 'u', 'v', 'f'}, {'r', 4, 't', 'b', 'w', 'd'},
    {'w', 4, 'b', 'w', 'd', 'h'}, {'\0'}};

static int IsItAnAlphabet(char c) {
  if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
    return 1;
  return 0;
}

static int IsItAValidSymbolName(char c) {
  if ((((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) ||
       (c >= '0' && c <= '9')) ||
      c == '_')
    return 1;
  return 0;
}

static int SearchCharInString(char c, const char *string) {
  int len = strlen(string);
  for (int i = 0; i < len; i++) {
    if (c == string[i])
      return 1;
  }
  return 0;
}

static int SearchListOfValidCharOfEachChar(char intro_char, char second_char,
                                           const char list[][6]) {
  int list_index = 0;
  while (1) {
    if (list[list_index][0] == '\0')
      break;
    if (list[list_index][0] == intro_char) {
      for (int list_index_of_index = 0;
           list_index_of_index < (list[list_index][1] - 1);
           list_index_of_index++) {
        if (list[list_index][list_index_of_index + 2] == second_char)
          return 1;
      }
    }
    list_index++;
  }
  return 0;
}

static int AppendNewTokens(TokensArray_t *array, Tokens_t *token) {
  void *temp = realloc(array->array, (array->count + 1) * sizeof(Tokens_t));
  if (!temp)
    return -1;
  array->array = temp;
  memcpy(&array->array[array->count], token, sizeof(Tokens_t));
  array->count++;
  return 0;
}

static int AppendNewSymbolToken(TokensArray_t *array, const char *buffer,
                                int offset_base, int offset_target) {
  Tokens_t token;
  char *symbol_string = malloc(offset_target - offset_base);
  if (!symbol_string)
    return -1;
  for (int i = offset_base; i < offset_target; i++) {
    symbol_string[i - offset_base] = buffer[i];
  }
  token.type = TOKEN_SYMBOL;
  token.string = symbol_string;
  token.at_line = GetLineNumberViaBuffer(buffer, offset_base);
  return AppendNewTokens(array, &token);
}

static int AppendNewKeywordToken(TokensArray_t *array, char intro_char,
                                 char second_char, const char *buffer,
                                 int offset) {
  Tokens_t token;
  token.type = TOKEN_KEYWORD;
  token.at_line = GetLineNumberViaBuffer(buffer, offset);
  token.introduction_char = intro_char;
  token.secondary_char = second_char;
  return AppendNewTokens(array, &token);
}

int Tokenize(const char *buffer, int buffer_size, TokensArray_t *token_array,
             CompilerStatus *status) {
  // TODO
  for (int i = 0; i < buffer_size; i++) {
    if (IsItAnAlphabet(buffer[i])) {
      if (SearchCharInString(buffer[i], valid_introduction_char) &&
          SearchListOfValidCharOfEachChar(buffer[i], buffer[i + 1],
                                          list_of_valid_secondary_char)) {
        AppendNewKeywordToken(token_array, buffer[i], buffer[i + 1], buffer, i);
        i++;
        continue;
      } else {
        for (int j = i; j < buffer_size; j++) {
          if (!IsItAValidSymbolName(buffer[j])) {
            AppendNewSymbolToken(token_array, buffer, i, j);
            i = j;
            break;
          }
        }
        continue;
      }
    }
  }
  return 0;
}
