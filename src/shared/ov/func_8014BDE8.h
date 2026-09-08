/* func_8014BDE8 — shared body (overlay slot 0x80128158, h_exact db10e052). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_8016F1AC(void);
extern s32 func_8017267C(s32 *a0);
extern void func_80015978(s32 a0, s32 *a1);
extern s32 func_80013294(void *a0, void *a1);
extern void func_80029ED4(s32 a0);
void func_8014BDE8(s32 a0) {
    s32 s0 = a0;
    struct B8014 sp10;
    s16 sp18[4];
    if (func_8016F1AC() != 0) {
        return;
    }
    if (func_8017267C((s32 *)s0) != 0) {
        return;
    }
    sp10 = *(struct B8014 *)(s0 + 0x98);
    func_80015978(s0 + 4, (s32 *)sp18);
    sp18[1] = 0;
    *(s16 *)((s32)&sp10 + 0x2) = 0;
    func_80029ED4((func_80013294(&sp10, sp18) << 16) >> 16);
}
