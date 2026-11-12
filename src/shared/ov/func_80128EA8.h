/* guess_StartPairSequence — shared body (overlay slot 0x80128158, h_exact 2905b55f). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
/* guess_StartPairSequence: starts the cursor a1 on pair-sequence table a2 (index 0, count from entry 0's flags & 0x3F) and writes entry 0's halves to a0 +0x28/+0x2A
 * Confidence medium, code inference: a1+0 = a2, a1+4 = 0, a1+6 = a2[1] & 0x3F; a0+0x28/+0x2A = a2's two halfwords; the cursor guess_StepPairSequence advances
 * Names ledger: config/names.tsv guess_StartPairSequence */
void guess_StartPairSequence(s32 a0, s32 a1, s32 a2) {
    *(s32 *)(a1 + 0x0) = a2;                       /* sw a2, 0x0(a1) */
    *(s16 *)(a1 + 0x4) = 0;                         /* sh zero, 0x4(a1) */
    *(s16 *)(a1 + 0x6) = (*(s32 *)(a2 + 0x4)) & 0x3F; /* lw; andi 0x3F; sh 0x6(a1) */
    *(s16 *)(a0 + 0x28) = *(u16 *)(a2 + 0x0);      /* lhu 0x0(a2); sh 0x28(a0) */
    *(s16 *)(a0 + 0x2A) = *(u16 *)(a2 + 0x2);      /* lhu 0x2(a2); sh 0x2A(a0) */
}
