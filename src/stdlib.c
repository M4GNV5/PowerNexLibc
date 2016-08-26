#include "include/stdlib.h"
#include "include/syscall.h"

static unsigned int seed = 1;
int rand()
{
	seed = (seed * 214013 + 2531011) % 32768;
	return seed;
}
void srand(unsigned int _seed)
{
	seed = _seed;
}

int abs(int n)
{
	return n < 0 ? -n : n;
}
long labs(long n)
{
	return n < 0 ? -n : n;
}

div_t div(int num, int denom)
{
	div_t result = {num / denom, num % denom};
	return result;
}
ldiv_t ldiv(long num, long denom)
{
	ldiv_t result = {num / denom, num % denom};
	return result;
}



struct exitHandler
{
	atexit_callback func;
	void *data;
	struct exitHandler *next;
};
struct exitHandler *exitHandlers;
int atexit_data(atexit_callback func, void *data)
{
	struct exitHandler *entry = malloc(sizeof(struct exitHandler));
	if(entry == NULL)
		return 1;

	entry->func = func;
	entry->data = data;
	entry->next = exitHandlers;
	exitHandlers = entry;
	return 0;
}
int atexit(atexit_callback func)
{
	return atexit_data((void *)func, NULL);
}

void exit(int status)
{
	struct exitHandler *curr = exitHandlers;
	while(curr != NULL)
	{
		curr->func(curr->data);
		curr = curr->next;
	}

	syscall_exit(status & 0xFF);
}

void abort()
{
	syscall_exit(EXIT_FAILURE);
}
