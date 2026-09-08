/* func_80139DF4 — shared body (overlay slot 0x80128158, h_exact 8974153e). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80139A8C(s32 a0);
void func_80139DF4(s32 a0) {
    s32 c;
    s32 v;
    c = *(u8 *)(a0 + 0xC);
    if (c != 0) {
        c = c - 1;
        *(s8 *)(a0 + 0xC) = (s8)c;
        if ((c & 0xFF) != 0) {
            goto calls;
        }
    }
    *(s16 *)(a0 + 0x4) = 2;
    return;
calls:
    func_80139A8C(a0);
    if (*(s32 *)(a0 + 0x8) & 0x20) {
        *(s16 *)(a0 + 0x4) = 2;
        v = *(s32 *)(a0 + 0x8);
        *(s8 *)(a0 + 0xC) = 0;
        if ((v & 0x20000) == 0) {
            *(s32 *)(a0 + 0x8) = v & -0x21;
        }
    }
}
