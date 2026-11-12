/* func_8015D738 — shared body (overlay slot 0x80128158, h_exact d338deef). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_8015D738(void *arg0) {

    extern u8 D_80181124[];
    extern u8 D_80181134[];
    u8 *p = guess_g_PlayerRecord;
    s32 s1;
    ((void (*)(void))func_80148AFC)();
    if (func_80161B18(arg0) != 0) return;
    if (func_80161B84(arg0) != 0) return;
    do {
        s1 = *(s32 *)((char *)arg0 + 0x178);
    } while (0);
    if (s1 != 0 && *(u16 *)s1 == 0x360) goto block_808;
    s1 = *(s32 *)((char *)arg0 + 0x178);
    if (s1 == 0 || *(u16 *)s1 == 0) {
        D_80181160[*(u16 *)arg0](arg0);
        ((void (*)(void *, s32))guess_SetState)(arg0, 0);
        func_80159B70(arg0);
        return;
    }
    if (((s32 (*)(void *))guess_GetPadPressed)(arg0) & 0x80) {
    block_808:
        ((void (*)(void *, s32))guess_SetTexAnim)(arg0, 0x11);
        ((void (*)(void *))func_8015DAC4)(arg0);
        return;
    }
    if ((((s32 (*)(void *))guess_GetPadPressed)(arg0) & 0x10) && ((s32 (*)(void *))func_8014BEF8)(arg0) != 0) {
        ((void (*)(void *, s32))guess_SetTexAnim)(arg0, 0x11);
        ((void (*)(void *))func_8015DE24)(arg0);
        return;
    }
    if ((((s32 (*)(void *))guess_GetPadPressed)(arg0) & 0x20) && p[0x49] == 0xA) {
        if (((s32 (*)(void *))func_80165624)(arg0) != 0) {
            ((void (*)(void *))func_8015DA5C)(arg0);
            ((void (*)(void *))func_8015F948)(arg0);
            return;
        }
        ((void (*)(void *, s32))guess_SetTexAnim)(arg0, 0x11);
        func_800CAF14(arg0);
        return;
    }
    if (((s32 (*)(void *))guess_IsDirectionHeld)(arg0) != 0 && *(u16 *)(*(s32 *)((char *)arg0 + 0x178)) != 0x82) {
        ((void (*)(void *, s32))guess_SetAnim)(arg0, 0x1B);
        ((void (*)(void *, void *))guess_SetMoveVector)(arg0, &D_80181124);
    } else {
        ((void (*)(void *, s32))guess_SetAnim)(arg0, 0x1A);
        ((void (*)(void *, void *))guess_SetMoveVector)(arg0, &D_80181134);
    }
    ((void (*)(void *))guess_SetVelocityFromMoveVector)(arg0);
    ((void (*)(void *))guess_ApplyVelocity)(arg0);
    s1 = *(s32 *)((char *)arg0 + 0x178);
    *(s16 *)(s1 + 6) = (s16)((s8)D_801813A4[*(s32 *)((char *)arg0 + 0x234)] + *(u16 *)(*(s32 *)(s1 + 0x78) + 0xc));
    *(s16 *)(s1 + 0xa) = (s16)((s8)D_801813A4[*(s32 *)((char *)arg0 + 0x234) + 1] + *(u16 *)(*(s32 *)(s1 + 0x78) + 0xe));
    *(s16 *)(s1 + 0xe) = (s16)((s8)D_801813A4[*(s32 *)((char *)arg0 + 0x234) + 2] + *(u16 *)(*(s32 *)(s1 + 0x78) + 0x10));
    ((void (*)(void *, void *))guess_TransformPosByObjMatrix)(arg0, (void *)(s1 + 4));
    *(s16 *)(*(s32 *)(s1 + 0x20) + 0x12) = (*(u16 *)(*(s32 *)((char *)arg0 + 0x20) + 0x12) + 0x800) & 0xFFF;
    if (((s32 (*)(void *))func_8014D738)(arg0) != 0) {
        D_80181160[*(u16 *)arg0](arg0);
        ((void (*)(void *, s32))guess_SetState)(arg0, 9);
        func_8015C714(arg0);
        return;
    }
    if (func_80161208(arg0) != 0) return;
    ((void (*)(void *))guess_SaveGroundedPos)(arg0);
}
