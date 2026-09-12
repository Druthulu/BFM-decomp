/* func_80137614 — shared body (overlay slot 0x80128158, h_exact d0c88331). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
s32 func_80137614(s32 a0, s32 a1, s32 a2)
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
