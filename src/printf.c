#include <stdarg.h>
#include <stdbool.h>
#include "include/stream.h"
#include "include/ctype.h"
#include "include/stdlib.h"
#include "include/string.h"

void strstream_create(FILE *fd, char *str, int max); //stream.c
int vfprintf(FILE *fd, const char *fmt, va_list ap);

int printf(const char *fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	return vfprintf(stdout, fmt, ap);
}

int vprintf(const char *fmt, va_list ap)
{
	return vfprintf(stdout, fmt, ap);
}

int sprintf(char *buff, const char *fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);

	FILE fd;
	strstream_create(&fd, buff, -1);
	return vfprintf(&fd, fmt, ap);
}
int snprintf(char *buff, int len, const char *fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);

	FILE fd;
	strstream_create(&fd, buff, len);
	return vfprintf(&fd, fmt, ap);
}

int vsprintf(char *buff, const char *fmt, va_list ap)
{
	FILE fd;
	strstream_create(&fd, buff, -1);
	return vfprintf(&fd, fmt, ap);
}
int vsnprintf(char *buff, int len, const char *fmt, va_list ap)
{
	FILE fd;
	strstream_create(&fd, buff, len);
	return vfprintf(&fd, fmt, ap);
}

int fprintf(FILE *fd, const char *fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	return vfprintf(fd, fmt, ap);
}

struct printfmt
{
	bool leftAdjust;
	bool alternateForm;
	bool lowerCase;
	char sign;
	char pad;
	int width;
	int precision;
	int size;
};

static void vprintPad(FILE *fd, int length, char padChar)
{
	for(int i = 0; i < length; i++)
	{
		fd->putc(fd, padChar);
	}
}

static int fprintString(FILE *fd, const char *str, struct printfmt *fmt)
{
	int len = strlen(str);
	if(fmt->precision <= 0)
		fmt->precision = len + 1;

	if(!fmt->leftAdjust && fmt->width > len) {
		vprintPad(fd, fmt->width - len, fmt->pad);
		len = fmt->width;
	}

	for(int i = 0; str[i] != 0 && i < fmt->precision; i++)
		fd->putc(fd, str[i]);

	if(fmt->leftAdjust && fmt->width > len) {
		vprintPad(fd, fmt->width - len, fmt->pad);
		len = fmt->width;
	}

	return len;
}

static int vfprintInt(FILE *fd, va_list ap, struct printfmt *fmt)
{
	int64_t val;
	switch(fmt->size)
	{
		case -2:
			val = va_arg(ap, int) & 0xFF; //TODO use preprocessor macros instead of constants here?
			break;
		case -1:
			val = va_arg(ap, int) & 0xFFFF;
			break;
		case 0:
			val = va_arg(ap, signed int);
			break;
		case 1:
			val = va_arg(ap, signed long int);
			break;
		case 2:
			val = va_arg(ap, signed long long int);
			break;
	}

	char buff[fmt->precision + 16];
	char *str = buff + fmt->precision;
	int len = itoa(val, str, fmt->sign);

	if(len < fmt->precision) {
		len = fmt->precision - len;
		str -= len;

		for(int i = 0; i < len; i++)
			str[i] = '0';

		len = fmt->precision;
	}
	if(!fmt->leftAdjust && fmt->width > len) {
		vprintPad(fd, fmt->width - len, fmt->pad);
		len = fmt->width;
	}

	for(int i = 0; str[i] != 0; i++)
		fd->putc(fd, str[i]);

	if(fmt->leftAdjust && fmt->width > len) {
		vprintPad(fd, fmt->width - len, fmt->pad);
		len = fmt->width;
	}

	return len;
}
static int vfprintUint(FILE *fd, va_list ap, struct printfmt *fmt, int base)
{
	uint64_t val;
	switch(fmt->size) {
		case -2:
			val = va_arg(ap, unsigned int) & 0xFF;
			break;
		case -1:
			val = va_arg(ap, unsigned int) & 0xFFFF;
			break;
		case 0:
			val = va_arg(ap, unsigned int);
			break;
		case 1:
			val = va_arg(ap, unsigned long int);
			break;
		case 2:
			val = va_arg(ap, unsigned long long int);
			break;
		case 3:
			val = (uint64_t)va_arg(ap, void *);
			if(val == 0)
				return fprintString(fd, "(null)", fmt);
			break;
	}

	char buff[fmt->precision + 16];
	char *str = buff + fmt->precision;
	int len;

	if(!fmt->alternateForm) {
		len = 0;
	}
	else {
		switch(base) {
			case 8:
				*str++ = '0';
				len = 1;
				break;
			case 16:
				*str++ = '0';
				*str++ = fmt->lowerCase ? 'x' : 'X';
				len = 2;
				break;
			default:
				len = 0;
				break;
		}
	}
	len += utoa(val, str, base, fmt->lowerCase);
	str = buff + fmt->precision;

	if(len < fmt->precision) {
		len = fmt->precision - len;
		str -= len;

		for(int i = 0; i < len; i++)
			str[i] = '0';

		len = fmt->precision;
	}
	if(!fmt->leftAdjust && fmt->width > len) {
		vprintPad(fd, fmt->width - len, fmt->pad);
		len = fmt->width;
	}

	for(int i = 0; i < len; i++)
		fd->putc(fd, str[i]);

	if(fmt->leftAdjust && fmt->width > len) {
		vprintPad(fd, fmt->width - len, fmt->pad);
		len = fmt->width;
	}

	return len;
}

int vfprintf(FILE *fd, const char *fmt, va_list ap)
{
	int written = 0;
	char curr;

	while((curr = *fmt++) != 0) {
		if(curr != '%') {
			fd->putc(fd, curr);
			written++;
		}
		else {
			struct printfmt currfmt = {
				false, //leftAdjust
				false, //alternateForm
				false, //lowerCase
				0, //sign
				' ', //pad
				0, //width
				0, //precision
				0 //size
			};
			while(true) {
				curr = *fmt++;
				switch(curr) {
					case '%':
						fd->putc(fd, '%');
						written++;
						goto end_outer;
					case '-':
						currfmt.leftAdjust = true;
						break;
					case '+':
						currfmt.sign = '+';
						break;
					case '#':
						currfmt.alternateForm = true;
						break;
					case ' ':
						currfmt.sign = ' ';
						break;
					case '0':
						currfmt.pad = '0';
						break;
					case 'h':
						if(*fmt == 'h') {
							currfmt.size = -2; //char
							fmt++;
						}
						else {
							currfmt.size = -1; //short
						}
						break;
					case 'l':
						if(*fmt == 'l') {
							currfmt.size = 2; //long long
							fmt++;
						}
						else {
							currfmt.size = 1; //long
						}
						break;
					case 'd':
					case 'i':
						written += vfprintInt(fd, ap, &currfmt);
						goto end_outer;
					case 'o':
						written += vfprintUint(fd, ap, &currfmt, 8);
						goto end_outer;
					case 'u':
						written += vfprintUint(fd, ap, &currfmt, 10);
						goto end_outer;
					case 'x':
						currfmt.lowerCase = true;
					case 'X':
						written += vfprintUint(fd, ap, &currfmt, 16);
						goto end_outer;
					case 'c':
						fd->putc(fd, va_arg(ap, int) & 0xFF);
						goto end_outer;
					case 's':
						written += fprintString(fd, va_arg(ap, char*), &currfmt);
						goto end_outer;
					case 'p':
						currfmt.size = 3;
						currfmt.alternateForm = true;
						written += 2 + vfprintUint(fd, ap, &currfmt, 16);
						goto end_outer;
					case 'n':
						*va_arg(ap, int*) = written;
						goto end_outer;
					case '.':
						if(isdigit(*fmt))
							currfmt.precision = strtol(fmt, &fmt, 10);
						else if(*fmt != '*')
							currfmt.precision = 0;
						else if(*fmt++ == '*')
							currfmt.precision = va_arg(ap, int);
						break;
					case '*':
						currfmt.width = va_arg(ap, int);
						break;
					default:
						if(isdigit(curr))
							currfmt.width = strtol(fmt - 1, &fmt, 10);
						else
							return -1;
						break;
				}
			}
			end_outer:
			;
		}
	}

	fd->putc(fd, 0);
	return written;
}
