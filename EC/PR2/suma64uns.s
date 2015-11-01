.section .data
.macro linea

	#	.int 1,1,1,1		#Comprobado - d 32 / h 20
	#	.int 2,2,2,2		#Comprobado - d 64 / h 40
	#	.int 1,2,3,4		#Comprobado - d 80 / h 50
	#	.int -1,-1,-1,-1	#Comprobado - d 137438953440 / h 1fffffffe0
	# 	.int 0x80000000,0x80000000,0x80000000,0x80000000  #Comprobado - d 68719476736 / h 1000000000
		.int 0x10000000,0x10000000,0x10000000,0x10000000  #Comprobado - d 8589934592  / h 200000000

.endm

lista:	.irpc i,12345678
		linea
	.endr

longlista:	.int (.-lista)/4
formato:	.ascii "suma = %llu = %llx hex\n\0"
resultado:	.quad 0x0123456789ABCDEF

.section .text

main:	.global main

	mov	   $lista, %ebx
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
	mov $0, %eax
	mov $0, %edx
	mov $0, %esi

bucle:
	add (%ebx,%esi,4), %eax
	jnc nocarry
	inc %edx

nocarry:
	inc       %esi
	cmp  %esi,%ecx
	jne bucle
	ret


