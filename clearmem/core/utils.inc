.macro PPU_SETADDR addr

	bit PPU_STATUS
	lda #>addr
	sta PPU_ADDR
	lda #<addr
	sta PPU_ADDR
.endmacro

.macro CollisionProcs

.proc CheckCollide
LDX XPos
LDY YPos

txa
lsr
lsr
lsr
lsr
lsr
lsr
sta temp
tya
lsr
lsr
lsr
asl 
asl
clc
adc temp
tay

txa
lsr
lsr
lsr
and #%00000111

tax 
lda CollisionMap,y
and BitMask,x 
beq :+
 inc YPos
 :




.endmacro
