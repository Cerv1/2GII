.section .data
.macro linea
		.int 1,1,1,1
	#	.int 2,2,2,2
	#	.int 1,2,3,4
	#	.int -1,-1,-1,-1
	# 	.int 0xffffffff,0xffffffff,0xffffffff,0xffffffff	
	# 	.int 0x08000000,0x08000000,0x08000000,0x08000000
	#	.int 0x10000000,0x10000000,0x10000000,0x10000000

.endm

lista:	.irpc i,12345678
		linea
	.endr

longlista:	.int (.-lista)/4
formato:	.ascii "suma = %llu = %llx hex\n\0"
resultado:	.quad 0x0123456789ABCDEF

.section .text

main:	.global main
	mov    $lista, %ebx
	mov longlista, %ecx
	call suma
	mov %eax, resultado+4
	
	push resultado+4
	push resultado
	push resultado+4
	push resultado
	push $formato
	call printf
	add $20, %esp	

	mov $1, %eax
	mov $0, %ebx
	int $0x80

suma:	
	mov $0, %eax
	mov $0, %edx
	mov $0, %esi

bucle:
	add (%ebx,%esi,4), %esi
	jnc nocarry
	inc %edx

nocarry:
	inc       %esi
	cmp  %esi,%ecx
	jne bucle

	ret


