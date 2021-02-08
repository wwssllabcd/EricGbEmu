#pragma once
#include "type/type_header.h"

#define PRINT_LEVEL_NO (0)
#define PRINTF_LEVEL(LEVEL, FMT, ...)                ((LEVEL <= PRINT_LEVEL_NO) ? show_msg(_ET(FMT), ##__VA_ARGS__) : 0)
#define PRINTF_CRITICAL(FMT, ...)                    PRINTF_LEVEL(0, "\nCritical: "FMT, ##__VA_ARGS__)
#define PRINTF_ALWAYS(FMT, ...)                      PRINTF_LEVEL(0, "\n"FMT, ##__VA_ARGS__)
#define PRINTF_ALWAYS_NOCRLF(FMT, ...)               PRINTF_LEVEL(0, FMT, ##__VA_ARGS__)
#define PRINTF_CODE                                  PRINTF_ALWAYS

#define ASSERT_CODE(COND, FMT, ...)                   do {    \
    if (!(COND)) {                                            \
        write_log(_ET("\n"FMT),  ##__VA_ARGS__);              \
		hang_up();                                            \
    }                                                         \
} while (0)                                                   \

typedef eu16 PrintRamAddr;
typedef eu8(*GetRamFun)(PrintRamAddr);

void show_msg(echar_p fmt, ...);
void hang_up(void);
void print_ram_base(PrintRamAddr ptr, eu32 len, GetRamFun fun);
void write_log(echar_p fmt, ...);