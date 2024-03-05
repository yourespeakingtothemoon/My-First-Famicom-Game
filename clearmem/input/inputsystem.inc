

.macro buttonProcs

.proc ReadButtons
    lda #1
    sta Buttons ;shift all to left and move carry to rightmost bit

    sta $4016 ;Collection mode
    lda #0  
    sta $4016 ;Output mode
LoopButtons:
    lda $4016

    lsr
    rol Buttons
    
    bcc LoopButtons
    rts
.endproc


.endmacro

.macro buttonChecks
CheckRight:
    lda Buttons
    and #%00000001
    beq CheckLeft
;;controller do
    inc XPos
CheckLeft:
    lda Buttons
    and #%00000010
    beq CheckUp
;;controller do
    dec XPos
CheckUp:
    lda Buttons
    and #%00000100
    beq CheckDown
;;controller do
    inc YPos
CheckDown:
    lda Buttons
    and #%00001000
    beq CheckA
;;controller do
    dec YPos
CheckA:
    lda Buttons
    and #%00010000
    beq CheckB
;;controller do
CheckB:
    lda Buttons
    and #%00100000
    beq CheckSelect
;;controller do
CheckSelect:
    lda Buttons
    and #%01000000
    beq CheckStart
;;controller do
CheckStart:
    lda Buttons
    and #%10000000
    beq :+

:
.endmacro

.macro buttonActionProcs_MainGame
   ; .proc 
.endmacro
