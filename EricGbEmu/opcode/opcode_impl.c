
#include "opcode_impl.h"

#include "cpu.h"
#include "mmu.h"


bool check_hc_add(eu32 summand, eu32 addend, eu32 mask) {
    return ((summand & mask) + (addend & mask) > mask);
}

bool check_hc_sub(eu32 minute, eu32 minus, eu32 mask) {
    return (minute & mask) < (minus & mask);
}

eu32 add_a_b(eu32 summand, eu32 addend, eu32 mask) {
    eu32 result = summand + addend;

    set_z((result & mask) == 0);
    set_n(false);
    set_h(check_hc_add(summand, addend, mask >> 4));
    set_c(result > mask);

    return result;
}

eu32 sub_a_b(eu32 minute, eu32 minus, eu32 mask) {
    eu32 result = minute - minus;

    set_z((result & mask) == 0);
    set_n(true);
    set_h(check_hc_sub(minute, minus, mask >> 4));
    set_c(minute < minus);
    return result;
}

eu8 inc_n(eu8 value) {
    value++;
    set_z(value == 0);
    set_n(false);
    set_h((value & 0x0F) == 0x00);

    return value;
}

eu8 dec_n(eu8 value) {
    value--;

    set_z(value == 0);
    set_n(true);
    set_h((value & 0x0F) == 0x0F);
    return value;
}

eu8 swap_n(eu8 val) {
    eu8 low = val & 0xF;
    eu8 high = val >> 4;
    eu8 res = (low << 4) | high;

    set_z(res == 0);
    set_n(false);
    set_h(false);
    set_c(false);

    return res;
}

eu8 rlx_n(eu8 value, eu8 plus) {
    eu8 result = (value << 1) | plus;

    set_z(result == 0);
    set_n(false);
    set_h(false);
    set_c(CHECK_BIT(value, 7));

    return result;
}

eu8 rrx_n(eu8 value, eu8 plus) {
    eu8 result = (value >> 1) | (plus << 7);

    set_z(result == 0);
    set_n(false);
    set_h(false);
    set_c(CHECK_BIT(value, 0));

    return result;
}

void set_sla_sra_srl_flag(eu8 value, eu8 checkBit) {
    set_z(value == 0);
    set_n(false);
    set_h(false);
    set_c(CHECK_BIT(value, checkBit));
}

eu8 sla_n(eu8 value) {
    eu8 res = (value << 1);
    set_sla_sra_srl_flag(res, 7);
    return res;
}

eu8 sra_n(eu8 value) {
    eu8 res = (value >> 1);
    set_sla_sra_srl_flag(res, 0);
    return res;
}

eu8 srl_n(eu8 value) {
    eu8 res = (value >> 1);
    set_sla_sra_srl_flag(res, 0);
    return res;
}

//----------------- 3.3.1. 8-Bit Loads ----------------
void opcode_ld_nn_n(ByteReg_p reg) {
    opcode_ld_r1_r2(reg, fetch());
}

void opcode_ld_r1_r2(ByteReg_p r1, eu8 r2) {
    REG_VAL(r1) = r2;
}

void opcode_ld_r1_r2_addr(RamAddr address, eu8 r2) {
    set_ram(address, r2);
}

void opcode_ld_a_n(eu8 n) {
    opcode_ld_r1_r2(a, n);
}

void opcode_ld_n_a(ByteReg_p reg) {
    opcode_ld_r1_r2(reg, REG_A);
}

void opcode_ld_n_a_addr(RamAddr address) {
    opcode_ld_r1_r2_addr(address, REG_A);
}

void opcode_ld_a_c() {
    opcode_ld_r1_r2(a, get_ram(ZERO_PAGE + REG_C));
}

void opcode_ld_c_a() {
    opcode_ld_r1_r2_addr(ZERO_PAGE + REG_C, REG_A);
}

void opcode_ldd_a_hl() {
    opcode_ld_r1_r2(a, get_ram(REG_HL));
    DEC_REG(hl);
}

void opcode_ldd_hl_a() {
    opcode_ld_r1_r2_addr(REG_HL, REG_A);
    DEC_REG(hl);
}

void opcode_ldi_a_hl() {
    opcode_ld_r1_r2(a, get_ram(REG_HL));
    INC_REG(hl);
}

void opcode_ldi_hl_a() {
    opcode_ld_r1_r2_addr(REG_HL, REG_A);
    INC_REG(hl);
}

void opcode_ldh_n_a() {
    opcode_ld_r1_r2_addr(ZERO_PAGE + fetch(), REG_A);
}

void opcode_ldh_a_n() {
    opcode_ld_r1_r2(a, get_ram(ZERO_PAGE + fetch()));
}

// ----------- 3.3.2. 16-Bit Loads ----------------
void opcode_put_value_into_reg(WordReg_p reg, eu16 value) {
    REG_VAL(reg) = value;
}

void opcode_put_value_into_addr(RamAddr addr, eu16 value) {
    set_ram(addr + 0, ((value >> 0) & 0xFF));
    set_ram(addr + 1, ((value >> 8) & 0xFF));
}

// Put value nn into n.
void opcode_ld_n_nn(WordReg_p reg) {
    opcode_put_value_into_reg(reg, fetch_word());
}

void opcode_ld_sp_hl() {
    opcode_put_value_into_reg(sp, REG_HL);
}

void opcode_ldhl_sp_n() {
    eu16 reg = REG_SP;
    es8 value = (es8)fetch();
    int result = reg + value;

    set_z(false);
    set_n(false);
    set_h(((reg ^ value ^ (result & 0xFFFF)) & 0x10) == 0x10);
    set_c(((reg ^ value ^ (result & 0xFFFF)) & 0x100) == 0x100);

    REG_HL = (eu16)result;
}

void opcode_ld_nn_sp() {
    opcode_put_value_into_addr(fetch_word(), REG_SP);
}

void opcode_push_nn(WordReg_p reg) {
    stack_push(reg);
}

void opcode_pop_nn(WordReg_p reg) {
    stack_pop(reg);
}

// ----------- 3.3.3. 8-Bit ALU ----------------
void opcode_add_a_n(eu8 n) {
    REG_VAL(a) = (eu8)add_a_b(REG_VAL(a), n, 0xFF);
}

void opcode_adc_a_n(eu8 n) {
    opcode_add_a_n(n + flags->c);
}

void opcode_sub_n(eu8 n) {
    REG_A = (eu8)sub_a_b(REG_A, n, 0xFF);
}

void opcode_sbc_a_n(eu8 n) {
    opcode_sub_n(n + flags->c);
}

void opcode_and_n(eu8 value) {
    REG_A &= value;

    set_z(REG_A == 0);
    set_n(false);
    set_h(true);
    set_c(false);
}

void opcode_or_n(eu8 val) {
    REG_A |= val;

    set_z(REG_A == 0);
    set_n(false);
    set_h(false);
    set_c(false);
}

void opcode_xor_n(eu8 val) {
    REG_A ^= val;

    set_z(REG_A == 0);
    set_n(false);
    set_h(false);
    set_c(false);
}

void opcode_cp_n(eu8 n) {
    sub_a_b(REG_A, n, 0xFF);
}

void opcode_inc_n(ByteReg_p n) {
    REG_VAL(n) = inc_n(REG_VAL(n));
}

void opcode_inc_n_addr(RamAddr address) {
    set_ram(address, inc_n(get_ram(address)));
}

void opcode_dec_n(ByteReg_p reg) {
    REG_VAL(reg) = dec_n(REG_VAL(reg));
}

void opcode_dec_n_addr(RamAddr address) {
    set_ram(address, dec_n(get_ram(address)));
}

// ----------- 3.3.4. 16 - Bit Arithmetic -----------
void opcode_add_hl_n(WordReg_p reg) {
    REG_HL = (eu16)add_a_b(REG_HL, REG_VAL(reg), 0xFFFF);
}

void opcode_add_sp_n() {
    eu16 reg = REG_SP;
    es8 value = (es8)fetch();

    int result = (int)(reg + value);

    set_z(false);
    set_n(false);
    set_h(((reg ^ value ^ (result & 0xFFFF)) & 0x10) == 0x10);
    set_c(((reg ^ value ^ (result & 0xFFFF)) & 0x100) == 0x100);

    REG_SP = (eu16)result;
}

void opcode_inc_nn(WordReg_p reg) {
    INC_REG(reg);
}

void opcode_dec_nn(WordReg_p reg) {
    DEC_REG(reg);
}

// ----------- 3.3.5. Miscellaneous -----------
void opcode_cb_swap_n(ByteReg_p reg) {
    REG_VAL(reg) = swap_n(REG_VAL(reg));
}

void opcode_cb_swap_n_addr(RamAddr address) {
    set_ram(address, swap_n(get_ram(address)));
}

void opcode_daa() {
    eu8 reg = REG_A;
    eu16 correction = flags->c ? 0x60 : 0x00;

    if (flags->c || (!flags->n && ((reg & 0x0F) > 9))) {
        correction |= 0x06;
    }

    if (flags->c || (!flags->n && (reg > 0x99))) {
        correction |= 0x60;
    }

    if (flags->n) {
        reg = (eu8)(reg - correction);
    } else {
        reg = (eu8)(reg + correction);
    }

    if (((correction << 2) & 0x100) != 0) {
        set_c(true);
    }

    set_h(false);
    set_z(reg == 0);

    REG_A = reg;
}

void opcode_cpl() {
    REG_A = ~REG_A;
    set_n(true);
    set_h(true);
}

void opcode_ccf() {
    set_n(false);
    set_h(false);
    set_c(!flags->c);
}

void opcode_scf() {
    set_n(false);
    set_h(false);
    set_c(true);
}

void opcode_nop() {
}

void opcode_halt() {
    enable_halt();
}

void opcode_stop() {
}

void opcode_di() {
    g_cpu.enableInterrupt = false;
}

void opcode_ei() {
    g_cpu.enableInterrupt = true;
}

// ----------- 3.3.6. Rotates & Shifts -----------
void opcode_rlca() {
    opcode_cb_rlc_n(a);
    set_z(false);
}

void opcode_rla() {
    opcode_cb_rl_n(a);
    set_z(false);
}

void opcode_rrca() {
    opcode_cb_rrc_n(a);
    set_z(false);
}

void opcode_rra() {
    opcode_cb_rr_n(a);
    set_z(false);
}

void opcode_cb_rlc_n(ByteReg_p reg) {
    eu8 plus = CHECK_BIT(REG_VAL(reg), 7);
    REG_VAL(reg) = rlx_n(REG_VAL(reg), plus);
}

void opcode_cb_rlc_n_addr(RamAddr addr) {
    eu8 plus = CHECK_BIT(get_ram(addr), 7);
    set_ram(addr, rlx_n(get_ram(addr), plus));
}

void opcode_cb_rl_n(ByteReg_p reg) {
    REG_VAL(reg) = rlx_n(REG_VAL(reg), flags->c);
}

void opcode_cb_rl_n_addr(RamAddr addr) {
    set_ram(addr, rlx_n(get_ram(addr), flags->c));
}

void opcode_cb_rrc_n(ByteReg_p reg) {
    eu8 value = REG_VAL(reg);
    REG_VAL(reg) = rrx_n(value, CHECK_BIT(value, 0));
}

void opcode_cb_rrc_n_addr(RamAddr addr) {
    eu8 value = get_ram(addr);
    set_ram(addr, rrx_n(value, CHECK_BIT(value, 0)));
}

void opcode_cb_rr_n(ByteReg_p reg) {
    REG_VAL(reg) = rrx_n(REG_VAL(reg), flags->c);
}

void opcode_cb_rr_n_addr(RamAddr address) {
    set_ram(address, rrx_n(get_ram(address), flags->c));
}

void opcode_cb_sla_n(ByteReg_p reg) {
    REG_VAL(reg) = sla_n(REG_VAL(reg));
}

void opcode_cb_sla_n_addr(RamAddr addr) {
    set_ram(addr, sla_n(get_ram(addr)));
}

void opcode_cb_sra_n(ByteReg_p reg) {
    REG_VAL(reg) = sra_n(REG_VAL(reg));
}

void opcode_cb_sra_n_addr(RamAddr addr) {
    set_ram(addr, sra_n(get_ram(addr)));
}

void opcode_cb_srl_n(ByteReg_p reg) {
    REG_VAL(reg) = srl_n(REG_VAL(reg));
}

void opcode_cb_srl_n_addr(RamAddr address) {
    set_ram(address, srl_n(get_ram(address)));
}

// ----------- 3.3.7. Bit Opcodes -----------
void opcode_cb_bit_b_r(eu8 val, eu8 bit) {
    set_z(CHECK_BIT(val, bit) == 0);
    set_n(false);
    set_h(true);
}

// Set bit b in register r.
void opcode_cb_set_b_r(ByteReg_p reg, eu8 bit) {
    SET_BIT(REG_VAL(reg), bit);
}

void opcode_cb_set_b_r_addr(RamAddr addr, eu8 bit) {
    eu8 res = get_ram(addr);
    SET_BIT(res, bit);
    set_ram(addr, res);
}

// Reset bit b in register r.
void opcode_cb_res_b_r(ByteReg_p reg, eu8 bit) {
    CLEAR_BIT(REG_VAL(reg), bit);
}

void opcode_cb_res_b_r_addr(RamAddr addr, eu8 bit) {
    eu8 res = get_ram(addr);
    CLEAR_BIT(res, bit);
    set_ram(addr, res);
}

// ----------- 3.3.8. Jumps -----------
void opcode_jp_nn() {
    REG_PC = fetch_word();
}

void opcode_jp_cc_nn(bool condition) {
    if (condition) {
        opcode_jp_nn();
    } else {
        // skip 2 byte
        fetch_word();
    }
}

void opcode_jp_hl() {
    REG_PC = REG_HL;
}

void opcode_jr_n() {
    es8 offset = fetch();
    REG_PC = REG_PC + offset;
}

void opcode_jr_cc_n(bool condition) {
    if (condition) {
        opcode_jr_n();
    } else {
        INC_REG(pc);
    }
}

// ----------- 3.3.9. Calls -----------
void opcode_call_nn() {
    RamAddr address = fetch_word();
    stack_push(pc);
    REG_PC = address;
}

void opcode_call_cc_nn(bool condition) {
    if (condition) {
        opcode_call_nn();
    } else {
        INC_REG(pc);
        INC_REG(pc);
    }
}

// ----------- 3.3.10. Restarts -----------
void opcode_rst_n(eu8 n) {
    stack_push(pc);
    REG_PC = n;
}

// ----------- 3.3.11. Returns -----------
void opcode_ret() {
    stack_pop(pc);
}

void opcode_ret_cc(bool condition) {
    if (condition) {
        opcode_ret();
    }
}

void opcode_reti() {
    opcode_ret();
    opcode_ei();
}
