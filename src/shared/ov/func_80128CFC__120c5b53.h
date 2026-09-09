/* func_80128CFC — shared body (overlay slot 0x80128158, h_exact 120c5b53). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
s32 func_80128CFC(s32 arg0) {

    extern s16 D_8017F538[];
    s16 idx = D_8017F538[arg0];

    if (idx >= 0) {
        func_8001ABBC(0, 0, (u8 *)&cdFileLocTable[idx], D_8018D4F8, 0);
    } else {
        return 1;
    }
}
