#include <stddef.h>
#include "include/syscall.h"
#include "include/string.h"

//
//TODO wait for a syscall to allocate/map whole page and use a userspace buddy allocator
//
size_t malloc_size(void *ptr)
{
	return *(size_t *)(ptr - sizeof(size_t));
}

void *malloc(size_t size)
{
	void *ptr = syscall_alloc(size + sizeof(size_t));
	*(size_t *)ptr = size;
	return ptr + sizeof(size_t);
}

void* calloc(size_t nobj, size_t objsize)
{
	size_t size = nobj * objsize;
	void *ptr = syscall_alloc(size + sizeof(size_t)) + sizeof(size_t);
	*(size_t *)(ptr - sizeof(size_t)) = size;
	memset(ptr, 0, size);
	return ptr;
}

void *realloc(void *ptr, size_t size)
{
	size_t oldSize = *(size_t *)(ptr - sizeof(size_t));
	if(size < oldSize)
		return ptr;

	void *newptr = malloc(size);
	memcpy(newptr, ptr, oldSize);
	syscall_free(ptr - sizeof(size_t));
	return newptr;
}

void free(void *ptr)
{
	syscall_free(ptr - sizeof(size_t));
}
