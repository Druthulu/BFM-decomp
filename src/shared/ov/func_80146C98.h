/* guess_SetStep — shared body (overlay slot 0x80128158, h_exact 1a41e4df). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
/* guess_SetStep: sets the step counter (s16 at +0x2) of a0's state machine to a1, keeping the state (+0x0)
 * Confidence medium, xref chain: +0x2 = a1; guess_SetState writes +0x0 = state and +0x2 = 0, guess_NextStep adds 1 to +0x2; handlers jump to steps 0x9/0xB/0xC with it
 * Names ledger: config/names.tsv guess_SetStep */
void guess_SetStep(s32 *a0, s16 a1) {
    *(s16*)((s32)a0 + 0x2) = a1;
}
