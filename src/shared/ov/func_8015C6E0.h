/* guess_EnterState9 — shared body (overlay slot 0x80128158, h_exact c48dfc14). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void guess_SetState(s32 *a0, s16 a1);
extern void func_8015C714(void *a0);
/* guess_EnterState9: puts a0's state machine in state 9 (guess_SetState) and runs that state's step 0 at once
 * Confidence medium, code inference: guess_SetState(a0, 9); func_8015C714 calls step table[+0x2]; called from state 4's steps func_8015C128/func_8015C32C
 * Names ledger: config/names.tsv guess_EnterState9 */
void guess_EnterState9(s32 *a0) {
    guess_SetState(a0, 0x9);
    func_8015C714(a0);
}
