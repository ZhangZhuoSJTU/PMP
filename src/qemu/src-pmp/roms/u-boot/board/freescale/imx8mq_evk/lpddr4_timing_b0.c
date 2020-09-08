// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright 2018 NXP
 */

#include <linux/kernel.h>
#include <common.h>
#include <asm/arch/ddr.h>
#include <asm/arch/lpddr4_define.h>

#define WR_POST_EXT_3200  /* recommened to define */

static struct dram_cfg_param lpddr4_ddrc_cfg[] = {
	/* Start to config, default 3200mbps */
	/* dis_dq=1, indicates no reads or writes are issued to SDRAM */
	{ DDRC_DBG1(0), 0x00000001 },
	/* selfref_en=1, SDRAM enter self-refresh state */
	{ DDRC_PWRCTL(0), 0x00000001 },
	{ DDRC_MSTR(0), 0xa3080020 },
	{ DDRC_MSTR2(0), 0x00000000 },
	{ DDRC_RFSHTMG(0), 0x006100E0 },
	{ DDRC_INIT0(0), 0xC003061B },
	{ DDRC_INIT1(0), 0x009D0000 },
	{ DDRC_INIT3(0), 0x00D4002D },
#ifdef WR_POST_EXT_3200  /* recommened to define */
	{ DDRC_INIT4(0), 0x00330008 },
#else
	{ DDRC_INIT4(0), 0x00310008 },
#endif
	{ DDRC_INIT6(0), 0x0066004a },
	{ DDRC_INIT7(0), 0x0006004a },

	{ DDRC_DRAMTMG0(0), 0x1A201B22 },
	{ DDRC_DRAMTMG1(0), 0x00060633 },
	{ DDRC_DRAMTMG3(0), 0x00C0C000 },
	{ DDRC_DRAMTMG4(0), 0x0F04080F },
	{ DDRC_DRAMTMG5(0), 0x02040C0C },
	{ DDRC_DRAMTMG6(0), 0x01010007 },
	{ DDRC_DRAMTMG7(0), 0x00000401 },
	{ DDRC_DRAMTMG12(0), 0x00020600 },
	{ DDRC_DRAMTMG13(0), 0x0C100002 },
	{ DDRC_DRAMTMG14(0), 0x000000E6 },
	{ DDRC_DRAMTMG17(0), 0x00A00050 },

	{ DDRC_ZQCTL0(0), 0x03200018 },
	{ DDRC_ZQCTL1(0), 0x028061A8 },
	{ DDRC_ZQCTL2(0), 0x00000000 },

	{ DDRC_DFITMG0(0), 0x0497820A },
	{ DDRC_DFITMG1(0), 0x00080303 },
	{ DDRC_DFIUPD0(0), 0xE0400018 },
	{ DDRC_DFIUPD1(0), 0x00DF00E4 },
	{ DDRC_DFIUPD2(0), 0x80000000 },
	{ DDRC_DFIMISC(0), 0x00000011 },
	{ DDRC_DFITMG2(0), 0x0000170A },

	{ DDRC_DBICTL(0), 0x00000001 },
	{ DDRC_DFIPHYMSTR(0), 0x00000001 },

	/* need be refined by ddrphy trained value */
	{ DDRC_RANKCTL(0), 0x00000c99 },
	{ DDRC_DRAMTMG2(0), 0x070E171a },

	/* address mapping */
	/* Address map is from MSB 29: r15, r14, cs, r13-r0, b2-b0, c9-c0 */
	{ DDRC_ADDRMAP0(0), 0x00000015 },
	{ DDRC_ADDRMAP3(0), 0x00000000 },
	/* addrmap_col_b10 addrmap_col_b11 set to de-activated (5-bit width) */
	{ DDRC_ADDRMAP4(0), 0x00001F1F },
	/* bank interleave */
	/* addrmap_bank_b2, addrmap_bank_b1, addrmap_bank_b0 */
	{ DDRC_ADDRMAP1(0), 0x00080808 },
	/* addrmap_row_b11 addrmap_row_b10_b2 addrmap_row_b1 addrmap_row_b0 */
	{ DDRC_ADDRMAP5(0), 0x07070707 },
	/* addrmap_row_b15 addrmap_row_b14 addrmap_row_b13 addrmap_row_b12 */
	{ DDRC_ADDRMAP6(0), 0x08080707 },

	/* 667mts frequency setting */
	{ DDRC_FREQ1_DERATEEN(0), 0x0000000 },
	{ DDRC_FREQ1_DERATEINT(0), 0x0800000 },
	{ DDRC_FREQ1_RFSHCTL0(0), 0x0210000 },
	{ DDRC_FREQ1_RFSHTMG(0), 0x014001E },
	{ DDRC_FREQ1_INIT3(0), 0x0140009 },
	{ DDRC_FREQ1_INIT4(0), 0x00310008 },
	{ DDRC_FREQ1_INIT6(0), 0x0066004a },
	{ DDRC_FREQ1_INIT7(0), 0x0006004a },
	{ DDRC_FREQ1_DRAMTMG0(0), 0xB070A07 },
	{ DDRC_FREQ1_DRAMTMG1(0), 0x003040A },
	{ DDRC_FREQ1_DRAMTMG2(0), 0x305080C },
	{ DDRC_FREQ1_DRAMTMG3(0), 0x0505000 },
	{ DDRC_FREQ1_DRAMTMG4(0), 0x3040203 },
	{ DDRC_FREQ1_DRAMTMG5(0), 0x2030303 },
	{ DDRC_FREQ1_DRAMTMG6(0), 0x2020004 },
	{ DDRC_FREQ1_DRAMTMG7(0), 0x0000302 },
	{ DDRC_FREQ1_DRAMTMG12(0), 0x0020310 },
	{ DDRC_FREQ1_DRAMTMG13(0), 0xA100002 },
	{ DDRC_FREQ1_DRAMTMG14(0), 0x0000020 },
	{ DDRC_FREQ1_DRAMTMG17(0), 0x0220011 },
	{ DDRC_FREQ1_ZQCTL0(0), 0x0A70005 },
	{ DDRC_FREQ1_DFITMG0(0), 0x3858202 },
	{ DDRC_FREQ1_DFITMG1(0), 0x0000404 },
	{ DDRC_FREQ1_DFITMG2(0), 0x0000502 },

	/* performance setting */
	{ DDRC_ODTCFG(0), 0x0b060908 },
	{ DDRC_ODTMAP(0), 0x00000000 },
	{ DDRC_SCHED(0), 0x29511505 },
	{ DDRC_SCHED1(0), 0x0000002c },
	{ DDRC_PERFHPR1(0), 0x5900575b },
	/* 150T starve and 0x90 max tran len */
	{ DDRC_PERFLPR1(0), 0x90000096 },
	/* 300T starve and 0x10 max tran len */
	{ DDRC_PERFWR1(0), 0x1000012c },
	{ DDRC_DBG0(0), 0x00000016 },
	{ DDRC_DBG1(0), 0x00000000 },
	{ DDRC_DBGCMD(0), 0x00000000 },
	{ DDRC_SWCTL(0), 0x00000001 },
	{ DDRC_POISONCFG(0), 0x00000011 },
	{ DDRC_PCCFG(0), 0x00000111 },
	{ DDRC_PCFGR_0(0), 0x000010f3 },
	{ DDRC_PCFGW_0(0), 0x000072ff },
	{ DDRC_PCTRL_0(0), 0x00000001 },
	/* disable Read Qos*/
	{ DDRC_PCFGQOS0_0(0), 0x00000e00 },
	{ DDRC_PCFGQOS1_0(0), 0x0062ffff },
	/* disable Write Qos*/
	{ DDRC_PCFGWQOS0_0(0), 0x00000e00 },
	{ DDRC_PCFGWQOS1_0(0), 0x0000ffff },
	{ DDRC_FREQ1_DERATEEN(0), 0x00000202 },
	{ DDRC_FREQ1_DERATEINT(0), 0xec78f4b5 },
	{ DDRC_FREQ1_RFSHCTL0(0), 0x00618040 },
	{ DDRC_FREQ1_RFSHTMG(0), 0x00610090 },
};

/* PHY Initialize Configuration */
static struct dram_cfg_param lpddr4_ddrphy_cfg[] = {
	{ 0x20110, 0x02 }, /* MapCAB0toDFI */
	{ 0x20111, 0x03 }, /* MapCAB1toDFI */
	{ 0x20112, 0x04 }, /* MapCAB2toDFI */
	{ 0x20113, 0x05 }, /* MapCAB3toDFI */
	{ 0x20114, 0x00 }, /* MapCAB4toDFI */
	{ 0x20115, 0x01 }, /* MapCAB5toDFI */

	/* Initialize PHY Configuration */
	{ 0x1005f, 0x1ff },
	{ 0x1015f, 0x1ff },
	{ 0x1105f, 0x1ff },
	{ 0x1115f, 0x1ff },
	{ 0x1205f, 0x1ff },
	{ 0x1215f, 0x1ff },
	{ 0x1305f, 0x1ff },
	{ 0x1315f, 0x1ff },

	{ 0x11005f, 0x1ff },
	{ 0x11015f, 0x1ff },
	{ 0x11105f, 0x1ff },
	{ 0x11115f, 0x1ff },
	{ 0x11205f, 0x1ff },
	{ 0x11215f, 0x1ff },
	{ 0x11305f, 0x1ff },
	{ 0x11315f, 0x1ff },

	{ 0x21005f, 0x1ff },
	{ 0x21015f, 0x1ff },
	{ 0x21105f, 0x1ff },
	{ 0x21115f, 0x1ff },
	{ 0x21205f, 0x1ff },
	{ 0x21215f, 0x1ff },
	{ 0x21305f, 0x1ff },
	{ 0x21315f, 0x1ff },

	{ 0x55, 0x1ff },
	{ 0x1055, 0x1ff },
	{ 0x2055, 0x1ff },
	{ 0x3055, 0x1ff },
	{ 0x4055, 0x1ff },
	{ 0x5055, 0x1ff },
	{ 0x6055, 0x1ff },
	{ 0x7055, 0x1ff },
	{ 0x8055, 0x1ff },
	{ 0x9055, 0x1ff },
	{ 0x200c5, 0x19 },
	{ 0x1200c5, 0x7 },
	{ 0x2200c5, 0x7 },
	{ 0x2002e, 0x2 },
	{ 0x12002e, 0x1 },
	{ 0x22002e, 0x2 },
	{ 0x90204, 0x0 },
	{ 0x190204, 0x0 },
	{ 0x290204, 0x0 },

	{ 0x20024, 0xe3 },
	{ 0x2003a, 0x2 },
	{ 0x120024, 0xa3 },
	{ 0x2003a, 0x2 },
	{ 0x220024, 0xa3 },
	{ 0x2003a, 0x2 },

	{ 0x20056, 0x3 },
	{ 0x120056, 0xa },
	{ 0x220056, 0xa },

	{ 0x1004d, 0xe00 },
	{ 0x1014d, 0xe00 },
	{ 0x1104d, 0xe00 },
	{ 0x1114d, 0xe00 },
	{ 0x1204d, 0xe00 },
	{ 0x1214d, 0xe00 },
	{ 0x1304d, 0xe00 },
	{ 0x1314d, 0xe00 },
	{ 0x11004d, 0xe00 },
	{ 0x11014d, 0xe00 },
	{ 0x11104d, 0xe00 },
	{ 0x11114d, 0xe00 },
	{ 0x11204d, 0xe00 },
	{ 0x11214d, 0xe00 },
	{ 0x11304d, 0xe00 },
	{ 0x11314d, 0xe00 },
	{ 0x21004d, 0xe00 },
	{ 0x21014d, 0xe00 },
	{ 0x21104d, 0xe00 },
	{ 0x21114d, 0xe00 },
	{ 0x21204d, 0xe00 },
	{ 0x21214d, 0xe00 },
	{ 0x21304d, 0xe00 },
	{ 0x21314d, 0xe00 },

	{ 0x10049, 0xfbe },
	{ 0x10149, 0xfbe },
	{ 0x11049, 0xfbe },
	{ 0x11149, 0xfbe },
	{ 0x12049, 0xfbe },
	{ 0x12149, 0xfbe },
	{ 0x13049, 0xfbe },
	{ 0x13149, 0xfbe },

	{ 0x110049, 0xfbe },
	{ 0x110149, 0xfbe },
	{ 0x111049, 0xfbe },
	{ 0x111149, 0xfbe },
	{ 0x112049, 0xfbe },
	{ 0x112149, 0xfbe },
	{ 0x113049, 0xfbe },
	{ 0x113149, 0xfbe },

	{ 0x210049, 0xfbe },
	{ 0x210149, 0xfbe },
	{ 0x211049, 0xfbe },
	{ 0x211149, 0xfbe },
	{ 0x212049, 0xfbe },
	{ 0x212149, 0xfbe },
	{ 0x213049, 0xfbe },
	{ 0x213149, 0xfbe },

	{ 0x43, 0x63 },
	{ 0x1043, 0x63 },
	{ 0x2043, 0x63 },
	{ 0x3043, 0x63 },
	{ 0x4043, 0x63 },
	{ 0x5043, 0x63 },
	{ 0x6043, 0x63 },
	{ 0x7043, 0x63 },
	{ 0x8043, 0x63 },
	{ 0x9043, 0x63 },

	{ 0x20018, 0x3 },
	{ 0x20075, 0x4 },
	{ 0x20050, 0x0 },
	{ 0x20008, 0x320 },
	{ 0x120008, 0xa7 },
	{ 0x220008, 0x19 },
	{ 0x20088, 0x9 },
	{ 0x200b2, 0x104 },
	{ 0x10043, 0x5a1 },
	{ 0x10143, 0x5a1 },
	{ 0x11043, 0x5a1 },
	{ 0x11143, 0x5a1 },
	{ 0x12043, 0x5a1 },
	{ 0x12143, 0x5a1 },
	{ 0x13043, 0x5a1 },
	{ 0x13143, 0x5a1 },
	{ 0x1200b2, 0x104 },
	{ 0x110043, 0x5a1 },
	{ 0x110143, 0x5a1 },
	{ 0x111043, 0x5a1 },
	{ 0x111143, 0x5a1 },
	{ 0x112043, 0x5a1 },
	{ 0x112143, 0x5a1 },
	{ 0x113043, 0x5a1 },
	{ 0x113143, 0x5a1 },
	{ 0x2200b2, 0x104 },
	{ 0x210043, 0x5a1 },
	{ 0x210143, 0x5a1 },
	{ 0x211043, 0x5a1 },
	{ 0x211143, 0x5a1 },
	{ 0x212043, 0x5a1 },
	{ 0x212143, 0x5a1 },
	{ 0x213043, 0x5a1 },
	{ 0x213143, 0x5a1 },
	{ 0x200fa, 0x1 },
	{ 0x1200fa, 0x1 },
	{ 0x2200fa, 0x1 },
	{ 0x20019, 0x1 },
	{ 0x120019, 0x1 },
	{ 0x220019, 0x1 },
	{ 0x200f0, 0x600 },
	{ 0x200f1, 0x0 },
	{ 0x200f2, 0x4444 },
	{ 0x200f3, 0x8888 },
	{ 0x200f4, 0x5655 },
	{ 0x200f5, 0x0 },
	{ 0x200f6, 0x0 },
	{ 0x200f7, 0xf000 },
	{ 0x20025, 0x0 },
	{ 0x2002d, 0x0 },
	{ 0x12002d, 0x0 },
	{ 0x22002d, 0x0 },
};

/* P0 message block paremeter for training firmware */
static struct dram_cfg_param lpddr4_fsp0_cfg[] = {
	{ 0xd0000, 0x0 },
	{ 0x54000, 0x0 },
	{ 0x54001, 0x0 },
	{ 0x54002, 0x0 },
	{ 0x54003, 0xc80 },
	{ 0x54004, 0x2 },
	{ 0x54005, ((LPDDR4_PHY_RON << 8) | LPDDR4_PHY_RTT) },
	{ 0x54006, LPDDR4_PHY_VREF_VALUE },
	{ 0x54007, 0x0 },
	{ 0x54008, 0x131f },
	{ 0x54009, LPDDR4_HDT_CTL_3200_1D },
	{ 0x5400a, 0x0 },
	{ 0x5400b, 0x2 },
	{ 0x5400c, 0x0 },
	{ 0x5400d, (LPDDR4_CATRAIN_3200_1d << 8) },
	{ 0x5400e, 0x0 },
	{ 0x5400f, 0x0 },
	{ 0x54010, 0x0 },
	{ 0x54011, 0x0 },
	{ 0x54012, 0x310 },
	{ 0x54013, 0x0 },
	{ 0x54014, 0x0 },
	{ 0x54015, 0x0 },
	{ 0x54016, 0x0 },
	{ 0x54017, 0x0 },
	{ 0x54018, 0x0 },
	{ 0x54019, 0x2dd4 },
	{ 0x5401a, (((LPDDR4_RON) << 3) | 0x3) },
	{ 0x5401b, ((LPDDR4_VREF_VALUE_CA << 8) |
		    (LPDDR4_RTT_CA_BANK0 << 4) | LPDDR4_RTT_DQ) },
	{ 0x5401c, ((LPDDR4_VREF_VALUE_DQ_RANK0 << 8) | 0x08) },
	{ 0x5401d, 0x0 },
	{ 0x5401e, LPDDR4_MR22_RANK0 },
	{ 0x5401f, 0x2dd4 },
	{ 0x54020, (((LPDDR4_RON) << 3) | 0x3) },
	{ 0x54021, ((LPDDR4_VREF_VALUE_CA << 8) |
		    (LPDDR4_RTT_CA_BANK1 << 4) | LPDDR4_RTT_DQ) },
	{ 0x54022, ((LPDDR4_VREF_VALUE_DQ_RANK1 << 8) | 0x08) },
	{ 0x54023, 0x0 },
	{ 0x54024, LPDDR4_MR22_RANK1 },
	{ 0x54025, 0x0 },
	{ 0x54026, 0x0 },
	{ 0x54027, 0x0 },
	{ 0x54028, 0x0 },
	{ 0x54029, 0x0 },
	{ 0x5402a, 0x0 },
	{ 0x5402b, 0x1000 },
	{ 0x5402c, 0x3 },
	{ 0x5402d, 0x0 },
	{ 0x5402e, 0x0 },
	{ 0x5402f, 0x0 },
	{ 0x54030, 0x0 },
	{ 0x54031, 0x0 },
	{ 0x54032, 0xd400 },
	{ 0x54033, ((((LPDDR4_RON) << 3) | 0x3) << 8) | 0x2d },
	{ 0x54034, (((LPDDR4_RTT_CA_BANK0 << 4) | LPDDR4_RTT_DQ) << 8) },
	{ 0x54035, (0x0800 | LPDDR4_VREF_VALUE_CA) },
	{ 0x54036, LPDDR4_VREF_VALUE_DQ_RANK0 },
	{ 0x54037, (LPDDR4_MR22_RANK0 << 8) },
	{ 0x54038, 0xd400 },
	{ 0x54039, ((((LPDDR4_RON) << 3) | 0x3) << 8) | 0x2d },
	{ 0x5403a, (((LPDDR4_RTT_CA_BANK1 << 4) | LPDDR4_RTT_DQ) << 8) },
	{ 0x5403b, (0x0800 | LPDDR4_VREF_VALUE_CA) },
	{ 0x5403c, LPDDR4_VREF_VALUE_DQ_RANK1 },
	{ 0x5403d, (LPDDR4_MR22_RANK1 << 8) },
	{ 0x5403d, (LPDDR4_MR22_RANK1 << 8) },
	{ 0x5403e, 0x0 },
	{ 0x5403f, 0x0 },
	{ 0x54040, 0x0 },
	{ 0x54041, 0x0 },
	{ 0x54042, 0x0 },
	{ 0x54043, 0x0 },
	{ 0x54044, 0x0 },
	{ 0xd0000, 0x1 },
};

/* P1 message block paremeter for training firmware */
static struct dram_cfg_param lpddr4_fsp1_cfg[] = {
	{ 0xd0000, 0x0 },
	{ 0x54000, 0x0 },
	{ 0x54001, 0x0 },
	{ 0x54002, 0x1 },
	{ 0x54003, 0x29c },
	{ 0x54004, 0x2 },
	{ 0x54005, ((LPDDR4_PHY_RON << 8) | LPDDR4_PHY_RTT) },
	{ 0x54006, LPDDR4_PHY_VREF_VALUE },
	{ 0x54007, 0x0 },
	{ 0x54008, 0x121f },
	{ 0x54009, 0xc8 },
	{ 0x5400a, 0x0 },
	{ 0x5400b, 0x2 },
	{ 0x5400c, 0x0 },
	{ 0x5400d, 0x0 },
	{ 0x5400e, 0x0 },
	{ 0x5400f, 0x0 },
	{ 0x54010, 0x0 },
	{ 0x54011, 0x0 },
	{ 0x54012, 0x310 },
	{ 0x54013, 0x0 },
	{ 0x54014, 0x0 },
	{ 0x54015, 0x0 },
	{ 0x54016, 0x0 },
	{ 0x54017, 0x0 },
	{ 0x54018, 0x0 },
	{ 0x54019, 0x914 },
	{ 0x5401a, (((LPDDR4_RON) << 3) | 0x1) },
	{ 0x5401b, ((LPDDR4_VREF_VALUE_CA << 8) |
		    (LPDDR4_RTT_CA_BANK0 << 4) | LPDDR4_RTT_DQ) },
	{ 0x5401c, ((LPDDR4_VREF_VALUE_DQ_RANK0 << 8) | 0x08) },
	{ 0x5401e, 0x6 },
	{ 0x5401f, 0x914 },
	{ 0x54020, (((LPDDR4_RON) << 3) | 0x1) },
	{ 0x54021, ((LPDDR4_VREF_VALUE_CA << 8) |
		    (LPDDR4_RTT_CA_BANK1 << 4) | LPDDR4_RTT_DQ) },
	{ 0x54022, ((LPDDR4_VREF_VALUE_DQ_RANK1 << 8) | 0x08) },
	{ 0x54023, 0x0 },
	{ 0x54024, LPDDR4_MR22_RANK1 },
	{ 0x54025, 0x0 },
	{ 0x54026, 0x0 },
	{ 0x54027, 0x0 },
	{ 0x54028, 0x0 },
	{ 0x54029, 0x0 },
	{ 0x5402a, 0x0 },
	{ 0x5402b, 0x1000 },
	{ 0x5402c, 0x3 },
	{ 0x5402d, 0x0 },
	{ 0x5402e, 0x0 },
	{ 0x5402f, 0x0 },
	{ 0x54030, 0x0 },
	{ 0x54031, 0x0 },
	{ 0x54032, 0x1400 },
	{ 0x54033, ((((LPDDR4_RON) << 3) | 0x1) << 8) | 0x09 },
	{ 0x54034, (((LPDDR4_RTT_CA_BANK0 << 4) | LPDDR4_RTT_DQ) << 8) },
	{ 0x54035, (0x0800 | LPDDR4_VREF_VALUE_CA) },
	{ 0x54036, LPDDR4_VREF_VALUE_DQ_RANK0 },
	{ 0x54037, 0x600 },
	{ 0x54038, 0x1400 },
	{ 0x54039, ((((LPDDR4_RON) << 3) | 0x1) << 8) | 0x09 },
	{ 0x5403a, (((LPDDR4_RTT_CA_BANK1 << 4) | LPDDR4_RTT_DQ) << 8) },
	{ 0x5403b, (0x0800 | LPDDR4_VREF_VALUE_CA) },
	{ 0x5403c, LPDDR4_VREF_VALUE_DQ_RANK1 },
	{ 0x5403d, (LPDDR4_MR22_RANK1 << 8) },
	{ 0x5403e, 0x0 },
	{ 0x5403f, 0x0 },
	{ 0x54040, 0x0 },
	{ 0x54041, 0x0 },
	{ 0x54042, 0x0 },
	{ 0x54043, 0x0 },
	{ 0xd0000, 0x1 },

};

/* P0 2D message block paremeter for training firmware */
static struct dram_cfg_param lpddr4_fsp0_2d_cfg[] = {
	{ 0xd0000, 0x0 },
	{ 0x54000, 0x0 },
	{ 0x54001, 0x0 },
	{ 0x54002, 0x0 },
	{ 0x54003, 0xc80 },
	{ 0x54004, 0x2 },
	{ 0x54005, ((LPDDR4_PHY_RON << 8) | LPDDR4_PHY_RTT) },
	{ 0x54006, LPDDR4_PHY_VREF_VALUE },
	{ 0x54007, 0x0 },
	{ 0x54008, 0x61 },
	{ 0x54009, LPDDR4_HDT_CTL_2D },
	{ 0x5400a, 0x0 },
	{ 0x5400b, 0x2 },
	{ 0x5400c, 0x0 },
	{ 0x5400d, (LPDDR4_CATRAIN_3200_2d << 8) },
	{ 0x5400e, 0x0 },
	{ 0x5400f, (LPDDR4_2D_SHARE << 8) | 0x00 },
	{ 0x54010, LPDDR4_2D_WEIGHT },
	{ 0x54011, 0x0 },
	{ 0x54012, 0x310 },
	{ 0x54013, 0x0 },
	{ 0x54014, 0x0 },
	{ 0x54015, 0x0 },
	{ 0x54016, 0x0 },
	{ 0x54017, 0x0 },
	{ 0x54018, 0x0 },
	{ 0x54024, 0x5 },
	{ 0x54019, 0x2dd4 },
	{ 0x5401a, (((LPDDR4_RON) << 3) | 0x3) },
	{ 0x5401b, ((LPDDR4_VREF_VALUE_CA << 8) |
		    (LPDDR4_RTT_CA_BANK0 << 4) | LPDDR4_RTT_DQ) },
	{ 0x5401c, ((LPDDR4_VREF_VALUE_DQ_RANK0 << 8) | 0x08) },
	{ 0x5401d, 0x0 },
	{ 0x5401e, LPDDR4_MR22_RANK0 },
	{ 0x5401f, 0x2dd4 },
	{ 0x54020, (((LPDDR4_RON) << 3) | 0x3) },
	{ 0x54021, ((LPDDR4_VREF_VALUE_CA << 8) |
		    (LPDDR4_RTT_CA_BANK1 << 4) | LPDDR4_RTT_DQ) },
	{ 0x54022, ((LPDDR4_VREF_VALUE_DQ_RANK1 << 8) | 0x08) },
	{ 0x54023, 0x0 },
	{ 0x54024, LPDDR4_MR22_RANK1 },
	{ 0x54025, 0x0 },
	{ 0x54026, 0x0 },
	{ 0x54027, 0x0 },
	{ 0x54028, 0x0 },
	{ 0x54029, 0x0 },
	{ 0x5402a, 0x0 },
	{ 0x5402b, 0x1000 },
	{ 0x5402c, 0x3 },
	{ 0x5402d, 0x0 },
	{ 0x5402e, 0x0 },
	{ 0x5402f, 0x0 },
	{ 0x54030, 0x0 },
	{ 0x54031, 0x0 },
	{ 0x54032, 0xd400 },
	{ 0x54033, ((((LPDDR4_RON) << 3) | 0x3) << 8) | 0x2d },
	{ 0x54034, (((LPDDR4_RTT_CA_BANK0 << 4) | LPDDR4_RTT_DQ) << 8) },
	{ 0x54035, (0x0800 | LPDDR4_VREF_VALUE_CA) },
	{ 0x54036, LPDDR4_VREF_VALUE_DQ_RANK0 },
	{ 0x54037, (LPDDR4_MR22_RANK0 << 8) },
	{ 0x54038, 0xd400 },
	{ 0x54039, ((((LPDDR4_RON) << 3) | 0x3) << 8) | 0x2d },
	{ 0x5403a, (((LPDDR4_RTT_CA_BANK1 << 4) | LPDDR4_RTT_DQ) << 8) },
	{ 0x5403b, (0x0800 | LPDDR4_VREF_VALUE_CA) },
	{ 0x5403c, LPDDR4_VREF_VALUE_DQ_RANK1 },
	{ 0x5403d, (LPDDR4_MR22_RANK1 << 8) },
	{ 0x5403e, 0x0 },
	{ 0x5403f, 0x0 },
	{ 0x54040, 0x0 },
	{ 0x54041, 0x0 },
	{ 0x54042, 0x0 },
	{ 0x54043, 0x0 },
	{ 0x54044, 0x0 },
	{ 0xd0000, 0x1 },

};

/* DRAM PHY init engine image */
static struct dram_cfg_param lpddr4_phy_pie[] = {
	{ 0xd0000, 0x0 },
	{ 0x90000, 0x10 },
	{ 0x90001, 0x400 },
	{ 0x90002, 0x10e },
	{ 0x90003, 0x0 },
	{ 0x90004, 0x0 },
	{ 0x90005, 0x8 },
	{ 0x90029, 0xb },
	{ 0x9002a, 0x480 },
	{ 0x9002b, 0x109 },
	{ 0x9002c, 0x8 },
	{ 0x9002d, 0x448 },
	{ 0x9002e, 0x139 },
	{ 0x9002f, 0x8 },
	{ 0x90030, 0x478 },
	{ 0x90031, 0x109 },
	{ 0x90032, 0x0 },
	{ 0x90033, 0xe8 },
	{ 0x90034, 0x109 },
	{ 0x90035, 0x2 },
	{ 0x90036, 0x10 },
	{ 0x90037, 0x139 },
	{ 0x90038, 0xb },
	{ 0x90039, 0x7c0 },
	{ 0x9003a, 0x139 },
	{ 0x9003b, 0x44 },
	{ 0x9003c, 0x630 },
	{ 0x9003d, 0x159 },
	{ 0x9003e, 0x14f },
	{ 0x9003f, 0x630 },
	{ 0x90040, 0x159 },
	{ 0x90041, 0x47 },
	{ 0x90042, 0x630 },
	{ 0x90043, 0x149 },
	{ 0x90044, 0x4f },
	{ 0x90045, 0x630 },
	{ 0x90046, 0x179 },
	{ 0x90047, 0x8 },
	{ 0x90048, 0xe0 },
	{ 0x90049, 0x109 },
	{ 0x9004a, 0x0 },
	{ 0x9004b, 0x7c8 },
	{ 0x9004c, 0x109 },
	{ 0x9004d, 0x0 },
	{ 0x9004e, 0x1 },
	{ 0x9004f, 0x8 },
	{ 0x90050, 0x0 },
	{ 0x90051, 0x45a },
	{ 0x90052, 0x9 },
	{ 0x90053, 0x0 },
	{ 0x90054, 0x448 },
	{ 0x90055, 0x109 },
	{ 0x90056, 0x40 },
	{ 0x90057, 0x630 },
	{ 0x90058, 0x179 },
	{ 0x90059, 0x1 },
	{ 0x9005a, 0x618 },
	{ 0x9005b, 0x109 },
	{ 0x9005c, 0x40c0 },
	{ 0x9005d, 0x630 },
	{ 0x9005e, 0x149 },
	{ 0x9005f, 0x8 },
	{ 0x90060, 0x4 },
	{ 0x90061, 0x48 },
	{ 0x90062, 0x4040 },
	{ 0x90063, 0x630 },
	{ 0x90064, 0x149 },
	{ 0x90065, 0x0 },
	{ 0x90066, 0x4 },
	{ 0x90067, 0x48 },
	{ 0x90068, 0x40 },
	{ 0x90069, 0x630 },
	{ 0x9006a, 0x149 },
	{ 0x9006b, 0x10 },
	{ 0x9006c, 0x4 },
	{ 0x9006d, 0x18 },
	{ 0x9006e, 0x0 },
	{ 0x9006f, 0x4 },
	{ 0x90070, 0x78 },
	{ 0x90071, 0x549 },
	{ 0x90072, 0x630 },
	{ 0x90073, 0x159 },
	{ 0x90074, 0xd49 },
	{ 0x90075, 0x630 },
	{ 0x90076, 0x159 },
	{ 0x90077, 0x94a },
	{ 0x90078, 0x630 },
	{ 0x90079, 0x159 },
	{ 0x9007a, 0x441 },
	{ 0x9007b, 0x630 },
	{ 0x9007c, 0x149 },
	{ 0x9007d, 0x42 },
	{ 0x9007e, 0x630 },
	{ 0x9007f, 0x149 },
	{ 0x90080, 0x1 },
	{ 0x90081, 0x630 },
	{ 0x90082, 0x149 },
	{ 0x90083, 0x0 },
	{ 0x90084, 0xe0 },
	{ 0x90085, 0x109 },
	{ 0x90086, 0xa },
	{ 0x90087, 0x10 },
	{ 0x90088, 0x109 },
	{ 0x90089, 0x9 },
	{ 0x9008a, 0x3c0 },
	{ 0x9008b, 0x149 },
	{ 0x9008c, 0x9 },
	{ 0x9008d, 0x3c0 },
	{ 0x9008e, 0x159 },
	{ 0x9008f, 0x18 },
	{ 0x90090, 0x10 },
	{ 0x90091, 0x109 },
	{ 0x90092, 0x0 },
	{ 0x90093, 0x3c0 },
	{ 0x90094, 0x109 },
	{ 0x90095, 0x18 },
	{ 0x90096, 0x4 },
	{ 0x90097, 0x48 },
	{ 0x90098, 0x18 },
	{ 0x90099, 0x4 },
	{ 0x9009a, 0x58 },
	{ 0x9009b, 0xa },
	{ 0x9009c, 0x10 },
	{ 0x9009d, 0x109 },
	{ 0x9009e, 0x2 },
	{ 0x9009f, 0x10 },
	{ 0x900a0, 0x109 },
	{ 0x900a1, 0x5 },
	{ 0x900a2, 0x7c0 },
	{ 0x900a3, 0x109 },
	{ 0x900a4, 0xd },
	{ 0x900a5, 0x7c0 },
	{ 0x900a6, 0x109 },
	{ 0x900a7, 0x4 },
	{ 0x900a8, 0x7c0 },
	{ 0x900a9, 0x109 },
	{ 0x40000, 0x811 },
	{ 0x40020, 0x880 },
	{ 0x40040, 0x0 },
	{ 0x40060, 0x0 },
	{ 0x40001, 0x4008 },
	{ 0x40021, 0x83 },
	{ 0x40041, 0x4f },
	{ 0x40061, 0x0 },
	{ 0x40002, 0x4040 },
	{ 0x40022, 0x83 },
	{ 0x40042, 0x51 },
	{ 0x40062, 0x0 },
	{ 0x40003, 0x811 },
	{ 0x40023, 0x880 },
	{ 0x40043, 0x0 },
	{ 0x40063, 0x0 },
	{ 0x40004, 0x720 },
	{ 0x40024, 0xf },
	{ 0x40044, 0x1740 },
	{ 0x40064, 0x0 },
	{ 0x40005, 0x16 },
	{ 0x40025, 0x83 },
	{ 0x40045, 0x4b },
	{ 0x40065, 0x0 },
	{ 0x40006, 0x716 },
	{ 0x40026, 0xf },
	{ 0x40046, 0x2001 },
	{ 0x40066, 0x0 },
	{ 0x40007, 0x716 },
	{ 0x40027, 0xf },
	{ 0x40047, 0x2800 },
	{ 0x40067, 0x0 },
	{ 0x40008, 0x716 },
	{ 0x40028, 0xf },
	{ 0x40048, 0xf00 },
	{ 0x40068, 0x0 },
	{ 0x40009, 0x720 },
	{ 0x40029, 0xf },
	{ 0x40049, 0x1400 },
	{ 0x40069, 0x0 },
	{ 0x4000a, 0xe08 },
	{ 0x4002a, 0xc15 },
	{ 0x4004a, 0x0 },
	{ 0x4006a, 0x0 },
	{ 0x4000b, 0x623 },
	{ 0x4002b, 0x15 },
	{ 0x4004b, 0x0 },
	{ 0x4006b, 0x0 },
	{ 0x4000c, 0x4028 },
	{ 0x4002c, 0x80 },
	{ 0x4004c, 0x0 },
	{ 0x4006c, 0x0 },
	{ 0x4000d, 0xe08 },
	{ 0x4002d, 0xc1a },
	{ 0x4004d, 0x0 },
	{ 0x4006d, 0x0 },
	{ 0x4000e, 0x623 },
	{ 0x4002e, 0x1a },
	{ 0x4004e, 0x0 },
	{ 0x4006e, 0x0 },
	{ 0x4000f, 0x4040 },
	{ 0x4002f, 0x80 },
	{ 0x4004f, 0x0 },
	{ 0x4006f, 0x0 },
	{ 0x40010, 0x2604 },
	{ 0x40030, 0x15 },
	{ 0x40050, 0x0 },
	{ 0x40070, 0x0 },
	{ 0x40011, 0x708 },
	{ 0x40031, 0x5 },
	{ 0x40051, 0x0 },
	{ 0x40071, 0x2002 },
	{ 0x40012, 0x8 },
	{ 0x40032, 0x80 },
	{ 0x40052, 0x0 },
	{ 0x40072, 0x0 },
	{ 0x40013, 0x2604 },
	{ 0x40033, 0x1a },
	{ 0x40053, 0x0 },
	{ 0x40073, 0x0 },
	{ 0x40014, 0x708 },
	{ 0x40034, 0xa },
	{ 0x40054, 0x0 },
	{ 0x40074, 0x2002 },
	{ 0x40015, 0x4040 },
	{ 0x40035, 0x80 },
	{ 0x40055, 0x0 },
	{ 0x40075, 0x0 },
	{ 0x40016, 0x60a },
	{ 0x40036, 0x15 },
	{ 0x40056, 0x1200 },
	{ 0x40076, 0x0 },
	{ 0x40017, 0x61a },
	{ 0x40037, 0x15 },
	{ 0x40057, 0x1300 },
	{ 0x40077, 0x0 },
	{ 0x40018, 0x60a },
	{ 0x40038, 0x1a },
	{ 0x40058, 0x1200 },
	{ 0x40078, 0x0 },
	{ 0x40019, 0x642 },
	{ 0x40039, 0x1a },
	{ 0x40059, 0x1300 },
	{ 0x40079, 0x0 },
	{ 0x4001a, 0x4808 },
	{ 0x4003a, 0x880 },
	{ 0x4005a, 0x0 },
	{ 0x4007a, 0x0 },
	{ 0x900aa, 0x0 },
	{ 0x900ab, 0x790 },
	{ 0x900ac, 0x11a },
	{ 0x900ad, 0x8 },
	{ 0x900ae, 0x7aa },
	{ 0x900af, 0x2a },
	{ 0x900b0, 0x10 },
	{ 0x900b1, 0x7b2 },
	{ 0x900b2, 0x2a },
	{ 0x900b3, 0x0 },
	{ 0x900b4, 0x7c8 },
	{ 0x900b5, 0x109 },
	{ 0x900b6, 0x10 },
	{ 0x900b7, 0x10 },
	{ 0x900b8, 0x109 },
	{ 0x900b9, 0x10 },
	{ 0x900ba, 0x2a8 },
	{ 0x900bb, 0x129 },
	{ 0x900bc, 0x8 },
	{ 0x900bd, 0x370 },
	{ 0x900be, 0x129 },
	{ 0x900bf, 0xa },
	{ 0x900c0, 0x3c8 },
	{ 0x900c1, 0x1a9 },
	{ 0x900c2, 0xc },
	{ 0x900c3, 0x408 },
	{ 0x900c4, 0x199 },
	{ 0x900c5, 0x14 },
	{ 0x900c6, 0x790 },
	{ 0x900c7, 0x11a },
	{ 0x900c8, 0x8 },
	{ 0x900c9, 0x4 },
	{ 0x900ca, 0x18 },
	{ 0x900cb, 0xe },
	{ 0x900cc, 0x408 },
	{ 0x900cd, 0x199 },
	{ 0x900ce, 0x8 },
	{ 0x900cf, 0x8568 },
	{ 0x900d0, 0x108 },
	{ 0x900d1, 0x18 },
	{ 0x900d2, 0x790 },
	{ 0x900d3, 0x16a },
	{ 0x900d4, 0x8 },
	{ 0x900d5, 0x1d8 },
	{ 0x900d6, 0x169 },
	{ 0x900d7, 0x10 },
	{ 0x900d8, 0x8558 },
	{ 0x900d9, 0x168 },
	{ 0x900da, 0x70 },
	{ 0x900db, 0x788 },
	{ 0x900dc, 0x16a },
	{ 0x900dd, 0x1ff8 },
	{ 0x900de, 0x85a8 },
	{ 0x900df, 0x1e8 },
	{ 0x900e0, 0x50 },
	{ 0x900e1, 0x798 },
	{ 0x900e2, 0x16a },
	{ 0x900e3, 0x60 },
	{ 0x900e4, 0x7a0 },
	{ 0x900e5, 0x16a },
	{ 0x900e6, 0x8 },
	{ 0x900e7, 0x8310 },
	{ 0x900e8, 0x168 },
	{ 0x900e9, 0x8 },
	{ 0x900ea, 0xa310 },
	{ 0x900eb, 0x168 },
	{ 0x900ec, 0xa },
	{ 0x900ed, 0x408 },
	{ 0x900ee, 0x169 },
	{ 0x900ef, 0x6e },
	{ 0x900f0, 0x0 },
	{ 0x900f1, 0x68 },
	{ 0x900f2, 0x0 },
	{ 0x900f3, 0x408 },
	{ 0x900f4, 0x169 },
	{ 0x900f5, 0x0 },
	{ 0x900f6, 0x8310 },
	{ 0x900f7, 0x168 },
	{ 0x900f8, 0x0 },
	{ 0x900f9, 0xa310 },
	{ 0x900fa, 0x168 },
	{ 0x900fb, 0x1ff8 },
	{ 0x900fc, 0x85a8 },
	{ 0x900fd, 0x1e8 },
	{ 0x900fe, 0x68 },
	{ 0x900ff, 0x798 },
	{ 0x90100, 0x16a },
	{ 0x90101, 0x78 },
	{ 0x90102, 0x7a0 },
	{ 0x90103, 0x16a },
	{ 0x90104, 0x68 },
	{ 0x90105, 0x790 },
	{ 0x90106, 0x16a },
	{ 0x90107, 0x8 },
	{ 0x90108, 0x8b10 },
	{ 0x90109, 0x168 },
	{ 0x9010a, 0x8 },
	{ 0x9010b, 0xab10 },
	{ 0x9010c, 0x168 },
	{ 0x9010d, 0xa },
	{ 0x9010e, 0x408 },
	{ 0x9010f, 0x169 },
	{ 0x90110, 0x58 },
	{ 0x90111, 0x0 },
	{ 0x90112, 0x68 },
	{ 0x90113, 0x0 },
	{ 0x90114, 0x408 },
	{ 0x90115, 0x169 },
	{ 0x90116, 0x0 },
	{ 0x90117, 0x8b10 },
	{ 0x90118, 0x168 },
	{ 0x90119, 0x0 },
	{ 0x9011a, 0xab10 },
	{ 0x9011b, 0x168 },
	{ 0x9011c, 0x0 },
	{ 0x9011d, 0x1d8 },
	{ 0x9011e, 0x169 },
	{ 0x9011f, 0x80 },
	{ 0x90120, 0x790 },
	{ 0x90121, 0x16a },
	{ 0x90122, 0x18 },
	{ 0x90123, 0x7aa },
	{ 0x90124, 0x6a },
	{ 0x90125, 0xa },
	{ 0x90126, 0x0 },
	{ 0x90127, 0x1e9 },
	{ 0x90128, 0x8 },
	{ 0x90129, 0x8080 },
	{ 0x9012a, 0x108 },
	{ 0x9012b, 0xf },
	{ 0x9012c, 0x408 },
	{ 0x9012d, 0x169 },
	{ 0x9012e, 0xc },
	{ 0x9012f, 0x0 },
	{ 0x90130, 0x68 },
	{ 0x90131, 0x9 },
	{ 0x90132, 0x0 },
	{ 0x90133, 0x1a9 },
	{ 0x90134, 0x0 },
	{ 0x90135, 0x408 },
	{ 0x90136, 0x169 },
	{ 0x90137, 0x0 },
	{ 0x90138, 0x8080 },
	{ 0x90139, 0x108 },
	{ 0x9013a, 0x8 },
	{ 0x9013b, 0x7aa },
	{ 0x9013c, 0x6a },
	{ 0x9013d, 0x0 },
	{ 0x9013e, 0x8568 },
	{ 0x9013f, 0x108 },
	{ 0x90140, 0xb7 },
	{ 0x90141, 0x790 },
	{ 0x90142, 0x16a },
	{ 0x90143, 0x1f },
	{ 0x90144, 0x0 },
	{ 0x90145, 0x68 },
	{ 0x90146, 0x8 },
	{ 0x90147, 0x8558 },
	{ 0x90148, 0x168 },
	{ 0x90149, 0xf },
	{ 0x9014a, 0x408 },
	{ 0x9014b, 0x169 },
	{ 0x9014c, 0xc },
	{ 0x9014d, 0x0 },
	{ 0x9014e, 0x68 },
	{ 0x9014f, 0x0 },
	{ 0x90150, 0x408 },
	{ 0x90151, 0x169 },
	{ 0x90152, 0x0 },
	{ 0x90153, 0x8558 },
	{ 0x90154, 0x168 },
	{ 0x90155, 0x8 },
	{ 0x90156, 0x3c8 },
	{ 0x90157, 0x1a9 },
	{ 0x90158, 0x3 },
	{ 0x90159, 0x370 },
	{ 0x9015a, 0x129 },
	{ 0x9015b, 0x20 },
	{ 0x9015c, 0x2aa },
	{ 0x9015d, 0x9 },
	{ 0x9015e, 0x0 },
	{ 0x9015f, 0x400 },
	{ 0x90160, 0x10e },
	{ 0x90161, 0x8 },
	{ 0x90162, 0xe8 },
	{ 0x90163, 0x109 },
	{ 0x90164, 0x0 },
	{ 0x90165, 0x8140 },
	{ 0x90166, 0x10c },
	{ 0x90167, 0x10 },
	{ 0x90168, 0x8138 },
	{ 0x90169, 0x10c },
	{ 0x9016a, 0x8 },
	{ 0x9016b, 0x7c8 },
	{ 0x9016c, 0x101 },
	{ 0x9016d, 0x8 },
	{ 0x9016e, 0x0 },
	{ 0x9016f, 0x8 },
	{ 0x90170, 0x8 },
	{ 0x90171, 0x448 },
	{ 0x90172, 0x109 },
	{ 0x90173, 0xf },
	{ 0x90174, 0x7c0 },
	{ 0x90175, 0x109 },
	{ 0x90176, 0x0 },
	{ 0x90177, 0xe8 },
	{ 0x90178, 0x109 },
	{ 0x90179, 0x47 },
	{ 0x9017a, 0x630 },
	{ 0x9017b, 0x109 },
	{ 0x9017c, 0x8 },
	{ 0x9017d, 0x618 },
	{ 0x9017e, 0x109 },
	{ 0x9017f, 0x8 },
	{ 0x90180, 0xe0 },
	{ 0x90181, 0x109 },
	{ 0x90182, 0x0 },
	{ 0x90183, 0x7c8 },
	{ 0x90184, 0x109 },
	{ 0x90185, 0x8 },
	{ 0x90186, 0x8140 },
	{ 0x90187, 0x10c },
	{ 0x90188, 0x0 },
	{ 0x90189, 0x1 },
	{ 0x9018a, 0x8 },
	{ 0x9018b, 0x8 },
	{ 0x9018c, 0x4 },
	{ 0x9018d, 0x8 },
	{ 0x9018e, 0x8 },
	{ 0x9018f, 0x7c8 },
	{ 0x90190, 0x101 },
	{ 0x90006, 0x0 },
	{ 0x90007, 0x0 },
	{ 0x90008, 0x8 },
	{ 0x90009, 0x0 },
	{ 0x9000a, 0x0 },
	{ 0x9000b, 0x0 },
	{ 0xd00e7, 0x400 },
	{ 0x90017, 0x0 },
	{ 0x9001f, 0x2b },
	{ 0x90026, 0x6c },
	{ 0x400d0, 0x0 },
	{ 0x400d1, 0x101 },
	{ 0x400d2, 0x105 },
	{ 0x400d3, 0x107 },
	{ 0x400d4, 0x10f },
	{ 0x400d5, 0x202 },
	{ 0x400d6, 0x20a },
	{ 0x400d7, 0x20b },
	{ 0x2003a, 0x2 },
	{ 0x2000b, 0x64 },
	{ 0x2000c, 0xc8 },
	{ 0x2000d, 0x7d0 },
	{ 0x2000e, 0x2c },
	{ 0x12000b, 0x14 },
	{ 0x12000c, 0x29 },
	{ 0x12000d, 0x1a1 },
	{ 0x12000e, 0x10 },
	{ 0x22000b, 0x3 },
	{ 0x22000c, 0x6 },
	{ 0x22000d, 0x3e },
	{ 0x22000e, 0x10 },
	{ 0x9000c, 0x0 },
	{ 0x9000d, 0x173 },
	{ 0x9000e, 0x60 },
	{ 0x9000f, 0x6110 },
	{ 0x90010, 0x2152 },
	{ 0x90011, 0xdfbd },
	{ 0x90012, 0x60 },
	{ 0x90013, 0x6152 },
	{ 0x20010, 0x5a },
	{ 0x20011, 0x3 },
	{ 0x40080, 0xe0 },
	{ 0x40081, 0x12 },
	{ 0x40082, 0xe0 },
	{ 0x40083, 0x12 },
	{ 0x40084, 0xe0 },
	{ 0x40085, 0x12 },
	{ 0x140080, 0xe0 },
	{ 0x140081, 0x12 },
	{ 0x140082, 0xe0 },
	{ 0x140083, 0x12 },
	{ 0x140084, 0xe0 },
	{ 0x140085, 0x12 },
	{ 0x240080, 0xe0 },
	{ 0x240081, 0x12 },
	{ 0x240082, 0xe0 },
	{ 0x240083, 0x12 },
	{ 0x240084, 0xe0 },
	{ 0x240085, 0x12 },
	{ 0x400fd, 0xf },
	{ 0x10011, 0x1 },
	{ 0x10012, 0x1 },
	{ 0x10013, 0x180 },
	{ 0x10018, 0x1 },
	{ 0x10002, 0x6209 },
	{ 0x100b2, 0x1 },
	{ 0x101b4, 0x1 },
	{ 0x102b4, 0x1 },
	{ 0x103b4, 0x1 },
	{ 0x104b4, 0x1 },
	{ 0x105b4, 0x1 },
	{ 0x106b4, 0x1 },
	{ 0x107b4, 0x1 },
	{ 0x108b4, 0x1 },
	{ 0x11011, 0x1 },
	{ 0x11012, 0x1 },
	{ 0x11013, 0x180 },
	{ 0x11018, 0x1 },
	{ 0x11002, 0x6209 },
	{ 0x110b2, 0x1 },
	{ 0x111b4, 0x1 },
	{ 0x112b4, 0x1 },
	{ 0x113b4, 0x1 },
	{ 0x114b4, 0x1 },
	{ 0x115b4, 0x1 },
	{ 0x116b4, 0x1 },
	{ 0x117b4, 0x1 },
	{ 0x118b4, 0x1 },
	{ 0x12011, 0x1 },
	{ 0x12012, 0x1 },
	{ 0x12013, 0x180 },
	{ 0x12018, 0x1 },
	{ 0x12002, 0x6209 },
	{ 0x120b2, 0x1 },
	{ 0x121b4, 0x1 },
	{ 0x122b4, 0x1 },
	{ 0x123b4, 0x1 },
	{ 0x124b4, 0x1 },
	{ 0x125b4, 0x1 },
	{ 0x126b4, 0x1 },
	{ 0x127b4, 0x1 },
	{ 0x128b4, 0x1 },
	{ 0x13011, 0x1 },
	{ 0x13012, 0x1 },
	{ 0x13013, 0x180 },
	{ 0x13018, 0x1 },
	{ 0x13002, 0x6209 },
	{ 0x130b2, 0x1 },
	{ 0x131b4, 0x1 },
	{ 0x132b4, 0x1 },
	{ 0x133b4, 0x1 },
	{ 0x134b4, 0x1 },
	{ 0x135b4, 0x1 },
	{ 0x136b4, 0x1 },
	{ 0x137b4, 0x1 },
	{ 0x138b4, 0x1 },
	{ 0x20089, 0x1 },
	{ 0x20088, 0x19 },
	{ 0xc0080, 0x2 },
	{ 0xd0000, 0x1 },
};

static struct dram_fsp_msg lpddr4_dram_fsp_msg[] = {
	{
		/* P0 3200mts 1D */
		.drate = 3200,
		.fw_type = FW_1D_IMAGE,
		.fsp_cfg = lpddr4_fsp0_cfg,
		.fsp_cfg_num = ARRAY_SIZE(lpddr4_fsp0_cfg),
	},
	{
		/* P1 667mts 1D */
		.drate = 667,
		.fw_type = FW_1D_IMAGE,
		.fsp_cfg = lpddr4_fsp1_cfg,
		.fsp_cfg_num = ARRAY_SIZE(lpddr4_fsp1_cfg),
	},
	{
		/* P0 3200mts 2D */
		.drate = 3200,
		.fw_type = FW_2D_IMAGE,
		.fsp_cfg = lpddr4_fsp0_2d_cfg,
		.fsp_cfg_num = ARRAY_SIZE(lpddr4_fsp0_2d_cfg),
	},
};

/* lpddr4 timing config params on EVK board */
struct dram_timing_info dram_timing_b0 = {
	.ddrc_cfg = lpddr4_ddrc_cfg,
	.ddrc_cfg_num = ARRAY_SIZE(lpddr4_ddrc_cfg),
	.ddrphy_cfg = lpddr4_ddrphy_cfg,
	.ddrphy_cfg_num = ARRAY_SIZE(lpddr4_ddrphy_cfg),
	.fsp_msg = lpddr4_dram_fsp_msg,
	.fsp_msg_num = ARRAY_SIZE(lpddr4_dram_fsp_msg),
	.ddrphy_pie = lpddr4_phy_pie,
	.ddrphy_pie_num = ARRAY_SIZE(lpddr4_phy_pie),
	/*
	 * this table must be initialized if DDRPHY bypass mode is
	 * not used: all fsp drate > 666MTS.
	 */
	.fsp_table = { 3200, 667, },
};
