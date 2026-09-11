s32 func_801A3594(void *a0) {
    s16 buf[12];
    s16 diff;
    s16 v1;
    s16 t16;
    s16 xr;

    v1 = *(s16 *)((s32)a0 + 0x106);
    switch (v1) {
    case 0: {
        s32 tw;

        diff = *(u16 *)((s32)a0 + 0xE8) - *(u16 *)((s32)a0 + 0x6);
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

        diff = *(u16 *)((s32)a0 + 0xEA) - *(u16 *)((s32)a0 + 0xE);
        buf[1] = diff;
        tw = *(s16 *)((s32)a0 + 0xEE);
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
    return 0;
}
