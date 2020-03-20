@echo off

SET JAVA_HOME=

SET KERNELNAME=irqtool

SET BUILD=Y
SET VERBOSE=
SET TRANSFER=
SET CLEAN=

set argCount=0
for %%x in (%*) do (
   set /A argCount+=1
)


REM IF %argCount% == 0 GOTO usage

for %%x in (%*) do (
	IF [%%x] == [-n] SET BUILD=
	IF [%%x] == [-v] SET VERBOSE=Y
	IF [%%x] == [-t] SET TRANSFER=Y
	IF [%%x] == [-c] SET CLEAN=Y
)

IF [%JAVA_HOME%] == [] ( 
SET JAVABIN=java.exe
) else (
SET JAVABIN="%JAVA_HOME%\bin\java.exe"
)

REM set JAVA_HOME=G:\devtools\java\jdk1.8.0_211\jre

SET CCTEMP=%TEMP%
SET WDC_INC_65816=G:\devtools\WDCTools\wdc\Tools\include
SET WDC_INC_6502=G:\devtools\WDCTools\wdc\Tools\include
SET WDC_LIB=G:\devtools\WDCTools\wdc\Tools\lib

SET SREC_DIR=G:\devprojects\c256feonix\tools

SET COMPILER=G:\devtools\WDCTools\wdc\Tools\bin\wdc816cc.exe

SET ASSEMBLER=G:\devtools\WDCTools\wdc\Tools\bin\wdc816AS.exe
REM ASSEMBLER=G:\devtools\WDCTools\wdc\Tools\bin\WDC02AS.exe

SET LINKER=G:\devtools\WDCTools\wdc\Tools\bin\wdcln.exe
SET INCLUDES=-IG:\devprojects\6502
REM SET OPTIONS=-DUSING_816 -DUSING_DEBUG -ML -MT -LT -PX -WO -A -BS
SET ASM_OPTIONS=-DUSING_816 -DLARGE -V -l 
SET OPTIONS=-DUSING_816 -DLARGE -ML -MT -LT -PX -WO -WR -A -BS -SO0S
REM SET LINK_OPT= -CC020,C020 -T -G -B
SET ASM_OPT=-G -V -L -W
REM MAIN WOKRING 
REM SET LINK_OPT=-C1A0000,1A0000 -D1C0000,1C0000 -T -G -B
REM MOVE LOWER
SET LINK_OPT=-C001000,001000 -T -G -B -Q

REM SET LINK_OPT= -C15000A,15000A -D160000,160000 -T -G -B
REM SET LINK_OPT= -C150000,C150000 -T -G
REM OPTIONS=-lt -PX -A
SET LIBS=-LG:\devtools\WDCTools\wdc\Tools\lib

SET TASSDIR=G:\devprojects\c256feonix\kernel-builds\Kernel-Trinity-11-Cleaned-up
SET CURDIR=%~dp0

IF [%CLEAN%] == [Y] ( 
	del /q srec.out
	del /q myprog.hex
	del /q myprog.s28.hex
	
	del /q *.obj
	del /q *.o
	del /q *.bnk	
	del /q *.sym	
	del /q *.lst
	del /q *.hex
	del /q *.map
	del /q *.bin
)


IF [%VERBOSE%] == [Y] ( 

echo Build Settings:
echo WDC 65816 Includes:%WDC_INC_65816%
echo WDC  6502 Includes:%WDC_INC_6502%
echo WDC LIB:%WDC_LIB%
echo SREC DIR:%SREC_DIR%
echo COMPILER:%COMPILER%
echo ASSEMBLER:%ASSEMBLER%
echo LINKER:%LINKER%
echo INCLUDES:%INCLUDES%
echo OPTIONS:%OPTIONS%
echo LINK OPTIONS:%LINK_OPT%
echo LIBS:%LIBS%
echo TASSDIR:%TASSDIR%
echo CURRENT DIR:%CURDIR%

)

IF [%BUILD%] == [Y] (
del /Q *.s

%COMPILER% %INCLUDES% %OPTIONS% -Ofxstartup.s fxstartup.c
%ASSEMBLER% %ASM_OPTIONS% fxstartup.s -o fxstartup.obj

%ASSEMBLER% %ASM_OPTIONS% uart.asm -o uart.obj
%ASSEMBLER% %ASM_OPTIONS% fxloader.asm -o fxloader.obj
%ASSEMBLER% %ASM_OPT% fxsdcard.s -o fxsdcard.obj

%LINKER% %LINK_OPT% -HB   uart.obj fxloader.obj fxstartup.obj -LCL -O %KERNELNAME%.bin
%LINKER% %LINK_OPT% -HM28 uart.obj fxloader.obj fxstartup.obj -LCL -O %KERNELNAME%.s28.hex


IF [%VERBOSE%] == [Y] ( 
	srec_cat.exe %KERNELNAME%.s28.hex -output %KERNELNAME%.hex -intel -address-length=3 > srec.out
) else (
	srec_cat.exe %KERNELNAME%.s28.hex -output %KERNELNAME%.hex -intel -address-length=3 > NUL
)

) else (
echo Skipping Build
)

copy /Y *.hex .\dist
copy /Y *.bin .\dist

IF [%TRANSFER%] == [Y] (
c256serial.bat -s28 %KERNELNAME%.hex -p XR21B1411
)

