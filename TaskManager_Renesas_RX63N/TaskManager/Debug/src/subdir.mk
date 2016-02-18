################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
..\src/CMT.c \
..\src/S12ADC.c \
..\src/main.c 

C_DEPS += \
./src/CMT.d \
./src/S12ADC.d \
./src/main.d 

OBJS += \
./src/CMT.obj \
./src/S12ADC.obj \
./src/main.obj 


# Each subdirectory must supply rules for building sources it contributes
src/%.obj: ../src/%.c
	@echo 'Scanning and building file: $<'
	@echo 'Invoking: Scanner and Compiler'
	ccrx  -MM -MP -output=dep="$(@:%.obj=%.d)" -MT="$(@:%.obj=%.obj)" -MT="$(@:%.obj=%.d)" -lang=c99   -include="C:/Workspace Renesas/TaskManager\r_bsp","C:/Workspace Renesas/TaskManager\r_glyph","C:/Workspace Renesas/TaskManager\r_glyph\src","C:/Workspace Renesas/TaskManager\r_glyph\src\glyph","C:/Workspace Renesas/TaskManager\r_rspi_rx600","C:/Workspace Renesas/TaskManager\r_rspi_rx600\src","C:/Workspace Renesas/TaskManager\src","C:\PROGRA~2\Renesas\RX\2_3_0\include"  -debug -cpu=rx600 -speed -alias=noansi -nologo  -define=__RX   "$<"
	ccrx -lang=c99 -output=obj="$(@:%.d=%.obj)"  -include="C:/Workspace Renesas/TaskManager\r_bsp","C:/Workspace Renesas/TaskManager\r_glyph","C:/Workspace Renesas/TaskManager\r_glyph\src","C:/Workspace Renesas/TaskManager\r_glyph\src\glyph","C:/Workspace Renesas/TaskManager\r_rspi_rx600","C:/Workspace Renesas/TaskManager\r_rspi_rx600\src","C:/Workspace Renesas/TaskManager\src","C:\PROGRA~2\Renesas\RX\2_3_0\include"  -debug -cpu=rx600 -speed -alias=noansi -nologo  -define=__RX   "$<"
	@echo 'Finished scanning and building: $<'
	@echo.

