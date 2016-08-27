#ifndef _PWRNX_STDIO
#define _PWRNX_STDIO

#include <stdarg.h>
#include "stream.h"

int printf(const char *fmt, ...);
int vprintf(const char *fmt, va_list ap);

int sprintf(char *buff, const char *fmt, ...);
int snprintf(char *buff, int len, const char *fmt, ...);
int vsprintf(char *buff, const char *fmt, va_list ap);
int vsnprintf(char *buff, int len, const char *fmt, va_list ap);

int fprintf(FILE *fd, const char *fmt, ...);
int vfprintf(FILE *fd, const char *fmt, va_list ap);

//TODO file modify functions

#endif
