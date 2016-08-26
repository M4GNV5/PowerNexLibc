/* TODO: save callee-saved registers
struct jmp_buf
{
	void *rip;
	void *rsp;
	void *rbp;
}
*/

.global setjmp
.type setjmp, %function
setjmp:
	mov (%rsp), %rax

	mov %rax, (%rdi)
	mov %rsp, 8(%rdi)
	mov %rbp, 16(%rdi)

	mov $0, %eax
	ret

.global longjmp
.type longjmp, %function
longjmp:
	test %esi, %esi
	jnz .dojmp
	mov $1, %esi

.dojmp:
	mov %esi, %eax
	mov 16(%rdi), %rbp
	mov 8(%rdi), %rsp
	jmp *(%rdi)
