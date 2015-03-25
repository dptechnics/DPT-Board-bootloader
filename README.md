DPT-Board U-boot bootloader
==========

Table of contents
-----------------

- [Introduction](#introduction)
- [Supported devices](#supported-devices)
- [Modifications, changes](#modifications-changes)
	- [Web server](#web-server)
	- [Network Console](#network-console)
	- [Other](#other)
	- [Supported FLASH chips](#supported-flash-chips)
- [How to install it?](#how-to-install-it)
	- [Cautions, backups](#cautions-backups)
	- [Using external programmer](#using-external-programmer)
	- [Using UART, U-Boot console and TFTP server](#using-uart-u-boot-console-and-tftp-server)
		- [Important notice!](#important-notice)
		- [Step by step instruction](#step-by-step-instruction)
	- [Using OpenWrt](#using-openwrt)
	- [Using DD-WRT](#using-dd-wrt)
- [How to use it?](#how-to-use-it)
- [How to compile the code?](#how-to-compile-the-code)
- [FAQ](#faq)
- [License, outdated sources etc.](#license-outdated-sources-etc)
- [Credits](#credits)

Introduction
------------

This bootloader is based on the U-Boot modification of pepe2k. You can find this project on https://github.com/pepe2k/u-boot_mod

How to install it?
------------------

### Cautions, backups

**You do so at your own risk!**   
**If you make any mistake or something goes wrong during upgrade, in worst case, your router will not boot again!**

It is a good practice to backup your original U-Boot image/partition before you make any changes. For example, using DPT-Board-OS:

```
cat /proc/mtd
```

This command will show you all **MTD** (Memory Technology Device) partitions:

```
dev:    size   erasesize  name
mtd0: 00020000 00010000 "u-boot"
mtd1: 000eeb70 00010000 "kernel"
mtd2: 00ee1490 00010000 "rootfs"
mtd3: 00c60000 00010000 "rootfs_data"
mtd4: 00010000 00010000 "art"
mtd5: 00fd0000 00010000 "firmware"
```

As you can see, `u-boot` partition size is **0x20000** (128 KiB) and my image for this model has size of **0x10000** (64 KiB) - it is a very important difference! You should remember about this if you want to use `mtd` utility, to change U-Boot.

To backup `u-boot` partition in RAM, run:

```
cat /dev/mtd0 > /tmp/uboot_backup.bin
```

And then connect to your DPT-Board using `SCP protocol` and download from `/tmp` the `uboot_backup.bin` file.

### Using UART, U-Boot console and TFTP server

It is probably the most common method to change firmware in case of any problems. Main disadvantage of this approach is the need to connect with device using a serial port (this does not apply to Carambola 2 with development board, which already has a built-in USB-UART adapter, based on FTDI FT232RQ).

#### Important notice!

All these devices have an UART interface integrated inside the SoC, which operates at TTL 3.3 V (in fact, GPIO pins can work at this voltage, but their real range is < 3 V)!

Please, **do not** connect any RS232 +/- 12 V cable or any adapter without logic level converter, because it may damage your device. It would be the best if you use any USB to UART adapter with integrated 3.3 V logic level converter. And please, remember that **you should connect only RX, TX and GND signals**. **DO NOT** connect together 3.3 V signals from router and from adapter if you do not know what are you doing, because you may burn out your adapter and/or router! Connect the adapter using USB port in your PC and router with original power supply.

For a long time I have been using without any problems a small and very cheap (about 1-2 USD) **CP2102** based adapter. Go to [Serial Console article in OpenWrt Wiki](http://wiki.openwrt.org/doc/hardware/port.serial) for more, detailed information.

#### Step by step instruction

1. Install and configure any **TFTP server** on your PC (on Windows, you can use [TFTP32](http://tftpd32.jounin.net)).

2. Set a fixed IP address on your PC (**192.168.1.2**) and connect it to the DPT-Board, using RJ45 network cable to the LAN port. 
3. Connect USB to UART adapter to the DPT-Board and start any application to communicate with it, like [PuTTY](http://www.chiark.greenend.org.uk/~sgtatham/putty/download.html).   
Configure adapter to use the following settings:
  * Baud rate: 19200 if using this bootloader, 115200 for older version
  * Data bits: 8
  * Parity control: none
  * Stop bits: 1
  * Handshaking: none
4. Power on the DPT-Board, wait for a line like one of the following and interrupt the process of loading a kernel:

  `Autobooting in 1 seconds`   
  `Hit any key to stop autoboot:  1` (for **D-Link DIR-505**, use any key)

5. Download and store in RAM proper image for your DPT-Board, using `tftpboot` command in U-Boot console:

  ```
  tftpboot 0x80800000 uboot_for_dpt_board_v1.bin

  eth1 link down
  Using eth0 device
  TFTP from server 192.168.1.2; our IP address is 192.168.1.1
  Filename 'uboot_for_dpt_board_v1.bin'.
  Load address: 0x80800000
  Loading: #############
  done
  Bytes transferred = 65536 (10000 hex)
  uboot>
  ```

8. Next step is very risky! You are going to delete existing U-Boot image from FLASH in your device and copy the new one from RAM. If something goes wrong (for example, a power failure), your router, without bootloader, will not boot again!

  You should also note the size of downloaded image. It must always be **0x10000** (64 KiB). The start address of FLASH is **0x9F000000**, so this is where the bootloader must be written to.

  Please, do not make any mistake with offsets and sizes during next steps!

9. Erase appropriate FLASH space for new U-Boot image (this command will remove default U-Boot image!):

  ```
  uboot> erase 0x9F000000 +0x10000   

  First 0x0 last 0x0 sector size 0x10000
  0
  Erased 1 sectors
  ```

10. Now your DPT-Board does not have U-Boot, so do not wait and copy to FLASH the new one, stored earlier in RAM:

  ```
  uboot> cp.b 0x80800000 0x9F000000 0x10000   

  Copy to Flash... write addr: 9f000000
  done
  ```

11. If you want, you can check content of the newly written FLASH and compare it to the image on your PC using `md` command in U-Boot console, which prints indicated memory area (press only ENTER after first execution of this command to move further in memory):

  ```
  uboot> md 0x9F000000

  9f000000: 100000ff 00000000 100000fd 00000000    ................
  9f000010: 10000222 00000000 10000220 00000000    ..."....... ....
  9f000020: 1000021e 00000000 1000021c 00000000    ................
  9f000030: 1000021a 00000000 10000218 00000000    ................
  9f000040: 10000216 00000000 10000214 00000000    ................
  9f000050: 10000212 00000000 10000210 00000000    ................
  9f000060: 1000020e 00000000 1000020c 00000000    ................
  9f000070: 1000020a 00000000 10000208 00000000    ................
  9f000080: 10000206 00000000 10000204 00000000    ................
  9f000090: 10000202 00000000 10000200 00000000    ................
  9f0000a0: 100001fe 00000000 100001fc 00000000    ................
  9f0000b0: 100001fa 00000000 100001f8 00000000    ................
  9f0000c0: 100001f6 00000000 100001f4 00000000    ................
  9f0000d0: 100001f2 00000000 100001f0 00000000    ................
  9f0000e0: 100001ee 00000000 100001ec 00000000    ................
  9f0000f0: 100001ea 00000000 100001e8 00000000    ................
  ```

12. If you are sure that everything went OK, you may reset the DPT-Board:

  ```
  uboot> reset
  ```

### Using OpenWrt

1. Compile and flash OpenWrt with an unlocked U-Boot partition.
  - This is done by removing the `MTD_WRITEABLE` from the `mask_flags` of the `u-boot` partition.
2. Find out which mtd partition is the `u-boot` partition:

  ```
  root@dptboard:/tmp/uboot-work# cat /proc/mtd
  dev:    size   erasesize  name
  mtd0: 00020000 00010000 "u-boot"
  mtd1: 000feba0 00010000 "kernel"
  mtd2: 002d1460 00010000 "rootfs"
  mtd3: 00100000 00010000 "rootfs_data"
  mtd4: 00010000 00010000 "art"
  mtd5: 003d0000 00010000 "firmware"
  ```

3. Transfer the new U-Boot image to the DPT-Board:

  ```
  me@laptop:~# scp uboot_for_dpt_board_v1.bin root@192.168.1.1:/tmp/
  uboot_for_dpt_board_v1.bin            100%   64KB  64.0KB/s   00:00
  ```

4. Verify the MD5 sum of the image:

  ```
  me@laptop:~# md5sum uboot_for_dpt_board_v1.bin
  cefad12aa9fbd04291652dae3eb7650c  uboot_for_dpt_board_v1.bin

  root@dptboard:/tmp# md5sum uboot_for_dpt_board_v1.bin
  cefad12aa9fbd04291652dae3eb7650c  uboot_for_dpt_board_v1.bin
  ```

5. Take a backup of the current u-boot partition (`mtd0`):

  ```
  root@dptboard:/tmp# dd if=/dev/mtd0 of=uboot_orig.bin
  256+0 records in
  256+0 records out
  ```

6. Transfer the backup off the device and to a safe place:

  ```
  me@laptop:~# scp root@192.168.1.1:/tmp/uboot_orig.bin .
  uboot_orig.bin                                100%  128KB 128.0KB/s   00:00
  ```

7. **Danger**: This is the point of no return, if you have any errors or problems, please revert the original image at any time using:

  ```
  root@dptboard:/tmp# mtd write uboot_orig.bin "u-boot"
  Unlocking u-boot ...

  Writing from uboot_orig.bin to u-boot ...
  ```

8. Now, to actually flash the new image, run:

  ```
  root@dptboard:/tmp# mtd write uboot_new.bin "u-boot"
  Unlocking u-boot ...

  Writing from uboot_new.bin to u-boot ...
  ```

11. To verify that the image was flashed correctly, you should verify it:

  ```
  root@dptboard:/tmp# mtd verify uboot_new.bin "u-boot"
  Verifying u-boot against uboot_new.bin ...
  a80c3a8683345a3fb311555c5d4194c5 - u-boot
  a80c3a8683345a3fb311555c5d4194c5 - uboot_new.bin
  Success
  ```

12. To restart with the new bootloader, reboot the router:

  ```
  root@dptboard:/tmp# reboot
  ```

How to compile the code?
------------------------

You can use one of the free toolchains:

- [Sourcery CodeBench Lite Edition for MIPS GNU/Linux](https://sourcery.mentor.com/GNUToolchain/subscription3130?lite=MIPS),
- [OpenWrt Toolchain for AR71xx MIPS](http://downloads.openwrt.org/attitude_adjustment/12.09/ar71xx/generic/OpenWrt-Toolchain-ar71xx-for-mips_r2-gcc-4.6-linaro_uClibc-0.9.33.2.tar.bz2),
- [ELDK (Embedded Linux Development Kit)](ftp://ftp.denx.de/pub/eldk/),
- or any others...

I am using **Sourcery CodeBench Lite Edition for MIPS GNU/Linux** on **Ubuntu 12.04 LTS** (32-bit, virtual machine) and all released binary images were/will be built using this set.

All you need to do, after choosing a toolchain, is to modify [Makefile](Makefile) - change or remove `export MAKECMD` and if needed add `export PATH`. For example, to use OpenWrt Toolchain instead of Sourcery CodeBench Lite, download it and extract into `toolchain` folder, inside the top dir and change first lines in [Makefile](Makefile):

```
export BUILD_TOPDIR=$(PWD)
export STAGING_DIR=$(BUILD_TOPDIR)/tmp

export MAKECMD=make --silent ARCH=mips CROSS_COMPILE=mips-openwrt-linux-uclibc-
export PATH:=$(BUILD_TOPDIR)/toolchain/bin/:$(PATH)
```

To build image, run `make model` inside top dir, for example, command:

```
make dpt-board-v1
```

will start building U-Boot image for **DPT-Board v1**.

License, outdated sources etc.
------------------------------

**[U-Boot](http://www.denx.de/wiki/U-Boot/WebHome "U-Boot")** project is Free Software, licensed under version 2 of the **GNU General Public License**. All information about license, contributors etc., are included with sources, inside *u-boot* folder.

You should know, that most routers, especially those based on Atheros SoCs, uses very old versions of U-Boot (1.1.4 is from 2005/2006). So, *these sources are definitely outdated* (do not even try to merge them with official release), but it was easier for me to modify them, than move TP-Link/Atheros changes to the current version. Moreover, lot of unnecessary code fragments and source files were removed for ease of understanding the code.

Credits
-------

- Thanks to *pepe2k* from OpenWrt to make this awesome U-Boot modification
