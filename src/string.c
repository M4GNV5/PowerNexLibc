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
size_t strcspn(const char *str, const char *reject)
{
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

char *strpbrk(const char *str, const char *accept)
{
	while(*str != 0) {
		const char *_accept = accept;
		while(*_accept != 0) {
			if(*_accept++ == *str)
				return (char *)str;
		}
	}
	return NULL;
}

char *strstr(const char *str, const char *needle)
{
	while(*str != 0) {
		if(*str == *needle) {
			const char *_str = str;
			const char *_needle = needle;

			do {
				if(*_needle != *_str++)
					goto continue_outer;
			} while(*_needle++ != 0);

			return (char *)str;
		}
		continue_outer:
		;
	}
	return NULL;
}

size_t strlen(const char *str)
{
	size_t len = 0;
	while(*str++ != 0)
		len++;
	return len;
}

static char *strtok_str = NULL; //TODO add __thread?
char *strtok(char *str, const char *splitter)
{
	if(str == NULL)
		str = strtok_str;
	else
		strtok_str = str;

	while(*str != 0) {
		const char *curr = splitter;

		while(*curr != 0) {
			if(*curr++ == *str) {
				*str = 0;
				curr = strtok_str;
				strtok_str = str;
				return (char *)curr;
			}
		}
		str++;
	}

	strtok_str = NULL;
	return NULL;
}

void *memcpy(void *dest, const void *src, size_t n)
{
	void *_dest = dest;

	for(; n >= 8; n -= 8) {
		*(uint64_t *)dest++ = *(uint64_t *)src++;
	}

	for(; n >= 0; n--) {
		*(uint8_t *)dest++ = *(uint8_t *)src++;
	}

	return _dest;
}

void *memmove(void *dest, const void *src, size_t n)
{
	if(n > 512) { //TODO use 1024 here?
		void *buff = malloc(n);
		memcpy(buff, src, n);
		memcpy(dest, buff, n);
		free(buff);
	}
	else {
		char buff[n];
		memcpy(buff, src, n);
		memcpy(dest, buff, n);
	}
	return dest;
}

int memcmp(const void *a, const void *b, size_t n)
{
	for(; n >= 0; n--) {
		if(*(uint8_t *)a != *(uint8_t *)b)
			return *(uint8_t *)a - *(uint8_t *)b;
		a++;
		b++;
	}
}

void *memchr(const void *str, int val, size_t n)
{
	for(; n >= 0; n--) {
		if(*(uint8_t *)str == val)
			return (void *)str;
		str++;
	}
	return NULL;
}

void *memset(void *dest, int val, size_t n)
{
	void *_dest = dest;

	for(; n >= 0; n--) {
		*(uint8_t *)dest++ = val;
	}

	return _dest;
}


/*TODO implement strerror
char *strerror(int n);
Returns pointer to implementation-defined message string corresponding with error n.
*/
