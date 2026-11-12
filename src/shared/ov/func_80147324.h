/* guess_PlaySoundUnlessSkipped — shared body (overlay slot 0x80128158, h_exact f4200521). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80147364(u16 param_1, u16 param_2);
extern void *D_8012707C;
/* guess_PlaySoundUnlessSkipped: requests sound id a0 unless it equals the one-shot skip id D_8012707C, which it then clears
 * Confidence medium, xref chain: id == D_8012707C -> D_8012707C = 0; else func_80147364(id, 0) (guess_PlaySound's call); func_801472DC / func_801472F0 set the skip id
 * Names ledger: config/names.tsv guess_PlaySoundUnlessSkipped */
void guess_PlaySoundUnlessSkipped(s32 arg0) {
    s32 temp_a0;
    temp_a0 = arg0 & 0xFFFF;
    if (temp_a0 == D_8012707C) {
        D_8012707C = 0;
        return;
    }
    func_80147364(temp_a0, 0);
}
