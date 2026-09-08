/* func_8012C820 — shared body (overlay slot 0x80128158, h_exact 244d3779). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern u8 D_80120194[];
extern s32 func_8012C890(s32 a0, s32 a1, s32 a2);
s32 func_8012C820(u8 *a0) {
    u8 *base = D_80120194;
    u8 *p = base + 0x6480;
    if (p != base) {
        do {
            if (*(u16 *)p == 0) goto found;
            p -= 0x10C;
        } while (p != base);
    }
    p = 0;
found:
    if (p != 0) {
        *(u16 *)(a0 + 0xA) = *(u16 *)(a0 + 0xA) | 0x8000;
        func_8012C890((s32)a0, (s32)p, 0);
    } else {
        return 0;
    }
}
