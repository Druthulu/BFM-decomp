/* guess_WorldToScreenFlag — shared body (overlay slot 0x80128158, h_exact 26e46daf). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
/* guess_WorldToScreenFlag: projects point a0 with the camera matrix (GTE rtps), stores the screen xy at a1 and returns the GTE flag word
 * Confidence medium, xref chain: gte_SetRotMatrix/SetTransMatrix(guess_g_CameraWsMatrix); ldv0(a0); rtps; stsxy(a1); return stflg; guess_WorldToScreen's inline twin
 * Names ledger: config/names.tsv guess_WorldToScreenFlag */
s32 guess_WorldToScreenFlag(void *param_1, void *param_2)
{
    extern u8 guess_g_CameraWsMatrix;
    s32 *m;
    s32 flag;
    m = (s32 *)&guess_g_CameraWsMatrix;
    gte_SetRotMatrix(m);
    gte_SetTransMatrix(m);
    gte_ldv0(param_1);
    gte_rtps();
    gte_stsxy(param_2);
    gte_stflg(&flag);
    return flag;
}
