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
	lda #<BackgroundData
	sta BkgPtr
	lda #>BackgroundData
	sta BkgPtr+1

	PPU_SETADDR $2000
	ldx #$00
	ldy #$00
OuterLoop:
InnerLoop:
	lda(BkgPtr),y
	sta PPU_DATA
	iny
	cpy #0
	beq IncreaseHiByte
	jmp InnerLoop
IncreaseHiByte:
	inc BkgPtr+1
	inx
	cpx #4
	bne OuterLoop
	
.endproc



.proc LoadSprites
	ldx #0 ;;;;;;;;;;
LoopSprite:
	lda SpriteData,x
	sta $0200,x
	inx
	cpx #16
	bne LoopSprite
	rts
.endproc

.endmacro

.macro playerUpdate
SpriteUpdate:
	lda XPos
	sta $0203
	sta $020B
	clc
	adc #8
	sta $0207
	sta $020F

	lda YPos
	sta $0200
	sta $0204
	clc
	adc #8
	sta $0208
	sta $020C


.endmacro