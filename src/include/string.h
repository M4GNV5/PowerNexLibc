#ifndef _PWRNX_STRING
#define _PWRNX_STRING

#include <stddef.h>
//typedef intptr_t size_t;

char *strcpy(char *s, const char *ct);
char *strncpy(char *s, const char *ct, int n);
char *strcat(char *s, const char *ct);
char *strncat(char *s, const char *ct, int n);
int strcmp(const char *cs, const char *ct);
int strncmp(const char *cs, const char *ct, int n);
char *strchr(const char *cs, int c);
char *strrchr(const char *cs, int c);
size_t strspn(const char *cs, const char *ct);
size_t strcspn(const char *cs, const char *ct);
char *strpbrk(const char *cs, const char *ct);
char *strstr(const char *cs, const char *ct);
size_t strlen(const char *cs);
//char *strerror(int n);
char *strtok(char *s, const char *t);
void* memcpy(void* s, const void* ct, int n);
void* memmove(void* s, const void* ct, int n);
int memcmp(const void* cs, const void* ct, int n);
void* memchr(const char *cs, int c, int n);
void* memset(char *s, int c, int n);

#endif
