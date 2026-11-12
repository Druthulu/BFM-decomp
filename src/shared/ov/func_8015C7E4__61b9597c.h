/* func_8015C7E4 — shared body (overlay slot 0x80128158, h_exact 61b9597c). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_8015C7E4(u16 *param_1)
{

    extern void (*D_80181914[])(void*);
    extern int D_801818B8;
    s32 iVar1;
    u32 uVar2;

    iVar1 = ((s32 (*)(u16 *))func_80161B18)(param_1);
    if ((iVar1 == 0) && (iVar1 = ((s32 (*)(u16 *))func_80161B84)(param_1), iVar1 == 0)) {
        iVar1 = ((s32 (*)(u16 *))guess_IsConfirmPressed)(param_1);
        if (iVar1 != 0) {
            ((void (**)(u16*))D_80181914)[*param_1](param_1);
            ((void (*)(u16 *))guess_EnterJumpState)(param_1);
        } else {
            uVar2 = ((s32 (*)(u16 *))guess_GetPadHeld)(param_1);
            if (((uVar2 & 0x80) == 0) && (iVar1 = ((s32 (*)(u16 *))guess_IsDirectionHeld)(param_1), iVar1 == 0)) {
                ((void (**)(u16*))D_80181914)[*param_1](param_1);
                ((void (*)(u16 *, s32))guess_SetState)(param_1, 0);
                ((void (*)(u16 *))func_80159B70)(param_1);
            } else {
                iVar1 = ((s32 (*)(u16 *))func_80161240)(param_1);
                if (iVar1 == 0) {
                    iVar1 = ((s32 (*)(u16 *))guess_TickWaitTimer_2)(param_1);
                    if (iVar1 != 0) {
                        ((void (*)(u16 *))func_80148AAC)(param_1);
                        ((void (*)(u16 *, void *))guess_SetMoveVector)(param_1, &D_801818B8);
                        ((void (*)(u16 *, s32))guess_SetWaitTimer_2)(param_1, 0x14);
                        ((void (*)(u16 *))guess_NextStep)(param_1);
                    }
                    if ((param_1[0x5c] & 0x2000) != 0) {
                        ((void (*)(u16 *, s32))func_80161C24)(param_1, param_1[0xb7]);
                        ((void (*)(u16 *, s32))guess_SpawnSmallObjectType2)(param_1, 2);
                    }
                }
            }
        }
    }
    return;
}
