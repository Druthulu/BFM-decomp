/* func_801642AC — shared body (overlay slot 0x80128158, h_exact 94963a44). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80164418();
extern s32 func_80013328(s32 a0, s32 a1);
extern s32 func_80146E98(s32 a0);
extern void func_80146E90(s32 *a0, s32 a1);
extern void func_80147324(s32 a0);
extern void func_80146CA0(void *a0);
extern s32 func_80163764(s32 a0);
void func_801642AC(s32 a0) {
    s32 s1 = a0;
    s32 s0 = *(s32 *)(s1 + 0x4C);
    func_80164418();
    if (func_80013328(s0 + 4, s1 + 4) < 0x28 || func_80146E98(s1) != 0) {
        func_80146E90((s32 *)s1, 8);
        func_80147324(0x44A);
        func_80146CA0((void *)s1);
    }
    func_80163764(s1);
}
