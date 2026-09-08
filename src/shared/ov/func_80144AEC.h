/* func_80144AEC — shared body (overlay slot 0x80128158, h_exact 7eace388). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern int func_80144B14(int param_1);
void func_80144AEC(s32 *a0) {
    s32 old;
    old = *(s32 *)((s32)a0 + 0xDC);
    *(s32 *)((s32)a0 + 0xDC) = (s32)&func_80144B14;
    *(s16 *)((s32)a0 + 0x0) = 0x83;
    *(s16 *)((s32)a0 + 0x2) = 1;
    *(s32 *)((s32)a0 + 0xCC) = old;
}
