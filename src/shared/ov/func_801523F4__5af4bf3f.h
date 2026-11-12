/* func_801523F4 — shared body (overlay slot 0x80128158, h_exact 5af4bf3f). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_801523F4(s32 arg0)
{
    s32 pad[4];
    s32 buf[4];
    s32 s0a;                    /* $s0 = buf */
    s32 s2a = (s32)&D_80180828; /* $s2 = &D_80180828 */

    ((void (*)(s32, s32))guess_SetWaitTimer_2)(arg0, 0);
    guess_StartPadVibration(&guess_g_RumblePatternFade);
    ((void (*)(s32, s32))func_80151204)(arg0, *(s16 *)(arg0 + 0xF2));
    if ((s16)func_80012A60((s32)*(s16 *)(*(s32 *)(arg0 + 0x20) + 0x12),
                           (s32)*(s16 *)(arg0 + 0xF4)) >= 0x401) {
        ((void (*)(s32, s32))guess_SetAnimScript)(arg0, (s32)&D_800D5880);
    } else {
        ((void (*)(s32, s32))guess_SetAnimScript)(arg0, (s32)&D_800D58AC);
    }
    guess_SetTexAnim(arg0, 0x16);
    ((void (*)(s32))func_80149020)(arg0);
    s0a = (s32)buf;
    ((void (*)(s32, s32, s32))func_8001382C)((*(u16 *)(arg0 + 0xF4) - *(u16 *)(*(s32 *)(arg0 + 0x20) + 0x12)) & 0xFFF,
                  s2a, s0a);
    ((void (*)(s32, s32))guess_SetMoveVector)(arg0, s0a);
    ((void (*)(s32, s32))guess_SetVertSpeed)(arg0, *(s32 *)(s2a + 0xC));
    guess_PlaySoundUnlessSkipped(0x451);
    ((void (*)(s32))guess_NextStep)(arg0);
    (void)pad;
}
