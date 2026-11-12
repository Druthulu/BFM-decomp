/* func_8015EA3C — shared body (overlay slot 0x80128158, h_exact 47c5b5e8). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_8015EA3C(void *arg0) {

    extern s16 guess_g_CameraRelativeYaw; // Names ledger: config/names.tsv guess_g_CameraRelativeYaw
    s32 invec[4];
    s32 outbuf[4];
    s32 temp;
    s32 r;

    if (!(((s32 (*)(void))guess_GetPadHeld)() & 8)) {
        D_80181160[*(u16 *)arg0](arg0);
        ((void (*)(void *, s16))guess_SetState)(arg0, 0);
        func_80159B70(arg0);
        return;
    }
    r = ((s32 (*)(void *))func_80149D10)(arg0);
    if (r == 1) goto Lcase1;
    if (r < 2) goto Ldefault;
    if (r == 2) goto Lcase2;
    goto Ldefault;
Lcase1:
    D_80181160[*(u16 *)arg0](arg0);
    func_80175150(arg0);
    return;
Lcase2:
    guess_ReturnPlayerToStandingState(*(s32 *)((u8 *)arg0 + 0x21C), 0x01000000);
    return;
Ldefault:
    if (((s32 (*)(void *))guess_IsChargedSquarePressed)(arg0) != 0) {
        D_80181160[*(u16 *)arg0](arg0);
        ((void (*)(void *))guess_StartChargedSquareAction)(arg0);
        return;
    }
    if (func_80161B84(arg0) != 0) {
        return;
    }
    if (func_8014A4B4(arg0) != 0) {
        D_80181160[*(u16 *)arg0](arg0);
        ((void (*)(void *))func_8014A4FC)(arg0);
        return;
    }
    if (((s32 (*)(void *))guess_IsSquarePressed)(arg0) != 0) {
        D_80181160[*(u16 *)arg0](arg0);
        ((void (*)(void *))guess_StartSquareAction)(arg0);
        return;
    }
    if (((s32 (*)(void *))guess_IsTrianglePressed)(arg0) != 0) {
        D_80181160[*(u16 *)arg0](arg0);
        ((void (*)(void *))guess_StartTriangleAction)(arg0);
        return;
    }
    if (func_800CF8B4() != 0) {
        *(u16 *)(*(s32 *)((u8 *)arg0 + 0x20) + 0x12) =
            ((*(u16 *)&guess_g_CameraRelativeYaw) + ((s32 (*)(void *))guess_GetCameraYaw)(arg0)) & 0xFFF;
    }
    temp = func_80148E54(arg0);
    if ((s16)temp >= 0) {
        s32 d = temp - *(u16 *)(*(s32 *)((u8 *)arg0 + 0x20) + 0x12);
        invec[0] = 0;
        invec[1] = 0;
        invec[2] = 0xFFFC0000;
        func_8001382C((s16)d, invec, outbuf);
        ((void (*)(void *, void *))guess_SetMoveVector)(arg0, outbuf);
        ((void (*)(void *))guess_SetVelocityFromMoveVector)(arg0);
        ((void (*)(void *))guess_ApplyVelocity)(arg0);
        ((void (*)(void *, s32))guess_SetAnim)(arg0, 0x1E);
    } else {
        ((void (*)(void *, s32))guess_SetAnim)(arg0, 0x1D);
    }
    if (((s32 (*)(void *))func_8014D738)(arg0) != 0) {
        D_80181160[*(u16 *)arg0](arg0);
        ((void (*)(void *, s16))guess_SetState)(arg0, 9);
        func_8015C714(arg0);
        return;
    }
    if (((s32 (*)(s32))func_80161208)(arg0) == 0) {  /* §17a-1 */
        ((void (*)(void *))guess_SaveGroundedPos)(arg0);
    }
}
