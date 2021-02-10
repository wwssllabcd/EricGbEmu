#pragma once


#define PREFIX_CMD (0xCB)

typedef void(*OpcodeFun)();
ERIC_GEN_POINTER_TYPE(OpcodeFun);

extern OpcodeFun g_opcodeFunMap[0x100];
extern OpcodeFun g_opcodeFunMap_cb[0x100];