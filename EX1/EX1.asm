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
		mov.w #vetor,R5
		call #MENOR
		jmp $

MENOR:	mov.b #255,R6
		mov.b #1,R7
		mov.b @R5,R8
loop:	tst.b R8
		jz 	fim
		dec.b R8
		inc.w R5
		cmp.b @R5,R6
		jlo	lb_maior
		jeq lb_igual
lb_menor:
		mov.b @R5,R6
		jmp loop

lb_maior:
			jmp loop

lb_igual:
			inc.b R7
			jmp loop


fim:	ret

	.data
vetor:	.byte 6, 5, 3, 2, 1, 1, 8
                                            

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
            
