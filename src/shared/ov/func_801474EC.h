/* guess_ClearTiltVectors — shared body (overlay slot 0x80128158, h_exact c43c4e20). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
/* guess_ClearTiltVectors: zeroes the three s16 vectors the tilt update uses: current (+0x118), target (+0x120) and offset (+0x128)
 * Confidence medium, xref chain: zeroes +0x118..+0x11C, +0x120..+0x124, +0x128..+0x12C; func_80147514 eases +0x118 toward +0x120 (+ +0x128) and builds a matrix from it
 * Names ledger: config/names.tsv guess_ClearTiltVectors */
void guess_ClearTiltVectors(s32 *a0) {
    *(s16 *)((s32)a0 + 0x11C) = 0;
    *(s16 *)((s32)a0 + 0x11A) = 0;
    *(s16 *)((s32)a0 + 0x118) = 0;
    *(s16 *)((s32)a0 + 0x124) = 0;
    *(s16 *)((s32)a0 + 0x122) = 0;
    *(s16 *)((s32)a0 + 0x120) = 0;
    *(s16 *)((s32)a0 + 0x12C) = 0;
    *(s16 *)((s32)a0 + 0x12A) = 0;
    *(s16 *)((s32)a0 + 0x128) = 0;
}
