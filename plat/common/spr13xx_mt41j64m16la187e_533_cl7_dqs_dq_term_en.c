/*
 * (C) Copyright 2000-2009
 * Vipin Kumar, ST Microelectronics, vipin.kumar@st.com
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#include <common.h>

#if defined(CONFIG_SPEAR13XX) && \
	(CONFIG_DDR_MT41J64M16) && (CONFIG_DDR_FREQ_533)

#if !(defined(CONFIG_SPEAR1340) || defined(CONFIG_SPEAR1310))

const u32 mpmc_conf_vals[CONFIG_SPEAR_MPMCREGS] = {
	0x00000101,		/* ; DENALI_CTL_00 */
	0x00000100,		/* ; DENALI_CTL_01 */
	0x01010000,		/* ; DENALI_CTL_02 */
#ifdef CONFIG_DDR_ECC_ENABLE
	0x00000101,
#else
	0x00000100,
#endif
	0x00000000,		/* ; DENALI_CTL_04 */
	0x00010101,		/* ; DENALI_CTL_05 VM : Disable DRAM cmds until TDLL
				   expires. */
	/* 0x00010100, */	/* ; DENALI_CTL_05 */
	0x00000001,		/* ; DENALI_CTL_06 */
	0x00000000,		/* ; DENALI_CTL_07 */
	0x00000000,		/* ; DENALI_CTL_08 */
	0x00000000,		/* ; DENALI_CTL_09 */
	0x00000000,		/* ; DENALI_CTL_10 */
	0x00000101,		/* ; DENALI_CTL_11 */
	0x00000101,		/* ; DENALI_CTL_12 */
	0x01010000,		/* ; DENALI_CTL_13 */
	0x00000000,		/* ; DENALI_CTL_14 VM:Bit 16 is write_mode_REG*/
	0x01000000,		/* ; DENALI_CTL_15 */
	0x00000000,		/* ; DENALI_CTL_16 */
	0x00000000,		/* ; DENALI_CTL_17 */
#ifdef CONFIG_DDR_ECC_ENABLE
	0x00000001,		/* DENALI_CTL_18 */
#else
	0x00000201,		/* DENALI_CTL_18 */
#endif
	/* 0x01020102, */	/* ; DENALI_CTL_19 VM : CS2 termination enable
				 when CS1 reas/write taking place & vice-versa*/
	0x02010102,		/* ; DENALI_CTL_19 */
	0x00020000,		/* ; DENALI_CTL_20 */
	0x07070002,		/* ; DENALI_CTL_21 */
	0x00070700,		/* ; DENALI_CTL_22 */
	0x07000707,		/* ; DENALI_CTL_23 */
	0x00000007,		/* ; DENALI_CTL_24 */
	0x03070700,		/* ; DENALI_CTL_25 */
	0x00000400,		/* ; DENALI_CTL_26 */
	/* 0x02000104, */	/* ; DENALI_CTL_27 VM : Q_fullness value = 4(middle
				   value) */
	0x02000100,		/* ; DENALI_CTL_27 */
	0x06030402,		/* ; DENALI_CTL_28 */
	0x01000104,		/* ; DENALI_CTL_29 */
	0x02020000,		/* ; DENALI_CTL_30 */
	0x0606060a,		/* ; DENALI_CTL_31 */
	0x06060606,		/* ; DENALI_CTL_32 */
	0x05050506,		/* ; DENALI_CTL_33 */
	0x05050505,		/* ; DENALI_CTL_34 */
	0x04040405,		/* ; DENALI_CTL_35 */
	0x04040404,		/* ; DENALI_CTL_36 */
	0x03030304,		/* ; DENALI_CTL_37 */
	0x03030303,		/* ; DENALI_CTL_38 */
	0x02020203,		/* ; DENALI_CTL_39 */
	0x02020202,		/* ; DENALI_CTL_40 */
	0x01010102,		/* ; DENALI_CTL_41 */
	0x01010101,		/* ; DENALI_CTL_42 */
	0x06070c01,		/* ; DENALI_CTL_43 */
	0x00000000,		/* ; DENALI_CTL_44 */
	0x00000204,		/* ; DENALI_CTL_45 */
	0x04080702,		/* ; DENALI_CTL_46 */
	0x02000606,		/* ; DENALI_CTL_47 */
	0x0000110e,		/* ; DENALI_CTL_48 */
	0x0f040407,		/* ; DENALI_CTL_49 */
	0x0802000d,		/* ; DENALI_CTL_50 */
	0x3f003f08,		/* ; DENALI_CTL_51 */
	0x191b1b00,		/* ; DENALI_CTL_52 */
	0x00000028,		/* ; DENALI_CTL_53 */
	0x00000000,		/* ; DENALI_CTL_54 */
	0x00000000,		/* ; DENALI_CTL_55 */
	0x00000000,		/* ; DENALI_CTL_56 */
	0x00004000,		/* ; DENALI_CTL_57 */
	0x03000000,		/* ; DENALI_CTL_58 */
	0x03030c03,		/* ; DENALI_CTL_59 */
	0x07140c04,		/* ; DENALI_CTL_60 */
	0x0000643b,		/* ; DENALI_CTL_61 */
	0x00640064,		/* ; DENALI_CTL_62 */
	0x00640064,		/* ; DENALI_CTL_63 */
	0x000f0064,		/* ; DENALI_CTL_64 */
	0x0000000a,		/* ; DENALI_CTL_65 */
	0x00400100,		/* ; DENALI_CTL_66 */
	0x10330200,		/* ; DENALI_CTL_67 */
	0x10331033,		/* ; DENALI_CTL_68 */
	0x10331033,		/* ; DENALI_CTL_69 */
	0x10331033,		/* ; DENALI_CTL_70 */
	0x08300830,		/* ; DENALI_CTL_71 */
	0x00060006,		/* ; DENALI_CTL_72 */
	0x00080008,		/* ; DENALI_CTL_73 */
	0x00000000,		/* ; DENALI_CTL_74 */
	0xff005555,		/* ; DENALI_CTL_75 */
	0xaaaa00ff,		/* ; DENALI_CTL_76 */
	0xff005555,		/* ; DENALI_CTL_77 */
	0x00000007,		/* ; DENALI_CTL_78 */
	0x00000000,		/* ; DENALI_CTL_79 */
	0x00000000,		/* ; DENALI_CTL_80 */
	0x00070000,		/* ; DENALI_CTL_81 */
	0x00070007,		/* ; DENALI_CTL_82 */
	0x00070007,		/* ; DENALI_CTL_83 */
	0x00000000,		/* ; DENALI_CTL_84 */
	0x00000000,		/* ; DENALI_CTL_85 */
	0x00030000,		/* ; DENALI_CTL_86 */
	0x00030003,		/* ; DENALI_CTL_87 */
	0x00030003,		/* ; DENALI_CTL_88 */
	0xffff0010,		/* ; DENALI_CTL_89 */
	0x00000000,		/* ; DENALI_CTL_90 */
	0x00000000,		/* ; DENALI_CTL_91 */
	0x00000000,		/* ; DENALI_CTL_92 */
	0x00000000,		/* ; DENALI_CTL_93 */
	0x00000000,		/* ; DENALI_CTL_94 */
	0x00000000,		/* ; DENALI_CTL_95 */
	0x02000000,		/* ; DENALI_CTL_96 */
	0x91d30004,		/* ; DENALI_CTL_97 */
	0x0040000d,		/* ; DENALI_CTL_98 */
	0x00000200,		/* ; DENALI_CTL_99 */
	0x00000000,		/* ; DENALI_CTL_100 */
	0x00000000,		/* ; DENALI_CTL_101 */
	0x00000000,		/* ; DENALI_CTL_102 */
	0x00000000,		/* ; DENALI_CTL_103 */
	0x00000000,		/* ; DENALI_CTL_104 */
	0x00000000,		/* ; DENALI_CTL_105 */
	0x00000000,		/* ; DENALI_CTL_106 */
	0x00000001,		/* ; DENALI_CTL_107 */
	0x00000001,		/* ; DENALI_CTL_108 */
	0x00000001,		/* ; DENALI_CTL_109 */
	0x00000001,		/* ; DENALI_CTL_110 */
	0x00000001,		/* ; DENALI_CTL_111 */
	0x0000ffff,		/* ; DENALI_CTL_112 */
	0x00000000,		/* ; DENALI_CTL_113 */
	0x00040ee6,		/* ; DENALI_CTL_114 */
	0x00000050,		/* ; DENALI_CTL_115 */
	0x00000050,		/* ; DENALI_CTL_116 */
	0x00000050,		/* ; DENALI_CTL_117 */
	0x00000050,		/* ; DENALI_CTL_118 */
	0x00000050,		/* ; DENALI_CTL_119 */
	0x00000050,		/* ; DENALI_CTL_120 */
	0x00000000,		/* ; DENALI_CTL_121 */
	0x00000000,		/* ; DENALI_CTL_122 */
	0x000f1133,		/* ; DENALI_CTL_123 */
	0x00304001,		/* DENALI_CTL_124 */
	0x00304001,		/* DENALI_CTL_125 */
	0x00304001,		/* DENALI_CTL_126 */
	0x00304001,		/* DENALI_CTL_127 */
	0x00304001,		/* DENALI_CTL_128 */
	0x00000002,		/* ; DENALI_CTL_129 */
	0x2288a108,		/* ; DENALI_CTL_130 */
	0x2288a108,		/* ; DENALI_CTL_131 */
	0x2288a108,		/* ; DENALI_CTL_132 */
	0x2288a108,		/* ; DENALI_CTL_133 */
	0x2288a108,		/* ; DENALI_CTL_134 */
	0x01000000,		/* ; DENALI_CTL_135 */
	0x01000000,		/* ; DENALI_CTL_136 */
	0x01000000,		/* ; DENALI_CTL_137 */
	0x01000000,		/* ; DENALI_CTL_138 */
	0x01000000,		/* ; DENALI_CTL_139 */
	0x01000000,		/* ; DENALI_CTL_140 */
	0x01000000,		/* ; DENALI_CTL_141 */
	0x01000000,		/* ; DENALI_CTL_142 */
	0x01000000,		/* ; DENALI_CTL_143 */
	0x01000000,		/* ; DENALI_CTL_144 */
	0x06db6db6,		/* DENALI_CTL_145 */
	0x06db6db6,		/* DENALI_CTL_146 */
	0x06db6db6,		/* DENALI_CTL_147 */
	0x06db6db6,		/* DENALI_CTL_148 */
	0x06db6db6,		/* DENALI_CTL_149 */
	0x00000000,		/* ; DENALI_CTL_150 */
	0x00000000,		/* ; DENALI_CTL_151 */
	0x00000000,		/* ; DENALI_CTL_152 */
	0x00000000,		/* ; DENALI_CTL_153 */
	0x00000000,		/* ; DENALI_CTL_154 */
	0x2494a249,		/* ; DENALI_CTL_155 */
	0x2494a249,		/* ; DENALI_CTL_156 */
	0x2494a249,		/* ; DENALI_CTL_157 */
	0x2494a249,		/* ; DENALI_CTL_158 */
	0x2494a249,		/* ; DENALI_CTL_159 */
	0x04803219,		/* ; DENALI_CTL_160 */
	0x04803219,		/* ; DENALI_CTL_161 */
	0x04803219,		/* ; DENALI_CTL_162 */
	0x04803219,		/* ; DENALI_CTL_163 */
	0x04803219,		/* ; DENALI_CTL_164 */
	0x00000000,		/* ; DENALI_CTL_165 */
	0x00000000,		/* ; DENALI_CTL_166 */
	0x00000000,		/* ; DENALI_CTL_167 */
	0x00000000,		/* ; DENALI_CTL_168 */
	0x00000000,		/* ; DENALI_CTL_169 */
	0x00000000,		/* ; DENALI_CTL_170 */
	0x00000000,		/* ; DENALI_CTL_171 */
	0x00000000,		/* ; DENALI_CTL_172 */
	0x00000000,		/* ; DENALI_CTL_173 */
	0x00000000,		/* ; DENALI_CTL_174 */
	0x00000000,		/* ; DENALI_CTL_175 */
	0x00000000,		/* ; DENALI_CTL_176 */
	0x00000000,		/* ; DENALI_CTL_177 */
	0x00000000,		/* ; DENALI_CTL_178 */
	0x00000000,		/* ; DENALI_CTL_179 */
	0x00000000,		/* ; DENALI_CTL_180 */
	0x00000000,		/* ; DENALI_CTL_181 */
	0x00001033,		/* ; DENALI_CTL_182 */
	0x00001033,		/* ; DENALI_CTL_183 */
	0x00000000,		/* ; DENALI_CTL_184 */
	0x00001033,		/* ; DENALI_CTL_185 */
	0x00019f8f,		/* ; DENALI_CTL_186 */
	0x00000000,		/* ; DENALI_CTL_187 */
	0x00000000,		/* ; DENALI_CTL_188 */
	0x00000000,		/* ; DENALI_CTL_189 */
	0x00000000,		/* ; DENALI_CTL_190 */
	0x00000000,		/* ; DENALI_CTL_191 */
	0x00000000,		/* ; DENALI_CTL_192 */
	0x00000000,		/* ; DENALI_CTL_193 */
	0x00000000,		/* ; DENALI_CTL_194 */
	0x00000000,		/* ; DENALI_CTL_195 */
	0x00000000,		/* ; DENALI_CTL_196 */
	0x00000000,		/* ; DENALI_CTL_197 */
	0x07000000,		/* ; DENALI_CTL_198 */
	0x00000007,		/* ; DENALI_CTL_199 */
	0x00000000,		/* ; DENALI_CTL_200 */
};
#endif

#endif
