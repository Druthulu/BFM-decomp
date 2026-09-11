s32 func_801A3594(void *a0) {
    s16 buf[12];
    u16 b;
    u16 a;
    s16 diff;
    s16 v1;
    s32 tw;
    s16 t16;
    s16 xr;

    v1 = *(s16 *)((s32)a0 + 0x106);
    switch (v1) {
    case 0:
        a = *(u16 *)((s32)a0 + 0xE8);
        b = *(u16 *)((s32)a0 + 0x6);
        diff = a - b;
        buf[0] = diff;
        tw = *(s16 *)((s32)a0 + 0xEC);
        break;
    case 1:
        a = *(u16 *)((s32)a0 + 0xEA);
        b = *(u16 *)((s32)a0 + 0xE);
        diff = a - b;
        buf[1] = diff;
        tw = *(s16 *)((s32)a0 + 0xEE);
        break;
    default:
        goto default_case;
    }

    if (tw == 0) goto ret1;
    t16 = tw;
    if (diff == 0) goto ret1;
    xr = diff ^ t16;
    if (xr >= 0) goto default_case;
ret1:
    return 1;
default_case:
    return 0;
}
