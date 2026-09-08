/* func_8012C0EC — shared body (overlay slot 0x80128158, h_exact e05b7bff). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 D_801274D4;
extern s16 D_80126CAC;
extern s32 D_801274E0;
extern s32 func_80013478(s32 a0, s32 a1);
extern void func_8012C218(void *a0);
s32 func_8012C0EC(s32 a0) {
    s32 (*fp)(s32) = (s32 (*)(s32))D_801274D4;
    s32 cond;
    s32 *p;
    if (fp == 0) {
        cond = (func_80013478(a0 + 4, (s32)&D_80126CAC) < D_801274E0) ^ 1;
    } else {
        cond = fp(a0);
    }
    if (cond == 0) {
        return 0;
    }
    p = *(s32 **)(a0 + 0x68);
    if (p != 0) {
        if ((*(s16 *)(a0 + 0x72) & 0x8000) != 0) {
            *(u16 *)((s32)p + 0xA) = *(u16 *)((s32)p + 0xA) & 0x7FFF;
        }
    }
    func_8012C218((void *)a0);
    return 1;
}
