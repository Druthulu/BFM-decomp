/* func_801EF4F8 — shared body (module slot 0x801EF468, h_exact 54f18e02). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_8016EDEC(s32 a0, s32 a1, s32 a2);
extern void func_801EF798(void *arg0);
s32 func_801EF4F8(s32 param_1) {
    ((void (*)(void *, s32))func_8016EDEC)((void *)func_801EF798, 0x1000000);
    *(u8 *)(param_1 + 0x15) = *(u8 *)(param_1 + 0x15) + 1;
    *(s32 *)(param_1 + 0x28) = 16;
    return 0;
}
