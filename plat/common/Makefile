#
# (C) Copyright 2006
# Wolfgang Denk, DENX Software Engineering, wd@denx.de.
#
# See file CREDITS for list of people who contributed to this
# project.
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License as
# published by the Free Software Foundation; either version 2 of
# the License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place, Suite 330, Boston,
# MA 02111-1307 USA
#

include $(TOPDIR)/config.mk

ifneq ($(OBJTREE),$(SRCTREE))
$(shell mkdir -p $(obj)plat/common)
endif

LIB	= $(obj)libcommon.a

COBJS-y += spr_serial.o
COBJS-$(CONFIG_SPEAR600) += spr_lowlevelinit.o
COBJS-$(CONFIG_SPEAR3XX) += spr_lowlevelinit.o
COBJS-$(CONFIG_SPEAR600) += spr_nand.o
COBJS-$(CONFIG_SPEAR3XX) += spr_nand.o
COBJS-$(CONFIG_SPEAR600) += spr600_mt47h64m16_3_333_cl5_psync.o
COBJS-$(CONFIG_SPEAR600) += spr600_mt47h32m16_333_cl5_psync.o
COBJS-$(CONFIG_SPEAR600) += spr600_mt47h32m16_37e_166_cl4_sync.o
COBJS-$(CONFIG_SPEAR600) += spr600_mt47h128m8_3_266_cl5_async.o
COBJS-$(CONFIG_SPEAR3XX) += spr3xx_mt47h64m16_3_333_cl5_async.o
COBJS-$(CONFIG_SPEAR3XX) += spr3xx_mt47h64m16_3_266_cl5_async.o
COBJS-$(CONFIG_SPEAR3XX) += spr3xx_mt47h64m16_3_166_cl4_async.o
COBJS-$(CONFIG_SPEAR3XX) += spr3xx_mt46h32m16_6_166_cl3.o
COBJS-$(CONFIG_SPEAR3XX) += spr3xx_jedec_512m_x16_800d_BL4_CL5_333.o

COBJS-$(CONFIG_SPEAR13XX) += spear13xx.o
COBJS-$(CONFIG_SPEAR13XX) += spr13xx_lowlevelinit.o
COBJS-$(CONFIG_SPEAR13XX) += spr13xx_nand.o

COBJS-$(CONFIG_SPEAR900) += spr13xx_mt41j64m16la187e_400_cl6_dqs_dq_term_en.o
COBJS-$(CONFIG_SPEAR900) += spr13xx_mt41j64m16la187e_533_cl7_dqs_dq_term_en.o
COBJS-$(CONFIG_SPEAR900) += spr13xx_mt41j256m8187e_400_cl6_dqs_dq_term_en.o
COBJS-$(CONFIG_SPEAR900) += spr13xx_mt41j256m8187e_533_cl7_dqs_dq_term_en.o

COBJS-$(CONFIG_SPEAR900_LCAD) += spr13xx_mt41j64m16la187e_400_cl6_dqs_dq_term_en.o
COBJS-$(CONFIG_SPEAR900_LCAD) += spr13xx_mt41j64m16la187e_533_cl7_dqs_dq_term_en.o

COBJS-$(CONFIG_SPEAR1300) += spr13xx_mt41j64m16la187e_400_cl6_dqs_dq_term_en.o
COBJS-$(CONFIG_SPEAR1300) += spr13xx_mt41j64m16la187e_533_cl7_dqs_dq_term_en.o
COBJS-$(CONFIG_SPEAR1300) += spr13xx_mt41j256m8187e_400_cl6_dqs_dq_term_en.o
COBJS-$(CONFIG_SPEAR1300) += spr13xx_mt41j256m8187e_533_cl7_dqs_dq_term_en.o

COBJS-$(CONFIG_SPEAR1310_REVA) += spr13xx_mt41j64m16la187e_400_cl6_dqs_dq_term_en.o
COBJS-$(CONFIG_SPEAR1310_REVA) += spr13xx_mt41j64m16la187e_533_cl7_dqs_dq_term_en.o
COBJS-$(CONFIG_SPEAR1310_REVA) += spr13xx_mt41j256m8187e_400_cl6_dqs_dq_term_en.o
COBJS-$(CONFIG_SPEAR1310_REVA) += spr13xx_mt41j256m8187e_533_cl7_dqs_dq_term_en.o

COBJS-$(CONFIG_SPEAR1310) += spr1340_mt41j256m8187e_400_cl6_dqs_dq_term_en.o
COBJS-$(CONFIG_SPEAR1310) += spr1340_mt41j256m8187e_533_cl7_dqs_dq_term_en.o

COBJS-$(CONFIG_SPEAR1340) += spr1340_mt41j256m8187e_400_cl6_dqs_dq_term_en.o
COBJS-$(CONFIG_SPEAR1340) += spr1340_mt41j256m8187e_533_cl7_dqs_dq_term_en.o
COBJS-$(CONFIG_SPEAR1340) += spr1340_mt47h128m16rt187e_533_cl7_DDR2.o
COBJS-$(CONFIG_SPEAR1340) += spr1340_mt47h128m16rt187e_400_cl6_DDR2.o

COBJS-$(CONFIG_SPEAR1340_LCAD) += spr1340_mt41j64m16_15e_400_cl6_dqs_dq_term_en.o
COBJS-$(CONFIG_SPEAR1340_LCAD) += spr1340_mt41j64m16_15e_533_cl7_dqs_dq_term_en.o
COBJS-$(CONFIG_SPEAR1340_LCAD) += spr1340_mt41j128m16_15e_400_cl6_dqs_dq_term_en.o
COBJS-$(CONFIG_SPEAR1340_LCAD) += spr1340_k4b2g1646c_k0_400_cl6.o

COBJS-$(CONFIG_SPEAR1380_REVC) += spr1380_revc_mt41j64m16_15e_533_cl7_dqs_dq_term_en.o

COBJS-$(CONFIG_SPEAR13XX) += spr13xx_swlvl.o
COBJS-$(CONFIG_SPEAR13XX) += spr13xx_lvl_read.o
COBJS-$(CONFIG_SPEAR13XX) += spr13xx_lvl_write.o
COBJS-$(CONFIG_SPEAR13XX) += spr13xx_lvl_gatetrn.o
COBJS-y += ddrtest.o

SOBJS-$(CONFIG_SPEAR13XX) += spr13xx_wakeup.o
SOBJS-$(CONFIG_SPEAR13XX) += cache.o

SOBJS	:= $(SOBJS-y)
COBJS	:= $(COBJS-y)

SRCS	:= $(SOBJS:.o=.S) $(COBJS:.o=.c)
OBJS	:= $(addprefix $(obj),$(COBJS))
SOBJS	:= $(addprefix $(obj),$(SOBJS))

$(LIB):	$(obj).depend $(OBJS) $(SOBJS)
	$(AR) $(ARFLAGS) $@ $(OBJS) $(SOBJS)

clean:
	rm -f $(SOBJS) $(OBJS)

distclean:	clean
	rm -f $(LIB) core *.bak $(obj).depend

#########################################################################
# This is for $(obj).depend target
include $(TOPDIR)/rules.mk

sinclude $(obj).depend

#########################################################################
