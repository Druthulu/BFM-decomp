/* guess_AllocSpriteObjectHigh — shared body (overlay slot 0x80128158, h_exact fd2fa91b). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_8001D074(s32 a, s32 b);
/* $v0 at exit: leftover of void func_8001D074; no byte-neutral return: `return 0;` puts `move v0,zero` at +0x18 and moves `addiu sp` into the jr delay slot +0x20, ov_SC06_008 objdump */
/* guess_AllocSpriteObjectHigh: returns a free 0x38-byte record of guess_g_RenderWork from slots 0x3E-0x7C, or 0
 * Confidence low, xref chain: func_8001D074(0x3E, 0x7D): first slot whose u16 +0 is 0; guess_AllocSpriteObject takes slots 0x16-0x3D
 * Names ledger: config/names.tsv guess_AllocSpriteObjectHigh */
s32 guess_AllocSpriteObjectHigh(void) {
    func_8001D074(0x3E, 0x7D);
}
