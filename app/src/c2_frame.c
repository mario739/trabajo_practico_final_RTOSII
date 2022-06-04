#include "c2_frame.h"
#include "c2_parser.h"


void timer_call_back(TimerHandle_t timer)
{
	ts_frame *frame=(ts_frame*) pvTimerGetTimerID(timer);
	frame->count_buffer=0;
}
void frame_init(ts_frame *self, uint8_t *buffer, uint8_t max_size_buffer, uint8_t size_buffer, en_frame state_frame, uint8_t count_buffer)
{
    self->buffer = buffer;
    self->max_size_buffer = max_size_buffer;
    self->size_buffer = size_buffer;
    self->state_frame = state_frame;
    self->count_buffer = count_buffer;
    self->c2_queue = xQueueCreate((unsigned portBASE_TYPE) 1, sizeof(void*));
    self->timer=xTimerCreate("Timerx",10000, pdFALSE,(void*)self,timer_call_back);
}
bool frame_process(ts_frame *self, uint8_t byte)
{
    switch (self->state_frame)
    {
    case SOM:
        if (byte == '(')
        {
            self->buffer[self->count_buffer] = byte;
            self->count_buffer++;
            self->state_frame = EOM;
            xTimerStartFromISR(self->timer,0);
        }
        return 0;
        break;
    case EOM:
        if (byte == ')')
        {
        	xTimerStopFromISR(self->timer,0);
            self->buffer[self->count_buffer] = byte;
            ts_c2_parser c2_parser;
            self->state_frame = SOM;
            c2_parser_init(&c2_parser, self->buffer, self->count_buffer);
            if (validate_id_hex(&c2_parser) == 1)
            {
                if (validate_crc_hex(&c2_parser) == 1)
                {
                	xQueueSendToFrontFromISR(self->c2_queue,(void*)&self->buffer,0);
                	self->count_buffer=0;
                    return 1;
                }
            }
            memset(self->buffer,'\0',self->count_buffer);
            self->count_buffer=0;
        }
        else
        {
            if (byte == '(')
            {
                self->count_buffer = 0;
                self->buffer[self->count_buffer] = byte;
            }
            else
            {
                self->buffer[self->count_buffer] = byte;
                self->count_buffer++;
            }
            xTimerStartFromISR(self->timer,0);
        }
        return 0;
        break;
    default:
        break;
    }
}

