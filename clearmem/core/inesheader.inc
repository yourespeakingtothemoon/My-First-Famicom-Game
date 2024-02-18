;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;iNES Header;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


.segment "HEADER"
.byte $4E,$45,$53,$1A     ; 4 bytes with characters N E S and \n
.byte $02 	          ; how many 16KB are we using PRG ROM?
.byte $01	          ; how many 8KB of CHR-ROM we are using?
.byte %00000000	          ; Horiz mirroring, no bat, no mapper
.byte %00000000           ; mapper 0, playchoice, NES 2.0
.byte $00	          ; no PRG-RAM - supplemental on cart
.byte $00                 ; 0-NTSC 1-PAL
.byte $00                 ; PRG RAM presence
.byte $00,$00,$00,$00,$00 ; header padding bytes

