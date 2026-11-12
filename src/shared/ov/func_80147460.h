/* guess_ApplyVertSpeed — shared body (overlay slot 0x80128158, h_exact e3104997). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
/* guess_ApplyVertSpeed: adds the vertical speed (+0x34) to the y position word (+0x8)
 * Confidence medium, xref chain: *(a0 + 0x8) += *(a0 + 0x34); +0x8 is the y word guess_g_PlayerPosY reads the integer half of
 * Names ledger: config/names.tsv guess_ApplyVertSpeed */
void guess_ApplyVertSpeed(s32 a0) {
    *(s32 *)(a0 + 0x8) += *(s32 *)(a0 + 0x34);
}
