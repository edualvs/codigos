; 190112701 - Luiz Eduardo Alves da Costa
;
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
Prova_A1:	MOV		#VET1,R5
			MOV		#VET2,R6
			MOV		#VET3,R7
			CALL	#MESCLA  	;CHAMANDO a sub-rotina MESCLA
			JMP		$
			NOP

MESCLA:		mov @R5,R8	;movendo posição de R5 para R8
			add @R6,R8	;somando a posição de R6 em R8
			mov R8,0(R7);movendo a soma das posições de R5 E R6 para R7
			incd R5		;incrementando R5
			incd R6		;incrementando R6
			incd R7		;incrementando R7
confere:
			bit #1,0(R5)		;Testando o último bit de R5
			jz  move_vetor1		;Pulando pra mudança vetor1 primeiro do que vetor2
			bit #1,0(R6)		;Testando o último bit de R6
			jz move_vetor2		;Pulando pra mudança vetor2 primeiro do que vetor1

move_vetor1:	;SUBROTINA DE MUDANÇA DOS VALORES DOS VETOR1 E 2 PARA O VETOR3
			mov @R5+,0(R7)
			incd R7
			dec R8
			mov @R6+,0(R7)
			incd R7
			dec R8
			jz FIM
			jmp confere

move_vetor2:	;SUBROTINA DE MUDANÇA DOS VALORES DOS VETOR2 E 1 PARA O VETOR3
			mov @R6+,0(R7)
			incd R7
			dec R8
			mov @R5+,0(R7)
			incd R7
			dec R8
			jz FIM
			jmp confere



FIM:		RET 	;Retorna para onde foi chamado

			.data
VET1:		.word	7, 2, -33,  4590, -1, -32768, 1, 2
VET2:		.word	7, 3,  52, -4596,  0,  32767, 7, 2
VET3:		.word 	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 ;20 zeros

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
            
