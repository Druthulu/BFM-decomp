/* func_8012BA10 — shared body (overlay slot 0x80128158, h_exact 8bd6fb17). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 ratan2(s32 a0, s32 a1);
s32 func_8012BA10(s32 arg0, s32 arg1) {
    extern u16 D_80126B5E;
    extern u16 D_80126B66;
    register s32 d __asm__("$16");      /* $s0 -- pinned: divisor, live across the jal */  // !FAKE: pin $16 — NEEDED DIFFERS (P36 rung B headers1)
    s32 s1ang;  /* $s1 -- pinned: ptr+0x12 angle, live across the jal */
    s32 u5; s32 u6; s32 iVar4; s32 q; s32 t;
    d = arg1;
    s1ang = *(s16 *)(*(s32 *)(arg0 + 0x20) + 0x12);
    u5 = (ratan2(*(s16 *)(arg0 + 0xE) - (s16)D_80126B66, (s16)D_80126B5E - *(s16 *)(arg0 + 6)) - 0x400) & 0xFFF;
    __asm__ __volatile__("" : : "r"(u5));   /* scheduling barrier: anchor u5 before the (s16)d cast */  // !FAKE: keepalive — NEEDED DIFFERS (P36 rung B headers1)
    d = (s16)d;
    u6 = s1ang & 0xFFF;
    if (u6 == u5) return 0;
    iVar4 = u5 - u6;
    if (iVar4 > 0x800) { t = u6 + 0x1000; iVar4 = u5 - t; }
    if (iVar4 < -0x800) { t = u6 - 0x1000; iVar4 = u5 - t; }
    if (iVar4 >= 0) { q = iVar4 / d; if (q == 0) q = 1; }
    else { q = iVar4 / d; if (q == 0) q = -1; }
    return q;
}
