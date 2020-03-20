
#ifndef __BASIC_STD
#define __BASIC_STD 

#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TRUE	(0x01)
#define FALSE	(0x00)

typedef unsigned char BYTE;
typedef char  CHAR;
typedef int   WORD;
typedef long  LONG;
typedef char  BOOL;

#define LOBYTE(a) ((CHAR)(a))
#define HIBYTE(a) ((CHAR)(((WORD)(a) >> 8) & 0xFF))

#define L24BYTE(a) ((CHAR)(a))
#define M24BYTE(a) ((CHAR)(((LONG)(a) >> 8) & 0xFF))
#define H24BYTE(a) ((CHAR)(((LONG)(a) >> 16) & 0xFF))

#define MAKEWORD(low, high) ((WORD)((((WORD)(high)) << 8) | ((BYTE)(low))))

#define VOLATILE		


#define MOUSE_CLICK_LEFT 	((FXOS_MOUSE_BYTE_0[0] & 0x01) == 0x01)
#define MOUSE_CLICK_RIGHT 	((FXOS_MOUSE_BYTE_0[0] & 0x02) == 0x02)
#define MOUSE_CLICK_MIDDLE	((FXOS_MOUSE_BYTE_0[0] & 0x04) == 0x04)


/*

;Internal VICKY Registers and Internal Memory Locations (LUTs)
MASTER_CTRL_REG_L	       EQU $AF0000
;Control Bits Fields
Mstr_Ctrl_Text_Mode_En   EQU $01
Mstr_Ctrl_Text_Overlay   EQU $02       ; Enable the Overlay of the text mode on top of Graphic Mode (the Background Color is ignored)
Mstr_Ctrl_Graph_Mode_En  EQU $04
Mstr_Ctrl_Bitmap_En      EQU $08
Mstr_Ctrl_TileMap_En     EQU $10
Mstr_Ctrl_Sprite_En      EQU $20
Mstr_Ctrl_GAMMA_En       EQU $40
Mstr_Ctrl_Disable_Vid    EQU $80
MASTER_CTRL_REG_H	       EQU $AF0001
; Reserved - TBD
VKY_RESERVED_00          EQU $AF0002
VKY_RESERVED_01          EQU $AF0003
BORDER_CTRL_REG          EQU $AF0004
Border_Ctrl_Enable       EQU $01

BORDER_COLOR_B           EQU $AF0005
BORDER_COLOR_G           EQU $AF0006
BORDER_COLOR_R           EQU $AF0007

VKY_TXT_CURSOR_CTRL_REG  EQU $AF0010   ;[0]  Enable Text Mode
Vky_Cursor_Enable        EQU $01
Vky_Cursor_Flash_Rate0   EQU $02
Vky_Cursor_Flash_Rate1   EQU $04
Vky_Cursor_FONT_Page0    EQU $08       ; Pick Font Page 0 or Font Page 1
Vky_Cursor_FONT_Page1    EQU $10       ; Pick Font Page 0 or Font Page 1
VKY_TXT_RESERVED         EQU $AF0011   ;Not in Use
VKY_TXT_CURSOR_CHAR_REG  EQU $AF0012

VKY_TXT_CURSOR_COLR_REG  EQU $AF0013
VKY_TXT_CURSOR_X_REG_L   EQU $AF0014VKY_TXT_CURSOR_X_REG_H   EQU $AF0015
VKY_TXT_CURSOR_Y_REG_L   EQU $AF0016
VKY_TXT_CURSOR_Y_REG_H   EQU $AF0017

VKY_INFO_CHIP_NUM_L      EQU $AF001C
VKY_INFO_CHIP_NUM_H      EQU $AF001D
VKY_INFO_CHIP_VER_L      EQU $AF001E
VKY_INFO_CHIP_VER_H      EQU $AF001F

;
; Bit Field Definition for the Control Register
TILE_Enable              EQU $01
TILE_LUT0                EQU $02
TILE_LUT1                EQU $04
TILE_LUT2                EQU $08
TILESHEET_256x256_En     EQU $80   ; 0 -> Sequential, 1-> 256x256 Tile Sheet Striding
;
;Tile MAP Layer 0 Registers
TL0_CONTROL_REG          EQU $AF0100       ; Bit[0] - Enable, Bit[3:1] - LUT Select,
TL0_START_ADDY_L         EQU $AF0101       ; Not USed right now - Starting Address to where is the MAP
TL0_START_ADDY_M         EQU $AF0102
TL0_START_ADDY_H         EQU $AF0103
TL0_MAP_X_STRIDE_L       EQU $AF0104       ; The Stride of the Map
TL0_MAP_X_STRIDE_H       EQU $AF0105
TL0_MAP_Y_STRIDE_L       EQU $AF0106       ; The Stride of the Map
TL0_MAP_Y_STRIDE_H       EQU $AF0107
;TL0_RESERVED_0           EQU $AF0108
;TL0_RESERVED_1           EQU $AF0109
;TL0_RESERVED_2           EQU $AF010A
;TL0_RESERVED_3           EQU $AF010B
;TL0_RESERVED_4           EQU $AF010C
;TL0_RESERVED_5           EQU $AF010D
;TL0_RESERVED_6           EQU $AF010E
;TL0_RESERVED_7           EQU $AF010F
;Tile MAP Layer 1 Registers
TL1_CONTROL_REG          EQU $AF0108       ; Bit[0] - Enable, Bit[3:1] - LUT Select,
TL1_START_ADDY_L         EQU $AF0109       ; Not USed right now - Starting Address to where is the MAP
TL1_START_ADDY_M         EQU $AF010A
TL1_START_ADDY_H         EQU $AF010B
TL1_MAP_X_STRIDE_L       EQU $AF010C       ; The Stride of the Map
TL1_MAP_X_STRIDE_H       EQU $AF010D
TL1_MAP_Y_STRIDE_L       EQU $AF010E       ; The Stride of the Map
TL1_MAP_Y_STRIDE_H       EQU $AF010F
;TL1_RESERVED_0           EQU $AF0118
;TL1_RESERVED_1           EQU $AF0119
;TL1_RESERVED_2           EQU $AF011A
;TL1_RESERVED_3           EQU $AF011B
;TL1_RESERVED_4           EQU $AF011C
;TL1_RESERVED_5           EQU $AF011D
;TL1_RESERVED_6           EQU $AF011E
;TL1_RESERVED_7           EQU $AF011F
;Tile MAP Layer 2 Registers
TL2_CONTROL_REG          EQU $AF0110       ; Bit[0] - Enable, Bit[3:1] - LUT Select,
TL2_START_ADDY_L         EQU $AF0111       ; Not USed right now - Starting Address to where is the MAP
TL2_START_ADDY_M         EQU $AF0112
TL2_START_ADDY_H         EQU $AF0113
TL2_MAP_X_STRIDE_L       EQU $AF0114       ; The Stride of the Map
TL2_MAP_X_STRIDE_H       EQU $AF0115
TL2_MAP_Y_STRIDE_L       EQU $AF0116       ; The Stride of the Map
TL2_MAP_Y_STRIDE_H       EQU $AF0117
;TL2_RESERVED_0           EQU $AF0128
;TL2_RESERVED_1           EQU $AF0129
;TL2_RESERVED_2           EQU $AF012A
;TL2_RESERVED_3           EQU $AF012B
;TL2_RESERVED_4           EQU $AF012C
;TL2_RESERVED_5           EQU $AF012D
;TL2_RESERVED_6           EQU $AF012E
;TL2_RESERVED_7           EQU $AF012F
;Tile MAP Layer 3 Registers
TL3_CONTROL_REG          EQU $AF0118       ; Bit[0] - Enable, Bit[3:1] - LUT Select,
TL3_START_ADDY_L         EQU $AF0119       ; Not USed right now - Starting Address to where is the MAP
TL3_START_ADDY_M         EQU $AF011A
TL3_START_ADDY_H         EQU $AF011B
TL3_MAP_X_STRIDE_L       EQU $AF011C       ; The Stride of the Map
TL3_MAP_X_STRIDE_H       EQU $AF011D
TL3_MAP_Y_STRIDE_L       EQU $AF011E       ; The Stride of the Map
TL3_MAP_Y_STRIDE_H       EQU $AF011F
;TL3_RESERVED_0           EQU $AF0138
;TL3_RESERVED_1           EQU $AF0139
;TL3_RESERVED_2           EQU $AF013A
;TL3_RESERVED_3           EQU $AF013B
;TL3_RESERVED_4           EQU $AF013C
;TL3_RESERVED_5           EQU $AF013D
;TL3_RESERVED_6           EQU $AF013E
;TL3_RESERVED_7           EQU $AF013F
;Bitmap Registers
BM_CONTROL_REG           EQU $AF0140
BM_START_ADDY_L          EQU $AF0141
BM_START_ADDY_M          EQU $AF0142
BM_START_ADDY_H          EQU $AF0143
BM_X_SIZE_L              EQU $AF0144
BM_X_SIZE_H              EQU $AF0145
BM_Y_SIZE_L              EQU $AF0146
BM_Y_SIZE_H              EQU $AF0147
BM_RESERVED_0            EQU $AF0148
BM_RESERVED_1            EQU $AF0149
BM_RESERVED_2            EQU $AF014A
BM_RESERVED_3            EQU $AF014B
BM_RESERVED_4            EQU $AF014C
BM_RESERVED_5            EQU $AF014D
BM_RESERVED_6            EQU $AF014E
BM_RESERVED_7            EQU $AF014F
;Sprite Registers
; Bit Field Definition for the Control Register
SPRITE_Enable              EQU $01
SPRITE_LUT0                EQU $02
SPRITE_LUT1                EQU $04
SPRITE_LUT2                EQU $08
SPRITE_DEPTH0              EQU $10
SPRITE_DEPTH1              EQU $20
SPRITE_DEPTH2              EQU $40

; Sprite 0 (Highest Priority)
SP00_CONTROL_REG         EQU $AF0200
SP00_ADDY_PTR_L          EQU $AF0201
SP00_ADDY_PTR_M          EQU $AF0202
SP00_ADDY_PTR_H          EQU $AF0203
SP00_X_POS_L             EQU $AF0204
SP00_X_POS_H             EQU $AF0205
SP00_Y_POS_L             EQU $AF0206
SP00_Y_POS_H             EQU $AF0207
; Sprite 1
SP01_CONTROL_REG         EQU $AF0208
SP01_ADDY_PTR_L          EQU $AF0209
SP01_ADDY_PTR_M          EQU $AF020A
SP01_ADDY_PTR_H          EQU $AF020B
SP01_X_POS_L             EQU $AF020C
SP01_X_POS_H             EQU $AF020D
SP01_Y_POS_L             EQU $AF020E
SP01_Y_POS_H             EQU $AF020F
; Sprite 2
SP02_CONTROL_REG         EQU $AF0210
SP02_ADDY_PTR_L          EQU $AF0211
SP02_ADDY_PTR_M          EQU $AF0212
SP02_ADDY_PTR_H          EQU $AF0213
SP02_X_POS_L             EQU $AF0214
SP02_X_POS_H             EQU $AF0215
SP02_Y_POS_L             EQU $AF0216
SP02_Y_POS_H             EQU $AF0217
; Sprite 3
SP03_CONTROL_REG         EQU $AF0218
SP03_ADDY_PTR_L          EQU $AF0219
SP03_ADDY_PTR_M          EQU $AF021A
SP03_ADDY_PTR_H          EQU $AF021B
SP03_X_POS_L             EQU $AF021C
SP03_X_POS_H             EQU $AF021D
SP03_Y_POS_L             EQU $AF021E
SP03_Y_POS_H             EQU $AF021F
; Sprite 4
SP04_CONTROL_REG         EQU $AF0220
SP04_ADDY_PTR_L          EQU $AF0221
SP04_ADDY_PTR_M          EQU $AF0222
SP04_ADDY_PTR_H          EQU $AF0223
SP04_X_POS_L             EQU $AF0224
SP04_X_POS_H             EQU $AF0225
SP04_Y_POS_L             EQU $AF0226
SP04_Y_POS_H             EQU $AF0227
; Sprite 5
SP05_CONTROL_REG         EQU $AF0228
SP05_ADDY_PTR_L          EQU $AF0229
SP05_ADDY_PTR_M          EQU $AF022A
SP05_ADDY_PTR_H          EQU $AF022B
SP05_X_POS_L             EQU $AF022C
SP05_X_POS_H             EQU $AF022D
SP05_Y_POS_L             EQU $AF022E
SP05_Y_POS_H             EQU $AF022F
; Sprite 6
SP06_CONTROL_REG         EQU $AF0230
SP06_ADDY_PTR_L          EQU $AF0231
SP06_ADDY_PTR_M          EQU $AF0232
SP06_ADDY_PTR_H          EQU $AF0233
SP06_X_POS_L             EQU $AF0234
SP06_X_POS_H             EQU $AF0235
SP06_Y_POS_L             EQU $AF0236
SP06_Y_POS_H             EQU $AF0237
; Sprite 7
SP07_CONTROL_REG         EQU $AF0238
SP07_ADDY_PTR_L          EQU $AF0239
SP07_ADDY_PTR_M          EQU $AF023A
SP07_ADDY_PTR_H          EQU $AF023B
SP07_X_POS_L             EQU $AF023C
SP07_X_POS_H             EQU $AF023D
SP07_Y_POS_L             EQU $AF023E
SP07_Y_POS_H             EQU $AF023F
; Sprite 8
SP08_CONTROL_REG         EQU $AF0240
SP08_ADDY_PTR_L          EQU $AF0241
SP08_ADDY_PTR_M          EQU $AF0242
SP08_ADDY_PTR_H          EQU $AF0243
SP08_X_POS_L             EQU $AF0244
SP08_X_POS_H             EQU $AF0245
SP08_Y_POS_L             EQU $AF0246
SP08_Y_POS_H             EQU $AF0247
; Sprite 9
SP09_CONTROL_REG         EQU $AF0248
SP09_ADDY_PTR_L          EQU $AF0249
SP09_ADDY_PTR_M          EQU $AF024A
SP09_ADDY_PTR_H          EQU $AF024B
SP09_X_POS_L             EQU $AF024C
SP09_X_POS_H             EQU $AF024D
SP09_Y_POS_L             EQU $AF024E
SP09_Y_POS_H             EQU $AF024F
; Sprite 10
SP10_CONTROL_REG         EQU $AF0250
SP10_ADDY_PTR_L          EQU $AF0251
SP10_ADDY_PTR_M          EQU $AF0252
SP10_ADDY_PTR_H          EQU $AF0253
SP10_X_POS_L             EQU $AF0254
SP10_X_POS_H             EQU $AF0255
SP10_Y_POS_L             EQU $AF0256
SP10_Y_POS_H             EQU $AF0257
; Sprite 11
SP11_CONTROL_REG         EQU $AF0258
SP11_ADDY_PTR_L          EQU $AF0259
SP11_ADDY_PTR_M          EQU $AF025A
SP11_ADDY_PTR_H          EQU $AF025B
SP11_X_POS_L             EQU $AF025C
SP11_X_POS_H             EQU $AF025D
SP11_Y_POS_L             EQU $AF025E
SP11_Y_POS_H             EQU $AF025F
; Sprite 12
SP12_CONTROL_REG         EQU $AF0260
SP12_ADDY_PTR_L          EQU $AF0261
SP12_ADDY_PTR_M          EQU $AF0262
SP12_ADDY_PTR_H          EQU $AF0263
SP12_X_POS_L             EQU $AF0264
SP12_X_POS_H             EQU $AF0265
SP12_Y_POS_L             EQU $AF0266
SP12_Y_POS_H             EQU $AF0267
; Sprite 13
SP13_CONTROL_REG         EQU $AF0268
SP13_ADDY_PTR_L          EQU $AF0269
SP13_ADDY_PTR_M          EQU $AF026A
SP13_ADDY_PTR_H          EQU $AF026B
SP13_X_POS_L             EQU $AF026C
SP13_X_POS_H             EQU $AF026D
SP13_Y_POS_L             EQU $AF026E
SP13_Y_POS_H             EQU $AF026F
; Sprite 14
SP14_CONTROL_REG         EQU $AF0270
SP14_ADDY_PTR_L          EQU $AF0271
SP14_ADDY_PTR_M          EQU $AF0272
SP14_ADDY_PTR_H          EQU $AF0273
SP14_X_POS_L             EQU $AF0274
SP14_X_POS_H             EQU $AF0275
SP14_Y_POS_L             EQU $AF0276
SP14_Y_POS_H             EQU $AF0277
; Sprite 15
SP15_CONTROL_REG         EQU $AF0278
SP15_ADDY_PTR_L          EQU $AF0279
SP15_ADDY_PTR_M          EQU $AF027A
SP15_ADDY_PTR_H          EQU $AF027B
SP15_X_POS_L             EQU $AF027C
SP15_X_POS_H             EQU $AF027D
SP15_Y_POS_L             EQU $AF027E
SP15_Y_POS_H             EQU $AF027F
; Sprite 16
SP16_CONTROL_REG         EQU $AF0280
SP16_ADDY_PTR_L          EQU $AF0281
SP16_ADDY_PTR_M          EQU $AF0282
SP16_ADDY_PTR_H          EQU $AF0283
SP16_X_POS_L             EQU $AF0284
SP16_X_POS_H             EQU $AF0285
SP16_Y_POS_L             EQU $AF0286
SP16_Y_POS_H             EQU $AF0287
; Sprite 17
SP17_CONTROL_REG         EQU $AF0288
SP17_ADDY_PTR_L          EQU $AF0289
SP17_ADDY_PTR_M          EQU $AF028A
SP17_ADDY_PTR_H          EQU $AF028B
SP17_X_POS_L             EQU $AF028C
SP17_X_POS_H             EQU $AF028D
SP17_Y_POS_L             EQU $AF028E
SP17_Y_POS_H             EQU $AF028F
; DMA Controller $AF0400 - $AF04FF
VDMA_CONTROL_REG         EQU $AF0400
VDMA_COUNT_REG_L         EQU $AF0401
VDMA_COUNT_REG_M         EQU $AF0402
VDMA_COUNT_REG_H         EQU $AF0403
VDMA_DATA_2_WRITE_L      EQU $AF0404
VDMA_DATA_2_WRITE_H      EQU $AF0405
VDMA_STRIDE_L            EQU $AF0406
VDMA_STRIDE_H            EQU $AF0407
VDMA_SRC_ADDY_L          EQU $AF0408
VDMA_SRC_ADDY_M          EQU $AF0409
VDMA_SRC_ADDY_H          EQU $AF040A
VDMA_RESERVED_0          EQU $AF040B
VDMA_DST_ADDY_L          EQU $AF040C
VDMA_DST_ADDY_M          EQU $AF040D
VDMA_DST_ADDY_H          EQU $AF040E
VDMA_RESERVED_1          EQU $AF040F


FG_CHAR_LUT_PTR          EQU $AF1F40
BG_CHAR_LUT_PTR		       EQU $AF1F80

GRPH_LUT0_PTR		         EQU $AF2000
GRPH_LUT1_PTR		         EQU $AF2400
GRPH_LUT2_PTR		         EQU $AF2800
GRPH_LUT3_PTR		         EQU $AF2C00
GRPH_LUT4_PTR		         EQU $AF3000
GRPH_LUT5_PTR		         EQU $AF3400
GRPH_LUT6_PTR		         EQU $AF3800
GRPH_LUT7_PTR		         EQU $AF3C00

GAMMA_B_LUT_PTR		       EQU $AF4000
GAMMA_G_LUT_PTR		       EQU $AF4100
GAMMA_R_LUT_PTR		       EQU $AF4200

TILE_MAP0       		     EQU $AF5000     ;$AF5000 - $AF57FF
TILE_MAP1                EQU $AF5800     ;$AF5800 - $AF5FFF
TILE_MAP2                EQU $AF6000     ;$AF6000 - $AF67FF
TILE_MAP3                EQU $AF6800     ;$AF6800 - $AF6FFF

FONT_MEMORY_BANK         EQU $AF8000     ;$AF8000 - $AFBFFF
CS_TEXT_MEM_PTR          EQU $AFA000
CS_COLOR_MEM_PTR         EQU $AFC000

BMP_X_SIZE       EQU $000040 ; 2 Bytes
BM_CLEAR_SCRN_X  EQU $000040
BMP_Y_SIZE       EQU $000042 ; 2 Bytes
BM_CLEAR_SCRN_Y  EQU $000042
BMP_PRSE_SRC_PTR EQU $000044 ; 3 Bytes
BMP_PRSE_DST_PTR EQU $000048 ; 3 Bytes
BMP_COLOR_PALET  EQU $00004C ; 2 Bytes
SCRN_X_STRIDE    EQU $00004E ; 2 Bytes, Basically How many Pixel Accross in Bitmap Mode
BMP_FILE_SIZE    EQU $000050 ; 4 Bytes
BMP_POSITION_X   EQU $000054 ; 2 Bytes Where, the BMP will be position on the X Axis
BMP_POSITION_Y   EQU $000056 ; 2 Bytes Where, the BMP will be position on the Y Axis
BMP_PALET_CHOICE EQU $000058 ;


BTX_START                EQU $AFE000     ; BEATRIX Registers
BTX_END                  EQU $AFFFFF


; Joystick Ports
JOYSTICK0     = $AFE800  ;(R) Joystick 0 - J7 (Next to Buzzer)
JOYSTICK1     = $AFE801  ;(R) Joystick 1 - J8
JOYSTICK2     = $AFE802  ;(R) Joystick 2 - J9
JOYSTICK3     = $AFE803  ;(R) Joystick 3 - J10 (next to SD Card)
; Dip switch Ports
DIPSWITCH     = $AFE804  ;(R) $AFE804...$AFE807
; SD Card CH376S Port
SDCARD_DATA   = $AFE808  ;(R/W) SDCARD (CH376S) Data PORT_A (A0 = 0)
SDCARD_CMD    = $AFE809  ;(R/W) SDCARD (CH376S) CMD/STATUS Port (A0 = 1)
; SD Card Card Presence / Write Protect Status Reg
SDCARD_STAT   = $AFE810  ;(R) SDCARD (Bit[0] = CD, Bit[1] = WP)
; Audio WM8776 CODEC Control Interface (Write Only)
CODEC_DATA_LO = $AFE820  ;(W) LSB of Add/Data Reg to Control CODEC See WM8776 Spec
CODEC_DATA_HI = $AFE821  ;(W) MSB od Add/Data Reg to Control CODEC See WM8776 Spec
CODEC_WR_CTRL = $AFE822  ;(W) Bit[0] = 1 -> Start Writing the CODEC Control Register

OPL2_L_BASE               = $AFE500
OPL2_L_TEST               = $AFE501 ; TEST
OPL2_L_TIMER1             = $AFE502 ; TIMER-1
OPL2_L_TIMER2             = $AFE503 ; TIMER-2
OPL2_L_IRQ                = $AFE504 ;
OPL2_L_CSM                = $AFE508 ;
OPL2_L_AM_VID_EG_KSR_MULT = $AFE520 ; $40..$35 (21 Registers)
OPL2_L_KSL_TL             = $AFEE40;  $40..$55 (21 Registers)
OPL2_L_AR_DR              = $AFE560;  $60..$75 (21 Registers)
OPL2_L_SL_RR              = $AFE580;  $80..$95 (21 Registers)
OPL2_L_FNumber            = $AFE5A0;  $A0..$A8
OPL2_L_KON_BLOCK_FNumber  = $AFE5B0;  $B0..$B9
OPL2_L_DPTH_RHYTM         = $AFE5BD;  $BD
OPL2_L_FEEDBACK           = $AFE5C0;  $C0..$C9
OPL2_L_WAVE_SELECT        = $AFE5E0;  $E0..$F5
; Direct Access to Right Channel
; R = Right
OPL2_R_BASE               = $AFE600
OPL2_R_TEST               = $AFE601 ; TEST
OPL2_R_TIMER1             = $AFE602 ; TIMER-1
OPL2_R_TIMER2             = $AFE603 ; TIMER-2
OPL2_R_IRQ                = $AFE604 ;
OPL2_R_CSM                = $AFE608 ;
OPL2_R_AM_VID_EG_KSR_MULT = $AFE620 ; $40..$35 (21 Registers)
OPL2_R_KSL_TL             = $AFE640;  $40..$55 (21 Registers)
OPL2_R_AR_DR              = $AFE660;  $60..$75 (21 Registers)
OPL2_R_SL_RR              = $AFE680;  $80..$95 (21 Registers)
OPL2_R_FNumber            = $AFE6A0;  $A0..$A8
OPL2_R_KON_BLOCK_FNumber  = $AFE6B0;  $B0..$B9
OPL2_R_DPTH_RHYTM         = $AFE6BD;  $BD
OPL2_R_FEEDBACK           = $AFE6C0;  $C0..$C9
OPL2_R_WAVE_SELECT        = $AFE6E0;  $E0..$F5
This is the OPL2 in the same range
; Direct Access to Both at the same time (Write Only of course)
; S = Stereo
OPL2_S_BASE_LL            = $E700
OPL2_S_BASE_HL            = $00AF
OPL2_S_TEST               = $AFE701 ; TEST
OPL2_S_TIMER1             = $AFE702 ; TIMER-1
OPL2_S_TIMER2             = $AFE703 ; TIMER-2
OPL2_S_IRQ                = $AFE704 ;
OPL2_S_CSM                = $AFE708 ;
OPL2_S_AM_VID_EG_KSR_MULT = $AFE720 ; $40..$35 (21 Registers)
OPL2_S_KSL_TL             = $AFE740;  $40..$55 (21 Registers)
OPL2_S_AR_DR              = $AFE760;  $60..$75 (21 Registers)
OPL2_S_SL_RR              = $AFE780;  $80..$95 (21 Registers)
OPL2_S_FNumber            = $AFE7A0;  $A0..$A8
OPL2_S_KON_BLOCK_FNumber  = $AFE7B0;  $B0..$B9
OPL2_S_DPTH_RHYTM         = $AFE7BD;  $BD
OPL2_S_FEEDBACK           = $AFE7C0;  $C0..$C9
OPL2_S_WAVE_SELECT        = $AFE7E0;  $E0..$F5


*/


#ifdef USING_816
	
	#ifdef USING_DEBUG	

	#else

	#endif
	
//* Addresses are the byte AFTER the block. Use this to confirm block locations and check for overlaps
	#define BANK0_BEGIN       ((VOLATILE unsigned char far*)0x000000) 
	//Start of bank 0 and Direct page
	#define unused_0000       ((VOLATILE unsigned char far*)0x000000) 
	//12 Bytes unused
	#define SCREENBEGIN       ((VOLATILE unsigned char far*)0x00000C) 
	//3 Bytes Start of screen in video RAM. This is the upper-left corrner of the current video page being written to. This may not be what's being displayed by VICKY. Update this if you change VICKY's display page.
	#define COLS_VISIBLE      ((VOLATILE unsigned char far*)0x00000F) 
	//2 Bytes Columns visible per screen line. A virtual line can be longer than displayed, up to COLS_PER_LINE long. Default  80
	#define COLS_PER_LINE     ((VOLATILE unsigned char far*)0x000011) 
	//2 Bytes Columns in memory per screen line. A virtual line can be this long. Default128
	#define LINES_VISIBLE     ((VOLATILE unsigned char far*)0x000013) 
	//2 Bytes The number of rows visible on the screen. Default25
	#define LINES_MAX         ((VOLATILE unsigned char far*)0x000015) 
	//2 Bytes The number of rows in memory for the screen. Default64
	#define CURSORPOS         ((VOLATILE unsigned char far*)0x000017) 
	//3 Bytes The next character written to the screen will be written in this location.
	#define CURSORX           ((VOLATILE unsigned char far*)0x00001A) 
	//2 Bytes This is where the blinking cursor sits. Do not edit this direectly. Call LOCATE to update the location and handle moving the cursor correctly.
	#define CURSORY           ((VOLATILE unsigned char far*)0x00001C) 
	//2 Bytes This is where the blinking cursor sits. Do not edit this direectly. Call LOCATE to update the location and handle moving the cursor correctly.
	#define CURCOLOR_L        ((VOLATILE unsigned char far*)0x00001E) 
	//2 Bytes Color of next character to be printed to the screen.
	#define CURCOLOR_H        ((VOLATILE unsigned char far*)0x00001F) 
	//2 Bytes Color of next character to be printed to the screen.
	#define CURATTR           ((VOLATILE unsigned char far*)0x000020) 
	//2 Bytes Attribute of next character to be printed to the screen.
	#define STACKBOT          ((VOLATILE unsigned char far*)0x000022) 
	//2 Bytes Lowest location the stack should be allowed to write to. If SP falls below this value, the runtime should generate STACK OVERFLOW error and abort.
	#define STACKTOP          ((VOLATILE unsigned char far*)0x000024) 
	//2 Bytes Highest location the stack can occupy. If SP goes above this value, the runtime should generate STACK OVERFLOW error and abort.
	
	
	
	//CONTROL BITS FIELDS)
	#define MSTR_CTRL_TEXT_MODE_EN    (0x01)
	#define MSTR_CTRL_TEXT_OVERLAY    (0x02)
	//        ENABLE THE OVERLAY OF THE TEXT MODE ON TOP OF GRAPHIC MODE (THE BACKGROUND COLOR IS IGNORED))
	#define MSTR_CTRL_GRAPH_MODE_EN   (0x04)
	#define MSTR_CTRL_BITMAP_EN       (0x08)
	#define MSTR_CTRL_TILEMAP_EN      (0x10)
	#define MSTR_CTRL_SPRITE_EN       (0x20)
	#define MSTR_CTRL_GAMMA_EN        (0x40)
	#define MSTR_CTRL_DISABLE_VID     (0x80)
	#define MASTER_CTRL_REG_L	   ((VOLATILE unsigned char far*)0xAF0000)
	#define MASTER_CTRL_REG_H	   ((VOLATILE unsigned char far*)0xAF0001)
	
	#define VKY_RESERVED_00           ((VOLATILE unsigned char far*)0xAF0002)
	#define VKY_RESERVED_01           ((VOLATILE unsigned char far*)0xAF0003)
	#define BORDER_CTRL_REG           ((VOLATILE unsigned char far*)0xAF0004)
	#define BORDER_CTRL_ENABLE        0x01
	#define BORDER_COLOR_B            ((VOLATILE unsigned char far*)0xAF0005)
	#define BORDER_COLOR_G            ((VOLATILE unsigned char far*)0xAF0006)
	#define BORDER_COLOR_R            ((VOLATILE unsigned char far*)0xAF0007)

	#define VKY_TXT_CURSOR_CTRL_REG   ((VOLATILE unsigned char far*)0xAF0010)
	//   [0]  ENABLE TEXT MODE)
	#define VKY_CURSOR_ENABLE         (0x01)
	#define VKY_CURSOR_FLASH_RATE0    (0x02)
	#define VKY_CURSOR_FLASH_RATE1    (0x04)
	#define VKY_CURSOR_FONT_PAGE0     (0x08)
	//        PICK FONT PAGE 0 OR FONT PAGE 1)
	#define VKY_CURSOR_FONT_PAGE1     (0x10)
	//       PICK FONT PAGE 0 OR FONT PAGE 1)
	#define VKY_TXT_RESERVED          ((VOLATILE unsigned char far*)0xAF0011)
	//   NOT IN USE)
	#define VKY_TXT_CURSOR_CHAR_REG   ((VOLATILE unsigned char far*)0xAF0012)

	#define VKY_TXT_CURSOR_COLR_REG   ((VOLATILE unsigned char far*)0xAF0013)
	#define VKY_TXT_CURSOR_X_REG_L    ((VOLATILE unsigned char far*)0xAF0014)
	#define VKY_TXT_CURSOR_X_REG_H    ((VOLATILE unsigned char far*)0xAF0015)
	#define VKY_TXT_CURSOR_Y_REG_L    ((VOLATILE unsigned char far*)0xAF0016)
	#define VKY_TXT_CURSOR_Y_REG_H    ((VOLATILE unsigned char far*)0xAF0017)

	#define VKY_INFO_CHIP_NUM_L       ((VOLATILE unsigned char far*)0xAF001C)
	#define VKY_INFO_CHIP_NUM_H       ((VOLATILE unsigned char far*)0xAF001D)
	#define VKY_INFO_CHIP_VER_L       ((VOLATILE unsigned char far*)0xAF001E)
	#define VKY_INFO_CHIP_VER_H       ((VOLATILE unsigned char far*)0xAF001F)

	//)
	// BIT FIELD DEFINITION FOR THE CONTROL REGISTER)
	#define TILE_ENABLE               ((VOLATILE unsigned char far*)0x01)
	#define TILE_LUT0                 ((VOLATILE unsigned char far*)0x02)
	#define TILE_LUT1                 ((VOLATILE unsigned char far*)0x04)
	#define TILE_LUT2                 ((VOLATILE unsigned char far*)0x08)
	#define TILESHEET_256X256_EN      ((VOLATILE unsigned char far*)0x80)
	//    0 -> SEQUENTIAL, 1-> 256X256 TILE SHEET STRIDING)
	//)
	//TILE MAP LAYER 0 REGISTERS)
	#define TL0_CONTROL_REG           ((VOLATILE unsigned char far*)0xAF0100)
	//        BIT[0] - ENABLE, BIT[3:1] - LUT SELECT,)
	#define TL0_START_ADDY_L          ((VOLATILE unsigned char far*)0xAF0101)
	//        NOT USED RIGHT NOW - STARTING ADDRESS TO WHERE IS THE MAP)
	#define TL0_START_ADDY_M          ((VOLATILE unsigned char far*)0xAF0102)
	#define TL0_START_ADDY_H          ((VOLATILE unsigned char far*)0xAF0103)
	#define TL0_MAP_X_STRIDE_L        ((VOLATILE unsigned char far*)0xAF0104)
	//        THE STRIDE OF THE MAP)
	#define TL0_MAP_X_STRIDE_H        ((VOLATILE unsigned char far*)0xAF0105)
	#define TL0_MAP_Y_STRIDE_L        ((VOLATILE unsigned char far*)0xAF0106)
	//        THE STRIDE OF THE MAP)
	#define TL0_MAP_Y_STRIDE_H        ((VOLATILE unsigned char far*)0xAF0107)
	//TL0_RESERVED_0            ((VOLATILE unsigned char far*)0xAF0108)
	//TL0_RESERVED_1            ((VOLATILE unsigned char far*)0xAF0109)
	//TL0_RESERVED_2            ((VOLATILE unsigned char far*)0xAF010A)
	//TL0_RESERVED_3            ((VOLATILE unsigned char far*)0xAF010B)
	//TL0_RESERVED_4            ((VOLATILE unsigned char far*)0xAF010C)
	//TL0_RESERVED_5            ((VOLATILE unsigned char far*)0xAF010D)
	//TL0_RESERVED_6            ((VOLATILE unsigned char far*)0xAF010E)
	//TL0_RESERVED_7            ((VOLATILE unsigned char far*)0xAF010F)
	//TILE MAP LAYER 1 REGISTERS)
	#define TL1_CONTROL_REG           ((VOLATILE unsigned char far*)0xAF0108)
	//        BIT[0] - ENABLE, BIT[3:1] - LUT SELECT,)
	#define TL1_START_ADDY_L          ((VOLATILE unsigned char far*)0xAF0109)
	//        NOT USED RIGHT NOW - STARTING ADDRESS TO WHERE IS THE MAP)
	#define TL1_START_ADDY_M          ((VOLATILE unsigned char far*)0xAF010A)
	#define TL1_START_ADDY_H          ((VOLATILE unsigned char far*)0xAF010B)
	#define TL1_MAP_X_STRIDE_L        ((VOLATILE unsigned char far*)0xAF010C)
	//        THE STRIDE OF THE MAP)
	#define TL1_MAP_X_STRIDE_H        ((VOLATILE unsigned char far*)0xAF010D)
	#define TL1_MAP_Y_STRIDE_L        ((VOLATILE unsigned char far*)0xAF010E)
	//        THE STRIDE OF THE MAP)
	#define TL1_MAP_Y_STRIDE_H        ((VOLATILE unsigned char far*)0xAF010F)
	//TL1_RESERVED_0            ((VOLATILE unsigned char far*)0xAF0118)
	//TL1_RESERVED_1            ((VOLATILE unsigned char far*)0xAF0119)
	//TL1_RESERVED_2            ((VOLATILE unsigned char far*)0xAF011A)
	//TL1_RESERVED_3            ((VOLATILE unsigned char far*)0xAF011B)
	//TL1_RESERVED_4            ((VOLATILE unsigned char far*)0xAF011C)
	//TL1_RESERVED_5            ((VOLATILE unsigned char far*)0xAF011D)
	//TL1_RESERVED_6            ((VOLATILE unsigned char far*)0xAF011E)
	//TL1_RESERVED_7            ((VOLATILE unsigned char far*)0xAF011F)
	//TILE MAP LAYER 2 REGISTERS)
	#define TL2_CONTROL_REG           ((VOLATILE unsigned char far*)0xAF0110)
	//        BIT[0] - ENABLE, BIT[3:1] - LUT SELECT,)
	#define TL2_START_ADDY_L          ((VOLATILE unsigned char far*)0xAF0111)
	//        NOT USED RIGHT NOW - STARTING ADDRESS TO WHERE IS THE MAP)
	#define TL2_START_ADDY_M          ((VOLATILE unsigned char far*)0xAF0112)
	#define TL2_START_ADDY_H          ((VOLATILE unsigned char far*)0xAF0113)
	#define TL2_MAP_X_STRIDE_L        ((VOLATILE unsigned char far*)0xAF0114)
	//        THE STRIDE OF THE MAP)
	#define TL2_MAP_X_STRIDE_H        ((VOLATILE unsigned char far*)0xAF0115)
	#define TL2_MAP_Y_STRIDE_L        ((VOLATILE unsigned char far*)0xAF0116)
	//        THE STRIDE OF THE MAP)
	#define TL2_MAP_Y_STRIDE_H        ((VOLATILE unsigned char far*)0xAF0117)
	//TL2_RESERVED_0            ((VOLATILE unsigned char far*)0xAF0128)
	//TL2_RESERVED_1            ((VOLATILE unsigned char far*)0xAF0129)
	//TL2_RESERVED_2            ((VOLATILE unsigned char far*)0xAF012A)
	//TL2_RESERVED_3            ((VOLATILE unsigned char far*)0xAF012B)
	//TL2_RESERVED_4            ((VOLATILE unsigned char far*)0xAF012C)
	//TL2_RESERVED_5            ((VOLATILE unsigned char far*)0xAF012D)
	//TL2_RESERVED_6            ((VOLATILE unsigned char far*)0xAF012E)
	//TL2_RESERVED_7            ((VOLATILE unsigned char far*)0xAF012F)
	//TILE MAP LAYER 3 REGISTERS)
	#define TL3_CONTROL_REG           ((VOLATILE unsigned char far*)0xAF0118)
	//        BIT[0] - ENABLE, BIT[3:1] - LUT SELECT,)
	#define TL3_START_ADDY_L          ((VOLATILE unsigned char far*)0xAF0119)
	//        NOT USED RIGHT NOW - STARTING ADDRESS TO WHERE IS THE MAP)
	#define TL3_START_ADDY_M          ((VOLATILE unsigned char far*)0xAF011A)
	#define TL3_START_ADDY_H          ((VOLATILE unsigned char far*)0xAF011B)
	#define TL3_MAP_X_STRIDE_L        ((VOLATILE unsigned char far*)0xAF011C)
	//        THE STRIDE OF THE MAP)
	#define TL3_MAP_X_STRIDE_H        ((VOLATILE unsigned char far*)0xAF011D)
	#define TL3_MAP_Y_STRIDE_L        ((VOLATILE unsigned char far*)0xAF011E)
	//        THE STRIDE OF THE MAP)
	#define TL3_MAP_Y_STRIDE_H        ((VOLATILE unsigned char far*)0xAF011F)
	//TL3_RESERVED_0            ((VOLATILE unsigned char far*)0xAF0138)
	//TL3_RESERVED_1            ((VOLATILE unsigned char far*)0xAF0139)
	//TL3_RESERVED_2            ((VOLATILE unsigned char far*)0xAF013A)
	//TL3_RESERVED_3            ((VOLATILE unsigned char far*)0xAF013B)
	//TL3_RESERVED_4            ((VOLATILE unsigned char far*)0xAF013C)
	//TL3_RESERVED_5            ((VOLATILE unsigned char far*)0xAF013D)
	//TL3_RESERVED_6            ((VOLATILE unsigned char far*)0xAF013E)
	//TL3_RESERVED_7            ((VOLATILE unsigned char far*)0xAF013F)
	//BITMAP REGISTERS)
	#define BM_CONTROL_REG            ((VOLATILE unsigned char far*)0xAF0140)
	#define BM_START_ADDY_L           ((VOLATILE unsigned char far*)0xAF0141)
	#define BM_START_ADDY_M           ((VOLATILE unsigned char far*)0xAF0142)
	#define BM_START_ADDY_H           ((VOLATILE unsigned char far*)0xAF0143)
	#define BM_X_SIZE_L               ((VOLATILE unsigned char far*)0xAF0144)
	#define BM_X_SIZE_H               ((VOLATILE unsigned char far*)0xAF0145)
	#define BM_Y_SIZE_L               ((VOLATILE unsigned char far*)0xAF0146)
	#define BM_Y_SIZE_H               ((VOLATILE unsigned char far*)0xAF0147)

	#define ASM_BM_CONTROL_REG           $AF0140
	#define ASM_BM_START_ADDY_L          $AF0141
	#define ASM_BM_START_ADDY_M          $AF0142
	#define ASM_BM_START_ADDY_H          $AF0143
	#define ASM_BM_X_SIZE_L              $AF0144
	#define ASM_BM_X_SIZE_H              $AF0145
	#define ASM_BM_Y_SIZE_L              $AF0146
	#define ASM_BM_Y_SIZE_H              $AF0147


	#define BM_RESERVED_0             ((VOLATILE unsigned char far*)0xAF0148)
	#define BM_RESERVED_1             ((VOLATILE unsigned char far*)0xAF0149)
	#define BM_RESERVED_2             ((VOLATILE unsigned char far*)0xAF014A)
	#define BM_RESERVED_3             ((VOLATILE unsigned char far*)0xAF014B)
	#define BM_RESERVED_4             ((VOLATILE unsigned char far*)0xAF014C)
	#define BM_RESERVED_5             ((VOLATILE unsigned char far*)0xAF014D)
	#define BM_RESERVED_6             ((VOLATILE unsigned char far*)0xAF014E)
	#define BM_RESERVED_7             ((VOLATILE unsigned char far*)0xAF014F)
	//SPRITE REGISTERS)
	// BIT FIELD DEFINITION FOR THE CONTROL REGISTER)
	#define SPRITE_ENABLE               ((VOLATILE unsigned char far*)0x01)
	#define SPRITE_LUT0                 ((VOLATILE unsigned char far*)0x02)
	#define SPRITE_LUT1                 ((VOLATILE unsigned char far*)0x04)
	#define SPRITE_LUT2                 ((VOLATILE unsigned char far*)0x08)
	#define SPRITE_DEPTH0               ((VOLATILE unsigned char far*)0x10)
	#define SPRITE_DEPTH1               ((VOLATILE unsigned char far*)0x20)
	#define SPRITE_DEPTH2               ((VOLATILE unsigned char far*)0x40)

	// SPRITE 0 (HIGHEST PRIORITY))
	#define SP00_CONTROL_REG          ((VOLATILE unsigned char far*)0xAF0200)
	#define SP00_ADDY_PTR_L           ((VOLATILE unsigned char far*)0xAF0201)
	#define SP00_ADDY_PTR_M           ((VOLATILE unsigned char far*)0xAF0202)
	#define SP00_ADDY_PTR_H           ((VOLATILE unsigned char far*)0xAF0203)
	#define SP00_X_POS_L              ((VOLATILE unsigned char far*)0xAF0204)
	#define SP00_X_POS_H              ((VOLATILE unsigned char far*)0xAF0205)
	#define SP00_Y_POS_L              ((VOLATILE unsigned char far*)0xAF0206)
	#define SP00_Y_POS_H              ((VOLATILE unsigned char far*)0xAF0207)
	// SPRITE 1)
	#define SP01_CONTROL_REG          ((VOLATILE unsigned char far*)0xAF0208)
	#define SP01_ADDY_PTR_L           ((VOLATILE unsigned char far*)0xAF0209)
	#define SP01_ADDY_PTR_M           ((VOLATILE unsigned char far*)0xAF020A)
	#define SP01_ADDY_PTR_H           ((VOLATILE unsigned char far*)0xAF020B)
	#define SP01_X_POS_L              ((VOLATILE unsigned char far*)0xAF020C)
	#define SP01_X_POS_H              ((VOLATILE unsigned char far*)0xAF020D)
	#define SP01_Y_POS_L              ((VOLATILE unsigned char far*)0xAF020E)
	#define SP01_Y_POS_H              ((VOLATILE unsigned char far*)0xAF020F)
	// SPRITE 2)
	#define SP02_CONTROL_REG          ((VOLATILE unsigned char far*)0xAF0210)
	#define SP02_ADDY_PTR_L           ((VOLATILE unsigned char far*)0xAF0211)
	#define SP02_ADDY_PTR_M           ((VOLATILE unsigned char far*)0xAF0212)
	#define SP02_ADDY_PTR_H           ((VOLATILE unsigned char far*)0xAF0213)
	#define SP02_X_POS_L              ((VOLATILE unsigned char far*)0xAF0214)
	#define SP02_X_POS_H              ((VOLATILE unsigned char far*)0xAF0215)
	#define SP02_Y_POS_L              ((VOLATILE unsigned char far*)0xAF0216)
	#define SP02_Y_POS_H              ((VOLATILE unsigned char far*)0xAF0217)
	// SPRITE 3)
	#define SP03_CONTROL_REG          ((VOLATILE unsigned char far*)0xAF0218)
	#define SP03_ADDY_PTR_L           ((VOLATILE unsigned char far*)0xAF0219)
	#define SP03_ADDY_PTR_M           ((VOLATILE unsigned char far*)0xAF021A)
	#define SP03_ADDY_PTR_H           ((VOLATILE unsigned char far*)0xAF021B)
	#define SP03_X_POS_L              ((VOLATILE unsigned char far*)0xAF021C)
	#define SP03_X_POS_H              ((VOLATILE unsigned char far*)0xAF021D)
	#define SP03_Y_POS_L              ((VOLATILE unsigned char far*)0xAF021E)
	#define SP03_Y_POS_H              ((VOLATILE unsigned char far*)0xAF021F)
	// SPRITE 4)
	#define SP04_CONTROL_REG          ((VOLATILE unsigned char far*)0xAF0220)
	#define SP04_ADDY_PTR_L           ((VOLATILE unsigned char far*)0xAF0221)
	#define SP04_ADDY_PTR_M           ((VOLATILE unsigned char far*)0xAF0222)
	#define SP04_ADDY_PTR_H           ((VOLATILE unsigned char far*)0xAF0223)
	#define SP04_X_POS_L              ((VOLATILE unsigned char far*)0xAF0224)
	#define SP04_X_POS_H              ((VOLATILE unsigned char far*)0xAF0225)
	#define SP04_Y_POS_L              ((VOLATILE unsigned char far*)0xAF0226)
	#define SP04_Y_POS_H              ((VOLATILE unsigned char far*)0xAF0227)
	// SPRITE 5)
	#define SP05_CONTROL_REG          ((VOLATILE unsigned char far*)0xAF0228)
	#define SP05_ADDY_PTR_L           ((VOLATILE unsigned char far*)0xAF0229)
	#define SP05_ADDY_PTR_M           ((VOLATILE unsigned char far*)0xAF022A)
	#define SP05_ADDY_PTR_H           ((VOLATILE unsigned char far*)0xAF022B)
	#define SP05_X_POS_L              ((VOLATILE unsigned char far*)0xAF022C)
	#define SP05_X_POS_H              ((VOLATILE unsigned char far*)0xAF022D)
	#define SP05_Y_POS_L              ((VOLATILE unsigned char far*)0xAF022E)
	#define SP05_Y_POS_H              ((VOLATILE unsigned char far*)0xAF022F)
	// SPRITE 6)
	#define SP06_CONTROL_REG          ((VOLATILE unsigned char far*)0xAF0230)
	#define SP06_ADDY_PTR_L           ((VOLATILE unsigned char far*)0xAF0231)
	#define SP06_ADDY_PTR_M           ((VOLATILE unsigned char far*)0xAF0232)
	#define SP06_ADDY_PTR_H           ((VOLATILE unsigned char far*)0xAF0233)
	#define SP06_X_POS_L              ((VOLATILE unsigned char far*)0xAF0234)
	#define SP06_X_POS_H              ((VOLATILE unsigned char far*)0xAF0235)
	#define SP06_Y_POS_L              ((VOLATILE unsigned char far*)0xAF0236)
	#define SP06_Y_POS_H              ((VOLATILE unsigned char far*)0xAF0237)
	// SPRITE 7)
	#define SP07_CONTROL_REG          ((VOLATILE unsigned char far*)0xAF0238)
	#define SP07_ADDY_PTR_L           ((VOLATILE unsigned char far*)0xAF0239)
	#define SP07_ADDY_PTR_M           ((VOLATILE unsigned char far*)0xAF023A)
	#define SP07_ADDY_PTR_H           ((VOLATILE unsigned char far*)0xAF023B)
	#define SP07_X_POS_L              ((VOLATILE unsigned char far*)0xAF023C)
	#define SP07_X_POS_H              ((VOLATILE unsigned char far*)0xAF023D)
	#define SP07_Y_POS_L              ((VOLATILE unsigned char far*)0xAF023E)
	#define SP07_Y_POS_H              ((VOLATILE unsigned char far*)0xAF023F)
	// SPRITE 8)
	#define SP08_CONTROL_REG          ((VOLATILE unsigned char far*)0xAF0240)
	#define SP08_ADDY_PTR_L           ((VOLATILE unsigned char far*)0xAF0241)
	#define SP08_ADDY_PTR_M           ((VOLATILE unsigned char far*)0xAF0242)
	#define SP08_ADDY_PTR_H           ((VOLATILE unsigned char far*)0xAF0243)
	#define SP08_X_POS_L              ((VOLATILE unsigned char far*)0xAF0244)
	#define SP08_X_POS_H              ((VOLATILE unsigned char far*)0xAF0245)
	#define SP08_Y_POS_L              ((VOLATILE unsigned char far*)0xAF0246)
	#define SP08_Y_POS_H              ((VOLATILE unsigned char far*)0xAF0247)
	// SPRITE 9)
	#define SP09_CONTROL_REG          ((VOLATILE unsigned char far*)0xAF0248)
	#define SP09_ADDY_PTR_L           ((VOLATILE unsigned char far*)0xAF0249)
	#define SP09_ADDY_PTR_M           ((VOLATILE unsigned char far*)0xAF024A)
	#define SP09_ADDY_PTR_H           ((VOLATILE unsigned char far*)0xAF024B)
	#define SP09_X_POS_L              ((VOLATILE unsigned char far*)0xAF024C)
	#define SP09_X_POS_H              ((VOLATILE unsigned char far*)0xAF024D)
	#define SP09_Y_POS_L              ((VOLATILE unsigned char far*)0xAF024E)
	#define SP09_Y_POS_H              ((VOLATILE unsigned char far*)0xAF024F)
	// SPRITE 10)
	#define SP10_CONTROL_REG          ((VOLATILE unsigned char far*)0xAF0250)
	#define SP10_ADDY_PTR_L           ((VOLATILE unsigned char far*)0xAF0251)
	#define SP10_ADDY_PTR_M           ((VOLATILE unsigned char far*)0xAF0252)
	#define SP10_ADDY_PTR_H           ((VOLATILE unsigned char far*)0xAF0253)
	#define SP10_X_POS_L              ((VOLATILE unsigned char far*)0xAF0254)
	#define SP10_X_POS_H              ((VOLATILE unsigned char far*)0xAF0255)
	#define SP10_Y_POS_L              ((VOLATILE unsigned char far*)0xAF0256)
	#define SP10_Y_POS_H              ((VOLATILE unsigned char far*)0xAF0257)
	// SPRITE 11)
	#define SP11_CONTROL_REG          ((VOLATILE unsigned char far*)0xAF0258)
	#define SP11_ADDY_PTR_L           ((VOLATILE unsigned char far*)0xAF0259)
	#define SP11_ADDY_PTR_M           ((VOLATILE unsigned char far*)0xAF025A)
	#define SP11_ADDY_PTR_H           ((VOLATILE unsigned char far*)0xAF025B)
	#define SP11_X_POS_L              ((VOLATILE unsigned char far*)0xAF025C)
	#define SP11_X_POS_H              ((VOLATILE unsigned char far*)0xAF025D)
	#define SP11_Y_POS_L              ((VOLATILE unsigned char far*)0xAF025E)
	#define SP11_Y_POS_H              ((VOLATILE unsigned char far*)0xAF025F)
	// SPRITE 12)
	#define SP12_CONTROL_REG          ((VOLATILE unsigned char far*)0xAF0260)
	#define SP12_ADDY_PTR_L           ((VOLATILE unsigned char far*)0xAF0261)
	#define SP12_ADDY_PTR_M           ((VOLATILE unsigned char far*)0xAF0262)
	#define SP12_ADDY_PTR_H           ((VOLATILE unsigned char far*)0xAF0263)
	#define SP12_X_POS_L              ((VOLATILE unsigned char far*)0xAF0264)
	#define SP12_X_POS_H              ((VOLATILE unsigned char far*)0xAF0265)
	#define SP12_Y_POS_L              ((VOLATILE unsigned char far*)0xAF0266)
	#define SP12_Y_POS_H              ((VOLATILE unsigned char far*)0xAF0267)
	// SPRITE 13)
	#define SP13_CONTROL_REG          ((VOLATILE unsigned char far*)0xAF0268)
	#define SP13_ADDY_PTR_L           ((VOLATILE unsigned char far*)0xAF0269)
	#define SP13_ADDY_PTR_M           ((VOLATILE unsigned char far*)0xAF026A)
	#define SP13_ADDY_PTR_H           ((VOLATILE unsigned char far*)0xAF026B)
	#define SP13_X_POS_L              ((VOLATILE unsigned char far*)0xAF026C)
	#define SP13_X_POS_H              ((VOLATILE unsigned char far*)0xAF026D)
	#define SP13_Y_POS_L              ((VOLATILE unsigned char far*)0xAF026E)
	#define SP13_Y_POS_H              ((VOLATILE unsigned char far*)0xAF026F)
	// SPRITE 14)
	#define SP14_CONTROL_REG          ((VOLATILE unsigned char far*)0xAF0270)
	#define SP14_ADDY_PTR_L           ((VOLATILE unsigned char far*)0xAF0271)
	#define SP14_ADDY_PTR_M           ((VOLATILE unsigned char far*)0xAF0272)
	#define SP14_ADDY_PTR_H           ((VOLATILE unsigned char far*)0xAF0273)
	#define SP14_X_POS_L              ((VOLATILE unsigned char far*)0xAF0274)
	#define SP14_X_POS_H              ((VOLATILE unsigned char far*)0xAF0275)
	#define SP14_Y_POS_L              ((VOLATILE unsigned char far*)0xAF0276)
	#define SP14_Y_POS_H              ((VOLATILE unsigned char far*)0xAF0277)
	// SPRITE 15)
	#define SP15_CONTROL_REG          ((VOLATILE unsigned char far*)0xAF0278)
	#define SP15_ADDY_PTR_L           ((VOLATILE unsigned char far*)0xAF0279)
	#define SP15_ADDY_PTR_M           ((VOLATILE unsigned char far*)0xAF027A)
	#define SP15_ADDY_PTR_H           ((VOLATILE unsigned char far*)0xAF027B)
	#define SP15_X_POS_L              ((VOLATILE unsigned char far*)0xAF027C)
	#define SP15_X_POS_H              ((VOLATILE unsigned char far*)0xAF027D)
	#define SP15_Y_POS_L              ((VOLATILE unsigned char far*)0xAF027E)
	#define SP15_Y_POS_H              ((VOLATILE unsigned char far*)0xAF027F)
	// SPRITE 16)
	#define SP16_CONTROL_REG          ((VOLATILE unsigned char far*)0xAF0280)
	#define SP16_ADDY_PTR_L           ((VOLATILE unsigned char far*)0xAF0281)
	#define SP16_ADDY_PTR_M           ((VOLATILE unsigned char far*)0xAF0282)
	#define SP16_ADDY_PTR_H           ((VOLATILE unsigned char far*)0xAF0283)
	#define SP16_X_POS_L              ((VOLATILE unsigned char far*)0xAF0284)
	#define SP16_X_POS_H              ((VOLATILE unsigned char far*)0xAF0285)
	#define SP16_Y_POS_L              ((VOLATILE unsigned char far*)0xAF0286)
	#define SP16_Y_POS_H              ((VOLATILE unsigned char far*)0xAF0287)
	// SPRITE 17)
	#define SP17_CONTROL_REG          ((VOLATILE unsigned char far*)0xAF0288)
	#define SP17_ADDY_PTR_L           ((VOLATILE unsigned char far*)0xAF0289)
	#define SP17_ADDY_PTR_M           ((VOLATILE unsigned char far*)0xAF028A)
	#define SP17_ADDY_PTR_H           ((VOLATILE unsigned char far*)0xAF028B)
	#define SP17_X_POS_L              ((VOLATILE unsigned char far*)0xAF028C)
	#define SP17_X_POS_H              ((VOLATILE unsigned char far*)0xAF028D)
	#define SP17_Y_POS_L              ((VOLATILE unsigned char far*)0xAF028E)
	#define SP17_Y_POS_H              ((VOLATILE unsigned char far*)0xAF028F)
	// DMA CONTROLLER 0xAF0400 - 0xAF04FF)
	#define VDMA_CONTROL_REG          ((unsigned char *)0xAF0400)
	#define VDMA_COUNT_REG_L          ((VOLATILE unsigned char far*)0xAF0401)
	#define VDMA_COUNT_REG_M          ((VOLATILE unsigned char far*)0xAF0402)
	#define VDMA_COUNT_REG_H          ((VOLATILE unsigned char far*)0xAF0403)
	#define VDMA_DATA_2_WRITE_L       ((VOLATILE unsigned char far*)0xAF0404)
	#define VDMA_DATA_2_WRITE_H       ((VOLATILE unsigned char far*)0xAF0405)
	#define VDMA_STRIDE_L             ((VOLATILE unsigned char far*)0xAF0406)
	#define VDMA_STRIDE_H             ((VOLATILE unsigned char far*)0xAF0407)
	//#define VDMA_SRC_ADDY_L           ((VOLATILE unsigned char far*)0xAF0408)
	//#define VDMA_SRC_ADDY_M           ((VOLATILE unsigned char far*)0xAF0409)
	//#define VDMA_SRC_ADDY_H           ((VOLATILE unsigned char far*)0xAF040A)
	#define VDMA_RESERVED_0           ((VOLATILE unsigned char far*)0xAF040B)
	//#define VDMA_DST_ADDY_L           ((VOLATILE unsigned char far*)0xAF040C)
	//#define VDMA_DST_ADDY_M           ((VOLATILE unsigned char far*)0xAF040D)
	//#define VDMA_DST_ADDY_H           ((VOLATILE unsigned char far*)0xAF040E)
	#define VDMA_RESERVED_1           ((VOLATILE unsigned char far*)0xAF040F)
	
	// DMA CONTROLLER $AF0400 - $AF04FF
	// BIT FIELD DEFINITION
	#define VDMA_CTRL_ENABLE        ((char)0x01)
	#define VDMA_CTRL_1D_2D         ((char)0x02)  
	// 0 - 1D (LINEAR) TRANSFER , 1 - 2D (BLOCK) TRANSFER
	#define VDMA_CTRL_TRF_FILL      ((char)0x04)   
	// 0 - TRANSFER SRC -> DST, 1 - FILL DESTINATION WITH "BYTE2WRITE"
	#define VDMA_CTRL_INT_ENABLE    ((char)0x08)    
	// SET TO 1 TO ENABLE THE GENERATION OF INTERRUPT WHEN THE TRANSFER IS OVER.
	#define VDMA_CTRL_START_TRF     ((char)0x80)   
	// SET TO 1 TO BEGIN PROCESS, NEED TO CLEARED BEFORE, YOU CAN START ANOTHER

	// WRITE ONLY - BYTE TO WRITE IN THE FILL FUNCTION
	#define VDMA_BYTE_2_WRITE       ((unsigned char *)0xAF0401)
	// READ ONLY
	#define VDMA_STATUS_REG         ((VOLATILE unsigned char far*)0xAF0401)
	
	//STATUS BIT FIELD DEFINITION
	#define VDMA_STAT_SIZE_ERR      ((char)0x01)     
	// IF SET TO 1, OVERALL SIZE IS INVALID
	#define VDMA_STAT_DST_ADD_ERR   ((char)0x02)    
	// IF SET TO 1, DESTINATION ADDRESS INVALID
	#define VDMA_STAT_SRC_ADD_ERR   ((char)0x04)     
	// IF SET TO 1, SOURCE ADDRESS INVALID
	// IF SET TO 1, VDMA TRANSFER IN PROGRESS (THIS INHIBIT CPU ACCESS TO MEM)
	#define VDMA_STAT_VDMA_IPS      ((char)0x80)     
	// LET ME REPEAT, DON'T ACCESS THE VIDEO MEMORY THEN THERE IS A VDMA IN PROGRESS
	// THIS NEEDS TO BE WITHIN VICKY'S RANGE ($00_0000 - $3F_0000)
	#define VDMA_SRC_ADDY_L         ((VOLATILE unsigned char far*)0xAF0402)
	#define VDMA_SRC_ADDY_M         ((VOLATILE unsigned char far*)0xAF0403)
	#define VDMA_SRC_ADDY_H         ((VOLATILE unsigned char far*)0xAF0404)

	#define VDMA_DST_ADDY_L         ((VOLATILE unsigned char far*)0xAF0405)
	// DESTINATION POINTER WITHIN VICKY'S VIDEO MEMORY RANGE
	#define VDMA_DST_ADDY_M         ((VOLATILE unsigned char far*)0xAF0406)
	// ($00_0000 - $3F_0000)
	#define VDMA_DST_ADDY_H         ((VOLATILE unsigned char far*)0xAF0407)
	// IN 1D TRANSFER MODE
	#define VDMA_SIZE_L             ((VOLATILE unsigned char far*)0xAF0408)
	// MAXIMUM VALUE: $40:0000 (4MEGS)
	#define VDMA_SIZE_M             ((VOLATILE unsigned char far*)0xAF0409)
	#define VDMA_SIZE_H             ((VOLATILE unsigned char far*)0xAF040A)
	#define VDMA_IGNORED            ((VOLATILE unsigned char far*)0xAF040B)
	// IN 2D TRANSFER MODE
	#define VDMA_X_SIZE_L           ((VOLATILE unsigned char far*)0xAF0408)
	// MAXIMUM VALUE: 65535
	#define VDMA_X_SIZE_H           ((VOLATILE unsigned char far*)0xAF0409)
	#define VDMA_Y_SIZE_L           ((VOLATILE unsigned char far*)0xAF040A)
	// MAXIMUM VALUE: 65535
	#define VDMA_Y_SIZE_H           ((VOLATILE unsigned char far*)0xAF040B)

	#define VDMA_SRC_STRIDE_L       ((VOLATILE unsigned char far*)0xAF040C)
	// ALWAYS USE AN EVEN NUMBER ( THE ENGINE USES EVEN VER OF THAT VALUE)
	#define VDMA_SRC_STRIDE_H       ((VOLATILE unsigned char far*)0xAF040D)
	//
	#define VDMA_DST_STRIDE_L       ((VOLATILE unsigned char far*)0xAF040E)
	// ALWAYS USE AN EVEN NUMBER ( THE ENGINE USES EVEN VER OF THAT VALUE)
	#define VDMA_DST_STRIDE_H       ((VOLATILE unsigned char far*)0xAF040F)
	//
	
	
	#define FG_CHAR_LUT_PTR           ((VOLATILE unsigned char far*)0xAF1F40)
	#define BG_CHAR_LUT_PTR		    ((VOLATILE unsigned char far*)0xAF1F80)

	#define GRPH_LUT0_PTR		 ((VOLATILE unsigned char far*)0xAF2000)
	#define GRPH_LUT1_PTR		 ((VOLATILE unsigned char far*)0xAF2400)
	#define GRPH_LUT2_PTR		 ((VOLATILE unsigned char far*)0xAF2800)
	#define GRPH_LUT3_PTR		 ((VOLATILE unsigned char far*)0xAF2C00)
	#define GRPH_LUT4_PTR		 ((VOLATILE unsigned char far*)0xAF3000)
	#define GRPH_LUT5_PTR		 ((VOLATILE unsigned char far*)0xAF3400)
	#define GRPH_LUT6_PTR		 ((VOLATILE unsigned char far*)0xAF3800)
	#define GRPH_LUT7_PTR		 ((VOLATILE unsigned char far*)0xAF3C00)

	#define GAMMA_B_LUT_PTR		 ((VOLATILE unsigned char far*)0xAF4000)
	#define GAMMA_G_LUT_PTR		 ((VOLATILE unsigned char far*)0xAF4100)
	#define GAMMA_R_LUT_PTR		 ((VOLATILE unsigned char far*)0xAF4200)

	#define TILE_MAP0       		 ((VOLATILE unsigned char far*)0xAF5000)
	#define TILE_MAP1                 ((VOLATILE unsigned char far*)0xAF5800)
	#define TILE_MAP2                 ((VOLATILE unsigned char far*)0xAF6000)
	#define TILE_MAP3                 ((VOLATILE unsigned char far*)0xAF6800)

	#define FONT_MEMORY_BANK          ((VOLATILE unsigned char far*)0xAF8000)
	#define CS_TEXT_MEM_PTR           ((VOLATILE unsigned char far*)0xAFA000)
	#define CS_COLOR_MEM_PTR          ((VOLATILE unsigned char far*)0xAFC000)

	#define BMP_X_SIZE        ((VOLATILE unsigned char far*)0x000040)
	//2 BYTES)
	#define BM_CLEAR_SCRN_X   ((VOLATILE unsigned char far*)0x000040)
	#define BMP_Y_SIZE        ((VOLATILE unsigned char far*)0x000042) 
	//2 BYTES)
	#define BM_CLEAR_SCRN_Y   ((VOLATILE unsigned char far*)0x000042)
	#define BMP_PRSE_SRC_PTR  ((VOLATILE unsigned char far*)0x000044) 
	//3 BYTES)
	#define BMP_PRSE_DST_PTR  ((VOLATILE unsigned char far*)0x000048) 
	//3 BYTES)
	#define BMP_COLOR_PALET   ((VOLATILE unsigned char far*)0x00004C) 
	//2 BYTES)
	#define SCRN_X_STRIDE     ((VOLATILE unsigned char far*)0x00004E) 
	//2 BYTES, BASICALLY HOW MANY PIXEL ACCROSS IN BITMAP MODE)
	#define BMP_FILE_SIZE     ((VOLATILE unsigned char far*)0x000050) 
	//4 BYTES)
	#define BMP_POSITION_X    ((VOLATILE unsigned char far*)0x000054) 
	//2 BYTES WHERE, THE BMP WILL BE POSITION ON THE X AXIS)
	#define BMP_POSITION_Y    ((VOLATILE unsigned char far*)0x000056) 
	//2 BYTES WHERE, THE BMP WILL BE POSITION ON THE Y AXIS)
	#define BMP_PALET_CHOICE  ((VOLATILE unsigned char far*)0x000058)


	#define BTX_START                 ((VOLATILE unsigned char far*)0xAFE000) 
	//BEATRIX REGISTERS)
	#define BTX_END                   ((VOLATILE unsigned char far*)0xAFFFFF)	
	
	#define MOUSE_PTR_GRAP0_START     ((VOLATILE unsigned char far*)0xAF0500) 
	//  16 x 16  256 Pixels (Grey Scale) 0  Transparent, 1  Black , 255  White
	#define MOUSE_PTR_GRAP0_END       ((VOLATILE unsigned char far*)0xAF05FF) 
	//  Pointer 0
	#define MOUSE_PTR_GRAP1_START     ((VOLATILE unsigned char far*)0xAF0600) 
	#define FPGA_YOR                 ((VOLATILE unsigned char far*)0xAF070F)  
	#define MOUSE_PTR_GRAP1_END       ((VOLATILE unsigned char far*)0xAF06FF) 
	//  Pointer 1

	#define MOUSE_PTR_CTRL_REG_L     ((VOLATILE unsigned char far*)0xAF0700) 
	//  Bit[0] Enable, Bit[1]  0  ( 0  Pointer0, 1  Pointer1)
	#define MOUSE_PTR_CTRL_REG_H     ((VOLATILE unsigned char far*)0xAF0701) 
	// 
	#define MOUSE_PTR_X_POS_L        ((VOLATILE unsigned char far*)0xAF0702) 
	//  X Position (0 - 639) (Can only read now) Writing will have no effect
	#define MOUSE_PTR_X_POS_H        ((VOLATILE unsigned char far*)0xAF0703) 
	// 
	#define MOUSE_PTR_Y_POS_L        ((VOLATILE unsigned char far*)0xAF0704) 
	//  Y Position (0 - 479) (Can only read now) Writing will have no effect
	#define MOUSE_PTR_Y_POS_H        ((VOLATILE unsigned char far*)0xAF0705) 
	// 
	#define MOUSE_PTR_BYTE0          ((VOLATILE unsigned char far*)0xAF0706) 
	//  Byte 0 of Mouse Packet (you must write 3 Bytes)
	#define MOUSE_PTR_BYTE1          ((VOLATILE unsigned char far*)0xAF0707) 
	//  Byte 1 of Mouse Packet (if you don't, then )
	#define MOUSE_PTR_BYTE2          ((VOLATILE unsigned char far*)0xAF0708) 
	//  Byte 2 of Mouse Packet (state Machine will be jammed in 1 state)
                                  // (And the mouse won't work)
	
	#define MOUSE_PTR_BYTE0_ASM         $AF0706
	#define MOUSE_PTR_BYTE1_ASM         $AF0707
	#define MOUSE_PTR_BYTE2_ASM         $AF0708

	#define MOUSE_POS_X_LO  ((VOLATILE unsigned char far*)0x0000E1)
	#define MOUSE_POS_X_HI  ((VOLATILE unsigned char far*)0x0000E2)
	#define MOUSE_POS_Y_LO  ((VOLATILE unsigned char far*)0x0000E3)
	#define MOUSE_POS_Y_HI  ((VOLATILE unsigned char far*)0x0000E4)
				

	#define FXOS_MOUSE_BYTE_0		  ((VOLATILE unsigned char far*)0x001500)
	#define FXOS_MOUSE_BYTE_1		  ((VOLATILE unsigned char far*)0x001501)
	#define FXOS_MOUSE_BYTE_2		  ((VOLATILE unsigned char far*)0x001502)
	#define FXOS_MOUSE_BYTE_T		  ((VOLATILE unsigned char far*)0x001503)

	#define FXOS_MOUSE_BYTE_0_ASM	  $00C500
	#define FXOS_MOUSE_BYTE_T_ASM	  $00C503	  

	#define FXOS_MOUSE_BYTE_X_L		  ((VOLATILE unsigned char far*)0x001504)
	#define FXOS_MOUSE_BYTE_X_H		  ((VOLATILE unsigned char far*)0x001505)
	#define FXOS_MOUSE_BYTE_Y_L		  ((VOLATILE unsigned char far*)0x001506)
	#define FXOS_MOUSE_BYTE_Y_H		  ((VOLATILE unsigned char far*)0x001507)

	#define FXOS_MOUSE_CTL			  ((VOLATILE unsigned char far*)0x00150B)
	#define FXOS_MOUSE_INDEX   		  ((VOLATILE unsigned char far*)0x00150C)
	#define FXOS_MOUSE_STATUS		  ((VOLATILE unsigned char far*)0x00150D)


	#define FXOS_KEY_BYTE_0		  	  ((VOLATILE unsigned char far*)0x001508)
	#define FXOS_KEY_BYTE_1		      ((VOLATILE unsigned char far*)0x001509)
	#define FXOS_KEY_BYTE_2		      ((VOLATILE unsigned char far*)0x00150A)

		
	#define C256F_MODEL_MAJOR        ((VOLATILE unsigned char far*)0xAF070B)  
	#define C256F_MODEL_MINOR        ((VOLATILE unsigned char far*)0xAF070C)  
	#define FPGA_DOR                 ((VOLATILE unsigned char far*)0xAF070D)  
	#define FPGA_MOR                 ((VOLATILE unsigned char far*)0xAF070E)  
	
	#define	KEYBOARD_SCAN_CODE		 ((VOLATILE unsigned char far*)0xAF115F) 
	#define	KEY_BUFFER_RPOS  		 ((VOLATILE unsigned char far*)0x000F40) 
	#define	KEY_BUFFER       		 ((VOLATILE unsigned char far*)0x000F00) 
	
	#define	JOYSTICK0     ((VOLATILE unsigned char far*)0xAFE800)
	#define	JOYSTICK1     ((VOLATILE unsigned char far*)0xAFE801)
	#define	JOYSTICK2     ((VOLATILE unsigned char far*)0xAFE802)
	#define	JOYSTICK3     ((VOLATILE unsigned char far*)0xAFE803)
	
	// clock
	#define	RTC_SEC       ((VOLATILE unsigned char far*)0xAF0800 )
	//Seconds Register
	#define	RTC_SEC_ALARM ((VOLATILE unsigned char far*)0xAF0801 )
	//Seconds Alarm Register
	#define	RTC_MIN       ((VOLATILE unsigned char far*)0xAF0802 )
	//Minutes Register
	#define	RTC_MIN_ALARM ((VOLATILE unsigned char far*)0xAF0803 )
	//Minutes Alarm Register
	#define	RTC_HRS       ((VOLATILE unsigned char far*)0xAF0804 )
	//Hours Register
	#define	RTC_HRS_ALARM ((VOLATILE unsigned char far*)0xAF0805 )
	//Hours Alarm Register
	#define	RTC_DAY       ((VOLATILE unsigned char far*)0xAF0806 )
	//Day Register
	#define	RTC_DAY_ALARM ((VOLATILE unsigned char far*)0xAF0807 )
	//Day Alarm Register
	#define	RTC_DOW       ((VOLATILE unsigned char far*)0xAF0808 )
	//Day of Week Register
	#define	RTC_MONTH     ((VOLATILE unsigned char far*)0xAF0809 )
	//Month Register
	#define	RTC_YEAR      ((VOLATILE unsigned char far*)0xAF080A )
	//Year Register
	#define	RTC_RATES     ((VOLATILE unsigned char far*)0xAF080B )
	//Rates Register
	#define	RTC_ENABLE    ((VOLATILE unsigned char far*)0xAF080C )
	//Enables Register
	#define	RTC_FLAGS     ((VOLATILE unsigned char far*)0xAF080D )
	//Flags Register
	#define	RTC_CTRL      ((VOLATILE unsigned char far*)0xAF080E )
	//Control Register
	#define	RTC_CENTURY   ((VOLATILE unsigned char far*)0xAF080F )
	//Century Register

	//[0] - Enable Line 0, [1] -Enable Line 1
	#define	VKY_LINE_IRQ_CTRL_REG   ((VOLATILE unsigned char far*)0xAF001B) 
	//Write Only [7:0]
	#define	VKY_LINE0_CMP_VALUE_LO  ((VOLATILE unsigned char far*)0xAF001C) 
	//Write Only [3:0]
	#define	VKY_LINE0_CMP_VALUE_HI  ((VOLATILE unsigned char far*)0xAF001D )
	//Write Only [7:0]
	#define	VKY_LINE1_CMP_VALUE_LO  ((VOLATILE unsigned char far*)0xAF001E )
	//Write Only [3:0]
	#define	VKY_LINE1_CMP_VALUE_HI  ((VOLATILE unsigned char far*)0xAF001F )
		
	#define UART1_BASE    ((unsigned char far*)0xAF13F8) 
	#define UART2_BASE 	  ((unsigned char far*)0xAF12F8)

	#define	STATUS_PORT 	         ((char far*)0xAF1064)
	#define	KBD_OUT_BUF 	         ((char far*)0xAF1060)
	#define	KBD_INPT_BUF	         ((char far*)0xAF1060)
	#define	KBD_CMD_BUF		         ((char far*)0xAF1064)
	#define	KBD_DATA_BUF	         ((char far*)0xAF1060)
	#define	PORT_A			         ((char far*)0xAF1060)
	#define	PORT_B			         ((char far*)0xAF1061)


		
	#define	BITMAP_BANK_0       		 ((VOLATILE unsigned char far*)0xB00000) 
	#define	BITMAP_BANK_1       		 ((VOLATILE unsigned char far*)0xB10000) 
	#define	BITMAP_BANK_2       		 ((VOLATILE unsigned char far*)0xB20000) 
	#define	BITMAP_BANK_3       		 ((VOLATILE unsigned char far*)0xB30000) 
	#define	BITMAP_BANK_4       		 ((VOLATILE unsigned char far*)0xB40000) 
	#define	BITMAP_BANK_5       		 ((VOLATILE unsigned char far*)0xB50000) 

	#define	BITMAP_PAGE_START       	 (0xB00000)


	#define WIN_BORDER_CHAR_TOP 		   	(0xC4)	
	#define WIN_BORDER_CHAR_BOTTOM 		   	(0xC4)	
	#define WIN_BORDER_CHAR_EDGE 		   	(0xBA)
	#define WIN_BORDER_CHAR_CORNER_TLEFT	(0xD6)
	#define WIN_BORDER_CHAR_CORNER_BLEFT	(0xD3)	
	#define WIN_BORDER_CHAR_CORNER_TRIGHT  	(0xB7)
	#define WIN_BORDER_CHAR_CORNER_BRIGHT  	(0xD3)

typedef struct _RectStruct
{
	int x;
	int y;
	int width;
	int height;
} RECT;

typedef RECT far* PRECT;

typedef struct _WindowStruct
{
	int win_id;
	int win_x;
	int win_y;
	int win_width;
	int win_height;
	char far win_title[10];
} Window;

typedef int HANDLE;
typedef HANDLE far* PHANDLE;

typedef char far* TITLE;

typedef struct _FontMetric
{
	int width;
	int height;
} FONTMETRIC;

struct _ctl_Textbox
{
	int win_id;
	int win_x;
	int win_y;
	int win_width;
	int win_height;
	char far** content;
};
typedef struct _ctl_Textbox TEXTBOX;
typedef TEXTBOX far* PTEXTBOX;
typedef long HTEXTBOX;

typedef struct _ClickableRect
{
	RECT area;
	BOOL enabled;
	char depth;
} CLICKABLE;
typedef CLICKABLE far* PCLICKABLE;
typedef long HCLICKABLE;


struct _MenuStruct
{
	int cx;
	int cy;
	int width;
	int height;
	char fcolor;
	char bcolor;
	char chromeLeft;
	char chromeRight1;
	char chromeRight2;
	char far *pCaption;
	void far **subMenus;
};

typedef struct _MenuStruct MENU;
typedef MENU far* PMENU;
typedef long HMENU;

typedef void (*MenuAction)(PMENU pmenu,int cx,int cy,void far* data);

struct _SubMenuStruct
{
	char far* caption;
	MenuAction action;	
};

typedef struct _SubMenuStruct SUBMENU;
typedef SUBMENU far* PSUBMENU;
typedef long HSUBMENU;

typedef struct _SubMenuListStruct
{
	char cMenus;
	PSUBMENU far** psubmenus;	
}SUBMENULIST;
typedef SUBMENULIST far* PSUBMENULIST;


typedef struct _fx_irq_data
{
	int line;
	char far* keycode;
}IRQDATA;
typedef IRQDATA far* PIRQDATA;

typedef struct task_stack
{
	unsigned char SSL;
	unsigned char SSH;	
	unsigned char SPL;
	unsigned char SPH;
	char far *pstack;
}TASK_STACK;

typedef struct int_regs
{
	unsigned char PB;
	unsigned char PH;
	unsigned char PL;
	unsigned char PP;
	unsigned char DB;
	unsigned char DH;
	unsigned char DL;	
	unsigned char AH;
	unsigned char AL;
	unsigned char XH;
	unsigned char XL;
	unsigned char YH;
	unsigned char YL;		
}INT_REGS;

typedef void (*C256Task)(HANDLE console,void far* arg);

typedef void (*task_type)(void);

void t0(void);
void t1(void);

void disable(void);
void enable(void);

void k_init_multitasking(void);
void k_task_switch(void);
void t_make_task(task_type task,unsigned int ssize,int id);

char * k_itoa (unsigned int value, char *result, int base);
PMENU k_vdraw_ui_menu(int cx,int cy,int width,char far *title,int color, int bgcolor);

#define PASCAL		pascal	

void k_clear_screen(int bcolor);
void k_print(char * message);
void k_put_char(int col,int row,char c,int fcolor,int bcolor);
int  k_put_string(int col,int row,char * text,int fcolor,int bcolor);

void k_delay(int millisecs);

void k_enable_border(void);
void k_disable_border(void);
void k_set_border_color(char r,char g,char b);

void k_set_foreground_palette(char paletteId);
void k_set_text_gamma(char c);
void k_set_text_color(char c);

void k_reverse(char far str[], int length) ;

void k_get_c256_major_version(char *buffer);
void k_get_c256_minor_version(char *buffer);

void k_get_fpga_date_day(char *buffer);
void k_get_fpga_date_month(char *buffer);
void k_get_fpga_date_year(char *buffer);

void k_drawPixel(char fcolor,char fcolor2,char fcolor3);
void setFColors(void);
void setBColors(void);
void k_test_graphics(void);
void k_test_desktop(void);
void k_test_tasking(void);
void k_test_mouse(void);

void  k_init_vicky(void);

void k_enable_text_mode(void);

void k_reboot(void);
void k_restore(void);
void k_init_mouse(void);
void k_init_graphics(void);

int k_get_cols_visible(void);
int k_get_cols_per_line(void);
int k_get_lines_visible(void);
int k_get_lines_max(void);

char far* k_pad_string(char far* dest,char far* src,char filler,int width);

void setColors(void);
void k_draw_lines(void);

void k_draw_pixel(long x,long y,char pcolor);
void k_draw_segments(int xc, int yc, int x, int y,int color);
void k_draw_circle(int xc, int yc, int r, int color);
void k_draw_filled_circle(int xc, int yc, int r, int color);
void k_draw_line(int x0, int y0, int x1, int y1,int color);
void k_draw_rect_slow(int left,int top, int right, int bottom, char color);
void k_draw_filled_rect(int cx,int cy,int height,int width,int color);

void k_vdraw_filled_rect(int cx,int cy,int height,int width,int color);

void k_fill_line(int cx,int cy,int width,int color);
void k_fill_bank(int bankId,char fcolor);

int k_font_index(char a);
void k_font_draw(char far *arg);
void k_put_font(char outChar,int row,int column,char textC);
void k_put_font_scaled(char outChar,int row,int column,char color,int scale);

int k_draw_text(char far *text,int row,int col,char color);
int k_draw_text_scaled(char far *text,int row,int col,char color,int scale);

int k_put_font_point(char outChar,int cx,int cy,char color);
int k_draw_text_point(char far *text,int x,int y,char color);

void k_draw_char_scaled_point(char charCode,int locX,int locY,char color,int scale);

int k_put_draw_text(int row,int col,char far *text,char color,char bcolor);
void k_draw_char(char charCode,int row,int column,char color);
void k_draw_fontset(void);

int k_get_font_metrics(FONTMETRIC far *metric);

void k_draw_char_scaled(char charCode,int row,int column,char color,int scale);

void k_render_bitmap_info(int fcolor);

// windowing
HANDLE k_create_window(int bx,int by,int bw,int bh,char far* title);
void k_window_draw_background(int bx,int by, int bw,int bh,char bcolor);

int k_put_wingadget_point(char iconCode,int cx,int cy,char color);
int k_put_winicon_point(char iconCode,int cx,int cy,char paletteId,int mode);
void k_put_winicon_scaled(char iconCode,int cx,int cy,char paletteId,int mode,int scale);

void k_draw_ui_window(int cx,int cy,int height,int width,char far *title,int color,int bgcolor);
void k_vdraw_ui_window(int cx,int cy,int height,int width,char far *title,int color,int bgcolor);


void k_vdma_fill(char far * pdst,long size,unsigned char data);
void k_vdma_fill_address(char far * pdst,int width,int height,unsigned char data);
void k_vdma_fill_rect(long x,long y,int width,int height,unsigned char data);

int k_get_mouse_button(int ctx);
int k_get_mouse_pos_X(void);
int k_get_mouse_pos_Y(void);
int k_get_key_handler(void);
char k_get_key_buffer(char position);

int k_system_call(char far* data);

void k_tickManagement(void);

void k_query_environment(void);
void k_run_loop(void);


extern void pascal init_sd_card(void);
void sd_card_dir(void);

void k_init_keyboard(void);
void k_uart_enableirq(void);
void k_print_uart_status(int lc);

void k_print_uart_status_com1(int lc);
void k_print_uart_status_com2(int lc);

void k_dispatch_reg0(PIRQDATA pIRQ);
void k_dispatch_reg1(PIRQDATA pIRQ);
void k_dispatch_reg2(PIRQDATA pIRQ);


extern char buffer[32];
extern char strbuf[32];
extern char spinner[];
extern char titles[3][10];

extern char *version_title;

extern int g_key_index;

extern int 	_k_window_index;
extern Window 	_k_window_list[];

extern char *p_message1;
extern char *p_message2;

extern C256Task tasks[2];
extern HANDLE consoles[2];






#endif


#endif