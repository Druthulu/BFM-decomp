/* func_8017F4F8 — shared body (overlay slot 0x80128158, h_exact fb05278a). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
    extern void (*D_8018DA64[])(void);
    extern void func_80162D28(s32*);
    void func_8017F4F8(void *a0) {
        D_8018DA64[*(u16 *)((s32)a0 + 0x2)]();
        if (*(s32 *)((s32)a0 + 0x20) != 0) {
            ((void (*)(void *))func_80162D28)(a0);
        }
    }
