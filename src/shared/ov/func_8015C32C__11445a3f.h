/* func_8015C32C — shared body (overlay slot 0x80128158, h_exact 11445a3f). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_8015C32C(s32 arg0) {

    extern void (*D_80181914[])(void *);
    s32 iVar2;
    u32 uVar4;
    s32 vin[4];
    s32 vout[4];

    func_80149FB0(arg0);
    if (((s32 (*)(s32))guess_IsConfirmPressed)(arg0) != 0) {
        D_80181914[*(u16 *)arg0]((void *)arg0);
        ((void (*)(s32))guess_EnterJumpState)(arg0);
        return;
    }
    switch (((s32 (*)(s32))func_801619A4)(arg0)) {
    case 0:
    case 1:
    case 6:
        if (((s32 (*)(s32))guess_IsSquarePressed)(arg0) != 0) {
            D_80181914[*(u16 *)arg0]((void *)arg0);
            ((void (*)(s32))guess_StartSquareAction)(arg0);
            return;
        }
        if (((s32 (*)(s32))guess_IsTrianglePressed)(arg0) != 0) {
            D_80181914[*(u16 *)arg0]((void *)arg0);
            ((void (*)(s32))guess_StartTriangleAction)(arg0);
            return;
        }
        break;
    case 3:
        ((void (*)(s32))func_801498E0)(arg0);
        break;
    case 4:
        ((void (*)(s32))func_80149954)(arg0);
        break;
    case 5:
        if (((s32 (*)(s32))guess_IsSquareOrTrianglePressed)(arg0) != 0) {
            D_80181914[*(u16 *)arg0]((void *)arg0);
            func_800CCCC0(arg0);
            return;
        }
    }
    if ((func_80148AFC((void *)arg0) & 0xff) != 0) {
        vin[0] = 0;
        vin[1] = 0;
        vin[2] = -0x4000;
        func_8001382C((s32)*(s16 *)(*(s32 *)(arg0 + 0x20) + 0x12), vin, vout);
        *(s32 *)(arg0 + 0x234) += vout[0];
        *(s32 *)(arg0 + 0x238) += vout[1];
        *(s32 *)(arg0 + 0x23c) += vout[2];
    }
    func_8001382C((s16)-*(u16 *)(*(s32 *)(arg0 + 0x20) + 0x12), (void *)(arg0 + 0x234), vout);
    guess_SetMoveVector((s32 *)arg0, vout);
    guess_SetVelocityFromMoveVector(arg0);
    ((void (*)(s32))guess_ApplyVelocity)(arg0);
    if ((guess_g_FrameCounter & 3) == 0) {
        guess_SpawnSmallObjectType2(arg0, 1);
        guess_PlaySoundUnlessSkipped(0x65f);
    }
    if (((s32 (*)(s32))func_8014D738)(arg0) != 0) {
        D_80181914[*(u16 *)arg0]((void *)arg0);
        ((void (*)(s32))func_8015C6E0)(arg0);
        return;
    }
    iVar2 = ((s32 (*)(s32))func_8014CC28)(arg0);
    uVar4 = ((u32 (*)(s32))func_8014F3E8)(arg0);
    if (uVar4 != 0) {
        if ((uVar4 & 0x4000) == 0) {
            if (guess_TickWaitTimer_2(arg0) != 0) {
                D_80181914[*(u16 *)arg0]((void *)arg0);
                guess_SetState((s32 *)arg0, 0);
                func_80159BE4(arg0);
            }
        } else {
            guess_SetState((s32 *)arg0, 4);
            func_8015C0C4(arg0);
        }
    } else {
        if (iVar2 == 0) {
            D_80181914[*(u16 *)arg0]((void *)arg0);
            guess_SetState((s32 *)arg0, 3);
            ((void (*)(s32))func_8015BE94)(arg0);
        }
    }
}
