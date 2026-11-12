/* guess_SetYawToAnglePlus90_2 — shared body (overlay slot 0x80128158, h_exact f9b1883b). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
/* guess_SetYawToAnglePlus90_2: sets the facing yaw (+0x12 of the +0x20 model) to the angle a1 plus a quarter turn (0x400) and returns 1
 * Confidence medium, xref chain: model +0x12 = (a1 + 0x400) & 0xFFF; +0x12 is guess_TurnStepToTarget's facing; table entry; twin 0x80148C9C (guess_SetYawToAnglePlus90_2)
 * Names ledger: config/names.tsv guess_SetYawToAnglePlus90_2 */
s32 guess_SetYawToAnglePlus90_2(s32 a0, s32 a1) {
    Obj_td *p = *(Obj_td **)((s32)a0 + 0x20);
    p->field_0x12 = (a1 + 0x400) & 0xFFF;
    return 1;
}
