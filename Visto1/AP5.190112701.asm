;Luiz Eduardo Alves da Costa - 190112701
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
RT_TAM .equ 26 ;Tamanho dos rotores (26 letras)
CONF1 .equ 4 ;Configuração do Rotor 2
CONF2 .equ 6 ;Configuração do Rotor 3
CONF3 .equ 8 ;Configuração do Rotor 2
CONF4 .equ 1 ;Configuração do Rotor 3
CONF5 .equ 12 ;Configuração do Rotor 2
VISTO1:
		 MOV #MSG,R5
		 MOV #GSM,R6

		 CLR R11 ; Contador do giro do rotor a esquerda
		 MOV.B  #1,R13 ; Contador do giro do rotor central
		 MOV.B  #1,R15 ; Contador do giro do rotor da direita
		 MOV.B #CONF2,R10
		 MOV.B #CONF3,R12
		 MOV.B #CONF5,R14

		 CALL #ENIGMA ;Cifrar

		 MOV #GSM,R5
		 MOV #DCF,R6

		 CLR R11 ; Contador do giro do rotor a esquerda
		 MOV.B #1,R13 ; Contador do giro do rotor central
		 MOV.B #1,R15 ; Contador do giro do rotor da direita
		 MOV.B #CONF2,R10
		 MOV.B #CONF3,R12
		 MOV.B #CONF5,R14

		 CALL #ENIGMA ;Cifrar
		 JMP $
		 NOP



; Coloque aqui sua sub-rotina ENIGMA
ENIGMA:

CONFERE:
			CMP.B #0X41,0(R5)
			JGE LB
			MOV.B 0(R5),0(R6)
			JMP INCREMENTA
LB:			CMP.B #0X5B,0(R5)
			JL GIRA_ROTOR
			MOV.B 0(R5),0(R6)
			JMP INCREMENTA

GIRA_ROTOR: ;GIRA ROTOR DA ESQUERDA
			MOV.B #CONF2,R10
			SUB R11,R10
			INC R11
			CMP.B #0,R10
			JL  DESLOCA
CONTINUA:	CMP #27,R11
			JEQ CICLO_COMPLETO
			JMP ROTOR_FOWARD1

DESLOCA:
			ADD.B #26,R10
			JMP CONTINUA

CICLO_COMPLETO: ;GIRA ROTOR CENTRAL
			MOV.B #CONF2,R10
			MOV #1,R11
			MOV.B #CONF3,R12
			SUB R13,R12
			INC R13
			CMP.B #0,R12
			JL  DESLOCA2
CONTINUA2:	CMP #27,R13
			JEQ CICLO_COMPLETO2
			JMP ROTOR_FOWARD1

DESLOCA2:
			ADD.B #26,R12
			JMP CONTINUA2

CICLO_COMPLETO2: ;GIRA ROTOR DA DIREITA
			MOV.B #CONF3,R12
			MOV #1, R13
			MOV.B #CONF5,R14
			SUB R15,R14
			INC R15
			CMP.B #0,R14
			JL  DESLOCA3
CONTINUA3:  JMP ROTOR_FOWARD1


DESLOCA3:
			ADD.B #26,R10
			JMP CONTINUA3

ROTOR_FOWARD1: ;ROTOR DA ESQUERDA (IDA)
			MOV #RT2,R7; Ponteiro Rotor
			MOV.B R10,R4
			ADD.W R4,R7
			MOV.B 0(R5),0(R6)
			SUB.B #0X41,0(R6)
			MOV.B 0(R6),R4
			ADD.W R4,R7
			MOV.B 0(R7),0(R6)
			ADD.B #0X41,0(R6)
			JMP ROTOR_FOWARD2

ROTOR_FOWARD2: ;ROTOR CENTRAL (IDA)
			MOV #RT3,R7; Ponteiro Rotor
			MOV.B R12,R4
			ADD.W R4,R7
			SUB.B #0X41,0(R6)
			MOV.B 0(R6),R4
			ADD.W R4,R7
			MOV.B 0(R7),0(R6)
			ADD.B #0X41,0(R6)
			JMP ROTOR_FOWARD3

ROTOR_FOWARD3: ;ROTOR DA DIREITA (IDA)
			MOV #RT5,R7; Ponteiro Rotor
			MOV.B R14,R4
			ADD.W R4,R7

			SUB.B #0X41,0(R6)
			MOV.B 0(R6),R4
			ADD.W R4,R7
			MOV.B 0(R7),0(R6)
			ADD.B #0X41,0(R6)
			JMP REFLETOR

REFLETOR: ;REFLETOR
			MOV #RF2,R8	; Ponteiro Refletor
			SUB.B #0X41,0(R6)
			MOV.B 0(R6),R4
			ADD R4,R8
			MOV.B #0X41,0(R6)
			ADD.B 0(R8),0(R6)
			JMP ROTOR_BACKWARD1

ROTOR_BACKWARD1:  ;ROTOR DA DIREITA (VOLTA)
			MOV #RT5,R7
			MOV.B R14,R4
			ADD R4,R7
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

ROTOR_BACKWARD2: ;ROTOR CENTRAL (VOLTA)
			MOV #RT3,R7
			MOV.B R12,R4
			ADD R4,R7
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
			JMP ROTOR_BACKWARD3

ROTOR_BACKWARD3: ;ROTOR DA ESQUERDA (VOLTA)
			MOV #RT2,R7
			MOV.B R10,R4
			ADD R4,R7
			CLR R9 ; Contador
			SUB.B #0X41,0(R6)
LOOP3:		CMP.B 0(R7),0(R6)
			JEQ R_B3
			INC R7
			INC R9
			JMP LOOP3
R_B3:
			MOV.B #0X41,0(R6)
			ADD.B R9,0(R6)
			JMP INCREMENTA



INCREMENTA: ;INCREMENTA R5 E R6
			INC R5
			INC R6
			CMP.B #0,0(R5)
			JEQ	FIM
			JMP CONFERE

FIM: 		RET


 	.data
MSG:
	 .byte "UMA NOITE DESTAS, VINDO DA CIDADE PARA O ENGENHO NOVO,"
 	 .byte " ENCONTREI NO TREM DA CENTRAL UM RAPAZ AQUI DO BAIRRO,"
 	 .byte " QUE EU CONHECO DE VISTA E DE CHAPEU.",0 ;Don Casmurro
GSM:
	 .byte "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX"
 	 .byte "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX"
 	 .byte "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX",0
DCF:
	 .byte "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX"
	 .byte "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX"
 	 .byte "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX",0

;Rotores com 26 posições
RT1:
		 .byte 10, 18, 0, 7, 3, 2, 4, 8, 14, 17, 5, 22, 20
		 .byte 25, 23, 1, 24, 13, 21, 19, 11, 6, 12, 15, 9, 16
		 .byte 10, 18, 0, 7, 3, 2, 4, 8, 14, 17, 5, 22, 20
		 .byte 25, 23, 1, 24, 13, 21, 19, 11, 6, 12, 15, 9
RT2:
		 .byte 19, 9, 7, 23, 11, 25, 17, 16, 2, 24, 15, 10, 6
		 .byte 14, 0, 8, 13, 4, 3, 18, 1, 22, 21, 20, 5, 12
		 .byte 19, 9, 7, 23, 11, 25, 17, 16, 2, 24, 15, 10, 6
		 .byte 14, 0, 8, 13, 4, 3, 18, 1, 22, 21, 20, 5
RT3:
		 .byte 16, 21, 4, 0, 1, 12, 15, 14, 8, 25, 9, 19, 17
		 .byte 6, 5, 20, 13, 24, 23, 10, 3, 22, 11, 7, 18, 2
		 .byte 16, 21, 4, 0, 1, 12, 15, 14, 8, 25, 9, 19, 17
		 .byte 6, 5, 20, 13, 24, 23, 10, 3, 22, 11, 7, 18
RT4:
		 .byte 25, 4, 21, 22, 17, 14, 12, 8, 5, 15, 23, 6, 2
		 .byte 18, 10, 16, 13, 3, 19, 20, 0, 24, 11, 7, 9, 1
		 .byte 25, 4, 21, 22, 17, 14, 12, 8, 5, 15, 23, 6, 2
		 .byte 18, 10, 16, 13, 3, 19, 20, 0, 24, 11, 7, 9
RT5:
		 .byte 13, 5, 20, 7, 0, 15, 21, 9, 19, 14, 24, 18, 12
		 .byte 6, 2, 11, 16, 8, 3, 1, 10, 23, 4, 25, 22, 17
		 .byte 13, 5, 20, 7, 0, 15, 21, 9, 19, 14, 24, 18, 12
		 .byte 6, 2, 11, 16, 8, 3, 1, 10, 23, 4, 25, 22

;Refletores com 26 posições
RF1:
		.byte 7, 17, 5, 19, 15, 2, 9, 0, 14, 6, 18, 16, 25
 		.byte 23, 8, 4, 11, 1, 10, 3, 22, 24, 20, 13, 21, 12
RF2:
		.byte 2, 13, 0, 8, 10, 19, 23, 14, 3, 22, 4, 20, 25
 		.byte 1, 7, 17, 21, 15, 24, 5, 11, 16, 9, 6, 18, 12
RF3:
		.byte 22, 5, 9, 12, 14, 1, 13, 10, 23, 2, 7, 21, 3
 		.byte 6, 4, 24, 17, 16, 19, 18, 25, 11, 0, 8, 15, 20
                                            

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
            
