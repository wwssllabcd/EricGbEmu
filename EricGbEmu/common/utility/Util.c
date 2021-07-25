
#include <stdio.h>
#include <string.h>

#include "Util.h"
#include "common/define/define_header.h"
#include "define/define_unicode.h"
#include "show_msg.h"

void mem_cpy(eu8_p dst, eu8_sp src, eu32 len) {
    memcpy(dst, src, len);
}

void mem_set(eu8_p dst, eu8 value, eu32 len) {
    memset(dst, value, len);
}

FILE* file_open(echar_p path, echar_p op) {
    FILE* file;
#ifdef WIN_PLATFORM
    TFOPEN(&file, path, op);
#else
    file = fopen(path, op);
#endif
    return file;
}

void file_read(echar_p filename, eu8_p buffer, eu32 len) {
    FILE *file = file_open(filename, _ET("r"));
    if (file == NULL) {
        ASSERT_CODE(0, "file open fail = %s", filename);
        return;
    }
    
    fread(buffer, len, 1, file);
    fclose(file);
}

