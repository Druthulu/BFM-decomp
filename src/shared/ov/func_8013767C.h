/* guess_OpenTextWindow — shared body (overlay slot 0x80128158, h_exact 5887ff3a). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_801399A8(void);
extern void func_801377B4(s32 a0, s32 a1, s32 a2);
/* guess_OpenTextWindow: takes a free text window record (func_801399A8) and starts text a0 in it (func_801377B4, flags 0); returns the record or 0
 * Confidence medium, xref chain: rec = func_801399A8() (first free of guess_g_TextBoxes 1-2); func_801377B4(a0, 0, rec): +0 = text, +4 = 1; func_80158FA4 passes the start prompt
 * Names ledger: config/names.tsv guess_OpenTextWindow */
s32 guess_OpenTextWindow(s32 a0) {
    s32 s0 = func_801399A8();
    if (s0 != 0) {
        func_801377B4(a0, 0, s0);
    }
    return s0;
}
