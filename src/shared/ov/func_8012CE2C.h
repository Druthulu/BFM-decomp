/* func_8012CE2C — shared body (overlay slot 0x80128158, h_exact 5563d2c5). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_80133784(s32 a0, void *a1, s32 a2);
s32 func_8012CE2C(s32 a0) {
    short a[4];
    short b[4];
    s32 pa, pb;
    a[0] = *(u16 *)(a0 + 0x6);
    a[1] = *(u16 *)(a0 + 0xA);
    a[2] = *(u16 *)(a0 + 0xE);
    pa = (s32)a;
    pb = (s32)b;
    __builtin_memcpy((void *)pb, (void *)pa, 8);
    b[1] += 8;
    func_80133784(1, a, pb);
    return a[1] == b[1];
}
