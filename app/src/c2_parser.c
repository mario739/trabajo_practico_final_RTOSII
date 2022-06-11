#include "c2_parser.h"

void c2_parser_init(ts_c2_parser *self, uint8_t *buffer, uint8_t size)
{
    self->buffer = buffer;
    self->size_buffer = size;
    self->id = (self->buffer) + 1;
    self->crc = (self->buffer + size - 3);
}

bool validate_id_hex(ts_c2_parser *self)
{
    for (uint8_t i = 0; i < 4; i++)
    {
        if (!((self->id[i] <= 70 && self->id[i] >= 65) || (self->id[i] <= 57 && self->id[i] >= 48)))
        {
            return false;
        }
    }
    return true;
}

bool validate_crc_hex(ts_c2_parser *self)
{
    for (uint8_t i = 0; i < 2; i++)
    {
        if (!((self->crc[i] <= 70 && self->crc[i]  >= 65) || (self->crc[i]  <= 57 && self->crc[i]  >= 48)))
        {
            return false;
        }
    }
    return true;
}
