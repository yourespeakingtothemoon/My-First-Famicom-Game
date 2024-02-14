.segment "HEADER"
.org $7FF0
.byte $4E,$45,$53,$1A,$02,$01,$00,$00,$00,$00,$00,$00,$00,$00,$00,$00

.segment "CODE:
.org $8000

Reset:
	lda $82
	ldx 82
	ldy #$82

NMI:
	rti

IRQ:
	rti 

.segment "VECTORS"
.org $FFFA
.word NMI
.word Reset
.word IRQ

