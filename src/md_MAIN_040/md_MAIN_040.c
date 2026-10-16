#include "common.h"

#include "common.h"

extern void func_800183E0(s32 a0);

void func_800CAE0C(void) {
    extern s32 D_800CB9F4;
    extern s32 D_800CB9B4;

    func_800183E0((s32)&D_800CB9F4);
    func_800183E0((s32)&D_800CB9B4);
}




void func_800CAE44(void *a0) {

    extern void (*D_800CB8C8[])(void);
    ((Unkstruct_800CAE34 *)a0)->unk44 |= 8;
    D_800CB8C8[((Unkstruct_800CAE34 *)a0)->unk197]();
}


extern s32 func_80161104(void);
extern void func_800CAED0(u8 *a0);
#include "../shared/slot_800CAE08/func_800CAE88__34360208.h"


extern void func_80154274(s32 *a0, s32 a1);
extern void func_801655E4(void *a0);
extern M2C_UNK D_800D57F4;

void func_800CAED0(u8 *a0) {
    func_80154274((s32 *)a0, (s32)&D_800D57F4);
    func_801655E4(a0);
    ((Unkstruct_80126B58 *)a0)->unk197 = ((Unkstruct_80126B58 *)a0)->unk197 + 1;
}


#include "common.h"

extern void func_801599A4(void *a0);
extern void func_80159B3C(void *a0);
extern void func_801466F0(s32 a0, s32 a1, s32 a2, s32 a3,
                          s32 a4, s32 a5, s32 a6, s32 a7);
extern s32 func_80161208();  /* canonical no-proto */

void func_800CAF18(void *a0) {
    u16 flag;

    flag = ((Unkstruct_80126B58 *)a0)->unkB8;
    if (flag == 0x8000) {
        func_801599A4(a0);
        func_80159B3C(a0);
    } else {
        if (flag & 0x4000) {
            func_801466F0(0x20, (s32)a0, 0, -0x40, 0, 0, 0, 0);
        }
        if (func_80161208(a0) == 0) {
            ((Unkstruct_80126B58 *)a0)->unk44 |= 2;
        }
    }
}


void func_800CAFB0(void *a0) {
    ((Unkstruct_800CAF88 *)a0)->unk44 &= ~2;
}


#include "common.h"

extern u8 D_80078EC1;
extern void (*D_800CB8D4[])(void);
extern void func_800CB3BC(void);

void func_800CAFC4(s32 a0) {
    u16 index;
    s16 value;

    if (D_80078EC1 == 0x1D) {
        index = *(u16 *)(a0 + 2);
        D_800CB8D4[index]();

        value = *(s16 *)(a0 + 0xA);
        if (value < 0x401) {
            return;
        }
        ((void (*)(s32))func_800CB3BC)(a0);
    } else {
        ((void (*)(s32))func_800CB3BC)(a0);
    }
}


void func_800CB038(void *a0) {
    extern s32 D_800CBD74;
    extern void func_8014659C(void);
    extern void func_8001C214(s32 a0, s32 a1);
    extern void func_80149374(s32 a0, s32 a1);
    extern void func_80146DE8(s32 *a0, s32 a1, s32 a2, s32 a3);
    extern void func_80146E90(s32 *a0, s32 a1);
    extern void func_80147324(s32 a0);
    extern void func_80146CA0(void *a0);
    extern void func_800CB3BC(void);

    void *s2 = *(void **)((s32)a0 + 0x4C);
    s32 s1 = ((s32 (*)(void))func_8014659C)();
    ((Unkstruct_80126B58 *)a0)->unk20 = s1;
    if (s1 != 0) {
        func_8001C214(s1, (s32)&D_800CBD74);
        *(u16 *)(s1 + 0x12) = *(u16 *)(((Unkstruct_80126B58 *)s2)->unk20 + 0x12);
        func_80149374((s32)s2, (s32)a0 + 4);
        func_80146DE8((s32 *)a0, 0, -0xC0000, -0x100000);
        func_80146E90((s32 *)a0, 100);
        memcpy((void *)((s32)a0 + 0x58), (void *)(s1 + 0x10), 8);
        ((Unkstruct_80126B58 *)a0)->unk60 = 2;
        func_80147324(0x8F3);
        func_80146CA0(a0);
    } else {
        ((void (*)(s32))func_800CB3BC)(a0);
    }
}


void func_800CB114(void *a0) {
    extern void func_80162FF4(s32 a0, s32 a1, s32 a2, s32 a3);
    extern void func_80162FC0(s32 a0);
    extern s32 func_80146E98(s32 a0);
    extern void func_800CB3BC(void);
    extern s32 func_80163950(s32 a0);
    extern s32 func_801638A0(s32 a0, s32 *a1);
    extern void func_80146E90(s32 *a0, s32 a1);
    extern void func_80147324(s32 a0);
    extern void func_80146CA0(void *a0);
    extern void func_80163408(s32 a0, s32 a1, s32 a2, s32 a3);
    extern void func_80163328(s32 a0);
    extern s32 func_801632F0(s32 a0);
    extern void func_80162D28(s32 a0);

    s32 vec[2];
    s32 save[2];
    void *obj;
    s32 f;
    s32 w;

    obj = CAST_SIGN(void *, (s32)a0, 0x20);
    memcpy(save, (void *)(obj + 0x10), 8);
    memcpy((void *)(obj + 0x10), (void *)((s32)a0 + 0x58), 8);
    func_80162FF4((s32)a0, 0, 0x20000, 0);
    func_80162FC0((s32)a0);
    *(u16 *)save = *(u16 *)save + 0x71;
    *(u16 *)((s32)save + 4) = *(u16 *)((s32)save + 4) + 0x71;
    memcpy((void *)(obj + 0x10), save, 8);
    if (func_80146E98((s32)a0) != 0) {
        ((void (*)(s32))func_800CB3BC)(a0);
        return;
    }
    f = (func_80163950((s32)a0) != 0) << 13;
    f |= func_801638A0((s32)a0, vec);
    if (f == 0) {
        goto L274;
    }
    if ((f & 0x6000) == 0) {
        goto L250;
    }
    w = ((Unkstruct_80126B58 *)a0)->unk60;
    w = w - 1;
    ((Unkstruct_80126B58 *)a0)->unk60 = w;
    if ((s16)w == -1) {
        goto L250;
    }
    {
        s32 v = ((Unkstruct_80126B58 *)a0)->unk28;
        ((Unkstruct_80126B58 *)a0)->unk28 = -(v / 2);
    }
    goto L274;
L250:
    func_80146E90((s32 *)a0, 8);
    func_80147324(0x8E7);
    func_80146CA0(a0);
    return;
L274:
    func_80163408((s32)a0, 0x2A, 0, 0x20);
    func_80163328((s32)a0);
    f = func_801632F0((s32)a0);
    if (f == 2) {
        goto L2E4;
    }
    if ((u32)f < 3) {
        if (f == 1) {
            goto L2CC;
        }
        goto L2E4;
    }
    if (f != 4) {
        goto L2E4;
    }
L2CC:
    func_80146E90((s32 *)a0, 8);
    func_80147324(0x8E7);
    func_80146CA0(a0);
L2E4:
    func_80162D28((s32)a0);
}


void func_800CB304(void *a0) {
    extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
    extern s32 func_80146E98(s32 a0);
    extern void func_80146CA0(void *a0);
    extern void func_800CB3DC(void *a0);
    s32 pad[2];
    s32 var_s2;
    s32 i;

    if (pad == NULL) {}
    var_s2 = ((Unkstruct_80126B58 *)a0)->unk20;
    for (i = 0; i < 6; i++) {
        func_80146A6C(0x4D, a0, ((Unkstruct_80126B58 *)a0)->unk6, ((Unkstruct_80126B58 *)a0)->unkA,
                      ((Unkstruct_80126B58 *)a0)->unkE, i, 1);
    }
    if (func_80146E98((s32)a0) != 0) {
        func_80146CA0(a0);
    } else {
        u16 var_v0;
        var_v0 = *(u16 *)(var_s2 + 0x1C);
        var_v0 = var_v0 - 0x80;
        *(u16 *)(var_s2 + 0x1C) = var_v0;
        *(u16 *)(var_s2 + 0x1A) = var_v0;
        *(u16 *)(var_s2 + 0x18) = var_v0;
        func_800CB3DC(a0);
    }
}


extern void func_80162CCC();  // K&R: 0 of 1 args (P37 rung D t4_D58)
void func_800CB3BC(void) {
    func_80162CCC();
}


#include "common.h"

extern u8 D_801202A0[];
extern s32 func_8014C308(s32 a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8014C278(s32 a0, s32 a1, s32 a2);
extern void func_80015978(s32 a0, s32 *a1);
extern s32 func_8014C3A4(void *a0, s32 a1, s32 a2, s32 a3);

void func_800CB3DC(s32 a0) {
    u8 *p;
    s16 buf[4];
    p = D_801202A0;
    if (p < p + 0x6480) {
        do {
            if (func_8014C308(a0, (s32)p, 0x2A, 0x20) != 0) {
                if (func_8014C278(a0, (s32)p, 0x80) != 0) {
                    func_80015978((s32)(p + 4), (s32 *)buf);
                    buf[3] = 0;
                    func_8014C3A4((void *)a0, (s32)p, 0x2A, (s32)buf);
                }
            }
            p += 0x10C;
        } while (p < D_801202A0 + 0x6480);
    }
}



extern void func_80146C3C();  // K&R: 0 of 1 args (P37 rung D t4_D58)

void func_800CB488(void *arg0) {

    extern u8 D_80078EC1;
    extern void (*D_800CB948[])(void);
    if (D_80078EC1 == 0x1d) {
        u16 v0 = *(u16 *)((u8 *)arg0 + 2);
        D_800CB948[v0]();
    } else {
        func_80146C3C();
    }
}


    /* 8B, align 2 -> lwl/lwr+swl/swr copy */
  /* 0x20, align 4 */
     /* 0x10, align 4 -> plain lw/sw copy */

extern void func_801465C0(void);
extern void func_8001CC3C(s32 a0, void *a1, s32 a2, s32 a3);
extern void func_80128EA8(s32 a0, s32 a1, s32 a2);
extern void func_80049CAC(s32 a0, s32 a1);
extern void func_800484EC(s32 a0, s32 a1, s32 a2);
extern void func_80146E90(s32 *a0, s32 a1);
extern void func_80146C3C();  // K&R: 0 of 1 args (P37 rung D t4_D58)
extern int rand(void);

extern u8 D_800CB8EC[];
extern u8 D_800CB8F8[];
extern SV_800CB4E4 D_800CB954[];
extern V32_800CB4E4 D_800CB984;

void func_800CB4E4(s32 param_1) {
    SV_800CB4E4 rot;
    MTX_800CB4E4 m;
    V32_800CB4E4 vel;
    s32 obj;
    s32 node;

    obj = ((s32 (*)(void))func_801465C0)();
    ((Unkstruct_80126B58 *)param_1)->unk20 = obj;

    if (((Unkstruct_80126B58 *)param_1)->unk20 != 0) {
        func_8001CC3C(obj, D_800CB8EC, 0, 0);
        node = obj;
        *(u8 *)(node + 0x27) = 0x90;
        *(u16 *)(node + 0x18) = *(u16 *)(node + 0x1a) = 0x3000;
        *(s32 *)(node + 0x4) |= 0x50000000;
        func_80128EA8(node, param_1 + 0x24, (s32)D_800CB8F8);

        vel = D_800CB984;
        rot = D_800CB954[((Unkstruct_80126B58 *)param_1)->unk2C];

        if (((Unkstruct_80126B58 *)param_1)->unk30 != 0) {
            rot.vx += ((rand() & 0x3f) << 4) - 0x200;
            rot.vy += ((rand() & 0x3f) << 4) - 0x200;
            rot.vz += ((rand() & 0x3f) << 4) - 0x200;
            vel.vx = ((rand() & 0x1f) - 0x10) * 3 << 15;
            vel.vy = ((rand() & 0x1f) - 0x10) * 3 << 15;
            vel.vz = ((rand() & 0x1f) - 0x10) * 3 << 15;
        }

        func_80049CAC((s32)&rot, (s32)&m);
        func_800484EC((s32)&m, (s32)&vel, (s32)&vel);

        ((Unkstruct_80126B58 *)param_1)->unk10 = vel.vx;
        ((Unkstruct_80126B58 *)param_1)->unk14 = vel.vy;
        ((Unkstruct_80126B58 *)param_1)->unk18 = vel.vz;

        func_80146E90((s32 *)param_1, 4);
        ((Unkstruct_80126B58 *)param_1)->unk2 = ((Unkstruct_80126B58 *)param_1)->unk2 + 1;
    } else {
        ((void (*)(s32))func_80146C3C)(param_1);
    }
}


extern s32 func_80128ED8(s32 param_1, s32 *param_2);
extern void func_800CB840(s32 param_1);
extern void func_800CB8A8(void*, s16);
extern s32 func_80146E98(s32 param_1);
extern void func_80146E90(s32 *param_1, s32 param_2);

void func_800CB710(s32 param_1) {
    s32 node;

    node = ((Unkstruct_80126B58 *)param_1)->unk20;
    func_80128ED8(node, (s32 *)(param_1 + 0x24));
    *(u8 *)(node + 0x27) = CAST_WIDTH(u8, param_1, 0x28) - 0x70;
    func_800CB840(param_1);
    ((void (*)(s32, s32))func_800CB8A8)(param_1, 0x30);
    if (func_80146E98(param_1) != 0) {
        ((Unkstruct_80126B58 *)param_1)->unk10 = ((Unkstruct_80126B58 *)param_1)->unk10 >> 2;
        ((Unkstruct_80126B58 *)param_1)->unk14 = ((Unkstruct_80126B58 *)param_1)->unk14 >> 2;
        ((Unkstruct_80126B58 *)param_1)->unk18 = ((Unkstruct_80126B58 *)param_1)->unk18 >> 2;
        func_80146E90((s32 *)param_1, 8);
        ((Unkstruct_80126B58 *)param_1)->unk2 = ((Unkstruct_80126B58 *)param_1)->unk2 + 1;
    }
}


extern s32 func_80128ED8(s32 param_1, s32 *param_2);
extern void func_800CB840(s32 param_1);
extern void func_800CB8A8(void*, s16);
extern s32 func_80146E98(s32 param_1);
extern void func_80146C3C();  // K&R: 0 of 1 args (P37 rung D t4_D58)
extern void func_800CB874(s32 param_1);

void func_800CB7B8(s32 param_1) {
    s32 p;
    s32 node;

    p = param_1;
    node = ((Unkstruct_800CB7B8 *)p)->unk20;
    func_800CB874(param_1);
    func_80128ED8(node, (s32 *)(p + 0x24));
    *(u8 *)(node + 0x27) = ((Unkstruct_800CB7B8 *)p)->unk28 - 0x70;
    ((void (*)(s32, s32))func_800CB8A8)((void *)p, 0x40);
    ((Unkstruct_800CB7B8 *)p)->unk14 -= 0x4000;
    func_800CB840(p);
    if (func_80146E98(p) != 0) {
        ((void (*)(s32))func_80146C3C)(p);
    }
}


void func_800CB840(s32 param_1) {
    CAST_WIDTH(s32, param_1, 0x4) += ((Unkstruct_80126B58 *)param_1)->unk10;
    CAST_WIDTH(s32, param_1, 0x8) += ((Unkstruct_80126B58 *)param_1)->unk14;
    CAST_WIDTH(s32, param_1, 0xC) += ((Unkstruct_80126B58 *)param_1)->unk18;
}


void func_800CB874(s32 arg0)
{
    u8 *p;
    s16 t;
    s16 d;
    u8 x;

    p = CAST_SIGN(u8 *, arg0, 0x20);
    t = p[0x24];
    d = t - 4;
    if (d < 0)
        t = 0;
    else
        t = d;
    x = t;
    p[0x26] = x;
    p[0x25] = x;
    p[0x24] = x;
}


void func_800CB8A8(void *arg0, s16 arg1) {
    u16 *ptr = *(u16 **)((s32)arg0 + 0x20);
    ptr[13] = ptr[13] - arg1;
    ptr[12] = ptr[13];
}

