/* func_8014DCE0 — shared body (overlay slot 0x80128158, h_exact 2728f3d9). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_80135888(s32 a0, s32 a1, s32 a2, s32 a3);
s32 func_8014DCE0(s32 arg0, s32 arg1, s32 arg2) {
    struct Quad buf;
    register s32 i __asm__("$17");  // !FAKE: pin $17 — NEEDED DIFFERS (P36 rung B headers1)
    s32 s0;
    buf = *(struct Quad *)(*(u32 *)(arg0 + 0x58) & 0xFFFFFFF);
    i = 0;
    s0 = arg2;
    do {
        s32 r;
        r = func_80135888(*(s32 *)(arg0 + 0x20), (s32)&buf, arg1, s0);
        i += 1;
        if (r == 0) {
            s0 += 8;
        } else {
            return 1;
        }
    } while (i < 3);
    return 0;
}
