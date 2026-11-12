/* guess_GetTextWindowResult — shared body (overlay slot 0x80128158, h_exact b8c9276b). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
/* guess_GetTextWindowResult: polls a text window: -1 when it is gone or in state 0/0xE, its byte +0x1F in state 0xD, else 0 (still open)
 * Confidence low, xref chain: !a0[0] -> -1; s16 +4 in {0, 0xE} -> -1; 0xD -> s8 +0x1F; else 0; callers close the window (func_80139914) on non-zero
 * Names ledger: config/names.tsv guess_GetTextWindowResult */
s32 guess_GetTextWindowResult(s32 a0) {
    s32 v1;
    if (*(s32*)(a0 + 0x0) == 0) return -1;
    v1 = *(s16*)(a0 + 0x4);
    if (v1 == 0) return -1;
    if (v1 == 0xE) return -1;
    if (v1 == 0xD) return *(s8*)(a0 + 0x1F);
    return 0;
}
