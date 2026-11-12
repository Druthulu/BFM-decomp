/* guess_SetYawToAngleMinus90_2 — shared body (overlay slot 0x80128158, h_exact d04fb717). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
/* guess_SetYawToAngleMinus90_2: sets the facing yaw (+0x12 of the +0x20 model) to the angle a1 minus a quarter turn (0x400) and returns 1
 * Confidence medium, xref chain: model +0x12 = (a1 - 0x400) & 0xFFF; +0x12 is guess_TurnStepToTarget's facing; table entry; twin 0x80148D0C (guess_SetYawToAngleMinus90_2)
 * Names ledger: config/names.tsv guess_SetYawToAngleMinus90_2 */
s32 guess_SetYawToAngleMinus90_2(s32 a0, s32 a1) {
    s32 v0 = *(s32 *)(a0 + 0x20);
    *(s16 *)(v0 + 0x12) = (a1 - 0x400) & 0xFFF;
    return 1;
}
