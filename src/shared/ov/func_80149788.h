/* guess_StartChargedSquareAction — shared body (overlay slot 0x80128158, h_exact a99691d4). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_8015F7A0(s32 *arg0);
/* guess_StartChargedSquareAction: enters player state 0x15 (func_8015F7A0: guess_SetState(a0, 0x15) and its first step), the action after guess_IsChargedSquarePressed
 * Confidence low, xref chain: func_8015F7A0(a0): guess_SetState(a0, 0x15), func_8015F7D4 runs D_80180D58[+0x2]; called only after guess_IsChargedSquarePressed
 * Names ledger: config/names.tsv guess_StartChargedSquareAction */
void guess_StartChargedSquareAction(void) {
    KR_AS(void, func_8015F7A0)();
}
