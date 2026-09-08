/* func_8012AE00 — shared body (overlay slot 0x80128158, h_exact a0992d25). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 *D_80126B78;
extern s32 *D_80126B90;
extern s32 D_80126B58;
extern s32 func_80135888(s32 a0, s32 a1, s32 a2, s32 a3);
extern s32 func_80013478(s32 a0, s32 a1);
s32 func_8012AE00(s32 a0) {
    s16 sp10[3];
    s16 sp18[4];
    struct V8 sp20;
    s32 r1, r2;
    s32 base;
    s32 p18 = (s32)sp18;
    sp10[0] = *(u16 *)(a0 + 0x3A);
    sp10[1] = *(u16 *)(a0 + 0x3E);
    sp10[2] = *(u16 *)(a0 + 0x42);
    sp18[0] = *(u16 *)(a0 + 0x6);
    sp18[1] = *(u16 *)(a0 + 0xA);
    sp18[2] = *(u16 *)(a0 + 0xE);
    base = (s32)&D_80126B58;
    sp20 = *(struct V8 *)sp18;
    if (func_80135888((s32)D_80126B78, (s32)D_80126B90, (s32)sp10, (s32)&sp20) == 0) {
        return 0;
    }
    base += 4;
    r1 = func_80013478(base, (s32)sp10);
    r2 = func_80013478(base, p18);
    if (r1 < r2) {
        return 0;
    }
    *(s32 *)(a0 + 0x4) = *(s32 *)(a0 + 0x38);
    *(s32 *)(a0 + 0x8) = *(s32 *)(a0 + 0x3C);
    *(s32 *)(a0 + 0xC) = *(s32 *)(a0 + 0x40);
    return 1;
}
