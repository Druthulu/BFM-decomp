#include "common.h"

extern void func_800183E0(s32 a0);

void func_800CAE0C(void) {
    extern s32 D_800CC57C;
    extern s32 D_800CC5BC;
    extern s32 D_800CB93C;

    func_800183E0((s32)&D_800CC57C);
    func_800183E0((s32)&D_800CC5BC);
    func_800183E0((s32)&D_800CB93C);
}




void func_800CAE54(void *a0) {

    extern void (*D_800CB880[])(void);
    *(u32 *)((s32)a0 + 0x44) |= 8;
    D_800CB880[*(u8 *)((s32)a0 + 0x197)]();
}


extern s32 func_80161104(void);
extern void func_800CAEE0(u8 *a0);
void func_800CAE98(u8 *a0) {
    if (func_80161104()) {
        func_800CAEE0(a0);
        *(u8 *)(a0 + 0x197) = *(u8 *)(a0 + 0x197) + 1;
    }
}


extern void func_80154274(void *a0, void *a1);
extern void func_80154A74(s32 a0, s32 a1);
extern void func_80147324(s32 a0);
extern void func_801655E4(void *a0);
extern void func_80156648(s32 *a0);
extern void func_800CB054(void *a0);
extern void func_80019064(void *a0);

void func_800CAEE0(u8 *a0) {
    extern u8 D_800CB830[];
    extern u8 D_80062BD0;

    func_80154274(a0, D_800CB830);
    func_80154A74((s32)a0, 0x15);
    func_80147324(0x477);
    func_801655E4(a0);
    *(u8 *)(a0 + 0xBE) = 0;
    *(u8 *)(a0 + 0xBF) = 0;
    func_80156648((s32 *)a0);
    *(u8 *)(a0 + 0x1AA) = 0;
    func_800CB054(a0);
    func_80019064(&D_80062BD0);
    *(u8 *)(a0 + 0x197) = *(u8 *)(a0 + 0x197) + 1;
}


extern s32 func_80161208();
extern void func_800CB05C(s32 a0, s32 a1);
extern void func_801599A4(void *a0);
extern void func_80159B3C(void *a0);
extern s32 func_80155FD4(s32 a0, s32 a1);

void func_800CAF68(s32 a0) {
    *(u32 *)(a0 + 0x44) |= 2;
    if (func_80161208() != 0) {
        return;
    }
    if (*(u16 *)(a0 + 0xB8) & 0x2000) {
        *(u8 *)(a0 + 0xBF) += 1;
    }
    if (*(u8 *)(a0 + 0xBF) != 0) {
        func_800CB05C(a0, *(u8 *)(a0 + 0xBF));
    }
    if (*(u16 *)(a0 + 0xB8) == 0x8000) {
        func_801599A4((void *)a0);
        func_80159B3C((void *)a0);
        return;
    }
    func_80155FD4(a0, *(u8 *)(a0 + 0x1AA));
}


void func_800CB018(s32 a0) {
    extern void func_80154A74(s32 a0, s32 a1);
    *(u16 *)(a0 + 0x1BA) = 0x1000;
    *(u16 *)(a0 + 0x1B8) = 0x1000;
    *(u32 *)(a0 + 0x44) = *(u32 *)(a0 + 0x44) & ~2;
    func_80154A74(a0, 0x11);
}


void func_800CB054(void *a0) {
    *(s32 *)((s32)a0 + 0xC0) = 0;
}


void func_800CB05C(s32 a0, s32 a1) {
    s32 v; s16 x; s16 y;
    a1 &= 0xFF;
    switch (a1) {
    case 1:
        v = *(s32 *)(a0 + 0xC0) + 0x800;
        *(s32 *)(a0 + 0xC0) = v;
        if (v >= 0x2001) { *(s32 *)(a0 + 0xC0) = 0x2000; }
        x = *(u16 *)(a0 + 0x1B8) + 0x800;
        y = *(u16 *)(a0 + 0x1BA) + 0x800;
        *(u16 *)(a0 + 0x1B8) = x;
        *(u16 *)(a0 + 0x1BA) = y;
        break;
    case 2:
        v = *(s32 *)(a0 + 0xC0) - 0x800;
        *(s32 *)(a0 + 0xC0) = v;
        if (v < 0) { *(s32 *)(a0 + 0xC0) = 0; }
        x = *(u16 *)(a0 + 0x1B8) - 0x800;
        y = *(u16 *)(a0 + 0x1BA) - 0x800;
        *(u16 *)(a0 + 0x1B8) = x;
        *(u16 *)(a0 + 0x1BA) = y;
        break;
    }
}


void func_800CB0E8(void *a0) {
    extern s32 func_80146994(s32 a0, s32 a1, s32 a2, s32 a3);
    s32 v1;

    v1 = func_80146994(0x15, (s32)a0, 0, 0);
    if (v1 != 0) {
        *(s32 *)(v1 + 0x30) = *(s16 *)((u8 *)a0 + 0x36);
    }
}


#include "common.h"

void func_800CB138(s32 arg0) {

    typedef struct { s32 w[8]; } Blk20;

    extern Blk20 D_800AE620;
    extern u8 D_800CB8FC[];
    extern u8 D_800CB88C[];
    extern s32 rand(void);
    extern u8 *func_800D222C(s32 a0, s32 a1, s32 a2);
    extern void func_800D20C0(void *a0, void *a1, s32 a2);
    extern void func_800D23D0(void *a0);
    extern void RotMatrixYXZ();
    extern void RotMatrixZ(s32 a0, void *a1);
    extern void ApplyMatrixSV();
    extern void MulMatrix0(s32 a0, void *a1, s32 a2);
    extern void func_8012F14C(s32 a0, s32 a1, s32 a2);
    extern void func_80128EA8();
    extern void func_80146C3C();

    s16   sp10[4];
    s16   sp18[4];
    s16   mtx[16];
    u16   vec[4];
    s16   sv2[4];
    Blk20 blk;

    s32 ent;
    u8 *p;
    s32 m;
    s32 ang;
    register s32 ang2 __asm__("$4");

    ent = *(s32 *)(arg0 + 0x34);
    if ((*(s32 *)(arg0 + 0x2C) & 0x8000) == 0) {
        sp10[0] = *(u16 *)(ent + 6);
        sp10[1] = *(u16 *)(ent + 0xA);
        sp10[2] = *(u16 *)(ent + 0xE);
        func_800D20C0(sp10, sp18, 0);
        func_800D23D0(sp18);
        RotMatrixYXZ(sp18, arg0 + 0x38);
        *(s16 *)(arg0 + 2) = 2;
    } else {
        p = func_800D222C(arg0, (s32)D_800CB8FC, 0x1A);
        if (p != 0) {
            *(s16 *)(arg0 + 0x10) = rand() & 0xFFF;
            m = *(s32 *)(arg0 + 0x34);
            __asm__ __volatile__("" : : : "memory");
            { register Blk20 *s __asm__("$5") = &D_800AE620; s32 t0, t1, t2;
              __asm__ __volatile__("" : "=r"(s) : "0"(s));
              t0 = s->w[0]; t1 = s->w[1]; t2 = s->w[2];
              blk.w[0] = t0; blk.w[1] = t1; blk.w[2] = t2;
              t0 = s->w[3]; t1 = s->w[4]; t2 = s->w[5];
              blk.w[3] = t0; blk.w[4] = t1; blk.w[5] = t2;
              t0 = s->w[6]; t1 = s->w[7];
              blk.w[6] = t0; blk.w[7] = t1; }
            ang = *(s16 *)(arg0 + 0x10);
            { void *q = &blk; RotMatrixZ(ang, q); __asm__ __volatile__("" : "=r"(q)); }
            vec[0] = *(s32 *)(arg0 + 0x30) << 2;
            vec[1] = 0;
            vec[2] = 0x30;
            { void *q = &blk; ApplyMatrixSV(q, vec, vec); __asm__ __volatile__("" : "=r"(q)); }
            m += 0x38;
            func_8012F14C(m, (s32)vec, (s32)vec);
            *(s16 *)(arg0 + 6)   = vec[0];
            *(s16 *)(arg0 + 0xA) = vec[1];
            ang2 = ang + 0x200;
            __asm__ __volatile__("" : : : "memory");
            *(s16 *)(arg0 + 0xE) = vec[2];
            __asm__ __volatile__("" : : : "memory");
            { register Blk20 *s __asm__("$7") = &D_800AE620;
              s32 t0, t1; register s32 t2 __asm__("$6");
              __asm__ __volatile__("" : "=r"(s) : "0"(s));
              t0 = s->w[0]; t1 = s->w[1]; t2 = s->w[2];
              blk.w[0] = t0; blk.w[1] = t1; blk.w[2] = t2;
              t0 = s->w[3]; t1 = s->w[4]; t2 = s->w[5];
              blk.w[3] = t0; blk.w[4] = t1; blk.w[5] = t2;
              t0 = s->w[6]; t1 = s->w[7];
              blk.w[6] = t0; blk.w[7] = t1; }
            { void *q; __asm__ __volatile__("" : : : "memory"); q = &blk;
              RotMatrixZ(ang2, q); __asm__ __volatile__("" : "=r"(q)); }
            MulMatrix0(m, &blk, arg0 + 0x38);
            *(s32 *)(arg0 + 0x20) = (s32)p;
            *(s32 *)(p + 0x34) = arg0 + 0x38;
            *(u16 *)(p + 0x1A) = 0x2000;
            *(u16 *)(p + 0x18) = 0x2000;
            func_80128EA8(p, arg0 + 0x24, D_800CB88C);
            *(s16 *)(arg0 + 2) = *(u16 *)(arg0 + 2) + 1;
        } else {
            func_80146C3C(arg0);
        }
    }
}



extern void func_80146C3C(void);

void func_800CB370(void *arg0) {

    extern u8 D_80078EC1;
    extern void (*D_800CB908[])(void);
    if (D_80078EC1 == 0x7) {
        u16 v0 = *(u16 *)((u8 *)arg0 + 2);
        D_800CB908[v0]();
    } else {
        func_80146C3C();
    }
}


void func_800CB3CC(void *arg0) {
    extern void func_800D2318(void);
    extern void RotMatrixYXZ();
    extern void ApplyMatrixSV();
    extern void func_800D1FC8();
    extern s32 func_800D21C4();
    extern void func_80128EA8();
    extern void func_80146C3C();
    extern u8 D_800CB8FC[];
    extern u8 D_800CB8BC[];
    s16 sp10[8];
    s16 sp20[16];
    s32 p;

    func_800D2318();
    sp10[0] = *(u16 *)((s32)arg0 + 0x12);
    sp10[1] = *(u16 *)((s32)arg0 + 0x16);
    sp10[2] = 0;
    RotMatrixYXZ(sp10, sp20);
    sp10[1] = -8;
    sp10[0] = 0;
    sp10[2] = -0x10;
    ApplyMatrixSV(sp20, sp10, sp10);
    *(s32 *)((s32)arg0 + 0x4C) = (s16)(*(u16 *)((s32)arg0 + 6) = *(u16 *)((s32)arg0 + 6) + (u16)sp10[0]);
    *(s32 *)((s32)arg0 + 0x50) = (s16)(*(u16 *)((s32)arg0 + 0xA) = *(u16 *)((s32)arg0 + 0xA) + (u16)sp10[1]);
    *(s32 *)((s32)arg0 + 0x54) = (s16)(*(u16 *)((s32)arg0 + 0xE) = *(u16 *)((s32)arg0 + 0xE) + (u16)sp10[2]);
    func_800D1FC8(arg0, 6);
    p = func_800D21C4(arg0, D_800CB8FC, 0x19);
    if (p != 0) {
        *(s32 *)((s32)arg0 + 0x20) = p;
        *(u16 *)(p + 0x1A) = 0x3000;
        *(u16 *)(p + 0x18) = 0x3000;
        *(s32 *)(p + 4) |= 0x50000000;
        func_80128EA8(p, (s32)arg0 + 0x24, D_800CB8BC);
        *(u16 *)((s32)arg0 + 2) = *(u16 *)((s32)arg0 + 2) + 1;
    } else {
        ((void (*)(s32))func_80146C3C)(arg0);
    }
}



extern void func_80146C3C(void);

void func_800CB510(void *arg0) {

    extern u8 D_80078EC1;
    extern void (*D_800CB914[])(void);
    if (D_80078EC1 == 0x7) {
        u16 v0 = *(u16 *)((u8 *)arg0 + 2);
        D_800CB914[v0]();
    } else {
        func_80146C3C();
    }
}


INCLUDE_ASM("asm/md_MAIN_013/nonmatchings/md_MAIN_013", func_800CB56C);

void func_800CB6E4(void *arg0) {
    extern s32 func_80146A6C(s32, void *, s32, s32, s32, s32, s32);
    extern void func_80146C3C();
    u8 *a0 = *(u8 **)((s32)arg0 + 0x34);
    if (*(s32 *)((s32)arg0 + 0x30) == *(s16 *)(a0 + 0x36)) {
        s16 var;
        if (*(s32 *)(a0 + 0x58) < 0) {
            u8 *p = (u8 *)(*(s32 *)(a0 + 0x58) & (s32)0x8FFFFFFF);
            var = ((*(s16 *)(p + 8) + *(s16 *)(p + 0xA)) >> 1) - 0x10;
        } else {
            var = -0x30;
        }
        *(s32 *)((s32)arg0 + 0x4C) = *(s16 *)(a0 + 6);
        *(s32 *)((s32)arg0 + 0x50) = *(s16 *)(a0 + 0xA) + (s16)var;
        *(s32 *)((s32)arg0 + 0x54) = *(s16 *)(a0 + 0xE);
    }
    if (*(s32 *)((s32)arg0 + 0x1C) < 0x18 && *(u16 *)a0 != 0) {
        if (*(s32 *)((s32)arg0 + 0x1C) < 0xE) {
            func_80146A6C(0x15, arg0, 0, 0, 0, 0x8000, *(s32 *)((s32)arg0 + 0x1C));
        }
        *(s32 *)((s32)arg0 + 0x1C) = *(s32 *)((s32)arg0 + 0x1C) + 1;
    } else {
        ((void (*)(void *))func_80146C3C)(arg0);
    }
}


extern s32 func_80128ED8(s32 param_1, s32 *param_2);
extern void func_80146C3C();
void func_800CB7F0(s32 a0) {
    if (func_80128ED8((void *)*(s32 *)(a0 + 0x20), (void *)(a0 + 0x24)) != 0) {
        ((void (*)(s32))func_80146C3C)(a0);
    }
}

