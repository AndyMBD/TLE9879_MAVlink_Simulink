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
/**
 * \file     dma.h
 *
 * \brief    Direct Memory Access low level access library
 *
 * \version  V0.2.3
 * \date     28. Feb 2022
 *
 *  \note This file violates [MISRA Rule 1], [MISRA Rule 26], [MISRA Rule 45], [MISRA Rule 52], [MISRA Rule 72], [MISRA Rule 85], [MISRA 2012 Rule 12.1, advisory], [MISRA 2012 Rule 12.2, required], [MISRA 2012 Directive 4.9, advisory], [MISRA 2012 Rule 20.10, advisory]
 */

/*******************************************************************************
**                             Author(s) Identity                             **
********************************************************************************
** Initials     Name                                                          **
** ---------------------------------------------------------------------------**
** DM           Daniel Mysliwitz                                              **
** BG           Blandine Guillot                                              **
** JO           Julia Ott                                                     **
*******************************************************************************/

/*******************************************************************************
**                          Revision Control History                          **
********************************************************************************
** V0.1.0: 2015-11-25, DM:   Initial version                                  **
** V0.1.1: 2017-07-09, DM:   Interrupt macros added                           **
**                           Scatter-gather support added                     **
** V0.1.2: 2017-07-12, DM:   Setup task for scatter-gather added              **
** V0.1.3: 2017-07-20, DM:   API macros added                                 **
** V0.1.4: 2017-09-22, DM:   MISRA 2012 compliance, the following PC-Lint     **
**                           rules are globally deactivated:                  **
**                           - Info 793: ANSI/ISO limit of 6 'significant     **
**                             characters in an external identifier           **
**                           - Note 950: Non-ANSI reserved word or construct: **
**                             '_to_brackets' [MISRA Rule 1]                  **
**                           - Note 923: cast from unsigned int to pointer    **
**                            [MISRA Rule 45]                                 **
**                           - Note 923: cast from pointer to unsigned int    **
**                             [MISRA Rule 45]                                **
**                           - Info 765: Info 765: external '...' could be    **
**                             made static [MISRA Rule 23]                    **
**                           - Error 18: Symbol '..' redeclared (void/nonvoid)**
**                             ... [MISRA Rule 26],[Encompasses MISRA Rule 72]**
** V0.1.5: 2018-03-12, DM:   DMA Ch13 (SDADC) added                           **
**                           DMA_MASK_CHx macros changed due to MISRA 2012    **
**                           Replaced macros by INLINE functions              **
**                           Replaced register accesses within functions by   **
**                           function calls                                   **
**                           Replaced __STATIC_INLINE by INLINE               **
**                           Renamed DMA entries according to channel number  **
** V0.1.6: 2018-11-27, JO:   Doxygen update                                   **
**                           Moved revision history from dma.c to dma.h       **
** V0.1.7: 2019-02-21, DM:   DMA structures modified to be ARMCC v6 compliant **
**                           DMA base structure set to upper most address     **
**                           3KB RAM: 0x18000A00..0x18000BFF                  **
**                           6KB RAM: 0x18001600..0x180017FF                  **
**                           8KB RAM: 0x18001E00..0x18001FFF                  **
** V0.1.8: 2020-04-15, BG:   Updated revision history format                  **
** V0.1.9: 2020-07-14, JO:   EP-431: remove ARMCC v6 Compiler warnings        **
**                           - Initialized alternate table entry              **
**                           - Disabled ARMCC v6 warnings -Wmissing-variable- **
**                             declarations, -Wunreachable-code, and          **
**                             -Wpedantic locally in file dma.c               **
** V0.2.0: 2020-07-21, BG:   EP-439: Formatted .h/.c files                    **
** V0.2.1: 2020-10-28, DM:   EP-565: Set DMA struct to volatile to remove     **
**                           ARMCC v6 O3 LTO problem                          **
** V0.2.2: 2021-02-01, BG:   EP-175: Updated code for compatibility with      **
**                           IAR compiler                                     **
** V0.2.3: 2022-02-28, JO:   EP-936: Updated copyright and branding           **
*******************************************************************************/

#ifndef _DMA_H
#define _DMA_H

/*******************************************************************************
**                                  Includes                                  **
*******************************************************************************/
#include "tle987x.h"
#include "types.h"
#include "dma_defines.h"
#include "sfr_access.h"

/*******************************************************************************
**                          Global Macro Definitions                          **
*******************************************************************************/
/**\brief DMA channel selection macro, DMA CH0 */
#define DMA_CH0                       (0u)
/**\brief DMA channel selection macro, DMA CH1 */
#define DMA_CH1                       (1u)
/**\brief DMA channel selection macro, DMA CH2 */
#define DMA_CH2                       (2u)
/**\brief DMA channel selection macro, DMA CH3 */
#define DMA_CH3                       (3u)
/**\brief DMA channel selection macro, DMA CH4 */
#define DMA_CH4                       (4u)
/**\brief DMA channel selection macro, DMA CH5 */
#define DMA_CH5                       (5u)
/**\brief DMA channel selection macro, DMA CH6 */
#define DMA_CH6                       (6u)
/**\brief DMA channel selection macro, DMA CH7 */
#define DMA_CH7                       (7u)
/**\brief DMA channel selection macro, DMA CH8 */
#define DMA_CH8                       (8u)
/**\brief DMA channel selection macro, DMA CH9 */
#define DMA_CH9                       (9u)
/**\brief DMA channel selection macro, DMA CH10 */
#define DMA_CH10                      (10u)
/**\brief DMA channel selection macro, DMA CH11 */
#define DMA_CH11                      (11u)
/**\brief DMA channel selection macro, DMA CH12 */
#define DMA_CH12                      (12u)
#if defined TLE9879_2QXA40 || defined TLE9872_2QXW40
  /**\brief DMA channel selection macro, DMA CH13, for TLE9879-2QXA40 only */
  #define DMA_CH13                      (13u)
#endif /* TLE9879_2QXA40 || defined TLE9872_2QXW40 */

/**\brief DMA channel Mask macro, DMA CH0 MASK */
#define DMA_MASK_CH0                  ((uint16)1u << DMA_CH0)
/**\brief DMA channel Mask macro, DMA CH1 MASK */
#define DMA_MASK_CH1                  ((uint16)1u << DMA_CH1)
/**\brief DMA channel Mask macro, DMA CH2 MASK */
#define DMA_MASK_CH2                  ((uint16)1u << DMA_CH2)
/**\brief DMA channel Mask macro, DMA CH3 MASK */
#define DMA_MASK_CH3                  ((uint16)1u << DMA_CH3)
/**\brief DMA channel Mask macro, DMA CH4 MASK */
#define DMA_MASK_CH4                  ((uint16)1u << DMA_CH4)
/**\brief DMA channel Mask macro, DMA CH5 MASK */
#define DMA_MASK_CH5                  ((uint16)1u << DMA_CH5)
/**\brief DMA channel Mask macro, DMA CH6 MASK */
#define DMA_MASK_CH6                  ((uint16)1u << DMA_CH6)
/**\brief DMA channel Mask macro, DMA CH7 MASK */
#define DMA_MASK_CH7                  ((uint16)1u << DMA_CH7)
/**\brief DMA channel Mask macro, DMA CH8 MASK */
#define DMA_MASK_CH8                  ((uint16)1u << DMA_CH8)
/**\brief DMA channel Mask macro, DMA CH9 MASK */
#define DMA_MASK_CH9                  ((uint16)1u << DMA_CH9)
/**\brief DMA channel Mask macro, DMA CH10 MASK */
#define DMA_MASK_CH10                 ((uint16)1u << DMA_CH10)
/**\brief DMA channel Mask macro, DMA CH11 MASK */
#define DMA_MASK_CH11                 ((uint16)1u << DMA_CH11)
/**\brief DMA channel Mask macro, DMA CH12 MASK */
#define DMA_MASK_CH12                 ((uint16)1u << DMA_CH12)
#if defined TLE9879_2QXA40 || defined TLE9872_2QXW40
  /**\brief DMA channel Mask macro, DMA CH13 MASK,  for TLE9879-2QXA40 only */
  #define DMA_MASK_CH13                 ((uint16)1u << DMA_CH13)
#endif /* TLE9879_2QXA40 || defined TLE9872_2QXW40 */

/** \enum _TDMA_Transfer_Size
 *  \brief This enum lists the transfer size options for the DMA
 */
typedef enum _TDMA_Transfer_Size
{
  DMA_8Bit_Transfer   = 0u, /**< DMA Transfer Codes macro, 8Bit Transfer  */
  DMA_16Bit_Transfer  = 1u, /**< DMA Transfer Codes macro, 16Bit Transfer */
  DMA_32Bit_Transfer  = 2u  /**< DMA Transfer Codes macro, 32Bit Transfer */
} TDMA_Transfer_Size;

/** \enum _TDMA_Increment_Size
 *  \brief This enum lists the increment size options for the DMA
 */
typedef enum _TDMA_Increment_Size
{
  DMA_Inc_8bit   = 0u, /**< DMA Increment macro, Increment 8Bit  */
  DMA_Inc_16bit  = 1u, /**< DMA Increment macro, Increment 16Bit */
  DMA_Inc_32bit  = 2u  /**< DMA Increment macro, Increment 32Bit */
} TDMA_Increment_Size;

/** \enum _TDMA_Increment_Mode
 *  \brief This enum lists the increment mode options for the DMA
 */
typedef enum _TDMA_Increment_Mode
{
  DMA_No_Inc       = 0u, /**< DMA Increment Codes macro, No Increment */
  DMA_Src_Inc      = 1u, /**< DMA Increment Codes macro, Source Address Increment */
  DMA_Dst_Inc      = 2u, /**< DMA Increment Codes macro, Destination Address Increment */
  DMA_Src_Dst_Inc  = 3u  /**< DMA Increment Codes macro, Source and Destination Address Increment */
} TDMA_Increment_Mode;

/** \enum _TDMA_Cycle_Types
 *  \brief This enum lists the cycle type options for the DMA
 */
typedef enum _TDMA_Cycle_Types
{
  DMA_Cycle_Type_Invalid       = 0u, /**< DMA Cycle Types macro, Invalid Mode */
  DMA_Cycle_Type_Basic         = 1u, /**< DMA Cycle Types macro, Basic Mode */
  DMA_Cycle_Type_Auto          = 2u, /**< DMA Cycle Types macro, Auto-request Mode */
  DMA_Cycle_Type_PingPong      = 3u, /**< DMA Cycle Types macro, PingPong Mode */
  DMA_Cycle_Type_MemSctGthPrim = 4u, /**< DMA Cycle Types macro, Memory scatter/gather Primary Mode */
  DMA_Cycle_Type_MemSctGthAlt  = 5u, /**< DMA Cycle Types macro, Memory scatter/gather Alternate Mode */
  DMA_Cycle_Type_PerSctGthPrim = 6u, /**< DMA Cycle Types macro, Peripheral scatter/gather Primary Mode */
  DMA_Cycle_Type_PerSctGthAlt  = 7u  /**< DMA Cycle Types macro, Peripheral scatter/gather Alternate Mode */
} TDMA_Cycle_Types;

/*******************************************************************************
**                           Global Type Definitions                          **
*******************************************************************************/
/** \struct TControl
 *  \brief This structure lists the bit assignments for the channel_cfg memory location.
 */
typedef union
{
  uint32  reg;
  struct
  {
    uint32 Cycle_Ctrl: 3;           /**< \brief Bit[2..0] */
    uint32 Next_UseBurst: 1;        /**< \brief Bit[3] */
    uint32 N_Minus_1: 10;           /**< \brief Bit[13..4] */
    uint32 R_Power: 4;              /**< \brief Bit[17..14] */
    uint32 Src_Prot_Ctrl: 3;        /**< \brief Bit[20..18] */
    uint32 Dst_Prot_Ctrl: 3;        /**< \brief Bit[23..21] */
    uint32 Src_Size: 2;             /**< \brief Bit[25..24] */
    uint32 Src_Inc: 2;              /**< \brief Bit[27..26] */
    uint32 Dst_Size: 2;             /**< \brief Bit[29..28] */
    uint32 Dst_Inc: 2;              /**< \brief Bit[31..30] */
  } bit;
} TControl;

/** \struct TDMA_Entry
 *  \brief This structure lists the DMA transfer memory locations.
 */
typedef struct
{
  uint32 Src_End_Ptr;
  uint32 Dst_End_Ptr;
  TControl Control;
  uint32 reserved;
} TDMA_Entry;


/*******************************************************************************
**                     Global Inline Function Definitions                     **
*******************************************************************************/
/** \brief clears DMA Channel 0 Interrupt flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the DMA Channel 0 Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   DMA_CH0_Int_En();
 *   if ((uint8)SCU->DMAIRC2.bit.TRSEQ1DY == (uint8)1)
 *   {
 *     DMA_SQ1_RDY_CALLBACK();
 *     DMA_CH0_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup dma_api
 */
INLINE void DMA_CH0_Int_Clr(void)
{
  Field_Wrt8(&SCU->DMAIRC2CLR.reg, (uint8)SCU_DMAIRC2CLR_TRSEQ1DYC_Pos, (uint8)SCU_DMAIRC2CLR_TRSEQ1DYC_Msk, 1u);
}

/** \brief clears DMA Channel 1 Interrupt flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the DMA Channel 1 Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   DMA_CH1_Int_En();
 *   if ((uint8)SCU->DMAIRC2.bit.TRSEQ2DY == (uint8)1)
 *   {
 *     DMA_SQ2_RDY_CALLBACK();
 *     DMA_CH1_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup dma_api
 */
INLINE void DMA_CH1_Int_Clr(void)
{
  Field_Wrt8(&SCU->DMAIRC2CLR.reg, (uint8)SCU_DMAIRC2CLR_TRSEQ2DYC_Pos, (uint8)SCU_DMAIRC2CLR_TRSEQ2DYC_Msk, 1u);
}

/** \brief clears DMA Channel 2 Interrupt flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the DMA Channel 2 Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   DMA_CH2_Int_En();
 *   if ((uint8)SCU->DMAIRC2.bit.SSC1RDY == (uint8)1)
 *   {
 *     DMA_SSC_TX_CALLBACK();
 *     DMA_CH2_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup dma_api
 */
INLINE void DMA_CH2_Int_Clr(void)
{
  Field_Wrt8(&SCU->DMAIRC2CLR.reg, (uint8)SCU_DMAIRC2CLR_SSC1C_Pos, (uint8)SCU_DMAIRC2CLR_SSC1C_Msk, 1u);
}

/** \brief clears DMA Channel 3 Interrupt flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the DMA Channel 3 Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   DMA_CH3_Int_En();
 *   if ((uint8)SCU->DMAIRC2.bit.SSC2RDY == (uint8)1)
 *   {
 *     DMA_SSC_RX_CALLBACK();
 *     DMA_CH3_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup dma_api
 */
INLINE void DMA_CH3_Int_Clr(void)
{
  Field_Wrt8(&SCU->DMAIRC2CLR.reg, (uint8)SCU_DMAIRC2CLR_SSC2C_Pos, (uint8)SCU_DMAIRC2CLR_SSC2C_Msk, 1u);
}

/** \brief clears DMA Channel 4 Interrupt flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the DMA Channel 4 Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   DMA_CH4_Int_En();
 *   if ((uint8)SCU->DMAIRC1.bit.CH1 == (uint8)1)
 *   {
 *     DMA_CH1_CALLBACK();
 *     DMA_CH4_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup dma_api
 */
INLINE void DMA_CH4_Int_Clr(void)
{
  Field_Wrt8(&SCU->DMAIRC1CLR.reg, (uint8)SCU_DMAIRC1CLR_CH1C_Pos, (uint8)SCU_DMAIRC1CLR_CH1C_Msk, 1u);
}

/** \brief clears DMA Channel 5 Interrupt flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the DMA Channel 5 Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   DMA_CH5_Int_En();
 *   if ((uint8)SCU->DMAIRC1.bit.CH2 == (uint8)1)
 *   {
 *     DMA_CH2_CALLBACK();
 *     DMA_CH5_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup dma_api
 */
INLINE void DMA_CH5_Int_Clr(void)
{
  Field_Wrt8(&SCU->DMAIRC1CLR.reg, (uint8)SCU_DMAIRC1CLR_CH2C_Pos, (uint8)SCU_DMAIRC1CLR_CH2C_Msk, 1u);
}

/** \brief clears DMA Channel 6 Interrupt flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the DMA Channel 6 Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   DMA_CH6_Int_En();
 *   if ((uint8)SCU->DMAIRC1.bit.CH3 == (uint8)1)
 *   {
 *     DMA_CH3_CALLBACK();
 *     DMA_CH6_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup dma_api
 */
INLINE void DMA_CH6_Int_Clr(void)
{
  Field_Wrt8(&SCU->DMAIRC1CLR.reg, (uint8)SCU_DMAIRC1CLR_CH3C_Pos, (uint8)SCU_DMAIRC1CLR_CH3C_Msk, 1u);
}

/** \brief clears DMA Channel 7 Interrupt flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the DMA Channel 7 Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   DMA_CH7_Int_En();
 *   if ((uint8)SCU->DMAIRC1.bit.CH4 == (uint8)1)
 *   {
 *     DMA_CH4_CALLBACK();
 *     DMA_CH7_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup dma_api
 */
INLINE void DMA_CH7_Int_Clr(void)
{
  Field_Wrt8(&SCU->DMAIRC1CLR.reg, (uint8)SCU_DMAIRC1CLR_CH4C_Pos, (uint8)SCU_DMAIRC1CLR_CH4C_Msk, 1u);
}

/** \brief clears DMA Channel 8 Interrupt flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the DMA Channel 8 Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   DMA_CH8_Int_En();
 *   if ((uint8)SCU->DMAIRC1.bit.CH5 == (uint8)1)
 *   {
 *     DMA_CH5_CALLBACK();
 *     DMA_CH8_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup dma_api
 */
INLINE void DMA_CH8_Int_Clr(void)
{
  Field_Wrt8(&SCU->DMAIRC1CLR.reg, (uint8)SCU_DMAIRC1CLR_CH5C_Pos, (uint8)SCU_DMAIRC1CLR_CH5C_Msk, 1u);
}

/** \brief clears DMA Channel 9 Interrupt flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the DMA Channel 9 Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   DMA_CH9_Int_En();
 *   if ((uint8)SCU->DMAIRC1.bit.CH6 == (uint8)1)
 *   {
 *     DMA_CH6_CALLBACK();
 *     DMA_CH9_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup dma_api
 */
INLINE void DMA_CH9_Int_Clr(void)
{
  Field_Wrt8(&SCU->DMAIRC1CLR.reg, (uint8)SCU_DMAIRC1CLR_CH6C_Pos, (uint8)SCU_DMAIRC1CLR_CH6C_Msk, 1u);
}

/** \brief clears DMA Channel 10 Interrupt flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the DMA Channel 10 Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   DMA_CH10_Int_En();
 *   if ((uint8)SCU->DMAIRC1.bit.CH7 == (uint8)1)
 *   {
 *     DMA_CH7_CALLBACK();
 *     DMA_CH10_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup dma_api
 */
INLINE void DMA_CH10_Int_Clr(void)
{
  Field_Wrt8(&SCU->DMAIRC1CLR.reg, (uint8)SCU_DMAIRC1CLR_CH7C_Pos, (uint8)SCU_DMAIRC1CLR_CH7C_Msk, 1u);
}

/** \brief clears DMA Channel 11 Interrupt flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the DMA Channel 11 Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   DMA_CH11_Int_En();
 *   if ((uint8)SCU->DMAIRC1.bit.CH8 == (uint8)1)
 *   {
 *     DMA_CH8_CALLBACK();
 *     DMA_CH11_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup dma_api
 */
INLINE void DMA_CH11_Int_Clr(void)
{
  Field_Wrt8(&SCU->DMAIRC1CLR.reg, (uint8)SCU_DMAIRC1CLR_CH8C_Pos, (uint8)SCU_DMAIRC1CLR_CH8C_Msk, 1u);
}

/** \brief clears DMA Channel 12 Interrupt flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the DMA Channel 12 Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   DMA_CH12_Int_En();
 *   if ((uint8)SCU->DMAIRC2.bit.GPT12 == (uint8)1)
 *   {
 *     DMA_GPT12E_CALLBACK();
 *     DMA_CH12_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup dma_api
 */
INLINE void DMA_CH12_Int_Clr(void)
{
  Field_Wrt8(&SCU->DMAIRC2CLR.reg, (uint8)SCU_DMAIRC2CLR_GPT12C_Pos, (uint8)SCU_DMAIRC2CLR_GPT12C_Msk, 1u);
}

#if defined TLE9879_2QXA40 || defined TLE9872_2QXW40
/** \brief clears DMA Channel 13 Interrupt flag.
 * \note for TLE9879-2QXA40 only
 *
 * \brief <b>Example</b><br>
 * \brief This example clears the DMA Channel 13 Interrupt flag when its Status is equal to 1.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   DMA_CH13_Int_En();
 *   if ((uint8)SCU->DMAIRC2.bit.SDADC == (uint8)1)
 *   {
 *     DMA_CH13_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup dma_api
 */
INLINE void DMA_CH13_Int_Clr(void)
{
  Field_Wrt8(&SCU->DMAIRC2CLR.reg, (uint8)SCU_DMAIRC2CLR_SDADCC_Pos, (uint8)SCU_DMAIRC2CLR_SDADCC_Msk, 1u);
}
#endif /* TLE9879_2QXA40 || defined TLE9872_2QXW40 */

/** \brief enables DMA Channel 0 Interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the DMA Channel 0 Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   DMA_CH0_Int_En();
 *   if ((uint8)SCU->DMAIRC2.bit.TRSEQ1DY == (uint8)1)
 *   {
 *     DMA_SQ1_RDY_CALLBACK();
 *     DMA_CH0_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup dma_api
 */
INLINE void DMA_CH0_Int_En(void)
{
  Field_Mod8(&SCU->DMAIEN2.reg, (uint8)SCU_DMAIEN2_TRSEQ1RDYIE_Pos, (uint8)SCU_DMAIEN2_TRSEQ1RDYIE_Msk, 1u);
}

/** \brief disables DMA Channel 0 Interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the DMA Channel 0 Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   DMA_CH0_Int_En();
 *   if ((uint8)SCU->DMAIRC2.bit.TRSEQ1DY == (uint8)1)
 *   {
 *     DMA_SQ1_RDY_CALLBACK();
 *     DMA_CH0_Int_Clr();
 *   }
 *   DMA_CH0_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup dma_api
 */
INLINE void DMA_CH0_Int_Dis(void)
{
  Field_Mod8(&SCU->DMAIEN2.reg, (uint8)SCU_DMAIEN2_TRSEQ1RDYIE_Pos, (uint8)SCU_DMAIEN2_TRSEQ1RDYIE_Msk, 0u);
}

/** \brief enables DMA Channel 1 Interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the DMA Channel 1 Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   DMA_CH1_Int_En();
 *   if ((uint8)SCU->DMAIRC2.bit.TRSEQ2DY == (uint8)1)
 *   {
 *     DMA_SQ2_RDY_CALLBACK();
 *     DMA_CH1_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup dma_api
 */
INLINE void DMA_CH1_Int_En(void)
{
  Field_Mod8(&SCU->DMAIEN2.reg, (uint8)SCU_DMAIEN2_TRSEQ2RDYIE_Pos, (uint8)SCU_DMAIEN2_TRSEQ2RDYIE_Msk, 1u);
}

/** \brief disables DMA Channel 1 Interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the DMA Channel 1 Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   DMA_CH1_Int_En();
 *   if ((uint8)SCU->DMAIRC2.bit.TRSEQ2DY == (uint8)1)
 *   {
 *     DMA_SQ2_RDY_CALLBACK();
 *     DMA_CH1_Int_Clr();
 *   }
 *   DMA_CH1_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup dma_api
 */
INLINE void DMA_CH1_Int_Dis(void)
{
  Field_Mod8(&SCU->DMAIEN2.reg, (uint8)SCU_DMAIEN2_TRSEQ2RDYIE_Pos, (uint8)SCU_DMAIEN2_TRSEQ2RDYIE_Msk, 0u);
}

/** \brief enables DMA Channel 2 Interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the DMA Channel 2 Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   DMA_CH2_Int_En();
 *   if ((uint8)SCU->DMAIRC2.bit.SSC1RDY == (uint8)1)
 *   {
 *     DMA_SSC_TX_CALLBACK();
 *     DMA_CH2_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup dma_api
 */
INLINE void DMA_CH2_Int_En(void)
{
  Field_Mod8(&SCU->DMAIEN2.reg, (uint8)SCU_DMAIEN2_SSCTXIE_Pos, (uint8)SCU_DMAIEN2_SSCTXIE_Msk, 1u);
}

/** \brief disables DMA Channel 2 Interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the DMA Channel 2 Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   DMA_CH2_Int_En();
 *   if ((uint8)SCU->DMAIRC2.bit.SSC1RDY == (uint8)1)
 *   {
 *     DMA_SSC_TX_CALLBACK();
 *     DMA_CH2_Int_Clr();
 *   }
 *   DMA_CH2_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup dma_api
 */
INLINE void DMA_CH2_Int_Dis(void)
{
  Field_Mod8(&SCU->DMAIEN2.reg, (uint8)SCU_DMAIEN2_SSCTXIE_Pos, (uint8)SCU_DMAIEN2_SSCTXIE_Msk, 0u);
}

/** \brief enables DMA Channel 3 Interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the DMA Channel 3 Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   DMA_CH3_Int_En();
 *   if ((uint8)SCU->DMAIRC2.bit.SSC2RDY == (uint8)1)
 *   {
 *     DMA_SSC_RX_CALLBACK();
 *     DMA_CH3_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup dma_api
 */
INLINE void DMA_CH3_Int_En(void)
{
  Field_Mod8(&SCU->DMAIEN2.reg, (uint8)SCU_DMAIEN2_SSCRXIE_Pos, (uint8)SCU_DMAIEN2_SSCRXIE_Msk, 1u);
}

/** \brief disables DMA Channel 3 Interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the DMA Channel 3 Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   DMA_CH3_Int_En();
 *   if ((uint8)SCU->DMAIRC2.bit.SSC2RDY == (uint8)1)
 *   {
 *     DMA_SSC_RX_CALLBACK();
 *     DMA_CH3_Int_Clr();
 *   }
 *   DMA_CH3_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup dma_api
 */
INLINE void DMA_CH3_Int_Dis(void)
{
  Field_Mod8(&SCU->DMAIEN2.reg, (uint8)SCU_DMAIEN2_SSCRXIE_Pos, (uint8)SCU_DMAIEN2_SSCRXIE_Msk, 0u);
}

/** \brief enables DMA Channel 4 Interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the DMA Channel 4 Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   DMA_CH4_Int_En();
 *   if ((uint8)SCU->DMAIRC1.bit.CH1 == (uint8)1)
 *   {
 *     DMA_CH1_CALLBACK();
 *     DMA_CH4_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup dma_api
 */
INLINE void DMA_CH4_Int_En(void)
{
  Field_Mod8(&SCU->DMAIEN1.reg, (uint8)SCU_DMAIEN1_CH1IE_Pos, (uint8)SCU_DMAIEN1_CH1IE_Msk, 1u);
}

/** \brief disables DMA Channel 4 Interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the DMA Channel 4 Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   DMA_CH4_Int_En();
 *   if ((uint8)SCU->DMAIRC1.bit.CH1 == (uint8)1)
 *   {
 *     DMA_CH1_CALLBACK();
 *     DMA_CH4_Int_Clr();
 *   }
 *   DMA_CH4_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup dma_api
 */
INLINE void DMA_CH4_Int_Dis(void)
{
  Field_Mod8(&SCU->DMAIEN1.reg, (uint8)SCU_DMAIEN1_CH1IE_Pos, (uint8)SCU_DMAIEN1_CH1IE_Msk, 0u);
}

/** \brief enables DMA Channel 5 Interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the DMA Channel 5 Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   DMA_CH5_Int_En();
 *   if ((uint8)SCU->DMAIRC1.bit.CH2 == (uint8)1)
 *   {
 *     DMA_CH2_CALLBACK();
 *     DMA_CH5_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup dma_api
 */
INLINE void DMA_CH5_Int_En(void)
{
  Field_Mod8(&SCU->DMAIEN1.reg, (uint8)SCU_DMAIEN1_CH2IE_Pos, (uint8)SCU_DMAIEN1_CH2IE_Msk, 1u);
}

/** \brief disables DMA Channel 5 Interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the DMA Channel 5 Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   DMA_CH5_Int_En();
 *   if ((uint8)SCU->DMAIRC1.bit.CH2 == (uint8)1)
 *   {
 *     DMA_CH2_CALLBACK();
 *     DMA_CH5_Int_Clr();
 *   }
 *   DMA_CH5_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup dma_api
 */
INLINE void DMA_CH5_Int_Dis(void)
{
  Field_Mod8(&SCU->DMAIEN1.reg, (uint8)SCU_DMAIEN1_CH2IE_Pos, (uint8)SCU_DMAIEN1_CH2IE_Msk, 0u);
}

/** \brief enables DMA Channel 6 Interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the DMA Channel 6 Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   DMA_CH6_Int_En();
 *   if ((uint8)SCU->DMAIRC1.bit.CH3 == (uint8)1)
 *   {
 *     DMA_CH3_CALLBACK();
 *     DMA_CH6_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup dma_api
 */
INLINE void DMA_CH6_Int_En(void)
{
  Field_Mod8(&SCU->DMAIEN1.reg, (uint8)SCU_DMAIEN1_CH3IE_Pos, (uint8)SCU_DMAIEN1_CH3IE_Msk, 1u);
}

/** \brief disables DMA Channel 6 Interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the DMA Channel 6 Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   DMA_CH6_Int_En();
 *   if ((uint8)SCU->DMAIRC1.bit.CH3 == (uint8)1)
 *   {
 *     DMA_CH3_CALLBACK();
 *     DMA_CH6_Int_Clr();
 *   }
 *   DMA_CH6_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup dma_api
 */
INLINE void DMA_CH6_Int_Dis(void)
{
  Field_Mod8(&SCU->DMAIEN1.reg, (uint8)SCU_DMAIEN1_CH3IE_Pos, (uint8)SCU_DMAIEN1_CH3IE_Msk, 0u);
}

/** \brief enables DMA Channel 7 Interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the DMA Channel 7 Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   DMA_CH7_Int_En();
 *   if ((uint8)SCU->DMAIRC1.bit.CH4 == (uint8)1)
 *   {
 *     DMA_CH4_CALLBACK();
 *     DMA_CH7_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup dma_api
 */
INLINE void DMA_CH7_Int_En(void)
{
  Field_Mod8(&SCU->DMAIEN1.reg, (uint8)SCU_DMAIEN1_CH4IE_Pos, (uint8)SCU_DMAIEN1_CH4IE_Msk, 1u);
}

/** \brief disables DMA Channel 7 Interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the DMA Channel 7 Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   DMA_CH7_Int_En();
 *   if ((uint8)SCU->DMAIRC1.bit.CH4 == (uint8)1)
 *   {
 *     DMA_CH4_CALLBACK();
 *     DMA_CH7_Int_Clr();
 *   }
 *   DMA_CH7_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup dma_api
 */
INLINE void DMA_CH7_Int_Dis(void)
{
  Field_Mod8(&SCU->DMAIEN1.reg, (uint8)SCU_DMAIEN1_CH4IE_Pos, (uint8)SCU_DMAIEN1_CH4IE_Msk, 0u);
}

/** \brief enables DMA Channel 8 Interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the DMA Channel 8 Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   DMA_CH8_Int_En();
 *   if ((uint8)SCU->DMAIRC1.bit.CH5 == (uint8)1)
 *   {
 *     DMA_CH5_CALLBACK();
 *     DMA_CH8_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup dma_api
 */
INLINE void DMA_CH8_Int_En(void)
{
  Field_Mod8(&SCU->DMAIEN1.reg, (uint8)SCU_DMAIEN1_CH5IE_Pos, (uint8)SCU_DMAIEN1_CH5IE_Msk, 1u);
}

/** \brief disables DMA Channel 8 Interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the DMA Channel 8 Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   DMA_CH8_Int_En();
 *   if ((uint8)SCU->DMAIRC1.bit.CH5 == (uint8)1)
 *   {
 *     DMA_CH5_CALLBACK();
 *     DMA_CH8_Int_Clr();
 *   }
 *   DMA_CH8_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup dma_api
 */
INLINE void DMA_CH8_Int_Dis(void)
{
  Field_Mod8(&SCU->DMAIEN1.reg, (uint8)SCU_DMAIEN1_CH5IE_Pos, (uint8)SCU_DMAIEN1_CH5IE_Msk, 0u);
}

/** \brief enables DMA Channel 9 Interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the DMA Channel 9 Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   DMA_CH9_Int_En();
 *   if ((uint8)SCU->DMAIRC1.bit.CH6 == (uint8)1)
 *   {
 *     DMA_CH6_CALLBACK();
 *     DMA_CH9_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup dma_api
 */
INLINE void DMA_CH9_Int_En(void)
{
  Field_Mod8(&SCU->DMAIEN1.reg, (uint8)SCU_DMAIEN1_CH6IE_Pos, (uint8)SCU_DMAIEN1_CH6IE_Msk, 1u);
}

/** \brief disables DMA Channel 9 Interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the DMA Channel 9 Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   DMA_CH9_Int_En();
 *   if ((uint8)SCU->DMAIRC1.bit.CH6 == (uint8)1)
 *   {
 *     DMA_CH6_CALLBACK();
 *     DMA_CH9_Int_Clr();
 *   }
 *   DMA_CH9_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup dma_api
 */
INLINE void DMA_CH9_Int_Dis(void)
{
  Field_Mod8(&SCU->DMAIEN1.reg, (uint8)SCU_DMAIEN1_CH6IE_Pos, (uint8)SCU_DMAIEN1_CH6IE_Msk, 0u);
}

/** \brief enables DMA Channel 10 Interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the DMA Channel 10 Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   DMA_CH10_Int_En();
 *   if ((uint8)SCU->DMAIRC1.bit.CH7 == (uint8)1)
 *   {
 *     DMA_CH7_CALLBACK();
 *     DMA_CH10_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup dma_api
 */
INLINE void DMA_CH10_Int_En(void)
{
  Field_Mod8(&SCU->DMAIEN1.reg, (uint8)SCU_DMAIEN1_CH7IE_Pos, (uint8)SCU_DMAIEN1_CH7IE_Msk, 1u);
}

/** \brief disables DMA Channel 10 Interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the DMA Channel 10 Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   DMA_CH10_Int_En();
 *   if ((uint8)SCU->DMAIRC1.bit.CH7 == (uint8)1)
 *   {
 *     DMA_CH7_CALLBACK();
 *     DMA_CH10_Int_Clr();
 *   }
 *   DMA_CH10_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup dma_api
 */
INLINE void DMA_CH10_Int_Dis(void)
{
  Field_Mod8(&SCU->DMAIEN1.reg, (uint8)SCU_DMAIEN1_CH7IE_Pos, (uint8)SCU_DMAIEN1_CH7IE_Msk, 0u);
}

/** \brief enables DMA Channel 11 Interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the DMA Channel 11 Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   DMA_CH11_Int_En();
 *   if ((uint8)SCU->DMAIRC1.bit.CH8 == (uint8)1)
 *   {
 *     DMA_CH8_CALLBACK();
 *     DMA_CH11_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup dma_api
 */
INLINE void DMA_CH11_Int_En(void)
{
  Field_Mod8(&SCU->DMAIEN1.reg, (uint8)SCU_DMAIEN1_CH8IE_Pos, (uint8)SCU_DMAIEN1_CH8IE_Msk, 1u);
}

/** \brief disables DMA Channel 11 Interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the DMA Channel 11 Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   DMA_CH11_Int_En();
 *   if ((uint8)SCU->DMAIRC1.bit.CH8 == (uint8)1)
 *   {
 *     DMA_CH8_CALLBACK();
 *     DMA_CH11_Int_Clr();
 *   }
 *   DMA_CH11_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup dma_api
 */
INLINE void DMA_CH11_Int_Dis(void)
{
  Field_Mod8(&SCU->DMAIEN1.reg, (uint8)SCU_DMAIEN1_CH8IE_Pos, (uint8)SCU_DMAIEN1_CH8IE_Msk, 0u);
}

/** \brief enables DMA Channel 12 Interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the DMA Channel 12 Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   DMA_CH12_Int_En();
 *   if ((uint8)SCU->DMAIRC2.bit.GPT12 == (uint8)1)
 *   {
 *     DMA_GPT12E_CALLBACK();
 *     DMA_CH12_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup dma_api
 */
INLINE void DMA_CH12_Int_En(void)
{
  Field_Mod8(&SCU->DMAIEN2.reg, (uint8)SCU_DMAIEN2_GPT12IE_Pos, (uint8)SCU_DMAIEN2_GPT12IE_Msk, 1u);
}

/** \brief disables DMA Channel 12 Interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the DMA Channel 12 Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   DMA_CH12_Int_En();
 *   if ((uint8)SCU->DMAIRC2.bit.GPT12 == (uint8)1)
 *   {
 *     DMA_GPT12E_CALLBACK();
 *     DMA_CH12_Int_Clr();
 *   }
 *   DMA_CH12_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup dma_api
 */
INLINE void DMA_CH12_Int_Dis(void)
{
  Field_Mod8(&SCU->DMAIEN2.reg, (uint8)SCU_DMAIEN2_GPT12IE_Pos, (uint8)SCU_DMAIEN2_GPT12IE_Msk, 0u);
}

#if defined TLE9879_2QXA40 || defined TLE9872_2QXW40
/** \brief enables DMA Channel 13 Interrupt.
 * \note for TLE9879-2QXA40 only
 *
 * \brief <b>Example</b><br>
 * \brief This example clears the DMA Channel 13 Interrupt flag when its Status is equal to 1.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   DMA_CH13_Int_En();
 *   if ((uint8)SCU->DMAIRC2.bit.SDADC == (uint8)1)
 *   {
 *     DMA_CH13_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup dma_api
 */
INLINE void DMA_CH13_Int_En(void)
{
  Field_Mod8(&SCU->DMAIEN2.reg, (uint8)SCU_DMAIEN2_SDADCIE_Pos, (uint8)SCU_DMAIEN2_SDADCIE_Msk, 1u);
}

/** \brief disables DMA Channel 13 Interrupt.
 * \note for TLE9879-2QXA40 only
 *
 * \brief <b>Example</b><br>
 * \brief This example clears the DMA Channel 13 Interrupt flag when its Status is equal to 1.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   DMA_CH13_Int_En();
 *   if ((uint8)SCU->DMAIRC2.bit.SDADC == (uint8)1)
 *   {
 *     DMA_CH13_Int_Clr();
 *   }
 *   DMA_CH13_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup dma_api
 */
INLINE void DMA_CH13_Int_Dis(void)
{
  Field_Mod8(&SCU->DMAIEN2.reg, (uint8)SCU_DMAIEN2_SDADCIE_Pos, (uint8)SCU_DMAIEN2_SDADCIE_Msk, 0u);
}
#endif /* TLE9879_2QXA40 || defined TLE9872_2QXW40 */

/** \brief points to the base address of the primary data structure.
 *
 * \param mask_ch DMA channel Mask
 *
 * \brief <b>Example</b><br>
 * \brief This example points to the base address of Channel 0.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   DMA_Master_En();
 *   DMA_Primary_Struct_Set(DMA_MASK_CH0);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup dma_api
 */
INLINE void DMA_Primary_Struct_Set(uint32 mask_ch)
{
  Field_Mod32(&DMA->CTRL_BASE_PTR.reg, DMA_CTRL_BASE_PTR_CTRL_BASE_PTR_Pos, DMA_CTRL_BASE_PTR_CTRL_BASE_PTR_Msk, mask_ch);
}

/** \brief enables DMA Channels.
 *
 * \param mask_ch DMA channel Mask
 *
 * \brief <b>Example</b><br>
 * \brief This example enables DMA Channel 0.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   DMA_Master_En();
 *   DMA_Channel_Enable_Set(DMA_MASK_CH0);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup dma_api
 */
INLINE void DMA_Channel_Enable_Set(uint32 mask_ch)
{
  Field_Mod32(&DMA->CHNL_ENABLE_SET.reg, DMA_CHNL_ENABLE_SET_CHNL_ENABLE_SET_Pos, DMA_CHNL_ENABLE_SET_CHNL_ENABLE_SET_Msk, mask_ch);
}

/** \brief Set software request for DMA Channels.
 *
 * \param mask_ch DMA channel Mask
 *
 * \brief <b>Example</b><br>
 * \brief This example enables DMA Channel 0.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   DMA_Master_En();
 *   DMA_Software_Request_Set(DMA_MASK_CH0);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup dma_api
 */
INLINE void DMA_Software_Request_Set(uint32 mask_ch)
{
  Field_Mod32(&DMA->CHNL_SW_REQUEST.reg, DMA_CHNL_SW_REQUEST_CHNL_SW_REQUEST_Pos, DMA_CHNL_SW_REQUEST_CHNL_SW_REQUEST_Msk, mask_ch);
}

/** \brief selects the primary data structure for the corresponding DMA channel.
 *
 * \param mask_ch DMA channel Mask
 *
 * \brief <b>Example</b><br>
 * \brief This example selects the primary data structure for DMA channel 0.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   DMA_Master_En();
 *   DMA_Primary_Struct_Usage_Set(DMA_MASK_CH0);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup dma_api
 */
INLINE void DMA_Primary_Struct_Usage_Set(uint32 mask_ch)
{
  Field_Mod32(&DMA->CHNL_PRI_ALT_CLR.reg, DMA_CHNL_PRI_ALT_CLR_CHNL_PRI_ALT_CLR_Pos, DMA_CHNL_PRI_ALT_CLR_CHNL_PRI_ALT_CLR_Msk, mask_ch);
}

/** \brief selects the alternate data structure for the corresponding DMA channel.
 *
 * \param mask_ch DMA channel Mask
 *
 * \brief <b>Example</b><br>
 * \brief This example selects the alternate data structure for DMA channel 0.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   DMA_Master_En();
 *   DMA_Alternate_Struct_Usage_Set(DMA_MASK_CH0);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup dma_api
 */
INLINE void DMA_Alternate_Struct_Usage_Set(uint32 mask_ch)
{
  Field_Mod32(&DMA->CHNL_PRI_ALT_SET.reg, DMA_CHNL_PRI_ALT_SET_CHNL_PRI_ALT_SET_Pos, DMA_CHNL_PRI_ALT_SET_CHNL_PRI_ALT_SET_Msk, mask_ch);
}

/** \brief This function returns the address inside the alternate structure in RAM for a given DMA channel.
 *
 * \param DMA_Ch DMA channel number
 * \return uint32 32bit address to entry inside alternate structure
 *
 * \ingroup dma_api
 */
INLINE uint32 DMA_CHx_Entry_Alt(uint8 DMA_Ch)
{
  return ( (uint32)(DMA->ALT_CTRL_BASE_PTR.reg + (DMA_Ch * sizeof(TDMA_Entry))) );
}

/** \brief This function returns the address inside the primary structure in RAM for a given DMA channel.
 *
 * \param DMA_Ch DMA channel number
 * \return uint32 32bit address to entry inside primary structure
 *
 * \ingroup dma_api
 */
INLINE uint32 DMA_CHx_Entry_Pri(uint8 DMA_Ch)
{
  return ( (uint32)(DMA->CTRL_BASE_PTR.reg + (DMA_Ch * sizeof(TDMA_Entry))) );
}

/*******************************************************************************
**                        Global Function Declarations                        **
*******************************************************************************/
#if (DMA_XML_VERSION >= 10200)

/** \brief Initializes the DMA structure in RAM and SFRs based on the Config Wizard for MOTIX MCU configuration
 *  \note This function violates [MISRA Rule 45], [MISRA Rule 52], [MISRA Rule 85]
 * \ingroup dma_api
 */
void DMA_Init(void);

/** \brief Sets up the desired DMA channel in the primary structure in RAM.
 *  \note This function violates [MISRA Rule 45]
 *
 * \param DMA_ChIdx DMA channel to be set up
 * \param addr_src address pointing to the source location
 * \param addr_dst address pointing to the destination location
 * \param trans_cnt number of transfers
 * \param datawidth data width for each transfer, see \link TDMA_Transfer_Size \endlink
 * \param increment incrementing scheme used for the transfer, see \link TDMA_Increment_Mode \endlink
 *
 * \brief <b>Example</b><br>
 * \brief This example transfers the result of ADC1.Ch4 into a local variable once the ADC1.Ch4 conversion is done.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   uint16 adc_val;
 *
 *   //setup DMA channel 8 to transfer ADC1.Ch4 result into local variable
 *   DMA_Setup_Channel(DMA_CH8, (uint32)&ADC1->RES_OUT4.reg, (uint32)&adc_val, 1, DMA_16Bit_Transfer, DMA_No_Inc);
 *
 *   //arm DMA channel 8
 *   DMA_Channel_Enable_Set(DMA_MASK_CH8);
 *
 *   //enable DMA
 *   DMA_Master_En();
 *
 *   //start ADC1.Ch4 conversion
 *   ADC1_SetSocSwMode(ADC1_CH4);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup dma_api
 */
void DMA_Setup_Channel(uint32 DMA_ChIdx, uint32 addr_src, uint32 addr_dst,
                       uint32 trans_cnt, TDMA_Transfer_Size datawidth, TDMA_Increment_Mode increment);


/** \brief Resets the primary structure in RAM for a given channel and rearms it.
 *  \note This function violates [MISRA Rule 45]
 *
 * \param DMA_ChIdx DMA channel to be set up
 * \param trans_cnt number of transfers
 *
 * \brief <b>Example</b><br>
 * \brief This example transfers the result of ADC1.Ch4 into a local variable, inside the interrupt service callback the DMA channel 8 gets reset.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   uint16 adc_val;
 *
 *   //setup DMA channel 8 to transfer ADC1.Ch4 result into local variable
 *   DMA_Setup_Channel(DMA_CH8, (uint32)&ADC1->RES_OUT4.reg, (uint32)&adc_val, 1, DMA_16Bit_Transfer, DMA_No_Inc);
 *
 *   //arm DMA channel 8
 *   DMA_Channel_Enable_Set(DMA_MASK_CH8);
 *
 *   //enable DMA
 *   DMA_Master_En();
 *
 *   //start ADC1.Ch4 conversion
 *   ADC1_SetSocSwMode(ADC1_CH4);
 * }
 *
 * void DMA_Ch8_ISR(void)
 * {
 *   //reset channel parameter and rearm channel
 *   DMA_Reset_Channel(DMA_CH8, 1);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup dma_api
 */
void DMA_Reset_Channel(uint32 DMA_ChIdx, uint32 trans_cnt);

/** \brief Sets up a task to be used with memory scatter-gather mode.
 * \brief The DMA scather-gather mode can be used to perform multiple but different DMA transfers initiated with one trigger.
 * \brief The last task can be used to self-arm this scatter-gather transfer again.
 * \brief This function can be used to define the last, self-arming task for the scather-gather mode.
 *
 * \param entry pointer to the task
 * \param DMA_Ch the DMA channel for with the task is setup
 * \param Task_List pointer to the task list to be executed with this DMA transfer
 * \param NoOfTask number of tasks defined in the task list
 *
 * \return pointer to the task
 *
 * \brief <b>Example</b><br>
 * \brief This example performs an endless scatter-gather transfer and toggles P0.1.
 * ~~~~~~~~~~~~~~~{.c}
 * #define no_of_tasks 4+1
 * TDMA_Entry MainTask_Ch0;
 * TDMA_Entry Tasks_Ch0[no_of_tasks];
 * uint8 lport_p01_high = 2;
 * uint8 lport_p01_low  = 0;
 *
 * void Example_Function(void)
 * {
 *   //initializes the primary structure task (MainTask_Ch0) to be used to reset the scatter-gather sequence
 *   DMA_Task_SctGth_Set(&MainTask_Ch0, DMA_CH0, &Tasks_Ch0[0], DMA_CH0_TASK_NoOfTasks);
 *   //initializes the task list 0
 *   //tasks[3..0] are the tasks actually doing some real work, here causing P0.1 to toggle
 *   DMA_Task_Set(&Tasks_Ch0[0], DMA_Cycle_Type_MemSctGthAlt, 0, (uint32)&lport_p01_high, (uint32)&PORT->P0_DATA.reg,         1, DMA_8Bit_Transfer, DMA_No_Inc);
 *   DMA_Task_Set(&Tasks_Ch0[1], DMA_Cycle_Type_MemSctGthAlt, 0, (uint32)&lport_p01_low,  (uint32)&PORT->P0_DATA.reg,         1, DMA_8Bit_Transfer, DMA_No_Inc);
 *   DMA_Task_Set(&Tasks_Ch0[2], DMA_Cycle_Type_MemSctGthAlt, 0, (uint32)&lport_p01_high, (uint32)&PORT->P0_DATA.reg,         1, DMA_8Bit_Transfer, DMA_No_Inc);
 *   DMA_Task_Set(&Tasks_Ch0[3], DMA_Cycle_Type_MemSctGthAlt, 0, (uint32)&lport_p01_low,  (uint32)&PORT->P0_DATA.reg,         1, DMA_8Bit_Transfer, DMA_No_Inc);
 *   //tasks[4] are used to reset Channel1, the fast that the last task is NOT of type 'DMA_Cycle_Type_Basic' keeps the scatter-gather running for ever
 *   DMA_Task_Set(&Tasks_Ch0[4], DMA_Cycle_Type_MemSctGthAlt, 2, (uint32)&MainTask_Ch0,   ui32_DMA_CHx_Entry_Pri(DMA_CH0),    4, DMA_32Bit_Transfer, DMA_Src_Dst_Inc);
 *   //preloads the primary structure with the task list for Channel0
 *   DMA_Channel_MemSctGth_Set(DMA_CH0, &Tasks_Ch0[0], DMA_CH0_TASK_NoOfTasks);
 *   //enable DMA Channel0
 *   DMA_Channel_Enable_Set(DMA_MASK_CH0);
 *   //enable DMA master
 *   DMA_Master_En();
 *   //trigger DMA Channel0 by software
 *   DMA_Software_Request_Set(DMA_MASK_CH0);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup drv_api
 */
TDMA_Entry *DMA_Task_SctGth_Set(TDMA_Entry *entry, uint8 DMA_Ch, TDMA_Entry *Task_List, uint32 NoOfTask);

/** \brief Sets up a channel to operate in Memory Scatter-Gather mode on a given task list.
 *  \note This function violates [MISRA Rule 45]
 *
 * \param DMA_ChIdx DMA channel to be set up
 * \param Task_List points to the task structure defined in RAM, see \link DMA_Task_Set \endlink
 * \param NoOfTasks number of tasks in the Task_List
 *
 * \brief <b>Example</b><br>
 * \brief This example transfers the result of ADC1.Ch4 into a local variable once the ADC1.Ch4 conversion is done.
 * ~~~~~~~~~~~~~~~{.c}
 * #define no_of_tasks 2
 * TDMA_Entry tasks[no_of_tasks];
 * static uint32 data0, data1;
 * static uint32 data2, data3;
 *
 * void Example_Function(void)
 * {
 *   // tasks[0] copies data0 to data1
 *   data0 = 0x12345678;
 *   data1 = 0;
 *   // tasks[1] copies data2 to data3
 *   data2 = 0xABCD;
 *   data3 = 0;
 *
 *   DMA_Task_Set(&tasks[0], DMA_Cycle_Type_MemSctGthAlt, 0, (uint32)&data0, (uint32)&data1, 1, DMA_32Bit_Transfer, DMA_No_Inc);
 *   DMA_Task_Set(&tasks[1], DMA_Cycle_Type_Basic,        0, (uint32)&data2, (uint32)&data3, 1, DMA_16Bit_Transfer, DMA_No_Inc);
 *
 *   DMA_Channel_MemSctGth_Set(DMA_CH8, &tasks[0], no_of_tasks);
 *
 *   //arm DMA channel 8
 *   DMA_Channel_Enable_Set(DMA_MASK_CH8);
 *
 *   //enable DMA
 *   DMA_Master_En();
 *
 *   ADC1_SetSocSwMode(ADC1_CH4);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup dma_api
 */
void DMA_Channel_MemSctGth_Set(uint32 DMA_ChIdx, TDMA_Entry *Task_List, uint32 NoOfTasks);


/** \brief Sets up a channel to operate in Peripheral Scatter-Gather mode on a given task list.
 *  \note This function violates [MISRA Rule 45]
 *
 * \param DMA_ChIdx DMA channel to be set up
 * \param Task_List points to the task structure defined in RAM, see \link DMA_Task_Set \endlink
 * \param NoOfTasks number of tasks in the Task_List
 *
 * \brief <b>Example</b><br>
 * \brief This example transfers the four SPI values from RAM to SSC1.
 * ~~~~~~~~~~~~~~~{.c}
 * #define no_of_tasks 4
 * TDMA_Entry tasks[no_of_tasks];
 * #define no_of_spi_trans 4
 * uint16 spi_data[no_of_spi_trans] = {0xAAAA, 0x5555, 0xCCCC, 0x3333};
 *
 * void Example_Function(void)
 * {
 *   //setup tasks for SPI transfer
 *   DMA_Task_Set(&tasks[0], DMA_Cycle_Type_PerSctGthAlt, 0, (uint32)&spi_data[0], (uint32)&SSC1->TB.reg, 1, DMA_16Bit_Transfer, DMA_No_Inc);
 *   DMA_Task_Set(&tasks[1], DMA_Cycle_Type_PerSctGthAlt, 0, (uint32)&spi_data[1], (uint32)&SSC1->TB.reg, 1, DMA_16Bit_Transfer, DMA_No_Inc);
 *   DMA_Task_Set(&tasks[2], DMA_Cycle_Type_PerSctGthAlt, 0, (uint32)&spi_data[2], (uint32)&SSC1->TB.reg, 1, DMA_16Bit_Transfer, DMA_No_Inc);
 *   DMA_Task_Set(&tasks[3], DMA_Cycle_Type_Basic,        0, (uint32)&spi_data[3], (uint32)&SSC1->TB.reg, 1, DMA_16Bit_Transfer, DMA_No_Inc);
 *
 *   //initialize DMA.Ch2 to tasks list
 *   DMA_Channel_PerSctGth_Set(DMA_CH2, &tasks[0], no_of_tasks);
 *
 *   //arm DMA channel 2
 *   DMA_Channel_Enable_Set(DMA_MASK_CH2);
 *
 *   //enable DMA
 *   DMA_Master_En();
 *
 *   //trigger DMA.Ch2 by software request
 *   DMA_Software_Request_Set(DMA_MASK_CH2);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup dma_api
 */
void DMA_Channel_PerSctGth_Set(uint32 DMA_ChIdx, TDMA_Entry *Task_List, uint32 NoOfTasks);

/** \brief Sets up a task to be used in the Scatter-Gather modes.
 *
 * \param entry pointer to the task structure \link TDMA_Entry \endlink
 * \param cycle_type defines the type of DMA transfer to be performed, see \link TDMA_Cycle_Types \endlink
 * \param arb_rate arbitration rate, defines after how many DMA transfer it rearbitrates, 2^arb_rate
 * \param addr_src address pointing to the source location
 * \param addr_dst address pointing to the destination location
 * \param trans_cnt number of transfers
 * \param datawidth data width for each transfer, see \link TDMA_Transfer_Size \endlink
 * \param increment incrementing scheme used for the transfer, see \link TDMA_Increment_Mode \endlink
 *
 * \brief <b>Example</b><br>
 * \brief This example transfers the four SPI values from RAM to SSC1.
 * ~~~~~~~~~~~~~~~{.c}
 * #define no_of_tasks 4
 * TDMA_Entry tasks[no_of_tasks];
 * #define no_of_spi_trans 4
 * uint16 spi_data[no_of_spi_trans] = {0xAAAA, 0x5555, 0xCCCC, 0x3333};
 *
 * void Example_Function(void)
 * {
 *   //setup tasks for SPI transfer
 *   DMA_Task_Set(&tasks[0], DMA_Cycle_Type_PerSctGthAlt, 0, (uint32)&spi_data[0], (uint32)&SSC1->TB.reg, 1, DMA_16Bit_Transfer, DMA_No_Inc);
 *   DMA_Task_Set(&tasks[1], DMA_Cycle_Type_PerSctGthAlt, 0, (uint32)&spi_data[1], (uint32)&SSC1->TB.reg, 1, DMA_16Bit_Transfer, DMA_No_Inc);
 *   DMA_Task_Set(&tasks[2], DMA_Cycle_Type_PerSctGthAlt, 0, (uint32)&spi_data[2], (uint32)&SSC1->TB.reg, 1, DMA_16Bit_Transfer, DMA_No_Inc);
 *   DMA_Task_Set(&tasks[3], DMA_Cycle_Type_Basic,        0, (uint32)&spi_data[3], (uint32)&SSC1->TB.reg, 1, DMA_16Bit_Transfer, DMA_No_Inc);
 *
 *   //initialize DMA.Ch2 to tasks list
 *   DMA_Channel_PerSctGth_Set(DMA_CH2, &tasks[0], no_of_tasks);
 *
 *   //arm DMA channel 2
 *   DMA_Channel_Enable_Set(DMA_MASK_CH2);
 *
 *   //enable DMA
 *   DMA_Master_En();
 *
 *   //trigger DMA.Ch2 by software request
 *   DMA_Software_Request_Set(DMA_MASK_CH2);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup dma_api
 */
TDMA_Entry *DMA_Task_Set(TDMA_Entry *entry, TDMA_Cycle_Types cycle_type, uint8 arb_rate, uint32 addr_src, uint32 addr_dst,
                         uint32 trans_cnt, TDMA_Transfer_Size datawidth, TDMA_Increment_Mode increment);

/** \brief Enabled the DMA master.
 *
 * \brief <b>Example</b><br>
 * \brief This example transfers the result of ADC1.Ch4 into a local variable once the ADC1.Ch4 conversion is done.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   uint16 adc_val;
 *
 *   //setup DMA channel 8 to transfer ADC1.Ch4 result into local variable
 *   DMA_Setup_Channel(DMA_CH8, (uint32)&ADC1->RES_OUT4.reg, (uint32)&adc_val, 1, DMA_16Bit_Transfer, DMA_No_Inc);
 *
 *   //arm DMA channel 8
 *   DMA_Channel_Enable_Set(DMA_MASK_CH8);
 *
 *   //enable DMA
 *   DMA_Master_En();
 *
 *   //start ADC1.Ch4 conversion
 *   ADC1_SetSocSwMode(ADC1_CH4);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup dma_api
 */
INLINE void DMA_Master_En(void);

/*******************************************************************************
**                     Global Inline Function Definitions                     **
*******************************************************************************/
INLINE void DMA_Master_En(void)
{
  /* arm the DMA */
  DMA->CFG.bit.MASTER_ENABLE = 1u;
}
#else
#error "use IFXConfigWizard XML Version V1.2.0 or greater"
#endif

#endif
