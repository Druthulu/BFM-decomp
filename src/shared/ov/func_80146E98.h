/* guess_TickWaitTimer_2 — shared body (overlay slot 0x80128158, h_exact 1f7e636d). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
/* guess_TickWaitTimer_2: counts down the timer word at +0x1C; returns 1 when it is 0 or reaches 0 now, else 0
 * Confidence high, code inference: v = +0x1C; v == 0 returns 1; else +0x1C = v - 1 and returns v - 1 == 0; the operation of guess_TickWaitTimer, a different body hash
 * Names ledger: config/names.tsv guess_TickWaitTimer_2 */
s32 guess_TickWaitTimer_2(s32 a0) {
    s32 v0;
    v0 = *(s32*)(a0 + 0x1C);
    if (v0 != 0) {
        v0 = v0 - 1;
        *(s32*)(a0 + 0x1C) = v0;
        return (u32)v0 < 1;
    }
    return 1;
}
