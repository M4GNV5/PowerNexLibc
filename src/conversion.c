#include <stdint.h>
#include <stdbool.h>

#define NULL ((void *)0)

unsigned long strtoul(const char *str, const char **end, int base)
{
	unsigned long val = 0;
	char curr;

	while((curr = *str++) != 0) {
		int step = 37;
		if(curr >= '0' && curr <= '9')
			step = curr - '0';
		else if(curr >= 'A' && curr <= 'Z')
			step = curr - 'A' + 10;
		else if(curr >= 'a' && curr <= 'z')
			step = curr - 'a' + 10;
		else
			break;

		if(step > base)
			break;

		val = val * base + step;
	}

	if(end != NULL)
		*end = str - 1;
	return val;
}

long strtol(const char *str, const char **end, int base)
{
	bool neg = false;
	if(*str == '-') {
		str++;
		neg = true;
	}

	long val = strtoul(str, end, base);

	if(neg)
		return -val;
	else
		return val;
}

int atoi(const char *str)
{
	return strtol(str, NULL, 10);
}

long atol(const char *str)
{
	return strtol(str, NULL, 10);
}

const char lowerItoaChars[] = "0123456789abcdefghijklmnopqrstuvwxyz";
const char upperItoaChars[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
int utoa(uint64_t val, char *str, int base, bool lowerCase)
{
	if(val == 0) {
		str[0] = '0';
		str[1] = 0;
		return 1;
	}

	int len = 1;
	uint64_t _val = val;
	const char *itoaChars = lowerCase ? lowerItoaChars : upperItoaChars;

	while((_val /= base) > 0)
		len++;

	_val = val;
	str = str + len;
	*str-- = 0;

	while(_val > 0) {
		*str-- = itoaChars[_val % base];
		_val /= base;
	}
	return len;
}
int itoa(int64_t val, char *str, char sign)
{
	if(val < 0) {
		*str = '-';
		return 1 + utoa(-val, str + 1, 10, true);
	}
	else {
		if(sign != 0)
			*str++ = sign;
		return utoa(val, str, 10, true) + (sign == 0 ? 0 : 1);
	}
}

double strtod(const char *str, const char **end)
{
	double val = strtol(str, &str, 10);
	if(*str == '.') {
		char curr = *str++;
		int exp = 10;
		while(curr >= '0' && curr <= '9') {
			val += (curr - '0') / exp;
			exp *= 10;
			curr = *str++;
		}
	}
	/*else if(*str == 'e') {
		long exp = strtol(++str, &str, 10);
		val = pow(val, exp); //TODO implement math.h 's pow
	}*/

	if(end != NULL)
		*end = str;
	return val;
}

double atof(const char *str)
{
	return strtod(str, NULL);
}
