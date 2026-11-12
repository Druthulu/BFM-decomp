/* guess_EnterState11 — shared body (overlay slot 0x80128158, h_exact 31db8954). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void guess_SetState(s32 *a0, s16 a1);
extern void func_8015E8E8();
/* guess_EnterState11: puts a0's state machine in state 0x11 (guess_SetState) and runs that state's step 0 at once
 * Confidence medium, code inference: guess_SetState(a0, 0x11); func_8015E8E8 calls step table[+0x2]; the standing step enters it when guess_IsR1Held returns 1
 * Names ledger: config/names.tsv guess_EnterState11 */
void guess_EnterState11(s32 *a0) {
    guess_SetState(a0, 0x11);
    func_8015E8E8(a0);
}
