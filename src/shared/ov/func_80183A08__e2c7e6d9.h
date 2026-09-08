/* func_80183A08 — shared body (overlay slot 0x80128158, h_exact e2c7e6d9). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
    extern void func_8012E88C(s32 a0);
    extern void func_8012A828(s32*, s32);
    extern void func_80184C90(s32 a0);
    extern void func_80184ED4(s32 a0, s32 a1, s32 a2, s32 a3);
    extern s32 D_801B9C50;
    extern short D_801B67C8;
    void func_80183A08(s32 a0) {
        *(u16 *)(a0 + 2) = 6;
        func_8012E88C(a0);
        ((void (*)(s32, s32))func_8012A828)(a0, (s32)&D_801B9C50);
        func_80184C90(a0);
        func_80184ED4(a0, (s32)&(*(s32 *)&D_801B67C8), 1, 0x60);
    }
