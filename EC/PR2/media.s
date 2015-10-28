.section .data
	.macro linea
		#	.int -1,0		
		#	.int 1,1,1,1		#done
		#	.int 2,2,2,2		#done
		#	.int 1,2,3,4		#done
		#	.int -1,-1,-1,-1
		# 	.int 0xffffffff,0xffffffff,0xffffffff,0xffffffff	
		# 	.int 0x08000000,0x08000000,0x08000000,0x08000000
		#	.int 0x10000000,0x10000000,0x10000000,0x10000000

	.endm
	
	.macro linea0 
		#	.int 0,-1,-1,-1		#13 lineas con excepciones
		# 	.int 0,-2,-1,-1
		#	.int ...
	.endm

lista:		linea0	
		.irpc i,1234567#8
			linea
		.endr

longlista:	.int (.-lista)/4
formato:	.ascii "media =   %8d \t resto = 0%8d \n"
		.ascii "hexadec 0x%08x \t resto = 0x%08x\n\0"

media:  0x89ABCDEF
resto:	0x01234567

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
	mov $0, %edx
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


