/* guess_SetAnimScript — shared body (overlay slot 0x80128158, h_exact dac93a94). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_801542A4();  // K&R: 0 of 2 args (P37 rung D t4_HD5)
/* guess_SetAnimScript: starts animation script a1 (a pointer) unless it is already the current one (+0xB4)
 * Confidence medium, xref chain: if +0xB4 != a1: func_801542A4 sets +0xB4 = a1, resets its counters and steps it; guess_SetAnim takes an index into +0xB0 instead
 * Names ledger: config/names.tsv guess_SetAnimScript */
void guess_SetAnimScript(s32 *a0, s32 a1) {
    if (*(s32 *)((s32)a0 + 0xB4) != a1) {
        func_801542A4();
    }
}
