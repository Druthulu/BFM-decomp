# Makefile — Brave Fencer Musashi decompilation (SLUS-00726, USA)
# =============================================================================
# Phase 4 deliverable. The ONLY live target is `check-env` (the Phase-4
# milestone: toolchain preflight). The split/build/check/expected/clean targets
# have their NAMES fixed here per docs/SETUP.md §6.3, but are loud-failing stubs
# until Phase 5 implements them. Run builds natively from the ext4 clone (H2/R2).
# =============================================================================

SHELL := /bin/bash
.ONESHELL:
.DEFAULT_GOAL := help

# --- paths & tooling ---------------------------------------------------------
PYTHON      := python3
VENV        := .venv
VENV_PY     := $(VENV)/bin/python
MIPS_PREFIX := mipsel-linux-gnu-
AS          := $(MIPS_PREFIX)as
LD          := $(MIPS_PREFIX)ld
OBJCOPY     := $(MIPS_PREFIX)objcopy
CC1_PSX     := tools/bin/gcc-2.7.2-psx/cc1
CC1_CDK     := tools/bin/gcc-2.7.2-cdk/cc1
MASPSX      := tools/maspsx/maspsx.py
EXE         := extracted/retail/SLUS_007.26

# cc1 smoke flags — the §5.4 first-candidate set; the real triple is pinned only
# after Phase-6 fingerprinting. Used here purely to prove cc1 executes.
CC1_SMOKE_FLAGS := -quiet -O2 -G0 -mips1 -mcpu=3000 -mgas -msoft-float -fgnu-linker

# binutils regression line (docs/SETUP.md §4.5): >= 2.38 is a WARN (PS1-matching
# regression suspect; 2.35 known-good). The verdict is revisited in Phase 5.
BINUTILS_WARN_MAJOR := 2
BINUTILS_WARN_MINOR := 38

.PHONY: help check-env extract build check expected clean report sig-refresh

# -----------------------------------------------------------------------------
help:
	@echo "BFM-decomp — make targets:"
	echo "  make check-env   Phase-4 toolchain preflight (the only live target)"
	echo "  make extract     [Phase 5] splat split -> asm/ + linker scripts"
	echo "  make build       [Phase 5] full pipeline -> build/us/SLUS_007.26 (+ SHA1 check)"
	echo "  make check       [Phase 5] standalone SHA1 verification"
	echo "  make expected    [Phase 5] snapshot build/us -> expected/ (asm-differ baseline)"
	echo "  make clean       [Phase 5] remove build output"
	echo "  make report      [Phase 7] regenerate docs/ progress+difficulty+duplicate digests"
	echo "  make sig-refresh [Phase 7] regenerate .run/sig.*.jsonl from Ghidra (MCP must be stopped)"

# -----------------------------------------------------------------------------
# Phase 7 reports: deterministic, committable docs/ digests. progress/difficulty/dup_report
# are Ghidra-free; sig-refresh regenerates dup_report's input from the saved Ghidra DB.
GHIDRA       := $(or $(GHIDRA_INSTALL_DIR),$(HOME)/ghidra_12.1_PUBLIC)
GHIDRA_PROJ  := $(HOME)/bfm-decomp/ghidra

report:
	$(VENV_PY) tools/progress.py --audit
	$(VENV_PY) tools/difficulty.py
	$(VENV_PY) tools/dup_report.py

sig-refresh:
	@if ss -tln 2>/dev/null | grep -qE ':8080([^0-9]|$$)'; then
		echo "sig-refresh: ERROR — Ghidra MCP serving on :8080; run tools/ghidra_mcp_stop.sh first."; exit 2
	fi
	"$(GHIDRA)/support/analyzeHeadless" "$(GHIDRA_PROJ)" bfm -process SLUS_007.26 -noanalysis -readOnly \
	  -scriptPath tools/ghidra_scripts -postScript DumpFunctionSignatures.java

# -----------------------------------------------------------------------------
# check-env: assert every Phase-4 toolchain component. Runs ALL checks (does not
# stop at the first failure) so the report is complete, then exits nonzero if any
# hard check failed. binutils >= 2.38 is a WARN, never a FAIL (§4.5).
check-env:
	@fail=0
	echo "== BFM-decomp environment preflight (Phase 4 check-env) =="
	echo
	# 1) Python >= 3.12 (system python3 drives tooling + the EXE-hash import)
	pyver=$$($(PYTHON) -c 'import sys; print("%d.%d" % sys.version_info[:2])' 2>/dev/null)
	if $(PYTHON) -c 'import sys; raise SystemExit(0 if sys.version_info[:2] >= (3,12) else 1)' 2>/dev/null; then
		echo "[PASS] python3 $$pyver (>= 3.12)"
	else
		echo "[FAIL] python3 $${pyver:-not-found} (need >= 3.12)"; fail=1
	fi
	# 2) venv present + splat importable
	if [ -x "$(VENV_PY)" ]; then
		if $(VENV_PY) -c 'import splat' 2>/dev/null; then
			sv=$$($(VENV_PY) -c 'import importlib.metadata as m; print(m.version("splat64"))' 2>/dev/null)
			echo "[PASS] venv 'import splat' OK (splat64 $${sv:-?})"
		else
			echo "[FAIL] venv present but 'import splat' failed (run: $(VENV_PY) -m pip install 'splat64[mips]>=0.41.0,<1.0.0')"; fail=1
		fi
	else
		echo "[FAIL] $(VENV_PY) missing (run: $(PYTHON) -m venv $(VENV) && $(VENV)/bin/pip install 'splat64[mips]>=0.41.0,<1.0.0')"; fail=1
	fi
	# 3) cc1 candidates executable — R12-clean smoke (stdin -> /dev/null, no temp file)
	for cc1 in "$(CC1_PSX)" "$(CC1_CDK)"; do
		if [ -x "$$cc1" ] && echo 'int _ce(){return 0;}' | "$$cc1" $(CC1_SMOKE_FLAGS) -o /dev/null 2>/dev/null; then
			echo "[PASS] cc1 runs: $$cc1"
		else
			echo "[FAIL] cc1 not runnable: $$cc1 (see docs/SETUP.md §4.7)"; fail=1
		fi
	done
	# 4) maspsx submodule populated
	if [ -f "$(MASPSX)" ]; then
		echo "[PASS] maspsx present: $(MASPSX)"
	else
		echo "[FAIL] $(MASPSX) missing (run: git submodule update --init)"; fail=1
	fi
	# 5) mipsel binutils on PATH (as / ld / objcopy)
	for t in $(AS) $(LD) $(OBJCOPY); do
		if command -v $$t >/dev/null 2>&1; then
			echo "[PASS] $$t: $$($$t --version | head -1)"
		else
			echo "[FAIL] $$t not on PATH (apt install binutils-mipsel-linux-gnu)"; fail=1
		fi
	done
	# 5b) binutils regression line: >= 2.38 -> WARN (not FAIL); §4.5
	asver=$$($(AS) --version 2>/dev/null | head -1 | grep -oE '[0-9]+\.[0-9]+' | head -1)
	if [ -n "$$asver" ]; then
		amaj=$${asver%%.*}; amin=$${asver##*.}
		if [ "$$amaj" -gt $(BINUTILS_WARN_MAJOR) ] || { [ "$$amaj" -eq $(BINUTILS_WARN_MAJOR) ] && [ "$$amin" -ge $(BINUTILS_WARN_MINOR) ]; }; then
			echo "[WARN] mipsel binutils $$asver >= 2.38 — PS1-matching regression suspect (2.35 known-good); revisit in Phase 5 (docs/SETUP.md §4.5)"
		else
			echo "[PASS] mipsel binutils $$asver (< 2.38)"
		fi
	fi
	# 6) committed EXE hash == EXPECTED_EXE_SHA1 (reused constant; fresh-clone-safe)
	if [ -f "$(EXE)" ]; then
		want=$$($(PYTHON) -c 'from tools.bfm_extract.extract_exe import EXPECTED_EXE_SHA1 as h; print(h)' 2>/dev/null)
		got=$$(sha1sum "$(EXE)" | cut -d' ' -f1)
		if [ -n "$$want" ] && [ "$$got" = "$$want" ]; then
			echo "[PASS] $(EXE) sha1 $$got == EXPECTED_EXE_SHA1"
		else
			echo "[FAIL] $(EXE) sha1 $${got:-none} != expected $${want:-unknown}"; fail=1
		fi
	else
		echo "[FAIL] $(EXE) missing (committed retail EXE)"; fail=1
	fi
	echo
	if [ "$$fail" -ne 0 ]; then
		echo "check-env: FAIL — see the [FAIL] lines above."
		exit 1
	fi
	echo "check-env: OK — Phase-4 toolchain ready."

# -----------------------------------------------------------------------------
# Phase-5 build: splat split -> assemble -> link -> objcopy -> SHA1 check.
# The code is 100% assembly (the "all-asm byte-match" milestone). The cpp->cc1->
# maspsx->as path is documented below but dormant until Phase 6 adds `c` segments.
SPLAT       := $(VENV_PY) -m splat
SPLAT_YAML  := config/splat.us.exe.yaml
CPP         := $(MIPS_PREFIX)cpp
OUT_DIR     := build/us
OUT         := $(OUT_DIR)/SLUS_007.26
ELF         := $(OUT_DIR)/SLUS_007.26.elf
MAPFILE     := $(OUT_DIR)/SLUS_007.26.map
LD_SCRIPT   := $(OUT_DIR)/SLUS_007.26.ld
CHECK_SHA   := config/check.us.sha
UNDEF_SYMS  := undefined_syms_auto.txt
UNDEF_FUNCS := undefined_funcs_auto.txt

# Phase 7 (Task 2'): link the real PsyQ libcd SDK objects in place of the libcd-region asm stubs.
# tools/psyq_integrate.py rewrites the splat .ld (swap stub objects -> build/psyq/libcd/*.o + NOLOAD
# data placement, no carving) and emits the externals defsym fragment. Conditional on the SDK ELF
# objects being present (gitignored, SDK-derived, via tools/psyq_build_libs.sh LIBCD); a fresh clone
# without them builds byte-identically via the stubs.
LIBCD_ELF    := .run/obj40/libcd
LIBCD_OBJDIR := build/psyq/libcd
LIBCD_SYMS   := build/psyq/libcd_externals.ld

# libgs (Phase 7 Task #9, FULL integration): 31 libgs objects in 6 contiguous blocks linked in place
# of the libgs1..libgs6 block stubs (the 5 non-libgs gaps stay gsgapN asm stubs). Same conditional/
# idempotent model as libcd. The curated object dir is SDK-derived (gitignored), regenerated by
# tools/make_libgs.sh (needs the LIBGS ELF from psyq_build_libs.sh LIBGS). GS_106 (block 4) anchors
# uniquely only within the libgs window, so the integrate call passes 0x80051804 0x80057928.
LIBGS_ELF    := .run/obj40/libgs_used
LIBGS_OBJDIR := build/psyq/libgs
LIBGS_SYMS   := build/psyq/libgs_externals.ld

# libetc (Phase 8): 5 objects (VSYNC/INTR/INTR_VB/INTR_DMA/VMODE) in ONE contiguous block at the tail
# of the old 800 subseg (ends at libcd1). Single stub "libetc"; no placement window needed (all 5
# anchor uniquely over the full text window). Same conditional/idempotent model as libcd/libgs.
LIBETC_ELF    := .run/obj40/libetc
LIBETC_OBJDIR := build/psyq/libetc
LIBETC_SYMS   := build/psyq/libetc_externals.ld

# libgpu (Phase 8): EXT+PRIM only — SYS.o EXCLUDED (scattered-.bss, cookbook §9.1, GS_001 class; stays a
# stub in 800c). Curated dir libgpu_used = {EXT,PRIM}; regenerate: tools/psyq_build_libs.sh LIBGPU then
# `mkdir -p .run/obj40/libgpu_used && cp .run/obj40/libgpu/{EXT,PRIM}.o .run/obj40/libgpu_used/`.
LIBGPU_ELF    := .run/obj40/libgpu_used
LIBGPU_OBJDIR := build/psyq/libgpu
LIBGPU_SYMS   := build/psyq/libgpu_externals.ld

# libmcrd (Phase 8): 2 objects (LIBMCRD.o = the 55 LIBMCRD_OBJ_* + _card_* memcard I/O; USERFUNC.o), 2
# non-adjacent blocks. Clean (.bss commons all recovered). NB: these are the libmcrd SDK objects; the
# GAME's SaveLoadRoutine/Q#5 save logic is a separate Phase-12 item.
LIBMCRD_ELF    := .run/obj40/libmcrd
LIBMCRD_OBJDIR := build/psyq/libmcrd
LIBMCRD_SYMS   := build/psyq/libmcrd_externals.ld

# libc2 (Phase 8): C stdlib, 17 objects, 2 blocks (16-obj main run libc2_1 + STRCAT.o libc2_2). Clean
# (PRNT.o's printf-format jtbl resolves via NOLOAD .rodata).
LIBC2_ELF    := .run/obj40/libc2
LIBC2_OBJDIR := build/psyq/libc2
LIBC2_SYMS   := build/psyq/libc2_externals.ld

# libgte (Phase 8): GTE math, 53 objects in 22 blocks across the 800b region (subseg lines generated by
# tools/gen_lib_subsegs.py). The integrate window 0x4787C..0x51804 restricts placement to 800b so it
# sees 22 blocks (excludes the 5 deferred libgs-gap objects MTX_05/07/11/REG03/REG11; gsgap1/2/4/5 stay
# stubs). Clean (no scattered .bss). stub list = libgte1..libgte22.
LIBGTE_ELF    := .run/obj40/libgte
LIBGTE_OBJDIR := build/psyq/libgte
LIBGTE_SYMS   := build/psyq/libgte_externals.ld
LIBGTE_STUBS  := libgte1,libgte2,libgte3,libgte4,libgte5,libgte6,libgte7,libgte8,libgte9,libgte10,libgte11,libgte12,libgte13,libgte14,libgte15,libgte16,libgte17,libgte18,libgte19,libgte20,libgte21,libgte22

# Combined libspu+libsnd sound region (Phase 8): the two SDK sound libs interleave in 0x3A444..0x4239C
# so they link as one 60-object region (snd1..snd9). Curated dir .run/obj40/snd_used built by
# tools/make_snd_used.py (4 addresses excluded as scattered-.bss/false-positive stubs). Window arg below.
SND_ELF    := .run/obj40/snd_used
SND_OBJDIR := build/psyq/snd
SND_SYMS   := build/psyq/snd_externals.ld
SND_STUBS  := snd1,snd2,snd3,snd4,snd5,snd6,snd7,snd8,snd9

# Combined libapi+libcard 800c2 region (Phase 8): 22 objects in 4 blocks (apicard1..4). Curated dir
# .run/obj40/apicard_used (tools/make_apicard_used.py). Window 0x61F38..0x62888. (libapi's ~22 objects
# in the 800c3 region are DEFERRED — lowest value.)
APICARD_ELF    := .run/obj40/apicard_used
APICARD_OBJDIR := build/psyq/apicard
APICARD_SYMS   := build/psyq/apicard_externals.ld
APICARD_STUBS  := apicard1,apicard2,apicard3,apicard4

# Assembler flags (docs/SETUP.md §6.2). -G0 is confirmed by the disassembly
# (ledger #8: zero $gp-relative addressing). -no-pad-sections keeps section ends
# un-padded so the link reproduces the original layout.
ASFLAGS       := -Iinclude -march=r3000 -mtune=r3000 -no-pad-sections -O1 -G0
# maspsx ASPSX version — ALWAYS explicit (G8). Inert for the all-asm build; the
# real pin is Phase 6. (Only used on the future cpp->cc1->maspsx `c` path.)
ASPSX_VERSION := 2.56
# Extra maspsx flags. --expand-div is PINNED (Phase-6 fingerprint): the original
# emits the full aspsx div sequence (divu + bnez + break 0x7 zero-check); without it
# maspsx leaves a bare divu and div/rem functions never match. Only affects div/rem,
# so the all-INCLUDE_ASM build and div-free functions are unchanged.
MASPSX_FLAGS  := --expand-div

# Object set must match the splat linker script's references. After the Phase-6 asm->c
# flip the text subseg is src/800.c -> build/src/800.o; the per-function
# asm/nonmatchings/<seg>/*.s are TEXTUALLY .include'd by the .c (via INCLUDE_ASM) at
# assembly time, so they are NOT separate objects and must be excluded from the glob.
# header.s and the data subseg stay asm. Globbed at parse time -> run the canonical
# `make extract && make build`.
ASM_SRCS := $(shell find asm -name '*.s' -not -path 'asm/nonmatchings/*' 2>/dev/null)
C_SRCS   := $(shell find src -name '*.c' 2>/dev/null)
OBJS     := $(ASM_SRCS:%.s=build/%.o) $(C_SRCS:%.c=build/%.o)

# extract: splat split -> asm/, the linker script, include/ macros, undefined_*_auto.txt.
extract:
	@mkdir -p $(OUT_DIR)
	$(SPLAT) split $(SPLAT_YAML)
	# Phase 7 (LZSS): reorder splat's section-major .main into the real
	# .data(front) -> .rodata -> .data(tail) sandwich, so the migrated LZSS
	# jtbl_80072A38 (800.o .rodata) lands at 0x80072A38 between 531DC.data and
	# 6324C.data. Idempotent; keyed off splat's exact output (re-run = no-op).
	$(PYTHON) tools/ld_interleave.py $(LD_SCRIPT)

# The linker script is an `extract` output, not produced by `build` — guard with a
# friendly message instead of make's raw "No rule to make target".
$(LD_SCRIPT):
	@echo "make: $(LD_SCRIPT) missing — run 'make extract' first."; exit 1

# Assemble one splat .s (all-asm path).
build/asm/%.o: asm/%.s
	@mkdir -p $(dir $@)
	@echo "  AS      $@"
	@$(AS) $(ASFLAGS) -o $@ $<

# C path (Phase 6): modern cpp -> vintage cc1 -> maspsx -> modern as. Each src/*.c is
# splat-generated INCLUDE_ASM stubs (file-scope __asm__ .include of the per-function
# asm/nonmatchings/<seg>/<fn>.s); as we match, stubs are replaced by real C. The flags
# below are the docs/SETUP.md §5.4 FIRST-CANDIDATE set — provisional until the Phase-6
# fingerprint ladder PINS the triple (then this block + ASPSX_VERSION are updated, G8).
CPPFLAGS := -lang-c -Iinclude -undef -Wall -fno-builtin -Dmips -D__GNUC__=2 -D__OPTIMIZE__ -Dpsx -D_PSYQ -D_MIPSEL -D_LANGUAGE_C
CC1FLAGS := -quiet -O2 -G0 -mips1 -mcpu=3000 -mgas -msoft-float -fgnu-linker
build/src/%.o: src/%.c
	@mkdir -p $(dir $@)
	@echo "  CC      $@"
	@set -o pipefail; $(CPP) $(CPPFLAGS) $< | $(CC1_PSX) $(CC1FLAGS) | $(VENV_PY) $(MASPSX) --aspsx-version=$(ASPSX_VERSION) $(MASPSX_FLAGS) | $(AS) $(ASFLAGS) -o $@

# Per-module optimization override (SETUP §5.5 — per-module compiler mixing). The boot/
# main/game-mode-dispatch module (src/boot.c, vram 0x80010000-0x800123F0) was compiled at
# -O0, NOT the -O2 game-code default: frame-pointer setup + unfolded large-offset loads
# are the evidence (GameModeDispatch byte-matches only at -O0). gcc 2.7.2 has no
# per-function optimize pragma, so opt level is per-file. Target-specific CC1FLAGS (the
# pattern recipe reads $(CC1FLAGS), so this overrides it for just build/src/boot.o):
build/src/boot.o: CC1FLAGS := -quiet -O0 -G0 -mips1 -mcpu=3000 -mgas -msoft-float -fgnu-linker

# link (the .ld pulls in the .o by path) + objcopy to the raw PS-X EXE image.
$(OUT): $(OBJS) $(LD_SCRIPT)
	@set -e
	mkdir -p $(dir $@)
	# Wire in the real libcd objects (after the build objects exist — the externals discovery
	# trial-links the whole image). Idempotent: re-running re-derives the externals only.
	if [ -d "$(LIBCD_ELF)" ]; then
		$(PYTHON) tools/psyq_integrate.py $(LIBCD_ELF) $(LD_SCRIPT) $(LIBCD_OBJDIR) $(LIBCD_SYMS) libcd1,libcd2
	else
		echo "  (no $(LIBCD_ELF) — libcd region stays asm stubs; run tools/psyq_build_libs.sh LIBCD)"
	fi
	if [ -d "$(LIBGS_ELF)" ]; then
		$(PYTHON) tools/psyq_integrate.py $(LIBGS_ELF) $(LD_SCRIPT) $(LIBGS_OBJDIR) $(LIBGS_SYMS) libgs1,libgs2,libgs3,libgs4,libgs5,libgs6 0x80051804 0x80057928
	else
		echo "  (no $(LIBGS_ELF) — libgs region stays asm stubs; run tools/make_libgs.sh)"
	fi
	if [ -d "$(LIBETC_ELF)" ]; then
		$(PYTHON) tools/psyq_integrate.py $(LIBETC_ELF) $(LD_SCRIPT) $(LIBETC_OBJDIR) $(LIBETC_SYMS) libetc
	else
		echo "  (no $(LIBETC_ELF) — libetc region stays asm stubs; run tools/psyq_build_libs.sh LIBETC)"
	fi
	if [ -d "$(LIBGPU_ELF)" ]; then
		$(PYTHON) tools/psyq_integrate.py $(LIBGPU_ELF) $(LD_SCRIPT) $(LIBGPU_OBJDIR) $(LIBGPU_SYMS) libgpu
	else
		echo "  (no $(LIBGPU_ELF) — libgpu region stays asm stubs; run tools/psyq_build_libs.sh LIBGPU + curate libgpu_used)"
	fi
	if [ -d "$(LIBMCRD_ELF)" ]; then
		$(PYTHON) tools/psyq_integrate.py $(LIBMCRD_ELF) $(LD_SCRIPT) $(LIBMCRD_OBJDIR) $(LIBMCRD_SYMS) libmcrd1,libmcrd2
	else
		echo "  (no $(LIBMCRD_ELF) — libmcrd region stays asm stubs; run tools/psyq_build_libs.sh LIBMCRD)"
	fi
	if [ -d "$(LIBC2_ELF)" ]; then
		$(PYTHON) tools/psyq_integrate.py $(LIBC2_ELF) $(LD_SCRIPT) $(LIBC2_OBJDIR) $(LIBC2_SYMS) libc2_1,libc2_2
	else
		echo "  (no $(LIBC2_ELF) — libc2 region stays asm stubs; run tools/psyq_build_libs.sh LIBC2)"
	fi
	if [ -d "$(LIBGTE_ELF)" ]; then
		$(PYTHON) tools/psyq_integrate.py $(LIBGTE_ELF) $(LD_SCRIPT) $(LIBGTE_OBJDIR) $(LIBGTE_SYMS) $(LIBGTE_STUBS) 0x8004787C 0x80051804
	else
		echo "  (no $(LIBGTE_ELF) — libgte region stays asm stubs; run tools/psyq_build_libs.sh LIBGTE)"
	fi
	if [ -d "$(SND_ELF)" ]; then
		$(PYTHON) tools/psyq_integrate.py $(SND_ELF) $(LD_SCRIPT) $(SND_OBJDIR) $(SND_SYMS) $(SND_STUBS) 0x8003A444 0x8004239C
	else
		echo "  (no $(SND_ELF) — sound region stays asm stubs; run tools/psyq_build_libs.sh LIBSPU LIBSND + tools/make_snd_used.py)"
	fi
	if [ -d "$(APICARD_ELF)" ]; then
		$(PYTHON) tools/psyq_integrate.py $(APICARD_ELF) $(LD_SCRIPT) $(APICARD_OBJDIR) $(APICARD_SYMS) $(APICARD_STUBS) 0x80061F38 0x80062888
	else
		echo "  (no $(APICARD_ELF) — apicard region stays asm stubs; run tools/psyq_build_libs.sh LIBAPI LIBCARD + tools/make_apicard_used.py)"
	fi
	SYMS=""; [ -f "$(LIBCD_SYMS)" ] && SYMS="-T $(LIBCD_SYMS)"; [ -f "$(LIBGS_SYMS)" ] && SYMS="$$SYMS -T $(LIBGS_SYMS)"; [ -f "$(LIBETC_SYMS)" ] && SYMS="$$SYMS -T $(LIBETC_SYMS)"; [ -f "$(LIBGPU_SYMS)" ] && SYMS="$$SYMS -T $(LIBGPU_SYMS)"; [ -f "$(LIBMCRD_SYMS)" ] && SYMS="$$SYMS -T $(LIBMCRD_SYMS)"; [ -f "$(LIBC2_SYMS)" ] && SYMS="$$SYMS -T $(LIBC2_SYMS)"; [ -f "$(LIBGTE_SYMS)" ] && SYMS="$$SYMS -T $(LIBGTE_SYMS)"; [ -f "$(SND_SYMS)" ] && SYMS="$$SYMS -T $(SND_SYMS)"; [ -f "$(APICARD_SYMS)" ] && SYMS="$$SYMS -T $(APICARD_SYMS)"
	echo "  LD      $(ELF)"
	$(LD) -T $(LD_SCRIPT) -T $(UNDEF_SYMS) -T $(UNDEF_FUNCS) $$SYMS --no-check-sections -Map $(MAPFILE) -o $(ELF)
	echo "  OBJCOPY $@"
	$(OBJCOPY) -O binary $(ELF) $@

# build = produce $(OUT) and verify its SHA1 (check pulls in $(OUT)).
build: check

# check: SHA1 of the build vs the committed original hash. The definition of "build OK".
check: $(OUT)
	@got=$$(sha1sum $(OUT) | cut -d' ' -f1)
	want=$$(cut -d' ' -f1 $(CHECK_SHA) 2>/dev/null)
	if [ -z "$$want" ]; then echo "[FAIL] $(CHECK_SHA) missing or empty"; exit 1; fi
	if [ "$$got" = "$$want" ]; then
		echo "[ OK ] $(OUT)"
		echo "       sha1 $$got == $(CHECK_SHA)  (BYTE-IDENTICAL)"
	else
		echo "[FAIL] $(OUT)"
		echo "       got  $$got"
		echo "       want $$want"
		exit 1
	fi

# expected: snapshot a SHA1-verified build into expected/build/ as the asm-differ
# baseline for Phase 6 (asm-differ diffs build/<obj> vs expected/build/<obj>).
expected: build
	@set -e
	rm -rf expected/build
	mkdir -p expected/build
	cp -r build/. expected/build/
	echo "expected: baseline -> expected/build/ (from the verified, byte-identical build)"

# clean: remove ALL regenerable outputs (build/ + the splat tree) so a config change
# is followed by a stale-free `make clean && make extract && make build` (H3).
clean:
	@rm -rf build expected asm undefined_syms_auto.txt undefined_funcs_auto.txt
	@rm -f include/include_asm.h include/macro.inc include/labels.inc include/gte_macros.inc
	@echo "clean: removed build/, expected/, and the regenerated splat tree (asm/, include macros, undefined_*_auto.txt)."
