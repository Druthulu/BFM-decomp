/* func_801542DC — shared body (overlay slot 0x80128158, h_exact cbcabba4). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_8015430C(u8 *arg0, s32 arg1, s32 arg2);
void func_801542DC(s32 *a0, s32 a1) {
    if (*(s32 *)((s32)a0 + 0xB4) != a1) {
        KR_AS(void, func_8015430C)();
    }
}
