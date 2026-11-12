/* guess_GetTimeUntilGameVar08 — shared body (overlay slot 0x80128158, h_exact 11673a70). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern int func_800291DC(int);
extern s16 func_800D0E30(void *a0);
/* guess_GetTimeUntilGameVar08: returns the time left (hours * 100 + minutes) until the hour:minute stored at byte 0x8 of the game-variable table
 * Confidence medium, xref chain: func_800D0E30(func_800291DC(8) & 0x7FFF): stored hour/minute minus D_80078EB1/guess_g_ClockMinute, wrapped; hi * 100 + lo
 * Names ledger: config/names.tsv guess_GetTimeUntilGameVar08 */
int guess_GetTimeUntilGameVar08(void) {
    short local;
    int lo;
    local = func_800291DC(8) & 0x7FFF;
    local = func_800D0E30(&local);
    lo = *(unsigned char *)&local;
    return (short)(*((unsigned char *)&local + 1) * 100 + lo);
}
