/* func_8015CD20 — shared body (overlay slot 0x80128158, h_exact d8c58cdb). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
/* $v0 at exit: result of guess_ClearMoveVector or result of guess_SetMoveVector or result of func_80159B70 or result of func_801725E0; no byte-neutral return: `return 0;` moved `move v0,zero` at +0x1E4, ov_SC03_126 objdump */
s32 func_8015CD20(s32 arg0) {
    extern void (*D_80181914[])(Unkstruct_80126B58 *);
    extern u8 D_801818C8;
    extern u8 D_80181AB8;
    extern u8 D_80181AC8;

    s32 temp_v0;
    s32 var_v0;
    Unkstruct_8001C9D0 *sp;

    ((void(*)())func_80149FB0)();
    if (((s32(*)(Unkstruct_80126B58 *))guess_IsConfirmPressed)(((Unkstruct_80126B58 *)arg0)) != 0) {
        D_80181914[((Unkstruct_80126B58 *)arg0)->unk0](((Unkstruct_80126B58 *)arg0));
        ((Unkstruct_80126B58 *)arg0)->unk1BC = 0xA;
        ((s32(*)(Unkstruct_80126B58 *))guess_EnterJumpStateAndLaunch)(((Unkstruct_80126B58 *)arg0));
        if (((s32(*)(Unkstruct_80126B58 *))func_80148AFC)(((Unkstruct_80126B58 *)arg0)) & 0xFF) {
            ((void(*)(Unkstruct_80126B58 *, u8 *))guess_SetMoveVector)(((Unkstruct_80126B58 *)arg0), &D_801818C8);
        } else {
            ((void(*)(Unkstruct_80126B58 *))guess_ClearMoveVector)(((Unkstruct_80126B58 *)arg0));
        }
        return;
    }
    temp_v0 = ((Unkstruct_80126B58 *)arg0)->unk234;
    if (temp_v0 == 0) {
        if (((s32(*)(Unkstruct_80126B58 *))guess_IsDownHeld)(((Unkstruct_80126B58 *)arg0)) != 0) {
            ((void(*)(Unkstruct_80126B58 *, u8 *))guess_SetMoveVector)(((Unkstruct_80126B58 *)arg0), &D_80181AB8);
            ((void(*)(Unkstruct_80126B58 *))guess_SetVelocityFromMoveVector)(((Unkstruct_80126B58 *)arg0));
            ((void(*)(Unkstruct_80126B58 *))guess_ApplyVelocity)(((Unkstruct_80126B58 *)arg0));
            ((void(*)(Unkstruct_80126B58 *, s32))guess_SetAnim)(((Unkstruct_80126B58 *)arg0), 0x15);
            sp = ((Unkstruct_80126B58 *)arg0)->unk20.m;
            var_v0 = sp->head.unk10.w.unk12.u - 0xAA;
            goto block_13;
        }
        if (((s32(*)(Unkstruct_80126B58 *))func_8014891C)(((Unkstruct_80126B58 *)arg0)) != 0) {
            ((void(*)(Unkstruct_80126B58 *, u8 *))guess_SetMoveVector)(((Unkstruct_80126B58 *)arg0), &D_80181AC8);
            ((void(*)(Unkstruct_80126B58 *))guess_SetVelocityFromMoveVector)(((Unkstruct_80126B58 *)arg0));
            ((void(*)(Unkstruct_80126B58 *))guess_ApplyVelocity)(((Unkstruct_80126B58 *)arg0));
            ((void(*)(Unkstruct_80126B58 *, s32))guess_SetAnim)(((Unkstruct_80126B58 *)arg0), 0x14);
            ((Unkstruct_80126B58 *)arg0)->unkB8.s = 1;
        }
        if (((s32(*)(Unkstruct_80126B58 *))func_801489E8)(((Unkstruct_80126B58 *)arg0)) != 0) {
            sp = ((Unkstruct_80126B58 *)arg0)->unk20.m;
            var_v0 = sp->head.unk10.w.unk12.u + 0x71;
            goto block_13;
        }
        if (((s32(*)(Unkstruct_80126B58 *))func_80148A48)(((Unkstruct_80126B58 *)arg0)) != 0) {
            sp = ((Unkstruct_80126B58 *)arg0)->unk20.m;
            var_v0 = sp->head.unk10.w.unk12.u - 0x71;
block_13:
            sp->head.unk10.w.unk12.u = var_v0 & 0xFFF;
        }
    } else {
        ((Unkstruct_80126B58 *)arg0)->unk234 = temp_v0 - 1;
    }
    ((void(*)(Unkstruct_80126B58 *))func_8014FA04)(((Unkstruct_80126B58 *)arg0));
    if (((s32(*)(Unkstruct_80126B58 *))func_8014E434)(((Unkstruct_80126B58 *)arg0)) == 0) {
        D_80181914[((Unkstruct_80126B58 *)arg0)->unk0](((Unkstruct_80126B58 *)arg0));
        ((void(*)(Unkstruct_80126B58 *, s32))guess_SetState)(((Unkstruct_80126B58 *)arg0), 0);
        ((void(*)(Unkstruct_80126B58 *))func_80159B70)(((Unkstruct_80126B58 *)arg0));
    } else {
        ((void(*)(Unkstruct_80126B58 *))func_801725E0)(((Unkstruct_80126B58 *)arg0));
    }
}
