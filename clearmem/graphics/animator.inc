.macro animationReservations

    player1: .res 1
    player2: .res 1
    player3: .res 1
    player4: .res 1

    playerParachute1: .res 1
    playerParachute2: .res 1
    playerParachute3: .res 1
    playerParachute4: .res 1
    playerParachute5: .res 1
    ;;middle of bottom row in parachute metasprite is just blank square sprite address 0

    frameCounter: .res 1


    PlayerAnimState: .res 1 
    ;00000000 - no animation 00000001 - idle 00000010 - walking 00000100 - falling/parachute 
    PlayerDirectionFlag: .res 1
    ;10000000 - verticalflipflag 01000000 - x flip flag
    playerSpriteTopLeftTile: .res 1
    ; 1 = face  2 = tail 3 = horn 4= hind leg

.endmacro



.macro processAnimation

.proc AnimationChange

CheckAnimationState:
   lda PlayerAnimState
   cmp NOANIM
        beq NoAnimation
    cmp IDLE
        beq IdleAnimation
    cmp WALK
        beq WalkingAnimation
    cmp PARACHUTE
        beq ParachuteAnimation
IdleAnimation:
    lda playerframe1a
    cmp STDFACE
        beq IdleFrame2
    ;;if not equal than initalize standard sprites
    lda STDFACE
    sta player1
    lda STDTAIL
    sta player2
    lda STDBACKFOOT
    sta player3
    lda STDHORN
    sta player4
    jmp EndAnimation
    IdleFrame2:
        lda IDLEFACE
        sta player1
        lda IDLETAIL
        sta player2
        lda IDLEBACKFOOT
        sta player3
        lda IDLEHORN
        sta player4
    jmp EndAnimation
.endproc
Animate:
    lda frameCounter
    cmp ANIMDELAY
    bne SpriteData
    lda 0
    sta frameCounter
    .proc AnimationChange
SpriteData:
    ;		  y | tile# |   attribute           |  x
.byte  	$10,	player2,	PlayerDirectionFlag,	$10
.byte	$10,	player1,	PlayerDirectionFlag,	$18
.byte	$18,	player3,	PlayerDirectionFlag,	$10
.byte	$18,	player4,	PlayerDirectionFlag,	$18