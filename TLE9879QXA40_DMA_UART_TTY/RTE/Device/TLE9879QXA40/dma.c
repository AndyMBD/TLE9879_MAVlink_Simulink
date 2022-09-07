/*
 ***********************************************************************************************************************
 *
 * Copyright (c) Infineon Technologies AG
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,are permitted provided that the
 * following conditions are met:
 *
 *   Redistributions of source code must retain the above copyright notice, this list of conditions and the  following
 *   disclaimer.
 *
 *   Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the
 *   following disclaimer in the documentation and/or other materials provided with the distribution.
 *
 *   Neither the name of the copyright holders nor the names of its contributors may be used to endorse or promote
 *   products derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE  FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY,OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT  OF THE
 * USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 **********************************************************************************************************************/

/*******************************************************************************
**                                  Includes                                  **
*******************************************************************************/

#include "dma.h"
#include "tle_variants.h"

/* the following defines are used to build the linker section for the ARMCC v6 **
** They violate the following MISRA 2012 rules:                                **
** - [MISRA 2012 Directive 4.9, advisory]                                      **
** - [MISRA 2012 Rule 20.10, advisory]                                         */

#if (RAMSize == 0xC00u)
  #define DMA_BASE_ADDR 0x18000A00u
#elif (RAMSize == 0x1800u)
  #define DMA_BASE_ADDR 0x18001600u
#elif (RAMSize == 0x2000u)
  #define DMA_BASE_ADDR 0x18001E00u
#else
  #error RAM size not supported
#endif /* RAMSize */

/* Arm Compiler 6 (armclang) */
#if (__ARMCC_VERSION > 6000000)
  #define MAKE_STRING( string ) #string
  #define MAKE_SECTION_NAME( part1, part2 ) MAKE_STRING( part1##part2 )
  #define AT_ADDRESS_ZI( address ) MAKE_SECTION_NAME( .bss.ARM.__at_,address )
#endif

/* The following warnings are disabled for ARMCC v6 Compiler */
/* Rules are only disabled for the current file */
#if defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6000000)
  #pragma clang diagnostic push
  #pragma clang diagnostic ignored "-Wmissing-variable-declarations"
  #pragma clang diagnostic ignored "-Wunreachable-code"
  #pragma clang diagnostic ignored "-Wpedantic"
  #pragma clang diagnostic ignored "-Wcovered-switch-default"
#endif

/*******************************************************************************
**                        Private Variable Definitions                        **
*******************************************************************************/
/* violation: Non-ANSI reserved word or construct: '_to_brackets' [MISRA Rule 1]*/
/* violation: Symbol '...' redeclared (void/nonvoid) [MISRA Rule 26], [Encompasses MISRA Rule 72]*/
/*
 * Config Wizard V1 XML V1.3.4 or greater
 * Config Wizard V2 XML V2.0.3 or greater
*/
#if (((DMA_XML_VERSION < 20000) && (DMA_XML_VERSION >= 10304)) || (DMA_XML_VERSION >= 20003))
/**********************************************************************************************************************
** DMA Channel 0 struct definition                                                                                   **
**********************************************************************************************************************/
#if ((DMA_EN & 1u) != 0u)
  #if defined(__ARMCC_VERSION) && (__ARMCC_VERSION < 6000000)
    /* ARMCC V5 */
    TDMA_Entry volatile DMA_Entry_Ch0_Pri  __attribute__((at(DMA_BASE_ADDR + DMA_CH0 *sizeof(TDMA_Entry)), used));
  #elif defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6000000)
    /* Arm Compiler 6 (armclang) */
    #if (RAMSize == 0xC00u)
      #define DMA_CH0_Pri_Addr 0x18000A00u
    #elif (RAMSize == 0x1800u)
      #define DMA_CH0_Pri_Addr 0x18001600u
    #elif (RAMSize == 0x2000u)
      #define DMA_CH0_Pri_Addr 0x18001E00u
    #else
      #error RAM size not supported
    #endif /* RAMSize */
    __attribute__((section(AT_ADDRESS_ZI(DMA_CH0_Pri_Addr)))) TDMA_Entry volatile DMA_Entry_Ch0_Pri ;
  #elif defined(__IAR_SYSTEMS_ICC__)
    #if (RAMSize == 0xC00u)
      #pragma location=0x18000A00u
    #elif (RAMSize == 0x1800u)
      #pragma location=0x18001600u
    #elif (RAMSize == 0x2000u)
      #pragma location=0x18001E00u
    #else
      #error RAM size not supported
    #endif /* RAMSize */
    TDMA_Entry volatile DMA_Entry_Ch0_Pri;
  #endif /* (__ARMCC_VERSION < 6000000) */
  #if (DMA_CH0_TRANS_MODE == 0)
    /* Basic Transfer */
    #if ((DMA_CH0_SRC_SEL == 1) && (DMA_CH0_SRC_EXT == 1))
      extern void DMA_CH0_SRC;
    #endif
    #if (DMA_CH0_DST_EXT == 1)
      extern void DMA_CH0_DST;
    #endif
  #else
    /* Scather-Gatter Transfer */
    #if defined(__ARMCC_VERSION) && (__ARMCC_VERSION < 6000000)
      /* ARMCC V5 */
      TDMA_Entry volatile DMA_Entry_Ch0_Alt  __attribute__((at((DMA_BASE_ADDR + 0x100) + DMA_CH0 *sizeof(TDMA_Entry)), used));
    #elif defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6000000)
      /* Arm Compiler 6 (armclang) */
      #if (RAMSize == 0xC00u)
        #define DMA_CH0_Alt_Addr 0x18000B00u
      #elif (RAMSize == 0x1800u)
        #define DMA_CH0_Alt_Addr 0x18001700u
      #elif (RAMSize == 0x2000u)
        #define DMA_CH0_Alt_Addr 0x18001F00u
      #else
        #error RAM size not supported
      #endif
      __attribute__((section(AT_ADDRESS_ZI(DMA_CH0_Alt_Addr)))) TDMA_Entry volatile DMA_Entry_Ch0_Alt ;
    #elif defined(__IAR_SYSTEMS_ICC__)
      #if (RAMSize == 0xC00u)
        #pragma location=0x18000B00u
      #elif (RAMSize == 0x1800u)
        #pragma location=0x18001700u
      #elif (RAMSize == 0x2000u)
        #pragma location=0x18001F00u
      #else
        #error RAM size not supported
      #endif /* RAMSize */
      TDMA_Entry volatile DMA_Entry_Ch0_Alt;
    #endif /* (__ARMCC_VERSION < 6000000) */
    #if (DMA_CH0_TASK_NoOfTasks == 0)
      #error "NoOfTasks = 0 not meaningful"
    #elif (DMA_CH0_TASK_NoOfTasks == 1)
      extern TDMA_Entry DMA_CH0_TASK_SRC;
    #else
      extern TDMA_Entry DMA_CH0_TASK_SRC[];
    #endif /*(DMA_CH0_TASK_NoOfTasks == 0)*/
  #endif /* (DMA_CH0_TRANS_MODE == 0) */
#endif
/**********************************************************************************************************************
** DMA Channel 1 struct definition                                                                                   **
**********************************************************************************************************************/
#if ((DMA_EN & (1u << DMA_CH1)) != 0u)
  #if defined(__ARMCC_VERSION) && (__ARMCC_VERSION < 6000000)
    /* ARMCC V5 */
    TDMA_Entry volatile DMA_Entry_Ch1_Pri  __attribute__((at(DMA_BASE_ADDR + DMA_CH1 *sizeof(TDMA_Entry)), used));
  #elif defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6000000)
    /* Arm Compiler 6 (armclang) */
    #if (RAMSize == 0xC00u)
      #define DMA_CH1_Pri_Addr 0x18000A10u
    #elif (RAMSize == 0x1800u)
      #define DMA_CH1_Pri_Addr 0x18001610u
    #elif (RAMSize == 0x2000u)
      #define DMA_CH1_Pri_Addr 0x18001E10u
    #else
      #error RAM size not supported
    #endif
    __attribute__((section(AT_ADDRESS_ZI(DMA_CH1_Pri_Addr)))) TDMA_Entry volatile DMA_Entry_Ch1_Pri ;
  #elif defined(__IAR_SYSTEMS_ICC__)
    #if (RAMSize == 0xC00u)
      #pragma location=0x18000A10u
    #elif (RAMSize == 0x1800u)
      #pragma location=0x18001610u
    #elif (RAMSize == 0x2000u)
      #pragma location=0x18001E10u
    #else
      #error RAM size not supported
    #endif /* RAMSize */
    TDMA_Entry volatile DMA_Entry_Ch1_Pri;
  #endif /* (__ARMCC_VERSION < 6000000) */
  #if (DMA_CH1_TRANS_MODE == 0)
    #if ((DMA_CH1_SRC_SEL == 1) && (DMA_CH1_SRC_EXT == 1))
      extern void DMA_CH1_SRC;
    #endif
    #if (DMA_CH1_DST_EXT == 1)
      extern void DMA_CH1_DST;
    #endif
  #else
    #if defined(__ARMCC_VERSION) && (__ARMCC_VERSION < 6000000)
      /* ARMCC V5 */
      TDMA_Entry volatile DMA_Entry_Ch1_Alt  __attribute__((at((DMA_BASE_ADDR + 0x100) + DMA_CH1 *sizeof(TDMA_Entry)), used));
    #elif defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6000000)
      /* Arm Compiler 6 (armclang) */
      #if (RAMSize == 0xC00u)
        #define DMA_CH1_Alt_Addr 0x18000B10u
      #elif (RAMSize == 0x1800u)
        #define DMA_CH1_Alt_Addr 0x18001710u
      #elif (RAMSize == 0x2000u)
        #define DMA_CH1_Alt_Addr 0x18001F10u
      #else
        #error RAM size not supported
      #endif
      __attribute__((section(AT_ADDRESS_ZI(DMA_CH1_Alt_Addr)))) TDMA_Entry volatile DMA_Entry_Ch1_Alt ;
    #elif defined(__IAR_SYSTEMS_ICC__)
      #if (RAMSize == 0xC00u)
        #pragma location=0x18000B10u
      #elif (RAMSize == 0x1800u)
        #pragma location=0x18001710u
      #elif (RAMSize == 0x2000u)
        #pragma location=0x18001F10u
      #else
        #error RAM size not supported
      #endif /* RAMSize */
      TDMA_Entry volatile DMA_Entry_Ch1_Alt;
    #endif /* (__ARMCC_VERSION < 6000000) */
    #if (DMA_CH1_TASK_NoOfTasks == 0)
      #error "NoOfTasks = 0 not meaningful"
    #elif (DMA_CH1_TASK_NoOfTasks == 1)
      extern TDMA_Entry DMA_CH1_TASK_SRC;
    #else
      extern TDMA_Entry DMA_CH1_TASK_SRC[];
    #endif /*(DMA_CH1_TASK_NoOfTasks == 0)*/
  #endif /* (DMA_CH1_TRANS_MODE == 0) */
#endif
/**********************************************************************************************************************
** DMA Channel 2 struct definition                                                                                   **
**********************************************************************************************************************/
#if ((DMA_EN & (1u << DMA_CH2)) != 0u)
  #if defined(__ARMCC_VERSION) && (__ARMCC_VERSION < 6000000)
    /* ARMCC V5 */
    TDMA_Entry volatile DMA_Entry_Ch2_Pri  __attribute__((at(DMA_BASE_ADDR + DMA_CH2 *sizeof(TDMA_Entry)), used));
  #elif defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6000000)
    /* Arm Compiler 6 (armclang) */
    #if (RAMSize == 0xC00u)
      #define DMA_CH2_Pri_Addr 0x18000A20u
    #elif (RAMSize == 0x1800u)
      #define DMA_CH2_Pri_Addr 0x18001620u
    #elif (RAMSize == 0x2000u)
      #define DMA_CH2_Pri_Addr 0x18001E20u
    #else
      #error RAM size not supported
    #endif
    __attribute__((section(AT_ADDRESS_ZI(DMA_CH2_Pri_Addr)))) TDMA_Entry volatile DMA_Entry_Ch2_Pri ;
  #elif defined(__IAR_SYSTEMS_ICC__)
    #if (RAMSize == 0xC00u)
      #pragma location=0x18000A20u
    #elif (RAMSize == 0x1800u)
      #pragma location=0x18001620u
    #elif (RAMSize == 0x2000u)
      #pragma location=0x18001E20u
    #else
      #error RAM size not supported
    #endif /* RAMSize */
    TDMA_Entry volatile DMA_Entry_Ch2_Pri;
  #endif
  #if (DMA_CH2_TRANS_MODE == 0)
    #if (DMA_CH2_SRC_EXT == 1)
      extern void DMA_CH2_SRC;
    #endif
    #if ((DMA_CH2_DST_SEL == 1) && (DMA_CH2_DST_EXT == 1))
      extern void DMA_CH2_DST;
    #endif
  #else
    #if defined(__ARMCC_VERSION) && (__ARMCC_VERSION < 6000000)
      /* ARMCC V5 */
      TDMA_Entry volatile DMA_Entry_Ch2_Alt  __attribute__((at((DMA_BASE_ADDR + 0x100) + DMA_CH2 *sizeof(TDMA_Entry)), used));
    #elif defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6000000)
      /* Arm Compiler 6 (armclang) */
      #if (RAMSize == 0xC00u)
        #define DMA_CH2_Alt_Addr 0x18000B20u
      #elif (RAMSize == 0x1800u)
        #define DMA_CH2_Alt_Addr 0x18001720u
      #elif (RAMSize == 0x2000u)
        #define DMA_CH2_Alt_Addr 0x18001F20u
      #else
        #error RAM size not supported
      #endif
      __attribute__((section(AT_ADDRESS_ZI(DMA_CH2_Alt_Addr)))) TDMA_Entry volatile DMA_Entry_Ch2_Alt ;
    #elif defined(__IAR_SYSTEMS_ICC__)
      #if (RAMSize == 0xC00u)
        #pragma location=0x18000B20u
      #elif (RAMSize == 0x1800u)
        #pragma location=0x18001720u
      #elif (RAMSize == 0x2000u)
        #pragma location=0x18001F20u
      #else
        #error RAM size not supported
      #endif /* RAMSize */
      TDMA_Entry volatile DMA_Entry_Ch2_Alt;
    #endif
    #if (DMA_CH2_TASK_NoOfTasks == 0)
      #error "NoOfTasks = 0 not meaningful"
    #elif (DMA_CH2_TASK_NoOfTasks == 1)
      extern TDMA_Entry DMA_CH2_TASK_SRC;
    #else
      extern TDMA_Entry DMA_CH2_TASK_SRC[];
    #endif /*(DMA_CH2_TASK_NoOfTasks == 0)*/
  #endif /* (DMA_CH2_TRANS_MODE == 0) */
#endif
/**********************************************************************************************************************
** DMA Channel 3 struct definition                                                                                   **
**********************************************************************************************************************/
#if ((DMA_EN & (1u << DMA_CH3)) != 0u)
  #if defined(__ARMCC_VERSION) && (__ARMCC_VERSION < 6000000)
    /* ARMCC V5 */
    TDMA_Entry volatile DMA_Entry_Ch3_Pri  __attribute__((at(DMA_BASE_ADDR + DMA_CH3 *sizeof(TDMA_Entry)), used));
  #elif defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6000000)
    /* Arm Compiler 6 (armclang) */
    #if (RAMSize == 0xC00u)
      #define DMA_CH3_Pri_Addr 0x18000A30u
    #elif (RAMSize == 0x1800u)
      #define DMA_CH3_Pri_Addr 0x18001630u
    #elif (RAMSize == 0x2000u)
      #define DMA_CH3_Pri_Addr 0x18001E30u
    #else
      #error RAM size not supported
    #endif
    __attribute__((section(AT_ADDRESS_ZI(DMA_CH3_Pri_Addr)))) TDMA_Entry volatile DMA_Entry_Ch3_Pri ;
  #elif defined(__IAR_SYSTEMS_ICC__)
    #if (RAMSize == 0xC00u)
      #pragma location=0x18000A30u
    #elif (RAMSize == 0x1800u)
      #pragma location=0x18001630u
    #elif (RAMSize == 0x2000u)
      #pragma location=0x18001E30u
    #else
      #error RAM size not supported
    #endif /* RAMSize */
    TDMA_Entry volatile DMA_Entry_Ch3_Pri;
  #endif
  #if (DMA_CH3_TRANS_MODE == 0)
    #if ((DMA_CH3_SRC_SEL == 1) && (DMA_CH3_SRC_EXT == 1))
      extern void DMA_CH3_SRC;
    #endif
    #if (DMA_CH3_DST_EXT == 1)
      extern void DMA_CH3_DST;
    #endif
  #else
    /* ARMCC V5 */
    #if defined(__ARMCC_VERSION) && (__ARMCC_VERSION < 6000000)
      TDMA_Entry volatile DMA_Entry_Ch3_Alt  __attribute__((at((DMA_BASE_ADDR + 0x100) + DMA_CH3 *sizeof(TDMA_Entry)), used));
      /* Arm Compiler 6 (armclang) */
    #elif defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6000000)
      #if (RAMSize == 0xC00u)
        #define DMA_CH3_Alt_Addr 0x18000B30u
      #elif (RAMSize == 0x1800u)
        #define DMA_CH3_Alt_Addr 0x18001730u
      #elif (RAMSize == 0x2000u)
        #define DMA_CH3_Alt_Addr 0x18001F30u
      #else
        #error RAM size not supported
      #endif
      __attribute__((section(AT_ADDRESS_ZI(DMA_CH3_Alt_Addr)))) TDMA_Entry volatile DMA_Entry_Ch3_Alt ;
    #elif defined(__IAR_SYSTEMS_ICC__)
      #if (RAMSize == 0xC00u)
        #pragma location=0x18000B30u
      #elif (RAMSize == 0x1800u)
        #pragma location=0x18001730u
      #elif (RAMSize == 0x2000u)
        #pragma location=0x18001F30u
      #else
        #error RAM size not supported
      #endif /* RAMSize */
      TDMA_Entry volatile DMA_Entry_Ch3_Alt;
    #endif
    #if (DMA_CH3_TASK_NoOfTasks == 0)
      #error "NoOfTasks = 0 not meaningful"
    #elif (DMA_CH3_TASK_NoOfTasks == 1)
      extern TDMA_Entry DMA_CH3_TASK_SRC;
    #else
      extern TDMA_Entry DMA_CH3_TASK_SRC[];
    #endif /*(DMA_CH3_TASK_NoOfTasks == 0)*/
  #endif /* (DMA_CH3_TRANS_MODE == 0) */
#endif
/**********************************************************************************************************************
** DMA Channel 4 struct definition                                                                                   **
**********************************************************************************************************************/
#if ((DMA_EN & (1u << DMA_CH4)) != 0u)
  #if defined(__ARMCC_VERSION) && (__ARMCC_VERSION < 6000000)
    /* ARMCC V5 */
    TDMA_Entry volatile DMA_Entry_Ch4_Pri  __attribute__((at(DMA_BASE_ADDR + DMA_CH4 *sizeof(TDMA_Entry)), used));
  #elif defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6000000)
    /* Arm Compiler 6 (armclang) */
    #if (RAMSize == 0xC00u)
      #define DMA_CH4_Pri_Addr 0x18000A40u
    #elif (RAMSize == 0x1800u)
      #define DMA_CH4_Pri_Addr 0x18001640u
    #elif (RAMSize == 0x2000u)
      #define DMA_CH4_Pri_Addr 0x18001E40u
    #else
      #error RAM size not supported
    #endif
    __attribute__((section(AT_ADDRESS_ZI(DMA_CH4_Pri_Addr)))) TDMA_Entry volatile DMA_Entry_Ch4_Pri ;
  #elif defined(__IAR_SYSTEMS_ICC__)
    #if (RAMSize == 0xC00u)
      #pragma location=0x18000A40u
    #elif (RAMSize == 0x1800u)
      #pragma location=0x18001640u
    #elif (RAMSize == 0x2000u)
      #pragma location=0x18001E40u
    #else
      #error RAM size not supported
    #endif /* RAMSize */
    TDMA_Entry volatile DMA_Entry_Ch4_Pri;
  #endif
  #if (DMA_CH4_TRANS_MODE == 0)
    #if ((DMA_CH4_SRC_SEL == 1) && (DMA_CH4_SRC_EXT == 1))
      extern void DMA_CH4_SRC;
    #endif
    #if (DMA_CH4_DST_EXT == 1)
      extern void DMA_CH4_DST;
    #endif
  #else
    #if defined(__ARMCC_VERSION) && (__ARMCC_VERSION < 6000000)
      /* ARMCC V5 */
      TDMA_Entry volatile DMA_Entry_Ch4_Alt  __attribute__((at((DMA_BASE_ADDR + 0x100) + DMA_CH4 *sizeof(TDMA_Entry)), used));
    #elif defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6000000)
      /* Arm Compiler 6 (armclang) */
      #if (RAMSize == 0xC00u)
        #define DMA_CH4_Alt_Addr 0x18000B40u
      #elif (RAMSize == 0x1800u)
        #define DMA_CH4_Alt_Addr 0x18001740u
      #elif (RAMSize == 0x2000u)
        #define DMA_CH4_Alt_Addr 0x18001F40u
      #else
        #error RAM size not supported
      #endif
      __attribute__((section(AT_ADDRESS_ZI(DMA_CH4_Alt_Addr)))) TDMA_Entry volatile DMA_Entry_Ch4_Alt ;
    #elif defined(__IAR_SYSTEMS_ICC__)
      #if (RAMSize == 0xC00u)
        #pragma location=0x18000B40u
      #elif (RAMSize == 0x1800u)
        #pragma location=0x18001740u
      #elif (RAMSize == 0x2000u)
        #pragma location=0x18001F40u
      #else
        #error RAM size not supported
      #endif /* RAMSize */
      TDMA_Entry volatile DMA_Entry_Ch4_Alt;
    #endif
    #if (DMA_CH4_TASK_NoOfTasks == 0)
      #error "NoOfTasks = 0 not meaningful"
    #elif (DMA_CH4_TASK_NoOfTasks == 1)
      extern TDMA_Entry DMA_CH4_TASK_SRC;
    #else
      extern TDMA_Entry DMA_CH4_TASK_SRC[];
    #endif /*(DMA_CH4_TASK_NoOfTasks == 0)*/
  #endif /* (DMA_CH4_TRANS_MODE == 0) */
#endif
/**********************************************************************************************************************
** DMA Channel 5 struct definition                                                                                   **
**********************************************************************************************************************/
#if ((DMA_EN & (1u << DMA_CH5)) != 0u)
  #if defined(__ARMCC_VERSION) && (__ARMCC_VERSION < 6000000)
    /* ARMCC V5 */
    TDMA_Entry volatile DMA_Entry_Ch5_Pri  __attribute__((at(DMA_BASE_ADDR + DMA_CH5 *sizeof(TDMA_Entry)), used));
  #elif defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6000000)
    /* Arm Compiler 6 (armclang) */
    #if (RAMSize == 0xC00u)
      #define DMA_CH5_Pri_Addr 0x18000A50u
    #elif (RAMSize == 0x1800u)
      #define DMA_CH5_Pri_Addr 0x18001650u
    #elif (RAMSize == 0x2000u)
      #define DMA_CH5_Pri_Addr 0x18001E50u
    #else
      #error RAM size not supported
    #endif
    __attribute__((section(AT_ADDRESS_ZI(DMA_CH5_Pri_Addr)))) TDMA_Entry volatile DMA_Entry_Ch5_Pri ;
  #elif defined(__IAR_SYSTEMS_ICC__)
    #if (RAMSize == 0xC00u)
      #pragma location=0x18000A50u
    #elif (RAMSize == 0x1800u)
      #pragma location=0x18001650u
    #elif (RAMSize == 0x2000u)
      #pragma location=0x18001E50u
    #else
      #error RAM size not supported
    #endif /* RAMSize */
    TDMA_Entry volatile DMA_Entry_Ch5_Pri;
  #endif
  #if (DMA_CH5_TRANS_MODE == 0)
    #if ((DMA_CH5_SRC_SEL == 1) && (DMA_CH5_SRC_EXT == 1))
      extern void DMA_CH5_SRC;
    #endif
    #if (DMA_CH5_DST_EXT == 1)
      extern void DMA_CH5_DST;
    #endif
  #else
    #if defined(__ARMCC_VERSION) && (__ARMCC_VERSION < 6000000)
      /* ARMCC V5 */
      TDMA_Entry volatile DMA_Entry_Ch5_Alt  __attribute__((at((DMA_BASE_ADDR + 0x100) + DMA_CH5 *sizeof(TDMA_Entry)), used));
    #elif defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6000000)
      /* Arm Compiler 6 (armclang) */
      #if (RAMSize == 0xC00u)
        #define DMA_CH5_Alt_Addr 0x18000B50u
      #elif (RAMSize == 0x1800u)
        #define DMA_CH5_Alt_Addr 0x18001750u
      #elif (RAMSize == 0x2000u)
        #define DMA_CH5_Alt_Addr 0x18001F50u
      #else
        #error RAM size not supported
      #endif
      __attribute__((section(AT_ADDRESS_ZI(DMA_CH5_Alt_Addr)))) TDMA_Entry volatile DMA_Entry_Ch5_Alt ;
    #elif defined(__IAR_SYSTEMS_ICC__)
      #if (RAMSize == 0xC00u)
        #pragma location=0x18000B50u
      #elif (RAMSize == 0x1800u)
        #pragma location=0x18001750u
      #elif (RAMSize == 0x2000u)
        #pragma location=0x18001F50u
      #else
        #error RAM size not supported
      #endif /* RAMSize */
      TDMA_Entry volatile DMA_Entry_Ch5_Alt;
    #endif
    #if (DMA_CH5_TASK_NoOfTasks == 0)
      #error "NoOfTasks = 0 not meaningful"
    #elif (DMA_CH5_TASK_NoOfTasks == 1)
      extern TDMA_Entry DMA_CH5_TASK_SRC;
    #else
      extern TDMA_Entry DMA_CH5_TASK_SRC[];
    #endif /*(DMA_CH5_TASK_NoOfTasks == 0)*/
  #endif /* (DMA_CH5_TRANS_MODE == 0) */
#endif
/**********************************************************************************************************************
** DMA Channel 6 struct definition                                                                                   **
**********************************************************************************************************************/
#if ((DMA_EN & (1u << DMA_CH6)) != 0u)
  #if defined(__ARMCC_VERSION) && (__ARMCC_VERSION < 6000000)
    /* ARMCC V5 */
    TDMA_Entry volatile DMA_Entry_Ch6_Pri  __attribute__((at(DMA_BASE_ADDR + DMA_CH6 *sizeof(TDMA_Entry)), used));
  #elif defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6000000)
    /* Arm Compiler 6 (armclang) */
    #if (RAMSize == 0xC00u)
      #define DMA_CH6_Pri_Addr 0x18000A60u
    #elif (RAMSize == 0x1800u)
      #define DMA_CH6_Pri_Addr 0x18001660u
    #elif (RAMSize == 0x2000u)
      #define DMA_CH6_Pri_Addr 0x18001E60u
    #else
      #error RAM size not supported
    #endif
    __attribute__((section(AT_ADDRESS_ZI(DMA_CH6_Pri_Addr)))) TDMA_Entry volatile DMA_Entry_Ch6_Pri ;
  #elif defined(__IAR_SYSTEMS_ICC__)
    #if (RAMSize == 0xC00u)
      #pragma location=0x18000A60u
    #elif (RAMSize == 0x1800u)
      #pragma location=0x18001660u
    #elif (RAMSize == 0x2000u)
      #pragma location=0x18001E60u
    #else
      #error RAM size not supported
    #endif /* RAMSize */
    TDMA_Entry volatile DMA_Entry_Ch6_Pri;
  #endif
  #if (DMA_CH6_TRANS_MODE == 0)
    #if ((DMA_CH6_SRC_SEL == 1) && (DMA_CH6_SRC_EXT == 1))
      extern void DMA_CH6_SRC;
    #endif
    #if (DMA_CH6_DST_EXT == 1)
      extern void DMA_CH6_DST;
    #endif
  #else
    #if defined(__ARMCC_VERSION) && (__ARMCC_VERSION < 6000000)
      /* ARMCC V5 */
      TDMA_Entry volatile DMA_Entry_Ch6_Alt  __attribute__((at((DMA_BASE_ADDR + 0x100) + DMA_CH6 *sizeof(TDMA_Entry)), used));
    #elif defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6000000)
      /* Arm Compiler 6 (armclang) */
      #if (RAMSize == 0xC00u)
        #define DMA_CH6_Alt_Addr 0x18000B60u
      #elif (RAMSize == 0x1800u)
        #define DMA_CH6_Alt_Addr 0x18001760u
      #elif (RAMSize == 0x2000u)
        #define DMA_CH6_Alt_Addr 0x18001F60u
      #else
        #error RAM size not supported
      #endif
      __attribute__((section(AT_ADDRESS_ZI(DMA_CH6_Alt_Addr)))) TDMA_Entry volatile DMA_Entry_Ch6_Alt ;
    #elif defined(__IAR_SYSTEMS_ICC__)
      #if (RAMSize == 0xC00u)
        #pragma location=0x18000B60u
      #elif (RAMSize == 0x1800u)
        #pragma location=0x18001760u
      #elif (RAMSize == 0x2000u)
        #pragma location=0x18001F60u
      #else
        #error RAM size not supported
      #endif /* RAMSize */
      TDMA_Entry volatile DMA_Entry_Ch6_Alt;
    #endif
    #if (DMA_CH6_TASK_NoOfTasks == 0)
      #error "NoOfTasks = 0 not meaningful"
    #elif (DMA_CH6_TASK_NoOfTasks == 1)
      extern TDMA_Entry DMA_CH6_TASK_SRC;
    #else
      extern TDMA_Entry DMA_CH6_TASK_SRC[];
    #endif /*(DMA_CH6_TASK_NoOfTasks == 0)*/
  #endif /* (DMA_CH6_TRANS_MODE == 0) */
#endif
/**********************************************************************************************************************
** DMA Channel 7 struct definition                                                                                   **
**********************************************************************************************************************/
#if ((DMA_EN & (1u << DMA_CH7)) != 0u)
  #if defined(__ARMCC_VERSION) && (__ARMCC_VERSION < 6000000)
    /* ARMCC V5 */
    TDMA_Entry volatile DMA_Entry_Ch7_Pri  __attribute__((at(DMA_BASE_ADDR + DMA_CH7 *sizeof(TDMA_Entry)), used));
  #elif defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6000000)
    /* Arm Compiler 6 (armclang) */
    #if (RAMSize == 0xC00u)
      #define DMA_CH7_Pri_Addr 0x18000A70u
    #elif (RAMSize == 0x1800u)
      #define DMA_CH7_Pri_Addr 0x18001670u
    #elif (RAMSize == 0x2000u)
      #define DMA_CH7_Pri_Addr 0x18001E70u
    #else
      #error RAM size not supported
    #endif
    __attribute__((section(AT_ADDRESS_ZI(DMA_CH7_Pri_Addr)))) TDMA_Entry volatile DMA_Entry_Ch7_Pri ;
  #elif defined(__IAR_SYSTEMS_ICC__)
    #if (RAMSize == 0xC00u)
      #pragma location=0x18000A70u
    #elif (RAMSize == 0x1800u)
      #pragma location=0x18001670u
    #elif (RAMSize == 0x2000u)
      #pragma location=0x18001E70u
    #else
      #error RAM size not supported
    #endif /* RAMSize */
    TDMA_Entry volatile DMA_Entry_Ch7_Pri;
  #endif
  #if (DMA_CH7_TRANS_MODE == 0)
    #if ((DMA_CH7_SRC_SEL == 1) && (DMA_CH7_SRC_EXT == 1))
      extern void DMA_CH7_SRC;
    #endif
    #if (DMA_CH7_DST_EXT == 1)
      extern void DMA_CH7_DST;
    #endif
  #else
    #if defined(__ARMCC_VERSION) && (__ARMCC_VERSION < 6000000)
      /* ARMCC V5 */
      TDMA_Entry volatile DMA_Entry_Ch7_Alt  __attribute__((at((DMA_BASE_ADDR + 0x100) + DMA_CH7 *sizeof(TDMA_Entry)), used));
    #elif defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6000000)
      /* Arm Compiler 6 (armclang) */
      #if (RAMSize == 0xC00u)
        #define DMA_CH7_Alt_Addr 0x18000B70u
      #elif (RAMSize == 0x1800u)
        #define DMA_CH7_Alt_Addr 0x18001770u
      #elif (RAMSize == 0x2000u)
        #define DMA_CH7_Alt_Addr 0x18001F70u
      #else
        #error RAM size not supported
      #endif
      __attribute__((section(AT_ADDRESS_ZI(DMA_CH7_Alt_Addr)))) TDMA_Entry volatile DMA_Entry_Ch7_Alt ;
    #elif defined(__IAR_SYSTEMS_ICC__)
      #if (RAMSize == 0xC00u)
        #pragma location=0x18000B70u
      #elif (RAMSize == 0x1800u)
        #pragma location=0x18001770u
      #elif (RAMSize == 0x2000u)
        #pragma location=0x18001F70u
      #else
        #error RAM size not supported
      #endif /* RAMSize */
      TDMA_Entry volatile DMA_Entry_Ch7_Alt;
    #endif
    #if (DMA_CH7_TASK_NoOfTasks == 0)
      #error "NoOfTasks = 0 not meaningful"
    #elif (DMA_CH7_TASK_NoOfTasks == 1)
      extern TDMA_Entry DMA_CH7_TASK_SRC;
    #else
      extern TDMA_Entry DMA_CH7_TASK_SRC[];
    #endif /*(DMA_CH7_TASK_NoOfTasks == 0)*/
  #endif /* (DMA_CH7_TRANS_MODE == 0) */
#endif
/**********************************************************************************************************************
** DMA Channel 8 struct definition                                                                                   **
**********************************************************************************************************************/
/* violation: the shift value is at least the precision of the essential type of the left hand side [MISRA 2012 Rule 12.2, required] */
#if ((DMA_EN & (1u << DMA_CH8)) != 0u)
  #if defined(__ARMCC_VERSION) && (__ARMCC_VERSION < 6000000)
    /* ARMCC V5 */
    TDMA_Entry volatile DMA_Entry_Ch8_Pri  __attribute__((at(DMA_BASE_ADDR + DMA_CH8 *sizeof(TDMA_Entry)), used));
  #elif defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6000000)
    /* Arm Compiler 6 (armclang) */
    #if (RAMSize == 0xC00u)
      #define DMA_CH8_Pri_Addr 0x18000A80u
    #elif (RAMSize == 0x1800u)
      #define DMA_CH8_Pri_Addr 0x18001680u
    #elif (RAMSize == 0x2000u)
      #define DMA_CH8_Pri_Addr 0x18001E80u
    #else
      #error RAM size not supported
    #endif
    __attribute__((section(AT_ADDRESS_ZI(DMA_CH8_Pri_Addr)))) TDMA_Entry volatile DMA_Entry_Ch8_Pri ;
  #elif defined(__IAR_SYSTEMS_ICC__)
    #if (RAMSize == 0xC00u)
      #pragma location=0x18000A80u
    #elif (RAMSize == 0x1800u)
      #pragma location=0x18001680u
    #elif (RAMSize == 0x2000u)
      #pragma location=0x18001E80u
    #else
      #error RAM size not supported
    #endif /* RAMSize */
    TDMA_Entry volatile DMA_Entry_Ch8_Pri;
  #endif
  #if (DMA_CH8_TRANS_MODE == 0)
    #if ((DMA_CH8_SRC_SEL == 1) && (DMA_CH8_SRC_EXT == 1))
      extern void DMA_CH8_SRC;
    #endif
    #if (DMA_CH8_DST_EXT == 1)
      extern void DMA_CH8_DST;
    #endif
  #else
    #if defined(__ARMCC_VERSION) && (__ARMCC_VERSION < 6000000)
      /* ARMCC V5 */
      TDMA_Entry volatile DMA_Entry_Ch8_Alt  __attribute__((at((DMA_BASE_ADDR + 0x100) + DMA_CH8 *sizeof(TDMA_Entry)), used));
    #elif defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6000000)
      /* Arm Compiler 6 (armclang) */
      #if (RAMSize == 0xC00u)
        #define DMA_CH8_Alt_Addr 0x18000B80u
      #elif (RAMSize == 0x1800u)
        #define DMA_CH8_Alt_Addr 0x18001780u
      #elif (RAMSize == 0x2000u)
        #define DMA_CH8_Alt_Addr 0x18001F80u
      #else
        #error RAM size not supported
      #endif
      __attribute__((section(AT_ADDRESS_ZI(DMA_CH8_Alt_Addr)))) TDMA_Entry volatile DMA_Entry_Ch8_Alt ;
    #elif defined(__IAR_SYSTEMS_ICC__)
      #if (RAMSize == 0xC00u)
        #pragma location=0x18000B80u
      #elif (RAMSize == 0x1800u)
        #pragma location=0x18001780u
      #elif (RAMSize == 0x2000u)
        #pragma location=0x18001F80u
      #else
        #error RAM size not supported
      #endif /* RAMSize */
      TDMA_Entry volatile DMA_Entry_Ch8_Alt;
    #endif
    #if (DMA_CH8_TASK_NoOfTasks == 0)
      #error "NoOfTasks = 0 not meaningful"
    #elif (DMA_CH8_TASK_NoOfTasks == 1)
      extern TDMA_Entry DMA_CH8_TASK_SRC;
    #else
      extern TDMA_Entry DMA_CH8_TASK_SRC[];
    #endif /*(DMA_CH8_TASK_NoOfTasks == 0)*/
  #endif /* (DMA_CH8_TRANS_MODE == 0) */
#endif
/**********************************************************************************************************************
** DMA Channel 9 struct definition                                                                                   **
**********************************************************************************************************************/
/* violation: the shift value is at least the precision of the essential type of the left hand side [MISRA 2012 Rule 12.2, required] */
#if ((DMA_EN & (1u << DMA_CH9)) != 0u)
  #if defined(__ARMCC_VERSION) && (__ARMCC_VERSION < 6000000)
    /* ARMCC V5 */
    TDMA_Entry volatile DMA_Entry_Ch9_Pri  __attribute__((at(DMA_BASE_ADDR + DMA_CH9 *sizeof(TDMA_Entry)), used));
  #elif defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6000000)
    /* Arm Compiler 6 (armclang) */
    #if (RAMSize == 0xC00u)
      #define DMA_CH9_Pri_Addr 0x18000A90u
    #elif (RAMSize == 0x1800u)
      #define DMA_CH9_Pri_Addr 0x18001690u
    #elif (RAMSize == 0x2000u)
      #define DMA_CH9_Pri_Addr 0x18001E90u
    #else
      #error RAM size not supported
    #endif
    __attribute__((section(AT_ADDRESS_ZI(DMA_CH9_Pri_Addr)))) TDMA_Entry volatile DMA_Entry_Ch9_Pri ;
  #elif defined(__IAR_SYSTEMS_ICC__)
    #if (RAMSize == 0xC00u)
      #pragma location=0x18000A90u
    #elif (RAMSize == 0x1800u)
      #pragma location=0x18001690u
    #elif (RAMSize == 0x2000u)
      #pragma location=0x18001E90u
    #else
      #error RAM size not supported
    #endif /* RAMSize */
    TDMA_Entry volatile DMA_Entry_Ch9_Pri;
  #endif
  #if (DMA_CH9_TRANS_MODE == 0)
    #if ((DMA_CH9_SRC_SEL == 1) && (DMA_CH9_SRC_EXT == 1))
      extern void DMA_CH9_SRC;
    #endif
    #if (DMA_CH9_DST_EXT == 1)
      extern void DMA_CH9_DST;
    #endif
  #else
    #if defined(__ARMCC_VERSION) && (__ARMCC_VERSION < 6000000)
      /* ARMCC V5 */
      TDMA_Entry volatile DMA_Entry_Ch9_Alt  __attribute__((at((DMA_BASE_ADDR + 0x100) + DMA_CH9 *sizeof(TDMA_Entry)), used));
    #elif defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6000000)
      /* Arm Compiler 6 (armclang) */
      #if (RAMSize == 0xC00u)
        #define DMA_CH9_Alt_Addr 0x18000B90u
      #elif (RAMSize == 0x1800u)
        #define DMA_CH9_Alt_Addr 0x18001790u
      #elif (RAMSize == 0x2000u)
        #define DMA_CH9_Alt_Addr 0x18001F90u
      #else
        #error RAM size not supported
      #endif
      __attribute__((section(AT_ADDRESS_ZI(DMA_CH9_Alt_Addr)))) TDMA_Entry volatile DMA_Entry_Ch9_Alt ;
    #elif defined(__IAR_SYSTEMS_ICC__)
      #if (RAMSize == 0xC00u)
        #pragma location=0x18000B90u
      #elif (RAMSize == 0x1800u)
        #pragma location=0x18001790u
      #elif (RAMSize == 0x2000u)
        #pragma location=0x18001F90u
      #else
        #error RAM size not supported
      #endif /* RAMSize */
      TDMA_Entry volatile DMA_Entry_Ch9_Alt;
    #endif
    #if (DMA_CH9_TASK_NoOfTasks == 0)
      #error "NoOfTasks = 0 not meaningful"
    #elif (DMA_CH9_TASK_NoOfTasks == 1)
      extern TDMA_Entry DMA_CH9_TASK_SRC;
    #else
      extern TDMA_Entry DMA_CH9_TASK_SRC[];
    #endif /*(DMA_CH9_TASK_NoOfTasks == 0)*/
  #endif /* (DMA_CH9_TRANS_MODE == 0) */
#endif
/**********************************************************************************************************************
** DMA Channel 10 struct definition                                                                                   **
**********************************************************************************************************************/
/* violation: the shift value is at least the precision of the essential type of the left hand side [MISRA 2012 Rule 12.2, required] */
#if ((DMA_EN & (1u << DMA_CH10)) != 0u)
  #if defined(__ARMCC_VERSION) && (__ARMCC_VERSION < 6000000)
    /* ARMCC V5 */
    TDMA_Entry volatile DMA_Entry_Ch10_Pri  __attribute__((at(DMA_BASE_ADDR + DMA_CH10 *sizeof(TDMA_Entry)), used));
  #elif defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6000000)
    /* Arm Compiler 6 (armclang) */
    #if (RAMSize == 0xC00u)
      #define DMA_CH10_Pri_Addr 0x18000AA0u
    #elif (RAMSize == 0x1800u)
      #define DMA_CH10_Pri_Addr 0x180016A0u
    #elif (RAMSize == 0x2000u)
      #define DMA_CH10_Pri_Addr 0x18001EA0u
    #else
      #error RAM size not supported
    #endif
    __attribute__((section(AT_ADDRESS_ZI(DMA_CH10_Pri_Addr)))) TDMA_Entry volatile DMA_Entry_Ch10_Pri ;
  #elif defined(__IAR_SYSTEMS_ICC__)
    #if (RAMSize == 0xC00u)
      #pragma location=0x18000AA0u
    #elif (RAMSize == 0x1800u)
      #pragma location=0x180016A0u
    #elif (RAMSize == 0x2000u)
      #pragma location=0x18001EA0u
    #else
      #error RAM size not supported
    #endif /* RAMSize */
    TDMA_Entry volatile DMA_Entry_Ch10_Pri;
  #endif
  #if (DMA_CH10_TRANS_MODE == 0)
    #if ((DMA_CH10_SRC_SEL == 1) && (DMA_CH10_SRC_EXT == 1))
      extern void DMA_CH10_SRC;
    #endif
    #if (DMA_CH10_DST_EXT == 1)
      extern void DMA_CH10_DST;
    #endif
  #else
    #if defined(__ARMCC_VERSION) && (__ARMCC_VERSION < 6000000)
      /* ARMCC V5 */
      TDMA_Entry volatile DMA_Entry_Ch10_Alt  __attribute__((at((DMA_BASE_ADDR + 0x100) + DMA_CH10 *sizeof(TDMA_Entry)), used));
    #elif defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6000000)
      /* Arm Compiler 6 (armclang) */
      #if (RAMSize == 0xC00u)
        #define DMA_CH10_Alt_Addr 0x18000BA0u
      #elif (RAMSize == 0x1800u)
        #define DMA_CH10_Alt_Addr 0x180017A0u
      #elif (RAMSize == 0x2000u)
        #define DMA_CH10_Alt_Addr 0x18001FA0u
      #else
        #error RAM size not supported
      #endif
      __attribute__((section(AT_ADDRESS_ZI(DMA_CH10_Alt_Addr)))) TDMA_Entry volatile DMA_Entry_Ch10_Alt ;
    #elif defined(__IAR_SYSTEMS_ICC__)
      #if (RAMSize == 0xC00u)
        #pragma location=0x18000BA0u
      #elif (RAMSize == 0x1800u)
        #pragma location=0x180017A0u
      #elif (RAMSize == 0x2000u)
        #pragma location=0x18001FA0u
      #else
        #error RAM size not supported
      #endif /* RAMSize */
      TDMA_Entry volatile DMA_Entry_Ch10_Alt;
    #endif
    #if (DMA_CH10_TASK_NoOfTasks == 0)
      #error "NoOfTasks = 0 not meaningful"
    #elif (DMA_CH10_TASK_NoOfTasks == 1)
      extern TDMA_Entry DMA_CH10_TASK_SRC;
    #else
      extern TDMA_Entry DMA_CH10_TASK_SRC[];
    #endif /*(DMA_CH10_TASK_NoOfTasks == 0)*/
  #endif /* (DMA_CH10_TRANS_MODE == 0) */
#endif
/**********************************************************************************************************************
** DMA Channel 11 struct definition                                                                                   **
**********************************************************************************************************************/
/* violation: the shift value is at least the precision of the essential type of the left hand side [MISRA 2012 Rule 12.2, required] */
#if ((DMA_EN & (1u << DMA_CH11)) != 0u)
  #if defined(__ARMCC_VERSION) && (__ARMCC_VERSION < 6000000)
    /* ARMCC V5 */
    TDMA_Entry volatile DMA_Entry_Ch11_Pri  __attribute__((at(DMA_BASE_ADDR + DMA_CH11 *sizeof(TDMA_Entry)), used));
  #elif defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6000000)
    /* Arm Compiler 6 (armclang) */
    #if (RAMSize == 0xC00u)
      #define DMA_CH11_Pri_Addr 0x18000AB0u
    #elif (RAMSize == 0x1800u)
      #define DMA_CH11_Pri_Addr 0x180016B0u
    #elif (RAMSize == 0x2000u)
      #define DMA_CH11_Pri_Addr 0x18001EB0u
    #else
      #error RAM size not supported
    #endif
    __attribute__((section(AT_ADDRESS_ZI(DMA_CH11_Pri_Addr)))) TDMA_Entry volatile DMA_Entry_Ch11_Pri ;
  #elif defined(__IAR_SYSTEMS_ICC__)
    #if (RAMSize == 0xC00u)
      #pragma location=0x18000AB0u
    #elif (RAMSize == 0x1800u)
      #pragma location=0x180016B0u
    #elif (RAMSize == 0x2000u)
      #pragma location=0x18001EB0u
    #else
      #error RAM size not supported
    #endif /* RAMSize */
    TDMA_Entry volatile DMA_Entry_Ch11_Pri;
  #endif
  #if (DMA_CH11_TRANS_MODE == 0)
    #if (DMA_CH11_SRC_EXT == 1)
      extern void DMA_CH11_SRC;
    #endif
    #if (DMA_CH11_DST_EXT == 1)
      extern void DMA_CH11_DST;
    #endif
  #else
    #if defined(__ARMCC_VERSION) && (__ARMCC_VERSION < 6000000)
      /* ARMCC V5 */
      TDMA_Entry volatile DMA_Entry_Ch11_Alt  __attribute__((at((DMA_BASE_ADDR + 0x100) + DMA_CH11 *sizeof(TDMA_Entry)), used));
    #elif defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6000000)
      /* Arm Compiler 6 (armclang) */
      #if (RAMSize == 0xC00u)
        #define DMA_CH11_Alt_Addr 0x18000BB0u
      #elif (RAMSize == 0x1800u)
        #define DMA_CH11_Alt_Addr 0x180017B0u
      #elif (RAMSize == 0x2000u)
        #define DMA_CH11_Alt_Addr 0x18001FB0u
      #else
        #error RAM size not supported
      #endif
      __attribute__((section(AT_ADDRESS_ZI(DMA_CH11_Alt_Addr)))) TDMA_Entry volatile DMA_Entry_Ch11_Alt ;
    #elif defined(__IAR_SYSTEMS_ICC__)
      #if (RAMSize == 0xC00u)
        #pragma location=0x18000BB0u
      #elif (RAMSize == 0x1800u)
        #pragma location=0x180017B0u
      #elif (RAMSize == 0x2000u)
        #pragma location=0x18001FB0u
      #else
        #error RAM size not supported
      #endif /* RAMSize */
      TDMA_Entry volatile DMA_Entry_Ch11_Alt;
    #endif
    #if (DMA_CH11_TASK_NoOfTasks == 0)
      #error "NoOfTasks = 0 not meaningful"
    #elif (DMA_CH11_TASK_NoOfTasks == 1)
      extern TDMA_Entry DMA_CH11_TASK_SRC;
    #else
      extern TDMA_Entry DMA_CH11_TASK_SRC[];
    #endif /*(DMA_CH11_TASK_NoOfTasks == 0)*/
  #endif /* (DMA_CH11_TRANS_MODE == 0) */
#endif
/**********************************************************************************************************************
** DMA Channel 12 struct definition                                                                                   **
**********************************************************************************************************************/
/* violation: the shift value is at least the precision of the essential type of the left hand side [MISRA 2012 Rule 12.2, required] */
#if ((DMA_EN & (1u << DMA_CH12)) != 0u)
  #if defined(__ARMCC_VERSION) && (__ARMCC_VERSION < 6000000)
    /* ARMCC V5 */
    TDMA_Entry volatile DMA_Entry_Ch12_Pri  __attribute__((at(DMA_BASE_ADDR + DMA_CH12 *sizeof(TDMA_Entry)), used));
  #elif defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6000000)
    /* Arm Compiler 6 (armclang) */
    #if (RAMSize == 0xC00u)
      #define DMA_CH12_Pri_Addr 0x18000AC0u
    #elif (RAMSize == 0x1800u)
      #define DMA_CH12_Pri_Addr 0x180016C0u
    #elif (RAMSize == 0x2000u)
      #define DMA_CH12_Pri_Addr 0x18001EC0u
    #else
      #error RAM size not supported
    #endif
    __attribute__((section(AT_ADDRESS_ZI(DMA_CH12_Pri_Addr)))) TDMA_Entry volatile DMA_Entry_Ch12_Pri ;
  #elif defined(__IAR_SYSTEMS_ICC__)
    #if (RAMSize == 0xC00u)
      #pragma location=0x18000AC0u
    #elif (RAMSize == 0x1800u)
      #pragma location=0x180016C0u
    #elif (RAMSize == 0x2000u)
      #pragma location=0x18001EC0u
    #else
      #error RAM size not supported
    #endif /* RAMSize */
    TDMA_Entry volatile DMA_Entry_Ch12_Pri;
  #endif
  #if (DMA_CH12_TRANS_MODE == 0)
    #if (DMA_CH12_SRC_EXT == 1)
      extern void DMA_CH12_SRC;
    #endif
    #if (DMA_CH12_DST_EXT == 1)
      extern void DMA_CH12_DST;
    #endif
  #else
    #if defined(__ARMCC_VERSION) && (__ARMCC_VERSION < 6000000)
      /* ARMCC V5 */
      TDMA_Entry volatile DMA_Entry_Ch12_Alt  __attribute__((at((DMA_BASE_ADDR + 0x100) + DMA_CH12 *sizeof(TDMA_Entry)), used));
    #elif defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6000000)
      /* Arm Compiler 6 (armclang) */
      #if (RAMSize == 0xC00u)
        #define DMA_CH12_Alt_Addr 0x18000BC0u
      #elif (RAMSize == 0x1800u)
        #define DMA_CH12_Alt_Addr 0x180017C0u
      #elif (RAMSize == 0x2000u)
        #define DMA_CH12_Alt_Addr 0x18001FC0u
      #else
        #error RAM size not supported
      #endif
      __attribute__((section(AT_ADDRESS_ZI(DMA_CH12_Alt_Addr)))) TDMA_Entry volatile DMA_Entry_Ch12_Alt ;
    #elif defined(__IAR_SYSTEMS_ICC__)
      #if (RAMSize == 0xC00u)
        #pragma location=0x18000BC0u
      #elif (RAMSize == 0x1800u)
        #pragma location=0x180017C0u
      #elif (RAMSize == 0x2000u)
        #pragma location=0x18001FC0u
      #else
        #error RAM size not supported
      #endif /* RAMSize */
      TDMA_Entry volatile DMA_Entry_Ch12_Alt;
    #endif
    #if (DMA_CH12_TASK_NoOfTasks == 0)
      #error "NoOfTasks = 0 not meaningful"
    #elif (DMA_CH12_TASK_NoOfTasks == 1)
      extern TDMA_Entry DMA_CH12_TASK_SRC;
    #else
      extern TDMA_Entry DMA_CH12_TASK_SRC[];
    #endif /*(DMA_CH12_TASK_NoOfTasks == 0)*/
  #endif /* (DMA_CH12_TRANS_MODE == 0) */
#endif
/**********************************************************************************************************************
** DMA Channel 13 struct definition                                                                                   **
**********************************************************************************************************************/
#if defined UC_FEATURE_DMA_CH13
  /* violation: the shift value is at least the precision of the essential type of the left hand side [MISRA 2012 Rule 12.2, required] */
  #if ((DMA_EN & (1u << DMA_CH13)) != 0u)
    #if defined(__ARMCC_VERSION) && (__ARMCC_VERSION < 6000000)
      /* ARMCC V5 */
      TDMA_Entry volatile DMA_Entry_Ch13_Pri  __attribute__((at(DMA_BASE_ADDR + DMA_CH13 *sizeof(TDMA_Entry)), used));
    #elif defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6000000)
      /* Arm Compiler 6 (armclang) */
      #if (RAMSize == 0xC00u)
        #define DMA_CH13_Pri_Addr 0x18000AD0u
      #elif (RAMSize == 0x1800u)
        #define DMA_CH13_Pri_Addr 0x180016D0u
      #elif (RAMSize == 0x2000u)
        #define DMA_CH13_Pri_Addr 0x18001ED0u
      #else
        #error RAM size not supported
      #endif
      __attribute__((section(AT_ADDRESS_ZI(DMA_CH13_Pri_Addr)))) TDMA_Entry volatile DMA_Entry_Ch13_Pri ;
    #elif defined(__IAR_SYSTEMS_ICC__)
      #if (RAMSize == 0xC00u)
        #pragma location=0x18000AD0u
      #elif (RAMSize == 0x1800u)
        #pragma location=0x180016D0u
      #elif (RAMSize == 0x2000u)
        #pragma location=0x18001ED0u
      #else
        #error RAM size not supported
      #endif /* RAMSize */
      TDMA_Entry volatile DMA_Entry_Ch13_Pri;
      #endif
      #if (DMA_CH13_TRANS_MODE == 0)
      #if (DMA_CH13_SRC_EXT == 1)
        extern void DMA_CH13_SRC;
      #endif
      #if (DMA_CH13_DST_EXT == 1)
        extern void DMA_CH13_DST;
      #endif
    #else
      #if defined(__ARMCC_VERSION) && (__ARMCC_VERSION < 6000000)
        /* ARMCC V5 */
        TDMA_Entry volatile DMA_Entry_Ch13_Alt  __attribute__((at((DMA_BASE_ADDR + 0x100) + DMA_CH13 *sizeof(TDMA_Entry)), used));
      #elif defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6000000)
        /* Arm Compiler 6 (armclang) */
        #if (RAMSize == 0xC00u)
          #define DMA_CH13_Alt_Addr 0x18000BD0u
        #elif (RAMSize == 0x1800u)
          #define DMA_CH13_Alt_Addr 0x180017D0u
        #elif (RAMSize == 0x2000u)
          #define DMA_CH13_Alt_Addr 0x18001FD0u
        #else
          #error RAM size not supported
        #endif
        __attribute__((section(AT_ADDRESS_ZI(DMA_CH13_Alt_Addr)))) TDMA_Entry volatile DMA_Entry_Ch13_Alt ;
      #elif defined(__IAR_SYSTEMS_ICC__)
        #if (RAMSize == 0xC00u)
          #pragma location=0x18000BD0u
        #elif (RAMSize == 0x1800u)
          #pragma location=0x180017D0u
        #elif (RAMSize == 0x2000u)
          #pragma location=0x18001FD0u
        #else
          #error RAM size not supported
        #endif /* RAMSize */
        TDMA_Entry volatile DMA_Entry_Ch13_Alt;
      #endif
      #if (DMA_CH13_TASK_NoOfTasks == 0)
        #error "NoOfTasks = 0 not meaningful"
      #elif (DMA_CH13_TASK_NoOfTasks == 1)
        extern TDMA_Entry DMA_CH13_TASK_SRC;
      #else
        extern TDMA_Entry DMA_CH13_TASK_SRC[];
      #endif /*(DMA_CH13_TASK_NoOfTasks == 0)*/
    #endif /* (DMA_CH13_TRANS_MODE == 0) */
  #endif /* ((DMA_EN & (1u << DMA_CH13)) != 0u) */
#endif /* UC_FEATURE_DMA_CH13 */

/*******************************************************************************
**                         Global Function Definitions                        **
*******************************************************************************/
void DMA_Setup_Channel(uint32 DMA_ChIdx, uint32 addr_src, uint32 addr_dst,
                       uint32 trans_cnt, TDMA_Transfer_Size datawidth, TDMA_Increment_Mode increment)
{
  TDMA_Entry *entry;
  uint32 ui32;
  ui32 = DMA_ChIdx * sizeof(TDMA_Entry);
  ui32 += DMA_BASE_ADDR;
  /* violation: cast from unsigned int to pointer [MISRA Rule 45]*/
  entry = (TDMA_Entry *)ui32;
  entry->Src_End_Ptr = addr_src + (trans_cnt * ((uint32)1u << ((uint8)datawidth - 1u)));
  entry->Dst_End_Ptr = addr_dst + (trans_cnt * ((uint32)1u << ((uint8)datawidth - 1u)));
  /* Basic Transfer */
  entry->Control.bit.Cycle_Ctrl = (uint8)DMA_Cycle_Type_Basic;
  /* */
  entry->Control.bit.Next_UseBurst = 0;
  /* number of transfers minus 1 */
  entry->Control.bit.N_Minus_1 = (uint16)(trans_cnt - 1u);
  /* Arbitrates after each DMA Trans */
  entry->Control.bit.R_Power = 0;
  /* HPROT control */
  entry->Control.bit.Src_Prot_Ctrl = 7u;
  /* HPROT control */
  entry->Control.bit.Dst_Prot_Ctrl = 7u;
  /* datawidth of the data to be transferred */
  entry->Control.bit.Src_Size = (uint8)datawidth;
  /* datawidth of the data to be transferred */
  entry->Control.bit.Dst_Size = (uint8)datawidth;

  switch (increment)
  {
    case DMA_Src_Inc:
    {
      //Dst_Inc error defination
//      entry->Control.bit.Src_Inc = (uint8)datawidth;
//      entry->Control.bit.Dst_Inc = (uint8)DMA_No_Inc;
        DMA_Entry_Ch12_Pri.Control.bit.Dst_Inc = ((DMA_CH12_INC & 2u) == 2u) ? (uint8)DMA_CH12_SIZE : (uint8)3;
        DMA_Entry_Ch12_Pri.Control.bit.Src_Inc = ((DMA_CH12_INC & 1u) == 1u) ? (uint8)DMA_CH12_SIZE : (uint8)3;
    }
    break;

    case DMA_Dst_Inc:
    {
      entry->Control.bit.Src_Inc = (uint8)DMA_No_Inc;
      entry->Control.bit.Dst_Inc = (uint8)datawidth;
    }
    break;

    case DMA_Src_Dst_Inc:
    {
      entry->Control.bit.Src_Inc = (uint8)datawidth;
      entry->Control.bit.Dst_Inc = (uint8)datawidth;
    }
    break;

    case DMA_No_Inc:
    default:
    {
      entry->Control.bit.Src_Inc = (uint8)DMA_No_Inc;
      entry->Control.bit.Dst_Inc = (uint8)DMA_No_Inc;
    }
    break;
  }

  /* set DMA structure base pointer */
  DMA->CTRL_BASE_PTR.reg = DMA_BASE_ADDR;
  /* enable the DMA channel */
  DMA->CHNL_ENABLE_SET.reg |= ((uint32)1u << DMA_ChIdx);
}

TDMA_Entry *DMA_Task_SctGth_Set(TDMA_Entry *entry, uint8 DMA_Ch, TDMA_Entry *Task_List, uint32 NoOfTask)
{
  /* Scatter-Gather Transfer */
  entry->Control.bit.Cycle_Ctrl = (uint8)DMA_Cycle_Type_MemSctGthPrim;
  /* */
  entry->Control.bit.Next_UseBurst = 0;
  /* number of transfers  */
  entry->Control.bit.N_Minus_1 = (uint16)(NoOfTask * 4u) - 1u;
  /* Arbitrates after each DMA Trans */
  entry->Control.bit.R_Power = 2u;
  /* HPROT control */
  entry->Control.bit.Src_Prot_Ctrl = 7u;
  /* HPROT control */
  entry->Control.bit.Dst_Prot_Ctrl = 7u;
  /* datawidth of the data to be transferred */
  entry->Control.bit.Src_Size = (uint8)DMA_32Bit_Transfer;
  /* datawidth of the data to be transferred */
  entry->Control.bit.Dst_Size = (uint8)DMA_32Bit_Transfer;
  /* source increment */
  entry->Control.bit.Src_Inc = (uint8)2u;
  /* destination increment */
  entry->Control.bit.Dst_Inc = (uint8)2u;
  /* source end pointer, points to last task in task list */
  entry->Src_End_Ptr = (uint32)Task_List + (((NoOfTask * 4u) - 1u) * ((uint32)1u << (uint8)DMA_32Bit_Transfer));
  /* destination pointer, points to channel index in alternate stucture */
  entry->Dst_End_Ptr = (DMA->ALT_CTRL_BASE_PTR.reg + (DMA_Ch * sizeof(TDMA_Entry))) + 12u;
  return (entry);
}

void DMA_Channel_MemSctGth_Set(uint32 DMA_ChIdx, TDMA_Entry *Task_List, uint32 NoOfTasks)
{
  uint32 ui32;
  uint32 BASE_ADDR;
  TDMA_Entry *entry;
  /* get DMA structure base pointer */
  BASE_ADDR = DMA->CTRL_BASE_PTR.reg;
  ui32 = DMA_ChIdx * sizeof(TDMA_Entry);
  ui32 += BASE_ADDR;
  /* violation: cast from unsigned int to pointer [MISRA Rule 45]*/
  entry = (TDMA_Entry *)ui32;
  /* Scatter-Gather Transfer */
  entry->Control.bit.Cycle_Ctrl = (uint8)DMA_Cycle_Type_MemSctGthPrim;
  /* */
  entry->Control.bit.Next_UseBurst = 0;
  /* number of transfers  */
  entry->Control.bit.N_Minus_1 = (uint16)((NoOfTasks * 4u) - 1u);
  /* Arbitrates after one Task trans (4 DMA trans)*/
  entry->Control.bit.R_Power = 2u;
  /* HPROT control */
  entry->Control.bit.Src_Prot_Ctrl = 7u;
  /* HPROT control */
  entry->Control.bit.Dst_Prot_Ctrl = 7u;
  /* datawidth of the data to be transferred */
  entry->Control.bit.Src_Size = (uint8)DMA_32Bit_Transfer;
  /* datawidth of the data to be transferred */
  entry->Control.bit.Dst_Size = (uint8)DMA_32Bit_Transfer;
  entry->Control.bit.Src_Inc = (uint8)DMA_32Bit_Transfer;
  entry->Control.bit.Dst_Inc = (uint8)DMA_32Bit_Transfer;
  /* set up source pointer */
  /* violation: cast from pointer to unsigned int [MISRA Rule 45] */
  entry->Src_End_Ptr = (uint32)Task_List + (((NoOfTasks * 4u) - 1u) * ((uint32)1u << (uint8)DMA_32Bit_Transfer));
  /* set up destination pointer */
  entry->Dst_End_Ptr = (DMA->ALT_CTRL_BASE_PTR.reg + (DMA_ChIdx * sizeof(TDMA_Entry))) + 12u;
}

void DMA_Channel_PerSctGth_Set(uint32 DMA_ChIdx, TDMA_Entry *Task_List, uint32 NoOfTasks)
{
  uint32 ui32;
  uint32 BASE_ADDR;
  TDMA_Entry *entry;
  /* get DMA structure base pointer */
  BASE_ADDR = DMA->CTRL_BASE_PTR.reg;
  ui32 = DMA_ChIdx * sizeof(TDMA_Entry);
  ui32 += BASE_ADDR;
  /* violation: cast from unsigned int to pointer [MISRA Rule 45]*/
  entry = (TDMA_Entry *)ui32;
  /* Scatter-Gather Transfer */
  entry->Control.bit.Cycle_Ctrl = (uint8)DMA_Cycle_Type_PerSctGthPrim;
  /* */
  entry->Control.bit.Next_UseBurst = 0;
  /* number of transfers  */
  entry->Control.bit.N_Minus_1 = (uint16)((NoOfTasks * 4u) - 1u);
  /* Arbitrates after one Task trans (4 DMA trans)*/
  entry->Control.bit.R_Power = 2u;
  /* HPROT control */
  entry->Control.bit.Src_Prot_Ctrl = 7u;
  /* HPROT control */
  entry->Control.bit.Dst_Prot_Ctrl = 7u;
  /* datawidth of the data to be transferred */
  entry->Control.bit.Src_Size = (uint8)DMA_32Bit_Transfer;
  /* datawidth of the data to be transferred */
  entry->Control.bit.Dst_Size = (uint8)DMA_32Bit_Transfer;
  entry->Control.bit.Src_Inc = (uint8)DMA_32Bit_Transfer;
  entry->Control.bit.Dst_Inc = (uint8)DMA_32Bit_Transfer;
  /* violation: cast from pointer to unsigned int [MISRA Rule 45] */
  entry->Src_End_Ptr = (uint32)Task_List + (((NoOfTasks * 4u) - 1u) * ((uint32)1u << (uint8)DMA_32Bit_Transfer));
  entry->Dst_End_Ptr = (DMA->ALT_CTRL_BASE_PTR.reg + (DMA_ChIdx * sizeof(TDMA_Entry))) + 12u;
}

TDMA_Entry *DMA_Task_Set(TDMA_Entry *entry, TDMA_Cycle_Types cycle_type, uint8 arb_rate, uint32 addr_src, uint32 addr_dst,
                         uint32 trans_cnt, TDMA_Transfer_Size datawidth, TDMA_Increment_Mode increment)
{
  /* Scatter-Gather Transfer */
  entry->Control.bit.Cycle_Ctrl = (uint8)cycle_type;
  /* */
  entry->Control.bit.Next_UseBurst = 0;
  /* number of transfers  */
  entry->Control.bit.N_Minus_1 = (uint16)(trans_cnt - 1u);
  /* Arbitrates after each DMA Trans */
  entry->Control.bit.R_Power = arb_rate;
  /* HPROT control */
  entry->Control.bit.Src_Prot_Ctrl = 7u;
  /* HPROT control */
  entry->Control.bit.Dst_Prot_Ctrl = 7u;
  /* datawidth of the data to be transferred */
  entry->Control.bit.Src_Size = (uint8)datawidth;
  /* datawidth of the data to be transferred */
  entry->Control.bit.Dst_Size = (uint8)datawidth;

  switch (increment)
  {
    case DMA_Src_Inc:
    {
      entry->Control.bit.Src_Inc = (uint8)datawidth;
      entry->Control.bit.Dst_Inc = (uint8)DMA_No_Inc;
      entry->Src_End_Ptr = addr_src + ((trans_cnt - 1u) * ((uint32)1u << (uint8)datawidth));
      entry->Dst_End_Ptr = addr_dst;
    }
    break;

    case DMA_Dst_Inc:
    {
      entry->Control.bit.Src_Inc = (uint8)DMA_No_Inc;
      entry->Control.bit.Dst_Inc = (uint8)datawidth;
      entry->Src_End_Ptr = addr_src;
      entry->Dst_End_Ptr = addr_dst + ((trans_cnt - 1u) * ((uint32)1u << (uint8)datawidth));
    }
    break;

    case DMA_Src_Dst_Inc:
    {
      entry->Control.bit.Src_Inc = (uint8)datawidth;
      entry->Control.bit.Dst_Inc = (uint8)datawidth;
      entry->Src_End_Ptr = addr_src + ((trans_cnt - 1u) * ((uint32)1u << (uint8)datawidth));
      entry->Dst_End_Ptr = addr_dst + ((trans_cnt - 1u) * ((uint32)1u << (uint8)datawidth));
    }
    break;

    case DMA_No_Inc:
    default:
    {
      entry->Control.bit.Src_Inc = (uint8)DMA_No_Inc;
      entry->Control.bit.Dst_Inc = (uint8)DMA_No_Inc;
      entry->Src_End_Ptr = addr_src;
      entry->Dst_End_Ptr = addr_dst;
    }
    break;
  }

  return (entry);
}

void DMA_Reset_Channel(uint32 DMA_ChIdx, uint32 trans_cnt)
{
  uint32 ui32;
  uint32 BASE_ADDR;
  TDMA_Entry *entry;
  /* get DMA structure base pointer */
  BASE_ADDR = DMA->CTRL_BASE_PTR.reg;
  ui32 = DMA_ChIdx * sizeof(TDMA_Entry);
  ui32 += BASE_ADDR;
  /* violation: cast from unsigned int to pointer [MISRA Rule 45]*/
  entry = (TDMA_Entry *)ui32;
  /* number of transfers minus 1 */
  entry->Control.bit.N_Minus_1 = (uint16)(trans_cnt - 1u);
  /* Basic Transfer */
  entry->Control.bit.Cycle_Ctrl = (uint8)DMA_Cycle_Type_Basic;
  /* enable the DMA channel */
  DMA->CHNL_ENABLE_SET.reg |= ((uint32)1u << DMA_ChIdx);
}

void DMA_Init(void)
{
  /* set DMA structure base pointer */
  DMA->CTRL_BASE_PTR.reg = DMA_BASE_ADDR;
#if ((DMA_EN & 1u) != 0u)
  /* HPROT control */
  DMA_Entry_Ch0_Pri.Control.bit.Src_Prot_Ctrl = 7u;
  /* HPROT control */
  DMA_Entry_Ch0_Pri.Control.bit.Dst_Prot_Ctrl = 7u;
#if (DMA_CH0_TRANS_MODE == 0)
  /* Basic Transfer */
  DMA_Entry_Ch0_Pri.Control.bit.Cycle_Ctrl = (uint8)DMA_Cycle_Type_Basic;
  /* */
  DMA_Entry_Ch0_Pri.Control.bit.Next_UseBurst = 0;
  /* load source pointer */
  /* violation: cast from pointer to unsigned int [MISRA Rule 45] */
  DMA_Entry_Ch0_Pri.Src_End_Ptr = (uint32)&DMA_CH0_SRC + (uint32)DMA_CH0_SRC_PTR_OFFS;
  /* load destination pointer */
  /* violation: cast from pointer to unsigned int [MISRA Rule 45] */
  DMA_Entry_Ch0_Pri.Dst_End_Ptr = (uint32)&DMA_CH0_DST + (uint32)DMA_CH0_DST_PTR_OFFS;
  /* violation: Constant value Boolean [MISRA Rule 52], [MISRA Rule 85] */
  DMA_Entry_Ch0_Pri.Control.bit.Dst_Inc = ((DMA_CH0_INC & 2u) == 2u) ? (uint8)DMA_CH0_SIZE : (uint8)3;
  DMA_Entry_Ch0_Pri.Control.bit.Src_Inc = ((DMA_CH0_INC & 1u) == 1u) ? (uint8)DMA_CH0_SIZE : (uint8)3;
  DMA_Entry_Ch0_Pri.Control.bit.Dst_Size = DMA_CH0_SIZE;
  DMA_Entry_Ch0_Pri.Control.bit.Src_Size = DMA_CH0_SIZE;
  /* number of transfers minus 1 */
  DMA_Entry_Ch0_Pri.Control.bit.N_Minus_1 = (uint16)(DMA_CH0_NoOfTrans - 1);
#else
  /* initialize alternate table entry */
  DMA_Entry_Ch0_Alt.Control.reg = 0u;
  DMA_Entry_Ch0_Alt.Dst_End_Ptr = 0u;
  DMA_Entry_Ch0_Alt.Src_End_Ptr = 0u;
  /* Scatter-Gather Transfer */
  DMA_Entry_Ch0_Pri.Control.bit.Cycle_Ctrl = (uint8)DMA_Cycle_Type_MemSctGthPrim;
  /* must be '0' for Scatter-Gather */
  DMA_Entry_Ch0_Pri.Control.bit.Next_UseBurst = 0;
  /* number of transfers  */
  DMA_Entry_Ch0_Pri.Control.bit.N_Minus_1 = (uint16)(((uint16)DMA_CH0_TASK_NoOfTasks * 4u) - 1u);
  /* Arbitrates after one Task trans (4 DMA trans)*/
  DMA_Entry_Ch0_Pri.Control.bit.R_Power = 2;
  /* datawidth of the data to be transferred */
  DMA_Entry_Ch0_Pri.Control.bit.Src_Size = (uint8)DMA_32Bit_Transfer;
  /* datawidth of the data to be transferred */
  DMA_Entry_Ch0_Pri.Control.bit.Dst_Size = (uint8)DMA_32Bit_Transfer;
  /* source increment */
  DMA_Entry_Ch0_Pri.Control.bit.Src_Inc = (uint8)DMA_Inc_32bit;
  /* destination increment */
  DMA_Entry_Ch0_Pri.Control.bit.Dst_Inc = (uint8)DMA_Inc_32bit;
  /* source end pointer, points to last task in task list */
  /* violation: cast from pointer to unsigned int [MISRA Rule 45] */
  DMA_Entry_Ch0_Pri.Src_End_Ptr = (uint32)&DMA_CH0_TASK_SRC[0] + (uint32)((uint16)(((uint16)DMA_CH0_TASK_NoOfTasks * 4u) - 1u) * ((uint8)1u << (uint8)DMA_32Bit_Transfer));
  /* destination pointer, points to channel index in alternate stucture */
  DMA_Entry_Ch0_Pri.Dst_End_Ptr = DMA->ALT_CTRL_BASE_PTR.reg + 12u;
#endif /* (DMA_CH0_TRANS_MODE == 0u) */
#endif
#if ((DMA_EN & (1u << DMA_CH1)) != 0u)
  /* HPROT control */
  DMA_Entry_Ch1_Pri.Control.bit.Src_Prot_Ctrl = 7u;
  /* HPROT control */
  DMA_Entry_Ch1_Pri.Control.bit.Dst_Prot_Ctrl = 7u;
#if (DMA_CH1_TRANS_MODE == 0)
  /* Basic Transfer */
  DMA_Entry_Ch1_Pri.Control.bit.Cycle_Ctrl = (uint8)DMA_Cycle_Type_Basic;
  /* */
  DMA_Entry_Ch1_Pri.Control.bit.Next_UseBurst = 0;
  /* load source pointer */
  /* violation: cast from pointer to unsigned int [MISRA Rule 45] */
  DMA_Entry_Ch1_Pri.Src_End_Ptr = (uint32)&DMA_CH1_SRC + (uint32)DMA_CH1_SRC_PTR_OFFS;
  /* load destination pointer */
  /* violation: cast from pointer to unsigned int [MISRA Rule 45] */
  DMA_Entry_Ch1_Pri.Dst_End_Ptr = (uint32)&DMA_CH1_DST + (uint32)DMA_CH1_DST_PTR_OFFS;
  /* violation: Constant value Boolean [MISRA Rule 52], [MISRA Rule 85] */
  DMA_Entry_Ch1_Pri.Control.bit.Dst_Inc = ((DMA_CH1_INC & 2u) == 2u) ? (uint8)DMA_CH1_SIZE : (uint8)3;
  DMA_Entry_Ch1_Pri.Control.bit.Src_Inc = ((DMA_CH1_INC & 1u) == 1u) ? (uint8)DMA_CH1_SIZE : (uint8)3;
  DMA_Entry_Ch1_Pri.Control.bit.Dst_Size = DMA_CH1_SIZE;
  DMA_Entry_Ch1_Pri.Control.bit.Src_Size = DMA_CH1_SIZE;
  /* number of transfers minus 1 */
  DMA_Entry_Ch1_Pri.Control.bit.N_Minus_1 = (uint16)(DMA_CH1_NoOfTrans - 1);
#else
  /* initialize alternate table entry */
  DMA_Entry_Ch1_Alt.Control.reg = 0u;
  DMA_Entry_Ch1_Alt.Dst_End_Ptr = 0u;
  DMA_Entry_Ch1_Alt.Src_End_Ptr = 0u;
  /* Scatter-Gather Transfer */
  DMA_Entry_Ch1_Pri.Control.bit.Cycle_Ctrl = (uint8)DMA_Cycle_Type_MemSctGthPrim;
  /* must be '0' for Scatter-Gather */
  DMA_Entry_Ch1_Pri.Control.bit.Next_UseBurst = 0;
  /* number of transfers  */
  DMA_Entry_Ch1_Pri.Control.bit.N_Minus_1 = (uint16)(((uint16)DMA_CH1_TASK_NoOfTasks * 4u) - 1u);
  /* Arbitrates after one Task trans (4 DMA trans)*/
  DMA_Entry_Ch1_Pri.Control.bit.R_Power = 2;
  /* datawidth of the data to be transferred */
  DMA_Entry_Ch1_Pri.Control.bit.Src_Size = (uint8)DMA_32Bit_Transfer;
  /* datawidth of the data to be transferred */
  DMA_Entry_Ch1_Pri.Control.bit.Dst_Size = (uint8)DMA_32Bit_Transfer;
  /* source increment */
  DMA_Entry_Ch1_Pri.Control.bit.Src_Inc = (uint8)DMA_Inc_32bit;
  /* destination increment */
  DMA_Entry_Ch1_Pri.Control.bit.Dst_Inc = (uint8)DMA_Inc_32bit;
  /* source end pointer, points to last task in task list */
  /* violation: cast from pointer to unsigned int [MISRA Rule 45] */
  DMA_Entry_Ch1_Pri.Src_End_Ptr = (uint32)&DMA_CH1_TASK_SRC[0] + (uint32)((uint16)(((uint16)DMA_CH1_TASK_NoOfTasks * 4u) - 1u) * ((uint8)1u << (uint8)DMA_32Bit_Transfer));
  /* destination pointer, points to channel index in alternate stucture */
  DMA_Entry_Ch1_Pri.Dst_End_Ptr = (DMA->ALT_CTRL_BASE_PTR.reg + (DMA_CH1 * sizeof(TDMA_Entry))) + 12u;
#endif /* (DMA_CH1_TRANS_MODE == 0u) */
#endif
#if ((DMA_EN & (1u << DMA_CH2)) != 0u)
  /* HPROT control */
  DMA_Entry_Ch2_Pri.Control.bit.Src_Prot_Ctrl = 7u;
  /* HPROT control */
  DMA_Entry_Ch2_Pri.Control.bit.Dst_Prot_Ctrl = 7u;
#if (DMA_CH2_TRANS_MODE == 0)
  /* Basic Transfer */
  DMA_Entry_Ch2_Pri.Control.bit.Cycle_Ctrl = (uint8)DMA_Cycle_Type_Basic;
  /* */
  DMA_Entry_Ch2_Pri.Control.bit.Next_UseBurst = 0;
  /* load source pointer */
  /* violation: cast from pointer to unsigned int [MISRA Rule 45] */
  DMA_Entry_Ch2_Pri.Src_End_Ptr = (uint32)&DMA_CH2_SRC + (uint32)DMA_CH2_SRC_PTR_OFFS;
  /* load destination pointer */
  /* violation: cast from pointer to unsigned int [MISRA Rule 45] */
  DMA_Entry_Ch2_Pri.Dst_End_Ptr = (uint32)&DMA_CH2_DST + (uint32)DMA_CH2_DST_PTR_OFFS;
  /* violation: Constant value Boolean [MISRA Rule 52], [MISRA Rule 85] */
  DMA_Entry_Ch2_Pri.Control.bit.Dst_Inc = ((DMA_CH2_INC & 2u) == 2u) ? (uint8)DMA_CH2_SIZE : (uint8)3;
  DMA_Entry_Ch2_Pri.Control.bit.Src_Inc = ((DMA_CH2_INC & 1u) == 1u) ? (uint8)DMA_CH2_SIZE : (uint8)3;
  DMA_Entry_Ch2_Pri.Control.bit.Dst_Size = DMA_CH2_SIZE;
  DMA_Entry_Ch2_Pri.Control.bit.Src_Size = DMA_CH2_SIZE;
  /* number of transfers minus 1 */
  DMA_Entry_Ch2_Pri.Control.bit.N_Minus_1 = (uint16)(DMA_CH2_NoOfTrans - 1);
#else
  /* initialize alternate table entry */
  DMA_Entry_Ch2_Alt.Control.reg = 0u;
  DMA_Entry_Ch2_Alt.Dst_End_Ptr = 0u;
  DMA_Entry_Ch2_Alt.Src_End_Ptr = 0u;
  /* Scatter-Gather Transfer */
  DMA_Entry_Ch2_Pri.Control.bit.Cycle_Ctrl = (uint8)DMA_Cycle_Type_MemSctGthPrim;
  /* must be '0' for Scatter-Gather */
  DMA_Entry_Ch2_Pri.Control.bit.Next_UseBurst = 0;
  /* number of transfers  */
  DMA_Entry_Ch2_Pri.Control.bit.N_Minus_1 = (uint16)(((uint16)DMA_CH2_TASK_NoOfTasks * 4u) - 1u);
  /* Arbitrates after one Task trans (4 DMA trans)*/
  DMA_Entry_Ch2_Pri.Control.bit.R_Power = 2;
  /* datawidth of the data to be transferred */
  DMA_Entry_Ch2_Pri.Control.bit.Src_Size = (uint8)DMA_32Bit_Transfer;
  /* datawidth of the data to be transferred */
  DMA_Entry_Ch2_Pri.Control.bit.Dst_Size = (uint8)DMA_32Bit_Transfer;
  /* source increment */
  DMA_Entry_Ch2_Pri.Control.bit.Src_Inc = (uint8)DMA_Inc_32bit;
  /* destination increment */
  DMA_Entry_Ch2_Pri.Control.bit.Dst_Inc = (uint8)DMA_Inc_32bit;
  /* source end pointer, points to last task in task list */
  /* violation: cast from pointer to unsigned int [MISRA Rule 45] */
  DMA_Entry_Ch2_Pri.Src_End_Ptr = (uint32)&DMA_CH2_TASK_SRC[0] + (uint32)((uint16)(((uint16)DMA_CH2_TASK_NoOfTasks * 4u) - 1u) * ((uint8)1u << (uint8)DMA_32Bit_Transfer));
  /* destination pointer, points to channel index in alternate stucture */
  DMA_Entry_Ch2_Pri.Dst_End_Ptr = (DMA->ALT_CTRL_BASE_PTR.reg + (DMA_CH2 * sizeof(TDMA_Entry))) + 12u;
#endif /* (DMA_CH2_TRANS_MODE == 0u) */
#endif
#if ((DMA_EN & (1u << DMA_CH3)) != 0u)
  /* HPROT control */
  DMA_Entry_Ch3_Pri.Control.bit.Src_Prot_Ctrl = 7u;
  /* HPROT control */
  DMA_Entry_Ch3_Pri.Control.bit.Dst_Prot_Ctrl = 7u;
#if (DMA_CH3_TRANS_MODE == 0)
  /* Basic Transfer */
  DMA_Entry_Ch3_Pri.Control.bit.Cycle_Ctrl = (uint8)DMA_Cycle_Type_Basic;
  /* */
  DMA_Entry_Ch3_Pri.Control.bit.Next_UseBurst = 0;
  /* load source pointer */
  /* violation: cast from pointer to unsigned int [MISRA Rule 45] */
  DMA_Entry_Ch3_Pri.Src_End_Ptr = (uint32)&DMA_CH3_SRC + (uint32)DMA_CH3_SRC_PTR_OFFS;
  /* load destination pointer */
  /* violation: cast from pointer to unsigned int [MISRA Rule 45] */
  DMA_Entry_Ch3_Pri.Dst_End_Ptr = (uint32)&DMA_CH3_DST + (uint32)DMA_CH3_DST_PTR_OFFS;
  /* violation: Constant value Boolean [MISRA Rule 52], [MISRA Rule 85] */
  DMA_Entry_Ch3_Pri.Control.bit.Dst_Inc = ((DMA_CH3_INC & 2u) == 2u) ? (uint8)DMA_CH3_SIZE : (uint8)3;
  DMA_Entry_Ch3_Pri.Control.bit.Src_Inc = ((DMA_CH3_INC & 1u) == 1u) ? (uint8)DMA_CH3_SIZE : (uint8)3;
  DMA_Entry_Ch3_Pri.Control.bit.Dst_Size = DMA_CH3_SIZE;
  DMA_Entry_Ch3_Pri.Control.bit.Src_Size = DMA_CH3_SIZE;
  /* number of transfers minus 1 */
  DMA_Entry_Ch3_Pri.Control.bit.N_Minus_1 = (uint16)(DMA_CH3_NoOfTrans - 1);
#else
  /* initialize alternate table entry */
  DMA_Entry_Ch3_Alt.Control.reg = 0u;
  DMA_Entry_Ch3_Alt.Dst_End_Ptr = 0u;
  DMA_Entry_Ch3_Alt.Src_End_Ptr = 0u;
  /* Scatter-Gather Transfer */
  DMA_Entry_Ch3_Pri.Control.bit.Cycle_Ctrl = (uint8)DMA_Cycle_Type_MemSctGthPrim;
  /* must be '0' for Scatter-Gather */
  DMA_Entry_Ch3_Pri.Control.bit.Next_UseBurst = 0;
  /* number of transfers  */
  DMA_Entry_Ch3_Pri.Control.bit.N_Minus_1 = (uint16)(((uint16)DMA_CH3_TASK_NoOfTasks * 4u) - 1u);
  /* Arbitrates after one Task trans (4 DMA trans)*/
  DMA_Entry_Ch3_Pri.Control.bit.R_Power = 2;
  /* datawidth of the data to be transferred */
  DMA_Entry_Ch3_Pri.Control.bit.Src_Size = (uint8)DMA_32Bit_Transfer;
  /* datawidth of the data to be transferred */
  DMA_Entry_Ch3_Pri.Control.bit.Dst_Size = (uint8)DMA_32Bit_Transfer;
  /* source increment */
  DMA_Entry_Ch3_Pri.Control.bit.Src_Inc = (uint8)DMA_Inc_32bit;
  /* destination increment */
  DMA_Entry_Ch3_Pri.Control.bit.Dst_Inc = (uint8)DMA_Inc_32bit;
  /* source end pointer, points to last task in task list */
  /* violation: cast from pointer to unsigned int [MISRA Rule 45] */
  DMA_Entry_Ch3_Pri.Src_End_Ptr = (uint32)&DMA_CH3_TASK_SRC[0] + (uint32)((uint16)(((uint16)DMA_CH3_TASK_NoOfTasks * 4u) - 1u) * ((uint8)1u << (uint8)DMA_32Bit_Transfer));
  /* destination pointer, points to channel index in alternate stucture */
  DMA_Entry_Ch3_Pri.Dst_End_Ptr = (DMA->ALT_CTRL_BASE_PTR.reg + (DMA_CH3 * sizeof(TDMA_Entry))) + 12u;
#endif /* (DMA_CH3_TRANS_MODE == 0u) */
#endif
#if ((DMA_EN & (1u << DMA_CH4)) != 0u)
  /* HPROT control */
  DMA_Entry_Ch4_Pri.Control.bit.Src_Prot_Ctrl = 7u;
  /* HPROT control */
  DMA_Entry_Ch4_Pri.Control.bit.Dst_Prot_Ctrl = 7u;
#if (DMA_CH4_TRANS_MODE == 0)
  /* Basic Transfer */
  DMA_Entry_Ch4_Pri.Control.bit.Cycle_Ctrl = (uint8)DMA_Cycle_Type_Basic;
  /* */
  DMA_Entry_Ch4_Pri.Control.bit.Next_UseBurst = 0;
  /* load source pointer */
  /* violation: cast from pointer to unsigned int [MISRA Rule 45] */
  DMA_Entry_Ch4_Pri.Src_End_Ptr = (uint32)&DMA_CH4_SRC + (uint32)DMA_CH4_SRC_PTR_OFFS;
  /* load destination pointer */
  /* violation: cast from pointer to unsigned int [MISRA Rule 45] */
  DMA_Entry_Ch4_Pri.Dst_End_Ptr = (uint32)&DMA_CH4_DST + (uint32)DMA_CH4_DST_PTR_OFFS;
  /* violation: Constant value Boolean [MISRA Rule 52], [MISRA Rule 85] */
  DMA_Entry_Ch4_Pri.Control.bit.Dst_Inc = ((DMA_CH4_INC & 2u) == 2u) ? (uint8)DMA_CH4_SIZE : (uint8)3;
  DMA_Entry_Ch4_Pri.Control.bit.Src_Inc = ((DMA_CH4_INC & 1u) == 1u) ? (uint8)DMA_CH4_SIZE : (uint8)3;
  DMA_Entry_Ch4_Pri.Control.bit.Dst_Size = DMA_CH4_SIZE;
  DMA_Entry_Ch4_Pri.Control.bit.Src_Size = DMA_CH4_SIZE;
  /* number of transfers minus 1 */
  DMA_Entry_Ch4_Pri.Control.bit.N_Minus_1 = (uint16)(DMA_CH4_NoOfTrans - 1);
#else
  /* initialize alternate table entry */
  DMA_Entry_Ch4_Alt.Control.reg = 0u;
  DMA_Entry_Ch4_Alt.Dst_End_Ptr = 0u;
  DMA_Entry_Ch4_Alt.Src_End_Ptr = 0u;
  /* Scatter-Gather Transfer */
  DMA_Entry_Ch4_Pri.Control.bit.Cycle_Ctrl = (uint8)DMA_Cycle_Type_MemSctGthPrim;
  /* must be '0' for Scatter-Gather */
  DMA_Entry_Ch4_Pri.Control.bit.Next_UseBurst = 0;
  /* number of transfers  */
  DMA_Entry_Ch4_Pri.Control.bit.N_Minus_1 = (uint16)(((uint16)DMA_CH4_TASK_NoOfTasks * 4u) - 1u);
  /* Arbitrates after one Task trans (4 DMA trans)*/
  DMA_Entry_Ch4_Pri.Control.bit.R_Power = 2;
  /* datawidth of the data to be transferred */
  DMA_Entry_Ch4_Pri.Control.bit.Src_Size = (uint8)DMA_32Bit_Transfer;
  /* datawidth of the data to be transferred */
  DMA_Entry_Ch4_Pri.Control.bit.Dst_Size = (uint8)DMA_32Bit_Transfer;
  /* source increment */
  DMA_Entry_Ch4_Pri.Control.bit.Src_Inc = (uint8)DMA_Inc_32bit;
  /* destination increment */
  DMA_Entry_Ch4_Pri.Control.bit.Dst_Inc = (uint8)DMA_Inc_32bit;
  /* source end pointer, points to last task in task list */
  /* violation: cast from pointer to unsigned int [MISRA Rule 45] */
  DMA_Entry_Ch4_Pri.Src_End_Ptr = (uint32)&DMA_CH4_TASK_SRC[0] + (uint32)((uint16)(((uint16)DMA_CH4_TASK_NoOfTasks * 4u) - 1u) * ((uint8)1u << (uint8)DMA_32Bit_Transfer));
  /* destination pointer, points to channel index in alternate stucture */
  DMA_Entry_Ch4_Pri.Dst_End_Ptr = (DMA->ALT_CTRL_BASE_PTR.reg + (DMA_CH4 * sizeof(TDMA_Entry))) + 12u;
#endif /* (DMA_CH4_TRANS_MODE == 0u) */
#endif
#if ((DMA_EN & (1u << DMA_CH5)) != 0u)
  /* HPROT control */
  DMA_Entry_Ch5_Pri.Control.bit.Src_Prot_Ctrl = 7u;
  /* HPROT control */
  DMA_Entry_Ch5_Pri.Control.bit.Dst_Prot_Ctrl = 7u;
#if (DMA_CH5_TRANS_MODE == 0)
  /* Basic Transfer */
  DMA_Entry_Ch5_Pri.Control.bit.Cycle_Ctrl = (uint8)DMA_Cycle_Type_Basic;
  /* */
  DMA_Entry_Ch5_Pri.Control.bit.Next_UseBurst = 0;
  /* load source pointer */
  /* violation: cast from pointer to unsigned int [MISRA Rule 45] */
  DMA_Entry_Ch5_Pri.Src_End_Ptr = (uint32)&DMA_CH5_SRC + (uint32)DMA_CH5_SRC_PTR_OFFS;
  /* load destination pointer */
  /* violation: cast from pointer to unsigned int [MISRA Rule 45] */
  DMA_Entry_Ch5_Pri.Dst_End_Ptr = (uint32)&DMA_CH5_DST + (uint32)DMA_CH5_DST_PTR_OFFS;
  /* violation: Constant value Boolean [MISRA Rule 52], [MISRA Rule 85] */
  DMA_Entry_Ch5_Pri.Control.bit.Dst_Inc = ((DMA_CH5_INC & 2u) == 2u) ? (uint8)DMA_CH5_SIZE : (uint8)3;
  DMA_Entry_Ch5_Pri.Control.bit.Src_Inc = ((DMA_CH5_INC & 1u) == 1u) ? (uint8)DMA_CH5_SIZE : (uint8)3;
  DMA_Entry_Ch5_Pri.Control.bit.Dst_Size = DMA_CH5_SIZE;
  DMA_Entry_Ch5_Pri.Control.bit.Src_Size = DMA_CH5_SIZE;
  /* number of transfers minus 1 */
  DMA_Entry_Ch5_Pri.Control.bit.N_Minus_1 = (uint16)(DMA_CH5_NoOfTrans - 1);
#else
  /* initialize alternate table entry */
  DMA_Entry_Ch5_Alt.Control.reg = 0u;
  DMA_Entry_Ch5_Alt.Dst_End_Ptr = 0u;
  DMA_Entry_Ch5_Alt.Src_End_Ptr = 0u;
  /* Scatter-Gather Transfer */
  DMA_Entry_Ch5_Pri.Control.bit.Cycle_Ctrl = (uint8)DMA_Cycle_Type_MemSctGthPrim;
  /* must be '0' for Scatter-Gather */
  DMA_Entry_Ch5_Pri.Control.bit.Next_UseBurst = 0;
  /* number of transfers  */
  DMA_Entry_Ch5_Pri.Control.bit.N_Minus_1 = (uint16)(((uint16)DMA_CH5_TASK_NoOfTasks * 4u) - 1u);
  /* Arbitrates after one Task trans (4 DMA trans)*/
  DMA_Entry_Ch5_Pri.Control.bit.R_Power = 2;
  /* datawidth of the data to be transferred */
  DMA_Entry_Ch5_Pri.Control.bit.Src_Size = (uint8)DMA_32Bit_Transfer;
  /* datawidth of the data to be transferred */
  DMA_Entry_Ch5_Pri.Control.bit.Dst_Size = (uint8)DMA_32Bit_Transfer;
  /* source increment */
  DMA_Entry_Ch5_Pri.Control.bit.Src_Inc = (uint8)DMA_Inc_32bit;
  /* destination increment */
  DMA_Entry_Ch5_Pri.Control.bit.Dst_Inc = (uint8)DMA_Inc_32bit;
  /* source end pointer, points to last task in task list */
  /* violation: cast from pointer to unsigned int [MISRA Rule 45] */
  DMA_Entry_Ch5_Pri.Src_End_Ptr = (uint32)&DMA_CH5_TASK_SRC[0] + (uint32)((uint16)(((uint16)DMA_CH5_TASK_NoOfTasks * 4u) - 1u) * ((uint8)1u << (uint8)DMA_32Bit_Transfer));
  /* destination pointer, points to channel index in alternate stucture */
  DMA_Entry_Ch5_Pri.Dst_End_Ptr = (DMA->ALT_CTRL_BASE_PTR.reg + (DMA_CH5 * sizeof(TDMA_Entry))) + 12u;
#endif /* (DMA_CH5_TRANS_MODE == 0u) */
#endif
#if ((DMA_EN & (1u << DMA_CH6)) != 0u)
  /* HPROT control */
  DMA_Entry_Ch6_Pri.Control.bit.Src_Prot_Ctrl = 7u;
  /* HPROT control */
  DMA_Entry_Ch6_Pri.Control.bit.Dst_Prot_Ctrl = 7u;
#if (DMA_CH6_TRANS_MODE == 0)
  /* Basic Transfer */
  DMA_Entry_Ch6_Pri.Control.bit.Cycle_Ctrl = (uint8)DMA_Cycle_Type_Basic;
  /* */
  DMA_Entry_Ch6_Pri.Control.bit.Next_UseBurst = 0;
  /* load source pointer */
  /* violation: cast from pointer to unsigned int [MISRA Rule 45] */
  DMA_Entry_Ch6_Pri.Src_End_Ptr = (uint32)&DMA_CH6_SRC + (uint32)DMA_CH6_SRC_PTR_OFFS;
  /* load destination pointer */
  /* violation: cast from pointer to unsigned int [MISRA Rule 45] */
  DMA_Entry_Ch6_Pri.Dst_End_Ptr = (uint32)&DMA_CH6_DST + (uint32)DMA_CH6_DST_PTR_OFFS;
  /* violation: Constant value Boolean [MISRA Rule 52], [MISRA Rule 85] */
  DMA_Entry_Ch6_Pri.Control.bit.Dst_Inc = ((DMA_CH6_INC & 2u) == 2u) ? (uint8)DMA_CH6_SIZE : (uint8)3;
  DMA_Entry_Ch6_Pri.Control.bit.Src_Inc = ((DMA_CH6_INC & 1u) == 1u) ? (uint8)DMA_CH6_SIZE : (uint8)3;
  DMA_Entry_Ch6_Pri.Control.bit.Dst_Size = DMA_CH6_SIZE;
  DMA_Entry_Ch6_Pri.Control.bit.Src_Size = DMA_CH6_SIZE;
  /* number of transfers minus 1 */
  DMA_Entry_Ch6_Pri.Control.bit.N_Minus_1 = (uint16)(DMA_CH6_NoOfTrans - 1);
#else
  /* initialize alternate table entry */
  DMA_Entry_Ch6_Alt.Control.reg = 0u;
  DMA_Entry_Ch6_Alt.Dst_End_Ptr = 0u;
  DMA_Entry_Ch6_Alt.Src_End_Ptr = 0u;
  /* Scatter-Gather Transfer */
  DMA_Entry_Ch6_Pri.Control.bit.Cycle_Ctrl = (uint8)DMA_Cycle_Type_MemSctGthPrim;
  /* must be '0' for Scatter-Gather */
  DMA_Entry_Ch6_Pri.Control.bit.Next_UseBurst = 0;
  /* number of transfers  */
  DMA_Entry_Ch6_Pri.Control.bit.N_Minus_1 = (uint16)(((uint16)DMA_CH6_TASK_NoOfTasks * 4u) - 1u);
  /* Arbitrates after one Task trans (4 DMA trans)*/
  DMA_Entry_Ch6_Pri.Control.bit.R_Power = 2;
  /* datawidth of the data to be transferred */
  DMA_Entry_Ch6_Pri.Control.bit.Src_Size = (uint8)DMA_32Bit_Transfer;
  /* datawidth of the data to be transferred */
  DMA_Entry_Ch6_Pri.Control.bit.Dst_Size = (uint8)DMA_32Bit_Transfer;
  /* source increment */
  DMA_Entry_Ch6_Pri.Control.bit.Src_Inc = (uint8)DMA_Inc_32bit;
  /* destination increment */
  DMA_Entry_Ch6_Pri.Control.bit.Dst_Inc = (uint8)DMA_Inc_32bit;
  /* source end pointer, points to last task in task list */
  /* violation: cast from pointer to unsigned int [MISRA Rule 45] */
  DMA_Entry_Ch6_Pri.Src_End_Ptr = (uint32)&DMA_CH6_TASK_SRC[0] + (uint32)((uint16)(((uint16)DMA_CH6_TASK_NoOfTasks * 4u) - 1u) * ((uint8)1u << (uint8)DMA_32Bit_Transfer));
  /* destination pointer, points to channel index in alternate stucture */
  DMA_Entry_Ch6_Pri.Dst_End_Ptr = (DMA->ALT_CTRL_BASE_PTR.reg + (DMA_CH6 * sizeof(TDMA_Entry))) + 12u;
#endif /* (DMA_CH6_TRANS_MODE == 0u) */
#endif
#if ((DMA_EN & (1u << DMA_CH7)) != 0u)
  /* HPROT control */
  DMA_Entry_Ch7_Pri.Control.bit.Src_Prot_Ctrl = 7u;
  /* HPROT control */
  DMA_Entry_Ch7_Pri.Control.bit.Dst_Prot_Ctrl = 7u;
#if (DMA_CH7_TRANS_MODE == 0)
  /* Basic Transfer */
  DMA_Entry_Ch7_Pri.Control.bit.Cycle_Ctrl = (uint8)DMA_Cycle_Type_Basic;
  /* */
  DMA_Entry_Ch7_Pri.Control.bit.Next_UseBurst = 0;
  /* load source pointer */
  /* violation: cast from pointer to unsigned int [MISRA Rule 45] */
  DMA_Entry_Ch7_Pri.Src_End_Ptr = (uint32)&DMA_CH7_SRC + (uint32)DMA_CH7_SRC_PTR_OFFS;
  /* load destination pointer */
  /* violation: cast from pointer to unsigned int [MISRA Rule 45] */
  DMA_Entry_Ch7_Pri.Dst_End_Ptr = (uint32)&DMA_CH7_DST + (uint32)DMA_CH7_DST_PTR_OFFS;
  /* violation: Constant value Boolean [MISRA Rule 52], [MISRA Rule 85] */
  DMA_Entry_Ch7_Pri.Control.bit.Dst_Inc = ((DMA_CH7_INC & 2u) == 2u) ? (uint8)DMA_CH7_SIZE : (uint8)3;
  DMA_Entry_Ch7_Pri.Control.bit.Src_Inc = ((DMA_CH7_INC & 1u) == 1u) ? (uint8)DMA_CH7_SIZE : (uint8)3;
  DMA_Entry_Ch7_Pri.Control.bit.Dst_Size = DMA_CH7_SIZE;
  DMA_Entry_Ch7_Pri.Control.bit.Src_Size = DMA_CH7_SIZE;
  /* number of transfers minus 1 */
  DMA_Entry_Ch7_Pri.Control.bit.N_Minus_1 = (uint16)(DMA_CH7_NoOfTrans - 1);
#else
  /* initialize alternate table entry */
  DMA_Entry_Ch7_Alt.Control.reg = 0u;
  DMA_Entry_Ch7_Alt.Dst_End_Ptr = 0u;
  DMA_Entry_Ch7_Alt.Src_End_Ptr = 0u;
  /* Scatter-Gather Transfer */
  DMA_Entry_Ch7_Pri.Control.bit.Cycle_Ctrl = (uint8)DMA_Cycle_Type_MemSctGthPrim;
  /* must be '0' for Scatter-Gather */
  DMA_Entry_Ch7_Pri.Control.bit.Next_UseBurst = 0;
  /* number of transfers  */
  DMA_Entry_Ch7_Pri.Control.bit.N_Minus_1 = (uint16)(((uint16)DMA_CH7_TASK_NoOfTasks * 4u) - 1u);
  /* Arbitrates after one Task trans (4 DMA trans)*/
  DMA_Entry_Ch7_Pri.Control.bit.R_Power = 2;
  /* datawidth of the data to be transferred */
  DMA_Entry_Ch7_Pri.Control.bit.Src_Size = (uint8)DMA_32Bit_Transfer;
  /* datawidth of the data to be transferred */
  DMA_Entry_Ch7_Pri.Control.bit.Dst_Size = (uint8)DMA_32Bit_Transfer;
  /* source increment */
  DMA_Entry_Ch7_Pri.Control.bit.Src_Inc = (uint8)DMA_Inc_32bit;
  /* destination increment */
  DMA_Entry_Ch7_Pri.Control.bit.Dst_Inc = (uint8)DMA_Inc_32bit;
  /* source end pointer, points to last task in task list */
  /* violation: cast from pointer to unsigned int [MISRA Rule 45] */
  DMA_Entry_Ch7_Pri.Src_End_Ptr = (uint32)&DMA_CH7_TASK_SRC[0] + (uint32)((uint16)(((uint16)DMA_CH7_TASK_NoOfTasks * 4u) - 1u) * ((uint8)1u << (uint8)DMA_32Bit_Transfer));
  /* destination pointer, points to channel index in alternate stucture */
  DMA_Entry_Ch7_Pri.Dst_End_Ptr = (DMA->ALT_CTRL_BASE_PTR.reg + (DMA_CH7 * sizeof(TDMA_Entry))) + 12u;
#endif /* (DMA_CH7_TRANS_MODE == 0u) */
#endif
  /* violation: the shift value is at least the precision of the essential type of the left hand side [MISRA 2012 Rule 12.2, required] */
#if ((DMA_EN & (1u << DMA_CH8)) != 0u)
  /* HPROT control */
  DMA_Entry_Ch8_Pri.Control.bit.Src_Prot_Ctrl = 7u;
  /* HPROT control */
  DMA_Entry_Ch8_Pri.Control.bit.Dst_Prot_Ctrl = 7u;
#if (DMA_CH8_TRANS_MODE == 0)
  /* Basic Transfer */
  DMA_Entry_Ch8_Pri.Control.bit.Cycle_Ctrl = (uint8)DMA_Cycle_Type_Basic;
  /* */
  DMA_Entry_Ch8_Pri.Control.bit.Next_UseBurst = 0;
  /* load source pointer */
  /* violation: cast from pointer to unsigned int [MISRA Rule 45] */
  DMA_Entry_Ch8_Pri.Src_End_Ptr = (uint32)&DMA_CH8_SRC + (uint32)DMA_CH8_SRC_PTR_OFFS;
  /* load destination pointer */
  /* violation: cast from pointer to unsigned int [MISRA Rule 45] */
  DMA_Entry_Ch8_Pri.Dst_End_Ptr = (uint32)&DMA_CH8_DST + (uint32)DMA_CH8_DST_PTR_OFFS;
  /* violation: Constant value Boolean [MISRA Rule 52], [MISRA Rule 85] */
  DMA_Entry_Ch8_Pri.Control.bit.Dst_Inc = ((DMA_CH8_INC & 2u) == 2u) ? (uint8)DMA_CH8_SIZE : (uint8)3;
  DMA_Entry_Ch8_Pri.Control.bit.Src_Inc = ((DMA_CH8_INC & 1u) == 1u) ? (uint8)DMA_CH8_SIZE : (uint8)3;
  DMA_Entry_Ch8_Pri.Control.bit.Dst_Size = DMA_CH8_SIZE;
  DMA_Entry_Ch8_Pri.Control.bit.Src_Size = DMA_CH8_SIZE;
  /* number of transfers minus 1 */
  DMA_Entry_Ch8_Pri.Control.bit.N_Minus_1 = (uint16)(DMA_CH8_NoOfTrans - 1);
#else
  /* initialize alternate table entry */
  DMA_Entry_Ch8_Alt.Control.reg = 0u;
  DMA_Entry_Ch8_Alt.Dst_End_Ptr = 0u;
  DMA_Entry_Ch8_Alt.Src_End_Ptr = 0u;
  /* Scatter-Gather Transfer */
  DMA_Entry_Ch8_Pri.Control.bit.Cycle_Ctrl = (uint8)DMA_Cycle_Type_MemSctGthPrim;
  /* must be '0' for Scatter-Gather */
  DMA_Entry_Ch8_Pri.Control.bit.Next_UseBurst = 0;
  /* number of transfers  */
  DMA_Entry_Ch8_Pri.Control.bit.N_Minus_1 = (uint16)(((uint16)DMA_CH8_TASK_NoOfTasks * 4u) - 1u);
  /* Arbitrates after one Task trans (4 DMA trans)*/
  DMA_Entry_Ch8_Pri.Control.bit.R_Power = 2;
  /* datawidth of the data to be transferred */
  DMA_Entry_Ch8_Pri.Control.bit.Src_Size = (uint8)DMA_32Bit_Transfer;
  /* datawidth of the data to be transferred */
  DMA_Entry_Ch8_Pri.Control.bit.Dst_Size = (uint8)DMA_32Bit_Transfer;
  /* source increment */
  DMA_Entry_Ch8_Pri.Control.bit.Src_Inc = (uint8)DMA_Inc_32bit;
  /* destination increment */
  DMA_Entry_Ch8_Pri.Control.bit.Dst_Inc = (uint8)DMA_Inc_32bit;
  /* source end pointer, points to last task in task list */
  /* violation: cast from pointer to unsigned int [MISRA Rule 45] */
  DMA_Entry_Ch8_Pri.Src_End_Ptr = (uint32)&DMA_CH8_TASK_SRC[0] + (uint32)((uint16)(((uint16)DMA_CH8_TASK_NoOfTasks * 4u) - 1u) * ((uint8)1u << (uint8)DMA_32Bit_Transfer));
  /* destination pointer, points to channel index in alternate stucture */
  DMA_Entry_Ch8_Pri.Dst_End_Ptr = (DMA->ALT_CTRL_BASE_PTR.reg + (DMA_CH8 * sizeof(TDMA_Entry))) + 12u;
#endif /* (DMA_CH8_TRANS_MODE == 0u) */
#endif
  /* violation: the shift value is at least the precision of the essential type of the left hand side [MISRA 2012 Rule 12.2, required] */
#if ((DMA_EN & (1u << DMA_CH9)) != 0u)
  /* HPROT control */
  DMA_Entry_Ch9_Pri.Control.bit.Src_Prot_Ctrl = 7u;
  /* HPROT control */
  DMA_Entry_Ch9_Pri.Control.bit.Dst_Prot_Ctrl = 7u;
#if (DMA_CH9_TRANS_MODE == 0)
  /* Basic Transfer */
  DMA_Entry_Ch9_Pri.Control.bit.Cycle_Ctrl = (uint8)DMA_Cycle_Type_Basic;
  /* */
  DMA_Entry_Ch9_Pri.Control.bit.Next_UseBurst = 0;
  /* load source pointer */
  /* violation: cast from pointer to unsigned int [MISRA Rule 45] */
  DMA_Entry_Ch9_Pri.Src_End_Ptr = (uint32)&DMA_CH9_SRC + (uint32)DMA_CH9_SRC_PTR_OFFS;
  /* load destination pointer */
  /* violation: cast from pointer to unsigned int [MISRA Rule 45] */
  DMA_Entry_Ch9_Pri.Dst_End_Ptr = (uint32)&DMA_CH9_DST + (uint32)DMA_CH9_DST_PTR_OFFS;
  /* violation: Constant value Boolean [MISRA Rule 52], [MISRA Rule 85] */
  DMA_Entry_Ch9_Pri.Control.bit.Dst_Inc = ((DMA_CH9_INC & 2u) == 2u) ? (uint8)DMA_CH9_SIZE : (uint8)3;
  DMA_Entry_Ch9_Pri.Control.bit.Src_Inc = ((DMA_CH9_INC & 1u) == 1u) ? (uint8)DMA_CH9_SIZE : (uint8)3;
  DMA_Entry_Ch9_Pri.Control.bit.Dst_Size = DMA_CH9_SIZE;
  DMA_Entry_Ch9_Pri.Control.bit.Src_Size = DMA_CH9_SIZE;
  /* number of transfers minus 1 */
  DMA_Entry_Ch9_Pri.Control.bit.N_Minus_1 = (uint16)(DMA_CH9_NoOfTrans - 1);
#else
  /* initialize alternate table entry */
  DMA_Entry_Ch9_Alt.Control.reg = 0u;
  DMA_Entry_Ch9_Alt.Dst_End_Ptr = 0u;
  DMA_Entry_Ch9_Alt.Src_End_Ptr = 0u;
  /* Scatter-Gather Transfer */
  DMA_Entry_Ch9_Pri.Control.bit.Cycle_Ctrl = (uint8)DMA_Cycle_Type_MemSctGthPrim;
  /* must be '0' for Scatter-Gather */
  DMA_Entry_Ch9_Pri.Control.bit.Next_UseBurst = 0;
  /* number of transfers  */
  DMA_Entry_Ch9_Pri.Control.bit.N_Minus_1 = (uint16)(((uint16)DMA_CH9_TASK_NoOfTasks * 4u) - 1u);
  /* Arbitrates after one Task trans (4 DMA trans)*/
  DMA_Entry_Ch9_Pri.Control.bit.R_Power = 2;
  /* datawidth of the data to be transferred */
  DMA_Entry_Ch9_Pri.Control.bit.Src_Size = (uint8)DMA_32Bit_Transfer;
  /* datawidth of the data to be transferred */
  DMA_Entry_Ch9_Pri.Control.bit.Dst_Size = (uint8)DMA_32Bit_Transfer;
  /* source increment */
  DMA_Entry_Ch9_Pri.Control.bit.Src_Inc = (uint8)DMA_Inc_32bit;
  /* destination increment */
  DMA_Entry_Ch9_Pri.Control.bit.Dst_Inc = (uint8)DMA_Inc_32bit;
  /* source end pointer, points to last task in task list */
  /* violation: cast from pointer to unsigned int [MISRA Rule 45] */
  DMA_Entry_Ch9_Pri.Src_End_Ptr = (uint32)&DMA_CH9_TASK_SRC[0] + (uint32)((uint16)(((uint16)DMA_CH9_TASK_NoOfTasks * 4u) - 1u) * ((uint8)1u << (uint8)DMA_32Bit_Transfer));
  /* destination pointer, points to channel index in alternate stucture */
  DMA_Entry_Ch9_Pri.Dst_End_Ptr = (DMA->ALT_CTRL_BASE_PTR.reg + (DMA_CH9 * sizeof(TDMA_Entry))) + 12u;
#endif /* (DMA_CH9_TRANS_MODE == 0u) */
#endif
  /* violation: the shift value is at least the precision of the essential type of the left hand side [MISRA 2012 Rule 12.2, required] */
#if ((DMA_EN & (1u << DMA_CH10)) != 0u)
  DMA_Entry_Ch10_Pri.Control.bit.Src_Prot_Ctrl = 7u;
  /* HPROT control */
  DMA_Entry_Ch10_Pri.Control.bit.Dst_Prot_Ctrl = 7u;
#if (DMA_CH10_TRANS_MODE == 0)
  /* Basic Transfer */
  DMA_Entry_Ch10_Pri.Control.bit.Cycle_Ctrl = (uint8)DMA_Cycle_Type_Basic;
  /* */
  DMA_Entry_Ch10_Pri.Control.bit.Next_UseBurst = 0;
  /* load source pointer */
  /* violation: cast from pointer to unsigned int [MISRA Rule 45] */
  DMA_Entry_Ch10_Pri.Src_End_Ptr = (uint32)&DMA_CH10_SRC + (uint32)DMA_CH10_SRC_PTR_OFFS;
  /* load destination pointer */
  /* violation: cast from pointer to unsigned int [MISRA Rule 45] */
  DMA_Entry_Ch10_Pri.Dst_End_Ptr = (uint32)&DMA_CH10_DST + (uint32)DMA_CH10_DST_PTR_OFFS;
  /* violation: Constant value Boolean [MISRA Rule 52], [MISRA Rule 85] */
  DMA_Entry_Ch10_Pri.Control.bit.Dst_Inc = ((DMA_CH10_INC & 2u) == 2u) ? (uint8)DMA_CH10_SIZE : (uint8)3;
  DMA_Entry_Ch10_Pri.Control.bit.Src_Inc = ((DMA_CH10_INC & 1u) == 1u) ? (uint8)DMA_CH10_SIZE : (uint8)3;
  DMA_Entry_Ch10_Pri.Control.bit.Dst_Size = DMA_CH10_SIZE;
  DMA_Entry_Ch10_Pri.Control.bit.Src_Size = DMA_CH10_SIZE;
  /* number of transfers minus 1 */
  DMA_Entry_Ch10_Pri.Control.bit.N_Minus_1 = (uint16)(DMA_CH10_NoOfTrans - 1);
#else
  /* initialize alternate table entry */
  DMA_Entry_Ch10_Alt.Control.reg = 0u;
  DMA_Entry_Ch10_Alt.Dst_End_Ptr = 0u;
  DMA_Entry_Ch10_Alt.Src_End_Ptr = 0u;
  /* Scatter-Gather Transfer */
  DMA_Entry_Ch10_Pri.Control.bit.Cycle_Ctrl = (uint8)DMA_Cycle_Type_MemSctGthPrim;
  /* must be '0' for Scatter-Gather */
  DMA_Entry_Ch10_Pri.Control.bit.Next_UseBurst = 0;
  /* number of transfers  */
  DMA_Entry_Ch10_Pri.Control.bit.N_Minus_1 = (uint16)(((uint16)DMA_CH10_TASK_NoOfTasks * 4u) - 1u);
  /* Arbitrates after one Task trans (4 DMA trans)*/
  DMA_Entry_Ch10_Pri.Control.bit.R_Power = 2;
  /* datawidth of the data to be transferred */
  DMA_Entry_Ch10_Pri.Control.bit.Src_Size = (uint8)DMA_32Bit_Transfer;
  /* datawidth of the data to be transferred */
  DMA_Entry_Ch10_Pri.Control.bit.Dst_Size = (uint8)DMA_32Bit_Transfer;
  /* source increment */
  DMA_Entry_Ch10_Pri.Control.bit.Src_Inc = (uint8)DMA_Inc_32bit;
  /* destination increment */
  DMA_Entry_Ch10_Pri.Control.bit.Dst_Inc = (uint8)DMA_Inc_32bit;
  /* source end pointer, points to last task in task list */
  /* violation: cast from pointer to unsigned int [MISRA Rule 45] */
  DMA_Entry_Ch10_Pri.Src_End_Ptr = (uint32)&DMA_CH10_TASK_SRC[0] + (uint32)((uint16)(((uint16)DMA_CH10_TASK_NoOfTasks * 4u) - 1u) * ((uint8)1u << (uint8)DMA_32Bit_Transfer));
  /* destination pointer, points to channel index in alternate stucture */
  DMA_Entry_Ch10_Pri.Dst_End_Ptr = (DMA->ALT_CTRL_BASE_PTR.reg + (DMA_CH10 * sizeof(TDMA_Entry))) + 12u;
#endif /* (DMA_CH10_TRANS_MODE == 0u) */
#endif
  /* violation: the shift value is at least the precision of the essential type of the left hand side [MISRA 2012 Rule 12.2, required] */
#if ((DMA_EN & (1u << DMA_CH11)) != 0u)
  /* HPROT control */
  DMA_Entry_Ch11_Pri.Control.bit.Src_Prot_Ctrl = 7u;
  /* HPROT control */
  DMA_Entry_Ch11_Pri.Control.bit.Dst_Prot_Ctrl = 7u;
#if (DMA_CH11_TRANS_MODE == 0)
  /* Basic Transfer */
  DMA_Entry_Ch11_Pri.Control.bit.Cycle_Ctrl = (uint8)DMA_Cycle_Type_Basic;
  /* */
  DMA_Entry_Ch11_Pri.Control.bit.Next_UseBurst = 0;
  /* load source pointer */
  /* violation: cast from pointer to unsigned int [MISRA Rule 45] */
  DMA_Entry_Ch11_Pri.Src_End_Ptr = (uint32)&DMA_CH11_SRC + (uint32)DMA_CH11_SRC_PTR_OFFS;
  /* load destination pointer */
  /* violation: cast from pointer to unsigned int [MISRA Rule 45] */
  DMA_Entry_Ch11_Pri.Dst_End_Ptr = (uint32)&DMA_CH11_DST + (uint32)DMA_CH11_DST_PTR_OFFS;
  /* violation: Constant value Boolean [MISRA Rule 52], [MISRA Rule 85] */
  DMA_Entry_Ch11_Pri.Control.bit.Dst_Inc = ((DMA_CH11_INC & 2u) == 2u) ? (uint8)DMA_CH11_SIZE : (uint8)3;
  DMA_Entry_Ch11_Pri.Control.bit.Src_Inc = ((DMA_CH11_INC & 1u) == 1u) ? (uint8)DMA_CH11_SIZE : (uint8)3;
  DMA_Entry_Ch11_Pri.Control.bit.Dst_Size = DMA_CH11_SIZE;
  DMA_Entry_Ch11_Pri.Control.bit.Src_Size = DMA_CH11_SIZE;
  /* number of transfers minus 1 */
  DMA_Entry_Ch11_Pri.Control.bit.N_Minus_1 = (uint16)(DMA_CH11_NoOfTrans - 1);
#else
  /* initialize alternate table entry */
  DMA_Entry_Ch11_Alt.Control.reg = 0u;
  DMA_Entry_Ch11_Alt.Dst_End_Ptr = 0u;
  DMA_Entry_Ch11_Alt.Src_End_Ptr = 0u;
  /* Scatter-Gather Transfer */
  DMA_Entry_Ch11_Pri.Control.bit.Cycle_Ctrl = (uint8)DMA_Cycle_Type_MemSctGthPrim;
  /* must be '0' for Scatter-Gather */
  DMA_Entry_Ch11_Pri.Control.bit.Next_UseBurst = 0;
  /* number of transfers  */
  DMA_Entry_Ch11_Pri.Control.bit.N_Minus_1 = (uint16)(((uint16)DMA_CH11_TASK_NoOfTasks * 4u) - 1u);
  /* Arbitrates after one Task trans (4 DMA trans)*/
  DMA_Entry_Ch11_Pri.Control.bit.R_Power = 2;
  /* datawidth of the data to be transferred */
  DMA_Entry_Ch11_Pri.Control.bit.Src_Size = (uint8)DMA_32Bit_Transfer;
  /* datawidth of the data to be transferred */
  DMA_Entry_Ch11_Pri.Control.bit.Dst_Size = (uint8)DMA_32Bit_Transfer;
  /* source increment */
  DMA_Entry_Ch11_Pri.Control.bit.Src_Inc = (uint8)DMA_Inc_32bit;
  /* destination increment */
  DMA_Entry_Ch11_Pri.Control.bit.Dst_Inc = (uint8)DMA_Inc_32bit;
  /* source end pointer, points to last task in task list */
  /* violation: cast from pointer to unsigned int [MISRA Rule 45] */
  DMA_Entry_Ch11_Pri.Src_End_Ptr = (uint32)&DMA_CH11_TASK_SRC[0] + (uint32)((uint16)(((uint16)DMA_CH11_TASK_NoOfTasks * 4u) - 1u) * ((uint8)1u << (uint8)DMA_32Bit_Transfer));
  /* destination pointer, points to channel index in alternate stucture */
  DMA_Entry_Ch11_Pri.Dst_End_Ptr = (DMA->ALT_CTRL_BASE_PTR.reg + (DMA_CH11 * sizeof(TDMA_Entry))) + 12u;
#endif /* (DMA_CH11_TRANS_MODE == 0u) */
#endif
  /* violation: the shift value is at least the precision of the essential type of the left hand side [MISRA 2012 Rule 12.2, required] */
#if ((DMA_EN & (1u << DMA_CH12)) != 0u)
  /* HPROT control */
  DMA_Entry_Ch12_Pri.Control.bit.Src_Prot_Ctrl = 7u;
  /* HPROT control */
  DMA_Entry_Ch12_Pri.Control.bit.Dst_Prot_Ctrl = 7u;
#if (DMA_CH12_TRANS_MODE == 0)
  /* Basic Transfer */
  DMA_Entry_Ch12_Pri.Control.bit.Cycle_Ctrl = (uint8)DMA_Cycle_Type_Basic;
  /* */
  DMA_Entry_Ch12_Pri.Control.bit.Next_UseBurst = 0;
  /* load source pointer */
  /* violation: cast from pointer to unsigned int [MISRA Rule 45] */
  DMA_Entry_Ch12_Pri.Src_End_Ptr = (uint32)&DMA_CH12_SRC + (uint32)DMA_CH12_SRC_PTR_OFFS;
  /* load destination pointer */
  /* violation: cast from pointer to unsigned int [MISRA Rule 45] */
  DMA_Entry_Ch12_Pri.Dst_End_Ptr = (uint32)&DMA_CH12_DST + (uint32)DMA_CH12_DST_PTR_OFFS;
  /* violation: Constant value Boolean [MISRA Rule 52], [MISRA Rule 85] */
  DMA_Entry_Ch12_Pri.Control.bit.Dst_Inc = ((DMA_CH12_INC & 2u) == 2u) ? (uint8)DMA_CH12_SIZE : (uint8)3;
  DMA_Entry_Ch12_Pri.Control.bit.Src_Inc = ((DMA_CH12_INC & 1u) == 1u) ? (uint8)DMA_CH12_SIZE : (uint8)3;
  DMA_Entry_Ch12_Pri.Control.bit.Dst_Size = DMA_CH12_SIZE;
  DMA_Entry_Ch12_Pri.Control.bit.Src_Size = DMA_CH12_SIZE;
  /* number of transfers minus 1 */
  DMA_Entry_Ch12_Pri.Control.bit.N_Minus_1 = (uint16)(DMA_CH12_NoOfTrans - 1);
#else
  /* initialize alternate table entry */
  DMA_Entry_Ch12_Alt.Control.reg = 0u;
  DMA_Entry_Ch12_Alt.Dst_End_Ptr = 0u;
  DMA_Entry_Ch12_Alt.Src_End_Ptr = 0u;
  /* Scatter-Gather Transfer */
  DMA_Entry_Ch12_Pri.Control.bit.Cycle_Ctrl = (uint8)DMA_Cycle_Type_MemSctGthPrim;
  /* must be '0' for Scatter-Gather */
  DMA_Entry_Ch12_Pri.Control.bit.Next_UseBurst = 0;
  /* number of transfers  */
  DMA_Entry_Ch12_Pri.Control.bit.N_Minus_1 = (uint16)(((uint16)DMA_CH12_TASK_NoOfTasks * 4u) - 1u);
  /* Arbitrates after one Task trans (4 DMA trans)*/
  DMA_Entry_Ch12_Pri.Control.bit.R_Power = 2;
  /* datawidth of the data to be transferred */
  DMA_Entry_Ch12_Pri.Control.bit.Src_Size = (uint8)DMA_32Bit_Transfer;
  /* datawidth of the data to be transferred */
  DMA_Entry_Ch12_Pri.Control.bit.Dst_Size = (uint8)DMA_32Bit_Transfer;
  /* source increment */
  DMA_Entry_Ch12_Pri.Control.bit.Src_Inc = (uint8)DMA_Inc_32bit;
  /* destination increment */
  DMA_Entry_Ch12_Pri.Control.bit.Dst_Inc = (uint8)DMA_Inc_32bit;
  /* source end pointer, points to last task in task list */
  /* violation: cast from pointer to unsigned int [MISRA Rule 45] */
  DMA_Entry_Ch12_Pri.Src_End_Ptr = (uint32)&DMA_CH12_TASK_SRC[0] + (uint32)((uint16)(((uint16)DMA_CH12_TASK_NoOfTasks * 4u) - 1u) * ((uint8)1u << (uint8)DMA_32Bit_Transfer));
  /* destination pointer, points to channel index in alternate stucture */
  DMA_Entry_Ch12_Pri.Dst_End_Ptr = (DMA->ALT_CTRL_BASE_PTR.reg + (DMA_CH12 * sizeof(TDMA_Entry))) + 12u;
#endif /* (DMA_CH12_TRANS_MODE == 0u) */
#endif
#if defined UC_FEATURE_DMA_CH13
  /* violation: the shift value is at least the precision of the essential type of the left hand side [MISRA 2012 Rule 12.2, required] */
#if ((DMA_EN & (1u << DMA_CH13)) != 0u)
  /* HPROT control */
  DMA_Entry_Ch13_Pri.Control.bit.Src_Prot_Ctrl = 7u;
  /* HPROT control */
  DMA_Entry_Ch13_Pri.Control.bit.Dst_Prot_Ctrl = 7u;
#if (DMA_CH13_TRANS_MODE == 0)
  /* Basic Transfer */
  DMA_Entry_Ch13_Pri.Control.bit.Cycle_Ctrl = (uint8)DMA_Cycle_Type_Basic;
  /* */
  DMA_Entry_Ch13_Pri.Control.bit.Next_UseBurst = 0;
  /* load source pointer */
  /* violation: cast from pointer to unsigned int [MISRA Rule 45] */
  DMA_Entry_Ch13_Pri.Src_End_Ptr = (uint32)&DMA_CH13_SRC + (uint32)DMA_CH13_SRC_PTR_OFFS;
  /* load destination pointer */
  /* violation: cast from pointer to unsigned int [MISRA Rule 45] */
  DMA_Entry_Ch13_Pri.Dst_End_Ptr = (uint32)&DMA_CH13_DST + (uint32)DMA_CH13_DST_PTR_OFFS;
  /* violation: Constant value Boolean [MISRA Rule 52], [MISRA Rule 85] */
  DMA_Entry_Ch13_Pri.Control.bit.Dst_Inc = ((DMA_CH13_INC & 2u) == 2u) ? (uint8)DMA_CH13_SIZE : (uint8)3;
  DMA_Entry_Ch13_Pri.Control.bit.Src_Inc = ((DMA_CH13_INC & 1u) == 1u) ? (uint8)DMA_CH13_SIZE : (uint8)3;
  DMA_Entry_Ch13_Pri.Control.bit.Dst_Size = DMA_CH13_SIZE;
  DMA_Entry_Ch13_Pri.Control.bit.Src_Size = DMA_CH13_SIZE;
  /* number of transfers minus 1 */
  DMA_Entry_Ch13_Pri.Control.bit.N_Minus_1 = (uint16)(DMA_CH13_NoOfTrans - 1);
#else
  /* initialize alternate table entry */
  DMA_Entry_Ch13_Alt.Control.reg = 0u;
  DMA_Entry_Ch13_Alt.Dst_End_Ptr = 0u;
  DMA_Entry_Ch13_Alt.Src_End_Ptr = 0u;
  /* Scatter-Gather Transfer */
  DMA_Entry_Ch13_Pri.Control.bit.Cycle_Ctrl = (uint8)DMA_Cycle_Type_MemSctGthPrim;
  /* must be '0' for Scatter-Gather */
  DMA_Entry_Ch13_Pri.Control.bit.Next_UseBurst = 0;
  /* number of transfers  */
  DMA_Entry_Ch13_Pri.Control.bit.N_Minus_1 = (uint16)(((uint16)DMA_CH13_TASK_NoOfTasks * 4u) - 1u);
  /* Arbitrates after one Task trans (4 DMA trans)*/
  DMA_Entry_Ch13_Pri.Control.bit.R_Power = 2;
  /* datawidth of the data to be transferred */
  DMA_Entry_Ch13_Pri.Control.bit.Src_Size = (uint8)DMA_32Bit_Transfer;
  /* datawidth of the data to be transferred */
  DMA_Entry_Ch13_Pri.Control.bit.Dst_Size = (uint8)DMA_32Bit_Transfer;
  /* source increment */
  DMA_Entry_Ch13_Pri.Control.bit.Src_Inc = (uint8)DMA_Inc_32bit;
  /* destination increment */
  DMA_Entry_Ch13_Pri.Control.bit.Dst_Inc = (uint8)DMA_Inc_32bit;
  /* source end pointer, points to last task in task list */
  /* violation: cast from pointer to unsigned int [MISRA Rule 45] */
  DMA_Entry_Ch13_Pri.Src_End_Ptr = (uint32)&DMA_CH13_TASK_SRC[0] + (uint32)((uint16)(((uint16)DMA_CH13_TASK_NoOfTasks * 4u) - 1u) * ((uint8)1u << (uint8)DMA_32Bit_Transfer));
  /* destination pointer, points to channel index in alternate stucture */
  DMA_Entry_Ch13_Pri.Dst_End_Ptr = (DMA->ALT_CTRL_BASE_PTR.reg + (DMA_CH13 * sizeof(TDMA_Entry))) + 12u;
#endif /* (DMA_CH13_TRANS_MODE == 0u) */
#endif /* ((DMA_EN & DMA_MASK_CH13) != 0u) */
#endif /* UC_FEATURE_DMA_CH13 */
  /* enable the DMA channel */
  DMA->CHNL_ENABLE_SET.reg = (uint32)DMA_EN;
}
#else
#if (CONFIGWIZARD == 1)
  #error "use IFXConfigWizard V1 XML Version V1.3.4 or greater"
#else
  #error "use Config Wizard for MOTIX MCU XML Version V2.0.3 or greater"
#endif
#endif

#if defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6000000)
  #pragma clang diagnostic pop
#endif
