/* guess_AllocModelObject — shared body (overlay slot 0x80128158, h_exact 5d72630c). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_8001CFDC(s32 a, s32 b);
/* $v0 at exit: leftover of void func_8001CFDC; no byte-neutral return: `return 0;` puts `move v0,zero` at +0x18 and moves `addiu sp` into the jr delay slot +0x20, ov_SC02_027 objdump */
/* guess_AllocModelObject: returns a free 0x84-byte model record of guess_g_RenderWork (slots 0x26-0x84), or 0
 * Confidence medium, xref chain: func_8001CFDC(0x26, 0x85): first 0x84-byte record at guess_g_RenderWork + 0x2A8 + i * 0x84 whose u16 at +0 is 0
 * Names ledger: config/names.tsv guess_AllocModelObject */
s32 guess_AllocModelObject(void) {
    func_8001CFDC(0x26, 0x85);
}
