.macro syscall name, id
.global syscall_\name
.type syscall_\name, %function
syscall_\name:
	movq $\id, %rax
	int $0x80
	ret
.endm

SYSCALL exit, 0
SYSCALL clone, 1
SYSCALL fork, 2
SYSCALL yield, 3
SYSCALL exec, 4
SYSCALL alloc, 5
SYSCALL free, 6
SYSCALL realloc, 7
SYSCALL nputs, 15
SYSCALL puts, 16
