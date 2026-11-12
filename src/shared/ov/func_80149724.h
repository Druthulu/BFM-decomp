/* guess_EnterJumpStateAndLaunch — shared body (overlay slot 0x80128158, h_exact c19bb350). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_8015ACC4();  // K&R: 0 of 1 args (P37 rung D t4_HD7)
/* guess_EnterJumpStateAndLaunch: puts the object in state 2 and launches it at once (func_8015ADB0) without step 0's check
 * Confidence low, xref chain: func_8015ACC4: guess_SetState(a0, 2), func_8014ED28, func_8014FA04, then func_8015ADB0 (vertical speed -0x12)
 * Names ledger: config/names.tsv guess_EnterJumpStateAndLaunch */
void guess_EnterJumpStateAndLaunch(void) {
    func_8015ACC4();
}
