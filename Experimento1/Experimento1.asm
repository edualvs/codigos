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
EXP1: 	MOV #MSG,R5
		MOV #GSM,R6
		CALL #ENIGMA1
		JMP $
		NOP
;
; Sua rotina ENIGMA (Exp 1)
ENIGMA1:

CONFERE:
			CMP.B #0X41,0(R5)		;compara 'A' com a letra a ser cifrada
			JGE LB					; se for maior ou igual pula para LB
			MOV.B 0(R5),0(R6)		;Se não estiver no intervalo desejado só copia para a msg cifrada
			JMP INCREMENTA			;Pula para o label de incremento e verificação dos vetores
LB:			CMP.B #0X47,0(R5)		;compara 'G' com 0(R5)
			JL ROTOR_FOWARD			; Se for menor pula para ROTOR_FOWARD
			MOV.B 0(R5),0(R6)		;Se não estiver no intervalo desejado só copia para a msg cifrada
			JMP INCREMENTA			;Pula para o label de incremento e verificação dos vetores

ROTOR_FOWARD:
			MOV #RT1,R7
			MOV.B 0(R5),0(R6)
			SUB.B #0X41,0(R6)
			mov.b 0(R6),R15
			ADD.W R15,R7
			MOV.B 0(R7),0(R6)
			ADD.B #0X41,0(R6)
			JMP INCREMENTA

INCREMENTA:
			INC R5
			INC R6
			CMP.B #0,0(R5)
			JEQ	FIM
			JMP CONFERE

FIM: RET




; Dados para o enigma
		.data
MSG: .byte "CABECAFEFACAFAD",0 ;Mensagem em claro
GSM: .byte "XXXXXXXXXXXXXXX",0 ;Mensagem cifrada
RT1: .byte 2, 4, 1, 5, 3, 0 ;Trama do Rotor 1
                                            

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
            
