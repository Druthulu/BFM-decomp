#include "common.h"

extern u8 *D_80126B10;
extern u8 D_801EE620[];
extern void func_80175414(s32 _arg0);
void func_800167B8(int);

int func_801ED9B0(u8 *arg) {
    extern u8 *D_80126B10;
    D_80126B10 = D_801EE620;
    func_800167B8(0);
    ((void (*)(void))func_80175414)();
    arg[0x15]++;
    return 0;
}



extern s32 func_800167F0(s32 a0);

s32 func_801EDA08(void) {
    return (func_800167F0(0) & 0xffff) != 0;
}



extern void func_8016EDEC(s32 a0, s32 a1, s32 a2);
extern void func_801EDCF4(void *arg0);

s32 func_801EDA2C(s32 param_1) {
    ((void (*)(void *, s32))func_8016EDEC)((void *)func_801EDCF4, 0x1000000);
    ((Unkstruct_801E2670 *)param_1)->unk15 = ((Unkstruct_801E2670 *)param_1)->unk15 + 1;
    ((Unkstruct_801E2670 *)param_1)->unk28 = 16;
    return 0;
}


extern s32 func_8001BFD0(void);
extern s32 func_800291B4(s32);
extern s32 func_80029504(void);
extern s32 func_8002D4C8(s32, s32);
extern s32 func_800D0C48(s32);
extern s32 func_800D1E28(void);

s32 func_801EDA78(s32 param_1) {
    u32 s1 = func_80029504();

    if ((((Unkstruct_801EDA64 *)param_1)->unk28 = ((Unkstruct_801EDA64 *)param_1)->unk28 - 1) == -1) {
        func_800D1E28();
        func_8002D4C8(0x1C, 0);
        func_8001BFD0();
        if ((func_800291B4(0xCE) & 0xFF) == 0 &&
            (s1 - 0x384) >= 0x6E && (s1 - 0x460) >= 0x32) {
            func_8002D4C8(0x1D, 0);
            func_800D0C48(1);
        }
        ((Unkstruct_801EDA64 *)param_1)->unk15 = ((Unkstruct_801EDA64 *)param_1)->unk15 + 1;
    }
    return 0;
}


extern void func_800D1EBC(void);
void func_801EDB30(void) {
    func_800D1EBC();
}




void func_801EDB50(void *a0) {

    extern void (*D_801EE5C4[])(void);
    D_801EE5C4[((Unkstruct_80159698_2 *)a0)->unk15]();
}




void func_801EDB8C(void *a0) {

    extern void (*D_801EE5CC[])(void);
    D_801EE5CC[((Unkstruct_80159698_2 *)a0)->unk15]();
}




void func_801EDBC8(void *a0) {

    extern void (*D_801EE650[])(void);
    D_801EE650[((Unkstruct_80172CA0_2 *)a0)->unk214]();
}


extern void func_80171A1C(void*);
extern void func_80175414(s32 _arg0);
void func_801EDC04(void) {
    ((void (*)(void))func_80171A1C)();
    ((void (*)(void))func_80175414)();
}


INCLUDE_RODATA("asm/md_SC05_027/nonmatchings/md_SC05_027", D_801ED988);

const Blk8_md_SC03_076 D_801ED98C = {{0x00, 0x00, 0x7E, 0xFF, 0xB0, 0x00, 0x00, 0x00}};
extern s32 func_80171D78(u32, void *);
extern void func_80171A1C(void*);

void func_801EDC2C(u32 arg0) {
    Blk8_md_SC03_076 buffer;

    buffer = D_801ED98C;

    if (func_80171D78(arg0, &buffer)) {
        ((void (*)(u32))func_80171A1C)(arg0);
    }
}



extern s32 func_80014C54(s32, s32, s32);
extern void func_800D1724(void *);
extern void func_80171A1C(void *);

void func_801EDC94(void *arg0) {

    extern u8 D_801EE620[];
    s32 result;
    result = func_80014C54(0, 0, 0x80);
    if ((result << 16) != 0) {
        func_800D1724(&(*(int *)D_801EE620));
        func_80171A1C(arg0);
    }
}


void func_801EDCEC(void) {
}



void func_801EDCF4(void *a0) {

    extern void (*D_801EE660[])(void);
    D_801EE660[((Unkstruct_80172CA0_2 *)a0)->unk214]();
}


extern void func_80171A1C(void*);
void func_801EDD30(void) {
    ((void (*)(void))func_80171A1C)();
}



const Blk8_md_SC03_076 D_801ED994 = {{0xD5, 0xFF, 0x7E, 0xFF, 0xF5, 0xFE, 0x00, 0x00}};
extern s32 func_80171D78(u32, void *);
extern void func_80171A1C(void*);

void func_801EDD50(u32 arg0) {
    Blk8_md_SC03_076 buffer;

    buffer = D_801ED994;

    if (func_80171D78(arg0, &buffer)) {
        ((void (*)(u32))func_80171A1C)(arg0);
    }
}


void func_801EDDB8(void) {
}

void func_801EDDC0(void) {
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
    extern void func_8012A018(s32 a0, s32 a1);
    extern void func_8012A094(s32 a0);
    extern void func_801EDE84(void *a0);

    D_80126954 = 0x190;
    D_80126950 = 0x190;
    D_8012695C = 0x82;
    D_80126968 = 0xFB1;
    D_8012696A = 0x7C7;
    D_8012696C = 0;
    D_80126976 = 0;
    D_80126978 = -0x50;
    D_8012697A = 0;
    func_8012A018((s32)func_801EDE84, 0);
    func_801EDE84(D_80126948);
    func_8012A094((s32)D_80126948);
    D_801274EA = -0x82;
    D_801274E8 = 0;
    D_801274EC = -0x1B0;
}




void func_801EDE84(void *a0) {

    extern void (*D_801EE66C[])(void);
    D_801EE66C[((Unkstruct_80126948 *)a0)->unk4]();
}


void func_801EDEC0(s32 param_1) {
    extern s16 D_801274E8;
    extern void func_801EDEE8(s32 param_1, s16 *param_2);
    func_801EDEE8(param_1, &D_801274E8);
}


extern s32 func_80012ABC(s32 a0, s32 a1, s32 a2);
extern s32 func_80012C6C(s32 a0, s32 a1, s32 a2);
extern void func_80049CAC(s32 a0, s32 a1);
extern void func_8012F14C(s32 a0, s32 a1, s32 a2);

void func_801EDEE8(s32 param_1, s16 *param_2) {
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




u8 func_801EE080(a0)
u32 a0;
{
    if ((u32)(a0 - 0x460) < 0x32) {
        return 0x89;
    }
    if ((u32)(a0 - 0x384) < 0x6E) {
        return 0x65;
    }
    if ((u32)(a0 - 0x64) < 0x1E) {
        return 0x28;
    }
    return 0xD;
}
