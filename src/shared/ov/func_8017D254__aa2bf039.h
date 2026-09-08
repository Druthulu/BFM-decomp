/* func_8017D254 — shared body (overlay slot 0x80128158, h_exact aa2bf039). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_8017D440(void);
s32 func_8017D254(s32 a0) {
    func_8017D440();
    *(s32 *)(a0 + 0x28) = 10;
    *(u8 *)(a0 + 0x15) += 1;
    return 0;
}
