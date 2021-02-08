#pragma once

#define TO_BIT_NUM(num)                           ( 1 << (num) )

#define CHECK_BIT(value, bit)                     ( ((value) & TO_BIT_NUM(bit) )? 1 : 0 )

#define CLEAR_BIT(value, bit)                     ( (value) &= (~(TO_BIT_NUM(bit))) )
#define SET_BIT(value, bit)                       ( (value) |= ( (TO_BIT_NUM(bit))) )
#define SET_BIT_TO(value, bit, T)                 ( (T)?SET_BIT((value), (bit)): CLEAR_BIT((value), (bit)) )