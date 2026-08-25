#include "common.h"

extern s32 func_800183E0(s32 *a0);
void func_800CAE0C(void) {

    extern s32 D_800CBB88;
    func_800183E0(&D_800CBB88);
}




void func_800CAE34(void *a0) {

    extern void (*D_800CBB24[])(void);
    *(u32 *)((s32)a0 + 0x44) |= 8;
    D_800CBB24[*(u8 *)((s32)a0 + 0x197)]();
}


extern s32 func_80161104(void);
extern void func_800CAEC0(u8 *a0);
void func_800CAE78(u8 *a0) {
    if (func_80161104()) {
        func_800CAEC0(a0);
        *(u8 *)(a0 + 0x197) = *(u8 *)(a0 + 0x197) + 1;
    }
}


INCLUDE_ASM("asm/md_MAIN_015/nonmatchings/md_MAIN_015", func_800CAEC0);

extern s32 func_80161208();
extern u16 func_801487F4(s32 *a0);
extern void func_80154274(s32 *a0, s32 a1);
extern s32 D_800CBB00[];
extern s32 D_800CBAE0[];

void func_800CAF0C(s32 *a0) {
    if (func_80161208() == 0) {
        if (*(u16 *)((u8 *)a0 + 0xB8) == 0x8000) {
            if (func_801487F4(a0) & 0x20) {
                func_80154274(a0, (s32)D_800CBB00);
                *(u8 *)((s32)a0 + 0x197) += 1;
            } else {
                func_80154274(a0, (s32)D_800CBAE0);
                *(u8 *)((s32)a0 + 0x197) += 2;
            }
        }
    }
}


INCLUDE_ASM("asm/md_MAIN_015/nonmatchings/md_MAIN_015", func_800CAF9C);

extern s32 func_80161208();
extern void func_801599A4(void *a0);
extern void func_80159B3C(void *a0);
void func_800CB140(s32 *a0) {
    if (func_80161208() == 0) {
        if (*(u16 *)((u8 *)a0 + 0xB8) == 0x8000) {
            func_801599A4(a0);
            func_80159B3C(a0);
        }
    }
}


extern void func_80154A74(s32 a0, s32 a1);
s32 func_800CB190(s32 a0)
{
    *(u32 *)(a0 + 0x44) = *(u32 *)(a0 + 0x44) & ~2;
    func_80154A74(a0, 0x11);
}



extern void func_800CB474(void);

void func_800CB1C0(void *arg0) {

    extern u8 D_80078EC1;
    extern void (*D_800CBB38[])(void);
    if (D_80078EC1 == 0x8) {
        u16 v0 = *(u16 *)((u8 *)arg0 + 2);
        D_800CBB38[v0]();
    } else {
        func_800CB474();
    }
}


INCLUDE_ASM("asm/md_MAIN_015/nonmatchings/md_MAIN_015", func_800CB21C);

void func_800CB2E0(void *arg0) {
    extern s32 func_80146E98(s32 a0);
    extern void func_80013F3C(void *a0);
    extern void func_800126C4(s32 a0, s32 a1);
    extern void func_800123F0(s32 a0, s32 a1);
    extern void func_80012558(s32 a0, s32 a1);
    extern void func_80163194(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);
    extern void func_80162FC0(s32 *a0);
    extern s32 func_80163408(s32 a0, s32 a1, s32 a2, s32 a3);
    extern void func_80163328();
    extern s32 func_801632F0();
    extern void func_80013E94(void *a0, void *a1);
    extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
    extern void func_80146CA0(void *a0);
    extern s16 D_80126B18[];
    extern s16 D_80126B1A[];
    extern s16 D_80126B1C;
    extern s32 D_80114EB0;
    extern s32 D_80114EC8;

    register void *a0v __asm__("$17");
    register void *fp __asm__("$18");
    u8 buf[0x40];
    s32 sp60;
    s32 cmd;

    a0v = arg0;
    fp = *(void **)((u8 *)a0v + 0x20);

    if (func_80146E98((s32)a0v)) {
        func_80146A6C(3, a0v, *(s16 *)((u8 *)a0v + 6), *(s16 *)((u8 *)a0v + 0xA), *(s16 *)((u8 *)a0v + 0xE), 0, 0x80001C00);
    } else {
        register u8 *bp __asm__("$16");
        bp = buf + 0x20;
        func_80013F3C(bp);
        func_800126C4((s32)bp, *(s16 *)((u8 *)fp + 0x10));
        func_800123F0((s32)bp, *(s16 *)((u8 *)fp + 0x14));
        func_80012558((s32)bp, *(s16 *)((u8 *)fp + 0x12));
        func_80163194((s32)a0v, 0, 0, 0, (s32)bp);
        func_80162FC0((s32 *)a0v);
        func_80163408((s32)a0v, 0x10, 0x80, 0x200);
        func_80163328(a0v);
        switch ((u32)func_801632F0(a0v)) {
        case 1:
            func_80013E94(&D_80114EB0, &sp60);
            cmd = 0x1F;
            break;
        case 2:
        case 4:
            func_80013E94(&D_80114EC8, &sp60);
            cmd = 7;
            break;
        default:
            return;
        }
        sp60 |= 0x80000000;
        func_80146A6C(cmd, a0v, D_80126B18[0], D_80126B1A[0], D_80126B1C, sp60, 0);
    }
    func_80146CA0(a0v);
}


extern void func_80162CCC(void);
void func_800CB474(void) {
    func_80162CCC();
}



extern void func_80146C3C(void);

void func_800CB494(void *arg0) {

    extern u8 D_80078EC1;
    extern void (*D_800CBB58[])(void);
    if (D_80078EC1 == 0x8) {
        u16 v0 = *(u16 *)((u8 *)arg0 + 2);
        D_800CBB58[v0]();
    } else {
        func_80146C3C();
    }
}


void func_800CB4F0(void *arg0) {
    typedef struct { u32 a, b, c, d; } Blk16;
    extern s32 func_801465E4(void);
    extern void func_8001C810(s32 a0, s32 a1);
    extern void func_80149350();
    extern void func_80149374(s32 a0, s32 a1);
    extern s32 func_80017DC4(void *a0, void *a1);
    extern void RotMatrixZ(s32 a0, void *a1);
    extern void MulMatrix0(s32 a0, void *a1, s32 a2);
    extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
    extern void func_80146C3C(void);
    extern s32 rand(void);
    extern s32 D_800CC870;
    extern s32 D_800636C8;

    short sv[3];
    int mtx[8];
    s32 s3;
    s32 s2;
    s32 t;

    s3 = *(s32 *)((char *)arg0 + 0x34);
    s2 = func_801465E4();
    *(s32 *)((char *)arg0 + 0x20) = s2;
    if (s2 == 0) goto Lcall;

    func_8001C810(s2, (s32)&D_800CC870);
    *(u32 *)(s2 + 4) |= 0x50000040;
    *(s32 *)(s2 + 0x20) = (s32)&D_800636C8;

    sv[0] = 0;
    sv[1] = -6;
    sv[2] = *(u16 *)((char *)arg0 + 0xE) - 0x24;
    func_80149350(s3, sv, sv);

    t = *(s32 *)(s3 + 0x20);
    *(Blk16 *)((char *)arg0 + 0x38) = *(Blk16 *)(t + 0x34);
    *(Blk16 *)((char *)arg0 + 0x48) = *(Blk16 *)(t + 0x44);

    *(s32 *)((char *)arg0 + 0x4C) = sv[0];
    *(s32 *)((char *)arg0 + 0x50) = sv[1];
    *(s32 *)((char *)arg0 + 0x54) = sv[2];
    func_80149374(s3, (s32)arg0 + 4);

    sv[2] = 0x1800;
    sv[1] = 0x1800;
    sv[0] = 0x1800;
    func_80017DC4(sv, mtx);

    RotMatrixZ(rand() & 0xFFF, mtx);
    MulMatrix0(*(s32 *)(s3 + 0x20) + 0x34, mtx, s2 + 0x34);

    func_80146A6C(0x13, arg0,
                  *(short *)((char *)arg0 + 6),
                  *(short *)((char *)arg0 + 0xA),
                  *(short *)((char *)arg0 + 0xE),
                  0, 0);

    *(s32 *)((char *)arg0 + 0x30) = 0x80;
    func_800CB6FC(arg0);
    *(u16 *)((char *)arg0 + 2) = *(u16 *)((char *)arg0 + 2) + 1;
    goto Lend;

Lcall:
    ((void (*)(void *))func_80146C3C)(arg0);
Lend:;
}


void func_800CB6A4(void *arg0) {
    extern s32 func_800CB6FC(s32 a0);
    extern void func_80146C3C(void);

    (*(s32 *)((char *)arg0 + 0x1C))++;
    if ((*(s32 *)((char *)arg0 + 0x1C)) < 2) {
        *(u32 *)((char *)arg0 + 0x30) >>= 1;
        func_800CB6FC((s32)arg0);
    } else {
        func_80146C3C();
    }
}


extern signed char D_800CBB44[];
extern s32 func_80017758(void *a0, void *a1);

s32 func_800CB6FC(s32 param_1) {
    unsigned char buf[0x34];
    signed char *p;
    short i;
    u8 t;

    p = D_800CBB44;
    i = 0;
    *(short *)(buf + 0x0c) = 0;
    *(short *)(buf + 0x0a) = 0;
    *(short *)(buf + 0x08) = 0;
    *(short *)(buf + 0x1a) = 0;
    *(short *)(buf + 0x12) = 0;
    *(short *)(buf + 0x02) = 0;
    t = *(u8 *)(param_1 + 0x30);
    buf[0x22] = 0;
    buf[0x21] = 0;
    buf[0x20] = 0;
    buf[0x2a] = 0;
    buf[0x29] = 0;
    buf[0x28] = 0;
    buf[0x2e] = 0;
    buf[0x2d] = 0;
    buf[0x2c] = 0;
    *(int *)(buf + 0x30) = 0x50000000;
    buf[0x25] = t;
    buf[0x26] = t;
    buf[0x24] = t;
    do {
        *(short *)(buf + 0x00) = *p++;
        *(short *)(buf + 0x04) = *p++;
        *(short *)(buf + 0x10) = *p++;
        *(short *)(buf + 0x14) = *p++;
        *(short *)(buf + 0x18) = *p++;
        *(short *)(buf + 0x1c) = *p--;
        func_80017758(buf, (void *)((s32)param_1 + 0x38));
        i++;
    } while (i < 4);
}



extern void func_80146C3C(void);

void func_800CB830(void *arg0) {

    extern u8 D_80078EC1;
    extern void (*D_800CBB60[])(void);
    if (D_80078EC1 == 0x8) {
        u16 v0 = *(u16 *)((u8 *)arg0 + 2);
        D_800CBB60[v0]();
    } else {
        func_80146C3C();
    }
}


extern void func_800D20C0(void *a0, void *a1, s16 a2);
extern void func_800D23D0(s16 *a0);
extern void func_80017E68(void *a0, void *a1);
extern void RotMatrixYXZ(void *a0, void *a1);

void func_800CB88C(s32 param_1) {
    s16 sp[8];
    sp[0] = *(u16 *)(param_1 + 0x6);
    sp[1] = *(u16 *)(param_1 + 0xA);
    sp[2] = *(u16 *)(param_1 + 0xE);
    func_800D20C0(&sp[0], &sp[4], 7);
    func_800D23D0(&sp[4]);
    func_80017E68(&sp[0], (void *)(param_1 + 0x38));
    RotMatrixYXZ(&sp[4], (void *)(param_1 + 0x38));
    *(s32 *)(param_1 + 0x30) = 0xC0;
    func_800CB988(param_1);
    *(u16 *)(param_1 + 0x2) += 1;
}


extern void func_80146C3C(void);
extern s32 func_800CB988(s32 param_1);

void func_800CB930(void *arg0) {
    s32 v;

    v = *(s32 *)((s32)arg0 + 0x1C);
    v++;
    *(s32 *)((s32)arg0 + 0x1C) = v;
    if (v < 2) {
        *(u32 *)((s32)arg0 + 0x30) >>= 1;
        func_800CB988((s32)arg0);
    } else {
        func_80146C3C();
    }
}


extern signed char D_800CBB44[];
extern s32 func_80017758(void *a0, void *a1);

s32 func_800CB988(s32 param_1) {
    unsigned char buf[0x34];
    signed char *p;
    short i;
    u8 t;

    p = D_800CBB44;
    i = 0;
    *(short *)(buf + 0x0c) = 0;
    *(short *)(buf + 0x0a) = 0;
    *(short *)(buf + 0x08) = 0;
    *(short *)(buf + 0x1c) = 0;
    *(short *)(buf + 0x14) = 0;
    *(short *)(buf + 0x04) = 0;
    t = *(u8 *)(param_1 + 0x30);
    buf[0x22] = 0;
    buf[0x21] = 0;
    buf[0x20] = 0;
    buf[0x2a] = 0;
    buf[0x29] = 0;
    buf[0x28] = 0;
    buf[0x2e] = 0;
    buf[0x2d] = 0;
    buf[0x2c] = 0;
    *(int *)(buf + 0x30) = 0x50000000;
    buf[0x25] = t;
    buf[0x24] = t;
    buf[0x26] = t >> 1;
    do {
        *(short *)(buf + 0x00) = *p++;
        *(short *)(buf + 0x02) = *p++;
        *(short *)(buf + 0x10) = *p++;
        *(short *)(buf + 0x12) = *p++;
        *(short *)(buf + 0x18) = *p++;
        *(short *)(buf + 0x1a) = *p--;
        func_80017758(buf, (void *)((s32)param_1 + 0x38));
        i++;
    } while (i < 4);
}

