/* func_8012E014 — shared body (overlay slot 0x80128158, h_exact 18eeac9e). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_8012F0BC(s32 *a0, s32 *a1, s32 *a2);
extern void func_8012F1A4(s32 *a0, s32 a1, s32 *a2);
extern void func_80049CAC(s32 a0, s32 a1);
void func_8012E014(s32 a0) {
    /* asm-label alias (cookbook § "BANKING PATTERNS": `extern u16 X __asm__("D_x")`).
     * The TU already carries `extern u8 D_80126B5C;` from DEFINE_func_8012BD14()/
     * DEFINE_func_80149954(), so a plain `extern s32 D_80126B5C;` is a conflicting-types
     * hard error, and the `*(s32 *)&D_80126B5C` cast-at-use form makes gcc force_reg the
     * constant address (memory_address(), explow.c) -> 3 CSE'd `la` pseudos pinned in
     * $s2/$s3/$s4 across the calls = +6 ins. The alias gives a real s32 object at the
     * same assembler symbol, so each access stays a direct `lw/sw sym` MEM. */
    extern s32 gVecX __asm__("D_80126B5C");
    extern s32 gVecY __asm__("D_80126B60");
    extern s32 gVecZ __asm__("D_80126B64");
    s32 in[4];
    s32 out[4];
    s32 tmp[4];
    s32 v;
    s32 w;
    s16 t;
    in[0] = gVecX;
    in[1] = gVecY;
    in[2] = gVecZ;
    func_8012F0BC((s32 *)(*(s32 *)(a0 + 0x20) + 0x34), in, tmp);
    v = *(s32 *)(a0 + 0x20);
    if (v != 0) {
        func_80049CAC(v + 0x10, v + 0x34);
        w = *(s32 *)(a0 + 0x20);
        t = *(u16 *)(a0 + 0x6) + *(u16 *)(a0 + 0x50);
        *(s16 *)(w + 0x8) = t;
        *(s32 *)(w + 0x48) = t;
        t = *(u16 *)(a0 + 0xA) + *(u16 *)(a0 + 0x52);
        *(s16 *)(w + 0xA) = t;
        *(s32 *)(w + 0x4C) = t;
        t = *(u16 *)(a0 + 0xE) + *(u16 *)(a0 + 0x54);
        *(s16 *)(w + 0xC) = t;
        *(u16 *)(w + 0x2C) |= 1;
        *(s32 *)(w + 0x50) = t;
    }
    func_8012F1A4((s32 *)(*(s32 *)(a0 + 0x20) + 0x34), (s32)tmp, out);
    gVecX = out[0];
    gVecY = out[1];
    gVecZ = out[2];
}
