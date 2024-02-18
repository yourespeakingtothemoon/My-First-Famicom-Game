.macro PPU_SETADDR addr

	bit PPU_STATUS
	lda #>addr
	sta PPU_ADDR
	lda #<addr
	sta PPU_ADDR
.endmacro

