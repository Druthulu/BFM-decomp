/* func_8012C51C — shared body (overlay slot 0x80128158, h_exact ad674b4e). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern u8 D_80126720[];
extern s32 func_8012C890(s32 a0, s32 a1, s32 a2);
s32 func_8012C51C(void *a0, s32 a1) {
    u8 *base = D_80126720;
    u8 *p;
    s32 ret;
    if (a1 == 0) {
        p = base - 0x6480;
    } else {
        p = (u8 *)(a1 + 0x10C);
    }
    if (p != base) {
        do {
            if (*(u16 *)p == 0) goto found;
            p += 0x10C;
        } while (p != base);
    }
    p = 0;
found:
    ret = 0;
    if (p != 0) {
        ret = func_8012C890((s32)a0, (s32)p, a1);
    }
    return ret;
}
