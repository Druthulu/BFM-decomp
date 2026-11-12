/* guess_SetTexAnimScript — shared body (overlay slot 0x80128158, h_exact 48c87330). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80154B7C(u8 *a0, s32 a1);
/* guess_SetTexAnimScript: starts the texture-animation script a1 on a0 unless it is already the one at +0xD0
 * Confidence medium, xref chain: if (+0xD0 != a1) func_80154B7C: +0xD0 = a1, +0xD4 = +0xD6 = 1, +0xD8 = +0xD9 = 0; guess_SetTexAnim with the script given directly
 * Names ledger: config/names.tsv guess_SetTexAnimScript */
void guess_SetTexAnimScript(u8 *a0, s32 a1) {
    if (*(s32 *)(a0 + 0xD0) != a1) {
        func_80154B7C(a0, a1);
    }
}
