/*
 ***********************************************************************************************************************
 *
 * Copyright (c) 2015, Infineon Technologies AG
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
**                             Author(s) Identity                             **
********************************************************************************
** Initials     Name                                                          **
** ---------------------------------------------------------------------------**
** BG           Blandine Guillot                                              **
** JO           Julia Ott                                                     **
*******************************************************************************/

/*******************************************************************************
**                          Revision Control History                          **
********************************************************************************
** V1.0.0: 2020-04-15, BG:   Initial version of revision history              **
** V1.0.1: 2020-07-21, BG:   EP-439: Formatted .h/.c files                    **
** V1.1.0: 2022-04-01, JO:   EP-1113: Updated example for IAR to work with    **
**                           external terminal                                **
*******************************************************************************/

/*******************************************************************************
**                                  Abstract                                  **
********************************************************************************
** DMA: Send out a 'Hello World!' string at UART2 triggered by DMA            **
********************************************************************************
** In a terminal window set up a serial connection @115.2kBaud through the    **
** debugger port.                                                             **
** The Core timer 3 of GPT12E triggers a DMA transfer (DMA_CH12) every 100us. **
** The DMA takes one character out of the "uart_tx_data' string and puts it   **
** into the send buffer of UART2.                                             **
** The UART2 sends out the data at P1.1/P1.2 @115.2kBaud.                     **
*******************************************************************************/

#include "tle_device.h"
#include <stdio.h>
#include "mavlink.h"
#include "Sin_Table.h"  
   
#if defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6000000)
  #pragma clang diagnostic push
  #pragma clang diagnostic ignored "-Wmissing-variable-declarations"
#endif
char uart_tx_data[DMA_CH12_NoOfTrans] = "Hello World!\r\n";
#if defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6000000)
  #pragma clang diagnostic pop
#endif
mavlink_pmsm_command_t mavlink_pmsm_command;
mavlink_pmsm_status_t mavlink_pmsm_status;
mavlink_message_t msg_Tx;
mavlink_message_t msg_Rx;
uint8 mavlink_pmsm_status_buffer[MAVLINK_MAX_PACKET_LEN];
uint32 mavlink_pmsm_status_Length;

uint8_t system_id =1;
uint8_t component_id =1;
static uint8 index = 0;
//uint8_t chan =0;


void DMA_CH12_MAVlink_Config(void);

int main(void)
{
  /* Initialization of hardware modules based on Config Wizard configuration */
  TLE_Init();
  /* Enable DMA master */
  DMA_CH12_MAVlink_Config();
  DMA_Master_En();
  /* Start GPT12E.T3 to start DMA triggered UART transfer */
  GPT12E_T3_Start();

  for (;;)
  {
    (void)WDT1_Service();
    
    mavlink_pmsm_status.Battery_Voltage=17.2;
    mavlink_pmsm_status.Phase_Current_U=45.3;
    mavlink_pmsm_status.Phase_Current_V=73.4;
    mavlink_pmsm_status.Phase_Current_W=101.5;
    mavlink_pmsm_status.T1=129.6;
    mavlink_pmsm_status.T2=157.7;
    mavlink_pmsm_status.Sector=Sin_Table[index];
    GPT12E_T3_Start();
    /* Wait for MON button to be pressed */
//    if (MON_Debounce(0u) == 0u)
//    {
//      //      GPT12E_T3_Start();
//      /* Start GPT12E.T3 to start DMA triggered UART transfer */
//    }
   
  }
}


#if defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6000000)
  #pragma clang diagnostic push
  #pragma clang diagnostic ignored "-Wmissing-prototypes"
#endif
/* Callback function on DMA complete */
void DMA_UART_SEND_Complete(void)
{

  /* Stop GPT12E.T3 */
  GPT12E_T3_Stop();
  PORT_P04_Output_High_Set();
  /* Send a 'DMA done' through UART2 */
//  printf("DMA done\n");
  
  if (index>=254)
  {
    index = 0;
  } 
  //Pack MAVlink data
  mavlink_pmsm_status.Sector=Sin_Table[index];
  mavlink_msg_pmsm_status_pack(system_id, component_id, &msg_Tx,
                               mavlink_pmsm_status.Battery_Voltage, 
                               mavlink_pmsm_status.Phase_Current_U, 
                               mavlink_pmsm_status.Phase_Current_V, 
                               mavlink_pmsm_status.Phase_Current_W, 
                               mavlink_pmsm_status.T1, 
                               mavlink_pmsm_status.T2, 
                               mavlink_pmsm_status.Sector);
                              //  index
  //Send MAVlink data to buffer
  mavlink_msg_to_send_buffer(mavlink_pmsm_status_buffer, &msg_Tx);
  DMA_Reset_Channel(DMA_CH12,mavlink_pmsm_status_Length);
//  DMA_Reset_Channel(DMA_CH12,DMA_CH12_NoOfTrans);
  index++;
  
  
}
/* Callback function on UART Receive complete */
void UART2_Receive_Interrupt_Callback(void)
{
  mavlink_status_t status;
  mavlink_message_t msg;
  uint8_t chan = 0;
  static uint8_t data;
  data = UART2_Get_Byte();
//  mavlink_status_t
  /* Parse UART RX data */
  if (mavlink_parse_char(chan, data, &msg, &status))
  {
    /* code */
    mavlink_msg_pmsm_command_decode(&msg, &mavlink_pmsm_command);
  }
  
}
/* DMA CH12 setting initialize configuration */
void DMA_CH12_MAVlink_Config(void)
{
   mavlink_pmsm_status.Battery_Voltage=17.0;
   mavlink_pmsm_status.Phase_Current_U=45.0;
   mavlink_pmsm_status.Phase_Current_V=73.0;
   mavlink_pmsm_status.Phase_Current_W=101.0;
   mavlink_pmsm_status.T1=129.0;
   mavlink_pmsm_status.T2=157.0;
   mavlink_pmsm_status.Sector=Sin_Table[index];
   mavlink_msg_pmsm_status_pack(system_id, component_id, &msg_Tx,
                                mavlink_pmsm_status.Battery_Voltage, 
                                mavlink_pmsm_status.Phase_Current_U, 
                                mavlink_pmsm_status.Phase_Current_V, 
                                mavlink_pmsm_status.Phase_Current_W, 
                                mavlink_pmsm_status.T1, 
                                mavlink_pmsm_status.T2, 
                                mavlink_pmsm_status.Sector);
   mavlink_pmsm_status_Length = mavlink_msg_to_send_buffer(mavlink_pmsm_status_buffer, &msg_Tx);
   //Set up DMA Ch12 Data
   DMA_Setup_Channel(DMA_CH12,  (uint32)((uint32)&mavlink_pmsm_status_buffer+(uint32)mavlink_pmsm_status_Length -1), (uint32)&UART2->SBUF.reg,
                        mavlink_pmsm_status_Length, DMA_8Bit_Transfer, DMA_Src_Inc);

    /* load source pointer */
  /* violation: cast from pointer to unsigned int [MISRA Rule 45] */
  // DMA_Entry_Ch12_Pri.Src_End_Ptr = (uint32)&DMA_CH12_SRC + (uint32)DMA_CH12_SRC_PTR_OFFS;
//  DMA_Entry_Ch12_Pri.Src_End_Ptr = (uint32)((uint32)&mavlink_pmsm_status_buffer+(uint32)mavlink_pmsm_status_Length -1)
  /* load destination pointer */
  // /* violation: cast from pointer to unsigned int [MISRA Rule 45] */
  // DMA_Entry_Ch12_Pri.Dst_End_Ptr = (uint32)&DMA_CH12_DST + (uint32)DMA_CH12_DST_PTR_OFFS;                       
}


#if defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6000000)
  #pragma clang diagnostic pop
#endif
