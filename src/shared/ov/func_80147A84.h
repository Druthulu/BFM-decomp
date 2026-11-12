/* guess_SetVelocityFromMoveVector — shared body (overlay slot 0x80128158, h_exact 34c82f44). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void guess_AddMoveVectorThenSetVelocity(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
/* guess_SetVelocityFromMoveVector: sets the velocity to the move vector rotated by the model's angles (guess_AddMoveVectorThenSetVelocity with no delta)
 * Confidence medium, xref chain: guess_AddMoveVectorThenSetVelocity(a0, 0, 0, 0)
 * Names ledger: config/names.tsv guess_SetVelocityFromMoveVector */
void guess_SetVelocityFromMoveVector(s32 arg0) {
    guess_AddMoveVectorThenSetVelocity(arg0, 0, 0, 0);
}
