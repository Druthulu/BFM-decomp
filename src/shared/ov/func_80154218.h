/* func_80154218 — shared body (overlay slot 0x80128158, h_exact 27abf1b1). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_801549F8(s32 a0, s32 a1, s32 a2);
extern void func_80154418(void *a0);
void func_80154218(u8 *a0, s32 a1, s32 a2) {
    u8 *s0 = a0;
    s32 *base = *(s32 **)(s0 + 0xB0);
    s32 v1 = base[a1];
    *(u16 *)(s0 + 0xBA) = 1;
    *(u16 *)(s0 + 0xB8) = 1;
    *(s8 *)(s0 + 0xBC) = a2;
    *(s8 *)(s0 + 0xBD) = a2;
    *(s32 *)(s0 + 0xB4) = v1;
    s0[0xDC] = func_801549F8((s32)a0, (s32)&base[a1], a2);
    func_80154418(s0);
}
