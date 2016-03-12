export BUILD_TOPDIR=$(PWD)
export STAGING_DIR=$(BUILD_TOPDIR)/tmp

# export MAKECMD=make --silent --no-print-directory ARCH=mips CROSS_COMPILE=mips-linux-gnu-
# Use OpenWRT Linaro toolchain to build u-boot
export MAKECMD=make --silent ARCH=mips CROSS_COMPILE=mips-openwrt-linux-uclibc-
export PATH:=$(BUILD_TOPDIR)/toolchain/bin/:$(PATH)

# boot delay (time to autostart boot command)
export CONFIG_BOOTDELAY=1

# uncomment following line, to disable output in U-Boot console
#export DISABLE_CONSOLE_OUTPUT=1

# uncomment following line, to build RAM version images (without low level initialization)
#export CONFIG_SKIP_LOWLEVEL_INIT=1

dpt-module-v1:	export UBOOT_FILE_NAME=uboot_for_dpt_module_v1
dpt-module-v1:	export MAX_UBOOT_SIZE=64
ifndef CONFIG_SKIP_LOWLEVEL_INIT
dpt-module-v1:	export COMPRESSED_UBOOT=1
endif
dpt-module-v1:
	@cd $(BUILD_TOPDIR)/u-boot/ && $(MAKECMD) dpt_module_v1_config
	@cd $(BUILD_TOPDIR)/u-boot/ && $(MAKECMD) ENDIANNESS=-EB V=1 all
	@make --no-print-directory show_size

ifdef CONFIG_SKIP_LOWLEVEL_INIT
  ifdef DISABLE_CONSOLE_OUTPUT
show_size:	export UBOOT_FILE_NAME_SUFFIX=__SILENT-CONSOLE__RAM
  else
show_size:	export UBOOT_FILE_NAME_SUFFIX=__RAM
  endif
else
  ifdef DISABLE_CONSOLE_OUTPUT
show_size:	export UBOOT_FILE_NAME_SUFFIX=__SILENT-CONSOLE
  endif
endif
show_size:
ifdef COMPRESSED_UBOOT
	@cp $(BUILD_TOPDIR)/u-boot/tuboot.bin $(BUILD_TOPDIR)/bin/temp.bin
else
	@cp $(BUILD_TOPDIR)/u-boot/u-boot.bin $(BUILD_TOPDIR)/bin/temp.bin
endif
	@/bin/echo -ne "\e[32m"
ifndef CONFIG_SKIP_LOWLEVEL_INIT
	@echo "> Preparing $(MAX_UBOOT_SIZE)KB file filled with 0xFF..."
	@`tr "\000" "\377" < /dev/zero | dd ibs=1k count=$(MAX_UBOOT_SIZE) of=$(BUILD_TOPDIR)/bin/$(UBOOT_FILE_NAME)$(UBOOT_FILE_NAME_SUFFIX).bin 2> /dev/null`
	@echo "> Copying U-Boot image..."
	@`dd if=$(BUILD_TOPDIR)/bin/temp.bin of=$(BUILD_TOPDIR)/bin/$(UBOOT_FILE_NAME)$(UBOOT_FILE_NAME_SUFFIX).bin conv=notrunc 2> /dev/null`
	@`rm $(BUILD_TOPDIR)/bin/temp.bin`
else
	@echo "> Copying U-Boot image..."
	@`mv $(BUILD_TOPDIR)/bin/temp.bin $(BUILD_TOPDIR)/bin/$(UBOOT_FILE_NAME)$(UBOOT_FILE_NAME_SUFFIX).bin`
endif
	@echo "> U-Boot image ready, size:" `wc -c < $(BUILD_TOPDIR)/bin/$(UBOOT_FILE_NAME)$(UBOOT_FILE_NAME_SUFFIX).bin`" bytes"
	@`md5sum $(BUILD_TOPDIR)/bin/$(UBOOT_FILE_NAME)$(UBOOT_FILE_NAME_SUFFIX).bin | awk '{print $$1}' | tr -d '\n' > $(BUILD_TOPDIR)/bin/$(UBOOT_FILE_NAME)$(UBOOT_FILE_NAME_SUFFIX).md5`
	@`echo ' *'$(UBOOT_FILE_NAME)$(UBOOT_FILE_NAME_SUFFIX).bin >> $(BUILD_TOPDIR)/bin/$(UBOOT_FILE_NAME)$(UBOOT_FILE_NAME_SUFFIX).md5`
# Do not check image size for RAM version
ifndef CONFIG_SKIP_LOWLEVEL_INIT
	@if [ "`wc -c < $(BUILD_TOPDIR)/bin/$(UBOOT_FILE_NAME)$(UBOOT_FILE_NAME_SUFFIX).bin`" -gt "`/bin/echo '$(MAX_UBOOT_SIZE)*1024' | bc`" ]; then \
			/bin/echo -e "\e[31m\n**************************************************"; \
			/bin/echo "*     WARNING: U-BOOT IMAGE SIZE IS TOO BIG!     *"; \
			/bin/echo -e "**************************************************"; \
	fi;
endif
	@/bin/echo -ne "\e[0m"

clean:
	@cd $(BUILD_TOPDIR)/u-boot/ && $(MAKECMD) --no-print-directory distclean
	@rm -f $(BUILD_TOPDIR)/u-boot/httpd/fsdata.c

clean_all:	clean
	@/bin/echo -e "\e[32m> Removing all binary images...\e[0m"
	@rm -f $(BUILD_TOPDIR)/bin/*.bin
	@rm -f $(BUILD_TOPDIR)/bin/*.md5
