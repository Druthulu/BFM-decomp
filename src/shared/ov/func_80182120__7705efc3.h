/* func_80182120 — shared body (overlay slot 0x80128158, h_exact 7705efc3). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
    extern void func_8012E8E0(s32 a0, s32 a1);
    extern void func_8012E88C(s32 a0);
    extern void func_8012A828(s32*, s32);
    extern void func_80184C90(s32);
    extern void func_80184ED4(s32, s32, s32, s32);
    void func_80182120(void *arg0) {
        extern short D_80191C10;
        extern s32 D_801B9AA8;
        extern u8 D_801B66D8[];
        void *v1;
        *(short *)((char *)arg0 + 0x2) = 0x4;
        func_8012E8E0((s32)arg0, (s32)&D_80191C10);
        v1 = *(void **)((char *)arg0 + 0x20);
        *(short *)((char *)v1 + 0x12) = *(short *)((char *)v1 + 0x12) + 0x800;
        func_8012E88C((s32)arg0);
        ((void (*)(s32 *, s32))func_8012A828)((s32 *)arg0, (s32)&(*(short *)&D_801B9AA8));
        func_80184C90((s32)arg0);
        *(short *)((char *)arg0 + 0x34) = 0;
        func_80184ED4((s32)arg0, (s32)&(*(short *)D_801B66D8), 0x1, 0x40);
    }
