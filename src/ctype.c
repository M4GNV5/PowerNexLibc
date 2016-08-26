int isdigit(int c)
{
	return c >= '0' && c <= '9';
}
int isalpha(int c)
{
	return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}
int isalnum(int c)
{
	return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9');
}
int isxdigit(int c)
{
	return (c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

int isgraph(int c)
{
	return c > ' ' && c <= '~';
}
int isspace(int c)
{
	return c == ' ' || (c >= 9 && c <= 13);
}
int isprint(int c)
{
	return c >= ' ' && c <= '~';
}

int ispunct(int c)
{
	return isprint(c) && !isalnum(c);
}
int iscntrl(int c)
{
	return c <= 31 || c == 127;
}

int islower(int c)
{
	return c >= 'a' && c <= 'z';
}
int isupper(int c)
{
	return c >= 'A' && c <= 'Z';
}
int tolower(int c)
{
	return c - 'A' + 'a';
}
int toupper(int c)
{
	return c - 'a' + 'A';
}
