;;;;;;;;;;;;;;;;;;;
;;;Constant Aliases for PPU
;;;;;;;;;;;;;;;;;;;

PPU_CTRL   = $2000
PPU_MASK   = $2001
PPU_STATUS = $2002
OAM_ADDR   = $2003
OAM_DATA   = $2004
PPU_SCROLL = $2005
PPU_ADDR   = $2006
PPU_DATA   = $2007

;;Controller

JOYPAD1 = $4016
JOYPAD2 = $4017

;;;;;;;;;;;;;;;;;;;
;;; BUTTONS

A_BUTTON = $80
B_BUTTON = $40
SELECT_BUTTON = $20
START_BUTTON = $10
UP_BUTTON = $08
DOWN_BUTTON = $04
LEFT_BUTTON = $02
RIGHT_BUTTON = $01  

;;;;;;;;;;;;;;;;;;;
;;;; PHYSICS
;;;;;;;;;;;;;;;;;;;
MAXSPEED = 120
JUMPSPEED = 100
ACCEL = 2
STOP = 2
GRAVITY = 109

;;;;;;;;;;;;;;;;;;;
;;;; ANIMATION
;;;;;;;;;;;;;;;;;;;
;;anim utils
ANIMDELAY = 2 ;;; compare to this to move to next frame or not


;;Player States
NOANIM = 0
IDLE = 1
WALK = 2
PARACHUTE = 4

;;Sprite tile references
BLANK = 0

;;Player - no anim, first frame of idle
STDFACE = $01
STDTAIL = $02
STDBACKFOOT = $05
STDHORN = $08
;;Player - IDle frame 2
IDLFACE = $25
IDLTAIL = $24
IDLBACKFOOT = $34
IDLHORN = $35
;;Player - Walk frame 1
;;just use stdface
WLKTAIL1 = $03
WLKBACKFOOT1 = $06
WLKHORN1 = $09
;;Player - Walk frame 2
WLKTAIL2 = $04
WLKBACKFOOT2 = $07
WLKHORN2 = $0A
;;Player - Parachute
;;defaults
PARAHORN = $12
PARABACKFOOT = $11
;;frame 1
PARAFACE1 = $0F
PARAMID1 = $0E
PARATAIL1 = $0B
;;frame 2
PARAFACE2 = $10
PARAMID2 = $0D
PARATAIL2 = $0C

;;;;;;;;Snek;;;;;;
;;;always animating
SNEKFACE1= $18
SNETAIL1 = $17
SNEKBODYF1 = $1A
SNEKBODYB1 = $19
SNEKFACE2 = $14
SNETAIL2 = $13
SNEKBODYF2 = $16
SNEKBODYB2 = $15



