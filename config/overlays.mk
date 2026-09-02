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
OVERLAY_BINARIES := ov_SC01_077 ov_SC01_005 ov_SC01_006 ov_SC03_001 ov_SC01_000 ov_SC01_001 ov_SC02_000 ov_SC02_003 ov_SC03_002 ov_SC03_006 ov_SC04_000 ov_SC04_018 ov_SC04_019 ov_SC05_000 ov_SC06_000 ov_SC07_000 ov_SC01_004 ov_SC01_008 ov_SC01_009 ov_SC01_074 ov_SC01_080 ov_SC01_084 ov_SC02_004 ov_SC02_005 ov_SC02_011 ov_SC02_015 ov_SC02_016 ov_SC02_017 ov_SC02_021 ov_SC02_026 ov_SC02_027 ov_SC02_028 ov_SC02_031 ov_SC02_035 ov_SC02_039 ov_SC02_041 ov_SC03_003 ov_SC03_007 ov_SC03_010 ov_SC03_011 ov_SC03_012 ov_SC03_013 ov_SC03_014 ov_SC03_015 ov_SC03_023 ov_SC03_024 ov_SC03_028 ov_SC03_029 ov_SC03_030 ov_SC03_031 ov_SC03_089 ov_SC03_090 ov_SC03_091 ov_SC03_092 ov_SC03_093 ov_SC03_094 ov_SC03_095 ov_SC03_096 ov_SC03_097 ov_SC03_098 ov_SC03_099 ov_SC03_100 ov_SC03_101 ov_SC03_102 ov_SC03_103 ov_SC03_104 ov_SC03_105 ov_SC03_108 ov_SC03_109 ov_SC03_110 ov_SC03_111 ov_SC03_112 ov_SC03_113 ov_SC03_114 ov_SC03_115 ov_SC03_116 ov_SC03_117 ov_SC03_118 ov_SC03_119 ov_SC03_121 ov_SC03_124 ov_SC03_125 ov_SC03_126 ov_SC04_002 ov_SC04_003 ov_SC04_004 ov_SC04_005 ov_SC04_006 ov_SC04_007 ov_SC04_008 ov_SC04_009 ov_SC04_010 ov_SC04_011 ov_SC04_012 ov_SC04_015 ov_SC04_016 ov_SC04_020 ov_SC04_021 ov_SC05_001 ov_SC05_002 ov_SC05_003 ov_SC05_004 ov_SC05_005 ov_SC05_006 ov_SC05_007 ov_SC05_008 ov_SC05_009 ov_SC05_010 ov_SC05_011 ov_SC05_017 ov_SC05_018 ov_SC05_019 ov_SC06_006 ov_SC06_008 ov_SC06_010 ov_SC06_011 ov_SC06_013 ov_SC06_014 ov_SC06_015 ov_SC06_016 ov_SC06_018 ov_SC06_020 ov_SC06_022 ov_SC06_024 ov_SC06_025 ov_SC06_027 ov_SC06_029 ov_SC06_030 ov_SC06_032 ov_SC06_033 ov_SC07_001 ov_SC07_002 ov_SC07_008 ov_SC07_009 ov_SC07_006 ov_SC07_007 ov_SC07_010 ov_SC07_011 ov_MAIN_012 ov_SC02_037 ov_SC03_107

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
ov_SC01_077_JTBL_INTERLEAVE := --order tail.data.o,ov_SC01_077_a.o,ov_SC01_077_jr_8012ACE0.o,tail2.data.o,ov_SC01_077_jr_80135888.o,tail3.data.o,ov_SC01_077_jr_80135A4C.o,tail4.data.o,ov_SC01_077_jr_80135D20.o,tail5.data.o,ov_SC01_077_jr_801380E0.o,ov_SC01_077_o0.o,tail6.data.o,ov_SC01_077.o,tail7.data.o,ov_SC01_077_jr_8015444C.o,ov_SC01_077_jr_80154C24.o,ov_SC01_077_jr_801588CC.o,ov_SC01_077_jr_80159C84.o,tail8.data.o,ov_SC01_077_jr_8015A3C8.o,tail9.data.o,ov_SC01_077_jr_8015AE2C.o,tail10.data.o,ov_SC01_077_jr_8015C32C.o,tail11.data.o,ov_SC01_077_jr_8016AB6C.o,tail12.data.o,ov_SC01_077_jr_80171B4C.o,ov_SC01_077_jr_801734BC.o,tail13.data.o,ov_SC01_077_jr_801789AC.o,ov_SC01_077_jr_80178D40.o,tail14.data.o,ov_SC01_077_jr_8017A4AC.o,tail15.data.o,ov_SC01_077_jr_8017AE2C.o,tail16.data.o,ov_SC01_077_jr_80180B64.o,ov_SC01_077_jr_8018103C.o,ov_SC01_077_jr_80181BE4.o,tail17.data.o,ov_SC01_077_jr_80181F08.o,tail18.data.o,ov_SC01_077_jr_801820DC.o,ov_SC01_077_jr_80182268.o,ov_SC01_077_jr_80182E7C.o,ov_SC01_077_jr_80183324.o,ov_SC01_077_jr_80183AF0.o,ov_SC01_077_jr_80183BAC.o,ov_SC01_077_jr_80183CF4.o,tail19.data.o,trailing.o  # Phase-26 §8 jtbl-rodata carve
build/src/ov_SC01_077/ov_SC01_077.o: JTBL_PADS := 0,0,4,0,4,0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38,+0x58,+0x70,+0x90,+0xa8
build/src/ov_SC01_077/ov_SC01_077_a.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14
build/src/ov_SC01_077/ov_SC01_077_jr_8012ACE0.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0xcc,+0xe0
build/src/ov_SC01_077/ov_SC01_077_jr_80135D20.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC01_077/ov_SC01_077_jr_8015444C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x70
build/src/ov_SC01_077/ov_SC01_077_jr_80154C24.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x24
build/src/ov_SC01_077/ov_SC01_077_jr_801588CC.o: JTBL_PADS := 0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x28,+0x48
build/src/ov_SC01_077/ov_SC01_077_jr_80159C84.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC01_077/ov_SC01_077_jr_8015AE2C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC01_077/ov_SC01_077_jr_8016AB6C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC01_077/ov_SC01_077_jr_80178D40.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x178
build/src/ov_SC01_077/ov_SC01_077_jr_8017AE2C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14
build/src/ov_SC01_077/ov_SC01_077_jr_80180B64.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x40
build/src/ov_SC01_077/ov_SC01_077_jr_8018103C.o: JTBL_PADS := 0,4,0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18,+0x38,+0x58,+0x78
build/src/ov_SC01_077/ov_SC01_077_jr_80182268.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x40
build/src/ov_SC01_077/ov_SC01_077_jr_80182E7C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC01_077/ov_SC01_077_jr_80183324.o: JTBL_PADS := 0,0,0,0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x40,+0x60,+0x80,+0xa0
build/src/ov_SC01_077/ov_SC01_077_jr_80183BAC.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC01_077/ov_SC01_077_o0.o: JTBL_PADS := 0,4,4,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x38,+0xa8,+0x118
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
ov_SC01_005_JTBL_INTERLEAVE := --order tail.data.o,ov_SC01_005.o,ov_SC01_005_jr_8012ACE0.o,tail2.data.o,ov_SC01_005_jr_80135888.o,tail3.data.o,ov_SC01_005_jr_80135A4C.o,tail4.data.o,ov_SC01_005_jr_80135D20.o,tail5.data.o,ov_SC01_005_jr_801380E0.o,ov_SC01_005_o0c.o,tail6.data.o,ov_SC01_005_jr_8013F350.o,tail7.data.o,ov_SC01_005_jr_8013FFD8.o,tail8.data.o,ov_SC01_005_jr_80140608.o,tail9.data.o,ov_SC01_005_jr_8015444C.o,ov_SC01_005_jr_80154C24.o,ov_SC01_005_jr_801588CC.o,ov_SC01_005_jr_80159C84.o,tail10.data.o,ov_SC01_005_jr_8015A3C8.o,tail11.data.o,ov_SC01_005_jr_8015AE2C.o,tail12.data.o,ov_SC01_005_jr_8015C32C.o,tail13.data.o,ov_SC01_005_jr_8016AB6C.o,tail14.data.o,ov_SC01_005_jr_80171B4C.o,ov_SC01_005_jr_801734BC.o,tail15.data.o,ov_SC01_005_jr_801789AC.o,ov_SC01_005_jr_80178D40.o,tail16.data.o,ov_SC01_005_jr_8017A4AC.o,tail17.data.o,ov_SC01_005_jr_8017AE2C.o,ov_SC01_005_jr_8017C340.o,tail18.data.o,ov_SC01_005_jr_8017EB44.o,ov_SC01_005_jr_8017ED5C.o,tail19.data.o,trailing.o  # Phase-26 §8 jtbl-rodata carve
build/src/ov_SC01_005/ov_SC01_005.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14
build/src/ov_SC01_005/ov_SC01_005_jr_8012ACE0.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0xcc,+0xe0
build/src/ov_SC01_005/ov_SC01_005_jr_80135D20.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC01_005/ov_SC01_005_jr_8013F350.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC01_005/ov_SC01_005_jr_8013FFD8.o: JTBL_PADS := 0,0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38,+0x58
build/src/ov_SC01_005/ov_SC01_005_jr_8015444C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x70
build/src/ov_SC01_005/ov_SC01_005_jr_80154C24.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x24
build/src/ov_SC01_005/ov_SC01_005_jr_801588CC.o: JTBL_PADS := 0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x28,+0x48
build/src/ov_SC01_005/ov_SC01_005_jr_80159C84.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC01_005/ov_SC01_005_jr_8015AE2C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC01_005/ov_SC01_005_jr_8016AB6C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC01_005/ov_SC01_005_jr_80178D40.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x178
build/src/ov_SC01_005/ov_SC01_005_jr_8017ED5C.o: JTBL_PADS := 0  # §8e pads — 1 table(s), byte-proven by jtbl_pads_fix
build/src/ov_SC01_005/ov_SC01_005_o0c.o: JTBL_PADS := 0,4,4,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x38,+0xa8,+0x118
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
ov_SC01_006_JTBL_INTERLEAVE := --order tail.data.o,ov_SC01_006.o,ov_SC01_006_jr_8012ACE0.o,tail2.data.o,ov_SC01_006_jr_80135888.o,tail3.data.o,ov_SC01_006_jr_80135A4C.o,tail4.data.o,ov_SC01_006_jr_80135D20.o,tail5.data.o,ov_SC01_006_jr_801380E0.o,ov_SC01_006_o0c.o,tail6.data.o,ov_SC01_006_jr_8013F350.o,tail7.data.o,ov_SC01_006_jr_8013FFD8.o,tail8.data.o,ov_SC01_006_jr_80140608.o,tail9.data.o,ov_SC01_006_jr_8015444C.o,ov_SC01_006_jr_80154C24.o,ov_SC01_006_jr_801588CC.o,ov_SC01_006_jr_80159C84.o,tail10.data.o,ov_SC01_006_jr_8015A3C8.o,tail11.data.o,ov_SC01_006_jr_8015AE2C.o,tail12.data.o,ov_SC01_006_jr_8015C32C.o,tail13.data.o,ov_SC01_006_jr_8016AB6C.o,tail14.data.o,ov_SC01_006_jr_80171B4C.o,ov_SC01_006_jr_801734BC.o,tail15.data.o,ov_SC01_006_jr_801789AC.o,ov_SC01_006_jr_80178D40.o,tail16.data.o,ov_SC01_006_jr_8017A4AC.o,tail17.data.o,ov_SC01_006_jr_8017AE2C.o,ov_SC01_006_jr_8017C340.o,tail18.data.o,ov_SC01_006_jr_8017EB44.o,ov_SC01_006_jr_8017ED5C.o,tail19.data.o,trailing.o  # Phase-26 §8 jtbl-rodata carve
build/src/ov_SC01_006/ov_SC01_006.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14
build/src/ov_SC01_006/ov_SC01_006_jr_8012ACE0.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0xcc,+0xe0
build/src/ov_SC01_006/ov_SC01_006_jr_80135D20.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC01_006/ov_SC01_006_jr_8013F350.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC01_006/ov_SC01_006_jr_8013FFD8.o: JTBL_PADS := 0,0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38,+0x58
build/src/ov_SC01_006/ov_SC01_006_jr_8015444C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x70
build/src/ov_SC01_006/ov_SC01_006_jr_80154C24.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x24
build/src/ov_SC01_006/ov_SC01_006_jr_801588CC.o: JTBL_PADS := 0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x28,+0x48
build/src/ov_SC01_006/ov_SC01_006_jr_80159C84.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC01_006/ov_SC01_006_jr_8015AE2C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC01_006/ov_SC01_006_jr_8016AB6C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC01_006/ov_SC01_006_jr_80178D40.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x178
build/src/ov_SC01_006/ov_SC01_006_jr_8017ED5C.o: JTBL_PADS := 0  # §8e pads — 1 table(s), byte-proven by jtbl_pads_fix
build/src/ov_SC01_006/ov_SC01_006_o0c.o: JTBL_PADS := 0,4,4,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x38,+0xa8,+0x118
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
ov_SC03_001_JTBL_INTERLEAVE := --order tail.data.o,ov_SC03_001.o,ov_SC03_001_jr_8012ACE0.o,tail2.data.o,ov_SC03_001_jr_80135888.o,tail3.data.o,ov_SC03_001_jr_80135A4C.o,tail4.data.o,ov_SC03_001_jr_80135D20.o,tail5.data.o,ov_SC03_001_jr_801380E0.o,ov_SC03_001_o0c.o,tail6.data.o,ov_SC03_001_jr_8013F350.o,tail7.data.o,ov_SC03_001_jr_8013FFD8.o,tail8.data.o,ov_SC03_001_jr_80140608.o,tail9.data.o,ov_SC03_001_jr_8015444C.o,ov_SC03_001_jr_80154C24.o,ov_SC03_001_jr_801588CC.o,ov_SC03_001_jr_80159C84.o,tail10.data.o,ov_SC03_001_jr_8015A3C8.o,tail11.data.o,ov_SC03_001_jr_8015AE2C.o,tail12.data.o,ov_SC03_001_jr_8015C32C.o,tail13.data.o,ov_SC03_001_jr_8016AB6C.o,tail14.data.o,ov_SC03_001_jr_80171B4C.o,ov_SC03_001_jr_801734BC.o,tail15.data.o,ov_SC03_001_jr_801789AC.o,ov_SC03_001_jr_80178D40.o,tail16.data.o,ov_SC03_001_jr_8017A4AC.o,tail17.data.o,ov_SC03_001_jr_8017AE2C.o,ov_SC03_001_jr_80184DDC.o,tail18.data.o,ov_SC03_001_jr_80184F64.o,ov_SC03_001_jr_8018631C.o,ov_SC03_001_jr_801870B0.o,ov_SC03_001_jr_80188830.o,tail19.data.o,ov_SC03_001_jr_80189030.o,tail20.data.o,ov_SC03_001_jr_8018A3A8.o,ov_SC03_001_jr_8018B8DC.o,tail21.data.o,trailing.o  # Phase-26 §8 jtbl-rodata carve
build/src/ov_SC03_001/ov_SC03_001.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14
build/src/ov_SC03_001/ov_SC03_001_jr_8012ACE0.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0xcc,+0xe0
build/src/ov_SC03_001/ov_SC03_001_jr_80135D20.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC03_001/ov_SC03_001_jr_8013F350.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_001/ov_SC03_001_jr_8013FFD8.o: JTBL_PADS := 0,0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38,+0x58
build/src/ov_SC03_001/ov_SC03_001_jr_8015444C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x70
build/src/ov_SC03_001/ov_SC03_001_jr_80154C24.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x24
build/src/ov_SC03_001/ov_SC03_001_jr_801588CC.o: JTBL_PADS := 0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x28,+0x48
build/src/ov_SC03_001/ov_SC03_001_jr_80159C84.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_001/ov_SC03_001_jr_8015AE2C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_001/ov_SC03_001_jr_8016AB6C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_001/ov_SC03_001_jr_80178D40.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x178
build/src/ov_SC03_001/ov_SC03_001_jr_8017AE2C.o: JTBL_PADS := 0,0,0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14,+0x34,+0x4c
build/src/ov_SC03_001/ov_SC03_001_jr_80184F64.o: JTBL_PADS := 0,0,0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14,+0x7c,+0x94
build/src/ov_SC03_001/ov_SC03_001_jr_8018A3A8.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x38
build/src/ov_SC03_001/ov_SC03_001_o0c.o: JTBL_PADS := 0,4,4,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x38,+0xa8,+0x118
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
ov_SC01_000_JTBL_INTERLEAVE := --order tail.data.o,ov_SC01_000.o,ov_SC01_000_jr_8012ACE0.o,tail2.data.o,ov_SC01_000_jr_80135888.o,tail3.data.o,ov_SC01_000_jr_80135A4C.o,tail4.data.o,ov_SC01_000_jr_80135D20.o,tail5.data.o,ov_SC01_000_jr_801380E0.o,ov_SC01_000_o0c.o,tail6.data.o,ov_SC01_000_jr_8013F350.o,tail7.data.o,ov_SC01_000_jr_8013FFD8.o,tail8.data.o,ov_SC01_000_jr_80140608.o,tail9.data.o,ov_SC01_000_jr_8015444C.o,ov_SC01_000_jr_80154C24.o,ov_SC01_000_jr_801588CC.o,ov_SC01_000_jr_80159C84.o,tail10.data.o,ov_SC01_000_jr_8015A3C8.o,tail11.data.o,ov_SC01_000_jr_8015AE2C.o,tail12.data.o,ov_SC01_000_jr_8015C32C.o,tail13.data.o,ov_SC01_000_jr_8016AB6C.o,tail14.data.o,ov_SC01_000_jr_80171B4C.o,ov_SC01_000_jr_801734BC.o,tail15.data.o,ov_SC01_000_jr_801789AC.o,ov_SC01_000_jr_80178D40.o,tail16.data.o,ov_SC01_000_jr_8017A4AC.o,tail17.data.o,ov_SC01_000_jr_8017AE2C.o,ov_SC01_000_jr_8017BEBC.o,tail18.data.o,trailing.o  # Phase-26 §8 jtbl-rodata carve
build/src/ov_SC01_000/ov_SC01_000.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14
build/src/ov_SC01_000/ov_SC01_000_jr_8012ACE0.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0xcc,+0xe0
build/src/ov_SC01_000/ov_SC01_000_jr_80135D20.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC01_000/ov_SC01_000_jr_8013F350.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC01_000/ov_SC01_000_jr_8013FFD8.o: JTBL_PADS := 0,0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38,+0x58
build/src/ov_SC01_000/ov_SC01_000_jr_8015444C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x70
build/src/ov_SC01_000/ov_SC01_000_jr_80154C24.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x24
build/src/ov_SC01_000/ov_SC01_000_jr_801588CC.o: JTBL_PADS := 0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x28,+0x48
build/src/ov_SC01_000/ov_SC01_000_jr_80159C84.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC01_000/ov_SC01_000_jr_8015AE2C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC01_000/ov_SC01_000_jr_8016AB6C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC01_000/ov_SC01_000_jr_80178D40.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x178
build/src/ov_SC01_000/ov_SC01_000_jr_8017BEBC.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC01_000/ov_SC01_000_o0c.o: JTBL_PADS := 0,4,4,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x38,+0xa8,+0x118
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
ov_SC01_001_JTBL_INTERLEAVE := --order tail.data.o,ov_SC01_001.o,ov_SC01_001_jr_8012ACE0.o,tail2.data.o,ov_SC01_001_jr_80135888.o,tail3.data.o,ov_SC01_001_jr_80135A4C.o,tail4.data.o,ov_SC01_001_jr_80135D20.o,tail5.data.o,ov_SC01_001_jr_801380E0.o,ov_SC01_001_o0c.o,tail6.data.o,ov_SC01_001_jr_8013F350.o,tail7.data.o,ov_SC01_001_jr_8013FFD8.o,tail8.data.o,ov_SC01_001_jr_80140608.o,tail9.data.o,ov_SC01_001_jr_8015444C.o,ov_SC01_001_jr_80154C24.o,ov_SC01_001_jr_801588CC.o,ov_SC01_001_jr_80159C84.o,tail10.data.o,ov_SC01_001_jr_8015A3C8.o,tail11.data.o,ov_SC01_001_jr_8015AE2C.o,tail12.data.o,ov_SC01_001_jr_8015C32C.o,tail13.data.o,ov_SC01_001_jr_8016AB6C.o,tail14.data.o,ov_SC01_001_jr_80171B4C.o,ov_SC01_001_jr_801734BC.o,tail15.data.o,ov_SC01_001_jr_801789AC.o,ov_SC01_001_jr_80178D40.o,tail16.data.o,ov_SC01_001_jr_8017A4AC.o,tail17.data.o,ov_SC01_001_jr_8017AE2C.o,ov_SC01_001_jr_8017BEBC.o,ov_SC01_001_jr_8017D2DC.o,tail18.data.o,trailing.o  # Phase-26 §8 jtbl-rodata carve
build/src/ov_SC01_001/ov_SC01_001.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14
build/src/ov_SC01_001/ov_SC01_001_jr_8012ACE0.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0xcc,+0xe0
build/src/ov_SC01_001/ov_SC01_001_jr_80135D20.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC01_001/ov_SC01_001_jr_8013F350.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC01_001/ov_SC01_001_jr_8013FFD8.o: JTBL_PADS := 0,0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38,+0x58
build/src/ov_SC01_001/ov_SC01_001_jr_8015444C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x70
build/src/ov_SC01_001/ov_SC01_001_jr_80154C24.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x24
build/src/ov_SC01_001/ov_SC01_001_jr_801588CC.o: JTBL_PADS := 0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x28,+0x48
build/src/ov_SC01_001/ov_SC01_001_jr_80159C84.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC01_001/ov_SC01_001_jr_8015AE2C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC01_001/ov_SC01_001_jr_8016AB6C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC01_001/ov_SC01_001_jr_80178D40.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x178
build/src/ov_SC01_001/ov_SC01_001_o0c.o: JTBL_PADS := 0,4,4,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x38,+0xa8,+0x118
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
ov_SC02_000_JTBL_INTERLEAVE := --order tail.data.o,ov_SC02_000.o,ov_SC02_000_jr_8012ACE0.o,tail2.data.o,ov_SC02_000_jr_80135888.o,tail3.data.o,ov_SC02_000_jr_80135A4C.o,tail4.data.o,ov_SC02_000_jr_80135D20.o,tail5.data.o,ov_SC02_000_jr_801380E0.o,ov_SC02_000_o0c.o,tail6.data.o,ov_SC02_000_jr_8013F350.o,tail7.data.o,ov_SC02_000_jr_8013FFD8.o,tail8.data.o,ov_SC02_000_jr_80140608.o,tail9.data.o,ov_SC02_000_jr_8015444C.o,ov_SC02_000_jr_80154C24.o,ov_SC02_000_jr_801588CC.o,ov_SC02_000_jr_80159C84.o,tail10.data.o,ov_SC02_000_jr_8015A3C8.o,tail11.data.o,ov_SC02_000_jr_8015AE2C.o,tail12.data.o,ov_SC02_000_jr_8015C32C.o,tail13.data.o,ov_SC02_000_jr_8016AB6C.o,tail14.data.o,ov_SC02_000_jr_80171B4C.o,ov_SC02_000_jr_801734BC.o,tail15.data.o,ov_SC02_000_jr_801789AC.o,ov_SC02_000_jr_80178D40.o,tail16.data.o,ov_SC02_000_jr_8017A4AC.o,tail17.data.o,ov_SC02_000_jr_8017AE2C.o,ov_SC02_000_jr_8017EA84.o,tail18.data.o,ov_SC02_000_jr_8017F950.o,tail19.data.o,ov_SC02_000_jr_8017FB24.o,ov_SC02_000_jr_8017FCB0.o,ov_SC02_000_jr_801808C4.o,ov_SC02_000_jr_80180D6C.o,ov_SC02_000_jr_80181538.o,ov_SC02_000_jr_80181698.o,ov_SC02_000_jr_8018173C.o,tail20.data.o,trailing.o  # Phase-26 §8 jtbl-rodata carve
build/src/ov_SC02_000/ov_SC02_000.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14
build/src/ov_SC02_000/ov_SC02_000_jr_8012ACE0.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0xcc,+0xe0
build/src/ov_SC02_000/ov_SC02_000_jr_80135D20.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC02_000/ov_SC02_000_jr_8013F350.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC02_000/ov_SC02_000_jr_8013FFD8.o: JTBL_PADS := 0,0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38,+0x58
build/src/ov_SC02_000/ov_SC02_000_jr_8015444C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x70
build/src/ov_SC02_000/ov_SC02_000_jr_80154C24.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x24
build/src/ov_SC02_000/ov_SC02_000_jr_801588CC.o: JTBL_PADS := 0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x28,+0x48
build/src/ov_SC02_000/ov_SC02_000_jr_80159C84.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC02_000/ov_SC02_000_jr_8015AE2C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC02_000/ov_SC02_000_jr_8016AB6C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC02_000/ov_SC02_000_jr_80178D40.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x178
build/src/ov_SC02_000/ov_SC02_000_jr_8017AE2C.o: JTBL_PADS := 0,0,0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14,+0x34,+0x54,+0x74
build/src/ov_SC02_000/ov_SC02_000_jr_8017EA84.o: JTBL_PADS := 0,4,0,0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18,+0x38,+0x58,+0x78,+0x98
build/src/ov_SC02_000/ov_SC02_000_jr_8017FCB0.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x40
build/src/ov_SC02_000/ov_SC02_000_jr_801808C4.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC02_000/ov_SC02_000_jr_80180D6C.o: JTBL_PADS := 0,0,0,0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x40,+0x60,+0x80,+0xa0
build/src/ov_SC02_000/ov_SC02_000_jr_80181538.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC02_000/ov_SC02_000_o0c.o: JTBL_PADS := 0,4,4,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x38,+0xa8,+0x118
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
ov_SC02_003_JTBL_INTERLEAVE := --order tail.data.o,ov_SC02_003.o,ov_SC02_003_jr_8012ACE0.o,tail2.data.o,ov_SC02_003_jr_80135888.o,tail3.data.o,ov_SC02_003_jr_80135A4C.o,tail4.data.o,ov_SC02_003_jr_80135D20.o,tail5.data.o,ov_SC02_003_jr_801380E0.o,ov_SC02_003_o0c.o,tail6.data.o,ov_SC02_003_jr_8013F350.o,tail7.data.o,ov_SC02_003_jr_8013FFD8.o,tail8.data.o,ov_SC02_003_jr_80140608.o,tail9.data.o,ov_SC02_003_jr_8015444C.o,ov_SC02_003_jr_80154C24.o,ov_SC02_003_jr_801588CC.o,ov_SC02_003_jr_80159C84.o,tail10.data.o,ov_SC02_003_jr_8015A3C8.o,tail11.data.o,ov_SC02_003_jr_8015AE2C.o,tail12.data.o,ov_SC02_003_jr_8015C32C.o,tail13.data.o,ov_SC02_003_jr_8016AB6C.o,tail14.data.o,ov_SC02_003_jr_80171B4C.o,ov_SC02_003_jr_801734BC.o,tail15.data.o,ov_SC02_003_jr_801789AC.o,ov_SC02_003_jr_80178D40.o,tail16.data.o,ov_SC02_003_jr_8017A4AC.o,tail17.data.o,ov_SC02_003_jr_8017AE2C.o,ov_SC02_003_jr_8017EA84.o,tail18.data.o,ov_SC02_003_jr_8017F950.o,tail19.data.o,ov_SC02_003_jr_8017FB24.o,ov_SC02_003_jr_8017FCB0.o,ov_SC02_003_jr_801808C4.o,ov_SC02_003_jr_80180D6C.o,ov_SC02_003_jr_80181538.o,ov_SC02_003_jr_80181698.o,ov_SC02_003_jr_8018173C.o,tail20.data.o,trailing.o  # Phase-26 §8 jtbl-rodata carve
build/src/ov_SC02_003/ov_SC02_003.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14
build/src/ov_SC02_003/ov_SC02_003_jr_8012ACE0.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0xcc,+0xe0
build/src/ov_SC02_003/ov_SC02_003_jr_80135D20.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC02_003/ov_SC02_003_jr_8013F350.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC02_003/ov_SC02_003_jr_8013FFD8.o: JTBL_PADS := 0,0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38,+0x58
build/src/ov_SC02_003/ov_SC02_003_jr_8015444C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x70
build/src/ov_SC02_003/ov_SC02_003_jr_80154C24.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x24
build/src/ov_SC02_003/ov_SC02_003_jr_801588CC.o: JTBL_PADS := 0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x28,+0x48
build/src/ov_SC02_003/ov_SC02_003_jr_80159C84.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC02_003/ov_SC02_003_jr_8015AE2C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC02_003/ov_SC02_003_jr_8016AB6C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC02_003/ov_SC02_003_jr_80178D40.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x178
build/src/ov_SC02_003/ov_SC02_003_jr_8017AE2C.o: JTBL_PADS := 0,0,0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14,+0x34,+0x54,+0x74
build/src/ov_SC02_003/ov_SC02_003_jr_8017EA84.o: JTBL_PADS := 0,4,0,0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18,+0x38,+0x58,+0x78,+0x98
build/src/ov_SC02_003/ov_SC02_003_jr_8017FCB0.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x40
build/src/ov_SC02_003/ov_SC02_003_jr_801808C4.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC02_003/ov_SC02_003_jr_80180D6C.o: JTBL_PADS := 0,0,0,0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x40,+0x60,+0x80,+0xa0
build/src/ov_SC02_003/ov_SC02_003_jr_80181538.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC02_003/ov_SC02_003_o0c.o: JTBL_PADS := 0,4,4,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x38,+0xa8,+0x118
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
ov_SC03_002_JTBL_INTERLEAVE := --order tail.data.o,ov_SC03_002.o,ov_SC03_002_jr_8012ACE0.o,tail2.data.o,ov_SC03_002_jr_80135888.o,tail3.data.o,ov_SC03_002_jr_80135A4C.o,tail4.data.o,ov_SC03_002_jr_80135D20.o,tail5.data.o,ov_SC03_002_jr_801380E0.o,ov_SC03_002_o0c.o,tail6.data.o,ov_SC03_002_jr_8013F350.o,tail7.data.o,ov_SC03_002_jr_8013FFD8.o,tail8.data.o,ov_SC03_002_jr_80140608.o,tail9.data.o,ov_SC03_002_jr_8015444C.o,ov_SC03_002_jr_80154C24.o,ov_SC03_002_jr_801588CC.o,ov_SC03_002_jr_80159C84.o,tail10.data.o,ov_SC03_002_jr_8015A3C8.o,tail11.data.o,ov_SC03_002_jr_8015AE2C.o,tail12.data.o,ov_SC03_002_jr_8015C32C.o,tail13.data.o,ov_SC03_002_jr_8016AB6C.o,tail14.data.o,ov_SC03_002_jr_80171B4C.o,ov_SC03_002_jr_801734BC.o,tail15.data.o,ov_SC03_002_jr_801789AC.o,ov_SC03_002_jr_80178D40.o,tail16.data.o,ov_SC03_002_jr_8017A4AC.o,tail17.data.o,ov_SC03_002_jr_8017AE2C.o,ov_SC03_002_jr_8017D604.o,tail18.data.o,ov_SC03_002_jr_801815AC.o,ov_SC03_002_jr_80181BCC.o,tail19.data.o,ov_SC03_002_jr_80181D78.o,ov_SC03_002_jr_8018431C.o,tail20.data.o,trailing.o  # Phase-26 §8 jtbl-rodata carve
build/src/ov_SC03_002/ov_SC03_002.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14
build/src/ov_SC03_002/ov_SC03_002_jr_8012ACE0.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0xcc,+0xe0
build/src/ov_SC03_002/ov_SC03_002_jr_80135D20.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC03_002/ov_SC03_002_jr_8013F350.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_002/ov_SC03_002_jr_8013FFD8.o: JTBL_PADS := 0,0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38,+0x58
build/src/ov_SC03_002/ov_SC03_002_jr_8015444C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x70
build/src/ov_SC03_002/ov_SC03_002_jr_80154C24.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x24
build/src/ov_SC03_002/ov_SC03_002_jr_801588CC.o: JTBL_PADS := 0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x28,+0x48
build/src/ov_SC03_002/ov_SC03_002_jr_80159C84.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_002/ov_SC03_002_jr_8015AE2C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_002/ov_SC03_002_jr_8016AB6C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_002/ov_SC03_002_jr_80178D40.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x178
build/src/ov_SC03_002/ov_SC03_002_jr_8018431C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x1c
build/src/ov_SC03_002/ov_SC03_002_o0c.o: JTBL_PADS := 0,4,4,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x38,+0xa8,+0x118
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
ov_SC03_006_JTBL_INTERLEAVE := --order tail.data.o,ov_SC03_006.o,ov_SC03_006_jr_8012ACE0.o,tail2.data.o,ov_SC03_006_jr_80135888.o,tail3.data.o,ov_SC03_006_jr_80135A4C.o,tail4.data.o,ov_SC03_006_jr_80135D20.o,tail5.data.o,ov_SC03_006_jr_801380E0.o,ov_SC03_006_o0c.o,tail6.data.o,ov_SC03_006_jr_8013F350.o,tail7.data.o,ov_SC03_006_jr_8013FFD8.o,tail8.data.o,ov_SC03_006_jr_80140608.o,tail9.data.o,ov_SC03_006_jr_8015444C.o,ov_SC03_006_jr_80154C24.o,ov_SC03_006_jr_801588CC.o,ov_SC03_006_jr_80159C84.o,tail10.data.o,ov_SC03_006_jr_8015A3C8.o,tail11.data.o,ov_SC03_006_jr_8015AE2C.o,tail12.data.o,ov_SC03_006_jr_8015C32C.o,tail13.data.o,ov_SC03_006_jr_8016AB6C.o,tail14.data.o,ov_SC03_006_jr_80171B4C.o,ov_SC03_006_jr_801734BC.o,tail15.data.o,ov_SC03_006_jr_801789AC.o,ov_SC03_006_jr_80178D40.o,tail16.data.o,ov_SC03_006_jr_8017A4AC.o,tail17.data.o,ov_SC03_006_jr_8017AE2C.o,tail18.data.o,trailing.o  # Phase-26 §8 jtbl-rodata carve
build/src/ov_SC03_006/ov_SC03_006.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14
build/src/ov_SC03_006/ov_SC03_006_jr_8012ACE0.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0xcc,+0xe0
build/src/ov_SC03_006/ov_SC03_006_jr_80135D20.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC03_006/ov_SC03_006_jr_8013F350.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_006/ov_SC03_006_jr_8013FFD8.o: JTBL_PADS := 0,0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38,+0x58
build/src/ov_SC03_006/ov_SC03_006_jr_8015444C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x70
build/src/ov_SC03_006/ov_SC03_006_jr_80154C24.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x24
build/src/ov_SC03_006/ov_SC03_006_jr_801588CC.o: JTBL_PADS := 0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x28,+0x48
build/src/ov_SC03_006/ov_SC03_006_jr_80159C84.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_006/ov_SC03_006_jr_8015AE2C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_006/ov_SC03_006_jr_8016AB6C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_006/ov_SC03_006_jr_80178D40.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x178
build/src/ov_SC03_006/ov_SC03_006_jr_8017AE2C.o: JTBL_PADS := 0,0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14,+0x34,+0x48
build/src/ov_SC03_006/ov_SC03_006_o0c.o: JTBL_PADS := 0,4,4,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x38,+0xa8,+0x118
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
ov_SC04_000_JTBL_INTERLEAVE := --order tail.data.o,ov_SC04_000.o,ov_SC04_000_jr_8012ACE0.o,tail2.data.o,ov_SC04_000_jr_80135888.o,tail3.data.o,ov_SC04_000_jr_80135A4C.o,tail4.data.o,ov_SC04_000_jr_80135D20.o,tail5.data.o,ov_SC04_000_jr_801380E0.o,ov_SC04_000_o0c.o,tail6.data.o,ov_SC04_000_jr_8013F350.o,tail7.data.o,ov_SC04_000_jr_8013FFD8.o,tail8.data.o,ov_SC04_000_jr_80140608.o,tail9.data.o,ov_SC04_000_jr_8015444C.o,ov_SC04_000_jr_80154C24.o,ov_SC04_000_jr_801588CC.o,ov_SC04_000_jr_80159C84.o,tail10.data.o,ov_SC04_000_jr_8015A3C8.o,tail11.data.o,ov_SC04_000_jr_8015AE2C.o,tail12.data.o,ov_SC04_000_jr_8015C32C.o,tail13.data.o,ov_SC04_000_jr_8016AB6C.o,tail14.data.o,ov_SC04_000_jr_80171B4C.o,ov_SC04_000_jr_801734BC.o,tail15.data.o,ov_SC04_000_jr_801789AC.o,ov_SC04_000_jr_80178D40.o,tail16.data.o,ov_SC04_000_jr_8017A4AC.o,tail17.data.o,ov_SC04_000_jr_8017AE2C.o,ov_SC04_000_jr_8017BEBC.o,ov_SC04_000_jr_801818E8.o,tail18.data.o,trailing.o  # Phase-26 §8 jtbl-rodata carve
build/src/ov_SC04_000/ov_SC04_000.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14
build/src/ov_SC04_000/ov_SC04_000_jr_8012ACE0.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0xcc,+0xe0
build/src/ov_SC04_000/ov_SC04_000_jr_80135D20.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC04_000/ov_SC04_000_jr_8013F350.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC04_000/ov_SC04_000_jr_8013FFD8.o: JTBL_PADS := 0,0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38,+0x58
build/src/ov_SC04_000/ov_SC04_000_jr_8015444C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x70
build/src/ov_SC04_000/ov_SC04_000_jr_80154C24.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x24
build/src/ov_SC04_000/ov_SC04_000_jr_801588CC.o: JTBL_PADS := 0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x28,+0x48
build/src/ov_SC04_000/ov_SC04_000_jr_80159C84.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC04_000/ov_SC04_000_jr_8015AE2C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC04_000/ov_SC04_000_jr_8016AB6C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC04_000/ov_SC04_000_jr_80178D40.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x178
build/src/ov_SC04_000/ov_SC04_000_jr_8017BEBC.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x40
build/src/ov_SC04_000/ov_SC04_000_o0c.o: JTBL_PADS := 0,4,4,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x38,+0xa8,+0x118
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
ov_SC04_018_JTBL_INTERLEAVE := --order tail.data.o,ov_SC04_018.o,ov_SC04_018_jr_8012ACE0.o,tail2.data.o,ov_SC04_018_jr_80135888.o,tail3.data.o,ov_SC04_018_jr_80135A4C.o,tail4.data.o,ov_SC04_018_jr_80135D20.o,tail5.data.o,ov_SC04_018_jr_801380E0.o,ov_SC04_018_o0c.o,tail6.data.o,ov_SC04_018_jr_8013F350.o,tail7.data.o,ov_SC04_018_jr_8013FFD8.o,tail8.data.o,ov_SC04_018_jr_80140608.o,tail9.data.o,ov_SC04_018_jr_8015444C.o,ov_SC04_018_jr_80154C24.o,ov_SC04_018_jr_801588CC.o,ov_SC04_018_jr_80159C84.o,tail10.data.o,ov_SC04_018_jr_8015A3C8.o,tail11.data.o,ov_SC04_018_jr_8015AE2C.o,tail12.data.o,ov_SC04_018_jr_8015C32C.o,tail13.data.o,ov_SC04_018_jr_8016AB6C.o,tail14.data.o,ov_SC04_018_jr_80171B4C.o,ov_SC04_018_jr_801734BC.o,tail15.data.o,ov_SC04_018_jr_801789AC.o,ov_SC04_018_jr_80178D40.o,tail16.data.o,ov_SC04_018_jr_8017A4AC.o,tail17.data.o,ov_SC04_018_jr_8017AE2C.o,tail18.data.o,ov_SC04_018_jr_80183E6C.o,ov_SC04_018_jr_80185D70.o,tail19.data.o,ov_SC04_018_jr_80186570.o,tail20.data.o,ov_SC04_018_jr_801878E8.o,ov_SC04_018_jr_80188E1C.o,ov_SC04_018_jr_8018CC40.o,tail21.data.o,trailing.o  # Phase-26 §8 jtbl-rodata carve
build/src/ov_SC04_018/ov_SC04_018.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14
build/src/ov_SC04_018/ov_SC04_018_jr_8012ACE0.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0xcc,+0xe0
build/src/ov_SC04_018/ov_SC04_018_jr_80135D20.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC04_018/ov_SC04_018_jr_8013F350.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC04_018/ov_SC04_018_jr_8013FFD8.o: JTBL_PADS := 0,0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38,+0x58
build/src/ov_SC04_018/ov_SC04_018_jr_8015444C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x70
build/src/ov_SC04_018/ov_SC04_018_jr_80154C24.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x24
build/src/ov_SC04_018/ov_SC04_018_jr_801588CC.o: JTBL_PADS := 0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x28,+0x48
build/src/ov_SC04_018/ov_SC04_018_jr_80159C84.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC04_018/ov_SC04_018_jr_8015AE2C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC04_018/ov_SC04_018_jr_8016AB6C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC04_018/ov_SC04_018_jr_80178D40.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x178
build/src/ov_SC04_018/ov_SC04_018_jr_8017AE2C.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14,+0x34 (S62 T2d: pads_audit — the TU compiles 3 tables; the carve's 4th (0xbd450, 5 entries) belongs to func_80181804, currently a stub whose .s supplies it after the C tables)
build/src/ov_SC04_018/ov_SC04_018_jr_80183E6C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC04_018/ov_SC04_018_jr_801878E8.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x38
build/src/ov_SC04_018/ov_SC04_018_jr_80188E1C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC04_018/ov_SC04_018_o0c.o: JTBL_PADS := 0,4,4,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x38,+0xa8,+0x118
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
ov_SC04_019_JTBL_INTERLEAVE := --order tail.data.o,ov_SC04_019.o,ov_SC04_019_jr_8012ACE0.o,tail2.data.o,ov_SC04_019_jr_80135888.o,tail3.data.o,ov_SC04_019_jr_80135A4C.o,tail4.data.o,ov_SC04_019_jr_80135D20.o,tail5.data.o,ov_SC04_019_jr_801380E0.o,ov_SC04_019_o0c.o,tail6.data.o,ov_SC04_019_jr_8013F350.o,tail7.data.o,ov_SC04_019_jr_8013FFD8.o,tail8.data.o,ov_SC04_019_jr_80140608.o,tail9.data.o,ov_SC04_019_jr_8015444C.o,ov_SC04_019_jr_80154C24.o,ov_SC04_019_jr_801588CC.o,ov_SC04_019_jr_80159C84.o,tail10.data.o,ov_SC04_019_jr_8015A3C8.o,tail11.data.o,ov_SC04_019_jr_8015AE2C.o,tail12.data.o,ov_SC04_019_jr_8015C32C.o,tail13.data.o,ov_SC04_019_jr_8016AB6C.o,tail14.data.o,ov_SC04_019_jr_80171B4C.o,ov_SC04_019_jr_801734BC.o,tail15.data.o,ov_SC04_019_jr_801789AC.o,ov_SC04_019_jr_80178D40.o,tail16.data.o,ov_SC04_019_jr_8017A4AC.o,tail17.data.o,ov_SC04_019_jr_8017AE2C.o,ov_SC04_019_jr_80181804.o,ov_SC04_019_jr_80183E6C.o,ov_SC04_019_jr_80185D70.o,tail18.data.o,ov_SC04_019_jr_80186570.o,tail19.data.o,ov_SC04_019_jr_801878E8.o,ov_SC04_019_jr_80188E1C.o,ov_SC04_019_jr_8018CC40.o,tail20.data.o,trailing.o  # Phase-26 §8 jtbl-rodata carve
build/src/ov_SC04_019/ov_SC04_019.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14
build/src/ov_SC04_019/ov_SC04_019_jr_8012ACE0.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0xcc,+0xe0
build/src/ov_SC04_019/ov_SC04_019_jr_80135D20.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC04_019/ov_SC04_019_jr_8013F350.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC04_019/ov_SC04_019_jr_8013FFD8.o: JTBL_PADS := 0,0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38,+0x58
build/src/ov_SC04_019/ov_SC04_019_jr_8015444C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x70
build/src/ov_SC04_019/ov_SC04_019_jr_80154C24.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x24
build/src/ov_SC04_019/ov_SC04_019_jr_801588CC.o: JTBL_PADS := 0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x28,+0x48
build/src/ov_SC04_019/ov_SC04_019_jr_80159C84.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC04_019/ov_SC04_019_jr_8015AE2C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC04_019/ov_SC04_019_jr_8016AB6C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC04_019/ov_SC04_019_jr_80178D40.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x178
build/src/ov_SC04_019/ov_SC04_019_jr_8017AE2C.o: JTBL_PADS := 0,0,0  # §8e pads — None table(s), byte-proven by jtbl_pads_fix
build/src/ov_SC04_019/ov_SC04_019_jr_80181804.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC04_019/ov_SC04_019_jr_80183E6C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC04_019/ov_SC04_019_jr_801878E8.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x38
build/src/ov_SC04_019/ov_SC04_019_o0c.o: JTBL_PADS := 0,4,4,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x38,+0xa8,+0x118
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
ov_SC05_000_JTBL_INTERLEAVE := --order tail.data.o,ov_SC05_000.o,ov_SC05_000_jr_8012ACE0.o,tail2.data.o,ov_SC05_000_jr_80135888.o,tail3.data.o,ov_SC05_000_jr_80135A4C.o,tail4.data.o,ov_SC05_000_jr_80135D20.o,tail5.data.o,ov_SC05_000_jr_801380E0.o,ov_SC05_000_o0c.o,tail6.data.o,ov_SC05_000_jr_8013F350.o,tail7.data.o,ov_SC05_000_jr_8013FFD8.o,tail8.data.o,ov_SC05_000_jr_80140608.o,tail9.data.o,ov_SC05_000_jr_8015444C.o,ov_SC05_000_jr_80154C24.o,ov_SC05_000_jr_801588CC.o,ov_SC05_000_jr_80159C84.o,tail10.data.o,ov_SC05_000_jr_8015A3C8.o,tail11.data.o,ov_SC05_000_jr_8015AE2C.o,tail12.data.o,ov_SC05_000_jr_8015C32C.o,tail13.data.o,ov_SC05_000_jr_8016AB6C.o,tail14.data.o,ov_SC05_000_jr_80171B4C.o,ov_SC05_000_jr_801734BC.o,tail15.data.o,ov_SC05_000_jr_801789AC.o,ov_SC05_000_jr_80178D40.o,tail16.data.o,ov_SC05_000_jr_8017A4AC.o,tail17.data.o,ov_SC05_000_jr_8017AE2C.o,ov_SC05_000_jr_8017BEBC.o,tail18.data.o,trailing.o  # Phase-26 §8 jtbl-rodata carve
build/src/ov_SC05_000/ov_SC05_000.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14
build/src/ov_SC05_000/ov_SC05_000_jr_8012ACE0.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0xcc,+0xe0
build/src/ov_SC05_000/ov_SC05_000_jr_80135D20.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC05_000/ov_SC05_000_jr_8013F350.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC05_000/ov_SC05_000_jr_8013FFD8.o: JTBL_PADS := 0,0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38,+0x58
build/src/ov_SC05_000/ov_SC05_000_jr_8015444C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x70
build/src/ov_SC05_000/ov_SC05_000_jr_80154C24.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x24
build/src/ov_SC05_000/ov_SC05_000_jr_801588CC.o: JTBL_PADS := 0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x28,+0x48
build/src/ov_SC05_000/ov_SC05_000_jr_80159C84.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC05_000/ov_SC05_000_jr_8015AE2C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC05_000/ov_SC05_000_jr_8016AB6C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC05_000/ov_SC05_000_jr_80178D40.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x178
build/src/ov_SC05_000/ov_SC05_000_o0c.o: JTBL_PADS := 0,4,4,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x38,+0xa8,+0x118
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
ov_SC06_000_JTBL_INTERLEAVE := --order tail.data.o,ov_SC06_000.o,ov_SC06_000_jr_8012ACE0.o,tail2.data.o,ov_SC06_000_jr_80135888.o,tail3.data.o,ov_SC06_000_jr_80135A4C.o,tail4.data.o,ov_SC06_000_jr_80135D20.o,tail5.data.o,ov_SC06_000_jr_801380E0.o,ov_SC06_000_o0c.o,tail6.data.o,ov_SC06_000_jr_8013F350.o,tail7.data.o,ov_SC06_000_jr_8014032C.o,tail8.data.o,ov_SC06_000_jr_80140608.o,tail9.data.o,ov_SC06_000_jr_8015444C.o,ov_SC06_000_jr_80154C24.o,ov_SC06_000_jr_801588CC.o,ov_SC06_000_jr_80159C84.o,tail10.data.o,ov_SC06_000_jr_8015A3C8.o,tail11.data.o,ov_SC06_000_jr_8015AE2C.o,tail12.data.o,ov_SC06_000_jr_8015C32C.o,tail13.data.o,ov_SC06_000_jr_8016AB6C.o,tail14.data.o,ov_SC06_000_jr_80171B4C.o,ov_SC06_000_jr_801734BC.o,tail15.data.o,ov_SC06_000_jr_801789AC.o,ov_SC06_000_jr_80178D40.o,tail16.data.o,ov_SC06_000_jr_8017A4AC.o,tail17.data.o,ov_SC06_000_jr_8017AE2C.o,tail18.data.o,trailing.o  # Phase-26 §8 jtbl-rodata carve
build/src/ov_SC06_000/ov_SC06_000.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14
build/src/ov_SC06_000/ov_SC06_000_jr_8012ACE0.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0xcc,+0xe0
build/src/ov_SC06_000/ov_SC06_000_jr_80135D20.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC06_000/ov_SC06_000_jr_8013F350.o: JTBL_PADS := 0,0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38,+0x58
build/src/ov_SC06_000/ov_SC06_000_jr_8014032C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC06_000/ov_SC06_000_jr_8015444C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x70
build/src/ov_SC06_000/ov_SC06_000_jr_80154C24.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x24
build/src/ov_SC06_000/ov_SC06_000_jr_801588CC.o: JTBL_PADS := 0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x28,+0x48
build/src/ov_SC06_000/ov_SC06_000_jr_80159C84.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC06_000/ov_SC06_000_jr_8015AE2C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC06_000/ov_SC06_000_jr_8016AB6C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC06_000/ov_SC06_000_jr_80178D40.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x178
build/src/ov_SC06_000/ov_SC06_000_jr_8017AE2C.o: JTBL_PADS := 0,0,4  # §8e pads — None table(s), byte-proven by jtbl_pads_fix
build/src/ov_SC06_000/ov_SC06_000_o0c.o: JTBL_PADS := 0,4,4,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x38,+0xa8,+0x118
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
ov_SC07_000_JTBL_INTERLEAVE := --order tail.data.o,ov_SC07_000.o,ov_SC07_000_jr_8012ACE0.o,tail2.data.o,ov_SC07_000_jr_80135888.o,tail3.data.o,ov_SC07_000_jr_80135A4C.o,tail4.data.o,ov_SC07_000_jr_80135D20.o,tail5.data.o,ov_SC07_000_jr_801380E0.o,ov_SC07_000_o0c.o,tail6.data.o,ov_SC07_000_jr_8013F350.o,tail7.data.o,ov_SC07_000_jr_8013FFD8.o,tail8.data.o,ov_SC07_000_jr_80140608.o,tail9.data.o,ov_SC07_000_jr_8015444C.o,ov_SC07_000_jr_80154C24.o,ov_SC07_000_jr_801588CC.o,ov_SC07_000_jr_80159C84.o,tail10.data.o,ov_SC07_000_jr_8015A3C8.o,tail11.data.o,ov_SC07_000_jr_8015AE2C.o,tail12.data.o,ov_SC07_000_jr_8015C32C.o,tail13.data.o,ov_SC07_000_jr_8016AB6C.o,tail14.data.o,ov_SC07_000_jr_80171B4C.o,ov_SC07_000_jr_801734BC.o,tail15.data.o,ov_SC07_000_jr_801789AC.o,ov_SC07_000_jr_80178D40.o,tail16.data.o,ov_SC07_000_jr_8017A4AC.o,tail17.data.o,ov_SC07_000_jr_8017AE2C.o,ov_SC07_000_jr_8017BEBC.o,tail18.data.o,ov_SC07_000_jr_8017F8B8.o,tail19.data.o,trailing.o  # Phase-26 §8 jtbl-rodata carve
build/src/ov_SC07_000/ov_SC07_000.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14
build/src/ov_SC07_000/ov_SC07_000_jr_8012ACE0.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0xcc,+0xe0
build/src/ov_SC07_000/ov_SC07_000_jr_80135D20.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC07_000/ov_SC07_000_jr_8013F350.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC07_000/ov_SC07_000_jr_8013FFD8.o: JTBL_PADS := 0,0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38,+0x58
build/src/ov_SC07_000/ov_SC07_000_jr_8015444C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x70
build/src/ov_SC07_000/ov_SC07_000_jr_80154C24.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x24
build/src/ov_SC07_000/ov_SC07_000_jr_801588CC.o: JTBL_PADS := 0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x28,+0x48
build/src/ov_SC07_000/ov_SC07_000_jr_80159C84.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC07_000/ov_SC07_000_jr_8015AE2C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC07_000/ov_SC07_000_jr_8016AB6C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC07_000/ov_SC07_000_jr_80178D40.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x178
build/src/ov_SC07_000/ov_SC07_000_jr_8017BEBC.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py)
build/src/ov_SC07_000/ov_SC07_000_o0c.o: JTBL_PADS := 0,4,4,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x38,+0xa8,+0x118
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

# --- ov_SC01_004 (location overlay SC01/FILE_004, vram 0x80128158 — onboarded by new_overlay.sh) ---
ov_SC01_004_EXE        := extracted/retail/SC01.CD.dir/FILE_004.dir/0.4.dec
ov_SC01_004_NAME       := ov_SC01_004
ov_SC01_004_OUT_DIR    := build/ov_SC01_004
ov_SC01_004_OUT        := $(ov_SC01_004_OUT_DIR)/$(ov_SC01_004_NAME)
ov_SC01_004_ELF        := $(ov_SC01_004_OUT).elf
ov_SC01_004_MAPFILE    := $(ov_SC01_004_OUT).map
ov_SC01_004_LD_SCRIPT  := $(ov_SC01_004_OUT).ld
ov_SC01_004_SPLAT_YAML := config/splat.ov_SC01_004.yaml
ov_SC01_004_JTBL_INTERLEAVE := --order tail.data.o,ov_SC01_004.o,ov_SC01_004_jr_8012ACE0.o,tail2.data.o,ov_SC01_004_jr_80135888.o,tail3.data.o,ov_SC01_004_jr_80135A4C.o,tail4.data.o,ov_SC01_004_jr_80135D20.o,tail5.data.o,ov_SC01_004_jr_801380E0.o,ov_SC01_004_o0c.o,tail6.data.o,ov_SC01_004_jr_8013F350.o,tail7.data.o,ov_SC01_004_jr_8013FFD8.o,tail8.data.o,ov_SC01_004_jr_80140608.o,tail9.data.o,ov_SC01_004_jr_8015444C.o,ov_SC01_004_jr_80154C24.o,ov_SC01_004_jr_801588CC.o,ov_SC01_004_jr_80159C84.o,tail10.data.o,ov_SC01_004_jr_8015A3C8.o,tail11.data.o,ov_SC01_004_jr_8015AE2C.o,tail12.data.o,ov_SC01_004_jr_8015C32C.o,tail13.data.o,ov_SC01_004_jr_8016AB6C.o,tail14.data.o,ov_SC01_004_jr_80171B4C.o,ov_SC01_004_jr_801734BC.o,tail15.data.o,ov_SC01_004_jr_801789AC.o,ov_SC01_004_jr_80178D40.o,tail16.data.o,ov_SC01_004_jr_8017A4AC.o,tail17.data.o,ov_SC01_004_jr_8017AE2C.o,ov_SC01_004_jr_8017BE9C.o,tail18.data.o,ov_SC01_004_jr_8017E3A0.o,ov_SC01_004_jr_8017E5B8.o,tail19.data.o,trailing.o  # Phase-26 §8 jtbl-rodata carve
build/src/ov_SC01_004/ov_SC01_004.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14
build/src/ov_SC01_004/ov_SC01_004_jr_8012ACE0.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0xcc,+0xe0
build/src/ov_SC01_004/ov_SC01_004_jr_80135D20.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC01_004/ov_SC01_004_jr_8013F350.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC01_004/ov_SC01_004_jr_8013FFD8.o: JTBL_PADS := 0,0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38,+0x58
build/src/ov_SC01_004/ov_SC01_004_jr_8015444C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x70
build/src/ov_SC01_004/ov_SC01_004_jr_80154C24.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x24
build/src/ov_SC01_004/ov_SC01_004_jr_801588CC.o: JTBL_PADS := 0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x28,+0x48
build/src/ov_SC01_004/ov_SC01_004_jr_80159C84.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC01_004/ov_SC01_004_jr_8015AE2C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC01_004/ov_SC01_004_jr_8016AB6C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC01_004/ov_SC01_004_jr_80178D40.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x178
build/src/ov_SC01_004/ov_SC01_004_o0c.o: JTBL_PADS := 0,4,4,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x38,+0xa8,+0x118
ov_SC01_004_CHECK_SHA  := config/check.ov_SC01_004.sha
ov_SC01_004_SYMBOLS    := config/symbols.ov_SC01_004.txt
ov_SC01_004_SIG        := .run/sig.ov_SC01_004.jsonl
ov_SC01_004_GHIDRA_PROG := ov_SC01_004
ov_SC01_004_VRAM_BASE  := 0x80128158
ov_SC01_004_TEXT_LO    := 0x80128158
ov_SC01_004_TEXT_HI    := 0x801903CF
ov_SC01_004_ASM_DIR     := asm/ov_SC01_004
ov_SC01_004_SRC_DIR     := src/ov_SC01_004
ov_SC01_004_UNDEF_SYMS  := build/ov_SC01_004/undefined_syms_auto.txt
ov_SC01_004_UNDEF_FUNCS := build/ov_SC01_004/undefined_funcs_auto.txt

# --- ov_SC01_008 (location overlay SC01/FILE_008, vram 0x80128158 — onboarded by new_overlay.sh) ---
ov_SC01_008_EXE        := extracted/retail/SC01.CD.dir/FILE_008.dir/0.4.dec
ov_SC01_008_NAME       := ov_SC01_008
ov_SC01_008_OUT_DIR    := build/ov_SC01_008
ov_SC01_008_OUT        := $(ov_SC01_008_OUT_DIR)/$(ov_SC01_008_NAME)
ov_SC01_008_ELF        := $(ov_SC01_008_OUT).elf
ov_SC01_008_MAPFILE    := $(ov_SC01_008_OUT).map
ov_SC01_008_LD_SCRIPT  := $(ov_SC01_008_OUT).ld
ov_SC01_008_SPLAT_YAML := config/splat.ov_SC01_008.yaml
ov_SC01_008_JTBL_INTERLEAVE := --order tail.data.o,ov_SC01_008.o,ov_SC01_008_jr_8012ACE0.o,tail2.data.o,ov_SC01_008_jr_80135888.o,tail3.data.o,ov_SC01_008_jr_80135A4C.o,tail4.data.o,ov_SC01_008_jr_80135D20.o,tail5.data.o,ov_SC01_008_jr_801380E0.o,ov_SC01_008_o0c.o,tail6.data.o,ov_SC01_008_jr_8013F350.o,tail7.data.o,ov_SC01_008_jr_8013FFD8.o,tail8.data.o,ov_SC01_008_jr_80140608.o,tail9.data.o,ov_SC01_008_jr_8015444C.o,ov_SC01_008_jr_80154C24.o,ov_SC01_008_jr_801588CC.o,ov_SC01_008_jr_80159C84.o,tail10.data.o,ov_SC01_008_jr_8015A3C8.o,tail11.data.o,ov_SC01_008_jr_8015AE2C.o,tail12.data.o,ov_SC01_008_jr_8015C32C.o,tail13.data.o,ov_SC01_008_jr_8016AB6C.o,tail14.data.o,ov_SC01_008_jr_80171B4C.o,ov_SC01_008_jr_801734BC.o,tail15.data.o,ov_SC01_008_jr_801789AC.o,ov_SC01_008_jr_80178D40.o,tail16.data.o,ov_SC01_008_jr_8017A4AC.o,tail17.data.o,ov_SC01_008_jr_8017AE2C.o,ov_SC01_008_jr_8017BE9C.o,tail18.data.o,ov_SC01_008_jr_8017E4D8.o,ov_SC01_008_jr_8017E6F0.o,tail19.data.o,trailing.o  # Phase-26 §8 jtbl-rodata carve
build/src/ov_SC01_008/ov_SC01_008.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14
build/src/ov_SC01_008/ov_SC01_008_jr_8012ACE0.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0xcc,+0xe0
build/src/ov_SC01_008/ov_SC01_008_jr_80135D20.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC01_008/ov_SC01_008_jr_8013F350.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC01_008/ov_SC01_008_jr_8013FFD8.o: JTBL_PADS := 0,0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38,+0x58
build/src/ov_SC01_008/ov_SC01_008_jr_8015444C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x70
build/src/ov_SC01_008/ov_SC01_008_jr_80154C24.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x24
build/src/ov_SC01_008/ov_SC01_008_jr_801588CC.o: JTBL_PADS := 0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x28,+0x48
build/src/ov_SC01_008/ov_SC01_008_jr_80159C84.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC01_008/ov_SC01_008_jr_8015AE2C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC01_008/ov_SC01_008_jr_8016AB6C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC01_008/ov_SC01_008_jr_80178D40.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x178
build/src/ov_SC01_008/ov_SC01_008_o0c.o: JTBL_PADS := 0,4,4,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x38,+0xa8,+0x118
ov_SC01_008_CHECK_SHA  := config/check.ov_SC01_008.sha
ov_SC01_008_SYMBOLS    := config/symbols.ov_SC01_008.txt
ov_SC01_008_SIG        := .run/sig.ov_SC01_008.jsonl
ov_SC01_008_GHIDRA_PROG := ov_SC01_008
ov_SC01_008_VRAM_BASE  := 0x80128158
ov_SC01_008_TEXT_LO    := 0x80128158
ov_SC01_008_TEXT_HI    := 0x801A35DF
ov_SC01_008_ASM_DIR     := asm/ov_SC01_008
ov_SC01_008_SRC_DIR     := src/ov_SC01_008
ov_SC01_008_UNDEF_SYMS  := build/ov_SC01_008/undefined_syms_auto.txt
ov_SC01_008_UNDEF_FUNCS := build/ov_SC01_008/undefined_funcs_auto.txt

# --- ov_SC01_009 (location overlay SC01/FILE_009, vram 0x80128158 — onboarded by new_overlay.sh) ---
ov_SC01_009_EXE        := extracted/retail/SC01.CD.dir/FILE_009.dir/0.4.dec
ov_SC01_009_NAME       := ov_SC01_009
ov_SC01_009_OUT_DIR    := build/ov_SC01_009
ov_SC01_009_OUT        := $(ov_SC01_009_OUT_DIR)/$(ov_SC01_009_NAME)
ov_SC01_009_ELF        := $(ov_SC01_009_OUT).elf
ov_SC01_009_MAPFILE    := $(ov_SC01_009_OUT).map
ov_SC01_009_LD_SCRIPT  := $(ov_SC01_009_OUT).ld
ov_SC01_009_SPLAT_YAML := config/splat.ov_SC01_009.yaml
ov_SC01_009_JTBL_INTERLEAVE := --order tail.data.o,ov_SC01_009.o,ov_SC01_009_jr_8012ACE0.o,tail2.data.o,ov_SC01_009_jr_80135888.o,tail3.data.o,ov_SC01_009_jr_80135A4C.o,tail4.data.o,ov_SC01_009_jr_80135D20.o,tail5.data.o,ov_SC01_009_jr_801380E0.o,ov_SC01_009_o0c.o,tail6.data.o,ov_SC01_009_jr_8013F350.o,tail7.data.o,ov_SC01_009_jr_8013FFD8.o,tail8.data.o,ov_SC01_009_jr_80140608.o,tail9.data.o,ov_SC01_009_jr_8015444C.o,ov_SC01_009_jr_80154C24.o,ov_SC01_009_jr_801588CC.o,ov_SC01_009_jr_80159C84.o,tail10.data.o,ov_SC01_009_jr_8015A3C8.o,tail11.data.o,ov_SC01_009_jr_8015AE2C.o,tail12.data.o,ov_SC01_009_jr_8015C32C.o,tail13.data.o,ov_SC01_009_jr_8016AB6C.o,tail14.data.o,ov_SC01_009_jr_80171B4C.o,ov_SC01_009_jr_801734BC.o,tail15.data.o,ov_SC01_009_jr_801789AC.o,ov_SC01_009_jr_80178D40.o,tail16.data.o,ov_SC01_009_jr_8017A4AC.o,tail17.data.o,ov_SC01_009_jr_8017AE2C.o,ov_SC01_009_jr_8017BE9C.o,tail18.data.o,ov_SC01_009_jr_8017E378.o,ov_SC01_009_jr_8017E590.o,ov_SC01_009_jr_8018057C.o,tail19.data.o,trailing.o  # Phase-26 §8 jtbl-rodata carve
build/src/ov_SC01_009/ov_SC01_009.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14
build/src/ov_SC01_009/ov_SC01_009_jr_8012ACE0.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0xcc,+0xe0
build/src/ov_SC01_009/ov_SC01_009_jr_80135D20.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC01_009/ov_SC01_009_jr_8013F350.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC01_009/ov_SC01_009_jr_8013FFD8.o: JTBL_PADS := 0,0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38,+0x58
build/src/ov_SC01_009/ov_SC01_009_jr_8015444C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x70
build/src/ov_SC01_009/ov_SC01_009_jr_80154C24.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x24
build/src/ov_SC01_009/ov_SC01_009_jr_801588CC.o: JTBL_PADS := 0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x28,+0x48
build/src/ov_SC01_009/ov_SC01_009_jr_80159C84.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC01_009/ov_SC01_009_jr_8015AE2C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC01_009/ov_SC01_009_jr_8016AB6C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC01_009/ov_SC01_009_jr_80178D40.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x178
build/src/ov_SC01_009/ov_SC01_009_jr_8017E590.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x28
build/src/ov_SC01_009/ov_SC01_009_o0c.o: JTBL_PADS := 0,4,4,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x38,+0xa8,+0x118
ov_SC01_009_CHECK_SHA  := config/check.ov_SC01_009.sha
ov_SC01_009_SYMBOLS    := config/symbols.ov_SC01_009.txt
ov_SC01_009_SIG        := .run/sig.ov_SC01_009.jsonl
ov_SC01_009_GHIDRA_PROG := ov_SC01_009
ov_SC01_009_VRAM_BASE  := 0x80128158
ov_SC01_009_TEXT_LO    := 0x80128158
ov_SC01_009_TEXT_HI    := 0x801F345F
ov_SC01_009_ASM_DIR     := asm/ov_SC01_009
ov_SC01_009_SRC_DIR     := src/ov_SC01_009
ov_SC01_009_UNDEF_SYMS  := build/ov_SC01_009/undefined_syms_auto.txt
ov_SC01_009_UNDEF_FUNCS := build/ov_SC01_009/undefined_funcs_auto.txt

# --- ov_SC01_074 (location overlay SC01/FILE_074, vram 0x80128158 — onboarded by new_overlay.sh) ---
ov_SC01_074_EXE        := extracted/retail/SC01.CD.dir/FILE_074.dir/0.4.dec
ov_SC01_074_NAME       := ov_SC01_074
ov_SC01_074_OUT_DIR    := build/ov_SC01_074
ov_SC01_074_OUT        := $(ov_SC01_074_OUT_DIR)/$(ov_SC01_074_NAME)
ov_SC01_074_ELF        := $(ov_SC01_074_OUT).elf
ov_SC01_074_MAPFILE    := $(ov_SC01_074_OUT).map
ov_SC01_074_LD_SCRIPT  := $(ov_SC01_074_OUT).ld
ov_SC01_074_SPLAT_YAML := config/splat.ov_SC01_074.yaml
ov_SC01_074_JTBL_INTERLEAVE := --order tail.data.o,ov_SC01_074.o,ov_SC01_074_jr_8012ACE0.o,tail2.data.o,ov_SC01_074_jr_80135888.o,tail3.data.o,ov_SC01_074_jr_80135A4C.o,tail4.data.o,ov_SC01_074_jr_80135D20.o,tail5.data.o,ov_SC01_074_jr_801380E0.o,ov_SC01_074_o0c.o,tail6.data.o,ov_SC01_074_jr_8013F350.o,tail7.data.o,ov_SC01_074_jr_8013FFD8.o,tail8.data.o,ov_SC01_074_jr_80140608.o,tail9.data.o,ov_SC01_074_jr_8015444C.o,ov_SC01_074_jr_80154C24.o,ov_SC01_074_jr_801588CC.o,ov_SC01_074_jr_80159C84.o,tail10.data.o,ov_SC01_074_jr_8015A3C8.o,tail11.data.o,ov_SC01_074_jr_8015AE2C.o,tail12.data.o,ov_SC01_074_jr_8015C32C.o,tail13.data.o,ov_SC01_074_jr_8016AB6C.o,tail14.data.o,ov_SC01_074_jr_80171B4C.o,ov_SC01_074_jr_801734BC.o,tail15.data.o,ov_SC01_074_jr_801789AC.o,ov_SC01_074_jr_80178D40.o,tail16.data.o,ov_SC01_074_jr_8017A4AC.o,tail17.data.o,ov_SC01_074_jr_8017AE2C.o,ov_SC01_074_jr_8017BE9C.o,tail18.data.o,trailing.o  # Phase-26 §8 jtbl-rodata carve
build/src/ov_SC01_074/ov_SC01_074.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14
build/src/ov_SC01_074/ov_SC01_074_jr_8012ACE0.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0xcc,+0xe0
build/src/ov_SC01_074/ov_SC01_074_jr_80135D20.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC01_074/ov_SC01_074_jr_8013F350.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC01_074/ov_SC01_074_jr_8013FFD8.o: JTBL_PADS := 0,0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38,+0x58
build/src/ov_SC01_074/ov_SC01_074_jr_8015444C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x70
build/src/ov_SC01_074/ov_SC01_074_jr_80154C24.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x24
build/src/ov_SC01_074/ov_SC01_074_jr_801588CC.o: JTBL_PADS := 0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x28,+0x48
build/src/ov_SC01_074/ov_SC01_074_jr_80159C84.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC01_074/ov_SC01_074_jr_8015AE2C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC01_074/ov_SC01_074_jr_8016AB6C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC01_074/ov_SC01_074_jr_80178D40.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x178
build/src/ov_SC01_074/ov_SC01_074_o0c.o: JTBL_PADS := 0,4,4,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x38,+0xa8,+0x118
ov_SC01_074_CHECK_SHA  := config/check.ov_SC01_074.sha
ov_SC01_074_SYMBOLS    := config/symbols.ov_SC01_074.txt
ov_SC01_074_SIG        := .run/sig.ov_SC01_074.jsonl
ov_SC01_074_GHIDRA_PROG := ov_SC01_074
ov_SC01_074_VRAM_BASE  := 0x80128158
ov_SC01_074_TEXT_LO    := 0x80128158
ov_SC01_074_TEXT_HI    := 0x8019BD6F
ov_SC01_074_ASM_DIR     := asm/ov_SC01_074
ov_SC01_074_SRC_DIR     := src/ov_SC01_074
ov_SC01_074_UNDEF_SYMS  := build/ov_SC01_074/undefined_syms_auto.txt
ov_SC01_074_UNDEF_FUNCS := build/ov_SC01_074/undefined_funcs_auto.txt

# --- ov_SC01_080 (location overlay SC01/FILE_080, vram 0x80128158 — onboarded by new_overlay.sh) ---
ov_SC01_080_EXE        := extracted/retail/SC01.CD.dir/FILE_080.dir/0.4.dec
ov_SC01_080_NAME       := ov_SC01_080
ov_SC01_080_OUT_DIR    := build/ov_SC01_080
ov_SC01_080_OUT        := $(ov_SC01_080_OUT_DIR)/$(ov_SC01_080_NAME)
ov_SC01_080_ELF        := $(ov_SC01_080_OUT).elf
ov_SC01_080_MAPFILE    := $(ov_SC01_080_OUT).map
ov_SC01_080_LD_SCRIPT  := $(ov_SC01_080_OUT).ld
ov_SC01_080_SPLAT_YAML := config/splat.ov_SC01_080.yaml
ov_SC01_080_JTBL_INTERLEAVE := --order tail.data.o,ov_SC01_080.o,ov_SC01_080_jr_8012ACE0.o,tail2.data.o,ov_SC01_080_jr_80135888.o,tail3.data.o,ov_SC01_080_jr_80135A4C.o,tail4.data.o,ov_SC01_080_jr_80135D20.o,tail5.data.o,ov_SC01_080_jr_801380E0.o,ov_SC01_080_o0c.o,tail6.data.o,ov_SC01_080_jr_8013F350.o,tail7.data.o,ov_SC01_080_jr_8013FFD8.o,tail8.data.o,ov_SC01_080_jr_80140608.o,tail9.data.o,ov_SC01_080_jr_8015444C.o,ov_SC01_080_jr_80154C24.o,ov_SC01_080_jr_801588CC.o,ov_SC01_080_jr_80159C84.o,tail10.data.o,ov_SC01_080_jr_8015A3C8.o,tail11.data.o,ov_SC01_080_jr_8015AE2C.o,tail12.data.o,ov_SC01_080_jr_8015C32C.o,tail13.data.o,ov_SC01_080_jr_8016AB6C.o,tail14.data.o,ov_SC01_080_jr_80171B4C.o,ov_SC01_080_jr_801734BC.o,tail15.data.o,ov_SC01_080_jr_801789AC.o,ov_SC01_080_jr_80178D40.o,tail16.data.o,ov_SC01_080_jr_8017A4AC.o,tail17.data.o,ov_SC01_080_jr_8017AE2C.o,tail18.data.o,trailing.o  # Phase-26 §8 jtbl-rodata carve
build/src/ov_SC01_080/ov_SC01_080.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14
build/src/ov_SC01_080/ov_SC01_080_jr_8012ACE0.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0xcc,+0xe0
build/src/ov_SC01_080/ov_SC01_080_jr_80135D20.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC01_080/ov_SC01_080_jr_8013F350.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC01_080/ov_SC01_080_jr_8013FFD8.o: JTBL_PADS := 0,0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38,+0x58
build/src/ov_SC01_080/ov_SC01_080_jr_8015444C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x70
build/src/ov_SC01_080/ov_SC01_080_jr_80154C24.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x24
build/src/ov_SC01_080/ov_SC01_080_jr_801588CC.o: JTBL_PADS := 0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x28,+0x48
build/src/ov_SC01_080/ov_SC01_080_jr_80159C84.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC01_080/ov_SC01_080_jr_8015AE2C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC01_080/ov_SC01_080_jr_8016AB6C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC01_080/ov_SC01_080_jr_80178D40.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x178
build/src/ov_SC01_080/ov_SC01_080_jr_8017AE2C.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14,+0x34
build/src/ov_SC01_080/ov_SC01_080_o0c.o: JTBL_PADS := 0,4,4,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x38,+0xa8,+0x118
ov_SC01_080_CHECK_SHA  := config/check.ov_SC01_080.sha
ov_SC01_080_SYMBOLS    := config/symbols.ov_SC01_080.txt
ov_SC01_080_SIG        := .run/sig.ov_SC01_080.jsonl
ov_SC01_080_GHIDRA_PROG := ov_SC01_080
ov_SC01_080_VRAM_BASE  := 0x80128158
ov_SC01_080_TEXT_LO    := 0x80128158
ov_SC01_080_TEXT_HI    := 0x801C7F4F
ov_SC01_080_ASM_DIR     := asm/ov_SC01_080
ov_SC01_080_SRC_DIR     := src/ov_SC01_080
ov_SC01_080_UNDEF_SYMS  := build/ov_SC01_080/undefined_syms_auto.txt
ov_SC01_080_UNDEF_FUNCS := build/ov_SC01_080/undefined_funcs_auto.txt

# --- ov_SC01_084 (location overlay SC01/FILE_084, vram 0x80128158 — onboarded by new_overlay.sh) ---
ov_SC01_084_EXE        := extracted/retail/SC01.CD.dir/FILE_084.dir/0.4.dec
ov_SC01_084_NAME       := ov_SC01_084
ov_SC01_084_OUT_DIR    := build/ov_SC01_084
ov_SC01_084_OUT        := $(ov_SC01_084_OUT_DIR)/$(ov_SC01_084_NAME)
ov_SC01_084_ELF        := $(ov_SC01_084_OUT).elf
ov_SC01_084_MAPFILE    := $(ov_SC01_084_OUT).map
ov_SC01_084_LD_SCRIPT  := $(ov_SC01_084_OUT).ld
ov_SC01_084_SPLAT_YAML := config/splat.ov_SC01_084.yaml
ov_SC01_084_JTBL_INTERLEAVE := --order tail.data.o,ov_SC01_084.o,ov_SC01_084_jr_8012ACE0.o,tail2.data.o,ov_SC01_084_jr_80135888.o,tail3.data.o,ov_SC01_084_jr_80135A4C.o,tail4.data.o,ov_SC01_084_jr_80135D20.o,tail5.data.o,ov_SC01_084_jr_801380E0.o,ov_SC01_084_o0c.o,tail6.data.o,ov_SC01_084_jr_8013F350.o,tail7.data.o,ov_SC01_084_jr_8013FFD8.o,tail8.data.o,ov_SC01_084_jr_80140608.o,tail9.data.o,ov_SC01_084_jr_8015444C.o,ov_SC01_084_jr_80154C24.o,ov_SC01_084_jr_801588CC.o,ov_SC01_084_jr_80159C84.o,tail10.data.o,ov_SC01_084_jr_8015A3C8.o,tail11.data.o,ov_SC01_084_jr_8015AE2C.o,tail12.data.o,ov_SC01_084_jr_8015C32C.o,tail13.data.o,ov_SC01_084_jr_8016AB6C.o,tail14.data.o,ov_SC01_084_jr_80171B4C.o,ov_SC01_084_jr_801734BC.o,tail15.data.o,ov_SC01_084_jr_801789AC.o,ov_SC01_084_jr_80178D40.o,tail16.data.o,ov_SC01_084_jr_8017A4AC.o,tail17.data.o,ov_SC01_084_jr_8017AE2C.o,ov_SC01_084_jr_8017CA80.o,tail18.data.o,ov_SC01_084_jr_8017F690.o,tail19.data.o,trailing.o  # Phase-26 §8 jtbl-rodata carve
build/src/ov_SC01_084/ov_SC01_084.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14
build/src/ov_SC01_084/ov_SC01_084_jr_8012ACE0.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0xcc,+0xe0
build/src/ov_SC01_084/ov_SC01_084_jr_80135D20.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC01_084/ov_SC01_084_jr_8013F350.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC01_084/ov_SC01_084_jr_8013FFD8.o: JTBL_PADS := 0,0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38,+0x58
build/src/ov_SC01_084/ov_SC01_084_jr_8015444C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x70
build/src/ov_SC01_084/ov_SC01_084_jr_80154C24.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x24
build/src/ov_SC01_084/ov_SC01_084_jr_801588CC.o: JTBL_PADS := 0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x28,+0x48
build/src/ov_SC01_084/ov_SC01_084_jr_80159C84.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC01_084/ov_SC01_084_jr_8015AE2C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC01_084/ov_SC01_084_jr_8016AB6C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC01_084/ov_SC01_084_jr_80178D40.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x178
build/src/ov_SC01_084/ov_SC01_084_jr_8017CA80.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC01_084/ov_SC01_084_jr_8017F690.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14
build/src/ov_SC01_084/ov_SC01_084_o0c.o: JTBL_PADS := 0,4,4,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x38,+0xa8,+0x118
ov_SC01_084_CHECK_SHA  := config/check.ov_SC01_084.sha
ov_SC01_084_SYMBOLS    := config/symbols.ov_SC01_084.txt
ov_SC01_084_SIG        := .run/sig.ov_SC01_084.jsonl
ov_SC01_084_GHIDRA_PROG := ov_SC01_084
ov_SC01_084_VRAM_BASE  := 0x80128158
ov_SC01_084_TEXT_LO    := 0x80128158
ov_SC01_084_TEXT_HI    := 0x801C7BF7
ov_SC01_084_ASM_DIR     := asm/ov_SC01_084
ov_SC01_084_SRC_DIR     := src/ov_SC01_084
ov_SC01_084_UNDEF_SYMS  := build/ov_SC01_084/undefined_syms_auto.txt
ov_SC01_084_UNDEF_FUNCS := build/ov_SC01_084/undefined_funcs_auto.txt

# --- ov_SC02_004 (location overlay SC02/FILE_004, vram 0x80128158 — onboarded by new_overlay.sh) ---
ov_SC02_004_EXE        := extracted/retail/SC02.CD.dir/FILE_004.dir/0.4.dec
ov_SC02_004_NAME       := ov_SC02_004
ov_SC02_004_OUT_DIR    := build/ov_SC02_004
ov_SC02_004_OUT        := $(ov_SC02_004_OUT_DIR)/$(ov_SC02_004_NAME)
ov_SC02_004_ELF        := $(ov_SC02_004_OUT).elf
ov_SC02_004_MAPFILE    := $(ov_SC02_004_OUT).map
ov_SC02_004_LD_SCRIPT  := $(ov_SC02_004_OUT).ld
ov_SC02_004_SPLAT_YAML := config/splat.ov_SC02_004.yaml
ov_SC02_004_JTBL_INTERLEAVE := --order tail.data.o,ov_SC02_004.o,ov_SC02_004_jr_8012ACE0.o,tail2.data.o,ov_SC02_004_jr_80135888.o,tail3.data.o,ov_SC02_004_jr_80135A4C.o,tail4.data.o,ov_SC02_004_jr_80135D20.o,tail5.data.o,ov_SC02_004_jr_801380E0.o,ov_SC02_004_o0c.o,tail6.data.o,ov_SC02_004_jr_8013F350.o,tail7.data.o,ov_SC02_004_jr_8013FFD8.o,tail8.data.o,ov_SC02_004_jr_80140608.o,tail9.data.o,ov_SC02_004_jr_8015444C.o,ov_SC02_004_jr_80154C24.o,ov_SC02_004_jr_801588CC.o,ov_SC02_004_jr_80159C84.o,tail10.data.o,ov_SC02_004_jr_8015A3C8.o,tail11.data.o,ov_SC02_004_jr_8015AE2C.o,tail12.data.o,ov_SC02_004_jr_8015C32C.o,tail13.data.o,ov_SC02_004_jr_8016AB6C.o,tail14.data.o,ov_SC02_004_jr_80171B4C.o,ov_SC02_004_jr_801734BC.o,tail15.data.o,ov_SC02_004_jr_801789AC.o,ov_SC02_004_jr_80178D40.o,tail16.data.o,ov_SC02_004_jr_8017A4AC.o,tail17.data.o,ov_SC02_004_jr_8017AE2C.o,tail18.data.o,trailing.o  # Phase-26 §8 jtbl-rodata carve
build/src/ov_SC02_004/ov_SC02_004.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14
build/src/ov_SC02_004/ov_SC02_004_jr_8012ACE0.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0xcc,+0xe0
build/src/ov_SC02_004/ov_SC02_004_jr_80135D20.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC02_004/ov_SC02_004_jr_8013F350.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC02_004/ov_SC02_004_jr_8013FFD8.o: JTBL_PADS := 0,0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38,+0x58
build/src/ov_SC02_004/ov_SC02_004_jr_8015444C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x70
build/src/ov_SC02_004/ov_SC02_004_jr_80154C24.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x24
build/src/ov_SC02_004/ov_SC02_004_jr_801588CC.o: JTBL_PADS := 0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x28,+0x48
build/src/ov_SC02_004/ov_SC02_004_jr_80159C84.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC02_004/ov_SC02_004_jr_8015AE2C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC02_004/ov_SC02_004_jr_8016AB6C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC02_004/ov_SC02_004_jr_80178D40.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x178
build/src/ov_SC02_004/ov_SC02_004_jr_8017AE2C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14
build/src/ov_SC02_004/ov_SC02_004_o0c.o: JTBL_PADS := 0,4,4,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x38,+0xa8,+0x118
ov_SC02_004_CHECK_SHA  := config/check.ov_SC02_004.sha
ov_SC02_004_SYMBOLS    := config/symbols.ov_SC02_004.txt
ov_SC02_004_SIG        := .run/sig.ov_SC02_004.jsonl
ov_SC02_004_GHIDRA_PROG := ov_SC02_004
ov_SC02_004_VRAM_BASE  := 0x80128158
ov_SC02_004_TEXT_LO    := 0x80128158
ov_SC02_004_TEXT_HI    := 0x801963C7
ov_SC02_004_ASM_DIR     := asm/ov_SC02_004
ov_SC02_004_SRC_DIR     := src/ov_SC02_004
ov_SC02_004_UNDEF_SYMS  := build/ov_SC02_004/undefined_syms_auto.txt
ov_SC02_004_UNDEF_FUNCS := build/ov_SC02_004/undefined_funcs_auto.txt

# --- ov_SC02_005 (location overlay SC02/FILE_005, vram 0x80128158 — onboarded by new_overlay.sh) ---
ov_SC02_005_EXE        := extracted/retail/SC02.CD.dir/FILE_005.dir/0.4.dec
ov_SC02_005_NAME       := ov_SC02_005
ov_SC02_005_OUT_DIR    := build/ov_SC02_005
ov_SC02_005_OUT        := $(ov_SC02_005_OUT_DIR)/$(ov_SC02_005_NAME)
ov_SC02_005_ELF        := $(ov_SC02_005_OUT).elf
ov_SC02_005_MAPFILE    := $(ov_SC02_005_OUT).map
ov_SC02_005_LD_SCRIPT  := $(ov_SC02_005_OUT).ld
ov_SC02_005_SPLAT_YAML := config/splat.ov_SC02_005.yaml
ov_SC02_005_JTBL_INTERLEAVE := --order tail.data.o,ov_SC02_005.o,ov_SC02_005_jr_8012ACE0.o,tail2.data.o,ov_SC02_005_jr_80135888.o,tail3.data.o,ov_SC02_005_jr_80135A4C.o,tail4.data.o,ov_SC02_005_jr_80135D20.o,tail5.data.o,ov_SC02_005_jr_801380E0.o,ov_SC02_005_o0c.o,tail6.data.o,ov_SC02_005_jr_8013F350.o,tail7.data.o,ov_SC02_005_jr_8013FFD8.o,tail8.data.o,ov_SC02_005_jr_80140608.o,tail9.data.o,ov_SC02_005_jr_8015444C.o,ov_SC02_005_jr_80154C24.o,ov_SC02_005_jr_801588CC.o,ov_SC02_005_jr_80159C84.o,tail10.data.o,ov_SC02_005_jr_8015A3C8.o,tail11.data.o,ov_SC02_005_jr_8015AE2C.o,tail12.data.o,ov_SC02_005_jr_8015C32C.o,tail13.data.o,ov_SC02_005_jr_8016AB6C.o,tail14.data.o,ov_SC02_005_jr_80171B4C.o,ov_SC02_005_jr_801734BC.o,tail15.data.o,ov_SC02_005_jr_801789AC.o,ov_SC02_005_jr_80178D40.o,tail16.data.o,ov_SC02_005_jr_8017A4AC.o,tail17.data.o,ov_SC02_005_jr_8017AE2C.o,tail18.data.o,ov_SC02_005_jr_8017CF90.o,tail19.data.o,ov_SC02_005_jr_80181984.o,ov_SC02_005_jr_80181D30.o,tail20.data.o,ov_SC02_005_jr_8018EA04.o,tail21.data.o,trailing.o  # Phase-26 §8 jtbl-rodata carve
build/src/ov_SC02_005/ov_SC02_005.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14
build/src/ov_SC02_005/ov_SC02_005_jr_8012ACE0.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0xcc,+0xe0
build/src/ov_SC02_005/ov_SC02_005_jr_80135D20.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC02_005/ov_SC02_005_jr_8013F350.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC02_005/ov_SC02_005_jr_8013FFD8.o: JTBL_PADS := 0,0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38,+0x58
build/src/ov_SC02_005/ov_SC02_005_jr_8015444C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x70
build/src/ov_SC02_005/ov_SC02_005_jr_80154C24.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x24
build/src/ov_SC02_005/ov_SC02_005_jr_801588CC.o: JTBL_PADS := 0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x28,+0x48
build/src/ov_SC02_005/ov_SC02_005_jr_80159C84.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC02_005/ov_SC02_005_jr_8015AE2C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC02_005/ov_SC02_005_jr_8016AB6C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC02_005/ov_SC02_005_jr_80178D40.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x178
build/src/ov_SC02_005/ov_SC02_005_o0c.o: JTBL_PADS := 0,4,4,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x38,+0xa8,+0x118
ov_SC02_005_CHECK_SHA  := config/check.ov_SC02_005.sha
ov_SC02_005_SYMBOLS    := config/symbols.ov_SC02_005.txt
ov_SC02_005_SIG        := .run/sig.ov_SC02_005.jsonl
ov_SC02_005_GHIDRA_PROG := ov_SC02_005
ov_SC02_005_VRAM_BASE  := 0x80128158
ov_SC02_005_TEXT_LO    := 0x80128158
ov_SC02_005_TEXT_HI    := 0x801E4C59
ov_SC02_005_ASM_DIR     := asm/ov_SC02_005
ov_SC02_005_SRC_DIR     := src/ov_SC02_005
ov_SC02_005_UNDEF_SYMS  := build/ov_SC02_005/undefined_syms_auto.txt
ov_SC02_005_UNDEF_FUNCS := build/ov_SC02_005/undefined_funcs_auto.txt

# --- ov_SC02_011 (location overlay SC02/FILE_011, vram 0x80128158 — onboarded by new_overlay.sh) ---
ov_SC02_011_EXE        := extracted/retail/SC02.CD.dir/FILE_011.dir/0.4.dec
ov_SC02_011_NAME       := ov_SC02_011
ov_SC02_011_OUT_DIR    := build/ov_SC02_011
ov_SC02_011_OUT        := $(ov_SC02_011_OUT_DIR)/$(ov_SC02_011_NAME)
ov_SC02_011_ELF        := $(ov_SC02_011_OUT).elf
ov_SC02_011_MAPFILE    := $(ov_SC02_011_OUT).map
ov_SC02_011_LD_SCRIPT  := $(ov_SC02_011_OUT).ld
ov_SC02_011_SPLAT_YAML := config/splat.ov_SC02_011.yaml
ov_SC02_011_JTBL_INTERLEAVE := --order tail.data.o,ov_SC02_011.o,ov_SC02_011_jr_8012ACE0.o,tail2.data.o,ov_SC02_011_jr_80135888.o,tail3.data.o,ov_SC02_011_jr_80135A4C.o,tail4.data.o,ov_SC02_011_jr_80135D20.o,tail5.data.o,ov_SC02_011_jr_801380E0.o,ov_SC02_011_o0c.o,tail6.data.o,ov_SC02_011_jr_8013F350.o,tail7.data.o,ov_SC02_011_jr_8013FFD8.o,tail8.data.o,ov_SC02_011_jr_80140608.o,tail9.data.o,ov_SC02_011_jr_8015444C.o,ov_SC02_011_jr_80154C24.o,ov_SC02_011_jr_801588CC.o,ov_SC02_011_jr_80159C84.o,tail10.data.o,ov_SC02_011_jr_8015A3C8.o,tail11.data.o,ov_SC02_011_jr_8015AE2C.o,tail12.data.o,ov_SC02_011_jr_8015C32C.o,tail13.data.o,ov_SC02_011_jr_8016AB6C.o,tail14.data.o,ov_SC02_011_jr_80171B4C.o,ov_SC02_011_jr_801734BC.o,tail15.data.o,ov_SC02_011_jr_801789AC.o,ov_SC02_011_jr_80178D40.o,tail16.data.o,ov_SC02_011_jr_8017A4AC.o,tail17.data.o,ov_SC02_011_jr_8017AE2C.o,tail18.data.o,trailing.o  # Phase-26 §8 jtbl-rodata carve
build/src/ov_SC02_011/ov_SC02_011.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14
build/src/ov_SC02_011/ov_SC02_011_jr_8012ACE0.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0xcc,+0xe0
build/src/ov_SC02_011/ov_SC02_011_jr_80135D20.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC02_011/ov_SC02_011_jr_8013F350.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC02_011/ov_SC02_011_jr_8013FFD8.o: JTBL_PADS := 0,0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38,+0x58
build/src/ov_SC02_011/ov_SC02_011_jr_8015444C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x70
build/src/ov_SC02_011/ov_SC02_011_jr_80154C24.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x24
build/src/ov_SC02_011/ov_SC02_011_jr_801588CC.o: JTBL_PADS := 0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x28,+0x48
build/src/ov_SC02_011/ov_SC02_011_jr_80159C84.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC02_011/ov_SC02_011_jr_8015AE2C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC02_011/ov_SC02_011_jr_8016AB6C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC02_011/ov_SC02_011_jr_80178D40.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x178
build/src/ov_SC02_011/ov_SC02_011_jr_8017AE2C.o: JTBL_PADS := 0,0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14,+0x2c
build/src/ov_SC02_011/ov_SC02_011_o0c.o: JTBL_PADS := 0,4,4,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x38,+0xa8,+0x118
ov_SC02_011_CHECK_SHA  := config/check.ov_SC02_011.sha
ov_SC02_011_SYMBOLS    := config/symbols.ov_SC02_011.txt
ov_SC02_011_SIG        := .run/sig.ov_SC02_011.jsonl
ov_SC02_011_GHIDRA_PROG := ov_SC02_011
ov_SC02_011_VRAM_BASE  := 0x80128158
ov_SC02_011_TEXT_LO    := 0x80128158
ov_SC02_011_TEXT_HI    := 0x801EBA7F
ov_SC02_011_ASM_DIR     := asm/ov_SC02_011
ov_SC02_011_SRC_DIR     := src/ov_SC02_011
ov_SC02_011_UNDEF_SYMS  := build/ov_SC02_011/undefined_syms_auto.txt
ov_SC02_011_UNDEF_FUNCS := build/ov_SC02_011/undefined_funcs_auto.txt

# --- ov_SC02_015 (location overlay SC02/FILE_015, vram 0x80128158 — onboarded by new_overlay.sh) ---
ov_SC02_015_EXE        := extracted/retail/SC02.CD.dir/FILE_015.dir/0.4.dec
ov_SC02_015_NAME       := ov_SC02_015
ov_SC02_015_OUT_DIR    := build/ov_SC02_015
ov_SC02_015_OUT        := $(ov_SC02_015_OUT_DIR)/$(ov_SC02_015_NAME)
ov_SC02_015_ELF        := $(ov_SC02_015_OUT).elf
ov_SC02_015_MAPFILE    := $(ov_SC02_015_OUT).map
ov_SC02_015_LD_SCRIPT  := $(ov_SC02_015_OUT).ld
ov_SC02_015_SPLAT_YAML := config/splat.ov_SC02_015.yaml
ov_SC02_015_JTBL_INTERLEAVE := --order tail.data.o,ov_SC02_015.o,ov_SC02_015_jr_8012ACE0.o,tail2.data.o,ov_SC02_015_jr_80135888.o,tail3.data.o,ov_SC02_015_jr_80135A4C.o,tail4.data.o,ov_SC02_015_jr_80135D20.o,tail5.data.o,ov_SC02_015_jr_801380E0.o,ov_SC02_015_o0c.o,tail6.data.o,ov_SC02_015_jr_8013F350.o,tail7.data.o,ov_SC02_015_jr_8013FFD8.o,tail8.data.o,ov_SC02_015_jr_80140608.o,tail9.data.o,ov_SC02_015_jr_8015444C.o,ov_SC02_015_jr_80154C24.o,ov_SC02_015_jr_801588CC.o,ov_SC02_015_jr_80159C84.o,tail10.data.o,ov_SC02_015_jr_8015A3C8.o,tail11.data.o,ov_SC02_015_jr_8015AE2C.o,tail12.data.o,ov_SC02_015_jr_8015C32C.o,tail13.data.o,ov_SC02_015_jr_8016AB6C.o,tail14.data.o,ov_SC02_015_jr_80171B4C.o,ov_SC02_015_jr_801734BC.o,tail15.data.o,ov_SC02_015_jr_801789AC.o,ov_SC02_015_jr_80178D40.o,tail16.data.o,ov_SC02_015_jr_8017A4AC.o,tail17.data.o,ov_SC02_015_jr_8017AE2C.o,tail18.data.o,trailing.o  # Phase-26 §8 jtbl-rodata carve
build/src/ov_SC02_015/ov_SC02_015.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14
build/src/ov_SC02_015/ov_SC02_015_jr_8012ACE0.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0xcc,+0xe0
build/src/ov_SC02_015/ov_SC02_015_jr_80135D20.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC02_015/ov_SC02_015_jr_8013F350.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC02_015/ov_SC02_015_jr_8013FFD8.o: JTBL_PADS := 0,0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38,+0x58
build/src/ov_SC02_015/ov_SC02_015_jr_8015444C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x70
build/src/ov_SC02_015/ov_SC02_015_jr_80154C24.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x24
build/src/ov_SC02_015/ov_SC02_015_jr_801588CC.o: JTBL_PADS := 0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x28,+0x48
build/src/ov_SC02_015/ov_SC02_015_jr_80159C84.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC02_015/ov_SC02_015_jr_8015AE2C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC02_015/ov_SC02_015_jr_8016AB6C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC02_015/ov_SC02_015_jr_80178D40.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x178
build/src/ov_SC02_015/ov_SC02_015_jr_8017AE2C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14
build/src/ov_SC02_015/ov_SC02_015_o0c.o: JTBL_PADS := 0,4,4,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x38,+0xa8,+0x118
ov_SC02_015_CHECK_SHA  := config/check.ov_SC02_015.sha
ov_SC02_015_SYMBOLS    := config/symbols.ov_SC02_015.txt
ov_SC02_015_SIG        := .run/sig.ov_SC02_015.jsonl
ov_SC02_015_GHIDRA_PROG := ov_SC02_015
ov_SC02_015_VRAM_BASE  := 0x80128158
ov_SC02_015_TEXT_LO    := 0x80128158
ov_SC02_015_TEXT_HI    := 0x8019069F
ov_SC02_015_ASM_DIR     := asm/ov_SC02_015
ov_SC02_015_SRC_DIR     := src/ov_SC02_015
ov_SC02_015_UNDEF_SYMS  := build/ov_SC02_015/undefined_syms_auto.txt
ov_SC02_015_UNDEF_FUNCS := build/ov_SC02_015/undefined_funcs_auto.txt

# --- ov_SC02_016 (location overlay SC02/FILE_016, vram 0x80128158 — onboarded by new_overlay.sh) ---
ov_SC02_016_EXE        := extracted/retail/SC02.CD.dir/FILE_016.dir/0.4.dec
ov_SC02_016_NAME       := ov_SC02_016
ov_SC02_016_OUT_DIR    := build/ov_SC02_016
ov_SC02_016_OUT        := $(ov_SC02_016_OUT_DIR)/$(ov_SC02_016_NAME)
ov_SC02_016_ELF        := $(ov_SC02_016_OUT).elf
ov_SC02_016_MAPFILE    := $(ov_SC02_016_OUT).map
ov_SC02_016_LD_SCRIPT  := $(ov_SC02_016_OUT).ld
ov_SC02_016_SPLAT_YAML := config/splat.ov_SC02_016.yaml
ov_SC02_016_JTBL_INTERLEAVE := --order tail.data.o,ov_SC02_016.o,ov_SC02_016_jr_8012ACE0.o,tail2.data.o,ov_SC02_016_jr_80135888.o,tail3.data.o,ov_SC02_016_jr_80135A4C.o,tail4.data.o,ov_SC02_016_jr_80135D20.o,tail5.data.o,ov_SC02_016_jr_801380E0.o,ov_SC02_016_o0c.o,tail6.data.o,ov_SC02_016_jr_8013F350.o,tail7.data.o,ov_SC02_016_jr_8013FFD8.o,tail8.data.o,ov_SC02_016_jr_80140608.o,tail9.data.o,ov_SC02_016_jr_8015444C.o,ov_SC02_016_jr_80154C24.o,ov_SC02_016_jr_801588CC.o,ov_SC02_016_jr_80159C84.o,tail10.data.o,ov_SC02_016_jr_8015A3C8.o,tail11.data.o,ov_SC02_016_jr_8015AE2C.o,tail12.data.o,ov_SC02_016_jr_8015C32C.o,tail13.data.o,ov_SC02_016_jr_8016AB6C.o,tail14.data.o,ov_SC02_016_jr_80171B4C.o,ov_SC02_016_jr_801734BC.o,tail15.data.o,ov_SC02_016_jr_801789AC.o,ov_SC02_016_jr_80178D40.o,tail16.data.o,ov_SC02_016_jr_8017A4AC.o,tail17.data.o,ov_SC02_016_jr_8017AE2C.o,ov_SC02_016_jr_8017DC70.o,tail18.data.o,ov_SC02_016_jr_801810C8.o,tail19.data.o,trailing.o  # Phase-26 §8 jtbl-rodata carve
build/src/ov_SC02_016/ov_SC02_016.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14
build/src/ov_SC02_016/ov_SC02_016_jr_8012ACE0.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0xcc,+0xe0
build/src/ov_SC02_016/ov_SC02_016_jr_80135D20.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC02_016/ov_SC02_016_jr_8013F350.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC02_016/ov_SC02_016_jr_8013FFD8.o: JTBL_PADS := 0,0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38,+0x58
build/src/ov_SC02_016/ov_SC02_016_jr_8015444C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x70
build/src/ov_SC02_016/ov_SC02_016_jr_80154C24.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x24
build/src/ov_SC02_016/ov_SC02_016_jr_801588CC.o: JTBL_PADS := 0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x28,+0x48
build/src/ov_SC02_016/ov_SC02_016_jr_80159C84.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC02_016/ov_SC02_016_jr_8015AE2C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC02_016/ov_SC02_016_jr_8016AB6C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC02_016/ov_SC02_016_jr_80178D40.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x178
build/src/ov_SC02_016/ov_SC02_016_jr_801810C8.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC02_016/ov_SC02_016_o0c.o: JTBL_PADS := 0,4,4,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x38,+0xa8,+0x118
ov_SC02_016_CHECK_SHA  := config/check.ov_SC02_016.sha
ov_SC02_016_SYMBOLS    := config/symbols.ov_SC02_016.txt
ov_SC02_016_SIG        := .run/sig.ov_SC02_016.jsonl
ov_SC02_016_GHIDRA_PROG := ov_SC02_016
ov_SC02_016_VRAM_BASE  := 0x80128158
ov_SC02_016_TEXT_LO    := 0x80128158
ov_SC02_016_TEXT_HI    := 0x801B4AD7
ov_SC02_016_ASM_DIR     := asm/ov_SC02_016
ov_SC02_016_SRC_DIR     := src/ov_SC02_016
ov_SC02_016_UNDEF_SYMS  := build/ov_SC02_016/undefined_syms_auto.txt
ov_SC02_016_UNDEF_FUNCS := build/ov_SC02_016/undefined_funcs_auto.txt

# --- ov_SC02_017 (location overlay SC02/FILE_017, vram 0x80128158 — onboarded by new_overlay.sh) ---
ov_SC02_017_EXE        := extracted/retail/SC02.CD.dir/FILE_017.dir/0.4.dec
ov_SC02_017_NAME       := ov_SC02_017
ov_SC02_017_OUT_DIR    := build/ov_SC02_017
ov_SC02_017_OUT        := $(ov_SC02_017_OUT_DIR)/$(ov_SC02_017_NAME)
ov_SC02_017_ELF        := $(ov_SC02_017_OUT).elf
ov_SC02_017_MAPFILE    := $(ov_SC02_017_OUT).map
ov_SC02_017_LD_SCRIPT  := $(ov_SC02_017_OUT).ld
ov_SC02_017_SPLAT_YAML := config/splat.ov_SC02_017.yaml
ov_SC02_017_JTBL_INTERLEAVE := --order tail.data.o,ov_SC02_017.o,ov_SC02_017_jr_8012ACE0.o,tail2.data.o,ov_SC02_017_jr_80135888.o,tail3.data.o,ov_SC02_017_jr_80135A4C.o,tail4.data.o,ov_SC02_017_jr_80135D20.o,tail5.data.o,ov_SC02_017_jr_801380E0.o,ov_SC02_017_o0c.o,tail6.data.o,ov_SC02_017_jr_8013F350.o,tail7.data.o,ov_SC02_017_jr_8013FFD8.o,tail8.data.o,ov_SC02_017_jr_80140608.o,tail9.data.o,ov_SC02_017_jr_8015444C.o,ov_SC02_017_jr_80154C24.o,ov_SC02_017_jr_801588CC.o,ov_SC02_017_jr_80159C84.o,tail10.data.o,ov_SC02_017_jr_8015A3C8.o,tail11.data.o,ov_SC02_017_jr_8015AE2C.o,tail12.data.o,ov_SC02_017_jr_8015C32C.o,tail13.data.o,ov_SC02_017_jr_8016AB6C.o,tail14.data.o,ov_SC02_017_jr_80171B4C.o,ov_SC02_017_jr_801734BC.o,tail15.data.o,ov_SC02_017_jr_801789AC.o,ov_SC02_017_jr_80178D40.o,tail16.data.o,ov_SC02_017_jr_8017A4AC.o,tail17.data.o,ov_SC02_017_jr_8017AE2C.o,ov_SC02_017_jr_8017DF34.o,tail18.data.o,trailing.o  # Phase-26 §8 jtbl-rodata carve
build/src/ov_SC02_017/ov_SC02_017.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14
build/src/ov_SC02_017/ov_SC02_017_jr_8012ACE0.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0xcc,+0xe0
build/src/ov_SC02_017/ov_SC02_017_jr_80135D20.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC02_017/ov_SC02_017_jr_8013F350.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC02_017/ov_SC02_017_jr_8013FFD8.o: JTBL_PADS := 0,0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38,+0x58
build/src/ov_SC02_017/ov_SC02_017_jr_8015444C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x70
build/src/ov_SC02_017/ov_SC02_017_jr_80154C24.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x24
build/src/ov_SC02_017/ov_SC02_017_jr_801588CC.o: JTBL_PADS := 0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x28,+0x48
build/src/ov_SC02_017/ov_SC02_017_jr_80159C84.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC02_017/ov_SC02_017_jr_8015AE2C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC02_017/ov_SC02_017_jr_8016AB6C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC02_017/ov_SC02_017_jr_80178D40.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x178
build/src/ov_SC02_017/ov_SC02_017_o0c.o: JTBL_PADS := 0,4,4,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x38,+0xa8,+0x118
ov_SC02_017_CHECK_SHA  := config/check.ov_SC02_017.sha
ov_SC02_017_SYMBOLS    := config/symbols.ov_SC02_017.txt
ov_SC02_017_SIG        := .run/sig.ov_SC02_017.jsonl
ov_SC02_017_GHIDRA_PROG := ov_SC02_017
ov_SC02_017_VRAM_BASE  := 0x80128158
ov_SC02_017_TEXT_LO    := 0x80128158
ov_SC02_017_TEXT_HI    := 0x801EFD37
ov_SC02_017_ASM_DIR     := asm/ov_SC02_017
ov_SC02_017_SRC_DIR     := src/ov_SC02_017
ov_SC02_017_UNDEF_SYMS  := build/ov_SC02_017/undefined_syms_auto.txt
ov_SC02_017_UNDEF_FUNCS := build/ov_SC02_017/undefined_funcs_auto.txt

# --- ov_SC02_021 (location overlay SC02/FILE_021, vram 0x80128158 — onboarded by new_overlay.sh) ---
ov_SC02_021_EXE        := extracted/retail/SC02.CD.dir/FILE_021.dir/0.4.dec
ov_SC02_021_NAME       := ov_SC02_021
ov_SC02_021_OUT_DIR    := build/ov_SC02_021
ov_SC02_021_OUT        := $(ov_SC02_021_OUT_DIR)/$(ov_SC02_021_NAME)
ov_SC02_021_ELF        := $(ov_SC02_021_OUT).elf
ov_SC02_021_MAPFILE    := $(ov_SC02_021_OUT).map
ov_SC02_021_LD_SCRIPT  := $(ov_SC02_021_OUT).ld
ov_SC02_021_SPLAT_YAML := config/splat.ov_SC02_021.yaml
ov_SC02_021_JTBL_INTERLEAVE := --order tail.data.o,ov_SC02_021.o,ov_SC02_021_jr_8012ACE0.o,tail2.data.o,ov_SC02_021_jr_80135888.o,tail3.data.o,ov_SC02_021_jr_80135A4C.o,tail4.data.o,ov_SC02_021_jr_80135D20.o,tail5.data.o,ov_SC02_021_jr_801380E0.o,ov_SC02_021_o0c.o,tail6.data.o,ov_SC02_021_jr_8013F350.o,tail7.data.o,ov_SC02_021_jr_8013FFD8.o,tail8.data.o,ov_SC02_021_jr_80140608.o,tail9.data.o,ov_SC02_021_jr_8015444C.o,ov_SC02_021_jr_80154C24.o,ov_SC02_021_jr_801588CC.o,ov_SC02_021_jr_80159C84.o,tail10.data.o,ov_SC02_021_jr_8015A3C8.o,tail11.data.o,ov_SC02_021_jr_8015AE2C.o,tail12.data.o,ov_SC02_021_jr_8015C32C.o,tail13.data.o,ov_SC02_021_jr_8016AB6C.o,tail14.data.o,ov_SC02_021_jr_80171B4C.o,ov_SC02_021_jr_801734BC.o,tail15.data.o,ov_SC02_021_jr_801789AC.o,ov_SC02_021_jr_80178D40.o,tail16.data.o,ov_SC02_021_jr_8017A4AC.o,tail17.data.o,ov_SC02_021_jr_8017AE2C.o,ov_SC02_021_jr_8017C294.o,tail18.data.o,ov_SC02_021_jr_8017EB00.o,ov_SC02_021_jr_8017ECFC.o,tail19.data.o,trailing.o  # Phase-26 §8 jtbl-rodata carve
build/src/ov_SC02_021/ov_SC02_021.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14
build/src/ov_SC02_021/ov_SC02_021_jr_8012ACE0.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0xcc,+0xe0
build/src/ov_SC02_021/ov_SC02_021_jr_80135D20.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC02_021/ov_SC02_021_jr_8013F350.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC02_021/ov_SC02_021_jr_8013FFD8.o: JTBL_PADS := 0,0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38,+0x58
build/src/ov_SC02_021/ov_SC02_021_jr_8015444C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x70
build/src/ov_SC02_021/ov_SC02_021_jr_80154C24.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x24
build/src/ov_SC02_021/ov_SC02_021_jr_801588CC.o: JTBL_PADS := 0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x28,+0x48
build/src/ov_SC02_021/ov_SC02_021_jr_80159C84.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC02_021/ov_SC02_021_jr_8015AE2C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC02_021/ov_SC02_021_jr_8016AB6C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC02_021/ov_SC02_021_jr_80178D40.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x178
build/src/ov_SC02_021/ov_SC02_021_o0c.o: JTBL_PADS := 0,4,4,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x38,+0xa8,+0x118
ov_SC02_021_CHECK_SHA  := config/check.ov_SC02_021.sha
ov_SC02_021_SYMBOLS    := config/symbols.ov_SC02_021.txt
ov_SC02_021_SIG        := .run/sig.ov_SC02_021.jsonl
ov_SC02_021_GHIDRA_PROG := ov_SC02_021
ov_SC02_021_VRAM_BASE  := 0x80128158
ov_SC02_021_TEXT_LO    := 0x80128158
ov_SC02_021_TEXT_HI    := 0x8019389F
ov_SC02_021_ASM_DIR     := asm/ov_SC02_021
ov_SC02_021_SRC_DIR     := src/ov_SC02_021
ov_SC02_021_UNDEF_SYMS  := build/ov_SC02_021/undefined_syms_auto.txt
ov_SC02_021_UNDEF_FUNCS := build/ov_SC02_021/undefined_funcs_auto.txt

# --- ov_SC02_026 (location overlay SC02/FILE_026, vram 0x80128158 — onboarded by new_overlay.sh) ---
ov_SC02_026_EXE        := extracted/retail/SC02.CD.dir/FILE_026.dir/0.4.dec
ov_SC02_026_NAME       := ov_SC02_026
ov_SC02_026_OUT_DIR    := build/ov_SC02_026
ov_SC02_026_OUT        := $(ov_SC02_026_OUT_DIR)/$(ov_SC02_026_NAME)
ov_SC02_026_ELF        := $(ov_SC02_026_OUT).elf
ov_SC02_026_MAPFILE    := $(ov_SC02_026_OUT).map
ov_SC02_026_LD_SCRIPT  := $(ov_SC02_026_OUT).ld
ov_SC02_026_SPLAT_YAML := config/splat.ov_SC02_026.yaml
ov_SC02_026_JTBL_INTERLEAVE := --order tail.data.o,ov_SC02_026.o,ov_SC02_026_jr_8012ACE0.o,tail2.data.o,ov_SC02_026_jr_80135888.o,tail3.data.o,ov_SC02_026_jr_80135A4C.o,tail4.data.o,ov_SC02_026_jr_80135D20.o,tail5.data.o,ov_SC02_026_jr_801380E0.o,ov_SC02_026_o0c.o,tail6.data.o,ov_SC02_026_jr_8013F350.o,tail7.data.o,ov_SC02_026_jr_8013FFD8.o,tail8.data.o,ov_SC02_026_jr_80140608.o,tail9.data.o,ov_SC02_026_jr_8015444C.o,ov_SC02_026_jr_80154C24.o,ov_SC02_026_jr_801588CC.o,ov_SC02_026_jr_80159C84.o,tail10.data.o,ov_SC02_026_jr_8015A3C8.o,tail11.data.o,ov_SC02_026_jr_8015AE2C.o,tail12.data.o,ov_SC02_026_jr_8015C32C.o,tail13.data.o,ov_SC02_026_jr_8016AB6C.o,tail14.data.o,ov_SC02_026_jr_80171B4C.o,ov_SC02_026_jr_801734BC.o,tail15.data.o,ov_SC02_026_jr_801789AC.o,ov_SC02_026_jr_80178D40.o,tail16.data.o,ov_SC02_026_jr_8017A4AC.o,tail17.data.o,ov_SC02_026_jr_8017AE2C.o,ov_SC02_026_jr_8017C180.o,ov_SC02_026_jr_80185440.o,tail18.data.o,trailing.o  # Phase-26 §8 jtbl-rodata carve
build/src/ov_SC02_026/ov_SC02_026.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14
build/src/ov_SC02_026/ov_SC02_026_jr_8012ACE0.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0xcc,+0xe0
build/src/ov_SC02_026/ov_SC02_026_jr_80135D20.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC02_026/ov_SC02_026_jr_8013F350.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC02_026/ov_SC02_026_jr_8013FFD8.o: JTBL_PADS := 0,0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38,+0x58
build/src/ov_SC02_026/ov_SC02_026_jr_8015444C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x70
build/src/ov_SC02_026/ov_SC02_026_jr_80154C24.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x24
build/src/ov_SC02_026/ov_SC02_026_jr_801588CC.o: JTBL_PADS := 0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x28,+0x48
build/src/ov_SC02_026/ov_SC02_026_jr_80159C84.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC02_026/ov_SC02_026_jr_8015AE2C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC02_026/ov_SC02_026_jr_8016AB6C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC02_026/ov_SC02_026_jr_80178D40.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x178
build/src/ov_SC02_026/ov_SC02_026_jr_8017C180.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38
build/src/ov_SC02_026/ov_SC02_026_o0c.o: JTBL_PADS := 0,4,4,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x38,+0xa8,+0x118
ov_SC02_026_CHECK_SHA  := config/check.ov_SC02_026.sha
ov_SC02_026_SYMBOLS    := config/symbols.ov_SC02_026.txt
ov_SC02_026_SIG        := .run/sig.ov_SC02_026.jsonl
ov_SC02_026_GHIDRA_PROG := ov_SC02_026
ov_SC02_026_VRAM_BASE  := 0x80128158
ov_SC02_026_TEXT_LO    := 0x80128158
ov_SC02_026_TEXT_HI    := 0x801D02BF
ov_SC02_026_ASM_DIR     := asm/ov_SC02_026
ov_SC02_026_SRC_DIR     := src/ov_SC02_026
ov_SC02_026_UNDEF_SYMS  := build/ov_SC02_026/undefined_syms_auto.txt
ov_SC02_026_UNDEF_FUNCS := build/ov_SC02_026/undefined_funcs_auto.txt

# --- ov_SC02_027 (location overlay SC02/FILE_027, vram 0x80128158 — onboarded by new_overlay.sh) ---
ov_SC02_027_EXE        := extracted/retail/SC02.CD.dir/FILE_027.dir/0.4.dec
ov_SC02_027_NAME       := ov_SC02_027
ov_SC02_027_OUT_DIR    := build/ov_SC02_027
ov_SC02_027_OUT        := $(ov_SC02_027_OUT_DIR)/$(ov_SC02_027_NAME)
ov_SC02_027_ELF        := $(ov_SC02_027_OUT).elf
ov_SC02_027_MAPFILE    := $(ov_SC02_027_OUT).map
ov_SC02_027_LD_SCRIPT  := $(ov_SC02_027_OUT).ld
ov_SC02_027_SPLAT_YAML := config/splat.ov_SC02_027.yaml
ov_SC02_027_JTBL_INTERLEAVE := --order tail.data.o,ov_SC02_027.o,ov_SC02_027_jr_8012ACE0.o,tail2.data.o,ov_SC02_027_jr_80135888.o,tail3.data.o,ov_SC02_027_jr_80135A4C.o,tail4.data.o,ov_SC02_027_jr_80135D20.o,tail5.data.o,ov_SC02_027_jr_801380E0.o,ov_SC02_027_o0c.o,tail6.data.o,ov_SC02_027_jr_8013F350.o,tail7.data.o,ov_SC02_027_jr_8013FFD8.o,tail8.data.o,ov_SC02_027_jr_80140608.o,tail9.data.o,ov_SC02_027_jr_8015444C.o,ov_SC02_027_jr_80154C24.o,ov_SC02_027_jr_801588CC.o,ov_SC02_027_jr_80159C84.o,tail10.data.o,ov_SC02_027_jr_8015A3C8.o,tail11.data.o,ov_SC02_027_jr_8015AE2C.o,tail12.data.o,ov_SC02_027_jr_8015C32C.o,tail13.data.o,ov_SC02_027_jr_8016AB6C.o,tail14.data.o,ov_SC02_027_jr_80171B4C.o,ov_SC02_027_jr_801734BC.o,tail15.data.o,ov_SC02_027_jr_801789AC.o,ov_SC02_027_jr_80178D40.o,tail16.data.o,ov_SC02_027_jr_8017A4AC.o,tail17.data.o,ov_SC02_027_jr_8017AE2C.o,ov_SC02_027_jr_8017D898.o,ov_SC02_027_jr_8018A564.o,tail18.data.o,trailing.o  # Phase-26 §8 jtbl-rodata carve
build/src/ov_SC02_027/ov_SC02_027.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14
build/src/ov_SC02_027/ov_SC02_027_jr_8012ACE0.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0xcc,+0xe0
build/src/ov_SC02_027/ov_SC02_027_jr_80135D20.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC02_027/ov_SC02_027_jr_8013F350.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC02_027/ov_SC02_027_jr_8013FFD8.o: JTBL_PADS := 0,0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38,+0x58
build/src/ov_SC02_027/ov_SC02_027_jr_8015444C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x70
build/src/ov_SC02_027/ov_SC02_027_jr_80154C24.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x24
build/src/ov_SC02_027/ov_SC02_027_jr_801588CC.o: JTBL_PADS := 0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x28,+0x48
build/src/ov_SC02_027/ov_SC02_027_jr_80159C84.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC02_027/ov_SC02_027_jr_8015AE2C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC02_027/ov_SC02_027_jr_8016AB6C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC02_027/ov_SC02_027_jr_80178D40.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x178
build/src/ov_SC02_027/ov_SC02_027_jr_8017D898.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38
build/src/ov_SC02_027/ov_SC02_027_o0c.o: JTBL_PADS := 0,4,4,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x38,+0xa8,+0x118
ov_SC02_027_CHECK_SHA  := config/check.ov_SC02_027.sha
ov_SC02_027_SYMBOLS    := config/symbols.ov_SC02_027.txt
ov_SC02_027_SIG        := .run/sig.ov_SC02_027.jsonl
ov_SC02_027_GHIDRA_PROG := ov_SC02_027
ov_SC02_027_VRAM_BASE  := 0x80128158
ov_SC02_027_TEXT_LO    := 0x80128158
ov_SC02_027_TEXT_HI    := 0x801DAA3F
ov_SC02_027_ASM_DIR     := asm/ov_SC02_027
ov_SC02_027_SRC_DIR     := src/ov_SC02_027
ov_SC02_027_UNDEF_SYMS  := build/ov_SC02_027/undefined_syms_auto.txt
ov_SC02_027_UNDEF_FUNCS := build/ov_SC02_027/undefined_funcs_auto.txt

# --- ov_SC02_028 (location overlay SC02/FILE_028, vram 0x80128158 — onboarded by new_overlay.sh) ---
ov_SC02_028_EXE        := extracted/retail/SC02.CD.dir/FILE_028.dir/0.4.dec
ov_SC02_028_NAME       := ov_SC02_028
ov_SC02_028_OUT_DIR    := build/ov_SC02_028
ov_SC02_028_OUT        := $(ov_SC02_028_OUT_DIR)/$(ov_SC02_028_NAME)
ov_SC02_028_ELF        := $(ov_SC02_028_OUT).elf
ov_SC02_028_MAPFILE    := $(ov_SC02_028_OUT).map
ov_SC02_028_LD_SCRIPT  := $(ov_SC02_028_OUT).ld
ov_SC02_028_SPLAT_YAML := config/splat.ov_SC02_028.yaml
ov_SC02_028_JTBL_INTERLEAVE := --order tail.data.o,ov_SC02_028.o,ov_SC02_028_jr_8012ACE0.o,tail2.data.o,ov_SC02_028_jr_80135888.o,tail3.data.o,ov_SC02_028_jr_80135A4C.o,tail4.data.o,ov_SC02_028_jr_80135D20.o,tail5.data.o,ov_SC02_028_jr_801380E0.o,ov_SC02_028_o0c.o,tail6.data.o,ov_SC02_028_jr_8013F350.o,tail7.data.o,ov_SC02_028_jr_8013FFD8.o,tail8.data.o,ov_SC02_028_jr_80140608.o,tail9.data.o,ov_SC02_028_jr_8015444C.o,ov_SC02_028_jr_80154C24.o,ov_SC02_028_jr_801588CC.o,ov_SC02_028_jr_80159C84.o,tail10.data.o,ov_SC02_028_jr_8015A3C8.o,tail11.data.o,ov_SC02_028_jr_8015AE2C.o,tail12.data.o,ov_SC02_028_jr_8015C32C.o,tail13.data.o,ov_SC02_028_jr_8016AB6C.o,tail14.data.o,ov_SC02_028_jr_80171B4C.o,ov_SC02_028_jr_801734BC.o,tail15.data.o,ov_SC02_028_jr_801789AC.o,ov_SC02_028_jr_80178D40.o,tail16.data.o,ov_SC02_028_jr_8017A4AC.o,tail17.data.o,ov_SC02_028_jr_8017AE2C.o,ov_SC02_028_jr_8017D898.o,tail18.data.o,ov_SC02_028_jr_80184BD8.o,ov_SC02_028_jr_801884D8.o,tail19.data.o,trailing.o  # Phase-26 §8 jtbl-rodata carve
build/src/ov_SC02_028/ov_SC02_028.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14
build/src/ov_SC02_028/ov_SC02_028_jr_8012ACE0.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0xcc,+0xe0
build/src/ov_SC02_028/ov_SC02_028_jr_80135D20.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC02_028/ov_SC02_028_jr_8013F350.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC02_028/ov_SC02_028_jr_8013FFD8.o: JTBL_PADS := 0,0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38,+0x58
build/src/ov_SC02_028/ov_SC02_028_jr_8015444C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x70
build/src/ov_SC02_028/ov_SC02_028_jr_80154C24.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x24
build/src/ov_SC02_028/ov_SC02_028_jr_801588CC.o: JTBL_PADS := 0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x28,+0x48
build/src/ov_SC02_028/ov_SC02_028_jr_80159C84.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC02_028/ov_SC02_028_jr_8015AE2C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC02_028/ov_SC02_028_jr_8016AB6C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC02_028/ov_SC02_028_jr_80178D40.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x178
build/src/ov_SC02_028/ov_SC02_028_jr_801884D8.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC02_028/ov_SC02_028_o0c.o: JTBL_PADS := 0,4,4,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x38,+0xa8,+0x118
ov_SC02_028_CHECK_SHA  := config/check.ov_SC02_028.sha
ov_SC02_028_SYMBOLS    := config/symbols.ov_SC02_028.txt
ov_SC02_028_SIG        := .run/sig.ov_SC02_028.jsonl
ov_SC02_028_GHIDRA_PROG := ov_SC02_028
ov_SC02_028_VRAM_BASE  := 0x80128158
ov_SC02_028_TEXT_LO    := 0x80128158
ov_SC02_028_TEXT_HI    := 0x801D363F
ov_SC02_028_ASM_DIR     := asm/ov_SC02_028
ov_SC02_028_SRC_DIR     := src/ov_SC02_028
ov_SC02_028_UNDEF_SYMS  := build/ov_SC02_028/undefined_syms_auto.txt
ov_SC02_028_UNDEF_FUNCS := build/ov_SC02_028/undefined_funcs_auto.txt

# --- ov_SC02_031 (location overlay SC02/FILE_031, vram 0x80128158 — onboarded by new_overlay.sh) ---
ov_SC02_031_EXE        := extracted/retail/SC02.CD.dir/FILE_031.dir/0.4.dec
ov_SC02_031_NAME       := ov_SC02_031
ov_SC02_031_OUT_DIR    := build/ov_SC02_031
ov_SC02_031_OUT        := $(ov_SC02_031_OUT_DIR)/$(ov_SC02_031_NAME)
ov_SC02_031_ELF        := $(ov_SC02_031_OUT).elf
ov_SC02_031_MAPFILE    := $(ov_SC02_031_OUT).map
ov_SC02_031_LD_SCRIPT  := $(ov_SC02_031_OUT).ld
ov_SC02_031_SPLAT_YAML := config/splat.ov_SC02_031.yaml
ov_SC02_031_JTBL_INTERLEAVE := --order tail.data.o,ov_SC02_031.o,ov_SC02_031_jr_8012ACE0.o,tail2.data.o,ov_SC02_031_jr_80135888.o,tail3.data.o,ov_SC02_031_jr_80135A4C.o,tail4.data.o,ov_SC02_031_jr_80135D20.o,tail5.data.o,ov_SC02_031_jr_801380E0.o,ov_SC02_031_o0c.o,tail6.data.o,ov_SC02_031_jr_8013F350.o,tail7.data.o,ov_SC02_031_jr_8013FFD8.o,tail8.data.o,ov_SC02_031_jr_80140608.o,tail9.data.o,ov_SC02_031_jr_8015444C.o,ov_SC02_031_jr_80154C24.o,ov_SC02_031_jr_801588CC.o,ov_SC02_031_jr_80159C84.o,tail10.data.o,ov_SC02_031_jr_8015A3C8.o,tail11.data.o,ov_SC02_031_jr_8015AE2C.o,tail12.data.o,ov_SC02_031_jr_8015C32C.o,tail13.data.o,ov_SC02_031_jr_8016AB6C.o,tail14.data.o,ov_SC02_031_jr_80171B4C.o,ov_SC02_031_jr_801734BC.o,tail15.data.o,ov_SC02_031_jr_801789AC.o,ov_SC02_031_jr_80178D40.o,tail16.data.o,ov_SC02_031_jr_8017A4AC.o,tail17.data.o,ov_SC02_031_jr_8017AE2C.o,tail18.data.o,trailing.o  # Phase-26 §8 jtbl-rodata carve
build/src/ov_SC02_031/ov_SC02_031.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14
build/src/ov_SC02_031/ov_SC02_031_jr_8012ACE0.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0xcc,+0xe0
build/src/ov_SC02_031/ov_SC02_031_jr_80135D20.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC02_031/ov_SC02_031_jr_8013F350.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC02_031/ov_SC02_031_jr_8013FFD8.o: JTBL_PADS := 0,0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38,+0x58
build/src/ov_SC02_031/ov_SC02_031_jr_8015444C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x70
build/src/ov_SC02_031/ov_SC02_031_jr_80154C24.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x24
build/src/ov_SC02_031/ov_SC02_031_jr_801588CC.o: JTBL_PADS := 0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x28,+0x48
build/src/ov_SC02_031/ov_SC02_031_jr_80159C84.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC02_031/ov_SC02_031_jr_8015AE2C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC02_031/ov_SC02_031_jr_8016AB6C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC02_031/ov_SC02_031_jr_80178D40.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x178
build/src/ov_SC02_031/ov_SC02_031_o0c.o: JTBL_PADS := 0,4,4,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x38,+0xa8,+0x118
ov_SC02_031_CHECK_SHA  := config/check.ov_SC02_031.sha
ov_SC02_031_SYMBOLS    := config/symbols.ov_SC02_031.txt
ov_SC02_031_SIG        := .run/sig.ov_SC02_031.jsonl
ov_SC02_031_GHIDRA_PROG := ov_SC02_031
ov_SC02_031_VRAM_BASE  := 0x80128158
ov_SC02_031_TEXT_LO    := 0x80128158
ov_SC02_031_TEXT_HI    := 0x801B7B0F
ov_SC02_031_ASM_DIR     := asm/ov_SC02_031
ov_SC02_031_SRC_DIR     := src/ov_SC02_031
ov_SC02_031_UNDEF_SYMS  := build/ov_SC02_031/undefined_syms_auto.txt
ov_SC02_031_UNDEF_FUNCS := build/ov_SC02_031/undefined_funcs_auto.txt

# --- ov_SC02_035 (location overlay SC02/FILE_035, vram 0x80128158 — onboarded by new_overlay.sh) ---
ov_SC02_035_EXE        := extracted/retail/SC02.CD.dir/FILE_035.dir/0.4.dec
ov_SC02_035_NAME       := ov_SC02_035
ov_SC02_035_OUT_DIR    := build/ov_SC02_035
ov_SC02_035_OUT        := $(ov_SC02_035_OUT_DIR)/$(ov_SC02_035_NAME)
ov_SC02_035_ELF        := $(ov_SC02_035_OUT).elf
ov_SC02_035_MAPFILE    := $(ov_SC02_035_OUT).map
ov_SC02_035_LD_SCRIPT  := $(ov_SC02_035_OUT).ld
ov_SC02_035_SPLAT_YAML := config/splat.ov_SC02_035.yaml
ov_SC02_035_JTBL_INTERLEAVE := --order tail.data.o,ov_SC02_035.o,ov_SC02_035_jr_8012ACE0.o,tail2.data.o,ov_SC02_035_jr_80135888.o,tail3.data.o,ov_SC02_035_jr_80135A4C.o,tail4.data.o,ov_SC02_035_jr_80135D20.o,tail5.data.o,ov_SC02_035_jr_801380E0.o,ov_SC02_035_o0c.o,tail6.data.o,ov_SC02_035_jr_8013F350.o,tail7.data.o,ov_SC02_035_jr_8013FFD8.o,tail8.data.o,ov_SC02_035_jr_80140608.o,tail9.data.o,ov_SC02_035_jr_8015444C.o,ov_SC02_035_jr_80154C24.o,ov_SC02_035_jr_801588CC.o,ov_SC02_035_jr_80159C84.o,tail10.data.o,ov_SC02_035_jr_8015A3C8.o,tail11.data.o,ov_SC02_035_jr_8015AE2C.o,tail12.data.o,ov_SC02_035_jr_8015C32C.o,tail13.data.o,ov_SC02_035_jr_8016AB6C.o,tail14.data.o,ov_SC02_035_jr_80171B4C.o,ov_SC02_035_jr_801734BC.o,tail15.data.o,ov_SC02_035_jr_801789AC.o,ov_SC02_035_jr_80178D40.o,tail16.data.o,ov_SC02_035_jr_8017A4AC.o,tail17.data.o,ov_SC02_035_jr_8017AE2C.o,ov_SC02_035_jr_8017BEBC.o,ov_SC02_035_jr_80183FD4.o,tail18.data.o,trailing.o  # Phase-26 §8 jtbl-rodata carve
build/src/ov_SC02_035/ov_SC02_035.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14
build/src/ov_SC02_035/ov_SC02_035_jr_8012ACE0.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0xcc,+0xe0
build/src/ov_SC02_035/ov_SC02_035_jr_80135D20.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC02_035/ov_SC02_035_jr_8013F350.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC02_035/ov_SC02_035_jr_8013FFD8.o: JTBL_PADS := 0,0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38,+0x58
build/src/ov_SC02_035/ov_SC02_035_jr_8015444C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x70
build/src/ov_SC02_035/ov_SC02_035_jr_80154C24.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x24
build/src/ov_SC02_035/ov_SC02_035_jr_801588CC.o: JTBL_PADS := 0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x28,+0x48
build/src/ov_SC02_035/ov_SC02_035_jr_80159C84.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC02_035/ov_SC02_035_jr_8015AE2C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC02_035/ov_SC02_035_jr_8016AB6C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC02_035/ov_SC02_035_jr_80178D40.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x178
build/src/ov_SC02_035/ov_SC02_035_jr_8017BEBC.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38
build/src/ov_SC02_035/ov_SC02_035_o0c.o: JTBL_PADS := 0,4,4,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x38,+0xa8,+0x118
ov_SC02_035_CHECK_SHA  := config/check.ov_SC02_035.sha
ov_SC02_035_SYMBOLS    := config/symbols.ov_SC02_035.txt
ov_SC02_035_SIG        := .run/sig.ov_SC02_035.jsonl
ov_SC02_035_GHIDRA_PROG := ov_SC02_035
ov_SC02_035_VRAM_BASE  := 0x80128158
ov_SC02_035_TEXT_LO    := 0x80128158
ov_SC02_035_TEXT_HI    := 0x801BEA47
ov_SC02_035_ASM_DIR     := asm/ov_SC02_035
ov_SC02_035_SRC_DIR     := src/ov_SC02_035
ov_SC02_035_UNDEF_SYMS  := build/ov_SC02_035/undefined_syms_auto.txt
ov_SC02_035_UNDEF_FUNCS := build/ov_SC02_035/undefined_funcs_auto.txt

# --- ov_SC02_039 (location overlay SC02/FILE_039, vram 0x80128158 — onboarded by new_overlay.sh) ---
ov_SC02_039_EXE        := extracted/retail/SC02.CD.dir/FILE_039.dir/0.4.dec
ov_SC02_039_NAME       := ov_SC02_039
ov_SC02_039_OUT_DIR    := build/ov_SC02_039
ov_SC02_039_OUT        := $(ov_SC02_039_OUT_DIR)/$(ov_SC02_039_NAME)
ov_SC02_039_ELF        := $(ov_SC02_039_OUT).elf
ov_SC02_039_MAPFILE    := $(ov_SC02_039_OUT).map
ov_SC02_039_LD_SCRIPT  := $(ov_SC02_039_OUT).ld
ov_SC02_039_SPLAT_YAML := config/splat.ov_SC02_039.yaml
ov_SC02_039_JTBL_INTERLEAVE := --order tail.data.o,ov_SC02_039.o,ov_SC02_039_jr_8012ACE0.o,tail2.data.o,ov_SC02_039_jr_80135888.o,tail3.data.o,ov_SC02_039_jr_80135A4C.o,tail4.data.o,ov_SC02_039_jr_80135D20.o,tail5.data.o,ov_SC02_039_jr_801380E0.o,ov_SC02_039_o0c.o,tail6.data.o,ov_SC02_039_jr_8013F350.o,tail7.data.o,ov_SC02_039_jr_8013FFD8.o,tail8.data.o,ov_SC02_039_jr_80140608.o,tail9.data.o,ov_SC02_039_jr_8015444C.o,ov_SC02_039_jr_80154C24.o,ov_SC02_039_jr_801588CC.o,ov_SC02_039_jr_80159C84.o,tail10.data.o,ov_SC02_039_jr_8015A3C8.o,tail11.data.o,ov_SC02_039_jr_8015AE2C.o,tail12.data.o,ov_SC02_039_jr_8015C32C.o,tail13.data.o,ov_SC02_039_jr_8016AB6C.o,tail14.data.o,ov_SC02_039_jr_80171B4C.o,ov_SC02_039_jr_801734BC.o,tail15.data.o,ov_SC02_039_jr_801789AC.o,ov_SC02_039_jr_80178D40.o,tail16.data.o,ov_SC02_039_jr_8017A4AC.o,tail17.data.o,ov_SC02_039_jr_8017AE2C.o,ov_SC02_039_jr_8017BEBC.o,tail18.data.o,trailing.o  # Phase-26 §8 jtbl-rodata carve
build/src/ov_SC02_039/ov_SC02_039.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14
build/src/ov_SC02_039/ov_SC02_039_jr_8012ACE0.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0xcc,+0xe0
build/src/ov_SC02_039/ov_SC02_039_jr_80135D20.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC02_039/ov_SC02_039_jr_8013F350.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC02_039/ov_SC02_039_jr_8013FFD8.o: JTBL_PADS := 0,0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38,+0x58
build/src/ov_SC02_039/ov_SC02_039_jr_8015444C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x70
build/src/ov_SC02_039/ov_SC02_039_jr_80154C24.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x24
build/src/ov_SC02_039/ov_SC02_039_jr_801588CC.o: JTBL_PADS := 0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x28,+0x48
build/src/ov_SC02_039/ov_SC02_039_jr_80159C84.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC02_039/ov_SC02_039_jr_8015AE2C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC02_039/ov_SC02_039_jr_8016AB6C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC02_039/ov_SC02_039_jr_80178D40.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x178
build/src/ov_SC02_039/ov_SC02_039_o0c.o: JTBL_PADS := 0,4,4,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x38,+0xa8,+0x118
ov_SC02_039_CHECK_SHA  := config/check.ov_SC02_039.sha
ov_SC02_039_SYMBOLS    := config/symbols.ov_SC02_039.txt
ov_SC02_039_SIG        := .run/sig.ov_SC02_039.jsonl
ov_SC02_039_GHIDRA_PROG := ov_SC02_039
ov_SC02_039_VRAM_BASE  := 0x80128158
ov_SC02_039_TEXT_LO    := 0x80128158
ov_SC02_039_TEXT_HI    := 0x801A0DFF
ov_SC02_039_ASM_DIR     := asm/ov_SC02_039
ov_SC02_039_SRC_DIR     := src/ov_SC02_039
ov_SC02_039_UNDEF_SYMS  := build/ov_SC02_039/undefined_syms_auto.txt
ov_SC02_039_UNDEF_FUNCS := build/ov_SC02_039/undefined_funcs_auto.txt

# --- ov_SC02_041 (location overlay SC02/FILE_041, vram 0x80128158 — onboarded by new_overlay.sh) ---
ov_SC02_041_EXE        := extracted/retail/SC02.CD.dir/FILE_041.dir/0.4.dec
ov_SC02_041_NAME       := ov_SC02_041
ov_SC02_041_OUT_DIR    := build/ov_SC02_041
ov_SC02_041_OUT        := $(ov_SC02_041_OUT_DIR)/$(ov_SC02_041_NAME)
ov_SC02_041_ELF        := $(ov_SC02_041_OUT).elf
ov_SC02_041_MAPFILE    := $(ov_SC02_041_OUT).map
ov_SC02_041_LD_SCRIPT  := $(ov_SC02_041_OUT).ld
ov_SC02_041_SPLAT_YAML := config/splat.ov_SC02_041.yaml
ov_SC02_041_JTBL_INTERLEAVE := --order tail.data.o,ov_SC02_041.o,ov_SC02_041_jr_8012ACE0.o,tail2.data.o,ov_SC02_041_jr_80135888.o,tail3.data.o,ov_SC02_041_jr_80135A4C.o,tail4.data.o,ov_SC02_041_jr_80135D20.o,tail5.data.o,ov_SC02_041_jr_801380E0.o,ov_SC02_041_o0c.o,tail6.data.o,ov_SC02_041_jr_8013F350.o,tail7.data.o,ov_SC02_041_jr_8013FFD8.o,tail8.data.o,ov_SC02_041_jr_80140608.o,tail9.data.o,ov_SC02_041_jr_8015444C.o,ov_SC02_041_jr_80154C24.o,ov_SC02_041_jr_801588CC.o,ov_SC02_041_jr_80159C84.o,tail10.data.o,ov_SC02_041_jr_8015A3C8.o,tail11.data.o,ov_SC02_041_jr_8015AE2C.o,tail12.data.o,ov_SC02_041_jr_8015C32C.o,tail13.data.o,ov_SC02_041_jr_8016AB6C.o,tail14.data.o,ov_SC02_041_jr_80171B4C.o,ov_SC02_041_jr_801734BC.o,tail15.data.o,ov_SC02_041_jr_801789AC.o,ov_SC02_041_jr_80178D40.o,tail16.data.o,ov_SC02_041_jr_8017A4AC.o,tail17.data.o,ov_SC02_041_jr_8017AE2C.o,ov_SC02_041_jr_8017BEBC.o,tail18.data.o,trailing.o  # Phase-26 §8 jtbl-rodata carve
build/src/ov_SC02_041/ov_SC02_041.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14
build/src/ov_SC02_041/ov_SC02_041_jr_8012ACE0.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0xcc,+0xe0
build/src/ov_SC02_041/ov_SC02_041_jr_80135D20.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC02_041/ov_SC02_041_jr_8013F350.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC02_041/ov_SC02_041_jr_8013FFD8.o: JTBL_PADS := 0,0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38,+0x58
build/src/ov_SC02_041/ov_SC02_041_jr_8015444C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x70
build/src/ov_SC02_041/ov_SC02_041_jr_80154C24.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x24
build/src/ov_SC02_041/ov_SC02_041_jr_801588CC.o: JTBL_PADS := 0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x28,+0x48
build/src/ov_SC02_041/ov_SC02_041_jr_80159C84.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC02_041/ov_SC02_041_jr_8015AE2C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC02_041/ov_SC02_041_jr_8016AB6C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC02_041/ov_SC02_041_jr_80178D40.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x178
build/src/ov_SC02_041/ov_SC02_041_jr_8017BEBC.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC02_041/ov_SC02_041_o0c.o: JTBL_PADS := 0,4,4,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x38,+0xa8,+0x118
ov_SC02_041_CHECK_SHA  := config/check.ov_SC02_041.sha
ov_SC02_041_SYMBOLS    := config/symbols.ov_SC02_041.txt
ov_SC02_041_SIG        := .run/sig.ov_SC02_041.jsonl
ov_SC02_041_GHIDRA_PROG := ov_SC02_041
ov_SC02_041_VRAM_BASE  := 0x80128158
ov_SC02_041_TEXT_LO    := 0x80128158
ov_SC02_041_TEXT_HI    := 0x801B96D7
ov_SC02_041_ASM_DIR     := asm/ov_SC02_041
ov_SC02_041_SRC_DIR     := src/ov_SC02_041
ov_SC02_041_UNDEF_SYMS  := build/ov_SC02_041/undefined_syms_auto.txt
ov_SC02_041_UNDEF_FUNCS := build/ov_SC02_041/undefined_funcs_auto.txt

# --- ov_SC03_003 (location overlay SC03/FILE_003, vram 0x80128158 — onboarded by new_overlay.sh) ---
ov_SC03_003_EXE        := extracted/retail/SC03.CD.dir/FILE_003.dir/0.4.dec
ov_SC03_003_NAME       := ov_SC03_003
ov_SC03_003_OUT_DIR    := build/ov_SC03_003
ov_SC03_003_OUT        := $(ov_SC03_003_OUT_DIR)/$(ov_SC03_003_NAME)
ov_SC03_003_ELF        := $(ov_SC03_003_OUT).elf
ov_SC03_003_MAPFILE    := $(ov_SC03_003_OUT).map
ov_SC03_003_LD_SCRIPT  := $(ov_SC03_003_OUT).ld
ov_SC03_003_SPLAT_YAML := config/splat.ov_SC03_003.yaml
ov_SC03_003_JTBL_INTERLEAVE := --order tail.data.o,ov_SC03_003.o,ov_SC03_003_jr_8012ACE0.o,tail2.data.o,ov_SC03_003_jr_80135888.o,tail3.data.o,ov_SC03_003_jr_80135A4C.o,tail4.data.o,ov_SC03_003_jr_80135D20.o,tail5.data.o,ov_SC03_003_jr_801380E0.o,ov_SC03_003_o0c.o,tail6.data.o,ov_SC03_003_jr_8013F350.o,tail7.data.o,ov_SC03_003_jr_8013FFD8.o,tail8.data.o,ov_SC03_003_jr_80140608.o,tail9.data.o,ov_SC03_003_jr_8015444C.o,ov_SC03_003_jr_80154C24.o,ov_SC03_003_jr_801588CC.o,ov_SC03_003_jr_80159C84.o,tail10.data.o,ov_SC03_003_jr_8015A3C8.o,tail11.data.o,ov_SC03_003_jr_8015AE2C.o,tail12.data.o,ov_SC03_003_jr_8015C32C.o,tail13.data.o,ov_SC03_003_jr_8016AB6C.o,tail14.data.o,ov_SC03_003_jr_80171B4C.o,ov_SC03_003_jr_801734BC.o,tail15.data.o,ov_SC03_003_jr_801789AC.o,ov_SC03_003_jr_80178D40.o,tail16.data.o,ov_SC03_003_jr_8017A4AC.o,tail17.data.o,ov_SC03_003_jr_8017AE2C.o,ov_SC03_003_jr_8017D5C0.o,tail18.data.o,trailing.o  # Phase-26 §8 jtbl-rodata carve
build/src/ov_SC03_003/ov_SC03_003.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14
build/src/ov_SC03_003/ov_SC03_003_jr_8012ACE0.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0xcc,+0xe0
build/src/ov_SC03_003/ov_SC03_003_jr_80135D20.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC03_003/ov_SC03_003_jr_8013F350.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_003/ov_SC03_003_jr_8013FFD8.o: JTBL_PADS := 0,0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38,+0x58
build/src/ov_SC03_003/ov_SC03_003_jr_8015444C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x70
build/src/ov_SC03_003/ov_SC03_003_jr_80154C24.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x24
build/src/ov_SC03_003/ov_SC03_003_jr_801588CC.o: JTBL_PADS := 0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x28,+0x48
build/src/ov_SC03_003/ov_SC03_003_jr_80159C84.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_003/ov_SC03_003_jr_8015AE2C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_003/ov_SC03_003_jr_8016AB6C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_003/ov_SC03_003_jr_80178D40.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x178
build/src/ov_SC03_003/ov_SC03_003_jr_8017AE2C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14
build/src/ov_SC03_003/ov_SC03_003_o0c.o: JTBL_PADS := 0,4,4,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x38,+0xa8,+0x118
ov_SC03_003_CHECK_SHA  := config/check.ov_SC03_003.sha
ov_SC03_003_SYMBOLS    := config/symbols.ov_SC03_003.txt
ov_SC03_003_SIG        := .run/sig.ov_SC03_003.jsonl
ov_SC03_003_GHIDRA_PROG := ov_SC03_003
ov_SC03_003_VRAM_BASE  := 0x80128158
ov_SC03_003_TEXT_LO    := 0x80128158
ov_SC03_003_TEXT_HI    := 0x8018FB7D
ov_SC03_003_ASM_DIR     := asm/ov_SC03_003
ov_SC03_003_SRC_DIR     := src/ov_SC03_003
ov_SC03_003_UNDEF_SYMS  := build/ov_SC03_003/undefined_syms_auto.txt
ov_SC03_003_UNDEF_FUNCS := build/ov_SC03_003/undefined_funcs_auto.txt

# --- ov_SC03_007 (location overlay SC03/FILE_007, vram 0x80128158 — onboarded by new_overlay.sh) ---
ov_SC03_007_EXE        := extracted/retail/SC03.CD.dir/FILE_007.dir/0.4.dec
ov_SC03_007_NAME       := ov_SC03_007
ov_SC03_007_OUT_DIR    := build/ov_SC03_007
ov_SC03_007_OUT        := $(ov_SC03_007_OUT_DIR)/$(ov_SC03_007_NAME)
ov_SC03_007_ELF        := $(ov_SC03_007_OUT).elf
ov_SC03_007_MAPFILE    := $(ov_SC03_007_OUT).map
ov_SC03_007_LD_SCRIPT  := $(ov_SC03_007_OUT).ld
ov_SC03_007_SPLAT_YAML := config/splat.ov_SC03_007.yaml
ov_SC03_007_JTBL_INTERLEAVE := --order tail.data.o,ov_SC03_007.o,ov_SC03_007_jr_8012ACE0.o,tail2.data.o,ov_SC03_007_jr_80135888.o,tail3.data.o,ov_SC03_007_jr_80135A4C.o,tail4.data.o,ov_SC03_007_jr_80135D20.o,tail5.data.o,ov_SC03_007_jr_801380E0.o,ov_SC03_007_o0c.o,tail6.data.o,ov_SC03_007_jr_8013F350.o,tail7.data.o,ov_SC03_007_jr_8013FFD8.o,tail8.data.o,ov_SC03_007_jr_80140608.o,tail9.data.o,ov_SC03_007_jr_8015444C.o,ov_SC03_007_jr_80154C24.o,ov_SC03_007_jr_801588CC.o,ov_SC03_007_jr_80159C84.o,tail10.data.o,ov_SC03_007_jr_8015A3C8.o,tail11.data.o,ov_SC03_007_jr_8015AE2C.o,tail12.data.o,ov_SC03_007_jr_8015C32C.o,tail13.data.o,ov_SC03_007_jr_8016AB6C.o,tail14.data.o,ov_SC03_007_jr_80171B4C.o,ov_SC03_007_jr_801734BC.o,tail15.data.o,ov_SC03_007_jr_801789AC.o,ov_SC03_007_jr_80178D40.o,tail16.data.o,ov_SC03_007_jr_8017A4AC.o,tail17.data.o,ov_SC03_007_jr_8017AE2C.o,ov_SC03_007_jr_80181F94.o,ov_SC03_007_jr_80183894.o,tail18.data.o,trailing.o  # Phase-26 §8 jtbl-rodata carve
build/src/ov_SC03_007/ov_SC03_007.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14
build/src/ov_SC03_007/ov_SC03_007_jr_8012ACE0.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0xcc,+0xe0
build/src/ov_SC03_007/ov_SC03_007_jr_80135D20.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC03_007/ov_SC03_007_jr_8013F350.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_007/ov_SC03_007_jr_8013FFD8.o: JTBL_PADS := 0,0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38,+0x58
build/src/ov_SC03_007/ov_SC03_007_jr_8015444C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x70
build/src/ov_SC03_007/ov_SC03_007_jr_80154C24.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x24
build/src/ov_SC03_007/ov_SC03_007_jr_801588CC.o: JTBL_PADS := 0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x28,+0x48
build/src/ov_SC03_007/ov_SC03_007_jr_80159C84.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_007/ov_SC03_007_jr_8015AE2C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_007/ov_SC03_007_jr_8016AB6C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_007/ov_SC03_007_jr_80178D40.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x178
build/src/ov_SC03_007/ov_SC03_007_jr_8017AE2C.o: JTBL_PADS := 0,0,0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14,+0x34,+0x64,+0x78
build/src/ov_SC03_007/ov_SC03_007_jr_80183894.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC03_007/ov_SC03_007_o0c.o: JTBL_PADS := 0,4,4,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x38,+0xa8,+0x118
ov_SC03_007_CHECK_SHA  := config/check.ov_SC03_007.sha
ov_SC03_007_SYMBOLS    := config/symbols.ov_SC03_007.txt
ov_SC03_007_SIG        := .run/sig.ov_SC03_007.jsonl
ov_SC03_007_GHIDRA_PROG := ov_SC03_007
ov_SC03_007_VRAM_BASE  := 0x80128158
ov_SC03_007_TEXT_LO    := 0x80128158
ov_SC03_007_TEXT_HI    := 0x801EB2C7
ov_SC03_007_ASM_DIR     := asm/ov_SC03_007
ov_SC03_007_SRC_DIR     := src/ov_SC03_007
ov_SC03_007_UNDEF_SYMS  := build/ov_SC03_007/undefined_syms_auto.txt
ov_SC03_007_UNDEF_FUNCS := build/ov_SC03_007/undefined_funcs_auto.txt

# --- ov_SC03_010 (location overlay SC03/FILE_010, vram 0x80128158 — onboarded by new_overlay.sh) ---
ov_SC03_010_EXE        := extracted/retail/SC03.CD.dir/FILE_010.dir/0.4.dec
ov_SC03_010_NAME       := ov_SC03_010
ov_SC03_010_OUT_DIR    := build/ov_SC03_010
ov_SC03_010_OUT        := $(ov_SC03_010_OUT_DIR)/$(ov_SC03_010_NAME)
ov_SC03_010_ELF        := $(ov_SC03_010_OUT).elf
ov_SC03_010_MAPFILE    := $(ov_SC03_010_OUT).map
ov_SC03_010_LD_SCRIPT  := $(ov_SC03_010_OUT).ld
ov_SC03_010_SPLAT_YAML := config/splat.ov_SC03_010.yaml
ov_SC03_010_JTBL_INTERLEAVE := --order tail.data.o,ov_SC03_010.o,ov_SC03_010_jr_8012ACE0.o,tail2.data.o,ov_SC03_010_jr_80135888.o,tail3.data.o,ov_SC03_010_jr_80135A4C.o,tail4.data.o,ov_SC03_010_jr_80135D20.o,tail5.data.o,ov_SC03_010_jr_801380E0.o,ov_SC03_010_o0c.o,tail6.data.o,ov_SC03_010_jr_8013F350.o,tail7.data.o,ov_SC03_010_jr_8013FFD8.o,tail8.data.o,ov_SC03_010_jr_80140608.o,tail9.data.o,ov_SC03_010_jr_8015444C.o,ov_SC03_010_jr_80154C24.o,ov_SC03_010_jr_801588CC.o,ov_SC03_010_jr_80159C84.o,tail10.data.o,ov_SC03_010_jr_8015A3C8.o,tail11.data.o,ov_SC03_010_jr_8015AE2C.o,tail12.data.o,ov_SC03_010_jr_8015C32C.o,tail13.data.o,ov_SC03_010_jr_8016AB6C.o,tail14.data.o,ov_SC03_010_jr_80171B4C.o,ov_SC03_010_jr_801734BC.o,tail15.data.o,ov_SC03_010_jr_801789AC.o,ov_SC03_010_jr_80178D40.o,tail16.data.o,ov_SC03_010_jr_8017A4AC.o,tail17.data.o,ov_SC03_010_jr_8017AE2C.o,ov_SC03_010_jr_8017C730.o,tail18.data.o,ov_SC03_010_jr_8017F6C0.o,tail19.data.o,trailing.o  # Phase-26 §8 jtbl-rodata carve
build/src/ov_SC03_010/ov_SC03_010.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14
build/src/ov_SC03_010/ov_SC03_010_jr_8012ACE0.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0xcc,+0xe0
build/src/ov_SC03_010/ov_SC03_010_jr_80135D20.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC03_010/ov_SC03_010_jr_8013F350.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_010/ov_SC03_010_jr_8013FFD8.o: JTBL_PADS := 0,0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38,+0x58
build/src/ov_SC03_010/ov_SC03_010_jr_8015444C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x70
build/src/ov_SC03_010/ov_SC03_010_jr_80154C24.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x24
build/src/ov_SC03_010/ov_SC03_010_jr_801588CC.o: JTBL_PADS := 0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x28,+0x48
build/src/ov_SC03_010/ov_SC03_010_jr_80159C84.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_010/ov_SC03_010_jr_8015AE2C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_010/ov_SC03_010_jr_8016AB6C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_010/ov_SC03_010_jr_80178D40.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x178
build/src/ov_SC03_010/ov_SC03_010_o0c.o: JTBL_PADS := 0,4,4,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x38,+0xa8,+0x118
ov_SC03_010_CHECK_SHA  := config/check.ov_SC03_010.sha
ov_SC03_010_SYMBOLS    := config/symbols.ov_SC03_010.txt
ov_SC03_010_SIG        := .run/sig.ov_SC03_010.jsonl
ov_SC03_010_GHIDRA_PROG := ov_SC03_010
ov_SC03_010_VRAM_BASE  := 0x80128158
ov_SC03_010_TEXT_LO    := 0x80128158
ov_SC03_010_TEXT_HI    := 0x801A01CF
ov_SC03_010_ASM_DIR     := asm/ov_SC03_010
ov_SC03_010_SRC_DIR     := src/ov_SC03_010
ov_SC03_010_UNDEF_SYMS  := build/ov_SC03_010/undefined_syms_auto.txt
ov_SC03_010_UNDEF_FUNCS := build/ov_SC03_010/undefined_funcs_auto.txt

# --- ov_SC03_011 (location overlay SC03/FILE_011, vram 0x80128158 — onboarded by new_overlay.sh) ---
ov_SC03_011_EXE        := extracted/retail/SC03.CD.dir/FILE_011.dir/0.4.dec
ov_SC03_011_NAME       := ov_SC03_011
ov_SC03_011_OUT_DIR    := build/ov_SC03_011
ov_SC03_011_OUT        := $(ov_SC03_011_OUT_DIR)/$(ov_SC03_011_NAME)
ov_SC03_011_ELF        := $(ov_SC03_011_OUT).elf
ov_SC03_011_MAPFILE    := $(ov_SC03_011_OUT).map
ov_SC03_011_LD_SCRIPT  := $(ov_SC03_011_OUT).ld
ov_SC03_011_SPLAT_YAML := config/splat.ov_SC03_011.yaml
ov_SC03_011_JTBL_INTERLEAVE := --order tail.data.o,ov_SC03_011.o,ov_SC03_011_jr_8012ACE0.o,tail2.data.o,ov_SC03_011_jr_80135888.o,tail3.data.o,ov_SC03_011_jr_80135A4C.o,tail4.data.o,ov_SC03_011_jr_80135D20.o,tail5.data.o,ov_SC03_011_jr_801380E0.o,ov_SC03_011_o0c.o,tail6.data.o,ov_SC03_011_jr_8013F350.o,tail7.data.o,ov_SC03_011_jr_8014032C.o,tail8.data.o,ov_SC03_011_jr_80140608.o,tail9.data.o,ov_SC03_011_jr_8015444C.o,ov_SC03_011_jr_80154C24.o,ov_SC03_011_jr_801588CC.o,ov_SC03_011_jr_80159C84.o,tail10.data.o,ov_SC03_011_jr_8015A3C8.o,tail11.data.o,ov_SC03_011_jr_8015AE2C.o,tail12.data.o,ov_SC03_011_jr_8015C32C.o,tail13.data.o,ov_SC03_011_jr_8016AB6C.o,tail14.data.o,ov_SC03_011_jr_80171B4C.o,ov_SC03_011_jr_801734BC.o,tail15.data.o,ov_SC03_011_jr_801789AC.o,ov_SC03_011_jr_80178D40.o,tail16.data.o,ov_SC03_011_jr_8017A4AC.o,tail17.data.o,ov_SC03_011_jr_8017AE2C.o,ov_SC03_011_jr_8017C730.o,tail18.data.o,trailing.o  # Phase-26 §8 jtbl-rodata carve
build/src/ov_SC03_011/ov_SC03_011.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14
build/src/ov_SC03_011/ov_SC03_011_jr_8012ACE0.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0xcc,+0xe0
build/src/ov_SC03_011/ov_SC03_011_jr_80135D20.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC03_011/ov_SC03_011_jr_8013F350.o: JTBL_PADS := 0,0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38,+0x58
build/src/ov_SC03_011/ov_SC03_011_jr_8014032C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_011/ov_SC03_011_jr_8015444C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x70
build/src/ov_SC03_011/ov_SC03_011_jr_80154C24.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x24
build/src/ov_SC03_011/ov_SC03_011_jr_801588CC.o: JTBL_PADS := 0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x28,+0x48
build/src/ov_SC03_011/ov_SC03_011_jr_80159C84.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_011/ov_SC03_011_jr_8015AE2C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_011/ov_SC03_011_jr_8016AB6C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_011/ov_SC03_011_jr_80178D40.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x178
build/src/ov_SC03_011/ov_SC03_011_o0c.o: JTBL_PADS := 0,4,4,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x38,+0xa8,+0x118
ov_SC03_011_CHECK_SHA  := config/check.ov_SC03_011.sha
ov_SC03_011_SYMBOLS    := config/symbols.ov_SC03_011.txt
ov_SC03_011_SIG        := .run/sig.ov_SC03_011.jsonl
ov_SC03_011_GHIDRA_PROG := ov_SC03_011
ov_SC03_011_VRAM_BASE  := 0x80128158
ov_SC03_011_TEXT_LO    := 0x80128158
ov_SC03_011_TEXT_HI    := 0x801A2403
ov_SC03_011_ASM_DIR     := asm/ov_SC03_011
ov_SC03_011_SRC_DIR     := src/ov_SC03_011
ov_SC03_011_UNDEF_SYMS  := build/ov_SC03_011/undefined_syms_auto.txt
ov_SC03_011_UNDEF_FUNCS := build/ov_SC03_011/undefined_funcs_auto.txt

# --- ov_SC03_012 (location overlay SC03/FILE_012, vram 0x80128158 — onboarded by new_overlay.sh) ---
ov_SC03_012_EXE        := extracted/retail/SC03.CD.dir/FILE_012.dir/0.4.dec
ov_SC03_012_NAME       := ov_SC03_012
ov_SC03_012_OUT_DIR    := build/ov_SC03_012
ov_SC03_012_OUT        := $(ov_SC03_012_OUT_DIR)/$(ov_SC03_012_NAME)
ov_SC03_012_ELF        := $(ov_SC03_012_OUT).elf
ov_SC03_012_MAPFILE    := $(ov_SC03_012_OUT).map
ov_SC03_012_LD_SCRIPT  := $(ov_SC03_012_OUT).ld
ov_SC03_012_SPLAT_YAML := config/splat.ov_SC03_012.yaml
ov_SC03_012_JTBL_INTERLEAVE := --order tail.data.o,ov_SC03_012.o,ov_SC03_012_jr_8012ACE0.o,tail2.data.o,ov_SC03_012_jr_80135888.o,tail3.data.o,ov_SC03_012_jr_80135A4C.o,tail4.data.o,ov_SC03_012_jr_80135D20.o,tail5.data.o,ov_SC03_012_jr_801380E0.o,ov_SC03_012_o0c.o,tail6.data.o,ov_SC03_012_jr_8013F350.o,tail7.data.o,ov_SC03_012_jr_8013FFD8.o,tail8.data.o,ov_SC03_012_jr_80140608.o,tail9.data.o,ov_SC03_012_jr_8015444C.o,ov_SC03_012_jr_80154C24.o,ov_SC03_012_jr_801588CC.o,ov_SC03_012_jr_80159C84.o,tail10.data.o,ov_SC03_012_jr_8015A3C8.o,tail11.data.o,ov_SC03_012_jr_8015AE2C.o,tail12.data.o,ov_SC03_012_jr_8015C32C.o,tail13.data.o,ov_SC03_012_jr_8016AB6C.o,tail14.data.o,ov_SC03_012_jr_80171B4C.o,ov_SC03_012_jr_801734BC.o,tail15.data.o,ov_SC03_012_jr_801789AC.o,ov_SC03_012_jr_80178D40.o,tail16.data.o,ov_SC03_012_jr_8017A4AC.o,tail17.data.o,ov_SC03_012_jr_8017AE2C.o,tail18.data.o,trailing.o  # Phase-26 §8 jtbl-rodata carve
build/src/ov_SC03_012/ov_SC03_012.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14
build/src/ov_SC03_012/ov_SC03_012_jr_8012ACE0.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0xcc,+0xe0
build/src/ov_SC03_012/ov_SC03_012_jr_80135D20.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC03_012/ov_SC03_012_jr_8013F350.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_012/ov_SC03_012_jr_8013FFD8.o: JTBL_PADS := 0,0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38,+0x58
build/src/ov_SC03_012/ov_SC03_012_jr_8015444C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x70
build/src/ov_SC03_012/ov_SC03_012_jr_80154C24.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x24
build/src/ov_SC03_012/ov_SC03_012_jr_801588CC.o: JTBL_PADS := 0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x28,+0x48
build/src/ov_SC03_012/ov_SC03_012_jr_80159C84.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_012/ov_SC03_012_jr_8015AE2C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_012/ov_SC03_012_jr_8016AB6C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_012/ov_SC03_012_jr_80178D40.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x178
build/src/ov_SC03_012/ov_SC03_012_jr_8017AE2C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14
build/src/ov_SC03_012/ov_SC03_012_o0c.o: JTBL_PADS := 0,4,4,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x38,+0xa8,+0x118
ov_SC03_012_CHECK_SHA  := config/check.ov_SC03_012.sha
ov_SC03_012_SYMBOLS    := config/symbols.ov_SC03_012.txt
ov_SC03_012_SIG        := .run/sig.ov_SC03_012.jsonl
ov_SC03_012_GHIDRA_PROG := ov_SC03_012
ov_SC03_012_VRAM_BASE  := 0x80128158
ov_SC03_012_TEXT_LO    := 0x80128158
ov_SC03_012_TEXT_HI    := 0x8019515F
ov_SC03_012_ASM_DIR     := asm/ov_SC03_012
ov_SC03_012_SRC_DIR     := src/ov_SC03_012
ov_SC03_012_UNDEF_SYMS  := build/ov_SC03_012/undefined_syms_auto.txt
ov_SC03_012_UNDEF_FUNCS := build/ov_SC03_012/undefined_funcs_auto.txt

# --- ov_SC03_013 (location overlay SC03/FILE_013, vram 0x80128158 — onboarded by new_overlay.sh) ---
ov_SC03_013_EXE        := extracted/retail/SC03.CD.dir/FILE_013.dir/0.4.dec
ov_SC03_013_NAME       := ov_SC03_013
ov_SC03_013_OUT_DIR    := build/ov_SC03_013
ov_SC03_013_OUT        := $(ov_SC03_013_OUT_DIR)/$(ov_SC03_013_NAME)
ov_SC03_013_ELF        := $(ov_SC03_013_OUT).elf
ov_SC03_013_MAPFILE    := $(ov_SC03_013_OUT).map
ov_SC03_013_LD_SCRIPT  := $(ov_SC03_013_OUT).ld
ov_SC03_013_SPLAT_YAML := config/splat.ov_SC03_013.yaml
ov_SC03_013_JTBL_INTERLEAVE := --order tail.data.o,ov_SC03_013.o,ov_SC03_013_jr_8012ACE0.o,tail2.data.o,ov_SC03_013_jr_80135888.o,tail3.data.o,ov_SC03_013_jr_80135A4C.o,tail4.data.o,ov_SC03_013_jr_80135D20.o,tail5.data.o,ov_SC03_013_jr_801380E0.o,ov_SC03_013_o0c.o,tail6.data.o,ov_SC03_013_jr_8013F350.o,tail7.data.o,ov_SC03_013_jr_8013FFD8.o,tail8.data.o,ov_SC03_013_jr_80140608.o,tail9.data.o,ov_SC03_013_jr_8015444C.o,ov_SC03_013_jr_80154C24.o,ov_SC03_013_jr_801588CC.o,ov_SC03_013_jr_80159C84.o,tail10.data.o,ov_SC03_013_jr_8015A3C8.o,tail11.data.o,ov_SC03_013_jr_8015AE2C.o,tail12.data.o,ov_SC03_013_jr_8015C32C.o,tail13.data.o,ov_SC03_013_jr_8016AB6C.o,tail14.data.o,ov_SC03_013_jr_80171B4C.o,ov_SC03_013_jr_801734BC.o,tail15.data.o,ov_SC03_013_jr_801789AC.o,ov_SC03_013_jr_80178D40.o,tail16.data.o,ov_SC03_013_jr_8017A4AC.o,tail17.data.o,ov_SC03_013_jr_8017AE2C.o,ov_SC03_013_jr_8017C730.o,tail18.data.o,ov_SC03_013_jr_801806F8.o,tail19.data.o,trailing.o  # Phase-26 §8 jtbl-rodata carve
build/src/ov_SC03_013/ov_SC03_013.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14
build/src/ov_SC03_013/ov_SC03_013_jr_8012ACE0.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0xcc,+0xe0
build/src/ov_SC03_013/ov_SC03_013_jr_80135D20.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC03_013/ov_SC03_013_jr_8013F350.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_013/ov_SC03_013_jr_8013FFD8.o: JTBL_PADS := 0,0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38,+0x58
build/src/ov_SC03_013/ov_SC03_013_jr_8015444C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x70
build/src/ov_SC03_013/ov_SC03_013_jr_80154C24.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x24
build/src/ov_SC03_013/ov_SC03_013_jr_801588CC.o: JTBL_PADS := 0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x28,+0x48
build/src/ov_SC03_013/ov_SC03_013_jr_80159C84.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_013/ov_SC03_013_jr_8015AE2C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_013/ov_SC03_013_jr_8016AB6C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_013/ov_SC03_013_jr_80178D40.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x178
build/src/ov_SC03_013/ov_SC03_013_o0c.o: JTBL_PADS := 0,4,4,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x38,+0xa8,+0x118
ov_SC03_013_CHECK_SHA  := config/check.ov_SC03_013.sha
ov_SC03_013_SYMBOLS    := config/symbols.ov_SC03_013.txt
ov_SC03_013_SIG        := .run/sig.ov_SC03_013.jsonl
ov_SC03_013_GHIDRA_PROG := ov_SC03_013
ov_SC03_013_VRAM_BASE  := 0x80128158
ov_SC03_013_TEXT_LO    := 0x80128158
ov_SC03_013_TEXT_HI    := 0x801AD557
ov_SC03_013_ASM_DIR     := asm/ov_SC03_013
ov_SC03_013_SRC_DIR     := src/ov_SC03_013
ov_SC03_013_UNDEF_SYMS  := build/ov_SC03_013/undefined_syms_auto.txt
ov_SC03_013_UNDEF_FUNCS := build/ov_SC03_013/undefined_funcs_auto.txt

# --- ov_SC03_014 (location overlay SC03/FILE_014, vram 0x80128158 — onboarded by new_overlay.sh) ---
ov_SC03_014_EXE        := extracted/retail/SC03.CD.dir/FILE_014.dir/0.4.dec
ov_SC03_014_NAME       := ov_SC03_014
ov_SC03_014_OUT_DIR    := build/ov_SC03_014
ov_SC03_014_OUT        := $(ov_SC03_014_OUT_DIR)/$(ov_SC03_014_NAME)
ov_SC03_014_ELF        := $(ov_SC03_014_OUT).elf
ov_SC03_014_MAPFILE    := $(ov_SC03_014_OUT).map
ov_SC03_014_LD_SCRIPT  := $(ov_SC03_014_OUT).ld
ov_SC03_014_SPLAT_YAML := config/splat.ov_SC03_014.yaml
ov_SC03_014_JTBL_INTERLEAVE := --order tail.data.o,ov_SC03_014.o,ov_SC03_014_jr_8012ACE0.o,tail2.data.o,ov_SC03_014_jr_80135888.o,tail3.data.o,ov_SC03_014_jr_80135A4C.o,tail4.data.o,ov_SC03_014_jr_80135D20.o,tail5.data.o,ov_SC03_014_jr_801380E0.o,ov_SC03_014_o0e.o,tail6.data.o,ov_SC03_014_jr_8013F350.o,tail7.data.o,ov_SC03_014_jr_8013FFD8.o,tail8.data.o,ov_SC03_014_jr_80140608.o,tail9.data.o,ov_SC03_014_jr_8015444C.o,ov_SC03_014_jr_80154C24.o,ov_SC03_014_jr_801588CC.o,ov_SC03_014_jr_80159C84.o,tail10.data.o,ov_SC03_014_jr_8015A3C8.o,tail11.data.o,ov_SC03_014_jr_8015AE2C.o,tail12.data.o,ov_SC03_014_jr_8015C32C.o,tail13.data.o,ov_SC03_014_jr_8016AB6C.o,tail14.data.o,ov_SC03_014_jr_80171B4C.o,ov_SC03_014_jr_801734BC.o,tail15.data.o,ov_SC03_014_jr_801789AC.o,ov_SC03_014_jr_80178D40.o,tail16.data.o,ov_SC03_014_jr_8017A4AC.o,tail17.data.o,ov_SC03_014_jr_8017AE2C.o,ov_SC03_014_jr_8017EB7C.o,tail18.data.o,ov_SC03_014_jr_801848E4.o,tail19.data.o,trailing.o  # Phase-26 §8 jtbl-rodata carve
build/src/ov_SC03_014/ov_SC03_014.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14
build/src/ov_SC03_014/ov_SC03_014_jr_8012ACE0.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0xcc,+0xe0
build/src/ov_SC03_014/ov_SC03_014_jr_80135D20.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC03_014/ov_SC03_014_jr_8013F350.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_014/ov_SC03_014_jr_8013FFD8.o: JTBL_PADS := 0,0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38,+0x58
build/src/ov_SC03_014/ov_SC03_014_jr_8015444C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x70
build/src/ov_SC03_014/ov_SC03_014_jr_80154C24.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x24
build/src/ov_SC03_014/ov_SC03_014_jr_801588CC.o: JTBL_PADS := 0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x28,+0x48
build/src/ov_SC03_014/ov_SC03_014_jr_80159C84.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_014/ov_SC03_014_jr_8015AE2C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_014/ov_SC03_014_jr_8016AB6C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_014/ov_SC03_014_jr_80178D40.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x178
build/src/ov_SC03_014/ov_SC03_014_jr_8017AE2C.o: JTBL_PADS := 0,0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14,+0x2c
build/src/ov_SC03_014/ov_SC03_014_jr_801848E4.o: JTBL_PADS := 0,0,0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18,+0x30,+0x50,+0x68
build/src/ov_SC03_014/ov_SC03_014_o0e.o: JTBL_PADS := 0,4,4,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x38,+0xa8,+0x118
ov_SC03_014_CHECK_SHA  := config/check.ov_SC03_014.sha
ov_SC03_014_SYMBOLS    := config/symbols.ov_SC03_014.txt
ov_SC03_014_SIG        := .run/sig.ov_SC03_014.jsonl
ov_SC03_014_GHIDRA_PROG := ov_SC03_014
ov_SC03_014_VRAM_BASE  := 0x80128158
ov_SC03_014_TEXT_LO    := 0x80128158
ov_SC03_014_TEXT_HI    := 0x801EB03F
ov_SC03_014_ASM_DIR     := asm/ov_SC03_014
ov_SC03_014_SRC_DIR     := src/ov_SC03_014
ov_SC03_014_UNDEF_SYMS  := build/ov_SC03_014/undefined_syms_auto.txt
ov_SC03_014_UNDEF_FUNCS := build/ov_SC03_014/undefined_funcs_auto.txt

# --- ov_SC03_015 (location overlay SC03/FILE_015, vram 0x80128158 — onboarded by new_overlay.sh) ---
ov_SC03_015_EXE        := extracted/retail/SC03.CD.dir/FILE_015.dir/0.4.dec
ov_SC03_015_NAME       := ov_SC03_015
ov_SC03_015_OUT_DIR    := build/ov_SC03_015
ov_SC03_015_OUT        := $(ov_SC03_015_OUT_DIR)/$(ov_SC03_015_NAME)
ov_SC03_015_ELF        := $(ov_SC03_015_OUT).elf
ov_SC03_015_MAPFILE    := $(ov_SC03_015_OUT).map
ov_SC03_015_LD_SCRIPT  := $(ov_SC03_015_OUT).ld
ov_SC03_015_SPLAT_YAML := config/splat.ov_SC03_015.yaml
ov_SC03_015_JTBL_INTERLEAVE := --order tail.data.o,ov_SC03_015.o,ov_SC03_015_jr_8012ACE0.o,tail2.data.o,ov_SC03_015_jr_80135888.o,tail3.data.o,ov_SC03_015_jr_80135A4C.o,tail4.data.o,ov_SC03_015_jr_80135D20.o,tail5.data.o,ov_SC03_015_jr_801380E0.o,ov_SC03_015_o0e.o,tail6.data.o,ov_SC03_015_jr_8013F350.o,tail7.data.o,ov_SC03_015_jr_8013FFD8.o,tail8.data.o,ov_SC03_015_jr_80140608.o,tail9.data.o,ov_SC03_015_jr_8015444C.o,ov_SC03_015_jr_80154C24.o,ov_SC03_015_jr_801588CC.o,ov_SC03_015_jr_80159C84.o,tail10.data.o,ov_SC03_015_jr_8015A3C8.o,tail11.data.o,ov_SC03_015_jr_8015AE2C.o,tail12.data.o,ov_SC03_015_jr_8015C32C.o,tail13.data.o,ov_SC03_015_jr_8016AB6C.o,tail14.data.o,ov_SC03_015_jr_80171B4C.o,ov_SC03_015_jr_801734BC.o,tail15.data.o,ov_SC03_015_jr_801789AC.o,ov_SC03_015_jr_80178D40.o,tail16.data.o,ov_SC03_015_jr_8017A4AC.o,tail17.data.o,ov_SC03_015_jr_8017AE2C.o,ov_SC03_015_jr_8017EB7C.o,tail18.data.o,ov_SC03_015_jr_80184F14.o,ov_SC03_015_jr_80185B44.o,tail19.data.o,trailing.o  # Phase-26 §8 jtbl-rodata carve
build/src/ov_SC03_015/ov_SC03_015.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14
build/src/ov_SC03_015/ov_SC03_015_jr_8012ACE0.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0xcc,+0xe0
build/src/ov_SC03_015/ov_SC03_015_jr_80135D20.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC03_015/ov_SC03_015_jr_8013F350.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_015/ov_SC03_015_jr_8013FFD8.o: JTBL_PADS := 0,0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38,+0x58
build/src/ov_SC03_015/ov_SC03_015_jr_8015444C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x70
build/src/ov_SC03_015/ov_SC03_015_jr_80154C24.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x24
build/src/ov_SC03_015/ov_SC03_015_jr_801588CC.o: JTBL_PADS := 0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x28,+0x48
build/src/ov_SC03_015/ov_SC03_015_jr_80159C84.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_015/ov_SC03_015_jr_8015AE2C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_015/ov_SC03_015_jr_8016AB6C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_015/ov_SC03_015_jr_80178D40.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x178
build/src/ov_SC03_015/ov_SC03_015_jr_8017AE2C.o: JTBL_PADS := 0,0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14,+0x2c
build/src/ov_SC03_015/ov_SC03_015_jr_80185B44.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38
build/src/ov_SC03_015/ov_SC03_015_o0e.o: JTBL_PADS := 0,4,4,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x38,+0xa8,+0x118
ov_SC03_015_CHECK_SHA  := config/check.ov_SC03_015.sha
ov_SC03_015_SYMBOLS    := config/symbols.ov_SC03_015.txt
ov_SC03_015_SIG        := .run/sig.ov_SC03_015.jsonl
ov_SC03_015_GHIDRA_PROG := ov_SC03_015
ov_SC03_015_VRAM_BASE  := 0x80128158
ov_SC03_015_TEXT_LO    := 0x80128158
ov_SC03_015_TEXT_HI    := 0x801EB03F
ov_SC03_015_ASM_DIR     := asm/ov_SC03_015
ov_SC03_015_SRC_DIR     := src/ov_SC03_015
ov_SC03_015_UNDEF_SYMS  := build/ov_SC03_015/undefined_syms_auto.txt
ov_SC03_015_UNDEF_FUNCS := build/ov_SC03_015/undefined_funcs_auto.txt

# --- ov_SC03_023 (location overlay SC03/FILE_023, vram 0x80128158 — onboarded by new_overlay.sh) ---
ov_SC03_023_EXE        := extracted/retail/SC03.CD.dir/FILE_023.dir/0.4.dec
ov_SC03_023_NAME       := ov_SC03_023
ov_SC03_023_OUT_DIR    := build/ov_SC03_023
ov_SC03_023_OUT        := $(ov_SC03_023_OUT_DIR)/$(ov_SC03_023_NAME)
ov_SC03_023_ELF        := $(ov_SC03_023_OUT).elf
ov_SC03_023_MAPFILE    := $(ov_SC03_023_OUT).map
ov_SC03_023_LD_SCRIPT  := $(ov_SC03_023_OUT).ld
ov_SC03_023_SPLAT_YAML := config/splat.ov_SC03_023.yaml
ov_SC03_023_JTBL_INTERLEAVE := --order tail.data.o,ov_SC03_023.o,ov_SC03_023_jr_8012ACE0.o,tail2.data.o,ov_SC03_023_jr_80135888.o,tail3.data.o,ov_SC03_023_jr_80135A4C.o,tail4.data.o,ov_SC03_023_jr_80135D20.o,tail5.data.o,ov_SC03_023_jr_801380E0.o,ov_SC03_023_o0c.o,tail6.data.o,ov_SC03_023_jr_8013F350.o,tail7.data.o,ov_SC03_023_jr_8013FFD8.o,tail8.data.o,ov_SC03_023_jr_80140608.o,tail9.data.o,ov_SC03_023_jr_8015444C.o,ov_SC03_023_jr_80154C24.o,ov_SC03_023_jr_801588CC.o,ov_SC03_023_jr_80159C84.o,tail10.data.o,ov_SC03_023_jr_8015A3C8.o,tail11.data.o,ov_SC03_023_jr_8015AE2C.o,tail12.data.o,ov_SC03_023_jr_8015C32C.o,tail13.data.o,ov_SC03_023_jr_8016AB6C.o,tail14.data.o,ov_SC03_023_jr_80171B4C.o,ov_SC03_023_jr_801734BC.o,tail15.data.o,ov_SC03_023_jr_801789AC.o,ov_SC03_023_jr_80178D40.o,tail16.data.o,ov_SC03_023_jr_8017A4AC.o,tail17.data.o,ov_SC03_023_jr_8017AE2C.o,tail18.data.o,trailing.o  # Phase-26 §8 jtbl-rodata carve
build/src/ov_SC03_023/ov_SC03_023.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14
build/src/ov_SC03_023/ov_SC03_023_jr_8012ACE0.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0xcc,+0xe0
build/src/ov_SC03_023/ov_SC03_023_jr_80135D20.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC03_023/ov_SC03_023_jr_8013F350.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_023/ov_SC03_023_jr_8013FFD8.o: JTBL_PADS := 0,0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38,+0x58
build/src/ov_SC03_023/ov_SC03_023_jr_8015444C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x70
build/src/ov_SC03_023/ov_SC03_023_jr_80154C24.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x24
build/src/ov_SC03_023/ov_SC03_023_jr_801588CC.o: JTBL_PADS := 0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x28,+0x48
build/src/ov_SC03_023/ov_SC03_023_jr_80159C84.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_023/ov_SC03_023_jr_8015AE2C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_023/ov_SC03_023_jr_8016AB6C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_023/ov_SC03_023_jr_80178D40.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x178
build/src/ov_SC03_023/ov_SC03_023_jr_8017AE2C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14
build/src/ov_SC03_023/ov_SC03_023_o0c.o: JTBL_PADS := 0,4,4,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x38,+0xa8,+0x118
ov_SC03_023_CHECK_SHA  := config/check.ov_SC03_023.sha
ov_SC03_023_SYMBOLS    := config/symbols.ov_SC03_023.txt
ov_SC03_023_SIG        := .run/sig.ov_SC03_023.jsonl
ov_SC03_023_GHIDRA_PROG := ov_SC03_023
ov_SC03_023_VRAM_BASE  := 0x80128158
ov_SC03_023_TEXT_LO    := 0x80128158
ov_SC03_023_TEXT_HI    := 0x80198D87
ov_SC03_023_ASM_DIR     := asm/ov_SC03_023
ov_SC03_023_SRC_DIR     := src/ov_SC03_023
ov_SC03_023_UNDEF_SYMS  := build/ov_SC03_023/undefined_syms_auto.txt
ov_SC03_023_UNDEF_FUNCS := build/ov_SC03_023/undefined_funcs_auto.txt

# --- ov_SC03_024 (location overlay SC03/FILE_024, vram 0x80128158 — onboarded by new_overlay.sh) ---
ov_SC03_024_EXE        := extracted/retail/SC03.CD.dir/FILE_024.dir/0.4.dec
ov_SC03_024_NAME       := ov_SC03_024
ov_SC03_024_OUT_DIR    := build/ov_SC03_024
ov_SC03_024_OUT        := $(ov_SC03_024_OUT_DIR)/$(ov_SC03_024_NAME)
ov_SC03_024_ELF        := $(ov_SC03_024_OUT).elf
ov_SC03_024_MAPFILE    := $(ov_SC03_024_OUT).map
ov_SC03_024_LD_SCRIPT  := $(ov_SC03_024_OUT).ld
ov_SC03_024_SPLAT_YAML := config/splat.ov_SC03_024.yaml
ov_SC03_024_JTBL_INTERLEAVE := --order tail.data.o,ov_SC03_024.o,ov_SC03_024_jr_8012ACE0.o,tail2.data.o,ov_SC03_024_jr_80135888.o,tail3.data.o,ov_SC03_024_jr_80135A4C.o,tail4.data.o,ov_SC03_024_jr_80135D20.o,tail5.data.o,ov_SC03_024_jr_801380E0.o,ov_SC03_024_o0c.o,tail6.data.o,ov_SC03_024_jr_8013F350.o,tail7.data.o,ov_SC03_024_jr_8013FFD8.o,tail8.data.o,ov_SC03_024_jr_80140608.o,tail9.data.o,ov_SC03_024_jr_8015444C.o,ov_SC03_024_jr_80154C24.o,ov_SC03_024_jr_801588CC.o,ov_SC03_024_jr_80159C84.o,tail10.data.o,ov_SC03_024_jr_8015A3C8.o,tail11.data.o,ov_SC03_024_jr_8015AE2C.o,tail12.data.o,ov_SC03_024_jr_8015C32C.o,tail13.data.o,ov_SC03_024_jr_8016AB6C.o,tail14.data.o,ov_SC03_024_jr_80171B4C.o,ov_SC03_024_jr_801734BC.o,tail15.data.o,ov_SC03_024_jr_801789AC.o,ov_SC03_024_jr_80178D40.o,tail16.data.o,ov_SC03_024_jr_8017A4AC.o,tail17.data.o,ov_SC03_024_jr_8017AE2C.o,ov_SC03_024_jr_8017DF84.o,tail18.data.o,ov_SC03_024_jr_80183BF8.o,tail19.data.o,trailing.o  # Phase-26 §8 jtbl-rodata carve
build/src/ov_SC03_024/ov_SC03_024.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14
build/src/ov_SC03_024/ov_SC03_024_jr_8012ACE0.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0xcc,+0xe0
build/src/ov_SC03_024/ov_SC03_024_jr_80135D20.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC03_024/ov_SC03_024_jr_8013F350.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_024/ov_SC03_024_jr_8013FFD8.o: JTBL_PADS := 0,0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38,+0x58
build/src/ov_SC03_024/ov_SC03_024_jr_8015444C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x70
build/src/ov_SC03_024/ov_SC03_024_jr_80154C24.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x24
build/src/ov_SC03_024/ov_SC03_024_jr_801588CC.o: JTBL_PADS := 0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x28,+0x48
build/src/ov_SC03_024/ov_SC03_024_jr_80159C84.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_024/ov_SC03_024_jr_8015AE2C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_024/ov_SC03_024_jr_8016AB6C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_024/ov_SC03_024_jr_80178D40.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x178
build/src/ov_SC03_024/ov_SC03_024_jr_8017AE2C.o: JTBL_PADS := 0,0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14,+0x2c
build/src/ov_SC03_024/ov_SC03_024_o0c.o: JTBL_PADS := 0,4,4,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x38,+0xa8,+0x118
ov_SC03_024_CHECK_SHA  := config/check.ov_SC03_024.sha
ov_SC03_024_SYMBOLS    := config/symbols.ov_SC03_024.txt
ov_SC03_024_SIG        := .run/sig.ov_SC03_024.jsonl
ov_SC03_024_GHIDRA_PROG := ov_SC03_024
ov_SC03_024_VRAM_BASE  := 0x80128158
ov_SC03_024_TEXT_LO    := 0x80128158
ov_SC03_024_TEXT_HI    := 0x801C184F
ov_SC03_024_ASM_DIR     := asm/ov_SC03_024
ov_SC03_024_SRC_DIR     := src/ov_SC03_024
ov_SC03_024_UNDEF_SYMS  := build/ov_SC03_024/undefined_syms_auto.txt
ov_SC03_024_UNDEF_FUNCS := build/ov_SC03_024/undefined_funcs_auto.txt

# --- ov_SC03_028 (location overlay SC03/FILE_028, vram 0x80128158 — onboarded by new_overlay.sh) ---
ov_SC03_028_EXE        := extracted/retail/SC03.CD.dir/FILE_028.dir/0.4.dec
ov_SC03_028_NAME       := ov_SC03_028
ov_SC03_028_OUT_DIR    := build/ov_SC03_028
ov_SC03_028_OUT        := $(ov_SC03_028_OUT_DIR)/$(ov_SC03_028_NAME)
ov_SC03_028_ELF        := $(ov_SC03_028_OUT).elf
ov_SC03_028_MAPFILE    := $(ov_SC03_028_OUT).map
ov_SC03_028_LD_SCRIPT  := $(ov_SC03_028_OUT).ld
ov_SC03_028_SPLAT_YAML := config/splat.ov_SC03_028.yaml
ov_SC03_028_JTBL_INTERLEAVE := --order tail.data.o,ov_SC03_028.o,ov_SC03_028_jr_8012ACE0.o,tail2.data.o,ov_SC03_028_jr_80135888.o,tail3.data.o,ov_SC03_028_jr_80135A4C.o,tail4.data.o,ov_SC03_028_jr_80135D20.o,tail5.data.o,ov_SC03_028_jr_801380E0.o,ov_SC03_028_o0c.o,tail6.data.o,ov_SC03_028_jr_8013F350.o,tail7.data.o,ov_SC03_028_jr_8013FFD8.o,tail8.data.o,ov_SC03_028_jr_80140608.o,tail9.data.o,ov_SC03_028_jr_8015444C.o,ov_SC03_028_jr_80154C24.o,ov_SC03_028_jr_801588CC.o,ov_SC03_028_jr_80159C84.o,tail10.data.o,ov_SC03_028_jr_8015A3C8.o,tail11.data.o,ov_SC03_028_jr_8015AE2C.o,tail12.data.o,ov_SC03_028_jr_8015C32C.o,tail13.data.o,ov_SC03_028_jr_8016AB6C.o,tail14.data.o,ov_SC03_028_jr_80171B4C.o,ov_SC03_028_jr_801734BC.o,tail15.data.o,ov_SC03_028_jr_801789AC.o,ov_SC03_028_jr_80178D40.o,tail16.data.o,ov_SC03_028_jr_8017A4AC.o,tail17.data.o,ov_SC03_028_jr_8017AE2C.o,tail18.data.o,ov_SC03_028_jr_8017DF98.o,tail19.data.o,ov_SC03_028_jr_80183A74.o,ov_SC03_028_jr_801847E8.o,tail20.data.o,ov_SC03_028_jr_80184914.o,tail21.data.o,ov_SC03_028_jr_80185864.o,tail22.data.o,ov_SC03_028_jr_80185C14.o,tail23.data.o,ov_SC03_028_jr_801887A8.o,tail24.data.o,trailing.o  # Phase-26 §8 jtbl-rodata carve
build/src/ov_SC03_028/ov_SC03_028.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14
build/src/ov_SC03_028/ov_SC03_028_jr_8012ACE0.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0xcc,+0xe0
build/src/ov_SC03_028/ov_SC03_028_jr_80135D20.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC03_028/ov_SC03_028_jr_8013F350.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_028/ov_SC03_028_jr_8013FFD8.o: JTBL_PADS := 0,0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38,+0x58
build/src/ov_SC03_028/ov_SC03_028_jr_8015444C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x70
build/src/ov_SC03_028/ov_SC03_028_jr_80154C24.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x24
build/src/ov_SC03_028/ov_SC03_028_jr_801588CC.o: JTBL_PADS := 0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x28,+0x48
build/src/ov_SC03_028/ov_SC03_028_jr_80159C84.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_028/ov_SC03_028_jr_8015AE2C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_028/ov_SC03_028_jr_8016AB6C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_028/ov_SC03_028_jr_80178D40.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x178
build/src/ov_SC03_028/ov_SC03_028_jr_8017DF98.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x40
build/src/ov_SC03_028/ov_SC03_028_jr_80184914.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x30
build/src/ov_SC03_028/ov_SC03_028_jr_80185864.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x28
build/src/ov_SC03_028/ov_SC03_028_o0c.o: JTBL_PADS := 0,4,4,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x38,+0xa8,+0x118
ov_SC03_028_CHECK_SHA  := config/check.ov_SC03_028.sha
ov_SC03_028_SYMBOLS    := config/symbols.ov_SC03_028.txt
ov_SC03_028_SIG        := .run/sig.ov_SC03_028.jsonl
ov_SC03_028_GHIDRA_PROG := ov_SC03_028
ov_SC03_028_VRAM_BASE  := 0x80128158
ov_SC03_028_TEXT_LO    := 0x80128158
ov_SC03_028_TEXT_HI    := 0x801EC607
ov_SC03_028_ASM_DIR     := asm/ov_SC03_028
ov_SC03_028_SRC_DIR     := src/ov_SC03_028
ov_SC03_028_UNDEF_SYMS  := build/ov_SC03_028/undefined_syms_auto.txt
ov_SC03_028_UNDEF_FUNCS := build/ov_SC03_028/undefined_funcs_auto.txt

# --- ov_SC03_029 (location overlay SC03/FILE_029, vram 0x80128158 — onboarded by new_overlay.sh) ---
ov_SC03_029_EXE        := extracted/retail/SC03.CD.dir/FILE_029.dir/0.4.dec
ov_SC03_029_NAME       := ov_SC03_029
ov_SC03_029_OUT_DIR    := build/ov_SC03_029
ov_SC03_029_OUT        := $(ov_SC03_029_OUT_DIR)/$(ov_SC03_029_NAME)
ov_SC03_029_ELF        := $(ov_SC03_029_OUT).elf
ov_SC03_029_MAPFILE    := $(ov_SC03_029_OUT).map
ov_SC03_029_LD_SCRIPT  := $(ov_SC03_029_OUT).ld
ov_SC03_029_SPLAT_YAML := config/splat.ov_SC03_029.yaml
ov_SC03_029_JTBL_INTERLEAVE := --order tail.data.o,ov_SC03_029.o,ov_SC03_029_jr_8012ACE0.o,tail2.data.o,ov_SC03_029_jr_80135888.o,tail3.data.o,ov_SC03_029_jr_80135A4C.o,tail4.data.o,ov_SC03_029_jr_80135D20.o,tail5.data.o,ov_SC03_029_jr_801380E0.o,ov_SC03_029_o0c.o,tail6.data.o,ov_SC03_029_jr_8013F350.o,tail7.data.o,ov_SC03_029_jr_8013FFD8.o,tail8.data.o,ov_SC03_029_jr_80140608.o,tail9.data.o,ov_SC03_029_jr_8015444C.o,ov_SC03_029_jr_80154C24.o,ov_SC03_029_jr_801588CC.o,ov_SC03_029_jr_80159C84.o,tail10.data.o,ov_SC03_029_jr_8015A3C8.o,tail11.data.o,ov_SC03_029_jr_8015AE2C.o,tail12.data.o,ov_SC03_029_jr_8015C32C.o,tail13.data.o,ov_SC03_029_jr_8016AB6C.o,tail14.data.o,ov_SC03_029_jr_80171B4C.o,ov_SC03_029_jr_801734BC.o,tail15.data.o,ov_SC03_029_jr_801789AC.o,ov_SC03_029_jr_80178D40.o,tail16.data.o,ov_SC03_029_jr_8017A4AC.o,tail17.data.o,ov_SC03_029_jr_8017AE2C.o,ov_SC03_029_jr_8017DC70.o,tail18.data.o,ov_SC03_029_jr_8017FF7C.o,tail19.data.o,ov_SC03_029_jr_80186A34.o,tail20.data.o,trailing.o  # Phase-26 §8 jtbl-rodata carve
build/src/ov_SC03_029/ov_SC03_029.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14
build/src/ov_SC03_029/ov_SC03_029_jr_8012ACE0.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0xcc,+0xe0
build/src/ov_SC03_029/ov_SC03_029_jr_80135D20.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC03_029/ov_SC03_029_jr_8013F350.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_029/ov_SC03_029_jr_8013FFD8.o: JTBL_PADS := 0,0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38,+0x58
build/src/ov_SC03_029/ov_SC03_029_jr_8015444C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x70
build/src/ov_SC03_029/ov_SC03_029_jr_80154C24.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x24
build/src/ov_SC03_029/ov_SC03_029_jr_801588CC.o: JTBL_PADS := 0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x28,+0x48
build/src/ov_SC03_029/ov_SC03_029_jr_80159C84.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_029/ov_SC03_029_jr_8015AE2C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_029/ov_SC03_029_jr_8016AB6C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_029/ov_SC03_029_jr_80178D40.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x178
build/src/ov_SC03_029/ov_SC03_029_o0c.o: JTBL_PADS := 0,4,4,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x38,+0xa8,+0x118
ov_SC03_029_CHECK_SHA  := config/check.ov_SC03_029.sha
ov_SC03_029_SYMBOLS    := config/symbols.ov_SC03_029.txt
ov_SC03_029_SIG        := .run/sig.ov_SC03_029.jsonl
ov_SC03_029_GHIDRA_PROG := ov_SC03_029
ov_SC03_029_VRAM_BASE  := 0x80128158
ov_SC03_029_TEXT_LO    := 0x80128158
ov_SC03_029_TEXT_HI    := 0x801D9A47
ov_SC03_029_ASM_DIR     := asm/ov_SC03_029
ov_SC03_029_SRC_DIR     := src/ov_SC03_029
ov_SC03_029_UNDEF_SYMS  := build/ov_SC03_029/undefined_syms_auto.txt
ov_SC03_029_UNDEF_FUNCS := build/ov_SC03_029/undefined_funcs_auto.txt

# --- ov_SC03_030 (location overlay SC03/FILE_030, vram 0x80128158 — onboarded by new_overlay.sh) ---
ov_SC03_030_EXE        := extracted/retail/SC03.CD.dir/FILE_030.dir/0.4.dec
ov_SC03_030_NAME       := ov_SC03_030
ov_SC03_030_OUT_DIR    := build/ov_SC03_030
ov_SC03_030_OUT        := $(ov_SC03_030_OUT_DIR)/$(ov_SC03_030_NAME)
ov_SC03_030_ELF        := $(ov_SC03_030_OUT).elf
ov_SC03_030_MAPFILE    := $(ov_SC03_030_OUT).map
ov_SC03_030_LD_SCRIPT  := $(ov_SC03_030_OUT).ld
ov_SC03_030_SPLAT_YAML := config/splat.ov_SC03_030.yaml
ov_SC03_030_JTBL_INTERLEAVE := --order tail.data.o,ov_SC03_030.o,ov_SC03_030_jr_8012ACE0.o,tail2.data.o,ov_SC03_030_jr_80135888.o,tail3.data.o,ov_SC03_030_jr_80135A4C.o,tail4.data.o,ov_SC03_030_jr_80135D20.o,tail5.data.o,ov_SC03_030_jr_801380E0.o,ov_SC03_030_o0c.o,tail6.data.o,ov_SC03_030_jr_8013F350.o,tail7.data.o,ov_SC03_030_jr_8014032C.o,tail8.data.o,ov_SC03_030_jr_80140608.o,tail9.data.o,ov_SC03_030_jr_8015444C.o,ov_SC03_030_jr_80154C24.o,ov_SC03_030_jr_801588CC.o,ov_SC03_030_jr_80159C84.o,tail10.data.o,ov_SC03_030_jr_8015A3C8.o,tail11.data.o,ov_SC03_030_jr_8015AE2C.o,tail12.data.o,ov_SC03_030_jr_8015C32C.o,tail13.data.o,ov_SC03_030_jr_8016AB6C.o,tail14.data.o,ov_SC03_030_jr_80171B4C.o,ov_SC03_030_jr_801734BC.o,tail15.data.o,ov_SC03_030_jr_801789AC.o,ov_SC03_030_jr_80178D40.o,tail16.data.o,ov_SC03_030_jr_8017A4AC.o,tail17.data.o,ov_SC03_030_jr_8017AE2C.o,tail18.data.o  # Phase-26 §8 jtbl-rodata carve
build/src/ov_SC03_030/ov_SC03_030.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14
build/src/ov_SC03_030/ov_SC03_030_jr_8012ACE0.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0xcc,+0xe0
build/src/ov_SC03_030/ov_SC03_030_jr_80135D20.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC03_030/ov_SC03_030_jr_8013F350.o: JTBL_PADS := 0,0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38,+0x58
build/src/ov_SC03_030/ov_SC03_030_jr_8014032C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_030/ov_SC03_030_jr_8015444C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x70
build/src/ov_SC03_030/ov_SC03_030_jr_80154C24.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x24
build/src/ov_SC03_030/ov_SC03_030_jr_801588CC.o: JTBL_PADS := 0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x28,+0x48
build/src/ov_SC03_030/ov_SC03_030_jr_80159C84.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_030/ov_SC03_030_jr_8015AE2C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_030/ov_SC03_030_jr_8016AB6C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_030/ov_SC03_030_jr_80178D40.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x178
build/src/ov_SC03_030/ov_SC03_030_jr_8017AE2C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14
build/src/ov_SC03_030/ov_SC03_030_o0c.o: JTBL_PADS := 0,4,4,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x38,+0xa8,+0x118
ov_SC03_030_CHECK_SHA  := config/check.ov_SC03_030.sha
ov_SC03_030_SYMBOLS    := config/symbols.ov_SC03_030.txt
ov_SC03_030_SIG        := .run/sig.ov_SC03_030.jsonl
ov_SC03_030_GHIDRA_PROG := ov_SC03_030
ov_SC03_030_VRAM_BASE  := 0x80128158
ov_SC03_030_TEXT_LO    := 0x80128158
ov_SC03_030_TEXT_HI    := 0x801E1C48
ov_SC03_030_ASM_DIR     := asm/ov_SC03_030
ov_SC03_030_SRC_DIR     := src/ov_SC03_030
ov_SC03_030_UNDEF_SYMS  := build/ov_SC03_030/undefined_syms_auto.txt
ov_SC03_030_UNDEF_FUNCS := build/ov_SC03_030/undefined_funcs_auto.txt

# --- ov_SC03_031 (location overlay SC03/FILE_031, vram 0x80128158 — onboarded by new_overlay.sh) ---
ov_SC03_031_EXE        := extracted/retail/SC03.CD.dir/FILE_031.dir/0.4.dec
ov_SC03_031_NAME       := ov_SC03_031
ov_SC03_031_OUT_DIR    := build/ov_SC03_031
ov_SC03_031_OUT        := $(ov_SC03_031_OUT_DIR)/$(ov_SC03_031_NAME)
ov_SC03_031_ELF        := $(ov_SC03_031_OUT).elf
ov_SC03_031_MAPFILE    := $(ov_SC03_031_OUT).map
ov_SC03_031_LD_SCRIPT  := $(ov_SC03_031_OUT).ld
ov_SC03_031_SPLAT_YAML := config/splat.ov_SC03_031.yaml
ov_SC03_031_JTBL_INTERLEAVE := --order tail.data.o,ov_SC03_031.o,ov_SC03_031_jr_8012ACE0.o,tail2.data.o,ov_SC03_031_jr_80135888.o,tail3.data.o,ov_SC03_031_jr_80135A4C.o,tail4.data.o,ov_SC03_031_jr_80135D20.o,tail5.data.o,ov_SC03_031_jr_801380E0.o,ov_SC03_031_o0c.o,tail6.data.o,ov_SC03_031_jr_8013F350.o,tail7.data.o,ov_SC03_031_jr_8013FFD8.o,tail8.data.o,ov_SC03_031_jr_80140608.o,tail9.data.o,ov_SC03_031_jr_8015444C.o,ov_SC03_031_jr_80154C24.o,ov_SC03_031_jr_801588CC.o,ov_SC03_031_jr_80159C84.o,tail10.data.o,ov_SC03_031_jr_8015A3C8.o,tail11.data.o,ov_SC03_031_jr_8015AE2C.o,tail12.data.o,ov_SC03_031_jr_8015C32C.o,tail13.data.o,ov_SC03_031_jr_8016AB6C.o,tail14.data.o,ov_SC03_031_jr_80171B4C.o,ov_SC03_031_jr_801734BC.o,tail15.data.o,ov_SC03_031_jr_801789AC.o,ov_SC03_031_jr_80178D40.o,tail16.data.o,ov_SC03_031_jr_8017A4AC.o,tail17.data.o,ov_SC03_031_jr_8017AE2C.o,ov_SC03_031_jr_8017DB5C.o,tail18.data.o,trailing.o  # Phase-26 §8 jtbl-rodata carve
build/src/ov_SC03_031/ov_SC03_031.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14
build/src/ov_SC03_031/ov_SC03_031_jr_8012ACE0.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0xcc,+0xe0
build/src/ov_SC03_031/ov_SC03_031_jr_80135D20.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC03_031/ov_SC03_031_jr_8013F350.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_031/ov_SC03_031_jr_8013FFD8.o: JTBL_PADS := 0,0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38,+0x58
build/src/ov_SC03_031/ov_SC03_031_jr_8015444C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x70
build/src/ov_SC03_031/ov_SC03_031_jr_80154C24.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x24
build/src/ov_SC03_031/ov_SC03_031_jr_801588CC.o: JTBL_PADS := 0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x28,+0x48
build/src/ov_SC03_031/ov_SC03_031_jr_80159C84.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_031/ov_SC03_031_jr_8015AE2C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_031/ov_SC03_031_jr_8016AB6C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_031/ov_SC03_031_jr_80178D40.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x178
build/src/ov_SC03_031/ov_SC03_031_jr_8017DB5C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_031/ov_SC03_031_o0c.o: JTBL_PADS := 0,4,4,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x38,+0xa8,+0x118
ov_SC03_031_CHECK_SHA  := config/check.ov_SC03_031.sha
ov_SC03_031_SYMBOLS    := config/symbols.ov_SC03_031.txt
ov_SC03_031_SIG        := .run/sig.ov_SC03_031.jsonl
ov_SC03_031_GHIDRA_PROG := ov_SC03_031
ov_SC03_031_VRAM_BASE  := 0x80128158
ov_SC03_031_TEXT_LO    := 0x80128158
ov_SC03_031_TEXT_HI    := 0x801C62A7
ov_SC03_031_ASM_DIR     := asm/ov_SC03_031
ov_SC03_031_SRC_DIR     := src/ov_SC03_031
ov_SC03_031_UNDEF_SYMS  := build/ov_SC03_031/undefined_syms_auto.txt
ov_SC03_031_UNDEF_FUNCS := build/ov_SC03_031/undefined_funcs_auto.txt

# --- ov_SC03_089 (location overlay SC03/FILE_089, vram 0x80128158 — onboarded by new_overlay.sh) ---
ov_SC03_089_EXE        := extracted/retail/SC03.CD.dir/FILE_089.dir/0.4.dec
ov_SC03_089_NAME       := ov_SC03_089
ov_SC03_089_OUT_DIR    := build/ov_SC03_089
ov_SC03_089_OUT        := $(ov_SC03_089_OUT_DIR)/$(ov_SC03_089_NAME)
ov_SC03_089_ELF        := $(ov_SC03_089_OUT).elf
ov_SC03_089_MAPFILE    := $(ov_SC03_089_OUT).map
ov_SC03_089_LD_SCRIPT  := $(ov_SC03_089_OUT).ld
ov_SC03_089_SPLAT_YAML := config/splat.ov_SC03_089.yaml
ov_SC03_089_JTBL_INTERLEAVE := --order tail.data.o,ov_SC03_089.o,ov_SC03_089_jr_8012ACE0.o,tail2.data.o,ov_SC03_089_jr_80135888.o,tail3.data.o,ov_SC03_089_jr_80135A4C.o,tail4.data.o,ov_SC03_089_jr_80135D20.o,tail5.data.o,ov_SC03_089_jr_801380E0.o,ov_SC03_089_o0c.o,tail6.data.o,ov_SC03_089_jr_8013F350.o,tail7.data.o,ov_SC03_089_jr_8013FFD8.o,tail8.data.o,ov_SC03_089_jr_80140608.o,tail9.data.o,ov_SC03_089_jr_8015444C.o,ov_SC03_089_jr_80154C24.o,ov_SC03_089_jr_801588CC.o,ov_SC03_089_jr_80159C84.o,tail10.data.o,ov_SC03_089_jr_8015A3C8.o,tail11.data.o,ov_SC03_089_jr_8015AE2C.o,tail12.data.o,ov_SC03_089_jr_8015C32C.o,tail13.data.o,ov_SC03_089_jr_8016AB6C.o,tail14.data.o,ov_SC03_089_jr_80171B4C.o,ov_SC03_089_jr_801734BC.o,tail15.data.o,ov_SC03_089_jr_801789AC.o,ov_SC03_089_jr_80178D40.o,tail16.data.o,ov_SC03_089_jr_8017A4AC.o,tail17.data.o,ov_SC03_089_jr_8017AE2C.o,ov_SC03_089_jr_8017CA80.o,tail18.data.o,ov_SC03_089_jr_80185E50.o,ov_SC03_089_jr_80189168.o,tail19.data.o,trailing.o  # Phase-26 §8 jtbl-rodata carve
build/src/ov_SC03_089/ov_SC03_089.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14
build/src/ov_SC03_089/ov_SC03_089_jr_8012ACE0.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0xcc,+0xe0
build/src/ov_SC03_089/ov_SC03_089_jr_80135D20.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC03_089/ov_SC03_089_jr_8013F350.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_089/ov_SC03_089_jr_8013FFD8.o: JTBL_PADS := 0,0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38,+0x58
build/src/ov_SC03_089/ov_SC03_089_jr_8015444C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x70
build/src/ov_SC03_089/ov_SC03_089_jr_80154C24.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x24
build/src/ov_SC03_089/ov_SC03_089_jr_801588CC.o: JTBL_PADS := 0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x28,+0x48
build/src/ov_SC03_089/ov_SC03_089_jr_80159C84.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_089/ov_SC03_089_jr_8015AE2C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_089/ov_SC03_089_jr_8016AB6C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_089/ov_SC03_089_jr_80178D40.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x178
build/src/ov_SC03_089/ov_SC03_089_jr_8017CA80.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38
build/src/ov_SC03_089/ov_SC03_089_o0c.o: JTBL_PADS := 0,4,4,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x38,+0xa8,+0x118
ov_SC03_089_CHECK_SHA  := config/check.ov_SC03_089.sha
ov_SC03_089_SYMBOLS    := config/symbols.ov_SC03_089.txt
ov_SC03_089_SIG        := .run/sig.ov_SC03_089.jsonl
ov_SC03_089_GHIDRA_PROG := ov_SC03_089
ov_SC03_089_VRAM_BASE  := 0x80128158
ov_SC03_089_TEXT_LO    := 0x80128158
ov_SC03_089_TEXT_HI    := 0x801C691F
ov_SC03_089_ASM_DIR     := asm/ov_SC03_089
ov_SC03_089_SRC_DIR     := src/ov_SC03_089
ov_SC03_089_UNDEF_SYMS  := build/ov_SC03_089/undefined_syms_auto.txt
ov_SC03_089_UNDEF_FUNCS := build/ov_SC03_089/undefined_funcs_auto.txt

# --- ov_SC03_090 (location overlay SC03/FILE_090, vram 0x80128158 — onboarded by new_overlay.sh) ---
ov_SC03_090_EXE        := extracted/retail/SC03.CD.dir/FILE_090.dir/0.4.dec
ov_SC03_090_NAME       := ov_SC03_090
ov_SC03_090_OUT_DIR    := build/ov_SC03_090
ov_SC03_090_OUT        := $(ov_SC03_090_OUT_DIR)/$(ov_SC03_090_NAME)
ov_SC03_090_ELF        := $(ov_SC03_090_OUT).elf
ov_SC03_090_MAPFILE    := $(ov_SC03_090_OUT).map
ov_SC03_090_LD_SCRIPT  := $(ov_SC03_090_OUT).ld
ov_SC03_090_SPLAT_YAML := config/splat.ov_SC03_090.yaml
ov_SC03_090_JTBL_INTERLEAVE := --order tail.data.o,ov_SC03_090.o,ov_SC03_090_jr_8012ACE0.o,tail2.data.o,ov_SC03_090_jr_80135888.o,tail3.data.o,ov_SC03_090_jr_80135A4C.o,tail4.data.o,ov_SC03_090_jr_80135D20.o,tail5.data.o,ov_SC03_090_jr_801380E0.o,ov_SC03_090_o0c.o,tail6.data.o,ov_SC03_090_jr_8013F350.o,tail7.data.o,ov_SC03_090_jr_8013FFD8.o,tail8.data.o,ov_SC03_090_jr_80140608.o,tail9.data.o,ov_SC03_090_jr_8015444C.o,ov_SC03_090_jr_80154C24.o,ov_SC03_090_jr_801588CC.o,ov_SC03_090_jr_80159C84.o,tail10.data.o,ov_SC03_090_jr_8015A3C8.o,tail11.data.o,ov_SC03_090_jr_8015AE2C.o,tail12.data.o,ov_SC03_090_jr_8015C32C.o,tail13.data.o,ov_SC03_090_jr_8016AB6C.o,tail14.data.o,ov_SC03_090_jr_80171B4C.o,ov_SC03_090_jr_801734BC.o,tail15.data.o,ov_SC03_090_jr_801789AC.o,ov_SC03_090_jr_80178D40.o,tail16.data.o,ov_SC03_090_jr_8017A4AC.o,tail17.data.o,ov_SC03_090_jr_8017AE2C.o,ov_SC03_090_jr_8017CA80.o,tail18.data.o,ov_SC03_090_jr_80188274.o,ov_SC03_090_jr_8018B58C.o,tail19.data.o,trailing.o  # Phase-26 §8 jtbl-rodata carve
build/src/ov_SC03_090/ov_SC03_090.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14
build/src/ov_SC03_090/ov_SC03_090_jr_8012ACE0.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0xcc,+0xe0
build/src/ov_SC03_090/ov_SC03_090_jr_80135D20.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC03_090/ov_SC03_090_jr_8013F350.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_090/ov_SC03_090_jr_8013FFD8.o: JTBL_PADS := 0,0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38,+0x58
build/src/ov_SC03_090/ov_SC03_090_jr_8015444C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x70
build/src/ov_SC03_090/ov_SC03_090_jr_80154C24.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x24
build/src/ov_SC03_090/ov_SC03_090_jr_801588CC.o: JTBL_PADS := 0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x28,+0x48
build/src/ov_SC03_090/ov_SC03_090_jr_80159C84.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_090/ov_SC03_090_jr_8015AE2C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_090/ov_SC03_090_jr_8016AB6C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_090/ov_SC03_090_jr_80178D40.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x178
build/src/ov_SC03_090/ov_SC03_090_jr_8017CA80.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38
build/src/ov_SC03_090/ov_SC03_090_o0c.o: JTBL_PADS := 0,4,4,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x38,+0xa8,+0x118
ov_SC03_090_CHECK_SHA  := config/check.ov_SC03_090.sha
ov_SC03_090_SYMBOLS    := config/symbols.ov_SC03_090.txt
ov_SC03_090_SIG        := .run/sig.ov_SC03_090.jsonl
ov_SC03_090_GHIDRA_PROG := ov_SC03_090
ov_SC03_090_VRAM_BASE  := 0x80128158
ov_SC03_090_TEXT_LO    := 0x80128158
ov_SC03_090_TEXT_HI    := 0x801CBD8F
ov_SC03_090_ASM_DIR     := asm/ov_SC03_090
ov_SC03_090_SRC_DIR     := src/ov_SC03_090
ov_SC03_090_UNDEF_SYMS  := build/ov_SC03_090/undefined_syms_auto.txt
ov_SC03_090_UNDEF_FUNCS := build/ov_SC03_090/undefined_funcs_auto.txt

# --- ov_SC03_091 (location overlay SC03/FILE_091, vram 0x80128158 — onboarded by new_overlay.sh) ---
ov_SC03_091_EXE        := extracted/retail/SC03.CD.dir/FILE_091.dir/0.4.dec
ov_SC03_091_NAME       := ov_SC03_091
ov_SC03_091_OUT_DIR    := build/ov_SC03_091
ov_SC03_091_OUT        := $(ov_SC03_091_OUT_DIR)/$(ov_SC03_091_NAME)
ov_SC03_091_ELF        := $(ov_SC03_091_OUT).elf
ov_SC03_091_MAPFILE    := $(ov_SC03_091_OUT).map
ov_SC03_091_LD_SCRIPT  := $(ov_SC03_091_OUT).ld
ov_SC03_091_SPLAT_YAML := config/splat.ov_SC03_091.yaml
ov_SC03_091_JTBL_INTERLEAVE := --order tail.data.o,ov_SC03_091.o,ov_SC03_091_jr_8012ACE0.o,tail2.data.o,ov_SC03_091_jr_80135888.o,tail3.data.o,ov_SC03_091_jr_80135A4C.o,tail4.data.o,ov_SC03_091_jr_80135D20.o,tail5.data.o,ov_SC03_091_jr_801380E0.o,ov_SC03_091_o0c.o,tail6.data.o,ov_SC03_091_jr_8013F350.o,tail7.data.o,ov_SC03_091_jr_8013FFD8.o,tail8.data.o,ov_SC03_091_jr_80140608.o,tail9.data.o,ov_SC03_091_jr_8015444C.o,ov_SC03_091_jr_80154C24.o,ov_SC03_091_jr_801588CC.o,ov_SC03_091_jr_80159C84.o,tail10.data.o,ov_SC03_091_jr_8015A3C8.o,tail11.data.o,ov_SC03_091_jr_8015AE2C.o,tail12.data.o,ov_SC03_091_jr_8015C32C.o,tail13.data.o,ov_SC03_091_jr_8016AB6C.o,tail14.data.o,ov_SC03_091_jr_80171B4C.o,ov_SC03_091_jr_801734BC.o,tail15.data.o,ov_SC03_091_jr_801789AC.o,ov_SC03_091_jr_80178D40.o,tail16.data.o,ov_SC03_091_jr_8017A4AC.o,tail17.data.o,ov_SC03_091_jr_8017AE2C.o,ov_SC03_091_jr_8017D898.o,ov_SC03_091_jr_8018326C.o,tail18.data.o,ov_SC03_091_jr_8018911C.o,ov_SC03_091_jr_8018C434.o,tail19.data.o,trailing.o  # Phase-26 §8 jtbl-rodata carve
build/src/ov_SC03_091/ov_SC03_091.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14
build/src/ov_SC03_091/ov_SC03_091_jr_8012ACE0.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0xcc,+0xe0
build/src/ov_SC03_091/ov_SC03_091_jr_80135D20.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC03_091/ov_SC03_091_jr_8013F350.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_091/ov_SC03_091_jr_8013FFD8.o: JTBL_PADS := 0,0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38,+0x58
build/src/ov_SC03_091/ov_SC03_091_jr_8015444C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x70
build/src/ov_SC03_091/ov_SC03_091_jr_80154C24.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x24
build/src/ov_SC03_091/ov_SC03_091_jr_801588CC.o: JTBL_PADS := 0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x28,+0x48
build/src/ov_SC03_091/ov_SC03_091_jr_80159C84.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_091/ov_SC03_091_jr_8015AE2C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_091/ov_SC03_091_jr_8016AB6C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_091/ov_SC03_091_jr_80178D40.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x178
build/src/ov_SC03_091/ov_SC03_091_jr_8018326C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC03_091/ov_SC03_091_o0c.o: JTBL_PADS := 0,4,4,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x38,+0xa8,+0x118
ov_SC03_091_CHECK_SHA  := config/check.ov_SC03_091.sha
ov_SC03_091_SYMBOLS    := config/symbols.ov_SC03_091.txt
ov_SC03_091_SIG        := .run/sig.ov_SC03_091.jsonl
ov_SC03_091_GHIDRA_PROG := ov_SC03_091
ov_SC03_091_VRAM_BASE  := 0x80128158
ov_SC03_091_TEXT_LO    := 0x80128158
ov_SC03_091_TEXT_HI    := 0x801D26DF
ov_SC03_091_ASM_DIR     := asm/ov_SC03_091
ov_SC03_091_SRC_DIR     := src/ov_SC03_091
ov_SC03_091_UNDEF_SYMS  := build/ov_SC03_091/undefined_syms_auto.txt
ov_SC03_091_UNDEF_FUNCS := build/ov_SC03_091/undefined_funcs_auto.txt

# --- ov_SC03_092 (location overlay SC03/FILE_092, vram 0x80128158 — onboarded by new_overlay.sh) ---
ov_SC03_092_EXE        := extracted/retail/SC03.CD.dir/FILE_092.dir/0.4.dec
ov_SC03_092_NAME       := ov_SC03_092
ov_SC03_092_OUT_DIR    := build/ov_SC03_092
ov_SC03_092_OUT        := $(ov_SC03_092_OUT_DIR)/$(ov_SC03_092_NAME)
ov_SC03_092_ELF        := $(ov_SC03_092_OUT).elf
ov_SC03_092_MAPFILE    := $(ov_SC03_092_OUT).map
ov_SC03_092_LD_SCRIPT  := $(ov_SC03_092_OUT).ld
ov_SC03_092_SPLAT_YAML := config/splat.ov_SC03_092.yaml
ov_SC03_092_JTBL_INTERLEAVE := --order tail.data.o,ov_SC03_092.o,ov_SC03_092_jr_8012ACE0.o,tail2.data.o,ov_SC03_092_jr_80135888.o,tail3.data.o,ov_SC03_092_jr_80135A4C.o,tail4.data.o,ov_SC03_092_jr_80135D20.o,tail5.data.o,ov_SC03_092_jr_801380E0.o,ov_SC03_092_o0c.o,tail6.data.o,ov_SC03_092_jr_8013F350.o,tail7.data.o,ov_SC03_092_jr_8013FFD8.o,tail8.data.o,ov_SC03_092_jr_80140608.o,tail9.data.o,ov_SC03_092_jr_8015444C.o,ov_SC03_092_jr_80154C24.o,ov_SC03_092_jr_801588CC.o,ov_SC03_092_jr_80159C84.o,tail10.data.o,ov_SC03_092_jr_8015A3C8.o,tail11.data.o,ov_SC03_092_jr_8015AE2C.o,tail12.data.o,ov_SC03_092_jr_8015C32C.o,tail13.data.o,ov_SC03_092_jr_8016AB6C.o,tail14.data.o,ov_SC03_092_jr_80171B4C.o,ov_SC03_092_jr_801734BC.o,tail15.data.o,ov_SC03_092_jr_801789AC.o,ov_SC03_092_jr_80178D40.o,tail16.data.o,ov_SC03_092_jr_8017A4AC.o,tail17.data.o,ov_SC03_092_jr_8017AE2C.o,tail18.data.o,ov_SC03_092_jr_8017FE88.o,ov_SC03_092_jr_80181694.o,tail19.data.o,trailing.o  # Phase-26 §8 jtbl-rodata carve
build/src/ov_SC03_092/ov_SC03_092.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14
build/src/ov_SC03_092/ov_SC03_092_jr_8012ACE0.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0xcc,+0xe0
build/src/ov_SC03_092/ov_SC03_092_jr_80135D20.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC03_092/ov_SC03_092_jr_8013F350.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_092/ov_SC03_092_jr_8013FFD8.o: JTBL_PADS := 0,0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38,+0x58
build/src/ov_SC03_092/ov_SC03_092_jr_8015444C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x70
build/src/ov_SC03_092/ov_SC03_092_jr_80154C24.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x24
build/src/ov_SC03_092/ov_SC03_092_jr_801588CC.o: JTBL_PADS := 0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x28,+0x48
build/src/ov_SC03_092/ov_SC03_092_jr_80159C84.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_092/ov_SC03_092_jr_8015AE2C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_092/ov_SC03_092_jr_8016AB6C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_092/ov_SC03_092_jr_80178D40.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x178
build/src/ov_SC03_092/ov_SC03_092_jr_8017AE2C.o: JTBL_PADS := 0,0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14,+0x2c
build/src/ov_SC03_092/ov_SC03_092_jr_80181694.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC03_092/ov_SC03_092_o0c.o: JTBL_PADS := 0,4,4,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x38,+0xa8,+0x118
ov_SC03_092_CHECK_SHA  := config/check.ov_SC03_092.sha
ov_SC03_092_SYMBOLS    := config/symbols.ov_SC03_092.txt
ov_SC03_092_SIG        := .run/sig.ov_SC03_092.jsonl
ov_SC03_092_GHIDRA_PROG := ov_SC03_092
ov_SC03_092_VRAM_BASE  := 0x80128158
ov_SC03_092_TEXT_LO    := 0x80128158
ov_SC03_092_TEXT_HI    := 0x801B3087
ov_SC03_092_ASM_DIR     := asm/ov_SC03_092
ov_SC03_092_SRC_DIR     := src/ov_SC03_092
ov_SC03_092_UNDEF_SYMS  := build/ov_SC03_092/undefined_syms_auto.txt
ov_SC03_092_UNDEF_FUNCS := build/ov_SC03_092/undefined_funcs_auto.txt

# --- ov_SC03_093 (location overlay SC03/FILE_093, vram 0x80128158 — onboarded by new_overlay.sh) ---
ov_SC03_093_EXE        := extracted/retail/SC03.CD.dir/FILE_093.dir/0.4.dec
ov_SC03_093_NAME       := ov_SC03_093
ov_SC03_093_OUT_DIR    := build/ov_SC03_093
ov_SC03_093_OUT        := $(ov_SC03_093_OUT_DIR)/$(ov_SC03_093_NAME)
ov_SC03_093_ELF        := $(ov_SC03_093_OUT).elf
ov_SC03_093_MAPFILE    := $(ov_SC03_093_OUT).map
ov_SC03_093_LD_SCRIPT  := $(ov_SC03_093_OUT).ld
ov_SC03_093_SPLAT_YAML := config/splat.ov_SC03_093.yaml
ov_SC03_093_JTBL_INTERLEAVE := --order tail.data.o,ov_SC03_093.o,ov_SC03_093_jr_8012ACE0.o,tail2.data.o,ov_SC03_093_jr_80135888.o,tail3.data.o,ov_SC03_093_jr_80135A4C.o,tail4.data.o,ov_SC03_093_jr_80135D20.o,tail5.data.o,ov_SC03_093_jr_801380E0.o,ov_SC03_093_o0c.o,tail6.data.o,ov_SC03_093_jr_8013F350.o,tail7.data.o,ov_SC03_093_jr_8013FFD8.o,tail8.data.o,ov_SC03_093_jr_80140608.o,tail9.data.o,ov_SC03_093_jr_8015444C.o,ov_SC03_093_jr_80154C24.o,ov_SC03_093_jr_801588CC.o,ov_SC03_093_jr_80159C84.o,tail10.data.o,ov_SC03_093_jr_8015A3C8.o,tail11.data.o,ov_SC03_093_jr_8015AE2C.o,tail12.data.o,ov_SC03_093_jr_8015C32C.o,tail13.data.o,ov_SC03_093_jr_8016AB6C.o,tail14.data.o,ov_SC03_093_jr_80171B4C.o,ov_SC03_093_jr_801734BC.o,tail15.data.o,ov_SC03_093_jr_801789AC.o,ov_SC03_093_jr_80178D40.o,tail16.data.o,ov_SC03_093_jr_8017A4AC.o,tail17.data.o,ov_SC03_093_jr_8017AE2C.o,ov_SC03_093_jr_8017D898.o,ov_SC03_093_jr_801825B8.o,ov_SC03_093_jr_801859DC.o,tail18.data.o,trailing.o  # Phase-26 §8 jtbl-rodata carve
build/src/ov_SC03_093/ov_SC03_093.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14
build/src/ov_SC03_093/ov_SC03_093_jr_8012ACE0.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0xcc,+0xe0
build/src/ov_SC03_093/ov_SC03_093_jr_80135D20.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC03_093/ov_SC03_093_jr_8013F350.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_093/ov_SC03_093_jr_8013FFD8.o: JTBL_PADS := 0,0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38,+0x58
build/src/ov_SC03_093/ov_SC03_093_jr_8015444C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x70
build/src/ov_SC03_093/ov_SC03_093_jr_80154C24.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x24
build/src/ov_SC03_093/ov_SC03_093_jr_801588CC.o: JTBL_PADS := 0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x28,+0x48
build/src/ov_SC03_093/ov_SC03_093_jr_80159C84.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_093/ov_SC03_093_jr_8015AE2C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_093/ov_SC03_093_jr_8016AB6C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_093/ov_SC03_093_jr_80178D40.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x178
build/src/ov_SC03_093/ov_SC03_093_jr_8017D898.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38
build/src/ov_SC03_093/ov_SC03_093_jr_801825B8.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC03_093/ov_SC03_093_o0c.o: JTBL_PADS := 0,4,4,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x38,+0xa8,+0x118
ov_SC03_093_CHECK_SHA  := config/check.ov_SC03_093.sha
ov_SC03_093_SYMBOLS    := config/symbols.ov_SC03_093.txt
ov_SC03_093_SIG        := .run/sig.ov_SC03_093.jsonl
ov_SC03_093_GHIDRA_PROG := ov_SC03_093
ov_SC03_093_VRAM_BASE  := 0x80128158
ov_SC03_093_TEXT_LO    := 0x80128158
ov_SC03_093_TEXT_HI    := 0x801CC6DF
ov_SC03_093_ASM_DIR     := asm/ov_SC03_093
ov_SC03_093_SRC_DIR     := src/ov_SC03_093
ov_SC03_093_UNDEF_SYMS  := build/ov_SC03_093/undefined_syms_auto.txt
ov_SC03_093_UNDEF_FUNCS := build/ov_SC03_093/undefined_funcs_auto.txt

# --- ov_SC03_094 (location overlay SC03/FILE_094, vram 0x80128158 — onboarded by new_overlay.sh) ---
ov_SC03_094_EXE        := extracted/retail/SC03.CD.dir/FILE_094.dir/0.4.dec
ov_SC03_094_NAME       := ov_SC03_094
ov_SC03_094_OUT_DIR    := build/ov_SC03_094
ov_SC03_094_OUT        := $(ov_SC03_094_OUT_DIR)/$(ov_SC03_094_NAME)
ov_SC03_094_ELF        := $(ov_SC03_094_OUT).elf
ov_SC03_094_MAPFILE    := $(ov_SC03_094_OUT).map
ov_SC03_094_LD_SCRIPT  := $(ov_SC03_094_OUT).ld
ov_SC03_094_SPLAT_YAML := config/splat.ov_SC03_094.yaml
ov_SC03_094_JTBL_INTERLEAVE := --order tail.data.o,ov_SC03_094.o,ov_SC03_094_jr_8012ACE0.o,tail2.data.o,ov_SC03_094_jr_80135888.o,tail3.data.o,ov_SC03_094_jr_80135A4C.o,tail4.data.o,ov_SC03_094_jr_80135D20.o,tail5.data.o,ov_SC03_094_jr_801380E0.o,ov_SC03_094_o0c.o,tail6.data.o,ov_SC03_094_jr_8013F350.o,tail7.data.o,ov_SC03_094_jr_8013FFD8.o,tail8.data.o,ov_SC03_094_jr_80140608.o,tail9.data.o,ov_SC03_094_jr_8015444C.o,ov_SC03_094_jr_80154C24.o,ov_SC03_094_jr_801588CC.o,ov_SC03_094_jr_80159C84.o,tail10.data.o,ov_SC03_094_jr_8015A3C8.o,tail11.data.o,ov_SC03_094_jr_8015AE2C.o,tail12.data.o,ov_SC03_094_jr_8015C32C.o,tail13.data.o,ov_SC03_094_jr_8016AB6C.o,tail14.data.o,ov_SC03_094_jr_80171B4C.o,ov_SC03_094_jr_801734BC.o,tail15.data.o,ov_SC03_094_jr_801789AC.o,ov_SC03_094_jr_80178D40.o,tail16.data.o,ov_SC03_094_jr_8017A4AC.o,tail17.data.o,ov_SC03_094_jr_8017AE2C.o,ov_SC03_094_jr_8017BEBC.o,ov_SC03_094_jr_8018501C.o,ov_SC03_094_jr_801873D8.o,tail18.data.o,trailing.o  # Phase-26 §8 jtbl-rodata carve
build/src/ov_SC03_094/ov_SC03_094.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14
build/src/ov_SC03_094/ov_SC03_094_jr_8012ACE0.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0xcc,+0xe0
build/src/ov_SC03_094/ov_SC03_094_jr_80135D20.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC03_094/ov_SC03_094_jr_8013F350.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_094/ov_SC03_094_jr_8013FFD8.o: JTBL_PADS := 0,0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38,+0x58
build/src/ov_SC03_094/ov_SC03_094_jr_8015444C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x70
build/src/ov_SC03_094/ov_SC03_094_jr_80154C24.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x24
build/src/ov_SC03_094/ov_SC03_094_jr_801588CC.o: JTBL_PADS := 0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x28,+0x48
build/src/ov_SC03_094/ov_SC03_094_jr_80159C84.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_094/ov_SC03_094_jr_8015AE2C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_094/ov_SC03_094_jr_8016AB6C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_094/ov_SC03_094_jr_80178D40.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x178
build/src/ov_SC03_094/ov_SC03_094_jr_8017BEBC.o: JTBL_PADS := 0,0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38,+0x4c
build/src/ov_SC03_094/ov_SC03_094_o0c.o: JTBL_PADS := 0,4,4,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x38,+0xa8,+0x118
ov_SC03_094_CHECK_SHA  := config/check.ov_SC03_094.sha
ov_SC03_094_SYMBOLS    := config/symbols.ov_SC03_094.txt
ov_SC03_094_SIG        := .run/sig.ov_SC03_094.jsonl
ov_SC03_094_GHIDRA_PROG := ov_SC03_094
ov_SC03_094_VRAM_BASE  := 0x80128158
ov_SC03_094_TEXT_LO    := 0x80128158
ov_SC03_094_TEXT_HI    := 0x801D3297
ov_SC03_094_ASM_DIR     := asm/ov_SC03_094
ov_SC03_094_SRC_DIR     := src/ov_SC03_094
ov_SC03_094_UNDEF_SYMS  := build/ov_SC03_094/undefined_syms_auto.txt
ov_SC03_094_UNDEF_FUNCS := build/ov_SC03_094/undefined_funcs_auto.txt

# --- ov_SC03_095 (location overlay SC03/FILE_095, vram 0x80128158 — onboarded by new_overlay.sh) ---
ov_SC03_095_EXE        := extracted/retail/SC03.CD.dir/FILE_095.dir/0.4.dec
ov_SC03_095_NAME       := ov_SC03_095
ov_SC03_095_OUT_DIR    := build/ov_SC03_095
ov_SC03_095_OUT        := $(ov_SC03_095_OUT_DIR)/$(ov_SC03_095_NAME)
ov_SC03_095_ELF        := $(ov_SC03_095_OUT).elf
ov_SC03_095_MAPFILE    := $(ov_SC03_095_OUT).map
ov_SC03_095_LD_SCRIPT  := $(ov_SC03_095_OUT).ld
ov_SC03_095_SPLAT_YAML := config/splat.ov_SC03_095.yaml
ov_SC03_095_JTBL_INTERLEAVE := --order tail.data.o,ov_SC03_095.o,ov_SC03_095_jr_8012ACE0.o,tail2.data.o,ov_SC03_095_jr_80135888.o,tail3.data.o,ov_SC03_095_jr_80135A4C.o,tail4.data.o,ov_SC03_095_jr_80135D20.o,tail5.data.o,ov_SC03_095_jr_801380E0.o,ov_SC03_095_o0c.o,tail6.data.o,ov_SC03_095_jr_8013F350.o,tail7.data.o,ov_SC03_095_jr_8013FFD8.o,tail8.data.o,ov_SC03_095_jr_80140608.o,tail9.data.o,ov_SC03_095_jr_8015444C.o,ov_SC03_095_jr_80154C24.o,ov_SC03_095_jr_801588CC.o,ov_SC03_095_jr_80159C84.o,tail10.data.o,ov_SC03_095_jr_8015A3C8.o,tail11.data.o,ov_SC03_095_jr_8015AE2C.o,tail12.data.o,ov_SC03_095_jr_8015C32C.o,tail13.data.o,ov_SC03_095_jr_8016AB6C.o,tail14.data.o,ov_SC03_095_jr_80171B4C.o,ov_SC03_095_jr_801734BC.o,tail15.data.o,ov_SC03_095_jr_801789AC.o,ov_SC03_095_jr_80178D40.o,tail16.data.o,ov_SC03_095_jr_8017A4AC.o,tail17.data.o,ov_SC03_095_jr_8017AE2C.o,ov_SC03_095_jr_8017BEBC.o,ov_SC03_095_jr_80180A38.o,tail18.data.o,trailing.o  # Phase-26 §8 jtbl-rodata carve
build/src/ov_SC03_095/ov_SC03_095.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14
build/src/ov_SC03_095/ov_SC03_095_jr_8012ACE0.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0xcc,+0xe0
build/src/ov_SC03_095/ov_SC03_095_jr_80135D20.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC03_095/ov_SC03_095_jr_8013F350.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_095/ov_SC03_095_jr_8013FFD8.o: JTBL_PADS := 0,0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38,+0x58
build/src/ov_SC03_095/ov_SC03_095_jr_8015444C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x70
build/src/ov_SC03_095/ov_SC03_095_jr_80154C24.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x24
build/src/ov_SC03_095/ov_SC03_095_jr_801588CC.o: JTBL_PADS := 0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x28,+0x48
build/src/ov_SC03_095/ov_SC03_095_jr_80159C84.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_095/ov_SC03_095_jr_8015AE2C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_095/ov_SC03_095_jr_8016AB6C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_095/ov_SC03_095_jr_80178D40.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x178
build/src/ov_SC03_095/ov_SC03_095_jr_8017BEBC.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38
build/src/ov_SC03_095/ov_SC03_095_o0c.o: JTBL_PADS := 0,4,4,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x38,+0xa8,+0x118
ov_SC03_095_CHECK_SHA  := config/check.ov_SC03_095.sha
ov_SC03_095_SYMBOLS    := config/symbols.ov_SC03_095.txt
ov_SC03_095_SIG        := .run/sig.ov_SC03_095.jsonl
ov_SC03_095_GHIDRA_PROG := ov_SC03_095
ov_SC03_095_VRAM_BASE  := 0x80128158
ov_SC03_095_TEXT_LO    := 0x80128158
ov_SC03_095_TEXT_HI    := 0x8019BE97
ov_SC03_095_ASM_DIR     := asm/ov_SC03_095
ov_SC03_095_SRC_DIR     := src/ov_SC03_095
ov_SC03_095_UNDEF_SYMS  := build/ov_SC03_095/undefined_syms_auto.txt
ov_SC03_095_UNDEF_FUNCS := build/ov_SC03_095/undefined_funcs_auto.txt

# --- ov_SC03_096 (location overlay SC03/FILE_096, vram 0x80128158 — onboarded by new_overlay.sh) ---
ov_SC03_096_EXE        := extracted/retail/SC03.CD.dir/FILE_096.dir/0.4.dec
ov_SC03_096_NAME       := ov_SC03_096
ov_SC03_096_OUT_DIR    := build/ov_SC03_096
ov_SC03_096_OUT        := $(ov_SC03_096_OUT_DIR)/$(ov_SC03_096_NAME)
ov_SC03_096_ELF        := $(ov_SC03_096_OUT).elf
ov_SC03_096_MAPFILE    := $(ov_SC03_096_OUT).map
ov_SC03_096_LD_SCRIPT  := $(ov_SC03_096_OUT).ld
ov_SC03_096_SPLAT_YAML := config/splat.ov_SC03_096.yaml
ov_SC03_096_JTBL_INTERLEAVE := --order tail.data.o,ov_SC03_096.o,ov_SC03_096_jr_8012ACE0.o,tail2.data.o,ov_SC03_096_jr_80135888.o,tail3.data.o,ov_SC03_096_jr_80135A4C.o,tail4.data.o,ov_SC03_096_jr_80135D20.o,tail5.data.o,ov_SC03_096_jr_801380E0.o,ov_SC03_096_o0c.o,tail6.data.o,ov_SC03_096_jr_8013F350.o,tail7.data.o,ov_SC03_096_jr_8013FFD8.o,tail8.data.o,ov_SC03_096_jr_80140608.o,tail9.data.o,ov_SC03_096_jr_8015444C.o,ov_SC03_096_jr_80154C24.o,ov_SC03_096_jr_801588CC.o,ov_SC03_096_jr_80159C84.o,tail10.data.o,ov_SC03_096_jr_8015A3C8.o,tail11.data.o,ov_SC03_096_jr_8015AE2C.o,tail12.data.o,ov_SC03_096_jr_8015C32C.o,tail13.data.o,ov_SC03_096_jr_8016AB6C.o,tail14.data.o,ov_SC03_096_jr_80171B4C.o,ov_SC03_096_jr_801734BC.o,tail15.data.o,ov_SC03_096_jr_801789AC.o,ov_SC03_096_jr_80178D40.o,tail16.data.o,ov_SC03_096_jr_8017A4AC.o,tail17.data.o,ov_SC03_096_jr_8017AE2C.o,ov_SC03_096_jr_8017BEBC.o,ov_SC03_096_jr_801805B8.o,tail18.data.o,trailing.o  # Phase-26 §8 jtbl-rodata carve
build/src/ov_SC03_096/ov_SC03_096.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14
build/src/ov_SC03_096/ov_SC03_096_jr_8012ACE0.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0xcc,+0xe0
build/src/ov_SC03_096/ov_SC03_096_jr_80135D20.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC03_096/ov_SC03_096_jr_8013F350.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_096/ov_SC03_096_jr_8013FFD8.o: JTBL_PADS := 0,0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38,+0x58
build/src/ov_SC03_096/ov_SC03_096_jr_8015444C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x70
build/src/ov_SC03_096/ov_SC03_096_jr_80154C24.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x24
build/src/ov_SC03_096/ov_SC03_096_jr_801588CC.o: JTBL_PADS := 0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x28,+0x48
build/src/ov_SC03_096/ov_SC03_096_jr_80159C84.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_096/ov_SC03_096_jr_8015AE2C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_096/ov_SC03_096_jr_8016AB6C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_096/ov_SC03_096_jr_80178D40.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x178
build/src/ov_SC03_096/ov_SC03_096_jr_8017BEBC.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38
build/src/ov_SC03_096/ov_SC03_096_o0c.o: JTBL_PADS := 0,4,4,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x38,+0xa8,+0x118
ov_SC03_096_CHECK_SHA  := config/check.ov_SC03_096.sha
ov_SC03_096_SYMBOLS    := config/symbols.ov_SC03_096.txt
ov_SC03_096_SIG        := .run/sig.ov_SC03_096.jsonl
ov_SC03_096_GHIDRA_PROG := ov_SC03_096
ov_SC03_096_VRAM_BASE  := 0x80128158
ov_SC03_096_TEXT_LO    := 0x80128158
ov_SC03_096_TEXT_HI    := 0x8019A94F
ov_SC03_096_ASM_DIR     := asm/ov_SC03_096
ov_SC03_096_SRC_DIR     := src/ov_SC03_096
ov_SC03_096_UNDEF_SYMS  := build/ov_SC03_096/undefined_syms_auto.txt
ov_SC03_096_UNDEF_FUNCS := build/ov_SC03_096/undefined_funcs_auto.txt

# --- ov_SC03_097 (location overlay SC03/FILE_097, vram 0x80128158 — onboarded by new_overlay.sh) ---
ov_SC03_097_EXE        := extracted/retail/SC03.CD.dir/FILE_097.dir/0.4.dec
ov_SC03_097_NAME       := ov_SC03_097
ov_SC03_097_OUT_DIR    := build/ov_SC03_097
ov_SC03_097_OUT        := $(ov_SC03_097_OUT_DIR)/$(ov_SC03_097_NAME)
ov_SC03_097_ELF        := $(ov_SC03_097_OUT).elf
ov_SC03_097_MAPFILE    := $(ov_SC03_097_OUT).map
ov_SC03_097_LD_SCRIPT  := $(ov_SC03_097_OUT).ld
ov_SC03_097_SPLAT_YAML := config/splat.ov_SC03_097.yaml
ov_SC03_097_JTBL_INTERLEAVE := --order tail.data.o,ov_SC03_097.o,ov_SC03_097_jr_8012ACE0.o,tail2.data.o,ov_SC03_097_jr_80135888.o,tail3.data.o,ov_SC03_097_jr_80135A4C.o,tail4.data.o,ov_SC03_097_jr_80135D20.o,tail5.data.o,ov_SC03_097_jr_801380E0.o,ov_SC03_097_o0c.o,tail6.data.o,ov_SC03_097_jr_8013F350.o,tail7.data.o,ov_SC03_097_jr_8013FFD8.o,tail8.data.o,ov_SC03_097_jr_80140608.o,tail9.data.o,ov_SC03_097_jr_8015444C.o,ov_SC03_097_jr_80154C24.o,ov_SC03_097_jr_801588CC.o,ov_SC03_097_jr_80159C84.o,tail10.data.o,ov_SC03_097_jr_8015A3C8.o,tail11.data.o,ov_SC03_097_jr_8015AE2C.o,tail12.data.o,ov_SC03_097_jr_8015C32C.o,tail13.data.o,ov_SC03_097_jr_8016AB6C.o,tail14.data.o,ov_SC03_097_jr_80171B4C.o,ov_SC03_097_jr_801734BC.o,tail15.data.o,ov_SC03_097_jr_801789AC.o,ov_SC03_097_jr_80178D40.o,tail16.data.o,ov_SC03_097_jr_8017A4AC.o,tail17.data.o,ov_SC03_097_jr_8017AE2C.o,ov_SC03_097_jr_8017D898.o,tail18.data.o,ov_SC03_097_jr_80182B9C.o,ov_SC03_097_jr_801851B8.o,tail19.data.o,trailing.o  # Phase-26 §8 jtbl-rodata carve
build/src/ov_SC03_097/ov_SC03_097.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14
build/src/ov_SC03_097/ov_SC03_097_jr_8012ACE0.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0xcc,+0xe0
build/src/ov_SC03_097/ov_SC03_097_jr_80135D20.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC03_097/ov_SC03_097_jr_8013F350.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_097/ov_SC03_097_jr_8013FFD8.o: JTBL_PADS := 0,0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38,+0x58
build/src/ov_SC03_097/ov_SC03_097_jr_8015444C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x70
build/src/ov_SC03_097/ov_SC03_097_jr_80154C24.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x24
build/src/ov_SC03_097/ov_SC03_097_jr_801588CC.o: JTBL_PADS := 0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x28,+0x48
build/src/ov_SC03_097/ov_SC03_097_jr_80159C84.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_097/ov_SC03_097_jr_8015AE2C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_097/ov_SC03_097_jr_8016AB6C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_097/ov_SC03_097_jr_80178D40.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x178
build/src/ov_SC03_097/ov_SC03_097_jr_80182B9C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC03_097/ov_SC03_097_o0c.o: JTBL_PADS := 0,4,4,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x38,+0xa8,+0x118
ov_SC03_097_CHECK_SHA  := config/check.ov_SC03_097.sha
ov_SC03_097_SYMBOLS    := config/symbols.ov_SC03_097.txt
ov_SC03_097_SIG        := .run/sig.ov_SC03_097.jsonl
ov_SC03_097_GHIDRA_PROG := ov_SC03_097
ov_SC03_097_VRAM_BASE  := 0x80128158
ov_SC03_097_TEXT_LO    := 0x80128158
ov_SC03_097_TEXT_HI    := 0x801AAECF
ov_SC03_097_ASM_DIR     := asm/ov_SC03_097
ov_SC03_097_SRC_DIR     := src/ov_SC03_097
ov_SC03_097_UNDEF_SYMS  := build/ov_SC03_097/undefined_syms_auto.txt
ov_SC03_097_UNDEF_FUNCS := build/ov_SC03_097/undefined_funcs_auto.txt

# --- ov_SC03_098 (location overlay SC03/FILE_098, vram 0x80128158 — onboarded by new_overlay.sh) ---
ov_SC03_098_EXE        := extracted/retail/SC03.CD.dir/FILE_098.dir/0.4.dec
ov_SC03_098_NAME       := ov_SC03_098
ov_SC03_098_OUT_DIR    := build/ov_SC03_098
ov_SC03_098_OUT        := $(ov_SC03_098_OUT_DIR)/$(ov_SC03_098_NAME)
ov_SC03_098_ELF        := $(ov_SC03_098_OUT).elf
ov_SC03_098_MAPFILE    := $(ov_SC03_098_OUT).map
ov_SC03_098_LD_SCRIPT  := $(ov_SC03_098_OUT).ld
ov_SC03_098_SPLAT_YAML := config/splat.ov_SC03_098.yaml
ov_SC03_098_JTBL_INTERLEAVE := --order tail.data.o,ov_SC03_098.o,ov_SC03_098_jr_8012ACE0.o,tail2.data.o,ov_SC03_098_jr_80135888.o,tail3.data.o,ov_SC03_098_jr_80135A4C.o,tail4.data.o,ov_SC03_098_jr_80135D20.o,tail5.data.o,ov_SC03_098_jr_801380E0.o,ov_SC03_098_o0c.o,tail6.data.o,ov_SC03_098_jr_8013F350.o,tail7.data.o,ov_SC03_098_jr_8013FFD8.o,tail8.data.o,ov_SC03_098_jr_80140608.o,tail9.data.o,ov_SC03_098_jr_8015444C.o,ov_SC03_098_jr_80154C24.o,ov_SC03_098_jr_801588CC.o,ov_SC03_098_jr_80159C84.o,tail10.data.o,ov_SC03_098_jr_8015A3C8.o,tail11.data.o,ov_SC03_098_jr_8015AE2C.o,tail12.data.o,ov_SC03_098_jr_8015C32C.o,tail13.data.o,ov_SC03_098_jr_8016AB6C.o,tail14.data.o,ov_SC03_098_jr_80171B4C.o,ov_SC03_098_jr_801734BC.o,tail15.data.o,ov_SC03_098_jr_801789AC.o,ov_SC03_098_jr_80178D40.o,tail16.data.o,ov_SC03_098_jr_8017A4AC.o,tail17.data.o,ov_SC03_098_jr_8017AE2C.o,ov_SC03_098_jr_8017D898.o,ov_SC03_098_jr_80184E24.o,tail18.data.o,trailing.o  # Phase-26 §8 jtbl-rodata carve
build/src/ov_SC03_098/ov_SC03_098.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14
build/src/ov_SC03_098/ov_SC03_098_jr_8012ACE0.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0xcc,+0xe0
build/src/ov_SC03_098/ov_SC03_098_jr_80135D20.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC03_098/ov_SC03_098_jr_8013F350.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_098/ov_SC03_098_jr_8013FFD8.o: JTBL_PADS := 0,0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38,+0x58
build/src/ov_SC03_098/ov_SC03_098_jr_8015444C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x70
build/src/ov_SC03_098/ov_SC03_098_jr_80154C24.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x24
build/src/ov_SC03_098/ov_SC03_098_jr_801588CC.o: JTBL_PADS := 0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x28,+0x48
build/src/ov_SC03_098/ov_SC03_098_jr_80159C84.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_098/ov_SC03_098_jr_8015AE2C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_098/ov_SC03_098_jr_8016AB6C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_098/ov_SC03_098_jr_80178D40.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x178
build/src/ov_SC03_098/ov_SC03_098_jr_8017D898.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38
build/src/ov_SC03_098/ov_SC03_098_o0c.o: JTBL_PADS := 0,4,4,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x38,+0xa8,+0x118
ov_SC03_098_CHECK_SHA  := config/check.ov_SC03_098.sha
ov_SC03_098_SYMBOLS    := config/symbols.ov_SC03_098.txt
ov_SC03_098_SIG        := .run/sig.ov_SC03_098.jsonl
ov_SC03_098_GHIDRA_PROG := ov_SC03_098
ov_SC03_098_VRAM_BASE  := 0x80128158
ov_SC03_098_TEXT_LO    := 0x80128158
ov_SC03_098_TEXT_HI    := 0x801C58B7
ov_SC03_098_ASM_DIR     := asm/ov_SC03_098
ov_SC03_098_SRC_DIR     := src/ov_SC03_098
ov_SC03_098_UNDEF_SYMS  := build/ov_SC03_098/undefined_syms_auto.txt
ov_SC03_098_UNDEF_FUNCS := build/ov_SC03_098/undefined_funcs_auto.txt

# --- ov_SC03_099 (location overlay SC03/FILE_099, vram 0x80128158 — onboarded by new_overlay.sh) ---
ov_SC03_099_EXE        := extracted/retail/SC03.CD.dir/FILE_099.dir/0.4.dec
ov_SC03_099_NAME       := ov_SC03_099
ov_SC03_099_OUT_DIR    := build/ov_SC03_099
ov_SC03_099_OUT        := $(ov_SC03_099_OUT_DIR)/$(ov_SC03_099_NAME)
ov_SC03_099_ELF        := $(ov_SC03_099_OUT).elf
ov_SC03_099_MAPFILE    := $(ov_SC03_099_OUT).map
ov_SC03_099_LD_SCRIPT  := $(ov_SC03_099_OUT).ld
ov_SC03_099_SPLAT_YAML := config/splat.ov_SC03_099.yaml
ov_SC03_099_JTBL_INTERLEAVE := --order tail.data.o,ov_SC03_099.o,ov_SC03_099_jr_8012ACE0.o,tail2.data.o,ov_SC03_099_jr_80135888.o,tail3.data.o,ov_SC03_099_jr_80135A4C.o,tail4.data.o,ov_SC03_099_jr_80135D20.o,tail5.data.o,ov_SC03_099_jr_801380E0.o,ov_SC03_099_o0c.o,tail6.data.o,ov_SC03_099_jr_8013F350.o,tail7.data.o,ov_SC03_099_jr_8013FFD8.o,tail8.data.o,ov_SC03_099_jr_80140608.o,tail9.data.o,ov_SC03_099_jr_8015444C.o,ov_SC03_099_jr_80154C24.o,ov_SC03_099_jr_801588CC.o,ov_SC03_099_jr_80159C84.o,tail10.data.o,ov_SC03_099_jr_8015A3C8.o,tail11.data.o,ov_SC03_099_jr_8015AE2C.o,tail12.data.o,ov_SC03_099_jr_8015C32C.o,tail13.data.o,ov_SC03_099_jr_8016AB6C.o,tail14.data.o,ov_SC03_099_jr_80171B4C.o,ov_SC03_099_jr_801734BC.o,tail15.data.o,ov_SC03_099_jr_801789AC.o,ov_SC03_099_jr_80178D40.o,tail16.data.o,ov_SC03_099_jr_8017A4AC.o,tail17.data.o,ov_SC03_099_jr_8017AE2C.o,ov_SC03_099_jr_8017BEBC.o,ov_SC03_099_jr_80182F24.o,tail18.data.o,trailing.o  # Phase-26 §8 jtbl-rodata carve
build/src/ov_SC03_099/ov_SC03_099.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14
build/src/ov_SC03_099/ov_SC03_099_jr_8012ACE0.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0xcc,+0xe0
build/src/ov_SC03_099/ov_SC03_099_jr_80135D20.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC03_099/ov_SC03_099_jr_8013F350.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_099/ov_SC03_099_jr_8013FFD8.o: JTBL_PADS := 0,0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38,+0x58
build/src/ov_SC03_099/ov_SC03_099_jr_8015444C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x70
build/src/ov_SC03_099/ov_SC03_099_jr_80154C24.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x24
build/src/ov_SC03_099/ov_SC03_099_jr_801588CC.o: JTBL_PADS := 0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x28,+0x48
build/src/ov_SC03_099/ov_SC03_099_jr_80159C84.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_099/ov_SC03_099_jr_8015AE2C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_099/ov_SC03_099_jr_8016AB6C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_099/ov_SC03_099_jr_80178D40.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x178
build/src/ov_SC03_099/ov_SC03_099_jr_8017BEBC.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38
build/src/ov_SC03_099/ov_SC03_099_o0c.o: JTBL_PADS := 0,4,4,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x38,+0xa8,+0x118
ov_SC03_099_CHECK_SHA  := config/check.ov_SC03_099.sha
ov_SC03_099_SYMBOLS    := config/symbols.ov_SC03_099.txt
ov_SC03_099_SIG        := .run/sig.ov_SC03_099.jsonl
ov_SC03_099_GHIDRA_PROG := ov_SC03_099
ov_SC03_099_VRAM_BASE  := 0x80128158
ov_SC03_099_TEXT_LO    := 0x80128158
ov_SC03_099_TEXT_HI    := 0x801BF45F
ov_SC03_099_ASM_DIR     := asm/ov_SC03_099
ov_SC03_099_SRC_DIR     := src/ov_SC03_099
ov_SC03_099_UNDEF_SYMS  := build/ov_SC03_099/undefined_syms_auto.txt
ov_SC03_099_UNDEF_FUNCS := build/ov_SC03_099/undefined_funcs_auto.txt

# --- ov_SC03_100 (location overlay SC03/FILE_100, vram 0x80128158 — onboarded by new_overlay.sh) ---
ov_SC03_100_EXE        := extracted/retail/SC03.CD.dir/FILE_100.dir/0.4.dec
ov_SC03_100_NAME       := ov_SC03_100
ov_SC03_100_OUT_DIR    := build/ov_SC03_100
ov_SC03_100_OUT        := $(ov_SC03_100_OUT_DIR)/$(ov_SC03_100_NAME)
ov_SC03_100_ELF        := $(ov_SC03_100_OUT).elf
ov_SC03_100_MAPFILE    := $(ov_SC03_100_OUT).map
ov_SC03_100_LD_SCRIPT  := $(ov_SC03_100_OUT).ld
ov_SC03_100_SPLAT_YAML := config/splat.ov_SC03_100.yaml
ov_SC03_100_JTBL_INTERLEAVE := --order tail.data.o,ov_SC03_100.o,ov_SC03_100_jr_8012ACE0.o,tail2.data.o,ov_SC03_100_jr_80135888.o,tail3.data.o,ov_SC03_100_jr_80135A4C.o,tail4.data.o,ov_SC03_100_jr_80135D20.o,tail5.data.o,ov_SC03_100_jr_801380E0.o,ov_SC03_100_o0c.o,tail6.data.o,ov_SC03_100_jr_8013F350.o,tail7.data.o,ov_SC03_100_jr_8013FFD8.o,tail8.data.o,ov_SC03_100_jr_80140608.o,tail9.data.o,ov_SC03_100_jr_8015444C.o,ov_SC03_100_jr_80154C24.o,ov_SC03_100_jr_801588CC.o,ov_SC03_100_jr_80159C84.o,tail10.data.o,ov_SC03_100_jr_8015A3C8.o,tail11.data.o,ov_SC03_100_jr_8015AE2C.o,tail12.data.o,ov_SC03_100_jr_8015C32C.o,tail13.data.o,ov_SC03_100_jr_8016AB6C.o,tail14.data.o,ov_SC03_100_jr_80171B4C.o,ov_SC03_100_jr_801734BC.o,tail15.data.o,ov_SC03_100_jr_801789AC.o,ov_SC03_100_jr_80178D40.o,tail16.data.o,ov_SC03_100_jr_8017A4AC.o,tail17.data.o,ov_SC03_100_jr_8017AE2C.o,ov_SC03_100_jr_8017D898.o,ov_SC03_100_jr_80183C10.o,tail18.data.o,trailing.o  # Phase-26 §8 jtbl-rodata carve
build/src/ov_SC03_100/ov_SC03_100.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14
build/src/ov_SC03_100/ov_SC03_100_jr_8012ACE0.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0xcc,+0xe0
build/src/ov_SC03_100/ov_SC03_100_jr_80135D20.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC03_100/ov_SC03_100_jr_8013F350.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_100/ov_SC03_100_jr_8013FFD8.o: JTBL_PADS := 0,0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38,+0x58
build/src/ov_SC03_100/ov_SC03_100_jr_8015444C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x70
build/src/ov_SC03_100/ov_SC03_100_jr_80154C24.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x24
build/src/ov_SC03_100/ov_SC03_100_jr_801588CC.o: JTBL_PADS := 0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x28,+0x48
build/src/ov_SC03_100/ov_SC03_100_jr_80159C84.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_100/ov_SC03_100_jr_8015AE2C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_100/ov_SC03_100_jr_8016AB6C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_100/ov_SC03_100_jr_80178D40.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x178
build/src/ov_SC03_100/ov_SC03_100_jr_8017D898.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38
build/src/ov_SC03_100/ov_SC03_100_o0c.o: JTBL_PADS := 0,4,4,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x38,+0xa8,+0x118
ov_SC03_100_CHECK_SHA  := config/check.ov_SC03_100.sha
ov_SC03_100_SYMBOLS    := config/symbols.ov_SC03_100.txt
ov_SC03_100_SIG        := .run/sig.ov_SC03_100.jsonl
ov_SC03_100_GHIDRA_PROG := ov_SC03_100
ov_SC03_100_VRAM_BASE  := 0x80128158
ov_SC03_100_TEXT_LO    := 0x80128158
ov_SC03_100_TEXT_HI    := 0x801C8967
ov_SC03_100_ASM_DIR     := asm/ov_SC03_100
ov_SC03_100_SRC_DIR     := src/ov_SC03_100
ov_SC03_100_UNDEF_SYMS  := build/ov_SC03_100/undefined_syms_auto.txt
ov_SC03_100_UNDEF_FUNCS := build/ov_SC03_100/undefined_funcs_auto.txt

# --- ov_SC03_101 (location overlay SC03/FILE_101, vram 0x80128158 — onboarded by new_overlay.sh) ---
ov_SC03_101_EXE        := extracted/retail/SC03.CD.dir/FILE_101.dir/0.4.dec
ov_SC03_101_NAME       := ov_SC03_101
ov_SC03_101_OUT_DIR    := build/ov_SC03_101
ov_SC03_101_OUT        := $(ov_SC03_101_OUT_DIR)/$(ov_SC03_101_NAME)
ov_SC03_101_ELF        := $(ov_SC03_101_OUT).elf
ov_SC03_101_MAPFILE    := $(ov_SC03_101_OUT).map
ov_SC03_101_LD_SCRIPT  := $(ov_SC03_101_OUT).ld
ov_SC03_101_SPLAT_YAML := config/splat.ov_SC03_101.yaml
ov_SC03_101_JTBL_INTERLEAVE := --order tail.data.o,ov_SC03_101.o,ov_SC03_101_jr_8012ACE0.o,tail2.data.o,ov_SC03_101_jr_80135888.o,tail3.data.o,ov_SC03_101_jr_80135A4C.o,tail4.data.o,ov_SC03_101_jr_80135D20.o,tail5.data.o,ov_SC03_101_jr_801380E0.o,ov_SC03_101_o0c.o,tail6.data.o,ov_SC03_101_jr_8013F350.o,tail7.data.o,ov_SC03_101_jr_8013FFD8.o,tail8.data.o,ov_SC03_101_jr_80140608.o,tail9.data.o,ov_SC03_101_jr_8015444C.o,ov_SC03_101_jr_80154C24.o,ov_SC03_101_jr_801588CC.o,ov_SC03_101_jr_80159C84.o,tail10.data.o,ov_SC03_101_jr_8015A3C8.o,tail11.data.o,ov_SC03_101_jr_8015AE2C.o,tail12.data.o,ov_SC03_101_jr_8015C32C.o,tail13.data.o,ov_SC03_101_jr_8016AB6C.o,tail14.data.o,ov_SC03_101_jr_80171B4C.o,ov_SC03_101_jr_801734BC.o,tail15.data.o,ov_SC03_101_jr_801789AC.o,ov_SC03_101_jr_80178D40.o,tail16.data.o,ov_SC03_101_jr_8017A4AC.o,tail17.data.o,ov_SC03_101_jr_8017AE2C.o,ov_SC03_101_jr_8017CA80.o,tail18.data.o,ov_SC03_101_jr_801833CC.o,tail19.data.o,trailing.o  # Phase-26 §8 jtbl-rodata carve
build/src/ov_SC03_101/ov_SC03_101.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14
build/src/ov_SC03_101/ov_SC03_101_jr_8012ACE0.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0xcc,+0xe0
build/src/ov_SC03_101/ov_SC03_101_jr_80135D20.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC03_101/ov_SC03_101_jr_8013F350.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_101/ov_SC03_101_jr_8013FFD8.o: JTBL_PADS := 0,0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38,+0x58
build/src/ov_SC03_101/ov_SC03_101_jr_8015444C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x70
build/src/ov_SC03_101/ov_SC03_101_jr_80154C24.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x24
build/src/ov_SC03_101/ov_SC03_101_jr_801588CC.o: JTBL_PADS := 0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x28,+0x48
build/src/ov_SC03_101/ov_SC03_101_jr_80159C84.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_101/ov_SC03_101_jr_8015AE2C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_101/ov_SC03_101_jr_8016AB6C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_101/ov_SC03_101_jr_80178D40.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x178
build/src/ov_SC03_101/ov_SC03_101_jr_8017CA80.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_101/ov_SC03_101_o0c.o: JTBL_PADS := 0,4,4,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x38,+0xa8,+0x118
ov_SC03_101_CHECK_SHA  := config/check.ov_SC03_101.sha
ov_SC03_101_SYMBOLS    := config/symbols.ov_SC03_101.txt
ov_SC03_101_SIG        := .run/sig.ov_SC03_101.jsonl
ov_SC03_101_GHIDRA_PROG := ov_SC03_101
ov_SC03_101_VRAM_BASE  := 0x80128158
ov_SC03_101_TEXT_LO    := 0x80128158
ov_SC03_101_TEXT_HI    := 0x8019E227
ov_SC03_101_ASM_DIR     := asm/ov_SC03_101
ov_SC03_101_SRC_DIR     := src/ov_SC03_101
ov_SC03_101_UNDEF_SYMS  := build/ov_SC03_101/undefined_syms_auto.txt
ov_SC03_101_UNDEF_FUNCS := build/ov_SC03_101/undefined_funcs_auto.txt

# --- ov_SC03_102 (location overlay SC03/FILE_102, vram 0x80128158 — onboarded by new_overlay.sh) ---
ov_SC03_102_EXE        := extracted/retail/SC03.CD.dir/FILE_102.dir/0.4.dec
ov_SC03_102_NAME       := ov_SC03_102
ov_SC03_102_OUT_DIR    := build/ov_SC03_102
ov_SC03_102_OUT        := $(ov_SC03_102_OUT_DIR)/$(ov_SC03_102_NAME)
ov_SC03_102_ELF        := $(ov_SC03_102_OUT).elf
ov_SC03_102_MAPFILE    := $(ov_SC03_102_OUT).map
ov_SC03_102_LD_SCRIPT  := $(ov_SC03_102_OUT).ld
ov_SC03_102_SPLAT_YAML := config/splat.ov_SC03_102.yaml
ov_SC03_102_JTBL_INTERLEAVE := --order tail.data.o,ov_SC03_102.o,ov_SC03_102_jr_8012ACE0.o,tail2.data.o,ov_SC03_102_jr_80135888.o,tail3.data.o,ov_SC03_102_jr_80135A4C.o,tail4.data.o,ov_SC03_102_jr_80135D20.o,tail5.data.o,ov_SC03_102_jr_801380E0.o,ov_SC03_102_o0c.o,tail6.data.o,ov_SC03_102_jr_8013F350.o,tail7.data.o,ov_SC03_102_jr_8013FFD8.o,tail8.data.o,ov_SC03_102_jr_80140608.o,tail9.data.o,ov_SC03_102_jr_8015444C.o,ov_SC03_102_jr_80154C24.o,ov_SC03_102_jr_801588CC.o,ov_SC03_102_jr_80159C84.o,tail10.data.o,ov_SC03_102_jr_8015A3C8.o,tail11.data.o,ov_SC03_102_jr_8015AE2C.o,tail12.data.o,ov_SC03_102_jr_8015C32C.o,tail13.data.o,ov_SC03_102_jr_8016AB6C.o,tail14.data.o,ov_SC03_102_jr_80171B4C.o,ov_SC03_102_jr_801734BC.o,tail15.data.o,ov_SC03_102_jr_801789AC.o,ov_SC03_102_jr_80178D40.o,tail16.data.o,ov_SC03_102_jr_8017A4AC.o,tail17.data.o,ov_SC03_102_jr_8017AE2C.o,ov_SC03_102_jr_8017BEBC.o,ov_SC03_102_jr_801855D0.o,tail18.data.o,trailing.o  # Phase-26 §8 jtbl-rodata carve
build/src/ov_SC03_102/ov_SC03_102.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14
build/src/ov_SC03_102/ov_SC03_102_jr_8012ACE0.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0xcc,+0xe0
build/src/ov_SC03_102/ov_SC03_102_jr_80135D20.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC03_102/ov_SC03_102_jr_8013F350.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_102/ov_SC03_102_jr_8013FFD8.o: JTBL_PADS := 0,0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38,+0x58
build/src/ov_SC03_102/ov_SC03_102_jr_8015444C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x70
build/src/ov_SC03_102/ov_SC03_102_jr_80154C24.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x24
build/src/ov_SC03_102/ov_SC03_102_jr_801588CC.o: JTBL_PADS := 0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x28,+0x48
build/src/ov_SC03_102/ov_SC03_102_jr_80159C84.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_102/ov_SC03_102_jr_8015AE2C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_102/ov_SC03_102_jr_8016AB6C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_102/ov_SC03_102_jr_80178D40.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x178
build/src/ov_SC03_102/ov_SC03_102_jr_8017BEBC.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38
build/src/ov_SC03_102/ov_SC03_102_o0c.o: JTBL_PADS := 0,4,4,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x38,+0xa8,+0x118
ov_SC03_102_CHECK_SHA  := config/check.ov_SC03_102.sha
ov_SC03_102_SYMBOLS    := config/symbols.ov_SC03_102.txt
ov_SC03_102_SIG        := .run/sig.ov_SC03_102.jsonl
ov_SC03_102_GHIDRA_PROG := ov_SC03_102
ov_SC03_102_VRAM_BASE  := 0x80128158
ov_SC03_102_TEXT_LO    := 0x80128158
ov_SC03_102_TEXT_HI    := 0x801B9C27
ov_SC03_102_ASM_DIR     := asm/ov_SC03_102
ov_SC03_102_SRC_DIR     := src/ov_SC03_102
ov_SC03_102_UNDEF_SYMS  := build/ov_SC03_102/undefined_syms_auto.txt
ov_SC03_102_UNDEF_FUNCS := build/ov_SC03_102/undefined_funcs_auto.txt

# --- ov_SC03_103 (location overlay SC03/FILE_103, vram 0x80128158 — onboarded by new_overlay.sh) ---
ov_SC03_103_EXE        := extracted/retail/SC03.CD.dir/FILE_103.dir/0.4.dec
ov_SC03_103_NAME       := ov_SC03_103
ov_SC03_103_OUT_DIR    := build/ov_SC03_103
ov_SC03_103_OUT        := $(ov_SC03_103_OUT_DIR)/$(ov_SC03_103_NAME)
ov_SC03_103_ELF        := $(ov_SC03_103_OUT).elf
ov_SC03_103_MAPFILE    := $(ov_SC03_103_OUT).map
ov_SC03_103_LD_SCRIPT  := $(ov_SC03_103_OUT).ld
ov_SC03_103_SPLAT_YAML := config/splat.ov_SC03_103.yaml
ov_SC03_103_JTBL_INTERLEAVE := --order tail.data.o,ov_SC03_103.o,ov_SC03_103_jr_8012ACE0.o,tail2.data.o,ov_SC03_103_jr_80135888.o,tail3.data.o,ov_SC03_103_jr_80135A4C.o,tail4.data.o,ov_SC03_103_jr_80135D20.o,tail5.data.o,ov_SC03_103_jr_801380E0.o,ov_SC03_103_o0c.o,tail6.data.o,ov_SC03_103_jr_8013F350.o,tail7.data.o,ov_SC03_103_jr_8014032C.o,tail8.data.o,ov_SC03_103_jr_80140608.o,tail9.data.o,ov_SC03_103_jr_8015444C.o,ov_SC03_103_jr_80154C24.o,ov_SC03_103_jr_801588CC.o,ov_SC03_103_jr_80159C84.o,tail10.data.o,ov_SC03_103_jr_8015A3C8.o,tail11.data.o,ov_SC03_103_jr_8015AE2C.o,tail12.data.o,ov_SC03_103_jr_8015C32C.o,tail13.data.o,ov_SC03_103_jr_8016AB6C.o,tail14.data.o,ov_SC03_103_jr_80171B4C.o,ov_SC03_103_jr_801734BC.o,tail15.data.o,ov_SC03_103_jr_801789AC.o,ov_SC03_103_jr_80178D40.o,tail16.data.o,ov_SC03_103_jr_8017A4AC.o,tail17.data.o,ov_SC03_103_jr_8017AE2C.o,ov_SC03_103_jr_8017C294.o,ov_SC03_103_jr_80183C34.o,tail18.data.o,trailing.o  # Phase-26 §8 jtbl-rodata carve
build/src/ov_SC03_103/ov_SC03_103.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14
build/src/ov_SC03_103/ov_SC03_103_jr_8012ACE0.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0xcc,+0xe0
build/src/ov_SC03_103/ov_SC03_103_jr_80135D20.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC03_103/ov_SC03_103_jr_8013F350.o: JTBL_PADS := 0,0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38,+0x58
build/src/ov_SC03_103/ov_SC03_103_jr_8014032C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_103/ov_SC03_103_jr_8015444C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x70
build/src/ov_SC03_103/ov_SC03_103_jr_80154C24.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x24
build/src/ov_SC03_103/ov_SC03_103_jr_801588CC.o: JTBL_PADS := 0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x28,+0x48
build/src/ov_SC03_103/ov_SC03_103_jr_80159C84.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_103/ov_SC03_103_jr_8015AE2C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_103/ov_SC03_103_jr_8016AB6C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_103/ov_SC03_103_jr_80178D40.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x178
build/src/ov_SC03_103/ov_SC03_103_jr_8017C294.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38
build/src/ov_SC03_103/ov_SC03_103_o0c.o: JTBL_PADS := 0,4,4,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x38,+0xa8,+0x118
ov_SC03_103_CHECK_SHA  := config/check.ov_SC03_103.sha
ov_SC03_103_SYMBOLS    := config/symbols.ov_SC03_103.txt
ov_SC03_103_SIG        := .run/sig.ov_SC03_103.jsonl
ov_SC03_103_GHIDRA_PROG := ov_SC03_103
ov_SC03_103_VRAM_BASE  := 0x80128158
ov_SC03_103_TEXT_LO    := 0x80128158
ov_SC03_103_TEXT_HI    := 0x801C4DD7
ov_SC03_103_ASM_DIR     := asm/ov_SC03_103
ov_SC03_103_SRC_DIR     := src/ov_SC03_103
ov_SC03_103_UNDEF_SYMS  := build/ov_SC03_103/undefined_syms_auto.txt
ov_SC03_103_UNDEF_FUNCS := build/ov_SC03_103/undefined_funcs_auto.txt

# --- ov_SC03_104 (location overlay SC03/FILE_104, vram 0x80128158 — onboarded by new_overlay.sh) ---
ov_SC03_104_EXE        := extracted/retail/SC03.CD.dir/FILE_104.dir/0.4.dec
ov_SC03_104_NAME       := ov_SC03_104
ov_SC03_104_OUT_DIR    := build/ov_SC03_104
ov_SC03_104_OUT        := $(ov_SC03_104_OUT_DIR)/$(ov_SC03_104_NAME)
ov_SC03_104_ELF        := $(ov_SC03_104_OUT).elf
ov_SC03_104_MAPFILE    := $(ov_SC03_104_OUT).map
ov_SC03_104_LD_SCRIPT  := $(ov_SC03_104_OUT).ld
ov_SC03_104_SPLAT_YAML := config/splat.ov_SC03_104.yaml
ov_SC03_104_JTBL_INTERLEAVE := --order tail.data.o,ov_SC03_104.o,ov_SC03_104_jr_8012ACE0.o,tail2.data.o,ov_SC03_104_jr_80135888.o,tail3.data.o,ov_SC03_104_jr_80135A4C.o,tail4.data.o,ov_SC03_104_jr_80135D20.o,tail5.data.o,ov_SC03_104_jr_801380E0.o,ov_SC03_104_o0c.o,tail6.data.o,ov_SC03_104_jr_8013F350.o,tail7.data.o,ov_SC03_104_jr_8013FFD8.o,tail8.data.o,ov_SC03_104_jr_80140608.o,tail9.data.o,ov_SC03_104_jr_8015444C.o,ov_SC03_104_jr_80154C24.o,ov_SC03_104_jr_801588CC.o,ov_SC03_104_jr_80159C84.o,tail10.data.o,ov_SC03_104_jr_8015A3C8.o,tail11.data.o,ov_SC03_104_jr_8015AE2C.o,tail12.data.o,ov_SC03_104_jr_8015C32C.o,tail13.data.o,ov_SC03_104_jr_8016AB6C.o,tail14.data.o,ov_SC03_104_jr_80171B4C.o,ov_SC03_104_jr_801734BC.o,tail15.data.o,ov_SC03_104_jr_801789AC.o,ov_SC03_104_jr_80178D40.o,tail16.data.o,ov_SC03_104_jr_8017A4AC.o,tail17.data.o,ov_SC03_104_jr_8017AE2C.o,ov_SC03_104_jr_8017CA80.o,ov_SC03_104_jr_80182038.o,tail18.data.o,ov_SC03_104_jr_80186538.o,ov_SC03_104_jr_80189FE4.o,tail19.data.o,trailing.o  # Phase-26 §8 jtbl-rodata carve
build/src/ov_SC03_104/ov_SC03_104.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14
build/src/ov_SC03_104/ov_SC03_104_jr_8012ACE0.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0xcc,+0xe0
build/src/ov_SC03_104/ov_SC03_104_jr_80135D20.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC03_104/ov_SC03_104_jr_8013F350.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_104/ov_SC03_104_jr_8013FFD8.o: JTBL_PADS := 0,0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38,+0x58
build/src/ov_SC03_104/ov_SC03_104_jr_8015444C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x70
build/src/ov_SC03_104/ov_SC03_104_jr_80154C24.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x24
build/src/ov_SC03_104/ov_SC03_104_jr_801588CC.o: JTBL_PADS := 0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x28,+0x48
build/src/ov_SC03_104/ov_SC03_104_jr_80159C84.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_104/ov_SC03_104_jr_8015AE2C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_104/ov_SC03_104_jr_8016AB6C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_104/ov_SC03_104_jr_80178D40.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x178
build/src/ov_SC03_104/ov_SC03_104_jr_80186538.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC03_104/ov_SC03_104_o0c.o: JTBL_PADS := 0,4,4,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x38,+0xa8,+0x118
ov_SC03_104_CHECK_SHA  := config/check.ov_SC03_104.sha
ov_SC03_104_SYMBOLS    := config/symbols.ov_SC03_104.txt
ov_SC03_104_SIG        := .run/sig.ov_SC03_104.jsonl
ov_SC03_104_GHIDRA_PROG := ov_SC03_104
ov_SC03_104_VRAM_BASE  := 0x80128158
ov_SC03_104_TEXT_LO    := 0x80128158
ov_SC03_104_TEXT_HI    := 0x801C0497
ov_SC03_104_ASM_DIR     := asm/ov_SC03_104
ov_SC03_104_SRC_DIR     := src/ov_SC03_104
ov_SC03_104_UNDEF_SYMS  := build/ov_SC03_104/undefined_syms_auto.txt
ov_SC03_104_UNDEF_FUNCS := build/ov_SC03_104/undefined_funcs_auto.txt

# --- ov_SC03_105 (location overlay SC03/FILE_105, vram 0x80128158 — onboarded by new_overlay.sh) ---
ov_SC03_105_EXE        := extracted/retail/SC03.CD.dir/FILE_105.dir/0.4.dec
ov_SC03_105_NAME       := ov_SC03_105
ov_SC03_105_OUT_DIR    := build/ov_SC03_105
ov_SC03_105_OUT        := $(ov_SC03_105_OUT_DIR)/$(ov_SC03_105_NAME)
ov_SC03_105_ELF        := $(ov_SC03_105_OUT).elf
ov_SC03_105_MAPFILE    := $(ov_SC03_105_OUT).map
ov_SC03_105_LD_SCRIPT  := $(ov_SC03_105_OUT).ld
ov_SC03_105_SPLAT_YAML := config/splat.ov_SC03_105.yaml
ov_SC03_105_JTBL_INTERLEAVE := --order tail.data.o,ov_SC03_105.o,ov_SC03_105_jr_8012ACE0.o,tail2.data.o,ov_SC03_105_jr_80135888.o,tail3.data.o,ov_SC03_105_jr_80135A4C.o,tail4.data.o,ov_SC03_105_jr_80135D20.o,tail5.data.o,ov_SC03_105_jr_801380E0.o,ov_SC03_105_o0c.o,tail6.data.o,ov_SC03_105_jr_8013F350.o,tail7.data.o,ov_SC03_105_jr_8013FFD8.o,tail8.data.o,ov_SC03_105_jr_80140608.o,tail9.data.o,ov_SC03_105_jr_8015444C.o,ov_SC03_105_jr_80154C24.o,ov_SC03_105_jr_801588CC.o,ov_SC03_105_jr_80159C84.o,tail10.data.o,ov_SC03_105_jr_8015A3C8.o,tail11.data.o,ov_SC03_105_jr_8015AE2C.o,tail12.data.o,ov_SC03_105_jr_8015C32C.o,tail13.data.o,ov_SC03_105_jr_8016AB6C.o,tail14.data.o,ov_SC03_105_jr_80171B4C.o,ov_SC03_105_jr_801734BC.o,tail15.data.o,ov_SC03_105_jr_801789AC.o,ov_SC03_105_jr_80178D40.o,tail16.data.o,ov_SC03_105_jr_8017A4AC.o,tail17.data.o,ov_SC03_105_jr_8017AE2C.o,tail18.data.o,ov_SC03_105_jr_8017C8D0.o,tail19.data.o,ov_SC03_105_jr_80186B24.o,ov_SC03_105_jr_80186DDC.o,tail20.data.o,ov_SC03_105_jr_80189798.o,tail21.data.o,trailing.o  # Phase-26 §8 jtbl-rodata carve
build/src/ov_SC03_105/ov_SC03_105.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14
build/src/ov_SC03_105/ov_SC03_105_jr_8012ACE0.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0xcc,+0xe0
build/src/ov_SC03_105/ov_SC03_105_jr_80135D20.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC03_105/ov_SC03_105_jr_8013F350.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_105/ov_SC03_105_jr_8013FFD8.o: JTBL_PADS := 0,0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38,+0x58
build/src/ov_SC03_105/ov_SC03_105_jr_8015444C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x70
build/src/ov_SC03_105/ov_SC03_105_jr_80154C24.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x24
build/src/ov_SC03_105/ov_SC03_105_jr_801588CC.o: JTBL_PADS := 0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x28,+0x48
build/src/ov_SC03_105/ov_SC03_105_jr_80159C84.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_105/ov_SC03_105_jr_8015AE2C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_105/ov_SC03_105_jr_8016AB6C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_105/ov_SC03_105_jr_80178D40.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x178
build/src/ov_SC03_105/ov_SC03_105_jr_8017C8D0.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x34
build/src/ov_SC03_105/ov_SC03_105_o0c.o: JTBL_PADS := 0,4,4,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x38,+0xa8,+0x118
ov_SC03_105_CHECK_SHA  := config/check.ov_SC03_105.sha
ov_SC03_105_SYMBOLS    := config/symbols.ov_SC03_105.txt
ov_SC03_105_SIG        := .run/sig.ov_SC03_105.jsonl
ov_SC03_105_GHIDRA_PROG := ov_SC03_105
ov_SC03_105_VRAM_BASE  := 0x80128158
ov_SC03_105_TEXT_LO    := 0x80128158
ov_SC03_105_TEXT_HI    := 0x801BCD1F
ov_SC03_105_ASM_DIR     := asm/ov_SC03_105
ov_SC03_105_SRC_DIR     := src/ov_SC03_105
ov_SC03_105_UNDEF_SYMS  := build/ov_SC03_105/undefined_syms_auto.txt
ov_SC03_105_UNDEF_FUNCS := build/ov_SC03_105/undefined_funcs_auto.txt

# --- ov_SC03_108 (location overlay SC03/FILE_108, vram 0x80128158 — onboarded by new_overlay.sh) ---
ov_SC03_108_EXE        := extracted/retail/SC03.CD.dir/FILE_108.dir/0.4.dec
ov_SC03_108_NAME       := ov_SC03_108
ov_SC03_108_OUT_DIR    := build/ov_SC03_108
ov_SC03_108_OUT        := $(ov_SC03_108_OUT_DIR)/$(ov_SC03_108_NAME)
ov_SC03_108_ELF        := $(ov_SC03_108_OUT).elf
ov_SC03_108_MAPFILE    := $(ov_SC03_108_OUT).map
ov_SC03_108_LD_SCRIPT  := $(ov_SC03_108_OUT).ld
ov_SC03_108_SPLAT_YAML := config/splat.ov_SC03_108.yaml
ov_SC03_108_JTBL_INTERLEAVE := --order tail.data.o,ov_SC03_108.o,ov_SC03_108_jr_8012ACE0.o,tail2.data.o,ov_SC03_108_jr_80135888.o,tail3.data.o,ov_SC03_108_jr_80135A4C.o,tail4.data.o,ov_SC03_108_jr_80135D20.o,tail5.data.o,ov_SC03_108_jr_801380E0.o,ov_SC03_108_o0c.o,tail6.data.o,ov_SC03_108_jr_8013F350.o,tail7.data.o,ov_SC03_108_jr_8013FFD8.o,tail8.data.o,ov_SC03_108_jr_80140608.o,tail9.data.o,ov_SC03_108_jr_8015444C.o,ov_SC03_108_jr_80154C24.o,ov_SC03_108_jr_801588CC.o,ov_SC03_108_jr_80159C84.o,tail10.data.o,ov_SC03_108_jr_8015A3C8.o,tail11.data.o,ov_SC03_108_jr_8015AE2C.o,tail12.data.o,ov_SC03_108_jr_8015C32C.o,tail13.data.o,ov_SC03_108_jr_8016AB6C.o,tail14.data.o,ov_SC03_108_jr_80171B4C.o,ov_SC03_108_jr_801734BC.o,tail15.data.o,ov_SC03_108_jr_801789AC.o,ov_SC03_108_jr_80178D40.o,tail16.data.o,ov_SC03_108_jr_8017A4AC.o,tail17.data.o,ov_SC03_108_jr_8017AE2C.o,ov_SC03_108_jr_8017BEBC.o,tail18.data.o,ov_SC03_108_jr_8017F83C.o,tail19.data.o,trailing.o  # Phase-26 §8 jtbl-rodata carve
build/src/ov_SC03_108/ov_SC03_108.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14
build/src/ov_SC03_108/ov_SC03_108_jr_8012ACE0.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0xcc,+0xe0
build/src/ov_SC03_108/ov_SC03_108_jr_80135D20.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC03_108/ov_SC03_108_jr_8013F350.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_108/ov_SC03_108_jr_8013FFD8.o: JTBL_PADS := 0,0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38,+0x58
build/src/ov_SC03_108/ov_SC03_108_jr_8015444C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x70
build/src/ov_SC03_108/ov_SC03_108_jr_80154C24.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x24
build/src/ov_SC03_108/ov_SC03_108_jr_801588CC.o: JTBL_PADS := 0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x28,+0x48
build/src/ov_SC03_108/ov_SC03_108_jr_80159C84.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_108/ov_SC03_108_jr_8015AE2C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_108/ov_SC03_108_jr_80178D40.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x178
build/src/ov_SC03_108/ov_SC03_108_jr_8017F83C.o: JTBL_PADS := 0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18,+0xe0
build/src/ov_SC03_108/ov_SC03_108_o0c.o: JTBL_PADS := 0,4,4,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x38,+0xa8,+0x118
ov_SC03_108_CHECK_SHA  := config/check.ov_SC03_108.sha
ov_SC03_108_SYMBOLS    := config/symbols.ov_SC03_108.txt
ov_SC03_108_SIG        := .run/sig.ov_SC03_108.jsonl
ov_SC03_108_GHIDRA_PROG := ov_SC03_108
ov_SC03_108_VRAM_BASE  := 0x80128158
ov_SC03_108_TEXT_LO    := 0x80128158
ov_SC03_108_TEXT_HI    := 0x801A1AA7
ov_SC03_108_ASM_DIR     := asm/ov_SC03_108
ov_SC03_108_SRC_DIR     := src/ov_SC03_108
ov_SC03_108_UNDEF_SYMS  := build/ov_SC03_108/undefined_syms_auto.txt
ov_SC03_108_UNDEF_FUNCS := build/ov_SC03_108/undefined_funcs_auto.txt

# --- ov_SC03_109 (location overlay SC03/FILE_109, vram 0x80128158 — onboarded by new_overlay.sh) ---
ov_SC03_109_EXE        := extracted/retail/SC03.CD.dir/FILE_109.dir/0.4.dec
ov_SC03_109_NAME       := ov_SC03_109
ov_SC03_109_OUT_DIR    := build/ov_SC03_109
ov_SC03_109_OUT        := $(ov_SC03_109_OUT_DIR)/$(ov_SC03_109_NAME)
ov_SC03_109_ELF        := $(ov_SC03_109_OUT).elf
ov_SC03_109_MAPFILE    := $(ov_SC03_109_OUT).map
ov_SC03_109_LD_SCRIPT  := $(ov_SC03_109_OUT).ld
ov_SC03_109_SPLAT_YAML := config/splat.ov_SC03_109.yaml
ov_SC03_109_JTBL_INTERLEAVE := --order tail.data.o,ov_SC03_109.o,ov_SC03_109_jr_8012ACE0.o,tail2.data.o,ov_SC03_109_jr_80135888.o,tail3.data.o,ov_SC03_109_jr_80135A4C.o,tail4.data.o,ov_SC03_109_jr_80135D20.o,tail5.data.o,ov_SC03_109_jr_801380E0.o,ov_SC03_109_o0c.o,tail6.data.o,ov_SC03_109_jr_8013F350.o,tail7.data.o,ov_SC03_109_jr_8013FFD8.o,tail8.data.o,ov_SC03_109_jr_80140608.o,tail9.data.o,ov_SC03_109_jr_8015444C.o,ov_SC03_109_jr_80154C24.o,ov_SC03_109_jr_801588CC.o,ov_SC03_109_jr_80159C84.o,tail10.data.o,ov_SC03_109_jr_8015A3C8.o,tail11.data.o,ov_SC03_109_jr_8015AE2C.o,tail12.data.o,ov_SC03_109_jr_8015C32C.o,tail13.data.o,ov_SC03_109_jr_8016AB6C.o,tail14.data.o,ov_SC03_109_jr_80171B4C.o,ov_SC03_109_jr_801734BC.o,tail15.data.o,ov_SC03_109_jr_801789AC.o,ov_SC03_109_jr_80178D40.o,tail16.data.o,ov_SC03_109_jr_8017A4AC.o,tail17.data.o,ov_SC03_109_jr_8017AE2C.o,ov_SC03_109_jr_8017C180.o,tail18.data.o,trailing.o  # Phase-26 §8 jtbl-rodata carve
build/src/ov_SC03_109/ov_SC03_109.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14
build/src/ov_SC03_109/ov_SC03_109_jr_8012ACE0.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0xcc,+0xe0
build/src/ov_SC03_109/ov_SC03_109_jr_80135D20.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC03_109/ov_SC03_109_jr_8013F350.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_109/ov_SC03_109_jr_8013FFD8.o: JTBL_PADS := 0,0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38,+0x58
build/src/ov_SC03_109/ov_SC03_109_jr_8015444C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x70
build/src/ov_SC03_109/ov_SC03_109_jr_80154C24.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x24
build/src/ov_SC03_109/ov_SC03_109_jr_801588CC.o: JTBL_PADS := 0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x28,+0x48
build/src/ov_SC03_109/ov_SC03_109_jr_80159C84.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_109/ov_SC03_109_jr_8015AE2C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_109/ov_SC03_109_jr_8016AB6C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_109/ov_SC03_109_jr_80178D40.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x178
build/src/ov_SC03_109/ov_SC03_109_o0c.o: JTBL_PADS := 0,4,4,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x38,+0xa8,+0x118
ov_SC03_109_CHECK_SHA  := config/check.ov_SC03_109.sha
ov_SC03_109_SYMBOLS    := config/symbols.ov_SC03_109.txt
ov_SC03_109_SIG        := .run/sig.ov_SC03_109.jsonl
ov_SC03_109_GHIDRA_PROG := ov_SC03_109
ov_SC03_109_VRAM_BASE  := 0x80128158
ov_SC03_109_TEXT_LO    := 0x80128158
ov_SC03_109_TEXT_HI    := 0x8019A4AF
ov_SC03_109_ASM_DIR     := asm/ov_SC03_109
ov_SC03_109_SRC_DIR     := src/ov_SC03_109
ov_SC03_109_UNDEF_SYMS  := build/ov_SC03_109/undefined_syms_auto.txt
ov_SC03_109_UNDEF_FUNCS := build/ov_SC03_109/undefined_funcs_auto.txt

# --- ov_SC03_110 (location overlay SC03/FILE_110, vram 0x80128158 — onboarded by new_overlay.sh) ---
ov_SC03_110_EXE        := extracted/retail/SC03.CD.dir/FILE_110.dir/0.4.dec
ov_SC03_110_NAME       := ov_SC03_110
ov_SC03_110_OUT_DIR    := build/ov_SC03_110
ov_SC03_110_OUT        := $(ov_SC03_110_OUT_DIR)/$(ov_SC03_110_NAME)
ov_SC03_110_ELF        := $(ov_SC03_110_OUT).elf
ov_SC03_110_MAPFILE    := $(ov_SC03_110_OUT).map
ov_SC03_110_LD_SCRIPT  := $(ov_SC03_110_OUT).ld
ov_SC03_110_SPLAT_YAML := config/splat.ov_SC03_110.yaml
ov_SC03_110_JTBL_INTERLEAVE := --order tail.data.o,ov_SC03_110.o,ov_SC03_110_jr_8012ACE0.o,tail2.data.o,ov_SC03_110_jr_80135888.o,tail3.data.o,ov_SC03_110_jr_80135A4C.o,tail4.data.o,ov_SC03_110_jr_80135D20.o,tail5.data.o,ov_SC03_110_jr_801380E0.o,ov_SC03_110_o0c.o,tail6.data.o,ov_SC03_110_jr_8013F350.o,tail7.data.o,ov_SC03_110_jr_8013FFD8.o,tail8.data.o,ov_SC03_110_jr_80140608.o,tail9.data.o,ov_SC03_110_jr_8015444C.o,ov_SC03_110_jr_80154C24.o,ov_SC03_110_jr_801588CC.o,ov_SC03_110_jr_80159C84.o,tail10.data.o,ov_SC03_110_jr_8015A3C8.o,tail11.data.o,ov_SC03_110_jr_8015AE2C.o,tail12.data.o,ov_SC03_110_jr_8015C32C.o,tail13.data.o,ov_SC03_110_jr_8016AB6C.o,tail14.data.o,ov_SC03_110_jr_80171B4C.o,ov_SC03_110_jr_801734BC.o,tail15.data.o,ov_SC03_110_jr_801789AC.o,ov_SC03_110_jr_80178D40.o,tail16.data.o,ov_SC03_110_jr_8017A4AC.o,tail17.data.o,ov_SC03_110_jr_8017AE2C.o,ov_SC03_110_jr_8017D898.o,ov_SC03_110_jr_8017FBC8.o,tail18.data.o,trailing.o  # Phase-26 §8 jtbl-rodata carve
build/src/ov_SC03_110/ov_SC03_110.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14
build/src/ov_SC03_110/ov_SC03_110_jr_8012ACE0.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0xcc,+0xe0
build/src/ov_SC03_110/ov_SC03_110_jr_80135D20.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC03_110/ov_SC03_110_jr_8013F350.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_110/ov_SC03_110_jr_8013FFD8.o: JTBL_PADS := 0,0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38,+0x58
build/src/ov_SC03_110/ov_SC03_110_jr_8015444C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x70
build/src/ov_SC03_110/ov_SC03_110_jr_80154C24.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x24
build/src/ov_SC03_110/ov_SC03_110_jr_801588CC.o: JTBL_PADS := 0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x28,+0x48
build/src/ov_SC03_110/ov_SC03_110_jr_80159C84.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_110/ov_SC03_110_jr_8015AE2C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_110/ov_SC03_110_jr_8016AB6C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_110/ov_SC03_110_jr_80178D40.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x178
build/src/ov_SC03_110/ov_SC03_110_jr_8017D898.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_110/ov_SC03_110_jr_8017FBC8.o: JTBL_PADS := 0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18,+0xe0
build/src/ov_SC03_110/ov_SC03_110_o0c.o: JTBL_PADS := 0,4,4,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x38,+0xa8,+0x118
ov_SC03_110_CHECK_SHA  := config/check.ov_SC03_110.sha
ov_SC03_110_SYMBOLS    := config/symbols.ov_SC03_110.txt
ov_SC03_110_SIG        := .run/sig.ov_SC03_110.jsonl
ov_SC03_110_GHIDRA_PROG := ov_SC03_110
ov_SC03_110_VRAM_BASE  := 0x80128158
ov_SC03_110_TEXT_LO    := 0x80128158
ov_SC03_110_TEXT_HI    := 0x801A24DF
ov_SC03_110_ASM_DIR     := asm/ov_SC03_110
ov_SC03_110_SRC_DIR     := src/ov_SC03_110
ov_SC03_110_UNDEF_SYMS  := build/ov_SC03_110/undefined_syms_auto.txt
ov_SC03_110_UNDEF_FUNCS := build/ov_SC03_110/undefined_funcs_auto.txt

# --- ov_SC03_111 (location overlay SC03/FILE_111, vram 0x80128158 — onboarded by new_overlay.sh) ---
ov_SC03_111_EXE        := extracted/retail/SC03.CD.dir/FILE_111.dir/0.4.dec
ov_SC03_111_NAME       := ov_SC03_111
ov_SC03_111_OUT_DIR    := build/ov_SC03_111
ov_SC03_111_OUT        := $(ov_SC03_111_OUT_DIR)/$(ov_SC03_111_NAME)
ov_SC03_111_ELF        := $(ov_SC03_111_OUT).elf
ov_SC03_111_MAPFILE    := $(ov_SC03_111_OUT).map
ov_SC03_111_LD_SCRIPT  := $(ov_SC03_111_OUT).ld
ov_SC03_111_SPLAT_YAML := config/splat.ov_SC03_111.yaml
ov_SC03_111_JTBL_INTERLEAVE := --order tail.data.o,ov_SC03_111.o,ov_SC03_111_jr_8012ACE0.o,tail2.data.o,ov_SC03_111_jr_80135888.o,tail3.data.o,ov_SC03_111_jr_80135A4C.o,tail4.data.o,ov_SC03_111_jr_80135D20.o,tail5.data.o,ov_SC03_111_jr_801380E0.o,ov_SC03_111_o0c.o,tail6.data.o,ov_SC03_111_jr_8013F350.o,tail7.data.o,ov_SC03_111_jr_8013FFD8.o,tail8.data.o,ov_SC03_111_jr_80140608.o,tail9.data.o,ov_SC03_111_jr_8015444C.o,ov_SC03_111_jr_80154C24.o,ov_SC03_111_jr_801588CC.o,ov_SC03_111_jr_80159C84.o,tail10.data.o,ov_SC03_111_jr_8015A3C8.o,tail11.data.o,ov_SC03_111_jr_8015AE2C.o,tail12.data.o,ov_SC03_111_jr_8015C32C.o,tail13.data.o,ov_SC03_111_jr_8016AB6C.o,tail14.data.o,ov_SC03_111_jr_80171B4C.o,ov_SC03_111_jr_801734BC.o,tail15.data.o,ov_SC03_111_jr_801789AC.o,ov_SC03_111_jr_80178D40.o,tail16.data.o,ov_SC03_111_jr_8017A4AC.o,tail17.data.o,ov_SC03_111_jr_8017AE2C.o,ov_SC03_111_jr_8017EC58.o,tail18.data.o,trailing.o  # Phase-26 §8 jtbl-rodata carve
build/src/ov_SC03_111/ov_SC03_111.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14
build/src/ov_SC03_111/ov_SC03_111_jr_8012ACE0.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0xcc,+0xe0
build/src/ov_SC03_111/ov_SC03_111_jr_80135D20.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC03_111/ov_SC03_111_jr_8013F350.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_111/ov_SC03_111_jr_8013FFD8.o: JTBL_PADS := 0,0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38,+0x58
build/src/ov_SC03_111/ov_SC03_111_jr_8015444C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x70
build/src/ov_SC03_111/ov_SC03_111_jr_80154C24.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x24
build/src/ov_SC03_111/ov_SC03_111_jr_801588CC.o: JTBL_PADS := 0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x28,+0x48
build/src/ov_SC03_111/ov_SC03_111_jr_80159C84.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_111/ov_SC03_111_jr_8015AE2C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_111/ov_SC03_111_jr_8016AB6C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_111/ov_SC03_111_jr_80178D40.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x178
build/src/ov_SC03_111/ov_SC03_111_jr_8017EC58.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x88
build/src/ov_SC03_111/ov_SC03_111_o0c.o: JTBL_PADS := 0,4,4,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x38,+0xa8,+0x118
ov_SC03_111_CHECK_SHA  := config/check.ov_SC03_111.sha
ov_SC03_111_SYMBOLS    := config/symbols.ov_SC03_111.txt
ov_SC03_111_SIG        := .run/sig.ov_SC03_111.jsonl
ov_SC03_111_GHIDRA_PROG := ov_SC03_111
ov_SC03_111_VRAM_BASE  := 0x80128158
ov_SC03_111_TEXT_LO    := 0x80128158
ov_SC03_111_TEXT_HI    := 0x801B9B87
ov_SC03_111_ASM_DIR     := asm/ov_SC03_111
ov_SC03_111_SRC_DIR     := src/ov_SC03_111
ov_SC03_111_UNDEF_SYMS  := build/ov_SC03_111/undefined_syms_auto.txt
ov_SC03_111_UNDEF_FUNCS := build/ov_SC03_111/undefined_funcs_auto.txt

# --- ov_SC03_112 (location overlay SC03/FILE_112, vram 0x80128158 — onboarded by new_overlay.sh) ---
ov_SC03_112_EXE        := extracted/retail/SC03.CD.dir/FILE_112.dir/0.4.dec
ov_SC03_112_NAME       := ov_SC03_112
ov_SC03_112_OUT_DIR    := build/ov_SC03_112
ov_SC03_112_OUT        := $(ov_SC03_112_OUT_DIR)/$(ov_SC03_112_NAME)
ov_SC03_112_ELF        := $(ov_SC03_112_OUT).elf
ov_SC03_112_MAPFILE    := $(ov_SC03_112_OUT).map
ov_SC03_112_LD_SCRIPT  := $(ov_SC03_112_OUT).ld
ov_SC03_112_SPLAT_YAML := config/splat.ov_SC03_112.yaml
ov_SC03_112_JTBL_INTERLEAVE := --order tail.data.o,ov_SC03_112.o,ov_SC03_112_jr_8012ACE0.o,tail2.data.o,ov_SC03_112_jr_80135888.o,tail3.data.o,ov_SC03_112_jr_80135A4C.o,tail4.data.o,ov_SC03_112_jr_80135D20.o,tail5.data.o,ov_SC03_112_jr_801380E0.o,ov_SC03_112_o0c.o,tail6.data.o,ov_SC03_112_jr_8013F350.o,tail7.data.o,ov_SC03_112_jr_8013FFD8.o,tail8.data.o,ov_SC03_112_jr_80140608.o,tail9.data.o,ov_SC03_112_jr_8015444C.o,ov_SC03_112_jr_80154C24.o,ov_SC03_112_jr_801588CC.o,ov_SC03_112_jr_80159C84.o,tail10.data.o,ov_SC03_112_jr_8015A3C8.o,tail11.data.o,ov_SC03_112_jr_8015AE2C.o,tail12.data.o,ov_SC03_112_jr_8015C32C.o,tail13.data.o,ov_SC03_112_jr_8016AB6C.o,tail14.data.o,ov_SC03_112_jr_80171B4C.o,ov_SC03_112_jr_801734BC.o,tail15.data.o,ov_SC03_112_jr_801789AC.o,ov_SC03_112_jr_80178D40.o,tail16.data.o,ov_SC03_112_jr_8017A4AC.o,tail17.data.o,ov_SC03_112_jr_8017AE2C.o,ov_SC03_112_jr_8017C294.o,tail18.data.o,ov_SC03_112_jr_801817E0.o,ov_SC03_112_jr_80181F74.o,ov_SC03_112_jr_80182BF8.o,ov_SC03_112_jr_80183AE0.o,tail19.data.o,trailing.o  # Phase-26 §8 jtbl-rodata carve
build/src/ov_SC03_112/ov_SC03_112.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14
build/src/ov_SC03_112/ov_SC03_112_jr_8012ACE0.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0xcc,+0xe0
build/src/ov_SC03_112/ov_SC03_112_jr_80135D20.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC03_112/ov_SC03_112_jr_8013F350.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_112/ov_SC03_112_jr_8013FFD8.o: JTBL_PADS := 0,0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38,+0x58
build/src/ov_SC03_112/ov_SC03_112_jr_8015444C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x70
build/src/ov_SC03_112/ov_SC03_112_jr_80154C24.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x24
build/src/ov_SC03_112/ov_SC03_112_jr_801588CC.o: JTBL_PADS := 0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x28,+0x48
build/src/ov_SC03_112/ov_SC03_112_jr_80159C84.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_112/ov_SC03_112_jr_8015AE2C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_112/ov_SC03_112_jr_8016AB6C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_112/ov_SC03_112_jr_80178D40.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x178
build/src/ov_SC03_112/ov_SC03_112_jr_801817E0.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC03_112/ov_SC03_112_o0c.o: JTBL_PADS := 0,4,4,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x38,+0xa8,+0x118
ov_SC03_112_CHECK_SHA  := config/check.ov_SC03_112.sha
ov_SC03_112_SYMBOLS    := config/symbols.ov_SC03_112.txt
ov_SC03_112_SIG        := .run/sig.ov_SC03_112.jsonl
ov_SC03_112_GHIDRA_PROG := ov_SC03_112
ov_SC03_112_VRAM_BASE  := 0x80128158
ov_SC03_112_TEXT_LO    := 0x80128158
ov_SC03_112_TEXT_HI    := 0x801AD14F
ov_SC03_112_ASM_DIR     := asm/ov_SC03_112
ov_SC03_112_SRC_DIR     := src/ov_SC03_112
ov_SC03_112_UNDEF_SYMS  := build/ov_SC03_112/undefined_syms_auto.txt
ov_SC03_112_UNDEF_FUNCS := build/ov_SC03_112/undefined_funcs_auto.txt

# --- ov_SC03_113 (location overlay SC03/FILE_113, vram 0x80128158 — onboarded by new_overlay.sh) ---
ov_SC03_113_EXE        := extracted/retail/SC03.CD.dir/FILE_113.dir/0.4.dec
ov_SC03_113_NAME       := ov_SC03_113
ov_SC03_113_OUT_DIR    := build/ov_SC03_113
ov_SC03_113_OUT        := $(ov_SC03_113_OUT_DIR)/$(ov_SC03_113_NAME)
ov_SC03_113_ELF        := $(ov_SC03_113_OUT).elf
ov_SC03_113_MAPFILE    := $(ov_SC03_113_OUT).map
ov_SC03_113_LD_SCRIPT  := $(ov_SC03_113_OUT).ld
ov_SC03_113_SPLAT_YAML := config/splat.ov_SC03_113.yaml
ov_SC03_113_JTBL_INTERLEAVE := --order tail.data.o,ov_SC03_113.o,ov_SC03_113_jr_8012ACE0.o,tail2.data.o,ov_SC03_113_jr_80135888.o,tail3.data.o,ov_SC03_113_jr_80135A4C.o,tail4.data.o,ov_SC03_113_jr_80135D20.o,tail5.data.o,ov_SC03_113_jr_801380E0.o,ov_SC03_113_o0c.o,tail6.data.o,ov_SC03_113_jr_8013F350.o,tail7.data.o,ov_SC03_113_jr_8013FFD8.o,tail8.data.o,ov_SC03_113_jr_80140608.o,tail9.data.o,ov_SC03_113_jr_8015444C.o,ov_SC03_113_jr_80154C24.o,ov_SC03_113_jr_801588CC.o,ov_SC03_113_jr_80159C84.o,tail10.data.o,ov_SC03_113_jr_8015A3C8.o,tail11.data.o,ov_SC03_113_jr_8015AE2C.o,tail12.data.o,ov_SC03_113_jr_8015C32C.o,tail13.data.o,ov_SC03_113_jr_8016AB6C.o,tail14.data.o,ov_SC03_113_jr_80171B4C.o,ov_SC03_113_jr_801734BC.o,tail15.data.o,ov_SC03_113_jr_801789AC.o,ov_SC03_113_jr_80178D40.o,tail16.data.o,ov_SC03_113_jr_8017A4AC.o,tail17.data.o,ov_SC03_113_jr_8017AE2C.o,ov_SC03_113_jr_8017C294.o,tail18.data.o,trailing.o  # Phase-26 §8 jtbl-rodata carve
build/src/ov_SC03_113/ov_SC03_113.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14
build/src/ov_SC03_113/ov_SC03_113_jr_8012ACE0.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0xcc,+0xe0
build/src/ov_SC03_113/ov_SC03_113_jr_80135D20.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC03_113/ov_SC03_113_jr_8013F350.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_113/ov_SC03_113_jr_8013FFD8.o: JTBL_PADS := 0,0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38,+0x58
build/src/ov_SC03_113/ov_SC03_113_jr_8015444C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x70
build/src/ov_SC03_113/ov_SC03_113_jr_80154C24.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x24
build/src/ov_SC03_113/ov_SC03_113_jr_801588CC.o: JTBL_PADS := 0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x28,+0x48
build/src/ov_SC03_113/ov_SC03_113_jr_80159C84.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_113/ov_SC03_113_jr_8015AE2C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_113/ov_SC03_113_jr_8016AB6C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_113/ov_SC03_113_jr_80178D40.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x178
build/src/ov_SC03_113/ov_SC03_113_jr_8017C294.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x88
build/src/ov_SC03_113/ov_SC03_113_o0c.o: JTBL_PADS := 0,4,4,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x38,+0xa8,+0x118
ov_SC03_113_CHECK_SHA  := config/check.ov_SC03_113.sha
ov_SC03_113_SYMBOLS    := config/symbols.ov_SC03_113.txt
ov_SC03_113_SIG        := .run/sig.ov_SC03_113.jsonl
ov_SC03_113_GHIDRA_PROG := ov_SC03_113
ov_SC03_113_VRAM_BASE  := 0x80128158
ov_SC03_113_TEXT_LO    := 0x80128158
ov_SC03_113_TEXT_HI    := 0x801A5CEF
ov_SC03_113_ASM_DIR     := asm/ov_SC03_113
ov_SC03_113_SRC_DIR     := src/ov_SC03_113
ov_SC03_113_UNDEF_SYMS  := build/ov_SC03_113/undefined_syms_auto.txt
ov_SC03_113_UNDEF_FUNCS := build/ov_SC03_113/undefined_funcs_auto.txt

# --- ov_SC03_114 (location overlay SC03/FILE_114, vram 0x80128158 — onboarded by new_overlay.sh) ---
ov_SC03_114_EXE        := extracted/retail/SC03.CD.dir/FILE_114.dir/0.4.dec
ov_SC03_114_NAME       := ov_SC03_114
ov_SC03_114_OUT_DIR    := build/ov_SC03_114
ov_SC03_114_OUT        := $(ov_SC03_114_OUT_DIR)/$(ov_SC03_114_NAME)
ov_SC03_114_ELF        := $(ov_SC03_114_OUT).elf
ov_SC03_114_MAPFILE    := $(ov_SC03_114_OUT).map
ov_SC03_114_LD_SCRIPT  := $(ov_SC03_114_OUT).ld
ov_SC03_114_SPLAT_YAML := config/splat.ov_SC03_114.yaml
ov_SC03_114_JTBL_INTERLEAVE := --order tail.data.o,ov_SC03_114.o,ov_SC03_114_jr_8012ACE0.o,tail2.data.o,ov_SC03_114_jr_80135888.o,tail3.data.o,ov_SC03_114_jr_80135A4C.o,tail4.data.o,ov_SC03_114_jr_80135D20.o,tail5.data.o,ov_SC03_114_jr_801380E0.o,ov_SC03_114_o0c.o,tail6.data.o,ov_SC03_114_jr_8013F350.o,tail7.data.o,ov_SC03_114_jr_8013FFD8.o,tail8.data.o,ov_SC03_114_jr_80140608.o,tail9.data.o,ov_SC03_114_jr_8015444C.o,ov_SC03_114_jr_80154C24.o,ov_SC03_114_jr_801588CC.o,ov_SC03_114_jr_80159C84.o,tail10.data.o,ov_SC03_114_jr_8015A3C8.o,tail11.data.o,ov_SC03_114_jr_8015AE2C.o,tail12.data.o,ov_SC03_114_jr_8015C32C.o,tail13.data.o,ov_SC03_114_jr_8016AB6C.o,tail14.data.o,ov_SC03_114_jr_80171B4C.o,ov_SC03_114_jr_801734BC.o,tail15.data.o,ov_SC03_114_jr_801789AC.o,ov_SC03_114_jr_80178D40.o,tail16.data.o,ov_SC03_114_jr_8017A4AC.o,tail17.data.o,ov_SC03_114_jr_8017AE2C.o,ov_SC03_114_jr_8017BEBC.o,tail18.data.o,trailing.o  # Phase-26 §8 jtbl-rodata carve
build/src/ov_SC03_114/ov_SC03_114.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14
build/src/ov_SC03_114/ov_SC03_114_jr_8012ACE0.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0xcc,+0xe0
build/src/ov_SC03_114/ov_SC03_114_jr_80135D20.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC03_114/ov_SC03_114_jr_8013F350.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_114/ov_SC03_114_jr_8013FFD8.o: JTBL_PADS := 0,0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38,+0x58
build/src/ov_SC03_114/ov_SC03_114_jr_8015444C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x70
build/src/ov_SC03_114/ov_SC03_114_jr_80154C24.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x24
build/src/ov_SC03_114/ov_SC03_114_jr_801588CC.o: JTBL_PADS := 0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x28,+0x48
build/src/ov_SC03_114/ov_SC03_114_jr_80159C84.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_114/ov_SC03_114_jr_8015AE2C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_114/ov_SC03_114_jr_8016AB6C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_114/ov_SC03_114_jr_80178D40.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x178
build/src/ov_SC03_114/ov_SC03_114_jr_8017BEBC.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_114/ov_SC03_114_o0c.o: JTBL_PADS := 0,4,4,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x38,+0xa8,+0x118
ov_SC03_114_CHECK_SHA  := config/check.ov_SC03_114.sha
ov_SC03_114_SYMBOLS    := config/symbols.ov_SC03_114.txt
ov_SC03_114_SIG        := .run/sig.ov_SC03_114.jsonl
ov_SC03_114_GHIDRA_PROG := ov_SC03_114
ov_SC03_114_VRAM_BASE  := 0x80128158
ov_SC03_114_TEXT_LO    := 0x80128158
ov_SC03_114_TEXT_HI    := 0x801A9867
ov_SC03_114_ASM_DIR     := asm/ov_SC03_114
ov_SC03_114_SRC_DIR     := src/ov_SC03_114
ov_SC03_114_UNDEF_SYMS  := build/ov_SC03_114/undefined_syms_auto.txt
ov_SC03_114_UNDEF_FUNCS := build/ov_SC03_114/undefined_funcs_auto.txt

# --- ov_SC03_115 (location overlay SC03/FILE_115, vram 0x80128158 — onboarded by new_overlay.sh) ---
ov_SC03_115_EXE        := extracted/retail/SC03.CD.dir/FILE_115.dir/0.4.dec
ov_SC03_115_NAME       := ov_SC03_115
ov_SC03_115_OUT_DIR    := build/ov_SC03_115
ov_SC03_115_OUT        := $(ov_SC03_115_OUT_DIR)/$(ov_SC03_115_NAME)
ov_SC03_115_ELF        := $(ov_SC03_115_OUT).elf
ov_SC03_115_MAPFILE    := $(ov_SC03_115_OUT).map
ov_SC03_115_LD_SCRIPT  := $(ov_SC03_115_OUT).ld
ov_SC03_115_SPLAT_YAML := config/splat.ov_SC03_115.yaml
ov_SC03_115_JTBL_INTERLEAVE := --order tail.data.o,ov_SC03_115.o,ov_SC03_115_jr_8012ACE0.o,tail2.data.o,ov_SC03_115_jr_80135888.o,tail3.data.o,ov_SC03_115_jr_80135A4C.o,tail4.data.o,ov_SC03_115_jr_80135D20.o,tail5.data.o,ov_SC03_115_jr_801380E0.o,ov_SC03_115_o0c.o,tail6.data.o,ov_SC03_115_jr_8013F350.o,tail7.data.o,ov_SC03_115_jr_8013FFD8.o,tail8.data.o,ov_SC03_115_jr_80140608.o,tail9.data.o,ov_SC03_115_jr_8015444C.o,ov_SC03_115_jr_80154C24.o,ov_SC03_115_jr_801588CC.o,ov_SC03_115_jr_80159C84.o,tail10.data.o,ov_SC03_115_jr_8015A3C8.o,tail11.data.o,ov_SC03_115_jr_8015AE2C.o,tail12.data.o,ov_SC03_115_jr_8015C32C.o,tail13.data.o,ov_SC03_115_jr_8016AB6C.o,tail14.data.o,ov_SC03_115_jr_80171B4C.o,ov_SC03_115_jr_801734BC.o,tail15.data.o,ov_SC03_115_jr_801789AC.o,ov_SC03_115_jr_80178D40.o,tail16.data.o,ov_SC03_115_jr_8017A4AC.o,tail17.data.o,ov_SC03_115_jr_8017AE2C.o,ov_SC03_115_jr_8017BEBC.o,tail18.data.o,trailing.o  # Phase-26 §8 jtbl-rodata carve
build/src/ov_SC03_115/ov_SC03_115.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14
build/src/ov_SC03_115/ov_SC03_115_jr_8012ACE0.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0xcc,+0xe0
build/src/ov_SC03_115/ov_SC03_115_jr_80135D20.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC03_115/ov_SC03_115_jr_8013F350.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_115/ov_SC03_115_jr_8013FFD8.o: JTBL_PADS := 0,0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38,+0x58
build/src/ov_SC03_115/ov_SC03_115_jr_8015444C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x70
build/src/ov_SC03_115/ov_SC03_115_jr_80154C24.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x24
build/src/ov_SC03_115/ov_SC03_115_jr_801588CC.o: JTBL_PADS := 0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x28,+0x48
build/src/ov_SC03_115/ov_SC03_115_jr_80159C84.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_115/ov_SC03_115_jr_8015AE2C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_115/ov_SC03_115_jr_8016AB6C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_115/ov_SC03_115_jr_80178D40.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x178
build/src/ov_SC03_115/ov_SC03_115_o0c.o: JTBL_PADS := 0,4,4,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x38,+0xa8,+0x118
ov_SC03_115_CHECK_SHA  := config/check.ov_SC03_115.sha
ov_SC03_115_SYMBOLS    := config/symbols.ov_SC03_115.txt
ov_SC03_115_SIG        := .run/sig.ov_SC03_115.jsonl
ov_SC03_115_GHIDRA_PROG := ov_SC03_115
ov_SC03_115_VRAM_BASE  := 0x80128158
ov_SC03_115_TEXT_LO    := 0x80128158
ov_SC03_115_TEXT_HI    := 0x8019513F
ov_SC03_115_ASM_DIR     := asm/ov_SC03_115
ov_SC03_115_SRC_DIR     := src/ov_SC03_115
ov_SC03_115_UNDEF_SYMS  := build/ov_SC03_115/undefined_syms_auto.txt
ov_SC03_115_UNDEF_FUNCS := build/ov_SC03_115/undefined_funcs_auto.txt

# --- ov_SC03_116 (location overlay SC03/FILE_116, vram 0x80128158 — onboarded by new_overlay.sh) ---
ov_SC03_116_EXE        := extracted/retail/SC03.CD.dir/FILE_116.dir/0.4.dec
ov_SC03_116_NAME       := ov_SC03_116
ov_SC03_116_OUT_DIR    := build/ov_SC03_116
ov_SC03_116_OUT        := $(ov_SC03_116_OUT_DIR)/$(ov_SC03_116_NAME)
ov_SC03_116_ELF        := $(ov_SC03_116_OUT).elf
ov_SC03_116_MAPFILE    := $(ov_SC03_116_OUT).map
ov_SC03_116_LD_SCRIPT  := $(ov_SC03_116_OUT).ld
ov_SC03_116_SPLAT_YAML := config/splat.ov_SC03_116.yaml
ov_SC03_116_JTBL_INTERLEAVE := --order tail.data.o,ov_SC03_116.o,ov_SC03_116_jr_8012ACE0.o,tail2.data.o,ov_SC03_116_jr_80135888.o,tail3.data.o,ov_SC03_116_jr_80135A4C.o,tail4.data.o,ov_SC03_116_jr_80135D20.o,tail5.data.o,ov_SC03_116_jr_801380E0.o,ov_SC03_116_o0c.o,tail6.data.o,ov_SC03_116_jr_8013F350.o,tail7.data.o,ov_SC03_116_jr_8013FFD8.o,tail8.data.o,ov_SC03_116_jr_80140608.o,tail9.data.o,ov_SC03_116_jr_8015444C.o,ov_SC03_116_jr_80154C24.o,ov_SC03_116_jr_801588CC.o,ov_SC03_116_jr_80159C84.o,tail10.data.o,ov_SC03_116_jr_8015A3C8.o,tail11.data.o,ov_SC03_116_jr_8015AE2C.o,tail12.data.o,ov_SC03_116_jr_8015C32C.o,tail13.data.o,ov_SC03_116_jr_8016AB6C.o,tail14.data.o,ov_SC03_116_jr_80171B4C.o,ov_SC03_116_jr_801734BC.o,tail15.data.o,ov_SC03_116_jr_801789AC.o,ov_SC03_116_jr_80178D40.o,tail16.data.o,ov_SC03_116_jr_8017A4AC.o,tail17.data.o,ov_SC03_116_jr_8017AE2C.o,tail18.data.o,trailing.o  # Phase-26 §8 jtbl-rodata carve
build/src/ov_SC03_116/ov_SC03_116.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14
build/src/ov_SC03_116/ov_SC03_116_jr_8012ACE0.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0xcc,+0xe0
build/src/ov_SC03_116/ov_SC03_116_jr_80135D20.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC03_116/ov_SC03_116_jr_8013F350.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_116/ov_SC03_116_jr_8013FFD8.o: JTBL_PADS := 0,0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38,+0x58
build/src/ov_SC03_116/ov_SC03_116_jr_8015444C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x70
build/src/ov_SC03_116/ov_SC03_116_jr_80154C24.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x24
build/src/ov_SC03_116/ov_SC03_116_jr_801588CC.o: JTBL_PADS := 0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x28,+0x48
build/src/ov_SC03_116/ov_SC03_116_jr_80159C84.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_116/ov_SC03_116_jr_8015AE2C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_116/ov_SC03_116_jr_8016AB6C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_116/ov_SC03_116_jr_80178D40.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x178
build/src/ov_SC03_116/ov_SC03_116_jr_8017AE2C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14
build/src/ov_SC03_116/ov_SC03_116_o0c.o: JTBL_PADS := 0,4,4,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x38,+0xa8,+0x118
ov_SC03_116_CHECK_SHA  := config/check.ov_SC03_116.sha
ov_SC03_116_SYMBOLS    := config/symbols.ov_SC03_116.txt
ov_SC03_116_SIG        := .run/sig.ov_SC03_116.jsonl
ov_SC03_116_GHIDRA_PROG := ov_SC03_116
ov_SC03_116_VRAM_BASE  := 0x80128158
ov_SC03_116_TEXT_LO    := 0x80128158
ov_SC03_116_TEXT_HI    := 0x80197D4F
ov_SC03_116_ASM_DIR     := asm/ov_SC03_116
ov_SC03_116_SRC_DIR     := src/ov_SC03_116
ov_SC03_116_UNDEF_SYMS  := build/ov_SC03_116/undefined_syms_auto.txt
ov_SC03_116_UNDEF_FUNCS := build/ov_SC03_116/undefined_funcs_auto.txt

# --- ov_SC03_117 (location overlay SC03/FILE_117, vram 0x80128158 — onboarded by new_overlay.sh) ---
ov_SC03_117_EXE        := extracted/retail/SC03.CD.dir/FILE_117.dir/0.4.dec
ov_SC03_117_NAME       := ov_SC03_117
ov_SC03_117_OUT_DIR    := build/ov_SC03_117
ov_SC03_117_OUT        := $(ov_SC03_117_OUT_DIR)/$(ov_SC03_117_NAME)
ov_SC03_117_ELF        := $(ov_SC03_117_OUT).elf
ov_SC03_117_MAPFILE    := $(ov_SC03_117_OUT).map
ov_SC03_117_LD_SCRIPT  := $(ov_SC03_117_OUT).ld
ov_SC03_117_SPLAT_YAML := config/splat.ov_SC03_117.yaml
ov_SC03_117_JTBL_INTERLEAVE := --order tail.data.o,ov_SC03_117.o,ov_SC03_117_jr_8012ACE0.o,tail2.data.o,ov_SC03_117_jr_80135888.o,tail3.data.o,ov_SC03_117_jr_80135A4C.o,tail4.data.o,ov_SC03_117_jr_80135D20.o,tail5.data.o,ov_SC03_117_jr_801380E0.o,ov_SC03_117_o0c.o,tail6.data.o,ov_SC03_117_jr_8013F350.o,tail7.data.o,ov_SC03_117_jr_8013FFD8.o,tail8.data.o,ov_SC03_117_jr_80140608.o,tail9.data.o,ov_SC03_117_jr_8015444C.o,ov_SC03_117_jr_80154C24.o,ov_SC03_117_jr_801588CC.o,ov_SC03_117_jr_80159C84.o,tail10.data.o,ov_SC03_117_jr_8015A3C8.o,tail11.data.o,ov_SC03_117_jr_8015AE2C.o,tail12.data.o,ov_SC03_117_jr_8015C32C.o,tail13.data.o,ov_SC03_117_jr_8016AB6C.o,tail14.data.o,ov_SC03_117_jr_80171B4C.o,ov_SC03_117_jr_801734BC.o,tail15.data.o,ov_SC03_117_jr_801789AC.o,ov_SC03_117_jr_80178D40.o,tail16.data.o,ov_SC03_117_jr_8017A4AC.o,tail17.data.o,ov_SC03_117_jr_8017AE2C.o,ov_SC03_117_jr_8017BEBC.o,ov_SC03_117_jr_8017E6EC.o,tail18.data.o,ov_SC03_117_jr_80181C80.o,tail19.data.o,trailing.o  # Phase-26 §8 jtbl-rodata carve
build/src/ov_SC03_117/ov_SC03_117.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14
build/src/ov_SC03_117/ov_SC03_117_jr_8012ACE0.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0xcc,+0xe0
build/src/ov_SC03_117/ov_SC03_117_jr_80135D20.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC03_117/ov_SC03_117_jr_8013F350.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_117/ov_SC03_117_jr_8013FFD8.o: JTBL_PADS := 0,0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38,+0x58
build/src/ov_SC03_117/ov_SC03_117_jr_8015444C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x70
build/src/ov_SC03_117/ov_SC03_117_jr_80154C24.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x24
build/src/ov_SC03_117/ov_SC03_117_jr_801588CC.o: JTBL_PADS := 0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x28,+0x48
build/src/ov_SC03_117/ov_SC03_117_jr_80159C84.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_117/ov_SC03_117_jr_8015AE2C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_117/ov_SC03_117_jr_8016AB6C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_117/ov_SC03_117_jr_80178D40.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x178
build/src/ov_SC03_117/ov_SC03_117_jr_8017BEBC.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_117/ov_SC03_117_jr_80181C80.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x68
build/src/ov_SC03_117/ov_SC03_117_o0c.o: JTBL_PADS := 0,4,4,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x38,+0xa8,+0x118
ov_SC03_117_CHECK_SHA  := config/check.ov_SC03_117.sha
ov_SC03_117_SYMBOLS    := config/symbols.ov_SC03_117.txt
ov_SC03_117_SIG        := .run/sig.ov_SC03_117.jsonl
ov_SC03_117_GHIDRA_PROG := ov_SC03_117
ov_SC03_117_VRAM_BASE  := 0x80128158
ov_SC03_117_TEXT_LO    := 0x80128158
ov_SC03_117_TEXT_HI    := 0x801CE947
ov_SC03_117_ASM_DIR     := asm/ov_SC03_117
ov_SC03_117_SRC_DIR     := src/ov_SC03_117
ov_SC03_117_UNDEF_SYMS  := build/ov_SC03_117/undefined_syms_auto.txt
ov_SC03_117_UNDEF_FUNCS := build/ov_SC03_117/undefined_funcs_auto.txt

# --- ov_SC03_118 (location overlay SC03/FILE_118, vram 0x80128158 — onboarded by new_overlay.sh) ---
ov_SC03_118_EXE        := extracted/retail/SC03.CD.dir/FILE_118.dir/0.4.dec
ov_SC03_118_NAME       := ov_SC03_118
ov_SC03_118_OUT_DIR    := build/ov_SC03_118
ov_SC03_118_OUT        := $(ov_SC03_118_OUT_DIR)/$(ov_SC03_118_NAME)
ov_SC03_118_ELF        := $(ov_SC03_118_OUT).elf
ov_SC03_118_MAPFILE    := $(ov_SC03_118_OUT).map
ov_SC03_118_LD_SCRIPT  := $(ov_SC03_118_OUT).ld
ov_SC03_118_SPLAT_YAML := config/splat.ov_SC03_118.yaml
ov_SC03_118_JTBL_INTERLEAVE := --order tail.data.o,ov_SC03_118.o,ov_SC03_118_jr_8012ACE0.o,tail2.data.o,ov_SC03_118_jr_80135888.o,tail3.data.o,ov_SC03_118_jr_80135A4C.o,tail4.data.o,ov_SC03_118_jr_80135D20.o,tail5.data.o,ov_SC03_118_jr_801380E0.o,ov_SC03_118_o0c.o,tail6.data.o,ov_SC03_118_jr_8013F350.o,tail7.data.o,ov_SC03_118_jr_8013FFD8.o,tail8.data.o,ov_SC03_118_jr_80140608.o,tail9.data.o,ov_SC03_118_jr_8015444C.o,ov_SC03_118_jr_80154C24.o,ov_SC03_118_jr_801588CC.o,ov_SC03_118_jr_80159C84.o,tail10.data.o,ov_SC03_118_jr_8015A3C8.o,tail11.data.o,ov_SC03_118_jr_8015AE2C.o,tail12.data.o,ov_SC03_118_jr_8015C32C.o,tail13.data.o,ov_SC03_118_jr_8016AB6C.o,tail14.data.o,ov_SC03_118_jr_80171B4C.o,ov_SC03_118_jr_801734BC.o,tail15.data.o,ov_SC03_118_jr_801789AC.o,ov_SC03_118_jr_80178D40.o,tail16.data.o,ov_SC03_118_jr_8017A4AC.o,tail17.data.o,ov_SC03_118_jr_8017AE2C.o,ov_SC03_118_jr_8017FB84.o,tail18.data.o,ov_SC03_118_jr_801863CC.o,tail19.data.o,trailing.o  # Phase-26 §8 jtbl-rodata carve
build/src/ov_SC03_118/ov_SC03_118.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14
build/src/ov_SC03_118/ov_SC03_118_jr_8012ACE0.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0xcc,+0xe0
build/src/ov_SC03_118/ov_SC03_118_jr_80135D20.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC03_118/ov_SC03_118_jr_8013F350.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_118/ov_SC03_118_jr_8013FFD8.o: JTBL_PADS := 0,0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38,+0x58
build/src/ov_SC03_118/ov_SC03_118_jr_8015444C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x70
build/src/ov_SC03_118/ov_SC03_118_jr_80154C24.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x24
build/src/ov_SC03_118/ov_SC03_118_jr_801588CC.o: JTBL_PADS := 0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x28,+0x48
build/src/ov_SC03_118/ov_SC03_118_jr_80159C84.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_118/ov_SC03_118_jr_8015AE2C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_118/ov_SC03_118_jr_8016AB6C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_118/ov_SC03_118_jr_80178D40.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x178
build/src/ov_SC03_118/ov_SC03_118_jr_8017AE2C.o: JTBL_PADS := 0,0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14,+0x2c
build/src/ov_SC03_118/ov_SC03_118_jr_801863CC.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x68
build/src/ov_SC03_118/ov_SC03_118_o0c.o: JTBL_PADS := 0,4,4,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x38,+0xa8,+0x118
ov_SC03_118_CHECK_SHA  := config/check.ov_SC03_118.sha
ov_SC03_118_SYMBOLS    := config/symbols.ov_SC03_118.txt
ov_SC03_118_SIG        := .run/sig.ov_SC03_118.jsonl
ov_SC03_118_GHIDRA_PROG := ov_SC03_118
ov_SC03_118_VRAM_BASE  := 0x80128158
ov_SC03_118_TEXT_LO    := 0x80128158
ov_SC03_118_TEXT_HI    := 0x801D484F
ov_SC03_118_ASM_DIR     := asm/ov_SC03_118
ov_SC03_118_SRC_DIR     := src/ov_SC03_118
ov_SC03_118_UNDEF_SYMS  := build/ov_SC03_118/undefined_syms_auto.txt
ov_SC03_118_UNDEF_FUNCS := build/ov_SC03_118/undefined_funcs_auto.txt

# --- ov_SC03_119 (location overlay SC03/FILE_119, vram 0x80128158 — onboarded by new_overlay.sh) ---
ov_SC03_119_EXE        := extracted/retail/SC03.CD.dir/FILE_119.dir/0.4.dec
ov_SC03_119_NAME       := ov_SC03_119
ov_SC03_119_OUT_DIR    := build/ov_SC03_119
ov_SC03_119_OUT        := $(ov_SC03_119_OUT_DIR)/$(ov_SC03_119_NAME)
ov_SC03_119_ELF        := $(ov_SC03_119_OUT).elf
ov_SC03_119_MAPFILE    := $(ov_SC03_119_OUT).map
ov_SC03_119_LD_SCRIPT  := $(ov_SC03_119_OUT).ld
ov_SC03_119_SPLAT_YAML := config/splat.ov_SC03_119.yaml
ov_SC03_119_JTBL_INTERLEAVE := --order tail.data.o,ov_SC03_119.o,ov_SC03_119_jr_8012ACE0.o,tail2.data.o,ov_SC03_119_jr_80135888.o,tail3.data.o,ov_SC03_119_jr_80135A4C.o,tail4.data.o,ov_SC03_119_jr_80135D20.o,tail5.data.o,ov_SC03_119_jr_801380E0.o,ov_SC03_119_o0c.o,tail6.data.o,ov_SC03_119_jr_8013F350.o,tail7.data.o,ov_SC03_119_jr_8013FFD8.o,tail8.data.o,ov_SC03_119_jr_80140608.o,tail9.data.o,ov_SC03_119_jr_8015444C.o,ov_SC03_119_jr_80154C24.o,ov_SC03_119_jr_801588CC.o,ov_SC03_119_jr_80159C84.o,tail10.data.o,ov_SC03_119_jr_8015A3C8.o,tail11.data.o,ov_SC03_119_jr_8015AE2C.o,tail12.data.o,ov_SC03_119_jr_8015C32C.o,tail13.data.o,ov_SC03_119_jr_8016AB6C.o,tail14.data.o,ov_SC03_119_jr_80171B4C.o,ov_SC03_119_jr_801734BC.o,tail15.data.o,ov_SC03_119_jr_801789AC.o,ov_SC03_119_jr_80178D40.o,tail16.data.o,ov_SC03_119_jr_8017A4AC.o,tail17.data.o,ov_SC03_119_jr_8017AE2C.o,ov_SC03_119_jr_8017FB84.o,tail18.data.o,ov_SC03_119_jr_801863CC.o,tail19.data.o,trailing.o  # Phase-26 §8 jtbl-rodata carve
build/src/ov_SC03_119/ov_SC03_119.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14
build/src/ov_SC03_119/ov_SC03_119_jr_8012ACE0.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0xcc,+0xe0
build/src/ov_SC03_119/ov_SC03_119_jr_80135D20.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC03_119/ov_SC03_119_jr_8013F350.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_119/ov_SC03_119_jr_8013FFD8.o: JTBL_PADS := 0,0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38,+0x58
build/src/ov_SC03_119/ov_SC03_119_jr_8015444C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x70
build/src/ov_SC03_119/ov_SC03_119_jr_80154C24.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x24
build/src/ov_SC03_119/ov_SC03_119_jr_801588CC.o: JTBL_PADS := 0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x28,+0x48
build/src/ov_SC03_119/ov_SC03_119_jr_80159C84.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_119/ov_SC03_119_jr_8015AE2C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_119/ov_SC03_119_jr_8016AB6C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_119/ov_SC03_119_jr_80178D40.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x178
build/src/ov_SC03_119/ov_SC03_119_jr_8017AE2C.o: JTBL_PADS := 0,0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14,+0x2c
build/src/ov_SC03_119/ov_SC03_119_jr_801863CC.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x68
build/src/ov_SC03_119/ov_SC03_119_o0c.o: JTBL_PADS := 0,4,4,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x38,+0xa8,+0x118
ov_SC03_119_CHECK_SHA  := config/check.ov_SC03_119.sha
ov_SC03_119_SYMBOLS    := config/symbols.ov_SC03_119.txt
ov_SC03_119_SIG        := .run/sig.ov_SC03_119.jsonl
ov_SC03_119_GHIDRA_PROG := ov_SC03_119
ov_SC03_119_VRAM_BASE  := 0x80128158
ov_SC03_119_TEXT_LO    := 0x80128158
ov_SC03_119_TEXT_HI    := 0x801D484F
ov_SC03_119_ASM_DIR     := asm/ov_SC03_119
ov_SC03_119_SRC_DIR     := src/ov_SC03_119
ov_SC03_119_UNDEF_SYMS  := build/ov_SC03_119/undefined_syms_auto.txt
ov_SC03_119_UNDEF_FUNCS := build/ov_SC03_119/undefined_funcs_auto.txt

# --- ov_SC03_121 (location overlay SC03/FILE_121, vram 0x80128158 — onboarded by new_overlay.sh) ---
ov_SC03_121_EXE        := extracted/retail/SC03.CD.dir/FILE_121.dir/0.4.dec
ov_SC03_121_NAME       := ov_SC03_121
ov_SC03_121_OUT_DIR    := build/ov_SC03_121
ov_SC03_121_OUT        := $(ov_SC03_121_OUT_DIR)/$(ov_SC03_121_NAME)
ov_SC03_121_ELF        := $(ov_SC03_121_OUT).elf
ov_SC03_121_MAPFILE    := $(ov_SC03_121_OUT).map
ov_SC03_121_LD_SCRIPT  := $(ov_SC03_121_OUT).ld
ov_SC03_121_SPLAT_YAML := config/splat.ov_SC03_121.yaml
ov_SC03_121_JTBL_INTERLEAVE := --order tail.data.o,ov_SC03_121.o,ov_SC03_121_jr_8012ACE0.o,tail2.data.o,ov_SC03_121_jr_80135888.o,tail3.data.o,ov_SC03_121_jr_80135A4C.o,tail4.data.o,ov_SC03_121_jr_80135D20.o,tail5.data.o,ov_SC03_121_jr_801380E0.o,ov_SC03_121_o0c.o,tail6.data.o,ov_SC03_121_jr_8013F350.o,tail7.data.o,ov_SC03_121_jr_8013FFD8.o,tail8.data.o,ov_SC03_121_jr_80140608.o,tail9.data.o,ov_SC03_121_jr_8015444C.o,ov_SC03_121_jr_80154C24.o,ov_SC03_121_jr_801588CC.o,ov_SC03_121_jr_80159C84.o,tail10.data.o,ov_SC03_121_jr_8015A3C8.o,tail11.data.o,ov_SC03_121_jr_8015AE2C.o,tail12.data.o,ov_SC03_121_jr_8015C32C.o,tail13.data.o,ov_SC03_121_jr_8016AB6C.o,tail14.data.o,ov_SC03_121_jr_80171B4C.o,ov_SC03_121_jr_801734BC.o,tail15.data.o,ov_SC03_121_jr_801789AC.o,ov_SC03_121_jr_80178D40.o,tail16.data.o,ov_SC03_121_jr_8017A4AC.o,tail17.data.o,ov_SC03_121_jr_8017AE2C.o,ov_SC03_121_jr_8017BEBC.o,tail18.data.o,ov_SC03_121_jr_8017DF2C.o,tail19.data.o,ov_SC03_121_jr_8017E1D0.o,tail20.data.o,trailing.o  # Phase-26 §8 jtbl-rodata carve
build/src/ov_SC03_121/ov_SC03_121.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14
build/src/ov_SC03_121/ov_SC03_121_jr_8012ACE0.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0xcc,+0xe0
build/src/ov_SC03_121/ov_SC03_121_jr_80135D20.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC03_121/ov_SC03_121_jr_8013F350.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_121/ov_SC03_121_jr_8013FFD8.o: JTBL_PADS := 0,0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38,+0x58
build/src/ov_SC03_121/ov_SC03_121_jr_8015444C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x70
build/src/ov_SC03_121/ov_SC03_121_jr_80154C24.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x24
build/src/ov_SC03_121/ov_SC03_121_jr_801588CC.o: JTBL_PADS := 0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x28,+0x48
build/src/ov_SC03_121/ov_SC03_121_jr_80159C84.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_121/ov_SC03_121_jr_8015AE2C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_121/ov_SC03_121_jr_8016AB6C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_121/ov_SC03_121_jr_80178D40.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x178
build/src/ov_SC03_121/ov_SC03_121_jr_8017BEBC.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_121/ov_SC03_121_jr_8017E1D0.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14
build/src/ov_SC03_121/ov_SC03_121_o0c.o: JTBL_PADS := 0,4,4,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x38,+0xa8,+0x118
ov_SC03_121_CHECK_SHA  := config/check.ov_SC03_121.sha
ov_SC03_121_SYMBOLS    := config/symbols.ov_SC03_121.txt
ov_SC03_121_SIG        := .run/sig.ov_SC03_121.jsonl
ov_SC03_121_GHIDRA_PROG := ov_SC03_121
ov_SC03_121_VRAM_BASE  := 0x80128158
ov_SC03_121_TEXT_LO    := 0x80128158
ov_SC03_121_TEXT_HI    := 0x801AEFAF
ov_SC03_121_ASM_DIR     := asm/ov_SC03_121
ov_SC03_121_SRC_DIR     := src/ov_SC03_121
ov_SC03_121_UNDEF_SYMS  := build/ov_SC03_121/undefined_syms_auto.txt
ov_SC03_121_UNDEF_FUNCS := build/ov_SC03_121/undefined_funcs_auto.txt

# --- ov_SC03_124 (location overlay SC03/FILE_124, vram 0x80128158 — onboarded by new_overlay.sh) ---
ov_SC03_124_EXE        := extracted/retail/SC03.CD.dir/FILE_124.dir/0.4.dec
ov_SC03_124_NAME       := ov_SC03_124
ov_SC03_124_OUT_DIR    := build/ov_SC03_124
ov_SC03_124_OUT        := $(ov_SC03_124_OUT_DIR)/$(ov_SC03_124_NAME)
ov_SC03_124_ELF        := $(ov_SC03_124_OUT).elf
ov_SC03_124_MAPFILE    := $(ov_SC03_124_OUT).map
ov_SC03_124_LD_SCRIPT  := $(ov_SC03_124_OUT).ld
ov_SC03_124_SPLAT_YAML := config/splat.ov_SC03_124.yaml
ov_SC03_124_JTBL_INTERLEAVE := --order tail.data.o,ov_SC03_124.o,ov_SC03_124_jr_8012ACE0.o,tail2.data.o,ov_SC03_124_jr_80135888.o,tail3.data.o,ov_SC03_124_jr_80135A4C.o,tail4.data.o,ov_SC03_124_jr_80135D20.o,tail5.data.o,ov_SC03_124_jr_801380E0.o,ov_SC03_124_o0c.o,tail6.data.o,ov_SC03_124_jr_8013F350.o,tail7.data.o,ov_SC03_124_jr_8013FFD8.o,tail8.data.o,ov_SC03_124_jr_80140608.o,tail9.data.o,ov_SC03_124_jr_8015444C.o,ov_SC03_124_jr_80154C24.o,ov_SC03_124_jr_801588CC.o,ov_SC03_124_jr_80159C84.o,tail10.data.o,ov_SC03_124_jr_8015A3C8.o,tail11.data.o,ov_SC03_124_jr_8015AE2C.o,tail12.data.o,ov_SC03_124_jr_8015C32C.o,tail13.data.o,ov_SC03_124_jr_8016AB6C.o,tail14.data.o,ov_SC03_124_jr_80171B4C.o,ov_SC03_124_jr_801734BC.o,tail15.data.o,ov_SC03_124_jr_801789AC.o,ov_SC03_124_jr_80178D40.o,tail16.data.o,ov_SC03_124_jr_8017A4AC.o,tail17.data.o,ov_SC03_124_jr_8017AE2C.o,ov_SC03_124_jr_80181B44.o,ov_SC03_124_jr_80185498.o,tail18.data.o,ov_SC03_124_jr_80185C98.o,tail19.data.o,ov_SC03_124_jr_80187010.o,ov_SC03_124_jr_80188544.o,tail20.data.o,trailing.o  # Phase-26 §8 jtbl-rodata carve
build/src/ov_SC03_124/ov_SC03_124.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14
build/src/ov_SC03_124/ov_SC03_124_jr_8012ACE0.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0xcc,+0xe0
build/src/ov_SC03_124/ov_SC03_124_jr_80135D20.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC03_124/ov_SC03_124_jr_8013F350.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_124/ov_SC03_124_jr_8013FFD8.o: JTBL_PADS := 0,0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38,+0x58
build/src/ov_SC03_124/ov_SC03_124_jr_8015444C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x70
build/src/ov_SC03_124/ov_SC03_124_jr_80154C24.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x24
build/src/ov_SC03_124/ov_SC03_124_jr_801588CC.o: JTBL_PADS := 0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x28,+0x48
build/src/ov_SC03_124/ov_SC03_124_jr_80159C84.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_124/ov_SC03_124_jr_8015AE2C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_124/ov_SC03_124_jr_8016AB6C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_124/ov_SC03_124_jr_80178D40.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x178
build/src/ov_SC03_124/ov_SC03_124_jr_8017AE2C.o: JTBL_PADS := 0,0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14,+0x34,+0x48
build/src/ov_SC03_124/ov_SC03_124_jr_80187010.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x38
build/src/ov_SC03_124/ov_SC03_124_o0c.o: JTBL_PADS := 0,4,4,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x38,+0xa8,+0x118
ov_SC03_124_CHECK_SHA  := config/check.ov_SC03_124.sha
ov_SC03_124_SYMBOLS    := config/symbols.ov_SC03_124.txt
ov_SC03_124_SIG        := .run/sig.ov_SC03_124.jsonl
ov_SC03_124_GHIDRA_PROG := ov_SC03_124
ov_SC03_124_VRAM_BASE  := 0x80128158
ov_SC03_124_TEXT_LO    := 0x80128158
ov_SC03_124_TEXT_HI    := 0x801E25E7
ov_SC03_124_ASM_DIR     := asm/ov_SC03_124
ov_SC03_124_SRC_DIR     := src/ov_SC03_124
ov_SC03_124_UNDEF_SYMS  := build/ov_SC03_124/undefined_syms_auto.txt
ov_SC03_124_UNDEF_FUNCS := build/ov_SC03_124/undefined_funcs_auto.txt

# --- ov_SC03_125 (location overlay SC03/FILE_125, vram 0x80128158 — onboarded by new_overlay.sh) ---
ov_SC03_125_EXE        := extracted/retail/SC03.CD.dir/FILE_125.dir/0.4.dec
ov_SC03_125_NAME       := ov_SC03_125
ov_SC03_125_OUT_DIR    := build/ov_SC03_125
ov_SC03_125_OUT        := $(ov_SC03_125_OUT_DIR)/$(ov_SC03_125_NAME)
ov_SC03_125_ELF        := $(ov_SC03_125_OUT).elf
ov_SC03_125_MAPFILE    := $(ov_SC03_125_OUT).map
ov_SC03_125_LD_SCRIPT  := $(ov_SC03_125_OUT).ld
ov_SC03_125_SPLAT_YAML := config/splat.ov_SC03_125.yaml
ov_SC03_125_JTBL_INTERLEAVE := --order tail.data.o,ov_SC03_125.o,ov_SC03_125_jr_8012ACE0.o,tail2.data.o,ov_SC03_125_jr_80135888.o,tail3.data.o,ov_SC03_125_jr_80135A4C.o,tail4.data.o,ov_SC03_125_jr_80135D20.o,tail5.data.o,ov_SC03_125_jr_801380E0.o,ov_SC03_125_o0c.o,tail6.data.o,ov_SC03_125_jr_8013F350.o,tail7.data.o,ov_SC03_125_jr_8013FFD8.o,tail8.data.o,ov_SC03_125_jr_80140608.o,tail9.data.o,ov_SC03_125_jr_8015444C.o,ov_SC03_125_jr_80154C24.o,ov_SC03_125_jr_801588CC.o,ov_SC03_125_jr_80159C84.o,tail10.data.o,ov_SC03_125_jr_8015A3C8.o,tail11.data.o,ov_SC03_125_jr_8015AE2C.o,tail12.data.o,ov_SC03_125_jr_8015C32C.o,tail13.data.o,ov_SC03_125_jr_8016AB6C.o,tail14.data.o,ov_SC03_125_jr_80171B4C.o,ov_SC03_125_jr_801734BC.o,tail15.data.o,ov_SC03_125_jr_801789AC.o,ov_SC03_125_jr_80178D40.o,tail16.data.o,ov_SC03_125_jr_8017A4AC.o,tail17.data.o,ov_SC03_125_jr_8017AE2C.o,ov_SC03_125_jr_8017D604.o,tail18.data.o,ov_SC03_125_jr_80182BA0.o,tail19.data.o,trailing.o  # Phase-26 §8 jtbl-rodata carve
build/src/ov_SC03_125/ov_SC03_125.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14
build/src/ov_SC03_125/ov_SC03_125_jr_8012ACE0.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0xcc,+0xe0
build/src/ov_SC03_125/ov_SC03_125_jr_80135D20.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC03_125/ov_SC03_125_jr_8013F350.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_125/ov_SC03_125_jr_8013FFD8.o: JTBL_PADS := 0,0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38,+0x58
build/src/ov_SC03_125/ov_SC03_125_jr_8015444C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x70
build/src/ov_SC03_125/ov_SC03_125_jr_80154C24.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x24
build/src/ov_SC03_125/ov_SC03_125_jr_801588CC.o: JTBL_PADS := 0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x28,+0x48
build/src/ov_SC03_125/ov_SC03_125_jr_80159C84.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_125/ov_SC03_125_jr_8015AE2C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_125/ov_SC03_125_jr_8016AB6C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_125/ov_SC03_125_jr_80178D40.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x178
build/src/ov_SC03_125/ov_SC03_125_jr_80182BA0.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x1c
build/src/ov_SC03_125/ov_SC03_125_o0c.o: JTBL_PADS := 0,4,4,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x38,+0xa8,+0x118
ov_SC03_125_CHECK_SHA  := config/check.ov_SC03_125.sha
ov_SC03_125_SYMBOLS    := config/symbols.ov_SC03_125.txt
ov_SC03_125_SIG        := .run/sig.ov_SC03_125.jsonl
ov_SC03_125_GHIDRA_PROG := ov_SC03_125
ov_SC03_125_VRAM_BASE  := 0x80128158
ov_SC03_125_TEXT_LO    := 0x80128158
ov_SC03_125_TEXT_HI    := 0x801C453F
ov_SC03_125_ASM_DIR     := asm/ov_SC03_125
ov_SC03_125_SRC_DIR     := src/ov_SC03_125
ov_SC03_125_UNDEF_SYMS  := build/ov_SC03_125/undefined_syms_auto.txt
ov_SC03_125_UNDEF_FUNCS := build/ov_SC03_125/undefined_funcs_auto.txt

# --- ov_SC03_126 (location overlay SC03/FILE_126, vram 0x80128158 — onboarded by new_overlay.sh) ---
ov_SC03_126_EXE        := extracted/retail/SC03.CD.dir/FILE_126.dir/0.4.dec
ov_SC03_126_NAME       := ov_SC03_126
ov_SC03_126_OUT_DIR    := build/ov_SC03_126
ov_SC03_126_OUT        := $(ov_SC03_126_OUT_DIR)/$(ov_SC03_126_NAME)
ov_SC03_126_ELF        := $(ov_SC03_126_OUT).elf
ov_SC03_126_MAPFILE    := $(ov_SC03_126_OUT).map
ov_SC03_126_LD_SCRIPT  := $(ov_SC03_126_OUT).ld
ov_SC03_126_SPLAT_YAML := config/splat.ov_SC03_126.yaml
ov_SC03_126_JTBL_INTERLEAVE := --order tail.data.o,ov_SC03_126.o,ov_SC03_126_jr_8012ACE0.o,tail2.data.o,ov_SC03_126_jr_80135888.o,tail3.data.o,ov_SC03_126_jr_80135A4C.o,tail4.data.o,ov_SC03_126_jr_80135D20.o,tail5.data.o,ov_SC03_126_jr_801380E0.o,ov_SC03_126_o0c.o,tail6.data.o,ov_SC03_126_jr_8013F350.o,tail7.data.o,ov_SC03_126_jr_8013FFD8.o,tail8.data.o,ov_SC03_126_jr_80140608.o,tail9.data.o,ov_SC03_126_jr_8015444C.o,ov_SC03_126_jr_80154C24.o,ov_SC03_126_jr_801588CC.o,ov_SC03_126_jr_80159C84.o,tail10.data.o,ov_SC03_126_jr_8015A3C8.o,tail11.data.o,ov_SC03_126_jr_8015AE2C.o,tail12.data.o,ov_SC03_126_jr_8015C32C.o,tail13.data.o,ov_SC03_126_jr_8016AB6C.o,tail14.data.o,ov_SC03_126_jr_80171B4C.o,ov_SC03_126_jr_801734BC.o,tail15.data.o,ov_SC03_126_jr_801789AC.o,ov_SC03_126_jr_80178D40.o,tail16.data.o,ov_SC03_126_jr_8017A4AC.o,tail17.data.o,ov_SC03_126_jr_8017AE2C.o,ov_SC03_126_jr_8017D5C0.o,tail18.data.o,trailing.o  # Phase-26 §8 jtbl-rodata carve
build/src/ov_SC03_126/ov_SC03_126.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14
build/src/ov_SC03_126/ov_SC03_126_jr_8012ACE0.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0xcc,+0xe0
build/src/ov_SC03_126/ov_SC03_126_jr_80135D20.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC03_126/ov_SC03_126_jr_8013F350.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_126/ov_SC03_126_jr_8013FFD8.o: JTBL_PADS := 0,0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38,+0x58
build/src/ov_SC03_126/ov_SC03_126_jr_8015444C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x70
build/src/ov_SC03_126/ov_SC03_126_jr_80154C24.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x24
build/src/ov_SC03_126/ov_SC03_126_jr_801588CC.o: JTBL_PADS := 0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x28,+0x48
build/src/ov_SC03_126/ov_SC03_126_jr_80159C84.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_126/ov_SC03_126_jr_8015AE2C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_126/ov_SC03_126_jr_8016AB6C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_126/ov_SC03_126_jr_80178D40.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x178
build/src/ov_SC03_126/ov_SC03_126_jr_8017AE2C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14
build/src/ov_SC03_126/ov_SC03_126_o0c.o: JTBL_PADS := 0,4,4,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x38,+0xa8,+0x118
ov_SC03_126_CHECK_SHA  := config/check.ov_SC03_126.sha
ov_SC03_126_SYMBOLS    := config/symbols.ov_SC03_126.txt
ov_SC03_126_SIG        := .run/sig.ov_SC03_126.jsonl
ov_SC03_126_GHIDRA_PROG := ov_SC03_126
ov_SC03_126_VRAM_BASE  := 0x80128158
ov_SC03_126_TEXT_LO    := 0x80128158
ov_SC03_126_TEXT_HI    := 0x8018FB2D
ov_SC03_126_ASM_DIR     := asm/ov_SC03_126
ov_SC03_126_SRC_DIR     := src/ov_SC03_126
ov_SC03_126_UNDEF_SYMS  := build/ov_SC03_126/undefined_syms_auto.txt
ov_SC03_126_UNDEF_FUNCS := build/ov_SC03_126/undefined_funcs_auto.txt

# --- ov_SC04_002 (location overlay SC04/FILE_002, vram 0x80128158 — onboarded by new_overlay.sh) ---
ov_SC04_002_EXE        := extracted/retail/SC04.CD.dir/FILE_002.dir/0.4.dec
ov_SC04_002_NAME       := ov_SC04_002
ov_SC04_002_OUT_DIR    := build/ov_SC04_002
ov_SC04_002_OUT        := $(ov_SC04_002_OUT_DIR)/$(ov_SC04_002_NAME)
ov_SC04_002_ELF        := $(ov_SC04_002_OUT).elf
ov_SC04_002_MAPFILE    := $(ov_SC04_002_OUT).map
ov_SC04_002_LD_SCRIPT  := $(ov_SC04_002_OUT).ld
ov_SC04_002_SPLAT_YAML := config/splat.ov_SC04_002.yaml
ov_SC04_002_JTBL_INTERLEAVE := --order tail.data.o,ov_SC04_002.o,ov_SC04_002_jr_8012ACE0.o,tail2.data.o,ov_SC04_002_jr_80135888.o,tail3.data.o,ov_SC04_002_jr_80135A4C.o,tail4.data.o,ov_SC04_002_jr_80135D20.o,tail5.data.o,ov_SC04_002_jr_801380E0.o,ov_SC04_002_o0c.o,tail6.data.o,ov_SC04_002_jr_8013F350.o,tail7.data.o,ov_SC04_002_jr_8013FFD8.o,tail8.data.o,ov_SC04_002_jr_80140608.o,tail9.data.o,ov_SC04_002_jr_8015444C.o,ov_SC04_002_jr_80154C24.o,ov_SC04_002_jr_801588CC.o,ov_SC04_002_jr_80159C84.o,tail10.data.o,ov_SC04_002_jr_8015A3C8.o,tail11.data.o,ov_SC04_002_jr_8015AE2C.o,tail12.data.o,ov_SC04_002_jr_8015C32C.o,tail13.data.o,ov_SC04_002_jr_8016AB6C.o,tail14.data.o,ov_SC04_002_jr_80171B4C.o,ov_SC04_002_jr_801734BC.o,tail15.data.o,ov_SC04_002_jr_801789AC.o,ov_SC04_002_jr_80178D40.o,tail16.data.o,ov_SC04_002_jr_8017A4AC.o,tail17.data.o,ov_SC04_002_jr_8017AE2C.o,ov_SC04_002_jr_8017BEBC.o,tail18.data.o,trailing.o  # Phase-26 §8 jtbl-rodata carve
build/src/ov_SC04_002/ov_SC04_002.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14
build/src/ov_SC04_002/ov_SC04_002_jr_8012ACE0.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0xcc,+0xe0
build/src/ov_SC04_002/ov_SC04_002_jr_80135D20.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC04_002/ov_SC04_002_jr_8013F350.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC04_002/ov_SC04_002_jr_8013FFD8.o: JTBL_PADS := 0,0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38,+0x58
build/src/ov_SC04_002/ov_SC04_002_jr_8015444C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x70
build/src/ov_SC04_002/ov_SC04_002_jr_80154C24.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x24
build/src/ov_SC04_002/ov_SC04_002_jr_801588CC.o: JTBL_PADS := 0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x28,+0x48
build/src/ov_SC04_002/ov_SC04_002_jr_80159C84.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC04_002/ov_SC04_002_jr_8015AE2C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC04_002/ov_SC04_002_jr_8016AB6C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC04_002/ov_SC04_002_jr_80178D40.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x178
build/src/ov_SC04_002/ov_SC04_002_jr_8017BEBC.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC04_002/ov_SC04_002_o0c.o: JTBL_PADS := 0,4,4,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x38,+0xa8,+0x118
ov_SC04_002_CHECK_SHA  := config/check.ov_SC04_002.sha
ov_SC04_002_SYMBOLS    := config/symbols.ov_SC04_002.txt
ov_SC04_002_SIG        := .run/sig.ov_SC04_002.jsonl
ov_SC04_002_GHIDRA_PROG := ov_SC04_002
ov_SC04_002_VRAM_BASE  := 0x80128158
ov_SC04_002_TEXT_LO    := 0x80128158
ov_SC04_002_TEXT_HI    := 0x801C1737
ov_SC04_002_ASM_DIR     := asm/ov_SC04_002
ov_SC04_002_SRC_DIR     := src/ov_SC04_002
ov_SC04_002_UNDEF_SYMS  := build/ov_SC04_002/undefined_syms_auto.txt
ov_SC04_002_UNDEF_FUNCS := build/ov_SC04_002/undefined_funcs_auto.txt

# --- ov_SC04_003 (location overlay SC04/FILE_003, vram 0x80128158 — onboarded by new_overlay.sh) ---
ov_SC04_003_EXE        := extracted/retail/SC04.CD.dir/FILE_003.dir/0.4.dec
ov_SC04_003_NAME       := ov_SC04_003
ov_SC04_003_OUT_DIR    := build/ov_SC04_003
ov_SC04_003_OUT        := $(ov_SC04_003_OUT_DIR)/$(ov_SC04_003_NAME)
ov_SC04_003_ELF        := $(ov_SC04_003_OUT).elf
ov_SC04_003_MAPFILE    := $(ov_SC04_003_OUT).map
ov_SC04_003_LD_SCRIPT  := $(ov_SC04_003_OUT).ld
ov_SC04_003_SPLAT_YAML := config/splat.ov_SC04_003.yaml
ov_SC04_003_JTBL_INTERLEAVE := --order tail.data.o,ov_SC04_003.o,ov_SC04_003_jr_8012ACE0.o,tail2.data.o,ov_SC04_003_jr_80135888.o,tail3.data.o,ov_SC04_003_jr_80135A4C.o,tail4.data.o,ov_SC04_003_jr_80135D20.o,tail5.data.o,ov_SC04_003_jr_801380E0.o,ov_SC04_003_o0c.o,tail6.data.o,ov_SC04_003_jr_8013F350.o,tail7.data.o,ov_SC04_003_jr_8013FFD8.o,tail8.data.o,ov_SC04_003_jr_80140608.o,tail9.data.o,ov_SC04_003_jr_8015444C.o,ov_SC04_003_jr_80154C24.o,ov_SC04_003_jr_801588CC.o,ov_SC04_003_jr_80159C84.o,tail10.data.o,ov_SC04_003_jr_8015A3C8.o,tail11.data.o,ov_SC04_003_jr_8015AE2C.o,tail12.data.o,ov_SC04_003_jr_8015C32C.o,tail13.data.o,ov_SC04_003_jr_8016AB6C.o,tail14.data.o,ov_SC04_003_jr_80171B4C.o,ov_SC04_003_jr_801734BC.o,tail15.data.o,ov_SC04_003_jr_801789AC.o,ov_SC04_003_jr_80178D40.o,tail16.data.o,ov_SC04_003_jr_8017A4AC.o,tail17.data.o,ov_SC04_003_jr_8017AE2C.o,ov_SC04_003_jr_8017BEBC.o,tail18.data.o,trailing.o  # Phase-26 §8 jtbl-rodata carve
build/src/ov_SC04_003/ov_SC04_003.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14
build/src/ov_SC04_003/ov_SC04_003_jr_8012ACE0.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0xcc,+0xe0
build/src/ov_SC04_003/ov_SC04_003_jr_80135D20.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC04_003/ov_SC04_003_jr_8013F350.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC04_003/ov_SC04_003_jr_8013FFD8.o: JTBL_PADS := 0,0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38,+0x58
build/src/ov_SC04_003/ov_SC04_003_jr_8015444C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x70
build/src/ov_SC04_003/ov_SC04_003_jr_80154C24.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x24
build/src/ov_SC04_003/ov_SC04_003_jr_801588CC.o: JTBL_PADS := 0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x28,+0x48
build/src/ov_SC04_003/ov_SC04_003_jr_80159C84.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC04_003/ov_SC04_003_jr_8015AE2C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC04_003/ov_SC04_003_jr_8016AB6C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC04_003/ov_SC04_003_jr_80178D40.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x178
build/src/ov_SC04_003/ov_SC04_003_o0c.o: JTBL_PADS := 0,4,4,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x38,+0xa8,+0x118
ov_SC04_003_CHECK_SHA  := config/check.ov_SC04_003.sha
ov_SC04_003_SYMBOLS    := config/symbols.ov_SC04_003.txt
ov_SC04_003_SIG        := .run/sig.ov_SC04_003.jsonl
ov_SC04_003_GHIDRA_PROG := ov_SC04_003
ov_SC04_003_VRAM_BASE  := 0x80128158
ov_SC04_003_TEXT_LO    := 0x80128158
ov_SC04_003_TEXT_HI    := 0x8019BBEF
ov_SC04_003_ASM_DIR     := asm/ov_SC04_003
ov_SC04_003_SRC_DIR     := src/ov_SC04_003
ov_SC04_003_UNDEF_SYMS  := build/ov_SC04_003/undefined_syms_auto.txt
ov_SC04_003_UNDEF_FUNCS := build/ov_SC04_003/undefined_funcs_auto.txt

# --- ov_SC04_004 (location overlay SC04/FILE_004, vram 0x80128158 — onboarded by new_overlay.sh) ---
ov_SC04_004_EXE        := extracted/retail/SC04.CD.dir/FILE_004.dir/0.4.dec
ov_SC04_004_NAME       := ov_SC04_004
ov_SC04_004_OUT_DIR    := build/ov_SC04_004
ov_SC04_004_OUT        := $(ov_SC04_004_OUT_DIR)/$(ov_SC04_004_NAME)
ov_SC04_004_ELF        := $(ov_SC04_004_OUT).elf
ov_SC04_004_MAPFILE    := $(ov_SC04_004_OUT).map
ov_SC04_004_LD_SCRIPT  := $(ov_SC04_004_OUT).ld
ov_SC04_004_SPLAT_YAML := config/splat.ov_SC04_004.yaml
ov_SC04_004_JTBL_INTERLEAVE := --order tail.data.o,ov_SC04_004.o,ov_SC04_004_jr_8012ACE0.o,tail2.data.o,ov_SC04_004_jr_80135888.o,tail3.data.o,ov_SC04_004_jr_80135A4C.o,tail4.data.o,ov_SC04_004_jr_80135D20.o,tail5.data.o,ov_SC04_004_jr_801380E0.o,ov_SC04_004_o0c.o,tail6.data.o,ov_SC04_004_jr_8013F350.o,tail7.data.o,ov_SC04_004_jr_8013FFD8.o,tail8.data.o,ov_SC04_004_jr_80140608.o,tail9.data.o,ov_SC04_004_jr_8015444C.o,ov_SC04_004_jr_80154C24.o,ov_SC04_004_jr_801588CC.o,ov_SC04_004_jr_80159C84.o,tail10.data.o,ov_SC04_004_jr_8015A3C8.o,tail11.data.o,ov_SC04_004_jr_8015AE2C.o,tail12.data.o,ov_SC04_004_jr_8015C32C.o,tail13.data.o,ov_SC04_004_jr_8016AB6C.o,tail14.data.o,ov_SC04_004_jr_80171B4C.o,ov_SC04_004_jr_801734BC.o,tail15.data.o,ov_SC04_004_jr_801789AC.o,ov_SC04_004_jr_80178D40.o,tail16.data.o,ov_SC04_004_jr_8017A4AC.o,tail17.data.o,ov_SC04_004_jr_8017AE2C.o,tail18.data.o,trailing.o  # Phase-26 §8 jtbl-rodata carve
build/src/ov_SC04_004/ov_SC04_004.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14
build/src/ov_SC04_004/ov_SC04_004_jr_8012ACE0.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0xcc,+0xe0
build/src/ov_SC04_004/ov_SC04_004_jr_80135D20.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC04_004/ov_SC04_004_jr_8013F350.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC04_004/ov_SC04_004_jr_8013FFD8.o: JTBL_PADS := 0,0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38,+0x58
build/src/ov_SC04_004/ov_SC04_004_jr_8015444C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x70
build/src/ov_SC04_004/ov_SC04_004_jr_80154C24.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x24
build/src/ov_SC04_004/ov_SC04_004_jr_801588CC.o: JTBL_PADS := 0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x28,+0x48
build/src/ov_SC04_004/ov_SC04_004_jr_80159C84.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC04_004/ov_SC04_004_jr_8015AE2C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC04_004/ov_SC04_004_jr_8016AB6C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC04_004/ov_SC04_004_jr_80178D40.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x178
build/src/ov_SC04_004/ov_SC04_004_jr_8017AE2C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14
build/src/ov_SC04_004/ov_SC04_004_o0c.o: JTBL_PADS := 0,4,4,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x38,+0xa8,+0x118
ov_SC04_004_CHECK_SHA  := config/check.ov_SC04_004.sha
ov_SC04_004_SYMBOLS    := config/symbols.ov_SC04_004.txt
ov_SC04_004_SIG        := .run/sig.ov_SC04_004.jsonl
ov_SC04_004_GHIDRA_PROG := ov_SC04_004
ov_SC04_004_VRAM_BASE  := 0x80128158
ov_SC04_004_TEXT_LO    := 0x80128158
ov_SC04_004_TEXT_HI    := 0x801B3C57
ov_SC04_004_ASM_DIR     := asm/ov_SC04_004
ov_SC04_004_SRC_DIR     := src/ov_SC04_004
ov_SC04_004_UNDEF_SYMS  := build/ov_SC04_004/undefined_syms_auto.txt
ov_SC04_004_UNDEF_FUNCS := build/ov_SC04_004/undefined_funcs_auto.txt

# --- ov_SC04_005 (location overlay SC04/FILE_005, vram 0x80128158 — onboarded by new_overlay.sh) ---
ov_SC04_005_EXE        := extracted/retail/SC04.CD.dir/FILE_005.dir/0.4.dec
ov_SC04_005_NAME       := ov_SC04_005
ov_SC04_005_OUT_DIR    := build/ov_SC04_005
ov_SC04_005_OUT        := $(ov_SC04_005_OUT_DIR)/$(ov_SC04_005_NAME)
ov_SC04_005_ELF        := $(ov_SC04_005_OUT).elf
ov_SC04_005_MAPFILE    := $(ov_SC04_005_OUT).map
ov_SC04_005_LD_SCRIPT  := $(ov_SC04_005_OUT).ld
ov_SC04_005_SPLAT_YAML := config/splat.ov_SC04_005.yaml
ov_SC04_005_JTBL_INTERLEAVE := --order tail.data.o,ov_SC04_005.o,ov_SC04_005_jr_8012ACE0.o,tail2.data.o,ov_SC04_005_jr_80135888.o,tail3.data.o,ov_SC04_005_jr_80135A4C.o,tail4.data.o,ov_SC04_005_jr_80135D20.o,tail5.data.o,ov_SC04_005_jr_801380E0.o,ov_SC04_005_o0c.o,tail6.data.o,ov_SC04_005_jr_8013F350.o,tail7.data.o,ov_SC04_005_jr_8013FFD8.o,tail8.data.o,ov_SC04_005_jr_80140608.o,tail9.data.o,ov_SC04_005_jr_8015444C.o,ov_SC04_005_jr_80154C24.o,ov_SC04_005_jr_801588CC.o,ov_SC04_005_jr_80159C84.o,tail10.data.o,ov_SC04_005_jr_8015A3C8.o,tail11.data.o,ov_SC04_005_jr_8015AE2C.o,tail12.data.o,ov_SC04_005_jr_8015C32C.o,tail13.data.o,ov_SC04_005_jr_8016AB6C.o,tail14.data.o,ov_SC04_005_jr_80171B4C.o,ov_SC04_005_jr_801734BC.o,tail15.data.o,ov_SC04_005_jr_801789AC.o,ov_SC04_005_jr_80178D40.o,tail16.data.o,ov_SC04_005_jr_8017A4AC.o,tail17.data.o,ov_SC04_005_jr_8017AE2C.o,ov_SC04_005_jr_8017BEBC.o,tail18.data.o,trailing.o  # Phase-26 §8 jtbl-rodata carve
build/src/ov_SC04_005/ov_SC04_005.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14
build/src/ov_SC04_005/ov_SC04_005_jr_8012ACE0.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0xcc,+0xe0
build/src/ov_SC04_005/ov_SC04_005_jr_80135D20.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC04_005/ov_SC04_005_jr_8013F350.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC04_005/ov_SC04_005_jr_8013FFD8.o: JTBL_PADS := 0,0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38,+0x58
build/src/ov_SC04_005/ov_SC04_005_jr_8015444C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x70
build/src/ov_SC04_005/ov_SC04_005_jr_80154C24.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x24
build/src/ov_SC04_005/ov_SC04_005_jr_801588CC.o: JTBL_PADS := 0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x28,+0x48
build/src/ov_SC04_005/ov_SC04_005_jr_80159C84.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC04_005/ov_SC04_005_jr_8015AE2C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC04_005/ov_SC04_005_jr_8016AB6C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC04_005/ov_SC04_005_jr_80178D40.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x178
build/src/ov_SC04_005/ov_SC04_005_jr_8017BEBC.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC04_005/ov_SC04_005_o0c.o: JTBL_PADS := 0,4,4,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x38,+0xa8,+0x118
ov_SC04_005_CHECK_SHA  := config/check.ov_SC04_005.sha
ov_SC04_005_SYMBOLS    := config/symbols.ov_SC04_005.txt
ov_SC04_005_SIG        := .run/sig.ov_SC04_005.jsonl
ov_SC04_005_GHIDRA_PROG := ov_SC04_005
ov_SC04_005_VRAM_BASE  := 0x80128158
ov_SC04_005_TEXT_LO    := 0x80128158
ov_SC04_005_TEXT_HI    := 0x801C232F
ov_SC04_005_ASM_DIR     := asm/ov_SC04_005
ov_SC04_005_SRC_DIR     := src/ov_SC04_005
ov_SC04_005_UNDEF_SYMS  := build/ov_SC04_005/undefined_syms_auto.txt
ov_SC04_005_UNDEF_FUNCS := build/ov_SC04_005/undefined_funcs_auto.txt

# --- ov_SC04_006 (location overlay SC04/FILE_006, vram 0x80128158 — onboarded by new_overlay.sh) ---
ov_SC04_006_EXE        := extracted/retail/SC04.CD.dir/FILE_006.dir/0.4.dec
ov_SC04_006_NAME       := ov_SC04_006
ov_SC04_006_OUT_DIR    := build/ov_SC04_006
ov_SC04_006_OUT        := $(ov_SC04_006_OUT_DIR)/$(ov_SC04_006_NAME)
ov_SC04_006_ELF        := $(ov_SC04_006_OUT).elf
ov_SC04_006_MAPFILE    := $(ov_SC04_006_OUT).map
ov_SC04_006_LD_SCRIPT  := $(ov_SC04_006_OUT).ld
ov_SC04_006_SPLAT_YAML := config/splat.ov_SC04_006.yaml
ov_SC04_006_JTBL_INTERLEAVE := --order tail.data.o,ov_SC04_006.o,ov_SC04_006_jr_8012ACE0.o,tail2.data.o,ov_SC04_006_jr_80135888.o,tail3.data.o,ov_SC04_006_jr_80135A4C.o,tail4.data.o,ov_SC04_006_jr_80135D20.o,tail5.data.o,ov_SC04_006_jr_801380E0.o,ov_SC04_006_o0c.o,tail6.data.o,ov_SC04_006_jr_8013F350.o,tail7.data.o,ov_SC04_006_jr_8013FFD8.o,tail8.data.o,ov_SC04_006_jr_80140608.o,tail9.data.o,ov_SC04_006_jr_8015444C.o,ov_SC04_006_jr_80154C24.o,ov_SC04_006_jr_801588CC.o,ov_SC04_006_jr_80159C84.o,tail10.data.o,ov_SC04_006_jr_8015A3C8.o,tail11.data.o,ov_SC04_006_jr_8015AE2C.o,tail12.data.o,ov_SC04_006_jr_8015C32C.o,tail13.data.o,ov_SC04_006_jr_8016AB6C.o,tail14.data.o,ov_SC04_006_jr_80171B4C.o,ov_SC04_006_jr_801734BC.o,tail15.data.o,ov_SC04_006_jr_801789AC.o,ov_SC04_006_jr_80178D40.o,tail16.data.o,ov_SC04_006_jr_8017A4AC.o,tail17.data.o,ov_SC04_006_jr_8017AE2C.o,ov_SC04_006_jr_8017BEBC.o,tail18.data.o,trailing.o  # Phase-26 §8 jtbl-rodata carve
build/src/ov_SC04_006/ov_SC04_006.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14
build/src/ov_SC04_006/ov_SC04_006_jr_8012ACE0.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0xcc,+0xe0
build/src/ov_SC04_006/ov_SC04_006_jr_80135D20.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC04_006/ov_SC04_006_jr_8013F350.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC04_006/ov_SC04_006_jr_8013FFD8.o: JTBL_PADS := 0,0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38,+0x58
build/src/ov_SC04_006/ov_SC04_006_jr_8015444C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x70
build/src/ov_SC04_006/ov_SC04_006_jr_80154C24.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x24
build/src/ov_SC04_006/ov_SC04_006_jr_801588CC.o: JTBL_PADS := 0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x28,+0x48
build/src/ov_SC04_006/ov_SC04_006_jr_80159C84.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC04_006/ov_SC04_006_jr_8015AE2C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC04_006/ov_SC04_006_jr_8016AB6C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC04_006/ov_SC04_006_jr_80178D40.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x178
build/src/ov_SC04_006/ov_SC04_006_o0c.o: JTBL_PADS := 0,4,4,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x38,+0xa8,+0x118
ov_SC04_006_CHECK_SHA  := config/check.ov_SC04_006.sha
ov_SC04_006_SYMBOLS    := config/symbols.ov_SC04_006.txt
ov_SC04_006_SIG        := .run/sig.ov_SC04_006.jsonl
ov_SC04_006_GHIDRA_PROG := ov_SC04_006
ov_SC04_006_VRAM_BASE  := 0x80128158
ov_SC04_006_TEXT_LO    := 0x80128158
ov_SC04_006_TEXT_HI    := 0x8019DDCF
ov_SC04_006_ASM_DIR     := asm/ov_SC04_006
ov_SC04_006_SRC_DIR     := src/ov_SC04_006
ov_SC04_006_UNDEF_SYMS  := build/ov_SC04_006/undefined_syms_auto.txt
ov_SC04_006_UNDEF_FUNCS := build/ov_SC04_006/undefined_funcs_auto.txt

# --- ov_SC04_007 (location overlay SC04/FILE_007, vram 0x80128158 — onboarded by new_overlay.sh) ---
ov_SC04_007_EXE        := extracted/retail/SC04.CD.dir/FILE_007.dir/0.4.dec
ov_SC04_007_NAME       := ov_SC04_007
ov_SC04_007_OUT_DIR    := build/ov_SC04_007
ov_SC04_007_OUT        := $(ov_SC04_007_OUT_DIR)/$(ov_SC04_007_NAME)
ov_SC04_007_ELF        := $(ov_SC04_007_OUT).elf
ov_SC04_007_MAPFILE    := $(ov_SC04_007_OUT).map
ov_SC04_007_LD_SCRIPT  := $(ov_SC04_007_OUT).ld
ov_SC04_007_SPLAT_YAML := config/splat.ov_SC04_007.yaml
ov_SC04_007_JTBL_INTERLEAVE := --order tail.data.o,ov_SC04_007.o,ov_SC04_007_jr_8012ACE0.o,tail2.data.o,ov_SC04_007_jr_80135888.o,tail3.data.o,ov_SC04_007_jr_80135A4C.o,tail4.data.o,ov_SC04_007_jr_80135D20.o,tail5.data.o,ov_SC04_007_jr_801380E0.o,ov_SC04_007_o0c.o,tail6.data.o,ov_SC04_007_jr_8013F350.o,tail7.data.o,ov_SC04_007_jr_8013FFD8.o,tail8.data.o,ov_SC04_007_jr_80140608.o,tail9.data.o,ov_SC04_007_jr_8015444C.o,ov_SC04_007_jr_80154C24.o,ov_SC04_007_jr_801588CC.o,ov_SC04_007_jr_80159C84.o,tail10.data.o,ov_SC04_007_jr_8015A3C8.o,tail11.data.o,ov_SC04_007_jr_8015AE2C.o,tail12.data.o,ov_SC04_007_jr_8015C32C.o,tail13.data.o,ov_SC04_007_jr_8016AB6C.o,tail14.data.o,ov_SC04_007_jr_80171B4C.o,ov_SC04_007_jr_801734BC.o,tail15.data.o,ov_SC04_007_jr_801789AC.o,ov_SC04_007_jr_80178D40.o,tail16.data.o,ov_SC04_007_jr_8017A4AC.o,tail17.data.o,ov_SC04_007_jr_8017AE2C.o,ov_SC04_007_jr_8017BEBC.o,tail18.data.o,trailing.o  # Phase-26 §8 jtbl-rodata carve
build/src/ov_SC04_007/ov_SC04_007.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14
build/src/ov_SC04_007/ov_SC04_007_jr_8012ACE0.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0xcc,+0xe0
build/src/ov_SC04_007/ov_SC04_007_jr_80135D20.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC04_007/ov_SC04_007_jr_8013F350.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC04_007/ov_SC04_007_jr_8013FFD8.o: JTBL_PADS := 0,0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38,+0x58
build/src/ov_SC04_007/ov_SC04_007_jr_8015444C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x70
build/src/ov_SC04_007/ov_SC04_007_jr_80154C24.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x24
build/src/ov_SC04_007/ov_SC04_007_jr_801588CC.o: JTBL_PADS := 0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x28,+0x48
build/src/ov_SC04_007/ov_SC04_007_jr_80159C84.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC04_007/ov_SC04_007_jr_8015AE2C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC04_007/ov_SC04_007_jr_8016AB6C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC04_007/ov_SC04_007_jr_80178D40.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x178
build/src/ov_SC04_007/ov_SC04_007_jr_8017BEBC.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC04_007/ov_SC04_007_o0c.o: JTBL_PADS := 0,4,4,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x38,+0xa8,+0x118
ov_SC04_007_CHECK_SHA  := config/check.ov_SC04_007.sha
ov_SC04_007_SYMBOLS    := config/symbols.ov_SC04_007.txt
ov_SC04_007_SIG        := .run/sig.ov_SC04_007.jsonl
ov_SC04_007_GHIDRA_PROG := ov_SC04_007
ov_SC04_007_VRAM_BASE  := 0x80128158
ov_SC04_007_TEXT_LO    := 0x80128158
ov_SC04_007_TEXT_HI    := 0x801B5B8F
ov_SC04_007_ASM_DIR     := asm/ov_SC04_007
ov_SC04_007_SRC_DIR     := src/ov_SC04_007
ov_SC04_007_UNDEF_SYMS  := build/ov_SC04_007/undefined_syms_auto.txt
ov_SC04_007_UNDEF_FUNCS := build/ov_SC04_007/undefined_funcs_auto.txt

# --- ov_SC04_008 (location overlay SC04/FILE_008, vram 0x80128158 — onboarded by new_overlay.sh) ---
ov_SC04_008_EXE        := extracted/retail/SC04.CD.dir/FILE_008.dir/0.4.dec
ov_SC04_008_NAME       := ov_SC04_008
ov_SC04_008_OUT_DIR    := build/ov_SC04_008
ov_SC04_008_OUT        := $(ov_SC04_008_OUT_DIR)/$(ov_SC04_008_NAME)
ov_SC04_008_ELF        := $(ov_SC04_008_OUT).elf
ov_SC04_008_MAPFILE    := $(ov_SC04_008_OUT).map
ov_SC04_008_LD_SCRIPT  := $(ov_SC04_008_OUT).ld
ov_SC04_008_SPLAT_YAML := config/splat.ov_SC04_008.yaml
ov_SC04_008_JTBL_INTERLEAVE := --order tail.data.o,ov_SC04_008.o,ov_SC04_008_jr_8012ACE0.o,tail2.data.o,ov_SC04_008_jr_80135888.o,tail3.data.o,ov_SC04_008_jr_80135A4C.o,tail4.data.o,ov_SC04_008_jr_80135D20.o,tail5.data.o,ov_SC04_008_jr_801380E0.o,ov_SC04_008_o0c.o,tail6.data.o,ov_SC04_008_jr_8013F350.o,tail7.data.o,ov_SC04_008_jr_8013FFD8.o,tail8.data.o,ov_SC04_008_jr_80140608.o,tail9.data.o,ov_SC04_008_jr_8015444C.o,ov_SC04_008_jr_80154C24.o,ov_SC04_008_jr_801588CC.o,ov_SC04_008_jr_80159C84.o,tail10.data.o,ov_SC04_008_jr_8015AE2C.o,tail11.data.o,ov_SC04_008_jr_8015C32C.o,tail12.data.o,ov_SC04_008_jr_8016AB6C.o,tail13.data.o,ov_SC04_008_jr_80171B4C.o,ov_SC04_008_jr_801734BC.o,tail14.data.o,ov_SC04_008_jr_801789AC.o,ov_SC04_008_jr_80178D40.o,tail15.data.o,ov_SC04_008_jr_8017A4AC.o,tail16.data.o,ov_SC04_008_jr_8017AE2C.o,tail17.data.o,trailing.o  # Phase-26 §8 jtbl-rodata carve
build/src/ov_SC04_008/ov_SC04_008.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14
build/src/ov_SC04_008/ov_SC04_008_jr_8012ACE0.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0xcc,+0xe0
build/src/ov_SC04_008/ov_SC04_008_jr_80135D20.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC04_008/ov_SC04_008_jr_8013F350.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC04_008/ov_SC04_008_jr_8013FFD8.o: JTBL_PADS := 0,0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38,+0x58
build/src/ov_SC04_008/ov_SC04_008_jr_8015444C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x70
build/src/ov_SC04_008/ov_SC04_008_jr_80154C24.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x24
build/src/ov_SC04_008/ov_SC04_008_jr_801588CC.o: JTBL_PADS := 0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x28,+0x48
build/src/ov_SC04_008/ov_SC04_008_jr_80159C84.o: JTBL_PADS := 0,4,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38
build/src/ov_SC04_008/ov_SC04_008_jr_8015AE2C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC04_008/ov_SC04_008_jr_8016AB6C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC04_008/ov_SC04_008_jr_80178D40.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x178
build/src/ov_SC04_008/ov_SC04_008_jr_8017AE2C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14
build/src/ov_SC04_008/ov_SC04_008_o0c.o: JTBL_PADS := 0,4,4,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x38,+0xa8,+0x118
ov_SC04_008_CHECK_SHA  := config/check.ov_SC04_008.sha
ov_SC04_008_SYMBOLS    := config/symbols.ov_SC04_008.txt
ov_SC04_008_SIG        := .run/sig.ov_SC04_008.jsonl
ov_SC04_008_GHIDRA_PROG := ov_SC04_008
ov_SC04_008_VRAM_BASE  := 0x80128158
ov_SC04_008_TEXT_LO    := 0x80128158
ov_SC04_008_TEXT_HI    := 0x801934BF
ov_SC04_008_ASM_DIR     := asm/ov_SC04_008
ov_SC04_008_SRC_DIR     := src/ov_SC04_008
ov_SC04_008_UNDEF_SYMS  := build/ov_SC04_008/undefined_syms_auto.txt
ov_SC04_008_UNDEF_FUNCS := build/ov_SC04_008/undefined_funcs_auto.txt

# --- ov_SC04_009 (location overlay SC04/FILE_009, vram 0x80128158 — onboarded by new_overlay.sh) ---
ov_SC04_009_EXE        := extracted/retail/SC04.CD.dir/FILE_009.dir/0.4.dec
ov_SC04_009_NAME       := ov_SC04_009
ov_SC04_009_OUT_DIR    := build/ov_SC04_009
ov_SC04_009_OUT        := $(ov_SC04_009_OUT_DIR)/$(ov_SC04_009_NAME)
ov_SC04_009_ELF        := $(ov_SC04_009_OUT).elf
ov_SC04_009_MAPFILE    := $(ov_SC04_009_OUT).map
ov_SC04_009_LD_SCRIPT  := $(ov_SC04_009_OUT).ld
ov_SC04_009_SPLAT_YAML := config/splat.ov_SC04_009.yaml
ov_SC04_009_JTBL_INTERLEAVE := --order tail.data.o,ov_SC04_009.o,ov_SC04_009_jr_8012ACE0.o,tail2.data.o,ov_SC04_009_jr_80135888.o,tail3.data.o,ov_SC04_009_jr_80135A4C.o,tail4.data.o,ov_SC04_009_jr_80135D20.o,tail5.data.o,ov_SC04_009_jr_801380E0.o,ov_SC04_009_o0c.o,tail6.data.o,ov_SC04_009_jr_8013F350.o,tail7.data.o,ov_SC04_009_jr_8013FFD8.o,tail8.data.o,ov_SC04_009_jr_80140608.o,tail9.data.o,ov_SC04_009_jr_8015444C.o,ov_SC04_009_jr_80154C24.o,ov_SC04_009_jr_801588CC.o,ov_SC04_009_jr_80159C84.o,tail10.data.o,ov_SC04_009_jr_8015A3C8.o,tail11.data.o,ov_SC04_009_jr_8015AE2C.o,tail12.data.o,ov_SC04_009_jr_8015C32C.o,tail13.data.o,ov_SC04_009_jr_8016AB6C.o,tail14.data.o,ov_SC04_009_jr_80171B4C.o,ov_SC04_009_jr_801734BC.o,tail15.data.o,ov_SC04_009_jr_801789AC.o,ov_SC04_009_jr_80178D40.o,tail16.data.o,ov_SC04_009_jr_8017A4AC.o,tail17.data.o,ov_SC04_009_jr_8017AE2C.o,ov_SC04_009_jr_8017BEBC.o,tail18.data.o,trailing.o  # Phase-26 §8 jtbl-rodata carve
build/src/ov_SC04_009/ov_SC04_009.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14
build/src/ov_SC04_009/ov_SC04_009_jr_8012ACE0.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0xcc,+0xe0
build/src/ov_SC04_009/ov_SC04_009_jr_80135D20.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC04_009/ov_SC04_009_jr_8013F350.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC04_009/ov_SC04_009_jr_8013FFD8.o: JTBL_PADS := 0,0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38,+0x58
build/src/ov_SC04_009/ov_SC04_009_jr_8015444C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x70
build/src/ov_SC04_009/ov_SC04_009_jr_80154C24.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x24
build/src/ov_SC04_009/ov_SC04_009_jr_801588CC.o: JTBL_PADS := 0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x28,+0x48
build/src/ov_SC04_009/ov_SC04_009_jr_80159C84.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC04_009/ov_SC04_009_jr_8015AE2C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC04_009/ov_SC04_009_jr_8016AB6C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC04_009/ov_SC04_009_jr_80178D40.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x178
build/src/ov_SC04_009/ov_SC04_009_o0c.o: JTBL_PADS := 0,4,4,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x38,+0xa8,+0x118
ov_SC04_009_CHECK_SHA  := config/check.ov_SC04_009.sha
ov_SC04_009_SYMBOLS    := config/symbols.ov_SC04_009.txt
ov_SC04_009_SIG        := .run/sig.ov_SC04_009.jsonl
ov_SC04_009_GHIDRA_PROG := ov_SC04_009
ov_SC04_009_VRAM_BASE  := 0x80128158
ov_SC04_009_TEXT_LO    := 0x80128158
ov_SC04_009_TEXT_HI    := 0x8019826F
ov_SC04_009_ASM_DIR     := asm/ov_SC04_009
ov_SC04_009_SRC_DIR     := src/ov_SC04_009
ov_SC04_009_UNDEF_SYMS  := build/ov_SC04_009/undefined_syms_auto.txt
ov_SC04_009_UNDEF_FUNCS := build/ov_SC04_009/undefined_funcs_auto.txt

# --- ov_SC04_010 (location overlay SC04/FILE_010, vram 0x80128158 — onboarded by new_overlay.sh) ---
ov_SC04_010_EXE        := extracted/retail/SC04.CD.dir/FILE_010.dir/0.4.dec
ov_SC04_010_NAME       := ov_SC04_010
ov_SC04_010_OUT_DIR    := build/ov_SC04_010
ov_SC04_010_OUT        := $(ov_SC04_010_OUT_DIR)/$(ov_SC04_010_NAME)
ov_SC04_010_ELF        := $(ov_SC04_010_OUT).elf
ov_SC04_010_MAPFILE    := $(ov_SC04_010_OUT).map
ov_SC04_010_LD_SCRIPT  := $(ov_SC04_010_OUT).ld
ov_SC04_010_SPLAT_YAML := config/splat.ov_SC04_010.yaml
ov_SC04_010_JTBL_INTERLEAVE := --order tail.data.o,ov_SC04_010.o,ov_SC04_010_jr_8012ACE0.o,tail2.data.o,ov_SC04_010_jr_80135888.o,tail3.data.o,ov_SC04_010_jr_80135A4C.o,tail4.data.o,ov_SC04_010_jr_80135D20.o,tail5.data.o,ov_SC04_010_jr_801380E0.o,ov_SC04_010_o0c.o,tail6.data.o,ov_SC04_010_jr_8013F350.o,tail7.data.o,ov_SC04_010_jr_8013FFD8.o,tail8.data.o,ov_SC04_010_jr_80140608.o,tail9.data.o,ov_SC04_010_jr_8015444C.o,ov_SC04_010_jr_80154C24.o,ov_SC04_010_jr_801588CC.o,ov_SC04_010_jr_80159C84.o,tail10.data.o,ov_SC04_010_jr_8015A3C8.o,tail11.data.o,ov_SC04_010_jr_8015AE2C.o,tail12.data.o,ov_SC04_010_jr_8015C32C.o,tail13.data.o,ov_SC04_010_jr_8016AB6C.o,tail14.data.o,ov_SC04_010_jr_80171B4C.o,ov_SC04_010_jr_801734BC.o,tail15.data.o,ov_SC04_010_jr_801789AC.o,ov_SC04_010_jr_80178D40.o,tail16.data.o,ov_SC04_010_jr_8017A4AC.o,tail17.data.o,ov_SC04_010_jr_8017AE2C.o,ov_SC04_010_jr_8017BEBC.o,tail18.data.o,trailing.o  # Phase-26 §8 jtbl-rodata carve
build/src/ov_SC04_010/ov_SC04_010.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14
build/src/ov_SC04_010/ov_SC04_010_jr_8012ACE0.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0xcc,+0xe0
build/src/ov_SC04_010/ov_SC04_010_jr_80135D20.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC04_010/ov_SC04_010_jr_8013F350.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC04_010/ov_SC04_010_jr_8013FFD8.o: JTBL_PADS := 0,0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38,+0x58
build/src/ov_SC04_010/ov_SC04_010_jr_8015444C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x70
build/src/ov_SC04_010/ov_SC04_010_jr_80154C24.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x24
build/src/ov_SC04_010/ov_SC04_010_jr_801588CC.o: JTBL_PADS := 0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x28,+0x48
build/src/ov_SC04_010/ov_SC04_010_jr_80159C84.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC04_010/ov_SC04_010_jr_8015AE2C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC04_010/ov_SC04_010_jr_8016AB6C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC04_010/ov_SC04_010_jr_80178D40.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x178
build/src/ov_SC04_010/ov_SC04_010_o0c.o: JTBL_PADS := 0,4,4,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x38,+0xa8,+0x118
ov_SC04_010_CHECK_SHA  := config/check.ov_SC04_010.sha
ov_SC04_010_SYMBOLS    := config/symbols.ov_SC04_010.txt
ov_SC04_010_SIG        := .run/sig.ov_SC04_010.jsonl
ov_SC04_010_GHIDRA_PROG := ov_SC04_010
ov_SC04_010_VRAM_BASE  := 0x80128158
ov_SC04_010_TEXT_LO    := 0x80128158
ov_SC04_010_TEXT_HI    := 0x8018F747
ov_SC04_010_ASM_DIR     := asm/ov_SC04_010
ov_SC04_010_SRC_DIR     := src/ov_SC04_010
ov_SC04_010_UNDEF_SYMS  := build/ov_SC04_010/undefined_syms_auto.txt
ov_SC04_010_UNDEF_FUNCS := build/ov_SC04_010/undefined_funcs_auto.txt

# --- ov_SC04_011 (location overlay SC04/FILE_011, vram 0x80128158 — onboarded by new_overlay.sh) ---
ov_SC04_011_EXE        := extracted/retail/SC04.CD.dir/FILE_011.dir/0.4.dec
ov_SC04_011_NAME       := ov_SC04_011
ov_SC04_011_OUT_DIR    := build/ov_SC04_011
ov_SC04_011_OUT        := $(ov_SC04_011_OUT_DIR)/$(ov_SC04_011_NAME)
ov_SC04_011_ELF        := $(ov_SC04_011_OUT).elf
ov_SC04_011_MAPFILE    := $(ov_SC04_011_OUT).map
ov_SC04_011_LD_SCRIPT  := $(ov_SC04_011_OUT).ld
ov_SC04_011_SPLAT_YAML := config/splat.ov_SC04_011.yaml
ov_SC04_011_JTBL_INTERLEAVE := --order tail.data.o,ov_SC04_011.o,ov_SC04_011_jr_8012ACE0.o,tail2.data.o,ov_SC04_011_jr_80135888.o,tail3.data.o,ov_SC04_011_jr_80135A4C.o,tail4.data.o,ov_SC04_011_jr_80135D20.o,tail5.data.o,ov_SC04_011_jr_801380E0.o,ov_SC04_011_o0c.o,tail6.data.o,ov_SC04_011_jr_8013F350.o,tail7.data.o,ov_SC04_011_jr_8013FFD8.o,tail8.data.o,ov_SC04_011_jr_80140608.o,tail9.data.o,ov_SC04_011_jr_8015444C.o,ov_SC04_011_jr_80154C24.o,ov_SC04_011_jr_801588CC.o,ov_SC04_011_jr_80159C84.o,tail10.data.o,ov_SC04_011_jr_8015A3C8.o,tail11.data.o,ov_SC04_011_jr_8015AE2C.o,tail12.data.o,ov_SC04_011_jr_8015C32C.o,tail13.data.o,ov_SC04_011_jr_8016AB6C.o,tail14.data.o,ov_SC04_011_jr_80171B4C.o,ov_SC04_011_jr_801734BC.o,tail15.data.o,ov_SC04_011_jr_801789AC.o,ov_SC04_011_jr_80178D40.o,tail16.data.o,ov_SC04_011_jr_8017A4AC.o,tail17.data.o,ov_SC04_011_jr_8017AE2C.o,tail18.data.o,ov_SC04_011_jr_8017D494.o,tail19.data.o,trailing.o  # Phase-26 §8 jtbl-rodata carve
build/src/ov_SC04_011/ov_SC04_011.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14
build/src/ov_SC04_011/ov_SC04_011_jr_8012ACE0.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0xcc,+0xe0
build/src/ov_SC04_011/ov_SC04_011_jr_80135D20.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC04_011/ov_SC04_011_jr_8013F350.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC04_011/ov_SC04_011_jr_8013FFD8.o: JTBL_PADS := 0,0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38,+0x58
build/src/ov_SC04_011/ov_SC04_011_jr_8015444C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x70
build/src/ov_SC04_011/ov_SC04_011_jr_80154C24.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x24
build/src/ov_SC04_011/ov_SC04_011_jr_801588CC.o: JTBL_PADS := 0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x28,+0x48
build/src/ov_SC04_011/ov_SC04_011_jr_80159C84.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC04_011/ov_SC04_011_jr_8015AE2C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC04_011/ov_SC04_011_jr_8016AB6C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC04_011/ov_SC04_011_jr_80178D40.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x178
build/src/ov_SC04_011/ov_SC04_011_jr_8017D494.o: JTBL_PADS := 0,0,4,4,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x40,+0x58,+0x70
build/src/ov_SC04_011/ov_SC04_011_o0c.o: JTBL_PADS := 0,4,4,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x38,+0xa8,+0x118
ov_SC04_011_CHECK_SHA  := config/check.ov_SC04_011.sha
ov_SC04_011_SYMBOLS    := config/symbols.ov_SC04_011.txt
ov_SC04_011_SIG        := .run/sig.ov_SC04_011.jsonl
ov_SC04_011_GHIDRA_PROG := ov_SC04_011
ov_SC04_011_VRAM_BASE  := 0x80128158
ov_SC04_011_TEXT_LO    := 0x80128158
ov_SC04_011_TEXT_HI    := 0x801F16AF
ov_SC04_011_ASM_DIR     := asm/ov_SC04_011
ov_SC04_011_SRC_DIR     := src/ov_SC04_011
ov_SC04_011_UNDEF_SYMS  := build/ov_SC04_011/undefined_syms_auto.txt
ov_SC04_011_UNDEF_FUNCS := build/ov_SC04_011/undefined_funcs_auto.txt

# --- ov_SC04_012 (location overlay SC04/FILE_012, vram 0x80128158 — onboarded by new_overlay.sh) ---
ov_SC04_012_EXE        := extracted/retail/SC04.CD.dir/FILE_012.dir/0.4.dec
ov_SC04_012_NAME       := ov_SC04_012
ov_SC04_012_OUT_DIR    := build/ov_SC04_012
ov_SC04_012_OUT        := $(ov_SC04_012_OUT_DIR)/$(ov_SC04_012_NAME)
ov_SC04_012_ELF        := $(ov_SC04_012_OUT).elf
ov_SC04_012_MAPFILE    := $(ov_SC04_012_OUT).map
ov_SC04_012_LD_SCRIPT  := $(ov_SC04_012_OUT).ld
ov_SC04_012_SPLAT_YAML := config/splat.ov_SC04_012.yaml
ov_SC04_012_JTBL_INTERLEAVE := --order tail.data.o,ov_SC04_012.o,ov_SC04_012_jr_8012ACE0.o,tail2.data.o,ov_SC04_012_jr_80135888.o,tail3.data.o,ov_SC04_012_jr_80135A4C.o,tail4.data.o,ov_SC04_012_jr_80135D20.o,tail5.data.o,ov_SC04_012_jr_801380E0.o,ov_SC04_012_o0c.o,tail6.data.o,ov_SC04_012_jr_8013F350.o,tail7.data.o,ov_SC04_012_jr_8013FFD8.o,tail8.data.o,ov_SC04_012_jr_80140608.o,tail9.data.o,ov_SC04_012_jr_8015444C.o,ov_SC04_012_jr_80154C24.o,ov_SC04_012_jr_801588CC.o,ov_SC04_012_jr_80159C84.o,tail10.data.o,ov_SC04_012_jr_8015A3C8.o,tail11.data.o,ov_SC04_012_jr_8015AE2C.o,tail12.data.o,ov_SC04_012_jr_8015C32C.o,tail13.data.o,ov_SC04_012_jr_8016AB6C.o,tail14.data.o,ov_SC04_012_jr_80171B4C.o,ov_SC04_012_jr_801734BC.o,tail15.data.o,ov_SC04_012_jr_801789AC.o,ov_SC04_012_jr_80178D40.o,tail16.data.o,ov_SC04_012_jr_8017A4AC.o,tail17.data.o,ov_SC04_012_jr_8017AE2C.o,tail18.data.o,trailing.o  # Phase-26 §8 jtbl-rodata carve
build/src/ov_SC04_012/ov_SC04_012.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14
build/src/ov_SC04_012/ov_SC04_012_jr_8012ACE0.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0xcc,+0xe0
build/src/ov_SC04_012/ov_SC04_012_jr_80135D20.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC04_012/ov_SC04_012_jr_8013F350.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC04_012/ov_SC04_012_jr_8013FFD8.o: JTBL_PADS := 0,0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38,+0x58
build/src/ov_SC04_012/ov_SC04_012_jr_8015444C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x70
build/src/ov_SC04_012/ov_SC04_012_jr_80154C24.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x24
build/src/ov_SC04_012/ov_SC04_012_jr_801588CC.o: JTBL_PADS := 0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x28,+0x48
build/src/ov_SC04_012/ov_SC04_012_jr_80159C84.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC04_012/ov_SC04_012_jr_8015AE2C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC04_012/ov_SC04_012_jr_8016AB6C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC04_012/ov_SC04_012_jr_80178D40.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x178
build/src/ov_SC04_012/ov_SC04_012_jr_8017AE2C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14
build/src/ov_SC04_012/ov_SC04_012_o0c.o: JTBL_PADS := 0,4,4,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x38,+0xa8,+0x118
ov_SC04_012_CHECK_SHA  := config/check.ov_SC04_012.sha
ov_SC04_012_SYMBOLS    := config/symbols.ov_SC04_012.txt
ov_SC04_012_SIG        := .run/sig.ov_SC04_012.jsonl
ov_SC04_012_GHIDRA_PROG := ov_SC04_012
ov_SC04_012_VRAM_BASE  := 0x80128158
ov_SC04_012_TEXT_LO    := 0x80128158
ov_SC04_012_TEXT_HI    := 0x8019323F
ov_SC04_012_ASM_DIR     := asm/ov_SC04_012
ov_SC04_012_SRC_DIR     := src/ov_SC04_012
ov_SC04_012_UNDEF_SYMS  := build/ov_SC04_012/undefined_syms_auto.txt
ov_SC04_012_UNDEF_FUNCS := build/ov_SC04_012/undefined_funcs_auto.txt

# --- ov_SC04_015 (location overlay SC04/FILE_015, vram 0x80128158 — onboarded by new_overlay.sh) ---
ov_SC04_015_EXE        := extracted/retail/SC04.CD.dir/FILE_015.dir/0.4.dec
ov_SC04_015_NAME       := ov_SC04_015
ov_SC04_015_OUT_DIR    := build/ov_SC04_015
ov_SC04_015_OUT        := $(ov_SC04_015_OUT_DIR)/$(ov_SC04_015_NAME)
ov_SC04_015_ELF        := $(ov_SC04_015_OUT).elf
ov_SC04_015_MAPFILE    := $(ov_SC04_015_OUT).map
ov_SC04_015_LD_SCRIPT  := $(ov_SC04_015_OUT).ld
ov_SC04_015_SPLAT_YAML := config/splat.ov_SC04_015.yaml
ov_SC04_015_JTBL_INTERLEAVE := --order tail.data.o,ov_SC04_015.o,ov_SC04_015_jr_8012ACE0.o,tail2.data.o,ov_SC04_015_jr_80135888.o,tail3.data.o,ov_SC04_015_jr_80135A4C.o,tail4.data.o,ov_SC04_015_jr_80135D20.o,tail5.data.o,ov_SC04_015_jr_801380E0.o,ov_SC04_015_o0c.o,tail6.data.o,ov_SC04_015_jr_8013F350.o,tail7.data.o,ov_SC04_015_jr_8013FFD8.o,tail8.data.o,ov_SC04_015_jr_80140608.o,tail9.data.o,ov_SC04_015_jr_8015444C.o,ov_SC04_015_jr_80154C24.o,ov_SC04_015_jr_801588CC.o,ov_SC04_015_jr_80159C84.o,tail10.data.o,ov_SC04_015_jr_8015A3C8.o,tail11.data.o,ov_SC04_015_jr_8015AE2C.o,tail12.data.o,ov_SC04_015_jr_8015C32C.o,tail13.data.o,ov_SC04_015_jr_8016AB6C.o,tail14.data.o,ov_SC04_015_jr_80171B4C.o,ov_SC04_015_jr_801734BC.o,tail15.data.o,ov_SC04_015_jr_801789AC.o,ov_SC04_015_jr_80178D40.o,tail16.data.o,ov_SC04_015_jr_8017A4AC.o,tail17.data.o,ov_SC04_015_jr_8017AE2C.o,ov_SC04_015_jr_801820DC.o,tail18.data.o,trailing.o  # Phase-26 §8 jtbl-rodata carve
build/src/ov_SC04_015/ov_SC04_015.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14
build/src/ov_SC04_015/ov_SC04_015_jr_8012ACE0.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0xcc,+0xe0
build/src/ov_SC04_015/ov_SC04_015_jr_80135D20.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC04_015/ov_SC04_015_jr_8013F350.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC04_015/ov_SC04_015_jr_8013FFD8.o: JTBL_PADS := 0,0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38,+0x58
build/src/ov_SC04_015/ov_SC04_015_jr_8015444C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x70
build/src/ov_SC04_015/ov_SC04_015_jr_80154C24.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x24
build/src/ov_SC04_015/ov_SC04_015_jr_801588CC.o: JTBL_PADS := 0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x28,+0x48
build/src/ov_SC04_015/ov_SC04_015_jr_80159C84.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC04_015/ov_SC04_015_jr_8015AE2C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC04_015/ov_SC04_015_jr_8016AB6C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC04_015/ov_SC04_015_jr_80178D40.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x178
build/src/ov_SC04_015/ov_SC04_015_jr_8017AE2C.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14,+0x34
build/src/ov_SC04_015/ov_SC04_015_jr_801820DC.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x1c
build/src/ov_SC04_015/ov_SC04_015_o0c.o: JTBL_PADS := 0,4,4,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x38,+0xa8,+0x118
ov_SC04_015_CHECK_SHA  := config/check.ov_SC04_015.sha
ov_SC04_015_SYMBOLS    := config/symbols.ov_SC04_015.txt
ov_SC04_015_SIG        := .run/sig.ov_SC04_015.jsonl
ov_SC04_015_GHIDRA_PROG := ov_SC04_015
ov_SC04_015_VRAM_BASE  := 0x80128158
ov_SC04_015_TEXT_LO    := 0x80128158
ov_SC04_015_TEXT_HI    := 0x801C93DF
ov_SC04_015_ASM_DIR     := asm/ov_SC04_015
ov_SC04_015_SRC_DIR     := src/ov_SC04_015
ov_SC04_015_UNDEF_SYMS  := build/ov_SC04_015/undefined_syms_auto.txt
ov_SC04_015_UNDEF_FUNCS := build/ov_SC04_015/undefined_funcs_auto.txt

# --- ov_SC04_016 (location overlay SC04/FILE_016, vram 0x80128158 — onboarded by new_overlay.sh) ---
ov_SC04_016_EXE        := extracted/retail/SC04.CD.dir/FILE_016.dir/0.4.dec
ov_SC04_016_NAME       := ov_SC04_016
ov_SC04_016_OUT_DIR    := build/ov_SC04_016
ov_SC04_016_OUT        := $(ov_SC04_016_OUT_DIR)/$(ov_SC04_016_NAME)
ov_SC04_016_ELF        := $(ov_SC04_016_OUT).elf
ov_SC04_016_MAPFILE    := $(ov_SC04_016_OUT).map
ov_SC04_016_LD_SCRIPT  := $(ov_SC04_016_OUT).ld
ov_SC04_016_SPLAT_YAML := config/splat.ov_SC04_016.yaml
ov_SC04_016_JTBL_INTERLEAVE := --order tail.data.o,ov_SC04_016.o,ov_SC04_016_jr_8012ACE0.o,tail2.data.o,ov_SC04_016_jr_80135888.o,tail3.data.o,ov_SC04_016_jr_80135A4C.o,tail4.data.o,ov_SC04_016_jr_80135D20.o,tail5.data.o,ov_SC04_016_jr_801380E0.o,ov_SC04_016_o0c.o,tail6.data.o,ov_SC04_016_jr_8013F350.o,tail7.data.o,ov_SC04_016_jr_8013FFD8.o,tail8.data.o,ov_SC04_016_jr_80140608.o,tail9.data.o,ov_SC04_016_jr_8015444C.o,ov_SC04_016_jr_80154C24.o,ov_SC04_016_jr_801588CC.o,ov_SC04_016_jr_80159C84.o,tail10.data.o,ov_SC04_016_jr_8015A3C8.o,tail11.data.o,ov_SC04_016_jr_8015AE2C.o,tail12.data.o,ov_SC04_016_jr_8015C32C.o,tail13.data.o,ov_SC04_016_jr_8016AB6C.o,tail14.data.o,ov_SC04_016_jr_80171B4C.o,ov_SC04_016_jr_801734BC.o,tail15.data.o,ov_SC04_016_jr_801789AC.o,ov_SC04_016_jr_80178D40.o,tail16.data.o,ov_SC04_016_jr_8017A4AC.o,tail17.data.o,ov_SC04_016_jr_8017AE2C.o,ov_SC04_016_jr_8017BEBC.o,ov_SC04_016_jr_8017F03C.o,tail18.data.o,trailing.o  # Phase-26 §8 jtbl-rodata carve
build/src/ov_SC04_016/ov_SC04_016.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14
build/src/ov_SC04_016/ov_SC04_016_jr_8012ACE0.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0xcc,+0xe0
build/src/ov_SC04_016/ov_SC04_016_jr_80135D20.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC04_016/ov_SC04_016_jr_8013F350.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC04_016/ov_SC04_016_jr_8013FFD8.o: JTBL_PADS := 0,0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38,+0x58
build/src/ov_SC04_016/ov_SC04_016_jr_8015444C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x70
build/src/ov_SC04_016/ov_SC04_016_jr_80154C24.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x24
build/src/ov_SC04_016/ov_SC04_016_jr_801588CC.o: JTBL_PADS := 0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x28,+0x48
build/src/ov_SC04_016/ov_SC04_016_jr_80159C84.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC04_016/ov_SC04_016_jr_8015AE2C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC04_016/ov_SC04_016_jr_8016AB6C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC04_016/ov_SC04_016_jr_80178D40.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x178
build/src/ov_SC04_016/ov_SC04_016_jr_8017BEBC.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC04_016/ov_SC04_016_o0c.o: JTBL_PADS := 0,4,4,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x38,+0xa8,+0x118
ov_SC04_016_CHECK_SHA  := config/check.ov_SC04_016.sha
ov_SC04_016_SYMBOLS    := config/symbols.ov_SC04_016.txt
ov_SC04_016_SIG        := .run/sig.ov_SC04_016.jsonl
ov_SC04_016_GHIDRA_PROG := ov_SC04_016
ov_SC04_016_VRAM_BASE  := 0x80128158
ov_SC04_016_TEXT_LO    := 0x80128158
ov_SC04_016_TEXT_HI    := 0x801AC2DF
ov_SC04_016_ASM_DIR     := asm/ov_SC04_016
ov_SC04_016_SRC_DIR     := src/ov_SC04_016
ov_SC04_016_UNDEF_SYMS  := build/ov_SC04_016/undefined_syms_auto.txt
ov_SC04_016_UNDEF_FUNCS := build/ov_SC04_016/undefined_funcs_auto.txt

# --- ov_SC04_020 (location overlay SC04/FILE_020, vram 0x80128158 — onboarded by new_overlay.sh) ---
ov_SC04_020_EXE        := extracted/retail/SC04.CD.dir/FILE_020.dir/0.4.dec
ov_SC04_020_NAME       := ov_SC04_020
ov_SC04_020_OUT_DIR    := build/ov_SC04_020
ov_SC04_020_OUT        := $(ov_SC04_020_OUT_DIR)/$(ov_SC04_020_NAME)
ov_SC04_020_ELF        := $(ov_SC04_020_OUT).elf
ov_SC04_020_MAPFILE    := $(ov_SC04_020_OUT).map
ov_SC04_020_LD_SCRIPT  := $(ov_SC04_020_OUT).ld
ov_SC04_020_SPLAT_YAML := config/splat.ov_SC04_020.yaml
ov_SC04_020_JTBL_INTERLEAVE := --order tail.data.o,ov_SC04_020.o,ov_SC04_020_jr_8012ACE0.o,tail2.data.o,ov_SC04_020_jr_80135888.o,tail3.data.o,ov_SC04_020_jr_80135A4C.o,tail4.data.o,ov_SC04_020_jr_80135D20.o,tail5.data.o,ov_SC04_020_jr_801380E0.o,ov_SC04_020_o0c.o,tail6.data.o,ov_SC04_020_jr_8013F350.o,tail7.data.o,ov_SC04_020_jr_8013FFD8.o,tail8.data.o,ov_SC04_020_jr_80140608.o,tail9.data.o,ov_SC04_020_jr_8015444C.o,ov_SC04_020_jr_80154C24.o,ov_SC04_020_jr_801588CC.o,ov_SC04_020_jr_80159C84.o,tail10.data.o,ov_SC04_020_jr_8015A3C8.o,tail11.data.o,ov_SC04_020_jr_8015AE2C.o,tail12.data.o,ov_SC04_020_jr_8015C32C.o,tail13.data.o,ov_SC04_020_jr_8016AB6C.o,tail14.data.o,ov_SC04_020_jr_80171B4C.o,ov_SC04_020_jr_801734BC.o,tail15.data.o,ov_SC04_020_jr_801789AC.o,ov_SC04_020_jr_80178D40.o,tail16.data.o,ov_SC04_020_jr_8017A4AC.o,tail17.data.o,ov_SC04_020_jr_8017AE2C.o,ov_SC04_020_jr_8017D604.o,tail18.data.o,ov_SC04_020_jr_8018254C.o,tail19.data.o,trailing.o  # Phase-26 §8 jtbl-rodata carve
build/src/ov_SC04_020/ov_SC04_020.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14
build/src/ov_SC04_020/ov_SC04_020_jr_8012ACE0.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0xcc,+0xe0
build/src/ov_SC04_020/ov_SC04_020_jr_80135D20.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC04_020/ov_SC04_020_jr_8013F350.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC04_020/ov_SC04_020_jr_8013FFD8.o: JTBL_PADS := 0,0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38,+0x58
build/src/ov_SC04_020/ov_SC04_020_jr_8015444C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x70
build/src/ov_SC04_020/ov_SC04_020_jr_80154C24.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x24
build/src/ov_SC04_020/ov_SC04_020_jr_801588CC.o: JTBL_PADS := 0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x28,+0x48
build/src/ov_SC04_020/ov_SC04_020_jr_80159C84.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC04_020/ov_SC04_020_jr_8015AE2C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC04_020/ov_SC04_020_jr_8016AB6C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC04_020/ov_SC04_020_jr_80178D40.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x178
build/src/ov_SC04_020/ov_SC04_020_jr_8017D604.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC04_020/ov_SC04_020_jr_8018254C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x1c
build/src/ov_SC04_020/ov_SC04_020_o0c.o: JTBL_PADS := 0,4,4,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x38,+0xa8,+0x118
ov_SC04_020_CHECK_SHA  := config/check.ov_SC04_020.sha
ov_SC04_020_SYMBOLS    := config/symbols.ov_SC04_020.txt
ov_SC04_020_SIG        := .run/sig.ov_SC04_020.jsonl
ov_SC04_020_GHIDRA_PROG := ov_SC04_020
ov_SC04_020_VRAM_BASE  := 0x80128158
ov_SC04_020_TEXT_LO    := 0x80128158
ov_SC04_020_TEXT_HI    := 0x801BC7AF
ov_SC04_020_ASM_DIR     := asm/ov_SC04_020
ov_SC04_020_SRC_DIR     := src/ov_SC04_020
ov_SC04_020_UNDEF_SYMS  := build/ov_SC04_020/undefined_syms_auto.txt
ov_SC04_020_UNDEF_FUNCS := build/ov_SC04_020/undefined_funcs_auto.txt

# --- ov_SC04_021 (location overlay SC04/FILE_021, vram 0x80128158 — onboarded by new_overlay.sh) ---
ov_SC04_021_EXE        := extracted/retail/SC04.CD.dir/FILE_021.dir/0.4.dec
ov_SC04_021_NAME       := ov_SC04_021
ov_SC04_021_OUT_DIR    := build/ov_SC04_021
ov_SC04_021_OUT        := $(ov_SC04_021_OUT_DIR)/$(ov_SC04_021_NAME)
ov_SC04_021_ELF        := $(ov_SC04_021_OUT).elf
ov_SC04_021_MAPFILE    := $(ov_SC04_021_OUT).map
ov_SC04_021_LD_SCRIPT  := $(ov_SC04_021_OUT).ld
ov_SC04_021_SPLAT_YAML := config/splat.ov_SC04_021.yaml
ov_SC04_021_JTBL_INTERLEAVE := --order tail.data.o,ov_SC04_021.o,ov_SC04_021_jr_8012ACE0.o,tail2.data.o,ov_SC04_021_jr_80135888.o,tail3.data.o,ov_SC04_021_jr_80135A4C.o,tail4.data.o,ov_SC04_021_jr_80135D20.o,tail5.data.o,ov_SC04_021_jr_801380E0.o,ov_SC04_021_o0c.o,tail6.data.o,ov_SC04_021_jr_8013F350.o,tail7.data.o,ov_SC04_021_jr_8013FFD8.o,tail8.data.o,ov_SC04_021_jr_80140608.o,tail9.data.o,ov_SC04_021_jr_8015444C.o,ov_SC04_021_jr_80154C24.o,ov_SC04_021_jr_801588CC.o,ov_SC04_021_jr_80159C84.o,tail10.data.o,ov_SC04_021_jr_8015A3C8.o,tail11.data.o,ov_SC04_021_jr_8015AE2C.o,tail12.data.o,ov_SC04_021_jr_8015C32C.o,tail13.data.o,ov_SC04_021_jr_8016AB6C.o,tail14.data.o,ov_SC04_021_jr_80171B4C.o,ov_SC04_021_jr_801734BC.o,tail15.data.o,ov_SC04_021_jr_801789AC.o,ov_SC04_021_jr_80178D40.o,tail16.data.o,ov_SC04_021_jr_8017A4AC.o,tail17.data.o,ov_SC04_021_jr_8017AE2C.o,ov_SC04_021_jr_8017D5C0.o,tail18.data.o,trailing.o  # Phase-26 §8 jtbl-rodata carve
build/src/ov_SC04_021/ov_SC04_021.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14
build/src/ov_SC04_021/ov_SC04_021_jr_8012ACE0.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0xcc,+0xe0
build/src/ov_SC04_021/ov_SC04_021_jr_80135D20.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC04_021/ov_SC04_021_jr_8013F350.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC04_021/ov_SC04_021_jr_8013FFD8.o: JTBL_PADS := 0,0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38,+0x58
build/src/ov_SC04_021/ov_SC04_021_jr_8015444C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x70
build/src/ov_SC04_021/ov_SC04_021_jr_80154C24.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x24
build/src/ov_SC04_021/ov_SC04_021_jr_801588CC.o: JTBL_PADS := 0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x28,+0x48
build/src/ov_SC04_021/ov_SC04_021_jr_80159C84.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC04_021/ov_SC04_021_jr_8015AE2C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC04_021/ov_SC04_021_jr_8016AB6C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC04_021/ov_SC04_021_jr_80178D40.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x178
build/src/ov_SC04_021/ov_SC04_021_jr_8017AE2C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14
build/src/ov_SC04_021/ov_SC04_021_o0c.o: JTBL_PADS := 0,4,4,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x38,+0xa8,+0x118
ov_SC04_021_CHECK_SHA  := config/check.ov_SC04_021.sha
ov_SC04_021_SYMBOLS    := config/symbols.ov_SC04_021.txt
ov_SC04_021_SIG        := .run/sig.ov_SC04_021.jsonl
ov_SC04_021_GHIDRA_PROG := ov_SC04_021
ov_SC04_021_VRAM_BASE  := 0x80128158
ov_SC04_021_TEXT_LO    := 0x80128158
ov_SC04_021_TEXT_HI    := 0x8018FB2D
ov_SC04_021_ASM_DIR     := asm/ov_SC04_021
ov_SC04_021_SRC_DIR     := src/ov_SC04_021
ov_SC04_021_UNDEF_SYMS  := build/ov_SC04_021/undefined_syms_auto.txt
ov_SC04_021_UNDEF_FUNCS := build/ov_SC04_021/undefined_funcs_auto.txt

# --- ov_SC05_001 (location overlay SC05/FILE_001, vram 0x80128158 — onboarded by new_overlay.sh) ---
ov_SC05_001_EXE        := extracted/retail/SC05.CD.dir/FILE_001.dir/0.4.dec
ov_SC05_001_NAME       := ov_SC05_001
ov_SC05_001_OUT_DIR    := build/ov_SC05_001
ov_SC05_001_OUT        := $(ov_SC05_001_OUT_DIR)/$(ov_SC05_001_NAME)
ov_SC05_001_ELF        := $(ov_SC05_001_OUT).elf
ov_SC05_001_MAPFILE    := $(ov_SC05_001_OUT).map
ov_SC05_001_LD_SCRIPT  := $(ov_SC05_001_OUT).ld
ov_SC05_001_SPLAT_YAML := config/splat.ov_SC05_001.yaml
ov_SC05_001_JTBL_INTERLEAVE := --order tail.data.o,ov_SC05_001.o,ov_SC05_001_jr_8012ACE0.o,tail2.data.o,ov_SC05_001_jr_80135888.o,tail3.data.o,ov_SC05_001_jr_80135A4C.o,tail4.data.o,ov_SC05_001_jr_80135D20.o,tail5.data.o,ov_SC05_001_jr_801380E0.o,ov_SC05_001_o0c.o,tail6.data.o,ov_SC05_001_jr_8013F350.o,tail7.data.o,ov_SC05_001_jr_8013FFD8.o,tail8.data.o,ov_SC05_001_jr_80140608.o,tail9.data.o,ov_SC05_001_jr_8015444C.o,ov_SC05_001_jr_80154C24.o,ov_SC05_001_jr_801588CC.o,ov_SC05_001_jr_80159C84.o,tail10.data.o,ov_SC05_001_jr_8015A3C8.o,tail11.data.o,ov_SC05_001_jr_8015AE2C.o,tail12.data.o,ov_SC05_001_jr_8015C32C.o,tail13.data.o,ov_SC05_001_jr_8016AB6C.o,tail14.data.o,ov_SC05_001_jr_80171B4C.o,ov_SC05_001_jr_801734BC.o,tail15.data.o,ov_SC05_001_jr_801789AC.o,ov_SC05_001_jr_80178D40.o,tail16.data.o,ov_SC05_001_jr_8017A4AC.o,tail17.data.o,ov_SC05_001_jr_8017AE2C.o,ov_SC05_001_jr_8017BEBC.o,ov_SC05_001_jr_80183508.o,tail18.data.o,trailing.o  # Phase-26 §8 jtbl-rodata carve
build/src/ov_SC05_001/ov_SC05_001.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14
build/src/ov_SC05_001/ov_SC05_001_jr_8012ACE0.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0xcc,+0xe0
build/src/ov_SC05_001/ov_SC05_001_jr_80135D20.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC05_001/ov_SC05_001_jr_8013F350.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC05_001/ov_SC05_001_jr_8013FFD8.o: JTBL_PADS := 0,0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38,+0x58
build/src/ov_SC05_001/ov_SC05_001_jr_8015444C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x70
build/src/ov_SC05_001/ov_SC05_001_jr_80154C24.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x24
build/src/ov_SC05_001/ov_SC05_001_jr_801588CC.o: JTBL_PADS := 0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x28,+0x48
build/src/ov_SC05_001/ov_SC05_001_jr_80159C84.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC05_001/ov_SC05_001_jr_8015AE2C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC05_001/ov_SC05_001_jr_8016AB6C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC05_001/ov_SC05_001_jr_80178D40.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x178
build/src/ov_SC05_001/ov_SC05_001_jr_8017BEBC.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC05_001/ov_SC05_001_jr_80183508.o: JTBL_PADS := 0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18,+0xe0
build/src/ov_SC05_001/ov_SC05_001_o0c.o: JTBL_PADS := 0,4,4,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x38,+0xa8,+0x118
ov_SC05_001_CHECK_SHA  := config/check.ov_SC05_001.sha
ov_SC05_001_SYMBOLS    := config/symbols.ov_SC05_001.txt
ov_SC05_001_SIG        := .run/sig.ov_SC05_001.jsonl
ov_SC05_001_GHIDRA_PROG := ov_SC05_001
ov_SC05_001_VRAM_BASE  := 0x80128158
ov_SC05_001_TEXT_LO    := 0x80128158
ov_SC05_001_TEXT_HI    := 0x801B6007
ov_SC05_001_ASM_DIR     := asm/ov_SC05_001
ov_SC05_001_SRC_DIR     := src/ov_SC05_001
ov_SC05_001_UNDEF_SYMS  := build/ov_SC05_001/undefined_syms_auto.txt
ov_SC05_001_UNDEF_FUNCS := build/ov_SC05_001/undefined_funcs_auto.txt

# --- ov_SC05_002 (location overlay SC05/FILE_002, vram 0x80128158 — onboarded by new_overlay.sh) ---
ov_SC05_002_EXE        := extracted/retail/SC05.CD.dir/FILE_002.dir/0.4.dec
ov_SC05_002_NAME       := ov_SC05_002
ov_SC05_002_OUT_DIR    := build/ov_SC05_002
ov_SC05_002_OUT        := $(ov_SC05_002_OUT_DIR)/$(ov_SC05_002_NAME)
ov_SC05_002_ELF        := $(ov_SC05_002_OUT).elf
ov_SC05_002_MAPFILE    := $(ov_SC05_002_OUT).map
ov_SC05_002_LD_SCRIPT  := $(ov_SC05_002_OUT).ld
ov_SC05_002_SPLAT_YAML := config/splat.ov_SC05_002.yaml
ov_SC05_002_JTBL_INTERLEAVE := --order tail.data.o,ov_SC05_002.o,ov_SC05_002_jr_8012ACE0.o,tail2.data.o,ov_SC05_002_jr_80135888.o,tail3.data.o,ov_SC05_002_jr_80135A4C.o,tail4.data.o,ov_SC05_002_jr_80135D20.o,tail5.data.o,ov_SC05_002_jr_801380E0.o,ov_SC05_002_o0c.o,tail6.data.o,ov_SC05_002_jr_8013F350.o,tail7.data.o,ov_SC05_002_jr_8013FFD8.o,tail8.data.o,ov_SC05_002_jr_80140608.o,tail9.data.o,ov_SC05_002_jr_8015444C.o,ov_SC05_002_jr_80154C24.o,ov_SC05_002_jr_801588CC.o,ov_SC05_002_jr_80159C84.o,tail10.data.o,ov_SC05_002_jr_8015A3C8.o,tail11.data.o,ov_SC05_002_jr_8015AE2C.o,tail12.data.o,ov_SC05_002_jr_8015C32C.o,tail13.data.o,ov_SC05_002_jr_8016AB6C.o,tail14.data.o,ov_SC05_002_jr_80171B4C.o,ov_SC05_002_jr_801734BC.o,tail15.data.o,ov_SC05_002_jr_801789AC.o,ov_SC05_002_jr_80178D40.o,tail16.data.o,ov_SC05_002_jr_8017A4AC.o,tail17.data.o,ov_SC05_002_jr_8017AE2C.o,ov_SC05_002_jr_8017BEBC.o,tail18.data.o,trailing.o  # Phase-26 §8 jtbl-rodata carve
build/src/ov_SC05_002/ov_SC05_002.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14
build/src/ov_SC05_002/ov_SC05_002_jr_8012ACE0.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0xcc,+0xe0
build/src/ov_SC05_002/ov_SC05_002_jr_80135D20.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC05_002/ov_SC05_002_jr_8013F350.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC05_002/ov_SC05_002_jr_8013FFD8.o: JTBL_PADS := 0,0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38,+0x58
build/src/ov_SC05_002/ov_SC05_002_jr_8015444C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x70
build/src/ov_SC05_002/ov_SC05_002_jr_80154C24.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x24
build/src/ov_SC05_002/ov_SC05_002_jr_801588CC.o: JTBL_PADS := 0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x28,+0x48
build/src/ov_SC05_002/ov_SC05_002_jr_80159C84.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC05_002/ov_SC05_002_jr_8015AE2C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC05_002/ov_SC05_002_jr_8016AB6C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC05_002/ov_SC05_002_jr_80178D40.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x178
build/src/ov_SC05_002/ov_SC05_002_o0c.o: JTBL_PADS := 0,4,4,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x38,+0xa8,+0x118
ov_SC05_002_CHECK_SHA  := config/check.ov_SC05_002.sha
ov_SC05_002_SYMBOLS    := config/symbols.ov_SC05_002.txt
ov_SC05_002_SIG        := .run/sig.ov_SC05_002.jsonl
ov_SC05_002_GHIDRA_PROG := ov_SC05_002
ov_SC05_002_VRAM_BASE  := 0x80128158
ov_SC05_002_TEXT_LO    := 0x80128158
ov_SC05_002_TEXT_HI    := 0x8019FFBF
ov_SC05_002_ASM_DIR     := asm/ov_SC05_002
ov_SC05_002_SRC_DIR     := src/ov_SC05_002
ov_SC05_002_UNDEF_SYMS  := build/ov_SC05_002/undefined_syms_auto.txt
ov_SC05_002_UNDEF_FUNCS := build/ov_SC05_002/undefined_funcs_auto.txt

# --- ov_SC05_003 (location overlay SC05/FILE_003, vram 0x80128158 — onboarded by new_overlay.sh) ---
ov_SC05_003_EXE        := extracted/retail/SC05.CD.dir/FILE_003.dir/0.4.dec
ov_SC05_003_NAME       := ov_SC05_003
ov_SC05_003_OUT_DIR    := build/ov_SC05_003
ov_SC05_003_OUT        := $(ov_SC05_003_OUT_DIR)/$(ov_SC05_003_NAME)
ov_SC05_003_ELF        := $(ov_SC05_003_OUT).elf
ov_SC05_003_MAPFILE    := $(ov_SC05_003_OUT).map
ov_SC05_003_LD_SCRIPT  := $(ov_SC05_003_OUT).ld
ov_SC05_003_SPLAT_YAML := config/splat.ov_SC05_003.yaml
ov_SC05_003_JTBL_INTERLEAVE := --order tail.data.o,ov_SC05_003.o,ov_SC05_003_jr_8012ACE0.o,tail2.data.o,ov_SC05_003_jr_80135888.o,tail3.data.o,ov_SC05_003_jr_80135A4C.o,tail4.data.o,ov_SC05_003_jr_80135D20.o,tail5.data.o,ov_SC05_003_jr_801380E0.o,ov_SC05_003_o0c.o,tail6.data.o,ov_SC05_003_jr_8013F350.o,tail7.data.o,ov_SC05_003_jr_8013FFD8.o,tail8.data.o,ov_SC05_003_jr_80140608.o,tail9.data.o,ov_SC05_003_jr_8015444C.o,ov_SC05_003_jr_80154C24.o,ov_SC05_003_jr_801588CC.o,ov_SC05_003_jr_80159C84.o,tail10.data.o,ov_SC05_003_jr_8015A3C8.o,tail11.data.o,ov_SC05_003_jr_8015AE2C.o,tail12.data.o,ov_SC05_003_jr_8015C32C.o,tail13.data.o,ov_SC05_003_jr_8016AB6C.o,tail14.data.o,ov_SC05_003_jr_80171B4C.o,ov_SC05_003_jr_801734BC.o,tail15.data.o,ov_SC05_003_jr_801789AC.o,ov_SC05_003_jr_80178D40.o,tail16.data.o,ov_SC05_003_jr_8017A4AC.o,tail17.data.o,ov_SC05_003_jr_8017AE2C.o,ov_SC05_003_jr_8017BEBC.o,tail18.data.o,trailing.o  # Phase-26 §8 jtbl-rodata carve
build/src/ov_SC05_003/ov_SC05_003.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14
build/src/ov_SC05_003/ov_SC05_003_jr_8012ACE0.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0xcc,+0xe0
build/src/ov_SC05_003/ov_SC05_003_jr_80135D20.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC05_003/ov_SC05_003_jr_8013F350.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC05_003/ov_SC05_003_jr_8013FFD8.o: JTBL_PADS := 0,0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38,+0x58
build/src/ov_SC05_003/ov_SC05_003_jr_8015444C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x70
build/src/ov_SC05_003/ov_SC05_003_jr_80154C24.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x24
build/src/ov_SC05_003/ov_SC05_003_jr_801588CC.o: JTBL_PADS := 0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x28,+0x48
build/src/ov_SC05_003/ov_SC05_003_jr_80159C84.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC05_003/ov_SC05_003_jr_8015AE2C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC05_003/ov_SC05_003_jr_8016AB6C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC05_003/ov_SC05_003_jr_80178D40.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x178
build/src/ov_SC05_003/ov_SC05_003_jr_8017BEBC.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC05_003/ov_SC05_003_o0c.o: JTBL_PADS := 0,4,4,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x38,+0xa8,+0x118
ov_SC05_003_CHECK_SHA  := config/check.ov_SC05_003.sha
ov_SC05_003_SYMBOLS    := config/symbols.ov_SC05_003.txt
ov_SC05_003_SIG        := .run/sig.ov_SC05_003.jsonl
ov_SC05_003_GHIDRA_PROG := ov_SC05_003
ov_SC05_003_VRAM_BASE  := 0x80128158
ov_SC05_003_TEXT_LO    := 0x80128158
ov_SC05_003_TEXT_HI    := 0x801ACACF
ov_SC05_003_ASM_DIR     := asm/ov_SC05_003
ov_SC05_003_SRC_DIR     := src/ov_SC05_003
ov_SC05_003_UNDEF_SYMS  := build/ov_SC05_003/undefined_syms_auto.txt
ov_SC05_003_UNDEF_FUNCS := build/ov_SC05_003/undefined_funcs_auto.txt

# --- ov_SC05_004 (location overlay SC05/FILE_004, vram 0x80128158 — onboarded by new_overlay.sh) ---
ov_SC05_004_EXE        := extracted/retail/SC05.CD.dir/FILE_004.dir/0.4.dec
ov_SC05_004_NAME       := ov_SC05_004
ov_SC05_004_OUT_DIR    := build/ov_SC05_004
ov_SC05_004_OUT        := $(ov_SC05_004_OUT_DIR)/$(ov_SC05_004_NAME)
ov_SC05_004_ELF        := $(ov_SC05_004_OUT).elf
ov_SC05_004_MAPFILE    := $(ov_SC05_004_OUT).map
ov_SC05_004_LD_SCRIPT  := $(ov_SC05_004_OUT).ld
ov_SC05_004_SPLAT_YAML := config/splat.ov_SC05_004.yaml
ov_SC05_004_JTBL_INTERLEAVE := --order tail.data.o,ov_SC05_004.o,ov_SC05_004_jr_8012ACE0.o,tail2.data.o,ov_SC05_004_jr_80135888.o,tail3.data.o,ov_SC05_004_jr_80135A4C.o,tail4.data.o,ov_SC05_004_jr_80135D20.o,tail5.data.o,ov_SC05_004_jr_801380E0.o,ov_SC05_004_o0c.o,tail6.data.o,ov_SC05_004_jr_8013F350.o,tail7.data.o,ov_SC05_004_jr_8014032C.o,tail8.data.o,ov_SC05_004_jr_80140608.o,tail9.data.o,ov_SC05_004_jr_8015444C.o,ov_SC05_004_jr_80154C24.o,ov_SC05_004_jr_801588CC.o,ov_SC05_004_jr_80159C84.o,tail10.data.o,ov_SC05_004_jr_8015A3C8.o,tail11.data.o,ov_SC05_004_jr_8015AE2C.o,tail12.data.o,ov_SC05_004_jr_8015C32C.o,tail13.data.o,ov_SC05_004_jr_8016AB6C.o,tail14.data.o,ov_SC05_004_jr_80171B4C.o,ov_SC05_004_jr_801734BC.o,tail15.data.o,ov_SC05_004_jr_801789AC.o,ov_SC05_004_jr_80178D40.o,tail16.data.o,ov_SC05_004_jr_8017A4AC.o,tail17.data.o,ov_SC05_004_jr_8017AE2C.o,ov_SC05_004_jr_8017BEBC.o,tail18.data.o,ov_SC05_004_jr_8017F210.o,tail19.data.o,trailing.o  # Phase-26 §8 jtbl-rodata carve
build/src/ov_SC05_004/ov_SC05_004.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14
build/src/ov_SC05_004/ov_SC05_004_jr_8012ACE0.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0xcc,+0xe0
build/src/ov_SC05_004/ov_SC05_004_jr_80135D20.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC05_004/ov_SC05_004_jr_8013F350.o: JTBL_PADS := 0,0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38,+0x58
build/src/ov_SC05_004/ov_SC05_004_jr_8014032C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC05_004/ov_SC05_004_jr_8015444C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x70
build/src/ov_SC05_004/ov_SC05_004_jr_80154C24.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x24
build/src/ov_SC05_004/ov_SC05_004_jr_801588CC.o: JTBL_PADS := 0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x28,+0x48
build/src/ov_SC05_004/ov_SC05_004_jr_80159C84.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC05_004/ov_SC05_004_jr_8015AE2C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC05_004/ov_SC05_004_jr_8016AB6C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC05_004/ov_SC05_004_jr_80178D40.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x178
build/src/ov_SC05_004/ov_SC05_004_jr_8017F210.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x68
build/src/ov_SC05_004/ov_SC05_004_o0c.o: JTBL_PADS := 0,4,4,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x38,+0xa8,+0x118
ov_SC05_004_CHECK_SHA  := config/check.ov_SC05_004.sha
ov_SC05_004_SYMBOLS    := config/symbols.ov_SC05_004.txt
ov_SC05_004_SIG        := .run/sig.ov_SC05_004.jsonl
ov_SC05_004_GHIDRA_PROG := ov_SC05_004
ov_SC05_004_VRAM_BASE  := 0x80128158
ov_SC05_004_TEXT_LO    := 0x80128158
ov_SC05_004_TEXT_HI    := 0x8019F327
ov_SC05_004_ASM_DIR     := asm/ov_SC05_004
ov_SC05_004_SRC_DIR     := src/ov_SC05_004
ov_SC05_004_UNDEF_SYMS  := build/ov_SC05_004/undefined_syms_auto.txt
ov_SC05_004_UNDEF_FUNCS := build/ov_SC05_004/undefined_funcs_auto.txt

# --- ov_SC05_005 (location overlay SC05/FILE_005, vram 0x80128158 — onboarded by new_overlay.sh) ---
ov_SC05_005_EXE        := extracted/retail/SC05.CD.dir/FILE_005.dir/0.4.dec
ov_SC05_005_NAME       := ov_SC05_005
ov_SC05_005_OUT_DIR    := build/ov_SC05_005
ov_SC05_005_OUT        := $(ov_SC05_005_OUT_DIR)/$(ov_SC05_005_NAME)
ov_SC05_005_ELF        := $(ov_SC05_005_OUT).elf
ov_SC05_005_MAPFILE    := $(ov_SC05_005_OUT).map
ov_SC05_005_LD_SCRIPT  := $(ov_SC05_005_OUT).ld
ov_SC05_005_SPLAT_YAML := config/splat.ov_SC05_005.yaml
ov_SC05_005_JTBL_INTERLEAVE := --order tail.data.o,ov_SC05_005.o,ov_SC05_005_jr_8012ACE0.o,tail2.data.o,ov_SC05_005_jr_80135888.o,tail3.data.o,ov_SC05_005_jr_80135A4C.o,tail4.data.o,ov_SC05_005_jr_80135D20.o,tail5.data.o,ov_SC05_005_jr_801380E0.o,ov_SC05_005_o0c.o,tail6.data.o,ov_SC05_005_jr_8013F350.o,tail7.data.o,ov_SC05_005_jr_8013FFD8.o,tail8.data.o,ov_SC05_005_jr_80140608.o,tail9.data.o,ov_SC05_005_jr_8015444C.o,ov_SC05_005_jr_80154C24.o,ov_SC05_005_jr_801588CC.o,ov_SC05_005_jr_80159C84.o,tail10.data.o,ov_SC05_005_jr_8015A3C8.o,tail11.data.o,ov_SC05_005_jr_8015AE2C.o,tail12.data.o,ov_SC05_005_jr_8015C32C.o,tail13.data.o,ov_SC05_005_jr_8016AB6C.o,tail14.data.o,ov_SC05_005_jr_80171B4C.o,ov_SC05_005_jr_801734BC.o,tail15.data.o,ov_SC05_005_jr_801789AC.o,ov_SC05_005_jr_80178D40.o,tail16.data.o,ov_SC05_005_jr_8017A4AC.o,tail17.data.o,ov_SC05_005_jr_8017AE2C.o,ov_SC05_005_jr_8017D898.o,tail18.data.o,trailing.o  # Phase-26 §8 jtbl-rodata carve
build/src/ov_SC05_005/ov_SC05_005.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14
build/src/ov_SC05_005/ov_SC05_005_jr_8012ACE0.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0xcc,+0xe0
build/src/ov_SC05_005/ov_SC05_005_jr_80135D20.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC05_005/ov_SC05_005_jr_8013F350.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC05_005/ov_SC05_005_jr_8013FFD8.o: JTBL_PADS := 0,0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38,+0x58
build/src/ov_SC05_005/ov_SC05_005_jr_8015444C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x70
build/src/ov_SC05_005/ov_SC05_005_jr_80154C24.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x24
build/src/ov_SC05_005/ov_SC05_005_jr_801588CC.o: JTBL_PADS := 0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x28,+0x48
build/src/ov_SC05_005/ov_SC05_005_jr_80159C84.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC05_005/ov_SC05_005_jr_8015AE2C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC05_005/ov_SC05_005_jr_8016AB6C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC05_005/ov_SC05_005_jr_80178D40.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x178
build/src/ov_SC05_005/ov_SC05_005_o0c.o: JTBL_PADS := 0,4,4,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x38,+0xa8,+0x118
ov_SC05_005_CHECK_SHA  := config/check.ov_SC05_005.sha
ov_SC05_005_SYMBOLS    := config/symbols.ov_SC05_005.txt
ov_SC05_005_SIG        := .run/sig.ov_SC05_005.jsonl
ov_SC05_005_GHIDRA_PROG := ov_SC05_005
ov_SC05_005_VRAM_BASE  := 0x80128158
ov_SC05_005_TEXT_LO    := 0x80128158
ov_SC05_005_TEXT_HI    := 0x801B202F
ov_SC05_005_ASM_DIR     := asm/ov_SC05_005
ov_SC05_005_SRC_DIR     := src/ov_SC05_005
ov_SC05_005_UNDEF_SYMS  := build/ov_SC05_005/undefined_syms_auto.txt
ov_SC05_005_UNDEF_FUNCS := build/ov_SC05_005/undefined_funcs_auto.txt

# --- ov_SC05_006 (location overlay SC05/FILE_006, vram 0x80128158 — onboarded by new_overlay.sh) ---
ov_SC05_006_EXE        := extracted/retail/SC05.CD.dir/FILE_006.dir/0.4.dec
ov_SC05_006_NAME       := ov_SC05_006
ov_SC05_006_OUT_DIR    := build/ov_SC05_006
ov_SC05_006_OUT        := $(ov_SC05_006_OUT_DIR)/$(ov_SC05_006_NAME)
ov_SC05_006_ELF        := $(ov_SC05_006_OUT).elf
ov_SC05_006_MAPFILE    := $(ov_SC05_006_OUT).map
ov_SC05_006_LD_SCRIPT  := $(ov_SC05_006_OUT).ld
ov_SC05_006_SPLAT_YAML := config/splat.ov_SC05_006.yaml
ov_SC05_006_JTBL_INTERLEAVE := --order tail.data.o,ov_SC05_006.o,ov_SC05_006_jr_8012ACE0.o,tail2.data.o,ov_SC05_006_jr_80135888.o,tail3.data.o,ov_SC05_006_jr_80135A4C.o,tail4.data.o,ov_SC05_006_jr_80135D20.o,tail5.data.o,ov_SC05_006_jr_801380E0.o,ov_SC05_006_o0c.o,tail6.data.o,ov_SC05_006_jr_8013F350.o,tail7.data.o,ov_SC05_006_jr_8013FFD8.o,tail8.data.o,ov_SC05_006_jr_80140608.o,tail9.data.o,ov_SC05_006_jr_8015444C.o,ov_SC05_006_jr_80154C24.o,ov_SC05_006_jr_801588CC.o,ov_SC05_006_jr_80159C84.o,tail10.data.o,ov_SC05_006_jr_8015A3C8.o,tail11.data.o,ov_SC05_006_jr_8015AE2C.o,tail12.data.o,ov_SC05_006_jr_8015C32C.o,tail13.data.o,ov_SC05_006_jr_8016AB6C.o,tail14.data.o,ov_SC05_006_jr_80171B4C.o,ov_SC05_006_jr_801734BC.o,tail15.data.o,ov_SC05_006_jr_801789AC.o,ov_SC05_006_jr_80178D40.o,tail16.data.o,ov_SC05_006_jr_8017A4AC.o,tail17.data.o,ov_SC05_006_jr_8017AE2C.o,ov_SC05_006_jr_8017BEBC.o,tail18.data.o,trailing.o  # Phase-26 §8 jtbl-rodata carve
build/src/ov_SC05_006/ov_SC05_006.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14
build/src/ov_SC05_006/ov_SC05_006_jr_8012ACE0.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0xcc,+0xe0
build/src/ov_SC05_006/ov_SC05_006_jr_80135D20.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC05_006/ov_SC05_006_jr_8013F350.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC05_006/ov_SC05_006_jr_8013FFD8.o: JTBL_PADS := 0,0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38,+0x58
build/src/ov_SC05_006/ov_SC05_006_jr_8015444C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x70
build/src/ov_SC05_006/ov_SC05_006_jr_80154C24.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x24
build/src/ov_SC05_006/ov_SC05_006_jr_801588CC.o: JTBL_PADS := 0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x28,+0x48
build/src/ov_SC05_006/ov_SC05_006_jr_80159C84.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC05_006/ov_SC05_006_jr_8015AE2C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC05_006/ov_SC05_006_jr_8016AB6C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC05_006/ov_SC05_006_jr_80178D40.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x178
build/src/ov_SC05_006/ov_SC05_006_o0c.o: JTBL_PADS := 0,4,4,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x38,+0xa8,+0x118
ov_SC05_006_CHECK_SHA  := config/check.ov_SC05_006.sha
ov_SC05_006_SYMBOLS    := config/symbols.ov_SC05_006.txt
ov_SC05_006_SIG        := .run/sig.ov_SC05_006.jsonl
ov_SC05_006_GHIDRA_PROG := ov_SC05_006
ov_SC05_006_VRAM_BASE  := 0x80128158
ov_SC05_006_TEXT_LO    := 0x80128158
ov_SC05_006_TEXT_HI    := 0x8019015F
ov_SC05_006_ASM_DIR     := asm/ov_SC05_006
ov_SC05_006_SRC_DIR     := src/ov_SC05_006
ov_SC05_006_UNDEF_SYMS  := build/ov_SC05_006/undefined_syms_auto.txt
ov_SC05_006_UNDEF_FUNCS := build/ov_SC05_006/undefined_funcs_auto.txt

# --- ov_SC05_007 (location overlay SC05/FILE_007, vram 0x80128158 — onboarded by new_overlay.sh) ---
ov_SC05_007_EXE        := extracted/retail/SC05.CD.dir/FILE_007.dir/0.4.dec
ov_SC05_007_NAME       := ov_SC05_007
ov_SC05_007_OUT_DIR    := build/ov_SC05_007
ov_SC05_007_OUT        := $(ov_SC05_007_OUT_DIR)/$(ov_SC05_007_NAME)
ov_SC05_007_ELF        := $(ov_SC05_007_OUT).elf
ov_SC05_007_MAPFILE    := $(ov_SC05_007_OUT).map
ov_SC05_007_LD_SCRIPT  := $(ov_SC05_007_OUT).ld
ov_SC05_007_SPLAT_YAML := config/splat.ov_SC05_007.yaml
ov_SC05_007_JTBL_INTERLEAVE := --order tail.data.o,ov_SC05_007.o,ov_SC05_007_jr_8012ACE0.o,tail2.data.o,ov_SC05_007_jr_80135888.o,tail3.data.o,ov_SC05_007_jr_80135A4C.o,tail4.data.o,ov_SC05_007_jr_80135D20.o,tail5.data.o,ov_SC05_007_jr_801380E0.o,ov_SC05_007_o0c.o,tail6.data.o,ov_SC05_007_jr_8013F350.o,tail7.data.o,ov_SC05_007_jr_8013FFD8.o,tail8.data.o,ov_SC05_007_jr_80140608.o,tail9.data.o,ov_SC05_007_jr_8015444C.o,ov_SC05_007_jr_80154C24.o,ov_SC05_007_jr_801588CC.o,ov_SC05_007_jr_80159C84.o,tail10.data.o,ov_SC05_007_jr_8015A3C8.o,tail11.data.o,ov_SC05_007_jr_8015AE2C.o,tail12.data.o,ov_SC05_007_jr_8015C32C.o,tail13.data.o,ov_SC05_007_jr_8016AB6C.o,tail14.data.o,ov_SC05_007_jr_80171B4C.o,ov_SC05_007_jr_801734BC.o,tail15.data.o,ov_SC05_007_jr_801789AC.o,ov_SC05_007_jr_80178D40.o,tail16.data.o,ov_SC05_007_jr_8017A4AC.o,tail17.data.o,ov_SC05_007_jr_8017AE2C.o,ov_SC05_007_jr_8017BEBC.o,tail18.data.o,trailing.o  # Phase-26 §8 jtbl-rodata carve
build/src/ov_SC05_007/ov_SC05_007.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14
build/src/ov_SC05_007/ov_SC05_007_jr_8012ACE0.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0xcc,+0xe0
build/src/ov_SC05_007/ov_SC05_007_jr_80135D20.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC05_007/ov_SC05_007_jr_8013F350.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC05_007/ov_SC05_007_jr_8013FFD8.o: JTBL_PADS := 0,0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38,+0x58
build/src/ov_SC05_007/ov_SC05_007_jr_8015444C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x70
build/src/ov_SC05_007/ov_SC05_007_jr_80154C24.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x24
build/src/ov_SC05_007/ov_SC05_007_jr_801588CC.o: JTBL_PADS := 0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x28,+0x48
build/src/ov_SC05_007/ov_SC05_007_jr_80159C84.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC05_007/ov_SC05_007_jr_8015AE2C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC05_007/ov_SC05_007_jr_8016AB6C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC05_007/ov_SC05_007_jr_80178D40.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x178
build/src/ov_SC05_007/ov_SC05_007_o0c.o: JTBL_PADS := 0,4,4,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x38,+0xa8,+0x118
ov_SC05_007_CHECK_SHA  := config/check.ov_SC05_007.sha
ov_SC05_007_SYMBOLS    := config/symbols.ov_SC05_007.txt
ov_SC05_007_SIG        := .run/sig.ov_SC05_007.jsonl
ov_SC05_007_GHIDRA_PROG := ov_SC05_007
ov_SC05_007_VRAM_BASE  := 0x80128158
ov_SC05_007_TEXT_LO    := 0x80128158
ov_SC05_007_TEXT_HI    := 0x8019CEFF
ov_SC05_007_ASM_DIR     := asm/ov_SC05_007
ov_SC05_007_SRC_DIR     := src/ov_SC05_007
ov_SC05_007_UNDEF_SYMS  := build/ov_SC05_007/undefined_syms_auto.txt
ov_SC05_007_UNDEF_FUNCS := build/ov_SC05_007/undefined_funcs_auto.txt

# --- ov_SC05_008 (location overlay SC05/FILE_008, vram 0x80128158 — onboarded by new_overlay.sh) ---
ov_SC05_008_EXE        := extracted/retail/SC05.CD.dir/FILE_008.dir/0.4.dec
ov_SC05_008_NAME       := ov_SC05_008
ov_SC05_008_OUT_DIR    := build/ov_SC05_008
ov_SC05_008_OUT        := $(ov_SC05_008_OUT_DIR)/$(ov_SC05_008_NAME)
ov_SC05_008_ELF        := $(ov_SC05_008_OUT).elf
ov_SC05_008_MAPFILE    := $(ov_SC05_008_OUT).map
ov_SC05_008_LD_SCRIPT  := $(ov_SC05_008_OUT).ld
ov_SC05_008_SPLAT_YAML := config/splat.ov_SC05_008.yaml
ov_SC05_008_JTBL_INTERLEAVE := --order tail.data.o,ov_SC05_008.o,ov_SC05_008_jr_8012ACE0.o,tail2.data.o,ov_SC05_008_jr_80135888.o,tail3.data.o,ov_SC05_008_jr_80135A4C.o,tail4.data.o,ov_SC05_008_jr_80135D20.o,tail5.data.o,ov_SC05_008_jr_801380E0.o,ov_SC05_008_o0c.o,tail6.data.o,ov_SC05_008_jr_8013F350.o,tail7.data.o,ov_SC05_008_jr_8013FFD8.o,tail8.data.o,ov_SC05_008_jr_80140608.o,tail9.data.o,ov_SC05_008_jr_8015444C.o,ov_SC05_008_jr_80154C24.o,ov_SC05_008_jr_801588CC.o,ov_SC05_008_jr_80159C84.o,tail10.data.o,ov_SC05_008_jr_8015A3C8.o,tail11.data.o,ov_SC05_008_jr_8015AE2C.o,tail12.data.o,ov_SC05_008_jr_8015C32C.o,tail13.data.o,ov_SC05_008_jr_8016AB6C.o,tail14.data.o,ov_SC05_008_jr_80171B4C.o,ov_SC05_008_jr_801734BC.o,tail15.data.o,ov_SC05_008_jr_801789AC.o,ov_SC05_008_jr_80178D40.o,tail16.data.o,ov_SC05_008_jr_8017A4AC.o,tail17.data.o,ov_SC05_008_jr_8017AE2C.o,tail18.data.o,trailing.o  # Phase-26 §8 jtbl-rodata carve
build/src/ov_SC05_008/ov_SC05_008.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14
build/src/ov_SC05_008/ov_SC05_008_jr_8012ACE0.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0xcc,+0xe0
build/src/ov_SC05_008/ov_SC05_008_jr_80135D20.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC05_008/ov_SC05_008_jr_8013F350.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC05_008/ov_SC05_008_jr_8013FFD8.o: JTBL_PADS := 0,0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38,+0x58
build/src/ov_SC05_008/ov_SC05_008_jr_8015444C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x70
build/src/ov_SC05_008/ov_SC05_008_jr_80154C24.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x24
build/src/ov_SC05_008/ov_SC05_008_jr_801588CC.o: JTBL_PADS := 0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x28,+0x48
build/src/ov_SC05_008/ov_SC05_008_jr_80159C84.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC05_008/ov_SC05_008_jr_8015AE2C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC05_008/ov_SC05_008_jr_8016AB6C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC05_008/ov_SC05_008_jr_80178D40.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x178
build/src/ov_SC05_008/ov_SC05_008_jr_8017AE2C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14
build/src/ov_SC05_008/ov_SC05_008_o0c.o: JTBL_PADS := 0,4,4,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x38,+0xa8,+0x118
ov_SC05_008_CHECK_SHA  := config/check.ov_SC05_008.sha
ov_SC05_008_SYMBOLS    := config/symbols.ov_SC05_008.txt
ov_SC05_008_SIG        := .run/sig.ov_SC05_008.jsonl
ov_SC05_008_GHIDRA_PROG := ov_SC05_008
ov_SC05_008_VRAM_BASE  := 0x80128158
ov_SC05_008_TEXT_LO    := 0x80128158
ov_SC05_008_TEXT_HI    := 0x801A12EB
ov_SC05_008_ASM_DIR     := asm/ov_SC05_008
ov_SC05_008_SRC_DIR     := src/ov_SC05_008
ov_SC05_008_UNDEF_SYMS  := build/ov_SC05_008/undefined_syms_auto.txt
ov_SC05_008_UNDEF_FUNCS := build/ov_SC05_008/undefined_funcs_auto.txt

# --- ov_SC05_009 (location overlay SC05/FILE_009, vram 0x80128158 — onboarded by new_overlay.sh) ---
ov_SC05_009_EXE        := extracted/retail/SC05.CD.dir/FILE_009.dir/0.4.dec
ov_SC05_009_NAME       := ov_SC05_009
ov_SC05_009_OUT_DIR    := build/ov_SC05_009
ov_SC05_009_OUT        := $(ov_SC05_009_OUT_DIR)/$(ov_SC05_009_NAME)
ov_SC05_009_ELF        := $(ov_SC05_009_OUT).elf
ov_SC05_009_MAPFILE    := $(ov_SC05_009_OUT).map
ov_SC05_009_LD_SCRIPT  := $(ov_SC05_009_OUT).ld
ov_SC05_009_SPLAT_YAML := config/splat.ov_SC05_009.yaml
ov_SC05_009_JTBL_INTERLEAVE := --order tail.data.o,ov_SC05_009.o,ov_SC05_009_jr_8012ACE0.o,tail2.data.o,ov_SC05_009_jr_80135888.o,tail3.data.o,ov_SC05_009_jr_80135A4C.o,tail4.data.o,ov_SC05_009_jr_80135D20.o,tail5.data.o,ov_SC05_009_jr_801380E0.o,ov_SC05_009_o0c.o,tail6.data.o,ov_SC05_009_jr_8013F350.o,tail7.data.o,ov_SC05_009_jr_8013FFD8.o,tail8.data.o,ov_SC05_009_jr_80140608.o,tail9.data.o,ov_SC05_009_jr_8015444C.o,ov_SC05_009_jr_80154C24.o,ov_SC05_009_jr_801588CC.o,ov_SC05_009_jr_80159C84.o,tail10.data.o,ov_SC05_009_jr_8015AE2C.o,tail11.data.o,ov_SC05_009_jr_8015C32C.o,tail12.data.o,ov_SC05_009_jr_8016AB6C.o,tail13.data.o,ov_SC05_009_jr_80171B4C.o,ov_SC05_009_jr_801734BC.o,tail14.data.o,ov_SC05_009_jr_801789AC.o,ov_SC05_009_jr_80178D40.o,tail15.data.o,ov_SC05_009_jr_8017A4AC.o,tail16.data.o,ov_SC05_009_jr_8017AE2C.o,ov_SC05_009_jr_8017BEBC.o,tail17.data.o,trailing.o  # Phase-26 §8 jtbl-rodata carve
build/src/ov_SC05_009/ov_SC05_009.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14
build/src/ov_SC05_009/ov_SC05_009_jr_8012ACE0.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0xcc,+0xe0
build/src/ov_SC05_009/ov_SC05_009_jr_80135D20.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC05_009/ov_SC05_009_jr_8013F350.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC05_009/ov_SC05_009_jr_8013FFD8.o: JTBL_PADS := 0,0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38,+0x58
build/src/ov_SC05_009/ov_SC05_009_jr_8015444C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x70
build/src/ov_SC05_009/ov_SC05_009_jr_80154C24.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x24
build/src/ov_SC05_009/ov_SC05_009_jr_801588CC.o: JTBL_PADS := 0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x28,+0x48
build/src/ov_SC05_009/ov_SC05_009_jr_80159C84.o: JTBL_PADS := 0,4,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38
build/src/ov_SC05_009/ov_SC05_009_jr_8015AE2C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC05_009/ov_SC05_009_jr_8016AB6C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC05_009/ov_SC05_009_jr_80178D40.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x178
build/src/ov_SC05_009/ov_SC05_009_o0c.o: JTBL_PADS := 0,4,4,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x38,+0xa8,+0x118
ov_SC05_009_CHECK_SHA  := config/check.ov_SC05_009.sha
ov_SC05_009_SYMBOLS    := config/symbols.ov_SC05_009.txt
ov_SC05_009_SIG        := .run/sig.ov_SC05_009.jsonl
ov_SC05_009_GHIDRA_PROG := ov_SC05_009
ov_SC05_009_VRAM_BASE  := 0x80128158
ov_SC05_009_TEXT_LO    := 0x80128158
ov_SC05_009_TEXT_HI    := 0x80196C47
ov_SC05_009_ASM_DIR     := asm/ov_SC05_009
ov_SC05_009_SRC_DIR     := src/ov_SC05_009
ov_SC05_009_UNDEF_SYMS  := build/ov_SC05_009/undefined_syms_auto.txt
ov_SC05_009_UNDEF_FUNCS := build/ov_SC05_009/undefined_funcs_auto.txt

# --- ov_SC05_010 (location overlay SC05/FILE_010, vram 0x80128158 — onboarded by new_overlay.sh) ---
ov_SC05_010_EXE        := extracted/retail/SC05.CD.dir/FILE_010.dir/0.4.dec
ov_SC05_010_NAME       := ov_SC05_010
ov_SC05_010_OUT_DIR    := build/ov_SC05_010
ov_SC05_010_OUT        := $(ov_SC05_010_OUT_DIR)/$(ov_SC05_010_NAME)
ov_SC05_010_ELF        := $(ov_SC05_010_OUT).elf
ov_SC05_010_MAPFILE    := $(ov_SC05_010_OUT).map
ov_SC05_010_LD_SCRIPT  := $(ov_SC05_010_OUT).ld
ov_SC05_010_SPLAT_YAML := config/splat.ov_SC05_010.yaml
ov_SC05_010_JTBL_INTERLEAVE := --order tail.data.o,ov_SC05_010.o,ov_SC05_010_jr_8012ACE0.o,tail2.data.o,ov_SC05_010_jr_80135888.o,tail3.data.o,ov_SC05_010_jr_80135A4C.o,tail4.data.o,ov_SC05_010_jr_80135D20.o,tail5.data.o,ov_SC05_010_jr_801380E0.o,ov_SC05_010_o0c.o,tail6.data.o,ov_SC05_010_jr_8013F350.o,tail7.data.o,ov_SC05_010_jr_8013FFD8.o,tail8.data.o,ov_SC05_010_jr_80140608.o,tail9.data.o,ov_SC05_010_jr_8015444C.o,ov_SC05_010_jr_80154C24.o,ov_SC05_010_jr_801588CC.o,ov_SC05_010_jr_80159C84.o,tail10.data.o,ov_SC05_010_jr_8015A3C8.o,tail11.data.o,ov_SC05_010_jr_8015AE2C.o,tail12.data.o,ov_SC05_010_jr_8015C32C.o,tail13.data.o,ov_SC05_010_jr_8016AB6C.o,tail14.data.o,ov_SC05_010_jr_80171B4C.o,ov_SC05_010_jr_801734BC.o,tail15.data.o,ov_SC05_010_jr_801789AC.o,ov_SC05_010_jr_80178D40.o,tail16.data.o,ov_SC05_010_jr_8017A4AC.o,tail17.data.o,ov_SC05_010_jr_8017AE2C.o,tail18.data.o,ov_SC05_010_jr_8017C8D0.o,tail19.data.o,ov_SC05_010_jr_80181CDC.o,tail20.data.o,ov_SC05_010_jr_8018473C.o,tail21.data.o,trailing.o  # Phase-26 §8 jtbl-rodata carve
build/src/ov_SC05_010/ov_SC05_010.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14
build/src/ov_SC05_010/ov_SC05_010_jr_8012ACE0.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0xcc,+0xe0
build/src/ov_SC05_010/ov_SC05_010_jr_80135D20.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC05_010/ov_SC05_010_jr_8013F350.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC05_010/ov_SC05_010_jr_8013FFD8.o: JTBL_PADS := 0,0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38,+0x58
build/src/ov_SC05_010/ov_SC05_010_jr_8015444C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x70
build/src/ov_SC05_010/ov_SC05_010_jr_80154C24.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x24
build/src/ov_SC05_010/ov_SC05_010_jr_801588CC.o: JTBL_PADS := 0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x28,+0x48
build/src/ov_SC05_010/ov_SC05_010_jr_80159C84.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC05_010/ov_SC05_010_jr_8015AE2C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC05_010/ov_SC05_010_jr_8016AB6C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC05_010/ov_SC05_010_jr_80178D40.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x178
build/src/ov_SC05_010/ov_SC05_010_jr_8017C8D0.o: JTBL_PADS := 0,0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x48
build/src/ov_SC05_010/ov_SC05_010_jr_80181CDC.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC05_010/ov_SC05_010_o0c.o: JTBL_PADS := 0,4,4,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x38,+0xa8,+0x118
ov_SC05_010_CHECK_SHA  := config/check.ov_SC05_010.sha
ov_SC05_010_SYMBOLS    := config/symbols.ov_SC05_010.txt
ov_SC05_010_SIG        := .run/sig.ov_SC05_010.jsonl
ov_SC05_010_GHIDRA_PROG := ov_SC05_010
ov_SC05_010_VRAM_BASE  := 0x80128158
ov_SC05_010_TEXT_LO    := 0x80128158
ov_SC05_010_TEXT_HI    := 0x801C802F
ov_SC05_010_ASM_DIR     := asm/ov_SC05_010
ov_SC05_010_SRC_DIR     := src/ov_SC05_010
ov_SC05_010_UNDEF_SYMS  := build/ov_SC05_010/undefined_syms_auto.txt
ov_SC05_010_UNDEF_FUNCS := build/ov_SC05_010/undefined_funcs_auto.txt

# --- ov_SC05_011 (location overlay SC05/FILE_011, vram 0x80128158 — onboarded by new_overlay.sh) ---
ov_SC05_011_EXE        := extracted/retail/SC05.CD.dir/FILE_011.dir/0.4.dec
ov_SC05_011_NAME       := ov_SC05_011
ov_SC05_011_OUT_DIR    := build/ov_SC05_011
ov_SC05_011_OUT        := $(ov_SC05_011_OUT_DIR)/$(ov_SC05_011_NAME)
ov_SC05_011_ELF        := $(ov_SC05_011_OUT).elf
ov_SC05_011_MAPFILE    := $(ov_SC05_011_OUT).map
ov_SC05_011_LD_SCRIPT  := $(ov_SC05_011_OUT).ld
ov_SC05_011_SPLAT_YAML := config/splat.ov_SC05_011.yaml
ov_SC05_011_JTBL_INTERLEAVE := --order tail.data.o,ov_SC05_011.o,ov_SC05_011_jr_8012ACE0.o,tail2.data.o,ov_SC05_011_jr_80135888.o,tail3.data.o,ov_SC05_011_jr_80135A4C.o,tail4.data.o,ov_SC05_011_jr_80135D20.o,tail5.data.o,ov_SC05_011_jr_801380E0.o,ov_SC05_011_o0c.o,tail6.data.o,ov_SC05_011_jr_8013F350.o,tail7.data.o,ov_SC05_011_jr_8013FFD8.o,tail8.data.o,ov_SC05_011_jr_80140608.o,tail9.data.o,ov_SC05_011_jr_8015444C.o,ov_SC05_011_jr_80154C24.o,ov_SC05_011_jr_801588CC.o,ov_SC05_011_jr_80159C84.o,tail10.data.o,ov_SC05_011_jr_8015A3C8.o,tail11.data.o,ov_SC05_011_jr_8015AE2C.o,tail12.data.o,ov_SC05_011_jr_8015C32C.o,tail13.data.o,ov_SC05_011_jr_8016AB6C.o,tail14.data.o,ov_SC05_011_jr_80171B4C.o,ov_SC05_011_jr_801734BC.o,tail15.data.o,ov_SC05_011_jr_801789AC.o,ov_SC05_011_jr_80178D40.o,tail16.data.o,ov_SC05_011_jr_8017A4AC.o,tail17.data.o,ov_SC05_011_jr_8017AE2C.o,ov_SC05_011_jr_8017BEBC.o,tail18.data.o,trailing.o  # Phase-26 §8 jtbl-rodata carve
build/src/ov_SC05_011/ov_SC05_011.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14
build/src/ov_SC05_011/ov_SC05_011_jr_8012ACE0.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0xcc,+0xe0
build/src/ov_SC05_011/ov_SC05_011_jr_80135D20.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC05_011/ov_SC05_011_jr_8013F350.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC05_011/ov_SC05_011_jr_8013FFD8.o: JTBL_PADS := 0,0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38,+0x58
build/src/ov_SC05_011/ov_SC05_011_jr_8015444C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x70
build/src/ov_SC05_011/ov_SC05_011_jr_80154C24.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x24
build/src/ov_SC05_011/ov_SC05_011_jr_801588CC.o: JTBL_PADS := 0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x28,+0x48
build/src/ov_SC05_011/ov_SC05_011_jr_80159C84.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC05_011/ov_SC05_011_jr_8015AE2C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC05_011/ov_SC05_011_jr_8016AB6C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC05_011/ov_SC05_011_jr_80178D40.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x178
build/src/ov_SC05_011/ov_SC05_011_jr_8017BEBC.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x40
build/src/ov_SC05_011/ov_SC05_011_o0c.o: JTBL_PADS := 0,4,4,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x38,+0xa8,+0x118
ov_SC05_011_CHECK_SHA  := config/check.ov_SC05_011.sha
ov_SC05_011_SYMBOLS    := config/symbols.ov_SC05_011.txt
ov_SC05_011_SIG        := .run/sig.ov_SC05_011.jsonl
ov_SC05_011_GHIDRA_PROG := ov_SC05_011
ov_SC05_011_VRAM_BASE  := 0x80128158
ov_SC05_011_TEXT_LO    := 0x80128158
ov_SC05_011_TEXT_HI    := 0x8019D1DF
ov_SC05_011_ASM_DIR     := asm/ov_SC05_011
ov_SC05_011_SRC_DIR     := src/ov_SC05_011
ov_SC05_011_UNDEF_SYMS  := build/ov_SC05_011/undefined_syms_auto.txt
ov_SC05_011_UNDEF_FUNCS := build/ov_SC05_011/undefined_funcs_auto.txt

# --- ov_SC05_017 (location overlay SC05/FILE_017, vram 0x80128158 — onboarded by new_overlay.sh) ---
ov_SC05_017_EXE        := extracted/retail/SC05.CD.dir/FILE_017.dir/0.4.dec
ov_SC05_017_NAME       := ov_SC05_017
ov_SC05_017_OUT_DIR    := build/ov_SC05_017
ov_SC05_017_OUT        := $(ov_SC05_017_OUT_DIR)/$(ov_SC05_017_NAME)
ov_SC05_017_ELF        := $(ov_SC05_017_OUT).elf
ov_SC05_017_MAPFILE    := $(ov_SC05_017_OUT).map
ov_SC05_017_LD_SCRIPT  := $(ov_SC05_017_OUT).ld
ov_SC05_017_SPLAT_YAML := config/splat.ov_SC05_017.yaml
ov_SC05_017_JTBL_INTERLEAVE := --order tail.data.o,ov_SC05_017.o,ov_SC05_017_jr_8012ACE0.o,tail2.data.o,ov_SC05_017_jr_80135888.o,tail3.data.o,ov_SC05_017_jr_80135A4C.o,tail4.data.o,ov_SC05_017_jr_80135D20.o,tail5.data.o,ov_SC05_017_jr_801380E0.o,ov_SC05_017_o0c.o,tail6.data.o,ov_SC05_017_jr_8013F350.o,tail7.data.o,ov_SC05_017_jr_8013FFD8.o,tail8.data.o,ov_SC05_017_jr_80140608.o,tail9.data.o,ov_SC05_017_jr_8015444C.o,ov_SC05_017_jr_80154C24.o,ov_SC05_017_jr_801588CC.o,ov_SC05_017_jr_80159C84.o,tail10.data.o,ov_SC05_017_jr_8015A3C8.o,tail11.data.o,ov_SC05_017_jr_8015AE2C.o,tail12.data.o,ov_SC05_017_jr_8015C32C.o,tail13.data.o,ov_SC05_017_jr_8016AB6C.o,tail14.data.o,ov_SC05_017_jr_80171B4C.o,ov_SC05_017_jr_801734BC.o,tail15.data.o,ov_SC05_017_jr_801789AC.o,ov_SC05_017_jr_80178D40.o,tail16.data.o,ov_SC05_017_jr_8017A4AC.o,tail17.data.o,ov_SC05_017_jr_8017AE2C.o,tail18.data.o,ov_SC05_017_jr_801808D4.o,ov_SC05_017_jr_801828EC.o,tail19.data.o,ov_SC05_017_jr_80182A74.o,ov_SC05_017_jr_80185A70.o,tail20.data.o,ov_SC05_017_jr_80186270.o,tail21.data.o,ov_SC05_017_jr_801875E8.o,ov_SC05_017_jr_80188B1C.o,ov_SC05_017_jr_8018C694.o,tail22.data.o,trailing.o  # Phase-26 §8 jtbl-rodata carve
build/src/ov_SC05_017/ov_SC05_017.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14
build/src/ov_SC05_017/ov_SC05_017_jr_8012ACE0.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0xcc,+0xe0
build/src/ov_SC05_017/ov_SC05_017_jr_80135D20.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC05_017/ov_SC05_017_jr_8013F350.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC05_017/ov_SC05_017_jr_8013FFD8.o: JTBL_PADS := 0,0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38,+0x58
build/src/ov_SC05_017/ov_SC05_017_jr_8015444C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x70
build/src/ov_SC05_017/ov_SC05_017_jr_80154C24.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x24
build/src/ov_SC05_017/ov_SC05_017_jr_801588CC.o: JTBL_PADS := 0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x28,+0x48
build/src/ov_SC05_017/ov_SC05_017_jr_80159C84.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC05_017/ov_SC05_017_jr_8015AE2C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC05_017/ov_SC05_017_jr_8016AB6C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC05_017/ov_SC05_017_jr_80178D40.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x178
build/src/ov_SC05_017/ov_SC05_017_jr_8017AE2C.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14,+0x34
build/src/ov_SC05_017/ov_SC05_017_jr_80182A74.o: JTBL_PADS := 0,0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14,+0x2c
build/src/ov_SC05_017/ov_SC05_017_jr_801875E8.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x38
build/src/ov_SC05_017/ov_SC05_017_jr_80188B1C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC05_017/ov_SC05_017_o0c.o: JTBL_PADS := 0,4,4,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x38,+0xa8,+0x118
ov_SC05_017_CHECK_SHA  := config/check.ov_SC05_017.sha
ov_SC05_017_SYMBOLS    := config/symbols.ov_SC05_017.txt
ov_SC05_017_SIG        := .run/sig.ov_SC05_017.jsonl
ov_SC05_017_GHIDRA_PROG := ov_SC05_017
ov_SC05_017_VRAM_BASE  := 0x80128158
ov_SC05_017_TEXT_LO    := 0x80128158
ov_SC05_017_TEXT_HI    := 0x801ED987
ov_SC05_017_ASM_DIR     := asm/ov_SC05_017
ov_SC05_017_SRC_DIR     := src/ov_SC05_017
ov_SC05_017_UNDEF_SYMS  := build/ov_SC05_017/undefined_syms_auto.txt
ov_SC05_017_UNDEF_FUNCS := build/ov_SC05_017/undefined_funcs_auto.txt

# --- ov_SC05_018 (location overlay SC05/FILE_018, vram 0x80128158 — onboarded by new_overlay.sh) ---
ov_SC05_018_EXE        := extracted/retail/SC05.CD.dir/FILE_018.dir/0.4.dec
ov_SC05_018_NAME       := ov_SC05_018
ov_SC05_018_OUT_DIR    := build/ov_SC05_018
ov_SC05_018_OUT        := $(ov_SC05_018_OUT_DIR)/$(ov_SC05_018_NAME)
ov_SC05_018_ELF        := $(ov_SC05_018_OUT).elf
ov_SC05_018_MAPFILE    := $(ov_SC05_018_OUT).map
ov_SC05_018_LD_SCRIPT  := $(ov_SC05_018_OUT).ld
ov_SC05_018_SPLAT_YAML := config/splat.ov_SC05_018.yaml
ov_SC05_018_JTBL_INTERLEAVE := --order tail.data.o,ov_SC05_018.o,ov_SC05_018_jr_8012ACE0.o,tail2.data.o,ov_SC05_018_jr_80135888.o,tail3.data.o,ov_SC05_018_jr_80135A4C.o,tail4.data.o,ov_SC05_018_jr_80135D20.o,tail5.data.o,ov_SC05_018_jr_801380E0.o,ov_SC05_018_o0c.o,tail6.data.o,ov_SC05_018_jr_8013F350.o,tail7.data.o,ov_SC05_018_jr_8013FFD8.o,tail8.data.o,ov_SC05_018_jr_80140608.o,tail9.data.o,ov_SC05_018_jr_8015444C.o,ov_SC05_018_jr_80154C24.o,ov_SC05_018_jr_801588CC.o,ov_SC05_018_jr_80159C84.o,tail10.data.o,ov_SC05_018_jr_8015A3C8.o,tail11.data.o,ov_SC05_018_jr_8015AE2C.o,tail12.data.o,ov_SC05_018_jr_8015C32C.o,tail13.data.o,ov_SC05_018_jr_8016AB6C.o,tail14.data.o,ov_SC05_018_jr_80171B4C.o,ov_SC05_018_jr_801734BC.o,tail15.data.o,ov_SC05_018_jr_801789AC.o,ov_SC05_018_jr_80178D40.o,tail16.data.o,ov_SC05_018_jr_8017A4AC.o,tail17.data.o,ov_SC05_018_jr_8017AE2C.o,ov_SC05_018_jr_8017D604.o,tail18.data.o,ov_SC05_018_jr_80185754.o,tail19.data.o,trailing.o  # Phase-26 §8 jtbl-rodata carve
build/src/ov_SC05_018/ov_SC05_018.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14
build/src/ov_SC05_018/ov_SC05_018_jr_8012ACE0.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0xcc,+0xe0
build/src/ov_SC05_018/ov_SC05_018_jr_80135D20.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC05_018/ov_SC05_018_jr_8013F350.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC05_018/ov_SC05_018_jr_8013FFD8.o: JTBL_PADS := 0,0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38,+0x58
build/src/ov_SC05_018/ov_SC05_018_jr_8015444C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x70
build/src/ov_SC05_018/ov_SC05_018_jr_80154C24.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x24
build/src/ov_SC05_018/ov_SC05_018_jr_801588CC.o: JTBL_PADS := 0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x28,+0x48
build/src/ov_SC05_018/ov_SC05_018_jr_80159C84.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC05_018/ov_SC05_018_jr_8015AE2C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC05_018/ov_SC05_018_jr_8016AB6C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC05_018/ov_SC05_018_jr_80178D40.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x178
build/src/ov_SC05_018/ov_SC05_018_jr_8017D604.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC05_018/ov_SC05_018_jr_80185754.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x1c
build/src/ov_SC05_018/ov_SC05_018_o0c.o: JTBL_PADS := 0,4,4,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x38,+0xa8,+0x118
ov_SC05_018_CHECK_SHA  := config/check.ov_SC05_018.sha
ov_SC05_018_SYMBOLS    := config/symbols.ov_SC05_018.txt
ov_SC05_018_SIG        := .run/sig.ov_SC05_018.jsonl
ov_SC05_018_GHIDRA_PROG := ov_SC05_018
ov_SC05_018_VRAM_BASE  := 0x80128158
ov_SC05_018_TEXT_LO    := 0x80128158
ov_SC05_018_TEXT_HI    := 0x801E688F
ov_SC05_018_ASM_DIR     := asm/ov_SC05_018
ov_SC05_018_SRC_DIR     := src/ov_SC05_018
ov_SC05_018_UNDEF_SYMS  := build/ov_SC05_018/undefined_syms_auto.txt
ov_SC05_018_UNDEF_FUNCS := build/ov_SC05_018/undefined_funcs_auto.txt

# --- ov_SC05_019 (location overlay SC05/FILE_019, vram 0x80128158 — onboarded by new_overlay.sh) ---
ov_SC05_019_EXE        := extracted/retail/SC05.CD.dir/FILE_019.dir/0.4.dec
ov_SC05_019_NAME       := ov_SC05_019
ov_SC05_019_OUT_DIR    := build/ov_SC05_019
ov_SC05_019_OUT        := $(ov_SC05_019_OUT_DIR)/$(ov_SC05_019_NAME)
ov_SC05_019_ELF        := $(ov_SC05_019_OUT).elf
ov_SC05_019_MAPFILE    := $(ov_SC05_019_OUT).map
ov_SC05_019_LD_SCRIPT  := $(ov_SC05_019_OUT).ld
ov_SC05_019_SPLAT_YAML := config/splat.ov_SC05_019.yaml
ov_SC05_019_JTBL_INTERLEAVE := --order tail.data.o,ov_SC05_019.o,ov_SC05_019_jr_8012ACE0.o,tail2.data.o,ov_SC05_019_jr_80135888.o,tail3.data.o,ov_SC05_019_jr_80135A4C.o,tail4.data.o,ov_SC05_019_jr_80135D20.o,tail5.data.o,ov_SC05_019_jr_801380E0.o,ov_SC05_019_o0c.o,tail6.data.o,ov_SC05_019_jr_8013F350.o,tail7.data.o,ov_SC05_019_jr_8013FFD8.o,tail8.data.o,ov_SC05_019_jr_80140608.o,tail9.data.o,ov_SC05_019_jr_8015444C.o,ov_SC05_019_jr_80154C24.o,ov_SC05_019_jr_801588CC.o,ov_SC05_019_jr_80159C84.o,tail10.data.o,ov_SC05_019_jr_8015A3C8.o,tail11.data.o,ov_SC05_019_jr_8015AE2C.o,tail12.data.o,ov_SC05_019_jr_8015C32C.o,tail13.data.o,ov_SC05_019_jr_8016AB6C.o,tail14.data.o,ov_SC05_019_jr_80171B4C.o,ov_SC05_019_jr_801734BC.o,tail15.data.o,ov_SC05_019_jr_801789AC.o,ov_SC05_019_jr_80178D40.o,tail16.data.o,ov_SC05_019_jr_8017A4AC.o,tail17.data.o,ov_SC05_019_jr_8017AE2C.o,ov_SC05_019_jr_8017D5C0.o,tail18.data.o,trailing.o  # Phase-26 §8 jtbl-rodata carve
build/src/ov_SC05_019/ov_SC05_019.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14
build/src/ov_SC05_019/ov_SC05_019_jr_8012ACE0.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0xcc,+0xe0
build/src/ov_SC05_019/ov_SC05_019_jr_80135D20.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC05_019/ov_SC05_019_jr_8013F350.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC05_019/ov_SC05_019_jr_8013FFD8.o: JTBL_PADS := 0,0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38,+0x58
build/src/ov_SC05_019/ov_SC05_019_jr_8015444C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x70
build/src/ov_SC05_019/ov_SC05_019_jr_80154C24.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x24
build/src/ov_SC05_019/ov_SC05_019_jr_801588CC.o: JTBL_PADS := 0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x28,+0x48
build/src/ov_SC05_019/ov_SC05_019_jr_80159C84.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC05_019/ov_SC05_019_jr_8015AE2C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC05_019/ov_SC05_019_jr_8016AB6C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC05_019/ov_SC05_019_jr_80178D40.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x178
build/src/ov_SC05_019/ov_SC05_019_jr_8017AE2C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14
build/src/ov_SC05_019/ov_SC05_019_o0c.o: JTBL_PADS := 0,4,4,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x38,+0xa8,+0x118
ov_SC05_019_CHECK_SHA  := config/check.ov_SC05_019.sha
ov_SC05_019_SYMBOLS    := config/symbols.ov_SC05_019.txt
ov_SC05_019_SIG        := .run/sig.ov_SC05_019.jsonl
ov_SC05_019_GHIDRA_PROG := ov_SC05_019
ov_SC05_019_VRAM_BASE  := 0x80128158
ov_SC05_019_TEXT_LO    := 0x80128158
ov_SC05_019_TEXT_HI    := 0x8018FB2D
ov_SC05_019_ASM_DIR     := asm/ov_SC05_019
ov_SC05_019_SRC_DIR     := src/ov_SC05_019
ov_SC05_019_UNDEF_SYMS  := build/ov_SC05_019/undefined_syms_auto.txt
ov_SC05_019_UNDEF_FUNCS := build/ov_SC05_019/undefined_funcs_auto.txt

# --- ov_SC06_006 (location overlay SC06/FILE_006, vram 0x80128158 — onboarded by new_overlay.sh) ---
ov_SC06_006_EXE        := extracted/retail/SC06.CD.dir/FILE_006.dir/0.4.dec
ov_SC06_006_NAME       := ov_SC06_006
ov_SC06_006_OUT_DIR    := build/ov_SC06_006
ov_SC06_006_OUT        := $(ov_SC06_006_OUT_DIR)/$(ov_SC06_006_NAME)
ov_SC06_006_ELF        := $(ov_SC06_006_OUT).elf
ov_SC06_006_MAPFILE    := $(ov_SC06_006_OUT).map
ov_SC06_006_LD_SCRIPT  := $(ov_SC06_006_OUT).ld
ov_SC06_006_SPLAT_YAML := config/splat.ov_SC06_006.yaml
ov_SC06_006_JTBL_INTERLEAVE := --order tail.data.o,ov_SC06_006.o,ov_SC06_006_jr_8012ACE0.o,tail2.data.o,ov_SC06_006_jr_80135888.o,tail3.data.o,ov_SC06_006_jr_80135A4C.o,tail4.data.o,ov_SC06_006_jr_80135D20.o,tail5.data.o,ov_SC06_006_jr_801380E0.o,ov_SC06_006_o0c.o,tail6.data.o,ov_SC06_006_jr_8013F350.o,tail7.data.o,ov_SC06_006_jr_8013FFD8.o,tail8.data.o,ov_SC06_006_jr_80140608.o,tail9.data.o,ov_SC06_006_jr_8015444C.o,ov_SC06_006_jr_80154C24.o,ov_SC06_006_jr_801588CC.o,ov_SC06_006_jr_80159C84.o,tail10.data.o,ov_SC06_006_jr_8015A3C8.o,tail11.data.o,ov_SC06_006_jr_8015AE2C.o,tail12.data.o,ov_SC06_006_jr_8015C32C.o,tail13.data.o,ov_SC06_006_jr_8016AB6C.o,tail14.data.o,ov_SC06_006_jr_80171B4C.o,ov_SC06_006_jr_801734BC.o,tail15.data.o,ov_SC06_006_jr_801789AC.o,ov_SC06_006_jr_80178D40.o,tail16.data.o,ov_SC06_006_jr_8017A4AC.o,tail17.data.o,ov_SC06_006_jr_8017AE2C.o,ov_SC06_006_jr_8017BEBC.o,tail18.data.o,ov_SC06_006_jr_8017DB90.o,tail19.data.o,trailing.o  # Phase-26 §8 jtbl-rodata carve
build/src/ov_SC06_006/ov_SC06_006.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14
build/src/ov_SC06_006/ov_SC06_006_jr_8012ACE0.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0xcc,+0xe0
build/src/ov_SC06_006/ov_SC06_006_jr_80135D20.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC06_006/ov_SC06_006_jr_8013F350.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC06_006/ov_SC06_006_jr_8013FFD8.o: JTBL_PADS := 0,0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38,+0x58
build/src/ov_SC06_006/ov_SC06_006_jr_8015444C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x70
build/src/ov_SC06_006/ov_SC06_006_jr_80154C24.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x24
build/src/ov_SC06_006/ov_SC06_006_jr_801588CC.o: JTBL_PADS := 0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x28,+0x48
build/src/ov_SC06_006/ov_SC06_006_jr_80159C84.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC06_006/ov_SC06_006_jr_8015AE2C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC06_006/ov_SC06_006_jr_8016AB6C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC06_006/ov_SC06_006_jr_80178D40.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x178
build/src/ov_SC06_006/ov_SC06_006_o0c.o: JTBL_PADS := 0,4,4,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x38,+0xa8,+0x118
ov_SC06_006_CHECK_SHA  := config/check.ov_SC06_006.sha
ov_SC06_006_SYMBOLS    := config/symbols.ov_SC06_006.txt
ov_SC06_006_SIG        := .run/sig.ov_SC06_006.jsonl
ov_SC06_006_GHIDRA_PROG := ov_SC06_006
ov_SC06_006_VRAM_BASE  := 0x80128158
ov_SC06_006_TEXT_LO    := 0x80128158
ov_SC06_006_TEXT_HI    := 0x801F8B67
ov_SC06_006_ASM_DIR     := asm/ov_SC06_006
ov_SC06_006_SRC_DIR     := src/ov_SC06_006
ov_SC06_006_UNDEF_SYMS  := build/ov_SC06_006/undefined_syms_auto.txt
ov_SC06_006_UNDEF_FUNCS := build/ov_SC06_006/undefined_funcs_auto.txt

# --- ov_SC06_008 (location overlay SC06/FILE_008, vram 0x80128158 — onboarded by new_overlay.sh) ---
ov_SC06_008_EXE        := extracted/retail/SC06.CD.dir/FILE_008.dir/0.4.dec
ov_SC06_008_NAME       := ov_SC06_008
ov_SC06_008_OUT_DIR    := build/ov_SC06_008
ov_SC06_008_OUT        := $(ov_SC06_008_OUT_DIR)/$(ov_SC06_008_NAME)
ov_SC06_008_ELF        := $(ov_SC06_008_OUT).elf
ov_SC06_008_MAPFILE    := $(ov_SC06_008_OUT).map
ov_SC06_008_LD_SCRIPT  := $(ov_SC06_008_OUT).ld
ov_SC06_008_SPLAT_YAML := config/splat.ov_SC06_008.yaml
ov_SC06_008_JTBL_INTERLEAVE := --order tail.data.o,ov_SC06_008.o,ov_SC06_008_jr_8012ACE0.o,tail2.data.o,ov_SC06_008_jr_80135888.o,tail3.data.o,ov_SC06_008_jr_80135A4C.o,tail4.data.o,ov_SC06_008_jr_80135D20.o,tail5.data.o,ov_SC06_008_jr_801380E0.o,ov_SC06_008_o0c.o,tail6.data.o,ov_SC06_008_jr_8013F350.o,tail7.data.o,ov_SC06_008_jr_8013FFD8.o,tail8.data.o,ov_SC06_008_jr_80140608.o,tail9.data.o,ov_SC06_008_jr_8015444C.o,ov_SC06_008_jr_80154C24.o,ov_SC06_008_jr_801588CC.o,ov_SC06_008_jr_80159C84.o,tail10.data.o,ov_SC06_008_jr_8015A3C8.o,tail11.data.o,ov_SC06_008_jr_8015AE2C.o,tail12.data.o,ov_SC06_008_jr_8015C32C.o,tail13.data.o,ov_SC06_008_jr_8016AB6C.o,tail14.data.o,ov_SC06_008_jr_80171B4C.o,ov_SC06_008_jr_801734BC.o,tail15.data.o,ov_SC06_008_jr_801789AC.o,ov_SC06_008_jr_80178D40.o,tail16.data.o,ov_SC06_008_jr_8017A4AC.o,tail17.data.o,ov_SC06_008_jr_8017AE2C.o,ov_SC06_008_jr_8017C294.o,tail18.data.o,trailing.o  # Phase-26 §8 jtbl-rodata carve
build/src/ov_SC06_008/ov_SC06_008.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14
build/src/ov_SC06_008/ov_SC06_008_jr_8012ACE0.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0xcc,+0xe0
build/src/ov_SC06_008/ov_SC06_008_jr_80135D20.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC06_008/ov_SC06_008_jr_8013F350.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC06_008/ov_SC06_008_jr_8013FFD8.o: JTBL_PADS := 0,0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38,+0x58
build/src/ov_SC06_008/ov_SC06_008_jr_8015444C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x70
build/src/ov_SC06_008/ov_SC06_008_jr_80154C24.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x24
build/src/ov_SC06_008/ov_SC06_008_jr_801588CC.o: JTBL_PADS := 0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x28,+0x48
build/src/ov_SC06_008/ov_SC06_008_jr_80159C84.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC06_008/ov_SC06_008_jr_8015AE2C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC06_008/ov_SC06_008_jr_8016AB6C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC06_008/ov_SC06_008_jr_80178D40.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x178
build/src/ov_SC06_008/ov_SC06_008_o0c.o: JTBL_PADS := 0,4,4,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x38,+0xa8,+0x118
ov_SC06_008_CHECK_SHA  := config/check.ov_SC06_008.sha
ov_SC06_008_SYMBOLS    := config/symbols.ov_SC06_008.txt
ov_SC06_008_SIG        := .run/sig.ov_SC06_008.jsonl
ov_SC06_008_GHIDRA_PROG := ov_SC06_008
ov_SC06_008_VRAM_BASE  := 0x80128158
ov_SC06_008_TEXT_LO    := 0x80128158
ov_SC06_008_TEXT_HI    := 0x801AA837
ov_SC06_008_ASM_DIR     := asm/ov_SC06_008
ov_SC06_008_SRC_DIR     := src/ov_SC06_008
ov_SC06_008_UNDEF_SYMS  := build/ov_SC06_008/undefined_syms_auto.txt
ov_SC06_008_UNDEF_FUNCS := build/ov_SC06_008/undefined_funcs_auto.txt

# --- ov_SC06_010 (location overlay SC06/FILE_010, vram 0x80128158 — onboarded by new_overlay.sh) ---
ov_SC06_010_EXE        := extracted/retail/SC06.CD.dir/FILE_010.dir/0.4.dec
ov_SC06_010_NAME       := ov_SC06_010
ov_SC06_010_OUT_DIR    := build/ov_SC06_010
ov_SC06_010_OUT        := $(ov_SC06_010_OUT_DIR)/$(ov_SC06_010_NAME)
ov_SC06_010_ELF        := $(ov_SC06_010_OUT).elf
ov_SC06_010_MAPFILE    := $(ov_SC06_010_OUT).map
ov_SC06_010_LD_SCRIPT  := $(ov_SC06_010_OUT).ld
ov_SC06_010_SPLAT_YAML := config/splat.ov_SC06_010.yaml
ov_SC06_010_JTBL_INTERLEAVE := --order tail.data.o,ov_SC06_010.o,ov_SC06_010_jr_8012ACE0.o,tail2.data.o,ov_SC06_010_jr_80135888.o,tail3.data.o,ov_SC06_010_jr_80135A4C.o,tail4.data.o,ov_SC06_010_jr_80135D20.o,tail5.data.o,ov_SC06_010_jr_801380E0.o,ov_SC06_010_o0c.o,tail6.data.o,ov_SC06_010_jr_8013F350.o,tail7.data.o,ov_SC06_010_jr_8014032C.o,tail8.data.o,ov_SC06_010_jr_80140608.o,tail9.data.o,ov_SC06_010_jr_8015444C.o,ov_SC06_010_jr_80154C24.o,ov_SC06_010_jr_801588CC.o,ov_SC06_010_jr_80159C84.o,tail10.data.o,ov_SC06_010_jr_8015A3C8.o,tail11.data.o,ov_SC06_010_jr_8015AE2C.o,tail12.data.o,ov_SC06_010_jr_8015C32C.o,tail13.data.o,ov_SC06_010_jr_8016AB6C.o,tail14.data.o,ov_SC06_010_jr_80171B4C.o,ov_SC06_010_jr_801734BC.o,tail15.data.o,ov_SC06_010_jr_801789AC.o,ov_SC06_010_jr_80178D40.o,tail16.data.o,ov_SC06_010_jr_8017A4AC.o,tail17.data.o,trailing.o  # Phase-26 §8 jtbl-rodata carve
build/src/ov_SC06_010/ov_SC06_010.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14
build/src/ov_SC06_010/ov_SC06_010_jr_8012ACE0.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0xcc,+0xe0
build/src/ov_SC06_010/ov_SC06_010_jr_80135D20.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC06_010/ov_SC06_010_jr_8013F350.o: JTBL_PADS := 0,0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38,+0x58
build/src/ov_SC06_010/ov_SC06_010_jr_8014032C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC06_010/ov_SC06_010_jr_8015444C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x70
build/src/ov_SC06_010/ov_SC06_010_jr_80154C24.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x24
build/src/ov_SC06_010/ov_SC06_010_jr_801588CC.o: JTBL_PADS := 0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x28,+0x48
build/src/ov_SC06_010/ov_SC06_010_jr_80159C84.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC06_010/ov_SC06_010_jr_8015AE2C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC06_010/ov_SC06_010_jr_8016AB6C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC06_010/ov_SC06_010_jr_80178D40.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x178
build/src/ov_SC06_010/ov_SC06_010_jr_8017A4AC.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x90
build/src/ov_SC06_010/ov_SC06_010_o0c.o: JTBL_PADS := 0,4,4,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x38,+0xa8,+0x118
ov_SC06_010_CHECK_SHA  := config/check.ov_SC06_010.sha
ov_SC06_010_SYMBOLS    := config/symbols.ov_SC06_010.txt
ov_SC06_010_SIG        := .run/sig.ov_SC06_010.jsonl
ov_SC06_010_GHIDRA_PROG := ov_SC06_010
ov_SC06_010_VRAM_BASE  := 0x80128158
ov_SC06_010_TEXT_LO    := 0x80128158
ov_SC06_010_TEXT_HI    := 0x801B2C7F
ov_SC06_010_ASM_DIR     := asm/ov_SC06_010
ov_SC06_010_SRC_DIR     := src/ov_SC06_010
ov_SC06_010_UNDEF_SYMS  := build/ov_SC06_010/undefined_syms_auto.txt
ov_SC06_010_UNDEF_FUNCS := build/ov_SC06_010/undefined_funcs_auto.txt

# --- ov_SC06_011 (location overlay SC06/FILE_011, vram 0x80128158 — onboarded by new_overlay.sh) ---
ov_SC06_011_EXE        := extracted/retail/SC06.CD.dir/FILE_011.dir/0.4.dec
ov_SC06_011_NAME       := ov_SC06_011
ov_SC06_011_OUT_DIR    := build/ov_SC06_011
ov_SC06_011_OUT        := $(ov_SC06_011_OUT_DIR)/$(ov_SC06_011_NAME)
ov_SC06_011_ELF        := $(ov_SC06_011_OUT).elf
ov_SC06_011_MAPFILE    := $(ov_SC06_011_OUT).map
ov_SC06_011_LD_SCRIPT  := $(ov_SC06_011_OUT).ld
ov_SC06_011_SPLAT_YAML := config/splat.ov_SC06_011.yaml
ov_SC06_011_JTBL_INTERLEAVE := --order tail.data.o,ov_SC06_011.o,ov_SC06_011_jr_8012ACE0.o,tail2.data.o,ov_SC06_011_jr_80135888.o,tail3.data.o,ov_SC06_011_jr_80135A4C.o,tail4.data.o,ov_SC06_011_jr_80135D20.o,tail5.data.o,ov_SC06_011_jr_801380E0.o,ov_SC06_011_o0c.o,tail6.data.o,ov_SC06_011_jr_8013F350.o,tail7.data.o,ov_SC06_011_jr_8013FFD8.o,tail8.data.o,ov_SC06_011_jr_80140608.o,tail9.data.o,ov_SC06_011_jr_8015444C.o,ov_SC06_011_jr_80154C24.o,ov_SC06_011_jr_801588CC.o,ov_SC06_011_jr_80159C84.o,tail10.data.o,ov_SC06_011_jr_8015A3C8.o,tail11.data.o,ov_SC06_011_jr_8015AE2C.o,tail12.data.o,ov_SC06_011_jr_8015C32C.o,tail13.data.o,ov_SC06_011_jr_8016AB6C.o,tail14.data.o,ov_SC06_011_jr_80171B4C.o,ov_SC06_011_jr_801734BC.o,tail15.data.o,ov_SC06_011_jr_801789AC.o,ov_SC06_011_jr_80178D40.o,tail16.data.o,ov_SC06_011_jr_8017A4AC.o,tail17.data.o,ov_SC06_011_jr_8017AE2C.o,ov_SC06_011_jr_8017BEBC.o,ov_SC06_011_jr_8017EEEC.o,tail18.data.o,trailing.o  # Phase-26 §8 jtbl-rodata carve
build/src/ov_SC06_011/ov_SC06_011.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14
build/src/ov_SC06_011/ov_SC06_011_jr_8012ACE0.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0xcc,+0xe0
build/src/ov_SC06_011/ov_SC06_011_jr_80135D20.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC06_011/ov_SC06_011_jr_8013F350.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC06_011/ov_SC06_011_jr_8013FFD8.o: JTBL_PADS := 0,0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38,+0x58
build/src/ov_SC06_011/ov_SC06_011_jr_8015444C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x70
build/src/ov_SC06_011/ov_SC06_011_jr_80154C24.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x24
build/src/ov_SC06_011/ov_SC06_011_jr_801588CC.o: JTBL_PADS := 0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x28,+0x48
build/src/ov_SC06_011/ov_SC06_011_jr_80159C84.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC06_011/ov_SC06_011_jr_8015AE2C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC06_011/ov_SC06_011_jr_8016AB6C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC06_011/ov_SC06_011_jr_80178D40.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x178
build/src/ov_SC06_011/ov_SC06_011_jr_8017BEBC.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py)
build/src/ov_SC06_011/ov_SC06_011_o0c.o: JTBL_PADS := 0,4,4,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x38,+0xa8,+0x118
ov_SC06_011_CHECK_SHA  := config/check.ov_SC06_011.sha
ov_SC06_011_SYMBOLS    := config/symbols.ov_SC06_011.txt
ov_SC06_011_SIG        := .run/sig.ov_SC06_011.jsonl
ov_SC06_011_GHIDRA_PROG := ov_SC06_011
ov_SC06_011_VRAM_BASE  := 0x80128158
ov_SC06_011_TEXT_LO    := 0x80128158
ov_SC06_011_TEXT_HI    := 0x801ABD57
ov_SC06_011_ASM_DIR     := asm/ov_SC06_011
ov_SC06_011_SRC_DIR     := src/ov_SC06_011
ov_SC06_011_UNDEF_SYMS  := build/ov_SC06_011/undefined_syms_auto.txt
ov_SC06_011_UNDEF_FUNCS := build/ov_SC06_011/undefined_funcs_auto.txt

# --- ov_SC06_013 (location overlay SC06/FILE_013, vram 0x80128158 — onboarded by new_overlay.sh) ---
ov_SC06_013_EXE        := extracted/retail/SC06.CD.dir/FILE_013.dir/0.4.dec
ov_SC06_013_NAME       := ov_SC06_013
ov_SC06_013_OUT_DIR    := build/ov_SC06_013
ov_SC06_013_OUT        := $(ov_SC06_013_OUT_DIR)/$(ov_SC06_013_NAME)
ov_SC06_013_ELF        := $(ov_SC06_013_OUT).elf
ov_SC06_013_MAPFILE    := $(ov_SC06_013_OUT).map
ov_SC06_013_LD_SCRIPT  := $(ov_SC06_013_OUT).ld
ov_SC06_013_SPLAT_YAML := config/splat.ov_SC06_013.yaml
ov_SC06_013_JTBL_INTERLEAVE := --order tail.data.o,ov_SC06_013.o,ov_SC06_013_jr_8012ACE0.o,tail2.data.o,ov_SC06_013_jr_80135888.o,tail3.data.o,ov_SC06_013_jr_80135A4C.o,tail4.data.o,ov_SC06_013_jr_80135D20.o,tail5.data.o,ov_SC06_013_jr_801380E0.o,ov_SC06_013_o0c.o,tail6.data.o,ov_SC06_013_jr_8013F350.o,tail7.data.o,ov_SC06_013_jr_8013FFD8.o,tail8.data.o,ov_SC06_013_jr_80140608.o,tail9.data.o,ov_SC06_013_jr_8015444C.o,ov_SC06_013_jr_80154C24.o,ov_SC06_013_jr_801588CC.o,ov_SC06_013_jr_80159C84.o,tail10.data.o,ov_SC06_013_jr_8015A3C8.o,tail11.data.o,ov_SC06_013_jr_8015AE2C.o,tail12.data.o,ov_SC06_013_jr_8015C32C.o,tail13.data.o,ov_SC06_013_jr_8016AB6C.o,tail14.data.o,ov_SC06_013_jr_80171B4C.o,ov_SC06_013_jr_801734BC.o,tail15.data.o,ov_SC06_013_jr_801789AC.o,ov_SC06_013_jr_80178D40.o,tail16.data.o,ov_SC06_013_jr_8017A4AC.o,tail17.data.o,ov_SC06_013_jr_8017AE2C.o,ov_SC06_013_jr_8017BEBC.o,tail18.data.o,trailing.o  # Phase-26 §8 jtbl-rodata carve
build/src/ov_SC06_013/ov_SC06_013.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14
build/src/ov_SC06_013/ov_SC06_013_jr_8012ACE0.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0xcc,+0xe0
build/src/ov_SC06_013/ov_SC06_013_jr_80135D20.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC06_013/ov_SC06_013_jr_8013F350.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC06_013/ov_SC06_013_jr_8013FFD8.o: JTBL_PADS := 0,0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38,+0x58
build/src/ov_SC06_013/ov_SC06_013_jr_8015444C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x70
build/src/ov_SC06_013/ov_SC06_013_jr_80154C24.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x24
build/src/ov_SC06_013/ov_SC06_013_jr_801588CC.o: JTBL_PADS := 0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x28,+0x48
build/src/ov_SC06_013/ov_SC06_013_jr_80159C84.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC06_013/ov_SC06_013_jr_8015AE2C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC06_013/ov_SC06_013_jr_8016AB6C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC06_013/ov_SC06_013_jr_80178D40.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x178
build/src/ov_SC06_013/ov_SC06_013_jr_8017BEBC.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC06_013/ov_SC06_013_o0c.o: JTBL_PADS := 0,4,4,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x38,+0xa8,+0x118
ov_SC06_013_CHECK_SHA  := config/check.ov_SC06_013.sha
ov_SC06_013_SYMBOLS    := config/symbols.ov_SC06_013.txt
ov_SC06_013_SIG        := .run/sig.ov_SC06_013.jsonl
ov_SC06_013_GHIDRA_PROG := ov_SC06_013
ov_SC06_013_VRAM_BASE  := 0x80128158
ov_SC06_013_TEXT_LO    := 0x80128158
ov_SC06_013_TEXT_HI    := 0x8019AC07
ov_SC06_013_ASM_DIR     := asm/ov_SC06_013
ov_SC06_013_SRC_DIR     := src/ov_SC06_013
ov_SC06_013_UNDEF_SYMS  := build/ov_SC06_013/undefined_syms_auto.txt
ov_SC06_013_UNDEF_FUNCS := build/ov_SC06_013/undefined_funcs_auto.txt

# --- ov_SC06_014 (location overlay SC06/FILE_014, vram 0x80128158 — onboarded by new_overlay.sh) ---
ov_SC06_014_EXE        := extracted/retail/SC06.CD.dir/FILE_014.dir/0.4.dec
ov_SC06_014_NAME       := ov_SC06_014
ov_SC06_014_OUT_DIR    := build/ov_SC06_014
ov_SC06_014_OUT        := $(ov_SC06_014_OUT_DIR)/$(ov_SC06_014_NAME)
ov_SC06_014_ELF        := $(ov_SC06_014_OUT).elf
ov_SC06_014_MAPFILE    := $(ov_SC06_014_OUT).map
ov_SC06_014_LD_SCRIPT  := $(ov_SC06_014_OUT).ld
ov_SC06_014_SPLAT_YAML := config/splat.ov_SC06_014.yaml
ov_SC06_014_JTBL_INTERLEAVE := --order tail.data.o,ov_SC06_014.o,ov_SC06_014_jr_8012ACE0.o,tail2.data.o,ov_SC06_014_jr_80135888.o,tail3.data.o,ov_SC06_014_jr_80135A4C.o,tail4.data.o,ov_SC06_014_jr_80135D20.o,tail5.data.o,ov_SC06_014_jr_801380E0.o,ov_SC06_014_o0c.o,tail6.data.o,ov_SC06_014_jr_8013F350.o,tail7.data.o,ov_SC06_014_jr_8013FFD8.o,tail8.data.o,ov_SC06_014_jr_80140608.o,tail9.data.o,ov_SC06_014_jr_8015444C.o,ov_SC06_014_jr_80154C24.o,ov_SC06_014_jr_801588CC.o,ov_SC06_014_jr_80159C84.o,tail10.data.o,ov_SC06_014_jr_8015A3C8.o,tail11.data.o,ov_SC06_014_jr_8015AE2C.o,tail12.data.o,ov_SC06_014_jr_8015C32C.o,tail13.data.o,ov_SC06_014_jr_8016AB6C.o,tail14.data.o,ov_SC06_014_jr_80171B4C.o,ov_SC06_014_jr_801734BC.o,tail15.data.o,ov_SC06_014_jr_801789AC.o,ov_SC06_014_jr_80178D40.o,tail16.data.o,ov_SC06_014_jr_8017A4AC.o,tail17.data.o,ov_SC06_014_jr_8017AE2C.o,ov_SC06_014_jr_8017BEBC.o,tail18.data.o,trailing.o  # Phase-26 §8 jtbl-rodata carve
build/src/ov_SC06_014/ov_SC06_014.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14
build/src/ov_SC06_014/ov_SC06_014_jr_8012ACE0.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0xcc,+0xe0
build/src/ov_SC06_014/ov_SC06_014_jr_80135D20.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC06_014/ov_SC06_014_jr_8013F350.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC06_014/ov_SC06_014_jr_8013FFD8.o: JTBL_PADS := 0,0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38,+0x58
build/src/ov_SC06_014/ov_SC06_014_jr_8015444C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x70
build/src/ov_SC06_014/ov_SC06_014_jr_80154C24.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x24
build/src/ov_SC06_014/ov_SC06_014_jr_801588CC.o: JTBL_PADS := 0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x28,+0x48
build/src/ov_SC06_014/ov_SC06_014_jr_80159C84.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC06_014/ov_SC06_014_jr_8015AE2C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC06_014/ov_SC06_014_jr_8016AB6C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC06_014/ov_SC06_014_jr_80178D40.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x178
build/src/ov_SC06_014/ov_SC06_014_jr_8017BEBC.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC06_014/ov_SC06_014_o0c.o: JTBL_PADS := 0,4,4,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x38,+0xa8,+0x118
ov_SC06_014_CHECK_SHA  := config/check.ov_SC06_014.sha
ov_SC06_014_SYMBOLS    := config/symbols.ov_SC06_014.txt
ov_SC06_014_SIG        := .run/sig.ov_SC06_014.jsonl
ov_SC06_014_GHIDRA_PROG := ov_SC06_014
ov_SC06_014_VRAM_BASE  := 0x80128158
ov_SC06_014_TEXT_LO    := 0x80128158
ov_SC06_014_TEXT_HI    := 0x801A161F
ov_SC06_014_ASM_DIR     := asm/ov_SC06_014
ov_SC06_014_SRC_DIR     := src/ov_SC06_014
ov_SC06_014_UNDEF_SYMS  := build/ov_SC06_014/undefined_syms_auto.txt
ov_SC06_014_UNDEF_FUNCS := build/ov_SC06_014/undefined_funcs_auto.txt

# --- ov_SC06_015 (location overlay SC06/FILE_015, vram 0x80128158 — onboarded by new_overlay.sh) ---
ov_SC06_015_EXE        := extracted/retail/SC06.CD.dir/FILE_015.dir/0.4.dec
ov_SC06_015_NAME       := ov_SC06_015
ov_SC06_015_OUT_DIR    := build/ov_SC06_015
ov_SC06_015_OUT        := $(ov_SC06_015_OUT_DIR)/$(ov_SC06_015_NAME)
ov_SC06_015_ELF        := $(ov_SC06_015_OUT).elf
ov_SC06_015_MAPFILE    := $(ov_SC06_015_OUT).map
ov_SC06_015_LD_SCRIPT  := $(ov_SC06_015_OUT).ld
ov_SC06_015_SPLAT_YAML := config/splat.ov_SC06_015.yaml
ov_SC06_015_JTBL_INTERLEAVE := --order tail.data.o,ov_SC06_015.o,ov_SC06_015_jr_8012ACE0.o,tail2.data.o,ov_SC06_015_jr_80135888.o,tail3.data.o,ov_SC06_015_jr_80135A4C.o,tail4.data.o,ov_SC06_015_jr_80135D20.o,tail5.data.o,ov_SC06_015_jr_801380E0.o,ov_SC06_015_o0c.o,tail6.data.o,ov_SC06_015_jr_8013F350.o,tail7.data.o,ov_SC06_015_jr_8013FFD8.o,tail8.data.o,ov_SC06_015_jr_80140608.o,tail9.data.o,ov_SC06_015_jr_8015444C.o,ov_SC06_015_jr_80154C24.o,ov_SC06_015_jr_801588CC.o,ov_SC06_015_jr_80159C84.o,tail10.data.o,ov_SC06_015_jr_8015A3C8.o,tail11.data.o,ov_SC06_015_jr_8015AE2C.o,tail12.data.o,ov_SC06_015_jr_8015C32C.o,tail13.data.o,ov_SC06_015_jr_8016AB6C.o,tail14.data.o,ov_SC06_015_jr_80171B4C.o,ov_SC06_015_jr_801734BC.o,tail15.data.o,ov_SC06_015_jr_801789AC.o,ov_SC06_015_jr_80178D40.o,tail16.data.o,ov_SC06_015_jr_8017A4AC.o,tail17.data.o,ov_SC06_015_jr_8017AE2C.o,ov_SC06_015_jr_8017BEBC.o,tail18.data.o,trailing.o  # Phase-26 §8 jtbl-rodata carve
build/src/ov_SC06_015/ov_SC06_015.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14
build/src/ov_SC06_015/ov_SC06_015_jr_8012ACE0.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0xcc,+0xe0
build/src/ov_SC06_015/ov_SC06_015_jr_80135D20.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC06_015/ov_SC06_015_jr_8013F350.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC06_015/ov_SC06_015_jr_8013FFD8.o: JTBL_PADS := 0,0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38,+0x58
build/src/ov_SC06_015/ov_SC06_015_jr_8015444C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x70
build/src/ov_SC06_015/ov_SC06_015_jr_80154C24.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x24
build/src/ov_SC06_015/ov_SC06_015_jr_801588CC.o: JTBL_PADS := 0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x28,+0x48
build/src/ov_SC06_015/ov_SC06_015_jr_80159C84.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC06_015/ov_SC06_015_jr_8015AE2C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC06_015/ov_SC06_015_jr_8016AB6C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC06_015/ov_SC06_015_jr_80178D40.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x178
build/src/ov_SC06_015/ov_SC06_015_o0c.o: JTBL_PADS := 0,4,4,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x38,+0xa8,+0x118
ov_SC06_015_CHECK_SHA  := config/check.ov_SC06_015.sha
ov_SC06_015_SYMBOLS    := config/symbols.ov_SC06_015.txt
ov_SC06_015_SIG        := .run/sig.ov_SC06_015.jsonl
ov_SC06_015_GHIDRA_PROG := ov_SC06_015
ov_SC06_015_VRAM_BASE  := 0x80128158
ov_SC06_015_TEXT_LO    := 0x80128158
ov_SC06_015_TEXT_HI    := 0x801949FF
ov_SC06_015_ASM_DIR     := asm/ov_SC06_015
ov_SC06_015_SRC_DIR     := src/ov_SC06_015
ov_SC06_015_UNDEF_SYMS  := build/ov_SC06_015/undefined_syms_auto.txt
ov_SC06_015_UNDEF_FUNCS := build/ov_SC06_015/undefined_funcs_auto.txt

# --- ov_SC06_016 (location overlay SC06/FILE_016, vram 0x80128158 — onboarded by new_overlay.sh) ---
ov_SC06_016_EXE        := extracted/retail/SC06.CD.dir/FILE_016.dir/0.4.dec
ov_SC06_016_NAME       := ov_SC06_016
ov_SC06_016_OUT_DIR    := build/ov_SC06_016
ov_SC06_016_OUT        := $(ov_SC06_016_OUT_DIR)/$(ov_SC06_016_NAME)
ov_SC06_016_ELF        := $(ov_SC06_016_OUT).elf
ov_SC06_016_MAPFILE    := $(ov_SC06_016_OUT).map
ov_SC06_016_LD_SCRIPT  := $(ov_SC06_016_OUT).ld
ov_SC06_016_SPLAT_YAML := config/splat.ov_SC06_016.yaml
ov_SC06_016_JTBL_INTERLEAVE := --order tail.data.o,ov_SC06_016.o,ov_SC06_016_jr_8012ACE0.o,tail2.data.o,ov_SC06_016_jr_80135888.o,tail3.data.o,ov_SC06_016_jr_80135A4C.o,tail4.data.o,ov_SC06_016_jr_80135D20.o,tail5.data.o,ov_SC06_016_jr_801380E0.o,ov_SC06_016_o0c.o,tail6.data.o,ov_SC06_016_jr_8013F350.o,tail7.data.o,ov_SC06_016_jr_8013FFD8.o,tail8.data.o,ov_SC06_016_jr_80140608.o,tail9.data.o,ov_SC06_016_jr_8015444C.o,ov_SC06_016_jr_80154C24.o,ov_SC06_016_jr_801588CC.o,ov_SC06_016_jr_80159C84.o,tail10.data.o,ov_SC06_016_jr_8015A3C8.o,tail11.data.o,ov_SC06_016_jr_8015AE2C.o,tail12.data.o,ov_SC06_016_jr_8015C32C.o,tail13.data.o,ov_SC06_016_jr_8016AB6C.o,tail14.data.o,ov_SC06_016_jr_80171B4C.o,ov_SC06_016_jr_801734BC.o,tail15.data.o,ov_SC06_016_jr_801789AC.o,ov_SC06_016_jr_80178D40.o,tail16.data.o,ov_SC06_016_jr_8017A4AC.o,tail17.data.o,ov_SC06_016_jr_8017AE2C.o,tail18.data.o,ov_SC06_016_jr_8017C8D0.o,tail19.data.o,ov_SC06_016_jr_801816DC.o,ov_SC06_016_jr_801839D0.o,tail20.data.o,trailing.o  # Phase-26 §8 jtbl-rodata carve
build/src/ov_SC06_016/ov_SC06_016.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14
build/src/ov_SC06_016/ov_SC06_016_jr_8012ACE0.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0xcc,+0xe0
build/src/ov_SC06_016/ov_SC06_016_jr_80135D20.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC06_016/ov_SC06_016_jr_8013F350.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC06_016/ov_SC06_016_jr_8013FFD8.o: JTBL_PADS := 0,0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38,+0x58
build/src/ov_SC06_016/ov_SC06_016_jr_8015444C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x70
build/src/ov_SC06_016/ov_SC06_016_jr_80154C24.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x24
build/src/ov_SC06_016/ov_SC06_016_jr_801588CC.o: JTBL_PADS := 0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x28,+0x48
build/src/ov_SC06_016/ov_SC06_016_jr_80159C84.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC06_016/ov_SC06_016_jr_8015AE2C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC06_016/ov_SC06_016_jr_8016AB6C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC06_016/ov_SC06_016_jr_80178D40.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x178
build/src/ov_SC06_016/ov_SC06_016_jr_801816DC.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC06_016/ov_SC06_016_o0c.o: JTBL_PADS := 0,4,4,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x38,+0xa8,+0x118
ov_SC06_016_CHECK_SHA  := config/check.ov_SC06_016.sha
ov_SC06_016_SYMBOLS    := config/symbols.ov_SC06_016.txt
ov_SC06_016_SIG        := .run/sig.ov_SC06_016.jsonl
ov_SC06_016_GHIDRA_PROG := ov_SC06_016
ov_SC06_016_VRAM_BASE  := 0x80128158
ov_SC06_016_TEXT_LO    := 0x80128158
ov_SC06_016_TEXT_HI    := 0x801A026F
ov_SC06_016_ASM_DIR     := asm/ov_SC06_016
ov_SC06_016_SRC_DIR     := src/ov_SC06_016
ov_SC06_016_UNDEF_SYMS  := build/ov_SC06_016/undefined_syms_auto.txt
ov_SC06_016_UNDEF_FUNCS := build/ov_SC06_016/undefined_funcs_auto.txt

# --- ov_SC06_018 (location overlay SC06/FILE_018, vram 0x80128158 — onboarded by new_overlay.sh) ---
ov_SC06_018_EXE        := extracted/retail/SC06.CD.dir/FILE_018.dir/0.4.dec
ov_SC06_018_NAME       := ov_SC06_018
ov_SC06_018_OUT_DIR    := build/ov_SC06_018
ov_SC06_018_OUT        := $(ov_SC06_018_OUT_DIR)/$(ov_SC06_018_NAME)
ov_SC06_018_ELF        := $(ov_SC06_018_OUT).elf
ov_SC06_018_MAPFILE    := $(ov_SC06_018_OUT).map
ov_SC06_018_LD_SCRIPT  := $(ov_SC06_018_OUT).ld
ov_SC06_018_SPLAT_YAML := config/splat.ov_SC06_018.yaml
ov_SC06_018_JTBL_INTERLEAVE := --order tail.data.o,ov_SC06_018.o,ov_SC06_018_jr_8012ACE0.o,tail2.data.o,ov_SC06_018_jr_80135888.o,tail3.data.o,ov_SC06_018_jr_80135A4C.o,tail4.data.o,ov_SC06_018_jr_80135D20.o,tail5.data.o,ov_SC06_018_jr_801380E0.o,ov_SC06_018_o0c.o,tail6.data.o,ov_SC06_018_jr_8013F350.o,tail7.data.o,ov_SC06_018_jr_8013FFD8.o,tail8.data.o,ov_SC06_018_jr_80140608.o,tail9.data.o,ov_SC06_018_jr_8015444C.o,ov_SC06_018_jr_80154C24.o,ov_SC06_018_jr_801588CC.o,ov_SC06_018_jr_80159C84.o,tail10.data.o,ov_SC06_018_jr_8015A3C8.o,tail11.data.o,ov_SC06_018_jr_8015AE2C.o,tail12.data.o,ov_SC06_018_jr_8015C32C.o,tail13.data.o,ov_SC06_018_jr_8016AB6C.o,tail14.data.o,ov_SC06_018_jr_80171B4C.o,ov_SC06_018_jr_801734BC.o,tail15.data.o,ov_SC06_018_jr_801789AC.o,ov_SC06_018_jr_80178D40.o,tail16.data.o,ov_SC06_018_jr_8017A4AC.o,tail17.data.o,ov_SC06_018_jr_8017AE2C.o,ov_SC06_018_jr_8017C24C.o,ov_SC06_018_jr_80186270.o,tail18.data.o,ov_SC06_018_jr_80187AEC.o,tail19.data.o,ov_SC06_018_jr_8018FF98.o,ov_SC06_018_jr_8019059C.o,tail20.data.o,ov_SC06_018_jr_80191C50.o,tail21.data.o,trailing.o  # Phase-26 §8 jtbl-rodata carve
build/src/ov_SC06_018/ov_SC06_018.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14
build/src/ov_SC06_018/ov_SC06_018_jr_8012ACE0.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0xcc,+0xe0
build/src/ov_SC06_018/ov_SC06_018_jr_80135D20.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC06_018/ov_SC06_018_jr_8013F350.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC06_018/ov_SC06_018_jr_8013FFD8.o: JTBL_PADS := 0,0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38,+0x58
build/src/ov_SC06_018/ov_SC06_018_jr_8015444C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x70
build/src/ov_SC06_018/ov_SC06_018_jr_80154C24.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x24
build/src/ov_SC06_018/ov_SC06_018_jr_801588CC.o: JTBL_PADS := 0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x28,+0x48
build/src/ov_SC06_018/ov_SC06_018_jr_80159C84.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC06_018/ov_SC06_018_jr_8015AE2C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC06_018/ov_SC06_018_jr_8016AB6C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC06_018/ov_SC06_018_jr_80178D40.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x178
build/src/ov_SC06_018/ov_SC06_018_jr_8017C24C.o: JTBL_PADS := 0,0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38
build/src/ov_SC06_018/ov_SC06_018_jr_80186270.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC06_018/ov_SC06_018_jr_8019059C.o: JTBL_PADS := 0,0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x28,+0x40
build/src/ov_SC06_018/ov_SC06_018_o0c.o: JTBL_PADS := 0,4,4,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x38,+0xa8,+0x118
ov_SC06_018_CHECK_SHA  := config/check.ov_SC06_018.sha
ov_SC06_018_SYMBOLS    := config/symbols.ov_SC06_018.txt
ov_SC06_018_SIG        := .run/sig.ov_SC06_018.jsonl
ov_SC06_018_GHIDRA_PROG := ov_SC06_018
ov_SC06_018_VRAM_BASE  := 0x80128158
ov_SC06_018_TEXT_LO    := 0x80128158
ov_SC06_018_TEXT_HI    := 0x801D5B9F
ov_SC06_018_ASM_DIR     := asm/ov_SC06_018
ov_SC06_018_SRC_DIR     := src/ov_SC06_018
ov_SC06_018_UNDEF_SYMS  := build/ov_SC06_018/undefined_syms_auto.txt
ov_SC06_018_UNDEF_FUNCS := build/ov_SC06_018/undefined_funcs_auto.txt

# --- ov_SC06_020 (location overlay SC06/FILE_020, vram 0x80128158 — onboarded by new_overlay.sh) ---
ov_SC06_020_EXE        := extracted/retail/SC06.CD.dir/FILE_020.dir/0.4.dec
ov_SC06_020_NAME       := ov_SC06_020
ov_SC06_020_OUT_DIR    := build/ov_SC06_020
ov_SC06_020_OUT        := $(ov_SC06_020_OUT_DIR)/$(ov_SC06_020_NAME)
ov_SC06_020_ELF        := $(ov_SC06_020_OUT).elf
ov_SC06_020_MAPFILE    := $(ov_SC06_020_OUT).map
ov_SC06_020_LD_SCRIPT  := $(ov_SC06_020_OUT).ld
ov_SC06_020_SPLAT_YAML := config/splat.ov_SC06_020.yaml
ov_SC06_020_JTBL_INTERLEAVE := --order tail.data.o,ov_SC06_020.o,ov_SC06_020_jr_8012ACE0.o,tail2.data.o,ov_SC06_020_jr_80135888.o,tail3.data.o,ov_SC06_020_jr_80135A4C.o,tail4.data.o,ov_SC06_020_jr_80135D20.o,tail5.data.o,ov_SC06_020_jr_801380E0.o,ov_SC06_020_o0c.o,tail6.data.o,ov_SC06_020_jr_8013F350.o,tail7.data.o,ov_SC06_020_jr_8013FFD8.o,tail8.data.o,ov_SC06_020_jr_80140608.o,tail9.data.o,ov_SC06_020_jr_8015444C.o,ov_SC06_020_jr_80154C24.o,ov_SC06_020_jr_801588CC.o,ov_SC06_020_jr_80159C84.o,tail10.data.o,ov_SC06_020_jr_8015A3C8.o,tail11.data.o,ov_SC06_020_jr_8015AE2C.o,tail12.data.o,ov_SC06_020_jr_8015C32C.o,tail13.data.o,ov_SC06_020_jr_8016AB6C.o,tail14.data.o,ov_SC06_020_jr_80171B4C.o,ov_SC06_020_jr_801734BC.o,tail15.data.o,ov_SC06_020_jr_801789AC.o,ov_SC06_020_jr_80178D40.o,tail16.data.o,ov_SC06_020_jr_8017A4AC.o,tail17.data.o,ov_SC06_020_jr_8017AE2C.o,ov_SC06_020_jr_8017C24C.o,ov_SC06_020_jr_801803E0.o,ov_SC06_020_jr_80180B04.o,tail18.data.o,trailing.o  # Phase-26 §8 jtbl-rodata carve
build/src/ov_SC06_020/ov_SC06_020.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14
build/src/ov_SC06_020/ov_SC06_020_jr_8012ACE0.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0xcc,+0xe0
build/src/ov_SC06_020/ov_SC06_020_jr_80135D20.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC06_020/ov_SC06_020_jr_8013F350.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC06_020/ov_SC06_020_jr_8013FFD8.o: JTBL_PADS := 0,0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38,+0x58
build/src/ov_SC06_020/ov_SC06_020_jr_8015444C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x70
build/src/ov_SC06_020/ov_SC06_020_jr_80154C24.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x24
build/src/ov_SC06_020/ov_SC06_020_jr_801588CC.o: JTBL_PADS := 0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x28,+0x48
build/src/ov_SC06_020/ov_SC06_020_jr_80159C84.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC06_020/ov_SC06_020_jr_8015AE2C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC06_020/ov_SC06_020_jr_8016AB6C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC06_020/ov_SC06_020_jr_80178D40.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x178
build/src/ov_SC06_020/ov_SC06_020_jr_8017C24C.o: JTBL_PADS := 0,0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38
build/src/ov_SC06_020/ov_SC06_020_jr_80180B04.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC06_020/ov_SC06_020_o0c.o: JTBL_PADS := 0,4,4,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x38,+0xa8,+0x118
ov_SC06_020_CHECK_SHA  := config/check.ov_SC06_020.sha
ov_SC06_020_SYMBOLS    := config/symbols.ov_SC06_020.txt
ov_SC06_020_SIG        := .run/sig.ov_SC06_020.jsonl
ov_SC06_020_GHIDRA_PROG := ov_SC06_020
ov_SC06_020_VRAM_BASE  := 0x80128158
ov_SC06_020_TEXT_LO    := 0x80128158
ov_SC06_020_TEXT_HI    := 0x801BA9EF
ov_SC06_020_ASM_DIR     := asm/ov_SC06_020
ov_SC06_020_SRC_DIR     := src/ov_SC06_020
ov_SC06_020_UNDEF_SYMS  := build/ov_SC06_020/undefined_syms_auto.txt
ov_SC06_020_UNDEF_FUNCS := build/ov_SC06_020/undefined_funcs_auto.txt

# --- ov_SC06_022 (location overlay SC06/FILE_022, vram 0x80128158 — onboarded by new_overlay.sh) ---
ov_SC06_022_EXE        := extracted/retail/SC06.CD.dir/FILE_022.dir/0.4.dec
ov_SC06_022_NAME       := ov_SC06_022
ov_SC06_022_OUT_DIR    := build/ov_SC06_022
ov_SC06_022_OUT        := $(ov_SC06_022_OUT_DIR)/$(ov_SC06_022_NAME)
ov_SC06_022_ELF        := $(ov_SC06_022_OUT).elf
ov_SC06_022_MAPFILE    := $(ov_SC06_022_OUT).map
ov_SC06_022_LD_SCRIPT  := $(ov_SC06_022_OUT).ld
ov_SC06_022_SPLAT_YAML := config/splat.ov_SC06_022.yaml
ov_SC06_022_JTBL_INTERLEAVE := --order tail.data.o,ov_SC06_022.o,ov_SC06_022_jr_8012ACE0.o,tail2.data.o,ov_SC06_022_jr_80135888.o,tail3.data.o,ov_SC06_022_jr_80135A4C.o,tail4.data.o,ov_SC06_022_jr_80135D20.o,tail5.data.o,ov_SC06_022_jr_801380E0.o,ov_SC06_022_o0c.o,tail6.data.o,ov_SC06_022_jr_8013F350.o,tail7.data.o,ov_SC06_022_jr_8013FFD8.o,tail8.data.o,ov_SC06_022_jr_80140608.o,tail9.data.o,ov_SC06_022_jr_8015444C.o,ov_SC06_022_jr_80154C24.o,ov_SC06_022_jr_801588CC.o,ov_SC06_022_jr_80159C84.o,tail10.data.o,ov_SC06_022_jr_8015A3C8.o,tail11.data.o,ov_SC06_022_jr_8015AE2C.o,tail12.data.o,ov_SC06_022_jr_8015C32C.o,tail13.data.o,ov_SC06_022_jr_8016AB6C.o,tail14.data.o,ov_SC06_022_jr_80171B4C.o,ov_SC06_022_jr_801734BC.o,tail15.data.o,ov_SC06_022_jr_801789AC.o,ov_SC06_022_jr_80178D40.o,tail16.data.o,ov_SC06_022_jr_8017A4AC.o,tail17.data.o,ov_SC06_022_jr_8017AE2C.o,ov_SC06_022_jr_8017BEBC.o,tail18.data.o,ov_SC06_022_jr_80180CD0.o,ov_SC06_022_jr_80182D08.o,ov_SC06_022_jr_80184304.o,ov_SC06_022_jr_80184A28.o,tail19.data.o,trailing.o  # Phase-26 §8 jtbl-rodata carve
build/src/ov_SC06_022/ov_SC06_022.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14
build/src/ov_SC06_022/ov_SC06_022_jr_8012ACE0.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0xcc,+0xe0
build/src/ov_SC06_022/ov_SC06_022_jr_80135D20.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC06_022/ov_SC06_022_jr_8013F350.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC06_022/ov_SC06_022_jr_8013FFD8.o: JTBL_PADS := 0,0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38,+0x58
build/src/ov_SC06_022/ov_SC06_022_jr_8015444C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x70
build/src/ov_SC06_022/ov_SC06_022_jr_80154C24.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x24
build/src/ov_SC06_022/ov_SC06_022_jr_801588CC.o: JTBL_PADS := 0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x28,+0x48
build/src/ov_SC06_022/ov_SC06_022_jr_80159C84.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC06_022/ov_SC06_022_jr_8015AE2C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC06_022/ov_SC06_022_jr_8016AB6C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC06_022/ov_SC06_022_jr_80178D40.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x178
build/src/ov_SC06_022/ov_SC06_022_jr_8017BEBC.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC06_022/ov_SC06_022_jr_80180CD0.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC06_022/ov_SC06_022_jr_80182D08.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC06_022/ov_SC06_022_o0c.o: JTBL_PADS := 0,4,4,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x38,+0xa8,+0x118
ov_SC06_022_CHECK_SHA  := config/check.ov_SC06_022.sha
ov_SC06_022_SYMBOLS    := config/symbols.ov_SC06_022.txt
ov_SC06_022_SIG        := .run/sig.ov_SC06_022.jsonl
ov_SC06_022_GHIDRA_PROG := ov_SC06_022
ov_SC06_022_VRAM_BASE  := 0x80128158
ov_SC06_022_TEXT_LO    := 0x80128158
ov_SC06_022_TEXT_HI    := 0x801E226F
ov_SC06_022_ASM_DIR     := asm/ov_SC06_022
ov_SC06_022_SRC_DIR     := src/ov_SC06_022
ov_SC06_022_UNDEF_SYMS  := build/ov_SC06_022/undefined_syms_auto.txt
ov_SC06_022_UNDEF_FUNCS := build/ov_SC06_022/undefined_funcs_auto.txt

# --- ov_SC06_024 (location overlay SC06/FILE_024, vram 0x80128158 — onboarded by new_overlay.sh) ---
ov_SC06_024_EXE        := extracted/retail/SC06.CD.dir/FILE_024.dir/0.4.dec
ov_SC06_024_NAME       := ov_SC06_024
ov_SC06_024_OUT_DIR    := build/ov_SC06_024
ov_SC06_024_OUT        := $(ov_SC06_024_OUT_DIR)/$(ov_SC06_024_NAME)
ov_SC06_024_ELF        := $(ov_SC06_024_OUT).elf
ov_SC06_024_MAPFILE    := $(ov_SC06_024_OUT).map
ov_SC06_024_LD_SCRIPT  := $(ov_SC06_024_OUT).ld
ov_SC06_024_SPLAT_YAML := config/splat.ov_SC06_024.yaml
ov_SC06_024_JTBL_INTERLEAVE := --order tail.data.o,ov_SC06_024.o,ov_SC06_024_jr_8012ACE0.o,tail2.data.o,ov_SC06_024_jr_80135888.o,tail3.data.o,ov_SC06_024_jr_80135A4C.o,tail4.data.o,ov_SC06_024_jr_80135D20.o,tail5.data.o,ov_SC06_024_jr_801380E0.o,ov_SC06_024_o0c.o,tail6.data.o,ov_SC06_024_jr_8013F350.o,tail7.data.o,ov_SC06_024_jr_8013FFD8.o,tail8.data.o,ov_SC06_024_jr_80140608.o,tail9.data.o,ov_SC06_024_jr_8015444C.o,ov_SC06_024_jr_80154C24.o,ov_SC06_024_jr_801588CC.o,ov_SC06_024_jr_80159C84.o,tail10.data.o,ov_SC06_024_jr_8015A3C8.o,tail11.data.o,ov_SC06_024_jr_8015AE2C.o,tail12.data.o,ov_SC06_024_jr_8015C32C.o,tail13.data.o,ov_SC06_024_jr_8016AB6C.o,tail14.data.o,ov_SC06_024_jr_80171B4C.o,ov_SC06_024_jr_801734BC.o,tail15.data.o,ov_SC06_024_jr_801789AC.o,ov_SC06_024_jr_80178D40.o,tail16.data.o,ov_SC06_024_jr_8017A4AC.o,tail17.data.o,ov_SC06_024_jr_8017AE2C.o,ov_SC06_024_jr_8017BEBC.o,ov_SC06_024_jr_80181D34.o,tail18.data.o,ov_SC06_024_jr_80183B3C.o,ov_SC06_024_jr_801851E0.o,ov_SC06_024_jr_801867DC.o,ov_SC06_024_jr_80186F00.o,tail19.data.o,trailing.o  # Phase-26 §8 jtbl-rodata carve
build/src/ov_SC06_024/ov_SC06_024.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14
build/src/ov_SC06_024/ov_SC06_024_jr_8012ACE0.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0xcc,+0xe0
build/src/ov_SC06_024/ov_SC06_024_jr_80135D20.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC06_024/ov_SC06_024_jr_8013F350.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC06_024/ov_SC06_024_jr_8013FFD8.o: JTBL_PADS := 0,0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38,+0x58
build/src/ov_SC06_024/ov_SC06_024_jr_8015444C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x70
build/src/ov_SC06_024/ov_SC06_024_jr_80154C24.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x24
build/src/ov_SC06_024/ov_SC06_024_jr_801588CC.o: JTBL_PADS := 0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x28,+0x48
build/src/ov_SC06_024/ov_SC06_024_jr_80159C84.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC06_024/ov_SC06_024_jr_8015AE2C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC06_024/ov_SC06_024_jr_8016AB6C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC06_024/ov_SC06_024_jr_80178D40.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x178
build/src/ov_SC06_024/ov_SC06_024_jr_8017BEBC.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x48
build/src/ov_SC06_024/ov_SC06_024_jr_80181D34.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC06_024/ov_SC06_024_jr_801851E0.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC06_024/ov_SC06_024_jr_80186F00.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC06_024/ov_SC06_024_o0c.o: JTBL_PADS := 0,4,4,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x38,+0xa8,+0x118
ov_SC06_024_CHECK_SHA  := config/check.ov_SC06_024.sha
ov_SC06_024_SYMBOLS    := config/symbols.ov_SC06_024.txt
ov_SC06_024_SIG        := .run/sig.ov_SC06_024.jsonl
ov_SC06_024_GHIDRA_PROG := ov_SC06_024
ov_SC06_024_VRAM_BASE  := 0x80128158
ov_SC06_024_TEXT_LO    := 0x80128158
ov_SC06_024_TEXT_HI    := 0x801E1967
ov_SC06_024_ASM_DIR     := asm/ov_SC06_024
ov_SC06_024_SRC_DIR     := src/ov_SC06_024
ov_SC06_024_UNDEF_SYMS  := build/ov_SC06_024/undefined_syms_auto.txt
ov_SC06_024_UNDEF_FUNCS := build/ov_SC06_024/undefined_funcs_auto.txt

# --- ov_SC06_025 (location overlay SC06/FILE_025, vram 0x80128158 — onboarded by new_overlay.sh) ---
ov_SC06_025_EXE        := extracted/retail/SC06.CD.dir/FILE_025.dir/0.4.dec
ov_SC06_025_NAME       := ov_SC06_025
ov_SC06_025_OUT_DIR    := build/ov_SC06_025
ov_SC06_025_OUT        := $(ov_SC06_025_OUT_DIR)/$(ov_SC06_025_NAME)
ov_SC06_025_ELF        := $(ov_SC06_025_OUT).elf
ov_SC06_025_MAPFILE    := $(ov_SC06_025_OUT).map
ov_SC06_025_LD_SCRIPT  := $(ov_SC06_025_OUT).ld
ov_SC06_025_SPLAT_YAML := config/splat.ov_SC06_025.yaml
ov_SC06_025_JTBL_INTERLEAVE := --order tail.data.o,ov_SC06_025.o,ov_SC06_025_jr_8012ACE0.o,tail2.data.o,ov_SC06_025_jr_80135888.o,tail3.data.o,ov_SC06_025_jr_80135A4C.o,tail4.data.o,ov_SC06_025_jr_80135D20.o,tail5.data.o,ov_SC06_025_jr_801380E0.o,ov_SC06_025_o0c.o,tail6.data.o,ov_SC06_025_jr_8013F350.o,tail7.data.o,ov_SC06_025_jr_8013FFD8.o,tail8.data.o,ov_SC06_025_jr_80140608.o,tail9.data.o,ov_SC06_025_jr_8015444C.o,ov_SC06_025_jr_80154C24.o,ov_SC06_025_jr_801588CC.o,ov_SC06_025_jr_80159C84.o,tail10.data.o,ov_SC06_025_jr_8015A3C8.o,tail11.data.o,ov_SC06_025_jr_8015AE2C.o,tail12.data.o,ov_SC06_025_jr_8015C32C.o,tail13.data.o,ov_SC06_025_jr_8016AB6C.o,tail14.data.o,ov_SC06_025_jr_80171B4C.o,ov_SC06_025_jr_801734BC.o,tail15.data.o,ov_SC06_025_jr_801789AC.o,ov_SC06_025_jr_80178D40.o,tail16.data.o,ov_SC06_025_jr_8017A4AC.o,tail17.data.o,ov_SC06_025_jr_8017AE2C.o,ov_SC06_025_jr_8017BEBC.o,tail18.data.o,ov_SC06_025_jr_8017EEC4.o,tail19.data.o,trailing.o  # Phase-26 §8 jtbl-rodata carve
build/src/ov_SC06_025/ov_SC06_025.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14
build/src/ov_SC06_025/ov_SC06_025_jr_8012ACE0.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0xcc,+0xe0
build/src/ov_SC06_025/ov_SC06_025_jr_80135D20.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC06_025/ov_SC06_025_jr_8013F350.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC06_025/ov_SC06_025_jr_8013FFD8.o: JTBL_PADS := 0,0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38,+0x58
build/src/ov_SC06_025/ov_SC06_025_jr_8015444C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x70
build/src/ov_SC06_025/ov_SC06_025_jr_80154C24.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x24
build/src/ov_SC06_025/ov_SC06_025_jr_801588CC.o: JTBL_PADS := 0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x28,+0x48
build/src/ov_SC06_025/ov_SC06_025_jr_80159C84.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC06_025/ov_SC06_025_jr_8015AE2C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC06_025/ov_SC06_025_jr_8016AB6C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC06_025/ov_SC06_025_jr_80178D40.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x178
build/src/ov_SC06_025/ov_SC06_025_jr_8017EEC4.o: JTBL_PADS := 0,0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38
build/src/ov_SC06_025/ov_SC06_025_o0c.o: JTBL_PADS := 0,4,4,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x38,+0xa8,+0x118
ov_SC06_025_CHECK_SHA  := config/check.ov_SC06_025.sha
ov_SC06_025_SYMBOLS    := config/symbols.ov_SC06_025.txt
ov_SC06_025_SIG        := .run/sig.ov_SC06_025.jsonl
ov_SC06_025_GHIDRA_PROG := ov_SC06_025
ov_SC06_025_VRAM_BASE  := 0x80128158
ov_SC06_025_TEXT_LO    := 0x80128158
ov_SC06_025_TEXT_HI    := 0x801B2287
ov_SC06_025_ASM_DIR     := asm/ov_SC06_025
ov_SC06_025_SRC_DIR     := src/ov_SC06_025
ov_SC06_025_UNDEF_SYMS  := build/ov_SC06_025/undefined_syms_auto.txt
ov_SC06_025_UNDEF_FUNCS := build/ov_SC06_025/undefined_funcs_auto.txt

# --- ov_SC06_027 (location overlay SC06/FILE_027, vram 0x80128158 — onboarded by new_overlay.sh) ---
ov_SC06_027_EXE        := extracted/retail/SC06.CD.dir/FILE_027.dir/0.4.dec
ov_SC06_027_NAME       := ov_SC06_027
ov_SC06_027_OUT_DIR    := build/ov_SC06_027
ov_SC06_027_OUT        := $(ov_SC06_027_OUT_DIR)/$(ov_SC06_027_NAME)
ov_SC06_027_ELF        := $(ov_SC06_027_OUT).elf
ov_SC06_027_MAPFILE    := $(ov_SC06_027_OUT).map
ov_SC06_027_LD_SCRIPT  := $(ov_SC06_027_OUT).ld
ov_SC06_027_SPLAT_YAML := config/splat.ov_SC06_027.yaml
ov_SC06_027_JTBL_INTERLEAVE := --order tail.data.o,ov_SC06_027.o,ov_SC06_027_jr_8012ACE0.o,tail2.data.o,ov_SC06_027_jr_80135888.o,tail3.data.o,ov_SC06_027_jr_80135A4C.o,tail4.data.o,ov_SC06_027_jr_80135D20.o,tail5.data.o,ov_SC06_027_jr_801380E0.o,ov_SC06_027_o0c.o,tail6.data.o,ov_SC06_027_jr_8013F350.o,tail7.data.o,ov_SC06_027_jr_8013FFD8.o,tail8.data.o,ov_SC06_027_jr_80140608.o,tail9.data.o,ov_SC06_027_jr_8015444C.o,ov_SC06_027_jr_80154C24.o,ov_SC06_027_jr_801588CC.o,ov_SC06_027_jr_80159C84.o,tail10.data.o,ov_SC06_027_jr_8015A3C8.o,tail11.data.o,ov_SC06_027_jr_8015AE2C.o,tail12.data.o,ov_SC06_027_jr_8015C32C.o,tail13.data.o,ov_SC06_027_jr_8016AB6C.o,tail14.data.o,ov_SC06_027_jr_80171B4C.o,ov_SC06_027_jr_801734BC.o,tail15.data.o,ov_SC06_027_jr_801789AC.o,ov_SC06_027_jr_80178D40.o,tail16.data.o,ov_SC06_027_jr_8017A4AC.o,tail17.data.o,ov_SC06_027_jr_8017AE2C.o,ov_SC06_027_jr_8017BEBC.o,tail18.data.o,trailing.o  # Phase-26 §8 jtbl-rodata carve
build/src/ov_SC06_027/ov_SC06_027.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14
build/src/ov_SC06_027/ov_SC06_027_jr_8012ACE0.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0xcc,+0xe0
build/src/ov_SC06_027/ov_SC06_027_jr_80135D20.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC06_027/ov_SC06_027_jr_8013F350.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC06_027/ov_SC06_027_jr_8013FFD8.o: JTBL_PADS := 0,0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38,+0x58
build/src/ov_SC06_027/ov_SC06_027_jr_8015444C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x70
build/src/ov_SC06_027/ov_SC06_027_jr_80154C24.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x24
build/src/ov_SC06_027/ov_SC06_027_jr_801588CC.o: JTBL_PADS := 0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x28,+0x48
build/src/ov_SC06_027/ov_SC06_027_jr_80159C84.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC06_027/ov_SC06_027_jr_8015AE2C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC06_027/ov_SC06_027_jr_8016AB6C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC06_027/ov_SC06_027_jr_80178D40.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x178
build/src/ov_SC06_027/ov_SC06_027_o0c.o: JTBL_PADS := 0,4,4,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x38,+0xa8,+0x118
ov_SC06_027_CHECK_SHA  := config/check.ov_SC06_027.sha
ov_SC06_027_SYMBOLS    := config/symbols.ov_SC06_027.txt
ov_SC06_027_SIG        := .run/sig.ov_SC06_027.jsonl
ov_SC06_027_GHIDRA_PROG := ov_SC06_027
ov_SC06_027_VRAM_BASE  := 0x80128158
ov_SC06_027_TEXT_LO    := 0x80128158
ov_SC06_027_TEXT_HI    := 0x8019D42F
ov_SC06_027_ASM_DIR     := asm/ov_SC06_027
ov_SC06_027_SRC_DIR     := src/ov_SC06_027
ov_SC06_027_UNDEF_SYMS  := build/ov_SC06_027/undefined_syms_auto.txt
ov_SC06_027_UNDEF_FUNCS := build/ov_SC06_027/undefined_funcs_auto.txt

# --- ov_SC06_029 (location overlay SC06/FILE_029, vram 0x80128158 — onboarded by new_overlay.sh) ---
ov_SC06_029_EXE        := extracted/retail/SC06.CD.dir/FILE_029.dir/0.4.dec
ov_SC06_029_NAME       := ov_SC06_029
ov_SC06_029_OUT_DIR    := build/ov_SC06_029
ov_SC06_029_OUT        := $(ov_SC06_029_OUT_DIR)/$(ov_SC06_029_NAME)
ov_SC06_029_ELF        := $(ov_SC06_029_OUT).elf
ov_SC06_029_MAPFILE    := $(ov_SC06_029_OUT).map
ov_SC06_029_LD_SCRIPT  := $(ov_SC06_029_OUT).ld
ov_SC06_029_SPLAT_YAML := config/splat.ov_SC06_029.yaml
ov_SC06_029_JTBL_INTERLEAVE := --order tail.data.o,ov_SC06_029.o,ov_SC06_029_jr_8012ACE0.o,tail2.data.o,ov_SC06_029_jr_80135888.o,tail3.data.o,ov_SC06_029_jr_80135A4C.o,tail4.data.o,ov_SC06_029_jr_80135D20.o,tail5.data.o,ov_SC06_029_jr_801380E0.o,ov_SC06_029_o0c.o,tail6.data.o,ov_SC06_029_jr_8013F350.o,tail7.data.o,ov_SC06_029_jr_8013FFD8.o,tail8.data.o,ov_SC06_029_jr_80140608.o,tail9.data.o,ov_SC06_029_jr_8015444C.o,ov_SC06_029_jr_80154C24.o,ov_SC06_029_jr_801588CC.o,ov_SC06_029_jr_80159C84.o,tail10.data.o,ov_SC06_029_jr_8015A3C8.o,tail11.data.o,ov_SC06_029_jr_8015AE2C.o,tail12.data.o,ov_SC06_029_jr_8015C32C.o,tail13.data.o,ov_SC06_029_jr_8016AB6C.o,tail14.data.o,ov_SC06_029_jr_80171B4C.o,ov_SC06_029_jr_801734BC.o,tail15.data.o,ov_SC06_029_jr_801789AC.o,ov_SC06_029_jr_80178D40.o,tail16.data.o,ov_SC06_029_jr_8017A4AC.o,tail17.data.o,ov_SC06_029_jr_8017AE2C.o,tail18.data.o,ov_SC06_029_jr_8017C954.o,tail19.data.o,trailing.o  # Phase-26 §8 jtbl-rodata carve
build/src/ov_SC06_029/ov_SC06_029.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14
build/src/ov_SC06_029/ov_SC06_029_jr_8012ACE0.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0xcc,+0xe0
build/src/ov_SC06_029/ov_SC06_029_jr_80135D20.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC06_029/ov_SC06_029_jr_8013F350.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC06_029/ov_SC06_029_jr_8013FFD8.o: JTBL_PADS := 0,0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38,+0x58
build/src/ov_SC06_029/ov_SC06_029_jr_8015444C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x70
build/src/ov_SC06_029/ov_SC06_029_jr_80154C24.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x24
build/src/ov_SC06_029/ov_SC06_029_jr_801588CC.o: JTBL_PADS := 0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x28,+0x48
build/src/ov_SC06_029/ov_SC06_029_jr_80159C84.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC06_029/ov_SC06_029_jr_8015AE2C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC06_029/ov_SC06_029_jr_8016AB6C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC06_029/ov_SC06_029_jr_80178D40.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x178
build/src/ov_SC06_029/ov_SC06_029_jr_8017C954.o: JTBL_PADS := 0,0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x58
build/src/ov_SC06_029/ov_SC06_029_o0c.o: JTBL_PADS := 0,4,4,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x38,+0xa8,+0x118
ov_SC06_029_CHECK_SHA  := config/check.ov_SC06_029.sha
ov_SC06_029_SYMBOLS    := config/symbols.ov_SC06_029.txt
ov_SC06_029_SIG        := .run/sig.ov_SC06_029.jsonl
ov_SC06_029_GHIDRA_PROG := ov_SC06_029
ov_SC06_029_VRAM_BASE  := 0x80128158
ov_SC06_029_TEXT_LO    := 0x80128158
ov_SC06_029_TEXT_HI    := 0x801E218F
ov_SC06_029_ASM_DIR     := asm/ov_SC06_029
ov_SC06_029_SRC_DIR     := src/ov_SC06_029
ov_SC06_029_UNDEF_SYMS  := build/ov_SC06_029/undefined_syms_auto.txt
ov_SC06_029_UNDEF_FUNCS := build/ov_SC06_029/undefined_funcs_auto.txt

# --- ov_SC06_030 (location overlay SC06/FILE_030, vram 0x80128158 — onboarded by new_overlay.sh) ---
ov_SC06_030_EXE        := extracted/retail/SC06.CD.dir/FILE_030.dir/0.4.dec
ov_SC06_030_NAME       := ov_SC06_030
ov_SC06_030_OUT_DIR    := build/ov_SC06_030
ov_SC06_030_OUT        := $(ov_SC06_030_OUT_DIR)/$(ov_SC06_030_NAME)
ov_SC06_030_ELF        := $(ov_SC06_030_OUT).elf
ov_SC06_030_MAPFILE    := $(ov_SC06_030_OUT).map
ov_SC06_030_LD_SCRIPT  := $(ov_SC06_030_OUT).ld
ov_SC06_030_SPLAT_YAML := config/splat.ov_SC06_030.yaml
ov_SC06_030_JTBL_INTERLEAVE := --order tail.data.o,ov_SC06_030.o,ov_SC06_030_jr_8012ACE0.o,tail2.data.o,ov_SC06_030_jr_80135888.o,tail3.data.o,ov_SC06_030_jr_80135A4C.o,tail4.data.o,ov_SC06_030_jr_80135D20.o,tail5.data.o,ov_SC06_030_jr_801380E0.o,ov_SC06_030_o0c.o,tail6.data.o,ov_SC06_030_jr_8013F350.o,tail7.data.o,ov_SC06_030_jr_8013FFD8.o,tail8.data.o,ov_SC06_030_jr_80140608.o,tail9.data.o,ov_SC06_030_jr_8015444C.o,ov_SC06_030_jr_80154C24.o,ov_SC06_030_jr_801588CC.o,ov_SC06_030_jr_80159C84.o,tail10.data.o,ov_SC06_030_jr_8015A3C8.o,tail11.data.o,ov_SC06_030_jr_8015AE2C.o,tail12.data.o,ov_SC06_030_jr_8015C32C.o,tail13.data.o,ov_SC06_030_jr_8016AB6C.o,tail14.data.o,ov_SC06_030_jr_80171B4C.o,ov_SC06_030_jr_801734BC.o,tail15.data.o,ov_SC06_030_jr_801789AC.o,ov_SC06_030_jr_80178D40.o,tail16.data.o,ov_SC06_030_jr_8017A4AC.o,tail17.data.o,ov_SC06_030_jr_8017AE2C.o,tail18.data.o,ov_SC06_030_jr_8017C8D0.o,tail19.data.o,ov_SC06_030_jr_8017F65C.o,tail20.data.o,trailing.o  # Phase-26 §8 jtbl-rodata carve
build/src/ov_SC06_030/ov_SC06_030.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14
build/src/ov_SC06_030/ov_SC06_030_jr_8012ACE0.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0xcc,+0xe0
build/src/ov_SC06_030/ov_SC06_030_jr_80135D20.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC06_030/ov_SC06_030_jr_8013F350.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC06_030/ov_SC06_030_jr_8013FFD8.o: JTBL_PADS := 0,0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38,+0x58
build/src/ov_SC06_030/ov_SC06_030_jr_8015444C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x70
build/src/ov_SC06_030/ov_SC06_030_jr_80154C24.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x24
build/src/ov_SC06_030/ov_SC06_030_jr_801588CC.o: JTBL_PADS := 0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x28,+0x48
build/src/ov_SC06_030/ov_SC06_030_jr_80159C84.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC06_030/ov_SC06_030_jr_8015AE2C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC06_030/ov_SC06_030_jr_8016AB6C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC06_030/ov_SC06_030_jr_80178D40.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x178
build/src/ov_SC06_030/ov_SC06_030_jr_8017C8D0.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x40
build/src/ov_SC06_030/ov_SC06_030_jr_8017F65C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC06_030/ov_SC06_030_o0c.o: JTBL_PADS := 0,4,4,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x38,+0xa8,+0x118
ov_SC06_030_CHECK_SHA  := config/check.ov_SC06_030.sha
ov_SC06_030_SYMBOLS    := config/symbols.ov_SC06_030.txt
ov_SC06_030_SIG        := .run/sig.ov_SC06_030.jsonl
ov_SC06_030_GHIDRA_PROG := ov_SC06_030
ov_SC06_030_VRAM_BASE  := 0x80128158
ov_SC06_030_TEXT_LO    := 0x80128158
ov_SC06_030_TEXT_HI    := 0x801BA087
ov_SC06_030_ASM_DIR     := asm/ov_SC06_030
ov_SC06_030_SRC_DIR     := src/ov_SC06_030
ov_SC06_030_UNDEF_SYMS  := build/ov_SC06_030/undefined_syms_auto.txt
ov_SC06_030_UNDEF_FUNCS := build/ov_SC06_030/undefined_funcs_auto.txt

# --- ov_SC06_032 (location overlay SC06/FILE_032, vram 0x80128158 — onboarded by new_overlay.sh) ---
ov_SC06_032_EXE        := extracted/retail/SC06.CD.dir/FILE_032.dir/0.4.dec
ov_SC06_032_NAME       := ov_SC06_032
ov_SC06_032_OUT_DIR    := build/ov_SC06_032
ov_SC06_032_OUT        := $(ov_SC06_032_OUT_DIR)/$(ov_SC06_032_NAME)
ov_SC06_032_ELF        := $(ov_SC06_032_OUT).elf
ov_SC06_032_MAPFILE    := $(ov_SC06_032_OUT).map
ov_SC06_032_LD_SCRIPT  := $(ov_SC06_032_OUT).ld
ov_SC06_032_SPLAT_YAML := config/splat.ov_SC06_032.yaml
ov_SC06_032_JTBL_INTERLEAVE := --order tail.data.o,ov_SC06_032.o,ov_SC06_032_jr_8012ACE0.o,tail2.data.o,ov_SC06_032_jr_80135888.o,tail3.data.o,ov_SC06_032_jr_80135A4C.o,tail4.data.o,ov_SC06_032_jr_80135D20.o,tail5.data.o,ov_SC06_032_jr_801380E0.o,ov_SC06_032_o0c.o,tail6.data.o,ov_SC06_032_jr_8013F350.o,tail7.data.o,ov_SC06_032_jr_8013FFD8.o,tail8.data.o,ov_SC06_032_jr_80140608.o,tail9.data.o,ov_SC06_032_jr_8015444C.o,ov_SC06_032_jr_80154C24.o,ov_SC06_032_jr_801588CC.o,ov_SC06_032_jr_80159C84.o,tail10.data.o,ov_SC06_032_jr_8015A3C8.o,tail11.data.o,ov_SC06_032_jr_8015AE2C.o,tail12.data.o,ov_SC06_032_jr_8015C32C.o,tail13.data.o,ov_SC06_032_jr_8016AB6C.o,tail14.data.o,ov_SC06_032_jr_80171B4C.o,ov_SC06_032_jr_801734BC.o,tail15.data.o,ov_SC06_032_jr_801789AC.o,ov_SC06_032_jr_80178D40.o,tail16.data.o,ov_SC06_032_jr_8017A4AC.o,tail17.data.o,ov_SC06_032_jr_8017AE2C.o,ov_SC06_032_jr_8017C24C.o,ov_SC06_032_jr_80181014.o,tail18.data.o,ov_SC06_032_jr_80182890.o,tail19.data.o,ov_SC06_032_jr_8018FCE8.o,ov_SC06_032_jr_801902EC.o,tail20.data.o,ov_SC06_032_jr_801919A0.o,tail21.data.o,trailing.o  # Phase-26 §8 jtbl-rodata carve
build/src/ov_SC06_032/ov_SC06_032.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14
build/src/ov_SC06_032/ov_SC06_032_jr_8012ACE0.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0xcc,+0xe0
build/src/ov_SC06_032/ov_SC06_032_jr_80135D20.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC06_032/ov_SC06_032_jr_8013F350.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC06_032/ov_SC06_032_jr_8013FFD8.o: JTBL_PADS := 0,0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38,+0x58
build/src/ov_SC06_032/ov_SC06_032_jr_8015444C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x70
build/src/ov_SC06_032/ov_SC06_032_jr_80154C24.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x24
build/src/ov_SC06_032/ov_SC06_032_jr_801588CC.o: JTBL_PADS := 0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x28,+0x48
build/src/ov_SC06_032/ov_SC06_032_jr_80159C84.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC06_032/ov_SC06_032_jr_8015AE2C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC06_032/ov_SC06_032_jr_8016AB6C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC06_032/ov_SC06_032_jr_80178D40.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x178
build/src/ov_SC06_032/ov_SC06_032_jr_8017C24C.o: JTBL_PADS := 0,0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38
build/src/ov_SC06_032/ov_SC06_032_jr_80181014.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC06_032/ov_SC06_032_jr_801902EC.o: JTBL_PADS := 0,0,4  # §8e pads — None table(s), byte-proven by jtbl_pads_fix
build/src/ov_SC06_032/ov_SC06_032_o0c.o: JTBL_PADS := 0,4,4,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x38,+0xa8,+0x118
ov_SC06_032_CHECK_SHA  := config/check.ov_SC06_032.sha
ov_SC06_032_SYMBOLS    := config/symbols.ov_SC06_032.txt
ov_SC06_032_SIG        := .run/sig.ov_SC06_032.jsonl
ov_SC06_032_GHIDRA_PROG := ov_SC06_032
ov_SC06_032_VRAM_BASE  := 0x80128158
ov_SC06_032_TEXT_LO    := 0x80128158
ov_SC06_032_TEXT_HI    := 0x801D116F
ov_SC06_032_ASM_DIR     := asm/ov_SC06_032
ov_SC06_032_SRC_DIR     := src/ov_SC06_032
ov_SC06_032_UNDEF_SYMS  := build/ov_SC06_032/undefined_syms_auto.txt
ov_SC06_032_UNDEF_FUNCS := build/ov_SC06_032/undefined_funcs_auto.txt

# --- ov_SC06_033 (location overlay SC06/FILE_033, vram 0x80128158 — onboarded by new_overlay.sh) ---
ov_SC06_033_EXE        := extracted/retail/SC06.CD.dir/FILE_033.dir/0.4.dec
ov_SC06_033_NAME       := ov_SC06_033
ov_SC06_033_OUT_DIR    := build/ov_SC06_033
ov_SC06_033_OUT        := $(ov_SC06_033_OUT_DIR)/$(ov_SC06_033_NAME)
ov_SC06_033_ELF        := $(ov_SC06_033_OUT).elf
ov_SC06_033_MAPFILE    := $(ov_SC06_033_OUT).map
ov_SC06_033_LD_SCRIPT  := $(ov_SC06_033_OUT).ld
ov_SC06_033_SPLAT_YAML := config/splat.ov_SC06_033.yaml
ov_SC06_033_JTBL_INTERLEAVE := --order tail.data.o,ov_SC06_033.o,ov_SC06_033_jr_8012ACE0.o,tail2.data.o,ov_SC06_033_jr_80135888.o,tail3.data.o,ov_SC06_033_jr_80135A4C.o,tail4.data.o,ov_SC06_033_jr_80135D20.o,tail5.data.o,ov_SC06_033_jr_801380E0.o,ov_SC06_033_o0c.o,tail6.data.o,ov_SC06_033_jr_8013F350.o,tail7.data.o,ov_SC06_033_jr_8013FFD8.o,tail8.data.o,ov_SC06_033_jr_80140608.o,tail9.data.o,ov_SC06_033_jr_8015444C.o,ov_SC06_033_jr_80154C24.o,ov_SC06_033_jr_801588CC.o,ov_SC06_033_jr_80159C84.o,tail10.data.o,ov_SC06_033_jr_8015A3C8.o,tail11.data.o,ov_SC06_033_jr_8015AE2C.o,tail12.data.o,ov_SC06_033_jr_8015C32C.o,tail13.data.o,ov_SC06_033_jr_8016AB6C.o,tail14.data.o,ov_SC06_033_jr_80171B4C.o,ov_SC06_033_jr_801734BC.o,tail15.data.o,ov_SC06_033_jr_801789AC.o,ov_SC06_033_jr_80178D40.o,tail16.data.o,ov_SC06_033_jr_8017A4AC.o,tail17.data.o,ov_SC06_033_jr_8017AE2C.o,ov_SC06_033_jr_8017C24C.o,ov_SC06_033_jr_801836FC.o,ov_SC06_033_jr_80184CF8.o,tail18.data.o,ov_SC06_033_jr_80186574.o,tail19.data.o,ov_SC06_033_jr_8018BCD4.o,ov_SC06_033_jr_8018C2D8.o,tail20.data.o,ov_SC06_033_jr_8018D98C.o,tail21.data.o,trailing.o  # Phase-26 §8 jtbl-rodata carve
build/src/ov_SC06_033/ov_SC06_033.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14
build/src/ov_SC06_033/ov_SC06_033_jr_8012ACE0.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0xcc,+0xe0
build/src/ov_SC06_033/ov_SC06_033_jr_80135D20.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC06_033/ov_SC06_033_jr_8013F350.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC06_033/ov_SC06_033_jr_8013FFD8.o: JTBL_PADS := 0,0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38,+0x58
build/src/ov_SC06_033/ov_SC06_033_jr_8015444C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x70
build/src/ov_SC06_033/ov_SC06_033_jr_80154C24.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x24
build/src/ov_SC06_033/ov_SC06_033_jr_801588CC.o: JTBL_PADS := 0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x28,+0x48
build/src/ov_SC06_033/ov_SC06_033_jr_80159C84.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC06_033/ov_SC06_033_jr_8015AE2C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC06_033/ov_SC06_033_jr_8016AB6C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC06_033/ov_SC06_033_jr_80178D40.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x178
build/src/ov_SC06_033/ov_SC06_033_jr_8017C24C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC06_033/ov_SC06_033_jr_801836FC.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC06_033/ov_SC06_033_jr_80184CF8.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC06_033/ov_SC06_033_jr_8018C2D8.o: JTBL_PADS := 0,0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x28,+0x40
build/src/ov_SC06_033/ov_SC06_033_o0c.o: JTBL_PADS := 0,4,4,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x38,+0xa8,+0x118
ov_SC06_033_CHECK_SHA  := config/check.ov_SC06_033.sha
ov_SC06_033_SYMBOLS    := config/symbols.ov_SC06_033.txt
ov_SC06_033_SIG        := .run/sig.ov_SC06_033.jsonl
ov_SC06_033_GHIDRA_PROG := ov_SC06_033
ov_SC06_033_VRAM_BASE  := 0x80128158
ov_SC06_033_TEXT_LO    := 0x80128158
ov_SC06_033_TEXT_HI    := 0x801D0FEF
ov_SC06_033_ASM_DIR     := asm/ov_SC06_033
ov_SC06_033_SRC_DIR     := src/ov_SC06_033
ov_SC06_033_UNDEF_SYMS  := build/ov_SC06_033/undefined_syms_auto.txt
ov_SC06_033_UNDEF_FUNCS := build/ov_SC06_033/undefined_funcs_auto.txt

# --- ov_SC07_001 (location overlay SC07/FILE_001, vram 0x80128158 — onboarded by new_overlay.sh) ---
ov_SC07_001_EXE        := extracted/retail/SC07.CD.dir/FILE_001.dir/0.4.dec
ov_SC07_001_NAME       := ov_SC07_001
ov_SC07_001_OUT_DIR    := build/ov_SC07_001
ov_SC07_001_OUT        := $(ov_SC07_001_OUT_DIR)/$(ov_SC07_001_NAME)
ov_SC07_001_ELF        := $(ov_SC07_001_OUT).elf
ov_SC07_001_MAPFILE    := $(ov_SC07_001_OUT).map
ov_SC07_001_LD_SCRIPT  := $(ov_SC07_001_OUT).ld
ov_SC07_001_SPLAT_YAML := config/splat.ov_SC07_001.yaml
ov_SC07_001_JTBL_INTERLEAVE := --order tail.data.o,ov_SC07_001.o,ov_SC07_001_jr_8012ACE0.o,tail2.data.o,ov_SC07_001_jr_80135888.o,tail3.data.o,ov_SC07_001_jr_80135A4C.o,tail4.data.o,ov_SC07_001_jr_80135D20.o,tail5.data.o,ov_SC07_001_jr_801380E0.o,ov_SC07_001_o0c.o,tail6.data.o,ov_SC07_001_jr_8013F350.o,tail7.data.o,ov_SC07_001_jr_8013FFD8.o,tail8.data.o,ov_SC07_001_jr_80140608.o,tail9.data.o,ov_SC07_001_jr_8015444C.o,ov_SC07_001_jr_80154C24.o,ov_SC07_001_jr_801588CC.o,ov_SC07_001_jr_80159C84.o,tail10.data.o,ov_SC07_001_jr_8015A3C8.o,tail11.data.o,ov_SC07_001_jr_8015AE2C.o,tail12.data.o,ov_SC07_001_jr_8015C32C.o,tail13.data.o,ov_SC07_001_jr_8016AB6C.o,tail14.data.o,ov_SC07_001_jr_80171B4C.o,ov_SC07_001_jr_801734BC.o,tail15.data.o,ov_SC07_001_jr_801789AC.o,ov_SC07_001_jr_80178D40.o,tail16.data.o,ov_SC07_001_jr_8017A4AC.o,tail17.data.o,ov_SC07_001_jr_8017AE2C.o,ov_SC07_001_jr_8017BEBC.o,tail18.data.o,trailing.o  # Phase-26 §8 jtbl-rodata carve
build/src/ov_SC07_001/ov_SC07_001.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14
build/src/ov_SC07_001/ov_SC07_001_jr_8012ACE0.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0xcc,+0xe0
build/src/ov_SC07_001/ov_SC07_001_jr_80135D20.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC07_001/ov_SC07_001_jr_8013F350.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC07_001/ov_SC07_001_jr_8013FFD8.o: JTBL_PADS := 0,0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38,+0x58
build/src/ov_SC07_001/ov_SC07_001_jr_8015444C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x70
build/src/ov_SC07_001/ov_SC07_001_jr_80154C24.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x24
build/src/ov_SC07_001/ov_SC07_001_jr_801588CC.o: JTBL_PADS := 0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x28,+0x48
build/src/ov_SC07_001/ov_SC07_001_jr_80159C84.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC07_001/ov_SC07_001_jr_8015AE2C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC07_001/ov_SC07_001_jr_8016AB6C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC07_001/ov_SC07_001_jr_80178D40.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x178
build/src/ov_SC07_001/ov_SC07_001_o0c.o: JTBL_PADS := 0,4,4,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x38,+0xa8,+0x118
ov_SC07_001_CHECK_SHA  := config/check.ov_SC07_001.sha
ov_SC07_001_SYMBOLS    := config/symbols.ov_SC07_001.txt
ov_SC07_001_SIG        := .run/sig.ov_SC07_001.jsonl
ov_SC07_001_GHIDRA_PROG := ov_SC07_001
ov_SC07_001_VRAM_BASE  := 0x80128158
ov_SC07_001_TEXT_LO    := 0x80128158
ov_SC07_001_TEXT_HI    := 0x801AAF0F
ov_SC07_001_ASM_DIR     := asm/ov_SC07_001
ov_SC07_001_SRC_DIR     := src/ov_SC07_001
ov_SC07_001_UNDEF_SYMS  := build/ov_SC07_001/undefined_syms_auto.txt
ov_SC07_001_UNDEF_FUNCS := build/ov_SC07_001/undefined_funcs_auto.txt

# --- ov_SC07_002 (location overlay SC07/FILE_002, vram 0x80128158 — onboarded by new_overlay.sh) ---
ov_SC07_002_EXE        := extracted/retail/SC07.CD.dir/FILE_002.dir/0.4.dec
ov_SC07_002_NAME       := ov_SC07_002
ov_SC07_002_OUT_DIR    := build/ov_SC07_002
ov_SC07_002_OUT        := $(ov_SC07_002_OUT_DIR)/$(ov_SC07_002_NAME)
ov_SC07_002_ELF        := $(ov_SC07_002_OUT).elf
ov_SC07_002_MAPFILE    := $(ov_SC07_002_OUT).map
ov_SC07_002_LD_SCRIPT  := $(ov_SC07_002_OUT).ld
ov_SC07_002_SPLAT_YAML := config/splat.ov_SC07_002.yaml
ov_SC07_002_JTBL_INTERLEAVE := --order tail.data.o,ov_SC07_002.o,ov_SC07_002_jr_8012ACE0.o,tail2.data.o,ov_SC07_002_jr_80135888.o,tail3.data.o,ov_SC07_002_jr_80135A4C.o,tail4.data.o,ov_SC07_002_jr_80135D20.o,tail5.data.o,ov_SC07_002_jr_801380E0.o,ov_SC07_002_o0c.o,tail6.data.o,ov_SC07_002_jr_8013F350.o,tail7.data.o,ov_SC07_002_jr_8013FFD8.o,tail8.data.o,ov_SC07_002_jr_80140608.o,tail9.data.o,ov_SC07_002_jr_8015444C.o,ov_SC07_002_jr_80154C24.o,ov_SC07_002_jr_801588CC.o,ov_SC07_002_jr_80159C84.o,tail10.data.o,ov_SC07_002_jr_8015A3C8.o,tail11.data.o,ov_SC07_002_jr_8015AE2C.o,tail12.data.o,ov_SC07_002_jr_8015C32C.o,tail13.data.o,ov_SC07_002_jr_8016AB6C.o,tail14.data.o,ov_SC07_002_jr_80171B4C.o,ov_SC07_002_jr_801734BC.o,tail15.data.o,ov_SC07_002_jr_801789AC.o,ov_SC07_002_jr_80178D40.o,tail16.data.o,ov_SC07_002_jr_8017A4AC.o,tail17.data.o,ov_SC07_002_jr_8017AE2C.o,tail18.data.o,ov_SC07_002_jr_8017C8D0.o,tail19.data.o,trailing.o  # Phase-26 §8 jtbl-rodata carve
build/src/ov_SC07_002/ov_SC07_002.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14
build/src/ov_SC07_002/ov_SC07_002_jr_8012ACE0.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0xcc,+0xe0
build/src/ov_SC07_002/ov_SC07_002_jr_80135D20.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC07_002/ov_SC07_002_jr_8013F350.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC07_002/ov_SC07_002_jr_8013FFD8.o: JTBL_PADS := 0,0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38,+0x58
build/src/ov_SC07_002/ov_SC07_002_jr_8015444C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x70
build/src/ov_SC07_002/ov_SC07_002_jr_80154C24.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x24
build/src/ov_SC07_002/ov_SC07_002_jr_801588CC.o: JTBL_PADS := 0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x28,+0x48
build/src/ov_SC07_002/ov_SC07_002_jr_80159C84.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC07_002/ov_SC07_002_jr_8015AE2C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC07_002/ov_SC07_002_jr_8016AB6C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC07_002/ov_SC07_002_jr_80178D40.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x178
build/src/ov_SC07_002/ov_SC07_002_o0c.o: JTBL_PADS := 0,4,4,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x38,+0xa8,+0x118
ov_SC07_002_CHECK_SHA  := config/check.ov_SC07_002.sha
ov_SC07_002_SYMBOLS    := config/symbols.ov_SC07_002.txt
ov_SC07_002_SIG        := .run/sig.ov_SC07_002.jsonl
ov_SC07_002_GHIDRA_PROG := ov_SC07_002
ov_SC07_002_VRAM_BASE  := 0x80128158
ov_SC07_002_TEXT_LO    := 0x80128158
ov_SC07_002_TEXT_HI    := 0x801A00D7
ov_SC07_002_ASM_DIR     := asm/ov_SC07_002
ov_SC07_002_SRC_DIR     := src/ov_SC07_002
ov_SC07_002_UNDEF_SYMS  := build/ov_SC07_002/undefined_syms_auto.txt
ov_SC07_002_UNDEF_FUNCS := build/ov_SC07_002/undefined_funcs_auto.txt

# --- ov_SC07_008 (location overlay SC07/FILE_008, vram 0x80128158 — onboarded by new_overlay.sh) ---
ov_SC07_008_EXE        := extracted/retail/SC07.CD.dir/FILE_008.dir/0.4.dec
ov_SC07_008_NAME       := ov_SC07_008
ov_SC07_008_OUT_DIR    := build/ov_SC07_008
ov_SC07_008_OUT        := $(ov_SC07_008_OUT_DIR)/$(ov_SC07_008_NAME)
ov_SC07_008_ELF        := $(ov_SC07_008_OUT).elf
ov_SC07_008_MAPFILE    := $(ov_SC07_008_OUT).map
ov_SC07_008_LD_SCRIPT  := $(ov_SC07_008_OUT).ld
ov_SC07_008_SPLAT_YAML := config/splat.ov_SC07_008.yaml
ov_SC07_008_JTBL_INTERLEAVE := --order tail.data.o,ov_SC07_008.o,ov_SC07_008_jr_8012ACE0.o,tail2.data.o,ov_SC07_008_jr_80135888.o,tail3.data.o,ov_SC07_008_jr_80135A4C.o,tail4.data.o,ov_SC07_008_jr_80135D20.o,tail5.data.o,ov_SC07_008_jr_801380E0.o,ov_SC07_008_o0c.o,tail6.data.o,ov_SC07_008_jr_8013F350.o,tail7.data.o,ov_SC07_008_jr_8013FFD8.o,tail8.data.o,ov_SC07_008_jr_80140608.o,tail9.data.o,ov_SC07_008_jr_8015444C.o,ov_SC07_008_jr_80154C24.o,ov_SC07_008_jr_801588CC.o,ov_SC07_008_jr_80159C84.o,tail10.data.o,ov_SC07_008_jr_8015A3C8.o,tail11.data.o,ov_SC07_008_jr_8015AE2C.o,tail12.data.o,ov_SC07_008_jr_8015C32C.o,tail13.data.o,ov_SC07_008_jr_8016AB6C.o,tail14.data.o,ov_SC07_008_jr_80171B4C.o,ov_SC07_008_jr_801734BC.o,tail15.data.o,ov_SC07_008_jr_801789AC.o,ov_SC07_008_jr_80178D40.o,tail16.data.o,ov_SC07_008_jr_8017A4AC.o,tail17.data.o,ov_SC07_008_jr_8017AE2C.o,ov_SC07_008_jr_8017BEBC.o,tail18.data.o,trailing.o  # Phase-26 §8 jtbl-rodata carve
build/src/ov_SC07_008/ov_SC07_008.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14
build/src/ov_SC07_008/ov_SC07_008_jr_8012ACE0.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0xcc,+0xe0
build/src/ov_SC07_008/ov_SC07_008_jr_80135D20.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC07_008/ov_SC07_008_jr_8013F350.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC07_008/ov_SC07_008_jr_8013FFD8.o: JTBL_PADS := 0,0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38,+0x58
build/src/ov_SC07_008/ov_SC07_008_jr_8015444C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x70
build/src/ov_SC07_008/ov_SC07_008_jr_80154C24.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x24
build/src/ov_SC07_008/ov_SC07_008_jr_801588CC.o: JTBL_PADS := 0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x28,+0x48
build/src/ov_SC07_008/ov_SC07_008_jr_80159C84.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC07_008/ov_SC07_008_jr_8015AE2C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC07_008/ov_SC07_008_jr_8016AB6C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC07_008/ov_SC07_008_jr_80178D40.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x178
build/src/ov_SC07_008/ov_SC07_008_o0c.o: JTBL_PADS := 0,4,4,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x38,+0xa8,+0x118
ov_SC07_008_CHECK_SHA  := config/check.ov_SC07_008.sha
ov_SC07_008_SYMBOLS    := config/symbols.ov_SC07_008.txt
ov_SC07_008_SIG        := .run/sig.ov_SC07_008.jsonl
ov_SC07_008_GHIDRA_PROG := ov_SC07_008
ov_SC07_008_VRAM_BASE  := 0x80128158
ov_SC07_008_TEXT_LO    := 0x80128158
ov_SC07_008_TEXT_HI    := 0x80196747
ov_SC07_008_ASM_DIR     := asm/ov_SC07_008
ov_SC07_008_SRC_DIR     := src/ov_SC07_008
ov_SC07_008_UNDEF_SYMS  := build/ov_SC07_008/undefined_syms_auto.txt
ov_SC07_008_UNDEF_FUNCS := build/ov_SC07_008/undefined_funcs_auto.txt

# --- ov_SC07_009 (location overlay SC07/FILE_009, vram 0x80128158 — onboarded by new_overlay.sh) ---
ov_SC07_009_EXE        := extracted/retail/SC07.CD.dir/FILE_009.dir/0.4.dec
ov_SC07_009_NAME       := ov_SC07_009
ov_SC07_009_OUT_DIR    := build/ov_SC07_009
ov_SC07_009_OUT        := $(ov_SC07_009_OUT_DIR)/$(ov_SC07_009_NAME)
ov_SC07_009_ELF        := $(ov_SC07_009_OUT).elf
ov_SC07_009_MAPFILE    := $(ov_SC07_009_OUT).map
ov_SC07_009_LD_SCRIPT  := $(ov_SC07_009_OUT).ld
ov_SC07_009_SPLAT_YAML := config/splat.ov_SC07_009.yaml
ov_SC07_009_JTBL_INTERLEAVE := --order tail.data.o,ov_SC07_009.o,ov_SC07_009_jr_8012ACE0.o,tail2.data.o,ov_SC07_009_jr_80135888.o,tail3.data.o,ov_SC07_009_jr_80135A4C.o,tail4.data.o,ov_SC07_009_jr_80135D20.o,tail5.data.o,ov_SC07_009_jr_801380E0.o,ov_SC07_009_o0c.o,tail6.data.o,ov_SC07_009_jr_8013F350.o,tail7.data.o,ov_SC07_009_jr_8013FFD8.o,tail8.data.o,ov_SC07_009_jr_80140608.o,tail9.data.o,ov_SC07_009_jr_8015444C.o,ov_SC07_009_jr_80154C24.o,ov_SC07_009_jr_801588CC.o,ov_SC07_009_jr_80159C84.o,tail10.data.o,ov_SC07_009_jr_8015A3C8.o,tail11.data.o,ov_SC07_009_jr_8015AE2C.o,tail12.data.o,ov_SC07_009_jr_8015C32C.o,tail13.data.o,ov_SC07_009_jr_8016AB6C.o,tail14.data.o,ov_SC07_009_jr_80171B4C.o,ov_SC07_009_jr_801734BC.o,tail15.data.o,ov_SC07_009_jr_801789AC.o,ov_SC07_009_jr_80178D40.o,tail16.data.o,ov_SC07_009_jr_8017A4AC.o,tail17.data.o,ov_SC07_009_jr_8017AE2C.o,tail18.data.o,trailing.o  # Phase-26 §8 jtbl-rodata carve
build/src/ov_SC07_009/ov_SC07_009.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14
build/src/ov_SC07_009/ov_SC07_009_jr_8012ACE0.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0xcc,+0xe0
build/src/ov_SC07_009/ov_SC07_009_jr_80135D20.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC07_009/ov_SC07_009_jr_8013F350.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC07_009/ov_SC07_009_jr_8013FFD8.o: JTBL_PADS := 0,0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38,+0x58
build/src/ov_SC07_009/ov_SC07_009_jr_8015444C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x70
build/src/ov_SC07_009/ov_SC07_009_jr_80154C24.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x24
build/src/ov_SC07_009/ov_SC07_009_jr_801588CC.o: JTBL_PADS := 0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x28,+0x48
build/src/ov_SC07_009/ov_SC07_009_jr_80159C84.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC07_009/ov_SC07_009_jr_8015AE2C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC07_009/ov_SC07_009_jr_8016AB6C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC07_009/ov_SC07_009_jr_80178D40.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x178
build/src/ov_SC07_009/ov_SC07_009_jr_8017AE2C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14
build/src/ov_SC07_009/ov_SC07_009_o0c.o: JTBL_PADS := 0,4,4,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x38,+0xa8,+0x118
ov_SC07_009_CHECK_SHA  := config/check.ov_SC07_009.sha
ov_SC07_009_SYMBOLS    := config/symbols.ov_SC07_009.txt
ov_SC07_009_SIG        := .run/sig.ov_SC07_009.jsonl
ov_SC07_009_GHIDRA_PROG := ov_SC07_009
ov_SC07_009_VRAM_BASE  := 0x80128158
ov_SC07_009_TEXT_LO    := 0x80128158
ov_SC07_009_TEXT_HI    := 0x801A3DD7
ov_SC07_009_ASM_DIR     := asm/ov_SC07_009
ov_SC07_009_SRC_DIR     := src/ov_SC07_009
ov_SC07_009_UNDEF_SYMS  := build/ov_SC07_009/undefined_syms_auto.txt
ov_SC07_009_UNDEF_FUNCS := build/ov_SC07_009/undefined_funcs_auto.txt

# --- ov_SC07_006 (location overlay SC07/FILE_006, vram 0x80128158 — onboarded by new_overlay.sh) ---
ov_SC07_006_EXE        := extracted/retail/SC07.CD.dir/FILE_006.dir/1.4.dec
ov_SC07_006_NAME       := ov_SC07_006
ov_SC07_006_OUT_DIR    := build/ov_SC07_006
ov_SC07_006_OUT        := $(ov_SC07_006_OUT_DIR)/$(ov_SC07_006_NAME)
ov_SC07_006_ELF        := $(ov_SC07_006_OUT).elf
ov_SC07_006_MAPFILE    := $(ov_SC07_006_OUT).map
ov_SC07_006_LD_SCRIPT  := $(ov_SC07_006_OUT).ld
ov_SC07_006_SPLAT_YAML := config/splat.ov_SC07_006.yaml
ov_SC07_006_JTBL_INTERLEAVE := --order tail.data.o,ov_SC07_006.o,ov_SC07_006_jr_80131340.o,tail2.data.o,ov_SC07_006_jr_80135888.o,tail3.data.o,ov_SC07_006_jr_80135A4C.o,tail4.data.o,ov_SC07_006_jr_80135D20.o,tail5.data.o,ov_SC07_006_jr_801380E0.o,ov_SC07_006_o0c.o,tail6.data.o,ov_SC07_006_jr_8013F350.o,tail7.data.o,ov_SC07_006_jr_8014032C.o,tail8.data.o,ov_SC07_006_jr_80140608.o,tail9.data.o,ov_SC07_006_jr_8015444C.o,ov_SC07_006_jr_80154C24.o,ov_SC07_006_jr_801588CC.o,ov_SC07_006_jr_80159C84.o,tail10.data.o,ov_SC07_006_jr_8015A3C8.o,tail11.data.o,ov_SC07_006_jr_8015B950.o,tail12.data.o,ov_SC07_006_jr_8015C32C.o,tail13.data.o,ov_SC07_006_jr_8016AB6C.o,ov_SC07_006_jr_8016AE5C.o,tail14.data.o,ov_SC07_006_jr_80171B4C.o,tail15.data.o,ov_SC07_006_jr_801789AC.o,ov_SC07_006_jr_80179B74.o,tail16.data.o,ov_SC07_006_jr_8017AE2C.o,ov_SC07_006_jr_8017BEBC.o,ov_SC07_006_jr_80183814.o,tail17.data.o,trailing.o  # Phase-26 §8 jtbl-rodata carve
build/src/ov_SC07_006/ov_SC07_006.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14,+0xdc
build/src/ov_SC07_006/ov_SC07_006_jr_80131340.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14
build/src/ov_SC07_006/ov_SC07_006_jr_80135D20.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC07_006/ov_SC07_006_jr_8013F350.o: JTBL_PADS := 0,0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38,+0x58
build/src/ov_SC07_006/ov_SC07_006_jr_8014032C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC07_006/ov_SC07_006_jr_8015444C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x70
build/src/ov_SC07_006/ov_SC07_006_jr_80154C24.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x24
build/src/ov_SC07_006/ov_SC07_006_jr_801588CC.o: JTBL_PADS := 0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x28,+0x48
build/src/ov_SC07_006/ov_SC07_006_jr_80159C84.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC07_006/ov_SC07_006_jr_8015A3C8.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC07_006/ov_SC07_006_jr_80171B4C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC07_006/ov_SC07_006_jr_801789AC.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC07_006/ov_SC07_006_jr_80179B74.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x90
build/src/ov_SC07_006/ov_SC07_006_jr_8017BEBC.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC07_006/ov_SC07_006_o0c.o: JTBL_PADS := 0,4,4,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x38,+0xa8,+0x118
ov_SC07_006_CHECK_SHA  := config/check.ov_SC07_006.sha
ov_SC07_006_SYMBOLS    := config/symbols.ov_SC07_006.txt
ov_SC07_006_SIG        := .run/sig.ov_SC07_006.jsonl
ov_SC07_006_GHIDRA_PROG := ov_SC07_006
ov_SC07_006_VRAM_BASE  := 0x80128158
ov_SC07_006_TEXT_LO    := 0x80128158
ov_SC07_006_TEXT_HI    := 0x801F636F
ov_SC07_006_ASM_DIR     := asm/ov_SC07_006
ov_SC07_006_SRC_DIR     := src/ov_SC07_006
ov_SC07_006_UNDEF_SYMS  := build/ov_SC07_006/undefined_syms_auto.txt
ov_SC07_006_UNDEF_FUNCS := build/ov_SC07_006/undefined_funcs_auto.txt

# --- ov_SC07_007 (location overlay SC07/FILE_007, vram 0x80128158 — onboarded by new_overlay.sh) ---
ov_SC07_007_EXE        := extracted/retail/SC07.CD.dir/FILE_007.dir/1.4.dec
ov_SC07_007_NAME       := ov_SC07_007
ov_SC07_007_OUT_DIR    := build/ov_SC07_007
ov_SC07_007_OUT        := $(ov_SC07_007_OUT_DIR)/$(ov_SC07_007_NAME)
ov_SC07_007_ELF        := $(ov_SC07_007_OUT).elf
ov_SC07_007_MAPFILE    := $(ov_SC07_007_OUT).map
ov_SC07_007_LD_SCRIPT  := $(ov_SC07_007_OUT).ld
ov_SC07_007_SPLAT_YAML := config/splat.ov_SC07_007.yaml
ov_SC07_007_JTBL_INTERLEAVE := --order tail.data.o,ov_SC07_007.o,ov_SC07_007_jr_80131340.o,tail2.data.o,ov_SC07_007_jr_80135888.o,tail3.data.o,ov_SC07_007_jr_80135A4C.o,tail4.data.o,ov_SC07_007_jr_80135D20.o,tail5.data.o,ov_SC07_007_jr_801380E0.o,ov_SC07_007_o0c.o,tail6.data.o,ov_SC07_007_jr_8013F350.o,tail7.data.o,ov_SC07_007_jr_8014032C.o,tail8.data.o,ov_SC07_007_jr_80140608.o,tail9.data.o,ov_SC07_007_jr_8015444C.o,ov_SC07_007_jr_80154C24.o,ov_SC07_007_jr_801588CC.o,ov_SC07_007_jr_80159C84.o,tail10.data.o,ov_SC07_007_jr_8015A3C8.o,tail11.data.o,ov_SC07_007_jr_8015B950.o,tail12.data.o,ov_SC07_007_jr_8015C32C.o,tail13.data.o,ov_SC07_007_jr_8016AB6C.o,ov_SC07_007_jr_8016AE5C.o,tail14.data.o,ov_SC07_007_jr_80171B4C.o,tail15.data.o,ov_SC07_007_jr_801789AC.o,ov_SC07_007_jr_80179B74.o,tail16.data.o,ov_SC07_007_jr_8017AE2C.o,ov_SC07_007_jr_8017BEBC.o,tail17.data.o,trailing.o  # Phase-26 §8 jtbl-rodata carve
build/src/ov_SC07_007/ov_SC07_007.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14,+0xdc
build/src/ov_SC07_007/ov_SC07_007_jr_80131340.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14
build/src/ov_SC07_007/ov_SC07_007_jr_80135D20.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC07_007/ov_SC07_007_jr_8013F350.o: JTBL_PADS := 0,0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38,+0x58
build/src/ov_SC07_007/ov_SC07_007_jr_8014032C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC07_007/ov_SC07_007_jr_8015444C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x70
build/src/ov_SC07_007/ov_SC07_007_jr_80154C24.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x24
build/src/ov_SC07_007/ov_SC07_007_jr_801588CC.o: JTBL_PADS := 0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x28,+0x48
build/src/ov_SC07_007/ov_SC07_007_jr_80159C84.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC07_007/ov_SC07_007_jr_8015A3C8.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC07_007/ov_SC07_007_jr_80171B4C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC07_007/ov_SC07_007_jr_801789AC.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC07_007/ov_SC07_007_jr_80179B74.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x90
build/src/ov_SC07_007/ov_SC07_007_jr_8017BEBC.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC07_007/ov_SC07_007_o0c.o: JTBL_PADS := 0,4,4,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x38,+0xa8,+0x118
ov_SC07_007_CHECK_SHA  := config/check.ov_SC07_007.sha
ov_SC07_007_SYMBOLS    := config/symbols.ov_SC07_007.txt
ov_SC07_007_SIG        := .run/sig.ov_SC07_007.jsonl
ov_SC07_007_GHIDRA_PROG := ov_SC07_007
ov_SC07_007_VRAM_BASE  := 0x80128158
ov_SC07_007_TEXT_LO    := 0x80128158
ov_SC07_007_TEXT_HI    := 0x801C7B37
ov_SC07_007_ASM_DIR     := asm/ov_SC07_007
ov_SC07_007_SRC_DIR     := src/ov_SC07_007
ov_SC07_007_UNDEF_SYMS  := build/ov_SC07_007/undefined_syms_auto.txt
ov_SC07_007_UNDEF_FUNCS := build/ov_SC07_007/undefined_funcs_auto.txt

# --- ov_SC07_010 (location overlay SC07/FILE_010, vram 0x80128158 — onboarded by new_overlay.sh) ---
ov_SC07_010_EXE        := extracted/retail/SC07.CD.dir/FILE_010.dir/1.4.dec
ov_SC07_010_NAME       := ov_SC07_010
ov_SC07_010_OUT_DIR    := build/ov_SC07_010
ov_SC07_010_OUT        := $(ov_SC07_010_OUT_DIR)/$(ov_SC07_010_NAME)
ov_SC07_010_ELF        := $(ov_SC07_010_OUT).elf
ov_SC07_010_MAPFILE    := $(ov_SC07_010_OUT).map
ov_SC07_010_LD_SCRIPT  := $(ov_SC07_010_OUT).ld
ov_SC07_010_SPLAT_YAML := config/splat.ov_SC07_010.yaml
ov_SC07_010_JTBL_INTERLEAVE := --order tail.data.o,ov_SC07_010.o,ov_SC07_010_jr_80131340.o,tail2.data.o,ov_SC07_010_jr_80135888.o,tail3.data.o,ov_SC07_010_jr_80135A4C.o,tail4.data.o,ov_SC07_010_jr_80135D20.o,tail5.data.o,ov_SC07_010_jr_801380E0.o,ov_SC07_010_o0.o,tail6.data.o,ov_SC07_010_jr_8013F350.o,tail7.data.o,ov_SC07_010_jr_8014032C.o,tail8.data.o,ov_SC07_010_jr_80140608.o,tail9.data.o,ov_SC07_010_jr_8015444C.o,ov_SC07_010_jr_80154C24.o,ov_SC07_010_jr_801588CC.o,ov_SC07_010_jr_80159C84.o,tail10.data.o,ov_SC07_010_jr_8015A3C8.o,tail11.data.o,ov_SC07_010_jr_8015B950.o,tail12.data.o,ov_SC07_010_jr_8015C32C.o,tail13.data.o,ov_SC07_010_jr_8016AB6C.o,ov_SC07_010_jr_8016AE5C.o,tail14.data.o,ov_SC07_010_jr_80171B4C.o,tail15.data.o,ov_SC07_010_jr_801789AC.o,ov_SC07_010_jr_80179B74.o,tail16.data.o,ov_SC07_010_jr_8017AE2C.o,tail17.data.o,trailing.o  # Phase-26 §8 jtbl-rodata carve
build/src/ov_SC07_010/ov_SC07_010.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14,+0xdc
build/src/ov_SC07_010/ov_SC07_010_jr_80131340.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14
build/src/ov_SC07_010/ov_SC07_010_jr_80135D20.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC07_010/ov_SC07_010_jr_8014032C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC07_010/ov_SC07_010_jr_8015444C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x70
build/src/ov_SC07_010/ov_SC07_010_jr_80154C24.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x24
build/src/ov_SC07_010/ov_SC07_010_jr_801588CC.o: JTBL_PADS := 0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x28,+0x48
build/src/ov_SC07_010/ov_SC07_010_jr_80159C84.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC07_010/ov_SC07_010_jr_8015A3C8.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC07_010/ov_SC07_010_jr_80171B4C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC07_010/ov_SC07_010_jr_801789AC.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC07_010/ov_SC07_010_jr_80179B74.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x90
build/src/ov_SC07_010/ov_SC07_010_jr_8017AE2C.o: JTBL_PADS := 0,0,0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14,+0x34,+0x4c
build/src/ov_SC07_010/ov_SC07_010_o0.o: JTBL_PADS := 0,4,4,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x38,+0xa8,+0x118
ov_SC07_010_CHECK_SHA  := config/check.ov_SC07_010.sha
ov_SC07_010_SYMBOLS    := config/symbols.ov_SC07_010.txt
ov_SC07_010_SIG        := .run/sig.ov_SC07_010.jsonl
ov_SC07_010_GHIDRA_PROG := ov_SC07_010
ov_SC07_010_VRAM_BASE  := 0x80128158
ov_SC07_010_TEXT_LO    := 0x80128158
ov_SC07_010_TEXT_HI    := 0x801A9547
ov_SC07_010_ASM_DIR     := asm/ov_SC07_010
ov_SC07_010_SRC_DIR     := src/ov_SC07_010
ov_SC07_010_UNDEF_SYMS  := build/ov_SC07_010/undefined_syms_auto.txt
ov_SC07_010_UNDEF_FUNCS := build/ov_SC07_010/undefined_funcs_auto.txt

# --- ov_SC07_011 (location overlay SC07/FILE_011, vram 0x80128158 — onboarded by new_overlay.sh) ---
ov_SC07_011_EXE        := extracted/retail/SC07.CD.dir/FILE_011.dir/1.4.dec
ov_SC07_011_NAME       := ov_SC07_011
ov_SC07_011_OUT_DIR    := build/ov_SC07_011
ov_SC07_011_OUT        := $(ov_SC07_011_OUT_DIR)/$(ov_SC07_011_NAME)
ov_SC07_011_ELF        := $(ov_SC07_011_OUT).elf
ov_SC07_011_MAPFILE    := $(ov_SC07_011_OUT).map
ov_SC07_011_LD_SCRIPT  := $(ov_SC07_011_OUT).ld
ov_SC07_011_SPLAT_YAML := config/splat.ov_SC07_011.yaml
ov_SC07_011_JTBL_INTERLEAVE := --order tail.data.o,ov_SC07_011.o,ov_SC07_011_jr_80131340.o,tail2.data.o,ov_SC07_011_jr_80135888.o,tail3.data.o,ov_SC07_011_jr_80135A4C.o,tail4.data.o,ov_SC07_011_jr_80135D20.o,tail5.data.o,ov_SC07_011_jr_801380E0.o,ov_SC07_011_o0c.o,tail6.data.o,ov_SC07_011_jr_8013F350.o,tail7.data.o,ov_SC07_011_jr_8014032C.o,tail8.data.o,ov_SC07_011_jr_80140608.o,tail9.data.o,ov_SC07_011_jr_8015444C.o,ov_SC07_011_jr_80154C24.o,ov_SC07_011_jr_801588CC.o,ov_SC07_011_jr_80159C84.o,tail10.data.o,ov_SC07_011_jr_8015A3C8.o,tail11.data.o,ov_SC07_011_jr_8015B950.o,tail12.data.o,ov_SC07_011_jr_8015C32C.o,tail13.data.o,ov_SC07_011_jr_8016AB6C.o,ov_SC07_011_jr_8016AE5C.o,tail14.data.o,ov_SC07_011_jr_80171B4C.o,tail15.data.o,ov_SC07_011_jr_801789AC.o,ov_SC07_011_jr_80179B74.o,tail16.data.o,ov_SC07_011_jr_8017AE2C.o,ov_SC07_011_jr_8017BEBC.o,tail17.data.o,trailing.o  # Phase-26 §8 jtbl-rodata carve
build/src/ov_SC07_011/ov_SC07_011.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14,+0xdc
build/src/ov_SC07_011/ov_SC07_011_jr_80131340.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14
build/src/ov_SC07_011/ov_SC07_011_jr_80135D20.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC07_011/ov_SC07_011_jr_8013F350.o: JTBL_PADS := 0,0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38,+0x58
build/src/ov_SC07_011/ov_SC07_011_jr_8014032C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC07_011/ov_SC07_011_jr_8015444C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x70
build/src/ov_SC07_011/ov_SC07_011_jr_80154C24.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x24
build/src/ov_SC07_011/ov_SC07_011_jr_801588CC.o: JTBL_PADS := 0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x28,+0x48
build/src/ov_SC07_011/ov_SC07_011_jr_80159C84.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC07_011/ov_SC07_011_jr_8015A3C8.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC07_011/ov_SC07_011_jr_80171B4C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC07_011/ov_SC07_011_jr_801789AC.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC07_011/ov_SC07_011_jr_80179B74.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x90
build/src/ov_SC07_011/ov_SC07_011_o0c.o: JTBL_PADS := 0,4,4,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x38,+0xa8,+0x118
ov_SC07_011_CHECK_SHA  := config/check.ov_SC07_011.sha
ov_SC07_011_SYMBOLS    := config/symbols.ov_SC07_011.txt
ov_SC07_011_SIG        := .run/sig.ov_SC07_011.jsonl
ov_SC07_011_GHIDRA_PROG := ov_SC07_011
ov_SC07_011_VRAM_BASE  := 0x80128158
ov_SC07_011_TEXT_LO    := 0x80128158
ov_SC07_011_TEXT_HI    := 0x801904FF
ov_SC07_011_ASM_DIR     := asm/ov_SC07_011
ov_SC07_011_SRC_DIR     := src/ov_SC07_011
ov_SC07_011_UNDEF_SYMS  := build/ov_SC07_011/undefined_syms_auto.txt
ov_SC07_011_UNDEF_FUNCS := build/ov_SC07_011/undefined_funcs_auto.txt

# --- ov_MAIN_012 (location overlay, vram 0x80128158 — onboarded by new_binary.sh) ---
ov_MAIN_012_EXE        := extracted/retail/MAIN.CD.dir/FILE_012.dir/1.1
ov_MAIN_012_NAME       := ov_MAIN_012
ov_MAIN_012_OUT_DIR    := build/ov_MAIN_012
ov_MAIN_012_OUT        := $(ov_MAIN_012_OUT_DIR)/$(ov_MAIN_012_NAME)
ov_MAIN_012_ELF        := $(ov_MAIN_012_OUT).elf
ov_MAIN_012_MAPFILE    := $(ov_MAIN_012_OUT).map
ov_MAIN_012_LD_SCRIPT  := $(ov_MAIN_012_OUT).ld
ov_MAIN_012_SPLAT_YAML := config/splat.ov_MAIN_012.yaml
ov_MAIN_012_JTBL_INTERLEAVE := --order tail.data.o,ov_MAIN_012.o,ov_MAIN_012_jr_80131340.o,tail2.data.o,ov_MAIN_012_jr_80135A4C.o,tail3.data.o,ov_MAIN_012_jr_80135EB0.o,tail4.data.o,ov_MAIN_012_jr_801380E0.o,ov_MAIN_012_o0c.o,tail5.data.o,ov_MAIN_012_jr_8013F350.o,tail6.data.o,ov_MAIN_012_jr_8015444C.o,tail7.data.o,ov_MAIN_012_jr_801549F8.o,ov_MAIN_012_jr_801555F4.o,tail8.data.o,ov_MAIN_012_jr_801594E8.o,ov_MAIN_012_jr_80159C84.o,tail9.data.o,ov_MAIN_012_jr_8015A3C8.o,tail10.data.o,ov_MAIN_012_jr_8016AB6C.o,ov_MAIN_012_jr_8016AE5C.o,tail11.data.o,ov_MAIN_012_jr_80171B4C.o,tail12.data.o,ov_MAIN_012_jr_801789AC.o,tail13.data.o,ov_MAIN_012_jr_8017C3BC.o,tail14.data.o,ov_MAIN_012_jr_8017CA18.o,tail15.data.o,ov_MAIN_012_jr_8017CF3C.o,tail16.data.o,trailing.o  # Phase-26 §8 jtbl-rodata carve
build/src/ov_MAIN_012/ov_MAIN_012.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14,+0xdc
build/src/ov_MAIN_012/ov_MAIN_012_jr_80131340.o: JTBL_PADS := 0,0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14,+0x2c
build/src/ov_MAIN_012/ov_MAIN_012_jr_80135A4C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_MAIN_012/ov_MAIN_012_jr_8013F350.o: JTBL_PADS := 0,0,4,0,4,0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38,+0x58,+0x70,+0x90,+0xa8
build/src/ov_MAIN_012/ov_MAIN_012_jr_801549F8.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x6c
build/src/ov_MAIN_012/ov_MAIN_012_jr_801555F4.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_MAIN_012/ov_MAIN_012_jr_801594E8.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_MAIN_012/ov_MAIN_012_jr_80159C84.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_MAIN_012/ov_MAIN_012_jr_8015A3C8.o: JTBL_PADS := 0,4,4,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x40,+0x60
build/src/ov_MAIN_012/ov_MAIN_012_jr_80171B4C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_MAIN_012/ov_MAIN_012_jr_801789AC.o: JTBL_PADS := 0,0,0,4,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18,+0x190,+0x220,+0x2b0
build/src/ov_MAIN_012/ov_MAIN_012_jr_8017C3BC.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x38
build/src/ov_MAIN_012/ov_MAIN_012_jr_8017CF3C.o: JTBL_PADS := 0,4,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x28,+0x50
build/src/ov_MAIN_012/ov_MAIN_012_o0c.o: JTBL_PADS := 0,4,4,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x38,+0xa8,+0x118
ov_MAIN_012_CHECK_SHA  := config/check.ov_MAIN_012.sha
ov_MAIN_012_SYMBOLS    := config/symbols.ov_MAIN_012.txt
ov_MAIN_012_SIG        := .run/sig.ov_MAIN_012.jsonl
ov_MAIN_012_GHIDRA_PROG := ov_MAIN_012
ov_MAIN_012_VRAM_BASE  := 0x80128158
ov_MAIN_012_TEXT_LO    := 0x80128158
ov_MAIN_012_TEXT_HI    := 0x80185C7F
ov_MAIN_012_ASM_DIR     := asm/ov_MAIN_012
ov_MAIN_012_SRC_DIR     := src/ov_MAIN_012
ov_MAIN_012_UNDEF_SYMS  := build/ov_MAIN_012/undefined_syms_auto.txt
ov_MAIN_012_UNDEF_FUNCS := build/ov_MAIN_012/undefined_funcs_auto.txt

# --- ov_SC02_037 (location overlay, vram 0x80128158 — onboarded by new_binary.sh) ---
ov_SC02_037_EXE        := extracted/retail/SC02.CD.dir/FILE_037.dir/0.1
ov_SC02_037_NAME       := ov_SC02_037
ov_SC02_037_OUT_DIR    := build/ov_SC02_037
ov_SC02_037_OUT        := $(ov_SC02_037_OUT_DIR)/$(ov_SC02_037_NAME)
ov_SC02_037_ELF        := $(ov_SC02_037_OUT).elf
ov_SC02_037_MAPFILE    := $(ov_SC02_037_OUT).map
ov_SC02_037_LD_SCRIPT  := $(ov_SC02_037_OUT).ld
ov_SC02_037_SPLAT_YAML := config/splat.ov_SC02_037.yaml
ov_SC02_037_JTBL_INTERLEAVE := --order tail.data.o,ov_SC02_037.o,ov_SC02_037_jr_80131340.o,tail2.data.o,ov_SC02_037_jr_80135A4C.o,tail3.data.o,ov_SC02_037_jr_80135EB0.o,tail4.data.o,ov_SC02_037_jr_801380E0.o,ov_SC02_037_o0c.o,tail5.data.o,ov_SC02_037_jr_8013F350.o,tail6.data.o,ov_SC02_037_jr_8015444C.o,tail7.data.o,ov_SC02_037_jr_801549F8.o,ov_SC02_037_jr_801555F4.o,tail8.data.o,ov_SC02_037_jr_801594E8.o,ov_SC02_037_jr_80159C84.o,tail9.data.o,ov_SC02_037_jr_8015A3C8.o,tail10.data.o,ov_SC02_037_jr_8016AB6C.o,ov_SC02_037_jr_8016AE5C.o,tail11.data.o,ov_SC02_037_jr_80171B4C.o,tail12.data.o,ov_SC02_037_jr_801789AC.o,tail13.data.o,ov_SC02_037_jr_8017AE2C.o,tail14.data.o,trailing.o  # Phase-26 §8 jtbl-rodata carve
build/src/ov_SC02_037/ov_SC02_037.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14,+0xdc
build/src/ov_SC02_037/ov_SC02_037_jr_80131340.o: JTBL_PADS := 0,0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14,+0x2c
build/src/ov_SC02_037/ov_SC02_037_jr_80135A4C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC02_037/ov_SC02_037_jr_8013F350.o: JTBL_PADS := 0,0,4,0,4,0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38,+0x58,+0x70,+0x90,+0xa8
build/src/ov_SC02_037/ov_SC02_037_jr_801549F8.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x6c
build/src/ov_SC02_037/ov_SC02_037_jr_801555F4.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC02_037/ov_SC02_037_jr_801594E8.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC02_037/ov_SC02_037_jr_80159C84.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC02_037/ov_SC02_037_jr_8015A3C8.o: JTBL_PADS := 0,4,4,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x40,+0x60
build/src/ov_SC02_037/ov_SC02_037_jr_80171B4C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC02_037/ov_SC02_037_jr_801789AC.o: JTBL_PADS := 0,0,0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18,+0x190,+0x220
build/src/ov_SC02_037/ov_SC02_037_jr_8017AE2C.o: JTBL_PADS := 0,0,0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14,+0x34,+0x4c,+0x64
build/src/ov_SC02_037/ov_SC02_037_o0c.o: JTBL_PADS := 0,4,4,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x38,+0xa8,+0x118
ov_SC02_037_CHECK_SHA  := config/check.ov_SC02_037.sha
ov_SC02_037_SYMBOLS    := config/symbols.ov_SC02_037.txt
ov_SC02_037_SIG        := .run/sig.ov_SC02_037.jsonl
ov_SC02_037_GHIDRA_PROG := ov_SC02_037
ov_SC02_037_VRAM_BASE  := 0x80128158
ov_SC02_037_TEXT_LO    := 0x80128158
ov_SC02_037_TEXT_HI    := 0x801C9AE7
ov_SC02_037_ASM_DIR     := asm/ov_SC02_037
ov_SC02_037_SRC_DIR     := src/ov_SC02_037
ov_SC02_037_UNDEF_SYMS  := build/ov_SC02_037/undefined_syms_auto.txt
ov_SC02_037_UNDEF_FUNCS := build/ov_SC02_037/undefined_funcs_auto.txt

# --- ov_SC03_107 (location overlay, vram 0x80128158 — onboarded by new_binary.sh) ---
ov_SC03_107_EXE        := extracted/retail/SC03.CD.dir/FILE_107.dir/0.1
ov_SC03_107_NAME       := ov_SC03_107
ov_SC03_107_OUT_DIR    := build/ov_SC03_107
ov_SC03_107_OUT        := $(ov_SC03_107_OUT_DIR)/$(ov_SC03_107_NAME)
ov_SC03_107_ELF        := $(ov_SC03_107_OUT).elf
ov_SC03_107_MAPFILE    := $(ov_SC03_107_OUT).map
ov_SC03_107_LD_SCRIPT  := $(ov_SC03_107_OUT).ld
ov_SC03_107_SPLAT_YAML := config/splat.ov_SC03_107.yaml
ov_SC03_107_JTBL_INTERLEAVE := --order tail.data.o,ov_SC03_107.o,ov_SC03_107_jr_80131340.o,tail2.data.o,ov_SC03_107_jr_80135A4C.o,tail3.data.o,ov_SC03_107_jr_80135EB0.o,tail4.data.o,ov_SC03_107_jr_801380E0.o,ov_SC03_107_o0c.o,tail5.data.o,ov_SC03_107_jr_8013F350.o,tail6.data.o,ov_SC03_107_jr_8015444C.o,tail7.data.o,ov_SC03_107_jr_801549F8.o,ov_SC03_107_jr_801555F4.o,tail8.data.o,ov_SC03_107_jr_801594E8.o,ov_SC03_107_jr_80159C84.o,tail9.data.o,ov_SC03_107_jr_8015A3C8.o,tail10.data.o,ov_SC03_107_jr_8016AB6C.o,ov_SC03_107_jr_8016AE5C.o,tail11.data.o,ov_SC03_107_jr_80171B4C.o,tail12.data.o,ov_SC03_107_jr_801789AC.o,tail13.data.o,trailing.o  # Phase-26 §8 jtbl-rodata carve
build/src/ov_SC03_107/ov_SC03_107.o: JTBL_PADS := 0,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14,+0xdc
build/src/ov_SC03_107/ov_SC03_107_jr_80131340.o: JTBL_PADS := 0,0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x14,+0x2c
build/src/ov_SC03_107/ov_SC03_107_jr_80135A4C.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18
build/src/ov_SC03_107/ov_SC03_107_jr_8013F350.o: JTBL_PADS := 0,0,4,0,4,0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38,+0x58,+0x70,+0x90,+0xa8
build/src/ov_SC03_107/ov_SC03_107_jr_801549F8.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x6c
build/src/ov_SC03_107/ov_SC03_107_jr_801555F4.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_107/ov_SC03_107_jr_801594E8.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_107/ov_SC03_107_jr_80159C84.o: JTBL_PADS := 0,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_107/ov_SC03_107_jr_8015A3C8.o: JTBL_PADS := 0,4,4,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x40,+0x60
build/src/ov_SC03_107/ov_SC03_107_jr_80171B4C.o: JTBL_PADS := 0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20
build/src/ov_SC03_107/ov_SC03_107_jr_801789AC.o: JTBL_PADS := 0,0,0,4,4,0,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x18,+0x190,+0x220,+0x2b0,+0x2c4,+0x32c
build/src/ov_SC03_107/ov_SC03_107_o0c.o: JTBL_PADS := 0,4,4,4  # §8e pads (jtbl_carve.py) tables=+0x0,+0x38,+0xa8,+0x118
ov_SC03_107_CHECK_SHA  := config/check.ov_SC03_107.sha
ov_SC03_107_SYMBOLS    := config/symbols.ov_SC03_107.txt
ov_SC03_107_SIG        := .run/sig.ov_SC03_107.jsonl
ov_SC03_107_GHIDRA_PROG := ov_SC03_107
ov_SC03_107_VRAM_BASE  := 0x80128158
ov_SC03_107_TEXT_LO    := 0x80128158
ov_SC03_107_TEXT_HI    := 0x8019BD3F
ov_SC03_107_ASM_DIR     := asm/ov_SC03_107
ov_SC03_107_SRC_DIR     := src/ov_SC03_107
ov_SC03_107_UNDEF_SYMS  := build/ov_SC03_107/undefined_syms_auto.txt
ov_SC03_107_UNDEF_FUNCS := build/ov_SC03_107/undefined_funcs_auto.txt
