/* func_8017F8A8 — shared body (overlay slot 0x80128158, h_exact c4911ca7). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
    extern void func_8017FB40();
    extern void (*D_8018DAA8[])(int);
    extern void func_80162D28(s32*);
    void func_8017F8A8(int param_1)
    {
        func_8017FB40();
        D_8018DAA8[*(unsigned short *)(param_1 + 2)](param_1);
        if (*(s32 *)(param_1 + 0x20) != 0) {
            ((void (*)(int))func_80162D28)(param_1);
        }
    }
