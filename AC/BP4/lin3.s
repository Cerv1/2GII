	.file	"Linpack.c"
	.section	.rodata.str1.8,"aMS",@progbits,1
	.align 8
.LC0:
	.string	"\n[ERROR] - Debe introducir introducir dimension. \n"
	.align 8
.LC1:
	.string	"\n[ERROR] - El tama\303\261o tiene que ser un valor mayor que 0. \n"
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC4:
	.string	"INICIO"
.LC5:
	.string	"FIN"
.LC7:
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
	pushq	%r14
	pushq	%r13
	pushq	%r12
	pushq	%rbx
	subq	$48, %rsp
	.cfi_offset 14, -24
	.cfi_offset 13, -32
	.cfi_offset 12, -40
	.cfi_offset 3, -48
	cmpl	$1, %edi
	jle	.L43
	movq	8(%rsi), %rdi
	movl	$10, %edx
	xorl	%esi, %esi
	call	strtol
	movq	%rax, %rbx
	cltq
	leaq	18(,%rax,4), %rax
	shrq	$4, %rax
	salq	$4, %rax
	subq	%rax, %rsp
	leaq	3(%rsp), %r13
	subq	%rax, %rsp
	leaq	3(%rsp), %rdx
	shrq	$2, %r13
	shrq	$2, %rdx
	testl	%ebx, %ebx
	leaq	0(,%r13,4), %r14
	leaq	0(,%rdx,4), %r12
	jle	.L44
	movq	%r14, %rax
	shrq	$2, %rax
	negq	%rax
	andl	$3, %eax
	cmpl	%ebx, %eax
	cmova	%ebx, %eax
	cmpl	$6, %ebx
	cmovbe	%ebx, %eax
	testl	%eax, %eax
	je	.L21
	cmpl	$1, %eax
	movl	$0, 0(,%r13,4)
	movl	$0, 0(,%rdx,4)
	je	.L22
	cmpl	$2, %eax
	movl	$1, 4(,%r13,4)
	movl	$3, 4(,%rdx,4)
	je	.L23
	cmpl	$3, %eax
	movl	$2, 8(,%r13,4)
	movl	$6, 8(,%rdx,4)
	je	.L24
	cmpl	$4, %eax
	movl	$3, 12(,%r13,4)
	movl	$9, 12(,%rdx,4)
	je	.L25
	cmpl	$6, %eax
	movl	$4, 16(,%r13,4)
	movl	$12, 16(,%rdx,4)
	jne	.L26
	movl	$15, 20(,%rdx,4)
	movl	$5, 20(,%r13,4)
	movl	$6, %edx
.L6:
	cmpl	%eax, %ebx
	je	.L45
.L5:
	movl	%ebx, %r8d
	leal	-1(%rbx), %edi
	movl	%eax, %esi
	subl	%eax, %r8d
	leal	-4(%r8), %ecx
	subl	%eax, %edi
	shrl	$2, %ecx
	addl	$1, %ecx
	cmpl	$2, %edi
	leal	0(,%rcx,4), %r9d
	jbe	.L8
	movl	%edx, -68(%rbp)
	salq	$2, %rsi
	xorl	%eax, %eax
	movd	-68(%rbp), %xmm4
	leaq	(%r14,%rsi), %r10
	xorl	%edi, %edi
	movdqa	.LC3(%rip), %xmm2
	addq	%r12, %rsi
	pshufd	$0, %xmm4, %xmm0
	paddd	.LC2(%rip), %xmm0
.L9:
	movdqa	%xmm0, %xmm1
	addl	$1, %edi
	movdqa	%xmm0, %xmm3
	movaps	%xmm0, (%r10,%rax)
	pslld	$1, %xmm1
	paddd	%xmm1, %xmm0
	paddd	%xmm2, %xmm3
	movups	%xmm0, (%rsi,%rax)
	addq	$16, %rax
	cmpl	%edi, %ecx
	jbe	.L46
	movdqa	%xmm3, %xmm0
	jmp	.L9
.L46:
	addl	%r9d, %edx
	cmpl	%r9d, %r8d
	je	.L11
.L8:
	leal	(%rdx,%rdx,2), %ecx
	movslq	%edx, %rax
	movl	%edx, (%r14,%rax,4)
	movl	%ecx, (%r12,%rax,4)
	leal	1(%rdx), %eax
	cmpl	%eax, %ebx
	jle	.L11
	movslq	%eax, %rcx
	movl	%eax, (%r14,%rcx,4)
	leal	(%rax,%rax,2), %eax
	movl	%eax, (%r12,%rcx,4)
	leal	2(%rdx), %eax
	cmpl	%eax, %ebx
	jle	.L11
	movslq	%eax, %rdx
	movl	%eax, (%r14,%rdx,4)
	leal	(%rax,%rax,2), %eax
	movl	%eax, (%r12,%rdx,4)
.L11:
	leaq	-64(%rbp), %rsi
	xorl	%edi, %edi
	call	clock_gettime
	movl	$.LC4, %edi
	call	puts
	movq	%r12, %rax
	shrq	$2, %rax
	negq	%rax
	andl	$3, %eax
	cmpl	%ebx, %eax
	cmova	%ebx, %eax
	cmpl	$4, %ebx
	cmovbe	%ebx, %eax
.L13:
	testl	%eax, %eax
	je	.L47
.L20:
	movl	0(,%r13,4), %edx
	movl	$1, %ecx
	leal	(%rdx,%rdx,4), %edx
	addl	%edx, (%r12)
	cmpl	$1, %eax
	je	.L15
	movl	4(,%r13,4), %edx
	movl	$2, %ecx
	leal	(%rdx,%rdx,4), %edx
	addl	%edx, 4(%r12)
	cmpl	$2, %eax
	je	.L15
	movl	8(,%r13,4), %edx
	movl	$3, %ecx
	leal	(%rdx,%rdx,4), %edx
	addl	%edx, 8(%r12)
	cmpl	$4, %eax
	jne	.L15
	movl	12(,%r13,4), %edx
	movl	$4, %ecx
	leal	(%rdx,%rdx,4), %edx
	addl	%edx, 12(%r12)
.L15:
	cmpl	%eax, %ebx
	je	.L16
.L14:
	movl	%ebx, %r8d
	leal	-1(%rbx), %edi
	movl	%eax, %edx
	subl	%eax, %r8d
	leal	-4(%r8), %esi
	subl	%eax, %edi
	shrl	$2, %esi
	addl	$1, %esi
	cmpl	$2, %edi
	leal	0(,%rsi,4), %r9d
	jbe	.L17
	leaq	0(,%rdx,4), %rax
	xorl	%edi, %edi
	xorl	%edx, %edx
	leaq	(%r14,%rax), %r10
	addq	%r12, %rax
.L18:
	movdqu	(%r10,%rdx), %xmm1
	addl	$1, %edi
	movdqa	%xmm1, %xmm0
	pslld	$2, %xmm0
	paddd	%xmm1, %xmm0
	paddd	(%rax,%rdx), %xmm0
	movaps	%xmm0, (%rax,%rdx)
	addq	$16, %rdx
	cmpl	%edi, %esi
	ja	.L18
	addl	%r9d, %ecx
	cmpl	%r9d, %r8d
	je	.L16
.L17:
	movslq	%ecx, %rax
	imull	$5, (%r14,%rax,4), %edx
	addl	%edx, (%r12,%rax,4)
	leal	1(%rcx), %eax
	cmpl	%eax, %ebx
	jle	.L16
	cltq
	imull	$5, (%r14,%rax,4), %edx
	addl	%edx, (%r12,%rax,4)
.L16:
	movl	$.LC5, %edi
	call	puts
	leaq	-48(%rbp), %rsi
	xorl	%edi, %edi
	call	clock_gettime
	movq	-40(%rbp), %rax
	subq	-56(%rbp), %rax
	movl	$.LC7, %edi
	pxor	%xmm0, %xmm0
	pxor	%xmm1, %xmm1
	cvtsi2sdq	%rax, %xmm0
	movq	-48(%rbp), %rax
	subq	-64(%rbp), %rax
	cvtsi2sdq	%rax, %xmm1
	movl	$1, %eax
	divsd	.LC6(%rip), %xmm0
	addsd	%xmm1, %xmm0
	call	printf
	leaq	-32(%rbp), %rsp
	xorl	%eax, %eax
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%rbp
	.cfi_remember_state
	.cfi_def_cfa 7, 8
	ret
.L45:
	.cfi_restore_state
	leaq	-64(%rbp), %rsi
	xorl	%edi, %edi
	call	clock_gettime
	movl	$.LC4, %edi
	call	puts
	movq	%r12, %rax
	shrq	$2, %rax
	negq	%rax
	andl	$3, %eax
	cmpl	%ebx, %eax
	cmova	%ebx, %eax
	cmpl	$4, %ebx
	ja	.L13
	movl	%ebx, %eax
	jmp	.L20
.L21:
	xorl	%edx, %edx
	jmp	.L5
.L47:
	xorl	%ecx, %ecx
	jmp	.L14
.L22:
	movl	$1, %edx
	jmp	.L6
.L23:
	movl	$2, %edx
	jmp	.L6
.L24:
	movl	$3, %edx
	jmp	.L6
.L25:
	movl	$4, %edx
	jmp	.L6
.L26:
	movl	$5, %edx
	jmp	.L6
.L44:
	movq	stderr(%rip), %rcx
	movl	$.LC1, %edi
	movl	$59, %edx
	movl	$1, %esi
	call	fwrite
	orl	$-1, %edi
	call	exit
.L43:
	movq	stderr(%rip), %rcx
	movl	$.LC0, %edi
	movl	$50, %edx
	movl	$1, %esi
	call	fwrite
	orl	$-1, %edi
	call	exit
	.cfi_endproc
.LFE21:
	.size	main, .-main
	.section	.rodata.cst16,"aM",@progbits,16
	.align 16
.LC2:
	.long	0
	.long	1
	.long	2
	.long	3
	.align 16
.LC3:
	.long	4
	.long	4
	.long	4
	.long	4
	.section	.rodata.cst8,"aM",@progbits,8
	.align 8
.LC6:
	.long	0
	.long	1104006501
	.ident	"GCC: (GNU) 6.1.1 20160501"
	.section	.note.GNU-stack,"",@progbits
