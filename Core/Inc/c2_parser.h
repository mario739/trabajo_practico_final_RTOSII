#include <stdint.h>
#include <stdbool.h>
#include <string.h>

typedef struct 
{
    uint8_t *buffer;
    uint8_t *id;
    uint8_t *crc; 
    uint8_t size_buffer;
} ts_c2_parser;

void c2_parser_init(ts_c2_parser *self, uint8_t *buffer, uint8_t size);
bool validate_id_hex(ts_c2_parser *self);
bool validate_crc_hex(ts_c2_parser *self);

