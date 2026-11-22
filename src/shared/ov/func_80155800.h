/* func_80155800 — shared body (overlay slot 0x80128158, h_exact ac3af9dd). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_8001382C(s32 a0, void *a1, void *a2);
extern void guess_SetMoveVector(s32 *a0, s32 *a1);
extern s32 guess_TickWaitTimer_2(s32 a0);
extern void guess_ApplyVelocity(s32 *a0);
extern void guess_SetVelocityFromMoveVector(s32 arg0);
extern u16 guess_GetPadHeld(s32 *a0);
extern u16 guess_GetPadPressed(s32 *a0);
extern s32 guess_IsDirectionHeld(u8 *a0);
extern int func_80148AFC(void *a0);
extern s32 guess_IsConfirmPressed(void *a0);
extern void guess_EnterJumpState(void);
extern void guess_StartSquareAction(s32 *a0);
extern void func_80149B14(s32 *a0);
extern void func_80154134(u8 *a0);
extern void func_801599A4(void *a0);
extern void func_80159B3C(void *a0);
/* $v0 at exit: result of guess_EnterJumpState or result of func_80149B14 or result of func_80155FF8 or result of func_80159B3C or result of func_8015A230 or result of func_80161208 or ori $v0, $v0, 0x3 at ov_MAIN_012:0x80155930; no byte-neutral return: `return 0;` moved `bnez v0,<func_80155800+0x234>` at +0x21C, ov_MAIN_012 objdump */
s32 func_80155800(s32 arg0) {
    extern s32 D_8011F730;
    extern int func_80155A44(int);
    extern s32 func_80155F80(s32 a0);
    extern int func_80155FF8(int, int);
    extern void func_8015A230(s32*);
    extern s32 func_80161208(void *);
    struct { s16 a, b, c, d, e, f, g, h, i, j, k, l; } sp10;
    u8 temp_v0;
    u8 temp_v1;
    s32 var_v1;
    ((Unkstruct_80126B58 *)arg0)->unk44.s |= 2;
    if (((Unkstruct_80126B58 *)arg0)->unkB8.u == 0x8000) {
        ((void(*)(void *))func_801599A4)(((Unkstruct_80126B58 *)arg0));
        ((void(*)(void *))func_80159B3C)(((Unkstruct_80126B58 *)arg0));
        return;
    }
    ((void (*)(void *))func_80155A44)(((Unkstruct_80126B58 *)arg0));
    if (((s32(*)(void *))guess_GetPadPressed)(((Unkstruct_80126B58 *)arg0)) & 0x80) {
        temp_v1 = ((Unkstruct_80126B58 *)arg0)->unk1A9;
        if (temp_v1 >= 4U) {
            if (((Unkstruct_80126B58 *)arg0)->unk1C0 != 0) {
                ((void(*)(void *))func_80148AFC)(((Unkstruct_80126B58 *)arg0));
                ((void (*)(void *))func_80155F80)(((Unkstruct_80126B58 *)arg0));
                ((void(*)(void *))func_80154134)(((Unkstruct_80126B58 *)arg0));
                temp_v0 = ((Unkstruct_80126B58 *)arg0)->unk1AA;
                var_v1 = temp_v0 + 1;
                if (temp_v0 == 0) {
                    var_v1 = 2;
                } else if (var_v1 >= 5U) {
                    var_v1 = 1;
                }
                ((Unkstruct_80126B58 *)arg0)->unk1AA = var_v1;
                ((void(*)(void *))func_80149B14)(((Unkstruct_80126B58 *)arg0));
                return;
            }
            if (((Unkstruct_80126B58 *)arg0)->unk1AA >= 2U) {
                if (((Unkstruct_80126B58 *)arg0)->unk1A8 == 0) {
                    if (temp_v1 != 0) {
                        goto block_13;
                    }
                    goto block_15;
                }
                goto block_22;
            }
block_13:
            ((void(*)(void *))func_80148AFC)(((Unkstruct_80126B58 *)arg0));
            ((void (*)(void *))func_80155F80)(((Unkstruct_80126B58 *)arg0));
            ((void(*)(void *))func_80154134)(((Unkstruct_80126B58 *)arg0));
            ((void(*)(void *))guess_StartSquareAction)(((Unkstruct_80126B58 *)arg0));
            D_8011F730 |= 3;
            return;
        }
    }
block_15:
    if ((((Unkstruct_80126B58 *)arg0)->unk1A8 == 0) && (((Unkstruct_80126B58 *)arg0)->unk1A9 != 0)) {
        if (((s32(*)(void *))guess_IsConfirmPressed)(((Unkstruct_80126B58 *)arg0)) != 0) {
            ((void(*)(void *))func_801599A4)(((Unkstruct_80126B58 *)arg0));
            ((void(*)(void *))guess_EnterJumpState)(((Unkstruct_80126B58 *)arg0));
            return;
        }
        if (!(((s32(*)(void *))guess_GetPadHeld)(((Unkstruct_80126B58 *)arg0)) & 8) && (((s32(*)(void *))guess_IsDirectionHeld)(((Unkstruct_80126B58 *)arg0)) != 0)) {
            ((void(*)(void *))func_801599A4)(((Unkstruct_80126B58 *)arg0));
            ((void (*)(void *))func_8015A230)(((Unkstruct_80126B58 *)arg0));
            return;
        }
        goto block_22;
    }
block_22:
    if (((s32(*)(void *))guess_TickWaitTimer_2)(((Unkstruct_80126B58 *)arg0)) == 0) {
        ((void(*)(s16, void *, void *))func_8001382C)((s16) -(s32) ((Unkstruct_80126B58 *)arg0)->unk20.m->head.unk10.w.unk12.u, &((Unkstruct_80126B58 *)arg0)->unk234, &sp10);
        ((void(*)(void *, void *))guess_SetMoveVector)(((Unkstruct_80126B58 *)arg0), &sp10);
        ((void(*)(void *))guess_SetVelocityFromMoveVector)(((Unkstruct_80126B58 *)arg0));
        ((void(*)(void *))guess_ApplyVelocity)(((Unkstruct_80126B58 *)arg0));
    }
    if (func_80161208(((Unkstruct_80126B58 *)arg0)) == 0) {
        ((void (*)(void *, u8))func_80155FF8)(((Unkstruct_80126B58 *)arg0), ((Unkstruct_80126B58 *)arg0)->unk1AA);
    }
}
