#include "common.h"

extern s32 guess_AllocRenderWorkRecord(s32 *a0);
void func_800CAE0C(void) {

    extern s32 D_800CB610;
    guess_AllocRenderWorkRecord(&D_800CB610);
}




void func_800CAE34(void *a0) {

    extern void (*D_800CB5BC[])(void);
    ((Unkstruct_800CAE34 *)a0)->unk44.u |= 8;
    D_800CB5BC[((Unkstruct_800CAE34 *)a0)->unk197]();
}


extern void func_800CAEB0(void *a0);
#include "../shared/slot_800CAE08/func_800CAE78__3873a7ac.h"


extern s32 func_80165910(void);
extern void func_801655E4(s32 a0);
extern s32 guess_SpawnSmallObject(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
extern void guess_PlaySoundUnlessSkipped(s32 arg0);

void func_800CAEB0(void *a0) {
    if (KR_AS(s32, func_80165910)(a0) == 0) {
        func_801655E4((s32)a0);
    }
    guess_SpawnSmallObject(0xA, a0, 0, 0, 0, 0, 0);
    guess_PlaySoundUnlessSkipped(0x475);
    *(u8 *)((s32)a0 + 0x197) += 1;
}


#include "common.h"

extern s32 D_80078EC8;
extern s32 func_80165A20(s32 a0);

#define SHARED_FN func_800CAF20
#include "../shared/slot_800CAE08/cls_a794c5bff4fe.h"
#undef SHARED_FN


void func_800CAF4C(void) {
}



void func_800CAF54(void *a0) {

    extern void (*D_800CB5DC[])(void);
    D_800CB5DC[((Unkstruct_80126B58 *)a0)->unk2.u]();
}


#include "common.h"

void func_800CAF90(void *a0) {
    extern void func_80017DC4(void *a0, void *a1);
    extern void guess_RotTransSVWithMatrix(s32 a0, s32 a1, s32 a2);
    extern void func_800D20C0(Pos800D20C0 *arg0, SVECTOR_800 *arg1, s16 arg2);
    extern void func_800D23D0(void *a0);
    extern void func_80017E68(void *a0, void *a1);
    extern void RotMatrixYXZ(void *a0, void *a1);
    extern void func_80048D9C(void *a0, void *a1);
    extern void guess_AddPolyG4(void *a0, void *a1);
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

    fld = ((Unkstruct_8011D030 *)a0)->unk28.u;
    vecA[2] = fld;
    vecA[1] = fld;
    vecA[0] = fld;
    func_80017DC4(vecA, s2vec);

    vecA[2] = 0;
    vecA[0] = 0;
    vecA[1] = -0x2C;
    guess_RotTransSVWithMatrix((s32)a0 + 0x38, (s32)vecA, (s32)vecA);

    func_800D20C0(vecA, rot, 5);
    func_800D23D0(rot);

    ((Src_80016C28 *)info)->v[1].vz = 0;
    ((Src_80016C28 *)info)->v[1].vy = 0;
    ((Src_80016C28 *)info)->v[1].vx = 0;
    ((Src_80016C28 *)info)->v[3].vz = 0;
    ((Src_80016C28 *)info)->v[2].vz = 0;
    ((Src_80016C28 *)info)->v[0].vz = 0;

    fld2 = ((Unkstruct_8011D030 *)a0)->unk28.u;

    ((Src_80016C28 *)info)->unk24.v1.unk1 = 0;
    ((Src_80016C28 *)info)->unk20.v1.unk2 = 0;
    ((Src_80016C28 *)info)->unk20.v1.unk1 = 0;
    ((Src_80016C28 *)info)->unk20.v1.unk0 = 0;
    ((Src_80016C28 *)info)->unk28.v1.unk2 = 0;
    ((Src_80016C28 *)info)->unk28.v1.unk1 = 0;
    ((Src_80016C28 *)info)->unk28.v1.unk0 = 0;
    ((Src_80016C28 *)info)->unk2C.v1.unk2 = 0;
    ((Src_80016C28 *)info)->unk2C.v1.unk1 = 0;
    ((Src_80016C28 *)info)->unk2C.v1.unk0 = 0;
    ((Src_80016C28 *)info)->flags.u = 0x50000000;

    ang = (s16)fld2 >> 6;
    ang = ang + 0x70;
    ((Src_80016C28 *)info)->unk24.v1.unk2 = (s8)ang;
    ((Src_80016C28 *)info)->unk24.v1.unk0 = (s8)ang;
    func_80017E68(vecA, s2vec);

    RotMatrixYXZ(rot, mtx);
    func_80048D9C(s2vec, mtx);

    tbl = D_800CB5C8;
    for (i = 0; i < 4; i++) {
        ((Src_80016C28 *)info)->v[0].vx = (s8)*tbl; tbl++;
        ((Src_80016C28 *)info)->v[0].vy = (s8)*tbl; tbl++;
        ((Src_80016C28 *)info)->v[2].vx = (s8)*tbl; tbl++;
        ((Src_80016C28 *)info)->v[2].vy = (s8)*tbl; tbl++;
        ((Src_80016C28 *)info)->v[3].vx = (s8)*tbl; tbl++;
        last = (s8)*tbl; tbl--;
        ((Src_80016C28 *)info)->v[3].vy = last;
        guess_AddPolyG4(info, s2vec);
    }
}



void func_800CB164(void *a0) {
    extern u8 D_80078EC1;
    extern s32 guess_FreeSmallObject(u8 *a0);
    extern void func_800CAF90(void *a0);

    s32 src;
    s32 obj;
    s32 cnt;

    src = ((Unkstruct_8011D030 *)a0)->unk34.val;
    if (*(u8 *)&D_80078EC1 == 5) {
        if ((((Unkstruct_8011D030 *)a0)->unk2C.val.u & 0x8000) == 0) {
            cnt = ((Unkstruct_8011D030 *)a0)->unk1C.s;
            ((Unkstruct_8011D030 *)a0)->unk1C.s = cnt + 1;
            if (cnt < 8) {
                ((Unkstruct_8011D030 *)a0)->unk28.u += 0x120;
            } else {
                ((Unkstruct_8011D030 *)a0)->unk1C.s = 0;
                ((Unkstruct_8011D030 *)a0)->unk2.u = 4;
            }
            obj = ((Unkstruct_80126B58 *)src)->unk20.val;
            *(Blk16_956C *)((s32)a0 + 0x38) = *(Blk16_956C *)(obj + 0x34);
            *(Blk16_956C *)((s32)a0 + 0x48) = *(Blk16_956C *)(obj + 0x44);
            func_800CAF90(a0);
        } else {
            ((Unkstruct_8011D030 *)a0)->unk2.u += 1;
        }
    } else {
        guess_FreeSmallObject(a0);
    }
}


void func_800CB254(void *a0) {
    extern u8 D_80078EC1;
    extern s32 guess_FreeSmallObject(u8 *a0);
    extern void func_800CAF90(void *a0);
    s32 a1;
    s32 n;
    s32 m;
    s32 v0;
    a1 = ((Unkstruct_8011D030 *)a0)->unk34.val;
    if (D_80078EC1 == 5) {
        if ((((Unkstruct_8011D030 *)a0)->unk1C.s)++ < 10) {
            ((Unkstruct_8011D030 *)a0)->unk28.u += 0x120;
        } else {
            n = ((Unkstruct_8011D030 *)a0)->unk2.u;
            n += 1;
            ((Unkstruct_8011D030 *)a0)->unk10.i.hi.u = (s16)((Unkstruct_80126B58 *)a1)->unk10.i.hi >> 1;
            m = ((Unkstruct_80126B58 *)a1)->unk18.i.hi;
            ((Unkstruct_8011D030 *)a0)->unk30.val.s = 0x20;
            ((Unkstruct_8011D030 *)a0)->unk1C.s = -0xC0;
            ((Unkstruct_8011D030 *)a0)->unk2A.u = 0x500;
            ((Unkstruct_8011D030 *)a0)->unk2.u = n;
            ((Unkstruct_8011D030 *)a0)->unk18.i.hi.u = (s16)m >> 1;
        }
        v0 = ((Unkstruct_80126B58 *)a1)->unk20.val;
        *(Blk16_956C *)((s32)a0 + 0x38) = *(Blk16_956C *)(v0 + 0x34);
        *(Blk16_956C *)((s32)a0 + 0x48) = *(Blk16_956C *)(v0 + 0x44);
        func_800CAF90(a0);
    } else {
        guess_FreeSmallObject(a0);
    }
}


#include "common.h"

void func_800CB358(void *param_1) {
    extern u8 D_80078EC1;
    extern s32 guess_FreeSmallObject(u8 *a0);
    extern void func_800CAF90(void *a0);
    s32 iVar2;
    s32 cnt;

    if (*(u8 *)&D_80078EC1 != 5) goto LAB_800CB454;
    if (CAST_SIGN(s16, (s32)param_1, 0x28) > CAST_SIGN(s16, (s32)param_1, 0x2a)) {
        iVar2 = ((Unkstruct_8011D030 *)param_1)->unk1C.s;
        if (iVar2 < 1) goto LAB_800CB3ec;
        ((Unkstruct_8011D030 *)param_1)->unk2A.u = (rand() & 0x180) + 0x400;
        iVar2 = -0xA0;
    } else {
        iVar2 = ((Unkstruct_8011D030 *)param_1)->unk1C.s;
        if (-1 < iVar2) goto LAB_800CB3ec;
        ((Unkstruct_8011D030 *)param_1)->unk2A.u = (rand() & 0x180) + 0x700;
        iVar2 = 0xA0;
    }
    ((Unkstruct_8011D030 *)param_1)->unk1C.s = iVar2;
LAB_800CB3ec:
    ((Unkstruct_8011D030 *)param_1)->unk28.u = ((Unkstruct_8011D030 *)param_1)->unk28.u + ((Unkstruct_8011D030 *)param_1)->unk1C.s;
    ((Unkstruct_8011D030 *)param_1)->unk38.f.unk4C = ((Unkstruct_8011D030 *)param_1)->unk38.f.unk4C + CAST_SIGN(s16, (s32)param_1, 0x12);
    ((Unkstruct_8011D030 *)param_1)->unk38.f.unk50 = ((Unkstruct_8011D030 *)param_1)->unk38.f.unk50 - 3;
    ((Unkstruct_8011D030 *)param_1)->unk38.f.unk54 = ((Unkstruct_8011D030 *)param_1)->unk38.f.unk54 + CAST_SIGN(s16, (s32)param_1, 0x1a);
    func_800CAF90(param_1);

    cnt = ((Unkstruct_8011D030 *)param_1)->unk30.val.s;
    ((Unkstruct_8011D030 *)param_1)->unk30.val.s = cnt - 1;
    if (cnt != 0) return;
    ((Unkstruct_8011D030 *)param_1)->unk2.u = ((Unkstruct_8011D030 *)param_1)->unk2.u + 1;
    return;
LAB_800CB454:
    guess_FreeSmallObject(param_1);
}


void func_800CB470(void *a0) {
    extern u8 D_80078EC1;
    extern void func_800CAF90(void *);
    extern s32 guess_FreeSmallObject(u8 *a0);
    u16 uVar1;

    if (D_80078EC1 == 5) {
        uVar1 = ((Unkstruct_8011D030 *)a0)->unk28.u - 0x100;
        ((Unkstruct_8011D030 *)a0)->unk28.u = uVar1;
        if ((s16)uVar1 > 0) {
            ((Unkstruct_8011D030 *)a0)->unk38.f.unk50 -= 3;
            func_800CAF90(a0);
        } else {
            guess_FreeSmallObject(a0);
        }
    } else {
        guess_FreeSmallObject(a0);
    }
}



extern void func_800CAF90(void *a0);
extern s32 guess_SpawnSmallObject(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
extern s32 guess_FreeSmallObject(u8 *a0);
extern u8 D_80078EC1;

void func_800CB4D8(void *a0) {
    s32 s1;
    s32 src;

    s1 = ((Unkstruct_8011D030 *)a0)->unk34.val;
    src = ((Unkstruct_80126B58 *)s1)->unk20.val;
    *(Blk16_956C *)((s32)a0 + 0x38) = *(Blk16_956C *)(src + 0x34);
    *(Blk16_956C *)((s32)a0 + 0x48) = *(Blk16_956C *)(src + 0x44);
    func_800CAF90(a0);

    if (D_80078EC1 == 5) {
        if (--((Unkstruct_8011D030 *)a0)->unk1C.s == -1) {
            guess_SpawnSmallObject(0xA, (void *)s1, 0, 0, 0, 0x8000, 0);
            ((Unkstruct_8011D030 *)a0)->unk1C.s = 0x18;
        }
    } else {
        guess_FreeSmallObject(a0);
    }
}

