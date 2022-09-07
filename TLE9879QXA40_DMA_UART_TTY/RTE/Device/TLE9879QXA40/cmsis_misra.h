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
 * \file     cmsis_misra.h
 *
 * \brief    CMSIS Intrinsics access
 *
 * \version  V0.1.6
 * \date     28. Feb 2022
 *
 * \note This file violates [MISRA Rule 20] and [MISRA Rule 71]
 */

/*******************************************************************************
**                             Author(s) Identity                             **
********************************************************************************
** Initials     Name                                                          **
** ---------------------------------------------------------------------------**
** DM           Daniel Mysliwitz                                              **
** JO           Julia Ott                                                     **
** BG           Blandine Guillot                                              **
*******************************************************************************/

/*******************************************************************************
**                          Revision Control History                          **
********************************************************************************
** V0.1.0: 2018-06-13, DM:   Initial version                                  **
** V0.1.1: 2019-04-18, JO:   Modified CMSIS_Irq_Dis to be ARM GCC compliant   **
** V0.1.2: 2020-04-15, BG:   Updated revision history                         **
** V0.1.3: 2020-04-17, BG:   Added inline function CMSIS_SEV()                **
** V0.1.4: 2020-07-21, BG:   EP-439: Formatted .h/.c files                    **
** V0.1.5: 2022-02-17, JO:   EP-1040: Corrected CMSIS_Irq_Dis (for ARMCC v6)  **
** V0.1.6: 2022-02-28, JO:   EP-936: Updated copyright and branding           **
*******************************************************************************/

#ifndef _CMSIS_MISRA_H
#define _CMSIS_MISRA_H

/*******************************************************************************
**                                  Includes                                  **
*******************************************************************************/
#include "types.h"
#include "core_cm3.h"

/*******************************************************************************
**                           Unit Test Declarations                           **
*******************************************************************************/
#if defined(TESTING) || defined(UNIT_TESTING_LV2)

sint32 CMSIS_Irq_Dis(void);
void CMSIS_Irq_En(void);
void CMSIS_NOP(void);
void CMSIS_WFE(void);
void CMSIS_SEV(void);

#else

/*******************************************************************************
**                        Global Function Declarations                        **
*******************************************************************************/

/** \brief Access to the CMSIS intrinsic __disable_irq().
 *  \note This function violates [MISRA Rule 20] and [MISRA Rule 71]
 */
INLINE void CMSIS_Irq_Dis(void);

/** \brief Access to the CMSIS intrinsic __enable_irq().
 *  \note This function violates [MISRA Rule 20] and [MISRA Rule 71]
 */
INLINE void CMSIS_Irq_En(void);

/** \brief Access to the CMSIS intrinsic __NOP().
 *  \note This function violates [MISRA Rule 20] and [MISRA Rule 71]
 */
INLINE void CMSIS_NOP(void);

/** \brief Access to the CMSIS intrinsic __WFE().
 *  \note This function violates [MISRA Rule 20] and [MISRA Rule 71]
 */
INLINE void CMSIS_WFE(void);

/** \brief Access to the CMSIS intrinsic __SEV().
 *  \note This function violates [MISRA Rule 20] and [MISRA Rule 71]
 */
INLINE void CMSIS_SEV(void);


/*******************************************************************************
**                         Global Function Definitions                        **
*******************************************************************************/

INLINE void CMSIS_Irq_Dis(void)
{
  /* violation: Symbol '__disable_irq' undeclared, assumed to return int [MISRA Rule 20], [MISRA Rule 71]*/
  /* violation: call to function '__disable_irq()' not made in the presence of a prototype [MISRA Rule 71] */
  (void)__disable_irq();
}

INLINE void CMSIS_Irq_En(void)
{
  /* violation: Symbol '__enable_irq' undeclared, assumed to return int [MISRA Rule 20], [MISRA Rule 71]*/
  /* violation: call to function '__enable_irq()' not made in the presence of a prototype [MISRA Rule 71] */
  __enable_irq();
}

INLINE void CMSIS_NOP(void)
{
  /* violation: Symbol '__nop' undeclared, assumed to return int [MISRA Rule 20], [MISRA Rule 71]*/
  /* violation: call to function '__nop()' not made in the presence of a prototype [MISRA Rule 71] */
  __NOP();
}

INLINE void CMSIS_WFE(void)
{
  /* violation: Symbol '__wfe' undeclared, assumed to return int [MISRA Rule 20], [MISRA Rule 71]*/
  /* violation: call to function '__wfe()' not made in the presence of a prototype [MISRA Rule 71] */
  __WFE();
}

INLINE void CMSIS_SEV(void)
{
  /* violation: Symbol '__sev' undeclared, assumed to return int [MISRA Rule 20], [MISRA Rule 71]*/
  /* violation: call to function '__sev()' not made in the presence of a prototype [MISRA Rule 71] */
  __SEV();
}

#endif


#endif /*_CMSIS_MISRA_H*/
