.include "aliases.inc"
.include "inesheader.inc"
.include "reset.inc"
.include "titlescreentest.gfx"
.include "utils.inc"
.include "core/procedures.inc"
.segment "ZEROPAGE"

Frame: .res 1 	;Reserve for frame
Clock60: .res 1 
BkgPtr: .res 2  ; lo and hi for background pointer - little endian order lo first hi last

.segment "CODE"
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;PRG-ROM Code loc $8000;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
graphicsProcs
;;;;;;;;;;;;;;;;;;;;;;
;;its resettin time
;;;;;;;;;;;;;;;;;;;;;;
RESET:
	INIT_NES
	lda #0
	sta Frame
	sta Clock60
Main:
	PPU_SETADDR $3F00 
	jsr LoadPalette	

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
	

 ; set ppu mask to activate render
EnablePPURendering:
	lda #%10000000
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

	TitleTestPalette
	TitleTestPalette

BackgroundData:

	TitleScreen

;;;;CHR-ROM DATA;;;;;;;

.segment "CHARS"
.incbin "titlescreen.chr"

.segment "VECTORS"
;------Interrupt Handlers---------
;    address for NMI handle
.word NMI
;  address for the RESET handle
.word RESET
;    address for IRQ handle
.word IRQ
