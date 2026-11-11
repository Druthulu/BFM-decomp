/* guess_SetState — shared body (overlay slot 0x80128158, h_exact af92b5cb). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
/* guess_SetState: sets a state machine's state (s16 at +0x0) to a1 and resets its step counter (s16 at +0x2) to 0
 * Confidence medium, code inference: writes a1 to the s16 at +0x0 and 0 to the s16 at +0x2 of a0; its 95 callers pass constant numbers; one caller saves the old +0x0 first, then sets +0x2 = 1
 * Names ledger: config/names.tsv guess_SetState */
void guess_SetState(s32 *a0, s16 a1) {
    *(s16*)((s32)a0 + 0x0) = a1;
    *(s16*)((s32)a0 + 0x2) = 0;
}
