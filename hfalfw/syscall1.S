.globl __syscall1
.type __syscall1, @function
.align 16
__syscall1:
	movq %rdi, %rax	/* Syscall number -> rax.  */
	movq %rsi, %rdi	/* Set only arg1 for now */
	/* movq %rdx, %rsi */
	/* movq %rcx, %rdx */
	/* movq %r8, %r10 */
	/* movq %r9, %r8 */
	/* movq 8(%rsp), %r9 */
	syscall
	ret
