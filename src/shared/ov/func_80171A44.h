/* func_80171A44 — shared body (overlay slot 0x80128158, h_exact c78eaf58). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
s32 func_80171A44(u8 *a0)
{
    s32 v = a0[0x215] + 1;
    a0[0x216] = 0;
    a0[0x215] = v;
    return v;
}
