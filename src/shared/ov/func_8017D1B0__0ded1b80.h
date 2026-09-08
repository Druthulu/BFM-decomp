/* func_8017D1B0 — shared body (overlay slot 0x80128158, h_exact 0ded1b80). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_8017D418(void);
extern void func_800167B8(s32 a0);
s32 func_8017D1B0(s32 a0) {
    func_8017D418();
    func_800167B8(0);
    *(u8 *)(a0 + 0x15) += 1;
    return 0;
}
