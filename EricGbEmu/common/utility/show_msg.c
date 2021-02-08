
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#include "show_msg.h"
#include "define/define_unicode.h"

void show_msg(echar_p fmt, ...) {
    va_list arg;
    va_start(arg, fmt);
    t_vprintf(fmt, arg);
    va_end(arg);
}

void hang_up(void) {
    PRINTF_ALWAYS_NOCRLF("\n\n ----- hang_up -----\n");
    eu32 cnt = 0;
    while (cnt<0x10000) {
        cnt++;
    }
    exit(0);
}

void print_ram_base(PrintRamAddr ptr, eu32 len, GetRamFun fun) {
    for (PrintRamAddr i = 0; i < len; i++) {
        if ((i % 0x10) == 0) {
            PRINTF_ALWAYS_NOCRLF("\n");
            PRINTF_ALWAYS_NOCRLF("%04X | ", ptr + i);
        }
        PRINTF_ALWAYS_NOCRLF("%02X, ", fun(ptr + i));
    }
    PRINTF_ALWAYS_NOCRLF("\n");
}

void write_log(echar_p fmt, ...) {
    va_list arg;
    va_start(arg, fmt);
    echar_p filename = _ET("log.txt");
    FILE* file;
    TFOPEN(&file, _ET("log.txt"), _ET("a"));

    if (file == NULL) {
        PRINTF_ALWAYS("file open fail = %s", filename);
        return;
    }

    t_vfprintf(file, fmt, arg);
    fclose(file);
    va_end(arg);
}
