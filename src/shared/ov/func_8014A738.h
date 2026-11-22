/* func_8014A738 — shared body (overlay slot 0x80128158, h_exact b51a4f8c). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 guess_TestGameFlag(s32);
s32 func_8014A738(void *arg0) {
    extern u8 guess_g_ObjectTable[]; // Names ledger: config/names.tsv guess_g_ObjectTable
    Vec_8014A738 d;
    u32 i;
    Unkstruct_801202A0 *base;
    if ((guess_TestGameFlag(0x83) & 0xFF) == 0) {
        return 0;
    }
    base = (Unkstruct_801202A0 *)guess_g_ObjectTable;
    for (i = 0; i < 0x60; i++) {
        if (base[i].unkC1.u == 7) {
            d.vx = ((Unkstruct_80126B58 *)arg0)->unk4.i.hi.u - base[i].unk4.i.hi.u;
            d.vz = ((Unkstruct_80126B58 *)arg0)->unkC.i.hi.u - base[i].unkC.i.hi.u;
            if (d.vx >= 0) {
                if (d.vx < 0x40) {
                    goto zcheck;
                }
            } else {
                if (-d.vx < 0x40) {
                    goto zcheck;
                }
            }
            continue;
        zcheck:
            if (d.vz >= 0) {
                if (d.vz < 0x40) {
                    goto found;
                }
            } else {
                if (-d.vz < 0x40) {
                    goto found;
                }
            }
            continue;
        found:
            return 1;
        }
    }
    return 0;
}
