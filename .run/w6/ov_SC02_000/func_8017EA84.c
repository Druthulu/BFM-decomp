// @class: struct
// @stuck: none — big state machine (5-state switch), modeled on the exact call/loop/field idioms
//   already byte-proven in this same TU (func_8017E404 / func_8017E51C / func_8017E958).

extern s32 func_8012B608(s32 a0, s32 a1, s32 a2);
extern s32 func_8017E958(s32 a0, s32 a1);
extern void func_8012B178(s32 a0, s32 a1);
extern void func_8012B14C(s32 a0, s32 a1);
extern void func_8012CBA4(s32 a0);
extern s32 func_8012AE00(s32 a0);
extern s32 func_8012BCCC(s32 a0);
extern void func_8012A828(s32 a0, void *a1);
extern s32 func_8012BEE8(s32 a0);
extern s32 func_8012B8E4(s32 arg0, s32 arg1);
extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_80142414(s32 a0, s16 a1);
extern s32 func_80143B6C(s32 a0, s32 a1);
extern void func_8012B2CC(s32 a0);
extern void func_8012B23C(s32 a0);
extern s32 func_8012BD3C(s32 a0, s32 a1, s32 a2);
extern void func_8017F5A0(s32 a0);
extern void func_8017F5E4(s32 a0);
extern void func_801803B0(void);
extern void func_8017E6D8(s32 a0);
extern void func_8017E5AC(s32 a0);
extern s32 func_8017E404(s32 a0, s32 a1);
extern s32 ratan2(s32, s32);
extern s32 rand(void);

extern u8 D_801202A0[];
extern char D_8018E68C[];
extern char D_8018E698[];
extern char D_8018E680[];
extern char D_801A65BC[];
extern char D_801A6534[];
extern char D_801A648C[];
extern s32 D_801E8008;
extern s32 D_801270D4;
extern u16 D_80126B5E;
extern s16 D_8018E6E4;
extern s16 D_8018E6E8;

void func_8017EA84(s32 a0)
{
    s32 v0;
    s32 state;

    v0 = *(u16 *)(a0 + 0xE0);
    state = *(u16 *)(a0 + 0x34);
    *(u16 *)(a0 + 0xE0) = v0 + 1;

    switch (state) {
    case 0:
    {
        s32 v0;

        if (func_8017E958(a0, 0) != 0) {
            func_8017E6D8(a0);
            return;
        }

        if (*(s16 *)(a0 + 0xE0) < 9) {
            register s32 ptr20 __asm__("$2") = *(s32 *)(a0 + 0x20);
            s32 arg1 = *(s16 *)(a0 + 0xE2);
            s32 r;
            r = func_8012B608(*(s16 *)(ptr20 + 0x12), arg1, 6);
            {
                s32 ptr20b = *(s32 *)(a0 + 0x20);
                *(u16 *)(ptr20b + 0x12) = *(u16 *)(ptr20b + 0x12) + r;
            }
        } else {
            char *snd = D_8018E68C;
            if (*(u16 *)(a0 + 0xFE) & 2) {
                snd = D_8018E698;
            }
            func_8012B14C(a0, (s32) snd);
        }

        v0 = ((s32(*)(s32)) func_8012CBA4)(a0);
        D_801E8008 = v0;
        {
            s32 flag;
            if (v0 == 0 || (v0 & 0x4000) != 0) {
                *(s32 *)(a0 + 4) = *(s32 *)(a0 + 0x38);
                *(s32 *)(a0 + 8) = *(s32 *)(a0 + 0x3C);
                *(s32 *)(a0 + 0xC) = *(s32 *)(a0 + 0x40);
                flag = 1;
            } else {
                flag = 0;
            }

            if (flag != 0) {
                func_8017E5AC(a0);
                return;
            }
        }

        {
            s32 p, end, v;
            p = (s32) D_801202A0;
            end = (s32) D_801202A0 + 0x6480;
            v = *(u16 *)a0;
            for (; p != end; p += 0x10C) {
                if (p != a0) {
                    if (*(u16 *)p == v) {
                        if (func_8017E404(a0, p) != 0) {
                            break;
                        }
                    }
                }
            }
            ((void(*)(s32)) func_8012AE00)(p);
        }

        if (*(s16 *)(a0 + 0xE0) >= 0x3C) {
            *(u16 *)(a0 + 0xE0) = 0;
            if (*(u16 *)(a0 + 0xFE) & 2) {
                *(u16 *)(a0 + 0xE2) = 0;
            } else {
                s32 v1;
                v0 = rand();
                v1 = *(s32 *)(a0 + 0x20);
                v1 = *(u16 *)(v1 + 0x12);
                v0 = v0 & 0x800;
                v1 = v1 + v0;
                v1 = v1 - 0x400;
                *(u16 *)(a0 + 0xE2) = v1;
            }
        }

        v0 = *(u16 *)(a0 + 0xE4) - 1;
        *(u16 *)(a0 + 0xE4) = v0;
        if ((s16) v0 > 0) {
            return;
        }
        if (*(u16 *)(a0 + 0xFE) & 2) {
            return;
        }

        v0 = func_8012BCCC(a0);
        if (v0 > 0x10000) {
            return;
        }

        if ((s32)((u32)*(u16 *)(a0 + 0x70) << 0x10) >> 0x18 == 4) {
            if (D_801270D4 != 0) {
                return;
            }
        }

        if ((*(u16 *)(a0 + 0xFE) & 1) == 0) {
            func_8012A828(a0, &D_801A65BC);
            *(u16 *)(a0 + 2) = 1;
            *(u16 *)(a0 + 0x34) = 1;
            *(s32 *)(a0 + 0x1C) = 0x19;
            *(u16 *)(a0 + 0xFE) = *(u16 *)(a0 + 0xFE) | 1;
            return;
        }

        *(u16 *)(a0 + 0x5C) = 0xAA10;
        *(u16 *)(a0 + 2) = 1;
        *(u16 *)(a0 + 0x34) = 2;
        *(u16 *)(a0 + 0x5E) = 0;
        *(s32 *)(a0 + 0x1C) = 0x1E;
        func_8012A828(a0, &D_801A6534);
        *(u16 *)(a0 + 0xFC) = 0;
        return;
    }

    case 1:
    {
        s32 v0;
        s32 ptr20;

        v0 = func_8012B8E4(a0, 4);
        ptr20 = *(s32 *)(a0 + 0x20);
        *(u16 *)(ptr20 + 0x12) = *(u16 *)(ptr20 + 0x12) + v0;

        if (*(s32 *)(a0 + 0x1C) == 0xF) {
            func_8002D4C8(0x6A9, 0);
            func_80142414(a0, -0x78);
        }

        if (func_8012BEE8(a0) == 0) {
            return;
        }

        *(u16 *)(a0 + 0x5C) = 0xAA10;
        *(u16 *)(a0 + 2) = 1;
        *(u16 *)(a0 + 0x34) = 2;
        *(u16 *)(a0 + 0xE0) = 0;
        *(u16 *)(a0 + 0x5E) = 0;
        *(s32 *)(a0 + 0x1C) = 0x1E;
        func_8012A828(a0, &D_801A6534);
        *(u16 *)(a0 + 0xFC) = 0;
        return;
    }

    case 2:
    {
        s32 v0;

        if (func_8017E958(a0, 1) != 0) {
            func_8017E6D8(a0);
            return;
        }

        {
            s32 v0 = ((s32(*)(s32)) func_8012CBA4)(a0);
            s32 flag;
            D_801E8008 = v0;
            if (v0 == 0 || (v0 & 0x4000) != 0) {
                *(s32 *)(a0 + 4) = *(s32 *)(a0 + 0x38);
                *(s32 *)(a0 + 8) = *(s32 *)(a0 + 0x3C);
                *(s32 *)(a0 + 0xC) = *(s32 *)(a0 + 0x40);
                flag = 1;
            } else {
                flag = 0;
            }

            if (flag != 0) {
                func_8017E5AC(a0);
                return;
            }
        }

        {
            s32 p, end, v;
            p = (s32) D_801202A0;
            end = (s32) D_801202A0 + 0x6480;
            v = *(u16 *)a0;
            for (; p != end; p += 0x10C) {
                if (p != a0) {
                    if (*(u16 *)p == v) {
                        if (func_8017E404(a0, p) != 0) {
                            break;
                        }
                    }
                }
            }
            ((void(*)(s32)) func_8012AE00)(p);
        }

        if ((s32)((u32)*(u16 *)(a0 + 0x70) << 0x10) >> 0x18 == 4 &&
            *(s16 *)&D_80126B5E >= 0x220) {
            s32 ang;
            register s32 v1 __asm__("$3");
            s32 arg1;
            ang = ratan2((s32)*(s16 *)(a0 + 0xE) - (s32)D_8018E6E8,
                         (s32)D_8018E6E4 - (s32)*(s16 *)(a0 + 6));
            arg1 = (ang - 0x400) & 0xFFF;
            v1 = *(s32 *)(a0 + 0x20);
            v0 = func_8012B608(*(s16 *)(v1 + 0x12), arg1, 6);
            {
                s32 v1b = *(s32 *)(a0 + 0x20);
                *(u16 *)(v1b + 0x12) = *(u16 *)(v1b + 0x12) + v0;
            }
        } else if (*(s32 *)(a0 + 0x1C) >= 0x16) {
            s32 t;
            v0 = func_8012B8E4(a0, 6);
            t = *(s32 *)(a0 + 0x20);
            *(u16 *)(t + 0x12) = *(u16 *)(t + 0x12) + v0;
        }

        func_8012B14C(a0, (s32) D_8018E680);

        {
            s32 fc;
            fc = *(u16 *)(a0 + 0xFC) - 1;
            *(u16 *)(a0 + 0xFC) = fc;
            if ((s16) fc <= 0) {
                func_80143B6C(a0, 0);
                *(u16 *)(a0 + 0xFC) = 8;
            }
        }

        if (*(s16 *)(a0 + 0xE0) >= 0x5A) {
            s32 sub;
            s32 v1;
            *(u16 *)(a0 + 0xE0) = 0;
            *(u8 *)(a0 + 0xC1) = 0;
            *(u16 *)(a0 + 2) = 1;
            *(u16 *)(a0 + 0x34) = 0;
            v0 = rand();
            v1 = *(s32 *)(a0 + 0x20);
            v0 = (v0 & 0x1F) + 0x46;
            *(s32 *)(a0 + 0x1C) = v0;
            v0 = *(u16 *)(a0 + 0x70);
            *(u16 *)(a0 + 0xE0) = 0;
            v1 = *(u16 *)(v1 + 0x12);
            *(u16 *)(a0 + 0xE2) = v1;
            sub = (s32)((u32)v0 << 0x10) >> 0x18;
            switch (sub) {
            case 0:
            case 1:
            case 2:
            case 3:
            case 7:
                if (*(u16 *)(a0 + 0xFE) & 2) {
                    *(u16 *)(a0 + 0xE2) = 0;
                }
                break;
            case 4:
            case 6:
                goto shared_4_6_a;
            case 5:
                ((void(*)(s32)) func_801803B0)(a0);
                goto after_aa10_a;
            }
            shared_4_6_a:
            *(u16 *)(a0 + 0xE4) = 0x1E;
            *(u16 *)(a0 + 0x5E) = 0;
            *(u16 *)(a0 + 0x5C) = 0xAA10;
            func_8012B2CC(a0);
            func_8012B23C(a0);
            func_8012B14C(a0, (s32) D_8018E68C);
            func_8012A828(a0, &D_801A648C);
            after_aa10_a:;
        }

        if (func_8012BEE8(a0) != 0) {
            *(u16 *)(a0 + 0x5C) = 0xAA10;
            *(u16 *)(a0 + 2) = 1;
            *(u16 *)(a0 + 0x34) = 2;
            *(u16 *)(a0 + 0x5E) = 0;
            *(s32 *)(a0 + 0x1C) = 0x1E;
            func_8012A828(a0, &D_801A6534);
            *(u16 *)(a0 + 0xFC) = 0;
            return;
        }

        {
            s32 flag = 0x400;
            if (((s32)((u32)*(u16 *)(a0 + 0x70) << 0x10) >> 0x18) == 1) {
                flag = 0x200;
                if (func_8012BD3C(a0, flag, 0x3100) == 0) {
                    return;
                }
                func_8017F5E4(a0);
                return;
            }
            if (func_8012BD3C(a0, flag, 0x1000) == 0) {
                return;
            }
            func_8017F5A0(a0);
            return;
        }
    }

    case 3:
    {
        s32 v0;
        s32 v1;

        {
            register s32 ptr20 __asm__("$2") = *(s32 *)(a0 + 0x20);
            s32 arg1 = *(s16 *)(a0 + 0xE2);
            v0 = func_8012B608(*(s16 *)(ptr20 + 0x12), arg1, 4);
        }
        {
            s32 ptr20b = *(s32 *)(a0 + 0x20);
            *(u16 *)(ptr20b + 0x12) = *(u16 *)(ptr20b + 0x12) + v0;
        }

        if (func_8012BEE8(a0) == 0) {
            return;
        }

        *(u8 *)(a0 + 0xC1) = 0;
        *(u16 *)(a0 + 2) = 1;
        *(u16 *)(a0 + 0x34) = 0;
        v0 = rand();
        v1 = *(s32 *)(a0 + 0x20);
        v0 = (v0 & 0x1F) + 0x46;
        *(s32 *)(a0 + 0x1C) = v0;
        v0 = *(u16 *)(a0 + 0x70);
        *(u16 *)(a0 + 0xE0) = 0;
        v1 = *(u16 *)(v1 + 0x12);
        *(u16 *)(a0 + 0xE2) = v1;
        {
            s32 sub = (s32)((u32)v0 << 0x10) >> 0x18;
            switch (sub) {
            case 0:
            case 1:
            case 2:
            case 3:
            case 7:
                if (*(u16 *)(a0 + 0xFE) & 2) {
                    *(u16 *)(a0 + 0xE2) = 0;
                }
                break;
            case 4:
            case 6:
                goto shared_4_6_b;
            case 5:
                ((void(*)(s32)) func_801803B0)(a0);
                return;
            }
            shared_4_6_b:
            *(u16 *)(a0 + 0xE4) = 0x1E;
            *(u16 *)(a0 + 0x5E) = 0;
            *(u16 *)(a0 + 0x5C) = 0xAA10;
            func_8012B2CC(a0);
            func_8012B23C(a0);
            func_8012B14C(a0, (s32) D_8018E68C);
            func_8012A828(a0, &D_801A648C);
        }
        return;
    }

    case 4:
    {
        s32 v0;
        s32 v1;

        {
            s32 ptr20 = *(s32 *)(a0 + 0x20);
            *(u16 *)(ptr20 + 0x12) = *(u16 *)(a0 + 0xE2);
        }
        func_8012B2CC(a0);
        func_8012B178(a0, 0xFFF80000);

        v0 = ((s32(*)(s32)) func_8012CBA4)(a0);
        D_801E8008 = v0;
        if (v0 == 0 || (v0 & 0x4000) != 0) {
            *(s32 *)(a0 + 4) = *(s32 *)(a0 + 0x38);
            *(s32 *)(a0 + 8) = *(s32 *)(a0 + 0x3C);
            *(s32 *)(a0 + 0xC) = *(s32 *)(a0 + 0x40);
        }

        {
            s32 p, end, v;
            p = (s32) D_801202A0;
            end = (s32) D_801202A0 + 0x6480;
            v = *(u16 *)a0;
            for (; p != end; p += 0x10C) {
                if (p != a0) {
                    if (*(u16 *)p == v) {
                        if (func_8017E404(a0, p) != 0) {
                            break;
                        }
                    }
                }
            }
            ((void(*)(s32)) func_8012AE00)(p);
        }

        if (*(s16 *)(a0 + 6) >= 0x1F8) {
            return;
        }

        *(u8 *)(a0 + 0xC1) = 0;
        *(u16 *)(a0 + 2) = 1;
        *(u16 *)(a0 + 0x34) = 0;
        v0 = rand();
        v1 = *(s32 *)(a0 + 0x20);
        v0 = (v0 & 0x1F) + 0x46;
        *(s32 *)(a0 + 0x1C) = v0;
        v0 = *(u16 *)(a0 + 0x70);
        *(u16 *)(a0 + 0xE0) = 0;
        v1 = *(u16 *)(v1 + 0x12);
        *(u16 *)(a0 + 0xE2) = v1;
        {
            s32 sub = (s32)((u32)v0 << 0x10) >> 0x18;
            switch (sub) {
            case 0:
            case 1:
            case 2:
            case 3:
            case 7:
                if (*(u16 *)(a0 + 0xFE) & 2) {
                    *(u16 *)(a0 + 0xE2) = 0;
                }
                break;
            case 4:
            case 6:
                goto shared_4_6_c;
            case 5:
                ((void(*)(s32)) func_801803B0)(a0);
                goto after_aa10_c;
            }
            shared_4_6_c:
            *(u16 *)(a0 + 0xE4) = 0x1E;
            *(u16 *)(a0 + 0x5E) = 0;
            *(u16 *)(a0 + 0x5C) = 0xAA10;
            func_8012B2CC(a0);
            func_8012B23C(a0);
            func_8012B14C(a0, (s32) D_8018E68C);
            func_8012A828(a0, &D_801A648C);
            after_aa10_c:;
        }

        v0 = rand();
        v0 = v0 & 0x1F;
        *(u16 *)(a0 + 0xE4) = v0;
        v0 = rand();
        v0 = v0 & 0x1F;
        *(s32 *)(a0 + 0x1C) = v0;
        return;
    }
    }
}
