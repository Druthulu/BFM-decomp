void func_80186770(s32 param_1)
{
    struct { s32 vx, vy, vz, pad; } vec;
    s32 v;
    s32 d;
    s32 b178arg;
    void *target;

    switch (*(u16 *)(param_1 + 0x34)) {
    case 0:
        v = func_8012B8E4(param_1, 4);
        *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x12) += v;
        if (*(s32 *)(param_1 + 0x1C) == 0xF) {
            func_80142414(param_1, -0x78);
            func_8002D4C8(0x6A9, 0);
        }
        if (func_8012BEE8(param_1) != 0) {
            *(s16 *)(param_1 + 0x2) = 3;
            if ((*(u16 *)(param_1 + 0x86) & 2) != 0) {
                *(s16 *)(param_1 + 0x34) = 1;
                *(s32 *)(param_1 + 0x1C) = 0x28;
                if ((*(u16 *)(param_1 + 0x70) & 0x200) != 0) {
                    func_8012A828(param_1, &D_801E1AFC);
                } else {
                    func_8012A828(param_1, &D_801E11DC);
                }
                *(u16 *)(param_1 + 0xFE) = 0;
            } else {
                *(s16 *)(param_1 + 0x34) = 0;
                func_8012A828(param_1, &D_801E1264);
                *(s32 *)(param_1 + 0x1C) = 0x19;
                *(u16 *)(param_1 + 0x86) |= 2;
            }
        }
        break;
    case 1:
        v = func_8012B8E4(param_1, 6);
        b178arg = D_801D619C;
        {
            u16 *pp;
            register s32 nv __asm__("$6");  // !FAKE: pin $6 — NEEDED DIFFERS (P36 rung B tus8)

            pp = (u16 *)(*(s32 *)(param_1 + 0x20) + 0x12);
            nv = *pp + v;
            *pp = nv;
        }
        func_8012B178(param_1, b178arg);
        d = ((s32 (*)(s32))func_8012CBA4)(param_1);
        if ((d & 0x1000) != 0) {
            func_80131E00(param_1, 0x12);
        } else if (d != 0x2000) {
            func_8012ADE4((u8 *)param_1);
        }
        func_80185F88(param_1);
        v = *(u16 *)(param_1 + 0xFE) - 1;
        *(u16 *)(param_1 + 0xFE) = v;
        if ((v << 16) <= 0) {
            func_80143B6C(param_1, 0);
            *(u16 *)(param_1 + 0xFE) = 8;
        }
        if ((*(u16 *)(param_1 + 0x70) & 0x200) != 0) {
            func_80186C38(param_1, 0x11);
        }
        target = (void *)(param_1 + 0x88);
        vec.vx = *(s16 *)(param_1 + 6) - *(s16 *)(param_1 + 0x88);
        vec.vy = 0;
        vec.vz = *(s16 *)(param_1 + 0xE) - *(s16 *)(param_1 + 0x8C);
        Square0(&vec.vx, &vec.vx);
        if (vec.vx + vec.vz > 0x8FFFF || (d = func_8012BCCC(param_1), d > 0x24000)) {
            *(s16 *)(param_1 + 0x2) = 1;
            *(s16 *)(param_1 + 0x34) = 0;
            *(u16 *)(param_1 + 0x5C) = 0xAA10;
            *(s32 *)(param_1 + 0x1C) = (rand() & 0x1F) + 0x28;
            vec.vx = *(s16 *)(param_1 + 6) - *(s16 *)(param_1 + 0x88);
            vec.vy = 0;
            vec.vz = *(s16 *)(param_1 + 0xE) - *(s16 *)(param_1 + 0x8C);
            Square0(&vec.vx, &vec.vx);
            if (vec.vx + vec.vz > 0x8FFFF) {
                *(u16 *)(param_1 + 0xFC) = func_8012B744((void *)(param_1 + 4), target);
            } else {
                s32 t = rand() & 0x3FF;
                s32 off = t - 0x200;

                if (off < 0) {
                    off = t - 0x500;
                } else {
                    off = t + 0x100;
                }
                *(u16 *)(param_1 + 0xFC) =
                    (*(u16 *)(*(s32 *)(param_1 + 0x20) + 0x12) + off) & 0xFFF;
            }
            func_8012A828(param_1, &D_801E1134);
        }
        if ((*(u16 *)(param_1 + 0x70) & 0x100) == 0) {
            if (func_8012BD3C(param_1, 0x400, 0x1000) != 0) {
                if ((*(u16 *)(param_1 + 0x70) & 0xF00) == 0) {
                    ((void (*)(s32))func_80186B08)(param_1);
                } else {
                    func_80186B34(param_1);
                }
            }
        } else {
            if (func_8012BD3C(param_1, 0x400, 0x40000) != 0) {
                func_80186B7C(param_1);
            }
        }
        break;
    }
}
