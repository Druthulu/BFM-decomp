/* guess_StartActorSequence_2 — shared body (overlay slot 0x80128158, h_exact 5f61e157). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_8012AAAC();  // K&R: 0 of 1 args (P37 rung D t4_HD7)
/* guess_StartActorSequence_2: points an object's sequence at a1 (+0x90), resets its index (+0x94) and return link (+0x9C, +0x9A), then steps it
 * Confidence medium, code inference: sets +0x90 = a1, clears +0x94/+0x9C/+0x9A and bits 0x600 of +0x72, then calls the 8-byte-entry list stepper func_8012AAAC
 * Names ledger: config/names.tsv guess_StartActorSequence_2 */
void guess_StartActorSequence_2(u8 *a0, s32 a1) {
    u16 v0 = *(u16 *)(a0 + 0x72);
    *(s32 *)(a0 + 0x90) = a1;
    *(s32 *)(a0 + 0x94) = 0;
    *(s32 *)(a0 + 0x9C) = 0;
    *(s16 *)(a0 + 0x9A) = 0;
    *(u16 *)(a0 + 0x72) = v0 & 0xF9FF;
    func_8012AAAC();
}
