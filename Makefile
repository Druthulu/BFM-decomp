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
# Phase-5 targets: names fixed now (docs/SETUP.md §6.3), implemented in Phase 5.
# Loud-failing no-op stubs — never a silent exit 0 (would falsely read as success).
extract build check expected clean:
	@echo "make: target '$@' is a Phase-5 target — not implemented yet."
	echo "      (Its name is fixed now per docs/SETUP.md §6.3; Phase 5 implements it.)"
	exit 1
