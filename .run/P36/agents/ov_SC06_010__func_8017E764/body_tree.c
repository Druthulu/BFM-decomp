void func_8017E764(s32 param_1)
{
    s16 pos[4];
    s16 adv[4];
    s16 mv[4];
    s32 src3[4];
    s32 dst2[4];
    s32 mid[4];
    u16 angle;
    s32 angle2;
    s32 t;
    s32 i;
    s32 j;
    s32 k;
    s32 m;
    s32 self;
    s32 found;
    s32 flag;
    s32 val;
    s32 hundred;
    u16 *row;
    u16 *np;
    s32 *midp;
    u8 *ent;

    i = *(s16 *)&D_80126B66;
    if ((u32)(i - 0x44E) >= 0x32C5U) {
        if (*(s16 *)(param_1 + 0x84) != 0) {
            *(s16 *)(param_1 + 0x84) = 0;
            func_8002D4C8(4, 0x931);
        }
    } else {
        *(s16 *)(param_1 + 0x84) = 1;
        if (i < 0x5CE) {
            func_8002D4C8(0x931, (((i - 0x44E) * 0x7F / 0x180) | 0x1000) & 0xFFFF);
        } else if (i >= 0x3593) {
            func_8002D4C8(0x931, (((i - 0x3592) * 0x7F / 0x180) | 0x1000) & 0xFFFF);
        } else {
            func_8002D4C8(0x931, 0x107F);
        }
    }

    if (*(u16 *)(param_1 + 2) == 0) {
        hundred = 100;
        row = &D_8018A5A2;
        for (i = 0x13F; i >= 0; i--) {
            *row = hundred;
            row += 4;
        }
        *(s32 *)(param_1 + 0xCC) = func_8012C658(0x238, 0xA, param_1);
        *(u16 *)(param_1 + 2) += 1;
        *(u16 *)(param_1 + 0xE) += 0x5F0;
    }

    ent = D_801202A0;
    pos[0] = *(u16 *)(param_1 + 6);
    {
        register u16 *vp __asm__("$3");  // !FAKE: pin $3 — NEEDED DIFFERS (P36 rung B tus7)
        u16 t;
        vp = (u16 *)&D_80126B66;
        t = *(volatile u16 *)vp;
        pos[1] = *(u16 *)(param_1 + 0xA);
        pos[2] = t + 8;
    }
    i = 0;
    np = (u16 *)D_801152A8;
    t = (ratan2(*(s16 *)&D_80126B62 - *(s16 *)(param_1 + 0xA),
                *(s16 *)&D_80126B5E - *(s16 *)(param_1 + 6)) - 0x400) & 0xFFF;
    angle = t;
    adv[0] = pos[0] - (func_8004787C(t) >> 3);
    adv[1] = pos[1] + (func_80047948(t) >> 3);
    adv[2] = pos[2];
    self = *(s32 *)(param_1 + 0xCC);
    angle2 = t;
    *(u16 *)(self + 0x5C) = 0;

    for (; i < 0x60; ent += 0x10C, i++) {
        if (*(u16 *)ent != 0x238) {
            continue;
        }
        flag = *(u16 *)(ent + 0x34);
        if (flag != 1) {
            continue;
        }
        if (func_80135888(*(s32 *)(ent + 0x20), *(s32 *)(ent + 0x58), (s32)pos, (s32)adv) == 0) {
            continue;
        }
        found = 0;
        *(u16 *)(self + 0x5C) = 0x4C08;
        if (*(u8 *)(self + 0x74) != 0) {
            *(s32 *)(param_1 + 0xDC) = flag;
            if (*(s16 *)(ent + 0x70) == 0) {
                mv[0] = D_80126B5E;
                mv[1] = D_80126B62;
                mv[2] = D_80126B66;
                np[0] = -np[0];
                np[1] = -np[1];
                np[2] = -np[2];
                func_8012F568(1, 0x4018, 0, 0x20, (s32)mv, (s32)np);
            }
            j = *(s16 *)&D_80126B66 - *(s16 *)(param_1 + 0xE) + 0x98;
            j = j / 0x130;
            val = (&D_8018A5A0)[j * 0x20];
            if (val == flag) {
                goto Lup;
            }
            if (val < 2) {
                if (val == 0) {
                    *(u16 *)(*(s32 *)(self + 0x20) + 0x14) = angle;
                }
                goto Ldone;
            }
            if (val == 2) {
                goto Ldown;
            }
            goto Ldone;
        Lup:
            *(s16 *)(*(s32 *)(self + 0x20) + 0x14) =
                *(u16 *)(*(s32 *)(self + 0x20) + 0x14) + 0x10;
            found = 1;
            *(u16 *)(*(s32 *)(self + 0x20) + 0x14) &= 0xFFF;
            goto Ldone;
        Ldown:
            *(s16 *)(*(s32 *)(self + 0x20) + 0x14) =
                *(u16 *)(*(s32 *)(self + 0x20) + 0x14) - 0x10;
            found = 1;
            *(u16 *)(*(s32 *)(self + 0x20) + 0x14) &= 0xFFF;
        } else {
            *(u16 *)(*(s32 *)(self + 0x20) + 0x14) = angle;
        }
    Ldone:
        *(s32 *)(self + 4) = *(s32 *)(param_1 + 4)
            - func_8004787C(*(s16 *)(*(s32 *)(self + 0x20) + 0x14)) * 0x1A40;
        *(s32 *)(self + 8) = *(s32 *)(param_1 + 8)
            + func_80047948(*(s16 *)(*(s32 *)(self + 0x20) + 0x14)) * 0x1A40;
        *(s32 *)(self + 0xC) = D_80126B64;
        if (found != 0) {
            src3[0] = *(s32 *)&D_80126B5C;
            src3[1] = D_80126B60;
            src3[2] = *(s32 *)(&D_80126B5C + 8);
            midp = mid;
            func_8012F0BC((s32 *)(*(s32 *)(self + 0x20) + 0x34), src3, midp);
            midp = 0;
            func_8012B2CC(self);
            func_8012F1A4((s32 *)(*(s32 *)(self + 0x20) + 0x34), mid, dst2);
            *(s32 *)&D_80126B5C = dst2[0];
            D_80126B60 = dst2[1];
            *(u16 *)(*(s32 *)(self + 0x20) + 0x14) = angle;
            *(s32 *)(self + 4) = *(s32 *)(param_1 + 4)
                - func_8004787C(*(s16 *)(*(s32 *)(self + 0x20) + 0x14)) * 0x1A40;
            *(s32 *)(self + 8) = *(s32 *)(param_1 + 8)
                + func_80047948(*(s16 *)(*(s32 *)(self + 0x20) + 0x14)) * 0x1A40;
            func_8012B2CC(self);
        }
        if (*(s32 *)(param_1 + 0xDC) != 0) {
            i = *(s16 *)&D_80126B5E - *(s16 *)(param_1 + 6);
            j = *(s16 *)&D_80126B62 - *(s16 *)(param_1 + 0xA);
            if (i * i + j * j > 0x14D10) {
                *(s32 *)&D_80126B5C = *(s32 *)(param_1 + 4) - func_8004787C(angle2) * 0x1240;
                D_80126B60 = *(s32 *)(param_1 + 8) + func_80047948(angle2) * 0x1240;
            }
        }
    }

    if (*(u16 *)(self + 0x5C) == 0) {
        *(s32 *)(param_1 + 0xDC) = 0;
    }
    *(u16 *)(param_1 + 0xFC) = (*(u16 *)(param_1 + 0xFC) + 0x10) & 0xFFF;
    i = *(s16 *)&D_80126B66 - *(s16 *)(param_1 + 0xE);
    j = i / 0x130;
    j -= 2;
    row = &D_8018A59C + j * 0x20;
    for (k = 0; k < 7; k++, j++) {
        if ((u32)j < 0x28) {
            for (m = 0; m < 8; m++) {
                row += 3;
                if (*row == 100) {
                    row -= 3;
                    ent = (u8 *)func_8012C658(0x238, *row, param_1);
                    if (ent == 0) {
                        return;
                    }
                    *(s32 *)(ent + 0xCC) = (s32)row;
                    row += 3;
                }
                *row = j;
                row++;
            }
        } else {
            row += 0x20;
        }
    }
}
