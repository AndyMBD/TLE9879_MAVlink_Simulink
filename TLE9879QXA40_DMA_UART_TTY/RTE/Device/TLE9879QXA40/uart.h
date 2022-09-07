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
 * \file     uart.h
 *
 * \brief    UART low level access library
 *
 * \version  V0.2.3
 * \date     28. Feb 2022
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
** V0.1.0: 2014-05-11, DM:   Initial version                                  **
** V0.1.1: 2014-07-22, DM:   BGL baudrate calculation fixed                   **
** V0.1.2: 2015-02-10, DM:   Individual header file added                     **
** V0.1.3: 2015-07-15, DM:   STDIN/STDOUT function added                      **
** V0.1.4: 2017-02-15, DM:   GetByte, isByteReceived and isByteTransmitted    **
**                           inline functions added                           **
**                           Baudrate_Set function added                      **
** V0.1.5: 2017-10-20, DM:   MISRA 2012 compliance, the following PC-Lint     **
**                           rules are globally deactivated:                  **
**                           - Info 793: ANSI/ISO limit of 6 'significant     **
**                             characters in an external identifier           **
**                           - Info 835: A zero has been given as right       **
**                             argument to operator                           **
**                           - Info 845: The left argument to operator '&'    **
**                             is certain to be 0                             **
** V0.1.6: 2018-02-02, DM:   BaudRate_Set function corrected                  **
** V0.1.7: 2018-03-20, DM:   Preprocessor checks modified to allow only one   **
**                           UART to be STDIN/STDOUT at a time                **
** V0.1.8: 2018-11-27, JO:   Doxygen update                                   **
**                           Moved revision history from uart.c to uart.h     **
**                           Added ranges for UART1_BaudRate_Set and          **
**                           UART2_BaudRate_Set                               **
**                           Adapted the implementation of stdout_putchar     **
**                           and stdin_getchar for UART1 and UART2 so that    **
**                           they follow the same procedure                   **
**                           UART1_BaudRate_Value_Set(),                      **
**                           UART2_BaudRate_Value_Set() functions added       **
** V0.1.9: 2019-09-11, JO:   Corrected ranges for UART1_BaudRate_Set and      **
**                           UART2_BaudRate_Set                               **
** V0.2.0: 2020-04-15, BG:   Updated revision history format                  **
** V0.2.1: 2020-07-13, JO:   EP-431: remove ARMCC v6 Compiler warnings        **
**                           - added static to definition of uart1 and uart2  **
** V0.2.2: 2020-07-21, BG:   EP-439: Formatted .h/.c files                    **
** V0.2.3: 2022-02-28, JO:   EP-936: Updated copyright and branding           **
*******************************************************************************/

#ifndef UART_H
#define UART_H

/*******************************************************************************
**                                  Includes                                  **
*******************************************************************************/
#include "tle987x.h"
#include "types.h"
#include "uart_defines.h"
#include "sfr_access.h"

/*******************************************************************************
**                           Global Type Definitions                          **
*******************************************************************************/
/** \struct TUart
 *  \brief This struct lists parameter (clock) of UART1/UART2.
 */
typedef struct
{
  uint32 clock;
} TUart;

/*******************************************************************************
**                     Global Inline Function Definitions                     **
*******************************************************************************/
/** \brief Writes the baudrate timer register (UART1).
 * \note Setting new Baud-rate value must be when BaudRateGen is disabled.
 *
 * \brief <b>Example</b><br>
 * \brief This example receives a Byte via UART1 (baud-rate is equal to 19200 when frequency is equal to 40MHz).
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint8 ch;
 *
 *     UART1_Receiver_En();
 *     UART1_BaudRateGen_Dis();
 *     UART1_BaudRate_Value_Set(0x1046);
 *     UART1_BaudRateGen_En();
 *     if (UART1_isByteReceived() == TRUE)
 *     {
 *       ch = UART1_Get_Byte();
 *     }
 *     UART1_Receiver_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup uart_api
 */
INLINE void UART1_BaudRate_Value_Set(uint16 br_val)
{
  Field_Wrt8all(&SCU->BGH1.reg, (uint8)(br_val >> 8u));
  Field_Wrt8all(&SCU->BGL1.reg, (uint8)(br_val & (uint16)0x00FF));
}

/** \brief disables Baud-rate generator (UART1).
 * \note Setting new Baud-rate value must be when BaudRateGen is disabled.
 *
 * \brief <b>Example</b><br>
 * \brief This example receives a Byte via UART1 (baud-rate is equal to 19200 when frequency is equal to 40MHz).
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint8 ch;
 *
 *     UART1_Receiver_En();
 *     UART1_BaudRateGen_Dis();
 *     UART1_BaudRate_Value_Set(0x1046);
 *     UART1_BaudRateGen_En();
 *     if (UART1_isByteReceived() == TRUE)
 *     {
 *       ch = UART1_Get_Byte();
 *     }
 *     UART1_Receiver_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup uart_api
 */
INLINE void UART1_BaudRateGen_Dis(void)
{
  Field_Mod8(&SCU->BCON1.reg, (uint8)SCU_BCON1_R_Pos, (uint8)SCU_BCON1_R_Msk, 0u);
}


/** \brief enables Baud-rate generator (UART1).
 * \note Setting new Baud-rate value must be when BaudRateGen is disabled.
 *
 * \brief <b>Example</b><br>
 * \brief This example receives a Byte via UART1 (baud-rate is equal to 19200 when frequency is equal to 40MHz).
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint8 ch;
 *
 *     UART1_Receiver_En();
 *     UART1_BaudRateGen_Dis();
 *     UART1_BaudRate_Value_Set(0x1046);
 *     UART1_BaudRateGen_En();
 *     if (UART1_isByteReceived() == TRUE)
 *     {
 *       ch = UART1_Get_Byte();
 *     }
 *     UART1_Receiver_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup uart_api
 */
INLINE void UART1_BaudRateGen_En(void)
{
  Field_Mod8(&SCU->BCON1.reg, (uint8)SCU_BCON1_R_Pos, (uint8)SCU_BCON1_R_Msk, 1u);
}


/** \brief Writes the baudrate timer register (UART2).
 * \note Setting new Baud-rate value must be when BaudRateGen is disabled.
 *
 * \brief <b>Example</b><br>
 * \brief This example receives a Byte via UART1 (baud-rate is equal to 19200 when frequency is equal to 40MHz).
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint8 ch;
 *
 *     UART2_Receiver_En();
 *     UART2_BaudRateGen_Dis();
 *     UART2_BaudRate_Value_Set(0x1046);
 *     UART2_BaudRateGen_En();
 *     if (UART2_isByteReceived() == TRUE)
 *     {
 *       ch = UART2_Get_Byte();
 *     }
 *     UART2_Receiver_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup uart_api
 */
INLINE void UART2_BaudRate_Value_Set(uint16 br_val)
{
  Field_Wrt8all(&SCU->BGH2.reg, (uint8)(br_val >> 8u));
  Field_Wrt8all(&SCU->BGL2.reg, (uint8)(br_val & (uint16)0x00FF));
}

/** \brief disables Baud-rate generator (UART2).
 * \note Setting new Baud-rate value must be when BaudRateGen is disabled.
 *
 * \brief <b>Example</b><br>
 * \brief This example receives a Byte via UART2 (baud-rate is equal to 19200 when frequency is equal to 40MHz).
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint8 ch;
 *
 *     UART2_Receiver_En();
 *     UART2_BaudRateGen_Dis();
 *     UART2_BaudRate_Value_Set(0x1046);
 *     UART2_BaudRateGen_En();
 *     if (UART2_isByteReceived() == TRUE)
 *     {
 *       ch = UART2_Get_Byte();
 *     }
 *     UART2_Receiver_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup uart_api
 */
INLINE void UART2_BaudRateGen_Dis(void)
{
  Field_Mod8(&SCU->BCON2.reg, (uint8)SCU_BCON2_R_Pos, (uint8)SCU_BCON2_R_Msk, 0u);
}

/** \brief enables Baud-rate generator (UART2).
 * \note Setting new Baud-rate value must be when BaudRateGen is disabled.
 *
 * \brief <b>Example</b><br>
 * \brief This example receives a Byte via UART2 (baud-rate is equal to 19200 when frequency is equal to 40MHz).
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint8 ch;
 *
 *     UART2_Receiver_En();
 *     UART2_BaudRateGen_Dis();
 *     UART2_BaudRate_Value_Set(0x1046);
 *     UART2_BaudRateGen_En();
 *     if (UART2_isByteReceived() == TRUE)
 *     {
 *       ch = UART2_Get_Byte();
 *     }
 *     UART2_Receiver_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup uart_api
 */
INLINE void UART2_BaudRateGen_En(void)
{
  Field_Mod8(&SCU->BCON2.reg, (uint8)SCU_BCON2_R_Pos, (uint8)SCU_BCON2_R_Msk, 1u);
}

/** \brief Sends a Byte via UART1.
 *
 * \param data Byte to send
 *
 * \brief <b>Example</b><br>
 * \brief This example sends "A" via UART1.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     UART1_BaudRate_Set(19200);
 *     if (UART1_isByteTransmitted() == TRUE)
 *     {
 *       UART1_TX_Int_Clr();
 *       UART1_Buffer_Set(0x41);
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup uart_api
 */
INLINE void UART1_Buffer_Set(uint8 data)
{
  Field_Wrt8(&UART1->SBUF.reg, (uint8)UART1_SBUF_VAL_Pos, (uint8)UART1_SBUF_VAL_Msk, data);
}

/** \brief Sends a Byte via UART2.
 *
 * \param data Byte to send
 *
 * \brief <b>Example</b><br>
 * \brief This example sends "A" via UART2.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     UART2_BaudRate_Set(19200);
 *     if (UART2_isByteTransmitted() == TRUE)
 *     {
 *       UART2_TX_Int_Clr();
 *       UART2_Buffer_Set(0x41);
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup uart_api
 */
INLINE void UART2_Buffer_Set(uint8 data)
{
  Field_Wrt8(&UART2->SBUF.reg, (uint8)UART2_SBUF_VAL_Pos, (uint8)UART2_SBUF_VAL_Msk, data);
}

/** \brief Reads UART1 Buffer.
 *
 * \return Received Byte
 *
 * \brief <b>Example</b><br>
 * \brief This example receives a Byte via UART1.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint8 ch;
 *
 *     UART1_Receiver_En();
 *     UART1_BaudRate_Set(19200);
 *     if (UART1_isByteReceived() == TRUE)
 *     {
 *       UART1_RX_Int_Clr();
 *       ch = UART1_Buffer_Get();
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup uart_api
 */
INLINE uint8 UART1_Buffer_Get(void)
{
  return (u8_Field_Rd8(&UART1->SBUF.reg, (uint8)UART1_SBUF_VAL_Pos, (uint8)UART1_SBUF_VAL_Msk));
}

/** \brief Reads UART2 Buffer.
 *
 * \return Received Byte
 *
 * \brief <b>Example</b><br>
 * \brief This example receives a Byte via UART2.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint8 ch;
 *
 *     UART2_Receiver_En();
 *     UART2_BaudRate_Set(19200);
 *     if (UART2_isByteReceived() == TRUE)
 *     {
 *       UART2_RX_Int_Clr();
 *       ch = UART2_Buffer_Get();
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup uart_api
 */
INLINE uint8 UART2_Buffer_Get(void)
{
  return (u8_Field_Rd8(&UART2->SBUF.reg, (uint8)UART2_SBUF_VAL_Pos, (uint8)UART2_SBUF_VAL_Msk));
}

/** \brief reads the receive interrupt flag of UART1.
 *
 * \return Receive Interrupt Flag Status
 *
 * \brief <b>Example</b><br>
 * \brief This example receives a Byte via UART1.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint8 ch;
 *
 *     UART1_Receiver_En();
 *     UART1_BaudRate_Set(19200);
 *     if (UART1_RX_Sts() == (uint8)1u)
 *     {
 *       ch = UART1_Get_Byte();
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup uart_api
 */
INLINE uint8 UART1_RX_Sts(void)
{
  return (u1_Field_Rd8(&UART1->SCON.reg, (uint8)UART1_SCON_RI_Pos, (uint8)UART1_SCON_RI_Msk));
}

/** \brief reads the transmit interrupt flag of UART1.
 *
 * \return Receive Interrupt Flag Status
 *
 * \brief <b>Example</b><br>
 * \brief This example receives a Byte via UART1.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint8 ch;
 *
 *     UART1_Receiver_En();
 *     UART1_BaudRate_Set(19200);
 *     if (UART1_RX_Sts() == (uint8)1u)
 *     {
 *       ch = UART1_Get_Byte();
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup uart_api
 */
INLINE uint8 UART1_TX_Sts(void)
{
  return (u1_Field_Rd8(&UART1->SCON.reg, (uint8)UART1_SCON_TI_Pos, (uint8)UART1_SCON_TI_Msk));
}

/** \brief reads the receive interrupt flag of UART2.
 *
 * \return Receive Interrupt Flag Status
 *
 * \brief <b>Example</b><br>
 * \brief This example receives a Byte via UART2.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint8 ch;
 *
 *     UART2_Receiver_En();
 *     UART2_BaudRate_Set(19200);
 *     if (UART2_RX_Sts() == (uint8)1u)
 *     {
 *       ch = UART2_Get_Byte();
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup uart_api
 */
INLINE uint8 UART2_RX_Sts(void)
{
  return (u1_Field_Rd8(&UART2->SCON.reg, (uint8)UART2_SCON_RI_Pos, (uint8)UART2_SCON_RI_Msk));
}

/** \brief reads the transmit interrupt flag of UART2.
 *
 * \return Transmit Interrupt Flag Status
 *
 * \brief <b>Example</b><br>
 * \brief This example sends "A" via UART2.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     UART2_BaudRate_Set(19200);
 *     if (UART2_TX_Sts() == (uint8)1u)
 *     {
 *       UART2_Send_Byte(0x41);
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup uart_api
 */
INLINE uint8 UART2_TX_Sts(void)
{
  return (u1_Field_Rd8(&UART2->SCON.reg, (uint8)UART2_SCON_TI_Pos, (uint8)UART2_SCON_TI_Msk));
}

/** \brief enables Receiver of Serial Port (UART1).
 *
 * \brief <b>Example</b><br>
 * \brief This example receives a Byte via UART1.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint8 ch;
 *
 *     UART1_Receiver_En();
 *     UART1_BaudRate_Set(19200);
 *     if (UART1_isByteReceived() == TRUE)
 *     {
 *       ch = UART1_Get_Byte();
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup uart_api
 */
INLINE void UART1_Receiver_En(void)
{
  Field_Mod8(&UART1->SCON.reg, (uint8)UART1_SCON_REN_Pos, (uint8)UART1_SCON_REN_Msk, 1u);
}

/** \brief disables Receiver of Serial Port (UART1).
 *
 * \brief <b>Example</b><br>
 * \brief This example receives a Byte via UART1.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint8 ch;
 *
 *     UART1_Receiver_En();
 *     UART1_BaudRate_Set(19200);
 *     if (UART1_isByteReceived() == TRUE)
 *     {
 *       ch = UART1_Get_Byte();
 *     }
 *     UART1_Receiver_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup uart_api
 */
INLINE void UART1_Receiver_Dis(void)
{
  Field_Mod8(&UART1->SCON.reg, (uint8)UART1_SCON_REN_Pos, (uint8)UART1_SCON_REN_Msk, 0u);
}

/** \brief enables Receiver of Serial Port (UART2).
 *
 * \brief <b>Example</b><br>
 * \brief This example receives a Byte via UART2.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint8 ch;
 *
 *     UART2_Receiver_En();
 *     UART2_BaudRate_Set(19200);
 *     if (UART2_isByteReceived() == TRUE)
 *     {
 *       ch = UART2_Get_Byte();
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup uart_api
 */
INLINE void UART2_Receiver_En(void)
{
  Field_Mod8(&UART2->SCON.reg, (uint8)UART2_SCON_REN_Pos, (uint8)UART2_SCON_REN_Msk, 1u);
}

/** \brief disables Receiver of Serial Port (UART2).
 *
 * \brief <b>Example</b><br>
 * \brief This example receives a Byte via UART2.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint8 ch;
 *
 *     UART2_Receiver_En();
 *     UART2_BaudRate_Set(19200);
 *     if (UART2_isByteReceived() == TRUE)
 *     {
 *       ch = UART2_Get_Byte();
 *     }
 *     UART2_Receiver_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup uart_api
 */
INLINE void UART2_Receiver_Dis(void)
{
  Field_Mod8(&UART2->SCON.reg, (uint8)UART2_SCON_REN_Pos, (uint8)UART2_SCON_REN_Msk, 0u);
}

/** \brief clears receive interrupt flag for UART1.
 *
 *
 * \brief <b>Example</b><br>
 * \brief This example receives a Byte via UART1.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint8 ch;
 *
 *     UART1_Receiver_En();
 *     UART1_BaudRate_Set(19200);
 *     if (UART1_isByteReceived() == TRUE)
 *     {
 *       ch = UART1_Buffer_Get();
 *       UART1_RX_Int_Clr();
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup uart_api
 */
INLINE void UART1_RX_Int_Clr(void)
{
  Field_Wrt8(&UART1->SCONCLR.reg, (uint8)UART1_SCONCLR_RICLR_Pos, (uint8)UART1_SCONCLR_RICLR_Msk, 1u);
}

/** \brief clears transmit interrupt flag of UART1.
 *
 * \brief <b>Example</b><br>
 * \brief This example sends "A" via UART1.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     UART1_BaudRate_Set(19200);
 *     if (UART1_isByteTransmitted() == TRUE)
 *     {
 *       UART1_Buffer_Set(0x41);
 *       UART1_TX_Int_Clr();
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup uart_api
 */
INLINE void UART1_TX_Int_Clr(void)
{
  Field_Wrt8(&UART1->SCONCLR.reg, (uint8)UART1_SCONCLR_TICLR_Pos, (uint8)UART1_SCONCLR_TICLR_Msk, 1u);
}

/** \brief clears receive interrupt flag of UART2.
 *
 * \brief <b>Example</b><br>
 * \brief This example receives a Byte via UART2.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint8 ch;
 *
 *     UART2_Receiver_En();
 *     UART2_BaudRate_Set(19200);
 *     if (UART2_isByteReceived() == TRUE)
 *     {
 *       ch = UART2_Buffer_Get();
 *       UART2_RX_Int_Clr();
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup uart_api
 */
INLINE void UART2_RX_Int_Clr(void)
{
  Field_Wrt8(&UART2->SCONCLR.reg, (uint8)UART2_SCONCLR_RICLR_Pos, (uint8)UART2_SCONCLR_RICLR_Msk, 1u);
}

/** \brief clears transmit interrupt flag of UART2.
 *
 * \brief <b>Example</b><br>
 * \brief This example sends "A" via UART2.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     UART2_BaudRate_Set(19200);
 *     if (UART2_isByteTransmitted() == TRUE)
 *     {
 *       UART2_Buffer_Set(0x41);
 *       UART2_TX_Int_Clr();
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup uart_api
 */
INLINE void UART2_TX_Int_Clr(void)
{
  Field_Wrt8(&UART2->SCONCLR.reg, (uint8)UART2_SCONCLR_TICLR_Pos, (uint8)UART2_SCONCLR_TICLR_Msk, 1u);
}

/* UART Interrupt Enable/Disable */
/** \brief enables receive interrupt of UART1.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the receive interrupt for UART1.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     UART1_RX_Int_En();
 *     if (UART1_RX_Sts() == (uint8)1u)
 *     {
 *       UART1_RX_CALLBACK();
 *       UART1_RX_Int_Clr();
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup uart_api
 */
INLINE void UART1_RX_Int_En(void)
{
  Field_Mod8(&SCU->MODIEN1.reg, (uint8)SCU_MODIEN1_RIEN1_Pos, (uint8)SCU_MODIEN1_RIEN1_Msk, 1u);
}

/** \brief disables receive interrupt of UART1.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the receive interrupt for UART1.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     UART1_RX_Int_En();
 *     if (UART1_RX_Sts() == (uint8)1u)
 *     {
 *       UART1_RX_CALLBACK();
 *       UART1_RX_Int_Clr();
 *     }
 *     UART1_RX_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup uart_api
 */
INLINE void UART1_RX_Int_Dis(void)
{
  Field_Mod8(&SCU->MODIEN1.reg, (uint8)SCU_MODIEN1_RIEN1_Pos, (uint8)SCU_MODIEN1_RIEN1_Msk, 0u);
}

/** \brief enables transmit interrupt of UART1.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the transmit interrupt for UART1.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     UART1_TX_Int_En();
 *     if (UART1_TX_Sts() == (uint8)1u)
 *     {
 *       UART1_TX_CALLBACK();
 *       UART1_TX_Int_Clr();
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup uart_api
 */
INLINE void UART1_TX_Int_En(void)
{
  Field_Mod8(&SCU->MODIEN1.reg, (uint8)SCU_MODIEN1_TIEN1_Pos, (uint8)SCU_MODIEN1_TIEN1_Msk, 1u);
}

/** \brief disables transmit interrupt of UART1.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the transmit interrupt for UART1.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     UART1_TX_Int_En();
 *     if (UART1_TX_Sts() == (uint8)1u)
 *     {
 *       UART1_TX_CALLBACK();
 *       UART1_TX_Int_Clr();
 *     }
 *     UART1_TX_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup uart_api
 */
INLINE void UART1_TX_Int_Dis(void)
{
  Field_Mod8(&SCU->MODIEN1.reg, (uint8)SCU_MODIEN1_TIEN1_Pos, (uint8)SCU_MODIEN1_TIEN1_Msk, 0u);
}

/** \brief enables receive interrupt of UART2.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the receive interrupt for UART2.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     UART2_RX_Int_En();
 *     if (UART2_RX_Sts() == (uint8)1u)
 *     {
 *       UART2_RX_CALLBACK();
 *       UART2_RX_Int_Clr();
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup uart_api
 */
INLINE void UART2_RX_Int_En(void)
{
  Field_Mod8(&SCU->MODIEN2.reg, (uint8)SCU_MODIEN2_RIEN2_Pos, (uint8)SCU_MODIEN2_RIEN2_Msk, 1u);
}

/** \brief disables receive interrupt of UART2.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the receive interrupt for UART2.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     UART2_RX_Int_En();
 *     if (UART2_RX_Sts() == (uint8)1u)
 *     {
 *       UART2_RX_CALLBACK();
 *       UART2_RX_Int_Clr();
 *     }
 *     UART2_RX_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup uart_api
 */
INLINE void UART2_RX_Int_Dis(void)
{
  Field_Mod8(&SCU->MODIEN2.reg, (uint8)SCU_MODIEN2_RIEN2_Pos, (uint8)SCU_MODIEN2_RIEN2_Msk, 0u);
}

/** \brief enables transmit interrupt of UART2.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the transmit interrupt for UART2.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     UART2_TX_Int_En();
 *     if (UART2_TX_Sts() == (uint8)1u)
 *     {
 *       UART2_TX_CALLBACK();
 *       UART2_TX_Int_Clr();
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup uart_api
 */
INLINE void UART2_TX_Int_En(void)
{
  Field_Mod8(&SCU->MODIEN2.reg, (uint8)SCU_MODIEN2_TIEN2_Pos, (uint8)SCU_MODIEN2_TIEN2_Msk, 1u);
}

/** \brief disables transmit interrupt of UART2.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the transmit interrupt for UART2.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     UART2_TX_Int_En();
 *     if (UART2_TX_Sts() == (uint8)1u)
 *     {
 *       UART2_TX_CALLBACK();
 *       UART2_TX_Int_Clr();
 *     }
 *     UART2_TX_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup uart_api
 */
INLINE void UART2_TX_Int_Dis(void)
{
  Field_Mod8(&SCU->MODIEN2.reg, (uint8)SCU_MODIEN2_TIEN2_Pos, (uint8)SCU_MODIEN2_TIEN2_Msk, 0u);
}

/*******************************************************************************
**                        Global Function Declarations                        **
*******************************************************************************/
/** \brief Initializes the UART1 module based on the Config Wizard for MOTIX MCU configuration
 *
 * \ingroup drv_api
 */
void UART1_Init(void);

/** \brief Initializes the UART2 module based on the Config Wizard for MOTIX MCU configuration
 *
 * \ingroup drv_api
 */
void UART2_Init(void);

/** \brief Sets the baudrate of UART1.
 *
* \param baudrate baudrate, e.g. 19200, or 115200; range: 1221 to 5000000 (a value out of this range will not be applied)
 *
 * \brief <b>Example</b><br>
 * \brief This example sets UART1 BAUDRATE to 19200.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     UART1_BaudRate_Set(19200);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup drv_api
 */
void UART1_BaudRate_Set(uint32 baudrate);

/** \brief Sets the baudrate of UART2.
 *
 * \param baudrate baudrate, e.g. 19200, or 115200; range: 1221 to 5000000 (a value out of this range will not be applied)
 *
 * \brief <b>Example</b><br>
 * \brief This example sets UART2 BAUDRATE to 19200.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     UART2_BaudRate_Set(19200);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup drv_api
 */
void UART2_BaudRate_Set(uint32 baudrate);

/*******************************************************************************
**                     Global Inline Function Declarations                    **
*******************************************************************************/
#if ((UART1_STD_EN == 1) || (UART2_STD_EN == 1))
  /** \brief Sends a character via UART1/2.
  *
  * \param[in] Char Character to send
  * \return Sent character
  *
  * \ingroup uart_api
  */
  sint32 stdout_putchar(sint32 Char);

  /** \brief Receives a character via UART1/2.
  *
  * \return Received character
  *
  * \ingroup uart_api
  */
  sint32 stdin_getchar(void);
  void ttywrch(int ch);
#endif /* ((UART1_STD_EN == 1) || (UART2_STD_EN == 1)) */


/*******************************************************************************
**                  Global Inline Static Function Definitions                 **
*******************************************************************************/
/** \brief clears the UART1 Transmit interrupt and sends a Byte via UART1.
 *
 * \param c Byte to send
 *
 * \brief <b>Example</b><br>
 * \brief This example sends "A" via UART1.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     UART1_BaudRate_Set(19200);
 *     if (UART1_isByteTransmitted() == TRUE)
 *     {
 *       UART1_Send_Byte(0x41);
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup uart_api
 */
INLINE void UART1_Send_Byte(uint8 c)
{
  UART1_TX_Int_Clr();
  UART1_Buffer_Set(c);
}

/** \brief Clears the UART1 receive interrupt and returns the UART1 buffer.
 *
 * \return Received Byte
 *
 * \brief <b>Example</b><br>
 * \brief This example receives a Byte via UART1.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint8 ch;
 *
 *     UART1_Receiver_En();
 *     UART1_BaudRate_Set(19200);
 *     if (UART1_isByteReceived() == TRUE)
 *     {
 *       ch = UART1_Get_Byte();
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup uart_api
 */
INLINE uint8 UART1_Get_Byte(void)
{
  UART1_RX_Int_Clr();
  return (UART1_Buffer_Get());
}

/** \brief checks if UART1 has received Byte or not.
 *
 * \retval TRUE a byte was received
 * \retval FALSE no byte was received
 *
 * \brief <b>Example</b><br>
 * \brief This example receives a Byte via UART1.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint8 ch;
 *
 *     UART1_Receiver_En();
 *     UART1_BaudRate_Set(19200);
 *     if (UART1_isByteReceived() == TRUE)
 *     {
 *       ch = UART1_Get_Byte();
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup uart_api
 */
INLINE bool UART1_isByteReceived(void)
{
  bool bRes = false;

  if (UART1_RX_Sts() == (uint8)1)
  {
    bRes = true;
  }

  return (bRes);
}

/** \brief checks if UART1 has transmitted a Byte or not.
 *
 * \retval TRUE a byte was transmitted
 * \retval FALSE no byte was transmitted
 *
 * \brief <b>Example</b><br>
 * \brief This example sends "A" via UART1.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     UART1_BaudRate_Set(19200);
 *     if (UART1_isByteTransmitted() == TRUE)
 *     {
 *       UART1_Send_Byte(0x41);
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup uart_api
 */
INLINE bool UART1_isByteTransmitted(void)
{
  bool bRes = false;

  if (UART1_TX_Sts() == (uint8)1)
  {
    bRes = true;
  }

  return (bRes);
}

/** \brief clears the UART2 Transmit interrupt and sends a Byte via UART2.
 *
 * \param c Byte to send
 *
 * \brief <b>Example</b><br>
 * \brief This example sends "A" via UART2.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     UART2_BaudRate_Set(19200);
 *     if (UART2_isByteTransmitted() == TRUE)
 *     {
 *       UART2_Send_Byte(0x41);
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup uart_api
 */
INLINE void UART2_Send_Byte(uint8 c)
{
  UART2_TX_Int_Clr();
  UART2_Buffer_Set(c);
}

/** \brief Clears the UART2 receive interrupt and returns the UART2 buffer.
 *
 * \return Received Byte
 *
 * \brief <b>Example</b><br>
 * \brief This example receives a Byte via UART2.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint8 ch;
 *
 *     UART2_Receiver_En();
 *     UART2_BaudRate_Set(19200);
 *     if (UART2_isByteReceived() == TRUE)
 *     {
 *       ch = UART2_Get_Byte();
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup uart_api
 */
INLINE uint8 UART2_Get_Byte(void)
{
  UART2_RX_Int_Clr();
  return (UART2_Buffer_Get());
}

/** \brief checks if UART2 has received Byte or not.
 *
 * \retval TRUE a byte was received
 * \retval FALSE no byte was receive
 *
 * \brief <b>Example</b><br>
 * \brief This example receives a Byte via UART2.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint8 ch;
 *
 *     UART2_Receiver_En();
 *     UART2_BaudRate_Set(19200);
 *     if (UART2_isByteReceived() == TRUE)
 *     {
 *       ch = UART2_Get_Byte();
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup uart_api
 */
INLINE bool UART2_isByteReceived(void)
{
  bool bRes = false;

  if (UART2_RX_Sts() == (uint8)1)
  {
    bRes = true;
  }

  return (bRes);
}

/** \brief checks if UART2 has transmitted a Byte or not.
 *
 * \retval TRUE a byte was transmitted
 * \retval FALSE no byte was transmitted
 *
 * \brief <b>Example</b><br>
 * \brief This example sends "A" via UART2.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     UART2_BaudRate_Set(19200);
 *     if (UART2_isByteTransmitted() == TRUE)
 *     {
 *       UART2_Send_Byte(0x41);
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup uart_api
 */
INLINE bool UART2_isByteTransmitted(void)
{
  bool bRes = false;

  if (UART2_TX_Sts() == (uint8)1)
  {
    bRes = true;
  }

  return (bRes);
}

#endif
