/* guess_RelocateHeaderOffsets — shared body (overlay slot 0x80128158, h_exact 20e578d3). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
/* guess_RelocateHeaderOffsets: turns the six offset words +0x8..+0x1C of the block a0 into pointers (adds a0) once, while +0x8 still holds 0x20
 * Confidence high, code inference: if (+0x8 == 0x20) { +0x8 = a0 + 0x20; +0xC, +0x10, +0x14, +0x18, +0x1C += a0 }
 * Names ledger: config/names.tsv guess_RelocateHeaderOffsets */
void guess_RelocateHeaderOffsets(s32 a0) {
    if (*(s32*)(a0 + 0x8) == 0x20) {
        *(s32*)(a0 + 0x8) = a0 + 0x20;
        *(s32*)(a0 + 0xC) += a0;
        *(s32*)(a0 + 0x10) += a0;
        *(s32*)(a0 + 0x14) += a0;
        *(s32*)(a0 + 0x18) += a0;
        *(s32*)(a0 + 0x1C) += a0;
    }
}
