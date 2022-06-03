#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "cmsis_os.h"

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
    TimerHandle_t timer;
} ts_frame;

void frame_init(ts_frame *self,uint8_t *buffer,uint8_t max_size_buffer,uint8_t size_buffer,en_frame state_frame,uint8_t count_buffer);
bool frame_process(ts_frame *self, uint8_t byte);
