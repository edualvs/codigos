;-------------------------------------------------------------------------------
; MSP430 Assembler Code Template for use with TI Code Composer Studio
;
;
;-------------------------------------------------------------------------------
            .cdecls C,LIST,"msp430.h"       ; Include device header file
            
;-------------------------------------------------------------------------------
            .def    RESET                   ; Export program entry-point to
                                            ; make it known to linker.
;-------------------------------------------------------------------------------
            .text                           ; Assemble into program memory.
            .retain                         ; Override ELF conditional linking
                                            ; and retain current section.
            .retainrefs                     ; And retain any sections that have
                                            ; references to current section.

;-------------------------------------------------------------------------------
RESET       mov.w   #__STACK_END,SP         ; Initialize stackpointer
StopWDT     mov.w   #WDTPW|WDTHOLD,&WDTCTL  ; Stop watchdog timer


;-------------------------------------------------------------------------------
; Main loop here
;-------------------------------------------------------------------------------

;EXERCÍCIO 1 - LAB SIS  MIC


;		mov	#vetor,r5
;		call #menor
;		jmp $
;
;
;menor: 	mov.b @r5,r8
;		mov.b #255,r6
;		mov.b #1,r7
;loop:	inc r5
;		cmp.b @r5,r6
	;	jhs lb_menor
	;	dec r8
;;		jnz loop
;		ret
;lb_menor:	cmp.b @r5,r6
;			jeq lb_igual
;lb_menor2:	mov.b @r5,r6
;
;			dec r8
;			jnz loop
;lb_igual:  inc r7
;			jmp lb_menor2




;EXERCÍCIO 2 - LAB SIS  MIC
;		mov #vetor,r5
;		call #maior
;		jmp $

;maior:
	;	mov @r5,r8
	;	mov #0,r6
;loop:	incd r5
;		cmp @r5,r6
;		jlo	lb_maior
;		dec r8
;		jnz loop
;		ret
;lb_maior:
;;		mov @r5,r6
;		dec r8
;		jnz loop
;	ret


;EXERCÍCIO 3 - LAB SIS  MIC

;		mov #vetor,r5
	;	call #m2m4
	;	jmp $

;m2m4:
	;	clr r6
	;	clr r7
	;	inc r5
;loop:	sub #2,0(r5)
	;	add #1,r7
	;	tst 0(r5)
	;	jnz loop
	;	ret


	;EXERCÍCIO 4 - LAB SIS  MIC
 	;		mov #vetor,R5
		;	call #EXTREMOS
		;	jmp $

;EXTREMOS:
	;		mov @R5,R8
		;	incd R5
		;	mov @R5,R6
		;	mov @R5,R7
		;	incd R5

;loop:
	;		cmp @R5,R7
	;		jl	maior
;lb1:		cmp @R5,R6
;			jge menor
;lb2:		incd R5
;;			dec R8
;			jnz loop
;			ret

;maior: 		mov @R5,R7
;			jmp lb1

;menor: 		mov @R5,R6
	;		jmp lb2
	;		nop






	;EXERCÍCIO 5 - LAB SIS  MIC

;		mov #Vetor1,R5
;		mov #Vetor2,R6
;		call #SUM16
;		jmp $

;SUM16:
;		mov @R5,R10
;		mov #0x2420,R7
;		incd R5
;		incd R6
;loop:
;		mov @R5,R8
;		mov @R6,R9
;		add R8,R9
;		mov R9,0(R7)
;		incd R5
;;		incd R6
	;	incd R7
	;	dec R10
	;	jnz loop
	;	ret



		;EXERCÍCIO 6 - LAB SIS  MIC

;			mov		#Vetor1,R5
;			mov 	#Vetor2,R6
;			call 	#SUM_TOT
;			jmp 	$

;SUM_TOT:
;			mov @R5,R9
;			clr R7
;			clr R8
;			incd R5
;loop:		add @R5,R7
;			adc R8
;			incd R5
;			dec R9
;;			jnz loop
	;		mov @R6,R9
	;		incd R6
;loop1:		add @R6,R7
;			adc R8
;			incd R6
;			dec R9
;;			jnz loop1
;			ret




		;EXERCÍCIO 7 - LAB SIS  MIC

;			call 	#FIB
;			jmp 	$

;FIB:
;			mov #18,R7
;			mov #0x2400,R5
;			mov #1,0(R5)
;			incd R5
;			mov #1,0(R5)
;			clr R6
;loop:		add -1(R5),R6
;			add 0(R5),R6
;			incd R5
;			mov R6,0(R5)
;			clr R6
;			dec R7
;			jnz loop
;			ret



		;EXERCÍCIO 8 - LAB SIS  MIC

;			call 	#FIB16
;			jmp 	$

;FIB16:
;			mov #0x2400,R5
;			mov #1,0(R5)
;;			incd R5
	;		mov #1,0(R5)
	;		clr R10
;loop:
;			add -1(R5),R10
;			add 0(R5),R10
;			jc	fim
;			incd R5
;			mov R10,0(R5)
;			clr R10
;			jmp loop

;fim: 		mov @R5,R10
	;		ret


	;EXERCÍCIO 9 - LAB SIS  MIC
;		call #FIB32
;		jmp $

;FIB32:
;		mov #1,R5
;		mov #1,R6
;		clr R11
;fibo:	mov R5,R10
;		add R6,R10
;		adc R11
;		jc	fim
;
;		mov R6,R5
;		mov R10,R6
;		jmp	fibo

;fim:	dec	R11
;		ret



			;PROVA A1 2020/1
;		mov #SEQTRIB,R5
 ;		call #TRIB
 ;		jmp $

;TRIB:
;		mov #3,R6
;		incd	R5
;		incd	R5
;		incd	R5
;loop:	add -6(R5),0(R5)
;		add -4(R5),0(R5)
;		add -4(R5),0(R5)
;		sub -2(R5),0(R5)
;		sub -2(R5),0(R5)
;		sub -2(R5),0(R5)
;		cmp #500,0(R5)
;		jge fim
;		inc R6
;		incd R5
;		jmp loop
;
;fim:	mov @R5,R7
;		ret
;
;
 	.data

SEQTRIB: .word 1, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
 .word 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
 .word 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0











	.data
; Declarar vetor com 8 elementos [121, 234, 567, -1990, 117, 867, 45, -1980]
vetor: .word 8, 121, 234, 567, -1990, 117, 867, 45, -1980


;-------------------------------------------------------------------------------
; Stack Pointer definition
;-------------------------------------------------------------------------------
            .global __STACK_END
            .sect   .stack
            
;-------------------------------------------------------------------------------
; Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect   ".reset"                ; MSP430 RESET Vector
            .short  RESET
            
