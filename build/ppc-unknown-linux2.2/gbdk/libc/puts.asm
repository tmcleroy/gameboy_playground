;--------------------------------------------------------
; File Created by SDCC : FreeWare ANSI-C Compiler
; Version 2.3.1 Mon Jan 15 17:17:38 2018

;--------------------------------------------------------
	.module puts
	
;--------------------------------------------------------
; Public variables in this module
;--------------------------------------------------------
	.globl _puts
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
;	puts.c 3
;	genLabel
;	genFunction
;	---------------------------------
; Function puts
; ---------------------------------
___puts_start:
_puts:
	lda	sp,-1(sp)
;	puts.c 5
;	genAssign
;	AOP_STK for 
	lda	hl,3(sp)
	ld	c,(hl)
	inc	hl
	ld	b,(hl)
;	genLabel
00101$:
;	genPointerGet
;	AOP_STK for _puts_sloc0_1_0
	ld	a,(bc)
	lda	hl,0(sp)
	ld	(hl),a
;	genIfx
;	AOP_STK for _puts_sloc0_1_0
	xor	a,a
	or	a,(hl)
	jp	z,00103$
;	puts.c 6
;	genPlus
;	genPlusIncr
	inc	bc
;	genIpush
; _saveRegsForCall: sendSetSize: 0 deInUse: 0 bcInUse: 1 deSending: 0
	push	bc
;	AOP_STK for _puts_sloc0_1_0
	ld	a,(hl)
	push	af
	inc	sp
;	genCall
	call	_putchar
	lda	sp,1(sp)
	pop	bc
;	genGoto
	jp	00101$
;	genLabel
00103$:
;	puts.c 7
;	genIpush
; _saveRegsForCall: sendSetSize: 0 deInUse: 0 bcInUse: 0 deSending: 0
	ld	a,#0x0A
	push	af
	inc	sp
;	genCall
	call	_putchar
	lda	sp,1(sp)
;	genLabel
00104$:
;	genEndFunction
	lda	sp,1(sp)
	ret
___puts_end:
	.area _CODE
;--------------------------------------------------------
; code
;--------------------------------------------------------
	.area _CODE
	.area _CODE
