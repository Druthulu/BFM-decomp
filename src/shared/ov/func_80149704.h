/* guess_EnterJumpState — shared body (overlay slot 0x80128158, h_exact 4d663e3d). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_8015AD08();  // K&R: 0 of 1 args (P37 rung D t4_HD7)
/* guess_EnterJumpState: puts the object in state 2 and runs that state's first step (the jump launch)
 * Confidence low, xref chain: func_8015AD08: guess_SetState(a0, 2), step 0 func_8015AD78 -> func_8015ADB0 sets vertical speed -0x12; entered on Cross
 * Names ledger: config/names.tsv guess_EnterJumpState */
void guess_EnterJumpState(void) {
    func_8015AD08();
}
