/* func_8017CF20 — shared body (overlay slot 0x80128158, h_exact b2f519b3). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_8017D0D4(void);
s32 func_8017CF20(s32 a0) {
    func_8017D0D4();
    *(s32 *)(a0 + 0x28) = 10;
    *(u8 *)(a0 + 0x15) += 1;
    return 0;
}
