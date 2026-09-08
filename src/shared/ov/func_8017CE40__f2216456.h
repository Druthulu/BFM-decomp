/* func_8017CE40 — shared body (overlay slot 0x80128158, h_exact f2216456). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_8017CFF4(void);
s32 func_8017CE40(s32 a0) {
    func_8017CFF4();
    *(s32 *)(a0 + 0x28) = 10;
    *(u8 *)(a0 + 0x15) += 1;
    return 0;
}
