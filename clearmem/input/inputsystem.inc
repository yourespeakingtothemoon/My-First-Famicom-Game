

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
    and #BUTTON_RIGHT
    beq CheckLeft
;;controller do
        inc XPos
CheckLeft:
    lda Buttons
    and #BUTTON_LEFT
    beq CheckUp
;;controller do
        dec XPos
CheckUp:
    lda Buttons
    and #UP_BUTTON
    beq CheckDown
;;controller do
        inc YPos
CheckDown:
    lda Buttons
    and #DOWN_BUTTON
    beq CheckA
;;controller do
        dec YPos
CheckA:
    lda Buttons
    and #A_BUTTON
    beq CheckB
;;controller do
CheckB:
    lda Buttons
    and #B_BUTTON
    beq CheckSelect
;;controller do
CheckSelect:
    lda Buttons
    and #SELECT_BUTTON
    beq CheckStart
;;controller do
CheckStart:
    lda Buttons
    and #START_BUTTON
    beq :+

:
.endmacro

.macro buttonActionProcs_MainGame
 .proc right_action
.endproc
 .proc left_action
.endproc
    .proc up_action
.endproc
    .proc down_action
.endproc
    .proc a_action
.endproc
    .proc b_action
.endproc
    .proc select_action
.endproc
    .proc start_action
.endproc


.endmacro
