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

ts_erroy_type validate_data(ts_frame *self);
void convert_snake_case(ts_frame *self);
void convert_camel_case(ts_frame *self);
void convert_pascal_case(ts_frame *self);
void process_package(ts_frame *self);
#endif



