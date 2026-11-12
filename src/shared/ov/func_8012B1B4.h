/* guess_SetVelocityXZFromLocal — shared body (overlay slot 0x80128158, h_exact 0019c45c). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void ApplyMatrixLV(s32 a0, s32 a1, s32 a2);
/* guess_SetVelocityXZFromLocal: rotates the local vector a1 by object a0's model matrix and stores its x and z as the velocity x (+0x10) and z (+0x18)
 * Confidence medium, xref chain: ApplyMatrixLV(model+0x34, a1, out); +0x10 = out.x, +0x18 = out.z; +0x10.. is the velocity guess_ApplyVelocity adds
 * Names ledger: config/names.tsv guess_SetVelocityXZFromLocal */
void guess_SetVelocityXZFromLocal(s32 a0, s32 a1) {
    s32 sp10[4];
    ApplyMatrixLV(*(s32 *)(a0 + 0x20) + 0x34, a1, (s32)sp10);
    *(s32 *)(a0 + 0x10) = sp10[0];
    *(s32 *)(a0 + 0x18) = sp10[2];
}
