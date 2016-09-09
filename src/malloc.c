#include <stddef.h>
#include "include/syscall.h"
#include "include/string.h"

//
//TODO wait for a syscall to allocate/map whole page and write a userspace buddy allocator
//

void *malloc(size_t size)
{
	return syscall_alloc(size);
}

void* calloc(size_t nobj, size_t objsize)
{
	size_t size = nobj * objsize;
	void *ptr = syscall_alloc(size);
	memset(ptr, 0, size);
	return ptr;
}

void *realloc(void *ptr, size_t size)
{
	return syscall_realloc(ptr, size);
}

void free(void *ptr)
{
	syscall_free(ptr);
}
