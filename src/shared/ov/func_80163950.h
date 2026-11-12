/* func_80163950 — shared body (overlay slot 0x80128158, h_exact 3f08c26c). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern u8 guess_g_ObjectTable[];
extern u8 guess_g_BoxHitCenterX[];
extern void guess_CopyVec3HighHalves(s32 a0, s32 *a1);
extern s32 func_80135A4C(s32 a0, s32 a1, s32 *a2, s32 a3);
extern void func_80015954(s32 a0, s32 a1);
s32 func_80163950(s32 a0) {
    s32 sp10[2];
    s32 sp18[2];
    u8 *p;
    guess_CopyVec3HighHalves(a0 + 4, sp10);
    guess_CopyVec3HighHalves(a0 + 4, sp18);
    *(s16 *)((s32)sp10 + 0x2) = *(u16 *)((s32)sp10 + 0x2) - 0x20;
    *(s16 *)((s32)sp18 + 0x2) = *(u16 *)((s32)sp18 + 0x2) + 0x8;
    for (p = guess_g_ObjectTable; p < guess_g_ObjectTable + 0x6480; p += 0x10C) {
        if (*(u16 *)p == 0) continue;
        if ((*(u16 *)(p + 0x5C) & 0x400) == 0) continue;
        if (*(s32 *)(p + 0x58) == 0) continue;
        if (func_80135A4C(*(s32 *)(p + 0x20), *(s32 *)(p + 0x58), sp10, (s32)sp18) != 0) {
            func_80015954((s32)sp18, a0 + 4);
            return 1;
        }
    }
    return 0;
}
