/* guess_TryStartCircleAction — shared body (overlay slot 0x80128158, h_exact 2e065293). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_801497A8();  // K&R: 0 of 1 args (P37 rung D t4_HD7)
extern void func_801599A4(void *a0);
extern void func_80149864(void);
/* guess_TryStartCircleAction: when func_801497A8 sees Circle newly pressed (+0xAC & 0x20) and the action allowed, ends the current state and enters state 0x17; returns 1, else 0
 * Confidence low, xref chain: func_801497A8: +0xAC & 0x20 (Circle) unless state 0x1A or +0x44 & 0x404; then D_80180A1C[state](a0), func_801653B8: guess_SetState(a0, 0x17)
 * Names ledger: config/names.tsv guess_TryStartCircleAction */
int guess_TryStartCircleAction(void *param_1)
{
    if (func_801497A8() == 0) {
        return 0;
    }
    func_801599A4(param_1);
    ((void (*)(void *))func_80149864)(param_1);
    return 1;
}
