s32 func_801836D4(void *a0, void *a1) {
    s16 buf[16];                        /* dead-store scratch: forces frame 0x28 */
    s16 diff;
    s16 v1;
    s16 t16;
    s16 xr;

    if (*(s16 *)((s32)a0 + 0xEA) != 0) {
        *(s16 *)((s32)a0 + 0xEA) = *(s16 *)((s32)a0 + 0xEA) - 1;
    }

    v1 = *(s16 *)((s32)a0 + 0xE2);
    switch (v1) {
    case 0: {
        s32 tw;

        diff = *(u16 *)((s32)a0 + 0xE4) - *(u16 *)((s32)a1 + 0x6);
        buf[0] = diff;
        tw = *(s16 *)((s32)a0 + 0xEC);
        t16 = tw;
        if (tw == 0) {
            return 1;
        }
        break;
    }
    case 1: {
        s32 tw;

        diff = *(u16 *)((s32)a0 + 0xE6) - *(u16 *)((s32)a1 + 0xA);
        buf[1] = diff;
        tw = *(s16 *)((s32)a0 + 0xEE);
        t16 = tw;
        if (tw == 0) {
            return 1;
        }
        break;
    }
    case 2: {
        s32 tw;

        diff = *(u16 *)((s32)a0 + 0xE8) - *(u16 *)((s32)a1 + 0xE);
        buf[2] = diff;
        tw = *(s16 *)((s32)a0 + 0xF0);
        t16 = tw;
        if (tw == 0) {
            return 1;
        }
        break;
    }
    default:
        goto default_case;
    }

    if (diff == 0) goto ret1;
    xr = diff ^ t16;
    if (xr >= 0) goto default_case;
ret1:
    return 1;

default_case:
    return *(s16 *)((s32)a0 + 0xEA) == 0;
}
