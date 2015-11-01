.section .data
	.macro linea
		#	.int 1,-2,1,-2
		#	.int 1,2,-3,-4
		#	.int 0x7FFFFFFF,0x7FFFFFFF,0x7FFFFFFF,0x7FFFFFFF
		#	.int 0x80000000,0x80000000,0x80000000,0x80000000
		#	.int 0xF0000000,0xE0000000,0xE0000000,0xD0000000
			.int -1,-1,-1,-1


	.endm
	
	.macro linea0 
		#	.int 0,-1,-1,-1		# 13 lineas con excepciones para la
		#	.int 0,-2,-1,-1		# batería de pruebas.
		#	.int 1,-2,-1,-1
		#	.int 23,-2,-1,-1
		#	.int 32,-2,-1,-1
		#	.int 47,-2,-1,-1
		#	.int 63,-2,-1,-1
		#	.int 64,-2,-1,-1
		#	.int 78,-2,-1,-1
		#	.int 95,-2,-1,-1
		#	.int -31,-2,-1,-1
		#	.int -13,-2,-1,-1
			.int 0,-2,-1,-1
	.endm

lista:		
			linea0	
		.irpc i,1234567#8
			linea
		.endr

longlista:	.int (.-lista)/4
media:  .int 0x89ABCDEF
resto:	.int 0x01234567

formato:	.ascii "media =   %10d \t resto =   %10d \n"
			.ascii "hexadec 0x%010x \t resto = 0x%010x\n\0"


.section .text
main:	.global main
	
	mov    $lista, %ebx
	mov longlista, %ecx
	call suma
	mov %eax, media
	mov %edx, resto
	
	push resto
	push media
	push resto
	push media
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


	mov  %edi, %eax
	mov  %ebp, %edx
	idiv %ecx

	ret

