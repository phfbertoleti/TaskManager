################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
SRC_SRCS += \
..\r_bsp/board/rdkrx63n/lowlvl.src 

C_SRCS += \
..\r_bsp/board/rdkrx63n/dbsct.c \
..\r_bsp/board/rdkrx63n/flash_options.c \
..\r_bsp/board/rdkrx63n/hwsetup.c \
..\r_bsp/board/rdkrx63n/lcd.c \
..\r_bsp/board/rdkrx63n/lowsrc.c \
..\r_bsp/board/rdkrx63n/resetprg.c \
..\r_bsp/board/rdkrx63n/sbrk.c \
..\r_bsp/board/rdkrx63n/vecttbl.c 

C_DEPS += \
./r_bsp/board/rdkrx63n/dbsct.d \
./r_bsp/board/rdkrx63n/flash_options.d \
./r_bsp/board/rdkrx63n/hwsetup.d \
./r_bsp/board/rdkrx63n/lcd.d \
./r_bsp/board/rdkrx63n/lowsrc.d \
./r_bsp/board/rdkrx63n/resetprg.d \
./r_bsp/board/rdkrx63n/sbrk.d \
./r_bsp/board/rdkrx63n/vecttbl.d 

SRC_DEPS += \
./r_bsp/board/rdkrx63n/lowlvl.d 

OBJS += \
./r_bsp/board/rdkrx63n/dbsct.obj \
./r_bsp/board/rdkrx63n/flash_options.obj \
./r_bsp/board/rdkrx63n/hwsetup.obj \
./r_bsp/board/rdkrx63n/lcd.obj \
./r_bsp/board/rdkrx63n/lowlvl.obj \
./r_bsp/board/rdkrx63n/lowsrc.obj \
./r_bsp/board/rdkrx63n/resetprg.obj \
./r_bsp/board/rdkrx63n/sbrk.obj \
./r_bsp/board/rdkrx63n/vecttbl.obj 


# Each subdirectory must supply rules for building sources it contributes
r_bsp/board/rdkrx63n/%.obj: ../r_bsp/board/rdkrx63n/%.c
	@echo 'Scanning and building file: $<'
	@echo 'Invoking: Scanner and Compiler'
	ccrx  -MM -MP -output=dep="$(@:%.obj=%.d)" -MT="$(@:%.obj=%.obj)" -MT="$(@:%.obj=%.d)" -lang=c99   -include="C:/Workspace Renesas/TaskManager\r_bsp","C:/Workspace Renesas/TaskManager\r_glyph","C:/Workspace Renesas/TaskManager\r_glyph\src","C:/Workspace Renesas/TaskManager\r_glyph\src\glyph","C:/Workspace Renesas/TaskManager\r_rspi_rx600","C:/Workspace Renesas/TaskManager\r_rspi_rx600\src","C:/Workspace Renesas/TaskManager\src","C:\PROGRA~2\Renesas\RX\2_3_0\include"  -debug -cpu=rx600 -speed -alias=noansi -nologo  -define=__RX   "$<"
	ccrx -lang=c99 -output=obj="$(@:%.d=%.obj)"  -include="C:/Workspace Renesas/TaskManager\r_bsp","C:/Workspace Renesas/TaskManager\r_glyph","C:/Workspace Renesas/TaskManager\r_glyph\src","C:/Workspace Renesas/TaskManager\r_glyph\src\glyph","C:/Workspace Renesas/TaskManager\r_rspi_rx600","C:/Workspace Renesas/TaskManager\r_rspi_rx600\src","C:/Workspace Renesas/TaskManager\src","C:\PROGRA~2\Renesas\RX\2_3_0\include"  -debug -cpu=rx600 -speed -alias=noansi -nologo  -define=__RX   "$<"
	@echo 'Finished scanning and building: $<'
	@echo.

r_bsp/board/rdkrx63n/%.obj: ../r_bsp/board/rdkrx63n/%.src
	@echo 'Scanning and building file: $<'
	@echo 'Invoking: Scanner and Assembler'
	scandep1 -MM -MP -MF"$(@:%.obj=%.d)" -MT"$(@:%.obj=%.obj)" -MT"$(@:%.obj=%.d)"   -D__RX600=1  -D__LITTLE=1  -D__RENESAS_VERSION__=02030000H -U_WIN32 -UWIN32 -U__WIN32__ -U__GNUC__ -U__GNUC_MINOR__ -U__GNUC_PATCHLEVEL__   -E -quiet -I. -C "$<"
	asrx -output="$(@:%.d=%.obj)" -nolistfile -cpu=rx600 -debug -nologo   "$<"
	@echo 'Finished scanning and building: $<'
	@echo.

