.macro graphicsProcs

.proc LoadPalette
	ldy #0 ;;;;;;;;;;
LoopPalette:
	lda PaletteData,y
	sta PPU_DATA
	iny            
	cpy #32          
	bne LoopPalette
	rts
.endproc

.proc LoadBackground
	ldy #0 ;;;;;;;;;;
LoopBackground:
	lda (BkgPtr),y
	sta PPU_DATA
	iny            
	cpy #255          
	bne LoopBackground
	rts
.endproc

.proc LoadAttributes
	ldy #0 ;;;;;;;;;;
LoopAttrib:
	lda AttributeData,y
	sta PPU_DATA
	iny            
	cpy #16          
	bne LoopAttrib
	rts
.endproc


.endmacro
