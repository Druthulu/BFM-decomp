/* guess_SetForwardVelocity — shared body (overlay slot 0x80128158, h_exact c8e802f6). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void ApplyMatrixLV(s32 a0, s32 a1, s32 a2);
/* guess_SetForwardVelocity: sets object a0's velocity (+0x10) to (0, 0, a1) rotated by its model matrix
 * Confidence high, xref chain: ApplyMatrixLV(model + 0x34, {0, 0, a1}, a0 + 0x10); ApplyMatrixLV is libgte ApplyMatrixLV per the SLUS map
 * Names ledger: config/names.tsv guess_SetForwardVelocity */
void guess_SetForwardVelocity(s32 a0, s32 a1) {
    s32 sp10[3];
    sp10[2] = a1;
    sp10[1] = 0;
    sp10[0] = 0;
    ApplyMatrixLV(*(s32 *)(a0 + 0x20) + 0x34, (s32)sp10, a0 + 0x10);
}
