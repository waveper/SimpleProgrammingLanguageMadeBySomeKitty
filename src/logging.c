#include <stdio.h>
#include <stdlib.h>

_Noreturn void InvokeRuntimeError_compat(const char *string,
                                         const char *file_path,
                                         const char *function, int line) {
  fprintf(stderr, "Runtime Error: %s\nAt %s->%s:%d\n", string, file_path,
          function, line);
  exit(-1);
}

void InvokeCompilingWarning(void) {
  // TODO
}
