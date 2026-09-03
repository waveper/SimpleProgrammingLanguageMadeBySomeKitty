#ifndef COMPILER_NATIVE_H
#define COMPILER_NATIVE_H

typedef struct CompilerStatus {
  int at_line;
  char *error_message;
} CompilerStatus;

int GetLineNumberViaBuffer(const char *buffer, int offset);

#endif
