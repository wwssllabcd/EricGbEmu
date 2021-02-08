
#include <stdio.h>
#include <string.h>

#include "Util.h"
#include "define/define_unicode.h"
#include "show_msg.h"

void mem_cpy(eu8_p dst, eu8_sp src, eu32 len) {
    memcpy(dst, src, len);
}

void mem_set(eu8_p dst, eu8 value, eu32 len) {
    memset(dst, value, len);
}

void file_read(echar_p filename, eu8_p buffer, eu32 len) {
    FILE *file;
    TFOPEN(&file, filename, _ET("r"));

    if (file == NULL) {
        ASSERT_CODE(0, "file open fail = %s", filename);
        return;
    }
    
    fread(buffer, len, 1, file);
    fclose(file);
}
