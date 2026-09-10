void func_80186A8C(s32 a0) {

    extern u8 D_800AF630[];
    extern s32 D_801A8C0C[];
    s32 pad[4];   /* idiom 6: 16 bytes of dead locals at sp+0x10 => frame 0x30 */
    u8 *m = D_800AF630;
    s32 ang;
    s32 off;
    s32 base;

    ang = func_8004787C(*(s32 *)(a0 + 0xE4));
    if (*(s16 *)(a0 + 0xAA) == 0) {
        *(s16 *)(*(s32 *)(a0 + 0x20) + 0x18) = (ang >> 2) + 0x1000;
        *(s16 *)(*(s32 *)(a0 + 0x20) + 0x1A) = 0x1000 - (ang >> 1);
        *(s16 *)(*(s32 *)(a0 + 0x20) + 0x1C) = (ang >> 1) + 0x1000;
    } else {
        *(s16 *)(*(s32 *)(a0 + 0x20) + 0x18) = (ang >> 3) + 0x700;
        *(s16 *)(*(s32 *)(a0 + 0x20) + 0x1A) = 0x700 - (ang >> 2);
        *(s16 *)(*(s32 *)(a0 + 0x20) + 0x1C) = (ang >> 2) + 0x700;
    }

    if (*(u16 *)(m + 0xA3AA) % *(s16 *)(a0 + 0xFE) == 0) {
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) =
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) + func_8012B8E4(a0, 0x20);
    }

    switch (*(u16 *)(a0 + 0x34)) {
    case 0: {
        s32 t;
        s32 r;
        if (ang >= 0) {
            t = -(ang << 4);
        } else {
            t = ang << 4;
        }
        {
            register s32 av __asm__("$5");  // !FAKE: pin $5 — NEEDED DIFFERS (P36 rung B tus9)
            av = t - 0x4000;
            func_8012B178(a0, av);
        }
        r = ((s32 (*)(s32))func_8012CBA4)(a0);
        if (r & 0x8000) {
            *(u16 *)(a0 + 0x34) = 2;
            *(s32 *)(a0 + 0xE0) = *(s16 *)(*(s32 *)(a0 + 0x20) + 0x12) + 0x800;
            *(s32 *)(a0 + 0x1C) = rand() % 10 + 0x14;
        } else if ((r & 0x2000) == 0) {
            func_8012ADE4((u8 *)a0);
            *(u16 *)(a0 + 0x34) = 2;
            *(s32 *)(a0 + 0xE0) = *(s16 *)(*(s32 *)(a0 + 0x20) + 0x12) + 0x800;
            *(s32 *)(a0 + 0x1C) = rand() % 10 + 0x14;
        } else if (--*(s32 *)(a0 + 0xE8) == 0) {
            if (rand() & 1) {
                s32 v;
                *(u16 *)(a0 + 0x34) = 1;
                *(s32 *)(a0 + 0x1C) = 0x20;
                off = rand() % 1024;
                base = *(s16 *)(*(s32 *)(a0 + 0x20) + 0x12);
                if ((rand() & 1) == 0) {
                    v = base - off;
                } else {
                    v = base + off;
                }
                *(s32 *)(a0 + 0xE0) = v;
            } else {
                *(s32 *)(a0 + 0xE8) = 0x40;
            }
        }
        break;
    }
    case 1: {
        s32 t;
        s32 d = func_8012B608(*(s16 *)(*(s32 *)(a0 + 0x20) + 0x12),
                              *(s32 *)(a0 + 0xE0), 0x14);
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) =
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) + d;
        if (ang >= 0) {
            t = -(ang << 4);
        } else {
            t = ang << 4;
        }
        {
            register s32 av __asm__("$5");  // !FAKE: pin $5 — NEEDED DIFFERS (P36 rung B tus9)
            av = t - 0x4000;
            func_8012B178(a0, av);
        }
        if ((((s32 (*)(s32))func_8012CBA4)(a0) & 0x2000) == 0) {
            func_8012ADE4((u8 *)a0);
            *(u16 *)(a0 + 0x34) = 2;
            *(s32 *)(a0 + 0xE0) = *(s16 *)(*(s32 *)(a0 + 0x20) + 0x12) + 0x800;
            *(s32 *)(a0 + 0x1C) = rand() % 10 + 0x14;
        } else if (func_8012BEE8(a0) != 0) {
            *(u16 *)(a0 + 0x34) = 0;
            *(s32 *)(a0 + 0xE8) = 0x40;
        }
        break;
    }
    case 2: {
        s32 d = func_8012B608(*(s16 *)(*(s32 *)(a0 + 0x20) + 0x12),
                              *(s32 *)(a0 + 0xE0), 0x14);
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) =
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) + d;
        if (func_8012BEE8(a0) != 0) {
            *(u16 *)(a0 + 0x34) = 0;
            func_8012B030((u8 *)a0);
        }
        break;
    }
    }

    func_801877EC(a0);
    func_8018771C(a0, D_801A8C0C[*(u16 *)(a0 + 0x70) & 0xF]);
    *(s32 *)(a0 + 0xE4) = (*(s32 *)(a0 + 0xE4) + 0x40) & 0x7FF;
    if (*(s32 *)(a0 + 0x14) > 0x100000) {
        *(s32 *)(a0 + 0x14) = 0x100000;
    }
}
