/* func_8016380C — shared body (overlay slot 0x80128158, h_exact ffd7edfd). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80015978(s32 a0, s32 *a1);
extern s32 func_80133784(s32 a0, void *a1, s32 a2);
extern void func_80015954(s32 a0, s32 a1);
s32 func_8016380C(struct S8016380C *a0, s32 a1) {
    struct M8 local;
    s32 ret;
    local = a0->m;
    func_80015978((s32)((u8 *)a0 + 4), (s32 *)a1);
    ret = func_80133784(1, &local, a1);
    if (ret != 0) {
        func_80015954(a1, (s32)((u8 *)a0 + 4));
        return ret;
    }
    return 0;
}
