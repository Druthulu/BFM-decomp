# config/overlays.mk — GENERATED overlay-binary registry (Phase 13).
# =============================================================================
# Holds OVERLAY_BINARIES + the per-<ov> Makefile variable blocks for every onboarded
# location overlay. `-include`d by the Makefile BEFORE its `BINARIES :=` line so the
# aliases enter the build. Regenerated idempotently by tools/new_overlay.sh (T4); the
# hand-maintained Makefile body is never edited to add an overlay. Committed (tiny
# config, not ROM-derived). Each block mirrors the resident_* block (the flat-blob
# recipe): EXE -> the extracted 0.4.dec, VRAM_BASE/TEXT_LO = the shared slot 0x80128158,
# nested asm/<ov> + src/<ov> + build/<ov>, per-binary undefined_*_auto + GHIDRA_PROG.
# =============================================================================
OVERLAY_BINARIES := ov_SC01_077 ov_SC01_005 ov_SC01_006 ov_SC03_001

# --- ov_SC01_077 (location overlay SC01/FILE_077, vram 0x80128158 — Phase 13 T1) ---
# The milestone overlay (load byte-proven, Phase 3 T6b). 731,607 B (0xB29D7) -> end vram
# 0x801DAB2F. Decompressed 0.4.dec payload (LZSS repack is Gen3, not in the verify path).
ov_SC01_077_EXE        := extracted/retail/SC01.CD.dir/FILE_077.dir/0.4.dec
ov_SC01_077_NAME       := ov_SC01_077
ov_SC01_077_OUT_DIR    := build/ov_SC01_077
ov_SC01_077_OUT        := $(ov_SC01_077_OUT_DIR)/$(ov_SC01_077_NAME)
ov_SC01_077_ELF        := $(ov_SC01_077_OUT).elf
ov_SC01_077_MAPFILE    := $(ov_SC01_077_OUT).map
ov_SC01_077_LD_SCRIPT  := $(ov_SC01_077_OUT).ld
ov_SC01_077_SPLAT_YAML := config/splat.ov_SC01_077.yaml
ov_SC01_077_CHECK_SHA  := config/check.ov_SC01_077.sha
ov_SC01_077_SYMBOLS    := config/symbols.ov_SC01_077.txt
ov_SC01_077_SIG        := .run/sig.ov_SC01_077.jsonl
ov_SC01_077_GHIDRA_PROG := ov_SC01_077
ov_SC01_077_VRAM_BASE  := 0x80128158
ov_SC01_077_TEXT_LO    := 0x80128158
ov_SC01_077_TEXT_HI    := 0x801DAB2F
ov_SC01_077_ASM_DIR     := asm/ov_SC01_077
ov_SC01_077_SRC_DIR     := src/ov_SC01_077
ov_SC01_077_UNDEF_SYMS  := build/ov_SC01_077/undefined_syms_auto.txt
ov_SC01_077_UNDEF_FUNCS := build/ov_SC01_077/undefined_funcs_auto.txt

# --- ov_SC01_005 (location overlay SC01/FILE_005, vram 0x80128158 — onboarded by new_overlay.sh) ---
ov_SC01_005_EXE        := extracted/retail/SC01.CD.dir/FILE_005.dir/0.4.dec
ov_SC01_005_NAME       := ov_SC01_005
ov_SC01_005_OUT_DIR    := build/ov_SC01_005
ov_SC01_005_OUT        := $(ov_SC01_005_OUT_DIR)/$(ov_SC01_005_NAME)
ov_SC01_005_ELF        := $(ov_SC01_005_OUT).elf
ov_SC01_005_MAPFILE    := $(ov_SC01_005_OUT).map
ov_SC01_005_LD_SCRIPT  := $(ov_SC01_005_OUT).ld
ov_SC01_005_SPLAT_YAML := config/splat.ov_SC01_005.yaml
ov_SC01_005_CHECK_SHA  := config/check.ov_SC01_005.sha
ov_SC01_005_SYMBOLS    := config/symbols.ov_SC01_005.txt
ov_SC01_005_SIG        := .run/sig.ov_SC01_005.jsonl
ov_SC01_005_GHIDRA_PROG := ov_SC01_005
ov_SC01_005_VRAM_BASE  := 0x80128158
ov_SC01_005_TEXT_LO    := 0x80128158
ov_SC01_005_TEXT_HI    := 0x801CE061
ov_SC01_005_ASM_DIR     := asm/ov_SC01_005
ov_SC01_005_SRC_DIR     := src/ov_SC01_005
ov_SC01_005_UNDEF_SYMS  := build/ov_SC01_005/undefined_syms_auto.txt
ov_SC01_005_UNDEF_FUNCS := build/ov_SC01_005/undefined_funcs_auto.txt

# --- ov_SC01_006 (location overlay SC01/FILE_006, vram 0x80128158 — onboarded by new_overlay.sh) ---
ov_SC01_006_EXE        := extracted/retail/SC01.CD.dir/FILE_006.dir/0.4.dec
ov_SC01_006_NAME       := ov_SC01_006
ov_SC01_006_OUT_DIR    := build/ov_SC01_006
ov_SC01_006_OUT        := $(ov_SC01_006_OUT_DIR)/$(ov_SC01_006_NAME)
ov_SC01_006_ELF        := $(ov_SC01_006_OUT).elf
ov_SC01_006_MAPFILE    := $(ov_SC01_006_OUT).map
ov_SC01_006_LD_SCRIPT  := $(ov_SC01_006_OUT).ld
ov_SC01_006_SPLAT_YAML := config/splat.ov_SC01_006.yaml
ov_SC01_006_CHECK_SHA  := config/check.ov_SC01_006.sha
ov_SC01_006_SYMBOLS    := config/symbols.ov_SC01_006.txt
ov_SC01_006_SIG        := .run/sig.ov_SC01_006.jsonl
ov_SC01_006_GHIDRA_PROG := ov_SC01_006
ov_SC01_006_VRAM_BASE  := 0x80128158
ov_SC01_006_TEXT_LO    := 0x80128158
ov_SC01_006_TEXT_HI    := 0x801CE061
ov_SC01_006_ASM_DIR     := asm/ov_SC01_006
ov_SC01_006_SRC_DIR     := src/ov_SC01_006
ov_SC01_006_UNDEF_SYMS  := build/ov_SC01_006/undefined_syms_auto.txt
ov_SC01_006_UNDEF_FUNCS := build/ov_SC01_006/undefined_funcs_auto.txt

# --- ov_SC03_001 (location overlay SC03/FILE_001, vram 0x80128158 — onboarded by new_overlay.sh) ---
ov_SC03_001_EXE        := extracted/retail/SC03.CD.dir/FILE_001.dir/0.4.dec
ov_SC03_001_NAME       := ov_SC03_001
ov_SC03_001_OUT_DIR    := build/ov_SC03_001
ov_SC03_001_OUT        := $(ov_SC03_001_OUT_DIR)/$(ov_SC03_001_NAME)
ov_SC03_001_ELF        := $(ov_SC03_001_OUT).elf
ov_SC03_001_MAPFILE    := $(ov_SC03_001_OUT).map
ov_SC03_001_LD_SCRIPT  := $(ov_SC03_001_OUT).ld
ov_SC03_001_SPLAT_YAML := config/splat.ov_SC03_001.yaml
ov_SC03_001_CHECK_SHA  := config/check.ov_SC03_001.sha
ov_SC03_001_SYMBOLS    := config/symbols.ov_SC03_001.txt
ov_SC03_001_SIG        := .run/sig.ov_SC03_001.jsonl
ov_SC03_001_GHIDRA_PROG := ov_SC03_001
ov_SC03_001_VRAM_BASE  := 0x80128158
ov_SC03_001_TEXT_LO    := 0x80128158
ov_SC03_001_TEXT_HI    := 0x801EF467
ov_SC03_001_ASM_DIR     := asm/ov_SC03_001
ov_SC03_001_SRC_DIR     := src/ov_SC03_001
ov_SC03_001_UNDEF_SYMS  := build/ov_SC03_001/undefined_syms_auto.txt
ov_SC03_001_UNDEF_FUNCS := build/ov_SC03_001/undefined_funcs_auto.txt
