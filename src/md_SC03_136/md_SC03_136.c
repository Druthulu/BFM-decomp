#include "common.h"

extern u8 *D_80126B10;
extern u8 D_801E3230[];
extern void func_80175414(s32 _arg0);
void func_800167B8(int);

int func_801E2610(u8 *arg) {
    extern u8 *D_80126B10;
    D_80126B10 = D_801E3230;
    func_800167B8(0);
    ((void (*)(void))func_80175414)();
    arg[0x15]++;
    return 0;
}



extern s32 func_800167F0(s32 a0);

#define SHARED_FN func_801E2668
#include "../shared/multi/cls_511a8b68802b.h"
#undef SHARED_FN



extern void func_8016EDEC(s32 a0, s32 a1, s32 a2);
extern void func_801E293C(void *arg0);

s32 func_801E268C(s32 param_1) {
    ((void (*)(void *, s32))func_8016EDEC)((void *)func_801E293C, 0x1000000);
    ((Unkstruct_801E2670 *)param_1)->unk15 = ((Unkstruct_801E2670 *)param_1)->unk15 + 1;
    ((Unkstruct_801E2670 *)param_1)->unk28 = 16;
    return 0;
}




extern void func_800D1E28(void);
extern s32 func_8002D4C8(s32, s32);
extern void func_8001BFD0(void);
extern s32 func_800291B4(s32);
extern s32 func_80029524(void);
extern void func_800D0C48(s32);

#define SHARED_FN func_801E26D8
#include "../shared/multi/cls_250b43160334.h"
#undef SHARED_FN


extern s32 func_800D1EBC(void);
#define SHARED_FN func_801E2778
#include "../shared/multi/cls_37f67f3adb2e.h"
#undef SHARED_FN




void func_801E2798(void *a0) {

    extern void (*D_801E31D4[])(void);
    D_801E31D4[((Unkstruct_80159698_2 *)a0)->unk15]();
}




void func_801E27D4(void *a0) {

    extern void (*D_801E31DC[])(void);
    D_801E31DC[((Unkstruct_80159698_2 *)a0)->unk15]();
}




void func_801E2810(void *a0) {

    extern void (*D_801E3260[])(void);
    D_801E3260[((Unkstruct_80172CA0_2 *)a0)->unk214]();
}


extern void func_80171A1C(void*);
extern void func_80175414(s32 _arg0);
#define SHARED_FN func_801E284C
#include "../shared/multi/cls_b9caea59f74f.h"
#undef SHARED_FN


INCLUDE_RODATA("asm/md_SC03_136/nonmatchings/md_SC03_136", D_801E25E8);

const Blk8_md_SC03_076 D_801E25EC = {{0x00, 0x00, 0x7E, 0xFF, 0xB0, 0x00, 0x00, 0x00}};
extern s32 func_80171D78(u32, void *);
extern void func_80171A1C(void*);

void func_801E2874(u32 arg0) {
    Blk8_md_SC03_076 buffer;

    buffer = D_801E25EC;

    if (func_80171D78(arg0, &buffer)) {
        ((void (*)(u32))func_80171A1C)(arg0);
    }
}



extern s32 func_80014C54(s32, s32, s32);
extern void func_800D1724(void *);
extern void func_80171A1C(void *);

void func_801E28DC(void *arg0) {

    extern u8 D_801E3230[];
    s32 result;
    result = func_80014C54(0, 0, 0x80);
    if ((result << 16) != 0) {
        func_800D1724(&(*(int *)D_801E3230));
        func_80171A1C(arg0);
    }
}


void func_801E2934(void) {
}



void func_801E293C(void *a0) {

    extern void (*D_801E3270[])(void);
    D_801E3270[((Unkstruct_80172CA0_2 *)a0)->unk214]();
}


extern void func_80171A1C(void*);
#define SHARED_FN func_801E2978
#include "../shared/multi/cls_88741b5adb4e.h"
#undef SHARED_FN



const Blk8_md_SC03_076 D_801E25F4 = {{0xD5, 0xFF, 0x7E, 0xFF, 0xF5, 0xFE, 0x00, 0x00}};
extern s32 func_80171D78(u32, void *);
extern void func_80171A1C(void*);

void func_801E2998(u32 arg0) {
    Blk8_md_SC03_076 buffer;

    buffer = D_801E25F4;

    if (func_80171D78(arg0, &buffer)) {
        ((void (*)(u32))func_80171A1C)(arg0);
    }
}


void func_801E2A00(void) {
}

void func_801E2A08(void) {
    extern void func_8012A018(s32 a0, s32 a1);
    extern void func_8012A094(s32 a0);
    extern void func_801E2ACC(void *a0);

    extern s32 D_80126950;
    extern s32 D_80126954;
    extern s32 D_8012695C;
    extern s16 D_80126968;
    extern s16 D_8012696A;
    extern s16 D_8012696C;
    extern s16 D_80126976;
    extern s16 D_80126978;
    extern s16 D_8012697A;
    extern u8 D_80126948[];
    extern s16 D_801274E8;
    extern s16 D_801274EA;
    extern s16 D_801274EC;

    D_80126954 = 0x190;
    D_80126950 = 0x190;
    D_8012695C = 0x82;
    D_80126968 = 0xFB1;
    D_8012696A = 0x7C7;
    D_8012696C = 0;
    D_80126976 = 0;
    D_80126978 = -0x50;
    D_8012697A = 0;
    func_8012A018((s32)func_801E2ACC, 0);
    func_801E2ACC(D_80126948);
    func_8012A094((s32)D_80126948);
    D_801274EA = -0x82;
    D_801274E8 = 0;
    D_801274EC = -0x1B0;
}




void func_801E2ACC(void *a0) {

    extern void (*D_801E327C[])(void);
    D_801E327C[((Unkstruct_80126948 *)a0)->unk4]();
}


void func_801E2B08(void) {
    extern void func_801E2B30(s32 param_1, s16 *param_2);
    extern s16 D_801274E8;
    s32 x;

    func_801E2B30(x, &D_801274E8);
}


extern s32 func_80012ABC(s32 a0, s32 a1, s32 a2);
extern s32 func_80012C6C(s32 a0, s32 a1, s32 a2);
extern void func_80049CAC(s32 a0, s32 a1);
extern void func_8012F14C(s32 a0, s32 a1, s32 a2);

#define SHARED_FN func_801E2B30
#include "../shared/multi/cls_89463c3facc6.h"
#undef SHARED_FN



s32 func_801E2CC8(void) {
    return 39;
}
