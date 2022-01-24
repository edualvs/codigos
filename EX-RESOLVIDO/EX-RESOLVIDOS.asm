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
	;ER 2.1
	;mov.w	#0x1234,R5
	;mov.w	#0x4321,R6
	;add.w	R5,R6
	;jmp	$



	;ER 2.2
	;mov.w	#0x1234,R5
	;mov.w	#0x4321,R6
	;add.b	R5,R6
	;jmp	$



	;ER 2.3
	;mov.w	#0xABCD,R5
	;mov.w	#0xDCBA,R6
	;add.W	R5,R6
	;jmp	$


	;ER 2.4
	;mov.b &vetor,R10
	;add.b &0x2401,R10
	;jmp $
	;nop



	;ER 2.5
	;mov.w &vetor,R10
	;add.w &0x2402,R10
	;jmp $
	;nop





	;ER 2.6
	;mov.w &vetor,R10
	;call	#SOMA2
	;jmp $

;SOMA2: add.w &vetor+2,R10
		;ret





	;ER 2.7
	;call #SOMA
	;jmp	$

;SOMA:	clr R10
		;mov #5,R6
		;mov.w #vetor,R7
;loop: 	add.b @R7+,R10
;		dec.b	R6
;		jnz loop
;fim:		ret



	;ER 2.8
	;call #SOMA
	;jmp	$

;SOMA:	clr R10
;		mov #5,R6
;		mov.w #vetor,R7
;loop: 	add.w @R7+,R10
;		dec.w	R6
;		jnz loop
;fim:		ret



	;ER 2.9
	;call #SOMA
	;jmp	$

;SOMA:	clr.w R10
;		clr.w R11
;		mov.w	#5,R6
;		mov.w	#vetor,R5
;LOOP:	add.w 	@R5+,R10
;		adc 	R11
;		incd R5
;		dec.w R6
;		jnz LOOP
;		ret



	;ER 2.10
	;mov #vetor, R6
	;call #soma
	;jmp $

;sum8:
		;mov.b @R6+,R5
		;clr R7

;loop:	add.b @R6+,R7
		;dec R5
		;jnz loop
		;ret




	;ER 2.11
	;	mov #vetor,R5
	;	call #SUM16
		;jmp $

;SUM16:
	;	mov.w @R5+,R6
	;	clr R10

;loop:	add.w @R5+,R10
	;	dec R6
	;	jnz loop
	;	ret




	;ER 2.12
	;	mov #vetor,R5
	;	call #MAIOR8
	;	jmp $

;MAIOR8: mov.b @R5+,R6
	;	clr.b R10
;LOOP:	cmp.b @R5,R10
	;	jhs maior
	;	mov.b @R5,R10
;maior:	inc R5
		;dec.b R6
		;jnz LOOP
		;ret


		;ER 2.13
		;mov #vetor,R5
	;	call #MAIOR8
	;	jmp $

;MAIOR8: mov.b @R5+,R6
;		mov #127,R10
;LOOP:	cmp.b @R5,R10
;		jlo menor
;		mov.b @R5,R10
;menor:	inc R5
;		dec.b R6
;		jnz LOOP
;		ret





		;ER 2.14

	;	mov	#vetor,R5
	;	call #inv8
	;	jmp $

;inv8:
	;	mov.b @R5,R6
	;	add.w R5,R6
	;	inc R5
;loop:
	;	cmp R5,R6
	;	jhs	lb
	;	ret
;lb:
	;	mov.b @R5,R10
	;	mov.b @R6,R11
	;	mov.b R10,0(R5)
	;	mov.b R11,0(R6)
	;	inc r5
	;	dec r6
	;	jmp	loop








		;ER 2.15
	;	mov #5,r6
	;	mov #0x2400,r5
	;	call #fib
	;	jmp $

;fib:
	;	clr r7
	;	mov #0,0(r5)
	;	inc r5
	;	mov #1,1(r5)
	;	inc r5
;loop:	mov -1(r5),0(r5)
	;	add -2(r5),0(r5)
	;	inc r5
	;	dec r6
	;	jnz loop
	;	ret

	mov.b #-1,r10
	cmp.b #-1,r10
	jeq lb
	jmp $
lb: mov #1,r11
	ret






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
            
