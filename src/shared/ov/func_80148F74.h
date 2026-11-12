/* guess_AnglePlusQuarterTurn — shared body (overlay slot 0x80128158, h_exact 68f87554). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
/* guess_AnglePlusQuarterTurn: returns angle a0 plus a quarter turn (0x400), wrapped to 12 bits
 * Confidence high, code inference: (a0 + 0x400) & 0xFFF
 * Names ledger: config/names.tsv guess_AnglePlusQuarterTurn */
s32 guess_AnglePlusQuarterTurn(s32 a0) {
    return (a0 + 0x400) & 0xFFF;
}
