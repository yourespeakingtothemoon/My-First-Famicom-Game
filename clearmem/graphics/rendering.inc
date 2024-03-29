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
	bpl :+
		dec XPos+1
		:
	clc
	adc XPos
	sta XPos
	lda #0
	adc XPos+1
	sta XPos+1



;lda JumpFlag
;cmp #0
;beq NoJump
    ;	lda YVel
	;bpl :+
	;	dec YPos+1
	;	:
	;clc
	;adc YPos
	;sta YPos
	;lda #0
	;adc YPos+1
	;sta YPos+1
;NoJump:	
	

	lda #GRAVITY

	clc
	sbc YPos
	
	sta YPos
	lda #0
	adc YPos+1
	sta YPos+1
	


	lda YVel
	clc
	adc YPos+1
	sta YPos+1

	lda YVel
	sbc #AIRDECELL
	cmp #0
	bcs :+
		lda #0
		:
	sta YVel
	

	
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

lda Flipflag
	cmp #0 ; 0 means its not flipped
	beq NoFlip
		lda #%01000000
		sta $0202
		sta $0206
		sta $020A
		sta $020E
		lda #01
		sta sprite1
		lda #03
		sta sprite2
		lda #07
		sta sprite3
		lda #05
		sta sprite4

		lda #$0A
		sta spritewalk1
		lda #$0C
		sta spritewalk2
		lda #$10
		sta spritewalk3
		lda #$0E
		sta spritewalk4 
		jmp Animcheck
	NoFlip:
		lda #%00000000
		sta $0202
		sta $0206
		sta $020A
		sta $020E
	lda #$03
	sta sprite1
	lda #$01
	sta sprite2
	lda #$05
	sta sprite3
	lda #$07
	sta sprite4

	lda #$0C
	sta spritewalk1
	lda #$0A
	sta spritewalk2
	lda #$0E
	sta spritewalk3
	lda #$10
	sta spritewalk4	

Animcheck:
lda AnimFlag
  cmp #0
  bne walk
idle:
;this is the idle animation for the player, if not idle dont do this
	lda #0
	sta TileOffset
	lda Frame+1
	and #%00000001
	beq :+
		lda #1
		sta TileOffset
	:

	lda sprite1
	clc
	adc TileOffset
	sta $201

	lda sprite2
	clc
	adc TileOffset
	sta $205

	lda sprite3
	clc
	adc TileOffset
	sta $209

	lda sprite4
	clc
	adc TileOffset
	sta $20D
	jmp endAnim
walk:
	lda #0
	sta TileOffset
	lda XPos+1
	and #%00000010
	beq :+
		lda #1
		sta TileOffset
	:

	lda spritewalk1
	clc
	adc TileOffset
	sta $201

	lda spritewalk2
	clc
	adc TileOffset
	sta $205

	lda spritewalk3
	clc
	adc TileOffset
	sta $209

	lda spritewalk4
	clc
	adc TileOffset
	sta $20D
 endAnim:
.endmacro
