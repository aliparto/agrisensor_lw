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
OUTPUT_SUFFIX=a
DEBUGGABLE_SUFFIX=a
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/libSerialCom.X.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=a
DEBUGGABLE_SUFFIX=a
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/libSerialCom.X.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=Common/Delay.c Modbus.c UART.c SerialCom.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/Common/Delay.o ${OBJECTDIR}/Modbus.o ${OBJECTDIR}/UART.o ${OBJECTDIR}/SerialCom.o
POSSIBLE_DEPFILES=${OBJECTDIR}/Common/Delay.o.d ${OBJECTDIR}/Modbus.o.d ${OBJECTDIR}/UART.o.d ${OBJECTDIR}/SerialCom.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/Common/Delay.o ${OBJECTDIR}/Modbus.o ${OBJECTDIR}/UART.o ${OBJECTDIR}/SerialCom.o

# Source Files
SOURCEFILES=Common/Delay.c Modbus.c UART.c SerialCom.c


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
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/libSerialCom.X.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=24F16KL401
MP_LINKER_FILE_OPTION=,--script=p24F16KL401.gld
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/Common/Delay.o: Common/Delay.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Common" 
	@${RM} ${OBJECTDIR}/Common/Delay.o.d 
	@${RM} ${OBJECTDIR}/Common/Delay.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Common/Delay.c  -o ${OBJECTDIR}/Common/Delay.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Common/Delay.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mlarge-code -O0 -msmart-io=1 -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/Common/Delay.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Modbus.o: Modbus.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Modbus.o.d 
	@${RM} ${OBJECTDIR}/Modbus.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Modbus.c  -o ${OBJECTDIR}/Modbus.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Modbus.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mlarge-code -O0 -msmart-io=1 -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/Modbus.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/UART.o: UART.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/UART.o.d 
	@${RM} ${OBJECTDIR}/UART.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  UART.c  -o ${OBJECTDIR}/UART.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/UART.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mlarge-code -O0 -msmart-io=1 -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/UART.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/SerialCom.o: SerialCom.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/SerialCom.o.d 
	@${RM} ${OBJECTDIR}/SerialCom.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  SerialCom.c  -o ${OBJECTDIR}/SerialCom.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/SerialCom.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mlarge-code -O0 -msmart-io=1 -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/SerialCom.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
else
${OBJECTDIR}/Common/Delay.o: Common/Delay.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Common" 
	@${RM} ${OBJECTDIR}/Common/Delay.o.d 
	@${RM} ${OBJECTDIR}/Common/Delay.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Common/Delay.c  -o ${OBJECTDIR}/Common/Delay.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Common/Delay.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mlarge-code -O0 -msmart-io=1 -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/Common/Delay.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Modbus.o: Modbus.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Modbus.o.d 
	@${RM} ${OBJECTDIR}/Modbus.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Modbus.c  -o ${OBJECTDIR}/Modbus.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Modbus.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mlarge-code -O0 -msmart-io=1 -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/Modbus.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/UART.o: UART.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/UART.o.d 
	@${RM} ${OBJECTDIR}/UART.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  UART.c  -o ${OBJECTDIR}/UART.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/UART.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mlarge-code -O0 -msmart-io=1 -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/UART.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/SerialCom.o: SerialCom.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/SerialCom.o.d 
	@${RM} ${OBJECTDIR}/SerialCom.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  SerialCom.c  -o ${OBJECTDIR}/SerialCom.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/SerialCom.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mlarge-code -O0 -msmart-io=1 -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/SerialCom.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemblePreproc
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: archive
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/libSerialCom.X.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	@${RM} dist/${CND_CONF}/${IMAGE_TYPE}/libSerialCom.X.${OUTPUT_SUFFIX} 
	${MP_AR} $(MP_EXTRA_AR_PRE)  -omf=elf -r dist/${CND_CONF}/${IMAGE_TYPE}/libSerialCom.X.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/libSerialCom.X.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	@${RM} dist/${CND_CONF}/${IMAGE_TYPE}/libSerialCom.X.${OUTPUT_SUFFIX} 
	${MP_AR} $(MP_EXTRA_AR_PRE)  -omf=elf -r dist/${CND_CONF}/${IMAGE_TYPE}/libSerialCom.X.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      
	
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
