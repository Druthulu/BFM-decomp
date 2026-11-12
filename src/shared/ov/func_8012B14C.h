/* guess_SetLocalVelocity — shared body (overlay slot 0x80128158, h_exact 968eab05). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_800484EC(s32 a0, s32 a1, s32 a2);
/* guess_SetLocalVelocity: sets object a0's velocity (+0x10) to vector a1 rotated by its model matrix
 * Confidence high, xref chain: func_800484EC(model + 0x34, a1, a0 + 0x10); func_800484EC is libgte ApplyMatrixLV per the SLUS map
 * Names ledger: config/names.tsv guess_SetLocalVelocity */
void guess_SetLocalVelocity(s32 a0, s32 a1) {
    func_800484EC(*(s32 *)((s32)a0 + 0x20) + 0x34, a1, (s32)a0 + 0x10);
}
