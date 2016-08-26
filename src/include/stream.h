#ifndef _PWRNX_STREAM
#define _PWRNX_STREAM

#include <stdint.h>

#define BUFSIZ 512
#define EOF -1

typedef struct FILE
{
	void (*putc)(struct FILE *fd, char val);
	int (*getc)(struct FILE *fd);

	union {
		struct {
			int pos;
			char *str;
			int max;
		} string;
		struct {
			int pos;
			char *buff;
		} stdout;
	} data;
} FILE;

extern FILE *stdin;
extern FILE *stdout;
extern FILE *stderr;

void pwrnx_strstream_create(FILE *fd, char *str, int max);

#ifdef _PWRNX_SOURCE
//TODO move these to stdio.h
FILE *sopen(char *str);
FILE *snopen(char *str, int max);
#endif

#endif
