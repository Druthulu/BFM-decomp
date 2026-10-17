#include "common.h"

void func_800CCB20(void) {
}

extern void func_80149020(s32 a0);
extern void (*D_800CE1E4[])(s32);

void func_800CCB28(s32 param_1) {
    s32 s0 = param_1;
    s32 idx;
    func_80149020(s0);
    idx = *(u16 *)(s0 + 2) - 2;
    D_800CE1E4[idx](s0);
}


extern void func_8014B5C4(s32 *a0, s32 a1, s32 a2);
extern void func_801466F0(s32 a0, s32 a1, s32 a2, s32 a3, s32 sp5, s32 sp6, s32 sp7, s32 sp8);
extern void func_801599A4(void *a0);
extern void func_80159B3C(void *a0);

void func_800CCB78(void *a0) {
    func_8014B5C4((s32 *)a0, 3, 0);
    func_801466F0(7, (s32)a0, 0, 0, 0, 0, 0, 0);
    ((Unkstruct_80126B58 *)a0)->unk1C8 = 0xFF;
    func_801599A4(a0);
    func_80159B3C(a0);
}


extern void (*D_800CE1F4[])(s32);
extern void func_800CCE68(void);
extern s32 func_801619D0(s32 a0);
extern s32 func_80146994(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80147324(s32 a0);

void func_800CCBE4(s32 param_1) {
    s32 iVar1;
    iVar1 = ((Unkstruct_800CCBE4 *)param_1)->unk4C;
    D_800CE1F4[((Unkstruct_800CCBE4 *)param_1)->unk2](param_1);
    ((Unkstruct_800CCBE4_2 *)*(s32 *)(param_1 + 0x20))->unk4 &= 0x7FFFFFFF;
    ((Unkstruct_800CCBE4_2 *)*(s32 *)(param_1 + 0x20))->unk4 |= *(s32 *)(*(s32 *)(iVar1 + 0x20) + 4) & 0x80000000;
    if (func_801619D0(iVar1) == 0) {
        ((void (*)(s32))func_800CCE68)(param_1);
        func_80146994(0x3A, iVar1, 0, 0);
        func_80147324(0xA13);
    }
}


extern u8 D_800CEBEC;
extern void func_8014659C(void);
extern void func_8001C810(s32, void *);
extern void func_800CCF58(arg0, arg1);
extern void func_800CCE88(s32);
extern s32 func_80146CA0(void *);
extern void func_800CCE68();

void func_800CCCA0(s32 param_1) {
    s32 p1;
    s32 iVar1; /* $s0 */

    iVar1 = ((s32 (*)(void))func_8014659C)();
    ((Unkstruct_800CCCA0 *)param_1)->unk20 = iVar1;
    if (iVar1 != 0) {
        func_8001C810(iVar1, &D_800CEBEC);
        *(u32 *)(iVar1 + 4) |= 0x40010000;
        func_800CCF58(iVar1, 0);
        func_800CCE88(param_1);
        ((Unkstruct_800CCCA0 *)param_1)->unk60 = 0;
        ((s32 (*)(void *))func_80146CA0)(param_1);
    } else {
        ((void (*)(s32))func_800CCE68)(param_1);
    }
}


extern s32 func_800CCF30(void *a0);

void func_800CCD2C(s32 param_1) {
    s32 p1;
    s32 s0;
    s16 v0;
    s32 param_12;
    param_12 = param_1;

    p1 = param_12;
    s0 = ((Unkstruct_800CCD2C_2 *)p1)->unk20;
    if (func_800CCF30((void *)param_12) == 0) {
        v0 = CAST_SIGN(u16, s0, 0x18) + 0x100;
        ((Unkstruct_800CCD2C *)s0)->unk18 = v0;
        if (v0 >= 0x1001) {
            v0 = 0x1000;
            ((Unkstruct_800CCD2C *)s0)->unk18 = v0;
            func_80146CA0((void *)p1);
        }
        func_800CCF58(s0, ((Unkstruct_800CCD2C *)s0)->unk18);
        func_800CCE88(p1);
    }
}


extern s32 func_80012F74(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_800CCF58(arg0, arg1);
extern s32 func_800CCF30(void *a0);
extern void func_800CCE68();
extern void func_800CCE88(s32 a0);

void func_800CCDB0(s32 param_1) {
    s32 s2 = ((Unkstruct_800CCD2C_2 *)param_1)->unk4C;
    s32 s1 = ((Unkstruct_800CCD2C_2 *)param_1)->unk20;
    s32 a1val;
    s32 v0;

    if (CAST_SIGN(u16, s2, 0x1C8) & 0x10) {
        a1val = 0x1400;
    } else {
        a1val = 0x1000;
    }
    v0 = func_80012F74(((Unkstruct_800CCD2C *)s1)->unk18, a1val, 0xA, 1);
    ((Unkstruct_800CCD2C *)s1)->unk18 = v0;
    func_800CCF58(s1, ((Unkstruct_800CCD2C *)s1)->unk18);
    if (func_800CCF30((void *)param_1) != 0) {
        return;
    }
    if (((Unkstruct_800CCDB0_2 *)s2)->unk1C8 == 0) {
        ((void (*)(s32))func_800CCE68)(param_1);
    } else {
        ((Unkstruct_800CCDB0_2 *)s2)->unk1C8 -= 1;
        func_800CCE88(param_1);
    }
}


extern void func_80162CCC();  // K&R: 0 of 1 args (P37 rung D t4_D44)
void func_800CCE68(void) {
    func_80162CCC();
}


void func_800CCE88(s32 param_1) {
    s32 s2 = ((Unkstruct_800CCCA0 *)param_1)->unk4C;
    s32 a0 = *(s32 *)(s2 + 0x20);
    s32 s1 = ((Unkstruct_800CCCA0 *)param_1)->unk20;
    s32 s0 = s1 + 0x34;
    ((Unkstruct_800CCCA0 *)param_1)->unk6 = ((Unkstruct_800CCE88 *)a0)->unk48;
    ((Unkstruct_800CCCA0 *)param_1)->unkA = ((Unkstruct_800CCE88 *)a0)->unk4C - 0x20;
    ((Unkstruct_800CCCA0 *)param_1)->unkE = ((Unkstruct_800CCE88 *)a0)->unk50;
    func_80013F3C((void *)s0);
    RotMatrixY(*(s16 *)(s1 + 0x12), (void *)s0);
    func_80048D9C((void *)s0, (void *)(*(s32 *)(s2 + 0x20) + 0x34));
    func_80020F34(s0, s1 + 0x18);
    *(u16 *)(s1 + 0x2C) |= 1;
}


s32 func_800CCF30(void *a0) {
    if (((Unkstruct_800CCD2C_2 *)a0)->unk60 != 0) {
        ((Unkstruct_800CCD2C_2 *)a0)->unk2 = 3;
        return 1;
    }
    return 0;
}


void func_800CCF58(arg0, arg1) void *arg0; s16 arg1; {
    ((Unkstruct_800CCF58 *)arg0)->unk1C = arg1;
    ((Unkstruct_800CCF58 *)arg0)->unk1A = arg1;
    ((Unkstruct_800CCF58 *)arg0)->unk18 = arg1;
}


void func_800CCF68(s32 param_1)
{
    extern s32 func_8014C088(s32 a0, s32 a1);
    extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
    s32 ptr;

    ptr = func_8014C088(param_1, 7);
    if (ptr != 0) {
        *(u16 *)(ptr + 0x60) = 1;
    }
    ((Unkstruct_80126B58 *)param_1)->unk1C8 = 0;
    func_80146A6C(0x39, (void *)param_1, 0, 0, 0, 0, 0);
}


extern void (*D_800CE204[])(void);
extern s32 func_801619D0(s32 a0);
extern void func_800CD178(void);

void func_800CCFC8(s32 param_1)
{
    s32 iVar1;
    iVar1 = ((Unkstruct_800CCFA8 *)param_1)->unk4C;
    D_800CE204[((Unkstruct_800CCFA8 *)param_1)->unk2]();
    if (func_801619D0(iVar1) == 0) {
        ((void (*)(s32))func_800CD178)(param_1);
    }
}




extern s32 func_80146CA0(void *a0);
    void func_800CD030(s32 *a0) {
        *(s16 *)((s32)a0 + 0x60) = 0;
        ((void (*)(void))func_80146CA0)();
    }


extern u16 D_800B99DA;
extern u16 func_801487F4(s32*);
extern s32 func_80146608(s32, s32, s32, s32, s16, s32, s32, s32, s32);
extern s32 func_80146CA0(void*);
extern void func_80147324(s32);

void func_800CD050(s32 arg0) {
    s32 acc;
    s32 i;
    s32 ptr;

    ptr = *(s32*)(arg0 + 0x4C);
    if (!(func_801487F4((s32*)ptr) & 0x90)) {
        func_80146CA0(arg0);
        return;
    }
    ((Unkstruct_80126B58 *)arg0)->unk60 -= 1;
    if (CAST_SIGN(s16, arg0, 0x60) < 0) {
        ((Unkstruct_80126B58 *)arg0)->unk60 = 0;
    }
    if (D_800B99DA & 3) {
        return;
    }
    acc = 0;
    for (i = 0; i < 3; i++) {
        acc |= func_80146608(9, ptr, 0, -30, 0, (((Unkstruct_80126B58 *)arg0)->unk50)++, 0, 12, 1);
    }
    if ((CAST_SIGN(s16, arg0, 0x60) == 0) && (acc != 0)) {
        func_80147324(0x747);
        ((Unkstruct_80126B58 *)arg0)->unk60 = 0xF;
    }
}


extern void func_80162CCC();  // K&R: 0 of 1 args (P37 rung D t4_D44)
void func_800CD178(void) {
    func_80162CCC();
}




void func_800CD198(void *a0) {

    extern void (*D_800CE220[])(void);
    D_800CE220[((Unkstruct_80126B58 *)a0)->unk2]();
}


extern void func_80146578(void);
extern void func_8001CC3C(s32, void *, s32, s32);
extern void func_80149374(s32, s32);
extern void func_800CD5EC(void *);
extern void func_800CD834(void *);
extern void func_80146DB8(void *, void *);
extern void func_80146E90(s32*, s32);
extern s32 func_80146CA0(void *);
extern void func_800CD494(void *);
extern u8 D_800CE1E8[];
extern u8 D_800CE230[];


void func_800CD1D4(s32 *s1) {
    s32 *s0;
    s32 *s2;
    s32 v0;

    s2 = (s32 *)s1[0x13];
    s0 = (s32 *)((s32 (*)(void))func_80146578)();
    CAST_WIDTH(s32, s1, 8) = (s32)s0;
    if (s0 != NULL) {
        func_8001CC3C((s32)s0, D_800CE1E8, 0x238, 0x180);
        *(u8 *)((s32)s0 + 0x27) = 0x21;
        CAST_MISALIGNED(s32, s0, 1) |= 0x40000000;
        func_80149374((s32)s2, (s32)(s1 + 1));
        func_800CD5EC(s1);
        v0 = *(s32 *)((s32)s2 + 0x20);
        *(V8_md_MAIN_044 *)((s32)s0 + 0x10) = *(V8_md_MAIN_044 *)((s32)v0 + 0x10);
        ((Unkstruct_80126B58 *)s1)->unk60 = *(u16 *)((s32)s2 + 0x100);
        ((Unkstruct_80126B58 *)s1)->unk62 = *(u16 *)((s32)s2 + 0x102);
        ((Unkstruct_80126B58 *)s1)->unk64 = *(u16 *)((s32)s2 + 0x104);
        func_800CD834(s1);
        func_80146DB8(s1, D_800CE230);
        ((void (*)(void *, s32))func_80146E90)(s1, 0x20);
        *(u16 *)((s32)s1 + 0x5E) = 0;
        func_80146CA0(s1);
    } else {
        func_800CD494(s1);
    }
}


extern u16 D_800B99DA;
extern s16 currentLocationId;
extern s32 func_80146E98(s32 a0);
extern void func_800CD57C(void *arg0);
extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
extern void func_800CD848(s32 param_1);
extern void func_800CD780(s32 param_1);
extern void func_800CD7A8(s32 a0, s32 a1);
extern void func_80163194(s32 a0, s32 a1, s32 a2, s32 a3, s32 arg4);
extern void func_80162FC0(s32 *a0);
extern void func_800CD758(s32 param_1);
extern void func_800CD63C(s32 a0, s32 a1);
extern s32 func_800CD894(void *a0);
extern void func_80146DE8(s32 *a0, s32 a1, s32 a2, s32 a3);
extern void func_80146E90(s32 *a0, s32 a1);
extern void func_80146C98(s32 *a0, s16 a1);
extern void func_80147324(s32 a0);
extern s32 func_80163408(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80163328();
extern s32 func_801632F0();
extern s32 func_801632E0();
extern s32 func_80146CA0(void *a0);

void func_800CD2EC(s32 *s1) {
    u8 buf[0x40];
    u8 *p;
    s32 s2;
    s32 v0;

    s2 = CAST_WIDTH(s32, s1, 8);
    if (func_80146E98((s32)s1) == 0) {
        if ((*(u16 *)&D_800B99DA & 3) == 0) {
            func_800CD57C(s1);
        }
        func_80146A6C(0x26, s1, ((Unkstruct_80126B58 *)s1)->unk6, ((Unkstruct_80126B58 *)s1)->unkA,
                      ((Unkstruct_80126B58 *)s1)->unkE, *(s16 *)(s2 + 0x12), 0);
        func_800CD848((s32)s1);
        func_800CD780((s32)s1);
        p = buf + 0x20;
        func_800CD7A8((s32)s1, (s32)p);
        func_80163194((s32)s1, 0, -0x1000, 0x14000, (s32)p);
        func_80162FC0(s1);
        func_800CD758((s32)s1);
        func_800CD63C((s32)s1, (s32)p);
        if (currentLocationId == 0x3067) {
            if (func_800CD894(s1) != 0) {
                func_80146DE8(s1, 0, 0xFFF40000, 0x20000);
                func_80146E90(s1, 0x10);
                *(s32 *)(s2 + 4) |= 0x50000000;
                func_80146C98(s1, 3);
                func_80147324(0x990);
                return;
            }
        }
        func_80163408((s32)s1, 0x23, 0x80, 8);
        func_80163328(s1);
        v0 = func_801632F0(s1);
        if ((v0 & 1) != 0) {
            func_801632E0(s1);
        } else if ((v0 & 6) == 0) {
            return;
        }
    }
    func_80146CA0(s1);
}


extern s16 D_800CE210[];
extern u16 D_800CE212[];
extern void func_80162CCC();  // K&R: 0 of 1 args (P37 rung D t4_D44)

void func_800CD494(void *arg0) {
    s16 idx;
    s32 a1;
    s16 tv;
    u16 tv2;
    u16 acc;

    idx = *(s16 *)((s32)arg0 + 0x5E);
    a1 = ((Unkstruct_80126B58 *)arg0)->unk20;
    tv = D_800CE210[idx * 2];
    if (tv != 0) {
        *(s16 *)((s32)arg0 + 0x5E) = idx + 1;
        tv2 = D_800CE212[idx * 2];
        acc = *(u16 *)(a1 + 0x1A) + 0x555;
        *(u16 *)(a1 + 0x28) = tv;
        *(u16 *)(a1 + 0x1A) = acc;
        *(u16 *)(a1 + 0x18) = acc;
        *(u16 *)(a1 + 0x2A) = tv2;
    } else {
        func_80162CCC();
    }
}


extern s32 func_80146E98(s32 a0);
extern void func_80162CCC();  // K&R: 0 of 1 args (P37 rung D t4_D44)
extern void func_800CD7A8(s32 a0, s32 a1);
extern void func_80163194(s32 a0, s32 a1, s32 a2, s32 a3, s32 arg4);
extern void func_80162FC0(s32 *a0);

void func_800CD508(s32 param_1) {
    s32 obj = param_1;
    s32 bufp;            /* $s0 */
    u8 dead[0x20];
    char buf[0x20];
    s32 ret;

    do { ret = ((s32 (*)(void))func_80146E98)(); } while (0);
    if (ret != 0) {
        ((void (*)(s32))func_80162CCC)(obj);
    } else {
        bufp = (s32)buf;
        ((void (*)(s32, void *))func_800CD7A8)(obj, bufp);
        ((void (*)(s32, s32, s32, s32, void *))func_80163194)(obj, 0, 0x20000, 0, bufp);
        ((void (*)(s32 *))func_80162FC0)((s32 *)obj);
    }
}


extern s32 func_801469C8(s32, void *, s32, s32, u16, s32, s32, s32);

void func_800CD57C(void *arg0) {
    if (((s32 (*)(void *, void *, s32, s32, s32, s32, s32, s32))func_801469C8)(
            (void *)0x27, arg0,
            ((Unkstruct_80126B58 *)arg0)->unk6,
            ((Unkstruct_80126B58 *)arg0)->unkA,
            ((Unkstruct_80126B58 *)arg0)->unkE,
            ((Unkstruct_80126B58 *)arg0)->unk50 & 7,
            0, 8) != 0) {
        (((Unkstruct_80126B58 *)arg0)->unk50) += 1;
    }
}


void func_800CD5EC(void *a0) {
    func_800CD758((s32)a0);
    ((Unkstruct_80126B58 *)a0)->unk66 = (((Unkstruct_80126B58 *)a0)->unk50 * 1365) & 0xFFF;
}


#include "common.h"

extern s32 func_8004787C(s32 a0);
extern s32 func_80047948(s32 a0);
extern void func_80015A2C(s32 a0, s32 a1);
extern void func_8012F14C(s32 a0, s32 a1, s32 a2);
extern void func_80015954(s32 a0, s32 a1);


void func_800CD63C(s32 a0, s32 a1)
{
    s16 sp10[3];
    s32 sp18[2];
    W8__md_MAIN_044 sp20;
    s32 t;
    s32 r;

    t = 0x20 - ((Unkstruct_80126B58 *)a0)->unk1C;
    r = func_8004787C(CAST_SIGN(s16, a0, 0x66));
    sp10[0] = ((((t << 17) >> 16) * r) / 4096);
    r = func_80047948(CAST_SIGN(s16, a0, 0x66));
    sp10[1] = ((((t << 17) >> 16) * r) / 4096);
    sp10[2] = 0;

    sp20 = *(W8__md_MAIN_044 *)a1;

    func_80015A2C(a0 + 0x58, (s32)&sp20 + 0x14);
    func_8012F14C((s32)&sp20, (s32)sp10, (s32)sp18);
    func_80015954((s32)sp18, a0 + 4);

    ((Unkstruct_80126B58 *)a0)->unk66 = (((Unkstruct_80126B58 *)a0)->unk66 + 0xE3) & 0xFFF;
}


extern void func_80015978(s32 a0, s32 *a1);

void func_800CD758(s32 param_1) {
    func_80015978(param_1 + 4, param_1 + 0x58);
}


extern void func_80015954(s32 a0, s32 a1);

void func_800CD780(s32 param_1) {
    func_80015954(param_1 + 0x58, param_1 + 4);
}


extern void func_80013F3C(s32 a0);
extern void func_800126C4(s32 a0, s32 a1);
extern void func_80012558(s32 a0, s32 a1);
extern void func_800123F0(s32 a0, s32 a1);

void func_800CD7A8(s32 a0, s32 a1) {
    s32 q = ((Unkstruct_80126B58 *)a0)->unk20;
    func_80013F3C(a1);
    func_800126C4(a1, CAST_SIGN(s16, a0, 0x60));
    func_800123F0(a1, CAST_SIGN(s16, a0, 0x64));
    func_80012558(a1, CAST_SIGN(s16, a0, 0x62));
    func_80012558(a1, *(s16 *)(q + 0x12));
    func_800126C4(a1, *(s16 *)(q + 0x10));
    func_800123F0(a1, *(s16 *)(q + 0x14));
}


void func_800CD834(void *a0) {
    s32 v0 = ((Unkstruct_80126B58 *)a0)->unk20;
    *(s16 *)(v0 + 0x18) = *(s16 *)(v0 + 0x1A) = 0;
}


extern s32 func_80012F74(s32, s32, s32, s32);

void func_800CD848(s32 param_1) {
    *(s16 *)(((Unkstruct_80126B58 *)param_1)->unk20 + 0x18) =
        *(s16 *)(((Unkstruct_80126B58 *)param_1)->unk20 + 0x1A) =
        func_80012F74(*(s16 *)(((Unkstruct_80126B58 *)param_1)->unk20 + 0x1A), 0x1000, 4, 1);
}


extern void func_80015978(s32 a0, s32 *a1);
extern s32 func_80135260(s32 a0, s32 a1, s32 a2, s32 a3);
extern u8 D_801202A0[];

typedef Unkstruct_800B5CB8 Ent_CD894;

s32 func_800CD894(void *a0) {
    u8 sp10[8];
    s32 sp18;
    s32 i;
    register s32 tag __asm__("$2");  // !FAKE: pin $2 — NEEDED DIFFERS (P36 rung B t8_tus2)
    Ent_CD894 *base = (Ent_CD894 *)D_801202A0;

    __builtin_memcpy(sp10, (u8 *)a0 + 0x44, 8);
    func_80015978((s32)a0 + 4, &sp18);
    for (i = 0; i < 0x60; i++) {
        Ent_CD894 *e = base + i;
        tag = 0x200;
        if (e->unk0 == tag) {
            s32 f58 = e->unk58;
            if (f58 != 0) {
                s32 f20 = e->unk20;
                if (f20 != 0 && func_80135260(f20, f58, sp10, &sp18) != 0) {
                    return 1;
                }
            }
        }
    }
    return 0;
}




void func_800CD948(void *a0) {

    extern void (*D_800CE24C[])(void);
    D_800CE24C[((Unkstruct_80126B58 *)a0)->unk2]();
}


extern s32 func_800D21C4(s32 a0, void *a1, s32 a2);
extern void func_80146E90(s32 *a0, s32 a1);
extern s32 func_80146C3C(void *a0);
extern s32 D_800CE240;

void func_800CD984(s32 a0) {
    s32 a2;

    a2 = func_800D21C4(a0, (s32)&D_800CE240, 0x21);
    if (a2 != 0) {
        *(s32 *)(a2 + 4) |= 0x40000000;
        ((Unkstruct_80126B58 *)a0)->unk20 = a2;
        *(s16 *)(a2 + 0x28) = 0x230;
        *(s16 *)(a2 + 0x2A) = 0x1C0;
        func_80146E90((s32 *)a0, 2);
        ((Unkstruct_80126B58 *)a0)->unk2 += 1;
    } else {
        func_80146C3C((void *)a0);
    }
}


extern s32 func_80146E98(s32 a0);
extern s32 func_80146C3C(void *a0);
void func_800CDA0C(int param_1)
{
    if (((int (*)(void))func_80146E98)() != 0) {
        ((void (*)(int))func_80146C3C)(param_1);
    }
}




void func_800CDA44(void *a0) {

    extern void (*D_800CE254[])(void);
    D_800CE254[((Unkstruct_80126B58 *)a0)->unk2]();
}


extern void *func_800D2294(s32 a0, s32 a1);
extern void func_800233CC(void *a0, u16 a1);
extern void func_80146E90(s32 *a0, s32 a1);
extern s32 func_80146C3C(void *a0);
extern s32 rand(void);

void func_800CDA80(int param_1)
{
    extern unsigned char D_800CEBF4[];
    void *ptr;
    s32 base;
    s32 r;

    base = (int)D_800CEBF4 + ((Unkstruct_80126B58 *)param_1)->unk2C * 0x40;
    ptr = func_800D2294(param_1, base);
    ((Unkstruct_80126B58 *)param_1)->unk20 = ptr;
    if (ptr != 0) {
        r = rand();
        func_800233CC(base, (r & 0x1F) | 0x20);
        *(u32 *)((int)ptr + 4) |= 0x50000000;
        *(s32 *)base = ((r & 0x3F) + 0x40) << 16;
        *(s32 *)(base + 4) = 0;
        func_80146E90((s32 *)param_1, 4);
        ((Unkstruct_80126B58 *)param_1)->unk2 += 1;
    } else {
        func_80146C3C(param_1);
    }
}


extern s32 func_80146E98(s32 a0);
extern s32 func_80146C3C(void *a0);
void func_800CDB4C(int param_1)
{
    extern unsigned char D_800CEBF4[];
    unsigned char *base;

    base = (unsigned char *)D_800CEBF4 + ((Unkstruct_80126B58 *)param_1)->unk2C * 0x40;
    base[2] = base[2] - 8;
    if (func_80146E98(param_1) != 0) {
        func_80146C3C((void *)param_1);
    }
}


#include "common.h"

extern void RotMatrixYXZ(void *a0, void *a1);
extern void ApplyMatrixSV(void *a0, void *a1, void *a2);
extern void func_800D23D0(void*);
extern void func_800D20C0(Pos800D20C0 *arg0, SVECTOR_800 *arg1, s16 arg2);
extern void func_800CDDA8();
extern s32 rand(void);
extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
extern void func_80015978(s32 a0, s32 *a1);
extern s32 func_80146C3C(void *a0);

void func_800CDBA8(s32 param_1) {
    u16 sp20[4];
    u16 sp28[4];
    s16 sp30[4];
    s32 sp38[8];
    s16 s4;
    s32 s0;
    s32 a0;
    s32 v1;

    v1 = ((Unkstruct_800CDBA8 *)param_1)->unk34;
    if (((Unkstruct_800CDBA8 *)param_1)->unk2C == 0) {
        s4 = 0;
        sp20[0] = ((Unkstruct_800CDBA8_2 *)v1)->unk6;
        sp20[1] = ((Unkstruct_800CDBA8_2 *)v1)->unkA - 0x28;
        sp20[2] = ((Unkstruct_800CDBA8_2 *)v1)->unkE;
        do {
            s0 = rand();
            sp28[0] = ((s0 & 0x7F) << 3) - 0x40;
            sp28[1] = ((u32)(s0 & 0x7F00)) >> 3;
            sp28[2] = 0;
            RotMatrixYXZ(sp28, sp38);
            sp28[1] = 0;
            sp28[0] = 0;
            sp28[2] = 0x240;
            ApplyMatrixSV(sp38, sp28, sp28);
            sp30[0] = sp20[0] + ((s16)sp28[0] >> 4);
            sp30[1] = sp20[1] + ((s16)sp28[1] >> 4);
            sp30[2] = sp20[2] + ((s16)sp28[2] >> 4);
            a0 = func_80146A6C(0x39, (void *)param_1, sp30[0], sp30[1], sp30[2],
                               (s0 & 0xFFF) | 0x1000, 0);
            if (a0 == 0) {
                break;
            }
            *(s32 *)(a0 + 0x10) = (s16)sp28[0] << 11;
            *(s32 *)(a0 + 0x14) = (s16)sp28[1] << 11;
            s4 = s4 + 1;
            *(s32 *)(a0 + 0x18) = (s16)sp28[2] << 11;
        } while (s4 < 0x12);
        func_80146C3C((void *)param_1);
    } else {
        func_80015978(param_1 + 4, (s32 *)sp20);
        ((void (*)(void *, void *, s16))func_800D20C0)(sp20, sp30, 1);
        ((void (*)(s16 *))func_800D23D0)(sp30);
        RotMatrixYXZ(sp30, (void *)(param_1 + 0x38));
        ((Unkstruct_800CDBA8 *)param_1)->unk1C = 0x18;
        ((Unkstruct_800CDBA8 *)param_1)->unk2 += 1;
        func_800CDDA8(param_1);
    }
}


extern void func_800CE004();  // K&R: 0/1 of 1 args (P37 rung D t4_D35)
void func_800CDDA8(void) {
    func_800CE004();
}




void func_800CDDC8(void *a0) {

    extern void (*D_800CE25C[])(void);
    D_800CE25C[((Unkstruct_80126B58 *)a0)->unk2]();
}


#include "common.h"

extern s32 rand(void);
extern void RotMatrixYXZ(void *a0, void *a1);
extern void ApplyMatrixSV(void *a0, void *a1, void *a2);
extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
extern s32 func_80146C3C(void *a0);
extern void func_80015978(s32 a0, s32 *a1);
extern void func_800D20C0(Pos800D20C0 *arg0, SVECTOR_800 *arg1, s16 arg2);
extern void func_800D23D0(void *a0);
extern void func_800CE004();  // K&R: 0/1 of 1 args (P37 rung D t4_D35)

void func_800CDE04(s32 param_1) {
    u16 sp20[4];
    u16 sp28[4];
    u16 sp30[4];
    s32 sp38[8];
    u32 r;
    s32 e;
    s32 q;
    s16 i;
    s32 p;

    q = ((Unkstruct_800CDE04 *)param_1)->unk34;
    if (((Unkstruct_800CDE04 *)param_1)->unk2C == 0) {
        sp20[0] = ((Unkstruct_800CDE04_2 *)q)->unk6;
        sp20[1] = ((Unkstruct_800CDE04_2 *)q)->unkA - 0x28;
        sp20[2] = ((Unkstruct_800CDE04_2 *)q)->unkE;
        for (i = 0; i < 0x12; i++) {
            r = rand();
            sp28[0] = ((r & 0x7F) << 3) - 0x40;
            sp28[1] = (r & 0x7F00) >> 3;
            sp28[2] = 0;
            RotMatrixYXZ(sp28, sp38);
            sp28[1] = 0;
            sp28[0] = 0;
            sp28[2] = 0x240;
            ApplyMatrixSV(sp38, sp28, sp28);
            sp30[0] = sp20[0] + ((s16)sp28[0] >> 4);
            sp30[1] = sp20[1] + ((s16)sp28[1] >> 4);
            sp30[2] = sp20[2] + ((s16)sp28[2] >> 4);
            e = func_80146A6C(0x3A, (void *)param_1, (s16)sp30[0], (s16)sp30[1],
                              (s16)sp30[2], (r & 0xFFF) | 0x1000, 0);
            if (e == 0) break;
            *(s32 *)(e + 0x10) = (s16)sp28[0] << 8;
            *(s32 *)(e + 0x14) = (s16)sp28[1] << 8;
            *(s32 *)(e + 0x18) = (s16)sp28[2] << 8;
        }
        func_80146C3C((void *)param_1);
    } else {
        func_80015978(param_1 + 4, (s32 *)sp20);
        func_800D20C0(sp20, sp30, 1);
        func_800D23D0(sp30);
        RotMatrixYXZ(sp30, (void *)(param_1 + 0x38));
        p = param_1;
        ((Unkstruct_800CDE04 *)p)->unk1C = 0x18;
        ((Unkstruct_800CDE04 *)p)->unk2 += 1;
        func_800CE004(p);
    }
}


extern s32 func_80169A4C(s32 a0, s32 a1);
extern void func_80015978(s32 a0, s32 *a1);
extern void func_800D22E4(s32 a0);
extern s32 func_80135168(u16 a0, u16 *a1, u16 *a2);
extern void func_80015954(s32 a0, s32 a1);
extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
extern s32 func_80146C3C(void *a0);

void func_800CE004(s32 param_1)
{
    u16 sp20[4];
    u16 sp28[4];
    s32 *p;
    s32 *q;

    ((Unkstruct_800CE004 *)param_1)->unk30 = ((Unkstruct_800CE004 *)param_1)->unk1C * 8;
    func_80169A4C(param_1, param_1 + 0x38);
    if (--((Unkstruct_800CE004 *)param_1)->unk1C == 0)
        goto L_c3c;
    p = (s32 *)(param_1 + 4);
    func_80015978((s32)p, (s32 *)sp20);
    func_800D22E4(param_1);
    q = (s32 *)sp28;
    func_80015978((s32)p, q);
    if ((s16)func_80135168(1, sp20, sp28) == 0)
        goto L_ret0;
    func_80015954((s32)q, (s32)p);
    if (*(u8 *)((s32)q + 6) != 2)
        goto L_cnt;
    if (((Unkstruct_800CE004 *)param_1)->unk2C < 0x1E01)
        goto L_c3c;
    func_80146A6C(0x11, (void *)param_1, ((Unkstruct_800CE004 *)param_1)->unk6,
                  (s16)(((Unkstruct_800CE004 *)param_1)->unkA - 8),
                  ((Unkstruct_800CE004 *)param_1)->unkE, 0, 0);
    goto L_c3c;

L_cnt:
    ((Unkstruct_800CE004 *)param_1)->unk2 += 1;
    return;
L_ret0:
    ((Unkstruct_800CE004 *)param_1)->unk14 += 0x10000;
    return;
L_c3c:
    func_80146C3C((void *)param_1);
}


void func_800CE134() {
    register s32 a0v __asm__("$4");  // !FAKE: pin $4 — NEEDED DIFFERS (P36 rung B tus10)
    s32 param_1 = a0v;

    ((Unkstruct_800CE134 *)param_1)->unk30 = ((Unkstruct_800CE134 *)param_1)->unk1C * 8;
    func_80169A4C(a0v, param_1 + 0x38);
    if (--((Unkstruct_800CE134 *)param_1)->unk1C == 0)
        func_80146C3C((void *)param_1);
}




void func_800CE188(void *a0) {

    extern void (*D_800CE268[])(void);
    D_800CE268[((Unkstruct_80126B58 *)a0)->unk2]();
}


extern void func_800CE134();
void func_800CE1C4(s32 a0) {
    func_800CE134(a0);
}


INCLUDE_RODATA("asm/md_MAIN_044/nonmatchings/md_MAIN_044", D_800CCB1C);
