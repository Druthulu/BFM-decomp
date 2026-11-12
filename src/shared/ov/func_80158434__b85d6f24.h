/* func_80158434 — shared body (overlay slot 0x80128158, h_exact b85d6f24). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_80158434(s32 param_1)
{
    u32 uVar1;
    u32 uVar2;
    s32 frame_pad[4];
    (void)&frame_pad;

    *(u32 *)(param_1 + 0x44) = *(u32 *)(param_1 + 0x44) | 2;
    if ((*(u16 *)(param_1 + 0xB8) & 0x4000) != 0) {
        *(s32 *)(param_1 + 0x234) = *(s32 *)(param_1 + 0x234) + 1;
        ((s32 (*)(void))guess_ClearStoodOnActor)();
        ((void (*)(s32))guess_ClearTiltVectors)(param_1);
        ((void (*)(s32, s32))guess_SetVertSpeed)(param_1, 0xFFFA0000);
        ((void (*)(s32, s32))guess_SetMoveVector)(param_1, (s32)&D_801815A8);
    }
    if (*(s32 *)(param_1 + 0x234) != 0) {
        guess_AddVertSpeed(param_1, 0x10000);
        guess_ApplyVertSpeed(param_1);
        func_80147AD4(param_1, 0, 0, 0);
        ((void (*)(s32))guess_ApplyVelocity)(param_1);
    }
    uVar1 = ((s32 (*)(s32, s32))func_801615C4)(param_1, 0);
    if (uVar1 != 0) {
        if (uVar1 == 1) goto LAB_80158508;
        uVar2 = uVar1 & 0x2000;
    } else {
        uVar2 = guess_TickWaitTimer_2(param_1);
    }
    if (uVar2 == 0) goto LAB_80158528;
LAB_80158508:
    ((void (*)(s32, s32))guess_SetAnimScript)(param_1, (s32)&D_800D533C);
    ((void (*)(s32))func_80146CA0)(param_1);
    return;
LAB_80158528:
    ((void (*)(s32, s32))func_80155FF8)(param_1, *(u8 *)(param_1 + 0x1AA));
}
