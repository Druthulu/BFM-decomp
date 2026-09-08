/* func_8015E0D4 — shared body (overlay slot 0x80128158, h_exact 5953c40c). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
int func_8015E0D4(int a0)
{
    s16 sp18[4];
    s32 s0;
    s0 = *(s32 *)(a0 + 0x178);
    if (s0 != 0) {
        func_8014C1A0(a0, s0);
        func_80015978(s0 + 4, (s32 *)sp18);
        sp18[3] = 0;
        func_8014C4AC(s0, 0x11, func_80029AAC(), sp18,
                      *(s16 *)(*(s32 *)(a0 + 0x20) + 0x12));
        *(s32 *)(a0 + 0x178) = 0;
    }
}
