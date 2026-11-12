/* func_8015A3C8 — shared body (overlay slot 0x80128158, h_exact a4d009b4). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
s32 func_8015A3C8(arg0)
s32 arg0;
{

    extern void (*D_80181914[])(void *);
    extern u16 guess_g_FrameCounter;
    extern s32 D_800D5428;
    extern u8 D_80181898;
    s32 min;
    s32 grav;
    s32 hi;
    s32 t;
    s32 lo1;
    s32 lo2;
    s32 sv;
    u8 *p;

    p = guess_g_PlayerRecord;
    if (currentLocationId == 0x302A) {
        min = -0xC0000;
        grav = -0x4000;
        hi = 0;
    } else {
        min = -0xB0000;
        grav = -0x1000;
        hi = 0;
    }

    if (func_80149D9C(arg0) != 0) {
        D_80181914[*(u16 *)arg0]((void *)arg0);
        ((void (*)(s32))func_80149FA8)(arg0);
        return;
    }
    ((void (*)(s32))func_80149FB0)(arg0);
    if (((s32 (*)(s32))func_80161B84)(arg0) != 0) {
        return;
    }
    if (((s32 (*)(s32))func_80161B18)(arg0) != 0) {
        return;
    }
    if (*(s32 *)(arg0 + 0xB4) == (s32)&D_800D5428) {
        if (func_8014A048(arg0) != 0) {
            D_80181914[*(u16 *)arg0]((void *)arg0);
            ((void (*)(s32))func_8014A218)(arg0);
            return;
        }
    }
    if (((s32 (*)(s32))func_80161BE0)(arg0) != 0) {
        return;
    }
    switch (((s32 (*)(s32))func_801619A4)(arg0)) {
    case 0:
    case 1:
    case 2:
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
        break;
    }

    if (guess_IsR1Held(arg0) != 0) {
        D_80181914[*(u16 *)arg0]((void *)arg0);
        ((void (*)(s32))guess_EnterState11)(arg0);
        return;
    }
    if (((s32 (*)(s32))guess_IsConfirmPressed)(arg0) != 0) {
        D_80181914[*(u16 *)arg0]((void *)arg0);
        ((void (*)(s32))guess_EnterJumpState)(arg0);
        return;
    }
    if (((s32 (*)(s32))guess_IsDirectionHeld)(arg0) == 0) {
        sv = *(s32 *)(arg0 + 0x2C);
        D_80181914[*(u16 *)arg0]((void *)arg0);
        guess_SpawnSmallObjectType2(arg0, 1);
        ((void (*)(s32, s32))guess_SetState)(arg0, 0);
        ((void (*)(s32))func_80159B70)(arg0);
        if (func_8015ABD4(arg0, sv, min) != 0) {
            func_8015AC48(arg0);
        }
        return;
    }

    ((void (*)(s32))func_80148AFC)(arg0);
    if (*(u32 *)(arg0 + 0x44) & 0x200) {
        if (*(s32 *)(arg0 + 0x23C) == 0) {
            guess_SetAnim(arg0, 0xA);
            guess_SetTexAnim(arg0, 0x1C);
        }
        ((void (*)(s32, s32))guess_SetMoveVector)(arg0, (s32)&(*(s32 *)&D_80181898));
        guess_AddMoveVectorThenSetVelocity(arg0, 0, 0, 0);
    } else {
        switch (*(u8 *)(arg0 + 0xA9)) {
        case 0x41:
            guess_AddMoveVectorThenSetVelocity(arg0, 0, 0, grav);
            if (*(s32 *)(arg0 + 0x23C) == 0) {
                if (((s32 (*)(s32))guess_GetPadHeld)(arg0) & 4) {
                    if (*(s32 *)(arg0 + 0x2C) < -0x40000) {
                        *(s32 *)(arg0 + 0x2C) = -0x40000;
                    }
                } else if (func_8016F1C4() == 0) {
                    if ((*(s16 *)(p + 0x26) < 0x20) || (*(s16 *)(p + 0x2E) < 0x20)) {
                        if (*(s32 *)(arg0 + 0x2C) < -0x40000) {
                            *(s32 *)(arg0 + 0x2C) = -0x40000;
                        }
                    } else if ((*(s16 *)(p + 0x26) < 0x40) || (*(s16 *)(p + 0x2E) < 0x30)) {
                        if (*(s32 *)(arg0 + 0x2C) < -0x80000) {
                            *(s32 *)(arg0 + 0x2C) = -0x80000;
                        }
                    }
                }
                if (*(s32 *)(arg0 + 0x2C) < min) {
                    *(s32 *)(arg0 + 0x2C) = min;
                }
                if (*(s32 *)(arg0 + 0x2C) >= hi) {
                    *(s32 *)(arg0 + 0x2C) = hi;
                }
                lo1 = -0x94000;
                t = *(s32 *)(arg0 + 0x2C);
                if (t < lo1) {
                    guess_SetAnim(arg0, 8);
                } else if (t < -0x70000) {
                    ((void (*)(s32, s32, s32))guess_SetAnimFromIndex)(arg0, 7, func_8015AB7C(arg0) & 0xFFFF);
                } else {
                    guess_SetAnim(arg0, 6);
                }
            }
            break;
        case 0x53:
        case 0x73:
            *(s32 *)(arg0 + 0x2C) = (min * (((s32 (*)(s32))func_80148824)(arg0) & 0xFF)) / 127;
            if (func_8016F1C4() == 0) {
                if ((*(s16 *)(p + 0x26) < 0x40) || (*(s16 *)(p + 0x2E) < 0x30)) {
                    if (*(s32 *)(arg0 + 0x2C) < -0x80000) {
                        *(s32 *)(arg0 + 0x2C) = -0x80000;
                    }
                }
                if ((*(s16 *)(p + 0x26) < 0x20) || (*(s16 *)(p + 0x2E) < 0x20)) {
                    if (*(s32 *)(arg0 + 0x2C) < -0x40000) {
                        *(s32 *)(arg0 + 0x2C) = -0x40000;
                    }
                }
            }
            if (*(s32 *)(arg0 + 0x2C) < min) {
                *(s32 *)(arg0 + 0x2C) = min;
            }
            if (*(s32 *)(arg0 + 0x2C) >= hi) {
                *(s32 *)(arg0 + 0x2C) = hi;
            }
            guess_SetVelocityFromMoveVector(arg0);
            if (*(s32 *)(arg0 + 0x23C) == 0) {
                lo2 = -0x94000;
                t = *(s32 *)(arg0 + 0x2C);
                if (t < lo2) {
                    guess_SetAnim(arg0, 8);
                } else if (t < -0x70000) {
                    ((void (*)(s32, s32, s32))guess_SetAnimFromIndex)(arg0, 7, func_8015AB7C(arg0) & 0xFFFF);
                } else {
                    guess_SetAnim(arg0, 6);
                }
            }
            break;
        }
    }

    ((void (*)(s32))guess_ApplyVelocity)(arg0);
    if ((min >= *(s32 *)(arg0 + 0x2C)) && !(guess_g_FrameCounter & 7)) {
        guess_SpawnSmallObjectType2(arg0, 2);
    }
    if (((s32 (*)(s32))func_8014D738)(arg0) != 0) {
        D_80181914[*(u16 *)arg0]((void *)arg0);
        ((void (*)(s32))guess_EnterState9)(arg0);
        return;
    }
    if (((s32 (*)(s32))func_8014E934)(arg0) != 0) {
        ((void (*)(s32))func_80155440)(arg0);
        guess_SetAnim(arg0, 0x12);
        guess_SetTexAnim(arg0, 0x17);
        *(s32 *)(arg0 + 0x23C) = 1;
    } else {
        if (*(s32 *)(arg0 + 0x23C) != 0) {
            func_801553C0(arg0);
            guess_SetAnim(arg0, 6);
            guess_SetTexAnim(arg0, 0x21);
        }
        *(s32 *)(arg0 + 0x23C) = 0;
    }
    if (((s32 (*)(s32))func_80161278)(arg0) == 0) {
        if (*(u16 *)(arg0 + 0xB8) & 0x2000) {
            func_80161C24(arg0, *(u16 *)(arg0 + 0x16E));
        }
        ((void (*)(s32))func_80172608)(arg0);
        ((void (*)(s32))guess_SaveGroundedPos)(arg0);
    }
}
