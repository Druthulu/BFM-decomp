/* func_801623B8 — shared body (overlay slot 0x80128158, h_exact e4e04b3f). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_800D0C48(s32 a0);
extern void func_800167B8(s32 a0);
s32 func_801623B8(s32 *a0) {
    if (--a0[0xA] == -1) {
        func_800D0C48(1);
        func_800167B8(4);
        *((u8 *)a0 + 0x15) += 1;
    }
    return 0;
}
