/*
 * Copyright (c) YEAR NOMBRE <MAIL>.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from
 *    this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 *
 * @file   : frame_separation.c
 * @date   : May 17, 2022
 * @author : NOMBRE <MAIL>
 * @version	v1.0.0
 */

/********************** inclusions *******************************************/
#include "frame_separation.h"

/********************** macros and definitions *******************************/

/********************** internal data declaration ****************************/

/********************** internal functions declaration ***********************/

/********************** internal data definition *****************************/
em_string state_machine=IDLE;
//uint8_t buffer[200];
uint16_t count_byte=0;
/********************** external data definition *****************************/

extern uint8_t data_e;
extern TimerHandle_t timer;
/********************** internal functions definition ************************/

/********************** external functions definition ************************/

/*void timer_call_back(TimerHandle_t timer)
{
}

void frame_separation_init(st_fs_handle *self,UART_HandleTypeDef *uart,uint8_t *data)
{
  self->uartx=uart;
  timer=xTimerCreate("Timerx",1000, pdFALSE,(void*)0,timer_call_back);
  xTimerStart(timer,0);
  HAL_UART_Receive_IT(uart,&data_e,1);
}
*/
/*void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  BaseType_t depertar=pdFALSE;
  static uint8_t count_id=0;
  huart->pRxBuffPtr -= 1U;
  uint8_t data=*huart->pRxBuffPtr;
  HAL_UART_Receive_IT(huart,&data_e,1);
  if (huart != NULL)
  {
    switch (state_machine)
    {
      case IDLE:
        memset(buffer, '\0', 200);
        count_byte = 0;
        xTimerStartFromISR(timer,&depertar);
        portEND_SWITCHING_ISR(depertar);
        if (data =='(')
        {
          buffer[count_byte]=data;
          state_machine=SOM;
        }
        break;
      case SOM:
        //memset(buffer, '\0', 200);
        count_byte = 0;
        count_byte++;
        buffer[count_byte]=data;
        state_machine=ID;
        break;
      case ID:
        count_byte++;
        count_id++;
        buffer[count_byte]=data;
        if (count_id>=4)
        {
          count_id=0;
          state_machine=CODIGE;
        }
        break;
      case CODIGE:
        count_byte++;
        buffer[count_byte]=data;
        state_machine=DATA;
        break;
      case DATA:
        count_byte++;
        buffer[count_byte]=data;
        if (data==')')
        {
          state_machine=EOM;
          HAL_UART_Transmit(huart,&buffer,count_byte+1,100);
        }
        break;
      case EOM:
        //ENVIAR  LA COLA LOS DAATOS;
        state_machine=IDLE;
      default:
        break;
    }
  }
}*/
/********************** end of file ******************************************/
