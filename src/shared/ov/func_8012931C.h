/* guess_AddVelocityToPos — shared body (overlay slot 0x80128158, h_exact 194beddd). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
/* guess_AddVelocityToPos: adds the velocity words +0x10, +0x14, +0x18 of a0 to its position words +0x4, +0x8, +0xC
 * Confidence medium, xref chain: +0x4 += +0x10, +0x8 += +0x14, +0xC += +0x18; guess_SetVelocityXZFromLocal writes +0x10/+0x18
 * Names ledger: config/names.tsv guess_AddVelocityToPos */
void guess_AddVelocityToPos(struct vec *a0) {
    a0->unk4 += a0->unk10;
    a0->unk8 += a0->unk14;
    a0->unkC += a0->unk18;
}
