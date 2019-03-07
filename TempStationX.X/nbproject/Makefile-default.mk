#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/TempStationX.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/TempStationX.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=
else
COMPARISON_BUILD=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=../source/TimeDelay.c ../source/crc.c ../source/13pix.c ../source/53pix.c ../source/29pix.c ../source/graphics.c ../source/RF.c ../source/SHT_driver.c ../source/rtcc.c ../source/TempStation.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/812168374/TimeDelay.o ${OBJECTDIR}/_ext/812168374/crc.o ${OBJECTDIR}/_ext/812168374/13pix.o ${OBJECTDIR}/_ext/812168374/53pix.o ${OBJECTDIR}/_ext/812168374/29pix.o ${OBJECTDIR}/_ext/812168374/graphics.o ${OBJECTDIR}/_ext/812168374/RF.o ${OBJECTDIR}/_ext/812168374/SHT_driver.o ${OBJECTDIR}/_ext/812168374/rtcc.o ${OBJECTDIR}/_ext/812168374/TempStation.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/812168374/TimeDelay.o.d ${OBJECTDIR}/_ext/812168374/crc.o.d ${OBJECTDIR}/_ext/812168374/13pix.o.d ${OBJECTDIR}/_ext/812168374/53pix.o.d ${OBJECTDIR}/_ext/812168374/29pix.o.d ${OBJECTDIR}/_ext/812168374/graphics.o.d ${OBJECTDIR}/_ext/812168374/RF.o.d ${OBJECTDIR}/_ext/812168374/SHT_driver.o.d ${OBJECTDIR}/_ext/812168374/rtcc.o.d ${OBJECTDIR}/_ext/812168374/TempStation.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/812168374/TimeDelay.o ${OBJECTDIR}/_ext/812168374/crc.o ${OBJECTDIR}/_ext/812168374/13pix.o ${OBJECTDIR}/_ext/812168374/53pix.o ${OBJECTDIR}/_ext/812168374/29pix.o ${OBJECTDIR}/_ext/812168374/graphics.o ${OBJECTDIR}/_ext/812168374/RF.o ${OBJECTDIR}/_ext/812168374/SHT_driver.o ${OBJECTDIR}/_ext/812168374/rtcc.o ${OBJECTDIR}/_ext/812168374/TempStation.o

# Source Files
SOURCEFILES=../source/TimeDelay.c ../source/crc.c ../source/13pix.c ../source/53pix.c ../source/29pix.c ../source/graphics.c ../source/RF.c ../source/SHT_driver.c ../source/rtcc.c ../source/TempStation.c


CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/TempStationX.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=24F16KA102
MP_LINKER_FILE_OPTION=,-Tp24F16KA102.gld
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/812168374/TimeDelay.o: ../source/TimeDelay.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/812168374" 
	@${RM} ${OBJECTDIR}/_ext/812168374/TimeDelay.o.d 
	@${RM} ${OBJECTDIR}/_ext/812168374/TimeDelay.o.ok ${OBJECTDIR}/_ext/812168374/TimeDelay.o.err 
	@${RM} ${OBJECTDIR}/_ext/812168374/TimeDelay.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/812168374/TimeDelay.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I".." -I"../../Microchip/Include" -I"../../../../Program Files (x86)/Microchip/MPLAB C30/support/peripheral_24F" -I"../source" -I"../../../../Program Files (x86)/Microchip/MPLAB C30/include" -I"../include" -I"." -MMD -MF "${OBJECTDIR}/_ext/812168374/TimeDelay.o.d" -o ${OBJECTDIR}/_ext/812168374/TimeDelay.o ../source/TimeDelay.c    
	
${OBJECTDIR}/_ext/812168374/crc.o: ../source/crc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/812168374" 
	@${RM} ${OBJECTDIR}/_ext/812168374/crc.o.d 
	@${RM} ${OBJECTDIR}/_ext/812168374/crc.o.ok ${OBJECTDIR}/_ext/812168374/crc.o.err 
	@${RM} ${OBJECTDIR}/_ext/812168374/crc.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/812168374/crc.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I".." -I"../../Microchip/Include" -I"../../../../Program Files (x86)/Microchip/MPLAB C30/support/peripheral_24F" -I"../source" -I"../../../../Program Files (x86)/Microchip/MPLAB C30/include" -I"../include" -I"." -Os -MMD -MF "${OBJECTDIR}/_ext/812168374/crc.o.d" -o ${OBJECTDIR}/_ext/812168374/crc.o ../source/crc.c    
	
${OBJECTDIR}/_ext/812168374/13pix.o: ../source/13pix.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/812168374" 
	@${RM} ${OBJECTDIR}/_ext/812168374/13pix.o.d 
	@${RM} ${OBJECTDIR}/_ext/812168374/13pix.o.ok ${OBJECTDIR}/_ext/812168374/13pix.o.err 
	@${RM} ${OBJECTDIR}/_ext/812168374/13pix.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/812168374/13pix.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I".." -I"../../Microchip/Include" -I"../../../../Program Files (x86)/Microchip/MPLAB C30/support/peripheral_24F" -I"../source" -I"../../../../Program Files (x86)/Microchip/MPLAB C30/include" -I"../include" -I"." -Os -MMD -MF "${OBJECTDIR}/_ext/812168374/13pix.o.d" -o ${OBJECTDIR}/_ext/812168374/13pix.o ../source/13pix.c    
	
${OBJECTDIR}/_ext/812168374/53pix.o: ../source/53pix.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/812168374" 
	@${RM} ${OBJECTDIR}/_ext/812168374/53pix.o.d 
	@${RM} ${OBJECTDIR}/_ext/812168374/53pix.o.ok ${OBJECTDIR}/_ext/812168374/53pix.o.err 
	@${RM} ${OBJECTDIR}/_ext/812168374/53pix.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/812168374/53pix.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I".." -I"../../Microchip/Include" -I"../../../../Program Files (x86)/Microchip/MPLAB C30/support/peripheral_24F" -I"../source" -I"../../../../Program Files (x86)/Microchip/MPLAB C30/include" -I"../include" -I"." -Os -MMD -MF "${OBJECTDIR}/_ext/812168374/53pix.o.d" -o ${OBJECTDIR}/_ext/812168374/53pix.o ../source/53pix.c    
	
${OBJECTDIR}/_ext/812168374/29pix.o: ../source/29pix.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/812168374" 
	@${RM} ${OBJECTDIR}/_ext/812168374/29pix.o.d 
	@${RM} ${OBJECTDIR}/_ext/812168374/29pix.o.ok ${OBJECTDIR}/_ext/812168374/29pix.o.err 
	@${RM} ${OBJECTDIR}/_ext/812168374/29pix.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/812168374/29pix.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I".." -I"../../Microchip/Include" -I"../../../../Program Files (x86)/Microchip/MPLAB C30/support/peripheral_24F" -I"../source" -I"../../../../Program Files (x86)/Microchip/MPLAB C30/include" -I"../include" -I"." -Os -MMD -MF "${OBJECTDIR}/_ext/812168374/29pix.o.d" -o ${OBJECTDIR}/_ext/812168374/29pix.o ../source/29pix.c    
	
${OBJECTDIR}/_ext/812168374/graphics.o: ../source/graphics.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/812168374" 
	@${RM} ${OBJECTDIR}/_ext/812168374/graphics.o.d 
	@${RM} ${OBJECTDIR}/_ext/812168374/graphics.o.ok ${OBJECTDIR}/_ext/812168374/graphics.o.err 
	@${RM} ${OBJECTDIR}/_ext/812168374/graphics.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/812168374/graphics.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I".." -I"../../Microchip/Include" -I"../../../../Program Files (x86)/Microchip/MPLAB C30/support/peripheral_24F" -I"../source" -I"../../../../Program Files (x86)/Microchip/MPLAB C30/include" -I"../include" -I"." -Os -MMD -MF "${OBJECTDIR}/_ext/812168374/graphics.o.d" -o ${OBJECTDIR}/_ext/812168374/graphics.o ../source/graphics.c    
	
${OBJECTDIR}/_ext/812168374/RF.o: ../source/RF.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/812168374" 
	@${RM} ${OBJECTDIR}/_ext/812168374/RF.o.d 
	@${RM} ${OBJECTDIR}/_ext/812168374/RF.o.ok ${OBJECTDIR}/_ext/812168374/RF.o.err 
	@${RM} ${OBJECTDIR}/_ext/812168374/RF.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/812168374/RF.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I".." -I"../../Microchip/Include" -I"../../../../Program Files (x86)/Microchip/MPLAB C30/support/peripheral_24F" -I"../source" -I"../../../../Program Files (x86)/Microchip/MPLAB C30/include" -I"../include" -I"." -Os -MMD -MF "${OBJECTDIR}/_ext/812168374/RF.o.d" -o ${OBJECTDIR}/_ext/812168374/RF.o ../source/RF.c    
	
${OBJECTDIR}/_ext/812168374/SHT_driver.o: ../source/SHT_driver.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/812168374" 
	@${RM} ${OBJECTDIR}/_ext/812168374/SHT_driver.o.d 
	@${RM} ${OBJECTDIR}/_ext/812168374/SHT_driver.o.ok ${OBJECTDIR}/_ext/812168374/SHT_driver.o.err 
	@${RM} ${OBJECTDIR}/_ext/812168374/SHT_driver.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/812168374/SHT_driver.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I".." -I"../../Microchip/Include" -I"../../../../Program Files (x86)/Microchip/MPLAB C30/support/peripheral_24F" -I"../source" -I"../../../../Program Files (x86)/Microchip/MPLAB C30/include" -I"../include" -I"." -Os -MMD -MF "${OBJECTDIR}/_ext/812168374/SHT_driver.o.d" -o ${OBJECTDIR}/_ext/812168374/SHT_driver.o ../source/SHT_driver.c    
	
${OBJECTDIR}/_ext/812168374/rtcc.o: ../source/rtcc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/812168374" 
	@${RM} ${OBJECTDIR}/_ext/812168374/rtcc.o.d 
	@${RM} ${OBJECTDIR}/_ext/812168374/rtcc.o.ok ${OBJECTDIR}/_ext/812168374/rtcc.o.err 
	@${RM} ${OBJECTDIR}/_ext/812168374/rtcc.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/812168374/rtcc.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I".." -I"../../Microchip/Include" -I"../../../../Program Files (x86)/Microchip/MPLAB C30/support/peripheral_24F" -I"../source" -I"../../../../Program Files (x86)/Microchip/MPLAB C30/include" -I"../include" -I"." -Os -MMD -MF "${OBJECTDIR}/_ext/812168374/rtcc.o.d" -o ${OBJECTDIR}/_ext/812168374/rtcc.o ../source/rtcc.c    
	
${OBJECTDIR}/_ext/812168374/TempStation.o: ../source/TempStation.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/812168374" 
	@${RM} ${OBJECTDIR}/_ext/812168374/TempStation.o.d 
	@${RM} ${OBJECTDIR}/_ext/812168374/TempStation.o.ok ${OBJECTDIR}/_ext/812168374/TempStation.o.err 
	@${RM} ${OBJECTDIR}/_ext/812168374/TempStation.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/812168374/TempStation.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I".." -I"../../Microchip/Include" -I"../../../../Program Files (x86)/Microchip/MPLAB C30/support/peripheral_24F" -I"../source" -I"../../../../Program Files (x86)/Microchip/MPLAB C30/include" -I"../include" -I"." -Os -MMD -MF "${OBJECTDIR}/_ext/812168374/TempStation.o.d" -o ${OBJECTDIR}/_ext/812168374/TempStation.o ../source/TempStation.c    
	
else
${OBJECTDIR}/_ext/812168374/TimeDelay.o: ../source/TimeDelay.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/812168374" 
	@${RM} ${OBJECTDIR}/_ext/812168374/TimeDelay.o.d 
	@${RM} ${OBJECTDIR}/_ext/812168374/TimeDelay.o.ok ${OBJECTDIR}/_ext/812168374/TimeDelay.o.err 
	@${RM} ${OBJECTDIR}/_ext/812168374/TimeDelay.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/812168374/TimeDelay.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I".." -I"../../Microchip/Include" -I"../../../../Program Files (x86)/Microchip/MPLAB C30/support/peripheral_24F" -I"../source" -I"../../../../Program Files (x86)/Microchip/MPLAB C30/include" -I"../include" -I"." -MMD -MF "${OBJECTDIR}/_ext/812168374/TimeDelay.o.d" -o ${OBJECTDIR}/_ext/812168374/TimeDelay.o ../source/TimeDelay.c    
	
${OBJECTDIR}/_ext/812168374/crc.o: ../source/crc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/812168374" 
	@${RM} ${OBJECTDIR}/_ext/812168374/crc.o.d 
	@${RM} ${OBJECTDIR}/_ext/812168374/crc.o.ok ${OBJECTDIR}/_ext/812168374/crc.o.err 
	@${RM} ${OBJECTDIR}/_ext/812168374/crc.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/812168374/crc.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I".." -I"../../Microchip/Include" -I"../../../../Program Files (x86)/Microchip/MPLAB C30/support/peripheral_24F" -I"../source" -I"../../../../Program Files (x86)/Microchip/MPLAB C30/include" -I"../include" -I"." -Os -MMD -MF "${OBJECTDIR}/_ext/812168374/crc.o.d" -o ${OBJECTDIR}/_ext/812168374/crc.o ../source/crc.c    
	
${OBJECTDIR}/_ext/812168374/13pix.o: ../source/13pix.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/812168374" 
	@${RM} ${OBJECTDIR}/_ext/812168374/13pix.o.d 
	@${RM} ${OBJECTDIR}/_ext/812168374/13pix.o.ok ${OBJECTDIR}/_ext/812168374/13pix.o.err 
	@${RM} ${OBJECTDIR}/_ext/812168374/13pix.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/812168374/13pix.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I".." -I"../../Microchip/Include" -I"../../../../Program Files (x86)/Microchip/MPLAB C30/support/peripheral_24F" -I"../source" -I"../../../../Program Files (x86)/Microchip/MPLAB C30/include" -I"../include" -I"." -Os -MMD -MF "${OBJECTDIR}/_ext/812168374/13pix.o.d" -o ${OBJECTDIR}/_ext/812168374/13pix.o ../source/13pix.c    
	
${OBJECTDIR}/_ext/812168374/53pix.o: ../source/53pix.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/812168374" 
	@${RM} ${OBJECTDIR}/_ext/812168374/53pix.o.d 
	@${RM} ${OBJECTDIR}/_ext/812168374/53pix.o.ok ${OBJECTDIR}/_ext/812168374/53pix.o.err 
	@${RM} ${OBJECTDIR}/_ext/812168374/53pix.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/812168374/53pix.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I".." -I"../../Microchip/Include" -I"../../../../Program Files (x86)/Microchip/MPLAB C30/support/peripheral_24F" -I"../source" -I"../../../../Program Files (x86)/Microchip/MPLAB C30/include" -I"../include" -I"." -Os -MMD -MF "${OBJECTDIR}/_ext/812168374/53pix.o.d" -o ${OBJECTDIR}/_ext/812168374/53pix.o ../source/53pix.c    
	
${OBJECTDIR}/_ext/812168374/29pix.o: ../source/29pix.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/812168374" 
	@${RM} ${OBJECTDIR}/_ext/812168374/29pix.o.d 
	@${RM} ${OBJECTDIR}/_ext/812168374/29pix.o.ok ${OBJECTDIR}/_ext/812168374/29pix.o.err 
	@${RM} ${OBJECTDIR}/_ext/812168374/29pix.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/812168374/29pix.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I".." -I"../../Microchip/Include" -I"../../../../Program Files (x86)/Microchip/MPLAB C30/support/peripheral_24F" -I"../source" -I"../../../../Program Files (x86)/Microchip/MPLAB C30/include" -I"../include" -I"." -Os -MMD -MF "${OBJECTDIR}/_ext/812168374/29pix.o.d" -o ${OBJECTDIR}/_ext/812168374/29pix.o ../source/29pix.c    
	
${OBJECTDIR}/_ext/812168374/graphics.o: ../source/graphics.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/812168374" 
	@${RM} ${OBJECTDIR}/_ext/812168374/graphics.o.d 
	@${RM} ${OBJECTDIR}/_ext/812168374/graphics.o.ok ${OBJECTDIR}/_ext/812168374/graphics.o.err 
	@${RM} ${OBJECTDIR}/_ext/812168374/graphics.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/812168374/graphics.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I".." -I"../../Microchip/Include" -I"../../../../Program Files (x86)/Microchip/MPLAB C30/support/peripheral_24F" -I"../source" -I"../../../../Program Files (x86)/Microchip/MPLAB C30/include" -I"../include" -I"." -Os -MMD -MF "${OBJECTDIR}/_ext/812168374/graphics.o.d" -o ${OBJECTDIR}/_ext/812168374/graphics.o ../source/graphics.c    
	
${OBJECTDIR}/_ext/812168374/RF.o: ../source/RF.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/812168374" 
	@${RM} ${OBJECTDIR}/_ext/812168374/RF.o.d 
	@${RM} ${OBJECTDIR}/_ext/812168374/RF.o.ok ${OBJECTDIR}/_ext/812168374/RF.o.err 
	@${RM} ${OBJECTDIR}/_ext/812168374/RF.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/812168374/RF.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I".." -I"../../Microchip/Include" -I"../../../../Program Files (x86)/Microchip/MPLAB C30/support/peripheral_24F" -I"../source" -I"../../../../Program Files (x86)/Microchip/MPLAB C30/include" -I"../include" -I"." -Os -MMD -MF "${OBJECTDIR}/_ext/812168374/RF.o.d" -o ${OBJECTDIR}/_ext/812168374/RF.o ../source/RF.c    
	
${OBJECTDIR}/_ext/812168374/SHT_driver.o: ../source/SHT_driver.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/812168374" 
	@${RM} ${OBJECTDIR}/_ext/812168374/SHT_driver.o.d 
	@${RM} ${OBJECTDIR}/_ext/812168374/SHT_driver.o.ok ${OBJECTDIR}/_ext/812168374/SHT_driver.o.err 
	@${RM} ${OBJECTDIR}/_ext/812168374/SHT_driver.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/812168374/SHT_driver.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I".." -I"../../Microchip/Include" -I"../../../../Program Files (x86)/Microchip/MPLAB C30/support/peripheral_24F" -I"../source" -I"../../../../Program Files (x86)/Microchip/MPLAB C30/include" -I"../include" -I"." -Os -MMD -MF "${OBJECTDIR}/_ext/812168374/SHT_driver.o.d" -o ${OBJECTDIR}/_ext/812168374/SHT_driver.o ../source/SHT_driver.c    
	
${OBJECTDIR}/_ext/812168374/rtcc.o: ../source/rtcc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/812168374" 
	@${RM} ${OBJECTDIR}/_ext/812168374/rtcc.o.d 
	@${RM} ${OBJECTDIR}/_ext/812168374/rtcc.o.ok ${OBJECTDIR}/_ext/812168374/rtcc.o.err 
	@${RM} ${OBJECTDIR}/_ext/812168374/rtcc.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/812168374/rtcc.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I".." -I"../../Microchip/Include" -I"../../../../Program Files (x86)/Microchip/MPLAB C30/support/peripheral_24F" -I"../source" -I"../../../../Program Files (x86)/Microchip/MPLAB C30/include" -I"../include" -I"." -Os -MMD -MF "${OBJECTDIR}/_ext/812168374/rtcc.o.d" -o ${OBJECTDIR}/_ext/812168374/rtcc.o ../source/rtcc.c    
	
${OBJECTDIR}/_ext/812168374/TempStation.o: ../source/TempStation.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/812168374" 
	@${RM} ${OBJECTDIR}/_ext/812168374/TempStation.o.d 
	@${RM} ${OBJECTDIR}/_ext/812168374/TempStation.o.ok ${OBJECTDIR}/_ext/812168374/TempStation.o.err 
	@${RM} ${OBJECTDIR}/_ext/812168374/TempStation.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/812168374/TempStation.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I".." -I"../../Microchip/Include" -I"../../../../Program Files (x86)/Microchip/MPLAB C30/support/peripheral_24F" -I"../source" -I"../../../../Program Files (x86)/Microchip/MPLAB C30/include" -I"../include" -I"." -Os -MMD -MF "${OBJECTDIR}/_ext/812168374/TempStation.o.d" -o ${OBJECTDIR}/_ext/812168374/TempStation.o ../source/TempStation.c    
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/TempStationX.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -omf=elf -mcpu=$(MP_PROCESSOR_OPTION)  -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1 -o dist/${CND_CONF}/${IMAGE_TYPE}/TempStationX.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}         -Wl,--defsym=__MPLAB_BUILD=1,-L"../../../../Program Files/Microchip/MPLAB C30/lib",-L".",-Map="TempStationX.X.${IMAGE_TYPE}.map"$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PICKIT2=1
else
dist/${CND_CONF}/${IMAGE_TYPE}/TempStationX.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -omf=elf -mcpu=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/TempStationX.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}         -Wl,--defsym=__MPLAB_BUILD=1,-L"../../../../Program Files/Microchip/MPLAB C30/lib",-L".",-Map="TempStationX.X.${IMAGE_TYPE}.map"$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION)
	${MP_CC_DIR}\\pic30-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/TempStationX.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} -omf=elf
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
