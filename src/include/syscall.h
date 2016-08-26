#ifndef _PWRNX_SYSCALL
#define _PWRNX_SYSCALL

#include <stdint.h>

typedef int64_t (*syscall_clone_func)(void *data);

void syscall_exit(int64_t exitcode);
int64_t syscall_clone(syscall_clone_func func, void *stack, void *data, const char *name);
int64_t syscall_fork();
void syscall_yield();
void syscall_exec(char *file);
void *syscall_alloc(int64_t size);
void syscall_free(void *ptr);
void syscall_puts(char *str);

#endif
