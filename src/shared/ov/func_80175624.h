/* func_80175624 — shared body (overlay slot 0x80128158, h_exact 6fa48c7e). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s16 guess_g_DoubleBufferIndex; // Names ledger: config/names.tsv guess_g_DoubleBufferIndex
extern void func_801757A0(s32);
void func_80175624(void *a0) {
    func_801757A0(guess_g_DoubleBufferIndex);
    *((u8 *)a0 + 1) = *((u8 *)a0 + 1) + 1;
}
