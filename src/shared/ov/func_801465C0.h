/* guess_AllocSpriteObject — shared body (overlay slot 0x80128158, h_exact d8a69d1c). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_8001D074(s32, s32);
/* guess_AllocSpriteObject: returns a free 0x38-byte record of guess_g_RenderWork (slots 0x16-0x3D), or 0
 * Confidence low, xref chain: func_8001D074(0x16, 0x3E): first 0x38-byte record at guess_g_RenderWork + 0x65A8 + i * 0x38 whose u16 at +0 is 0
 * Names ledger: config/names.tsv guess_AllocSpriteObject */
void *guess_AllocSpriteObject(void) {
    func_8001D074(0x16, 0x3E);
}
