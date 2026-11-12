/* guess_IsConfirmPressed — shared body (overlay slot 0x80128158, h_exact a4d9cd33). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
/* guess_IsConfirmPressed: returns 1 when the confirm button (0x40) is newly pressed and +0x178 is clear, else 0
 * Confidence medium, xref chain: +0x178 != 0 returns 0; else returns (+0xAC & 0x40) != 0, +0xAC the newly-pressed copy and 0x40 the menus' confirm bit
 * Names ledger: config/names.tsv guess_IsConfirmPressed */
s32 guess_IsConfirmPressed(void *a0) {
    s32 v0 = 0;
    if (*(s32 *)((s32)a0 + 0x178)) {
        return v0;
    }
    v0 = *(u16 *)((s32)a0 + 0xAC) & 0x40;
    if (v0) {
        v0 = 1;
    }
    return v0;
}
