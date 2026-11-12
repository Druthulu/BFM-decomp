/* guess_DistSqToPlayer — shared body (overlay slot 0x80128158, h_exact 2f5797b1). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_80013478(s32 a0, s32 a1);
extern s16 D_80126CBA;
extern s32 guess_g_PlayerActor; // Names ledger: config/names.tsv guess_g_PlayerActor
/* guess_DistSqToPlayer: squared distance from object a0's position to the s16 point at guess_g_PlayerActor + 0x15C; 0x7FFFFFFF while D_80126CBA is set
 * Confidence low, xref chain: returns 0x7FFFFFFF if D_80126CBA != 0, else func_80013478(a0 + 4, &guess_g_PlayerActor + 0x15C), a GTE sum of squared deltas
 * Names ledger: config/names.tsv guess_DistSqToPlayer */
s32 guess_DistSqToPlayer(s32 a0) {
    s32 *p = &guess_g_PlayerActor;
    if (D_80126CBA != 0) {
        return 0x7FFFFFFF;
    }
    return func_80013478(a0 + 4, (s32)p + 0x15C);
}
