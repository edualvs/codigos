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

	;EP 2.1
		;mov.b #150,R5
		;mov.b #150,R6
		;call #soma
		;jmp $
;
;soma: 	clr r7
	;	add.b R5,R7
	;	add.b r6,r7
	;	ret



	;EP 2.2
		;mov #30000,R5
		;mov #30000,R6
		;call #soma
		;jmp $
;
;soma: 	clr r7
		;add R5,R7
		;add r6,r7
		;ret



		;EP 2.3
;		;mov #100,R5
;		mov #100,R6
;		call #soma
;		jmp $
;
;soma: 	clr r7
	;	add R5,R7
;;		add r6,r7
	;	ret




		;EP 2.4
	;	mov #40000,R5
	;	mov #40000,R6
;;		call #soma
;		jmp $
;
;soma: 	clr r7
;		clr r8
;		add R5,R7
;		adc r8
;		add R6,R7
;		adc r8
;		ret




		;EP 2.5
		mov #6,R5
		mov #5,R6
		call #sub
		jmp $

sub:
		mov.b #25
		clr r7
		add R5,R7
		add R6,R7
		adc r8
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
            
