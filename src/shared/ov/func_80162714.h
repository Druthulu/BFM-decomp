/* func_80162714 — shared body (overlay slot 0x80128158, h_exact cf4df967). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_800291DC(s32);
extern s32 func_800D0D7C(s32, s32);
extern void func_800291C8(s32, s32);
void func_80162714(void) {
    s32 v0;
    if ((s16)func_800291DC(0x12) == 0) {
        v0 = func_800D0D7C(0xC, 0);
        func_800291C8(0x12, (s16)(v0 | 0x8000));
    }
}
