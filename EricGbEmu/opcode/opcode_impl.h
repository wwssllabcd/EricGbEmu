#pragma once
#include "header.h"


//----------------- 3.3.1. 8-Bit Loads ----------------
void opcode_ld_nn_n(ByteReg_p reg);
void opcode_ld_r1_r2(ByteReg_p r1, eu8 r2);
void opcode_ld_r1_r2_addr(RamAddr address, eu8 r2);
void opcode_ld_a_n(eu8 n);
void opcode_ld_n_a(ByteReg_p reg);
void opcode_ld_n_a_addr(RamAddr address);
void opcode_ld_a_c();
void opcode_ld_c_a();
void opcode_ldd_a_hl();
void opcode_ldd_hl_a();
void opcode_ldi_a_hl();
void opcode_ldi_hl_a();
void opcode_ldh_n_a();
void opcode_ldh_a_n();

// ----------- 3.3.2. 16-Bit Loads ----------------
void opcode_put_value_into_reg(WordReg_p reg, eu16 value);
void opcode_put_value_into_addr(RamAddr addr, eu16 value);

// Put value nn into n.
void opcode_ld_n_nn(WordReg_p reg);
void opcode_ld_sp_hl();
void opcode_ldhl_sp_n();
void opcode_ld_nn_sp();
void opcode_push_nn(WordReg_p reg);
void opcode_pop_nn(WordReg_p reg);

// ----------- 3.3.3. 8-Bit ALU ----------------
void opcode_add_a_n(eu8 n);
void opcode_adc_a_n(eu8 n);
void opcode_sub_n(eu8 n);
void opcode_sbc_a_n(eu8 n);
void opcode_and_n(eu8 value);
void opcode_or_n(eu8 val);
void opcode_xor_n(eu8 val);
void opcode_cp_n(eu8 n);
void opcode_inc_n(ByteReg_p n);
void opcode_inc_n_addr(RamAddr address);
void opcode_dec_n(ByteReg_p reg);
void opcode_dec_n_addr(RamAddr address);

// ----------- 3.3.4. 16 - Bit Arithmetic -----------
void opcode_add_hl_n(WordReg_p reg);
void opcode_add_sp_n();
void opcode_inc_nn(WordReg_p reg);
void opcode_dec_nn(WordReg_p reg);

// ----------- 3.3.5. Miscellaneous -----------
void opcode_cb_swap_n(ByteReg_p reg);
void opcode_cb_swap_n_addr(RamAddr address);
void opcode_daa();
void opcode_cpl();
void opcode_ccf();
void opcode_scf();
void opcode_nop();
void opcode_halt();
void opcode_stop();
void opcode_di();
void opcode_ei();

// ----------- 3.3.6. Rotates & Shifts -----------
void opcode_rlca();
void opcode_rla();
void opcode_rrca();
void opcode_rra();
void opcode_cb_rlc_n(ByteReg_p reg);
void opcode_cb_rlc_n_addr(RamAddr addr);
void opcode_cb_rl_n(ByteReg_p reg);
void opcode_cb_rl_n_addr(RamAddr addr);
void opcode_cb_rrc_n(ByteReg_p reg);
void opcode_cb_rrc_n_addr(RamAddr addr);
void opcode_cb_rr_n(ByteReg_p reg);
void opcode_cb_rr_n_addr(RamAddr address);
void opcode_cb_sla_n(ByteReg_p reg);
void opcode_cb_sla_n_addr(RamAddr addr);
void opcode_cb_sra_n(ByteReg_p reg);
void opcode_cb_sra_n_addr(RamAddr addr);
void opcode_cb_srl_n(ByteReg_p reg);
void opcode_cb_srl_n_addr(RamAddr address);

// ----------- 3.3.7. Bit Opcodes -----------
void opcode_cb_bit_b_r(eu8 val, eu8 bit);
void opcode_cb_set_b_r(ByteReg_p reg, eu8 bit);
void opcode_cb_set_b_r_addr(RamAddr addr, eu8 bit);
void opcode_cb_res_b_r(ByteReg_p reg, eu8 bit);
void opcode_cb_res_b_r_addr(RamAddr addr, eu8 bit);

// ----------- 3.3.8. Jumps -----------
void opcode_jp_nn();
void opcode_jp_cc_nn(bool condition);
void opcode_jp_hl();
void opcode_jr_n();
void opcode_jr_cc_n(bool condition);

// ----------- 3.3.9. Calls -----------
void opcode_call_nn();
void opcode_call_cc_nn(bool condition);

// ----------- 3.3.10. Restarts -----------
void opcode_rst_n(eu8 n);

// ----------- 3.3.11. Returns -----------
void opcode_ret();
void opcode_ret_cc(bool condition);
void opcode_reti();

// ----------- undefine -----------
