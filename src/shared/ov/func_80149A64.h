/* guess_IsSquareOrTrianglePressed — shared body (overlay slot 0x80128158, h_exact 0b8da7ea). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 guess_IsSquarePressed(s32 *a0);
extern s32 guess_IsTrianglePressed(s32 *a0);
/* guess_IsSquareOrTrianglePressed: returns 1 when guess_IsSquarePressed or guess_IsTrianglePressed does
 * Confidence medium, xref chain: guess_IsSquarePressed(a0) || guess_IsTrianglePressed(a0)
 * Names ledger: config/names.tsv guess_IsSquareOrTrianglePressed */
s32 guess_IsSquareOrTrianglePressed(s32 *a0) {
    if (guess_IsSquarePressed(a0) || guess_IsTrianglePressed(a0)) {
        return 1;
    }
    return 0;
}
