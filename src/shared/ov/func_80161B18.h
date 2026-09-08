/* func_80161B18 — shared body (overlay slot 0x80128158, h_exact 574a62a2). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 D_800AE6B0;
extern void func_801599A4(void *a0);
extern void func_8015FA78(s32 *a0);
s32 func_80161B18(void *a0) {
    if ((D_800AE6B0 & 0x80FFFFFF) != 0) return 0;
    if (*(s32 *)((u8 *)a0 + 0x44) & 0x10) {
        func_801599A4(a0);
        func_8015FA78((s32 *)a0);
        return 1;
    }
    return 0;
}
