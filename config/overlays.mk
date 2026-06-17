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
OVERLAY_BINARIES := ov_SC01_077 ov_SC01_005 ov_SC01_006 ov_SC03_001 ov_SC01_000 ov_SC01_001 ov_SC02_000 ov_SC02_003 ov_SC03_002 ov_SC03_006 ov_SC04_000 ov_SC04_018 ov_SC04_019 ov_SC05_000 ov_SC06_000 ov_SC07_000

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

# --- ov_SC01_000 (location overlay SC01/FILE_000, vram 0x80128158 — onboarded by new_overlay.sh) ---
ov_SC01_000_EXE        := extracted/retail/SC01.CD.dir/FILE_000.dir/0.4.dec
ov_SC01_000_NAME       := ov_SC01_000
ov_SC01_000_OUT_DIR    := build/ov_SC01_000
ov_SC01_000_OUT        := $(ov_SC01_000_OUT_DIR)/$(ov_SC01_000_NAME)
ov_SC01_000_ELF        := $(ov_SC01_000_OUT).elf
ov_SC01_000_MAPFILE    := $(ov_SC01_000_OUT).map
ov_SC01_000_LD_SCRIPT  := $(ov_SC01_000_OUT).ld
ov_SC01_000_SPLAT_YAML := config/splat.ov_SC01_000.yaml
ov_SC01_000_CHECK_SHA  := config/check.ov_SC01_000.sha
ov_SC01_000_SYMBOLS    := config/symbols.ov_SC01_000.txt
ov_SC01_000_SIG        := .run/sig.ov_SC01_000.jsonl
ov_SC01_000_GHIDRA_PROG := ov_SC01_000
ov_SC01_000_VRAM_BASE  := 0x80128158
ov_SC01_000_TEXT_LO    := 0x80128158
ov_SC01_000_TEXT_HI    := 0x801A58E7
ov_SC01_000_ASM_DIR     := asm/ov_SC01_000
ov_SC01_000_SRC_DIR     := src/ov_SC01_000
ov_SC01_000_UNDEF_SYMS  := build/ov_SC01_000/undefined_syms_auto.txt
ov_SC01_000_UNDEF_FUNCS := build/ov_SC01_000/undefined_funcs_auto.txt

# --- ov_SC01_001 (location overlay SC01/FILE_001, vram 0x80128158 — onboarded by new_overlay.sh) ---
ov_SC01_001_EXE        := extracted/retail/SC01.CD.dir/FILE_001.dir/0.4.dec
ov_SC01_001_NAME       := ov_SC01_001
ov_SC01_001_OUT_DIR    := build/ov_SC01_001
ov_SC01_001_OUT        := $(ov_SC01_001_OUT_DIR)/$(ov_SC01_001_NAME)
ov_SC01_001_ELF        := $(ov_SC01_001_OUT).elf
ov_SC01_001_MAPFILE    := $(ov_SC01_001_OUT).map
ov_SC01_001_LD_SCRIPT  := $(ov_SC01_001_OUT).ld
ov_SC01_001_SPLAT_YAML := config/splat.ov_SC01_001.yaml
ov_SC01_001_CHECK_SHA  := config/check.ov_SC01_001.sha
ov_SC01_001_SYMBOLS    := config/symbols.ov_SC01_001.txt
ov_SC01_001_SIG        := .run/sig.ov_SC01_001.jsonl
ov_SC01_001_GHIDRA_PROG := ov_SC01_001
ov_SC01_001_VRAM_BASE  := 0x80128158
ov_SC01_001_TEXT_LO    := 0x80128158
ov_SC01_001_TEXT_HI    := 0x801F31C7
ov_SC01_001_ASM_DIR     := asm/ov_SC01_001
ov_SC01_001_SRC_DIR     := src/ov_SC01_001
ov_SC01_001_UNDEF_SYMS  := build/ov_SC01_001/undefined_syms_auto.txt
ov_SC01_001_UNDEF_FUNCS := build/ov_SC01_001/undefined_funcs_auto.txt

# --- ov_SC02_000 (location overlay SC02/FILE_000, vram 0x80128158 — onboarded by new_overlay.sh) ---
ov_SC02_000_EXE        := extracted/retail/SC02.CD.dir/FILE_000.dir/0.4.dec
ov_SC02_000_NAME       := ov_SC02_000
ov_SC02_000_OUT_DIR    := build/ov_SC02_000
ov_SC02_000_OUT        := $(ov_SC02_000_OUT_DIR)/$(ov_SC02_000_NAME)
ov_SC02_000_ELF        := $(ov_SC02_000_OUT).elf
ov_SC02_000_MAPFILE    := $(ov_SC02_000_OUT).map
ov_SC02_000_LD_SCRIPT  := $(ov_SC02_000_OUT).ld
ov_SC02_000_SPLAT_YAML := config/splat.ov_SC02_000.yaml
ov_SC02_000_CHECK_SHA  := config/check.ov_SC02_000.sha
ov_SC02_000_SYMBOLS    := config/symbols.ov_SC02_000.txt
ov_SC02_000_SIG        := .run/sig.ov_SC02_000.jsonl
ov_SC02_000_GHIDRA_PROG := ov_SC02_000
ov_SC02_000_VRAM_BASE  := 0x80128158
ov_SC02_000_TEXT_LO    := 0x80128158
ov_SC02_000_TEXT_HI    := 0x801E8867
ov_SC02_000_ASM_DIR     := asm/ov_SC02_000
ov_SC02_000_SRC_DIR     := src/ov_SC02_000
ov_SC02_000_UNDEF_SYMS  := build/ov_SC02_000/undefined_syms_auto.txt
ov_SC02_000_UNDEF_FUNCS := build/ov_SC02_000/undefined_funcs_auto.txt

# --- ov_SC02_003 (location overlay SC02/FILE_003, vram 0x80128158 — onboarded by new_overlay.sh) ---
ov_SC02_003_EXE        := extracted/retail/SC02.CD.dir/FILE_003.dir/0.4.dec
ov_SC02_003_NAME       := ov_SC02_003
ov_SC02_003_OUT_DIR    := build/ov_SC02_003
ov_SC02_003_OUT        := $(ov_SC02_003_OUT_DIR)/$(ov_SC02_003_NAME)
ov_SC02_003_ELF        := $(ov_SC02_003_OUT).elf
ov_SC02_003_MAPFILE    := $(ov_SC02_003_OUT).map
ov_SC02_003_LD_SCRIPT  := $(ov_SC02_003_OUT).ld
ov_SC02_003_SPLAT_YAML := config/splat.ov_SC02_003.yaml
ov_SC02_003_CHECK_SHA  := config/check.ov_SC02_003.sha
ov_SC02_003_SYMBOLS    := config/symbols.ov_SC02_003.txt
ov_SC02_003_SIG        := .run/sig.ov_SC02_003.jsonl
ov_SC02_003_GHIDRA_PROG := ov_SC02_003
ov_SC02_003_VRAM_BASE  := 0x80128158
ov_SC02_003_TEXT_LO    := 0x80128158
ov_SC02_003_TEXT_HI    := 0x801E8867
ov_SC02_003_ASM_DIR     := asm/ov_SC02_003
ov_SC02_003_SRC_DIR     := src/ov_SC02_003
ov_SC02_003_UNDEF_SYMS  := build/ov_SC02_003/undefined_syms_auto.txt
ov_SC02_003_UNDEF_FUNCS := build/ov_SC02_003/undefined_funcs_auto.txt

# --- ov_SC03_002 (location overlay SC03/FILE_002, vram 0x80128158 — onboarded by new_overlay.sh) ---
ov_SC03_002_EXE        := extracted/retail/SC03.CD.dir/FILE_002.dir/0.4.dec
ov_SC03_002_NAME       := ov_SC03_002
ov_SC03_002_OUT_DIR    := build/ov_SC03_002
ov_SC03_002_OUT        := $(ov_SC03_002_OUT_DIR)/$(ov_SC03_002_NAME)
ov_SC03_002_ELF        := $(ov_SC03_002_OUT).elf
ov_SC03_002_MAPFILE    := $(ov_SC03_002_OUT).map
ov_SC03_002_LD_SCRIPT  := $(ov_SC03_002_OUT).ld
ov_SC03_002_SPLAT_YAML := config/splat.ov_SC03_002.yaml
ov_SC03_002_CHECK_SHA  := config/check.ov_SC03_002.sha
ov_SC03_002_SYMBOLS    := config/symbols.ov_SC03_002.txt
ov_SC03_002_SIG        := .run/sig.ov_SC03_002.jsonl
ov_SC03_002_GHIDRA_PROG := ov_SC03_002
ov_SC03_002_VRAM_BASE  := 0x80128158
ov_SC03_002_TEXT_LO    := 0x80128158
ov_SC03_002_TEXT_HI    := 0x801CBB4F
ov_SC03_002_ASM_DIR     := asm/ov_SC03_002
ov_SC03_002_SRC_DIR     := src/ov_SC03_002
ov_SC03_002_UNDEF_SYMS  := build/ov_SC03_002/undefined_syms_auto.txt
ov_SC03_002_UNDEF_FUNCS := build/ov_SC03_002/undefined_funcs_auto.txt

# --- ov_SC03_006 (location overlay SC03/FILE_006, vram 0x80128158 — onboarded by new_overlay.sh) ---
ov_SC03_006_EXE        := extracted/retail/SC03.CD.dir/FILE_006.dir/0.4.dec
ov_SC03_006_NAME       := ov_SC03_006
ov_SC03_006_OUT_DIR    := build/ov_SC03_006
ov_SC03_006_OUT        := $(ov_SC03_006_OUT_DIR)/$(ov_SC03_006_NAME)
ov_SC03_006_ELF        := $(ov_SC03_006_OUT).elf
ov_SC03_006_MAPFILE    := $(ov_SC03_006_OUT).map
ov_SC03_006_LD_SCRIPT  := $(ov_SC03_006_OUT).ld
ov_SC03_006_SPLAT_YAML := config/splat.ov_SC03_006.yaml
ov_SC03_006_CHECK_SHA  := config/check.ov_SC03_006.sha
ov_SC03_006_SYMBOLS    := config/symbols.ov_SC03_006.txt
ov_SC03_006_SIG        := .run/sig.ov_SC03_006.jsonl
ov_SC03_006_GHIDRA_PROG := ov_SC03_006
ov_SC03_006_VRAM_BASE  := 0x80128158
ov_SC03_006_TEXT_LO    := 0x80128158
ov_SC03_006_TEXT_HI    := 0x801F78B7
ov_SC03_006_ASM_DIR     := asm/ov_SC03_006
ov_SC03_006_SRC_DIR     := src/ov_SC03_006
ov_SC03_006_UNDEF_SYMS  := build/ov_SC03_006/undefined_syms_auto.txt
ov_SC03_006_UNDEF_FUNCS := build/ov_SC03_006/undefined_funcs_auto.txt

# --- ov_SC04_000 (location overlay SC04/FILE_000, vram 0x80128158 — onboarded by new_overlay.sh) ---
ov_SC04_000_EXE        := extracted/retail/SC04.CD.dir/FILE_000.dir/0.4.dec
ov_SC04_000_NAME       := ov_SC04_000
ov_SC04_000_OUT_DIR    := build/ov_SC04_000
ov_SC04_000_OUT        := $(ov_SC04_000_OUT_DIR)/$(ov_SC04_000_NAME)
ov_SC04_000_ELF        := $(ov_SC04_000_OUT).elf
ov_SC04_000_MAPFILE    := $(ov_SC04_000_OUT).map
ov_SC04_000_LD_SCRIPT  := $(ov_SC04_000_OUT).ld
ov_SC04_000_SPLAT_YAML := config/splat.ov_SC04_000.yaml
ov_SC04_000_CHECK_SHA  := config/check.ov_SC04_000.sha
ov_SC04_000_SYMBOLS    := config/symbols.ov_SC04_000.txt
ov_SC04_000_SIG        := .run/sig.ov_SC04_000.jsonl
ov_SC04_000_GHIDRA_PROG := ov_SC04_000
ov_SC04_000_VRAM_BASE  := 0x80128158
ov_SC04_000_TEXT_LO    := 0x80128158
ov_SC04_000_TEXT_HI    := 0x801AB057
ov_SC04_000_ASM_DIR     := asm/ov_SC04_000
ov_SC04_000_SRC_DIR     := src/ov_SC04_000
ov_SC04_000_UNDEF_SYMS  := build/ov_SC04_000/undefined_syms_auto.txt
ov_SC04_000_UNDEF_FUNCS := build/ov_SC04_000/undefined_funcs_auto.txt

# --- ov_SC04_018 (location overlay SC04/FILE_018, vram 0x80128158 — onboarded by new_overlay.sh) ---
ov_SC04_018_EXE        := extracted/retail/SC04.CD.dir/FILE_018.dir/0.4.dec
ov_SC04_018_NAME       := ov_SC04_018
ov_SC04_018_OUT_DIR    := build/ov_SC04_018
ov_SC04_018_OUT        := $(ov_SC04_018_OUT_DIR)/$(ov_SC04_018_NAME)
ov_SC04_018_ELF        := $(ov_SC04_018_OUT).elf
ov_SC04_018_MAPFILE    := $(ov_SC04_018_OUT).map
ov_SC04_018_LD_SCRIPT  := $(ov_SC04_018_OUT).ld
ov_SC04_018_SPLAT_YAML := config/splat.ov_SC04_018.yaml
ov_SC04_018_CHECK_SHA  := config/check.ov_SC04_018.sha
ov_SC04_018_SYMBOLS    := config/symbols.ov_SC04_018.txt
ov_SC04_018_SIG        := .run/sig.ov_SC04_018.jsonl
ov_SC04_018_GHIDRA_PROG := ov_SC04_018
ov_SC04_018_VRAM_BASE  := 0x80128158
ov_SC04_018_TEXT_LO    := 0x80128158
ov_SC04_018_TEXT_HI    := 0x801E7B27
ov_SC04_018_ASM_DIR     := asm/ov_SC04_018
ov_SC04_018_SRC_DIR     := src/ov_SC04_018
ov_SC04_018_UNDEF_SYMS  := build/ov_SC04_018/undefined_syms_auto.txt
ov_SC04_018_UNDEF_FUNCS := build/ov_SC04_018/undefined_funcs_auto.txt

# --- ov_SC04_019 (location overlay SC04/FILE_019, vram 0x80128158 — onboarded by new_overlay.sh) ---
ov_SC04_019_EXE        := extracted/retail/SC04.CD.dir/FILE_019.dir/0.4.dec
ov_SC04_019_NAME       := ov_SC04_019
ov_SC04_019_OUT_DIR    := build/ov_SC04_019
ov_SC04_019_OUT        := $(ov_SC04_019_OUT_DIR)/$(ov_SC04_019_NAME)
ov_SC04_019_ELF        := $(ov_SC04_019_OUT).elf
ov_SC04_019_MAPFILE    := $(ov_SC04_019_OUT).map
ov_SC04_019_LD_SCRIPT  := $(ov_SC04_019_OUT).ld
ov_SC04_019_SPLAT_YAML := config/splat.ov_SC04_019.yaml
ov_SC04_019_CHECK_SHA  := config/check.ov_SC04_019.sha
ov_SC04_019_SYMBOLS    := config/symbols.ov_SC04_019.txt
ov_SC04_019_SIG        := .run/sig.ov_SC04_019.jsonl
ov_SC04_019_GHIDRA_PROG := ov_SC04_019
ov_SC04_019_VRAM_BASE  := 0x80128158
ov_SC04_019_TEXT_LO    := 0x80128158
ov_SC04_019_TEXT_HI    := 0x801E7B27
ov_SC04_019_ASM_DIR     := asm/ov_SC04_019
ov_SC04_019_SRC_DIR     := src/ov_SC04_019
ov_SC04_019_UNDEF_SYMS  := build/ov_SC04_019/undefined_syms_auto.txt
ov_SC04_019_UNDEF_FUNCS := build/ov_SC04_019/undefined_funcs_auto.txt

# --- ov_SC05_000 (location overlay SC05/FILE_000, vram 0x80128158 — onboarded by new_overlay.sh) ---
ov_SC05_000_EXE        := extracted/retail/SC05.CD.dir/FILE_000.dir/0.4.dec
ov_SC05_000_NAME       := ov_SC05_000
ov_SC05_000_OUT_DIR    := build/ov_SC05_000
ov_SC05_000_OUT        := $(ov_SC05_000_OUT_DIR)/$(ov_SC05_000_NAME)
ov_SC05_000_ELF        := $(ov_SC05_000_OUT).elf
ov_SC05_000_MAPFILE    := $(ov_SC05_000_OUT).map
ov_SC05_000_LD_SCRIPT  := $(ov_SC05_000_OUT).ld
ov_SC05_000_SPLAT_YAML := config/splat.ov_SC05_000.yaml
ov_SC05_000_CHECK_SHA  := config/check.ov_SC05_000.sha
ov_SC05_000_SYMBOLS    := config/symbols.ov_SC05_000.txt
ov_SC05_000_SIG        := .run/sig.ov_SC05_000.jsonl
ov_SC05_000_GHIDRA_PROG := ov_SC05_000
ov_SC05_000_VRAM_BASE  := 0x80128158
ov_SC05_000_TEXT_LO    := 0x80128158
ov_SC05_000_TEXT_HI    := 0x8019AC57
ov_SC05_000_ASM_DIR     := asm/ov_SC05_000
ov_SC05_000_SRC_DIR     := src/ov_SC05_000
ov_SC05_000_UNDEF_SYMS  := build/ov_SC05_000/undefined_syms_auto.txt
ov_SC05_000_UNDEF_FUNCS := build/ov_SC05_000/undefined_funcs_auto.txt

# --- ov_SC06_000 (location overlay SC06/FILE_000, vram 0x80128158 — onboarded by new_overlay.sh) ---
ov_SC06_000_EXE        := extracted/retail/SC06.CD.dir/FILE_000.dir/0.4.dec
ov_SC06_000_NAME       := ov_SC06_000
ov_SC06_000_OUT_DIR    := build/ov_SC06_000
ov_SC06_000_OUT        := $(ov_SC06_000_OUT_DIR)/$(ov_SC06_000_NAME)
ov_SC06_000_ELF        := $(ov_SC06_000_OUT).elf
ov_SC06_000_MAPFILE    := $(ov_SC06_000_OUT).map
ov_SC06_000_LD_SCRIPT  := $(ov_SC06_000_OUT).ld
ov_SC06_000_SPLAT_YAML := config/splat.ov_SC06_000.yaml
ov_SC06_000_CHECK_SHA  := config/check.ov_SC06_000.sha
ov_SC06_000_SYMBOLS    := config/symbols.ov_SC06_000.txt
ov_SC06_000_SIG        := .run/sig.ov_SC06_000.jsonl
ov_SC06_000_GHIDRA_PROG := ov_SC06_000
ov_SC06_000_VRAM_BASE  := 0x80128158
ov_SC06_000_TEXT_LO    := 0x80128158
ov_SC06_000_TEXT_HI    := 0x801B2187
ov_SC06_000_ASM_DIR     := asm/ov_SC06_000
ov_SC06_000_SRC_DIR     := src/ov_SC06_000
ov_SC06_000_UNDEF_SYMS  := build/ov_SC06_000/undefined_syms_auto.txt
ov_SC06_000_UNDEF_FUNCS := build/ov_SC06_000/undefined_funcs_auto.txt

# --- ov_SC07_000 (location overlay SC07/FILE_000, vram 0x80128158 — onboarded by new_overlay.sh) ---
ov_SC07_000_EXE        := extracted/retail/SC07.CD.dir/FILE_000.dir/0.4.dec
ov_SC07_000_NAME       := ov_SC07_000
ov_SC07_000_OUT_DIR    := build/ov_SC07_000
ov_SC07_000_OUT        := $(ov_SC07_000_OUT_DIR)/$(ov_SC07_000_NAME)
ov_SC07_000_ELF        := $(ov_SC07_000_OUT).elf
ov_SC07_000_MAPFILE    := $(ov_SC07_000_OUT).map
ov_SC07_000_LD_SCRIPT  := $(ov_SC07_000_OUT).ld
ov_SC07_000_SPLAT_YAML := config/splat.ov_SC07_000.yaml
ov_SC07_000_CHECK_SHA  := config/check.ov_SC07_000.sha
ov_SC07_000_SYMBOLS    := config/symbols.ov_SC07_000.txt
ov_SC07_000_SIG        := .run/sig.ov_SC07_000.jsonl
ov_SC07_000_GHIDRA_PROG := ov_SC07_000
ov_SC07_000_VRAM_BASE  := 0x80128158
ov_SC07_000_TEXT_LO    := 0x80128158
ov_SC07_000_TEXT_HI    := 0x801D0CE7
ov_SC07_000_ASM_DIR     := asm/ov_SC07_000
ov_SC07_000_SRC_DIR     := src/ov_SC07_000
ov_SC07_000_UNDEF_SYMS  := build/ov_SC07_000/undefined_syms_auto.txt
ov_SC07_000_UNDEF_FUNCS := build/ov_SC07_000/undefined_funcs_auto.txt
