/* guess_OpenTextWindowWithFlags — shared body (overlay slot 0x80128158, h_exact d0c88331). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
/* guess_OpenTextWindowWithFlags: as guess_OpenTextWindow with flags a2 & 0xD8, and stores a1 in the record's s16 +0x1C; returns the record or 0
 * Confidence medium, xref chain: rec = func_801399A8(); func_801377B4(a0, a2 & 0xD8, rec); rec+0x1C = a1; the open path of guess_OpenTextWindow
 * Names ledger: config/names.tsv guess_OpenTextWindowWithFlags */
s32 guess_OpenTextWindowWithFlags(s32 a0, s32 a1, s32 a2)
{
    s32 s0;
    u16 v1;
    v1 = a1;
    s0 = func_801399A8();
    if (s0 != 0) {
        func_801377B4(a0, a2 & 0xD8, s0);
        *(s16 *)(s0 + 0x1C) = v1;
    }
    return s0;
}
