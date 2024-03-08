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
UpdateSpritePosit:
	lda XVel
	clc
	adc XPos
	sta XPos
	lda #0
	adc XPos+1
	sta XPos+1
	
SpriteUpdate:
	lda XPos+1
	sta $0203
	sta $020B
	clc
	adc #8
	sta $0207
	sta $020F

	lda YPos+1
	sta $0200
	sta $0204
	clc
	adc #8
	sta $0208
	sta $020C

	lda #0
	sta TileOffset
	lda Frame+1
	and #%00000001
	beq :+
		lda #1
		sta TileOffset
	:
lda AnimFlag
  cmp #0
  bne walk
idle:
;this is the idle animation for the player, if not idle dont do this


	lda #03
	clc
	adc TileOffset
	sta $201

	lda #01
	clc
	adc TileOffset
	sta $205

	lda #05
	clc
	adc TileOffset
	sta $209

	lda #07
	clc
	adc TileOffset
	sta $20D
	jmp endAnim
walk:


	lda #$0C
	clc
	adc TileOffset
	sta $201

	lda #$0A
	clc
	adc TileOffset
	sta $205

	lda #$0E
	clc
	adc TileOffset
	sta $209

	lda #$10
	clc
	adc TileOffset
	sta $20D
 endAnim:
.endmacro