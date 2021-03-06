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
CONF2 .equ 4 ;Configuração do Rotor 2
CONF3 .equ 1 ;Configuração do Rotor 3

EXP5:
			MOV #MSG,R5
			MOV #GSM,R6
			CLR R11 ; Contador do giro do rotor a esquerda
			CLR R13 ; Contador do giro do rotor a direita
	 		CALL #ENIGMA5 ;Cifrar
			MOV #GSM,R5
			MOV #DCF,R6
			CLR R11
	 		CLR R13
			CALL #ENIGMA5 ;Decifrar
			JMP $
			NOP

;Rotina ENIGMA (Experimento 5)
;
ENIGMA5:

CONFERE:
			CMP.B #0X41,0(R5)
			JGE LB
			MOV.B 0(R5),0(R6)
			JMP INCREMENTA
LB:			CMP.B #0X47,0(R5)
			JL GIRA_ROTOR
			MOV.B 0(R5),0(R6)
			JMP INCREMENTA

GIRA_ROTOR:
			MOV.B #CONF2,R10
			SUB.B R11,R10
			INC R11
			CMP.B #-1,R10
			JEQ DESLOCA
CONTINUA:	CMP #6,R11
			JEQ CICLO_COMPLETO
			JMP ROTOR_FOWARD1

DESLOCA:
			ADD.B #6,R10
			JMP CONTINUA
CICLO_COMPLETO:
			CLR R11
			MOV.B #CONF3,R12
			SUB.B R13,R12
			INC R13
			CMP.B #-1,R12
			JEQ DESLOCA2
CONTINUA2:	JMP ROTOR_FOWARD1

DESLOCA2:
			ADD.B #6,R12
			JMP CONTINUA2

ROTOR_FOWARD1:
			MOV #RT2,R7; Ponteiro Rotor
			ADD.B R10,R7
			ADD #0X2400,R7
			MOV.B 0(R5),0(R6)
			SUB.B #0X41,0(R6)
			ADD.B 0(R6),R7
			ADD #0X2400,R7
			MOV.B 0(R7),0(R6)
			ADD.B #0X41,0(R6)
			JMP ROTOR_FOWARD2

ROTOR_FOWARD2:
			MOV #RT3,R7; Ponteiro Rotor
			ADD.B R12,R7
			ADD #0X2400,R7

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
			JMP ROTOR_BACKWARD1

ROTOR_BACKWARD1:
			MOV #RT3,R7
			ADD.B R12,R7
			ADD #0X2400,R7
			CLR R9 ; Contador
			SUB.B #0X41,0(R6)
LOOP1:		CMP.B 0(R7),0(R6)
			JEQ R_B1
			INC R7
			INC R9
			JMP LOOP1
R_B1:
			MOV.B #0X41,0(R6)
			ADD.B R9,0(R6)
			JMP ROTOR_BACKWARD2

ROTOR_BACKWARD2:
			MOV #RT2,R7
			ADD.B R10,R7
			ADD #0X2400,R7
			CLR R9 ; Contador
			SUB.B #0X41,0(R6)
LOOP2:		CMP.B 0(R7),0(R6)
			JEQ R_B2
			INC R7
			INC R9
			JMP LOOP2
R_B2:
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



 	.data
MSG: .byte "CABECAFEFACAFAD",0 ;Mensagem em claro
GSM: .byte "XXXXXXXXXXXXXXX",0 ;Mensagem cifrada
DCF: .byte "XXXXXXXXXXXXXXX",0 ;Mensagem decifrada

; Rotores disponíveis
RT1: .byte 2, 4, 1, 5, 3, 0, 2, 4, 1, 5, 3 ;Trama do Rotor 1
RT2: .byte 1, 5, 3, 2, 0, 4, 1, 5, 3, 2, 0 ;Trama do Rotor 2
RT3: .byte 4, 0, 5, 2, 3, 1, 4, 0, 5, 2, 3 ;Trama do Rotor 3
RT4: .byte 3, 4, 1, 5, 2, 0, 3, 4, 1, 5, 2 ;Trama do Rotor 4
RT5: .byte 5, 2, 3, 4, 1, 0, 5, 2, 3, 4, 1 ;Trama do Rotor 5


; Refletores disponíveis
RF1: .byte 3, 5, 4, 0, 2, 1 ;Tabela do Refletor 1
RF2: .byte 4, 5, 3, 2, 0, 1 ;Tabela do Refletor 2
RF3: .byte 3, 2, 1, 0, 5, 4 ;Tabela do Refletor 3
                                            

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
            
