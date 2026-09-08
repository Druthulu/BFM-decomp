/* func_8015DD74 — shared body (overlay slot 0x80128158, h_exact fa1d5e09). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_8014C4AC(s32 a0, s32 a1, s32 a2, s16 *a3, s32 a4);
int func_8015DD74(int arg0)
{
    s16 sp18[4];
    s32 s0;
    s0 = *(s32 *)(arg0 + 0x178);
    if (s0 != 0) {
        func_8014C1A0(arg0, s0);
        func_80015978(s0 + 4, (s32 *)sp18);
        sp18[3] = 0;
        func_8014C4AC(s0, 9, func_80029AAC(), sp18,
                      *(s16 *)(*(s32 *)(arg0 + 0x20) + 0x12));
        *(s32 *)(arg0 + 0x178) = 0;
    }
}
