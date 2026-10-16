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

s32 func_801E2668(void) {
    return (func_800167F0(0) & 0xffff) != 0;
}



extern void func_8016EDEC(s32 a0, s32 a1, s32 a2);
extern void func_801E293C(void *arg0);

s32 func_801E268C(s32 param_1) {
    ((void (*)(void *, s32))func_8016EDEC)((void *)func_801E293C, 0x1000000);
    ((Unkstruct_801E2670 *)param_1)->unk15 = ((Unkstruct_801E2670 *)param_1)->unk15 + 1;
    ((Unkstruct_801E2670 *)param_1)->unk28 = 16;
    return 0;
}




extern s32 func_800D1E28(void);
extern s32 func_8002D4C8(s32, s32);
extern s32 func_8001BFD0(void);
extern s32 func_800291B4(s32);
extern s32 func_80029524(void);
extern s32 func_800D0C48(s32);

s32 func_801E26D8(s32 param_1) {
    if ((((Unkstruct_801E26BC *)param_1)->unk28 = ((Unkstruct_801E26BC *)param_1)->unk28 - 1) == -1) {
        func_800D1E28();
        func_8002D4C8(0x1C, 0);
        func_8001BFD0();
        if ((func_800291B4(0xCE) & 0xFF) == 0 && func_80029524() == 0) {
            func_8002D4C8(0x1D, 0);
            func_800D0C48(1);
        }
        ((Unkstruct_801E26BC *)param_1)->unk15 = ((Unkstruct_801E26BC *)param_1)->unk15 + 1;
    }
    return 0;
}


extern void func_800D1EBC(void);
void func_801E2778(void) {
    func_800D1EBC();
}




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
void func_801E284C(void) {
    ((void (*)(void))func_80171A1C)();
    ((void (*)(void))func_80175414)();
}


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
void func_801E2978(void) {
    ((void (*)(void))func_80171A1C)();
}



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

void func_801E2B30(s32 param_1, s16 *param_2) {
    MATRIX m1;
    SVECTOR svec_in;
    SVECTOR svec_out;

    CAST_WIDTH(s32, param_1, 0x8)  = (s16)func_80012C6C((s32)((Unkstruct_8017D120 *)param_1)->unk8,  (s32)((Unkstruct_8017D120 *)param_1)->unkC,  0xa);
    ((Unkstruct_8017D120 *)param_1)->unk10 = (s16)func_80012C6C((s32)CAST_WIDTH(s16, param_1, 0x10), (s32)((Unkstruct_8017D120 *)param_1)->unk14, 0xa);
    ((Unkstruct_8017D120 *)param_1)->unk18 = func_80012ABC((s32)((Unkstruct_8017D120 *)param_1)->unk18, (s32)((Unkstruct_8017D120 *)param_1)->unk20, 0xa);
    ((Unkstruct_8017D120 *)param_1)->unk1A = func_80012ABC((s32)((Unkstruct_8017D120 *)param_1)->unk1A, (s32)((Unkstruct_8017D120 *)param_1)->unk22, 0xa);
    ((Unkstruct_8017D120 *)param_1)->unk1C = func_80012ABC((s32)((Unkstruct_8017D120 *)param_1)->unk1C, (s32)((Unkstruct_8017D120 *)param_1)->unk24, 0xa);
    ((Unkstruct_8017D120 *)param_1)->unk28 = func_80012C6C((s32)((Unkstruct_8017D120 *)param_1)->unk28, (s32)((Unkstruct_8017D120 *)param_1)->unk2E, 0xa);
    ((Unkstruct_8017D120 *)param_1)->unk2A = func_80012C6C((s32)((Unkstruct_8017D120 *)param_1)->unk2A, (s32)((Unkstruct_8017D120 *)param_1)->unk30, 0xa);
    ((Unkstruct_8017D120 *)param_1)->unk2C = func_80012C6C((s32)((Unkstruct_8017D120 *)param_1)->unk2C, (s32)((Unkstruct_8017D120 *)param_1)->unk32, 0xa);

    ((Unkstruct_8017D120 *)param_1)->unk48 = (s32)((Unkstruct_8017D120 *)param_1)->unk28 + (s32)param_2[0];
    ((Unkstruct_8017D120 *)param_1)->unk4C = (s32)((Unkstruct_8017D120 *)param_1)->unk2A + (s32)param_2[1];
    ((Unkstruct_8017D120 *)param_1)->unk50 = (s32)((Unkstruct_8017D120 *)param_1)->unk2C + (s32)param_2[2];
    func_80049CAC(param_1 + 0x18, (s32)&m1);

    m1.t[0] = ((Unkstruct_8017D120 *)param_1)->unk28 + param_2[0];
    m1.t[1] = ((Unkstruct_8017D120 *)param_1)->unk2A + param_2[1];
    m1.t[2] = ((Unkstruct_8017D120 *)param_1)->unk2C + param_2[2];
    svec_in.vx = 0;
    svec_in.vy = 0;
    svec_in.vz = ((Unkstruct_8017D120 *)param_1)->unk10;
    ((void (*)(s32, s32, s32))func_8012F14C)((s32)&m1, (s32)&svec_in, (s32)&svec_out);

    ((Unkstruct_8017D120 *)param_1)->unk3C = (s32)svec_out.vx;
    ((Unkstruct_8017D120 *)param_1)->unk40 = (s32)svec_out.vy;
    ((Unkstruct_8017D120 *)param_1)->unk44 = (s32)svec_out.vz;
}



s32 func_801E2CC8(void) {
    return 39;
}
