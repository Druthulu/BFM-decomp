#include "common.h"

void func_800CCB20(void) {
}

#include "common.h"

extern void func_80149020(s32 *a0);
extern void (*D_800CE040[])(s32 *);

void func_800CCB28(s32 *param_1) {
    s32 *s0;
    s32 idx;

    func_80149020(param_1);
    s0 = param_1;
    idx = ((Unkstruct_80126B58 *)s0)->unk2 - 2;
    D_800CE040[idx](s0);
}


extern void func_80147324(s32 a0);
extern void func_8014B5C4(s32 *a0, s32 a1, s32 a2);
extern void func_801466F0(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6, s32 a7);
extern void func_801599A4(void *a0);
extern void func_80159B3C(void *a0);

void func_800CCB78(void *a0) {
    func_80147324(0x8E3);
    func_8014B5C4((s32 *)a0, 5, 0);
    func_801466F0(0x13, (s32)a0, 0, 0, 0, 0, 0, 0);
    func_801466F0(0x14, (s32)a0, 0, 0, 0, 0, 0, 0);
    func_801466F0(0x14, (s32)a0, 0, 0, 0, 1, 0, 0);
    func_801466F0(0x14, (s32)a0, 0, 0, 0, 2, 0, 0);
    func_801466F0(0x14, (s32)a0, 0, 0, 0, 3, 0, 0);
    ((Unkstruct_80126B58 *)a0)->unk1C8 = 0xFF;
    func_801599A4(a0);
    func_80159B3C(a0);
}


extern void func_80147078(s32 *a0, s16 a1);
extern void func_800CCD50(void *a0);
void func_800CCC8C(s32 *a0) {
    func_80147078(a0, 33);
    ((void (*)(void *))func_800CCD50)(a0);
}


extern void func_80147078(s32 *a0, s16 a1);
extern void func_800CCCF4(void *a0);
void func_800CCCC0(s32 *a0) {
    func_80147078(a0, 33);
    func_800CCCF4(a0);
}




void func_800CCCF4(void *a0) {

    extern void (*D_800CE044[])(void);
    D_800CE044[((Unkstruct_80126B58 *)a0)->unk2]();
}


extern void func_800CCD50(void *a0);
void func_800CCD30(void *a0) {
    func_800CCD50(a0);
}


void func_800CCD50(void *a0) {
    extern void func_80154274(s32 *a0, s32 a1);
    extern void func_80146D90(s32 a0);
    extern void func_800CCDB0(s32 *a0);
    extern M2C_UNK D_800CE010;
    s32 s0;
    s32 v0;
    u16 v1;

    s0 = (s32)a0;
    func_80154274((s32 *)s0, (s32)&D_800CE010);
    v0 = ((Unkstruct_800CCD50 *)s0)->unk20;
    v1 = *(u16 *)(v0 + 0x12);
    ((Unkstruct_800CCD50 *)s0)->unk246 = 0x200;
    ((Unkstruct_800CCD50 *)s0)->unk244 = v1;
    func_80146D90(s0);
    func_800CCDB0((s32 *)s0);
    ((Unkstruct_800CCD50 *)s0)->unk240 = 0;
    func_80147324(0x8E4);
}


void func_800CCDB0(s32 *a0) {
    ((Unkstruct_800CCDB0 *)a0)->unk23C = 0;
    ((Unkstruct_800CCDB0 *)a0)->unk238 = 0;
    ((Unkstruct_800CCDB0 *)a0)->unk234 = 0;
    ((Unkstruct_800CCDB0 *)a0)->unk2 = 1;
}


void func_800CCDC8(s32 *param_1)
{
    s32 v1;
    s32 v0;

    if (func_800CD240() != 0) return;
    func_800CD288(param_1);
    if (func_800CD494(param_1) != 0) return;
    v0 = func_800CD5CC(param_1);
    if (v0 != 0)
        func_800CD6A4(param_1, v0);
    v1 = func_801612B8(param_1, 0);
    if ((v1 & 0x4000) != 0) {
        func_800CCFA8(param_1);
        return;
    }
    if (v1 == 0 || v1 == 0x8000) {
        func_801477E8(param_1, 0);
        func_80146CA0(param_1);
        return;
    }
    if (func_801496D4(param_1) != 0) {
        func_800CCEB8(param_1);
        return;
    }
    func_801483E8(param_1);
    CAST_SIGN(s32, (u8 *)param_1, 0x44) |= 0x1000;
}


extern void func_801477E8(s32 *a0, s32 a1);

void func_800CCEB8(void *arg0) {
    func_801477E8((s32 *)arg0, 0xFFEA0000);
    ((Unkstruct_80126B58 *)arg0)->unk2 = 2;
}


#include "common.h"

extern void func_80148038(s32 a0, s32 a1);
extern void func_80147460(s32 a0);
extern void func_800CD494(void *a0);
extern void func_800CD5CC(void *a0);
extern void func_8016151C(void *a0);

void func_800CCEEC(void *arg0) {
    s32 v1;
    s32 v0;

    if (func_800CD240() != 0) {
        return;
    }
    func_800CD288(arg0);
    if (((s32 (*)(void *))func_800CD494)(arg0) != 0) {
        return;
    }
    func_80148038((s32)arg0, 0x1A000);
    func_80147460((s32)arg0);
    v0 = ((s32 (*)(void *))func_800CD5CC)(arg0);
    if (v0 != 0) {
        func_800CD6A4(arg0, v0);
    }
    v1 = ((s32 (*)(void *))func_8016151C)(arg0);
    if ((v1 & 0x4000) != 0) {
        func_800CCFA8(arg0);
        return;
    }
    if (v1 != 0) {
        ((Unkstruct_80126B58 *)arg0)->unk2 = 1;
        return;
    }
    CAST_SIGN(s32, (s32)arg0, 0x44) |= 0x1000;
}


extern s16 D_801152B0;
extern s16 D_801152B4;

void func_800CCFA8(s32 *a0) {
    s32 t = D_801152B0 << 6;
    ((Unkstruct_80126B58 *)a0)->unk238 = 0x80000;
    CAST_ALIAS(s32, (s32)a0, 0x234) = t;
    ((Unkstruct_80126B58 *)a0)->unk23C = D_801152B4 << 6;
    ((Unkstruct_80126B58 *)a0)->unk2 = 3;
}


extern void func_80146DE8(s32 *a0, s32 a1, s32 a2, s32 a3);
extern void func_80147F50(s32 a0);
extern void func_801473EC(s32 *a0);
extern void func_80148038(s32 a0, s32 a1);
extern void func_80147460(s32 a0);
extern void func_800CD494(void *a0);
extern void func_800CD5CC(void *a0);
extern void func_8016151C(void *a0);
extern void func_80146E90(s32 *a0, s32 a1);
extern void func_80146CA0(void *a0);
extern s16 D_801152B0;
extern s16 D_801152B4;

void func_800CCFDC(void *arg0) {
    s32 ret;

    if (func_800CD240(arg0) != 0) {
        return;
    }
    func_80146DE8((s32 *)arg0, ((Unkstruct_80126B58 *)arg0)->unk234, ((Unkstruct_80126B58 *)arg0)->unk238, ((Unkstruct_80126B58 *)arg0)->unk23C);
    func_80147F50((s32)arg0);
    func_801473EC((s32 *)arg0);
    func_80148038((s32)arg0, 0x1A000);
    func_80147460((s32)arg0);
    if (((s32 (*)(void *))func_800CD494)(arg0) != 0) {
        return;
    }
    func_800CD5CC(arg0);
    ret = ((s32 (*)(void *))func_8016151C)(arg0);
    if (ret & 0x4000) {
        CAST_ALIAS(s32, (s32)arg0, 0x234) = D_801152B0 << 6;
        ((Unkstruct_80126B58 *)arg0)->unk238 = 0x80000;
        ((Unkstruct_80126B58 *)arg0)->unk23C = D_801152B4 << 6;
        ((Unkstruct_80126B58 *)arg0)->unk2 = 3;
    } else if (ret != 0) {
        func_80146E90((s32 *)arg0, 8);
        func_80146CA0(arg0);
    } else {
        CAST_SIGN(s32, (s32)arg0, 0x44) |= 0x1000;
    }
}


extern void func_80146DE8(s32 *a0, s32 a1, s32 a2, s32 a3);
extern void func_80147F50(s32 a0);
extern void func_801473EC(s32 *a0);
extern void func_800CD494(void *a0);
extern void func_800CD5CC(void *a0);
extern s32 func_801612B8(void *a0, s32 a1);
extern s32 func_80146E98(s32 a0);
extern void func_801477E8(s32 *a0, s32 a1);
extern s16 D_801152B0;
extern s16 D_801152B4;

void func_800CD0DC(void *arg0) {
    s32 ret;

    if (func_800CD240() != 0) {
        return;
    }
    func_80146DE8((s32 *)arg0, ((Unkstruct_80126B58 *)arg0)->unk234, ((Unkstruct_80126B58 *)arg0)->unk238, ((Unkstruct_80126B58 *)arg0)->unk23C);
    func_80147F50((s32)arg0);
    func_801473EC((s32 *)arg0);
    if (((s32 (*)(void *))func_800CD494)(arg0) != 0) {
        return;
    }
    func_800CD5CC(arg0);
    ret = func_801612B8(arg0, 0);
    if (func_80146E98((s32)arg0) != 0) {
        if (ret & 0x4000) {
            CAST_ALIAS(s32, (s32)arg0, 0x234) = D_801152B0 << 6;
            ((Unkstruct_80126B58 *)arg0)->unk238 = 0x80000;
            ((Unkstruct_80126B58 *)arg0)->unk23C = D_801152B4 << 6;
            ((Unkstruct_80126B58 *)arg0)->unk2 = 3;
        } else if (ret == 0 || ret == 0x8000) {
            func_801477E8((s32 *)arg0, 0xFFEA0000);
            ((Unkstruct_80126B58 *)arg0)->unk2 = 2;
        } else {
            ((Unkstruct_80126B58 *)arg0)->unk23C = 0;
            ((Unkstruct_80126B58 *)arg0)->unk238 = 0;
            ((Unkstruct_80126B58 *)arg0)->unk234 = 0;
            ((Unkstruct_80126B58 *)arg0)->unk2 = 1;
        }
    } else {
        CAST_SIGN(s32, (s32)arg0, 0x44) |= 0x1000;
    }
}


extern void func_801553C0(s32 a0);
extern void func_801553A8(s32 *a0);
extern void func_80154A74(s32 a0, s32 a1);

void func_800CD1F4(s32 *a0) {
    func_801553C0((s32)a0);
    func_801553A8(a0);
    func_80154A74((s32)a0, 0x11);
    CAST_SIGN(s32, (u8 *)a0, 0x44) &= ~0x1000;
}


extern void func_801599A4(void *a0);
extern void func_80159B3C(void *a0);

s32 func_800CD240(void *arg0) {
    s32 s0;

    s0 = (s32)arg0;
    __asm__ __volatile__("" : "=r"(s0) : "0"(s0));  // !FAKE: launder — NEEDED DIFFERS (P36 rung B tus10)
    if (*(s16 *)(s0 + 0x1C8) != 0) {
        return 0;
    }
    func_801599A4((void *)s0);
    func_80159B3C((void *)s0);
    return 1;
}


extern s32 func_801488A8();  // K&R: 0 of 1 args (P37 rung D t4_D58)
extern void func_80146D90(void *arg0);
extern s32 func_80148D44(void *arg0);
extern void func_80147AD4(void *arg0, s32 arg1, s32 arg2, s32 arg3);
extern void func_801473EC(s32*);


void func_800CD288(Work_md_MAIN_046 *arg0) {
    s32 pad00; s32 pad04; s32 pad08; s32 pad0C;
    s32 pad10; s32 pad14; s32 pad18; s32 pad1C;
    u8 *s1;
    s32 a0;
    (void)&pad00; (void)&pad04; (void)&pad08; (void)&pad0C;
    (void)&pad10; (void)&pad14; (void)&pad18; (void)&pad1C;
    s1 = (u8 *) arg0->unk20;
    if (func_801488A8() != 0) {
        func_80146D90(arg0);
        *(s16 *) (s1 + 0x12) = func_80148D44(arg0);
        func_80147AD4(arg0, 0, 0, -0xC000);

        arg0->unk234 += arg0->unk10;
        arg0->unk238 += arg0->unk14;
        arg0->unk23C += arg0->unk18;

        if (arg0->unk234 > 0xB0000) {
            arg0->unk234 = 0xB0000;
        } else if (arg0->unk234 < -0xB0000) {
            arg0->unk234 = -0xB0000;
        }

        if (arg0->unk238 > 0xB0000) {
            arg0->unk238 = 0xB0000;
        } else if (arg0->unk238 < -0xB0000) {
            arg0->unk238 = -0xB0000;
        }

        if (arg0->unk23C > 0xB0000) {
            arg0->unk23C = 0xB0000;
        } else if (arg0->unk23C < -0xB0000) {
            arg0->unk23C = -0xB0000;
        }
    } else {
        a0 = 0;
        if (arg0->unk234 != 0) {
            a0 = 1;
            if (arg0->unk234 >= 0) {
                arg0->unk234 -= 0x8000;
                if (arg0->unk234 < 0) {
                    arg0->unk234 = 0;
                }
            } else {
                arg0->unk234 += 0x8000;
                if (arg0->unk234 >= 0) {
                    arg0->unk234 = 0;
                }
            }
        }
        if (arg0->unk238 != 0) {
            a0 = 1;
            if (arg0->unk238 >= 0) {
                arg0->unk238 -= 0x8000;
                if (arg0->unk238 < 0) {
                    arg0->unk238 = 0;
                }
            } else {
                arg0->unk238 += 0x8000;
                if (arg0->unk238 >= 0) {
                    arg0->unk238 = 0;
                }
            }
        }
        if (arg0->unk23C != 0) {
            a0 = 1;
            if (arg0->unk23C >= 0) {
                arg0->unk23C -= 0x8000;
                if (arg0->unk23C < 0) {
                    arg0->unk23C = 0;
                }
            } else {
                arg0->unk23C += 0x8000;
                if (arg0->unk23C >= 0) {
                    arg0->unk23C = 0;
                }
            }
        }
        if (a0 == 0) {
            return;
        }
    }

    arg0->unk10 = arg0->unk234;
    arg0->unk14 = arg0->unk238;
    arg0->unk18 = arg0->unk23C;
    ((void (*)(void *))func_801473EC)(arg0);
}


extern void func_800CDA14(s32 a0);

void func_800CD494(void *a0) {
    s32 rv;
    s32 s0;
    s32 s1;
    u16 v0;
    u16 v1;

    s0 = (s32)a0;
    s1 = ((Unkstruct_80126B58 *)s0)->unk20;
    CAST_SIGN(s32, s0, 0x44) |= 2;
    v0 = func_80148800((s32 *)a0);
    if (v0 & 0x90) {
        CAST_WIDTH(u16, s0, 0x240) = 0;
        func_80147324(0x8E4);
    }
    v0 = func_801487F4((s32 *)s0);
    if (v0 & 0x90) {
        func_800CDA14(s0);
        v0 = ((Unkstruct_80126B58 *)s0)->unk246;
        v0 = v0 + 8;
        ((Unkstruct_80126B58 *)s0)->unk246 = v0;
        if ((s16)v0 >= 0x201) {
            ((Unkstruct_80126B58 *)s0)->unk246 = 0x200;
        }
        v0 = CAST_WIDTH(u16, s0, 0x240);
        v1 = ((Unkstruct_80126B58 *)s0)->unk246;
        v0 = v0 + v1;
        CAST_WIDTH(u16, s0, 0x240) = v0;
        if ((s16)v0 >= 0x1000) {
            CAST_WIDTH(u16, s0, 0x240) = 0;
            func_80147324(0x8E4);
        }
    } else {
        v0 = ((Unkstruct_80126B58 *)s0)->unk246;
        v0 = v0 - 0x20;
        ((Unkstruct_80126B58 *)s0)->unk246 = v0;
        if ((s16)v0 <= 0) {
            ((Unkstruct_80126B58 *)s0)->unk246 = 0;
        }
    }
    v0 = ((Unkstruct_80126B58 *)s0)->unk244;
    v1 = ((Unkstruct_80126B58 *)s0)->unk246;
    v0 = v0 + v1;
    v0 = v0 & 0xFFF;
    ((Unkstruct_80126B58 *)s0)->unk244 = v0;
    *(u16 *)(s1 + 0x12) = v0;
    if (CAST_SIGN(s16, s0, 0x246) == 0) {
        func_801599A4((void *)s0);
        func_80159B3C((void *)s0);
        rv = 1;
    } else {
        rv = 0;
    }
    __asm__ __volatile__("" : : "r"(rv));  // !FAKE: keepalive — NEEDED DIFFERS (P36 rung B t8_tus2)
}


extern u8 D_801202A0[];
extern s32 func_8014C308(s32 a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8014C278(s32 a0, s32 a1, s32 a2);
extern void func_80015978(s32 a0, s32 *a1);
extern s32 func_8014C3A4(void *a0, s32 a1, s32 a2, s32 a3);

void func_800CD5CC(void *arg0) {
    register s32 rv __asm__("$2");  // !FAKE: pin $2 — NEEDED DIFFERS (P36 rung B tus10)
    s32 a0 = (s32)arg0;
    s32 found = 0;
    u8 *p = D_801202A0;
    s32 t = 0x25;
    s16 buf[4];
    *(u8 *)(a0 + 0x1AB) ^= 1;
    if (p < p + 0x6480) {
        do {
            if (func_8014C308(a0, (s32)p, t, 0x10) != 0) {
                if (func_8014C278(a0, (s32)p, 0x40) != 0) {
                    func_80015978((s32)(p + 4), (s32 *)buf);
                    buf[3] = 0;
                    func_8014C3A4((void *)a0, (s32)p, t, (s32)buf);
                    found = (s32)p;
                }
            }
            p += 0x10C;
        } while (p < D_801202A0 + 0x6480);
    }
    rv = found;
    __asm__ __volatile__("" : : "r"(rv));  // !FAKE: keepalive — NEEDED DIFFERS (P36 rung B tus10)
}


extern void func_8001382C(s32 a0, void *a1, void *a2);
extern s32 func_8014C59C(void *a0, void *a1);
extern s32 D_800CE058[3];

void func_800CD6A4(void *arg0, void *arg1) {
    s32 sp10[4];
    s32 ret;

    ret = func_8014C59C(arg0, arg1);
    func_8001382C((ret + 0x800) & 0xFFF, D_800CE058, sp10);
    ((Unkstruct_80126B58 *)arg0)->unk234 = sp10[0];
    ((Unkstruct_80126B58 *)arg0)->unk238 = sp10[1];
    ((Unkstruct_80126B58 *)arg0)->unk23C = sp10[2];
}


extern s16 D_800CE8D4;
extern void (*D_800CE080[])(void);
extern s32 func_80012ABC(s32 a0, s32 a1, s32 a2);
extern void func_8014ACC0(s32 a0, s32 a1);
extern s32 func_80161A30(s32 a0);
extern void func_800CD94C(void);

void func_800CD708(s32 param_1)
{
    s32 s0;
    s32 iVar1;
    s0 = ((Unkstruct_800CD708 *)param_1)->unk4C;
    D_800CE080[((Unkstruct_800CD708 *)param_1)->unk2]();

    *(s32 *)(((Unkstruct_800CD708 *)param_1)->unk20 + 4) &= 0x7FFFFFFF;
    *(s32 *)(((Unkstruct_800CD708 *)param_1)->unk20 + 4) |= (*(s32 *)(((Unkstruct_800CD708_2 *)s0)->unk20 + 4)) & 0x80000000;

    ((Unkstruct_800CD708 *)param_1)->unk60 = 0;

    iVar1 = ((Unkstruct_800CD708_2 *)s0)->unk20;
    D_800CE8D4 = func_80012ABC(D_800CE8D4, *(s16 *)(iVar1 + 0x12), 0xA);

    func_8014ACC0(s0, 1);
    if (func_80161A30(s0) != 0) {
        return;
    }
    ((void (*)(s32))func_800CD94C)(param_1);
}


extern s32 func_8014659C(void);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_800CD96C(s32 a0);
extern void func_80146CA0(void *a0);
extern s32 D_800CE8CC;
extern s16 D_800CE8D4;
extern void func_800CD94C(void);

void func_800CD7D8(s32 a0) {
    s32 s0;
    s32 s2;
    s2 = *(s32 *)(a0 + 0x4C);
    s0 = func_8014659C();
    ((Unkstruct_80126B58 *)a0)->unk20 = s0;
    if (s0 != 0) {
        func_8001C214(s0, (s32)&D_800CE8CC);
        *(s32 *)(s0 + 4) |= 0x50000000;
        *(s16 *)(s0 + 0x1C) = 0;
        *(s16 *)(s0 + 0x1A) = 0;
        *(s16 *)(s0 + 0x18) = 0;
        func_800CD96C(a0);
        D_800CE8D4 = *(u16 *)(((Unkstruct_80126B58 *)s2)->unk20 + 0x12);
        func_80146CA0((void *)a0);
    } else {
        ((void (*)(s32))func_800CD94C)(a0);
    }
}


extern s32 rand(void);
extern void func_800CD96C(s32 a0);

void func_800CD884(void *arg0) {
    s32 s0;
    u16 w;
    u16 t2;

    s0 = ((Unkstruct_80126B58 *)arg0)->unk20;
    if (CAST_SIGN(s16, (s32)arg0, 0x60) != 0) {
        w = *(u16 *)(s0 + 0x18) + 0x100;
        *(u16 *)(s0 + 0x18) = w;
        if ((s16)w > 0x1000) {
            if ((rand() & 1) != 0) {
                *(u16 *)(s0 + 0x18) = 0x1000;
            } else {
                *(u16 *)(s0 + 0x18) = 0x1333;
            }
        }
    } else {
        w = *(u16 *)(s0 + 0x18) - 0x100;
        *(u16 *)(s0 + 0x18) = w;
        if ((s16)w < 0) {
            *(u16 *)(s0 + 0x18) = 0;
        }
    }
    t2 = *(u16 *)(s0 + 0x18);
    *(u16 *)(s0 + 0x1C) = t2;
    *(u16 *)(s0 + 0x1A) = t2;
    *(u16 *)(s0 + 0x12) += 0x1C7;
    func_800CD96C((s32)arg0);
}


extern void func_80162CCC();  // K&R: 0 of 1 args (P37 rung D t4_D44)
void func_800CD94C(void) {
    func_80162CCC();
}


void func_800CD96C(s32 param_1) {
    extern void func_80013F3C(void *a0);
    extern void RotMatrixY(s32 a0, void *a1);
    extern void func_80048D9C(void *a0, void *a1);
    extern void func_80020F34(s32 a0, s32 a1);

    s32 work;
    s32 hdr;
    s32 model;

    work = *(s32 *)(param_1 + 0x4C);
    hdr = ((Unkstruct_80126B58 *)work)->unk20;
    model = ((Unkstruct_80126B58 *)param_1)->unk20;
    ((Unkstruct_80126B58 *)param_1)->unk6 = *(s32 *)(hdr + 0x48);
    ((Unkstruct_80126B58 *)param_1)->unkA = *(s32 *)(hdr + 0x4C) - 0x20;
    ((Unkstruct_80126B58 *)param_1)->unkE = *(s32 *)(hdr + 0x50);
    func_80013F3C((void *)(model + 0x34));
    RotMatrixY(*(s16 *)(model + 0x12), (void *)(model + 0x34));
    func_80048D9C((void *)(model + 0x34), (void *)(((Unkstruct_80126B58 *)work)->unk20 + 0x34));
    func_80020F34(model + 0x34, model + 0x18);
    *(u16 *)(model + 0x2C) |= 1;
}


extern s32 func_8014C088(s32 a0, s32 a1);

void func_800CDA14(s32 a0) {
    s32 v1;

    v1 = func_8014C088(a0, 0x13);
    if (v1 != 0) {
        ((Unkstruct_800CB098 *)v1)->unk60 = 1;
    }
}


void func_800CDA44(s32 *a0) {
    *(s16 *)((s32)a0 + 0x1C8) = 0;
}


extern s32 func_80161A30(s32 a0);
extern void (*D_800CE0AC[])(void);
extern void func_800CDBD4(void);

void func_800CDA4C(s32 param_1)
{
    s32 iVar1;
    iVar1 = ((Unkstruct_800CCFA8 *)param_1)->unk4C;
    D_800CE0AC[((Unkstruct_800CCFA8 *)param_1)->unk2]();
    if (func_80161A30(iVar1) == 0) {
        ((void (*)(s32))func_800CDBD4)(param_1);
    }
}



extern s32 func_80146578(void);
extern void func_8001CC3C(s32 a0, void *a1, s32 a2, s32 a3);
extern void func_80146E90(s32 *a0, s32 a1);
extern void func_80146CA0(void *a0);
extern void func_800CDBD4();
extern void func_800CDBF4();  // K&R: 0 of 1 args (P37 rung D t4_D35)

extern u8 D_800CE068[];
extern u8 D_800CE08C[];

void func_800CDAB4(s32 *param_1) {
    s32 s0;
    s32 v0;

    s0 = func_80146578();
    ((Unkstruct_80126B58 *)param_1)->unk20 = s0;
    if (s0 != 0) {
        func_8001CC3C(s0, D_800CE068, 0x234, 0x1C0);
        *(u8 *)((s32)s0 + 0x27) = 0x26;
        *(u16 *)((s32)s0 + 0x1A) = 0x2000;
        *(u16 *)((s32)s0 + 0x18) = 0x2000;
        *(u32 *)((s32)s0 + 4) |= 0x8000000;
        v0 = ((Unkstruct_80126B58 *)param_1)->unk50 * 8;
        CAST_WIDTH(U8x, (s32)param_1, 0x60) = *(U8x *)(&D_800CE08C[v0]);
        func_80146E90(param_1, 0);
        ((void (*)(s32 *))func_800CDBF4)(param_1);
        func_80146CA0(param_1);
    } else {
        ((void (*)(s32 *))func_800CDBD4)(param_1);
    }
}


extern void func_800CDBF4();  // K&R: 0 of 1 args (P37 rung D t4_D35)
extern void func_800CDCA8(void *arg0);
void func_800CDBA4(s32 a0) {
    func_800CDBF4();
    ((void (*)(s32))func_800CDCA8)(a0);
}


extern void func_80162CCC();  // K&R: 0 of 1 args (P37 rung D t4_D44)
void func_800CDBD4(void) {
    func_80162CCC();
}


extern void func_80049CAC(s32 a0, s32 a1);
extern void ApplyMatrixSV(void *m0, void *m1, void *m2);
extern void func_80015954(s32 a0, s32 a1);
extern s16 D_800CE0B8[4];

void func_800CDBF4(s32 s0) {
    u16 sp10[3];
    u16 sp18[16];
    s32 *outer;
    s32 *inner;
    s32 t;

    outer = *(s32 **)(s0 + 0x4C);
    ((Unkstruct_800CDBF4 *)s0)->unk62 = (((Unkstruct_800CDBF4 *)s0)->unk62 + ((Unkstruct_800CDBF4 *)s0)->unk66) & 0xFFF;
    func_80049CAC(s0 + 0x60, sp18);
    ApplyMatrixSV(sp18, D_800CE0B8, sp10);
    inner = *(s32 **)((s32)outer + 0x20);
    sp10[0] = sp10[0] + inner[18];
    t = sp10[1] - 0x20;
    sp10[1] = t + inner[19];
    sp10[2] = sp10[2] + inner[20];
    func_80015954(sp10, s0 + 4);
}


extern void func_80146E90(s32 *a0, s32 a1);
extern s32 func_80146E98(s32 a0);

void func_800CDCA8(void *arg0) {
    s16 *ptr = CAST_SIGN(s16 *, (s32)arg0, 0x20);
    s32 val;

    if (func_80146E98((s32)arg0) != 0) {
        if ((rand() & 0x1F) == 0) {
            func_80146E90((s32 *)arg0, (rand() & 0x1F) | 0x20);
        }
        val = ((Unkstruct_800CDCA8 *)ptr)->unk12;
        val += 0x38;
    } else {
        val = ((Unkstruct_800CDCA8 *)ptr)->unk12;
        val += 0x155;
    }
    ((Unkstruct_800CDCA8 *)ptr)->unk12 = val & 0xFFF;
}


extern s32 func_80161A30(s32 a0);
extern void (*D_800CE0C0[])(void);
extern void func_800CDF64(void);

void func_800CDD34(s32 param_1)
{
    s32 iVar1;
    iVar1 = ((Unkstruct_800CCFA8 *)param_1)->unk4C;
    D_800CE0C0[((Unkstruct_800CCFA8 *)param_1)->unk2]();
    if (func_80161A30(iVar1) == 0) {
        ((void (*)(s32))func_800CDF64)(param_1);
    }
}


extern s32 func_80146578(void);
extern void func_8001CC3C(s32 a0, void *a1, s32 a2, s32 a3);
extern void func_80149374(s32 a0, s32 a1);
extern void func_80146DE8(s32 *a0, s32 a1, s32 a2, s32 a3);
extern void func_80146E90(s32 *a0, s32 a1);
extern void func_80146CA0(void *a0);
extern void func_8014ACC0(s32 a0, s32 a1);
extern void func_800CDF64(void);

void func_800CDD9C(s32 param_1) {
    extern u8 D_800CE068[];
    extern s16 D_800CE8D4;
    s32 iVar1;
    s32 iVar2;
    u16 d;
    u16 x;

    iVar1 = *(s32 *)(param_1 + 0x4C);
    iVar2 = func_80146578();
    ((Unkstruct_80126B58 *)param_1)->unk20 = iVar2;
    if (iVar2 != 0) {
        func_8001CC3C(iVar2, D_800CE068, 0x200, 0x100);
        *(u8 *)(iVar2 + 0x27) = 8;
        *(u32 *)(iVar2 + 4) = *(u32 *)(iVar2 + 4) | 0x50000000;
        func_80149374(iVar1, param_1 + 4);
        d = D_800CE8D4;
        x = *(u16 *)(((Unkstruct_80126B58 *)iVar1)->unk20 + 0x10);
        *(u16 *)(iVar2 + 0x12) = d;
        *(u16 *)(iVar2 + 0x10) = x;
        *(u16 *)(iVar2 + 0x14) = *(u16 *)(((Unkstruct_80126B58 *)iVar1)->unk20 + 0x14);
        ((Unkstruct_80126B58 *)param_1)->unk60 = ((Unkstruct_80126B58 *)iVar1)->unk100;
        ((Unkstruct_80126B58 *)param_1)->unk62 = ((Unkstruct_80126B58 *)iVar1)->unk102;
        ((Unkstruct_80126B58 *)param_1)->unk64 = ((Unkstruct_80126B58 *)iVar1)->unk104;
        *(u16 *)(iVar2 + 0x1A) = 0x1000;
        *(u16 *)(iVar2 + 0x18) = 0x1000;
        func_80146DE8((s32 *)param_1, 0, 0, 0xFFE00000);
        func_80146E90((s32 *)param_1, 8);
        func_80146CA0((void *)param_1);
        func_8014ACC0(iVar1, 1);
    } else {
        ((void (*)(s32))func_800CDF64)(param_1);
    }
}


extern s32 func_80146E98(s32 a0);
extern void func_80146CA0(void *a0);
extern void func_800CDF84(s32, s32);
extern void func_80163194(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);
extern void func_80162FC0(void *a0);
extern s32 func_80163408(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80163328(void *a0);
extern s32 func_801632F0(void *a0);

void func_800CDEB4(void *arg0) {
    s32 *s1;
    u16 var;
    s32 sp18[8];

    s1 = CAST_SIGN(s32 *, (u8 *)arg0, 0x20);
    if (func_80146E98((s32)arg0) != 0) {
        func_80146CA0(arg0);
    } else {
        ((void (*)(void *, void *))func_800CDF84)(arg0, sp18);
        func_80163194((s32)arg0, 0, 0, 0, (s32)sp18);
        func_80162FC0(arg0);
        var = ((Unkstruct_800CDCA8 *)s1)->unk1A + 0x100;
        ((Unkstruct_800CDCA8 *)s1)->unk1A = var;
        ((Unkstruct_800CDCA8 *)s1)->unk18 = var;
        func_80163408((s32)arg0, 0x23, 0x80, 8);
        func_80163328(arg0);
        func_801632F0(arg0);
    }
}


extern void func_80162CCC();  // K&R: 0 of 1 args (P37 rung D t4_D44)
void func_800CDF64(void) {
    func_80162CCC();
}


extern void func_80013F3C(s32 a0);
extern void func_800126C4(s32 a0, s32 a1);
extern void func_80012558(s32 a0, s32 a1);
extern void func_800123F0(s32 a0, s32 a1);

void func_800CDF84(s32 a0, s32 a1)
{
    s32 q;
    q = ((Unkstruct_800CDF84 *)a0)->unk20;
    func_80013F3C(a1);
    func_800126C4(a1, ((Unkstruct_800CDF84 *)a0)->unk60);
    func_800123F0(a1, ((Unkstruct_800CDF84 *)a0)->unk64);
    func_80012558(a1, ((Unkstruct_800CDF84 *)a0)->unk62);
    func_80012558(a1, ((Unkstruct_800CDF84_2 *)q)->unk12);
    func_800126C4(a1, ((Unkstruct_800CDF84_2 *)q)->unk10);
    func_800123F0(a1, ((Unkstruct_800CDF84_2 *)q)->unk14);
}


INCLUDE_RODATA("asm/md_MAIN_046/nonmatchings/md_MAIN_046", D_800CCB1C);
