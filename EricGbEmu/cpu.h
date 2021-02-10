#pragma once


#include "header.h"

//only for unknow reg
#define REG_VAL(REG)                              ((REG)->all)

#define INC_REG(REG)                              (REG_VAL(REG)++)
#define DEC_REG(REG)                              (REG_VAL(REG)--)

#define REG_HIGH(REG)                             (&(REG)->high)
#define REG_LOW(REG)                              (&(REG)->low)

#define REG_A                       REG_VAL(a)
#define REG_B                       REG_VAL(b)
#define REG_C                       REG_VAL(c)
#define REG_D                       REG_VAL(d)
#define REG_E                       REG_VAL(e)
#define REG_F                       REG_VAL(reg_f)
#define REG_H                       REG_VAL(h)
#define REG_L                       REG_VAL(l)

#define REG_AF                      REG_VAL(af)
#define REG_BC                      REG_VAL(bc)
#define REG_DE                      REG_VAL(de)
#define REG_HL                      REG_VAL(hl)
#define REG_SP                      REG_VAL(sp)
#define REG_PC                      REG_VAL(pc)

#define FLAG_Z                      (flags->z)
#define FLAG_NZ                     (!flags->z)

#define FLAG_C                      (flags->c)
#define FLAG_NC                     (!flags->c)

extern Cpu g_cpu;

extern WordReg_p af;
extern WordReg_p bc;
extern WordReg_p de;
extern WordReg_p hl;
extern WordReg_p sp;
extern WordReg_p pc;

extern ByteReg_p a;
extern FlagReg_p flags;
extern ByteReg_p b;
extern ByteReg_p c;
extern ByteReg_p d;
extern ByteReg_p e;
extern ByteReg_p h;
extern ByteReg_p l;

//-----------------
void set_z(bool val);
void set_h(bool val);
void set_n(bool val);
void set_c(bool val);

void power_on_cpu(eu8_p rom);

eu8 fetch(void);
eu16 fetch_word();

void stack_push(WordReg_p reg);
void stack_pop(WordReg_p reg);

void disable_halt();
void enable_halt();