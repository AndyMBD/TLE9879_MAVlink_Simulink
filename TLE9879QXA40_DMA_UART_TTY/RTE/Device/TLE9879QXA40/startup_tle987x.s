;*******************************************************************************
;* @file     startup_TLE987x.s
;* @brief    CMSIS Core Device Startup File for
;*           Infineon TLE987x Device Series with IAR
;* @version  V1.1.1
;* @date     28. Feb 2022
;*
;* Copyright (C) Infineon Technologies AG. All rights reserved.
;*
;*
;* @par
;* Infineon Technologies AG (Infineon) is supplying this software for use with 
;* Infineon's microcontrollers.  This file can be freely distributed
;* within development tools that are supporting such microcontrollers.
;*
;* @par
;* THIS SOFTWARE IS PROVIDED AS IS.  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
;* OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
;* MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
;* ARM SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR
;* CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
;*
;*******************************************************************************

;***************************** Author(s) Identity ******************************
; DM   Daniel Mysliwitz
; JO   Julia Ott        
;*******************************************************************************

;******************************* Version History *******************************
; V1.1.0: 2018-12-06, DM:   Initial version
; V1.1.1: 2022-02-28, JO:   EP-936: Updated copyright and branding
;*******************************************************************************

        MODULE  ?vector_table

        AAPCS INTERWORK, VFP_COMPATIBLE, RWPI_COMPATIBLE
        PRESERVE8


        ;; Forward declaration of sections.
        SECTION CSTACK:DATA:NOROOT(3)

        SECTION .intvec:CODE:NOROOT(2)

        EXTERN  __iar_program_start
        EXTERN  SystemInit
        PUBLIC  __vector_table

        DATA

__iar_init$$done:													; The vector table is not needed
																					; until after copy initialization is done

__vector_table
				DCD     sfe(CSTACK)
				DCD     Reset_Handler
				DCD     NMI_Handler								; NMI Handler
				DCD     HardFault_Handler					; Hard Fault Handler
				DCD     MemManage_Handler					; MPU Fault Handler
				DCD     BusFault_Handler					; Bus Fault Handler
				DCD     UsageFault_Handler				; Usage Fault Handler
				DCD     0													; Reserved
				DCD     0													; Reserved
				DCD     0													; Reserved
				DCD     0													; Reserved
				DCD     SVC_Handler								; SVCall Handler
				DCD     DebugMon_Handler					; Debug Monitor Handler
				DCD     0													; Reserved
				DCD     PendSV_Handler						; PendSV Handler
				DCD     SysTick_Handler						; SysTick Handler
                
				; External Interrupts
				DCD     GPT1_IRQHandler						; 0:  GPT1
				DCD     GPT2_IRQHandler						; 1:  GPT2
				DCD     ADC2_IRQHandler						; 2:  Measurement Unit, Timer3
				DCD     ADC1_IRQHandler						; 3:  10 bit ADC
				DCD     CCU6SR0_IRQHandler				; 4:  CCU0
				DCD     CCU6SR1_IRQHandler				; 5:  CCU1
				DCD     CCU6SR2_IRQHandler				; 6:  CCU2
				DCD     CCU6SR3_IRQHandler				; 7:  CCU3
				DCD     SSC1_IRQHandler						; 8:  SSC1
				DCD     SSC2_IRQHandler						; 9:  SSC2
				DCD     UART1_IRQHandler					; 10: UART1
				DCD     UART2_IRQHandler					; 11: UART2
				DCD     EXINT0_IRQHandler					; 12: EXINT0
				DCD     EXINT1_IRQHandler					; 13: EXINT1
				DCD     BDRV_IRQHandler						; 14: BDRV
				DCD     DMA_IRQHandler						; 15: DMA

Default_Handler
        NOCALL Default_Handler
        B Default_Handler


        SECTION .text:CODE:REORDER:NOROOT(2)
        THUMB
Reset_Handler:
        LDR     R0, =SystemInit           ; Call the device specific initialization (core clock, PLL etc.)
        BLX     R0

        LDR     R0, =__iar_program_start
        BX      R0


				PUBWEAK     NMI_Handler						; NMI Handler
				SECTION .text:CODE:REORDER:NOROOT(1)
NMI_Handler
				B NMI_Handler


				PUBWEAK     HardFault_Handler			; Hard Fault Handler
				SECTION .text:CODE:REORDER:NOROOT(1)
HardFault_Handler
				B HardFault_Handler	


				PUBWEAK     MemManage_Handler			; MPU Fault Handler
				SECTION .text:CODE:REORDER:NOROOT(1)
MemManage_Handler
				B MemManage_Handler


				PUBWEAK     BusFault_Handler			; Bus Fault Handler
				SECTION .text:CODE:REORDER:NOROOT(1)
BusFault_Handler
				B BusFault_Handler	


				PUBWEAK     UsageFault_Handler		; Usage Fault Handler
				SECTION .text:CODE:REORDER:NOROOT(1)
UsageFault_Handler
				B UsageFault_Handler	


				PUBWEAK     SVC_Handler						; SVCall Handler
				SECTION .text:CODE:REORDER:NOROOT(1)
SVC_Handler
				B SVC_Handler	


				PUBWEAK     DebugMon_Handler			; Debug Monitor Handler
				SECTION .text:CODE:REORDER:NOROOT(1)
DebugMon_Handler
				B DebugMon_Handler	


				PUBWEAK     PendSV_Handler				; PendSV Handler
				SECTION .text:CODE:REORDER:NOROOT(1)
PendSV_Handler
				B PendSV_Handler	


				PUBWEAK     SysTick_Handler				; SysTick Handler
				SECTION .text:CODE:REORDER:NOROOT(1)
SysTick_Handler
				B SysTick_Handler				


				PUBWEAK     GPT1_IRQHandler				; 0:  GPT1
				SECTION .text:CODE:REORDER:NOROOT(1)
GPT1_IRQHandler
				B GPT1_IRQHandler	


				PUBWEAK     GPT2_IRQHandler				; 1:  GPT2
				SECTION .text:CODE:REORDER:NOROOT(1)
GPT2_IRQHandler
				B GPT2_IRQHandler	


				PUBWEAK     ADC1_IRQHandler				; 2:  Measurement Unit, Timer3
				SECTION .text:CODE:REORDER:NOROOT(1)
ADC1_IRQHandler
				B ADC1_IRQHandler	


				PUBWEAK     ADC2_IRQHandler				; 3:  10 bit ADC
				SECTION .text:CODE:REORDER:NOROOT(1)
ADC2_IRQHandler
				B ADC2_IRQHandler			


				PUBWEAK     CCU6SR0_IRQHandler		; 4:  CCU0
				SECTION .text:CODE:REORDER:NOROOT(1)
CCU6SR0_IRQHandler
				B CCU6SR0_IRQHandler		


				PUBWEAK     CCU6SR1_IRQHandler		; 5:  CCU1
				SECTION .text:CODE:REORDER:NOROOT(1)
CCU6SR1_IRQHandler
				B CCU6SR1_IRQHandler


				PUBWEAK     CCU6SR2_IRQHandler		; 6:  CCU2
				SECTION .text:CODE:REORDER:NOROOT(1)
CCU6SR2_IRQHandler
				B CCU6SR2_IRQHandler


				PUBWEAK     CCU6SR3_IRQHandler		; 7:  CCU3
				SECTION .text:CODE:REORDER:NOROOT(1)
CCU6SR3_IRQHandler
				B CCU6SR3_IRQHandler


				PUBWEAK     SSC1_IRQHandler				; 8:  SSC1
				SECTION .text:CODE:REORDER:NOROOT(1)
SSC1_IRQHandler
				B SSC1_IRQHandler


				PUBWEAK     SSC2_IRQHandler				; 9:  SSC2
				SECTION .text:CODE:REORDER:NOROOT(1)
SSC2_IRQHandler
				B SSC2_IRQHandler


				PUBWEAK     UART1_IRQHandler			; 10: UART1
				SECTION .text:CODE:REORDER:NOROOT(1)
UART1_IRQHandler
				B UART1_IRQHandler


				PUBWEAK     UART2_IRQHandler			; 11: UART2
				SECTION .text:CODE:REORDER:NOROOT(1)
UART2_IRQHandler
				B UART2_IRQHandler


				PUBWEAK     EXINT0_IRQHandler			; 12: EXINT0
				SECTION .text:CODE:REORDER:NOROOT(1)
EXINT0_IRQHandler
				B EXINT0_IRQHandler


				PUBWEAK     EXINT1_IRQHandler			; 13: EXINT1
				SECTION .text:CODE:REORDER:NOROOT(1)
EXINT1_IRQHandler
				B EXINT1_IRQHandler


				PUBWEAK     BDRV_IRQHandler				; 14: BDRV
				SECTION .text:CODE:REORDER:NOROOT(1)
BDRV_IRQHandler
				B BDRV_IRQHandler


				PUBWEAK     DMA_IRQHandler				; 15: DMA
				SECTION .text:CODE:REORDER:NOROOT(1)
DMA_IRQHandler
				B DMA_IRQHandler

				END