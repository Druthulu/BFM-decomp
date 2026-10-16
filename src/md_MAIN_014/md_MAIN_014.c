#include "common.h"

extern s32 func_800183E0(s32 *a0);
void func_800CAE0C(void) {

    extern s32 D_800CB610;
    func_800183E0(&D_800CB610);
}




void func_800CAE34(void *a0) {

    extern void (*D_800CB5BC[])(void);
    ((Unkstruct_800CAE34 *)a0)->unk44 |= 8;
    D_800CB5BC[((Unkstruct_800CAE34 *)a0)->unk197]();
}


extern void func_800CAEB0(void *a0);
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
extern s32 func_80165A20();  // K&R: 0 of 1 args (P37 rung D t4_D58)

void func_800CAF20(void) {
    if (D_80078EC8 == 0) {
        func_80165A20();
    }
}


void func_800CAF4C(void) {
}



void func_800CAF54(void *a0) {

    extern void (*D_800CB5DC[])(void);
    D_800CB5DC[((Unkstruct_80126B58 *)a0)->unk2]();
}


#include "common.h"

void func_800CAF90(void *a0) {
    extern s32 func_80017DC4(void *a0, void *a1);
    extern void func_8012F14C(s32 a0, s32 a1, s32 a2);
    extern void func_800D20C0(Pos800D20C0 *arg0, SVECTOR_800 *arg1, s16 arg2);
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

    fld = ((Unkstruct_800CAF90 *)a0)->unk28;
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

    ((Unkstruct_800CAF90_2 *)info)->unkC = 0;
    ((Unkstruct_800CAF90_2 *)info)->unkA = 0;
    ((Unkstruct_800CAF90_2 *)info)->unk8 = 0;
    ((Unkstruct_800CAF90_2 *)info)->unk1C = 0;
    ((Unkstruct_800CAF90_2 *)info)->unk14 = 0;
    ((Unkstruct_800CAF90_2 *)info)->unk4 = 0;

    fld2 = ((Unkstruct_800CAF90 *)a0)->unk28;

    ((Unkstruct_800CAF90_2 *)info)->unk25 = 0;
    ((Unkstruct_800CAF90_2 *)info)->unk22 = 0;
    ((Unkstruct_800CAF90_2 *)info)->unk21 = 0;
    ((Unkstruct_800CAF90_2 *)info)->unk20 = 0;
    ((Unkstruct_800CAF90_2 *)info)->unk2A = 0;
    ((Unkstruct_800CAF90_2 *)info)->unk29 = 0;
    ((Unkstruct_800CAF90_2 *)info)->unk28 = 0;
    ((Unkstruct_800CAF90_2 *)info)->unk2E = 0;
    ((Unkstruct_800CAF90_2 *)info)->unk2D = 0;
    ((Unkstruct_800CAF90_2 *)info)->unk2C = 0;
    ((Unkstruct_800CAF90_2 *)info)->unk30 = 0x50000000;

    ang = (s16)fld2 >> 6;
    ang = ang + 0x70;
    ((Unkstruct_800CAF90_2 *)info)->unk26 = (s8)ang;
    ((Unkstruct_800CAF90_2 *)info)->unk24 = (s8)ang;
    func_80017E68(vecA, s2vec);

    RotMatrixYXZ(rot, mtx);
    func_80048D9C(s2vec, mtx);

    tbl = D_800CB5C8;
    for (i = 0; i < 4; i++) {
        ((Unkstruct_800CAF90_2 *)info)->unk0 = (s8)*tbl; tbl++;
        ((Unkstruct_800CAF90_2 *)info)->unk2 = (s8)*tbl; tbl++;
        ((Unkstruct_800CAF90_2 *)info)->unk10 = (s8)*tbl; tbl++;
        ((Unkstruct_800CAF90_2 *)info)->unk12 = (s8)*tbl; tbl++;
        ((Unkstruct_800CAF90_2 *)info)->unk18 = (s8)*tbl; tbl++;
        last = (s8)*tbl; tbl--;
        ((Unkstruct_800CAF90_2 *)info)->unk1A = last;
        func_80017758(info, s2vec);
    }
}



void func_800CB164(void *a0) {
    extern u8 D_80078EC1;
    extern void func_80146C3C(u8 *a0);
    extern void func_800CAF90(void *a0);

    s32 src;
    s32 obj;
    s32 cnt;

    src = ((Unkstruct_800CAF90 *)a0)->unk34;
    if (*(u8 *)&D_80078EC1 == 5) {
        if ((((Unkstruct_800CAF90 *)a0)->unk2C & 0x8000) == 0) {
            cnt = ((Unkstruct_800CAF90 *)a0)->unk1C;
            ((Unkstruct_800CAF90 *)a0)->unk1C = cnt + 1;
            if (cnt < 8) {
                ((Unkstruct_800CAF90 *)a0)->unk28 += 0x120;
            } else {
                ((Unkstruct_800CAF90 *)a0)->unk1C = 0;
                ((Unkstruct_800CAF90 *)a0)->unk2 = 4;
            }
            obj = ((Unkstruct_800CB164 *)src)->unk20;
            *(func_800CB164_Blk16 *)((s32)a0 + 0x38) = *(func_800CB164_Blk16 *)(obj + 0x34);
            *(func_800CB164_Blk16 *)((s32)a0 + 0x48) = *(func_800CB164_Blk16 *)(obj + 0x44);
            func_800CAF90(a0);
        } else {
            ((Unkstruct_800CAF90 *)a0)->unk2 += 1;
        }
    } else {
        func_80146C3C(a0);
    }
}


void func_800CB254(void *a0) {
    extern u8 D_80078EC1;
    extern void func_80146C3C(u8 *a0);
    extern void func_800CAF90(void *a0);
    s32 a1;
    s32 n;
    s32 m;
    s32 v0;
    a1 = ((Unkstruct_800CAF90 *)a0)->unk34;
    if (D_80078EC1 == 5) {
        if ((((Unkstruct_800CAF90 *)a0)->unk1C)++ < 10) {
            ((Unkstruct_800CAF90 *)a0)->unk28 += 0x120;
        } else {
            n = ((Unkstruct_800CAF90 *)a0)->unk2;
            n += 1;
            ((Unkstruct_800CAF90 *)a0)->unk12 = (s16)((Unkstruct_800CB164 *)a1)->unk12 >> 1;
            m = ((Unkstruct_800CB164 *)a1)->unk1A;
            ((Unkstruct_800CAF90 *)a0)->unk30 = 0x20;
            ((Unkstruct_800CAF90 *)a0)->unk1C = -0xC0;
            ((Unkstruct_800CAF90 *)a0)->unk2A = 0x500;
            ((Unkstruct_800CAF90 *)a0)->unk2 = n;
            ((Unkstruct_800CAF90 *)a0)->unk1A = (s16)m >> 1;
        }
        v0 = ((Unkstruct_800CB164 *)a1)->unk20;
        *(S16_md_MAIN_014_800CB254 *)((s32)a0 + 0x38) = *(S16_md_MAIN_014_800CB254 *)(v0 + 0x34);
        *(S16_md_MAIN_014_800CB254 *)((s32)a0 + 0x48) = *(S16_md_MAIN_014_800CB254 *)(v0 + 0x44);
        func_800CAF90(a0);
    } else {
        func_80146C3C(a0);
    }
}


#include "common.h"

void func_800CB358(void *param_1) {
    extern u8 D_80078EC1;
    extern void func_80146C3C(u8 *a0);
    extern void func_800CAF90(void *a0);
    s32 iVar2;
    s32 cnt;

    if (*(u8 *)&D_80078EC1 != 5) goto LAB_800CB454;
    if (CAST_SIGN(s16, (s32)param_1, 0x28) > CAST_SIGN(s16, (s32)param_1, 0x2a)) {
        iVar2 = ((Unkstruct_800CAF90 *)param_1)->unk1C;
        if (iVar2 < 1) goto LAB_800CB3ec;
        ((Unkstruct_800CAF90 *)param_1)->unk2A = (rand() & 0x180) + 0x400;
        iVar2 = -0xA0;
    } else {
        iVar2 = ((Unkstruct_800CAF90 *)param_1)->unk1C;
        if (-1 < iVar2) goto LAB_800CB3ec;
        ((Unkstruct_800CAF90 *)param_1)->unk2A = (rand() & 0x180) + 0x700;
        iVar2 = 0xA0;
    }
    ((Unkstruct_800CAF90 *)param_1)->unk1C = iVar2;
LAB_800CB3ec:
    ((Unkstruct_800CAF90 *)param_1)->unk28 = ((Unkstruct_800CAF90 *)param_1)->unk28 + ((Unkstruct_800CAF90 *)param_1)->unk1C;
    ((Unkstruct_800CAF90 *)param_1)->unk4C = ((Unkstruct_800CAF90 *)param_1)->unk4C + CAST_SIGN(s16, (s32)param_1, 0x12);
    ((Unkstruct_800CAF90 *)param_1)->unk50 = ((Unkstruct_800CAF90 *)param_1)->unk50 - 3;
    ((Unkstruct_800CAF90 *)param_1)->unk54 = ((Unkstruct_800CAF90 *)param_1)->unk54 + CAST_SIGN(s16, (s32)param_1, 0x1a);
    func_800CAF90(param_1);

    cnt = ((Unkstruct_800CAF90 *)param_1)->unk30;
    ((Unkstruct_800CAF90 *)param_1)->unk30 = cnt - 1;
    if (cnt != 0) return;
    ((Unkstruct_800CAF90 *)param_1)->unk2 = ((Unkstruct_800CAF90 *)param_1)->unk2 + 1;
    return;
LAB_800CB454:
    func_80146C3C(param_1);
}


void func_800CB470(void *a0) {
    extern u8 D_80078EC1;
    extern void func_800CAF90(void *);
    extern void func_80146C3C(u8 *a0);
    u16 uVar1;

    if (D_80078EC1 == 5) {
        uVar1 = ((Unkstruct_800CAF90 *)a0)->unk28 - 0x100;
        ((Unkstruct_800CAF90 *)a0)->unk28 = uVar1;
        if ((s16)uVar1 > 0) {
            ((Unkstruct_800CAF90 *)a0)->unk50 -= 3;
            func_800CAF90(a0);
        } else {
            func_80146C3C(a0);
        }
    } else {
        func_80146C3C(a0);
    }
}



extern void func_800CAF90(void *a0);
extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
extern void func_80146C3C(u8 *a0);
extern u8 D_80078EC1;

void func_800CB4D8(void *a0) {
    s32 s1;
    s32 src;

    s1 = ((Unkstruct_800CAF90 *)a0)->unk34;
    src = ((Unkstruct_800CB164 *)s1)->unk20;
    *(func_800CB4D8_Blk16 *)((s32)a0 + 0x38) = *(func_800CB4D8_Blk16 *)(src + 0x34);
    *(func_800CB4D8_Blk16 *)((s32)a0 + 0x48) = *(func_800CB4D8_Blk16 *)(src + 0x44);
    func_800CAF90(a0);

    if (D_80078EC1 == 5) {
        if (--((Unkstruct_800CAF90 *)a0)->unk1C == -1) {
            func_80146A6C(0xA, (void *)s1, 0, 0, 0, 0x8000, 0);
            ((Unkstruct_800CAF90 *)a0)->unk1C = 0x18;
        }
    } else {
        func_80146C3C(a0);
    }
}

