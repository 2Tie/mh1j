# environment flag
LEAVE_UNENCRYPTED = 0

# dirs

BIN_DIR := bin
BUILD_DIR := build
SRC_DIR := src
ASM_DIR := asm
INCLUDE_DIR := include
ASSETS_DIR := assets
CONFIG_DIR := config
TOOLS_DIR := tools
AFS_DIR := $(ASSETS_DIR)/AFS
EEGCC_PATHS := PATH=$(BIN_DIR)/ee/bin:$(BIN_DIR)/lib/gcc-lib/ee/2.96-ee-001003-1


# tools

WIBO := $(BIN_DIR)/wibo
MWCCPS2 := $(BIN_DIR)/mwccps2.exe
ifdef WSL_DISTRO_NAME
MWLDPS2 := MWCIncludes=$(BIN_DIR) $(BIN_DIR)/mwldps2.exe
else
MWLDPS2 := MWCIncludes=$(BIN_DIR) $(WIBO) $(BIN_DIR)/mwldps2.exe
endif

EEGCC := $(BIN_DIR)/ee/bin/gcc
CCPS2 := MWCIncludes=$(BIN_DIR) $(WIBO) $(MWCCPS2)

ASPS2 := $(BIN_DIR)/mips-ps2-decompals-as
MWCCGAP := $(TOOLS_DIR)/mwccgap/mwccgap.py

CC := $(CCPS2)
AS := mipsel-linux-gnu-as
AS := $(ASPS2)
LD := $(MWLDPS2)

PYTHON := python3
GENERATE_LCF := $(PYTHON) $(TOOLS_DIR)/lcf/generate_lcf.py
VERIFY := $(PYTHON) $(TOOLS_DIR)/verify.py

# flags

INCLUDES := -I$(INCLUDE_DIR) -I$(INCLUDE_DIR)/gcc -I$(INCLUDE_DIR)/cri -I$(INCLUDE_DIR)/cri/ee
MWCCPS2_FLAGS := -gccinc $(INCLUDES) -sdatathreshold 128 -O3,p -c -lang c -multibyte
EEGCC_FLAGS := $(INCLUDES) -O2 -G0 -c

AS_FLAGS += -EL -I $(INCLUDE_DIR) -G 128 -march=r5900 -mabi=eabi -no-pad-sections
LD_FLAGS := -main ENTRYPOINT0x100008 -map -noinhibit-exec $(OVERLAY_FLAGS)

OVERLAY_FLAGS := -overlaygroup game,0x533980 -overlay game -overlay lobby -overlay select -overlay yn -overlaygroup net,0xa06200 -overlay dnas_net -overlay dnas_ins

MWGAP_FLAGS := --mwcc-path $(MWCCPS2) --macro-inc-path $(INCLUDE_DIR)/macro.inc
MWGAP_FLAGS += --as-march r5900 --as-mabi eabi --target-encoding shift_jis --as-path $(AS) $(MWCCPS2_FLAGS)

# files

ELF := SLPM_654.95
MAIN_TARGET := $(BUILD_DIR)/$(ELF)

S_FILES := $(shell find $(ASM_DIR) -name '*.s' -not -path *nonmatchings* -not -path */elf* 2>/dev/null)
GAME_C_FILES := $(shell find $(SRC_DIR)/main -name '*.c' 2>/dev/null)
CRI_C_FILES := $(shell find $(SRC_DIR)/cri -name '*.c' 2>/dev/null)

ENC_FILES := $(TOOLS_DIR)/garbopad.bin $(TOOLS_DIR)/keys.bin $(TOOLS_DIR)/keytables.bin

NONMATCHINGS := $(shell find $(ASM_DIR) -name '@*.s' -path *nonmatchings* -not -path */elf* 2>/dev/null)

ASM_T_FILES := $(patsubst %.s,%.s.t,$(S_FILES))
ASM_T_FILES := $(addprefix $(BUILD_DIR)/,$(ASM_T_FILES))
ASM_O_FILES := $(patsubst %.s.t,%.s.o,$(ASM_T_FILES))
GAME_O_FILES := $(patsubst %.c,%.c.o,$(GAME_C_FILES))
GAME_O_FILES := $(addprefix $(BUILD_DIR)/,$(GAME_O_FILES))
CRI_O_FILES := $(patsubst %.c,%.c.o,$(CRI_C_FILES))
CRI_O_FILES := $(addprefix $(BUILD_DIR)/,$(CRI_O_FILES))
NONMATCHINGS_OLD := $(patsubst %.s,%.s.utf,$(NONMATCHINGS))

ALL_O_FILES := $(ASM_O_FILES) $(GAME_O_FILES) $(CRI_O_FILES)

LINKER_SCRIPT := $(BUILD_DIR)/SLPM_654.95.lcf

OVERLAY_BINS := game.bin lobby.bin select.bin yn.bin dnas_net.bin dnas_ins.bin
AFS_OVERLAYS := $(addprefix $(AFS_DIR)/bins/,$(OVERLAY_BINS))
OVERLAY_BINS := $(addprefix overlays/,$(OVERLAY_BINS))
OVERLAY_HEADERS := $(shell find $(ASM_DIR)/overlay -name '*_header.s')

COMPILER_TAR := mwcps2-3.0b52-030722.tar.gz
EE_COMPILER_TAR := ee-gcc2.96.tar.xz
BINUTILS_TAR := binutils-mips-ps2-decompals-linux-x86-64.tar.gz
MWCCGAP_URL := https://github.com/2Tie/mwccgap.git
M2CTX_URL := https://raw.githubusercontent.com/ethteck/m2ctx/refs/heads/main/m2ctx.py

# misc
DNAS_INS_VERIFY := $(BUILD_DIR)/dnas_ins.bin overlays/dnas_ins.bin 0x00 0x31B00
DNAS_NET_VERIFY := $(BUILD_DIR)/dnas_net.bin overlays/dnas_net.bin 0x00 0xA1000
ENCRYPT_FLAG := -e
ifeq ($(LEAVE_UNENCRYPTED), 1)
DNAS_INS_VERIFY := $(BUILD_DIR)/dnas_ins.bin overlays/dnas_ins_noencrypt.bin 0x00 0x31B00 config/dnas_ins_ignores.txt
DNAS_NET_VERIFY := $(BUILD_DIR)/dnas_net.bin overlays/dnas_net_noencrypt.bin 0x00 0xA1000 config/dnas_net_ignores.txt
ENCRYPT_FLAG := -n
endif

# rules

.PHONY: tools
# .PRECIOUS: $(ASM_T_FILES)

build: $(MAIN_TARGET)

split: $(ENC_FILES) $(OVERLAY_BINS)
	$(GENERATE_LCF) $(LINKER_SCRIPT)
	@find $(ASM_DIR)/overlay -name '*_header.s' -delete
	@rm -r asm/main/data/elf/ # need to find a way to stop making these .s files!!!
	$(PYTHON) tools/funcrypt.py -i
	@echo -e "\a"

clean:
	@#git clean -fdx $(ASSETS_DIR)
	@#git clean -fdx $(ASM_DIR)
	@#git clean -fdx $(BUILD_DIR)
	@#git clean -fdx .splache
	rm -r $(ASM_DIR)/*
	rm -r $(BUILD_DIR)/*
	rm -r $(ASSETS_DIR)/*

tools: $(MWCCPS2) $(WIBO) $(EEGCC) $(AS) $(MWCCGAP) $(M2CTX)

setup: $(OVERLAY_BINS) tools

$(MAIN_TARGET): $(ALL_O_FILES) $(LINKER_SCRIPT)
	@$(LD) $(LD_FLAGS) -o $@ \
		$(LINKER_SCRIPT) \
		$(shell find $(BUILD_DIR) -name '*.o')
	$(PYTHON) tools/funcrypt.py $(ENCRYPT_FLAG)
	$(VERIFY) $(MAIN_TARGET) $(ELF) 0x180 0x28a080
	$(VERIFY) $(BUILD_DIR)/select.bin overlays/select.bin 0x00 0x8000
	$(VERIFY) $(BUILD_DIR)/game.bin overlays/game.bin 0x00 0x15B780
	$(VERIFY) $(BUILD_DIR)/lobby.bin overlays/lobby.bin 0x00 0x134E00
	$(VERIFY) $(BUILD_DIR)/yn.bin overlays/yn.bin 0x00 0xDD00
	$(VERIFY) $(DNAS_INS_VERIFY)
	$(VERIFY) $(DNAS_NET_VERIFY)
	@echo -e "\a"

$(BUILD_DIR)/%.s.o: $(BUILD_DIR)/%.s.t
	$(AS) $(AS_FLAGS) -o $@ $<

$(BUILD_DIR)/%.s.t: %.s
	@mkdir -p $(dir $@)
	iconv --verbose -f UTF-8 -t SJIS $< -o $@

$(BUILD_DIR)/%.c.o: %.c #$(NONMATCHINGS_OLD)
	@mkdir -p $(dir $@)
	$(PYTHON) tools/mwccgap/mwccgap.py $< $@ $(MWGAP_FLAGS)

$(CRI_O_FILES): $(BUILD_DIR)/%.c.o: %.c
	@mkdir -p $(dir $@)
	$(EEGCC_PATHS) $(EEGCC) $< -o $@ $(EEGCC_FLAGS)

$(ENC_FILES):
	$(PYTHON) tools/funcrypt.py -d

overlays/%.bin: $(AFS_DIR)/bins/%.bin
	cp $< $@

$(AFS_OVERLAYS):
	$(PYTHON) tools/packer.py -u AFS_DATA.AFS assets/AFS/ tools/AFS_files.txt

#%.s.utf: %.s
#	cp '$<' '$@'
#	iconv --verbose -f UTF-8 -t SJIS '$<' -o '$<'
#	iconv --verbose -f UTF-8 -t SJIS $< -o $@
#	mv $< $(patsubst %.s, %.s.utf8, $<)
#	mv $@ $<

#$(NONMATCHINGS_OLD): $(NONMATCHINGS)
#	cp $< $@
#	iconv --verbose -f UTF-8 -t SJIS $< -o $<

$(WIBO):
	@mkdir -p $(BIN_DIR)
	wget -O $@ https://github.com/decompals/wibo/releases/download/0.6.13/wibo
	chmod +x $(WIBO)

$(MWCCPS2):
	@mkdir -p $(BIN_DIR)
	wget -O- https://github.com/decompme/compilers/releases/download/compilers/$(COMPILER_TAR) | tar xzv -C $(BIN_DIR)

$(EEGCC):
	@mkdir -p $(BIN_DIR)
	wget -O- https://github.com/decompme/compilers/releases/download/compilers/$(EE_COMPILER_TAR) | tar xJv -C $(BIN_DIR)

$(AS):
	@mkdir -p $(BIN_DIR)
	$(info running binutils recipe)
	wget -O- https://github.com/decompals/binutils-mips-ps2-decompals/releases/latest/download/$(BINUTILS_TAR) | tar xzv -C $(BIN_DIR)

$(MWCCGAP):
	@mkdir -p $(dir $@)
	git clone $(MWCCGAP_URL) $(dir $@)

$(M2CTX):
	@mkdir -b 
	wget -P $(TOOLS_DIR) $(M2CTX_URL)
