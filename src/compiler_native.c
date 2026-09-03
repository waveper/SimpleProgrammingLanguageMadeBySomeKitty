#include "compiler_native.h"

// Count new-line
int GetLineNumberViaBuffer(const char *buffer, int offset) {
  int lines = 1;
  for (int i = 0; i < offset; i++) {
    if (buffer[i] == '\n')
      lines++;
  }
  return lines;
}
