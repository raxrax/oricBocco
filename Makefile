PROJECT 		:= bocco
PROJECT_DIR		:= $(shell pwd)

# # #
# PROJECT_DSK		:= $(PROJECT).dsk

# # # Autorun main project file
PROJECT_AUTORUN		:= 1

# # # Leave DOS
PROJECT_QUITDOS		:= 0

# # # 6502, 65816
CPU             	:= 6502

ATAPS                   :=
BTAPS                   := start
CTAPS                   := $(PROJECT) $(PROJECT)t $(PROJECT)ed
OTHER                   := tap/se tap/tilesetcolor tap/font1 tap/title tap/lores levels/level0 levels/level1 levels/level2

TAPS                    := $(addsuffix .tap,$(ATAPS) $(BTAPS) $(CTAPS) $(OTHER))

$(PROJECT)_SRC		:= main.c compat.s  libsedoric.c #irqa.s
$(PROJECT)_AUTORUN	:= 1
$(PROJECT)_ADDRESS	:= $(shell echo $$((0x0503)))

$(PROJECT)ed_SRC        := main_editor.c compat.s libsedoric.c libgraphics.s 
$(PROJECT)ed_AUTORUN	:= 1
$(PROJECT)ed_ADDRESS	:= $(shell echo $$((0x0503)))

$(PROJECT)t_SRC		:= main.c compat.s libsedoric.c #irqa.s
$(PROJECT)t_AUTORUN	:= 1
$(PROJECT)t_ADDRESS	:= $(shell echo $$((0x0600)))

start_SRC		:= start.txt
start_AUTORUN		:= 1
start_ADDRESS		:= 

#
include Makefile.local
#
CC65                    := $(CC65_DIR)
OSDK                    := $(OSDK_DIR)
TOOLCHAIN               := CC65

EMU                     := ./oricutron
EMUDIR                  := $(EMUL_DIR)
EMUARG                  := -m a
EMUARG                  += -k m
EMUARG                  += --symbols $(PROJECT_DIR)/$(PROJECT).sym
EMUARG 			+= --serial none
EMUARG 			+= --vsynchack off

COMMON			:= $(COMMON_DIR)

START_ADDRESS		:= $(shell echo $$((0x0600)))

VPATH           	:= $(VPATH) libs objects src

PREPARE			:= prepare
FINALIZE		:= finalize

#
include $($(TOOLCHAIN))/atmos.make

AFLAGS			:= -DASSEMBLER
AFLAGS			+= $(addprefix -I,$(VPATH))

AFLAGS			+= -DUSE_VSYNC
AFLAGS			+= -DUSE_VSYNC_50HZ
# AFLAGS		+= -DUSE_VSYNC_60HZ
AFLAGS			+= -DUSE_VSYNC_SOFT
# AFLAGS		+= -DUSE_VSYNC_HARD
AFLAGS			+= -DUSE_VSYNC_NEGEDGE
AFLAGS			+= -DUSE_VSYNC_AUTO_TEXT

CFLAGS			+= $(addprefix -I,$(VPATH))
CFLAGS			+= -DUSE_VSYNC_50HZ
# CFLAGS		+= -DUSE_VSYNC_60HZ

$(PROJECT)_AFLAGS	+=
$(PROJECT)_CFLAGS	+=

$(PROJECT)t_AFLAGS	+= -DUSE_TAPE
$(PROJECT)t_CFLAGS	+= -DUSE_TAPE


EMUPARAM		:= -r :$(PROJECT_DIR)/$(PROJECT).brk
# EMUPARAM		+= -r $(START_ADDRESS)
# EMUPARAM		+= -r $(shell echo $$((0xfff7)))

TEMP_FILES 		+= $(PROJECT)_dsk.hfe DSKA0000.HFE game*.tap


.PHONY: gen

prepare:
	@echo "[USE]   $(TOOLCHAIN) ..."
	@[ -e $(PROJECT).brk ] || touch $(PROJECT).brk

finalize: hxc
# 	@cp -f $(PROJECT)_dsk.hfe DSKA0000.HFE
	@echo "[TAP]   -> game0.tap"
	@cat start.tap tap/font1.tap tap/tilesetcolor.tap levels/level0.tap $(PROJECT)t.tap > game0.tap
	@echo "[TAP]   -> game1.tap"
	@cat start.tap tap/font1.tap tap/tilesetcolor.tap levels/level1.tap $(PROJECT)t.tap > game1.tap
	@echo "[TAP]   -> game2.tap"
	@cat start.tap tap/font1.tap tap/tilesetcolor.tap levels/level2.tap $(PROJECT)t.tap > game2.tap
	@echo "[OK ]"
