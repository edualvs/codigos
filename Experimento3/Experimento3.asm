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
RT_TAM .equ 6 ;Tamanho dos rotores
CONF1 .equ 1 ;Configuração do Rotor 1
EXP3:
			MOV #MSG,R5
 			MOV #GSM,R6
 			CALL #ENIGMA3
 			MOV #GSM,R5
 			MOV #DCF,R6
 			CALL #ENIGMA3
 			JMP $
 			NOP

;Rotina ENIGMA (Experimento 3)
ENIGMA3:

CONFERE:
			CMP.B #0X41,0(R5)
			JGE LB
			MOV.B 0(R5),0(R6)
			JMP INCREMENTA
LB:			CMP.B #0X47,0(R5)
			JL ROTOR_FOWARD
			MOV.B 0(R5),0(R6)
			JMP INCREMENTA

ROTOR_FOWARD:
			MOV #RT1,R7; Ponteiro Rotor
			ADD.B #CONF1,R7
			ADD #0X2400,R7
			MOV.B 0(R5),0(R6)
			SUB.B #0X41,0(R6)
			ADD.B 0(R6),R7
			ADD #0X2400,R7
			MOV.B 0(R7),0(R6)
			ADD.B #0X41,0(R6)
			JMP REFLETOR

REFLETOR:
			MOV #RF1,R8	; Ponteiro Refletor
			SUB.B #0X41,0(R6)
			ADD.B 0(R6),R8
			ADD #0X2400,R8
			MOV.B #0X41,0(R6)
			ADD.B 0(R8),0(R6)
			JMP ROTOR_BACKWARD

ROTOR_BACKWARD:
			MOV #RT1,R7
			ADD.B #CONF1,R7
			ADD #0X2400,R7
			CLR R9 ; Contador
			SUB.B #0X41,0(R6)
LOOP:		CMP.B 0(R7),0(R6)
			JEQ R_B
			INC R7
			INC R9
			JMP LOOP
R_B:
			MOV.B #0X41,0(R6)
			ADD.B R9,0(R6)
			JMP INCREMENTA


INCREMENTA:
			INC R5
			INC R6
			CMP.B #0,0(R5)
			JEQ	FIM
			JMP CONFERE

FIM: 		RET




; Dados para o enigma
 .data
MSG: .byte "CABECAFEFACAFAD",0 ;Mensagem em claro
GSM: .byte "XXXXXXXXXXXXXXX",0 ;Mensagem cifrada
DCF: .byte "XXXXXXXXXXXXXXX",0 ;Mensagem decifrada
RT1: .byte 2, 4, 1, 5, 3, 0, 2, 4, 1, 5, 3 ;Trama do Rotor
RF1: .byte 3, 5, 4, 0, 2, 1 ;Tabela do Refletor
                                            

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
            
