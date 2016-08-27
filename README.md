#PowerNex libc
C standard library for a GLORIOUS C MASTERRACE USERSPACE (or just the first step in porting phobos)

##Currently missing:
- `time.h`
- `stdio.h` (however there is an incomplete inplementation of the `xxprintf`-functions)
- `stdlib.h`: `system`, `getenv`, `bsearch`, `qsort`
- `string.h`: partly implemented

##Extension functions:
```C
//before including headers define:
#define _PWRNX_SOURCE

//returns the size of the allocated memory area
size_t malloc_size(void *ptr);

//same as atexit but supports passing a data pointer to the exit handler
int atexit_data(void (*func)(void *data), void *data);

//opens the string pointed to by 'str' as a FILE allowing read/write operations
//(used for sprintf/snprintf)
FILE *sopen(char *str);
FILE *snopen(char *str, int max);

//converts an (unsigned-)integer to its string representation (mainly for use within printf)
int uitoa(uint64_t val, char *str, int base, bool lowerCase);
int itoa(int64_t val, char *str, int base, bool lowerCase);
```
