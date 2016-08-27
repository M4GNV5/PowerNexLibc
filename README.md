#PowerNex libc
C standard library for a GLORIOUS C MASTERRACE USERSPACE (or just the first step in porting phobos).
Written for the D-Kernel by [Dan “Wild” Printzell](https://github.com/Vild/) called [PowerNex](https://github.com/Vild/PowerNex)

##Currently missing:
- `_start` (i guess this requires compiling a custom `ld` that injects `_start` and links against pwrnxlibc?)
- `time.h`
- `stdio.h` (however the `xxprintf`-functions are implemented)
- `stdlib.h`: `system`, `getenv`, `bsearch`, `qsort`
- `string.h`: `strerror`

##Using
Create a C file similar to this one:
```C
#include "src/include/stdio.h"
#include "src/include/stdlib.h"

void _start()
{
	printf("Hello world from C userspace!\n");

	char buff[128];
	sprintf(buff, "Look what sprintf can do: %-10.5d? And this: %#20llX?", 42, 0xDEADC0DE);

	printf("%s\nIsnt that awesome?\n", buff);
	exit(EXIT_SUCCESS); //bye
}
```
then compile with:
```sh
#inside the PowerNexLibc directory
make
gcc -c myCreatedFile.c -o init.o
ld -nostdlib init.o bin/pwrnxlibc.a -o Init
```
Then move the generated Init file into Initrd/Binary in your powernex directory,
make sure it wont be overwritten by the PowerNex build system and start PowerNex

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
int utoa(uint64_t val, char *str, int base, bool lowerCase);
int itoa(int64_t val, char *str, char positiveSign);
```
