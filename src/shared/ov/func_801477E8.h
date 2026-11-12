/* guess_SetVertSpeed — shared body (overlay slot 0x80128158, h_exact d2f74e8f). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
/* guess_SetVertSpeed: sets the vertical speed word (+0x34) to a1, clamped to -0x1F0000..0x1F0000
 * Confidence medium, xref chain: a0[0xD] = a1 clamped to +-0x1F0000; guess_ApplyVertSpeed adds +0x34 to the y position +0x8
 * Names ledger: config/names.tsv guess_SetVertSpeed */
void guess_SetVertSpeed(s32 *a0, s32 a1) {
    a0[0xD] = a1;
    if (a1 < -0x1F0000) {
        a0[0xD] = -0x1F0000;
    } else if (a1 > 0x1F0000) {
        a0[0xD] = 0x1F0000;
    }
}
