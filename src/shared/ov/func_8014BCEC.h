/* func_8014BCEC — shared body (overlay slot 0x80128158, h_exact 3e099a2e). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern u16 D_80078EB6;
s32 func_8014BCEC(s32 a0, s32 a1)
{
    u16 v;
    v = D_80078EB6 + a1;
    D_80078EB6 = v;
    if (v >= 0x663) {
        D_80078EB6 = 0x662;
    }
}
