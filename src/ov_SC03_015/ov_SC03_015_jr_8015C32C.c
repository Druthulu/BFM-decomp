#include "common.h"
#include "../shared/engine_core.h"


/* ==== Phase-26 §8b carried decl layer (jr_isolate_all.py) ===================
 * The file-scope decl environment from earlier code regions of this object —
 * file-local types, col-0 decls, DEFINE_func macro externs, and each earlier
 * definition's implied prototype (types first, then decls in original order).
 * Decls emit no code => byte-neutral. See cookbook §8c. */
DEFINE_func_8015C32C()  /* dedup: shared engine-core @0x8015C32C (src/shared) */


DEFINE_func_8015C6A4()  /* dedup: shared engine-core @0x8015C6A4 (src/shared) */

DEFINE_func_8015C6AC()  /* dedup: shared engine-core @0x8015C6AC (src/shared) */

DEFINE_func_8015C6E0()  /* dedup: shared engine-core @0x8015C6E0 (src/shared) */


DEFINE_func_8015C714()  /* dedup: shared engine-core @0x8015C714 (src/shared) */


DEFINE_func_8015C750()  /* dedup: shared engine-core @0x8015C750 (src/shared) */

DEFINE_func_8015C788()  /* dedup: shared engine-core @0x8015C788 (src/shared) */


// @class: struct
// @stuck: none — MATCH (match_one 88/88); fn-ptr-array dispatch, top-level if/else needed branch-polarity invert (small block falls through, big block at L854)

DEFINE_func_8015C7E4()  /* dedup: shared engine-core @0x8015C7E4 (src/shared) */




// @class: struct
// @stuck: none — dispatch + control flow on a single callee-saved param; expect MATCH

extern s32 func_80149FB0(s32 a0);
extern void func_80147AD4(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_801473EC(s32 *a0);
extern void func_8014D738(void);
extern void func_80147078(s32 *a0, s16 a1);
extern void func_80159B70(void *a0);
extern void func_80161240(void *a0);
extern s32 func_80146E98(s32 a0);
extern void func_80146CA0(void *a0);
extern void func_80161C24(s32, s32);


void func_8015C944(int param_1) {

    extern void (*D_8018DC08[])();
    func_80149FB0(param_1);
    func_80147AD4(param_1, 0, 0, 0);
    ((void (*)(int))func_801473EC)(param_1);
    ((void (*)(int))func_8014D738)(param_1);
    if (*(int *)(param_1 + 0x170) == 0) {
        (*D_8018DC08[*(unsigned short *)param_1])(param_1);
        ((void (*)(int, int))func_80147078)(param_1, 0);
        ((void (*)(int))func_80159B70)(param_1);
    } else {
        if (((int (*)(int))func_80161240)(param_1) == 0) {
            if (func_80146E98(param_1) != 0) {
                ((void (*)(int))func_80146CA0)(param_1);
            }
            if ((*(unsigned short *)(param_1 + 0xb8) & 0x2000) != 0) {
                func_80161C24(param_1, *(unsigned short *)(param_1 + 0x16e));
            }
        }
    }
}



// @class: schedule
// @stuck: none — MATCH (goto forces the func_80161240 block to the function tail; bnez-to-end layout vs early-return fall-through)


DEFINE_func_8015CA28()  /* dedup: shared engine-core @0x8015CA28 (src/shared) */


DEFINE_func_8015CB94()  /* dedup: shared engine-core @0x8015CB94 (src/shared) */

DEFINE_func_8015CBCC()  /* dedup: shared engine-core @0x8015CBCC (src/shared) */

DEFINE_func_8015CBD4()  /* dedup: shared engine-core @0x8015CBD4 (src/shared) */

DEFINE_func_8015CBDC()  /* dedup: shared engine-core @0x8015CBDC (src/shared) */

DEFINE_func_8015CBE4()  /* dedup: shared engine-core @0x8015CBE4 (src/shared) */

DEFINE_func_8015CBEC()  /* dedup: shared engine-core @0x8015CBEC (src/shared) */

DEFINE_func_8015CBF4()  /* dedup: shared engine-core @0x8015CBF4 (src/shared) */

DEFINE_func_8015CBFC()  /* dedup: shared engine-core @0x8015CBFC (src/shared) */

DEFINE_func_8015CC04()  /* dedup: shared engine-core @0x8015CC04 (src/shared) */

DEFINE_func_8015CC0C()  /* dedup: shared engine-core @0x8015CC0C (src/shared) */

DEFINE_func_8015CC40()  /* dedup: shared engine-core @0x8015CC40 (src/shared) */



DEFINE_func_8015CC74()  /* dedup: shared engine-core @0x8015CC74 (src/shared) */


DEFINE_func_8015CCB0()  /* dedup: shared engine-core @0x8015CCB0 (src/shared) */

DEFINE_func_8015CCD0()  /* dedup: shared engine-core @0x8015CCD0 (src/shared) */

#define NULL 0





s32 func_8015CD20(s32 arg0) {
    extern void (*D_8018DC08[])(struct Ent_8015CD20 *);
    extern u8 D_8018DBBC;
    extern u8 D_8018DDAC;
    extern u8 D_8018DDBC;

    s32 temp_v0;
    s32 var_v0;
    struct Sub_8015CD20 *sp;

    ((void(*)())func_80149FB0)();
    if (((s32(*)(struct Ent_8015CD20 *))func_801496D4)(((struct Ent_8015CD20 *)arg0)) != 0) {
        D_8018DC08[((struct Ent_8015CD20 *)arg0)->unk0](((struct Ent_8015CD20 *)arg0));
        ((struct Ent_8015CD20 *)arg0)->unk1BC = 0xA;
        ((s32(*)(struct Ent_8015CD20 *))func_80149724)(((struct Ent_8015CD20 *)arg0));
        if (((s32(*)(struct Ent_8015CD20 *))func_80148AFC)(((struct Ent_8015CD20 *)arg0)) & 0xFF) {
            ((void(*)(struct Ent_8015CD20 *, u8 *))func_80146DB8)(((struct Ent_8015CD20 *)arg0), &D_8018DBBC);
        } else {
            ((void(*)(struct Ent_8015CD20 *))func_80146D90)(((struct Ent_8015CD20 *)arg0));
        }
        return;
    }
    temp_v0 = ((struct Ent_8015CD20 *)arg0)->unk234;
    if (temp_v0 == 0) {
        if (((s32(*)(struct Ent_8015CD20 *))func_80148980)(((struct Ent_8015CD20 *)arg0)) != 0) {
            ((void(*)(struct Ent_8015CD20 *, u8 *))func_80146DB8)(((struct Ent_8015CD20 *)arg0), &D_8018DDAC);
            ((void(*)(struct Ent_8015CD20 *))func_80147A84)(((struct Ent_8015CD20 *)arg0));
            ((void(*)(struct Ent_8015CD20 *))func_801473EC)(((struct Ent_8015CD20 *)arg0));
            ((void(*)(struct Ent_8015CD20 *, s32))func_80154150)(((struct Ent_8015CD20 *)arg0), 0x15);
            sp = ((struct Ent_8015CD20 *)arg0)->unk20;
            var_v0 = sp->unk12 - 0xAA;
            goto block_13;
        }
        if (((s32(*)(struct Ent_8015CD20 *))func_8014891C)(((struct Ent_8015CD20 *)arg0)) != 0) {
            ((void(*)(struct Ent_8015CD20 *, u8 *))func_80146DB8)(((struct Ent_8015CD20 *)arg0), &D_8018DDBC);
            ((void(*)(struct Ent_8015CD20 *))func_80147A84)(((struct Ent_8015CD20 *)arg0));
            ((void(*)(struct Ent_8015CD20 *))func_801473EC)(((struct Ent_8015CD20 *)arg0));
            ((void(*)(struct Ent_8015CD20 *, s32))func_80154150)(((struct Ent_8015CD20 *)arg0), 0x14);
            ((struct Ent_8015CD20 *)arg0)->unkB8 = 1;
        }
        if (((s32(*)(struct Ent_8015CD20 *))func_801489E8)(((struct Ent_8015CD20 *)arg0)) != 0) {
            sp = ((struct Ent_8015CD20 *)arg0)->unk20;
            var_v0 = sp->unk12 + 0x71;
            goto block_13;
        }
        if (((s32(*)(struct Ent_8015CD20 *))func_80148A48)(((struct Ent_8015CD20 *)arg0)) != 0) {
            sp = ((struct Ent_8015CD20 *)arg0)->unk20;
            var_v0 = sp->unk12 - 0x71;
block_13:
            sp->unk12 = var_v0 & 0xFFF;
        }
    } else {
        ((struct Ent_8015CD20 *)arg0)->unk234 = temp_v0 - 1;
    }
    ((void(*)(struct Ent_8015CD20 *))func_8014FA04)(((struct Ent_8015CD20 *)arg0));
    if (((s32(*)(struct Ent_8015CD20 *))func_8014E434)(((struct Ent_8015CD20 *)arg0)) == 0) {
        D_8018DC08[((struct Ent_8015CD20 *)arg0)->unk0](((struct Ent_8015CD20 *)arg0));
        ((void(*)(struct Ent_8015CD20 *, s32))func_80147078)(((struct Ent_8015CD20 *)arg0), 0);
        ((void(*)(struct Ent_8015CD20 *))func_80159B70)(((struct Ent_8015CD20 *)arg0));
    } else {
        ((void(*)(struct Ent_8015CD20 *))func_801725E0)(((struct Ent_8015CD20 *)arg0));
    }
}



DEFINE_func_8015CF24()  /* dedup: shared engine-core @0x8015CF24 (src/shared) */

DEFINE_func_8015CF58()  /* dedup: shared engine-core @0x8015CF58 (src/shared) */

DEFINE_func_8015CF8C()  /* dedup: shared engine-core @0x8015CF8C (src/shared) */



DEFINE_func_8015CFC0()  /* dedup: shared engine-core @0x8015CFC0 (src/shared) */


DEFINE_func_8015CFFC()  /* dedup: shared engine-core @0x8015CFFC (src/shared) */

// @class: regalloc-order
// @stuck: none — MATCH (uVar1 pinned $s3, uVar5 pinned $s1; param_1->s2, iVar4->s0 fall out)


void func_8015D01C(int param_1) {
    extern s32 func_801725F4(u8 *a0);
    extern int D_800D550C;
    extern int D_8018DDCC;

    int iVar4;
    register unsigned short uVar1 __asm__("$19");
    register unsigned short uVar5 __asm__("$17");
    short sVar2;
    short sVar3;

    ((void (*)(int, void *))func_80154274)(param_1, &D_800D550C);
    *(short *)(*(int *)(param_1 + 0x20) + 0x10) = 0;
    iVar4 = *(short *)(*(int *)(param_1 + 0x20) + 0x12);
    uVar1 = *(unsigned short *)(*(int *)(*(int *)(param_1 + 0x180) + 0x20) + 0x12);
    uVar5 = (uVar1 + 0x800) & 0xfff;
    sVar2 = func_80012A60(iVar4, (short)uVar1);
    sVar3 = func_80012A60(iVar4, uVar5);
    if (sVar2 < sVar3) {
        *(short *)(*(int *)(param_1 + 0x20) + 0x12) = uVar1;
    } else {
        *(unsigned short *)(*(int *)(param_1 + 0x20) + 0x12) = uVar5;
    }
    *(int *)(param_1 + 0x38) = (int)&D_8018DDCC | 0x40000000;
    ((void (*)(int))func_801725F4)(param_1);
    ((void (*)(int))func_80146CA0)(param_1);
}





// @class: struct
// @stuck: none — MATCH (pending gate)

extern s32 func_80149FB0(s32 a0);
extern void func_8014FA04(s32 a0);
extern void func_8014E6A0(void);
extern void (*D_8018DC08[])(void *);
extern void func_80147078(s32 *a0, s16 a1);
extern void func_80159B70(void *a0);
extern s32 func_801725F4(u8 *a0);
extern void func_80146CA0(void *a0);

void func_8015D104(void *arg0) {
    ((void (*)(void))func_80149FB0)();
    ((void (*)(void *))func_8014FA04)(arg0);
    if (((s32 (*)(void *))func_8014E6A0)(arg0) == 0) {
        D_8018DC08[*(u16 *)arg0](arg0);
        ((void (*)(void *, s16))func_80147078)(arg0, 0);
        func_80159B70(arg0);
    } else {
        ((void (*)(void *))func_801725F4)(arg0);
        *(s32 *)((u8 *)arg0 + 0x234) = 0xFF1D0000;
        *(u16 *)(*(s32 *)((u8 *)arg0 + 0x20) + 0x10) = 0x600;
        *(u16 *)((u8 *)arg0 + 0x244) = *(u16 *)(*(s32 *)((u8 *)arg0 + 0x20) + 0x10);
        func_80146CA0(arg0);
    }
}



DEFINE_func_8015D1B8()  /* dedup: shared engine-core @0x8015D1B8 (src/shared) */



// @class: regalloc-order
// @stuck: pinning a0->$s1 and buffer-ptr->$s0; body copy already matches
extern void func_80013F3C(s32 a0);
extern void func_80012558(s32 a0, s32 a1);
extern void func_800126C4(s32 a0, s32 a1);
extern void ApplyMatrixSV(void *a0, void *a1, void *a2);
extern void *memcpy(void *dst, const void *src, u32 n);

extern s32 D_8018DE38;

void func_8015D380(s32 a0) {
    s16 out[4];
    s32 buf[8];
    register s32 s1 __asm__("$17") = a0;
    register s32 *s0 __asm__("$16") = buf;
    ((void (*)(void *))func_80013F3C)((void *)s0);
    ((void (*)(void *, s32))func_80012558)((void *)s0, *(s16 *)(*(s32 *)(s1 + 0x20) + 0x12));
    ((void (*)(void *, s32))func_800126C4)((void *)s0, *(s16 *)(*(s32 *)(s1 + 0x20) + 0x10));
    ApplyMatrixSV((void *)s0, (void *)&D_8018DE38, (void *)out);
    memcpy((void *)(s1 + 0x138), (void *)out, 8);
}




// @class: plumbing
// @stuck: none — MATCH

extern unsigned char D_8018CF1C[];

extern void func_801553C0(s32 a0);
extern void func_80154A74(s32 a0, s32 a1);

void func_8015D414(int param_1)
{
    *(unsigned char *)(param_1 + 0x1bd) = 8;
    *(unsigned char **)(param_1 + 0x38) = D_8018CF1C;
    *(short *)(param_1 + 0x138) = 0;
    *(short *)(param_1 + 0x13a) = 0;
    *(short *)(param_1 + 0x13c) = 0;
    *(short *)(param_1 + 0x13e) = 0;
    *(short *)(param_1 + 0xA) = *(short *)(param_1 + 0xA) + 0x48;
    *(short *)(*(int *)(param_1 + 0x20) + 0x10) = 0;
    ((void (*)(void))func_801553C0)();
    func_80154A74(param_1, 0x11);
}


DEFINE_func_8015D480()  /* dedup: shared engine-core @0x8015D480 (src/shared) */

DEFINE_func_8015D4B4()  /* dedup: shared engine-core @0x8015D4B4 (src/shared) */



DEFINE_func_8015D4E8()  /* dedup: shared engine-core @0x8015D4E8 (src/shared) */


DEFINE_func_8015D524()  /* dedup: shared engine-core @0x8015D524 (src/shared) */

DEFINE_func_8015D544()  /* dedup: shared engine-core @0x8015D544 (src/shared) */

DEFINE_func_8015D57C()  /* dedup: shared engine-core @0x8015D57C (src/shared) */


// @class: loose-typing
// @stuck: none — MATCH (field 0xb8 compared as u16 == 0x8000, not s16 == -0x8000)

DEFINE_func_8015D5E8()  /* dedup: shared engine-core @0x8015D5E8 (src/shared) */



DEFINE_func_8015D738()  /* dedup: shared engine-core @0x8015D738 (src/shared) */


DEFINE_func_8015DA5C()  /* dedup: shared engine-core @0x8015DA5C (src/shared) */

DEFINE_func_8015DA90()  /* dedup: shared engine-core @0x8015DA90 (src/shared) */

DEFINE_func_8015DAC4()  /* dedup: shared engine-core @0x8015DAC4 (src/shared) */



DEFINE_func_8015DAF8()  /* dedup: shared engine-core @0x8015DAF8 (src/shared) */


DEFINE_func_8015DB34()  /* dedup: shared engine-core @0x8015DB34 (src/shared) */

DEFINE_func_8015DB6C()  /* dedup: shared engine-core @0x8015DB6C (src/shared) */


// @class: struct
// @stuck: none — MATCH (mirrors byte-matched func_8015F89C/func_8015F9A4 in same overlay)

extern void (*D_8018DC08[])(void *);
extern int func_8015DD74(int);
extern void func_80147078(s32 *a0, s16 a1);
extern void func_80159B70(void *a0);
extern s32 func_80161208();
extern void func_8015DCB8(s32 a0);

void func_8015DBD4(void *arg0) {
    if (*(u16 *)((u8 *)arg0 + 0xB8) & 0x4000) {
        ((void (*)(void))func_8015DD74)();
    }
    if (*(u16 *)((u8 *)arg0 + 0xB8) == 0x8000) {
        D_8018DC08[*(u16 *)arg0](arg0);
        ((void (*)(void *, s16))func_80147078)(arg0, 0);
        func_80159B70(arg0);
    } else {
        if (*(s32 *)((u8 *)arg0 + 0x178) != 0) {
            ((void (*)(void *))func_8015DCB8)(arg0);
        }
        ((s32 (*)(void *))func_80161208)(arg0);
    }
}


DEFINE_func_8015DC84()  /* dedup: shared engine-core @0x8015DC84 (src/shared) */


// @class: other
// @stuck: none — MATCH (proxy gate)

extern s8 D_8018DE88[];
extern void func_80149374(s32 a0, s32 a1);

void func_8015DCB8(s32 param_1) {
    s32 iVar1;
    s32 iVar2;

    iVar2 = *(s32 *)(param_1 + 0x178);

    iVar1 = *(s32 *)(param_1 + 0x234);
    *(s32 *)(param_1 + 0x234) = iVar1 + 1;
    *(s16 *)(iVar2 + 6) = (s16)D_8018DE88[iVar1] + *(s16 *)(*(s32 *)(iVar2 + 0x78) + 0xc);

    iVar1 = *(s32 *)(param_1 + 0x234);
    *(s32 *)(param_1 + 0x234) = iVar1 + 1;
    *(s16 *)(iVar2 + 10) = (s16)D_8018DE88[iVar1] + *(s16 *)(*(s32 *)(iVar2 + 0x78) + 0xe);

    iVar1 = *(s32 *)(param_1 + 0x234);
    *(s32 *)(param_1 + 0x234) = iVar1 + 1;
    *(s16 *)(iVar2 + 0xe) = (s16)D_8018DE88[iVar1] + *(s16 *)(*(s32 *)(iVar2 + 0x78) + 0x10);

    func_80149374(param_1, iVar2 + 4);
}


DEFINE_func_8015DD74()  /* dedup: shared engine-core @0x8015DD74 (src/shared) */

DEFINE_func_8015DDF0()  /* dedup: shared engine-core @0x8015DDF0 (src/shared) */

DEFINE_func_8015DE24()  /* dedup: shared engine-core @0x8015DE24 (src/shared) */



DEFINE_func_8015DE58()  /* dedup: shared engine-core @0x8015DE58 (src/shared) */


DEFINE_func_8015DE94()  /* dedup: shared engine-core @0x8015DE94 (src/shared) */

DEFINE_func_8015DECC()  /* dedup: shared engine-core @0x8015DECC (src/shared) */


// @class: struct
// @stuck: none — MATCH (mirrors byte-matched func_8015F89C/func_8015F9A4 in same overlay)

extern void (*D_8018DC08[])(void *);
extern int func_8015E0D4(int);
extern void func_80147078(s32 *a0, s16 a1);
extern void func_80159B70(void *a0);
extern s32 func_80161208();
extern void func_8015E018(s32 a0);

void func_8015DF34(void *arg0) {
    if (*(u16 *)((u8 *)arg0 + 0xB8) & 0x4000) {
        ((void (*)(void))func_8015E0D4)();
    }
    if (*(u16 *)((u8 *)arg0 + 0xB8) == 0x8000) {
        D_8018DC08[*(u16 *)arg0](arg0);
        ((void (*)(void *, s16))func_80147078)(arg0, 0);
        func_80159B70(arg0);
    } else {
        if (*(s32 *)((u8 *)arg0 + 0x178) != 0) {
            ((void (*)(void *))func_8015E018)(arg0);
        }
        ((s32 (*)(void *))func_80161208)(arg0);
    }
}


DEFINE_func_8015DFE4()  /* dedup: shared engine-core @0x8015DFE4 (src/shared) */


// @class: other
// @stuck: none — MATCH (proxy gate)

extern s8 D_8018DE88[];
extern void func_80149374(s32 a0, s32 a1);

void func_8015E018(s32 param_1) {
    s32 iVar1;
    s32 iVar2;

    iVar2 = *(s32 *)(param_1 + 0x178);

    iVar1 = *(s32 *)(param_1 + 0x234);
    *(s32 *)(param_1 + 0x234) = iVar1 + 1;
    *(s16 *)(iVar2 + 6) = (s16)D_8018DE88[iVar1] + *(s16 *)(*(s32 *)(iVar2 + 0x78) + 0xc);

    iVar1 = *(s32 *)(param_1 + 0x234);
    *(s32 *)(param_1 + 0x234) = iVar1 + 1;
    *(s16 *)(iVar2 + 10) = (s16)D_8018DE88[iVar1] + *(s16 *)(*(s32 *)(iVar2 + 0x78) + 0xe);

    iVar1 = *(s32 *)(param_1 + 0x234);
    *(s32 *)(param_1 + 0x234) = iVar1 + 1;
    *(s16 *)(iVar2 + 0xe) = (s16)D_8018DE88[iVar1] + *(s16 *)(*(s32 *)(iVar2 + 0x78) + 0x10);

    func_80149374(param_1, iVar2 + 4);
}


DEFINE_func_8015E0D4()  /* dedup: shared engine-core @0x8015E0D4 (src/shared) */

DEFINE_func_8015E150()  /* dedup: shared engine-core @0x8015E150 (src/shared) */

DEFINE_func_8015E184()  /* dedup: shared engine-core @0x8015E184 (src/shared) */



DEFINE_func_8015E1B8()  /* dedup: shared engine-core @0x8015E1B8 (src/shared) */


DEFINE_func_8015E1F4()  /* dedup: shared engine-core @0x8015E1F4 (src/shared) */

DEFINE_func_8015E22C()  /* dedup: shared engine-core @0x8015E22C (src/shared) */

DEFINE_func_8015E288()  /* dedup: shared engine-core @0x8015E288 (src/shared) */


// @class: struct
// @stuck: none — MATCH (pending whole-binary gate); fn-ptr table folds %lo via extern array, 0x234 single word store


extern void func_8015E40C(s32 a0);
extern s32 func_80161B18(void *a0);
extern s32 func_80161B84(void *a0);
extern s32 func_80161208();
extern void func_8015E5B0(u8*);
extern void func_80147078(s32 *a0, s16 a1);
extern void func_80159BE4(s32 arg0);

extern void (*D_8018DC08[])(void*);

void func_8015E344(u16 *param_1)
{
    ((s32 (*)(void))func_8015E40C)();
    if (((s32 (*)(u16 *))func_80161B18)(param_1) == 0 &&
        ((s32 (*)(u16 *))func_80161B84)(param_1) == 0 &&
        ((s32 (*)(u16 *))func_80161208)(param_1) == 0) {
        if ((param_1[0x5c] & 0x4000) != 0) {
            ((void (*)(u16 *))func_8015E5B0)(param_1);
            *(s32 *)((char *)param_1 + 0x234) = 1;
        }
        if ((param_1[0x5c] & 0x8000) != 0) {
            ((void (**)(u16*))D_8018DC08)[param_1[0]](param_1);
            ((s32 (*)(u16 *, s32))func_80147078)(param_1, 0);
            ((s32 (*)(u16 *))func_80159BE4)(param_1);
        }
    }
}


DEFINE_func_8015E40C()  /* dedup: shared engine-core @0x8015E40C (src/shared) */


// @class: struct
// @stuck: none — MATCH (pending whole-binary gate); s16 v[3] array forces all 3 locals addressable (reload-from-stack), u16* psVar1 → lhu null/flag check


extern u16 D_8018DED0;
extern u16 D_8018DED2;
extern u16 D_8018DED4;
extern s32 D_8018DED8;

extern void func_80149350(s32 arg0);
extern void func_80013E94(void *a0, void *a1);
extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);

void func_8015E4B0(s32 param_1)
{
    u16 *psVar1;
    s16 v[3];
    s32 local_10;

    psVar1 = *(u16 **)(param_1 + 0x18c);
    if ((psVar1 != (u16 *)0) && (*psVar1 != 0)) {
        v[0] = D_8018DED0 + *(u16 *)(*(s32 *)(psVar1 + 0x3c) + 0xc);
        v[1] = D_8018DED2 + *(s16 *)(*(s32 *)(psVar1 + 0x3c) + 0xe) * 2;
        v[2] = D_8018DED4 + *(u16 *)(*(s32 *)(psVar1 + 0x3c) + 0x10);
        ((s32 (*)(s32, s16 *, s16 *))func_80149350)(param_1, &v[0], &v[0]);
        ((s32 (*)(s32 *, s32 *))func_80013E94)(&D_8018DED8, &local_10);
        ((s32 (*)(s32, s32, s32, s32, s32, s32, s32))func_80146A6C)(0x1f, param_1, v[0], v[1], v[2], local_10, 0);
    }
    return;
}




DEFINE_func_8015E588()  /* dedup: shared engine-core @0x8015E588 (src/shared) */


DEFINE_func_8015E5B0()  /* dedup: shared engine-core @0x8015E5B0 (src/shared) */


// @class: struct
// @stuck: none — MATCH (clean -O2 reconstruction; table-of-fnptr indexed by param_1[0])


extern s32 func_80161208();
extern void func_80147078(s32 *a0, s16 a1);
extern void func_80159BE4(s32 arg0);

/* function-pointer dispatch table */
extern void (*D_8018DC08[])(void*);

void func_8015E698(u16 *param_1)
{
    if (func_80161208() == 0 && (param_1[0x5c] & 0x8000) != 0) {
        ((void (**)(u16*))D_8018DC08)[param_1[0]](param_1);
        ((void (*)(u16 *, s32))func_80147078)(param_1, 0);
        ((void (*)(u16 *))func_80159BE4)(param_1);
    }
}


DEFINE_func_8015E714()  /* dedup: shared engine-core @0x8015E714 (src/shared) */

DEFINE_func_8015E84C()  /* dedup: shared engine-core @0x8015E84C (src/shared) */

DEFINE_func_8015E880()  /* dedup: shared engine-core @0x8015E880 (src/shared) */

DEFINE_func_8015E8B4()  /* dedup: shared engine-core @0x8015E8B4 (src/shared) */



DEFINE_func_8015E8E8()  /* dedup: shared engine-core @0x8015E8E8 (src/shared) */


DEFINE_func_8015E924()  /* dedup: shared engine-core @0x8015E924 (src/shared) */

DEFINE_func_8015E95C()  /* dedup: shared engine-core @0x8015E95C (src/shared) */

DEFINE_func_8015E9B8()  /* dedup: shared engine-core @0x8015E9B8 (src/shared) */


DEFINE_func_8015EA3C()  /* dedup: shared engine-core @0x8015EA3C (src/shared) */


DEFINE_func_8015ED6C()  /* dedup: shared engine-core @0x8015ED6C (src/shared) */

DEFINE_func_8015EDA0()  /* dedup: shared engine-core @0x8015EDA0 (src/shared) */

DEFINE_func_8015EDD4()  /* dedup: shared engine-core @0x8015EDD4 (src/shared) */



DEFINE_func_8015EE08()  /* dedup: shared engine-core @0x8015EE08 (src/shared) */


DEFINE_func_8015EE44()  /* dedup: shared engine-core @0x8015EE44 (src/shared) */


// @class: plumbing
// @stuck: none — MATCH (straight STUB call sequence; param saved to $s0 across calls)

extern void func_8014CBF8(void *a0);
extern void func_801474EC(s32 *a0);
extern void func_80154274(s32 *a0, s32 a1);
extern void func_80146DB8(s32 *a0, s32 *a1);
extern void func_801477E8(s32 *a0, s32 a1);
extern void func_80146CA0(void *a0);

extern int D_800D4C48;
extern int D_8018DBEC;

void func_8015EE7C(s32 param_1)
{
    ((int (*)(void))func_8014CBF8)();
    ((int (*)(int))func_801474EC)(param_1);
    ((int (*)(int, void *))func_80154274)(param_1, &D_800D4C48);
    ((int (*)(int, void *))func_80146DB8)(param_1, &D_8018DBEC);
    ((int (*)(int, int))func_801477E8)(param_1, 0xFFF40000);
    ((int (*)(int))func_80146CA0)(param_1);
}



extern void (*D_8018DC08[])(void *);

extern void func_80148038(s32 a0, s32 a1);
extern void func_80147460(s32 a0);
extern void func_80147AD4(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_801473EC(s32 *a0);
extern void func_80147078(s32 *a0, s16 a1);
extern void func_80159B70(void *a0);
extern void func_80161418(void *a0);
extern s32 func_801725A4(u8 *a0);

void func_8015EEE0(void *arg0)
{
    ((void (*)(void *, s32))func_80148038)(arg0, 0x10000);
    ((void (*)(void *))func_80147460)(arg0);
    ((void (*)(void *, s32, s32, s32))func_80147AD4)(arg0, 0, 0, 0x1000);
    ((void (*)(void *))func_801473EC)(arg0);
    if (*(u16 *)((u8 *)arg0 + 0xB8) & 0x8000) {
        D_8018DC08[*(u16 *)arg0](arg0);
        ((void (*)(void *, s32))func_80147078)(arg0, 0);
        func_80159B70(arg0);
    } else {
        if (((s32 (*)(void *))func_80161418)(arg0) == 0) {
            ((void (*)(void *))func_801725A4)(arg0);
        }
    }
}


DEFINE_func_8015EF9C()  /* dedup: shared engine-core @0x8015EF9C (src/shared) */

DEFINE_func_8015EFA4()  /* dedup: shared engine-core @0x8015EFA4 (src/shared) */

DEFINE_func_8015EFD8()  /* dedup: shared engine-core @0x8015EFD8 (src/shared) */



DEFINE_func_8015F00C()  /* dedup: shared engine-core @0x8015F00C (src/shared) */


DEFINE_func_8015F048()  /* dedup: shared engine-core @0x8015F048 (src/shared) */

DEFINE_func_8015F080()  /* dedup: shared engine-core @0x8015F080 (src/shared) */

DEFINE_func_8015F118()  /* dedup: shared engine-core @0x8015F118 (src/shared) */


DEFINE_func_8015F260()  /* dedup: shared engine-core @0x8015F260 (src/shared) */

DEFINE_func_8015F2BC()  /* dedup: shared engine-core @0x8015F2BC (src/shared) */

DEFINE_func_8015F2F0()  /* dedup: shared engine-core @0x8015F2F0 (src/shared) */



DEFINE_func_8015F324()  /* dedup: shared engine-core @0x8015F324 (src/shared) */


DEFINE_func_8015F360()  /* dedup: shared engine-core @0x8015F360 (src/shared) */

DEFINE_func_8015F380()  /* dedup: shared engine-core @0x8015F380 (src/shared) */


DEFINE_func_8015F448()  /* dedup: shared engine-core @0x8015F448 (src/shared) */


DEFINE_func_8015F738()  /* dedup: shared engine-core @0x8015F738 (src/shared) */

DEFINE_func_8015F76C()  /* dedup: shared engine-core @0x8015F76C (src/shared) */

DEFINE_func_8015F7A0()  /* dedup: shared engine-core @0x8015F7A0 (src/shared) */



DEFINE_func_8015F7D4()  /* dedup: shared engine-core @0x8015F7D4 (src/shared) */


DEFINE_func_8015F810()  /* dedup: shared engine-core @0x8015F810 (src/shared) */

DEFINE_func_8015F848()  /* dedup: shared engine-core @0x8015F848 (src/shared) */


extern void (*D_8018DC08[])(void *);
extern void func_801466F0(s32, s32, s32, s32, s32, s32, s32, s32);
extern void func_80147078(s32 *, s16);
extern void func_80159B70(void *);
extern s32 func_80161208(void);

void func_8015F89C(void *arg0) {
    u16 flags = *(u16 *)((u8 *)arg0 + 0xB8);
    if (!(flags & 0x4000)) {
        if (flags & 0x8000) {
            D_8018DC08[*(u16 *)arg0](arg0);
            func_80147078(arg0, 0);
            func_80159B70(arg0);
            return;
        }
    } else {
        func_801466F0(1, arg0, 0, -0x1E, 0, 0, 0, 0);
    }
    ((s32 (*)(void *))func_80161208)(arg0);
}


DEFINE_func_8015F948()  /* dedup: shared engine-core @0x8015F948 (src/shared) */


extern void (*D_8018DC08[])(void *);
extern void func_80147078(s32 *a0, s16 a1);
extern void func_80159B70(void *a0);
extern s32 func_80161208(void);

void func_8015F9A4(void *arg0) {
    if (*(u16 *)((u8 *)arg0 + 0xB8) & 0x8000) {
        D_8018DC08[*(u16 *)arg0](arg0);
        func_80147078(arg0, 0);
        func_80159B70(arg0);
    } else {
        ((s32 (*)(void *))func_80161208)(arg0);
    }
}


DEFINE_func_8015FA24()  /* dedup: shared engine-core @0x8015FA24 (src/shared) */

DEFINE_func_8015FA44()  /* dedup: shared engine-core @0x8015FA44 (src/shared) */

DEFINE_func_8015FA78()  /* dedup: shared engine-core @0x8015FA78 (src/shared) */



DEFINE_func_8015FAAC()  /* dedup: shared engine-core @0x8015FAAC (src/shared) */



extern s32 func_801612B8(void *a0, s32 a1);
extern void func_8016007C(s32 a0);
extern void (*D_8018DC08[])(void *);
extern void func_80147078(s32 *a0, s16 a1);
extern s32 func_8015BE94();
extern void func_8015C0C4(s32 a0);
extern void func_8015FBE0(s32 *a0);

void func_8015FAE8(void *arg0) {
    s32 v;

    v = func_801612B8(arg0, 0);
    if (v == 0 || v == 0x8000) {
        ((void (*)(void *))func_8016007C)(arg0);
        *(u32 *)((u8 *)arg0 + 0x184) |= 0x80000000;
        D_8018DC08[*(u16 *)arg0](arg0);
        ((void (*)(void *, s16))func_80147078)(arg0, 3);
        ((void (*)(void *))func_8015BE94)(arg0);
    } else if ((v & 0x4000) != 0) {
        ((void (*)(void *))func_8016007C)(arg0);
        *(u32 *)((u8 *)arg0 + 0x184) |= 0x80000000;
        D_8018DC08[*(u16 *)arg0](arg0);
        ((void (*)(void *, s16))func_80147078)(arg0, 4);
        ((void (*)(void *))func_8015C0C4)(arg0);
    } else {
        ((void (*)(void *))func_8015FBE0)(arg0);
    }
}



extern void func_80147078(s32 *a0, s16 a1);
extern void func_80159B70(void *a0);
extern void func_80154150(s32 a0, s32 a1);
extern void func_80154A74(s32 a0, s32 a1);
extern s32 func_80146A6C(s32, void*, s32, s32, s32, s32, s32);
extern void func_80147324(s32 a0);
extern void func_801553A8(s32 *a0);
extern void func_801553C0(s32 a0);
extern void func_80146CA0(void *a0);


void func_8015FBE0(s32 *param_1)
{

    extern u8 D_800B9A17;
    if (param_1[0x61] < 0) {
        ((void (**)())D_8018DC08)[*(u16 *)param_1]();
        ((void (*)(s32 *, s16))func_80147078)(param_1, 0);
        ((void (*)(s32 *))func_80159B70)(param_1);
    } else {
        __asm__ __volatile__("");
        D_80078EC1 = 0;
        ((void (*)(s32 *, s32))func_80154150)(param_1, 0x20);
        ((void (*)(s32 *, s32))func_80154A74)(param_1, 0x18);
        ((void (*)(s32, s32 *, s32, s32, s32, s32, s32))func_80146A6C)(0x16, param_1, 0, 0, 0, 0, 0);
        func_80147324(0x44F);
        ((void (*)(s32 *))func_801553A8)(param_1);
        ((void (*)(s32 *))func_801553C0)(param_1);
        D_801270C0 = 2;
        D_800B9A17 = 0;
        ((void (*)(s32 *))func_80146CA0)(param_1);
    }
}


extern void func_801599A4(void *a0);

// @class: struct
// @stuck: none — MATCH (indexed fn-ptr table call + byte-offset struct stores; mirrors sibling func_801599A4 idiom)

extern s32 D_800AE6B0;
extern void (*D_8018DC08[])(void *);

extern void func_8016007C(s32 a0);
extern void func_80147078(s32 *a0, s16 a1);
extern void func_80159B70(void *a0);
extern void func_8014BFF4(s32 a0, s32 a1);
extern void func_80146CA0(void *a0);

void func_8015FCC8(void *param_1) {
    if ((D_800AE6B0 & 0x80FFFFFF) != 0) {
        ((void (*)(void))func_8016007C)();
        D_8018DC08[*(u16 *)param_1](param_1);
        ((void (*)(void *, s32))func_80147078)(param_1, 0);
        func_80159B70(param_1);
    } else {
        *(u8 *)((s32)param_1 + 0x197) = 0;
        *(u8 *)((s32)param_1 + 0xBE) = 0;
        *(u8 *)((s32)param_1 + 0xBF) = 0;
        *(u8 *)((s32)param_1 + 0x1A0) = (u8)*(s32 *)((s32)param_1 + 0x184);
        ((s32 (*)(void *, s32))func_8014BFF4)(param_1, 1);
        func_80146CA0(param_1);
    }
}



// @class: plumbing
// @stuck: none — MATCH expected; simple 3-call sequence with global table index

extern unsigned int D_8018DF64[];

extern void func_80147324(s32 arg0);
extern s32 func_8013767C(s32 a0);
extern void func_80146CA0(void *a0);

void func_8015FD74(int param_1)
{
    ((int (*)(int))func_80147324)(0x18);
    *(int *)(param_1 + 0x198) = func_8013767C(D_8018DF64[*(unsigned char *)(param_1 + 0x1a0)]);
    ((int (*)(int))func_80146CA0)(param_1);
}


DEFINE_func_8015FDCC()  /* dedup: shared engine-core @0x8015FDCC (src/shared) */


// @class: struct
// @stuck: none — MATCH expected (fn-ptr-table dispatch + ushort struct fields)


extern void (*D_8018DC08[])(void*);
extern void func_80147078(s32 *a0, s16 a1);
extern void func_80159B70(void *a0);
extern void func_80154A74(s32 a0, s32 a1);
extern s32 func_80161208();

void func_8015FE70(u16 *param_1)
{
    if ((param_1[0x5c] & 0x8000) != 0) {
        if (param_1[0x5d] == 0) {
            ((void (**)())D_8018DC08)[param_1[0]]();
            ((void (*)(u16 *, s16))func_80147078)(param_1, 0);
            ((void (*)(u16 *))func_80159B70)(param_1);
            return;
        }
        param_1[0x5c] = param_1[0x5d];
    }
    if ((param_1[0x5c] & 0x4000) != 0) {
        ((void (*)(u16 *, s16))func_80154A74)(param_1, 0x11);
    }
    ((void (*)(u16 *))func_80161208)(param_1);
}



extern s32 D_800AE6B0;
extern void (*D_8018DC08[])(void *);
extern u8 D_80078EC1;
extern u8 D_80078EC2;
extern u16 D_801270C0;

extern void func_8016007C(s32 a0);
extern void func_80147078(s32 *a0, s16 a1);
extern void func_80159B70(void *a0);
extern u8 func_801656E8(s32 a0, s32 a1);
extern void func_80150820(s32 a0, s32 a1);
extern void func_8014BFF4(s32 a0, s32 a1);
extern void func_80165670(s32 a0, s32 a1);
extern void func_80165840(void);
extern void func_801658DC(void);
extern void func_80154A74(s32 a0, s32 a1);
extern void func_8016004C(s32 a0);

void func_8015FF20(void *param_1) {
    s32 v2;
    u8 cur;

    if ((D_800AE6B0 & 0x80FFFFFF) != 0) {
        ((void (*)(void))func_8016007C)();
        D_8018DC08[*(u16 *)param_1](param_1);
        ((void (*)(void *, s16))func_80147078)(param_1, 0);
        func_80159B70(param_1);
        return;
    }

    v2 = *(s32 *)((s32)param_1 + 0x184);
    if (v2 < 0) {
        func_80150820((s32)param_1, func_801656E8((s32)param_1, v2 & 0xFF) & 0xFF);
    } else {
        if (*(u8 *)((s32)param_1 + 0x1A0) != *(u8 *)((s32)param_1 + 0x196)) {
            *(u8 *)((s32)param_1 + 0x1A0) = (u8)v2;
            *(u8 *)((s32)param_1 + 0x197) = 0;
            *(u8 *)((s32)param_1 + 0xBE) = 0;
            *(u8 *)((s32)param_1 + 0xBF) = 0;
            func_8014BFF4((s32)param_1, 1);
        }

        cur = *(u8 *)((s32)param_1 + 0x1A0);
        D_80078EC1 = cur;
        D_80078EC2 = cur;
        func_80165670((s32)param_1, cur);
        ((void (*)(void *))func_80165840)(param_1);
        ((void (*)(void *))func_801658DC)(param_1);
        func_80154A74((s32)param_1, 0x11);
        D_801270C0 = 1;
    }

    ((void (*)(void *))func_8016004C)(param_1);
}


DEFINE_func_8016004C()  /* dedup: shared engine-core @0x8016004C (src/shared) */

DEFINE_func_8016007C()  /* dedup: shared engine-core @0x8016007C (src/shared) */

DEFINE_func_801600D0()  /* dedup: shared engine-core @0x801600D0 (src/shared) */

DEFINE_func_80160104()  /* dedup: shared engine-core @0x80160104 (src/shared) */



DEFINE_func_80160138()  /* dedup: shared engine-core @0x80160138 (src/shared) */


DEFINE_func_80160174()  /* dedup: shared engine-core @0x80160174 (src/shared) */

DEFINE_func_801601AC()  /* dedup: shared engine-core @0x801601AC (src/shared) */

DEFINE_func_801601E4()  /* dedup: shared engine-core @0x801601E4 (src/shared) */

DEFINE_func_80160244()  /* dedup: shared engine-core @0x80160244 (src/shared) */


extern void (*D_8018DC08[])(void*);
extern void func_80154A74(s32 a0, s32 a1);
extern void func_80147078(s32 *a0, s16 a1);
extern void func_80159B70(void *a0);
extern s32 func_80161208();

void func_801602A4(s32 *a0) {
    if (*(u16 *)((u8 *)a0 + 0xB8) == 0x8000) {
        ((void (**)())D_8018DC08)[*(u16 *)a0]();
        func_80154A74((s32)a0, 0x11);
        ((void (*)(s32, s32))func_80147078)((s32)a0, 0);
        func_80159B70(a0);
    } else {
        ((s32 (*)(s32 *))func_80161208)(a0);
    }
}


DEFINE_func_8016032C()  /* dedup: shared engine-core @0x8016032C (src/shared) */

DEFINE_func_80160334()  /* dedup: shared engine-core @0x80160334 (src/shared) */

DEFINE_func_80160368()  /* dedup: shared engine-core @0x80160368 (src/shared) */



DEFINE_func_8016039C()  /* dedup: shared engine-core @0x8016039C (src/shared) */


DEFINE_func_801603D8()  /* dedup: shared engine-core @0x801603D8 (src/shared) */

DEFINE_func_80160410()  /* dedup: shared engine-core @0x80160410 (src/shared) */







/* data */
DEFINE_func_80160534()  /* dedup: shared engine-core @0x80160534 (src/shared) */


DEFINE_func_801607B8()  /* dedup: shared engine-core @0x801607B8 (src/shared) */

DEFINE_func_801607E4()  /* dedup: shared engine-core @0x801607E4 (src/shared) */

DEFINE_func_80160818()  /* dedup: shared engine-core @0x80160818 (src/shared) */



DEFINE_func_8016084C()  /* dedup: shared engine-core @0x8016084C (src/shared) */


DEFINE_func_80160888()  /* dedup: shared engine-core @0x80160888 (src/shared) */

DEFINE_func_801608C0()  /* dedup: shared engine-core @0x801608C0 (src/shared) */


// @class: struct
// @stuck: none — MATCH (function-pointer table folds %lo via extern array indexed by halfword)


extern void (*D_8018DC08[])(void*);

extern u16 func_801487F4(s32 *a0);
extern s32 func_80161208();
extern void func_80160A74(s32 *a0);
extern void func_80154150(s32 a0, s32 a1);
extern void func_80146CA0(void *a0);

void func_80160920(unsigned short *param_1)
{
    if ((((int (*)(void))func_801487F4)() & 8) == 0) {
        ((code *)D_8018DC08)[*param_1](param_1);
        ((void (*)(unsigned short *))func_80160A74)(param_1);
    } else {
        if (((int (*)(unsigned short *))func_80161208)(param_1) == 0 && param_1[0x5c] == 0x8000) {
            ((void (*)(unsigned short *, int))func_80154150)(param_1, 0x25);
            ((void (*)(unsigned short *))func_80146CA0)(param_1);
        }
    }
    return;
}




// @class: struct
// @stuck: none — MATCH (pending byte-gate); function-pointer table %lo-fold via extern array


extern u16 func_801487F4(s32 *a0);
extern void func_80160A74(s32 *a0);
extern s32 func_80161208();

/* function-pointer dispatch table; indexed by *param_1 (×4 = ptr size) */
extern void (*D_8018DC08[])(void*);

void func_801609B8(u16 *param_1) {
    if ((((u32 (*)(void))func_801487F4)() & 8) == 0) {
        ((void (**)(u16*))D_8018DC08)[*param_1](param_1);
        ((void (*)(u16 *))func_80160A74)(param_1);
    } else {
        ((void (*)(u16 *))func_80161208)(param_1);
    }
}


DEFINE_func_80160A28()  /* dedup: shared engine-core @0x80160A28 (src/shared) */

DEFINE_func_80160A74()  /* dedup: shared engine-core @0x80160A74 (src/shared) */

DEFINE_func_80160ACC()  /* dedup: shared engine-core @0x80160ACC (src/shared) */

DEFINE_func_80160B00()  /* dedup: shared engine-core @0x80160B00 (src/shared) */



DEFINE_func_80160B34()  /* dedup: shared engine-core @0x80160B34 (src/shared) */


DEFINE_func_80160B70()  /* dedup: shared engine-core @0x80160B70 (src/shared) */

DEFINE_func_80160BB4()  /* dedup: shared engine-core @0x80160BB4 (src/shared) */

DEFINE_func_80160C28()  /* dedup: shared engine-core @0x80160C28 (src/shared) */

DEFINE_func_80160CB4()  /* dedup: shared engine-core @0x80160CB4 (src/shared) */


// @class: struct
// @stuck: none — MATCH (mirrors byte-matched func_8015DBD4 in same overlay; dispatch via D_8018DC08 + func_80147078/func_80159B70 tail, func_80161208 else)

extern void (*D_8018DC08[])(void *);
extern u16 func_80148800(s32 *a0);
extern void func_80147078(s32 *a0, s16 a1);
extern void func_80159B70(void *a0);
extern s32 func_80161208();

void func_80160D10(void *arg0) {
    if (*(u32 *)((u8 *)arg0 + 0x44) & 0x10) {
        D_8018DC08[*(u16 *)arg0](arg0);
    } else {
        if (*(s32 *)((u8 *)arg0 + 0x1AC) == 0) {
            if ((((s32 (*)(void *))func_80148800)(arg0) & 0xF0) == 0) {
                goto dd0;
            }
        } else {
            s32 t = *(s32 *)((u8 *)arg0 + 0x1AC) - 0xAAA8;
            *(s32 *)((u8 *)arg0 + 0x1AC) = t;
            if (t >= 0) {
                goto dd0;
            }
        }
        D_8018DC08[*(u16 *)arg0](arg0);
    }
    ((void (*)(void *, s16))func_80147078)(arg0, 0);
    func_80159B70(arg0);
    return;
dd0:
    ((s32 (*)(void *))func_80161208)(arg0);
}


DEFINE_func_80160DEC()  /* dedup: shared engine-core @0x80160DEC (src/shared) */

DEFINE_func_80160E3C()  /* dedup: shared engine-core @0x80160E3C (src/shared) */

DEFINE_func_80160E70()  /* dedup: shared engine-core @0x80160E70 (src/shared) */


DEFINE_func_80160EA4()  /* dedup: shared engine-core @0x80160EA4 (src/shared) */


DEFINE_func_80160EE0()  /* dedup: shared engine-core @0x80160EE0 (src/shared) */

DEFINE_func_80160F00()  /* dedup: shared engine-core @0x80160F00 (src/shared) */

DEFINE_func_80160F70()  /* dedup: shared engine-core @0x80160F70 (src/shared) */

DEFINE_func_80160FE0()  /* dedup: shared engine-core @0x80160FE0 (src/shared) */


// @class: struct
// @stuck: none — MATCH

extern void func_80149020(s32 *a0);
extern void (*D_8018DC08[])(void *);
extern void func_80147078(s32 *a0, s16 a1);
extern void func_80159B70(void *a0);

void func_80161034(void *a0)
{
    func_80149020(a0);
    D_8018DC08[*(u16 *)a0](a0);
    func_80147078(a0, 0);
    func_80159B70(a0);
}


DEFINE_func_80161094()  /* dedup: shared engine-core @0x80161094 (src/shared) */

DEFINE_func_801610FC()  /* dedup: shared engine-core @0x801610FC (src/shared) */

DEFINE_func_80161104()  /* dedup: shared engine-core @0x80161104 (src/shared) */

DEFINE_func_80161124()  /* dedup: shared engine-core @0x80161124 (src/shared) */

extern s32 func_801612B8(void *a0, s32 a1);
extern void func_8016130C(void*, s32);
void aF80161208(void *a0) __asm__("func_80161208");
void aF80161208(void *a0)
{
    ((s32 (*)(s32, u32))func_8016130C)(a0, func_801612B8(a0, 0));
}


DEFINE_func_80161240()  /* dedup: shared engine-core @0x80161240 (src/shared) */

DEFINE_func_80161278()  /* dedup: shared engine-core @0x80161278 (src/shared) */

DEFINE_func_801612B8()  /* dedup: shared engine-core @0x801612B8 (src/shared) */

extern void func_80161240(void *a0);
extern s32 func_801612B8(void * a0, s32 a1);
#define SHB(x) __asm__ __volatile__("" : "=r"(x) : "0"(x))
#define SHB(x) __asm__("" : "=r"(x) : "0"(x))

extern void func_801599A4(void*);
extern void func_8015BDD0(s32*);
extern void func_8015BF48(s32*);

/* REDRAFT (decay axis: RETURN TYPE). The stored draft had been flipped to
 * `void` to fit the fleet header decl in src/shared/engine_core.h, while the
 * body still `return 1; / return 0;`. gcc-2.7.2 silently drops the $v0 sets in
 * that situation, costing the three `addiu $v0, $zero, 1` / `addu $v0,$zero,$zero`
 * instructions the ASM plainly has. Restored to s32 (§109/§85 — the single call
 * site `func_8016130C(a0, func_801612B8(a0, 1));` discards the result, so the
 * void->s32 widen is caller-neutral and must be fixed on the HEADER side). */

/* RECONCILE (§37/§124 asm-label alias — zero header touch).
 * Gate error: jr_8015C32C.c:3501 conflicting types for `func_8016130C'
 *             :3479 previous declaration.
 * TU line 3479 is `DEFINE_func_80161240()`, whose expansion (engine_core.h:3781)
 * declares `extern void func_8016130C(void *a0, s32 a1);` — a RETURN-TYPE
 * disagreement with this draft's required `s32`.  The third line the gate quoted
 * (:5228 "location of previous definition") is unrelated noise: it is the
 * pre-existing `#define SHB(x)` redefinition *warning* between TU lines 5227 and
 * 5538, present with or without this draft.
 * Fix: the C identifier becomes aF8016130C, so it never collides with the
 * canonical `void func_8016130C` declaration, while the GNU asm label makes the
 * EMITTED symbol `func_8016130C`.  The macro's caller func_80161240 keeps calling
 * the `extern void` spelling and is byte-unaffected (it discards the return).
 * Codegen for this function is untouched — match_one still MATCH.
 * (Alternative, house style, NOT taken here per the no-header-edit rule: widen
 * src/shared/engine_core.h:3781 to `extern s32 func_8016130C(void *a0, s32 a1);`
 * and rename back to the plain name — byte-identical either way.) */

s32 aF8016130C(void *a0, s32 a1) __asm__("func_8016130C");

s32 aF8016130C(void *a0, s32 a1)
{
    if ((a1 == 0) || (a1 == 0x8000)) {
        func_801599A4(a0);
        ((void (*)(void *))func_8015BDD0)(a0);
        return 1;
    }
    if ((a1 & 0x4000) != 0) {
        func_801599A4(a0);
        ((void (*)(void *))func_8015BF48)(a0);
        return 1;
    }
    return 0;
}



// @class: schedule
// @stuck: none — MATCH


DEFINE_func_80161374()  /* dedup: shared engine-core @0x80161374 (src/shared) */


DEFINE_func_80161418()  /* dedup: shared engine-core @0x80161418 (src/shared) */

DEFINE_func_80161450()  /* dedup: shared engine-core @0x80161450 (src/shared) */

DEFINE_func_80161488()  /* dedup: shared engine-core @0x80161488 (src/shared) */

DEFINE_func_801614E4()  /* dedup: shared engine-core @0x801614E4 (src/shared) */

DEFINE_func_8016151C()  /* dedup: shared engine-core @0x8016151C (src/shared) */

DEFINE_func_80161554()  /* dedup: shared engine-core @0x80161554 (src/shared) */

DEFINE_func_8016158C()  /* dedup: shared engine-core @0x8016158C (src/shared) */

DEFINE_func_801615C4()  /* dedup: shared engine-core @0x801615C4 (src/shared) */



// @class: other
// @stuck: first draft — plain if-chain over the flag bits
extern void func_801599A4(void *a0);
extern void func_80159B3C(void *a0);
extern void func_8015BF48(s32 *a0);
extern void func_8015F2F0(s32 *a0);
extern void func_8014C010(s32 a0, s32 a1);
extern void func_80161D20(int param_1, u32 param_2);
extern s32 func_8014A6C4(s32 a0);
extern s32 ratan2(s32 a0, s32 a1);

s32 func_8016163C(s32 arg0, u32 arg1) {

    extern s16 D_801152B0;
    extern s16 D_801152B4;
    if (arg1 & 1) {
        func_801599A4((void *)arg0);
        func_80159B3C((void *)arg0);
        func_8014C010(arg0, 1);
        ((void (*)(s32, s32))func_80161D20)(arg0, *(u16 *)(arg0 + 0x16E));
        return 1;
    }
    if (arg1 & 0x4000) {
        func_801599A4((void *)arg0);
        func_8015BF48((s32 *)arg0);
        func_8014C010(arg0, 1);
        ((void (*)(s32, s32))func_80161D20)(arg0, *(u16 *)(arg0 + 0x16E));
        return 2;
    }
    if (arg1 & 0x2000) {
        func_801599A4((void *)arg0);
        func_80159B3C((void *)arg0);
        func_8014C010(arg0, 1);
        ((void (*)(s32, s32))func_80161D20)(arg0, *(u16 *)(arg0 + 0x16E));
        return 4;
    }
    if (arg1 & 0x8000) {
        if (*(u16 *)(arg0 + 0x16C) != 0x15) {
            return 0;
        }
        if (func_8014A6C4(arg0) != 0) {
            func_801599A4((void *)arg0);
            func_8015F2F0((s32 *)arg0);
            *(s16 *)(*(s32 *)(arg0 + 0x20) + 0x12) = ratan2(D_801152B0, D_801152B4);
            return 8;
        }
    }
    return 0;
}



extern void func_8014C010(s32 a0, s32 a1);
extern void func_80161D20(int param_1, u32 param_2);
extern void func_801599A4(void *a0);
extern void func_8015BF48(s32 *a0);
extern s32 func_8014A6C4(s32 a0);
extern void func_8015F2F0(s32*);
extern s32 ratan2(s32 x, s32 y);

s32 func_80161774(int param_1, u32 param_2) {

    extern s16 D_801152B0;
    extern s16 D_801152B4;

    if ((param_2 & 1) != 0) {
        func_8014C010(param_1, 1);
        ((void (*)(s32, s32))func_80161D20)(param_1, *(unsigned short *)(param_1 + 0x16e));
        return 1;
    }
    if ((param_2 & 0x4000) != 0) {
        ((void (*)(int))func_801599A4)(param_1);
        ((void (*)(int))func_8015BF48)(param_1);
        func_8014C010(param_1, 1);
        ((void (*)(s32, s32))func_80161D20)(param_1, *(unsigned short *)(param_1 + 0x16e));
        return 2;
    }
    if ((param_2 & 0x2000) != 0) {
        func_8014C010(param_1, 1);
        ((void (*)(s32, s32))func_80161D20)(param_1, *(unsigned short *)(param_1 + 0x16e));
        return 4;
    }
    if ((param_2 & 0x8000) != 0) {
        if (*(unsigned short *)(param_1 + 0x16c) != 0x15) {
            return 0;
        }
        if (func_8014A6C4(param_1) != 0) {
            ((void (*)(int))func_801599A4)(param_1);
            ((void (*)(int))func_8015F2F0)(param_1);
            *(short *)(*(int *)(param_1 + 0x20) + 0x12) = ratan2(D_801152B0, D_801152B4);
            return 8;
        }
    }
    return 0;
}



// @class: schedule
// @stuck: none — MATCH

DEFINE_func_80161888()  /* dedup: shared engine-core @0x80161888 (src/shared) */


DEFINE_func_8016191C()  /* dedup: shared engine-core @0x8016191C (src/shared) */


DEFINE_func_8016197C()  /* dedup: shared engine-core @0x8016197C (src/shared) */

DEFINE_func_801619A4()  /* dedup: shared engine-core @0x801619A4 (src/shared) */

DEFINE_func_801619D0()  /* dedup: shared engine-core @0x801619D0 (src/shared) */

DEFINE_func_80161A00()  /* dedup: shared engine-core @0x80161A00 (src/shared) */

DEFINE_func_80161A30()  /* dedup: shared engine-core @0x80161A30 (src/shared) */

DEFINE_func_80161A60()  /* dedup: shared engine-core @0x80161A60 (src/shared) */


DEFINE_func_80161A90()  /* dedup: shared engine-core @0x80161A90 (src/shared) */


DEFINE_func_80161B18()  /* dedup: shared engine-core @0x80161B18 (src/shared) */

DEFINE_func_80161B84()  /* dedup: shared engine-core @0x80161B84 (src/shared) */

DEFINE_func_80161BE0()  /* dedup: shared engine-core @0x80161BE0 (src/shared) */


extern void func_80147324();

/* RECONCILE (§17a-1/§20): the TU already declares
 *   extern void func_80161C24(s32, s32);   (jr_8015C32C.c:1474 / :1417)
 * so the definition must use (int, int); the unsigned semantics of param_2
 * are restored by a cast at each use (codegen-neutral: sltiu + index math). */
void func_80161C24(int param_1, int param_2)
{

    extern unsigned short D_8018E024[];
    extern unsigned short D_8018E026[];

    if ((unsigned int)param_2 < 8) {
        if (*(u8 *)(param_1 + 0xDA) != 0) {
            func_80147324(D_8018E024[(unsigned int)param_2 * 2]);
            *(u8 *)(param_1 + 0xDA) = 0;
        } else {
            func_80147324(D_8018E026[(unsigned int)param_2 * 2]);
            *(u8 *)(param_1 + 0xDA) = 1;
        }
    }
}



// @class: struct
// @stuck: none — MATCH (indexed-global %lo-fold via extern u16 array, §18)

DEFINE_func_80161C98()  /* dedup: shared engine-core @0x80161C98 (src/shared) */



// @class: plumbing
// @stuck: none — MATCH (20 ins)
// DECAY AXIS: return type. The stored draft declared `s32 func_80161CD0(...)` with no
// return statement. That kept $v0 live-out at the epilogue, so gcc-2.7.2's delayed-branch
// pass refused to speculatively fill the second `beqz $v0` delay slot from the fall-through
// with `sll $v0, $s0, 1` — costing one extra nop (21 vs 20 ins) and shifting both branch
// displacements. Declaring the function `void` makes $v0 dead at the return and the fill
// happens. Same return-type axis as the wave, opposite direction (s32 -> void).
// param_2 must be UNSIGNED: the guard assembles as `sltiu $v0, $s0, 0x8`.
//
// RECONCILE (§37/§124 asm-label alias) — the ONLY change vs the uc2 draft; the body is
// byte-identical and untouched.
//   The real TU src/ov_SC01_077/ov_SC01_077_jr_8015C32C.c already carries the m2c canonical
//   declaration
//       :23   extern s32 func_80161CD0(s32 a0, s32 a1);   /* match-first, arity 2 */
//       :1207 extern s32 func_80161CD0(s32 a0, s32 a1);
//   so a plain `void func_80161CD0(int, unsigned int)` definition dies with
//       conflicting types for `func_80161CD0' / previous declaration ... (rtu_match CC1 FAIL).
//   This is the RETURN axis (s32 vs void) plus the param-2 signedness axis, and BOTH spellings
//   are load-bearing for the 20-instruction codegen — conforming the definition to the
//   declaration (escape #1) would perturb bytes, so it is not available here.
//   The alias fixes it at T0: the C identifier is aF80161CD0 (no declaration to collide with)
//   while the EMITTED SYMBOL is func_80161CD0. In-TU callers keep using the `extern s32`
//   spelling and are byte-unaffected (they discard the return). Zero tracked files touched;
//   no header edit is even possible/needed — grep shows func_80161CD0 has NO declaration in
//   include/ or src/shared/, the conflict is purely TU-local m2c boilerplate.
//   Exactly the pattern already banked at src/ov_SC03_099/ov_SC03_099_jr_8015C32C.c:3503
//   for the sibling func_8016191C.
//
//   NOTE on the third gate diagnostic (`:5223 note: location of previous definition`): that is
//   a RED HERRING, unrelated to this function. It is the pre-existing CPP note paired with
//   `:5533 warning: "SHB" redefined` — the TU defines the SHB scheduling-barrier macro twice
//   (post-splice :5222 with __volatile__, :5533 without). It is a warning, present with or
//   without this draft, and it does not fail cc1.

extern int func_800CF8B4();
extern void func_80147324(int arg0);

void aF80161CD0(int param_1, unsigned int param_2) __asm__("func_80161CD0");

void aF80161CD0(int param_1, unsigned int param_2)
{

    extern unsigned short D_8018E054;
    if (param_2 < 8) {
        if (func_800CF8B4() != 0) {
            func_80147324((&D_8018E054)[param_2]);
        }
    }
}



// @class: struct
// @stuck: none — MATCH (indexed-global %lo-fold via extern u16 array, §18)

DEFINE_func_80161D20()  /* dedup: shared engine-core @0x80161D20 (src/shared) */


DEFINE_func_80161D58()  /* dedup: shared engine-core @0x80161D58 (src/shared) */


// @class: other
// @stuck: none — MATCH (short-circuit && chain; reused 0x80FFFFFF mask const, andi-0xFF on callee ret)

extern s32 D_800AE6B0;
extern s32 D_800AE6A8;
extern s32 func_80029178(s32 arg);
extern void func_80029124(s32, s32);
extern void func_800D1734(void *);
extern s32 D_8018E0A8;

void func_80161D88(void) {
    if ((D_800AE6B0 & 0x80FFFFFF) == 0 && (D_800AE6A8 & 0x80FFFFFF) == 0 &&
        (func_80029178(0x141) & 0xFF) != 0) {
        func_80029124(0x141, 0);
        func_80029124(0x95, 1);
        func_800D1734(&D_8018E0A8);
    }
}


// @class: regalloc-order
// @stuck: none — MATCH (175 ins, relocation-masked). Giant, 3 similar guarded blocks. base=&D_800AF630
//   hoisted to $s2 (referenced only to build the 3 stored pointers base+0x65A8/0x65E0/0x6618 -> $s1);
//   guard reads (D_800B5BD8/C10/C48) + the "=1" + coord stores use direct symbols. Coord idiom:
//   -(s32)(u16)D_800AF7BC/2 + K (negu;srl31;addu;sra1). a2=func_800291DC(8) survives in $s3 for the
//   final (a2&0x7FFF)==(s16)D_80078EB0 test. KEY RESIDUAL (cracked): target computes each pointer into
//   scratch $v0 then `addu $s1,$v0` (dead-intermediate copy) and stores $s1 — natural C ALWAYS coalesces
//   that copy into a direct `addiu $s1,$s2,off` (172 ins, 3 short). Forcing the un-coalesced copy needs
//   an explicit `move` inline-asm (an empty "=r"/"0" re-tie is only a barrier, won't emit the copy).
#include "common.h"







void func_80161E08(s32 param_1) {
    extern void func_80024054(void *a0, void *a1);
    extern void func_8001CE28(void *a0, void *a1);
    extern void func_800242D0(s32 a0, void *a1, s32 a2);
    extern void func_8001CE68(void *a0, void *a1);
    extern int func_801620C4(void);
    extern void func_801622C4(void);
    extern u16 D_800AF7BC;
    extern u16 D_800AF7BE;
    extern s16 D_80078EB0;
    extern u16 D_800B5BD8;
    extern s16 D_800B5C04;
    extern u8 D_800B5BFF;
    extern s16 D_800B5BE0;
    extern s16 D_800B5BE2;
    extern u16 D_800B5C10;
    extern s16 D_800B5C3C;
    extern u8 D_800B5C37;
    extern s16 D_800B5C18;
    extern s16 D_800B5C1A;
    extern u16 D_800B5C48;
    extern s16 D_800B5C74;
    extern s16 D_800B5C50;
    extern s16 D_800B5C52;
    extern u8 * D_801E96F0[];
    extern u8 D_8018E074[];
    extern u8 D_8018E094[];
    extern u8 D_801E96FC[];
    extern u8 D_801E9724[];
    extern u8 D_801E973C[];

    u8 *base = &(*(u8 *)&D_800AF630);
    u8 *p;
    s32 a2;

    if (*((u16 *)param_1) != 0x1A &&
        currentLocationId != 0x3012 &&
        currentLocationId != 0x3054 &&
        currentLocationId != 0x3079 &&
        currentLocationId != 0x3096 &&
        ((a2 = func_800291DC(8)) & 0x8000) != 0) {

        if (D_800B5BD8 == 0) {
            __asm__("move %0,%1" : "=r"(p) : "r"(base + 0x65A8));
            D_801E96F0[0] = p;
            func_80024054(&D_8018E074, &D_801E96FC);
            func_8001CE28(p, &D_801E96FC);
            D_800B5C04 = 1;
            D_800B5BFF = 1;
            D_800B5BE0 = -(s32)(u16)D_800AF7BC / 2 + 0xD0;
            D_800B5BE2 = -(s32)(u16)D_800AF7BE / 2 + 0x28;
        }

        if (D_800B5C10 == 0) {
            __asm__("move %0,%1" : "=r"(p) : "r"(base + 0x65E0));
            D_801E96F0[1] = p;
            func_80024054(&D_8018E094, &D_801E9724);
            func_8001CE28(p, &D_801E9724);
            D_800B5C3C = 1;
            D_800B5C37 = 1;
            D_800B5C18 = -(s32)(u16)D_800AF7BC / 2 + 0xD0;
            D_800B5C1A = -(s32)(u16)D_800AF7BE / 2 + 0x30;
        }

        if (D_800B5C48 == 0) {
            __asm__("move %0,%1" : "=r"(p) : "r"(base + 0x6618));
            D_801E96F0[2] = p;
            func_800242D0((s16)func_801620C4(), &D_801E973C, 0x84);
            func_8001CE68(p, &D_801E973C);
            D_800B5C74 = 1;
            D_800B5C50 = -(s32)(u16)D_800AF7BC / 2 + 0xD0;
            D_800B5C52 = -(s32)(u16)D_800AF7BE / 2 + 0x10;
        }

        func_800242D0((s16)func_801620C4(), &D_801E973C, 0x84);
        if ((a2 & 0x7FFF) == (s32)D_80078EB0) {
            func_801622C4();
        }
    }
}



DEFINE_func_801620C4()  /* dedup: shared engine-core @0x801620C4 (src/shared) */

DEFINE_func_80162120()  /* dedup: shared engine-core @0x80162120 (src/shared) */


// @class: schedule
// @stuck: none — MATCH (do-while scan over 3-entry global; increments placed AFTER the call so p++ schedules between load and jal, i++ into the delay slot)

extern void func_800291C8(s32, s32);
extern void func_80016714(void *a0, s32 a1);

extern int D_801E96F0[];

void func_8016216C(void)
{
    int *p;
    int i;

    func_800291C8(8, 0);
    i = 0;
    p = D_801E96F0;
    do {
        int v = *p;
        ((void (*)(int, int))func_80016714)(v, 0x38);
        p = p + 1;
        i = i + 1;
    } while (i < 3);
}



extern s32 func_800291DC(s32);
extern u8 D_80078E78[];
extern u8 D_80078EB0;
extern u8 D_80078EB1;
extern s32 D_8018E0A8;

s32 func_801621CC(s32 arg0) {
    register s32 s0 __asm__("$16") = arg0;       /* $s0: arg0, crosses the call */
    register u8 *s1 __asm__("$17") = D_80078E78; /* $s1: base, hoisted for the loop */
    register s32 i __asm__("$5");                /* $a1: counter (pin fixes the i/d swap) */
    u32 a2;
    s32 d;                                       /* $a0: natural alloc; load via $v0 temp */
    s32 v, last, hi, lo;
    char pad[8];                                 /* phantom 8B local -> frame 0x28 (vars=8) */

    a2 = func_800291DC(8);
    if ((a2 & 0x8000) == 0) {
        return 0;
    }
    a2 &= 0x7FFF;
    if (((a2 >> 8) == D_80078EB1) && ((a2 & 0xFF) <= (u32)D_80078EB0)) {
        return (s32)&D_8018E0A8;
    }
    d = s1[0x39] - 1;
    i = 0;
    if (s0 <= 0) {
        return 0;
    }
    hi = (a2 >> 8) & 0xFF;
    last = s0 - 1;
    lo = a2 & 0xFF;
    do {
        if ((s8)d < 0) {
            d = 0x17;
        }
        v = (s8)d;
        if (hi == v) {
            if (i != last) {
                return (s32)&D_8018E0A8;
            }
            i++;
            if ((u32)s1[0x38] < (u32)lo) {
                return (s32)&D_8018E0A8;
            }
            goto bot;
        }
        i++;
    bot:
        d--;
    } while (i < s0);
    return 0;
}




// @class: schedule
// @stuck: none — MATCH
extern void func_80029124(s32, s32);
extern void func_800291C8(s32, s32);
extern void func_80016714(void *a0, s32 a1);
extern int D_801E96F0[];

void func_801622C4(void)
{
    int *p;
    int i;

    ((int (*)(int, int))func_80029124)(0x141, 1);
    ((int (*)(int, int))func_800291C8)(8, 0);
    i = 0;
    p = &D_801E96F0;
    do {
        ((int (*)(int, int))func_80016714)(*p, 0x38);
        p = p + 1;
        i = i + 1;
    } while (i < 3);
}



DEFINE_func_80162330()  /* dedup: shared engine-core @0x80162330 (src/shared) */


DEFINE_func_8016236C()  /* dedup: shared engine-core @0x8016236C (src/shared) */

DEFINE_func_801623B8()  /* dedup: shared engine-core @0x801623B8 (src/shared) */

DEFINE_func_80162414()  /* dedup: shared engine-core @0x80162414 (src/shared) */

// @class: regalloc-order
// @stuck: none — MATCH (160 ins, relocation-masked). Keys: (1) base=&D_800AF630 hoisted, pinned $s2;
//   uVar2 UNPINNED (a $s3 pin forced the final `uVar2 & 0x7FFF` in-place+early, breaking the lh delay
//   slot). (2) item pinned $s1, dest INLINED (D_801D96Dx in both call args) so it lands $s0 AFTER a0.
//   (3) base assigned BEFORE the func_800291DC call so the return-copy `addu $s3,$v0` schedules after
//   the base lui/addiu. (4) THE MOVE: each block's `addu $s1,$v0,$zero` = compute `base+off` into a
//   $v0-PINNED temp `t`, then `item = t`. Two distinct hard regs ($v0 vs $s1) can't coalesce, forcing
//   the exact `addiu $v0,$s2,off ; addu $s1,$v0` pair the target emits (plain `item=base+off` coalesces
//   into one `addiu $s1` — 3 ins short). (5) store D_801E9748[i] via `extern int D_801E9748[]` (folds
//   %lo, consistent with func_80162760). Coord = (s16)(-D_800AF7Bx / 2 + K) (negu; srl 31; addu; sra 1).

#include "common.h"








s32 func_80162438(s32 _unused0) {
    extern void func_80024054(void *, void *);
    extern void func_8001CE28(void *, void *);
    extern void func_8001CE68(void *, void *);
    extern void func_800242D0(s32, void *, s32);
    extern s32 func_801626B8(void);
    extern void func_80162760(void);
    extern u8 D_8018E0D8[];
    extern s32 D_8018E0F0;
    extern u8 D_801E9754[];
    extern u8 D_801E977C[];
    extern u8 D_801E9798[];
    extern int D_801E9748[];
    extern u16 D_800B5BD8;
    extern u16 D_800B5C10;
    extern u16 D_800B5C48;
    extern u16 D_800AF7BC;
    extern u16 D_800AF7BE;
    extern s16 D_800B5BE0;
    extern s16 D_800B5BE2;
    extern s16 D_800B5C04;
    extern u8 D_800B5BFF;
    extern s16 D_800B5C18;
    extern s16 D_800B5C1A;
    extern s16 D_800B5C3C;
    extern u8 D_800B5C37;
    extern s16 D_800B5C50;
    extern s16 D_800B5C52;
    extern s16 D_800B5C74;

    u32 uVar2;
    register u8 *base __asm__("$18");
    register u8 *item __asm__("$17");

    base = &(*(u8 *)&D_800AF630);
    uVar2 = func_800291DC(0x12);
    if ((uVar2 & 0x8000) != 0) {
        if (D_800B5BD8 == 0) {
            register u8 *t __asm__("$2") = base + 0x65A8;
            item = t;
            D_801E9748[0] = (s32)item;
            func_80024054(D_8018E0D8, D_801E9754);
            func_8001CE28(item, D_801E9754);
            D_800B5C04 = 1;
            D_800B5BFF = 1;
            D_800B5BE0 = -D_800AF7BC / 2 + 0xD0;
            D_800B5BE2 = -D_800AF7BE / 2 + 0x28;
        }
        if (D_800B5C10 == 0) {
            register u8 *t __asm__("$2") = base + 0x65E0;
            item = t;
            D_801E9748[1] = (s32)item;
            func_80024054(((u8 *)&D_8018E0F0), D_801E977C);
            func_8001CE28(item, D_801E977C);
            D_800B5C3C = 1;
            D_800B5C37 = 1;
            D_800B5C18 = -D_800AF7BC / 2 + 0xD0;
            D_800B5C1A = -D_800AF7BE / 2 + 0x30;
        }
        if (D_800B5C48 == 0) {
            register u8 *t __asm__("$2") = base + 0x6618;
            item = t;
            D_801E9748[2] = (s32)item;
            func_800242D0((s16)func_801626B8(), D_801E9798, 0x84);
            func_8001CE68(item, D_801E9798);
            D_800B5C74 = 1;
            D_800B5C50 = -D_800AF7BC / 2 + 0xD0;
            D_800B5C52 = -D_800AF7BE / 2 + 0x10;
        }
        func_800242D0((s16)func_801626B8(), D_801E9798, 0x84);
        if ((uVar2 & 0x7FFF) == (s32)(*(s16 *)&D_80078EB0)) {
            func_80162760();
        }
    }
}



DEFINE_func_801626B8()  /* dedup: shared engine-core @0x801626B8 (src/shared) */

DEFINE_func_80162714()  /* dedup: shared engine-core @0x80162714 (src/shared) */


// @class: schedule
// @stuck: none — MATCH (24 ins). do-while; load+call first, then p++ and i++ AFTER the call so gcc schedules p++/arg ahead of jal and i++ into the delay slot.

extern void func_800291C8(s32, s32);
extern void func_80016714(void *a0, s32 a1);

extern int D_801E9748[];

void func_80162760(void)
{
    int *p;
    int i;

    func_800291C8(0x12, 0);
    i = 0;
    p = D_801E9748;
    do {
        int v = *p;
        ((void (*)(int, int))func_80016714)(v, 0x38);
        p = p + 1;
        i = i + 1;
    } while (i < 3);
}


DEFINE_func_801627C0()  /* dedup: shared engine-core @0x801627C0 (src/shared) */


// @class: struct
// @stuck: none — MATCH (19 ins, relocation-masked)
//
// Tiny dispatcher: byte count at D_8011F750 (offset 0 of a 0x58-byte ctl struct;
// cf. func_801627C0 which calls func_80016714(&D_8011F750, 0x58)). If nonzero,
// call D_8018E110[count - 1]() through a word-stride fn-pointer table.
//
// Two idioms combined to match gcc-2.7.2 -O2:
//  1. The target MATERIALIZES &D_8011F750 (lui;addiu %lo) into $a0 before the lbu
//     instead of folding %lo into the load. A direct global byte read always
//     %lo-folds (lui;lbu %lo), so force the full-address materialization with the
//     §21 re-tie barrier __asm__ __volatile__("":"=r"(p):"0"(p)) and pin the
//     pointer to $a0 with register __asm__("$4") to get the exact register.
//  2. Writing `idx = idx - 1;` as its OWN statement (not inline D_8018E110[count-1])
//     keeps the array index/decrement separate so %lo(D_8018E110) folds into the
//     dispatch load (lw %lo(...)($at)) — the inline form instead constant-folds the
//     -1*4 into a -4 load offset and drops the %lo fold (1 ins short, schedule off).


void func_801627E8(void)
{

    extern s32 D_8011F750;               /* canonical: engine_core.h `extern s32 D_8011F750;` (read here as a byte) */
    extern void (*D_8018E110[])(void);   /* word-stride table of dispatch fn pointers */
    register u8 *p __asm__("$4") = (u8 *)&D_8011F750;
    s32 idx;

    __asm__ __volatile__("" : "=r"(p) : "0"(p));   /* materialize &D_8011F750 into $a0 (defeat %lo-fold of the lbu) */
    idx = *p;
    if (idx != 0) {
        idx = idx - 1;
        D_8018E110[idx]();
    }
}



DEFINE_func_80162834()  /* dedup: shared engine-core @0x80162834 (src/shared) */



// @class: plumbing
// @stuck: none — MATCH (stub: alloc + global init + two calls; $s0 holds param_1 across calls)

extern void func_8001CB6C(u8 *a0, s32 a1, s32 a2, s32 a3);
extern void func_80162968(s32 a0);
extern s32 func_80162ACC(u8 *a0);

extern u8 D_800B5CB8;
extern s32 D_8018E104;
extern s32 D_800B5CBC;
extern u8 D_800B5CDF;
extern s32 D_800B5CEC;

void func_80162870(s32 param_1) {
    *(s32 *)(param_1 + 8) = (s32)&D_800B5CB8;
    func_8001CB6C(&D_800B5CB8, (s32)&D_8018E104, 0x250, 0x1A0);
    D_800B5CEC = param_1 + 0xC;
    D_800B5CDF = 0x14;
    D_800B5CBC |= 0x60000000;
    func_80162968(param_1);
    func_80162ACC((u8 *)param_1);
}


DEFINE_func_801628F4()  /* dedup: shared engine-core @0x801628F4 (src/shared) */

DEFINE_func_80162968()  /* dedup: shared engine-core @0x80162968 (src/shared) */

DEFINE_func_80162AC0()  /* dedup: shared engine-core @0x80162AC0 (src/shared) */

DEFINE_func_80162ACC()  /* dedup: shared engine-core @0x80162ACC (src/shared) */

DEFINE_func_80162AE0()  /* dedup: shared engine-core @0x80162AE0 (src/shared) */

DEFINE_func_80162AF4()  /* dedup: shared engine-core @0x80162AF4 (src/shared) */

DEFINE_func_80162B1C()  /* dedup: shared engine-core @0x80162B1C (src/shared) */

DEFINE_func_80162CC4()  /* dedup: shared engine-core @0x80162CC4 (src/shared) */

extern void func_80016714(void *a0, s32 a1);
void aF80162CCC(u8 *a0) __asm__("func_80162CCC");
DEFINE_func_80162CCC()  /* dedup: shared engine-core @0x80162CCC (src/shared) */


DEFINE_func_80162D28()  /* dedup: shared engine-core @0x80162D28 (src/shared) */

DEFINE_func_80162D88()  /* dedup: shared engine-core @0x80162D88 (src/shared) */

DEFINE_func_80162DE8()  /* dedup: shared engine-core @0x80162DE8 (src/shared) */

DEFINE_func_80162E48()  /* dedup: shared engine-core @0x80162E48 (src/shared) */

DEFINE_func_80162EA8()  /* dedup: shared engine-core @0x80162EA8 (src/shared) */

DEFINE_func_80162F08()  /* dedup: shared engine-core @0x80162F08 (src/shared) */

DEFINE_func_80162F60()  /* dedup: shared engine-core @0x80162F60 (src/shared) */

DEFINE_func_80162F80()  /* dedup: shared engine-core @0x80162F80 (src/shared) */

DEFINE_func_80162FA0()  /* dedup: shared engine-core @0x80162FA0 (src/shared) */

DEFINE_func_80162FC0()  /* dedup: shared engine-core @0x80162FC0 (src/shared) */

DEFINE_func_80162FF4()  /* dedup: shared engine-core @0x80162FF4 (src/shared) */

DEFINE_func_801630C4()  /* dedup: shared engine-core @0x801630C4 (src/shared) */

DEFINE_func_80163194()  /* dedup: shared engine-core @0x80163194 (src/shared) */

DEFINE_func_80163234()  /* dedup: shared engine-core @0x80163234 (src/shared) */

DEFINE_func_8016325C()  /* dedup: shared engine-core @0x8016325C (src/shared) */

DEFINE_func_801632E0()  /* dedup: shared engine-core @0x801632E0 (src/shared) */

DEFINE_func_801632F0()  /* dedup: shared engine-core @0x801632F0 (src/shared) */

DEFINE_func_80163328()  /* dedup: shared engine-core @0x80163328 (src/shared) */

DEFINE_func_801633A8()  /* dedup: shared engine-core @0x801633A8 (src/shared) */

// @class: struct
// @stuck: none — MATCH (21 ins, relocation-masked)


s32 func_80163408(s32 param_1, s32 param_2, s32 param_3, s32 param_4) {
    extern int func_8016345C(int, unsigned short, int, unsigned short, void *);
    extern unsigned char D_801E8DBC[8];

    unsigned char sp18[8];
    memcpy(sp18, D_801E8DBC, 8);
    return func_8016345C(((int)param_1), ((int)param_2), ((int)param_3), ((int)param_4), sp18);
}



DEFINE_func_8016345C()  /* dedup: shared engine-core @0x8016345C (src/shared) */


// @class: struct
// @stuck: none — MATCH (unaligned 8-byte memcpy from global into stack buffer, then forward to callee)

extern char D_801E8DBC[8];

extern void *memcpy(void *dst, const void *src, unsigned int n);
extern void func_80163534(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, u16 * a5);

void func_801634D8(s32 param_1, u16 param_2, u16 param_3, s32 param_4, u16 param_5)
{
    char buf[8];

    memcpy(buf, D_801E8DBC, 8);
    ((void (*)(s32, u16, u16, s32, u16, s32))func_80163534)(param_1, param_2, param_3, param_4, param_5, (s32)buf);
}


DEFINE_func_80163534()  /* dedup: shared engine-core @0x80163534 (src/shared) */


DEFINE_func_80163664()  /* dedup: shared engine-core @0x80163664 (src/shared) */

DEFINE_func_801636D0()  /* dedup: shared engine-core @0x801636D0 (src/shared) */


DEFINE_func_80163764()  /* dedup: shared engine-core @0x80163764 (src/shared) */


DEFINE_func_8016380C()  /* dedup: shared engine-core @0x8016380C (src/shared) */

DEFINE_func_801638A0()  /* dedup: shared engine-core @0x801638A0 (src/shared) */

DEFINE_func_80163950()  /* dedup: shared engine-core @0x80163950 (src/shared) */


DEFINE_func_80163A58()  /* dedup: shared engine-core @0x80163A58 (src/shared) */


DEFINE_func_80163A94()  /* dedup: shared engine-core @0x80163A94 (src/shared) */

DEFINE_func_80163C2C()  /* dedup: shared engine-core @0x80163C2C (src/shared) */


void func_80163EC8(s32 param_1) {
    extern Blk8 D_801E8DC4;
    extern u16 D_800B99DA;
    extern u8 func_801656D0(s32 a0, s32 a1);
    extern s32 func_80012F74(s32 a0, s32 a1, s32 a2, s32 a3);
    extern void func_80015978(s32 a0, s32 *a1);
    extern void func_8014C4AC(s32 a0, s32 a1, s32 a2, s16 *a3, s32 a4);

    Blk8 in;
    u16 out[4];
    s16 buf[4];
    s32 psVar6;
    s32 iVar8;
    s32 iVar7;
    register s32 uVar5 __asm__("$2");   /* PIN (flagged): uVar5 -> $v0 */
    u16 uVar4;
    u8 uVar3;

    in = D_801E8DC4;
    psVar6 = *(s32 *)(param_1 + 0x4c);
    iVar8 = *(s32 *)(param_1 + 0x20);
    func_80162D88((s32 *)param_1);

    if (*(s32 *)(psVar6 + 0x184) == 0) {
        uVar5 = *(s32 *)(psVar6 + 0x44);
        *(s16 *)(psVar6 + 0x18a) = 0;
        *(s16 *)(psVar6 + 0x188) = 0;
        *(s32 *)(psVar6 + 0x44) = uVar5 & ~0x20;
        func_80146CA0((void *)param_1);
        func_80146CA0((void *)param_1);
        return;
    }
    if (*(s16 *)(*(s32 *)(psVar6 + 0x184) + 0x36) == *(u16 *)(psVar6 + 0x194)) {
        goto LAB_matched;
    }
    *(s32 *)(psVar6 + 0x184) = 0;
    uVar5 = *(s32 *)(psVar6 + 0x44);
    *(s16 *)(psVar6 + 0x18a) = 0;
    *(s16 *)(psVar6 + 0x188) = 0;
    *(s32 *)(psVar6 + 0x44) = uVar5 & ~0x20;
    func_80146CA0((void *)param_1);
    func_80146CA0((void *)param_1);
    return;

LAB_matched:
    *(s16 *)(psVar6 + 0x18a) = *(u16 *)(psVar6 + 0x18a) + 1;
    if ((D_800B99DA & 3) == 0) {
        if (*(s16 *)(psVar6 + 0x188) >= *(u8 *)(param_1 + 0x67)) {
            *(s16 *)(psVar6 + 0x188) = *(s16 *)(psVar6 + 0x188) - *(u8 *)(param_1 + 0x67);
        } else {
            *(s16 *)(psVar6 + 0x188) = 0;
        }
        if (*(s16 *)(psVar6 + 0x188) < 0) {
            *(s16 *)(psVar6 + 0x188) = 0;
        }
    }

    *(s16 *)(param_1 + 0x66) = *(u16 *)(param_1 + 0x66) + 0x40;
    uVar5 = func_80148800((s32 *)psVar6);
    if ((uVar5 & 0x80) != 0) {
        *(s16 *)(param_1 + 0x66) = 0;
        uVar3 = func_801656D0(psVar6, func_8014CA00(*(s32 *)(psVar6 + 0x184)) & 0xff);
        *(s16 *)(psVar6 + 0x188) = *(u16 *)(psVar6 + 0x188) + uVar3;
        *(s16 *)(iVar8 + 0x1a) = 0x4000;
        *(s16 *)(iVar8 + 0x18) = 0x4000;
        *(s32 *)(iVar8 + 0x48) = *(s16 *)(param_1 + 0x58);
        *(s32 *)(iVar8 + 0x4c) = *(s16 *)(param_1 + 0x5a);
        *(s32 *)(iVar8 + 0x50) = *(s16 *)(param_1 + 0x5c);
        ((void (*)(s32, s32, s32))func_80149350)(param_1, (s32)&in, (s32)out);
        *(s16 *)(param_1 + 0x6) = out[0];
        *(s16 *)(param_1 + 0xa) = out[1];
        *(s16 *)(param_1 + 0xe) = out[2];
    }

    if (0x80 < *(s16 *)(psVar6 + 0x188)) {
        *(s16 *)(psVar6 + 0x188) = 0x80;
    }
    if (*(s16 *)(psVar6 + 0x188) >= 0x80) {
        iVar7 = *(s32 *)(psVar6 + 0x184);
        if (iVar7 != 0) {
            func_80015978(iVar7 + 4, (s32 *)buf);
            buf[3] = 0;
            uVar4 = func_80156370(0xe);
            func_8014C4AC(iVar7, 0xe, uVar4, buf, *(s16 *)(iVar8 + 0x12));
            func_80146994(0x33, param_1, 0, iVar7);
        }
    } else {
        if (*(s16 *)(psVar6 + 0x18a) < 0x80 && *(u16 *)psVar6 != 0x19) {
            goto LAB_end;
        }
        iVar7 = *(s32 *)(psVar6 + 0x184);
        if (iVar7 != 0) {
            func_80015978(iVar7 + 4, (s32 *)buf);
            buf[3] = 0;
            uVar4 = func_80156370(0x21);
            func_8014C4AC(iVar7, 0x21, uVar4, buf, *(s16 *)(iVar8 + 0x12));
            if ((*(s32 *)(iVar7 + 0xb4) & 0x40000) != 0) {
                func_8014AD30(param_1, (u16 *)buf, 0, *(s16 *)(iVar7 + 0x60));
            }
        }
    }

    uVar5 = func_8014CA00(iVar7);
    *(s32 *)(psVar6 + 0x184) = uVar5;
    if (0x1e < (u32)uVar5) {
        *(s32 *)(psVar6 + 0x184) = 0;
    }
    func_80146E90((s32 *)param_1, 0x20);
    *(s32 *)(psVar6 + 0x44) = *(s32 *)(psVar6 + 0x44) & ~0x20;
    func_80147324(0x449);
    func_80146CA0((void *)param_1);
    func_80146CA0((void *)param_1);

LAB_end:
    uVar4 = func_80012F74(*(s16 *)(iVar8 + 0x1a), 0x1800, 3, 1);
    *(s16 *)(iVar8 + 0x1a) = uVar4;
    *(s16 *)(iVar8 + 0x18) = uVar4;
    uVar4 = func_80012F74(*(s16 *)(param_1 + 0x6), *(s16 *)(param_1 + 0x58), 8, 1);
    *(s16 *)(param_1 + 0x6) = uVar4;
    uVar4 = func_80012F74(*(s16 *)(param_1 + 0xa), *(s16 *)(param_1 + 0x5a), 8, 1);
    *(s16 *)(param_1 + 0xa) = uVar4;
    uVar4 = func_80012F74(*(s16 *)(param_1 + 0xe), *(s16 *)(param_1 + 0x5c), 8, 1);
    *(s16 *)(param_1 + 0xe) = uVar4;
}


DEFINE_func_80164270()  /* dedup: shared engine-core @0x80164270 (src/shared) */

DEFINE_func_801642AC()  /* dedup: shared engine-core @0x801642AC (src/shared) */

DEFINE_func_8016432C()  /* dedup: shared engine-core @0x8016432C (src/shared) */

DEFINE_func_80164410()  /* dedup: shared engine-core @0x80164410 (src/shared) */

DEFINE_func_80164418()  /* dedup: shared engine-core @0x80164418 (src/shared) */

DEFINE_func_80164530()  /* dedup: shared engine-core @0x80164530 (src/shared) */


// @class: struct
// @stuck: none — MATCH expected (fn-ptr table dispatch via u16 idx, $s0 holds *(s32*)(p+0x20) across the call)

extern void (*D_8018E170[])(void);
extern void func_80162D28(s32 *a0);

void func_80164744(s32 param_1)
{
    s32 iVar1;

    iVar1 = *(s32 *)(param_1 + 0x20);
    D_8018E170[*(u16 *)(param_1 + 2)]();
    if (iVar1 != 0) {
        ((void (*)(s32))func_80162D28)(param_1);
    }
}




// @class: other
// @stuck: none — MATCH (relocation-masked); key was `if (iVar1 != 0) { big } else { func_80164930 }` (non-zero case first → beqz, not bnez)


extern void func_8014659C(void);
extern void func_8001C810(s32 a0, s32 a1);
extern void func_80164A74(s32 *a0);
extern void func_80146CA0(void *a0);
extern void func_80164930(s32 a);

extern u16 D_800DF2E0;
extern s32 D_8018E138;
extern s16 D_8018E16C;
extern s16 D_8018E16A;
extern s16 D_8018E168;

void func_801647A4(int param_1) {
    s32 iVar1;

    iVar1 = ((s32 (*)(void))func_8014659C)();
    *(s32 *)(param_1 + 0x20) = iVar1;
    if (iVar1 != 0) {
        ((void (*)(s32, void *))func_8001C810)(iVar1, &D_800DF2E0);
        *(s32 **)(iVar1 + 0x80) = &D_8018E138;
        *(u32 *)(iVar1 + 4) = *(u32 *)(iVar1 + 4) | 0x50000000;
        *(u16 *)(iVar1 + 0x2c) = *(u16 *)(iVar1 + 0x2c) | 0xb0;
        D_8018E16C = 0x80;
        D_8018E16A = 0x80;
        D_8018E168 = 0x80;
        *(u16 *)(iVar1 + 0x1a) = 0;
        *(u16 *)(param_1 + 0x60) = 0;
        *(u16 *)(param_1 + 0x62) = 0x200;
        ((s32 (*)(s32))func_80164A74)(param_1);
        ((void (*)(s32))func_80146CA0)(param_1);
    } else {
        func_80164930(param_1);
    }
}


DEFINE_func_80164864()  /* dedup: shared engine-core @0x80164864 (src/shared) */

// @class: regalloc-order — wave-3 real-TU crack (§42a); cracked at Max.
// Fix: D_8018E16C read needs direct-addressed `lhu` (u16). Cannot use `*(u16*)&D_8018E16C`
// (forces &sym into a held reg -> drift) NOR a block-scoped `extern u16` (conflicting-types
// ERROR vs the ambient s16, cc1 exit 33). Solution: flip the file-scope decl (5802) to u16 —
// byte-neutral to the only other user (func_801647A4 store-only) — and reference directly.


void func_80164930(s32 param_1) {
    int iVar3 = *(int *)(((int)param_1) + 0x20);
    if (*(int *)(((int)param_1) + 0x50) == 0) {
        short sVar1 = *(u16 *)(iVar3 + 0x1c) + 0x100;
        short nv;
        *(short *)(iVar3 + 0x1c) = sVar1;
        *(short *)(iVar3 + 0x18) = sVar1;
        *(short *)(iVar3 + 0x12) = *(u16 *)(iVar3 + 0x12) + 0x71;
        nv = D_8018E16C - 8;
        D_8018E16C = nv;
        D_8018E16A = nv;
        D_8018E168 = nv;
        if (nv < -0x80) {
            int i, lim;
            Ent_80164930_80164930 *p;
            for (i = 0, lim = 0x19, p = ((Ent_80164930_80164930 *)&D_8011F9D0); i < 0x14; i++) {
                if (p->f0 == lim && p->f50 != 0) {
                    ((void(*)(Ent_80164930_80164930 *))func_80162CCC)(p);
                }
                p++;
            }
            ((void(*)(Ent_80164930_80164930 *))func_80162CCC)((Ent_80164930_80164930 *)((int)param_1));
        } else {
            ((void(*)(int))func_80164ACC)(((int)param_1));
        }
    } else {
        short sVar1 = *(u16 *)(iVar3 + 0x1c) + 0x40;
        u16 uVar2;
        *(short *)(iVar3 + 0x1c) = sVar1;
        *(short *)(iVar3 + 0x18) = sVar1;
        uVar2 = *(u16 *)(iVar3 + 0x1a) - 0x200;
        *(u16 *)(iVar3 + 0x1a) = uVar2;
        if ((int)((unsigned)uVar2 << 0x10) < 0) {
            *(short *)(iVar3 + 0x1a) = 0;
        }
        *(short *)(iVar3 + 0x12) = *(u16 *)(iVar3 + 0x12) - 0x71;
    }
}



DEFINE_func_80164A74()  /* dedup: shared engine-core @0x80164A74 (src/shared) */

DEFINE_func_80164ACC()  /* dedup: shared engine-core @0x80164ACC (src/shared) */


DEFINE_func_80164BA0()  /* dedup: shared engine-core @0x80164BA0 (src/shared) */



extern void func_80146578(void);
extern void func_8001CD50(s32 a0, s32 a1);
extern void func_800233CC(void *, unsigned short);
extern void func_80164DD0(s32 a0);
extern void func_80146CA0(void *a0);
extern void func_80164DB0(void);

extern u8 D_801E97A8;
extern u8 D_801E97A9;
extern u8 D_801E97AA;
extern u8 D_801E97AB;
extern u8 D_801E97AC;
extern u8 D_801E97AD;
extern u8 D_801E97AE;
extern u8 D_801E97AF;

void func_80164BDC(s32 param_1)
{
    register s32 p1   __asm__("$17");  /* $s1 */
    register s32 iVar1 __asm__("$16");  /* $s0 */
    register s32 base __asm__("$18");  /* $s2 */

    p1 = param_1;
    iVar1 = ((s32 (*)(void))func_80146578)();
    base = (s32)&D_801E97A8;
    *(s32 *)(p1 + 0x20) = iVar1;
    if (iVar1 != 0) {
        func_8001CD50(iVar1, base);
        ((void (*)(s32, s32))func_800233CC)(base, 0x60);
        *(u32 *)(iVar1 + 4) = *(u32 *)(iVar1 + 4) | 0x50000000;
        D_801E97A9 = 0xf0;
        *(u8 *)base = 0xf0;
        D_801E97AA = 0xc0;
        D_801E97AE = 0;
        D_801E97AD = 0;
        D_801E97AC = 0;
        D_801E97AF = 0;
        D_801E97AB = 0;
        *(s16 *)(iVar1 + 0x1e) = 0xccc;
        *(s16 *)(iVar1 + 0x10) = 0x400;
        *(s16 *)(p1 + 0x60) = 0x700;
        *(s16 *)(p1 + 0x62) = -0x60;
        func_80164DD0(p1);
        ((void (*)(s32))func_80146CA0)(p1);
    } else {
        ((void (*)(s32))func_80164DB0)(p1);
    }
}


DEFINE_func_80164CD4()  /* dedup: shared engine-core @0x80164CD4 (src/shared) */

DEFINE_func_80164D4C()  /* dedup: shared engine-core @0x80164D4C (src/shared) */

DEFINE_func_80164DB0()  /* dedup: shared engine-core @0x80164DB0 (src/shared) */

DEFINE_func_80164DD0()  /* dedup: shared engine-core @0x80164DD0 (src/shared) */





extern u8 D_801E97A8;
extern u8 D_801E97A9;
extern u8 D_801E97AA;

s32 func_80164E40(void) {
    u8 *p = &D_801E97A8;
    if (*p != 0) {
        *p -= 0x10;
    }
    if (D_801E97A9 != 0) {
        D_801E97A9 -= 0x10;
    }
    if (D_801E97AA != 0) {
        D_801E97AA -= 0x10;
    }
    return *(s32 *)p == 0;
}



DEFINE_func_80164EA4()  /* dedup: shared engine-core @0x80164EA4 (src/shared) */



// @class: struct
// @stuck: none — MATCH

  /* stride 0x10 */
extern DStruct D_801E97F4[];

extern void func_80165124(void *a0);
extern void func_80146CA0(void *a0);

void func_80164EE0(int param_1)
{
    int i;

    for (i = 7; i >= 0; i--) {
        D_801E97F4[i].f0 = 0;
    }
    *(short *)(param_1 + 0x2e) = 0x4000;
    *(short *)(param_1 + 0x2c) = 0x4000;
    *(short *)(param_1 + 0x60) = 0;
    *(short *)(param_1 + 0x62) = 0;
    ((void (*)(int))func_80165124)(param_1);
    *(short *)(param_1 + 0x66) = 0;
    ((void (*)(int))func_80146CA0)(param_1);
}


DEFINE_func_80164F44()  /* dedup: shared engine-core @0x80164F44 (src/shared) */

DEFINE_func_80165024()  /* dedup: shared engine-core @0x80165024 (src/shared) */

DEFINE_func_80165064()  /* dedup: shared engine-core @0x80165064 (src/shared) */

DEFINE_func_801650C4()  /* dedup: shared engine-core @0x801650C4 (src/shared) */

DEFINE_func_80165124()  /* dedup: shared engine-core @0x80165124 (src/shared) */

// @class: struct
// @stuck: none — MATCH (30 ins)
//
// Unaligned slot-fill: loop over 8 slots (0x10 stride) of a global table,
// fill the first free one (field @0xC == 0). Two unaligned block copies from
// param_1 (packed struct assigns -> lwl/lwr/swl/swr). Key: recompute
// p = &D_801E97E8[i] each iteration (NOT p++) so gcc reduces base+i*0x10 into
// a SINGLE pointer IV with immediate offsets 0/8/0xC. Hand-incrementing p makes
// combine_givs split the field offsets into a second pointer IV (+2 ins).




s32 func_80165140(s32 param_1) {
    extern Slot_80165140 D_801E97E8[8];

    int i;
    Slot_80165140 *p;
    for (i = 0; i < 8; i++) {
        p = &D_801E97E8[i];
        if (p->used == 0) {
            p->used = 8;
            p->a = *(B8_80165140 *)(((u8 *)param_1) + 0x2c);
            p->b = *(B4_80165140 *)(((u8 *)param_1) + 0x50);
            return;
        }
    }
}




// @class: schedule
// @stuck: none — MATCH (pins $s2/$s1/$s0 + zero-code barrier hoists $a0 copy into beqz delay slot)

extern void func_80165240(void *param_1, void *param_2, void *param_3);
extern s32 D_801E97E8;

void func_801651B8(void * param_1)
{
    register s32 *puVar1 __asm__("$16"); /* $s0 */
    register s32 iVar2 __asm__("$17");   /* $s1 */
    register s32 p __asm__("$18");        /* $s2 */

    p = param_1;
    ((s32 (*)(s32, s32, s32))func_80165240)(p, p + 0x2c, p + 0x50);
    iVar2 = 0;
    puVar1 = &D_801E97E8;
    do {
        if (puVar1[3] != 0) {
            s32 a0v = p;
            __asm__ __volatile__("" : "=r"(a0v) : "0"(a0v));
            ((s32 (*)(s32, s32, s32))func_80165240)(a0v, (s32)puVar1, (s32)(puVar1 + 2));
            puVar1[3] = puVar1[3] + -1;
        }
        iVar2 = iVar2 + 1;
        puVar1 = puVar1 + 4;
    } while (iVar2 < 8);
}


extern void func_80016ED4(void *a0);
extern s32 func_80017DC4(void *a0, void *a1);

void func_80165240(void *param_1, void *param_2, void *param_3)
{

    extern u8 D_8018E1A0[];
    extern u32 D_8018E1C0, D_8018E1C4, D_8018E1C8, D_8018E1CC;
    extern u32 D_8018E1C0, D_8018E1C4, D_8018E1C8, D_8018E1CC;
    extern u32 D_8018E1C0, D_8018E1C4, D_8018E1C8, D_8018E1CC;
    extern u32 D_8018E1C0, D_8018E1C4, D_8018E1C8, D_8018E1CC;
    u8 prim[0x40];   /* $sp+0x10 .. 0x50 */
    u8 mat[0x20];    /* $sp+0x50 .. 0x70 */
    u8 *p = prim;

    func_80017DC4(param_2, mat);
    ApplyMatrixSV(mat, &D_8018E1A0[0x00], p);
    ApplyMatrixSV(mat, &D_8018E1A0[0x08], prim + 0x08);
    ApplyMatrixSV(mat, &D_8018E1A0[0x10], prim + 0x10);
    ApplyMatrixSV(mat, &D_8018E1A0[0x18], prim + 0x18);

    *(s16 *)(prim + 0x04) = 3;
    prim[0x38] = 0x2c;
    *(u32 *)(prim + 0x20) = D_8018E1C8;
    *(u32 *)(prim + 0x24) = D_8018E1C0;
    *(u32 *)(prim + 0x28) = D_8018E1CC;
    *(u32 *)(prim + 0x2c) = D_8018E1C4;
    *(struct W4 *)(prim + 0x30) = *(struct W4 *)param_3;
    *(u32 *)(prim + 0x34) = 0x50000000;

    func_80016ED4(p);
}


DEFINE_func_8016533C()  /* dedup: shared engine-core @0x8016533C (src/shared) */

DEFINE_func_80165374()  /* dedup: shared engine-core @0x80165374 (src/shared) */

DEFINE_func_801653B8()  /* dedup: shared engine-core @0x801653B8 (src/shared) */

DEFINE_func_801653F4()  /* dedup: shared engine-core @0x801653F4 (src/shared) */


// @class: struct
// @stuck: none — MATCH (54 ins)

extern u8 D_80078E78[];
extern u8 D_80078EC1;
extern void (*D_8018E1D0[])(void);
extern u8 func_80165658(s32 a0, s32 a1);
extern void func_800CAE0C(s32 a0);

void func_801654A8(s32 arg0)
{
    u8 *s1 = D_80078E78;

    if (*(u16 *)arg0 == 0x16) {
        return;
    }
    if (*(u16 *)arg0 != 0x1A) {
        if ((*(s32 *)(arg0 + 0x1F8) & 0x80FFFFFF) == 0) {
            if (func_80165658(arg0, D_80078EC1) & 0x80) {
                ((void (*)(s32))D_8018E1D0[D_80078EC1 & 0x7F])(arg0);
            }
        }
    }
    if (*(u16 *)arg0 == 0x16) {
        return;
    }
    if (*(u16 *)arg0 == 0x1A) {
        return;
    }
    if (s1[0x49] == 0x19) {
        func_800CAE0C(arg0);
    }
}



// @class: struct
// @stuck: none — MATCH (function-pointer-array dispatch; & 0x80 branch + & 0x7f index fold)

extern u8 D_80078EC5;
extern u8 D_80078EC1;
extern void (*D_8018E1D0[])(void);
extern void func_80165B28(void *a0);

void func_80165580(s32 _arg0)
{
    if (D_80078EC5 & 0x80) {
        ((void (*)(void))func_80165B28)();
    } else {
        D_8018E1D0[D_80078EC1 & 0x7F]();
    }
}


DEFINE_func_801655E4()  /* dedup: shared engine-core @0x801655E4 (src/shared) */

DEFINE_func_80165624()  /* dedup: shared engine-core @0x80165624 (src/shared) */


DEFINE_func_80165658()  /* dedup: shared engine-core @0x80165658 (src/shared) */



DEFINE_func_80165670()  /* dedup: shared engine-core @0x80165670 (src/shared) */


DEFINE_func_80165694()  /* dedup: shared engine-core @0x80165694 (src/shared) */


DEFINE_func_801656D0()  /* dedup: shared engine-core @0x801656D0 (src/shared) */



DEFINE_func_801656E8()  /* dedup: shared engine-core @0x801656E8 (src/shared) */



DEFINE_func_80165700()  /* dedup: shared engine-core @0x80165700 (src/shared) */


DEFINE_func_80165718()  /* dedup: shared engine-core @0x80165718 (src/shared) */

DEFINE_func_80165770()  /* dedup: shared engine-core @0x80165770 (src/shared) */

DEFINE_func_801657A0()  /* dedup: shared engine-core @0x801657A0 (src/shared) */

DEFINE_func_801657D8()  /* dedup: shared engine-core @0x801657D8 (src/shared) */

DEFINE_func_80165840()  /* dedup: shared engine-core @0x80165840 (src/shared) */

DEFINE_func_80165874()  /* dedup: shared engine-core @0x80165874 (src/shared) */

DEFINE_func_801658DC()  /* dedup: shared engine-core @0x801658DC (src/shared) */

DEFINE_func_801658EC()  /* dedup: shared engine-core @0x801658EC (src/shared) */

DEFINE_func_80165900()  /* dedup: shared engine-core @0x80165900 (src/shared) */

DEFINE_func_80165910()  /* dedup: shared engine-core @0x80165910 (src/shared) */

DEFINE_func_80165938()  /* dedup: shared engine-core @0x80165938 (src/shared) */

DEFINE_func_80165958()  /* dedup: shared engine-core @0x80165958 (src/shared) */

DEFINE_func_80165978()  /* dedup: shared engine-core @0x80165978 (src/shared) */

DEFINE_func_80165988()  /* dedup: shared engine-core @0x80165988 (src/shared) */

DEFINE_func_801659A8()  /* dedup: shared engine-core @0x801659A8 (src/shared) */

DEFINE_func_801659B8()  /* dedup: shared engine-core @0x801659B8 (src/shared) */

DEFINE_func_801659CC()  /* dedup: shared engine-core @0x801659CC (src/shared) */



DEFINE_func_801659DC()  /* dedup: shared engine-core @0x801659DC (src/shared) */


DEFINE_func_80165A18()  /* dedup: shared engine-core @0x80165A18 (src/shared) */

DEFINE_func_80165A20()  /* dedup: shared engine-core @0x80165A20 (src/shared) */

DEFINE_func_80165A50()  /* dedup: shared engine-core @0x80165A50 (src/shared) */

DEFINE_func_80165A78()  /* dedup: shared engine-core @0x80165A78 (src/shared) */


extern u8 D_80078EC1;
extern void (*D_8018E3C4[])(void);

void func_80165AC8(void) {
    D_8018E3C4[D_80078EC1 & 0x7F]();
}


DEFINE_func_80165B08()  /* dedup: shared engine-core @0x80165B08 (src/shared) */

DEFINE_func_80165B10()  /* dedup: shared engine-core @0x80165B10 (src/shared) */

DEFINE_func_80165B18()  /* dedup: shared engine-core @0x80165B18 (src/shared) */

DEFINE_func_80165B20()  /* dedup: shared engine-core @0x80165B20 (src/shared) */


extern void (*D_8018E440[])(void);

void func_80165B28(void *a0) {
    *(u32 *)((s32)a0 + 0x44) |= 8;
    D_8018E440[*(u8 *)((s32)a0 + 0x197)]();
}


DEFINE_func_80165B6C()  /* dedup: shared engine-core @0x80165B6C (src/shared) */

DEFINE_func_80165BB4()  /* dedup: shared engine-core @0x80165BB4 (src/shared) */

DEFINE_func_80165BFC()  /* dedup: shared engine-core @0x80165BFC (src/shared) */

DEFINE_func_80165C58()  /* dedup: shared engine-core @0x80165C58 (src/shared) */

DEFINE_func_80165C78()  /* dedup: shared engine-core @0x80165C78 (src/shared) */

DEFINE_func_80165CA0()  /* dedup: shared engine-core @0x80165ca0 (src/shared) */


extern M2C_UNK D_801E8DCC;

void func_80165E2C(u16 *arg0) {
    func_8001534C(0, &D_801E8DCC, 0x80, 0x80, 0, 0);
    func_800153CC(1, *arg0, 0xA8, 0x80, 0x40, 0);
}


DEFINE_func_80165E90()  /* dedup: shared engine-core @0x80165E90 (src/shared) */

DEFINE_func_80165FA4()  /* dedup: shared engine-core @0x80165FA4 (src/shared) */


DEFINE_func_80166018()  /* dedup: shared engine-core @0x80166018 (src/shared) */


DEFINE_func_80166054()  /* dedup: shared engine-core @0x80166054 (src/shared) */

DEFINE_func_801661CC()  /* dedup: shared engine-core @0x801661CC (src/shared) */

DEFINE_func_80166244()  /* dedup: shared engine-core @0x80166244 (src/shared) */

DEFINE_func_8016629C()  /* dedup: shared engine-core @0x8016629C (src/shared) */

DEFINE_func_801662F4()  /* dedup: shared engine-core @0x801662F4 (src/shared) */

DEFINE_func_8016634C()  /* dedup: shared engine-core @0x8016634C (src/shared) */

DEFINE_func_801663A4()  /* dedup: shared engine-core @0x801663A4 (src/shared) */


DEFINE_func_801663FC()  /* dedup: shared engine-core @0x801663FC (src/shared) */


DEFINE_func_80166438()  /* dedup: shared engine-core @0x80166438 (src/shared) */

DEFINE_func_801665B4()  /* dedup: shared engine-core @0x801665B4 (src/shared) */


DEFINE_func_80166618()  /* dedup: shared engine-core @0x80166618 (src/shared) */



DEFINE_func_80166654()  /* dedup: shared engine-core @0x80166654 (src/shared) */


#include "common.h"

   /* 12-byte sub-table record (stride 0xC) */



DEFINE_func_80166690()  /* dedup: shared engine-core @0x80166690 (src/shared) */




/* func_80166994 — trail/afterimage ring recorder (0xC4-stride Trail records at D_801E9868).
 * param_2: 0=init, 1=advance(record), 2=fadeout; param_3: trail index (s16); param_4: divisor (s16).
 *
 * K&R definition: true s16 params => callee-side lazy per-use narrow/extend with raw pseudos
 * (s3/t0/s4 hold raw a1/a2/a3; first-use extension allocates IN PLACE into the arg reg), while
 * the promoted K&R type (int x4) stays compatible with the canon-sig s32 prototype in the TU.
 * Returns s32 (v0=1 when the fadeout completes, else 0) => the //@EDIT above flips the split's
 * canon-sig prototype return type, AND engine_core.h needs the once-global ec_edit (all 5 sites,
 * byte-neutral: every caller discards the result):
 *   ec_edit old: "extern void func_80166994(s32 a0, s32 a1, s32 a2, s32 a3); \"
 *   ec_edit new: "extern s32 func_80166994(s32 a0, s32 a1, s32 a2, s32 a3); \"
 * Without the ec_edit, cc1 hard-errors (conflicting types vs the void decls in DEFINE_ macros).
 *
 * Fully block-scoped (typedefs + externs inside the body) so the crack propagates ×134 via
 * family_remap with zero file-scope footprint. No register pins.
 */
s32 func_80166994(param_1, param_2, param_3, param_4)
    s32 param_1;
    s16 param_2;
    s16 param_3;
    s16 param_4;
{
    extern u8 D_801E9868[];
    extern void RotTransSV(void *a0, void *a1, void *a2);
    extern s32 VectorNormalSS(void *a0, void *a1);

    Trail *p = &((Trail *)D_801E9868)[param_3];
    s32 uVar6 = *(s32 *)(param_1 + 0x34);
    s16 v10[4];
    s16 v18[4];
    s16 v20[4];
    s16 v28[4];
    s16 out[4];
    s32 c;

    switch (param_2) {
    case 0:
        p->flag = 1;
        p->count = 0;
        p->idx = 0;
        p->timer = 0xf4;
        break;
    case 1:
        v20[0] = p->e[p->idx].f0;
        v20[1] = p->e[p->idx].f1;
        v20[2] = p->e[p->idx].f2;
        v28[0] = p->e[p->idx].f3;
        v28[1] = p->e[p->idx].f4;
        v28[2] = p->e[p->idx].f5;
        c = p->idx;
        p->idx = c + 1;
        if ((u8)(c + 1) > 0xf) {
            p->idx = 0;
        }
        if (p->count < 0xf) {
            p->count = p->count + 1;
        }
        break;
    case 2: {
        u8 bVar3 = p->timer - 0x10;
        p->timer = bVar3;
        if (bVar3 < 0x10) {
            p->flag = 0;
            return 1;
        }
        {
            u8 bVar1 = p->count;
            if (bVar1 >= 2 && (bVar3 >> 4) < bVar1) {
                p->count = bVar1 - 1;
            }
        }
        return 0;
    }
    }

    if (param_3 < 2) {
        func_801484B0((s32)v10, (s32)v18);
    } else {
        func_80148534((s32)v10, (s32)v18);
    }
    func_80165FA4(uVar6, (s32)v10, (s32)v18);
    ((void (*)(s32, s32, s32))func_80149350)(uVar6, (s32)v10, (s32)v10);
    RotTransSV(v18, v18, out);

    if (param_2 != 0) {
        v20[0] = (v10[0] + v20[0]) >> 1;
        v20[1] = (v10[1] + v20[1]) >> 1;
        v20[2] = (v10[2] + v20[2]) >> 1;
        v28[0] = (v18[0] + v28[0]) >> 1;
        v28[1] = (v18[1] + v28[1]) >> 1;
        v28[2] = (v18[2] + v28[2]) >> 1;
        v20[0] = v20[0] - v28[0];
        v20[1] = v20[1] - v28[1];
        v20[2] = v20[2] - v28[2];
        VectorNormalSS(v20, v20);
        v20[0] = v28[0] + v20[0] / param_4;
        v20[1] = v28[1] + v20[1] / param_4;
        v20[2] = v28[2] + v20[2] / param_4;
        p->e[p->idx].f0 = v20[0];
        p->e[p->idx].f1 = v20[1];
        p->e[p->idx].f2 = v20[2];
        p->e[p->idx].f3 = v28[0];
        p->e[p->idx].f4 = v28[1];
        p->e[p->idx].f5 = v28[2];
        c = p->idx;
        p->idx = c + 1;
        if ((u8)(c + 1) > 0xf) {
            p->idx = 0;
        }
        if (p->count < 0xf) {
            p->count = p->count + 1;
        }
    }

    p->e[p->idx].f0 = v10[0];
    p->e[p->idx].f1 = v10[1];
    p->e[p->idx].f2 = v10[2];
    p->e[p->idx].f3 = v18[0];
    p->e[p->idx].f4 = v18[1];
    p->e[p->idx].f5 = v18[2];
    return 0;
}


// @class: regalloc-order
// @stuck: none — MATCH (69 ins). Pins $s4/$s1 for param_2/param_3 + a1/a2-pinned temps
//   with non-volatile SHB barriers force the sign-ext move-form; short iVar2 (unpinned)
//   gives the temp-form counter increment that fills the skip-branch delay slots;
//   loop-invariant eq=(p2==p3) hoisted; SHB(p2) after the move serializes param_2 before
//   param_3's sign-ext (last ordering swap); param_1/param_4 left natural (arg-order saves).


#define SHB(x) __asm__("" : "=r"(x) : "0"(x))

s32 func_80166F58(s32 param_1, s32 param_2, s32 param_3, s32 param_4)
{
    /* [T51] scoped in from file scope: a file-scope decl of these symbols constrains every
       LATER function in this TU, which blocks a byte-true decl of a different type.
       Declaration-only move (cookbook §103); the whole-binary byte-gate is the arbiter. */
    extern s32 D_8011D030;
    extern unsigned char D_801E9868[];

    register int p2 __asm__("$20");             /* $s4 */
    register int p3 __asm__("$17");             /* $s1 */
    register int t2 __asm__("$5");              /* a1 */
    register int t3 __asm__("$6");              /* a2 */
    unsigned short *puVar1;
    short iVar2;
    int eq;

    iVar2 = 0;
    puVar1 = ((unsigned short *)&D_8011D030);
    t2 = ((short)param_2); SHB(t2); p2 = t2; SHB(p2);
    t3 = ((short)param_3); SHB(t3); p3 = t3;
    eq = (p2 == p3);
    do {
        if ((puVar1 != ((unsigned short *)param_1)) &&
            ((unsigned int)*puVar1 == p2 || (unsigned int)*puVar1 == p3) &&
            (!eq ||
             *(int *)(puVar1 + 0x16) == *(int *)(((unsigned short *)param_1) + 0x16))) {
            ((void(*)(unsigned short *))func_80146C3C)(puVar1);
        }
        iVar2 = iVar2 + 1;
        puVar1 = puVar1 + 0x2c;
    } while (iVar2 < 0x1e);
    ((void(*)(void *, int))func_80016714)(&D_801E9868[((short)param_4) * 0xc4], 0xc4);
}





DEFINE_func_8016706C()  /* dedup: shared engine-core @0x8016706C (src/shared) */



// @class: schedule
// @stuck: 16/279 masked. 3 runs, ONE residual class: gcc's list-scheduler puts `la $s2` (p=DATA) + `addu $s4,$zero,$zero` (i=0) BEFORE the callee-arg address setup (addiu $a1,$sp,0x10 / addu $a2,$a1,$zero); the target emits them AFTER. Inert to ~40 statement-order permutations + pin/barrier combos (sched priority dominates the LUID tie-break, sched.c rank_for_schedule). Runs: 19-24 (blk1), 111-114 (region-B cx-load rotation), 177-182 (blk3). Permuter fuel.




DEFINE_func_801670E4()  /* dedup: shared engine-core @0x801670E4 (src/shared) */



 /* 0x20 bytes */






s32 func_80167540(s32 arg0) {

    struct Node_80167540 *node;
    struct Entity_80167540 *ent;
    s32 v;

    node = ((struct Entity_80167540 *)arg0)->unk34;
    if (node->unk0 == 1) {
        if (((struct Entity_80167540 *)arg0)->unk12 > ((struct Entity_80167540 *)arg0)->unk10) {
            if (((struct Entity_80167540 *)arg0)->unk1C > 0) {
                ((struct Entity_80167540 *)arg0)->unk10 = (s16) (rand() & 0x30);
                v = -0x30;
                goto shared;
            }
        } else if (((struct Entity_80167540 *)arg0)->unk1C < 0) {
            ((struct Entity_80167540 *)arg0)->unk10 = (s16) ((rand() & 0x30) + 0x40);
            v = 0x30;
shared:
            ((struct Entity_80167540 *)arg0)->unk1C = v;
        }
        ((struct Entity_80167540 *)arg0)->unk12 = (s16) (((struct Entity_80167540 *)arg0)->unk12 + ((struct Entity_80167540 *)arg0)->unk1C);
        ((struct Entity_80167540 *)arg0)->mat = node->unk20->mat;
        ((void (*)(struct Entity_80167540 *, s32, s32, s32))func_801670E4)(((struct Entity_80167540 *)arg0), 0, 0, 0);
        ent = ((struct Entity_80167540 *(*)(s32, struct Entity_80167540 *, s16, s16, s32, s32, s32))func_80146A6C)(0xE, ((struct Entity_80167540 *)arg0), node->unk6, node->unkA, node->unkE, 0, 0);
        if (ent != 0) {
            ent->mat = node->unk20->mat;
        }
        if (((struct Entity_80167540 *)arg0)->unk34->unk4C->unk44 & 0x20) {
            ((struct Entity_80167540 *)arg0)->unk30 = 0x600;
            ((struct Entity_80167540 *)arg0)->unk2 = (u16) (((struct Entity_80167540 *)arg0)->unk2 + 1);
        }
    } else {
        ((void(*)(struct Entity_80167540 *))func_80146C3C)(((struct Entity_80167540 *)arg0));
    }
}



DEFINE_func_80167714()  /* dedup: shared engine-core @0x80167714 (src/shared) */


DEFINE_func_801678B4()  /* dedup: shared engine-core @0x801678B4 (src/shared) */



DEFINE_func_801678F0()  /* dedup: shared engine-core @0x801678F0 (src/shared) */



DEFINE_func_80167A9C()  /* dedup: shared engine-core @0x80167A9C (src/shared) */


DEFINE_func_80167AD8()  /* dedup: shared engine-core @0x80167AD8 (src/shared) */

// @class: regalloc-order
// @stuck: none — MATCH expected; mirrors already-matched sibling func_8016A290 (same 3-loop tail), swapping the inline matrix-setup for a func_80168070 call + constant color block.

#include "common.h"





s32 func_80167AE0(s32 param_1, s32 param_2, s32 param_3) {
    extern void func_80168070(s32 param_1, s16 *param_2, s16 *param_3, void *param_4);
    extern s32 func_80017758(void *a0, void *a1);
    extern u8 D_8018E654;
    extern u8 D_8018E668[];

    struct Fr_80167AE0 fr;
    u8 *p;
    s32 i;
    register s32 t __asm__("$2");
    register s32 zr __asm__("$0");
    s32 flags;

    func_80168070(param_1, ((s16 *)param_2), ((s16 *)param_3), fr.matrix);

    fr.v[3].z = 0;
    fr.v[2].z = 0;
    fr.v[0].z = 0;
    fr.v[1].z = 0;
    fr.v[1].y = 0;
    fr.v[1].x = 0;
    flags = D_800B99DA;
    if (flags & 1) {
        fr.col[1].r = 0xa0;
    } else if (flags & 2) {
        fr.col[1].r = 0xc0;
    } else {
        fr.col[1].r = 0x80;
    }

    p = ((u8 *)&D_8018E654);
    fr.col[0].b = 0;
    fr.col[0].g = 0;
    fr.col[0].r = 0;
    fr.col[2].b = 0;
    fr.col[2].g = 0;
    fr.col[2].r = 0;
    fr.col[3].b = 0;
    fr.col[3].g = 0;
    fr.col[3].r = 0;
    fr.code = 0x50000000;
    fr.col[1].b = fr.col[1].r >> 2;
    fr.col[1].g = fr.col[1].r >> 2;
    i = 0;
L1:
        fr.v[0].x = (s8)*p++;
        fr.v[0].y = (s8)*p++;
        fr.v[2].x = (s8)*p++;
        fr.v[2].y = (s8)*p++;
        fr.v[3].x = (s8)*p++;
        fr.v[3].y = (s8)*p--;
        func_80017758(fr.v, fr.matrix);
        t = i + 1;
        i = t + zr;
        if ((s16)t < 4) goto L1;

    fr.v[3].y = 0;
    fr.v[2].y = 0;
    fr.v[0].y = 0;
    fr.v[1].y = 0;
    fr.v[1].x = 0;
    fr.v[1].z = -0x20;
    p = D_8018E668;
    i = 0;
L2:
        fr.v[0].x = (s8)*p++;
        fr.v[0].z = (s8)*p++;
        fr.v[2].x = (s8)*p++;
        fr.v[2].z = (s8)*p++;
        fr.v[3].x = (s8)*p++;
        fr.v[3].z = (s8)*p--;
        func_80017758(fr.v, fr.matrix);
        if ((s16)i == 1) {
            fr.v[1].z = 0x20;
            p += 2;
        }
        t = i + 1;
        i = t + zr;
        if ((s16)t < 4) goto L2;

    p += 2;
    fr.v[0].x = 0;
    fr.v[0].z = -0x20;
    fr.col[0].r = fr.col[1].r;
    fr.col[0].b = fr.col[1].g;
    fr.col[0].g = fr.col[1].g;
    i = 0;
L3:
        fr.v[2].x = (s8)*p++;
        fr.v[2].z = (s8)*p++;
        fr.v[3].x = (s8)*p++;
        fr.v[3].z = (s8)*p++;
        func_80017758(fr.v, fr.matrix);
        t = i + 1;
        i = t + zr;
        if ((s16)t < 2) goto L3;
}




// @class: schedule
// @stuck: none — MATCH. The between-loops f1/f2 store-swap (0x55/0x56) is fixed by writing f2's assign first, then the chained `buf[0x44] = buf[0x45] = buf[0x45] << 1;` — the chain keeps f1's read first (read order fixed by -0x12 in $v0) while emitting f2's store (0x56) ahead of the f1/f0 pair (0x55,0x54). 173/173.

extern void func_80168070(s32 a0, s16 *a1, s16 *a2, void *a3);
extern u16  D_800B99DA;
extern u8   D_8018E4A8[];
extern u8   D_8018E4BC[];

s32 func_80167DBC(s32 arg0, s32 arg1, s32 arg2) {
    u8 buf[0x54];
    u8 *p;
    s16 i;

    func_80168070(arg0, ((s16 *)arg1), ((s16 *)arg2), buf);

    *(s16 *)(buf + 0x3C) = 0;
    *(s16 *)(buf + 0x34) = 0;
    *(s16 *)(buf + 0x24) = 0;
    *(s16 *)(buf + 0x2C) = 0;
    *(s16 *)(buf + 0x2A) = 0;
    *(s16 *)(buf + 0x28) = 0;
    if (D_800B99DA & 1) {
        buf[0x46] = 0x58;
    } else {
        buf[0x46] = 0x48;
    }
    buf[0x45] = buf[0x46] >> 2;
    buf[0x44] = buf[0x45];
    if (((u8 (*)(s32))func_80029178)(0x81) != 0) {
        buf[0x45] = buf[0x45] << 2;
        buf[0x46] = buf[0x46] >> 1;
    }

    p = D_8018E4A8;
    buf[0x42] = 0;
    buf[0x41] = 0;
    buf[0x40] = 0;
    buf[0x4A] = 0;
    buf[0x49] = 0;
    buf[0x48] = 0;
    buf[0x4E] = 0;
    buf[0x4D] = 0;
    buf[0x4C] = 0;
    *(s32 *)(buf + 0x50) = 0x50000000;

    for (i = 0; i < 4; i++) {
        *(s16 *)(buf + 0x20) = (s8)*p++;
        *(s16 *)(buf + 0x22) = (s8)*p++;
        *(s16 *)(buf + 0x30) = (s8)*p++;
        *(s16 *)(buf + 0x32) = (s8)*p++;
        *(s16 *)(buf + 0x38) = (s8)*p++;
        *(s16 *)(buf + 0x3A) = (s8)*p--;
        func_80017758(buf + 0x20, buf);
    }

    p = D_8018E4BC;
    *(s16 *)(buf + 0x2C) = -0x12;
    *(s16 *)(buf + 0x3A) = 0;
    *(s16 *)(buf + 0x32) = 0;
    *(s16 *)(buf + 0x22) = 0;
    *(s16 *)(buf + 0x2A) = 0;
    *(s16 *)(buf + 0x28) = 0;
    buf[0x46] = buf[0x46] << 1;
    buf[0x44] = buf[0x45] = buf[0x45] << 1;

    for (i = 0; i < 4; i++) {
        *(s16 *)(buf + 0x20) = (s8)*p++;
        *(s16 *)(buf + 0x24) = (s8)*p++;
        *(s16 *)(buf + 0x30) = (s8)*p++;
        *(s16 *)(buf + 0x34) = (s8)*p++;
        *(s16 *)(buf + 0x38) = (s8)*p++;
        *(s16 *)(buf + 0x3C) = (s8)*p--;
        if (i == 2) {
            buf[0x4E] = buf[0x46];
            buf[0x4D] = buf[0x44];
            buf[0x4C] = buf[0x4D];
        } else if (i == 3) {
            buf[0x4E] = 0;
            buf[0x4D] = 0;
            buf[0x4C] = buf[0x4D];
            buf[0x42] = buf[0x46];
            buf[0x41] = buf[0x44];
            buf[0x40] = buf[0x44];
        }
        func_80017758(buf + 0x20, buf);
    }
}


DEFINE_func_80168070()  /* dedup: shared engine-core @0x80168070 (src/shared) */


extern s32 func_80029178(s32 arg);
extern s32 func_80166F58(s32, s32, s32, s32);

void func_801681FC(s32 param_1) {

    extern u8 D_8018E500[];
    extern u8 D_8018E4D0[];
    extern u8 D_8018E4D1[];
    s32 iVar3;
    s32 a3;

    *(s16 *)(param_1 + 0x28) = func_80029178(0x81) & 0xFF;
    *(s32 *)(param_1 + 0x30) = D_8018E500[*(s32 *)(param_1 + 0x2C)];
    iVar3 = (*(s32 *)(param_1 + 0x2C) << 0x11) >> 0x10;
    *(s16 *)(param_1 + 0x2A) = D_8018E4D0[iVar3];
    *(s32 *)(param_1 + 0x1C) = D_8018E4D1[iVar3];
    a3 = *(s32 *)(param_1 + 0x2C) & 1;
    *(s32 *)(param_1 + 0x2C) = a3;
    ((void (*)(s32, s32, s32, s32))func_80166F58)(param_1, 4, 4, a3);
    *(s16 *)(param_1 + 2) = *(s16 *)(param_1 + 2) + 1;
}


DEFINE_func_8016829C()  /* dedup: shared engine-core @0x8016829C (src/shared) */

DEFINE_func_80168328()  /* dedup: shared engine-core @0x80168328 (src/shared) */

DEFINE_func_801683D8()  /* dedup: shared engine-core @0x801683D8 (src/shared) */


extern s32 func_80166F58(s32, s32, s32, s32);

void func_80168430(s32 param_1) {

    extern u8 D_8018E50C[];
    extern u8 D_8018E4E4[];
    extern u8 D_8018E4E5[];
    s32 iVar1;

    *(s32 *)(param_1 + 0x30) = D_8018E50C[*(s32 *)(param_1 + 0x2C)];
    iVar1 = (*(s32 *)(param_1 + 0x2C) << 0x11) >> 0x10;
    *(s16 *)(param_1 + 0x2A) = D_8018E4E4[iVar1];
    *(s32 *)(param_1 + 0x1C) = D_8018E4E5[iVar1];
    ((void (*)(s32, s32, s32, s32))func_80166F58)(param_1, 5, 0x3B, 2);
    *(s16 *)(param_1 + 2) = *(s16 *)(param_1 + 2) + 1;
}


DEFINE_func_801684B4()  /* dedup: shared engine-core @0x801684B4 (src/shared) */

DEFINE_func_80168540()  /* dedup: shared engine-core @0x80168540 (src/shared) */

DEFINE_func_801685EC()  /* dedup: shared engine-core @0x801685EC (src/shared) */

DEFINE_func_80168640()  /* dedup: shared engine-core @0x80168640 (src/shared) */

DEFINE_func_80168664()  /* dedup: shared engine-core @0x80168664 (src/shared) */


DEFINE_func_80168744()  /* dedup: shared engine-core @0x80168744 (src/shared) */


DEFINE_func_80168780()  /* dedup: shared engine-core @0x80168780 (src/shared) */

DEFINE_func_801687CC()  /* dedup: shared engine-core @0x801687CC (src/shared) */

// @class: decl-conflict (reconcile) — MATCH (108 ins), real-TU verified via rtu_match
// @crack: The wave-2 "8-residual SCHEDULE" note was a STALE-OBJECT / isolation phantom (§42b):
//   in the real TU the draft NOCOMPILEs — DEFINE_func_801687CC() (split line ~6757) expands
//   `extern void func_80168828(void);` right before the def, so `void func_80168828(s32 param_1)`
//   is a HARD `conflicting types` error (cc1 exit 33). RECONCILE-FIRST fix (sweep-safe, lives
//   entirely in the def — no //@EDIT, no macro edit): declare the fn `(void)` and capture a0 via
//     register s32 a0v __asm__("$4");  s32 param_1 = a0v;
//   The register-var binds incoming $a0; copying it into a NORMAL pseudo (live across the calls)
//   makes gcc allocate param_1 to a callee-saved reg, emitting the target's `addu $s1,$a0,$zero`
//   at idx2. NOTE: a DIRECT `register s32 param_1 __asm__("$4")` FAILS (param_1 stays in the
//   call-clobbered $a0 → 100-off). With this reconcile, gcc's natural schedule places the CSE'd
//   `li $v1,0x40` at idx15 with ZERO extra levers — the §42a lever-4 consumer-block reorder was
//   never needed. The $v1 pin (register c40 __asm__("$3")) is still load-bearing (else 0x40 folds
//   to a $v0 immediate). 134-overlay family exemplar: only D_8018E550 differs -> banks x134.
#include "common.h"



DEFINE_func_80168828()  /* dedup: shared engine-core @0x80168828 (src/shared) */




DEFINE_func_801689D8()  /* dedup: shared engine-core @0x801689D8 (src/shared) */


DEFINE_func_80168A14()  /* dedup: shared engine-core @0x80168A14 (src/shared) */

DEFINE_func_80168A88()  /* dedup: shared engine-core @0x80168A88 (src/shared) */


DEFINE_func_80168AA8()  /* dedup: shared engine-core @0x80168AA8 (src/shared) */


DEFINE_func_80168AE4()  /* dedup: shared engine-core @0x80168AE4 (src/shared) */


extern void func_80168BDC(s32 a0, s32 a1, s32 a2, s32 a3);
/* Conform to the TU's canonical decl (jr_8015C32C.c:5546 `extern void func_80146C3C(void);`)
 * and cast at the use site — same escape the TU already uses at :6388. Codegen-neutral. */
extern void func_80146C3C(void);

void func_80168B70(s32 a0) {
    s32 *p = (s32 *)a0;
    if (--p[0x1C / 4] != -1) {
        func_80168BDC(a0, 9, 3, 1);
    } else {
        func_80168BDC(a0, 9, 2, 1);
        ((void (*)(s32))func_80146C3C)(a0);
    }
}


DEFINE_func_80168BDC()  /* dedup: shared engine-core @0x80168BDC (src/shared) */


DEFINE_func_80168D58()  /* dedup: shared engine-core @0x80168D58 (src/shared) */


DEFINE_func_80168D94()  /* dedup: shared engine-core @0x80168D94 (src/shared) */

DEFINE_func_80168EC4()  /* dedup: shared engine-core @0x80168EC4 (src/shared) */

DEFINE_func_80168F40()  /* dedup: shared engine-core @0x80168F40 (src/shared) */


DEFINE_func_8016901C()  /* dedup: shared engine-core @0x8016901C (src/shared) */


DEFINE_func_80169058()  /* dedup: shared engine-core @0x80169058 (src/shared) */

DEFINE_func_801691B8()  /* dedup: shared engine-core @0x801691B8 (src/shared) */

DEFINE_func_80169228()  /* dedup: shared engine-core @0x80169228 (src/shared) */


DEFINE_func_801693CC()  /* dedup: shared engine-core @0x801693CC (src/shared) */


DEFINE_func_80169408()  /* dedup: shared engine-core @0x80169408 (src/shared) */

DEFINE_func_8016951C()  /* dedup: shared engine-core @0x8016951C (src/shared) */

DEFINE_func_80169584()  /* dedup: shared engine-core @0x80169584 (src/shared) */

DEFINE_func_801696D8()  /* dedup: shared engine-core @0x801696D8 (src/shared) */


DEFINE_func_80169830()  /* dedup: shared engine-core @0x80169830 (src/shared) */


DEFINE_func_8016986C()  /* dedup: shared engine-core @0x8016986C (src/shared) */

DEFINE_func_801699D0()  /* dedup: shared engine-core @0x801699D0 (src/shared) */

DEFINE_func_80169A4C()  /* dedup: shared engine-core @0x80169A4C (src/shared) */


DEFINE_func_80169B80()  /* dedup: shared engine-core @0x80169B80 (src/shared) */




DEFINE_func_80169BBC()  /* dedup: shared engine-core @0x80169BBC (src/shared) */


DEFINE_func_80169E44()  /* dedup: shared engine-core @0x80169E44 (src/shared) */


DEFINE_func_80169F00()  /* dedup: shared engine-core @0x80169F00 (src/shared) */



// @class: plumbing
// @stuck: none — MATCH (expected; simple straight-line + single branch, one call-crossing local in $s0)

extern void func_800D1FC8(s32 a0, s32 a1);
extern s32 func_800D21C4(s32 a0, void *a1, s32 a2);
extern void func_80128EA8(s32 a0, s32 a1, s32 a2);
extern void func_80146C3C(void);

extern char D_8018E5FC[];
extern char D_8018E5BC[];

void func_80169F3C(int param_1)
{
    int iVar1;

    ((int (*)(int, int))func_800D1FC8)(param_1, 6);
    iVar1 = func_800D21C4(param_1, D_8018E5FC, 0x16);
    if (iVar1 != 0) {
        *(int *)(param_1 + 0x20) = iVar1;
        *(short *)(iVar1 + 0x1a) = 0x2000;
        *(short *)(iVar1 + 0x18) = 0x2000;
        *(char *)(iVar1 + 0x26) = 0x60;
        *(char *)(iVar1 + 0x25) = 0x60;
        *(char *)(iVar1 + 0x24) = 0x60;
        *(unsigned int *)(iVar1 + 4) = *(unsigned int *)(iVar1 + 4) | 0x50000000;
        ((void (*)(int, int, void *))func_80128EA8)(iVar1, param_1 + 0x24, D_8018E5BC);
        *(short *)(param_1 + 2) = *(short *)(param_1 + 2) + 1;
    } else {
        ((void (*)(int))func_80146C3C)(param_1);
    }
}


DEFINE_func_80169FE0()  /* dedup: shared engine-core @0x80169FE0 (src/shared) */


DEFINE_func_8016A020()  /* dedup: shared engine-core @0x8016A020 (src/shared) */


DEFINE_func_8016A05C()  /* dedup: shared engine-core @0x8016A05C (src/shared) */

DEFINE_func_8016A08C()  /* dedup: shared engine-core @0x8016A08C (src/shared) */

DEFINE_func_8016A1CC()  /* dedup: shared engine-core @0x8016A1CC (src/shared) */

// @class: regalloc-order
// @stuck: none — MATCH (284 ins). Loop-counter biv update: pinned $v0 temp + $0-add opaque copy (i = t + zr) forces the target's 2-insn `addiu v0,s1,1; addu s1,v0,zero` and keeps CSE from rewriting the (s16)t test to read s1.

#include "common.h"





void func_8016A290(s32 param_1, void *param_2, void *param_3) {
    extern u8 D_8018E654;
    extern u8 D_8018E668[];

    struct Fr_8016A290 fr;
    u8 *p;
    s32 i;
    register s32 t __asm__("$2");
    register s32 zr __asm__("$0");
    s32 flags;
    s32 iVar3;

    iVar3 = *(s32 *)(param_1 + 0x34);

    fr.center.x = (*((s16 *)param_2) + *((s16 *)param_3)) >> 1;
    fr.center.y = (((s16 *)param_2)[1] + ((s16 *)param_3)[1]) >> 1;
    fr.center.z = (((s16 *)param_2)[2] + ((s16 *)param_3)[2]) >> 1;
    ((void(*)(s32, void *, void *))func_80149350)(iVar3, &fr.center, &fr.center);

    *(u16 *)(param_1 + 0x6) = *(u16 *)&fr.center.x;
    *(u16 *)(param_1 + 0xA) = *(u16 *)&fr.center.y;
    *(u16 *)(param_1 + 0xE) = *(u16 *)&fr.center.z;
    func_800D20C0(&fr.center, &fr.diff, 8);
    func_80017E68(&fr.center, fr.mtx);

    fr.diff.x = *(u16 *)((s16 *)param_3) - *(u16 *)((s16 *)param_2);
    fr.diff.y = *(u16 *)(((s16 *)param_3) + 1) - *(u16 *)(((s16 *)param_2) + 1);
    fr.diff.z = *(u16 *)(((s16 *)param_3) + 2) - *(u16 *)(((s16 *)param_2) + 2);
    ((void(*)(s32, void *, void *))ApplyMatrixSV)(*(s32 *)(iVar3 + 0x20) + 0x34, &fr.diff, &fr.diff);
    func_800D23D0(&fr.diff);
    RotMatrixYXZ(&fr.diff, fr.mtx);

    fr.pos[0] = D_801269A4 - fr.center.x;
    fr.pos[1] = D_801269A8 - fr.center.y;
    fr.pos[2] = D_801269AC - fr.center.z;
    ApplyTransposeMatrixLV(fr.mtx, fr.pos, fr.pos);
    fr.diff.z = -ratan2(fr.pos[0], fr.pos[1]);
    RotMatrixYXZ(&fr.diff, fr.mtx);

    fr.v[3].z = 0;
    fr.v[2].z = 0;
    fr.v[0].z = 0;
    fr.v[1].z = 0;
    fr.v[1].y = 0;
    fr.v[1].x = 0;
    flags = D_800B99DA;
    if (flags & 1) {
        fr.col[1].r = *(s32 *)(param_1 + 0x30) + 0x20;
    } else if (flags & 2) {
        fr.col[1].r = *(s32 *)(param_1 + 0x30) + 0x40;
    } else {
        fr.col[1].r = *(s32 *)(param_1 + 0x30);
    }

    p = ((u8 *)&D_8018E654);
    fr.col[0].b = 0;
    fr.col[0].g = 0;
    fr.col[0].r = 0;
    fr.col[2].b = 0;
    fr.col[2].g = 0;
    fr.col[2].r = 0;
    fr.col[3].b = 0;
    fr.col[3].g = 0;
    fr.col[3].r = 0;
    fr.code = 0x50000000;
    fr.col[1].b = fr.col[1].r >> 3;
    fr.col[1].g = fr.col[1].r >> 3;
    i = 0;
L1:
        fr.v[0].x = (s8)*p++;
        fr.v[0].y = (s8)*p++;
        fr.v[2].x = (s8)*p++;
        fr.v[2].y = (s8)*p++;
        fr.v[3].x = (s8)*p++;
        fr.v[3].y = (s8)*p--;
        func_80017758(fr.v, fr.mtx);
        t = i + 1;
        i = t + zr;
        if ((s16)t < 4) goto L1;

    fr.v[3].y = 0;
    fr.v[2].y = 0;
    fr.v[0].y = 0;
    fr.v[1].y = 0;
    fr.v[1].x = 0;
    fr.v[1].z = -0x20;
    p = D_8018E668;
    i = 0;
L2:
        fr.v[0].x = (s8)*p++;
        fr.v[0].z = (s8)*p++;
        fr.v[2].x = (s8)*p++;
        fr.v[2].z = (s8)*p++;
        fr.v[3].x = (s8)*p++;
        fr.v[3].z = (s8)*p--;
        func_80017758(fr.v, fr.mtx);
        if ((s16)i == 1) {
            fr.v[1].z = 0x20;
            p += 2;
        }
        t = i + 1;
        i = t + zr;
        if ((s16)t < 4) goto L2;

    p += 2;
    fr.v[0].x = 0;
    fr.v[0].z = -0x20;
    fr.col[0].r = fr.col[1].r;
    fr.col[0].b = fr.col[1].g;
    fr.col[0].g = fr.col[1].g;
    i = 0;
L3:
        fr.v[2].x = (s8)*p++;
        fr.v[2].z = (s8)*p++;
        fr.v[3].x = (s8)*p++;
        fr.v[3].z = (s8)*p++;
        func_80017758(fr.v, fr.mtx);
        t = i + 1;
        i = t + zr;
        if ((s16)t < 2) goto L3;
}




DEFINE_func_8016A700()  /* dedup: shared engine-core @0x8016A700 (src/shared) */


// Seed for func_8016A73C (ov_SC01_077 exemplar). Overlay-local struct guessed.





s32 func_8016A73C(s32 arg0) {
    int sp10[8];
    short v[3];   /* sp30, sp32, sp34 */
    int r;
    short tmp;

    r = ((int(*)())rand)();
    v[1] = ((r & 0x7F) << 4) + 0x400;
    v[0] = ((unsigned)(r & 0x7F00) >> 5) - 0x300;
    v[2] = 0;
    ((void(*)(short *, void *))RotMatrixYXZ)(v, sp10);
    ((void(*)(int, void *))func_80048EAC)(((Obj_8016A73C *)arg0)->unk34->unk34->unk20 + 0x34, sp10);
    v[0] = 0;
    v[1] = 0;
    v[2] = -0x50;
    ((int(*)(void *, short *, short *))ApplyMatrixSV)(sp10, v, v);

    ((Obj_8016A73C *)arg0)->mat = (*(Mat_8016A73C*)&D_800AE620);

    tmp = ((Obj_8016A73C *)arg0)->unk6 + v[0];
    ((Obj_8016A73C *)arg0)->unk6 = tmp;
    ((Obj_8016A73C *)arg0)->mat.w[5] = tmp;
    tmp = ((Obj_8016A73C *)arg0)->unkA + v[1];
    ((Obj_8016A73C *)arg0)->unkA = tmp;
    ((Obj_8016A73C *)arg0)->mat.w[6] = tmp;
    tmp = ((Obj_8016A73C *)arg0)->unkE + v[2];
    ((Obj_8016A73C *)arg0)->unkE = tmp;
    ((Obj_8016A73C *)arg0)->unk2 = ((Obj_8016A73C *)arg0)->unk2 + 1;
    ((Obj_8016A73C *)arg0)->mat.w[7] = tmp;
}



DEFINE_func_8016A890()  /* dedup: shared engine-core @0x8016A890 (src/shared) */


// @class: struct
// @stuck: none — expect MATCH (single-call leaf, stack-struct prim build + averaging writeback)

DEFINE_func_8016A8FC()  /* dedup: shared engine-core @0x8016A8FC (src/shared) */


DEFINE_func_8016AA50()  /* dedup: shared engine-core @0x8016AA50 (src/shared) */


DEFINE_func_8016AB30()  /* dedup: shared engine-core @0x8016AB30 (src/shared) */

