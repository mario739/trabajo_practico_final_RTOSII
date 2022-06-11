
#ifndef  FRAME_H
#define FRAME_H

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "cmsis_os.h"
#include "crc8.h"

#define BUFFER_MAX_SIZE 200

typedef enum
{
    SOM,
    EOM,
} en_frame;
typedef struct
{
    uint8_t *buffer;
    uint8_t max_size_buffer;
    uint8_t size_buffer;
    en_frame state_frame;
    uint8_t count_buffer;
    xQueueHandle c2_queue;
    xQueueHandle c2_queue_out;
    TimerHandle_t timer;
} ts_frame;

void frame_init(ts_frame *self);
void frame_reset(ts_frame *self);
void frame_process(ts_frame *self, uint8_t byte);

uint8_t calculate_crc(uint8_t *buffer, uint8_t count_buffer);
uint8_t convert_ascii_to_uint(uint8_t *data);
void convert_uint_to_ascii(uint8_t *data,uint8_t crc);

#endif
