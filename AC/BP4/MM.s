	.file	"MultMatrix.c"
	.section	.rodata.str1.8,"aMS",@progbits,1
	.align 8
.LC0:
	.string	"\n[ERROR] - Debe introducir introducir dimension. \n"
	.align 8
.LC1:
	.string	"\nEl tama\303\261o tiene que ser un valor menor que 5000 y mayor que 0. \n"
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC3:
	.string	"\tTiempo:\t%8.6f\n"
	.section	.text.startup,"ax",@progbits
	.p2align 4,,15
	.globl	main
	.type	main, @function
main:
.LFB21:
	.cfi_startproc
	pushq	%r13
	.cfi_def_cfa_offset 16
	.cfi_offset 13, -16
	pushq	%r12
	.cfi_def_cfa_offset 24
	.cfi_offset 12, -24
	pushq	%rbp
	.cfi_def_cfa_offset 32
	.cfi_offset 6, -32
	pushq	%rbx
	.cfi_def_cfa_offset 40
	.cfi_offset 3, -40
	subq	$40, %rsp
	.cfi_def_cfa_offset 80
	cmpl	$1, %edi
	jle	.L36
	movq	8(%rsi), %rdi
	movl	$10, %edx
	xorl	%esi, %esi
	call	strtol
	leal	-1(%rax), %ebp
	movl	%eax, %r9d
	cmpl	$4998, %ebp
	ja	.L3
	testl	%eax, %eax
	jle	.L37
	leaq	1(%rbp), %r12
	movl	$B, %ebx
	movl	$3, %eax
	movq	%rbx, %rdi
	imulq	$20000, %r12, %r13
	leaq	0(%r13,%rbx), %r8
.L7:
	leal	(%rax,%r9), %esi
	movq	%rdi, %rdx
	movl	%eax, %ecx
	.p2align 4,,10
	.p2align 3
.L6:
	addl	$1, %eax
	movl	%ecx, (%rdx)
	addq	$4, %rdx
	cmpl	%esi, %eax
	movl	%eax, %ecx
	jne	.L6
	addq	$20000, %rdi
	cmpq	%r8, %rdi
	jne	.L7
	movl	$B, %r8d
	movl	$1, %eax
.L8:
	leal	(%rax,%r9), %esi
	movq	%r8, %rdx
	movl	%eax, %ecx
	.p2align 4,,10
	.p2align 3
.L9:
	addl	$1, %eax
	movl	%ecx, (%rdx)
	addq	$4, %rdx
	cmpl	%esi, %eax
	movl	%eax, %ecx
	jne	.L9
	addq	$20000, %r8
	cmpq	%rdi, %r8
	jne	.L8
	movl	$C, %ecx
	leaq	4(,%rbp,4), %rsi
	leaq	0(%r13,%rcx), %rdi
.L11:
	leaq	(%rsi,%rcx), %rdx
	movq	%rcx, %rax
	.p2align 4,,10
	.p2align 3
.L10:
	movl	$0, (%rax)
	addq	$4, %rax
	cmpq	%rdx, %rax
	jne	.L10
	addq	$20000, %rcx
	cmpq	%rdi, %rcx
	jne	.L11
	movq	%rsp, %rsi
	xorl	%edi, %edi
	addq	$A, %r13
	call	clock_gettime
	movq	%rbp, %rax
	leaq	C(,%r12,4), %r9
	imulq	$-20000, %rbp, %rbp
	negq	%rax
	imulq	$20004, %r12, %r11
	leaq	-4(,%rax,4), %r12
	leaq	-20000(%rbp), %r10
	addq	$C, %r11
.L16:
	leaq	(%r12,%r9), %r8
	movq	%r13, %rdi
	.p2align 4,,10
	.p2align 3
.L14:
	movl	(%r8), %esi
	leaq	(%r10,%rdi), %rax
	movq	%rbx, %rcx
	.p2align 4,,10
	.p2align 3
.L13:
	movl	(%rcx), %edx
	addq	$20000, %rax
	addq	$4, %rcx
	imull	-20000(%rax), %edx
	addl	%edx, %esi
	cmpq	%rdi, %rax
	jne	.L13
	movl	%esi, (%r8)
	addq	$4, %r8
	leaq	4(%rax), %rdi
	cmpq	%r9, %r8
	jne	.L14
	addq	$20000, %r9
	addq	$20000, %rbx
	cmpq	%r11, %r9
	jne	.L16
.L17:
	leaq	16(%rsp), %rsi
	xorl	%edi, %edi
	call	clock_gettime
	movq	24(%rsp), %rax
	subq	8(%rsp), %rax
	movl	$.LC3, %edi
	pxor	%xmm0, %xmm0
	pxor	%xmm1, %xmm1
	cvtsi2sdq	%rax, %xmm0
	movq	16(%rsp), %rax
	subq	(%rsp), %rax
	cvtsi2sdq	%rax, %xmm1
	movl	$1, %eax
	divsd	.LC2(%rip), %xmm0
	addsd	%xmm1, %xmm0
	call	printf
	addq	$40, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 40
	xorl	%eax, %eax
	popq	%rbx
	.cfi_def_cfa_offset 32
	popq	%rbp
	.cfi_def_cfa_offset 24
	popq	%r12
	.cfi_def_cfa_offset 16
	popq	%r13
	.cfi_def_cfa_offset 8
	ret
.L37:
	.cfi_restore_state
	movq	%rsp, %rsi
	xorl	%edi, %edi
	call	clock_gettime
	jmp	.L17
.L3:
	movq	stderr(%rip), %rcx
	movl	$.LC1, %edi
	movl	$66, %edx
	movl	$1, %esi
	call	fwrite
	movl	$-1, %edi
	call	exit
.L36:
	movq	stderr(%rip), %rcx
	movl	$.LC0, %edi
	movl	$50, %edx
	movl	$1, %esi
	call	fwrite
	movl	$-1, %edi
	call	exit
	.cfi_endproc
.LFE21:
	.size	main, .-main
	.comm	C,100000000,32
	.comm	B,100000000,32
	.comm	A,100000000,32
	.section	.rodata.cst8,"aM",@progbits,8
	.align 8
.LC2:
	.long	0
	.long	1104006501
	.ident	"GCC: (GNU) 6.1.1 20160501"
	.section	.note.GNU-stack,"",@progbits
