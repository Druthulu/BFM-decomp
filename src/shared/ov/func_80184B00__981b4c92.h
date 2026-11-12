/* guess_NextStep_5 — shared body (overlay slot 0x80128158, h_exact 981b4c92). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
/* guess_NextStep_5: advances a state machine's step counter (s16 at +0x2) by one
 * Confidence medium, xref chain: +0x2 += 1; guess_SetState writes the state at +0x0 and resets this counter to 0; state set-up handlers end with it
 * Names ledger: config/names.tsv guess_NextStep_5 */
void guess_NextStep_5(void *a0) {
        *(s16 *)((s32)a0 + 0x2) += 1;
    }
