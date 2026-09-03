#ifndef ERROR_H
#define ERROR_H

#define InvokeRuntimeError(string)                                             \
  InvokeRuntimeError_compat(string, __FILE__, __FUNCTION__, __LINE__)

_Noreturn void InvokeRuntimeError_compat(const char *string,
                                         const char *file_path,
                                         const char *function, int line);
#endif
