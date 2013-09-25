/*
 * based on denaly webttol https://www.denali.com/en/support/databahn/genregs.jsp?p=ZD0xMjQyNzY0NzEzNjA4JmM9NTUwMjI4Mw==&flow=select#DDR3SDRAM
 */
/* ********************************************************************
// Option: Burst Length                  = 4
// Option: CAS Latency                   = 5
// Option: Simulation MHz                = 333
// Memory: mt47h64m16_3
   ********************************************************************
*/

#include <common.h>

#if defined(CONFIG_SPEAR3XX) && \
	(CONFIG_DDR_MT47H64M16) && \
	(CONFIG_DDR_PLL2 || CONFIG_DDR_2HCLK)

    /*  0x00000001, */             /* ; DENALI_CTL_00 : 000000_00 ahb2_fifo_type_reg 000000_00 ahb1_fifo_type_reg 000000_00 ahb0_fifo_type_reg 0000000_1 addr_cmp_en  */
    /*  0x00000000, */             /* ; DENALI_CTL_01 : 0000000000000000000000_00 ahb4_fifo_type_reg 000000_00 ahb3_fifo_type_reg  */
    /*  0x00000101, */             /* ; DENALI_CTL_04 : 0000000_0 intrptapburst 0000000_0 fast_write 0000000_1 eight_bank_mode 0000000_1 dqs_n_en  */
    /*  0x01020003, */             /* ; DENALI_CTL_09 : 000000_01 odt_rd_map_cs1 000000_10 odt_rd_map_cs0 000000_00 max_cs_reg 000000_11 cs_map  */
    /*  0x01000102, */             /* ; DENALI_CTL_10 : 000000_01 rtt_0 000000_00 out_of_range_type 000000_01 odt_wr_map_cs1 000000_10 odt_wr_map_cs0  */
    /*  0x02000202, */             /* ; DENALI_CTL_11 : 00000_010 ahb0_r_priority 00000_000 ahb0_port_ordering 00000_010 addr_pins 000000_10 rtt_pad_termination  */

const u32 mpmc_conf_vals[CONFIG_SPEAR_MPMCREGS] = {
#if CONFIG_DDR_PLL2
	    0x00000001,  
    	0x00000000,  
#else
	    0x02020201, 
	    0x00000202, 
#endif
        0x01000000,                 /* ; DENALI_CTL_02 : 0000000_1 bank_split_en 0000000_0 auto_refresh_mode 0000000_0 arefresh 0000000_0 ap  */
        0x00000101,                 /* ; DENALI_CTL_03 : 0000000_0 dll_bypass_mode 0000000_0 dlllockreg 0000000_1 ddrii_sdram_mode 0000000_1 concurrentap  */
#ifdef EIGHT_BANK_MODE
     	0x00000101,
#else
	    0x00000001,
#endif
        0x01000000,                 /* ; DENALI_CTL_05 : 0000000_1 odt_add_turn_clk_en 0000000_0 no_cmd_init 0000000_0 intrptwritea 0000000_0 intrptreada  */
        0x00010001,                 /* ; DENALI_CTL_06 : 0000000_0 reduc 0000000_1 priority_en 0000000_0 power_down 0000000_1 placement_en  */
        0x00000100,                 /* ; DENALI_CTL_07 : 0000000_0 start 0000000_0 srefresh 0000000_1 rw_same_en 0000000_0 reg_dimm_enable  */
        0x00010001,                 /* ; DENALI_CTL_08 : 0000000_0 write_modereg 0000000_1 writeinterp 0000000_0 weighted_round_robin_latency_control 0000000_1 tras_lockout  */
#if CONFIG_DUAL_DDR
	0x01020003,  
	0x01000102,    
	0x04000202,   
#else
	0x00000001,
	0x02000001,
	0x04000201,
#endif
        0x02020102,                /* ; DENALI_CTL_12 : 00000_010 ahb1_w_priority 00000_010 ahb1_r_priority 00000_001 ahb1_port_ordering 00000_010 ahb0_w_priority  */
        0x03020202,                /* ; DENALI_CTL_13 : 00000_011 ahb3_port_ordering 00000_010 ahb2_w_priority 00000_010 ahb2_r_priority 00000_010 ahb2_port_ordering  */
        0x02040202,                /* ; DENALI_CTL_14 : 00000_010 ahb4_r_priority 00000_100 ahb4_port_ordering 00000_010 ahb3_w_priority 00000_010 ahb3_r_priority  */
        0x00000002,                /* ; DENALI_CTL_15 : 00000000000000000000000000000_010 ahb4_w_priority  */
        0x00000000,                /* ; DENALI_CTL_16 : 00000000000000000000000000000000 */
        0x03000405,                /* ; DENALI_CTL_17 : 00000_011 tcke 00000_000 out_of_range_source_id 00000_100 column_size 00000_101 caslat  */
        0x03040002,                /* ; DENALI_CTL_18 : 00000_011 trtp 00000_100 trrd 0000000000000_010 temrs  */
        0x04000305,                /* ; DENALI_CTL_19 : 00000_100 wrlat 000000_00 weighted_round_robin_weight_sharing 00000_011 twtr 00000_101 twr_int  */
        0x0505053f,                /* ; DENALI_CTL_20 : 0000_0101 ahb0_priority2_relative_priority 0000_0101 ahb0_priority1_relative_priority 0000_0101 ahb0_priority0_relative_priority 00_111111 age_count  */
        0x05050505,                /* ; DENALI_CTL_21 : 0000_0101 ahb0_priority6_relative_priority 0000_0101 ahb0_priority5_relative_priority 0000_0101 ahb0_priority4_relative_priority 0000_0101 ahb0_priority3_relative_priority  */
        0x04040405,                /* ; DENALI_CTL_22 : 0000_0100 ahb1_priority2_relative_priority 0000_0100 ahb1_priority1_relative_priority 0000_0100 ahb1_priority0_relative_priority 0000_0101 ahb0_priority7_relative_priority  */
        0x04040404,                /* ; DENALI_CTL_23 : 0000_0100 ahb1_priority6_relative_priority 0000_0100 ahb1_priority5_relative_priority 0000_0100 ahb1_priority4_relative_priority 0000_0100 ahb1_priority3_relative_priority  */
        0x03030304,                /* ; DENALI_CTL_24 : 0000_0011 ahb2_priority2_relative_priority 0000_0011 ahb2_priority1_relative_priority 0000_0011 ahb2_priority0_relative_priority 0000_0100 ahb1_priority7_relative_priority  */
        0x03030303,                /* ; DENALI_CTL_25 : 0000_0011 ahb2_priority6_relative_priority 0000_0011 ahb2_priority5_relative_priority 0000_0011 ahb2_priority4_relative_priority 0000_0011 ahb2_priority3_relative_priority  */
        0x02020203,                /* ; DENALI_CTL_26 : 0000_0010 ahb3_priority2_relative_priority 0000_0010 ahb3_priority1_relative_priority 0000_0010 ahb3_priority0_relative_priority 0000_0011 ahb2_priority7_relative_priority  */
        0x02020202,                /* ; DENALI_CTL_27 : 0000_0010 ahb3_priority6_relative_priority 0000_0010 ahb3_priority5_relative_priority 0000_0010 ahb3_priority4_relative_priority 0000_0010 ahb3_priority3_relative_priority  */
        0x01010102,                /* ; DENALI_CTL_28 : 0000_0001 ahb4_priority2_relative_priority 0000_0001 ahb4_priority1_relative_priority 0000_0001 ahb4_priority0_relative_priority 0000_0010 ahb3_priority7_relative_priority  */
        0x01010101,                /* ; DENALI_CTL_29 : 0000_0001 ahb4_priority6_relative_priority 0000_0001 ahb4_priority5_relative_priority 0000_0001 ahb4_priority4_relative_priority 0000_0001 ahb4_priority3_relative_priority  */
        0x00000001,                /* ; DENALI_CTL_30 : 0000000000000000000000000000_0001 ahb4_priority7_relative_priority  */
        0x00000000,                /* ; DENALI_CTL_31 : 00000000000000000000000000000000 */
        0x00000000,                /* ; DENALI_CTL_32 : 00000000000000000000000000000000 */
        0x00000000,                /* ; DENALI_CTL_33 : 00000000000000000000000000000000 */
        0x0a0c0a00,                /* ; DENALI_CTL_34 : 0000_1010 caslat_lin_gate 0000_1100 caslat_lin 0000_1010 aprebit 00000000 */
        0x0000023f,                /* ; DENALI_CTL_35 : 0000_0000 max_row_reg 0000_0000 max_col_reg 0000_0010 initaref 00_111111 command_age_count  */
        0x00050a00,                /* ; DENALI_CTL_36 : 0000_0000 wrr_param_value_err 0000_0101 trp 0000_1010 tdal 0000_0000 q_fullness  */
        0x11000000,                /* ; DENALI_CTL_37 : 000_10001 tfaw 000_00000 ocd_adjust_pup_cs_0 000_00000 ocd_adjust_pdn_cs_0 00_000000 int_ack  */
        0x00001302,                /* ; DENALI_CTL_38 : 0_0000000 int_status 0_0000000 int_mask 000_10011 trc 000_00010 tmrd  */
        0x00001d1d,                /* ; DENALI_CTL_39 : 00000000000000000_0011101 dll_dqs_delay_1 0_0011101 dll_dqs_delay_0  */
        0x7f000000,                /* ; DENALI_CTL_40 : 0_1111111 dqs_out_shift 000000000000000000000000 */
        0x001f0000,                /* ; DENALI_CTL_41 : 000000000_0011111 wr_dqs_shift 0000000000000000 */
        0x2b050e00,                /* ; DENALI_CTL_42 : 00101011 trfc 00000101 trcd_int 00001110 tras_min 00000000 */
        0x00640064,                /* ; DENALI_CTL_43 : 000000_0001100100 ahb1_priority_relax 000000_0001100100 ahb0_priority_relax  */
        0x00640064,                /* ; DENALI_CTL_44 : 000000_0001100100 ahb3_priority_relax 000000_0001100100 ahb2_priority_relax  */
        0x00000064,                /* ; DENALI_CTL_45 : 0000000000000000000000_0001100100 ahb4_priority_relax  */
        0x00000000,                /* ; DENALI_CTL_46 : 000000_0000000000 out_of_range_length 0000000000000000 */
        0x00200020,                /* ; DENALI_CTL_47 : 00000_00000100000 ahb0_wrcnt 00000_00000100000 ahb0_rdcnt  */
        0x00200020,                /* ; DENALI_CTL_48 : 00000_00000100000 ahb1_wrcnt 00000_00000100000 ahb1_rdcnt  */
        0x00200020,                /* ; DENALI_CTL_49 : 00000_00000100000 ahb2_wrcnt 00000_00000100000 ahb2_rdcnt  */
        0x00200020,                /* ; DENALI_CTL_50 : 00000_00000100000 ahb3_wrcnt 00000_00000100000 ahb3_rdcnt  */
        0x00200020,                /* ; DENALI_CTL_51 : 00000_00000100000 ahb4_wrcnt 00000_00000100000 ahb4_rdcnt  */
        0x00000000,                /* ; DENALI_CTL_52 : 00000000000000000000000000000000 */
        0x00000000,                /* ; DENALI_CTL_53 : 00000000000000000000000000000000 */
        0x00000a24,                /* ; DENALI_CTL_54 : 000000000000000000_00101000100100 tref  */
        0x00000000,                /* ; DENALI_CTL_55 : 00000000000000000_000000000000000 emrs3_data  */
        0x5b1c00c8,                /* ; DENALI_CTL_56 : 0101101100011100 tras_max 0000000011001000 tdll  */
        0x00c8002e,                /* ; DENALI_CTL_57 : 0000000011001000 txsr 0000000000101110 txsnr  */
        0x00000000,                /* ; DENALI_CTL_58 : 00000000000000000000000000000000 version  */
        0x0001046b,                /* ; DENALI_CTL_59 : 00000000000000010000010001101011 tinit  */
        0x00000000,                /* ; DENALI_CTL_60 : 00000000000000000000000000000000 out_of_range_addr  */
        0x00000000,                /* ; DENALI_CTL_61 : 000000000000000000000000000000_00 */
        0x00000000,                /* ; DENALI_CTL_62 : 00000000000000000000000000000000 */
        0x00000000,                /* ; DENALI_CTL_63 : 00000000000000000000000000000000 */
        0x00000000,                /* ; DENALI_CTL_64 : 00000000000000000000000000000000 */
        0x001c0000,                /* ; DENALI_CTL_65 : 000000_0000011100 dll_dqs_delay_bypass_0 0000000000000000 */
        0x0019001c,                /* ; DENALI_CTL_66 : 000000_0000011001 dll_increment 000000_0000011100 dll_dqs_delay_bypass_1  */
        0x001e0000,                /* ; DENALI_CTL_67 : 000000_0000011110 dll_start_point 000000_0000000000 dll_lock  */
        0x001e007a,                /* ; DENALI_CTL_68 : 000000_0000011110 wr_dqs_shift_bypass 000000_0001111010 dqs_out_shift_bypass  */
        0x00000000,                /* ; DENALI_CTL_69 : 00000000000000000000000000000000 */
        0x00000000,                /* ; DENALI_CTL_70 : 00000000000000000000000000000000 */
        0x00000000,                /* ; DENALI_CTL_71 : 00000000000000000000000000000000 */
        0x00000000,                /* ; DENALI_CTL_72 : 00000000000000000000000000000000 */
        0x00000000,                /* ; DENALI_CTL_73 : 00000000000000000000000000000000 */
        0x00000000,                /* ; DENALI_CTL_74 : 00000000000000000000000000000000 */
        0x00000000,                /* ; DENALI_CTL_75 : 00000000000000000000000000000000 */
        0x00000000,                /* ; DENALI_CTL_76 : 00000000000000000000000000000000 */
        0x00000000,                /* ; DENALI_CTL_77 : 00000000000000000000000000000000 */
        0x00000000,                /* ; DENALI_CTL_78 : 00000000000000000000000000000000 */
        0x00000000,                /* ; DENALI_CTL_79 : 00000000000000000000000000000000 */
        0x00000000,                /* ; DENALI_CTL_80 : 00000000000000000000000000000000 */
        0x00000000,                /* ; DENALI_CTL_81 : 00000000000000000000000000000000 */
        0x00000000,                /* ; DENALI_CTL_82 : 00000000000000000000000000000000 */
        0x00000000,                /* ; DENALI_CTL_83 : 00000000000000000000000000000000 */
        0x00000000,                /* ; DENALI_CTL_84 : 00000000000000000000000000000000 */
        0x00000000,                /* ; DENALI_CTL_85 : 00000000000000000000000000000000 */
        0x00000000,                /* ; DENALI_CTL_86 : 00000000000000000000000000000000 */
        0x00000000,                /* ; DENALI_CTL_87 : 00000000000000000000000000000000 */
        0x00000000,                /* ; DENALI_CTL_88 : 00000000000000000000000000000000 */
        0x00000000,                /* ; DENALI_CTL_89 : 00000000000000000000000000000000 */
        0x00000000,                /* ; DENALI_CTL_90 : 00000000000000000000000000000000 */
        0x00000000,                /* ; DENALI_CTL_91 : 00000000000000000000000000000000 */
        0x00000000,                /* ; DENALI_CTL_92 : 00000000000000000000000000000000 */
        0x00000000,                /* ; DENALI_CTL_93 : 00000000000000000000000000000000 */
        0x00000000,                /* ; DENALI_CTL_94 : 00000000000000000000000000000000 */
        0x00000000,                /* ; DENALI_CTL_95 : 00000000000000000000000000000000 */
        0x00000000,                /* ; DENALI_CTL_96 : 00000000000000000000000000000000 */
        0x00000000,                /* ; DENALI_CTL_97 : 00000000000000000000000000000000 */
        0x00000000,                /* ; DENALI_CTL_98 : 00000000000000000000000000000000 user_def_reg_0  */
        0x00000000,                /* ; DENALI_CTL_99 : 00000000000000000000000000000000 user_def_reg_1  */
        0x01010001,                /* ; DENALI_CTL_100 : 0000000_1 enable_quick_srefresh 0000000_1 drive_dq_dqs 0000000_0 big_endian_en 0000000_1 active_aging  */
        0x01000000,                /* ; DENALI_CTL_101 : 0000000_1 swap_en 0000000_0 rd2rd_turn 0000000_0 pwrup_srefresh_exit 0000000_0 en_lowpower_mode  */
        0x00000001,                /* ; DENALI_CTL_102 : 000_00000 lowpower_auto_enable 00000_000 cke_delay 000000_00 lowpower_refresh_enable 0000000_1 tref_enable  */
        0x00000000,                /* ; DENALI_CTL_103 : 000000000_100000000000 emrs1_data 000_00000 lowpower_control  */
        0x00000000,                /* ; DENALI_CTL_104 : 0_000000000000000 emrs2_data_1 0_000000000000000 emrs2_data_0  */
        0x00000000,                /* ; DENALI_CTL_105 : 0000000000000000 lowpower_internal_cnt 0000000000000000 lowpower_external_cnt  */
        0x00000000,                /* ; DENALI_CTL_106 : 0000000000000000 lowpower_refresh_hold 0000000000000000 lowpower_power_down_cnt  */
        0x00860000,                /* ; DENALI_CTL_107 : 0000000010000110 tcpd 0000000000000000 lowpower_self_refresh_cnt  */
        0x00000002,                /* ; DENALI_CTL_108 : 00000000000000000000000000000010 tpdex  */
};

#endif
