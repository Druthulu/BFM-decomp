/* func_8017CDD8 — shared body (overlay slot 0x80128158, h_exact ca104e40). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_8017CFCC(void);
extern void func_800167B8(s32 a0);
s32 func_8017CDD8(s32 a0) {
    func_8017CFCC();
    func_800167B8(0);
    *(u8 *)(a0 + 0x15) += 1;
    return 0;
}
