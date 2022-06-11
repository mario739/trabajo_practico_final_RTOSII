/**
 * @file package.h
 * @author mario aguilar (fernandoaguilar731010@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-06-03
 * 
 * @copyright Copyright (c) 2022
 * 
 */


#ifndef PACKAGE
#define PACKAGE

#include <stdint.h>
#include <stdlib.h>
#include "c2_frame.h"

typedef enum
{
    ERROR_INVALID_DATA,
    ERROR_INVALID_OPCODE,
    ERROR_SYSTEM,
    NO_ERROR
} ts_erroy_type;
typedef struct
{
    uint8_t *buffer;
    uint8_t count_buffer;
} ts_package;

ts_erroy_type validate_data(ts_package *self);
void convert_snake_case(ts_package *self);
void convert_camel_case(ts_package *self);
void convert_pascal_case(ts_package *self);
void process_package(ts_package *self);
#endif



