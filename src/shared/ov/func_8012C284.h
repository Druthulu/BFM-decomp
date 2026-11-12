/* func_8012C284 — shared body (overlay slot 0x80128158, h_exact f450e581). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern u8 guess_g_BoxHitCenterX[]; // Names ledger: config/names.tsv guess_g_BoxHitCenterX
u16 *func_8012C284(u16 *a0)
{
    u16 *end;
    end = (u16 *)guess_g_BoxHitCenterX;
    if (a0 == 0) {
        a0 = (u16 *)(guess_g_BoxHitCenterX - 0x6480);
    } else {
        a0 = (u16 *)((u8 *)a0 + 0x10C);
    }
    while (a0 != end) {
        if (*a0 == 0) {
            return a0;
        }
        a0 = (u16 *)((u8 *)a0 + 0x10C);
    }
    return 0;
}
