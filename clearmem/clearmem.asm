;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;iNES Header;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


.segment "HEADER"
.byte $4E,$45,$53,$1A     ; 4 bytes with characters N E S and \n
.byte $02 	          ; how many 16KB are we using PRG ROM?
.byte $01	          ; how many 8KB of CHR-ROM we are using?
.byte %00000000	          ; Horiz mirroring, no bat, no mapper
.byte %00000000           ; mapper 0, playchoice, NES 2.0
.byte $00	          ; no PRG-RAM - supplemental on cart
.byte $00                 ; 0-NTSC 1-PAL
.byte $00                 ; PRG RAM presence
.byte $00,$00,$00,$00,$00 ; header padding bytes

.segment "CODE"
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;PRG-ROM Code loc $8000;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
.segment "CODE"
;TODO: Add code for PRG-ROM


RESET:
	sei		  ; Disable all IRQ interrupts
	cld		  ; Clear decimal mode flag (doesnt exist on Famicom processor)
	ldx #$FF
	txs 		  ;init stack pointer to bottom of stack
	
	inx	          ;X++ wrap to 0
	txa
ClearRAM:
	sta $0000,x	;Zero RAM from $0000 to $00FF
	sta $0100,x
	sta $0200,x
	sta $0300,x
	sta $0400,x
	sta $0500,x
	sta $0600,x
	sta $0700,x
	inx
	bne ClearRAM     ;if X is not zero we go back to loop
LoopForever:
	jmp LoopForever ;forces while(true)

NMI:
	rti
IRQ:
	rti


.segment "VECTORS"
;------Interrupt Handlers---------
;    address for NMI handle
.word NMI
;  address for the RESET handle
.word RESET
;    address for IRQ handle
.word IRQ
