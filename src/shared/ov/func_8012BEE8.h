/* guess_TickWaitTimer — shared body (overlay slot 0x80128158, h_exact 2c8a6ecc). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
/* guess_TickWaitTimer: counts down the timer word at +0x1C; returns 1 when it is 0 or reaches 0 now, else 0
 * Confidence high, code inference: v = +0x1C; v == 0 returns 1; else +0x1C = v - 1 and returns v - 1 == 0
 * Names ledger: config/names.tsv guess_TickWaitTimer */
s32 guess_TickWaitTimer(s32 a0) {
    s32 v0;
    v0 = *(s32*)(a0 + 0x1C);
    if (!v0) goto ret1;
    *(s32*)(a0 + 0x1C) = v0 - 1;
    return (u32)(v0 - 1) < 1;
ret1:
    return 1;
}
