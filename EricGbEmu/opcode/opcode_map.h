#pragma once


#define PREFIX_CMD (0xCB)

typedef void(*opcode_fun)();
ERIC_GEN_POINTER_TYPE(opcode_fun);

extern opcode_fun g_opcode_fun_map[0x100];
extern opcode_fun g_opcode_cb_fun_map[0x100];