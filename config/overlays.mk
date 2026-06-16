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
OVERLAY_BINARIES := ov_SC01_077

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
