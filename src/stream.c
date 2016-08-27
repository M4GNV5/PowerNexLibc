#include "include/stream.h"
#include "include/stdlib.h"
#include "include/syscall.h"

static void stdout_putc(FILE* fd, char val);
static char stdoutBuff[BUFSIZ];
static FILE stdoutv = {
	stdout_putc,
	NULL,
	{.stdout = {.pos = 0, .buff = stdoutBuff}}
};

FILE *stdin = NULL;
FILE *stdout = &stdoutv;
FILE *stderr = NULL;

static void stdout_putc(FILE* fd, char val)
{
	/*if(fd != &stdoutv)
		//wat do?*/

	int pos = fd->data.stdout.pos++;
	if(val == '\n') {
		fd->data.stdout.buff[pos] = 0;
		syscall_puts(fd->data.stdout.buff);
		fd->data.stdout.pos = 0;
	}
	else {
		fd->data.stdout.buff[pos] = val;
	}
}

static void strstream_putc(FILE *fd, char val)
{
	int pos = fd->data.string.pos++;
	int max = fd->data.string.max;
	if(max < 0 || pos < max)
		fd->data.string.str[pos] = val;
}

static int strstream_getc(FILE *fd)
{
	int pos = fd->data.string.pos++;
	int max = fd->data.string.max;
	if(max < 0 || pos < max)
		return fd->data.string.str[pos];
	else
		return EOF;
}

void strstream_create(FILE *fd, char *str, int max)
{
	fd->putc = strstream_putc;
	fd->getc = strstream_getc;
	fd->data.string.pos = 0;
	fd->data.string.str = str;
	fd->data.string.max = max;
}

FILE *snopen(char *str, int max)
{
	FILE *fd = malloc(sizeof(FILE));
	strstream_create(fd, str, max);
	return fd;
}
FILE *sopen(char *str)
{
	return snopen(str, -1);
}
