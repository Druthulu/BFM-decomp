/* func_8014A380 — shared body (overlay slot 0x80128158, h_exact 16d0dd6e). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void guess_CopyVec3HighHalves(s32 a0, s32 *a1);
extern void guess_PostActorEvent(s32 a0, s32 a1, s32 a2, s16 *a3, s32 a4);
void func_8014A380(s32 a0, s32 a1) {
    s16 buf[4];
    guess_CopyVec3HighHalves(a0 + 4, (s32 *)buf);
    buf[3] = 0;
    guess_PostActorEvent(a1, 0x1F, 0, buf, *(s16 *)(*(s32 *)(a0 + 0x20) + 0x12));
}
