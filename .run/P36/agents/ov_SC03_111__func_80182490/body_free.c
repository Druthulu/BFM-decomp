void func_80182490(s32 a0)
{
    u16 out[4];      /* sp+0x10 */
    s16 sv[4];       /* sp+0x18 */
    s16 pos[4];      /* sp+0x20 */
    s32 flag;        /* sp+0x28 */
    s16 *p;

    if (*(s16 *)(*(s32 *)(a0 + 0x64) + 0x36) != *(s16 *)(a0 + 0xFE)) {
        ((void (*)(void))func_8012C218)();
        return;
    }

    if (*(s16 *)(a0 + 0x70) == 1 || *(s16 *)(a0 + 0x70) == 8) {
        s32 ang;
        s32 t;
        ang = (*(u16 *)(a0 + 0xFC) + 0x40) & 0xFFF;
        p = *(s16 **)(a0 + 0xCC);
        *(s16 *)(a0 + 0xFC) = ang;
        t = (func_8004787C(ang) >> 6) + 0xBF;
        p[2] = t;
        p[1] = t;
        p[0] = t;
    }

    if (*(s32 *)(*(s32 *)(*(s32 *)(a0 + 0x64) + 0x20) + 4) < 0) {
        { s32 *q; q = *(s32 **)(a0 + 0x20);  // !FAKE: pin $3 — NEEDED DIFFERS (P36 rung B tus8)
          q[1] = q[1] | 0x80000000; }
    } else {
        *(s32 *)(*(s32 *)(a0 + 0x20) + 4) =
            *(s32 *)(*(s32 *)(a0 + 0x20) + 4) & 0x7FFFFFFF;
    }

    *(u16 *)(*(s32 *)(a0 + 0x20) + 0x18) =
        *(u16 *)(*(s32 *)(*(s32 *)(a0 + 0x64) + 0x20) + 0x18);

    if (*(s16 *)(*(s32 *)(a0 + 0x64) + 0x70) < 8) {
        *(s16 *)(a0 + 0x108) = (*(u16 *)(a0 + 0x108) + 0x40) & 0xFFF;
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) =
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) & 0xFFF;
        *(u16 *)(*(s32 *)(*(s32 *)(a0 + 0x64) + 0x20) + 0x12) =
            *(u16 *)(*(s32 *)(*(s32 *)(a0 + 0x64) + 0x20) + 0x12) & 0xFFF;

        flag = *(s16 *)(*(s32 *)(*(s32 *)(a0 + 0x64) + 0x20) + 0x12) -
               *(s16 *)(*(s32 *)(a0 + 0x20) + 0x12);
        if (flag > 0x800) {
            flag = flag - 0x1000;
        }
        if (flag < -0x800) {
            flag = flag + 0x1000;
        }
        if (flag > 0x200) {
            s32 t = *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) - 0x200;
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) = t + flag;
        } else if (flag < -0x200) {
            s32 t = *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) + 0x200;
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) = t + flag;
        } else {
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) =
                *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) + (flag / 16);
        }

        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) =
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) +
            (func_8004787C(*(s16 *)(a0 + 0x108)) >> 6);

        func_80049CAC(*(s32 *)(a0 + 0x20) + 0x10, *(s32 *)(a0 + 0x20) + 0x34);
        gte_SetRotMatrix((s32 *)(*(s32 *)(a0 + 0x20) + 0x34));
        gte_SetTransMatrix((s32 *)(*(s32 *)(*(s32 *)(a0 + 0x64) + 0x20) + 0x34));

        p = *(s16 **)(a0 + 0xD0);
        sv[0] = 0;
        sv[1] = 0;
        sv[2] = (p[2] * *(s16 *)(*(s32 *)(a0 + 0x20) + 0x18)) >> 12;
        RotTransSV(sv, out, &flag);

        *(s16 *)(a0 + 6) = out[0];
        *(s16 *)(a0 + 0xA) = out[1];
        *(s16 *)(a0 + 0xE) = out[2];
        out[1] = out[1] - 0x40;

        pos[0] = *(u16 *)(a0 + 6);
        pos[1] = *(u16 *)(a0 + 0xA) + 0x10;
        pos[2] = *(u16 *)(a0 + 0xE);
        flag = func_8012CEB0((s32)out, (s32)pos, 1);
        if (flag & 0x1000) {
            return;
        }
        if (flag != 0) {
            s32 d;
            s32 t = pos[1] - 0x10;
            d = *(s16 *)(a0 + 0xA) - t;
            if (d < 5) {
                return;
            }
            if (d > 0x40) {
                d = 0x40;
            }
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x10) =
                *(u16 *)(*(s32 *)(a0 + 0x20) + 0x10) + (d << 4);

            func_80049CAC(*(s32 *)(a0 + 0x20) + 0x10, *(s32 *)(a0 + 0x20) + 0x34);
            gte_SetRotMatrix((s32 *)(*(s32 *)(a0 + 0x20) + 0x34));
            gte_SetTransMatrix((s32 *)(*(s32 *)(*(s32 *)(a0 + 0x64) + 0x20) + 0x34));

            p = *(s16 **)(a0 + 0xD0);
            sv[0] = 0;
            sv[1] = 0;
            sv[2] = (p[2] * *(s16 *)(*(s32 *)(a0 + 0x20) + 0x18)) >> 12;
            RotTransSV(sv, out, &flag);

            *(s16 *)(a0 + 6) = out[0];
            *(s16 *)(a0 + 0xA) = out[1];
            *(s16 *)(a0 + 0xE) = out[2];
        } else {
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x10) =
                *(u16 *)(*(s32 *)(a0 + 0x20) + 0x10) - 0x80;
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x10) =
                *(u16 *)(*(s32 *)(a0 + 0x20) + 0x10) & 0xFFF;
            if ((u32)(*(u16 *)(*(s32 *)(a0 + 0x20) + 0x10) - 0x801) < 0x3FF) {
                *(s16 *)(*(s32 *)(a0 + 0x20) + 0x10) = 0xC00;
            }
        }
    } else {
        s32 ang;
        s32 ang2;

        ang = (*(u16 *)(a0 + 0x102) + *(u16 *)(a0 + 0x106)) & 0xFFF;
        *(s16 *)(a0 + 0x102) = ang;
        *(s16 *)(*(s32 *)(a0 + 0x20) + 0x10) = func_80047948(ang) >> 6;

        ang2 = (*(u16 *)(a0 + 0x104) + *(u16 *)(a0 + 0x100)) & 0xFFF;
        *(s16 *)(a0 + 0x104) = ang2;
        *(s16 *)(*(s32 *)(a0 + 0x20) + 0x14) = func_80047948(ang2) >> 6;

        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x10) =
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x10) + 0xC00;

        func_80049CAC(*(s32 *)(a0 + 0x20) + 0x10, *(s32 *)(a0 + 0x20) + 0x34);
        gte_SetRotMatrix((s32 *)(*(s32 *)(a0 + 0x20) + 0x34));
        gte_SetTransMatrix((s32 *)(*(s32 *)(*(s32 *)(a0 + 0x64) + 0x20) + 0x34));

        p = *(s16 **)(a0 + 0xD0);
        sv[0] = 0;
        sv[1] = 0;
        sv[2] = (p[2] * *(s16 *)(*(s32 *)(a0 + 0x20) + 0x18)) >> 12;
        RotTransSV(sv, out, &flag);

        *(s16 *)(a0 + 6) = out[0];
        *(s16 *)(a0 + 0xA) = out[1];
        *(s16 *)(a0 + 0xE) = out[2];
    }
    { s32 pad[2]; }   /* LEVER 1: frame pad. INNER-BLOCK + LAST is load-bearing --
                         a function-scope decl takes 0x28 and evicts flag to 0x30 */
}
