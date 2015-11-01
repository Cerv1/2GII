.section .data
.macro linea
	#	.int -1,-1,-1,-1	#Comprobado - d -32 / h ffffffffffffffe0
	#	.int 1,-2,1,-2		#Comprobado - d -16 / h fffffffffffffff0
	#	.int 1,2,-3,-4		#Comprobado - d -32 / h ffffffffffffffe0
	#	.int 0x7fffffff,0x7fffffff,0x7fffffff,0x7fffffff  #Comprobado - d 68719476704 / h fffffffe0
	#	.int 0x80000000,0x80000000,0x80000000,0x80000000  #Comprobado - d -68719476736 / h fffffff000000000
	#	.int 0x04000000,0x04000000,0x04000000,0x04000000  #Comprobado - d 2147483648 / h 80000000
	#	.int 0x08000000,0x08000000,0x08000000,0x08000000  #Comprobado - d 4294967296 / h 100000000
	#	.int 0xFC000000,0xFC000000,0xFC000000,0xFC000000  #Comprobado - d -2147483648 / h ffffffff80000000
	#	.int 0xF8000000,0xF8000000,0xF8000000,0xF8000000  #Comprobado - d -4294967296 / h ffffffff00000000
		.int 0xF0000000,0xE0000000,0xE0000000,0xD0000000  #Comprobado - d -17179869184 / h fffffffc00000000

.endm

lista:	.irpc i,12345678
		linea
	.endr

longlista:	.int (.-lista)/4
formato:	.ascii "suma = %lld = %llx hex\n\0"
resultado:	.quad 0x0123456789ABCDEF

.section .text

main:	.global main

	mov    $lista, %ebx
	mov longlista, %ecx
	call suma
	mov %eax, resultado
	mov %edx, resultado+4

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
	mov $0, %edi
	mov $0, %ebp
	mov $0, %esi

bucle:
	mov (%ebx,%esi,4), %eax
	cltd
	add %eax, %edi
	adc %edx, %ebp
	inc %esi
	cmp %esi, %ecx
	jne bucle
	mov %edi, %eax
	mov %ebp, %edx
	ret
