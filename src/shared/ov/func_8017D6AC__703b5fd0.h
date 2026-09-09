/* func_8017D6AC — shared body (overlay slot 0x80128158, h_exact 703b5fd0). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_800495EC(s32 a0, s32 a1, s32 a2);
u32 func_8017D6AC(s16 *param_1, s16 *param_2, s16 *param_3) {
    s16 ax, ay, bx, by, cx, cy;
    register s32 la __asm__("$8");  // !FAKE: pin $8 — NEEDED DIFFERS (P36 rung B headers2)
    register s32 lb __asm__("$7");  // !FAKE: pin $7 — NEEDED DIFFERS (P36 rung B headers2)
    register s32 lc __asm__("$3");  // !FAKE: pin $3 — NEEDED DIFFERS (P36 rung B headers2)
    u32 r;
    s32 pad[2];
    cx = param_3[0];
    bx = param_2[0];
    if (cx < bx) {
        return 0;
    }
    __asm__ __volatile__("" : : "r"(la), "r"(lb), "r"(lc));  // !FAKE: keepalive — NEEDED DIFFERS (P36 rung B headers2)
    ax = param_1[0];
    if (ax < cx) {
        return 1;
    }
    do {
        cy = param_3[2];
        ay = param_1[1];
        if (cy > ay) {
            return 0;
        }
        by = param_2[1];
        if (by <= cy) {
            la = (u16)ax;
            lb = (u16)bx;
            lc = (u16)cx;
            __asm__ __volatile__("" : : "r"(ax), "r"(bx), "r"(cx));  // !FAKE: keepalive — NEEDED DIFFERS (P36 rung B headers2)
            r = func_800495EC(la | ((u16)ay << 16), lb | ((u16)by << 16),
                              lc | ((u16)cy << 16));
            return ~r >> 31;
        }
        return 1;
    } while (0);
}
