/* func_801592CC — shared body (overlay slot 0x80128158, h_exact ec9e7430). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_801399F0(s32 a0);
extern void func_80139914(s32 a0);
extern s32 func_8013767C(s32 a0);
extern void func_80146C98(s32 *a0, s16 a1);
extern u8 D_80110C3C[];
void func_801592CC(s32 *a0) {
    s32 *s0 = a0;
    s32 *v1 = (s32 *)s0[0x20 / 4];
    *(s16 *)((char *)v1 + 0x12) = (*(u16 *)((char *)v1 + 0x12) + 0x16) & 0xFFF;
    if (func_801399F0(s0[0x198 / 4]) != 0) {
        func_80139914(s0[0x198 / 4]);
        s0[0x198 / 4] = func_8013767C((s32)D_80110C3C);
        func_80146C98(s0, 9);
    }
}
