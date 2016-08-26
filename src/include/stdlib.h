#ifndef _PWRNX_STDLIB
#define _PWRNX_STDLIB

#include <stddef.h>

//
//conversion.c
//
double strtod(const char* s, const char** endp);
double atof(const char* s);

long strtol(const char* s, const char** endp, int base);
unsigned long strtoul(const char* s, const char** endp, int base);
int atoi(const char* s);
long atol(const char* s);

//
//stdlib.c
//
#define RAND_MAX 32767
int rand();
void srand(unsigned int seed);

int abs(int n);
long labs(long n);

typedef struct
{
	int quot;
	int rem;
} div_t;
typedef struct
{
	long quot;
	long rem;
} ldiv_t;

div_t div(int num, int denom);
ldiv_t ldiv(long num, long denom);

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1
typedef void (*atexit_callback)(void *data);

void abort();
void exit(int status);
int atexit(atexit_callback func);

#ifdef _PWRNX_SOURCE
int atexit_data(atexit_callback func, void *data);
#endif

//
//malloc.c
//
#ifdef _PWRNX_SOURCE
size_t malloc_size(void *ptr);
#endif
void* malloc(size_t size);
void* calloc(size_t nobj, size_t size);
void* realloc(void* p, size_t size);
void free(void* p);

//TODO missing functions
/*int system(const char* s);
char getenv(const char* name);

void bsearch(const void* key, const void* base, size_t n, size_t size, int (*cmp)(const void* keyval, const void* datum);
void qsort(void* base, size_t n, size_t size, int (*cmp)(const void*, const void/);
*/

#endif
