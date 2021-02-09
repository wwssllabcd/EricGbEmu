#pragma once


typedef struct {
    eu8 all;
}ByteReg;
ERIC_GEN_POINTER_TYPE(ByteReg);

typedef union {
    eu16 all;
    struct {
        ByteReg low;
        ByteReg high;
    };
}WordReg;
ERIC_GEN_POINTER_TYPE(WordReg);

typedef union {
    eu8 all;
    struct {
        eu8 : 4;

        //This bit is set if a carry occurred from the last math operation or if register A is the smaller value when executing the CP instruction.
        eu8 c : 1;

        //This bit is set if a carry occurred from the lower nibble in the last math operation.
        eu8 h : 1;

        //This bit is set if a subtraction was performed in the last math instruction.
        eu8 n : 1;

        //This bit is set when the result of a math operation is zero or two values match when using the CP instruction.
        eu8 z : 1;
    };
}FlagReg;
ERIC_GEN_POINTER_TYPE(FlagReg);

typedef struct {
    union {
        WordReg af;
        struct {
            FlagReg f;
            ByteReg a;
        };
    };
    union {
        WordReg bc;
        struct {
            ByteReg c;
            ByteReg b;
        };
    };
    union {
        WordReg de;
        struct {
            ByteReg e;
            ByteReg d;
        };
    };
    union {
        WordReg hl;
        struct {
            ByteReg l;
            ByteReg h;
        };
    };

    WordReg sp;
    WordReg pc;

    bool halt;
    bool running;
    bool enable_interrupt;

    eu32 clock_cnt;
}Cpu;
ERIC_GEN_POINTER_TYPE(Cpu);
