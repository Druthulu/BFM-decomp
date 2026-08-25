#include "common.h"

INCLUDE_ASM("asm/md_MAIN_033/nonmatchings/md_MAIN_033", func_800CAE0C);



void func_800CAE44(void *a0) {

    extern void (*D_800CB8A4[])(void);
    *(u32 *)((s32)a0 + 0x44) |= 8;
    D_800CB8A4[*(u8 *)((s32)a0 + 0x197)]();
}


extern s32 func_80161104(void);
extern void func_800CAED0(u8 *a0);
void func_800CAE88(u8 *a0) {
    if (func_80161104()) {
        func_800CAED0(a0);
        *(u8 *)(a0 + 0x197) = *(u8 *)(a0 + 0x197) + 1;
    }
}


extern void func_80154274(s32 *a0, s32 a1);
extern void func_801655E4(s32 a0);
extern void func_80156648(s32 *a0);
extern u8 D_800CB858;

void func_800CAED0(u8 *a0) {
    func_80154274((s32 *)a0, (s32)&D_800CB858);
    func_801655E4((s32)a0);
    func_80156648((s32 *)a0);
    *(u8 *)(a0 + 0x1AA) = 1;
    *(u8 *)(a0 + 0x197) = *(u8 *)(a0 + 0x197) + 1;
}


void func_800CAF24(void *a0) {
    extern void func_801599A4(void *a0);
    extern void func_80159B3C(void *a0);
    extern s32 func_80161208();
    extern s32 func_80155FF8(s32 a0, s32 a1);
    extern s32 func_80146608(s32 a0, s32 a1, s32 a2, s32 a3, s16 a4, s32 a5, s32 a6, s32 a7, s32 a8);
    u16 flag;
    *(s32 *)((u8 *)a0 + 0x44) |= 2;
    flag = *(u16 *)((u8 *)a0 + 0xB8);
    if (!(flag & 0x4000)) {
        if (flag == 0x8000) {
            func_801599A4(a0);
            func_80159B3C(a0);
            return;
        }
    } else {
        func_80146608(0x21, (s32)a0, 0, -0x18, 0, 0, 0, 8, 1);
    }
    if (func_80161208(a0) == 0) {
        func_80155FF8((s32)a0, *(u8 *)((u8 *)a0 + 0x1AA));
    }
}


void func_800CAFD4(void *a0) {
    *(u32 *)((s32)a0 + 0x44) &= ~2;
}


void func_800CAFE8(void *arg0) {

    extern u8 D_80078EC1;
    extern void (*D_800CB8BC[])(void);
    extern void func_800CB3A4(void);
    extern void func_800CB384(void);
    if (D_80078EC1 == 0xb) {
        D_800CB8BC[*(u16 *)((s32)arg0 + 2)]();
        ((void (*)(s32))func_800CB3A4)(arg0);
    } else {
        ((void (*)(s32))func_800CB384)(arg0);
    }
}


INCLUDE_ASM("asm/md_MAIN_033/nonmatchings/md_MAIN_033", func_800CB058);

void func_800CB190(void *arg0) {
    extern void func_80147324(s32);
    extern void func_80146CA0(s32 *);
    extern s32 func_80146E98(s32);
    extern void func_8001382C(s32, void *, void *);
    extern s32 func_80012ABC(s32, s32, s32);
    extern void func_80162FC0(s32 *);
    extern u8 D_800CB8CC;

    void *p;
    void *ptr;
    s32 color;
    u16 w;
    s32 out[3];
    s32 i;
    s32 acc;

    ptr = *(void **)((u8 *)arg0 + 0x4C);
    p = *(void **)((u8 *)arg0 + 0x20);
    color = (*(s32 *)((u8 *)arg0 + 0x1C) & 1) ? 0x80 : 0x40;

    w = (*(u16 *)((u8 *)p + 0x1A) += 0x100);

    *(u8 *)((u8 *)p + 0x26) = color;
    *(u8 *)((u8 *)p + 0x25) = color;
    *(u8 *)((u8 *)p + 0x24) = color;

    *(u16 *)((u8 *)p + 0x18) = w;
    if (*(s16 *)((u8 *)p + 0x1A) >= 0x2001) {
        w = 0x2000;
        *(u16 *)((u8 *)p + 0x1A) = w;
        *(u16 *)((u8 *)p + 0x18) = w;
    }

    {
        s32 r = func_80012ABC(*(s16 *)((u8 *)p + 0x12),
                              *(s16 *)(*(void **)((u8 *)ptr + 0x20) + 0x12), 0x10);
        *(s16 *)((u8 *)p + 0x12) = r;
        func_8001382C((s16)r, (u8 *)arg0 + 0x24, out);
    }

    *(s32 *)((u8 *)arg0 + 0x10) = out[0];
    *(s32 *)((u8 *)arg0 + 0x14) = out[1];
    *(s32 *)((u8 *)arg0 + 0x18) = out[2];

    func_80162FC0((s32 *)arg0);
    if (func_80146E98((s32)arg0) == 0) {
        acc = 0;
        for (i = 0; i < 3; i++) {
            acc |= func_800CB3D8((s32)arg0, (s32)&D_800CB8CC + i * 8);
        }
        if (acc != 0) {
            func_80147324(0x8F0);
            func_80146CA0((s32 *)arg0);
        }
    } else {
        func_80146CA0((s32 *)arg0);
    }
}


void func_800CB2C8(void *arg0) {
    extern void func_80146CA0(s32 *);
    extern s32 func_80012ABC(s32, s32, s32);
    extern void func_8001382C(s32, void *, void *);
    extern void func_80162FC0(s32 *);

    void *s1;
    register void *p __asm__("$4");
    register s32 raw __asm__("$3");
    register s32 t __asm__("$2");
    s32 r;
    s32 buf[3];

    s1 = *(void **)((u8 *)arg0 + 0x20);
    p = *(void **)((u8 *)arg0 + 0x4C);
    raw = *(u8 *)((u8 *)s1 + 0x24);
    t = raw - 0x10;
    if (t < 0) {
        func_80146CA0((s32 *)arg0);
        return;
    }
    raw = t;
    __asm__("" : "=r"(raw) : "0"(raw));
    t = raw;
    *(u8 *)((u8 *)s1 + 0x24) = *(u8 *)((u8 *)s1 + 0x25) = *(u8 *)((u8 *)s1 + 0x26) = t;
    r = func_80012ABC(*(s16 *)((u8 *)s1 + 0x12),
                      *(s16 *)(*(void **)((u8 *)p + 0x20) + 0x12), 0x10);
    *(s16 *)((u8 *)s1 + 0x12) = r;
    func_8001382C((s16)r, (u8 *)arg0 + 0x24, buf);
    *(s32 *)((u8 *)arg0 + 0x10) = buf[0];
    *(s32 *)((u8 *)arg0 + 0x14) = buf[1];
    *(s32 *)((u8 *)arg0 + 0x18) = buf[2];
    func_80162FC0((s32 *)arg0);
}


extern void func_80162CCC(void);
void func_800CB384(void) {
    func_80162CCC();
}


extern void func_80049CAC(s32 arg0, s32 arg1);

void func_800CB3A4(void *arg0) {
    s32 temp_v0 = *(s32 *)((s32)arg0 + 0x20);

    if (temp_v0 != 0) {
        func_80049CAC(temp_v0 + 0x10, *(s32 *)(temp_v0 + 0x34));
    }
}


s32 func_800CB3D8(s32 arg0, s32 arg1) {
    extern void func_8012F14C(s32, s32, s32);
    extern void func_80015978(s32, s32 *);
    extern void func_80015954(s32, s32);
    extern s32 func_800CB4EC(s32);

    struct S { s32 f[8]; };
    struct S st;
    s32 out1[2];
    u16 out2[3];
    u8 *ptr;
    s32 ret;

    ptr = *(u8 **)(arg0 + 0x20);
    func_80015978(arg0 + 4, out1);
    st = *(struct S *)*(s32 *)(ptr + 0x34);
    st.f[5] = 0;
    st.f[6] = 0;
    st.f[7] = 0;
    func_8012F14C((s32)&st, arg1, (s32)out2);
    *(u16 *)(arg0 + 6) += out2[0];
    *(u16 *)(arg0 + 0xA) += out2[1];
    *(u16 *)(arg0 + 0xE) += out2[2];
    ret = func_800CB4EC(arg0);
    func_80015954((s32)out1, arg0 + 4);
    return ret;
}


INCLUDE_ASM("asm/md_MAIN_033/nonmatchings/md_MAIN_033", func_800CB4EC);


extern void func_80146C3C(void);

void func_800CB580(void *arg0) {

    extern u8 D_80078EC1;
    extern void (*D_800CB8F0[])(void);
    if (D_80078EC1 == 0xb) {
        u16 v0 = *(u16 *)((u8 *)arg0 + 2);
        D_800CB8F0[v0]();
    } else {
        func_80146C3C();
    }
}


extern void func_801465C0(void);
extern void func_8001CD50(s32 a0, s32 a1);
extern void func_800233CC(void *a0, u16 a1);
extern void func_80146C3C(void);

void func_800CB5DC(void *arg0) {

    extern u8 D_800CBA88;
    extern u8 D_800CBA89;
    extern u8 D_800CBA8A;
    extern u8 D_800CBA8C;
    extern u8 D_800CBA8D;
    extern u8 D_800CBA8E;
    void *s3;
    void *s1;
    void *s0;
    u16 v1;

    s3 = *(void **)((u8 *)arg0 + 0x34);
    s1 = ((void *(*)(void))func_801465C0)();
    *(void **)((u8 *)arg0 + 0x20) = s1;

    if (s1 != NULL) {
        s0 = &D_800CBA88;
        func_8001CD50((s32)s1, (s32)s0);
        func_800233CC(s0, 0x20);

        *(u8 *)s0 = 0x20;
        D_800CBA89 = 0x40;
        D_800CBA8A = 0x80;
        D_800CBA8E = 0;
        D_800CBA8D = 0;
        D_800CBA8C = 0;

        *(s32 *)((u8 *)s1 + 4) |= 0x50000000;

        v1 = *(u16 *)(*(void **)((u8 *)s3 + 0x20) + 0x12);
        *(s16 *)((u8 *)s1 + 0x10) = 0x400;
        *(s32 *)((u8 *)s1 + 0x34) = (s32)((u8 *)arg0 + 0x38);
        *(s16 *)((u8 *)s1 + 0x12) = v1;

        *(u16 *)((u8 *)arg0 + 2) = *(u16 *)((u8 *)arg0 + 2) + 1;
    } else {
        ((void (*)(void *))func_80146C3C)(arg0);
    }
}


INCLUDE_ASM("asm/md_MAIN_033/nonmatchings/md_MAIN_033", func_800CB6D4);

extern void func_80146C3C(void);

void func_800CB720(void *arg0) {
    u8 *p = *(u8 **)((u8 *)arg0 + 0x20);
    s16 x = *(u16 *)(p + 0x1A) - 0x300;
    *(u16 *)(p + 0x1A) = x;
    *(u16 *)(p + 0x18) = x;
    if (x < 0) {
        ((void (*)(void *))func_80146C3C)(arg0);
    }
}


void func_800CB76C(void *arg0) {
    extern void func_80049CAC(s32 a0, s32 a1);
    extern void func_800139C8(s32 a0, void *a1, void *a2);
    extern u8 D_800CB8FC[];
    s32 s2 = (s32)arg0;
    s32 s3;
    s32 s0;
    s32 s1;
    u16 sp10[3];
    s32 v;
    s32 q;

    s3 = *(s32 *)(s2 + 0x34);
    s0 = *(s32 *)(s2 + 0x20);
    s1 = *(s32 *)(s3 + 0x20);
    if (s0 != 0) {
        *(u16 *)(s0 + 0x12) = *(u16 *)(s1 + 0x12);
        func_80049CAC((s32)s0 + 0x10, *(s32 *)(s0 + 0x34));
        v = *(s16 *)(s1 + 0x1A);
        q = (v * 180) / 100;
        *(s16 *)(s0 + 0x1A) = q;
        *(s16 *)(s0 + 0x18) = q;
        func_800139C8(*(s16 *)(s0 + 0x12), D_800CB8FC, (s32)&sp10[0]);
        *(u16 *)(s2 + 6) = *(u16 *)(s3 + 6) + sp10[0];
        *(u16 *)(s2 + 0xA) = *(u16 *)(s3 + 0xA) + sp10[1];
        *(u16 *)(s2 + 0xE) = *(u16 *)(s3 + 0xE) + sp10[2];
    }
}

