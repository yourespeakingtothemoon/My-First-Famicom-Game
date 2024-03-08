.include "aliases.inc"
.include "core/inesheader.inc"
.include "core/reset.inc"
.include "graphics/zaraplay.gfx"
.include "core/utils.inc"
.include "graphics/rendering.inc"
.include "input/inputsystem.inc"
.include "graphics/animator.inc"


.segment "ZEROPAGE"
Buttons: .res 1 ;Button reader
XPos: .res 2
YPos: .res 2
;physics
XVel: .res 1
YVel: .res 1
JumpVel: .res 1

;sprite pointers
sprite1: .res 1
sprite2: .res 1
sprite3: .res 1
sprite4: .res 1
;same for walkin'
spritewalk1: .res 1
spritewalk2: .res 1
spritewalk3: .res 1
spritewalk4: .res 1

Flipflag: .res 1
AnimFlag: .res 1

temp: .res 1

TileOffset: .res 1

Frame: .res 1 	;Reserve for frame
Clock60: .res 1 
BkgPtr: .res 2  ; lo and hi for background pointer - little endian order lo first hi last





.segment "CODE"
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;PRG-ROM Code location $8000;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
graphicsProcs
buttonProcs
CollisionProcs
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;  RESET code, runs every time the NES console is reset  ;;;;;
;  game initalization code should all be contained here ;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
RESET:
	INIT_NES

	lda #0
	sta Frame
	sta Clock60
	sta TileOffset
	sta AnimFlag
	sta Flipflag
	sta JumpVel

	lda GRAVITY
	sta YVel


	lda #03
	sta sprite1
	lda #01
	sta sprite2
	lda #05
	sta sprite3
	lda #07
	sta sprite4

	lda #$0C
	sta spritewalk1
	lda #$0A
	sta spritewalk2
	lda #$0E
	sta spritewalk3
	lda #$10
	sta spritewalk4

	ldx #0
	lda SpriteData,x
	sta YPos+1
	inx
	inx
	inx
	lda SpriteData,x
	sta XPos+1
Main:
	PPU_SETADDR $3F00 
jsr LoadPalette	
jsr LoadBackground
jsr LoadSprites
 ; set ppu mask to activate render
EnablePPURendering:
	lda #%10010000
	sta PPU_CTRL
	lda #0
	sta PPU_SCROLL ;x scroll
	sta PPU_SCROLL ;y scroll
	lda #%00011110
	sta PPU_MASK	

LoopForever:
	jmp LoopForever 

NMI:
	inc Frame
	;inc frameCounter
	lda #$02
	sta $4014
	
	lda #0
	sta AnimFlag
	jsr ReadButtons
	buttonChecks
	jsr CheckCollide
	playerUpdate
	lda Frame
	cmp #60
	bne :+
	inc Clock60
	lda #0
	sta Frame
	
:
	rti
IRQ:
	rti
PaletteData:
;background palette
;.byte $0F,$2A,$0C,$3A, $0F,$2A,$0C,$3A, $0F,$2A,$0C,$3A, $0F,$2A,$0C,$3A
;sprite Palette
;.byte $0F,$10,$00,$26, $0F,$10,$00,$26, $0F,$10,$00,$26, $0F,$10,$00,$26

	PlayPalette
	PlayPalette
	BetaScreen
	CurelomStill
	collideMap
;;;;CHR-ROM DATA;;;;;;;

.segment "CHARS"
.incbin "graphics/curelomplay.chr"

.segment "VECTORS"
;------Interrupt Handlers---------
;    address for NMI handle
.word NMI
;  address for the RESET handle
.word RESET
;    address for IRQ handle
.word IRQ
