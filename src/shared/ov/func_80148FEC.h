/* guess_AngleMinusQuarterTurn_2 — shared body (overlay slot 0x80128158, h_exact 519baeec). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
/* guess_AngleMinusQuarterTurn_2: returns angle a0 minus a quarter turn (0x400), wrapped to 12 bits
 * Confidence high, code inference: (a0 - 0x400) & 0xFFF
 * Names ledger: config/names.tsv guess_AngleMinusQuarterTurn_2 */
s32 guess_AngleMinusQuarterTurn_2(s32 a0) {
    return (a0 - 0x400) & 0xFFF;
}
