;--------------------------------------------------------
; File Created by SDCC : FreeWare ANSI-C Compiler
; Version 2.3.1 Mon Jan 15 17:17:38 2018

;--------------------------------------------------------
	.module tolower
	
;--------------------------------------------------------
; Public variables in this module
;--------------------------------------------------------
	.globl _tolower
;--------------------------------------------------------
; special function registers
;--------------------------------------------------------
;--------------------------------------------------------
; special function bits 
;--------------------------------------------------------
;--------------------------------------------------------
; internal ram data
;--------------------------------------------------------
	.area _DATA
;--------------------------------------------------------
; overlayable items in internal ram 
;--------------------------------------------------------
	.area _OVERLAY
;--------------------------------------------------------
; indirectly addressable internal ram data
;--------------------------------------------------------
	.area _ISEG
;--------------------------------------------------------
; bit data
;--------------------------------------------------------
	.area _BSEG
;--------------------------------------------------------
; external ram data
;--------------------------------------------------------
	.area _XSEG
;--------------------------------------------------------
; global & static initialisations
;--------------------------------------------------------
	.area _GSINIT
	.area _GSFINAL
	.area _GSINIT
;--------------------------------------------------------
; Home
;--------------------------------------------------------
	.area _HOME
	.area _CODE
;--------------------------------------------------------
; code
;--------------------------------------------------------
	.area _CODE
;	tolower.c 3
;	genLabel
;	genFunction
;	---------------------------------
; Function tolower
; ---------------------------------
___tolower_start:
_tolower:
	
;	tolower.c 5
;	genCmpLt
;	AOP_STK for 
	lda	hl,2(sp)
	ld	a,(hl)
	xor	a,#0x80
	cp	#0x41^0x80
	ld	a,#0x00
	rla
	ld	c,a
;	genNot
	xor	a,a
	or	a,c
	sub	a,#0x01
	ld	a,#0x00
	rla
	ld	c,a
;	genCmpGt
;	AOP_STK for 
	ld	e,#0xDA
	ld	a,(hl)
	xor	a,#0x80
	ld	d,a
	ld	a,e
	sub	a,d
	ld	a,#0x00
	rla
	ld	b,a
;	genNot
	xor	a,a
	or	a,b
	sub	a,#0x01
	ld	a,#0x00
	rla
	ld	b,a
;	genAndOp
	xor	a,a
	or	a,c
	jr	z,00106$
	xor	a,a
	or	a,b
00106$:
	jr	z,00107$
	ld	a,#0x01
00107$:
	ld	c,a
;	genIfx
	xor	a,a
	or	a,c
	jp	z,00103$
;	genPlus
;	AOP_STK for 
;	genPlusIncr
;	Can't optimise plus by inc, falling back to the normal way
	lda	hl,2(sp)
	ld	a,(hl)
	add	a,#0x20
	ld	c,a
;	genGoto
	jp	00104$
;	genLabel
00103$:
;	genAssign
;	AOP_STK for 
	lda	hl,2(sp)
	ld	c,(hl)
;	genLabel
00104$:
;	genRet
	ld	e,c
;	genLabel
00101$:
;	genEndFunction
	
	ret
___tolower_end:
	.area _CODE
