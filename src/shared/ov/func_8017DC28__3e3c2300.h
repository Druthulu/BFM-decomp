/* func_8017DC28 — shared body (overlay slot 0x80128158, h_exact 3e3c2300). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80171A1C(u8 *a0);
    void func_8017DC28(s32 *param_1) {
        *(s32 *)((char *)param_1 + 0x200) = 1;
        ((void (*)(void))func_80171A1C)();
    }
