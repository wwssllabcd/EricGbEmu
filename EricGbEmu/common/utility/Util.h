#pragma once
#include <stdio.h>

#include "type/type_header.h"


void mem_cpy(eu8_p dst, eu8_sp src, eu32 len);
void mem_set(eu8_p dst, eu8 value, eu32 len);
FILE* file_open(echar_p path, echar_p op);
void file_read(echar_p s, eu8_p buffer, eu32 len);