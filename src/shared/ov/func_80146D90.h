/* guess_ClearMoveVector — shared body (overlay slot 0x80128158, h_exact f55bac35). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80146DE8(s32 *a0, s32 a1, s32 a2, s32 a3);
/* guess_ClearMoveVector: zeroes the object's move vector (+0x24/+0x28/+0x2C)
 * Confidence medium, xref chain: func_80146DE8(a0, 0, 0, 0); the vector guess_SetMoveVector sets
 * Names ledger: config/names.tsv guess_ClearMoveVector */
void guess_ClearMoveVector(s32 a0)
{
    func_80146DE8(a0, 0, 0, 0);
}
