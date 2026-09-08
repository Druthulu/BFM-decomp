/* func_801638A0 — shared body (overlay slot 0x80128158, h_exact 3da89c76). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80015978(s32 a0, s32 *a1);
extern s32 func_80135004(s32 a0, void *a1, s32 a2);
extern void func_80015954(s32 a0, s32 a1);
extern s16 D_801152AA;
extern void *memcpy(void *, const void *, u32);
s32 func_801638A0(u8 *a0, s32 a1) {
    u8 buf[8];
    s16 d;
    s32 p;
    __builtin_memcpy(buf, a0 + 0x44, 8);
    p = (s32)(a0 + 4);
    func_80015978(p, (s32 *)a1);
    if (func_80135004(1, buf, a1) != 0) {
        func_80015954(a1, p);
        d = D_801152AA;
        if (d >= -0x578) {
            return 0x8000;
        }
        if (d >= -0xBCB) {
            return 0x4000;
        }
        return 0x2000;
    }
    return 0;
}
