/* func_8015B950 — shared body (overlay slot 0x80128158, h_text 154619a5). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
s32 func_8015B950(s32 arg0)
{

    extern void (*D_80181160[])(void *);
    s16 sp10[4];
    s16 sp18[4];
    s32 t;
    s32 z;
    s32 doit;
    s32 lim = -0xB0000;

    if (func_80161B18() != 0) {
        return;
    }
    switch (((s32 (*)(s32))func_801619A4)(arg0)) {
    case 0:
    case 1:
    case 2:
    case 6:
        if (((s32 (*)(s32))func_80149AA8)(arg0) != 0) {
            D_80181160[*(u16 *)arg0]((void *)arg0);
            ((void (*)(s32))func_80149AD4)(arg0);
            return;
        }
        if (((s32 (*)(s32))func_80149B54)(arg0) != 0) {
            D_80181160[*(u16 *)arg0]((void *)arg0);
            ((void (*)(s32))func_80149BAC)(arg0);
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
        if (((s32 (*)(s32))func_80149A64)(arg0) != 0) {
            D_80181160[*(u16 *)arg0]((void *)arg0);
            func_800CCCC0(arg0);
            return;
        }
        break;
    }
    if (func_80149CD4(arg0) != 0) {
        D_80181160[*(u16 *)arg0]((void *)arg0);
        ((void (*)(s32))func_8015E880)(arg0);
        return;
    }
    if (((s32 (*)(s32))func_80149744)(arg0) != 0) {
        D_80181160[*(u16 *)arg0]((void *)arg0);
        ((void (*)(s32))func_80149788)(arg0);
        return;
    }
    if (((s32 (*)(s32))func_801496D4)(arg0) != 0) {
        D_80181160[*(u16 *)arg0]((void *)arg0);
        ((void (*)(s32))func_80149704)(arg0);
        if (((u8)((s32 (*)(s32))func_80148AFC)(arg0)) == 0) {
            func_80146D90(arg0);
        }
        if ((*(s32 *)(arg0 + 0x24) | *(s32 *)(arg0 + 0x2C)) != 0) {
            func_80154150(arg0, 0xF);
        } else {
            ((void (*)(s32, s32, s32))func_801541D8)(arg0, 0xD, 6);
        }
        *(s32 *)(arg0 + 0x238) = 1;
        return;
    }
    if (((s32 (*)(s32))func_801488A8)(arg0) != 0) {
        sp10[0] = 0;
        sp10[1] = 0;
        sp10[2] = 0;
        t = *(s16 *)(arg0 + 0x26);
        sp18[0] = t;
        sp18[1] = 0;
        t = *(s16 *)(arg0 + 0x2E);
        sp18[2] = t;
        D_80181160[*(u16 *)arg0]((void *)arg0);
        ((void (*)(s32, s32))func_80147078)(arg0, 1);
        ((void (*)(s32))func_8015A264)(arg0);
        t = -(((s32 (*)(s16 *, s16 *))func_80013294)(sp10, sp18) << 0x10);
        if (t < *(s32 *)(arg0 + 0x2C)) {
            *(s32 *)(arg0 + 0x2C) = t;
        }
        return;
    }
    if (*(u16 *)(arg0 + 0xB8) == 0x8000) {
        D_80181160[*(u16 *)arg0]((void *)arg0);
        ((void (*)(s32, s32))func_80147078)(arg0, 0);
        ((void (*)(s32))func_80159B70)(arg0);
        return;
    }
    z = *(s32 *)(arg0 + 0x2C);
    if (func_8016F1AC() != 0) {
        goto zero;
    }
    if (z <= lim) {
        goto one;
    }
    if (D_8011F9C4 == 0) {
        goto zero;
    }
    if (((u8)func_80029178(0x21)) != 0) {
        goto zero;
    }
one:
    doit = 1;
    goto join;
zero:
    doit = 0;
join:
    if (doit != 0) {
        D_80181160[*(u16 *)arg0]((void *)arg0);
        ((void (*)(s32, s32))func_80147078)(arg0, 0);
        ((void (*)(s32))func_80159B70)(arg0);
        func_80154150(arg0, 9);
        ((void (*)(s32, s32 *))func_80146DB8)(arg0, &D_801810F4);
        ((void (*)(s32, s32))func_80161CD0)(arg0, *(u16 *)(arg0 + 0x16E));
        return;
    }
    if (func_80161208(arg0) == 0) {
        ((void (*)(s32))func_801725A4)(arg0);
    }
}
