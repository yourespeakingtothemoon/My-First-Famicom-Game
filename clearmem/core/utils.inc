.macro PPU_SETADDR addr

	bit PPU_STATUS
	lda #>addr
	sta PPU_ADDR
	lda #<addr
	sta PPU_ADDR
.endmacro

.macro CollisionCheck
CheckTopLeft:
LDX XPos
LDA YPos
clc
adc #$01
tay
jsr CheckCollide
beq :+
 lda #0
 sta YVel
 dec YPos
 :
CheckRightColide:
lda XPos
clc
adc #$07
tax
lda YPos
clc
adc #$01
tay
jsr CheckCollide
beq :+
 lda #0
 sta XVel
 dec XPos
 :
lda XPos
clc
adc #$07
tax
lda YPos
clc
adc #$08
tay
jsr CheckCollide
beq :+
 lda #0
 sta YVel
 dec XPos
 inc YPos
 : 

CheckCollide:


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

rts



.endmacro
