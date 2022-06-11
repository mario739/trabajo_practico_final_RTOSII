#include "c2_frame.h"
#include "c2_parser.h"

void timer_call_back(TimerHandle_t timer)
{
	ts_frame *frame=(ts_frame*) pvTimerGetTimerID(timer);
	frame->count_buffer=0;
}
void frame_init(ts_frame *self, uint8_t *buffer, uint8_t max_size_buffer, uint8_t size_buffer, en_frame state_frame, uint8_t count_buffer)
{
    self->buffer =buffer;
    self->max_size_buffer = max_size_buffer;
    self->size_buffer = size_buffer;
    self->state_frame = state_frame;
    self->count_buffer = count_buffer;
    self->c2_queue = xQueueCreate((unsigned portBASE_TYPE) 1, sizeof(void*));
    self->c2_queue_out = xQueueCreate((unsigned portBASE_TYPE) 1, sizeof(void*));
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
                	uint8_t crc=calculate_crc(self);
                	uint8_t crc2=convert_ascii_to_uint(self->buffer+(self->count_buffer-2));
                	if (crc==crc2)
                	{
                    	xQueueSendToFrontFromISR(self->c2_queue,(void*)&self->buffer,0);
                    	//self->count_buffer=0;
                        return 1;
					}
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
uint8_t calculate_crc(ts_frame *self)
{
    uint8_t data_crc=crc8_calc(0,self->buffer+1,self->count_buffer-3);
    return data_crc;
}
uint8_t convert_ascii_to_uint(uint8_t *data)
{
	uint8_t result = 0;
	if (data[0] >= 'A' && data[0] <= 'F')
		result = (10 + data[0] - 'A') * 16;
	else
		result = (data[0] - '0') * 16;

	if (data[1] >= 'A' && data[1] <= 'F')
		result += 10 + data[1] - 'A';
	else
		result += data[1] - '0';

	return result;
}

void convert_uint_to_ascii(uint8_t *data,uint8_t crc)
{
    uint8_t msn, lsn;
    msn = crc / 16;
    lsn = crc - msn * 16;

    if (msn < 10)
        data[0] = msn + '0';
    else
        data[0] = msn - 10 + 'A';

    if (lsn < 10)
        data[1] = lsn + '0';
    else
        data[1] = lsn - 10 + 'A';
}


