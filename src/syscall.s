/* ["RDI", "RSI", "RDX", "R8", "R9", "R10", "R12", "R13", "R14", "R15"] */

.type syscall, %function
syscall:
	push %r12
	push %r13
	push %r14
	push %r15

	mov %r9, %r10
	mov %r8, %r9
	mov %rcx, %r8
	syscall

	pop %r15
	pop %r14
	pop %r13
	pop %r12

	ret



.macro syscall name, id
.global syscall_\name
.type syscall_\name, %function
syscall_\name:
	movq $\id, %rax
	jmp syscall
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
