/* func_8012C750 — shared body (overlay slot 0x80128158, h_exact 0789df87). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern u8 D_80120194[];
extern u8 D_801202A0[];
extern s32 func_8012C890(s32 a0, s32 a1, s32 a2);
s32 func_8012C750(s32 a0)
{
    s32 p;
    s32 it;
    s32 v0;
    if (*(u16 *)(a0 + 0xA) & 0x800) {
        s32 base = (s32)D_80120194;
        p = base + 0x6480;
        if (p != base) {
            do {
                if (*(u16 *)p == 0) goto found;
                p -= 0x10C;
            } while (p != base);
        }
        p = 0;
        goto found;
    } else {
        it = (s32)D_80120194;
        __asm__ __volatile__("" : "=r"(it) : "0"(it));
        p = it + 0x658C;
        goto test;
    copy:
        p = it;
        goto found;
    test:
        it = (s32)D_801202A0;
        __asm__ __volatile__("" : "=r"(it) : "0"(it));
        if (it == p) goto zero;
    body:
        if (*(u16 *)it == 0) goto copy;
        it += 0x10C;
        if (it != p) goto body;
    zero:
        p = 0;
    }
found:
    if (p == 0) {
        v0 = 0;
    } else {
        *(u16 *)(a0 + 0xA) = *(u16 *)(a0 + 0xA) | 0x8000;
        v0 = func_8012C890(a0, p, 0);
    }
    return v0;
}
