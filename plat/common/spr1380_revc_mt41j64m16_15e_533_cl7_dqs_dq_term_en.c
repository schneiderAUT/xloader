/*
 * based on denaly webttol https://www.denali.com/en/support/databahn/genregs.jsp?p=ZD0xMjQyNzY0NzEzNjA4JmM9NTUwMjI4Mw==&flow=select#DDR3SDRAM
 */
/* ********************************************************************
// Option: IP Mode                      = CTL
// Option: Burst Length                  = 8
// Option: CAS Latency                   = 7
// Option: Simulation MHz                = 533
// Memory: mt41j64m16_15e
   ********************************************************************
*/

#include <common.h>

#if defined(CONFIG_SPEAR1380_REVC)

const u32 mpmc_conf_vals[CONFIG_SPEAR_MPMCREGS] = {
        0x00000100,                /* ; DENALI_CTL_00 : 0000000_0 arefresh(WR) 0000000_0 ap(RW) 0000000_1 addr_cmp_en(RW) 00000000 */
        0x00010100,                /* ; DENALI_CTL_01 : 000000000000000_1 concurrentap(RW) 0000000_1 bank_split_en(RW) 0000000_0 auto_refresh_mode(RW)  */
        0x01000000,                /* ; DENALI_CTL_02 : 0000000_1 drive_dq_dqs(RW) 000000000000000000000000 */
     /* 0x00010100, */             /* ; DENALI_CTL_03 : 000000000000000_1 enable_quick_srefresh(RW) 0000000_1 eight_bank_mode(RW) 0000000_0 ecc_disable_w_uc_err(RW)  */
#ifdef CONFIG_DDR_ECC_ENABLE
	0x00000101,
#else
	0x00000100,
#endif
        0x00000000,                /* ; DENALI_CTL_04 : 0000000000000000000000000000000_0 fwc(WR)  */
     /* 0x00010100, */             /* ; DENALI_CTL_05 : 0000000_0 power_down(RW) 0000000_1 placement_en(RW) 0000000_1 odt_alt_en(RW) 0000000_0 no_cmd_init(RW)  */
        0x00010101,                /* ; DENALI_CTL_05 : Disable DRAM cmds until TDLL expires. */
        0x00000001,                /* ; DENALI_CTL_06 : 0000000_0 rdlvl_cs(RW) 0000000_0 rdlvl_begin_delay_en(RW) 0000000_0 pwrup_srefresh_exit(RW) 0000000_1 priority_en(RW)  */
        0x00000000,                /* ; DENALI_CTL_07 : 0000000_0 rdlvl_gate_preamble_check_en(RW) 0000000_0 rdlvl_gate_en(RW) 0000000_0 rdlvl_en(RW) 0000000_0 rdlvl_edge(RW)  */
        0x00000000,                /* ; DENALI_CTL_08 : 0000000_0 rdlvl_offset_dir_1(RW) 0000000_0 rdlvl_offset_dir_0(RW) 0000000_0 rdlvl_gate_req(WR) 0000000_0 rdlvl_gate_reg_en(RW)  */
        0x00000000,                /* ; DENALI_CTL_09 : 0000000_0 rdlvl_reg_en(RW) 0000000_0 rdlvl_offset_dir_4(RW) 0000000_0 rdlvl_offset_dir_3(RW) 0000000_0 rdlvl_offset_dir_2(RW)  */
        0x00000000,                /* ; DENALI_CTL_10 : 0000000_0 resync_dll(WR) 0000000_0 reg_dimm_enable(RW) 0000000_0 reduc(RW) 0000000_0 rdlvl_req(WR)  */
        0x00000101,                /* ; DENALI_CTL_11 : 0000000_0 start(RW) 0000000_0 srefresh(RW+) 0000000_1 rw_same_en(RW) 0000000_1 resync_dll_per_aref_en(RW)  */
        0x00000101,                /* ; DENALI_CTL_12 : 0000000_0 swlvl_load(WR) 0000000_0 swlvl_exit(WR) 0000000_1 swap_port_rw_same_en(RW) 0000000_1 swap_en(RW)  */
        0x01010000,                /* ; DENALI_CTL_13 : 0000000_1 tref_enable(RW) 0000000_1 tras_lockout(RW) 0000000_0 swlvl_start(WR) 0000000_0 swlvl_op_done(RD)  */
        0x00000000,                /* ; DENALI_CTL_14 : 0000000_0 wrlvl_cs(RW) 000000000000000_0 writeinterp(RW) 0000000_0 weighted_round_robin_latency_control(RW)  */
        0x01000000,                /* ; DENALI_CTL_15 : 0000000_1 zqcs_rotate(RW) 0000000_0 wrlvl_req(WR) 0000000_0 wrlvl_reg_en(RW) 00000000 */
        0x00000000,                /* ; DENALI_CTL_16 : 000000_00 axi1_fifo_type_reg(RW) 000000_00 axi0_fifo_type_reg(RW) 000000_00 address_mirroring(RW) 0000000_0 zq_in_progress(RD)  */
        0x00000000,                /* ; DENALI_CTL_17 : 000000_00 axi5_fifo_type_reg(RW) 000000_00 axi4_fifo_type_reg(RW) 000000_00 axi3_fifo_type_reg(RW) 000000_00 axi2_fifo_type_reg(RW)  */
     /* 0x00000303, */             /* ; DENALI_CTL_18 : 000000_00 max_cs_reg(RD) 000000_00 dram_clk_disable(RW) 000000_11 ctrl_raw(RW) 000000_11 cs_map(RW)  */
#ifdef CONFIG_DDR_ECC_ENABLE
	0x00000001,                    /* ; DENALI_CTL_18 : Only one chip select enabled. ECC being used (configured later) */
#else
	0x00000201,                    /* ; DENALI_CTL_18 : Only one chip select enabled. ECC not being used */
#endif
     /* 0x02010102, */             /* ; DENALI_CTL_19 : 000000_10 odt_wr_map_cs1(RW) 000000_01 odt_wr_map_cs0(RW) 000000_01 odt_rd_map_cs1(RW) 000000_10 odt_rd_map_cs0(RW)  */
        0x00010000,                /* ; DENALI_CTL_19 : 000000_10 odt_wr_map_cs1(RW) 000000_01 odt_wr_map_cs0(RW) 000000_01 odt_rd_map_cs1(RW) 000000_10 odt_rd_map_cs0(RW)  */
        0x00020000,                /* ; DENALI_CTL_20 : 000000_00 zq_req(WR) 000000_10 zq_on_sref_exit(RW) 000000_00 sw_leveling_mode(RW) 00000000 */
        0x03030002,                /* ; DENALI_CTL_21 : 00000_011 axi0_w_priority(RW) 00000_011 axi0_r_priority(RW) 00000_000 axi0_port_ordering(RW) 00000_010 addr_pins(RW)  */
        0x02030301,                /* ; DENALI_CTL_22 : 00000_010 axi2_port_ordering(RW) 00000_011 axi1_w_priority(RW) 00000_011 axi1_r_priority(RW) 00000_001 axi1_port_ordering(RW)  */
        0x03030303,                /* ; DENALI_CTL_23 : 00000_011 axi3_r_priority(RW) 00000_011 axi3_port_ordering(RW) 00000_011 axi2_w_priority(RW) 00000_011 axi2_r_priority(RW)  */
        0x03030403,                /* ; DENALI_CTL_24 : 00000_011 axi4_w_priority(RW) 00000_011 axi4_r_priority(RW) 00000_100 axi4_port_ordering(RW) 00000_011 axi3_w_priority(RW)  */
        0x03030305,                /* ; DENALI_CTL_25 : 00000_011 bstlen(RW_D) 00000_011 axi5_w_priority(RW) 00000_011 axi5_r_priority(RW) 00000_101 axi5_port_ordering(RW)  */
        0x00000400,                /* ; DENALI_CTL_26 : 00000_000 port_data_error_type(RD) 00000_000 lvl_status(RD) 00000_100 column_size(RW) 00000_000 cke_delay(RW)  */
     /* 0x02000100, */             /* ; DENALI_CTL_27 : 00000_010 r2w_diffcs_dly(RW) 00000_000 r2r_samecs_dly(RW) 00000_001 r2r_diffcs_dly(RW) 00000_000 q_fullness(RW)  */
        0x02000100,                /* ; DENALI_CTL_27 : 00000_010 r2w_diffcs_dly(RW) 00000_000 r2r_samecs_dly(RW) 00000_001 r2r_diffcs_dly(RW) 00000_000 q_fullness(RW)  */
        0x04030402,                /* ; DENALI_CTL_28 : 00000100 trrd(RW) 00000_011 tcke(RW) 00000_100 tbst_int_interval(RW) 00000_010 r2w_samecs_dly(RW)  */
        0x01000104,                /* ; DENALI_CTL_29 : 00000_001 w2w_diffcs_dly(RW) 00000_000 w2r_samecs_dly(RW) 00000_001 w2r_diffcs_dly(RW) 0000_0100 trtp(RW)  */
        0x04000000,                /* ; DENALI_CTL_30 : 0000_0100 add_odt_clk_sametype_diffcs(RW) 0000000000000_000 weighted_round_robin_weight_sharing(RW) 00000_000 w2w_samecs_dly(RW)  */
        0x0606060a,                /* ; DENALI_CTL_31 : 0000_0110 axi0_priority2_relative_priority(RW) 0000_0110 axi0_priority1_relative_priority(RW) 0000_0110 axi0_priority0_relative_priority(RW) 0000_1010 aprebit(RW_D)  */
        0x06060606,                /* ; DENALI_CTL_32 : 0000_0110 axi0_priority6_relative_priority(RW) 0000_0110 axi0_priority5_relative_priority(RW) 0000_0110 axi0_priority4_relative_priority(RW) 0000_0110 axi0_priority3_relative_priority(RW)  */
        0x05050506,                /* ; DENALI_CTL_33 : 0000_0101 axi1_priority2_relative_priority(RW) 0000_0101 axi1_priority1_relative_priority(RW) 0000_0101 axi1_priority0_relative_priority(RW) 0000_0110 axi0_priority7_relative_priority(RW)  */
        0x05050505,                /* ; DENALI_CTL_34 : 0000_0101 axi1_priority6_relative_priority(RW) 0000_0101 axi1_priority5_relative_priority(RW) 0000_0101 axi1_priority4_relative_priority(RW) 0000_0101 axi1_priority3_relative_priority(RW)  */
        0x04040405,                /* ; DENALI_CTL_35 : 0000_0100 axi2_priority2_relative_priority(RW) 0000_0100 axi2_priority1_relative_priority(RW) 0000_0100 axi2_priority0_relative_priority(RW) 0000_0101 axi1_priority7_relative_priority(RW)  */
        0x04040404,                /* ; DENALI_CTL_36 : 0000_0100 axi2_priority6_relative_priority(RW) 0000_0100 axi2_priority5_relative_priority(RW) 0000_0100 axi2_priority4_relative_priority(RW) 0000_0100 axi2_priority3_relative_priority(RW)  */
        0x03030304,                /* ; DENALI_CTL_37 : 0000_0011 axi3_priority2_relative_priority(RW) 0000_0011 axi3_priority1_relative_priority(RW) 0000_0011 axi3_priority0_relative_priority(RW) 0000_0100 axi2_priority7_relative_priority(RW)  */
        0x03030303,                /* ; DENALI_CTL_38 : 0000_0011 axi3_priority6_relative_priority(RW) 0000_0011 axi3_priority5_relative_priority(RW) 0000_0011 axi3_priority4_relative_priority(RW) 0000_0011 axi3_priority3_relative_priority(RW)  */
        0x02020203,                /* ; DENALI_CTL_39 : 0000_0010 axi4_priority2_relative_priority(RW) 0000_0010 axi4_priority1_relative_priority(RW) 0000_0010 axi4_priority0_relative_priority(RW) 0000_0011 axi3_priority7_relative_priority(RW)  */
        0x02020202,                /* ; DENALI_CTL_40 : 0000_0010 axi4_priority6_relative_priority(RW) 0000_0010 axi4_priority5_relative_priority(RW) 0000_0010 axi4_priority4_relative_priority(RW) 0000_0010 axi4_priority3_relative_priority(RW)  */
        0x01010102,                /* ; DENALI_CTL_41 : 0000_0001 axi5_priority2_relative_priority(RW) 0000_0001 axi5_priority1_relative_priority(RW) 0000_0001 axi5_priority0_relative_priority(RW) 0000_0010 axi4_priority7_relative_priority(RW)  */
        0x01010101,                /* ; DENALI_CTL_42 : 0000_0001 axi5_priority6_relative_priority(RW) 0000_0001 axi5_priority5_relative_priority(RW) 0000_0001 axi5_priority4_relative_priority(RW) 0000_0001 axi5_priority3_relative_priority(RW)  */
        0x06000c01,                /* ; DENALI_CTL_43 : 0000_0110 dram_class(RW) 000000000000_1100 burst_on_fly_bit(RW) 0000_0001 axi5_priority7_relative_priority(RW)  */
        0x00000000,                /* ; DENALI_CTL_44 : 0000_0000 port_cmd_error_type(RD) 0000_0000 max_row_reg(RD) 0000_0000 max_col_reg(RD) 0000_0000 initaref(RW)  */
        0x00000204,                /* ; DENALI_CTL_45 : 000_00000 tdfi_phy_wrlat(RD) 0000_0000 tdfi_ctrlupd_min(RD) 0000_0010 rdlvl_gate_dq_zero_count(RW) 0000_0100 rdlvl_dq_zero_count(RW)  */
        0x04090800,                /* ; DENALI_CTL_46 : 0000_0100 twtr(RW) 0000_1001 trp_ab(RW) 0000_1000 trp(RW) 00000000 */
        0x02000606,                /* ; DENALI_CTL_47 : 00_000010 add_odt_clk_difftype_diffcs(RW) 0000_0000 wrr_param_value_err(RD) 000_00110 wrlat_adj(RW) 000_00110 wrlat(RW)  */
        0x0000000e,                /* ; DENALI_CTL_48 : 000_00000 ocd_adjust_pup_cs_0(RW) 000_00000 ocd_adjust_pdn_cs_0(RW) 0000000000_001110 caslat_lin(RW)  */
        0x10040407,                /* ; DENALI_CTL_49 : 000_10000 tdal(RW) 000_00100 tckesr(RW) 000_00100 tccd(RW) 00_000111 rdlat_adj(RW)  */
        0x0800000d,                /* ; DENALI_CTL_50 : 000_01000 tmrd(RW) 0000000000_000000 tdfi_rddata_en(RD) 00_001101 tdfi_phy_rdlat(RW_D)  */
        0x3f003f08,                /* ; DENALI_CTL_51 : 00_111111 command_age_count(RW) 00_000000 axi_aligned_strobe_disable(RW) 00_111111 age_count(RW) 000_01000 twr_int(RW)  */
        0x191b1800,                /* ; DENALI_CTL_52 : 00_011001 wldqsen(RW) 00011011 trc(RW) 00_011000 tfaw(RW) 00_000000 out_of_range_type(RD)  */
        0x00000028,                /* ; DENALI_CTL_53 : 0_0000000 ecc_c_synd(RD) 0_0000000 ecc_c_id(RD) 0_0000000 dll_lock(RD) 00_101000 wlmrd(RW)  */
        0x00000000,                /* ; DENALI_CTL_54 : 0_0000000 out_of_range_source_id(RD) 0_0000000 out_of_range_length(RD) 0_0000000 ecc_u_synd(RD) 0_0000000 ecc_u_id(RD)  */
        0x00000000,                /* ; DENALI_CTL_55 : 00000000 dll_rst_adj_dly(RW) 00000000 dft_ctrl_reg(RW) 0_0000000 port_data_error_id(RD) 0_0000000 port_cmd_error_id(RD)  */
        0x00000000,                /* ; DENALI_CTL_56 : 00000000000000000000000000000000 */
        0x00004000,                /* ; DENALI_CTL_57 : 00000000 swlvl_resp_1(RD) 00000000 swlvl_resp_0(RD) 01000000 refresh_per_zq(RW) 00000000 */
        0x03000000,                /* ; DENALI_CTL_58 : 00000011 tdfi_rdlvl_dll(RW) 00000000 swlvl_resp_4(RD) 00000000 swlvl_resp_3(RD) 00000000 swlvl_resp_2(RD)  */
        0x03031903,                /* ; DENALI_CTL_59 : 00000011 tdfi_wrlvl_en(RW) 00000011 tdfi_wrlvl_dll(RW) 00011001 tdfi_rdlvl_resplat(RW) 00000011 tdfi_rdlvl_en(RW)  */
        0x08140c04,                /* ; DENALI_CTL_60 : 00001000 trcd_int(RW) 00010100 tras_min(RW) 00001100 tmod(RW) 00000100 tdfi_wrlvl_resplat(RW)  */
        0x00006400,                /* ; DENALI_CTL_61 : 00000000000000_0001100100 axi0_priority_relax(RW) 00000000 */
        0x00640064,                /* ; DENALI_CTL_62 : 000000_0001100100 axi2_priority_relax(RW) 000000_0001100100 axi1_priority_relax(RW)  */
        0x00640064,                /* ; DENALI_CTL_63 : 000000_0001100100 axi4_priority_relax(RW) 000000_0001100100 axi3_priority_relax(RW)  */
        0x000f0064,                /* ; DENALI_CTL_64 : 000000_0000001111 tdfi_rdlvl_rr(RW) 000000_0001100100 axi5_priority_relax(RW)  */
        0x0000000a,                /* ; DENALI_CTL_65 : 0000_000000000000 wrlvl_status(RD) 000000_0000001010 tdfi_wrlvl_ww(RW)  */
        0x00400100,                /* ; DENALI_CTL_66 : 0000_000001000000 zqcs(RW) 0000_000100000000 zqcl(RW)  */
        0x102d0200,                /* ; DENALI_CTL_67 : 00_01000000101101 tdfi_ctrlupd_max(RW) 0000_001000000000 zqinit(RW_D)  */
        0x0200102d,                /* ; DENALI_CTL_68 : 0000001000000000 tdfi_phyupd_type0(RW) 00_01000000101101 tdfi_phyupd_resp(RW)  */
        0x02000200,                /* ; DENALI_CTL_69 : 0000001000000000 tdfi_phyupd_type2(RW) 0000001000000000 tdfi_phyupd_type1(RW)  */
        0x102d0200,                /* ; DENALI_CTL_70 : 00_01000000101101 tref(RW) 0000001000000000 tdfi_phyupd_type3(RW)  */
        0x08300830,                /* ; DENALI_CTL_71 : 0_000100000110000 mr0_data_1(RW) 0_000100000110000 mr0_data_0(RW)  */
     /* 0x00460046, */             /* ; DENALI_CTL_72 : 0_000000001000110 mr1_data_1(RW) 0_000000001000110 mr1_data_0(RW)  */
        0x00060006,                /* ; DENALI_CTL_72 : 0_000000001000110 mr1_data_1(RW) 0_000000001000110 mr1_data_0(RW)  */
     /* 0x00080008, */             /* ; DENALI_CTL_73 : 0_000000000001000 mr2_data_1(RW) 0_000000000001000 mr2_data_0(RW)  */
        0x00880088,                /* ; DENALI_CTL_73 : 0_000000000001000 mr2_data_1(RW) 0_000000000001000 mr2_data_0(RW)  */
        0x00000000,                /* ; DENALI_CTL_74 : 0_000000000000000 mr3_data_1(RW) 0_000000000000000 mr3_data_0(RW)  */
        0xffffffff,                /* ; DENALI_CTL_75 : 1111111111111111 axi1_en_size_lt_width_instr(RW) 1111111111111111 axi0_en_size_lt_width_instr(RW)  */
        0xffffffff,                /* ; DENALI_CTL_76 : 1111111111111111 axi3_en_size_lt_width_instr(RW) 1111111111111111 axi2_en_size_lt_width_instr(RW)  */
        0xffffffff,                /* ; DENALI_CTL_77 : 1111111111111111 axi5_en_size_lt_width_instr(RW) 1111111111111111 axi4_en_size_lt_width_instr(RW)  */
        0x00000007,                /* ; DENALI_CTL_78 : 0000000000000000 dll_rst_delay(RW) 0000000000000111 dfi_wrlvl_max_delay(RW)  */
        0x00000000,                /* ; DENALI_CTL_79 : 0000000000000000 rdlvl_begin_delay_1(RD) 0000000000000000 rdlvl_begin_delay_0(RD)  */
        0x00000000,                /* ; DENALI_CTL_80 : 0000000000000000 rdlvl_begin_delay_3(RD) 0000000000000000 rdlvl_begin_delay_2(RD)  */
        0x00070000,                /* ; DENALI_CTL_81 : 0000000000000111 rdlvl_delay_0(RW) 0000000000000000 rdlvl_begin_delay_4(RD)  */
        0x00070007,                /* ; DENALI_CTL_82 : 0000000000000111 rdlvl_delay_2(RW) 0000000000000111 rdlvl_delay_1(RW)  */
        0x00070007,                /* ; DENALI_CTL_83 : 0000000000000111 rdlvl_delay_4(RW) 0000000000000111 rdlvl_delay_3(RW)  */
        0x00000000,                /* ; DENALI_CTL_84 : 0000000000000000 rdlvl_end_delay_1(RD) 0000000000000000 rdlvl_end_delay_0(RD)  */
        0x00000000,                /* ; DENALI_CTL_85 : 0000000000000000 rdlvl_end_delay_3(RD) 0000000000000000 rdlvl_end_delay_2(RD)  */
        0x00030000,                /* ; DENALI_CTL_86 : 0000000000000011 rdlvl_gate_delay_0(RW+) 0000000000000000 rdlvl_end_delay_4(RD)  */
        0x00030003,                /* ; DENALI_CTL_87 : 0000000000000011 rdlvl_gate_delay_2(RW+) 0000000000000011 rdlvl_gate_delay_1(RW+)  */
        0x00030003,                /* ; DENALI_CTL_88 : 0000000000000011 rdlvl_gate_delay_4(RW+) 0000000000000011 rdlvl_gate_delay_3(RW+)  */
        0xffff0010,                /* ; DENALI_CTL_89 : 1111111111111111 rdlvl_max_delay(RW) 0000000000010000 rdlvl_gate_max_delay(RW)  */
        0x00000000,                /* ; DENALI_CTL_90 : 0000000000000000 rdlvl_midpoint_delay_1(RD) 0000000000000000 rdlvl_midpoint_delay_0(RD)  */
        0x00000000,                /* ; DENALI_CTL_91 : 0000000000000000 rdlvl_midpoint_delay_3(RD) 0000000000000000 rdlvl_midpoint_delay_2(RD)  */
        0x00000000,                /* ; DENALI_CTL_92 : 0000000000000000 rdlvl_offset_delay_0(RW) 0000000000000000 rdlvl_midpoint_delay_4(RD)  */
        0x00000000,                /* ; DENALI_CTL_93 : 0000000000000000 rdlvl_offset_delay_2(RW) 0000000000000000 rdlvl_offset_delay_1(RW)  */
        0x00000000,                /* ; DENALI_CTL_94 : 0000000000000000 rdlvl_offset_delay_4(RW) 0000000000000000 rdlvl_offset_delay_3(RW)  */
        0x00000000,                /* ; DENALI_CTL_95 : 00000000000000000000000000000000 */
        0x02000000,                /* ; DENALI_CTL_96 : 0000001000000000 tdll(RW) 0000000000000000 tcpd(RW)  */
        0x00000004,                /* ; DENALI_CTL_97 : 0000000000000000_0000000000000100 tpdex(RW)  */
        0x0040000d,                /* ; DENALI_CTL_98 : 0000000001000000 txsnr(RW) 0000000000001101 txpdll(RW)  */
        0x00000200,                /* ; DENALI_CTL_99 : 0000000000000000 version(RD) 0000001000000000 txsr(RW)  */
        0x00000000,                /* ; DENALI_CTL_100 : 0000000000000000 wrlvl_delay_1(RW+) 0000000000000000 wrlvl_delay_0(RW+)  */
        0x00000000,                /* ; DENALI_CTL_101 : 0000000000000000 wrlvl_delay_3(RW+) 0000000000000000 wrlvl_delay_2(RW+)  */
        0x00000000,                /* ; DENALI_CTL_102 : 0000000000000000_0000000000000000 wrlvl_delay_4(RW+)  */
        0x00000000,                /* ; DENALI_CTL_103 : 00000000000_000000000000000000000 int_ack(WR)  */
        0x00000000,                /* ; DENALI_CTL_104 : 0000000000_0000000000000000000000 int_mask(RW)  */
        0x00000000,                /* ; DENALI_CTL_105 : 0000000000_0000000000000000000000 int_status(RD)  */
        0x00000000,                /* ; DENALI_CTL_106 : 0000000000_0000000000000000000000 rdlvl_error_status(RD)  */
        0x00000001,                /* ; DENALI_CTL_107 : 00000000_000000000000000000000001 phy_ctrl_reg_8_0(RW)  */
        0x00000001,                /* ; DENALI_CTL_108 : 00000000_000000000000000000000001 phy_ctrl_reg_8_1(RW)  */
        0x00000001,                /* ; DENALI_CTL_109 : 00000000_000000000000000000000001 phy_ctrl_reg_8_2(RW)  */
        0x00000001,                /* ; DENALI_CTL_110 : 00000000_000000000000000000000001 phy_ctrl_reg_8_3(RW)  */
        0x00000001,                /* ; DENALI_CTL_111 : 00000000_000000000000000000000001 phy_ctrl_reg_8_4(RW)  */
        0x00000006,                /* ; DENALI_CTL_112 : 00000000_000000000000000000000110 tinit(RW)  */
        0x00000000,                /* ; DENALI_CTL_113 : 0000_0000000000000000000000000000 xor_check_bits(RW)  */
        0x00040ee6,                /* ; DENALI_CTL_114 : 00000000000001000000111011100110 cke_inactive(RW)  */
        0x00000050,                /* ; DENALI_CTL_115 : 00000000000000000000000001010000 dll_ctrl_reg_0_0(RW)  */
        0x00000050,                /* ; DENALI_CTL_116 : 00000000000000000000000001010000 dll_ctrl_reg_0_1(RW)  */
        0x00000050,                /* ; DENALI_CTL_117 : 00000000000000000000000001010000 dll_ctrl_reg_0_2(RW)  */
        0x00000050,                /* ; DENALI_CTL_118 : 00000000000000000000000001010000 dll_ctrl_reg_0_3(RW)  */
        0x00000050,                /* ; DENALI_CTL_119 : 00000000000000000000000001010000 dll_ctrl_reg_0_4(RW)  */
        0x00000050,                /* ; DENALI_CTL_120 : 00000000000000000000000001010000 dll_ctrl_reg_2(RW)  */
        0x00000000,                /* ; DENALI_CTL_121 : 00000000000000000000000000000000 ecc_c_data(RD)  */
        0x00000000,                /* ; DENALI_CTL_122 : 00000000000000000000000000000000 ecc_u_data(RD)  */
        0x000f1133,                /* ; DENALI_CTL_123 : 00000000000011110001000100110011 pad_ctrl_reg_0(RW)  */
        0x00404000,                /* ; DENALI_CTL_124 : 00000000010000000100000000000000 phy_ctrl_reg_0_0(RW)  */
        0x00404000,                /* ; DENALI_CTL_125 : 00000000010000000100000000000000 phy_ctrl_reg_0_1(RW)  */
        0x00404000,                /* ; DENALI_CTL_126 : 00000000010000000100000000000000 phy_ctrl_reg_0_2(RW)  */
        0x00404000,                /* ; DENALI_CTL_127 : 00000000010000000100000000000000 phy_ctrl_reg_0_3(RW)  */
        0x00404000,                /* ; DENALI_CTL_128 : 00000000010000000100000000000000 phy_ctrl_reg_0_4(RW)  */
        0x00000002,                /* ; DENALI_CTL_129 : 00000000000000000000000000000010 phy_ctrl_reg_10(RW)  */
        0x1208a108,                /* ; DENALI_CTL_130 : 00010010000010001010000100001000 phy_ctrl_reg_1_0(RW)  */
        0x1208a108,                /* ; DENALI_CTL_131 : 00010010000010001010000100001000 phy_ctrl_reg_1_1(RW)  */
        0x1208a108,                /* ; DENALI_CTL_132 : 00010010000010001010000100001000 phy_ctrl_reg_1_2(RW)  */
        0x1208a108,                /* ; DENALI_CTL_133 : 00010010000010001010000100001000 phy_ctrl_reg_1_3(RW)  */
        0x1208a108,                /* ; DENALI_CTL_134 : 00010010000010001010000100001000 phy_ctrl_reg_1_4(RW)  */
        0x01000000,                /* ; DENALI_CTL_135 : 00000001000000000000000000000000 phy_ctrl_reg_2_0(RW)  */
        0x01000000,                /* ; DENALI_CTL_136 : 00000001000000000000000000000000 phy_ctrl_reg_2_1(RW)  */
        0x01000000,                /* ; DENALI_CTL_137 : 00000001000000000000000000000000 phy_ctrl_reg_2_2(RW)  */
        0x01000000,                /* ; DENALI_CTL_138 : 00000001000000000000000000000000 phy_ctrl_reg_2_3(RW)  */
        0x01000000,                /* ; DENALI_CTL_139 : 00000001000000000000000000000000 phy_ctrl_reg_2_4(RW)  */
        0x01000000,                /* ; DENALI_CTL_140 : 00000001000000000000000000000000 phy_ctrl_reg_3_0(RW)  */
        0x01000000,                /* ; DENALI_CTL_141 : 00000001000000000000000000000000 phy_ctrl_reg_3_1(RW)  */
        0x01000000,                /* ; DENALI_CTL_142 : 00000001000000000000000000000000 phy_ctrl_reg_3_2(RW)  */
        0x01000000,                /* ; DENALI_CTL_143 : 00000001000000000000000000000000 phy_ctrl_reg_3_3(RW)  */
        0x01000000,                /* ; DENALI_CTL_144 : 00000001000000000000000000000000 phy_ctrl_reg_3_4(RW)  */
        0x06db6db6,                /* ; DENALI_CTL_145 : 00000110110110110110110110110110 phy_ctrl_reg_4_0(RW)  */
        0x06db6db6,                /* ; DENALI_CTL_146 : 00000110110110110110110110110110 phy_ctrl_reg_4_1(RW)  */
        0x06db6db6,                /* ; DENALI_CTL_147 : 00000110110110110110110110110110 phy_ctrl_reg_4_2(RW)  */
        0x06db6db6,                /* ; DENALI_CTL_148 : 00000110110110110110110110110110 phy_ctrl_reg_4_3(RW)  */
        0x06db6db6,                /* ; DENALI_CTL_149 : 00000110110110110110110110110110 phy_ctrl_reg_4_4(RW)  */
        0x00000000,                /* ; DENALI_CTL_150 : 00000000000000000000000000000000 phy_ctrl_reg_5_0(RW)  */
        0x00000000,                /* ; DENALI_CTL_151 : 00000000000000000000000000000000 phy_ctrl_reg_5_1(RW)  */
        0x00000000,                /* ; DENALI_CTL_152 : 00000000000000000000000000000000 phy_ctrl_reg_5_2(RW)  */
        0x00000000,                /* ; DENALI_CTL_153 : 00000000000000000000000000000000 phy_ctrl_reg_5_3(RW)  */
        0x00000000,                /* ; DENALI_CTL_154 : 00000000000000000000000000000000 phy_ctrl_reg_5_4(RW)  */
        0x2498a249,                /* ; DENALI_CTL_155 : 00100100100110001010001001001001 phy_ctrl_reg_6_0(RW)  */
        0x2498a249,                /* ; DENALI_CTL_156 : 00100100100110001010001001001001 phy_ctrl_reg_6_1(RW)  */
        0x2498a249,                /* ; DENALI_CTL_157 : 00100100100110001010001001001001 phy_ctrl_reg_6_2(RW)  */
        0x2498a249,                /* ; DENALI_CTL_158 : 00100100100110001010001001001001 phy_ctrl_reg_6_3(RW)  */
        0x2498a249,                /* ; DENALI_CTL_159 : 00100100100110001010001001001001 phy_ctrl_reg_6_4(RW)  */
    /*  0x04800201, */             /* ; DENALI_CTL_160 : 00000100_10100000_00000010_00000001 phy_ctrl_reg_7_0(RW)  */
        0x04803219,                /* ; DENALI_CTL_160 : 00000100_10100000_00110010_00011001 phy_ctrl_reg_7_0(RW)  */
    /*  0x04800201, */             /* ; DENALI_CTL_161 : 00000100_10100000_00000010_00000001 phy_ctrl_reg_7_1(RW)  */
        0x04803219,                /* ; DENALI_CTL_161 : 00000100_10100000_00110010_00011001 phy_ctrl_reg_7_1(RW)  */
    /*  0x04800201, */             /* ; DENALI_CTL_162 : 00000100_10100000_00000010_00000001 phy_ctrl_reg_7_2(RW)  */
        0x04803219,                /* ; DENALI_CTL_162 : 00000100_10100000_00110010_00011001 phy_ctrl_reg_7_2(RW)  */
    /*  0x04800201, */             /* ; DENALI_CTL_163 : 00000100_10100000_00000010_00000001 phy_ctrl_reg_7_3(RW)  */
        0x04803219,                /* ; DENALI_CTL_163 : 00000100_10100000_00110010_00011001 phy_ctrl_reg_7_3(RW)  */
    /*  0x04800201, */             /* ; DENALI_CTL_164 : 00000100_10100000_00000010_00000001 phy_ctrl_reg_7_4(RW)  */
        0x04803219,                /* ; DENALI_CTL_164 : 00000100_10100000_00110010_00011001 phy_ctrl_reg_7_4(RW)  */
        0x00000000,                /* ; DENALI_CTL_165 : 00000000000000000000000000000000 phy_ctrl_reg_9_0(RW)  */
        0x00000000,                /* ; DENALI_CTL_166 : 00000000000000000000000000000000 phy_ctrl_reg_9_1(RW)  */
        0x00000000,                /* ; DENALI_CTL_167 : 00000000000000000000000000000000 phy_ctrl_reg_9_2(RW)  */
        0x00000000,                /* ; DENALI_CTL_168 : 00000000000000000000000000000000 phy_ctrl_reg_9_3(RW)  */
        0x00000000,                /* ; DENALI_CTL_169 : 00000000000000000000000000000000 phy_ctrl_reg_9_4(RW)  */
        0x00000000,                /* ; DENALI_CTL_170 : 00000000000000000000000000000000 phy_obs_reg_0_0(RD)  */
        0x00000000,                /* ; DENALI_CTL_171 : 00000000000000000000000000000000 phy_obs_reg_0_1(RD)  */
        0x00000000,                /* ; DENALI_CTL_172 : 00000000000000000000000000000000 phy_obs_reg_0_2(RD)  */
        0x00000000,                /* ; DENALI_CTL_173 : 00000000000000000000000000000000 phy_obs_reg_0_3(RD)  */
        0x00000000,                /* ; DENALI_CTL_174 : 00000000000000000000000000000000 phy_obs_reg_0_4(RD)  */
        0x00000000,                /* ; DENALI_CTL_175 : 00000000000000000000000000000000 phy_obs_reg_1_0(RD)  */
        0x00000000,                /* ; DENALI_CTL_176 : 00000000000000000000000000000000 phy_obs_reg_1_1(RD)  */
        0x00000000,                /* ; DENALI_CTL_177 : 00000000000000000000000000000000 phy_obs_reg_1_2(RD)  */
        0x00000000,                /* ; DENALI_CTL_178 : 00000000000000000000000000000000 phy_obs_reg_1_3(RD)  */
        0x00000000,                /* ; DENALI_CTL_179 : 00000000000000000000000000000000 phy_obs_reg_1_4(RD)  */
        0x00000000,                /* ; DENALI_CTL_180 : 00000000000000000000000000000000 phy_obs_reg_3(RD)  */
        0x00000000,                /* ; DENALI_CTL_181 : 00000000000000000000000000000000 phy_obs_reg_4(RD)  */
        0x0000102d,                /* ; DENALI_CTL_182 : 00000000000000000001000000101101 tdfi_rdlvl_max(RW)  */
        0x0000102d,                /* ; DENALI_CTL_183 : 00000000000000000001000000101101 tdfi_rdlvl_resp(RW)  */
        0x00000000,                /* ; DENALI_CTL_184 : 00000000000000000000000000000000 tdfi_wrlvl_max(RW)  */
        0x0000102d,                /* ; DENALI_CTL_185 : 00000000000000000001000000101101 tdfi_wrlvl_resp(RW)  */
        0x00019f8f,                /* ; DENALI_CTL_186 : 00000000000000011001111110001111 trst_pwron(RW)  */
        0x00000000,                /* ; DENALI_CTL_187 : 00000000000000000000000000000000 ecc_c_addr(RD)  */
        0x00000000,                /* ; DENALI_CTL_188 : 00000000000000000000000000000_000 */
        0x00000000,                /* ; DENALI_CTL_189 : 00000000000000000000000000000000 ecc_u_addr(RD)  */
        0x00000000,                /* ; DENALI_CTL_190 : 00000000000000000000000000000_000 */
        0x00000000,                /* ; DENALI_CTL_191 : 00000000000000000000000000000000 out_of_range_addr(RD)  */
        0x00000000,                /* ; DENALI_CTL_192 : 00000000000000000000000000000_000 */
        0x00000000,                /* ; DENALI_CTL_193 : 00000000000000000000000000000000 port_cmd_error_addr(RD)  */
        0x00000000,                /* ; DENALI_CTL_194 : 00000000000000000000000000000_000 */
        0x00000000,                /* ; DENALI_CTL_195 : 00000000000000000000000000000000 rdlvl_gate_resp_mask(RW)  */
        0x00000000,                /* ; DENALI_CTL_196 : 0000000000000000000000000_0000000 */
        0x00000000,                /* ; DENALI_CTL_197 : 00000000000000000000000000000000 rdlvl_resp_mask(RW)  */
        0x07000000,                /* ; DENALI_CTL_198 : 00000111 tdfi_rdlvl_load(RW) 0000000_0 wrlvl_en(RW) 0000000_0 cke_status(RD) 0_0000000 */
        0x00000007,                /* ; DENALI_CTL_199 : 00000000_0000000000000000 rdlvl_gate_refresh_interval(RW) 00000111 tdfi_wrlvl_load(RW)  */
        0x00000000,                /* ; DENALI_CTL_200 : 0000000000000000 wrlvl_refresh_interval(RW) 0000000000000000 rdlvl_refresh_interval(RW)  */
        0x000091dd,                /* ; DENALI_CTL_201 : 000000000000000_01001000111011101 tras_max(RW) */
        0x0000003b,                /* ; DENALI_CTL_202 : 000000000000000_0 srefresh_exit_no_refresh(RW) 000000_0000111011 trfc(RW) */
        0x00000000,                /* ; DENALI_CTL_203 : 000000_00000000000000000000000000 write_modereg(RW+) */
        0x00000000,                /* ; DENALI_CTL_204 : 000000000_000000000000000 mrsingle_data_0(RW) 00000000 mrw_status(RD) */
        0x02000000,                /* ; DENALI_CTL_205 : 0000_0010 add_odt_clk_r2w_samecs(RW) 0000000_0 inhibit_dram_cmd(RW) 0_000000000000000 mrsingle_data_1(RW) */
        0x00000000,                /* ; DENALI_CTL_206 : 000000000_0000000 update_error_status(RD) 0000000_0 mem_rst_valid(RD) 0000_0000 add_odt_clk_w2r_samecs(RW) */
        0x000050e1                 /* ; DENALI_CTL_207 : 00000000000000000101000011100001 tdfi_ctrlupd_interval(RW) */
};

#endif
