#include "common.h"

extern s32 func_800183E0(s32 *a0);
void func_800CAE0C(void) {

    extern s32 D_800CB610;
    func_800183E0(&D_800CB610);
}




void func_800CAE34(void *a0) {

    extern void (*D_800CB5BC[])(void);
    *(u32 *)((s32)a0 + 0x44) |= 8;
    D_800CB5BC[*(u8 *)((s32)a0 + 0x197)]();
}


extern void func_800CAEB0();
#include "../shared/slot_800CAE08/func_800CAE78__3873a7ac.h"


extern s32 func_80165910();
extern void func_801655E4(s32 a0);
extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
extern void func_80147324(s32 arg0);

void func_800CAEB0(void *a0) {
    if (func_80165910(a0) == 0) {
        func_801655E4((s32)a0);
    }
    func_80146A6C(0xA, a0, 0, 0, 0, 0, 0);
    func_80147324(0x475);
    *(u8 *)((s32)a0 + 0x197) += 1;
}


#include "common.h"

extern s32 D_80078EC8;
extern void func_80165A20(void);

void func_800CAF20(void) {
    if (D_80078EC8 == 0) {
        func_80165A20();
    }
}


void func_800CAF4C(void) {
}



void func_800CAF54(void *a0) {

    extern void (*D_800CB5DC[])(void);
    D_800CB5DC[*(u16 *)((s32)a0 + 0x2)]();
}


#include "common.h"

void func_800CAF90(void *a0) {
    extern s32 func_80017DC4(void *a0, void *a1);
    extern void func_8012F14C(s32 a0, s32 a1, s32 a2);
    extern void func_800D20C0(void *a0, void *a1, s32 a2);
    extern void func_800D23D0(void *a0);
    extern void func_80017E68(void *a0, void *a1);
    extern void RotMatrixYXZ(void *a0, void *a1);
    extern void func_80048D9C(void *a0, void *a1);
    extern s32 func_80017758(void *a0, void *a1);
    extern u8 D_800CB5C8[];

    s16 vecA[4];
    s16 rot[4];
    u8 info[0x38];
    u8 s2vec[0x20];
    s16 mtx[16];
    u16 fld;
    u16 fld2;
    s16 ang;
    u8 *tbl;
    s8 last;
    s16 i;

    fld = *(u16 *)((s32)a0 + 0x28);
    vecA[2] = fld;
    vecA[1] = fld;
    vecA[0] = fld;
    func_80017DC4(vecA, s2vec);

    vecA[2] = 0;
    vecA[0] = 0;
    vecA[1] = -0x2C;
    func_8012F14C((s32)a0 + 0x38, (s32)vecA, (s32)vecA);

    func_800D20C0(vecA, rot, 5);
    func_800D23D0(rot);

    *(s16 *)(info + 0x0C) = 0;
    *(s16 *)(info + 0x0A) = 0;
    *(s16 *)(info + 0x08) = 0;
    *(s16 *)(info + 0x1C) = 0;
    *(s16 *)(info + 0x14) = 0;
    *(s16 *)(info + 0x04) = 0;

    fld2 = *(u16 *)((s32)a0 + 0x28);

    *(u8 *)(info + 0x25) = 0;
    *(u8 *)(info + 0x22) = 0;
    *(u8 *)(info + 0x21) = 0;
    *(u8 *)(info + 0x20) = 0;
    *(u8 *)(info + 0x2A) = 0;
    *(u8 *)(info + 0x29) = 0;
    *(u8 *)(info + 0x28) = 0;
    *(u8 *)(info + 0x2E) = 0;
    *(u8 *)(info + 0x2D) = 0;
    *(u8 *)(info + 0x2C) = 0;
    *(u32 *)(info + 0x30) = 0x50000000;

    ang = (s16)fld2 >> 6;
    ang = ang + 0x70;
    *(s8 *)(info + 0x26) = (s8)ang;
    *(s8 *)(info + 0x24) = (s8)ang;
    func_80017E68(vecA, s2vec);

    RotMatrixYXZ(rot, mtx);
    func_80048D9C(s2vec, mtx);

    tbl = D_800CB5C8;
    for (i = 0; i < 4; i++) {
        *(s16 *)(info + 0x00) = (s8)*tbl; tbl++;
        *(s16 *)(info + 0x02) = (s8)*tbl; tbl++;
        *(s16 *)(info + 0x10) = (s8)*tbl; tbl++;
        *(s16 *)(info + 0x12) = (s8)*tbl; tbl++;
        *(s16 *)(info + 0x18) = (s8)*tbl; tbl++;
        last = (s8)*tbl; tbl--;
        *(s16 *)(info + 0x1A) = last;
        func_80017758(info, s2vec);
    }
}


typedef struct { s32 w[4]; } func_800CB164_Blk16;

void func_800CB164(void *a0) {
    extern u8 D_80078EC1;
    extern void func_80146C3C(void *a0);
    extern void func_800CAF90(void *a0);

    s32 src;
    s32 obj;
    s32 cnt;

    src = *(s32 *)((s32)a0 + 0x34);
    if (*(u8 *)&D_80078EC1 == 5) {
        if ((*(u32 *)((s32)a0 + 0x2C) & 0x8000) == 0) {
            cnt = *(s32 *)((s32)a0 + 0x1C);
            *(s32 *)((s32)a0 + 0x1C) = cnt + 1;
            if (cnt < 8) {
                *(u16 *)((s32)a0 + 0x28) += 0x120;
            } else {
                *(s32 *)((s32)a0 + 0x1C) = 0;
                *(u16 *)((s32)a0 + 2) = 4;
            }
            obj = *(s32 *)(src + 0x20);
            *(func_800CB164_Blk16 *)((s32)a0 + 0x38) = *(func_800CB164_Blk16 *)(obj + 0x34);
            *(func_800CB164_Blk16 *)((s32)a0 + 0x48) = *(func_800CB164_Blk16 *)(obj + 0x44);
            func_800CAF90(a0);
        } else {
            *(u16 *)((s32)a0 + 2) += 1;
        }
    } else {
        func_80146C3C(a0);
    }
}


void func_800CB254(void *a0) {
    typedef struct { s32 w[4]; } S16;
    extern u8 D_80078EC1;
    extern void func_80146C3C(void *a0);
    extern void func_800CAF90(void *a0);
    s32 a1;
    s32 n;
    s32 m;
    s32 v0;
    a1 = *(s32 *)((s32)a0 + 0x34);
    if (D_80078EC1 == 5) {
        if ((*(s32 *)((s32)a0 + 0x1C))++ < 10) {
            *(u16 *)((s32)a0 + 0x28) += 0x120;
        } else {
            n = *(u16 *)((s32)a0 + 2);
            n += 1;
            *(u16 *)((s32)a0 + 0x12) = (s16)*(u16 *)(a1 + 0x12) >> 1;
            m = *(u16 *)(a1 + 0x1A);
            *(s32 *)((s32)a0 + 0x30) = 0x20;
            *(s32 *)((s32)a0 + 0x1C) = -0xC0;
            *(u16 *)((s32)a0 + 0x2A) = 0x500;
            *(u16 *)((s32)a0 + 2) = n;
            *(u16 *)((s32)a0 + 0x1A) = (s16)m >> 1;
        }
        v0 = *(s32 *)(a1 + 0x20);
        *(S16 *)((s32)a0 + 0x38) = *(S16 *)(v0 + 0x34);
        *(S16 *)((s32)a0 + 0x48) = *(S16 *)(v0 + 0x44);
        func_800CAF90(a0);
    } else {
        func_80146C3C(a0);
    }
}


#include "common.h"

void func_800CB358(void *param_1) {
    extern u8 D_80078EC1;
    extern void func_80146C3C();
    extern void func_800CAF90(void *a0);
    register s32 iVar2 __asm__("$2");
    s32 cnt;

    if (*(u8 *)&D_80078EC1 != 5) goto LAB_800CB454;
    if (*(s16 *)((s32)param_1 + 0x28) > *(s16 *)((s32)param_1 + 0x2a)) {
        iVar2 = *(s32 *)((s32)param_1 + 0x1c);
        if (iVar2 < 1) goto LAB_800CB3ec;
        *(u16 *)((s32)param_1 + 0x2a) = (rand() & 0x180) + 0x400;
        iVar2 = -0xA0;
    } else {
        iVar2 = *(s32 *)((s32)param_1 + 0x1c);
        if (-1 < iVar2) goto LAB_800CB3ec;
        *(u16 *)((s32)param_1 + 0x2a) = (rand() & 0x180) + 0x700;
        iVar2 = 0xA0;
    }
    *(s32 *)((s32)param_1 + 0x1c) = iVar2;
LAB_800CB3ec:
    *(u16 *)((s32)param_1 + 0x28) = *(u16 *)((s32)param_1 + 0x28) + *(s32 *)((s32)param_1 + 0x1c);
    *(s32 *)((s32)param_1 + 0x4c) = *(s32 *)((s32)param_1 + 0x4c) + *(s16 *)((s32)param_1 + 0x12);
    *(s32 *)((s32)param_1 + 0x50) = *(s32 *)((s32)param_1 + 0x50) - 3;
    *(s32 *)((s32)param_1 + 0x54) = *(s32 *)((s32)param_1 + 0x54) + *(s16 *)((s32)param_1 + 0x1a);
    func_800CAF90(param_1);

    cnt = *(s32 *)((s32)param_1 + 0x30);
    *(s32 *)((s32)param_1 + 0x30) = cnt - 1;
    if (cnt != 0) return;
    *(u16 *)((s32)param_1 + 2) = *(u16 *)((s32)param_1 + 2) + 1;
    return;
LAB_800CB454:
    func_80146C3C(param_1);
}


void func_800CB470(void *a0) {
    extern u8 D_80078EC1;
    extern void func_800CAF90(void *);
    extern void func_80146C3C(void *);
    u16 uVar1;

    if (D_80078EC1 == 5) {
        uVar1 = *(u16 *)((s32)a0 + 0x28) - 0x100;
        *(u16 *)((s32)a0 + 0x28) = uVar1;
        if ((s16)uVar1 > 0) {
            *(s32 *)((s32)a0 + 0x50) -= 3;
            func_800CAF90(a0);
        } else {
            func_80146C3C(a0);
        }
    } else {
        func_80146C3C(a0);
    }
}


typedef struct { s32 w[4]; } func_800CB4D8_Blk16;

extern void func_800CAF90(void *a0);
extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
extern void func_80146C3C(void *a0);
extern u8 D_80078EC1;

void func_800CB4D8(void *a0) {
    s32 s1;
    s32 src;

    s1 = *(s32 *)((s32)a0 + 0x34);
    src = *(s32 *)(s1 + 0x20);
    *(func_800CB4D8_Blk16 *)((s32)a0 + 0x38) = *(func_800CB4D8_Blk16 *)(src + 0x34);
    *(func_800CB4D8_Blk16 *)((s32)a0 + 0x48) = *(func_800CB4D8_Blk16 *)(src + 0x44);
    func_800CAF90(a0);

    if (D_80078EC1 == 5) {
        if (--*(s32 *)((s32)a0 + 0x1C) == -1) {
            func_80146A6C(0xA, (void *)s1, 0, 0, 0, 0x8000, 0);
            *(s32 *)((s32)a0 + 0x1C) = 0x18;
        }
    } else {
        func_80146C3C(a0);
    }
}

