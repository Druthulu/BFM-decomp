/* guess_SetMoveVector — shared body (overlay slot 0x80128158, h_exact e82a2fd4). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80146DE8(s32 *a0, s32 a1, s32 a2, s32 a3);
/* guess_SetMoveVector: copies the three words at a1 into the object's move vector (+0x24/+0x28/+0x2C)
 * Confidence medium, xref chain: func_80146DE8(a0, a1[0], a1[1], a1[2]) stores +0x24/+0x28/+0x2C; func_80147F78 copies those to the velocity +0x10..+0x18
 * Names ledger: config/names.tsv guess_SetMoveVector */
void guess_SetMoveVector(s32 *a0, s32 *a1) {
    func_80146DE8(a0, a1[0], a1[1], a1[2]);
}
