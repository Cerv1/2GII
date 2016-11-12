	.file	"MultiMatrix-Optimizado.c"
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
	jle	.L39
	movq	8(%rsi), %rdi
	movl	$10, %edx
	xorl	%esi, %esi
	call	strtol
	leal	-1(%rax), %edx
	cmpl	$4998, %edx
	ja	.L3
	testl	%eax, %eax
	jle	.L40
	movl	%edx, %ebx
	movl	%edx, %r8d
	andl	$-4, %edx
	addq	$1, %rbx
	shrl	$2, %r8d
	leal	4(%rdx), %edi
	imulq	$20000, %rbx, %rbp
	leal	0(,%r8,4), %r9d
	movl	$A, %r12d
	movl	$3, %r11d
	leaq	A(%rbp), %r13
.L7:
	leal	(%r11,%rdi), %r10d
	movq	%r12, %rdx
	movl	%r11d, %eax
	.p2align 4,,10
	.p2align 3
.L6:
	movl	%eax, %ecx
	leal	1(%rax), %esi
	movl	%eax, (%rdx)
	addl	$3, %ecx
	addl	$4, %eax
	addq	$16, %rdx
	movl	%esi, -12(%rdx)
	movl	%ecx, -8(%rdx)
	cmpl	%r10d, %eax
	jne	.L6
	addq	$20000, %r12
	leal	4(%r11,%r9), %r11d
	cmpq	%r13, %r12
	jne	.L7
	movl	$B, %r12d
	movl	$1, %r11d
	leaq	0(%rbp,%r12), %r13
.L10:
	leal	(%r11,%rdi), %r10d
	movq	%r12, %rdx
	movl	%r11d, %eax
	.p2align 4,,10
	.p2align 3
.L9:
	leal	1(%rax), %esi
	movl	%eax, %ecx
	movl	%eax, (%rdx)
	addl	$3, %ecx
	addq	$16, %rdx
	movl	%esi, -12(%rdx)
	leal	2(%rax), %esi
	addl	$4, %eax
	movl	%ecx, -4(%rdx)
	movl	%esi, -8(%rdx)
	cmpl	%r10d, %eax
	jne	.L9
	addq	$20000, %r12
	leal	4(%r11,%r9), %r11d
	cmpq	%r13, %r12
	jne	.L10
	imulq	$1250, %rbx, %r9
	movl	%r8d, %r12d
	movl	$C, %esi
	leaq	1(%r12), %rdi
	xorl	%ecx, %ecx
.L12:
	leaq	(%rdi,%rcx), %rdx
	movq	%rsi, %rax
	salq	$4, %rdx
	addq	$C, %rdx
	.p2align 4,,10
	.p2align 3
.L11:
	movl	$0, (%rax)
	movl	$0, 4(%rax)
	addq	$16, %rax
	movl	$0, -8(%rax)
	movl	$0, -4(%rax)
	cmpq	%rdx, %rax
	jne	.L11
	addq	$1250, %rcx
	addq	$20000, %rsi
	cmpq	%rcx, %r9
	jne	.L12
	movq	%rsp, %rsi
	xorl	%edi, %edi
	call	clock_gettime
	imulq	$20000, %r12, %r8
	xorl	%r11d, %r11d
	leaq	20000(%r8), %r12
.L17:
	leaq	B(%r11), %r13
	movl	$A, %r10d
	xorl	%r9d, %r9d
	.p2align 4,,10
	.p2align 3
.L15:
	leaq	(%r12,%r9), %rdx
	movl	C(%r11,%r9,4), %eax
	movq	%r13, %rsi
	movq	%r10, %rcx
	leaq	A(,%rdx,4), %r8
	.p2align 4,,10
	.p2align 3
.L14:
	movl	(%rsi), %edx
	movl	8(%rsi), %edi
	addq	$80000, %rcx
	imull	-80000(%rcx), %edx
	addq	$16, %rsi
	addl	%eax, %edx
	movl	-12(%rsi), %eax
	imull	-60000(%rcx), %eax
	addl	%edx, %eax
	movl	-40000(%rcx), %edx
	imull	%edi, %edx
	imull	-20000(%rcx), %edi
	addl	%edx, %eax
	addl	%edi, %eax
	cmpq	%rcx, %r8
	jne	.L14
	movl	%eax, C(%r11,%r9,4)
	addq	$1, %r9
	addq	$4, %r10
	cmpq	%rbx, %r9
	jne	.L15
	addq	$20000, %r11
	cmpq	%rbp, %r11
	jne	.L17
.L18:
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
.L40:
	.cfi_restore_state
	movq	%rsp, %rsi
	xorl	%edi, %edi
	call	clock_gettime
	jmp	.L18
.L3:
	movq	stderr(%rip), %rcx
	movl	$.LC1, %edi
	movl	$66, %edx
	movl	$1, %esi
	call	fwrite
	movl	$-1, %edi
	call	exit
.L39:
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
