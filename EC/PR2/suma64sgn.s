.section .data
.macro linea
	#	.int -1,0		
	#	.int 1,1,1,1		#done
	#	.int 2,2,2,2		#done
	#	.int 1,2,-3,-4		#done
	#	.int -1,-1,-1,-1	#done
	#	.int 1,-2,1,-2
	#	.int 0xffffffff,0xffffffff,0xffffffff,0xffffffff
		.int 0x7fffffff,0x7fffffff,0x7fffffff,0x7fffffff
	#	.int 0x08000000,0x08000000,0x08000000,0x08000000	#done
	#	.int 0x10000000,0x10000000,0x10000000,0x10000000    #done

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


