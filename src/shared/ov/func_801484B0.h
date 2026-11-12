/* guess_GetPlayerFramePointsA — shared body (overlay slot 0x80128158, h_exact 57e465cf). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_801485B8(s32 a0, s32 a1, s32 a2);
extern s32 *guess_g_PlayerModelPtr;
/* guess_GetPlayerFramePointsA: reads the two s8 point triples at bytes 0-5 of the player's current animation frame entry into the s16 vectors a0 and a1
 * Confidence low, xref chain: func_801485B8(*(guess_g_PlayerModelPtr + 0x20) - 0x10, a0, a1); func_80165E90 tests them when +0x44 bit 28 is set
 * Names ledger: config/names.tsv guess_GetPlayerFramePointsA */
void guess_GetPlayerFramePointsA(s32 a0, s32 a1) {
    func_801485B8(*(s32 *)((s32)guess_g_PlayerModelPtr + 0x20) - 0x10, a0, a1);
}
