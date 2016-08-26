#include <stddef.h>
#include "include/stdlib.h"

char *strcpy(char *dst, const char *src)
{
	while(*src) {
		*dst++ = *src++;
	}
	*dst = 0;
	return dst;
}

char *strncpy(char *dst, const char *src, int n)
{
	for(int i = 0; i < n; i++) {
		dst[i] = src[i];

		if(src[i] == 0) {
			for(i++; i < n; i++)
				dst[i] = 0;
			break;
		}
	}
	return dst;
}

char *strcat(char *dst, const char *src)
{
	char *s = dst;
	while(*dst != 0)
		dst++;

	strcpy(dst, src);
	return s;
}

char *strncat(char *dst, const char *src, int n)
{
	char *s = dst;
	while(*dst != 0)
		dst++;

	strncpy(dst, src, n);
	return s;
}

int strcmp(const char *a, const char *b)
{
	for(;;) {
		if(*a != *b)
			return *a - *b;
		if(*a == 0)
			return 0;

		a++;
		b++;
	}
}
int strncmp(const char *a, const char *b, int n)
{
	for(int i = 0; i < n; i++) {
		if(a[i] != b[i])
			return a[i] - b[i];
		if(a[i] == 0)
			return 0;
	}
	return 0;
}

char *strchr(const char *str, int c)
{
	for(;;) {
		if(*str == c)
			return (char *)str;
		if(*str++ == 0)
			return NULL;
	}
}

char *strrchr(const char *str, int c)
{
	char *match = NULL;
	for(;;) {
		if(*str == c)
			match = (char *)str;
		if(*str++ == 0)
			break;
	}
	return match;
}

size_t strspn(const char *str, const char *accept)
{
	size_t len = -1;
	while(*str != 0) {
		len++;

		const char *_accept = accept;
		while(*_accept != 0) {
			if(*_accept++ == *str)
				goto continue_outer;
		}

		return len;
		continue_outer:
		;
	}
	return len;
}
size_t strcspn(const char *str, const char *reject) {
	size_t len = -1;
	while(*str != 0) {
		len++;

		const char *_reject = reject;
		while(*_reject != 0) {
			if(*_reject++ == *str)
				return len;
		}
	}
	return len;
}

/*
TODO missing functions
char *strpbrk(const char *cs, const char *ct);
Return pointer to first occurrence within cs of any character of ct, or NULL if not found.
char *strstr(const char *cs, const char *ct);
Return pointer to first occurrence of ct in cs, or NULL if not found.
size_t strlen(const char *cs);
Return length of cs.
char *strerror(int n);
Return pointer to implementation-defined string corresponding with error n.
char *strtok(char *s, const char *t);
A sequence of calls to strtok returns tokens from s delimted by a character in ct. Non-NULL s indicates the first call in a sequence. ct may differ on each call. Returns NULL when no such token found.
void* memcpy(void* s, const void* ct, int n);
Copy n characters from ct to s. Return s. Does not work correctly if objects overlap.
void* memmove(void* s, const void* ct, int n);
Copy n characters from ct to s. Return s. Works correctly even if objects overlap.
int memcmp(const void* cs, const void* ct, int n);
Compare first n characters of cs with ct. Return negative if cs < ct, zero if cs == ct, positive if cs > ct.
void* memchr(const char *cs, int c, int n);
Return pointer to first occurrence of c in first n characters of cs, or NULL if not found.
void* memset(char *s, int c, int n);
Replace each of the first n characters of s by c. Return s.
*/
