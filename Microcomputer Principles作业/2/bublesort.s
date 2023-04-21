	.file	"bublesort.c"
	.text
	.globl	bubble_sort
	.type	bubble_sort, @function
bubble_sort:
.LFB0:
	.cfi_startproc
	movl	$0, %r10d
	jmp	.L2
.L3:
	addl	$1, %edx
.L5:
	movl	%esi, %eax
	subl	%r10d, %eax
	subl	$1, %eax
	cmpl	%edx, %eax
	jle	.L7
	movslq	%edx, %rax
	leaq	(%rdi,%rax,4), %r8
	movl	(%r8), %ecx
	leaq	4(%rdi,%rax,4), %rax
	movl	(%rax), %r9d
	cmpl	%r9d, %ecx
	jle	.L3
	movl	%r9d, (%r8)
	movl	%ecx, (%rax)
	jmp	.L3
.L7:
	addl	$1, %r10d
.L2:
	leal	-1(%rsi), %eax
	cmpl	%r10d, %eax
	jle	.L8
	movl	$0, %edx
	jmp	.L5
.L8:
	ret
	.cfi_endproc
.LFE0:
	.size	bubble_sort, .-bubble_sort
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"%d"
.LC1:
	.string	"%d\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB1:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%r12
	pushq	%rbx
	subq	$16, %rsp
	.cfi_offset 12, -24
	.cfi_offset 3, -32
	movq	%fs:40, %rax
	movq	%rax, -24(%rbp)
	xorl	%eax, %eax
	leaq	-32(%rbp), %rsi
	leaq	.LC0(%rip), %rdi
	call	scanf@PLT
	movslq	-32(%rbp), %rax
	leaq	15(,%rax,4), %rax
	andq	$-16, %rax
	subq	%rax, %rsp
	movq	%rsp, %r12
	movl	$0, %ebx
	jmp	.L10
.L11:
	leaq	-28(%rbp), %rsi
	leaq	.LC0(%rip), %rdi
	movl	$0, %eax
	call	scanf@PLT
	movslq	%ebx, %rax
	movl	-28(%rbp), %edx
	movl	%edx, (%r12,%rax,4)
	addl	$1, %ebx
.L10:
	movl	-32(%rbp), %esi
	cmpl	%ebx, %esi
	jg	.L11
	movq	%r12, %rdi
	call	bubble_sort
	movl	$0, %ebx
	jmp	.L12
.L13:
	movslq	%ebx, %rax
	movl	(%r12,%rax,4), %esi
	leaq	.LC1(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	addl	$1, %ebx
.L12:
	cmpl	%ebx, -32(%rbp)
	jg	.L13
	movq	-24(%rbp), %rax
	subq	%fs:40, %rax
	jne	.L16
	movl	$0, %eax
	leaq	-16(%rbp), %rsp
	popq	%rbx
	popq	%r12
	popq	%rbp
	.cfi_remember_state
	.cfi_def_cfa 7, 8
	ret
.L16:
	.cfi_restore_state
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE1:
	.size	main, .-main
	.ident	"GCC: (GNU) 12.2.1 20230201"
	.section	.note.GNU-stack,"",@progbits
