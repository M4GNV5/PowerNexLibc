#ifndef _PWRNX_SYSCALL
#define _PWRNX_SYSCALL

#include <stdint.h>

typedef int64_t (*syscall_clone_func)(void *data);

void syscall_exit(uint64_t exitcode);
uint64_t syscall_clone(syscall_clone_func func, void *stack, void *data, const char *name, uint64_t nameLen);
uint64_t syscall_fork();
void syscall_yield();
void syscall_exec(char *file);
void *syscall_alloc(uint64_t size);
void syscall_free(void *ptr);
void *syscall_realloc(void *ptr, uint64_t size);
void syscall_nputs(char *str, uint64_t size);
void syscall_puts(char *str);

#endif
