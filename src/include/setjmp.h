#ifndef _PWRNX_SETJMP
#define _PWRNX_SETJMP

struct __jmp_buf
{
	void *rip;
	void *rsp;
	void *rbp;
};

typedef struct __jmp_buf jmp_buf[1];

int setjmp(jmp_buf env);
void longjmp(jmp_buf env, int val);

#endif
