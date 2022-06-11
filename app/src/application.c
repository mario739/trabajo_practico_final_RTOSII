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
 * @file   : application.c
 * @date   : May 10, 2022
 * @author : NOMBRE <MAIL>
 * @version	v1.0.0
 */

/********************** inclusions *******************************************/
#include "application.h"
#include<stdlib.h>
#include "package.h"
/********************** macros and definitions *******************************/

/********************** internal data declaration ****************************/

/********************** internal functions declaration ***********************/

/********************** internal data definition *****************************/

ts_frame frame;

ts_frame frame2;
uint8_t buffer2[200];
extern UART_HandleTypeDef huart3;
extern UART_HandleTypeDef huart2;
/********************** external data definition *****************************/

/********************** internal functions definition ************************/

/********************** external functions definition ************************/

static void task_c2_out(void *p_parameter)
{
  while (true)
  {
	  void *message;
	  xQueueReceive(frame.c2_queue_out, &message, portMAX_DELAY);

	  ts_package *package = (ts_package *)message;
	  uint8_t data = calculate_crc(package->buffer, package->count_buffer);
      convert_uint_to_ascii(package->buffer+package->count_buffer-3, data);

      HAL_UART_Transmit_IT(&huart3, package->buffer, package->count_buffer);
      free(package->buffer);
  }
}

static void task_c3(void *p_parameter)
{
  while (true)
  {
	  void *message;
	  xQueueReceive(frame.c2_queue, &message, portMAX_DELAY);

	  ts_package *package = (ts_package *)message;
	  validate_data(package);
	  process_package(package);

	  xQueueSend(frame.c2_queue_out, &package, 0);
  }
}

int application(void)
{
  BaseType_t res;
  //res = xTaskCreate(task_c2, (const char*)"task_c2", configMINIMAL_STACK_SIZE * 2, NULL,tskIDLE_PRIORITY + 1, NULL);
  //configASSERT(res == pdPASS);

  res = xTaskCreate(task_c3, (const char*)"task_c3", configMINIMAL_STACK_SIZE * 2, NULL,tskIDLE_PRIORITY + 1, NULL);
  configASSERT(res == pdPASS);

  res = xTaskCreate(task_c2_out, (const char*)"task_c2_out", configMINIMAL_STACK_SIZE * 2, NULL,tskIDLE_PRIORITY + 1, NULL);
  configASSERT(res == pdPASS);

  frame_init(&frame);
  osKernelStart();

  while (1)
  {
  }
  return 1;
}

/*static void task_c2(void *p_parameter)
{
  while (true)
  {
	  void *message;
	  xQueueReceive(frame2.c2_queue, (void*)&message,portMAX_DELAY);
	  HAL_UART_Transmit(&huart2,message,40,10);
  }
}*/

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
	if (huart==&huart3)
	{

	}
	if (huart==&huart2)
	{

	}
}

/********************** end of file ******************************************/
