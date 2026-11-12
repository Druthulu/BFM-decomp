/* guess_IsSquarePressed — shared body (overlay slot 0x80128158, h_exact d0967f29). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
/* guess_IsSquarePressed: returns 1 when Square (0x80) is newly pressed (+0xAC), 0 when bits 0x404 of +0x44 are set
 * Confidence medium, xref chain: +0x44 & 0x404 -> 0; else (+0xAC & 0x80) != 0; 0x80 is Square in the PlayStation button word
 * Names ledger: config/names.tsv guess_IsSquarePressed */
s32 guess_IsSquarePressed(s32 *a0) {
    s32 v0;
    if (a0[0x44 / 4] & 0x404) {
        v0 = 0;
    } else {
        v0 = *(u16 *)((s32)a0 + 0xAC) & 0x80;
        v0 = v0 != 0;
    }
    return v0;
}
