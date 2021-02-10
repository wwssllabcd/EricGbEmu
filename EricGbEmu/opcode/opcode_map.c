

#include "opcode_map.h"
#include "header.h"

#define GEN_FUN_MAP(NAME, NUM) \
op_##NAME##NUM##0, op_##NAME##NUM##1, op_##NAME##NUM##2, op_##NAME##NUM##3, \
op_##NAME##NUM##4, op_##NAME##NUM##5, op_##NAME##NUM##6, op_##NAME##NUM##7, \
op_##NAME##NUM##8, op_##NAME##NUM##9, op_##NAME##NUM##A, op_##NAME##NUM##B, \
op_##NAME##NUM##C, op_##NAME##NUM##D, op_##NAME##NUM##E, op_##NAME##NUM##F  \



#include "opcode_map.h"
#include "opcode_impl.h"
#include "cpu.h"
#include "mmu.h"

#define nn (fetch_word())
#define RAM_VAL_HL get_ram(REG_HL)

void not_support_cb() { ASSERT_CODE(0, "not support CB opcode"); }
void opcode_not_support_opcode() { ASSERT_CODE(0, "not support opcode"); }

//--------------------------------
void op_00() { opcode_nop(); }
void op_01() { opcode_ld_n_nn(bc); }
void op_02() { opcode_ld_n_a_addr(REG_BC); }
void op_03() { opcode_inc_nn(bc); }
void op_04() { opcode_inc_n(b); }
void op_05() { opcode_dec_n(b); }
void op_06() { opcode_ld_nn_n(b); }
void op_07() { opcode_rlca(); }
void op_08() { opcode_ld_nn_sp(); }
void op_09() { opcode_add_hl_n(bc); }
void op_0A() { opcode_ld_r1_r2(a, get_ram(REG_BC)); }
void op_0B() { opcode_dec_nn(bc); }
void op_0C() { opcode_inc_n(c); }
void op_0D() { opcode_dec_n(c); }
void op_0E() { opcode_ld_nn_n(c); }
void op_0F() { opcode_rrca(); }

void op_10() { opcode_not_support_opcode(); }
void op_11() { opcode_ld_n_nn(de); }
void op_12() { opcode_ld_n_a_addr(REG_DE); }
void op_13() { opcode_inc_nn(de); }
void op_14() { opcode_inc_n(d); }
void op_15() { opcode_dec_n(d); }
void op_16() { opcode_ld_nn_n(d); }
void op_17() { opcode_rla(); }
void op_18() { opcode_jr_n(); }
void op_19() { opcode_add_hl_n(de); }
void op_1A() { opcode_ld_r1_r2(a, get_ram(REG_DE)); }
void op_1B() { opcode_dec_nn(de); }
void op_1C() { opcode_inc_n(e); }
void op_1D() { opcode_dec_n(e); }
void op_1E() { opcode_ld_nn_n(e); }
void op_1F() { opcode_rra(); }

void op_20() { opcode_jr_cc_n(FLAG_NZ); }
void op_21() { opcode_ld_n_nn(hl); }
void op_22() { opcode_ldi_hl_a(); }
void op_23() { opcode_inc_nn(hl); }
void op_24() { opcode_inc_n(h); }
void op_25() { opcode_dec_n(h); }
void op_26() { opcode_ld_nn_n(h); }
void op_27() { opcode_daa(); }

void op_28() { opcode_jr_cc_n(FLAG_Z); }
void op_29() { opcode_add_hl_n(hl); }
void op_2A() { opcode_ldi_a_hl(); }
void op_2B() { opcode_dec_nn(hl); }
void op_2C() { opcode_inc_n(l); }
void op_2D() { opcode_dec_n(l); }
void op_2E() { opcode_ld_nn_n(l); }
void op_2F() { opcode_cpl(); }

void op_30() { opcode_jr_cc_n(FLAG_NC); }
void op_31() { opcode_ld_n_nn(sp); }
void op_32() { opcode_ldd_hl_a(); }
void op_33() { opcode_inc_nn(sp); }
void op_34() { opcode_inc_n_addr(REG_HL); }
void op_35() { opcode_dec_n_addr(REG_HL); }
void op_36() { opcode_ld_r1_r2_addr(REG_HL, fetch()); }
void op_37() { opcode_scf(); }

void op_38() { opcode_jr_cc_n(FLAG_C); }
void op_39() { opcode_add_hl_n(sp); }
void op_3A() { opcode_ldd_a_hl(); }
void op_3B() { opcode_dec_nn(sp); }
void op_3C() { opcode_inc_n(a); }
void op_3D() { opcode_dec_n(a); }
void op_3E() { opcode_ld_r1_r2(a, fetch()); }
void op_3F() { opcode_ccf(); }

void op_40() { opcode_ld_r1_r2(b, REG_B); }
void op_41() { opcode_ld_r1_r2(b, REG_C); }
void op_42() { opcode_ld_r1_r2(b, REG_D); }
void op_43() { opcode_ld_r1_r2(b, REG_E); }
void op_44() { opcode_ld_r1_r2(b, REG_H); }
void op_45() { opcode_ld_r1_r2(b, REG_L); }
void op_46() { opcode_ld_r1_r2(b, RAM_VAL_HL); }
void op_47() { opcode_ld_n_a(b); }
void op_48() { opcode_ld_r1_r2(c, REG_B); }
void op_49() { opcode_ld_r1_r2(c, REG_C); }
void op_4A() { opcode_ld_r1_r2(c, REG_D); }
void op_4B() { opcode_ld_r1_r2(c, REG_E); }
void op_4C() { opcode_ld_r1_r2(c, REG_H); }
void op_4D() { opcode_ld_r1_r2(c, REG_L); }
void op_4E() { opcode_ld_r1_r2(c, RAM_VAL_HL); }
void op_4F() { opcode_ld_n_a(c); }

void op_50() { opcode_ld_r1_r2(d, REG_B); }
void op_51() { opcode_ld_r1_r2(d, REG_C); }
void op_52() { opcode_ld_r1_r2(d, REG_D); }
void op_53() { opcode_ld_r1_r2(d, REG_E); }
void op_54() { opcode_ld_r1_r2(d, REG_H); }
void op_55() { opcode_ld_r1_r2(d, REG_L); }
void op_56() { opcode_ld_r1_r2(d, RAM_VAL_HL); }
void op_57() { opcode_ld_n_a(d); }
void op_58() { opcode_ld_r1_r2(e, REG_B); }
void op_59() { opcode_ld_r1_r2(e, REG_C); }
void op_5A() { opcode_ld_r1_r2(e, REG_D); }
void op_5B() { opcode_ld_r1_r2(e, REG_E); }
void op_5C() { opcode_ld_r1_r2(e, REG_H); }
void op_5D() { opcode_ld_r1_r2(e, REG_L); }
void op_5E() { opcode_ld_r1_r2(e, RAM_VAL_HL); }
void op_5F() { opcode_ld_n_a(e); }

void op_60() { opcode_ld_r1_r2(h, REG_B); }
void op_61() { opcode_ld_r1_r2(h, REG_C); }
void op_62() { opcode_ld_r1_r2(h, REG_D); }
void op_63() { opcode_ld_r1_r2(h, REG_E); }
void op_64() { opcode_ld_r1_r2(h, REG_H); }
void op_65() { opcode_ld_r1_r2(h, REG_L); }
void op_66() { opcode_ld_r1_r2(h, RAM_VAL_HL); }
void op_67() { opcode_ld_n_a(h); }
void op_68() { opcode_ld_r1_r2(l, REG_B); }
void op_69() { opcode_ld_r1_r2(l, REG_C); }
void op_6A() { opcode_ld_r1_r2(l, REG_D); }
void op_6B() { opcode_ld_r1_r2(l, REG_E); }
void op_6C() { opcode_ld_r1_r2(l, REG_H); }
void op_6D() { opcode_ld_r1_r2(l, REG_L); }
void op_6E() { opcode_ld_r1_r2(l, RAM_VAL_HL); }
void op_6F() { opcode_ld_n_a(l); }

void op_70() { opcode_ld_r1_r2_addr(REG_HL, REG_B); }
void op_71() { opcode_ld_r1_r2_addr(REG_HL, REG_C); }
void op_72() { opcode_ld_r1_r2_addr(REG_HL, REG_D); }
void op_73() { opcode_ld_r1_r2_addr(REG_HL, REG_E); }
void op_74() { opcode_ld_r1_r2_addr(REG_HL, REG_H); }
void op_75() { opcode_ld_r1_r2_addr(REG_HL, REG_L); }
void op_76() { opcode_halt(); }
void op_77() { opcode_ld_n_a_addr(REG_HL); }

// the same with opcode_ld_a_n
void op_78() { opcode_ld_r1_r2(a, REG_B); }
void op_79() { opcode_ld_r1_r2(a, REG_C); }
void op_7A() { opcode_ld_r1_r2(a, REG_D); }
void op_7B() { opcode_ld_r1_r2(a, REG_E); }
void op_7C() { opcode_ld_r1_r2(a, REG_H); }
void op_7D() { opcode_ld_r1_r2(a, REG_L); }
void op_7E() { opcode_ld_r1_r2(a, RAM_VAL_HL); }
void op_7F() { opcode_ld_r1_r2(a, REG_A); }

void op_80() { opcode_add_a_n(REG_B); }
void op_81() { opcode_add_a_n(REG_C); }
void op_82() { opcode_add_a_n(REG_D); }
void op_83() { opcode_add_a_n(REG_E); }
void op_84() { opcode_add_a_n(REG_H); }
void op_85() { opcode_add_a_n(REG_L); }
void op_86() { opcode_add_a_n(RAM_VAL_HL); }
void op_87() { opcode_add_a_n(REG_A); }

void op_88() { opcode_adc_a_n(REG_B); }
void op_89() { opcode_adc_a_n(REG_C); }
void op_8A() { opcode_adc_a_n(REG_D); }
void op_8B() { opcode_adc_a_n(REG_E); }
void op_8C() { opcode_adc_a_n(REG_H); }
void op_8D() { opcode_adc_a_n(REG_L); }
void op_8E() { opcode_adc_a_n(RAM_VAL_HL); }
void op_8F() { opcode_adc_a_n(REG_A); }

void op_90() { opcode_sub_n(REG_B); }
void op_91() { opcode_sub_n(REG_C); }
void op_92() { opcode_sub_n(REG_D); }
void op_93() { opcode_sub_n(REG_E); }
void op_94() { opcode_sub_n(REG_H); }
void op_95() { opcode_sub_n(REG_L); }
void op_96() { opcode_sub_n(RAM_VAL_HL); }
void op_97() { opcode_sub_n(REG_A); }

void op_98() { opcode_sbc_a_n(REG_B); }
void op_99() { opcode_sbc_a_n(REG_C); }
void op_9A() { opcode_sbc_a_n(REG_D); }
void op_9B() { opcode_sbc_a_n(REG_E); }
void op_9C() { opcode_sbc_a_n(REG_H); }
void op_9D() { opcode_sbc_a_n(REG_L); }
void op_9E() { opcode_sbc_a_n(RAM_VAL_HL); }
void op_9F() { opcode_sbc_a_n(REG_A); }

void op_A0() { opcode_and_n(REG_B); }
void op_A1() { opcode_and_n(REG_C); }
void op_A2() { opcode_and_n(REG_D); }
void op_A3() { opcode_and_n(REG_E); }
void op_A4() { opcode_and_n(REG_H); }
void op_A5() { opcode_and_n(REG_L); }
void op_A6() { opcode_and_n(RAM_VAL_HL); }
void op_A7() { opcode_and_n(REG_A); }

void op_A8() { opcode_xor_n(REG_B); }
void op_A9() { opcode_xor_n(REG_C); }
void op_AA() { opcode_xor_n(REG_D); }
void op_AB() { opcode_xor_n(REG_E); }
void op_AC() { opcode_xor_n(REG_H); }
void op_AD() { opcode_xor_n(REG_L); }
void op_AE() { opcode_xor_n(RAM_VAL_HL); }
void op_AF() { opcode_xor_n(REG_A); }

void op_B0() { opcode_or_n(REG_B); }
void op_B1() { opcode_or_n(REG_C); }
void op_B2() { opcode_or_n(REG_D); }
void op_B3() { opcode_or_n(REG_E); }
void op_B4() { opcode_or_n(REG_H); }
void op_B5() { opcode_or_n(REG_L); }
void op_B6() { opcode_or_n(RAM_VAL_HL); }
void op_B7() { opcode_or_n(REG_A); }

void op_B8() { opcode_cp_n(REG_B); }
void op_B9() { opcode_cp_n(REG_C); }
void op_BA() { opcode_cp_n(REG_D); }
void op_BB() { opcode_cp_n(REG_E); }
void op_BC() { opcode_cp_n(REG_H); }
void op_BD() { opcode_cp_n(REG_L); }
void op_BE() { opcode_cp_n(RAM_VAL_HL); }
void op_BF() { opcode_cp_n(REG_A); }

void op_C0() { opcode_ret_cc(FLAG_NZ); }
void op_C1() { opcode_pop_nn(bc); }
void op_C2() { opcode_jp_cc_nn(FLAG_NZ); }
void op_C3() { opcode_jp_nn(); }
void op_C4() { opcode_call_cc_nn(FLAG_NZ); }
void op_C5() { stack_push(bc); }
void op_C6() { opcode_add_a_n(fetch()); }
void op_C7() { opcode_rst_n(0x00); }
void op_C8() { opcode_ret_cc(FLAG_Z); }
void op_C9() { opcode_ret(); }
void op_CA() { opcode_jp_cc_nn(FLAG_Z); }
void op_CB() { opcode_not_support_opcode(); }
void op_CC() { opcode_call_cc_nn(FLAG_Z); }
void op_CD() { opcode_call_nn(); }
void op_CE() { opcode_adc_a_n(fetch()); }
void op_CF() { opcode_rst_n(0x08); }

void op_D0() { opcode_ret_cc(FLAG_NC); }
void op_D1() { opcode_pop_nn(de); }
void op_D2() { opcode_jp_cc_nn(FLAG_NC); }
void op_D3() { opcode_not_support_opcode(); }
void op_D4() { opcode_call_cc_nn(FLAG_NC); }
void op_D5() { stack_push(de); }
void op_D6() { opcode_sub_n(fetch()); }
void op_D7() { opcode_rst_n(0x10); }
void op_D8() { opcode_ret_cc(FLAG_C); }
void op_D9() { opcode_reti(); }
void op_DA() { opcode_jp_cc_nn(FLAG_C); }
void op_DB() { opcode_not_support_opcode(); }
void op_DC() { opcode_call_cc_nn(FLAG_C); }
void op_DD() { opcode_not_support_opcode(); }
void op_DE() { opcode_sbc_a_n(fetch()); }
void op_DF() { opcode_rst_n(0x18); }

void op_E0() { opcode_ldh_n_a(); }
void op_E1() { opcode_pop_nn(hl); }
void op_E2() { opcode_ld_c_a(); }
void op_E3() { opcode_not_support_opcode(); }
void op_E4() { opcode_not_support_opcode(); }
void op_E5() { stack_push(hl); }
void op_E6() { opcode_and_n(fetch()); }
void op_E7() { opcode_rst_n(0x20); }
void op_E8() { opcode_add_sp_n(); }
void op_E9() { opcode_jp_hl(); }
void op_EA() { opcode_ld_n_a_addr(fetch_word()); }
void op_EB() { opcode_not_support_opcode(); }
void op_EC() { opcode_not_support_opcode(); }
void op_ED() { opcode_not_support_opcode(); }
void op_EE() { opcode_xor_n(fetch()); }
void op_EF() { opcode_rst_n(0x28); }

void op_F0() { opcode_ldh_a_n(); }
void op_F1() { opcode_pop_nn(af); }
void op_F2() { opcode_ld_a_c(); }
void op_F3() { opcode_di(); }
void op_F4() { opcode_not_support_opcode(); }
void op_F5() { stack_push(af); }
void op_F6() { opcode_or_n(fetch()); }
void op_F7() { opcode_rst_n(0x30); }
void op_F8() { opcode_ldhl_sp_n(); }

void op_F9() { opcode_ld_sp_hl(); }
void op_FA() { opcode_ld_r1_r2(a, get_ram(fetch_word())); }
void op_FB() { opcode_ei(); }
void op_FC() { opcode_not_support_opcode(); }
void op_FD() { opcode_not_support_opcode(); }
void op_FE() { opcode_cp_n(fetch()); }
void op_FF() { opcode_rst_n(0x38); }

//------------------------------------------------


void op_cb_00() { opcode_cb_rlc_n(b); }
void op_cb_01() { opcode_cb_rlc_n(c); }
void op_cb_02() { opcode_cb_rlc_n(d); }
void op_cb_03() { opcode_cb_rlc_n(e); }
void op_cb_04() { opcode_cb_rlc_n(h); }
void op_cb_05() { opcode_cb_rlc_n(l); }
void op_cb_06() { opcode_cb_rlc_n_addr(REG_HL); }
void op_cb_07() { opcode_cb_rlc_n(a); }
void op_cb_08() { opcode_cb_rrc_n(b); }
void op_cb_09() { opcode_cb_rrc_n(c); }
void op_cb_0A() { opcode_cb_rrc_n(d); }
void op_cb_0B() { opcode_cb_rrc_n(e); }
void op_cb_0C() { opcode_cb_rrc_n(h); }
void op_cb_0D() { opcode_cb_rrc_n(l); }
void op_cb_0E() { opcode_cb_rrc_n_addr(REG_HL); }
void op_cb_0F() { opcode_cb_rrc_n(a); }

void op_cb_10() { opcode_cb_rl_n(b); }
void op_cb_11() { opcode_cb_rl_n(c); }
void op_cb_12() { opcode_cb_rl_n(d); }
void op_cb_13() { opcode_cb_rl_n(e); }
void op_cb_14() { opcode_cb_rl_n(h); }
void op_cb_15() { opcode_cb_rl_n(l); }
void op_cb_16() { opcode_cb_rl_n_addr(REG_HL); }
void op_cb_17() { opcode_cb_rl_n(a); }

void op_cb_18() { opcode_cb_rr_n(b); }
void op_cb_19() { opcode_cb_rr_n(c); }
void op_cb_1A() { opcode_cb_rr_n(d); }
void op_cb_1B() { opcode_cb_rr_n(e); }
void op_cb_1C() { opcode_cb_rr_n(h); }
void op_cb_1D() { opcode_cb_rr_n(l); }
void op_cb_1E() { opcode_cb_rr_n_addr(REG_HL); }
void op_cb_1F() { opcode_cb_rr_n(a); }

void op_cb_20() { opcode_cb_sla_n(b); }
void op_cb_21() { opcode_cb_sla_n(c); }
void op_cb_22() { opcode_cb_sla_n(d); }
void op_cb_23() { opcode_cb_sla_n(e); }
void op_cb_24() { opcode_cb_sla_n(h); }
void op_cb_25() { opcode_cb_sla_n(l); }
void op_cb_26() { opcode_cb_sla_n_addr(REG_HL); }
void op_cb_27() { opcode_cb_sla_n(a); }

void op_cb_28() { opcode_cb_sra_n(b); }
void op_cb_29() { opcode_cb_sra_n(c); }
void op_cb_2A() { opcode_cb_sra_n(d); }
void op_cb_2B() { opcode_cb_sra_n(e); }
void op_cb_2C() { opcode_cb_sra_n(h); }
void op_cb_2D() { opcode_cb_sra_n(l); }
void op_cb_2E() { opcode_cb_sra_n_addr(REG_HL); }
void op_cb_2F() { opcode_cb_sra_n(a); }

void op_cb_30() { opcode_cb_swap_n(b); }
void op_cb_31() { opcode_cb_swap_n(c); }
void op_cb_32() { opcode_cb_swap_n(d); }
void op_cb_33() { opcode_cb_swap_n(e); }
void op_cb_34() { opcode_cb_swap_n(h); }
void op_cb_35() { opcode_cb_swap_n(l); }
void op_cb_36() { opcode_cb_swap_n_addr(REG_HL); }
void op_cb_37() { opcode_cb_swap_n(a); }

void op_cb_38() { opcode_cb_srl_n(b); }
void op_cb_39() { opcode_cb_srl_n(c); }
void op_cb_3A() { opcode_cb_srl_n(d); }
void op_cb_3B() { opcode_cb_srl_n(e); }
void op_cb_3C() { opcode_cb_srl_n(h); }
void op_cb_3D() { opcode_cb_srl_n(l); }
void op_cb_3E() { opcode_cb_srl_n_addr(REG_HL); }
void op_cb_3F() { opcode_cb_srl_n(a); }
void op_cb_40() { opcode_cb_bit_b_r(REG_B, 0); }
void op_cb_41() { opcode_cb_bit_b_r(REG_C, 0); }
void op_cb_42() { opcode_cb_bit_b_r(REG_D, 0); }
void op_cb_43() { opcode_cb_bit_b_r(REG_E, 0); }
void op_cb_44() { opcode_cb_bit_b_r(REG_H, 0); }
void op_cb_45() { opcode_cb_bit_b_r(REG_L, 0); }
void op_cb_46() { opcode_cb_bit_b_r(RAM_VAL_HL, 0); }
void op_cb_47() { opcode_cb_bit_b_r(REG_A, 0); }
void op_cb_48() { opcode_cb_bit_b_r(REG_B, 1); }
void op_cb_49() { opcode_cb_bit_b_r(REG_C, 1); }
void op_cb_4A() { opcode_cb_bit_b_r(REG_D, 1); }
void op_cb_4B() { opcode_cb_bit_b_r(REG_E, 1); }
void op_cb_4C() { opcode_cb_bit_b_r(REG_H, 1); }
void op_cb_4D() { opcode_cb_bit_b_r(REG_L, 1); }
void op_cb_4E() { opcode_cb_bit_b_r(RAM_VAL_HL, 1); }
void op_cb_4F() { opcode_cb_bit_b_r(REG_A, 1); }

void op_cb_50() { opcode_cb_bit_b_r(REG_B, 2); }
void op_cb_51() { opcode_cb_bit_b_r(REG_C, 2); }
void op_cb_52() { opcode_cb_bit_b_r(REG_D, 2); }
void op_cb_53() { opcode_cb_bit_b_r(REG_E, 2); }
void op_cb_54() { opcode_cb_bit_b_r(REG_H, 2); }
void op_cb_55() { opcode_cb_bit_b_r(REG_L, 2); }
void op_cb_56() { opcode_cb_bit_b_r(RAM_VAL_HL, 2); }
void op_cb_57() { opcode_cb_bit_b_r(REG_A, 2); }
void op_cb_58() { opcode_cb_bit_b_r(REG_B, 3); }
void op_cb_59() { opcode_cb_bit_b_r(REG_C, 3); }
void op_cb_5A() { opcode_cb_bit_b_r(REG_D, 3); }
void op_cb_5B() { opcode_cb_bit_b_r(REG_E, 3); }
void op_cb_5C() { opcode_cb_bit_b_r(REG_H, 3); }
void op_cb_5D() { opcode_cb_bit_b_r(REG_L, 3); }
void op_cb_5E() { opcode_cb_bit_b_r(RAM_VAL_HL, 3); }
void op_cb_5F() { opcode_cb_bit_b_r(REG_A, 3); }

void op_cb_60() { opcode_cb_bit_b_r(REG_B, 4); }
void op_cb_61() { opcode_cb_bit_b_r(REG_C, 4); }
void op_cb_62() { opcode_cb_bit_b_r(REG_D, 4); }
void op_cb_63() { opcode_cb_bit_b_r(REG_E, 4); }
void op_cb_64() { opcode_cb_bit_b_r(REG_H, 4); }
void op_cb_65() { opcode_cb_bit_b_r(REG_L, 4); }
void op_cb_66() { opcode_cb_bit_b_r(RAM_VAL_HL, 4); }
void op_cb_67() { opcode_cb_bit_b_r(REG_A, 4); }

void op_cb_68() { opcode_cb_bit_b_r(REG_B, 5); }
void op_cb_69() { opcode_cb_bit_b_r(REG_C, 5); }
void op_cb_6A() { opcode_cb_bit_b_r(REG_D, 5); }
void op_cb_6B() { opcode_cb_bit_b_r(REG_E, 5); }
void op_cb_6C() { opcode_cb_bit_b_r(REG_H, 5); }
void op_cb_6D() { opcode_cb_bit_b_r(REG_L, 5); }
void op_cb_6E() { opcode_cb_bit_b_r(RAM_VAL_HL, 5); }
void op_cb_6F() { opcode_cb_bit_b_r(REG_A, 5); }

void op_cb_70() { opcode_cb_bit_b_r(REG_B, 6); }
void op_cb_71() { opcode_cb_bit_b_r(REG_C, 6); }
void op_cb_72() { opcode_cb_bit_b_r(REG_D, 6); }
void op_cb_73() { opcode_cb_bit_b_r(REG_E, 6); }
void op_cb_74() { opcode_cb_bit_b_r(REG_H, 6); }
void op_cb_75() { opcode_cb_bit_b_r(REG_L, 6); }
void op_cb_76() { opcode_cb_bit_b_r(RAM_VAL_HL, 6); }
void op_cb_77() { opcode_cb_bit_b_r(REG_A, 6); }

void op_cb_78() { opcode_cb_bit_b_r(REG_B, 7); }
void op_cb_79() { opcode_cb_bit_b_r(REG_C, 7); }
void op_cb_7A() { opcode_cb_bit_b_r(REG_D, 7); }
void op_cb_7B() { opcode_cb_bit_b_r(REG_E, 7); }
void op_cb_7C() { opcode_cb_bit_b_r(REG_H, 7); }
void op_cb_7D() { opcode_cb_bit_b_r(REG_L, 7); }
void op_cb_7E() { opcode_cb_bit_b_r(RAM_VAL_HL, 7); }
void op_cb_7F() { opcode_cb_bit_b_r(REG_A, 7); }

void op_cb_80() { opcode_cb_res_b_r(b, 0); }
void op_cb_81() { opcode_cb_res_b_r(c, 0); }
void op_cb_82() { opcode_cb_res_b_r(d, 0); }
void op_cb_83() { opcode_cb_res_b_r(e, 0); }
void op_cb_84() { opcode_cb_res_b_r(h, 0); }
void op_cb_85() { opcode_cb_res_b_r(l, 0); }
void op_cb_86() { opcode_cb_res_b_r_addr(REG_HL, 0); }
void op_cb_87() { opcode_cb_res_b_r(a, 0); }

void op_cb_88() { opcode_cb_res_b_r(b, 1); }
void op_cb_89() { opcode_cb_res_b_r(c, 1); }
void op_cb_8A() { opcode_cb_res_b_r(d, 1); }
void op_cb_8B() { opcode_cb_res_b_r(e, 1); }
void op_cb_8C() { opcode_cb_res_b_r(h, 1); }
void op_cb_8D() { opcode_cb_res_b_r(l, 1); }
void op_cb_8E() { opcode_cb_res_b_r_addr(REG_HL, 1); }
void op_cb_8F() { opcode_cb_res_b_r(a, 1); }

void op_cb_90() { opcode_cb_res_b_r(b, 2); }
void op_cb_91() { opcode_cb_res_b_r(c, 2); }
void op_cb_92() { opcode_cb_res_b_r(d, 2); }
void op_cb_93() { opcode_cb_res_b_r(e, 2); }
void op_cb_94() { opcode_cb_res_b_r(h, 2); }
void op_cb_95() { opcode_cb_res_b_r(l, 2); }
void op_cb_96() { opcode_cb_res_b_r_addr(REG_HL, 2); }
void op_cb_97() { opcode_cb_res_b_r(a, 2); }

void op_cb_98() { opcode_cb_res_b_r(b, 3); }
void op_cb_99() { opcode_cb_res_b_r(c, 3); }
void op_cb_9A() { opcode_cb_res_b_r(d, 3); }
void op_cb_9B() { opcode_cb_res_b_r(e, 3); }
void op_cb_9C() { opcode_cb_res_b_r(h, 3); }
void op_cb_9D() { opcode_cb_res_b_r(l, 3); }
void op_cb_9E() { opcode_cb_res_b_r_addr(REG_HL, 3); }
void op_cb_9F() { opcode_cb_res_b_r(a, 3); }

void op_cb_A0() { opcode_cb_res_b_r(b, 4); }
void op_cb_A1() { opcode_cb_res_b_r(c, 4); }
void op_cb_A2() { opcode_cb_res_b_r(d, 4); }
void op_cb_A3() { opcode_cb_res_b_r(e, 4); }
void op_cb_A4() { opcode_cb_res_b_r(h, 4); }
void op_cb_A5() { opcode_cb_res_b_r(l, 4); }
void op_cb_A6() { opcode_cb_res_b_r_addr(REG_HL, 4); }
void op_cb_A7() { opcode_cb_res_b_r(a, 4); }
void op_cb_A8() { opcode_cb_res_b_r(b, 5); }
void op_cb_A9() { opcode_cb_res_b_r(c, 5); }
void op_cb_AA() { opcode_cb_res_b_r(d, 5); }
void op_cb_AB() { opcode_cb_res_b_r(e, 5); }
void op_cb_AC() { opcode_cb_res_b_r(h, 5); }
void op_cb_AD() { opcode_cb_res_b_r(l, 5); }
void op_cb_AE() { opcode_cb_res_b_r_addr(REG_HL, 5); }
void op_cb_AF() { opcode_cb_res_b_r(a, 5); }

void op_cb_B0() { opcode_cb_res_b_r(b, 6); }
void op_cb_B1() { opcode_cb_res_b_r(c, 6); }
void op_cb_B2() { opcode_cb_res_b_r(d, 6); }
void op_cb_B3() { opcode_cb_res_b_r(e, 6); }
void op_cb_B4() { opcode_cb_res_b_r(h, 6); }
void op_cb_B5() { opcode_cb_res_b_r(l, 6); }
void op_cb_B6() { opcode_cb_res_b_r_addr(REG_HL, 6); }
void op_cb_B7() { opcode_cb_res_b_r(a, 6); }

void op_cb_B8() { opcode_cb_res_b_r(b, 7); }
void op_cb_B9() { opcode_cb_res_b_r(c, 7); }
void op_cb_BA() { opcode_cb_res_b_r(d, 7); }
void op_cb_BB() { opcode_cb_res_b_r(e, 7); }
void op_cb_BC() { opcode_cb_res_b_r(h, 7); }
void op_cb_BD() { opcode_cb_res_b_r(l, 7); }
void op_cb_BE() { opcode_cb_res_b_r_addr(REG_HL, 7); }
void op_cb_BF() { opcode_cb_res_b_r(a, 7); }

void op_cb_C0() { opcode_cb_set_b_r(b, 0); }
void op_cb_C1() { opcode_cb_set_b_r(c, 0); }
void op_cb_C2() { opcode_cb_set_b_r(d, 0); }
void op_cb_C3() { opcode_cb_set_b_r(e, 0); }
void op_cb_C4() { opcode_cb_set_b_r(h, 0); }
void op_cb_C5() { opcode_cb_set_b_r(l, 0); }
void op_cb_C6() { opcode_cb_set_b_r_addr(REG_HL, 0); }
void op_cb_C7() { opcode_cb_set_b_r(a, 0); }

void op_cb_C8() { opcode_cb_set_b_r(b, 1); }
void op_cb_C9() { opcode_cb_set_b_r(c, 1); }
void op_cb_CA() { opcode_cb_set_b_r(d, 1); }
void op_cb_CB() { opcode_cb_set_b_r(e, 1); }
void op_cb_CC() { opcode_cb_set_b_r(h, 1); }
void op_cb_CD() { opcode_cb_set_b_r(l, 1); }
void op_cb_CE() { opcode_cb_set_b_r_addr(REG_HL, 1); }
void op_cb_CF() { opcode_cb_set_b_r(a, 1); }

void op_cb_D0() { opcode_cb_set_b_r(b, 2); }
void op_cb_D1() { opcode_cb_set_b_r(c, 2); }
void op_cb_D2() { opcode_cb_set_b_r(d, 2); }
void op_cb_D3() { opcode_cb_set_b_r(e, 2); }
void op_cb_D4() { opcode_cb_set_b_r(h, 2); }
void op_cb_D5() { opcode_cb_set_b_r(l, 2); }
void op_cb_D6() { opcode_cb_set_b_r_addr(REG_HL, 2); }
void op_cb_D7() { opcode_cb_set_b_r(a, 2); }

void op_cb_D8() { opcode_cb_set_b_r(b, 3); }
void op_cb_D9() { opcode_cb_set_b_r(c, 3); }
void op_cb_DA() { opcode_cb_set_b_r(d, 3); }
void op_cb_DB() { opcode_cb_set_b_r(e, 3); }
void op_cb_DC() { opcode_cb_set_b_r(h, 3); }
void op_cb_DD() { opcode_cb_set_b_r(l, 3); }
void op_cb_DE() { opcode_cb_set_b_r_addr(REG_HL, 3); }
void op_cb_DF() { opcode_cb_set_b_r(a, 3); }

void op_cb_E0() { opcode_cb_set_b_r(b, 4); }
void op_cb_E1() { opcode_cb_set_b_r(c, 4); }
void op_cb_E2() { opcode_cb_set_b_r(d, 4); }
void op_cb_E3() { opcode_cb_set_b_r(e, 4); }
void op_cb_E4() { opcode_cb_set_b_r(h, 4); }
void op_cb_E5() { opcode_cb_set_b_r(l, 4); }
void op_cb_E6() { opcode_cb_set_b_r_addr(REG_HL, 4); }
void op_cb_E7() { opcode_cb_set_b_r(a, 4); }

void op_cb_E8() { opcode_cb_set_b_r(b, 5); }
void op_cb_E9() { opcode_cb_set_b_r(c, 5); }
void op_cb_EA() { opcode_cb_set_b_r(d, 5); }
void op_cb_EB() { opcode_cb_set_b_r(e, 5); }
void op_cb_EC() { opcode_cb_set_b_r(h, 5); }
void op_cb_ED() { opcode_cb_set_b_r(l, 5); }
void op_cb_EE() { opcode_cb_set_b_r_addr(REG_HL, 5); }
void op_cb_EF() { opcode_cb_set_b_r(a, 5); }

void op_cb_F0() { opcode_cb_set_b_r(b, 6); }
void op_cb_F1() { opcode_cb_set_b_r(c, 6); }
void op_cb_F2() { opcode_cb_set_b_r(d, 6); }
void op_cb_F3() { opcode_cb_set_b_r(e, 6); }
void op_cb_F4() { opcode_cb_set_b_r(h, 6); }
void op_cb_F5() { opcode_cb_set_b_r(l, 6); }
void op_cb_F6() { opcode_cb_set_b_r_addr(REG_HL, 6); }
void op_cb_F7() { opcode_cb_set_b_r(a, 6); }

void op_cb_F8() { opcode_cb_set_b_r(b, 7); }
void op_cb_F9() { opcode_cb_set_b_r(c, 7); }
void op_cb_FA() { opcode_cb_set_b_r(d, 7); }
void op_cb_FB() { opcode_cb_set_b_r(e, 7); }
void op_cb_FC() { opcode_cb_set_b_r(h, 7); }
void op_cb_FD() { opcode_cb_set_b_r(l, 7); }
void op_cb_FE() { opcode_cb_set_b_r_addr(REG_HL, 7); }
void op_cb_FF() { opcode_cb_set_b_r(a, 7); }

OpcodeFun g_opcodeFunMap_cb[0x100] = { 
    GEN_FUN_MAP(cb_, 0), GEN_FUN_MAP(cb_, 1), GEN_FUN_MAP(cb_, 2), GEN_FUN_MAP(cb_, 3), 
    GEN_FUN_MAP(cb_, 4), GEN_FUN_MAP(cb_, 5), GEN_FUN_MAP(cb_, 6), GEN_FUN_MAP(cb_, 7), 
    GEN_FUN_MAP(cb_, 8), GEN_FUN_MAP(cb_, 9), GEN_FUN_MAP(cb_, A), GEN_FUN_MAP(cb_, B),
    GEN_FUN_MAP(cb_, C), GEN_FUN_MAP(cb_, D), GEN_FUN_MAP(cb_, E), GEN_FUN_MAP(cb_, F) 
};

OpcodeFun g_opcodeFunMap[0x100] = { 
    GEN_FUN_MAP(, 0), GEN_FUN_MAP(, 1), GEN_FUN_MAP(, 2), GEN_FUN_MAP(, 3), 
    GEN_FUN_MAP(, 4), GEN_FUN_MAP(, 5), GEN_FUN_MAP(, 6), GEN_FUN_MAP(, 7),
    GEN_FUN_MAP(, 8), GEN_FUN_MAP(, 9), GEN_FUN_MAP(, A), GEN_FUN_MAP(, B), 
    GEN_FUN_MAP(, C), GEN_FUN_MAP(, D), GEN_FUN_MAP(, E), GEN_FUN_MAP(, F) 
};
