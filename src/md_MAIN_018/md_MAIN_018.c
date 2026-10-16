#include "common.h"

extern void func_800183E0(s32 a0);

extern u8 D_800CB680[];
extern u8 D_800CB6C0[];
extern u8 D_800CB700[];
extern u8 D_800CB740[];
extern u8 D_800CB780[];
extern u8 D_800CB7C0[];
extern u8 D_800CB800[];
extern u8 D_800CB840[];
extern u8 D_800CB640[];

void func_800CAE0C(void) {
    func_800183E0((s32)D_800CB680);
    func_800183E0((s32)D_800CB6C0);
    func_800183E0((s32)D_800CB700);
    func_800183E0((s32)D_800CB740);
    func_800183E0((s32)D_800CB780);
    func_800183E0((s32)D_800CB7C0);
    func_800183E0((s32)D_800CB800);
    func_800183E0((s32)D_800CB840);
    func_800183E0((s32)D_800CB640);
}




void func_800CAEB4(void *a0) {

    extern void (*D_800CB5E8[])(void);
    ((Unkstruct_800CAE34 *)a0)->unk44 |= 8;
    D_800CB5E8[((Unkstruct_800CAE34 *)a0)->unk197]();
}


extern void func_800CAF30(u8 *a0);
void func_800CAEF8(void *a0) {
    func_800CAF30(a0);
    ((Unkstruct_80126B58 *)a0)->unk197 += 1;
}


extern s32 func_80165910(void);
extern void func_801655E4(s32 a0);
extern void func_800CAFB4(void *arg);

void func_800CAF30(u8 *a0) {
    if (func_80165910() == 0) {
        func_801655E4((s32)a0);
    }
    func_800CAFB4(a0);
    ((Unkstruct_80126B58 *)a0)->unk197 = ((Unkstruct_80126B58 *)a0)->unk197 + 1;
}


extern s32 D_80078EC8;
extern s32 func_80165A20(s32 a0);

void func_800CAF80(void *a0) {
    if (D_80078EC8 == 0) {
        func_80165A20((s32)a0);
    }
}


void func_800CAFAC(void) {
}

void func_800CAFB4(void *arg) {
    extern s32 func_80146994(s32 a0, s32 a1, s32 a2, s32 a3);
    func_80146994(0x23, (s32)arg, 0x8000, 0);
}


extern u8 D_800CB860[];
extern u8 D_800CB861;
extern u8 D_800CB862;
extern u8 D_800CB864;
extern u8 D_800CB865;
extern u8 D_800CB866;
extern s16 D_800CB5F4;
extern s16 D_800CB5F6;
extern u8 D_800D387C[];
extern void func_800233CC(void *, u16);
extern void func_801465C0(void);
extern void func_80146C3C(u8 *a0);
extern void func_8001CC3C(s32, void *, s32, s32);
extern void func_8001CD9C(s32, void *);

void func_800CAFE0(s32 param_1) {
    s32 pad[2];
    s32 node;
    s32 node2;
    u32 hw;
    u32 sh;
    s32 sext;
    s32 save;

    if (*(u32 *)(param_1 + 0x2C) & 0x8000) {
        D_800CB861 = 0xA0;
        D_800CB860[0] = 0xA0;
        D_800CB862 = 0x70;
        D_800CB866 = 0;
        D_800CB865 = 0;
        D_800CB864 = 0;
        func_800233CC(D_800CB860, 0x1E);
        *(u16 *)(param_1 + 0x12) = 0x1C0;
        *(u16 *)(param_1 + 2) = 1;
        return;
    }
    hw = *(u32 *)(param_1 + 0x30);
    sh = hw >> 15;
    node = ((s32 (*)(void))func_801465C0)();
    if (node == 0) {
        ((void (*)(s32))func_80146C3C)(param_1);
        return;
    }
    sext = (s32)(sh << 16);
    func_8001CC3C(node, D_800D387C,
                  *(s16 *)((s32)&D_800CB5F4 + (sext >> 15)),
                  *(s16 *)((s32)&D_800CB5F6 + (sext >> 15)));
    ((Unkstruct_800CAFE0_2 *)node)->unk1A = 0x2000;
    ((Unkstruct_800CAFE0_2 *)node)->unk18 = 0x2000;
    ((Unkstruct_800CAFE0_2 *)node)->unk27 = (sext >> 17) + 0x19;
    ((Unkstruct_800CAFE0_2 *)node)->unk4 |= 0xC0000000;
    save = *(u16 *)(param_1 + 0x30);
    *(s32 *)(param_1 + 0x20) = node;
    *(u16 *)(param_1 + 2) = 2;
    *(u32 *)(param_1 + 0x30) = save;
    node2 = ((s32 (*)(void))func_801465C0)();
    if (node2 == 0) {
        ((void (*)(s32))func_80146C3C)(param_1);
        return;
    }
    *(s32 *)(param_1 + 0x34) = node2;
    func_8001CD9C(node2, D_800CB860);
    ((Unkstruct_800CAFE0 *)node2)->unk2C = 0xC001;
    ((Unkstruct_800CAFE0 *)node2)->unk4 |= 0xD0000000;
    ((Unkstruct_800CAFE0 *)node2)->unk8 = *(u16 *)(param_1 + 6);
    ((Unkstruct_800CAFE0 *)node2)->unkA = *(u16 *)(param_1 + 0xA);
    ((Unkstruct_800CAFE0 *)node2)->unkC = *(u16 *)(param_1 + 0xE);
}


void func_800CB168(void *arg0) {
    extern u8 D_80078EC1;
    extern s32 rand(void);
    extern s32 func_80146AB4(s16 a0, s32 a1, s16 a2, s16 a3, u16 a4, s32 a5, s32 a6);
    extern void func_80146C3C(u8 *a0);
    extern void func_8002D4C8(s32 a0, s32 a1);
    extern u16 D_80126BC8;
    extern u16 D_80126BCA;
    extern u16 D_80126BCC;
    extern u16 D_800B99DA;

    u32 *obj = (u32 *)arg0;
    s16 *pb;
    s32 state;
    s32 r;
    s32 ret;
    u16 v2a;

    if (D_80078EC1 == 3) {
        state = CAST_ALIAS(s32, obj, 12);
        if (state == 1) {
            goto L1DC;
        }
        if (state == 0) {
            goto L1B0;
        }
        if (state == 2) {
            goto L270;
        }
        goto L288;

L1B0:
        r = rand();
        ((Unkstruct_800CB168 *)obj)->unk1A = r & 0xFFF;
        ((Unkstruct_800CB168 *)obj)->unk2A = (r & 1) + 2;
        CAST_ALIAS(s32, obj, 12) = CAST_ALIAS(s32, obj, 12) + 1;
        goto L288;

L1DC:
        if ((CAST_MISALIGNED(s32, obj, 7))++ & 3) {
            goto L288;
        }
        ret = func_80146AB4(0x23, (s32)arg0, 0, 0, 0,
                            ((Unkstruct_800CB168 *)obj)->unk12,
                            CAST_SIGN(s16, (s32)obj, 0x1A) |
                                (((((Unkstruct_800CB168 *)obj)->unk28)++ & 7) << 16));
        if (ret == 0) {
            ((Unkstruct_800CB168 *)obj)->unk2A = 0;
        }
        v2a = ((Unkstruct_800CB168 *)obj)->unk2A - 1;
        ((Unkstruct_800CB168 *)obj)->unk2A = v2a;
        if ((s16)v2a > 0) {
            goto L288;
        }
        CAST_MISALIGNED(s32, obj, 7) = 0x10;
        CAST_ALIAS(s32, obj, 12) = CAST_ALIAS(s32, obj, 12) + 1;
        goto L288;

L270:
        if (--CAST_MISALIGNED(s32, obj, 7) == 0) {
            CAST_ALIAS(s32, obj, 12) = 0;
        }

L288:
        pb = (s16 *)&D_80126BCC;
        if (*pb >= 0x1001) {
            D_80126BC8 = *pb = *pb - 0xE0;
            D_80126BCA = D_80126BCA + 0x38;
        }
        if ((D_800B99DA & 0xF) == 0) {
            func_8002D4C8(0x5FB, 0);
        }
    } else {
        D_80126BC8 = D_80126BCA = D_80126BCC = 0x1000;
        ((void (*)(s32))func_80146C3C)((s32)arg0);
    }
}


void func_800CB328(void *a0) {

    extern u8 D_80078EC1;
    extern s32 func_80146A6C(s32, void *, s32, s32, s32, s32, s32);
    extern void RotMatrixY(s32, void *);
    extern void func_8012F14C(s32, s32, s32);
    extern void func_80016714(s8 *, s32);
    extern void func_80146C3C(u8 *a0);
    extern s16 D_80126B5E;
    extern s16 D_80126B62;
    extern s16 D_80126B66;
    extern u16 D_80126BC8;
    extern u16 D_80126BCA;
    extern u16 D_80126BCC;
    extern Mtx32b D_800AE620;

    void *obj = a0;
    register void *pf20 __asm__("$20");  // !FAKE: pin $20 — NEEDED DIFFERS (P36 rung B t8_tus2)
    void *pf34;
    Svec3 rot;
    Mtx32b m;
    u32 mask;
    s32 cnt;
    u16 t18;

    pf20 = ((Unkstruct_800CB328 *)obj)->unk20;
    pf34 = ((Unkstruct_800CB328 *)obj)->unk34;

    if (D_80078EC1 == 3) {
        cnt = ((Unkstruct_800CB328 *)obj)->unk2C - 4;
        ((Unkstruct_800CB328 *)obj)->unk2C = cnt;
        if ((u32)cnt < 0x1C) {
            func_80146A6C(3, obj,
                          CAST_SIGN(s16, (s32)obj, 0x6),
                          CAST_SIGN(s16, (s32)obj, 0xA),
                          CAST_SIGN(s16, (s32)obj, 0xE),
                          (s32)0xCCCFFFC,
                          (s32)0xE0009C00);
            D_80126BC8 = D_80126BCC = D_80126BCC + 0x400;
            D_80126BCA = D_80126BCA - 0x100;
        } else {
            mask = 0x7FFFFFFF;
            t18 = ((Unkstruct_800CB328_3 *)pf20)->unk1A;
            ((Unkstruct_800CB328_3 *)pf20)->unk4 &= mask;
            t18 = t18 - 0x2C;
            ((Unkstruct_800CB328_3 *)pf20)->unk1A = t18;
            ((Unkstruct_800CB328_3 *)pf20)->unk18 = t18;

            ((Unkstruct_800CB328 *)obj)->unk30 +=
                0xA00000u / (((Unkstruct_800CB328 *)obj)->unk2C * 804);

            m = D_800AE620;
            RotMatrixY(((Unkstruct_800CB328 *)obj)->unk30, &m);
            rot.vx = 0;
            rot.vy = -(CAST_SIGN(u32, (s32)obj, 0x2C) >> 1);
            rot.vz = ((Unkstruct_800CB328 *)obj)->unk2C;
            m.t[0] = D_80126B5E;
            m.t[1] = D_80126B62 - 0x1C;
            m.t[2] = D_80126B66;
            func_8012F14C((s32)&m, (s32)&rot, (s32)&rot);

            CAST_ALIAS(u16, (s32)obj, 0x6) = *(u16 *)&rot.vx;
            CAST_ALIAS(u16, (s32)obj, 0xA) = *(u16 *)&rot.vy;
            ((Unkstruct_800CB328 *)obj)->unkE = *(u16 *)&rot.vz;

            ((Unkstruct_800CB328_2 *)pf34)->unk4 &= mask;
            ((Unkstruct_800CB328_2 *)pf34)->unk18 = ((Unkstruct_800CB328_3 *)pf20)->unk18;
            ((Unkstruct_800CB328_2 *)pf34)->unk1A = ((Unkstruct_800CB328_3 *)pf20)->unk1A;
            ((Unkstruct_800CB328_2 *)pf34)->unk8 = ((Unkstruct_800CB328 *)obj)->unk6;
            ((Unkstruct_800CB328_2 *)pf34)->unkA = ((Unkstruct_800CB328 *)obj)->unkA;
            ((Unkstruct_800CB328_2 *)pf34)->unkC = ((Unkstruct_800CB328 *)obj)->unkE;
            return;
        }
    }
    if (pf34 != 0) {
        func_80016714((s8 *)pf34, 0x38);
    }
    ((void (*)(s32))func_80146C3C)((s32)obj);
}




void func_800CB5AC(void *a0) {

    extern void (*D_800CB614[])(void);
    D_800CB614[((Unkstruct_80126B58 *)a0)->unk2]();
}

