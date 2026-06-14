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

.PHONY: help check-env extract build check expected clean

# -----------------------------------------------------------------------------
help:
	@echo "BFM-decomp — make targets:"
	echo "  make check-env   Phase-4 toolchain preflight (the only live target)"
	echo "  make extract     [Phase 5] splat split -> asm/ + linker scripts"
	echo "  make build       [Phase 5] full pipeline -> build/us/SLUS_007.26 (+ SHA1 check)"
	echo "  make check       [Phase 5] standalone SHA1 verification"
	echo "  make expected    [Phase 5] snapshot build/us -> expected/ (asm-differ baseline)"
	echo "  make clean       [Phase 5] remove build output"

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
LD_SCRIPT   := $(OUT_DIR)/SLUS_007.26.ld
CHECK_SHA   := config/check.us.sha
UNDEF_SYMS  := undefined_syms_auto.txt
UNDEF_FUNCS := undefined_funcs_auto.txt

# Assembler flags (docs/SETUP.md §6.2). -G0 is confirmed by the disassembly
# (ledger #8: zero $gp-relative addressing). -no-pad-sections keeps section ends
# un-padded so the link reproduces the original layout.
ASFLAGS       := -Iinclude -march=r3000 -mtune=r3000 -no-pad-sections -O1 -G0
# maspsx ASPSX version — ALWAYS explicit (G8). Inert for the all-asm build; the
# real pin is Phase 6. (Only used on the future cpp->cc1->maspsx `c` path.)
ASPSX_VERSION := 2.56

# Every splat-emitted .s -> build/<path>.o, matching the object names the generated
# linker script references (asm/800.s -> build/asm/800.o). ASM_SRCS is globbed at
# parse time, so run the canonical `make extract && make build`.
ASM_SRCS := $(shell find asm -name '*.s' 2>/dev/null)
OBJS     := $(ASM_SRCS:%.s=build/%.o)

# extract: splat split -> asm/, the linker script, include/ macros, undefined_*_auto.txt.
extract:
	@mkdir -p $(OUT_DIR)
	$(SPLAT) split $(SPLAT_YAML)

# The linker script is an `extract` output, not produced by `build` — guard with a
# friendly message instead of make's raw "No rule to make target".
$(LD_SCRIPT):
	@echo "make: $(LD_SCRIPT) missing — run 'make extract' first."; exit 1

# Assemble one splat .s (all-asm path).
build/asm/%.o: asm/%.s
	@mkdir -p $(dir $@)
	@echo "  AS      $@"
	@$(AS) $(ASFLAGS) -o $@ $<

# Phase 6 will add the C path here, e.g.:
#   build/src/%.o: src/%.c
#       $(CPP) <§6.2 cpp flags> $< | $(CC1_PSX) <§6.2 cc1 flags> \
#         | $(VENV_PY) $(MASPSX) --aspsx-version=$(ASPSX_VERSION) | $(AS) $(ASFLAGS) -o $@

# link (the .ld pulls in the .o by path) + objcopy to the raw PS-X EXE image.
$(OUT): $(OBJS) $(LD_SCRIPT)
	@set -e
	mkdir -p $(dir $@)
	echo "  LD      $(ELF)"
	$(LD) -T $(LD_SCRIPT) -T $(UNDEF_SYMS) -T $(UNDEF_FUNCS) --no-check-sections -o $(ELF)
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
