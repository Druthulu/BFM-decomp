/* func_8017B368 — shared body (overlay slot 0x80128158, h_exact baab5d39). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
s32 func_8017B368(s32 param)
{
    extern void func_8017BA3C(s32 param_1, s32 param_2);
    extern void func_8012F214(s32 a0, s32 a1, s32 a2);
    extern SV4_8017B368 D_8018F934;
    extern SV4_8017B368 D_8018F93C;
    extern s16 D_8018F98C;
    extern s16 D_8018F984;
    extern u16 D_80182BB8;

    SV4_8017B368 loc0;
    SV4_8017B368 loc1;
    u32 n = (u32)&D_8018F934;

    ((void (*)(void))func_8017BA3C)();

    if (n >= 0xB) {
        loc0 = *(SV4_8017B368 *)n;
        loc1 = D_8018F93C;
    } else {
        s32 ax = (s32)&((Pair16_8017B368 *)&D_80182BB8)[n].x;
        s32 ay = (s32)&((Pair16_8017B368 *)&D_80182BB8)[n].y;
        func_8012F214(param, ax, (s32)&loc0);
        func_8012F214(param, ay, (s32)&loc1);
    }

    (*(SV4_8017B368 *)&D_8018F98C) = loc0;
    (*(SV4_8017B368 *)&D_8018F984) = loc1;
    D_8018FAB0 = 1;
    D_8018F914 = 0;
}
