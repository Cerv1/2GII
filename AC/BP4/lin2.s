	.file	"Linpack.c"
	.section	.rodata.str1.8,"aMS",@progbits,1
	.align 8
.LC0:
	.string	"\n[ERROR] - Debe introducir introducir dimension. \n"
	.align 8
.LC1:
	.string	"\n[ERROR] - El tama\303\261o tiene que ser un valor mayor que 0. \n"
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC2:
	.string	"INICIO"
.LC3:
	.string	"FIN"
.LC5:
	.string	"\tTiempo:\t%8.6f\n"
	.section	.text.startup,"ax",@progbits
	.p2align 4,,15
	.globl	main
	.type	main, @function
main:
.LFB21:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%r13
	pushq	%r12
	pushq	%rbx
	subq	$40, %rsp
	.cfi_offset 13, -24
	.cfi_offset 12, -32
	.cfi_offset 3, -40
	cmpl	$1, %edi
	jle	.L10
	movq	8(%rsi), %rdi
	movl	$10, %edx
	xorl	%esi, %esi
	call	strtol
	movslq	%eax, %rdx
	movl	%eax, %r12d
	leaq	18(,%rdx,4), %rdx
	shrq	$4, %rdx
	salq	$4, %rdx
	subq	%rdx, %rsp
	movq	%rsp, %r13
	subq	%rdx, %rsp
	testl	%eax, %eax
	movq	%rsp, %rbx
	jle	.L11
	xorl	%edx, %edx
	xorl	%eax, %eax
	.p2align 4,,10
	.p2align 3
.L4:
	movl	%edx, (%rbx,%rax,4)
	movl	%eax, 0(%r13,%rax,4)
	addq	$1, %rax
	addl	$3, %edx
	cmpl	%eax, %r12d
	jg	.L4
	leaq	-64(%rbp), %rsi
	xorl	%edi, %edi
	call	clock_gettime
	movl	$.LC2, %edi
	call	puts
	xorl	%eax, %eax
	.p2align 4,,10
	.p2align 3
.L5:
	movl	0(%r13,%rax,4), %edx
	leal	(%rdx,%rdx,4), %edx
	addl	%edx, (%rbx,%rax,4)
	addq	$1, %rax
	cmpl	%eax, %r12d
	jg	.L5
	movl	$.LC3, %edi
	call	puts
	leaq	-48(%rbp), %rsi
	xorl	%edi, %edi
	call	clock_gettime
	movq	-40(%rbp), %rax
	subq	-56(%rbp), %rax
	movl	$.LC5, %edi
	pxor	%xmm0, %xmm0
	pxor	%xmm1, %xmm1
	cvtsi2sdq	%rax, %xmm0
	movq	-48(%rbp), %rax
	subq	-64(%rbp), %rax
	cvtsi2sdq	%rax, %xmm1
	movl	$1, %eax
	divsd	.LC4(%rip), %xmm0
	addsd	%xmm1, %xmm0
	call	printf
	leaq	-24(%rbp), %rsp
	xorl	%eax, %eax
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%rbp
	.cfi_remember_state
	.cfi_def_cfa 7, 8
	ret
.L10:
	.cfi_restore_state
	movq	stderr(%rip), %rcx
	movl	$.LC0, %edi
	movl	$50, %edx
	movl	$1, %esi
	call	fwrite
	orl	$-1, %edi
	call	exit
.L11:
	movq	stderr(%rip), %rcx
	movl	$.LC1, %edi
	movl	$59, %edx
	movl	$1, %esi
	call	fwrite
	orl	$-1, %edi
	call	exit
	.cfi_endproc
.LFE21:
	.size	main, .-main
	.section	.rodata.cst8,"aM",@progbits,8
	.align 8
.LC4:
	.long	0
	.long	1104006501
	.ident	"GCC: (GNU) 6.1.1 20160501"
	.section	.note.GNU-stack,"",@progbits
