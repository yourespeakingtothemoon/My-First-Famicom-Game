.macro INIT_NES

	sei		  ; Disable all IRQ interrupts
	cld		  ; Clear decimal mode flag (d


	ldx #$FF
	txs 		  ;init stack pointer to botto
	
	inx	          ;X++ wrap to 0
	stx PPU_CTRL
	stx PPU_MASK
	stx $4010

	lda #$40
	sta $4017

	bit PPU_STATUS	
vblankwait1:
	bit PPU_STATUS
	bpl vblankwait1


	txa
ClearRAM:
	sta $0000,x	;Zero RAM from $0000 to $00FF
	sta $0100,x

	lda #$FF
	sta $0200,x
	
	lda #0
	sta $0300,x
	sta $0400,x
	sta $0500,x
	sta $0600,x
	sta $0700,x
	inx
	bne ClearRAM     ;if X is not zero we go back 
vblankwait2:
	bit PPU_STATUS
	bpl vblankwait2
.ENDMACRO
