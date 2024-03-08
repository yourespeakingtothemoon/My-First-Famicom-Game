

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
    and #RIGHT_BUTTON
    beq NotRight
;;controller do
lda #0
sta Flipflag
lda XVel
bmi NotRight
clc
adc #ACCEL
cmp #MAXSPEED
bcc :+
    lda #MAXSPEED
    :
    sta XVel
    ldx $01
    stx AnimFlag
    jmp CheckLeft
        NotRight:
        lda XVel
        bmi CheckLeft
        cmp #STOP
        bcs :+
        lda #STOP+1
        :
        sbc #STOP
        sta XVel
        lda #0
        sta AnimFlag
CheckLeft:
    lda Buttons
    and #LEFT_BUTTON
    beq NotLeft
;;controller do

lda XVel
beq:+
bpl NotLeft
:
sec 
sbc #ACCEL
cmp #256-MAXSPEED
bcs :+
    lda #256-MAXSPEED
    :
    sta XVel
    lda $01
sta Flipflag
sta AnimFlag
    jmp CheckUp
        NotLeft:
        lda XVel
        bpl CheckUp
       cmp #256-STOP
       bcc:+
       lda #256-STOP
       :
       adc #STOP
       sta XVel
       lda #0
        sta AnimFlag
CheckUp:
    lda Buttons
    and #UP_BUTTON
    beq CheckDown
;;controller do
        inc YPos
CheckDown:
lda YVel
	sec
	adc #GRAVITY
    cmp #256-MAXFALLSPEED
    bcc:+
    lda #256-MAXFALLSPEED
    :
	sta YVel
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
