/* func_80162120 — shared body (overlay slot 0x80128158, h_exact d51a273b). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_800291DC(s32);
extern s32 func_800D0D7C(s32, s32);
extern void func_800291C8(s32, s32);
void func_80162120(void) {
    s32 v0;
    if ((s16)func_800291DC(8) == 0) {
        v0 = func_800D0D7C(0, 1);
        func_800291C8(8, (s16)(v0 | 0x8000));
    }
}
