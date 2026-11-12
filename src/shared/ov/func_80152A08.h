/* guess_EaseToSavedPosThenNextStep_2 — shared body (overlay slot 0x80128158, h_exact 376c5f93). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80149020(s32 *a0);
extern s32 func_801536DC(s32 a0);
extern void guess_NextStep(void *a0);
/* guess_EaseToSavedPosThenNextStep_2: state step: eases the position toward the saved point at +0xA0; once there sets +0xDE = 1, +0xDF = 0 and advances the step
 * Confidence low, xref chain: func_80149020(a0); if !func_801536DC(a0) (eases +6/+A/+E toward +0xA0/+0xA2/+0xA4, 0 when there): +0xDE = 1, +0xDF = 0, step +0x2 += 1
 * Names ledger: config/names.tsv guess_EaseToSavedPosThenNextStep_2 */
void guess_EaseToSavedPosThenNextStep_2(s32 a0) {
    func_80149020((s32 *)a0);
    if (!func_801536DC(a0)) {
        *(s8 *)(a0 + 0xDE) = 1;
        *(s8 *)(a0 + 0xDF) = 0;
        guess_NextStep((void *)a0);
    }
}
