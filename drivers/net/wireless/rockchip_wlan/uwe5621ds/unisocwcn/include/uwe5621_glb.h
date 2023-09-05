/* SPDX-License-Identifier: GPL-2.0 */
#ifndef __UWE5621_GLB_H__
#define __UWE5621_GLB_H__

#include "../sleep/slp_mgr.h"
#include "mem_pd_mgr.h"
#include "rdc_debug.h"

/* log buf size */
#define MDBG_RX_RING_SIZE		(64*1024)

#define CP_START_ADDR		0x40500000
#define CP_RESET_REG		0x40088288
#define CP_SDIO_PRIORITY_ADDR 0x40130150

/* set sdio higher priority to visit iram */
#define M6_TO_S0_HIGH_PRIORITY 0X80000000

#define PACKET_SIZE		(32*1024)
/* time out in waiting wifi to come up */
#define POWERUP_WAIT_MS	30000
#define POWERUP_DELAY		200
#define RESET_DELAY		1

#define FIRMWARE_MAX_SIZE 0xf0c00
#define WIFI_REG 0x60300004
#define CHIPID_REG 0x4083c208
#define CALI_REG 0x70040000
#define CALI_OFSET_REG 0x70040010
#define MARLIN_AA_CHIPID 0x23550000
#define MARLIN_AB_CHIPID 0x23550001
#define MARLIN_AC_CHIPID 0x23550002
#define MARLIN_AD_CHIPID 0x23550003
#define MARLIN3_AA_CHIPID	MARLIN_AA_CHIPID
#define MARLIN3L_AA_CHIPID	0
#define MARLIN3E_AA_CHIPID	0

#define CARD_DETECT_WAIT_MS	3000
#define DCACHE_CMD_ISSUE_START 0X80000000
#define DCACHE_CMD_CLEAN_ALL 0X00000000
#define DCACHE_CMD_CLEAN_INVALID_ALL 0X00000008
#define DCACHE_REG_BASE 0X401E0000
#define DCACHE_REG_ENABLE (DCACHE_REG_BASE)
#define DCACHE_CFG0 (DCACHE_REG_BASE + 0X0040)
#define DCACHE_CMD_CFG2 (DCACHE_REG_BASE + 0X0058)
#define DCACHE_INT_RAW_STS (DCACHE_REG_BASE + 0X0064)
#define DCACHE_INT_CLR (DCACHE_REG_BASE + 0X006C)
#define DCACHE_CMD_IRQ_CLR 0X00000001
#define DCACHE_CMD_CFG2_MASK 0X8000003F
#define DCACHE_ENABLE_MASK 0XFFFFFFFF
#define DCACHE_DEBUG_EN 0X80000000
#define DCACHE_SIZE_32K 0X3
#define DCACHE_SIZE_SEL_MASK 0X30000000

#define DUMP_PACKET_SIZE		(32 * 1024)
#define DUMP_SDIO_ADDR			(0x40140000)
#define DUMP_SDIO_ADDR_SIZE		(0x10000)
/* for wifi */
#define DUMP_WIFI_AON_MAC_ADDR			(0x400f0000)
#define DUMP_WIFI_AON_MAC_ADDR_SIZE		(0x108)
#define DUMP_WIFI_REF_ADDR			(0x4083c000)
#define DUMP_WIFI_REF_ADDR_SIZE			(0x350)
#define DUMP_WIFI_RTN_PD_MAC_ADDR		(0x400f1000)
#define DUMP_WIFI_RTN_PD_MAC_ADDR_SIZE		(0xD100)
#define DUMP_WIFI_352K_RAM_ADDR			(0x40300000)
#define DUMP_WIFI_352K_RAM_ADDR_SIZE		(0x58000)
#define CHIP_SLP				(0X4083C00C)
#define WIFI_WRAP_PWRON				(1 << 14)
#define WIFI_PHY_PWRON				(1 << 15)
#define WIFI_MAC_PWRON				(1 << 16)
#define WIFI_ALL_PWRON	(WIFI_MAC_PWRON | WIFI_WRAP_PWRON)
#define PD_WIFI_AON_CFG4			(0x4083c088)
#define PD_WIFI_MAC_AON_CFG4			(0X4083C0A8)
#define PD_WIFI_PHY_AON_CFG4			(0x4083C0B8)
#define WIFI_MAC_RTN_SLEEPPS_CTL		(0x400f4704)
#define WIFI_RETENTION				(1 << 0)
#define WIFI_WRAP_PWR_DOWN			(1 << 1)
#define WIFI_MAC_PWR_DOWN			(1 << 2)
#define WIFI_PHY_PWR_DOWN			(1 << 2)
#define WIFI_ENABLE				(0x40130004)
#define AHB_EB0					(0x40130004)
#define WIFI_EN					(1 << 5)
#define BT_EN					(1 << 4)
#define WIFI_MAC_EN				(1 << 9)
#define WIFI_ALL_EN		(WIFI_EN | WIFI_MAC_EN)
#define CLK_CTRL0			0x4083c040
#define APLL_PDN			(1 << 0)
#define BPLL_PDN			(1 << 1)

/* AON_APB */
#define CLK_CTL3			0x4083c04c
#define BT_32M_EB			(1 << 18)
#define BT_64M_EB			(1 << 19)

/* for BT */
#define BT_ACC_ADDR			(0x40240000)
#define BT_ACC_SIZE			(0x8d8)
#define BT_JAL_ADDR			(0x40246000)
#define BT_JAL_SIZE			(0x738)
#define BT_HAB_ADDR			(0x40248000)
#define BT_HAB_SIZE			(0xA0)
#define BT_LEJAL_ADDR			(0x4024A000)
#define BT_LEJAL_SIZE			(0x21C)
#define BT_MODEM_ADDR			(0x4024F000)
#define BT_MODEM_SIZE			(0x300)
/* for BT (HW DEC and BB) Buffer */
#define HCI_ARM_WR_RD_MODE		(0x40240600)
#define HCI_ARM_WR_RD_VALUE		(0xFFFF)

#define BT_CMD_BUF_ADDR		(0x40200000)
#define BT_CMD_BUF_SIZE		(0x200)
#define BT_EVENT_BUF_ADDR		(0x40204000)
#define BT_EVENT_BUF_SIZE		(0x200)
#define BT_LMP_TX_BUF_ADDR		(0x40208000)
#define BT_LMP_TX_BUF_SIZE		(0x12A4)
#define BT_LMP_RX_BUF_ADDR		(0x40200C00)
#define BT_LMP_RX_BUF_SIZE		(0xB744)
#define BT_ACL_TX_BUF_ADDR		(0x40210000)
#define BT_ACL_TX_BUF_SIZE		(0x3000)
#define BT_ACL_RX_BUF_ADDR		(0x40214000)
#define BT_ACL_RX_BUF_SIZE		(0x3000)
#define BT_SCO_TX_BUF_ADDR		(0x40218000)
#define BT_SCO_TX_BUF_SIZE		(0x2D0)
#define BT_SCO_RX_BUF_ADDR		(0x4021C000)
#define BT_SCO_RX_BUF_SIZE		(0x5C0)
#define BT_BB_TX_BUF_ADDR		(0x40241000)
#define BT_BB_TX_BUF_SIZE		(0x400)
#define BT_BB_RX_BUF_ADDR		(0x40242000)
#define BT_BB_RX_BUF_SIZE		(0x400)

#define DUMP_BT_ADDR			(0)
#define DUMP_BT_ADDR_SIZE		(0)
/* for fm */
#define DUMP_FM1_ADDR			(0x40098000)
#define DUMP_FM1_ADDR_SIZE		(0x238)
#define DUMP_FM_RDS_ADDR		(0x40098800)
#define DUMP_FM_RDS_ADDR_SIZE		(0x4c)
#define DUMP_FM_ADDR			(0x40098000)
#define DUMP_FM_ADDR_SIZE		(0xabc)

#define DUMP_INTC_ADDR			(0)
#define DUMP_SYSTIMER_ADDR		(0)
/* need check, not need to dump it */
#define DUMP_WDG_ADDR			0
#define DUMP_WIFI_ADDR			0
#define DUMP_WIFI_ADDR_SIZE		0
#define DUMP_BT_CMD_ADDR		0
#define DUMP_BT_CMD_ADDR_SIZE	0

/* For TOP */
#define AON_AHB_ADDR			(0x40880000)
#define AON_AHB_SIZE			(0x54)
#define AON_APB_ADDR			(0x4083C000)
#define AON_APB_SIZE			(0x354)
#define BTWF_AHB_ADDR			(0x40130000)
#define BTWF_AHB_SIZE			(0x400)
#define BTWF_APB_ADDR			(0x40088000)
#define BTWF_APB_SIZE			(0x28C)
#define AON_CLK_ADDR			(0x40844200)
#define AON_CLK_SIZE			(0x144)
#define PRE_DIV_CLK_ADDR		(0x40844000)
#define PRE_DIV_CLK_SIZE		(0x48)

#define DUMP_APB_ADDR			(0)
#define DUMP_DMA_ADDR			(0)
#define DUMP_AHB_ADDR			(0)
#define DUMP_REG_SIZE			(0X10000)

#define SMP_HEADERFLAG 0X7E7E7E7E
#define SMP_RESERVEDFLAG 0X5A5A
#define SMP_DSP_CHANNEL_NUM 0X88
#define SMP_DSP_TYPE 0X9D
#define SMP_DSP_DUMP_TYPE 0X32

#define SYSNC_CODE_LEN 0X4
#define CHKSUM_LEN 0X2
#define ARMLOG_HEAD 9

/* For GNSS */
#define GNSS_CP_START_ADDR	0x40A20000
#define GNSS_CP_RESET_REG	0x40BC8280
#define GNSS_FIRMWARE_MAX_SIZE 0x58000
#define GNSS_CHIPID_REG 0x603003fc

/* For MARLIN3 DCACHE */
#define DCACHE_CMD_ISSUE_START 0X80000000
#define DCACHE_CMD_CLEAN_ALL 0X00000000
#define DCACHE_CMD_CLEAN_INVALID_ALL 0X00000008
#define DCACHE_REG_BASE 0X401E0000
#define DCACHE_CFG0 (DCACHE_REG_BASE + 0X0040)
#define DCACHE_CMD_CFG2 (DCACHE_REG_BASE + 0X0058)
#define DCACHE_INT_RAW_STS (DCACHE_REG_BASE + 0X0064)
#define DCACHE_INT_CLR (DCACHE_REG_BASE + 0X006C)
#define DCACHE_CMD_IRQ_CLR 0X00000001
#define DCACHE_CMD_CFG2_MASK 0X8000003F
#define DCACHE_DEBUG_EN 0X80000000
#define DCACHE_SIZE_32K 0X3
#define DCACHE_SIZE_SEL_MASK 0X30000000


/* For MARLIN3 MEM PD  */
#define CTL_BASE_AON_APB 0X4083C000
#define REG_AON_APB_CHIP_MEM_AUTO_EN (CTL_BASE_AON_APB + 0X0198)
#define REG_AON_APB_BTWF_MEM_CGG1 (CTL_BASE_AON_APB + 0X010C)
/* SHUTDOWN IRAM [0...15]*32K=512K,FORCE SHUTDOWN IRAM [16...31]*32K=512K */
#define REG_AON_APB_BTWF_MEM_CGG2 (CTL_BASE_AON_APB + 0X0110)
/* RETENTION IRAM [0...15]*32K=512K,FORCE RETENTION IRAM [16...31]*32K=512K */
#define REG_AON_APB_BTWF_MEM_CGG3 (CTL_BASE_AON_APB + 0X0114)
/* SHUTDOWN IRAM [0...13]*32K=448K,[14]mean 3k; */
#define REG_AON_APB_BTWF_MEM_CGG4 (CTL_BASE_AON_APB + 0X0118)


/* for dump arm register */
#define AON_APB_BASE_ADDR 0X4083C000

#define ARM_DAP_BASE_ADDR 0X4085C000
#define ARM_DAP_REG1 0X4085C000
#define ARM_DAP_REG2 0X4085C004
#define ARM_DAP_REG3 0X4085C00C

#define BTWF_STATUS_REG 0x4085c0fc
#define BTWF_OK_VALUE 0x24770011
#define GNSS_OK 0x408600fc

#define DJTAG_DAP_SEL (AON_APB_BASE_ADDR + 0X0064)
#define APB_RST (AON_APB_BASE_ADDR + 0x0000)
#define APB_EB  (AON_APB_BASE_ADDR + 0x0024)
#define CM4_DAP_SEL_BTWF 0X00000001	/* bit0 */
#define CM4_DAP_SEL_GNSS 0X00000002	/* bit1 */
#define CM4_DAP0_SOFT_RST 0X10000000	/* BIT28 */
#define CM4_DAP1_SOFT_RST 0X20000000	/* BIT29 */
#define CM4_DAP0_EB 0X40000000	/* BIT30 */
#define CM4_DAP1_EB 0X80000000	/* BIT31 */

#define PD_GNSS_SS_AON_CFG4 (AON_APB_BASE_ADDR + 0X00c8)
#define PD_AUTO_EN		(1 << 12)
#define FORCE_DEEP_SLEEP	(1 << 3)
#define GNSS_SS_POWER_DOWN	(1 << 2)/* NO USE */
#define CHIP_DEEP_SLP_EN	(1 << 1)

#define SYNC_ADDR		0x405F0BB0
#define SYNC_IN_PROGRESS	0xF0F0F0F0
#define SYNC_CALI_WAITING	0xF0F0F0F1
#define SYNC_CALI_WRITE_DONE	0xF0F0F0F2
#define SYNC_CALI_FINISHED	0xF0F0F0F3
#define SYNC_SDIO_REINIT_DONE	0xF0F0F0F4
#define SYNC_SDIO_IS_READY	0xF0F0F0F5
#define SYNC_VERIFY_WAITING	0xF0F0F0F6
#define SYNC_VERIFY_WRITE_DONE	0xF0F0F0F7
#define SYNC_VERIFY_FINISHED	0xF0F0F0F8
#define SYNC_ALL_FINISHED	0xF0F0F0FF
#define CHIP_SLP_REG		(AON_APB_BASE_ADDR + 0X000c)
#define GNSS_SS_PWRON_FINISH	(1 << 12)
#define GNSS_PWR_FINISH	(1 << 13)

#define CGM_GNSS_FAKE_CFG (0x40844200 + 0X0104)
#define CGM_GNSS_FAKE_SEL (0x3)

/* for sleep/wakeup */
#define REG_CP_SLP_CTL		0x1a2
#define REG_AP_INT_CP0		0x1b0
#define REG_PUB_INT_EN0		0x1c0
#define REG_PUB_INT_CLR0	0x1d0
#define REG_PUB_INT_STS0	0x1f0
/* BIT4~7, if value 0, stand for in deepsleep */
#define REG_BTWF_SLP_STS	0x148
#define BTWF_IN_DEEPSLEEP	0x0
/* fm playing in deep, and xtl on */
#define BTWF_IN_DEEPSLEEP_XLT_ON	0x30
#define  SLEEP_STATUS_FLAG 0xF0
/* For power save */
#define REG_WIFI_MEM_CFG1	0x4083c130
#define FORCE_SHUTDOWN_BTRAM	(1 << 22)

/* For FM Spue freq */
#define FM_REG_SPUR_FEQ1_ADDR			0x40098104
#define FM_DISABLE_SPUR_REMOVE_VALUE		0x06DC063C
#define FM_ENABLE_SPUR_REMOVE_FREQ2_VALUE	0x06DCAB7C

/*
 * For SPI interface
 * bit[15]:1'b0: TCXO mode, outside clock
 * bit[15]:1'b1: Crystal/TSX mode
 */
#define SPI_BASE_ADDR		0x408a0000
#define AD_DCXO_BONDING_OPT	0x5030
#define tsx_mode		(1 << 15)
#define SPI_BIT31		(1 << 31)

#define AON_APB_TEST_READ_REG	AON_APB_BASE_ADDR

/* for debug dump */
#define WIFI_AON_MAC_SIZE	0x108
#define WIFI_RAM_SIZE		0x58000
#define WIFI_GLB_REG_SIZE	0x4c

#define RESET_BIT		(1<<0)
#endif
