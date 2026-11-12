/* guess_GetPlayerFramePointsB — shared body (overlay slot 0x80128158, h_exact 24fc6cda). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_801485B8(s32 a0, s32 a1, s32 a2);
extern s32 *guess_g_PlayerModelPtr; // Names ledger: config/names.tsv guess_g_PlayerModelPtr
/* guess_GetPlayerFramePointsB: reads the two s8 point triples at bytes 8-13 of the player's current animation frame entry into the s16 vectors a0 and a1
 * Confidence low, xref chain: func_801485B8(*(guess_g_PlayerModelPtr + 0x20) - 0x8, a0, a1); func_80165E90 tests them when +0x44 bit 29 is set
 * Names ledger: config/names.tsv guess_GetPlayerFramePointsB */
void guess_GetPlayerFramePointsB(s32 a0, s32 a1) {
    func_801485B8(*(s32 *)((s32)guess_g_PlayerModelPtr + 0x20) - 0x8, a0, a1);
}
