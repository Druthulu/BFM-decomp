#include "common.h"

extern void func_800183E0(s32 a0);
extern u8 D_800CCA28[];
extern u8 D_800CBC18[];

void func_800CAE0C(void) {
    func_800183E0(D_800CCA28);
    func_800183E0(D_800CBC18);
}




void func_800CAE44(void *a0) {

    extern void (*D_800CBBA8[])(void);
    *(u32 *)((s32)a0 + 0x44) |= 8;
    D_800CBBA8[*(u8 *)((s32)a0 + 0x197)]();
}


extern s32 func_80161104(void);
extern void func_800CAED0(u8 *a0);
#include "../shared/slot_800CAE08/func_800CAE88__34360208.h"


extern void func_80154274(s32 *a0, s32 a1);
extern void func_80154A74(s32 a0, s32 a1);
extern u8 D_800CBB44[];

void func_800CAED0(u8 *a0)
{
    func_80154274((s32 *)a0, (s32)D_800CBB44);
    func_80154A74((s32)a0, 0x15);
    a0[0x197] += 1;
}


extern s32 func_80161208();
extern u16 func_801487F4(s32 *a0);
extern void func_80154274(s32 *a0, s32 a1);
extern u8 D_800CBB84[];
extern u8 D_800CBB64[];

void func_800CAF1C(s32 *a0) {
    if (func_80161208() == 0) {
        if (*(u16 *)((u8 *)a0 + 0xB8) == 0x8000) {
            if (func_801487F4(a0) & 0x20) {
                func_80154274(a0, (s32)D_800CBB84);
                *(u8 *)((u8 *)a0 + 0x197) += 1;
            } else {
                func_80154274(a0, (s32)D_800CBB64);
                *(u8 *)((u8 *)a0 + 0x197) += 2;
            }
        }
    }
}


extern s16 func_80148E54(void *a0);
extern s16 func_80012ABC(s16 a0, s16 a1, s32 a2);
extern void func_80148AFC(void *a0);
extern void func_801466F0(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6, s32 a7);
extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
extern void func_80147324(s32 a0);
extern void func_801655E4(void *a0);
extern s32 func_80165624(void *a0);
extern u8 D_800CBB84[];
extern u8 D_800CBB64[];

void func_800CAFAC(void *a0) {
    s32 temp = *(s32 *)((u8 *)a0 + 0x20);
    *(u32 *)((u8 *)a0 + 0x44) |= 2;
    if (func_80161208() == 0) {
        switch (*(u8 *)((u8 *)a0 + 0xA9)) {
        case 0x41: {
            s16 r = func_80148E54(a0);
            if (r > 0) {
                *(s16 *)(temp + 0x12) = func_80012ABC(*(s16 *)(temp + 0x12), r, 4);
            }
            break;
        }
        case 0x53:
        case 0x73:
            func_80148AFC(a0);
            break;
        }
        if (*(u16 *)((u8 *)a0 + 0xB8) & 0x4000) {
            s32 mf = -0xF;
            s32 one = 1;
            func_801466F0(0x1F, a0, 0, -0x18, mf, 0, 0, one);
            func_801466F0(0x1F, a0, 0, -0x18, mf, one, 0, one);
            func_801466F0(0x1F, a0, 0, -0x18, mf, 2, 0, one);
            func_80146A6C(0x43, a0, 0, -0x18, mf, 0, 0);
            func_80147324(0xA64);
            func_801655E4(a0);
        }
        if (*(u16 *)((u8 *)a0 + 0xB8) & 0x8000) {
            if (func_80165624(a0) == 0 && (func_801487F4((s32 *)a0) & 0x20)) {
                func_80154274((s32 *)a0, (s32)D_800CBB84);
            } else {
                func_80154274((s32 *)a0, (s32)D_800CBB64);
                *(u8 *)((u8 *)a0 + 0x197) += 1;
            }
        }
    }
}


extern s32 func_80161208();
extern void func_801599A4(void *a0);
extern void func_80159B3C(void *a0);

void func_800CB194(s32 *a0) {
    if (func_80161208() == 0) {
        if (*(u16 *)((u8 *)a0 + 0xB8) == 0x8000) {
            func_801599A4(a0);
            func_80159B3C(a0);
        }
    }
}


extern void func_80154A74(s32 a0, s32 a1);
s32 func_800CB1E4(s32 a0)
{
    *(u32 *)(a0 + 0x44) = *(u32 *)(a0 + 0x44) & ~2;
    func_80154A74(a0, 0x11);
}



extern void func_800CB4F8(void);

void func_800CB214(void *arg0) {

    extern u8 D_80078EC1;
    extern void (*D_800CBBC8[])(void);
    if (D_80078EC1 == 0x1b) {
        u16 v0 = *(u16 *)((u8 *)arg0 + 2);
        D_800CBBC8[v0]();
    } else {
        func_800CB4F8();
    }
}


extern void func_8014659C(void);
extern void func_8001CA1C(s32 a0, s32 a1);
extern void func_80149374(s32 a0, s32 a1);
extern void func_80146DE8(s32 *a0, s32 a1, s32 a2, s32 a3);
extern void func_80146E90(s32 *a0, s32 a1);
extern void func_80146CA0(void *a0);

void func_800CB270(s32 a0) {
    extern void func_80162CCC();
    extern u32 D_800CBBBC[];
    s32 iVar1;
    s32 iVar2;
    u16 uVar1;

    iVar1 = *(s32 *)(a0 + 0x4C);
    iVar2 = ((s32 (*)(void))func_8014659C)();
    *(s32 *)(a0 + 0x20) = iVar2;
    if (iVar2 != 0) {
        func_8001CA1C(iVar2, (s32)&D_800CBBBC);
        *(s32 *)(iVar2 + 4) |= 0x58000000;
        func_80149374(iVar1, a0 + 4);
        *(u16 *)(a0 + 0x60) = *(u16 *)(iVar1 + 0x100);
        *(u16 *)(a0 + 0x62) = *(u16 *)(iVar1 + 0x104);
        uVar1 = *(u16 *)(*(s32 *)(iVar1 + 0x20) + 0x12);
        *(u16 *)(a0 + 0x64) = (uVar1 + *(s32 *)(a0 + 0x50) * 0xAA - 0xAA) & 0xFFF;
        func_80146DE8((s32 *)a0, 0, 0, 0xFFC00000);
        func_80146E90((s32 *)a0, 0x10);
        func_80146CA0((void *)a0);
    } else {
        func_80162CCC(a0);
    }
}


void func_800CB360(void *arg0) {
    s32 unk60;
    u8 mat[0x40];

    extern s32 func_80146E98(s32 a0);
    extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
    extern void func_80146CA0(void *a0);
    extern void func_80013F3C(void *a0);
    extern void func_800126C4(void *a0, s32 a1);
    extern void func_800123F0(void *a0, s32 a1);
    extern void func_80012558(void *a0, s32 a1);
    extern void func_80163194(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);
    extern void func_80162FC0(s32 *a0);
    extern s32 func_80163408(s32 a0, s32 a1, s32 a2, s32 a3);
    extern void func_80163328(void *a0);
    extern s32 func_801632F0(void *a0);
    extern void func_80013E94(void *a0, void *a1);
    extern s16 D_80126B18[];
    extern u8 D_80114EB0[];
    extern u8 D_80114EC8[];

    s32 v1 = *(u32 *)((s32)arg0 + 0x20);
    *(u16 *)(v1 + 0x14) += 0x200;
    if (func_80146E98((s32)arg0)) {
        func_80146A6C(3, arg0, *(s16 *)((s32)arg0 + 6), *(s16 *)((s32)arg0 + 0xA),
                      *(s16 *)((s32)arg0 + 0xE), 0, 0x1C00);
    } else {
        void *r16 = mat + 0x20;
        u32 ret;
        s32 id;
        func_80013F3C(r16);
        func_800126C4(r16, *(s16 *)((s32)arg0 + 0x60));
        func_800123F0(r16, *(s16 *)((s32)arg0 + 0x62));
        func_80012558(r16, *(s16 *)((s32)arg0 + 0x64));
        func_80163194((s32)arg0, 0, 0, 0, (s32)r16);
        func_80162FC0((s32 *)arg0);
        func_80163408((s32)arg0, 0x2D, 0x80, 0x200);
        func_80163328(arg0);
        ret = func_801632F0(arg0);
        switch (ret) {
        case 1:
            func_80013E94(D_80114EB0, &unk60);
            id = 0x1F;
            break;
        case 2:
        case 4:
            func_80013E94(D_80114EC8, &unk60);
            id = 7;
            break;
        default:
            return;
        }
        unk60 |= 0x80000000;
        func_80146A6C(id, arg0, D_80126B18[0], D_80126B18[1], D_80126B18[2], unk60, 0);
    }
    func_80146CA0(arg0);
}


extern void func_80162CCC(void);
void func_800CB4F8(void) {
    func_80162CCC();
}



extern void func_80146C3C(void);

void func_800CB518(void *arg0) {

    extern u8 D_80078EC1;
    extern void (*D_800CBBE8[])(void);
    if (D_80078EC1 == 0x1b) {
        u16 v0 = *(u16 *)((u8 *)arg0 + 2);
        D_800CBBE8[v0]();
    } else {
        func_80146C3C();
    }
}


void func_800CB574(void *param_1) {
    typedef struct { u32 a, b, c, d; } Blk16;
    extern void func_801465E4(void);
    extern void func_8001C810(s32 a0, s32 a1);
    extern void func_80149350(s32 a0);
    extern void func_80149374(s32 a0, s32 a1);
    extern s32 func_80017DC4(void *a0, void *a1);
    extern void RotMatrixZ(s32 a0, void *a1);
    extern void MulMatrix0(s32 a0, void *a1, s32 a2);
    extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
    extern void func_80146C3C(void);
    extern void func_800CB780(s32 a0);
    extern s32 D_800CCA00;
    extern s32 D_800636C8;

    s32 src;
    s32 iVar2;
    s32 iVar3;
    s16 arr[3];
    s32 mat[8];

    src = *(s32 *)((s32)param_1 + 0x34);
    iVar2 = ((s32 (*)(void))func_801465E4)();
    *(s32 *)((s32)param_1 + 0x20) = iVar2;
    if (iVar2 != 0) {
        func_8001C810(iVar2, (s32)&D_800CCA00);
        *(u32 *)(iVar2 + 4) |= 0x50000040;
        *(s32 *)(iVar2 + 0x20) = (s32)&D_800636C8;

        arr[0] = 0;
        arr[1] = -6;
        arr[2] = (*(u16 *)((s32)param_1 + 0xE)) - 0x24;
        ((void (*)(s32, void *, void *))func_80149350)(src, arr, arr);

        iVar3 = *(s32 *)(src + 0x20);
        *(Blk16 *)((s32)param_1 + 0x38) = *(Blk16 *)(iVar3 + 0x34);
        *(Blk16 *)((s32)param_1 + 0x48) = *(Blk16 *)(iVar3 + 0x44);
        *(s32 *)((s32)param_1 + 0x4C) = arr[0];
        *(s32 *)((s32)param_1 + 0x50) = arr[1];
        *(s32 *)((s32)param_1 + 0x54) = arr[2];
        func_80149374(src, (s32)param_1 + 4);

        arr[2] = 0x1800;
        arr[1] = 0x1800;
        arr[0] = 0x1800;
        ((void (*)(void *, void *))func_80017DC4)(arr, mat);
        RotMatrixZ(rand() & 0xFFF, mat);
        MulMatrix0(*(s32 *)(src + 0x20) + 0x34, mat, iVar2 + 0x34);

        func_80146A6C(0x44, (void *)param_1,
                      *(s16 *)((s32)param_1 + 6),
                      *(s16 *)((s32)param_1 + 0xA),
                      *(s16 *)((s32)param_1 + 0xE),
                      0, 0);

        *(s32 *)((s32)param_1 + 0x30) = 0x80;
        func_800CB780((s32)param_1);
        *(u16 *)((s32)param_1 + 2) = *(u16 *)((s32)param_1 + 2) + 1;
    } else {
        ((void (*)(void *))func_80146C3C)(param_1);
    }
}


extern void func_800CB780(s32 param_1);
extern void func_80146C3C(void);

void func_800CB728(s32 *arg0) {
    arg0[7] = arg0[7] + 1;
    if (arg0[7] < 2) {
        *(u32 *)&arg0[12] >>= 1;
        func_800CB780((s32)arg0);
    } else {
        func_80146C3C();
    }
}


extern signed char D_800CBBD4[];

void func_800CB780(s32 param_1) {
    unsigned char buf[0x34];
    signed char *p;
    short i;
    u8 t;

    p = D_800CBBD4;
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
    *(s32 *)(buf + 0x30) = 0x50000000;
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
        func_80017758(buf, (void *)(param_1 + 0x38));
        i++;
    } while (i < 4);
}



extern void func_80146C3C(void);

void func_800CB8B4(void *arg0) {

    extern u8 D_80078EC1;
    extern void (*D_800CBBF0[])(void);
    if (D_80078EC1 == 0x1b) {
        u16 v0 = *(u16 *)((u8 *)arg0 + 2);
        D_800CBBF0[v0]();
    } else {
        func_80146C3C();
    }
}


extern void func_800D20C0(void *a0, void *a1, s32 a2);
extern void func_800D23D0(void *a0);
extern void func_80017E68(void *a0, void *a1);
extern void RotMatrixYXZ(void *a0, void *a1);
extern void func_800CBA0C(s32 param_1);

void func_800CB910(s32 param_1)
{
    u16 sp10[3];
    u16 sp18[3];

    sp10[0] = *(u16 *)(param_1 + 0x06);
    sp10[1] = *(u16 *)(param_1 + 0x0A);
    sp10[2] = *(u16 *)(param_1 + 0x0E);
    func_800D20C0(sp10, sp18, 7);
    func_800D23D0(sp18);
    func_80017E68(sp10, (void *)(param_1 + 0x38));
    RotMatrixYXZ(sp18, (void *)(param_1 + 0x38));
    *(s32 *)(param_1 + 0x30) = 0xC0;
    func_800CBA0C(param_1);
    *(u16 *)(param_1 + 2) = *(u16 *)(param_1 + 2) + 1;
}


extern void func_800CBA0C(s32 param_1);
extern void func_80146C3C(void);

void func_800CB9B4(s32 *arg0) {
    arg0[7] = arg0[7] + 1;
    if (arg0[7] < 2) {
        *(u32 *)&arg0[12] >>= 1;
        func_800CBA0C((s32)arg0);
    } else {
        func_80146C3C();
    }
}


extern signed char D_800CBBD4[];

void func_800CBA0C(s32 param_1) {
    unsigned char buf[0x34];
    signed char *p;
    short i;
    u8 t;

    p = D_800CBBD4;
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
    *(s32 *)(buf + 0x30) = 0x50000000;
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
        func_80017758(buf, (void *)(param_1 + 0x38));
        i++;
    } while (i < 4);
}

