# jtbl 8-align probe — the HONEST stage-walk (2026-07-18, replaces the vacuous probe_jtbl_{cc1,maspsx}.s)

**Target:** func_80131340 (424 ins) draft spliced over its INCLUDE_ASM stub in the committed
src/ov_SC01_077/ov_SC01_077_jr_8012ACE0.c (probe copy: tu_spliced.c). Real pipeline, real flags.

## Verdict — the session-2 checkpoint's half-pin ("cc1 AND maspsx emit .align 2") is INVERTED

| stage | observable | result |
|---|---|---|
| cc1 (Sony gcc 2.7.2) | directives before EACH jump table | `.rdata` + **`.align 3`** + label (cc1.s L46-48 → $L15/51 words = jtbl_801D8078; L10578-80 → $L810/5 words = jtbl_801D8144). Exactly one `.align 3` per table, exactly 2 tables in the TU. |
| maspsx (pinned 874855c) | `.align` handling | **passed through VERBATIM** (maspsx.s L40-42, L9312-14; `.rdata`→`.section .rodata` only). The `continue` at maspsx/__init__.py:435-437 is inventory-only (`preprocess_lines`); the output path catch-all (L872-873) re-emits `.align`. |
| GNU as 2.42 | .rodata content | **size 0xE4, sh_addralign=8, ZERO PAD WORD AT OFFSET 0xCC** (rodata_verbatim.objdump: `00c0 48000000 48000000 48000000 00000000` then table 2 at 0xD0). The +4 interior pad, baked into the object — the linker can never remove it. |
| as control | `.section .rodata`+`.word` alone → Al=**4** (ctrl.o); +`.align 3` → Al=**8** (ctrl2.o) | the Al=8 is cc1's directive, NOT an as default. |

## Why this breaks the image
Original layout (asm/ov_SC01_077/data/tail2.data.s): jtbl_801D8078's 51 entries end 0x801D8144 exactly
where jtbl_801D8144 begins — originally-SEPARATE TUs, packed TIGHT by the original linker. Merging both
into one decomp TU makes cc1's intra-TU `.align 3` fire at 0xCC (%8==4) where the original had a tight TU
boundary → every downstream data symbol +4 → %lo relocs break image-wide (.run/build_g2.log SHA1 FAIL).
Intra-TU pads ARE real elsewhere (jtbl_801D8158/8170/8188/81A0: 5 entries + one 0x00000000 each, every
non-first table landing %8==0) — so the align must be REPLACED by the original's exact pad bytes
(pad ∈ {0,4} from carve-interval arithmetic), not blanket-dropped. Isolation is not general: as computes
`.align` SECTION-RELATIVE, so a 4-mod-8-start multi-table object would mis-pad internally.

**Fix:** tools/jtbl_rodata_pads.py post-maspsx filter, per-object JTBL_PADS spec from jtbl_carve.
For this TU the spec is `0,0` → expected filtered .rodata = 0xE0, table 2 tight at 0xCC (= the merged
carve span 0xaff20..0xB0000).

## CONFIRMED (same session): the filter's byte proof
`maspsx.s | jtbl_rodata_pads.py --pads 0,0 | as` → `.rodata` size **0xE0**, Al=4, table 2 TIGHT at
0xCC (rodata_filtered.objdump) = the merged carve span 0xaff20..0xB0000 exactly. Guards verified
fail-loud (1-spec / 3-spec / pads[0]=4 all rc=1 with attributable messages). The pad=4 direction
verified synthetically (`.word 0` emitted in place of the align).
