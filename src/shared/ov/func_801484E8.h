/* func_801484E8 — shared body (overlay slot 0x80128158, h_exact c4c30138). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_80154358(void *a0);
extern void func_801485B8(s32 a0, s32 a1, s32 a2);
extern s32 D_80126B58;
void func_801484E8(s32 a0, s32 a1) {
    s32 v0 = func_80154358(&D_80126B58);
    func_801485B8(v0 - 0x10, a0, a1);
}
