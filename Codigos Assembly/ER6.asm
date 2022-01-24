Exercício Resolvido 6

	call soma
	jmp	$

soma: 	#5,r6
		mov.b &lb,r10
lb:		add.b &lb+2,r10
		dec r6
		jnz	lb
		ret



lb: .byte	1, 2, 3, 4, 5, 6