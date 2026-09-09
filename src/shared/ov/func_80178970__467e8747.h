/* func_80178970 — shared body (overlay slot 0x80128158, h_exact 467e8747). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
int func_80178970(void)
{
    register int r __asm__("$2");
    int v;

    v = ((s32 (*)(void))func_801789AC)();
    r = 0;
    if (v != 0)
        r = D_8018FAB0 == 0;
    return r;
}
