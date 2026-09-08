/* func_8017DD7C — shared body (overlay slot 0x80128158, h_exact fc81e68c). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_800D1E28(void);
extern s32 func_800D1D94(void);
extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8001BFD0(void);
extern void func_800D0C48(s32 a0);
s32 func_8017DD7C(s32 a0) {
    extern s16 D_800B9A0A;
    s16 s0;
    if (--(*(s32 *)(a0 + 0x28)) == -1) {
        func_800D1E28();
        s0 = D_800B9A0A;
        if (s0 != 0x1000 || (s16)func_800D1D94() != s0) {
            func_8002D4C8(0x1C, 0);
            func_8001BFD0();
            func_8002D4C8(0x1D, 0);
            func_800D0C48(1);
        }
        *(u8 *)(a0 + 0x15) += 1;
    }
    return 0;
}
