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
 * @file   : frame_separation.h
 * @date   : May 17, 2022
 * @author : NOMBRE <MAIL>
 * @version	v1.0.0
 */

#ifndef INC_FRAME_SEPARATION_H_
#define INC_FRAME_SEPARATION_H_

/********************** CPP guard ********************************************/
#ifdef __cplusplus
extern "C" {
#endif

/********************** inclusions *******************************************/

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "main.h"
#include "cmsis_os.h"
/********************** macros ***********************************************/

/********************** typedef **********************************************/
typedef struct
{
    UART_HandleTypeDef *uartx;
}st_fs_handle;
typedef enum
{
  IDLE,
  SOM,
  ID,
  CODIGE,
  DATA,
  EOM,
}em_string;
/********************** external data declaration ****************************/

/********************** external functions declaration ***********************/
void timer_call_back(TimerHandle_t timer);
//void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);
void frame_separation_init(st_fs_handle *self,UART_HandleTypeDef *uart,uint8_t *data);

/********************** End of CPP guard *************************************/
#ifdef __cplusplus
}
#endif

#endif /* INC_FRAME_SEPARATION_H_ */
/********************** end of file ******************************************/

