/**
 * Configuration for the DPT-Module V1. The DPT-Module 
 * has the following pinout:
 * 
 *         +---------------------------+
 *  GND <--|                           |
 *  ANT <--|                           |
 *  GND <--|                           |--> SPI_CLK
 *         |                           |--> SPI_MOSI
 * IO12 <--|                           |--> SPI_MISO
 *  GND <--|                           |--> SPI_CSO
 * IO26 <--|                           |--> GND
 * IO27 <--|                           |--> E_2V2
 * IO11 <--|                           |--> USB+
 *  IO7 <--|                           |--> USB-
 *  IO6 <--|                           |--> J_TCK
 *  IO8 <--|                           |--> P0_TX-
 *  GND <--|                           |--> P0_TX+
 *  GND <--|                           |--> P0_RX-
 *  3V3 <--|                           |--> P0_RX+
 *  3V3 <--|                           |--> GND
 * IO17 <--|                           |--> P4_TX-
 * IO16 <--|                           |--> P4_TX+
 * IO15 <--|                           |--> P4_RX-
 * IO14 <--|                           |--> P4_RX+
 *  GND <--|                           |--> GND
 * IO13 <--|                           |--> GND
 *  IO1 <--|                           |--> 3V3
 *  IO0 <--|                           |--> 3V3
 *  GND <--|                           |--> IO21
 *  GND <--|                           |--> IO24
 *  GND <--|                           |--> IO22
 *  GND <--|                           |--> IO18
 * U_RX <--|                           |--> IO19
 * U_TX <--|                           |--> IO20
 *  GND <--|                           |--> IO23
 *  GND <--|                           |--> GND
 *         +---------------------------+
 */

#ifndef __CONFIG_H
#define __CONFIG_H

#include <config.h>

#define CONFIG_BOOTLOADER_MSG       "Make RST high to enter bootloader mode" 
#define CONFIG_BAUDRATE             19200
#define CFG_BAUDRATE_TABLE          {CONFIG_BAUDRATE}

/*
 * Miscellaneous configurable options
 */
#define CFG_ALT_MEMTEST                                     
#define CFG_HUSH_PARSER     
#define	CFG_LONGHELP								/* Print complete help information, undef this to save space */
#define	CFG_PROMPT		"dptmodule> "                                   /* Shell command prompt */
#define CFG_PROMPT_HUSH_PS2	"> "                                            /* Prompt shown when the shell needs more info on the next line, only in hush shell */
#define	CFG_CBSIZE		1024						/* Buffer size for input from the console */
#define	CFG_PBSIZE		(CFG_CBSIZE+sizeof(CFG_PROMPT)+16)              /* Buffer size for console output */
#define	CFG_MAXARGS		16                                              /* Maximum number of arguments accepted for monitor commands */
#define CFG_MALLOC_LEN		512*1024                                        /* Size of RAM reserved for malloc() use */
#define CFG_BOOTPARAMS_LEN	512*1024                                        /* Size reserved for the length of the boot parameters */
#define CFG_SDRAM_BASE		0x80000000                                      /* The physical start address of RAM */
#define CFG_MEMTEST_START	(CFG_SDRAM_BASE + 0x200000)                     /* RAM test start = CFG_SDRAM_BASE + 2 MB */
#define CFG_MEMTEST_END		(CFG_SDRAM_BASE + bd->bi_memsize - 0x200001)	/* RAM test end   = CFG_SDRAM_BASE + RAM size - 2 MB - 1 Byte */
#define CFG_RX_ETH_BUFFER       16                                              /* The number of ethernet receive buffers */

/*
 * The config option CONFIG_SILENT_CONSOLE can be used to quiet messages
 * on the console.  If the option has been enabled, the output can be
 * silenced by setting the environment variable "silent".
 */
#if defined(CONFIG_SILENT_CONSOLE)
	#define SILENT_ENV_VARIABLE	"silent=1\0"
#else
	#define SILENT_ENV_VARIABLE	""
#endif

/*
 * PLL Config for different CPU/DDR/AHB frequencies
 */
#define CFG_PLL_200_200_100		1
#define CFG_PLL_200_200_200		2
#define CFG_PLL_225_225_112		3
#define CFG_PLL_225_225_225		4
#define CFG_PLL_250_250_125		5
#define CFG_PLL_250_250_250		6
#define CFG_PLL_300_300_150		7
#define CFG_PLL_325_325_162		8
#define CFG_PLL_350_350_175		9
#define CFG_PLL_360_360_180		10
#define CFG_PLL_380_380_190		11
#define CFG_PLL_400_400_200		12
#define CFG_PLL_412_412_206		13
#define CFG_PLL_420_420_210		14
#define CFG_PLL_425_425_212		15
#define CFG_PLL_437_437_218		16
#define CFG_PLL_440_440_220		17
#define CFG_PLL_450_450_225		18
#define CFG_PLL_460_460_230		19
#define CFG_PLL_475_475_237		20
#define CFG_PLL_480_480_240		21
#define CFG_PLL_487_487_243		22
#define CFG_PLL_500_500_250		23
#define CFG_PLL_500_250_250		24
#define CFG_PLL_520_520_260		25
#define CFG_PLL_525_262_131		26
#define CFG_PLL_560_280_140		27
#define CFG_PLL_580_290_145		28
#define CFG_PLL_600_300_200		29

/*
 * Cache Configuration
 */
#define CFG_DCACHE_SIZE			32768
#define CFG_ICACHE_SIZE			65536
#define CFG_CACHELINE_SIZE              32

/*
 * FLASH and environment organization
 */
#define CFG_MAX_FLASH_BANKS		1                                       /* There is 1 flash bank */
#define CFG_MAX_FLASH_SECT		4096                                    /* Every sector in 16MiB flash is 4KiB in size */

/*
 * We boot from this flash
 */
#define CFG_FLASH_BASE			0x9F000000                              /* The physical start address of the flash memory */   
#ifdef COMPRESSED_UBOOT
#define BOOTSTRAP_TEXT_BASE		CFG_FLASH_BASE
#define BOOTSTRAP_CFG_MONITOR_BASE 	BOOTSTRAP_TEXT_BASE
#endif

/*
 * The following #defines are needed to get flash environment right
 */
#define	CFG_MONITOR_BASE	TEXT_BASE                                       /* Physical start address of the boot monitor code. */
#define	CFG_MONITOR_LEN		(192 *1024)                                     /* Size of memory reserved for monitor code */

/*
 * DPT-Module V1 boot arguments
 */
#define	CONFIG_BOOTARGS	"console=ttyS0,19200 root=31:02 rootfstype=squashfs init=/sbin/init mtdparts=ar7240-nor0:128k(u-boot),1024k(kernel),2816k(rootfs),64k(config),64k(ART)"

/*
 * DPT-Board U-Boot environment variables
 */
#define CONFIG_BOOTFILE         "firmware.bin"                                  /* Environment boot file */          
#define CONFIG_LOADADDR         0x80800000                                      /* RAM Loader address */
#define	CFG_LOAD_ADDR           0x9F020000                                      /* Flash firmware start address */
#define UPDATE_SCRIPT_FW_ADDR	"0x9F020000"                                    /* Flash firmware start address */
#define CONFIG_BOOTCOMMAND      "bootm 0x9F020000"                              /* Boot command */
#define CONFIG_IPADDR		192.168.1.1                                     /* U-Boot IPv4 address */
#define CONFIG_SERVERIP		192.168.1.2                                     /* Server IPv4 address */


#define	CFG_HZ			bd->bi_cfg_hz                                   /* Board speed configuration in Hz */
#define CFG_PLL_FREQ            CFG_PLL_400_400_200                             /* Default PLL frequency setting */
    
/*
 * CPU_PLL_DITHER_FRAC_VAL
 *
 * Value written into CPU PLL Dither FRAC Register (PLL_DITHER_FRAC)
 *
 * bits	0..9	NFRAC_MAX	=>	1000 (0x3E8)
 * bits	10..13	NFRAC_MIN	=>	0 (minimum value is used)
 * bits	20..29	NFRAC_STEP	=>	1
 *
 */
#define CPU_PLL_DITHER_FRAC_VAL         0x001003E8

/*
 * CPU_PLL_SETTLE_TIME_VAL
 *
 * Value written into CPU Phase Lock Loop Configuration Register 2 (CPU_PLL_CONFIG2)
 *
 * bits	0..11	SETTLE_TIME	=>	850 (0x352)
 *
 */
#define CPU_PLL_SETTLE_TIME_VAL		0x00000352

/*
 * CPU_CLK_CONTROL_VAL
 *
 * In CPU_CLK_CONTROL_VAL bit 2 is set (BYPASS = 1 -> bypass PLL)
 * After PLL configuration we nedd to clear this bit
 *
 * Values written into CPU Clock Control Register CLOCK_CONTROL
 *
 * bits	2	(1bit)	BYPASS (Bypass PLL. This defaults to 1 for test purposes. Software must enable the CPU PLL for normal operation and then set this bit to 0)
 * bits	5..6	(2bit)	CPU_POST_DIV	=>	0	(DEFAULT, Ratio = 1)
 * bits	10..11	(2bit)	DDR_POST_DIV 	=>	0	(DEFAULT, Ratio = 1)
 * bits	15..16	(2bit)	AHB_POST_DIV	=>	1	(DEFAULT, Ratio = 2)
 */
#define MAKE_AR9331_CPU_CLK_CONTROL_VAL(cpudiv, ddrdiv, ahbdiv)        (((0x3 & (cpudiv - 1)) << 5)  | ((0x3 & (ddrdiv - 1)) << 10) | ((0x3 & (ahbdiv - 1)) << 15))

/*
 * CPU_PLL_CONFIG_VAL
 *
 * In CPU_PLL_CONFIG_VAL bit 30 is set (CPU_PLLPWD = 1 -> power down control for CPU PLL)
 * After PLL configuration we need to clear this bit
 *
 * Values written into CPU Phase Lock Loop Configuration (CPU_PLL_CONFIG)
 *
 * bits 10..15	(6bit)	DIV_INT	(The integer part of the DIV to CPU PLL)                                                =>	32	(0x20)
 * bits 16..20	(5bit)	REFDIV	(Reference clock divider)                                                               =>	1	(0x1)	[doesn't start at values different than 1 (maybe need to change other dividers?)]
    * bits 21	(1bit)	RANGE	(Determine the VCO frequency range of the CPU PLL)                                      =>	0	(0x0)	[doesn't have impact on clock values]
 * bits 23..25	(3bit)	OUTDIV	(Define the ratio between VCO output and PLL output VCOOUT * (1/2^OUTDIV) = PLLOUT)	=>	1	(0x1)	[value == 0 is illegal!]	
 * 
 * PLL CALCULATION
 * PLL = ((25 MHz / REFDIV) * DIV_INT) / (2 ^ OUTDIV)	// XTAL=25 MHz
 *
 * CPU = PLL / CPU_POST_DIV
 * DDR = PLL / DDR_POST_DIV
 * AHB = PLL / AHB_POST_DIV						
 */
#define MAKE_AR9331_CPU_PLL_CONFIG_VAL(divint, refdiv, range, outdiv)  (((0x3F & divint) << 10) | ((0x1F & refdiv) << 16) | ((0x1 & range)   << 21) | ((0x7 & outdiv)  << 23))

/*
 * AR7240_SPI_CONTROL
 *
 * Value written into SPI Control (SPI_CONTROL) register
 *
 * bits	0..5	(6bit)	CLOCK_DIVIDER	(Specifies the clock divider setting. Actual clock frequency would be (AHB_CLK / ((CLOCK_DIVIDER+1)*2)) )
 * bits	6		(1bit)	REMAP_DISABLE	(Remaps 4 MB space over unless explicitly disabled by setting this bit to 1. If set to 1, 16 MB is accessible.)
 *
 */
#define MAKE_AR9331_SPI_CONTROL_VAL(spidiv)                            (((spidiv >> 1) - 1) | 0x40)

/*
 * Default values frequency settings (400/400/200 MHz)
 */
#define CPU_CLK_CONTROL_VAL_DEFAULT	MAKE_AR9331_CPU_CLK_CONTROL_VAL(1, 1, 2)        /* CPU_DIV = 1, RAM_DIV = 1, AHB_DIV = 2 */
#define CPU_PLL_CONFIG_VAL_DEFAULT	MAKE_AR9331_CPU_PLL_CONFIG_VAL(32, 1, 0, 1)     /* DIV_INT = 32 (25 MHz * 32/2 = 400 MHz), REFDIV = 1, RANGE = 0, OUTDIV = 1 */
#define AR7240_SPI_CONTROL_DEFAULT	MAKE_AR9331_SPI_CONTROL_VAL(6)                  /* CLOCK_DIVIDER = 2 (SPI clock = 200 / 6 ~ 33 MHz) */

/**
 * Configure default settings 
 */
#define CPU_CLK_CONTROL_VAL	CPU_CLK_CONTROL_VAL_DEFAULT
#define CPU_PLL_CONFIG_VAL	CPU_PLL_CONFIG_VAL_DEFAULT
#define AR7240_SPI_CONTROL	AR7240_SPI_CONTROL_DEFAULT

#define CFG_HZ_FALLBACK	(400000000LU/2)

/*
 * Cache lock for stack
 */
#define CFG_INIT_SP_OFFSET		0x1000

/*
 * Address and size of Primary Environment Sector
 */
#define CFG_ENV_IS_NOWHERE	1                                               /* No U-Boot writable environment */
#define CFG_ENV_ADDR		0x9F040000                                      /* U-Boot environment address */ 
#define CFG_ENV_SIZE		65536                                           /* U-Boot environment is 64KiB large */

/*
 * Available commands
 */
#define CONFIG_COMMANDS (CFG_CMD_MEMORY | \
                                                 CFG_CMD_DHCP   | \
                                                 CFG_CMD_PING   | \
                                                 CFG_CMD_FLASH  | \
                                                 CFG_CMD_NET    | \
                                                 CFG_CMD_RUN    | \
                                                 CFG_CMD_DATE   | \
                                                 CFG_CMD_ECHO   | \
                                                 CFG_CMD_BOOTD  | \
                                                 CFG_CMD_ITEST)

/*
 *  Enable NetConsole and custom NetConsole port
 */
#define CONFIG_NETCONSOLE
#define CONFIG_NETCONSOLE_PORT	5000

/* DDR init values */
#define CFG_DDR_REFRESH_VAL                 0x4186
#define CFG_DDR_CONFIG_VAL                  0x7fbc8cd0
#define CFG_DDR_MODE_VAL_INIT               0x133
#define CFG_DDR_EXT_MODE_VAL                0x0
#define CFG_DDR_MODE_VAL                    0x33
#define CFG_DDR_TRTW_VAL                    0x1f
#define CFG_DDR_TWTR_VAL                    0x1e

#define CFG_DDR_CONFIG2_VAL                 0x9dd0e6a8
#define CFG_DDR_RD_DATA_THIS_CYCLE_VAL      0x00ff
#define CFG_DDR_TAP0_VAL                    0x8
#define CFG_DDR_TAP1_VAL                    0x9

/* DDR2 Init values */
#define CFG_DDR2_EXT_MODE_VAL               0x402

/* Define multiple ethernet interfaces */
#define CONFIG_NET_MULTI

/*
 * Web failsafe configuration
 */
#define WEBFAILSAFE_UPLOAD_RAM_ADDRESS              CONFIG_LOADADDR                                 /* RAM upload address */
#define WEBFAILSAFE_UPLOAD_UBOOT_ADDRESS            CFG_FLASH_BASE                                  /* U-Boot partition size and offset */
#define WEBFAILSAFE_UPLOAD_UBOOT_SIZE_IN_BYTES      (64 * 1024)                                     /* U-Boot upload size (64KiB) */
#define UPDATE_SCRIPT_UBOOT_SIZE_IN_BYTES           "0x10000"                                       /* U-Boot upload size in hex string (64KiB) */
#define WEBFAILSAFE_UPLOAD_KERNEL_ADDRESS           WEBFAILSAFE_UPLOAD_UBOOT_ADDRESS + 0x20000      /* Upload address for the firmware image */
#define WEBFAILSAFE_UPLOAD_ART_SIZE_IN_BYTES        (64 * 1024)                                     /* ART partition size (64KiB) */
#define WEBFAILSAFE_UPLOAD_LIMITED_AREA_IN_BYTES    (192 * 1024)                                    /* Max firmware size DPT-Board v1: 128k(U-Boot + MAC),64k(ART) */

/*
 * Web failsafe progress info
 */
#define WEBFAILSAFE_PROGRESS_START			0
#define WEBFAILSAFE_PROGRESS_TIMEOUT			1
#define WEBFAILSAFE_PROGRESS_UPLOAD_READY		2
#define WEBFAILSAFE_PROGRESS_UPGRADE_READY		3
#define WEBFAILSAFE_PROGRESS_UPGRADE_FAILED		4

/*
 * Web failsafe upload type
 */
#define WEBFAILSAFE_UPGRADE_TYPE_FIRMWARE		0
#define WEBFAILSAFE_UPGRADE_TYPE_UBOOT			1
#define WEBFAILSAFE_UPGRADE_TYPE_ART			2

/*
 * Additional environment variables for simple upgrades
 */
#define CONFIG_EXTRA_ENV_SETTINGS   "uboot_addr=0x9F000000\0" \
                                    "uboot_name=uboot.bin\0" \
                                    "uboot_size=" UPDATE_SCRIPT_UBOOT_SIZE_IN_BYTES "\0" \
                                    "uboot_upg=" \
                                    "if ping $serverip; then " \
                                    "tftp $loadaddr $uboot_name && " \
                                    "if itest.l $filesize == $uboot_size; then " \
                                    "erase $uboot_addr +$filesize && " \
                                    "cp.b $loadaddr $uboot_addr $filesize && " \
                                    "echo OK!; " \
                                    "else " \
                                    "echo ERROR! Wrong file size!; " \
                                    "fi; " \
                                    "else " \
                                    "ERROR! Server not reachable!; " \
                                    "fi\0" \
                                    "firmware_addr=" UPDATE_SCRIPT_FW_ADDR "\0" \
                                    "firmware_name=firmware.bin\0" \
                                    "firmware_upg=" \
                                    "if ping $serverip; then " \
                                    "tftp $loadaddr $firmware_name && " \
                                    "erase $firmware_addr +$filesize && " \
                                    "cp.b $loadaddr $firmware_addr $filesize && " \
                                    "echo OK!; " \
                                    "else " \
                                    "ERROR! Server not reachable!; " \
                                    "fi\0" \
                                    SILENT_ENV_VARIABLE

#define CFG_ATHRS26_PHY     1
#define CFG_AG7240_NMACS    2
#define CFG_MII0_RMII       1
#define CFG_BOOTM_LEN       (16 << 20)

#undef DEBUG
#define milisecdelay(_x)    udelay((_x) * 1000)

/*
 * Flash data block definitions
 */
#define OFFSET_MAC_DATA_BLOCK				0x010000
#define OFFSET_MAC_DATA_BLOCK_LENGTH			0x010000
#define OFFSET_MAC_ADDRESS				0x00FC00
#define OFFSET_ROUTER_MODEL				0x00FD00

/*
 * PLL and clocks configurations from FLASH
 *
 * We need space for 4x 32-bit variables:
 * - PLL_MAGIC_VARIABLE
 * - values of registers:
 *   - CPU_PLL_CONFIG (page 70 in datasheet)
 *   - CLOCK_CONTROL  (page 71)
 *   - SPI_CONTROL    (page 261)
 */
#define PLL_IN_FLASH_MAGIC				0x504C4C73
#define PLL_IN_FLASH_DATA_BLOCK_OFFSET	0x00010000
#define PLL_IN_FLASH_DATA_BLOCK_LENGTH	0x00010000
#define PLL_IN_FLASH_MAGIC_OFFSET		0x0000FFF0	// last 16 bytes

#include <cmd_confdefs.h>

#endif	/* __CONFIG_H */
