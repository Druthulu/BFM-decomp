/* func_8017250C — shared body (overlay slot 0x80128158, h_exact 11db5e80). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_80172560(u8 *a0, u8 *a1);
int func_8017250C(short *a0, short *a1) {
    if (func_80172560(a0, a1) == 0) {
        return 0;
    }
    a0[3] = a1[0];   /* sh v0,6(s1) <- lhu 0(s0) */
    a0[7] = a1[2];   /* sh v1,0xE(s1) <- lhu 4(s0) */
    return 1;
}
