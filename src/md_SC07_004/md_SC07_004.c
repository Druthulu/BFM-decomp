#include "common.h"

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A0230);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A03A4);

INCLUDE_RODATA("asm/md_SC07_004/nonmatchings/md_SC07_004", D_801A00D8);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A0400);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A09E4);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A0A98);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A0C58);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A0CD0);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A0D40);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A108C);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A1124);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A115C);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A11D4);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A1400);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A1470);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A18F4);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A1984);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A19C0);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A1C38);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A1C7C);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A1E74);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A1E94);

INCLUDE_RODATA("asm/md_SC07_004/nonmatchings/md_SC07_004", D_801A0168);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A1F3C);

extern void func_8017F578(void);
void func_801A2310(void) {
    func_8017F578();
}


INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A2330);


s32 func_801A2350(s32 arg0) {
        return *(u16*)(arg0 + 0x34) == 0x6;
    }


INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A2364);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A2400);

s32 func_801A2C4C(void) {
    return 0;
}



s32 func_801A2C54(s32 arg0) {
        return *(u16*)(arg0 + 0x34) == 0x7;
    }


extern void func_8017C068(void);
void func_801A2C68(void) {
    func_8017C068();
}


INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A2C88);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A2CA4);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A2D78);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A2DC4);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A2E90);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A2F34);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A30C8);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A3114);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A3180);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A34C4);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A34FC);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A3594);

typedef struct { s16 m[3][3]; s32 t[3]; } MTX_CF90_801A3624;

void func_801A3624(s32 target, u16 *cur, s32 step)
{
    s32 t;
    s32 diff;
    s32 mag;

    t = (target - *cur) & 0xFFF;
    if (t < 0x800) {
        diff = t;
    } else {
        diff = t | 0xF000;
    }
    mag = diff;
    if ((s16)diff < 0) {
        mag = -diff;
    }
    __asm__ __volatile__("" : "=r"(diff) : "0"(diff) : "memory");
    if ((s16)mag > (u16)step) {
        if ((s16)diff < 0) {
            *cur = *cur - step;
        } else {
            *cur = *cur + step;
        }
    } else {
        *cur = target;
    }
}


INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A36A8);


void func_801A36F0(void *a0) {
        s32 v0 = *(u16 *)((s32)a0 + 0xA);
        s32 v1 = *(u16 *)((s32)a0 + 0x52);
        *(u16 *)((s32)a0 + 0x52) = 0;
        *(u16 *)((s32)a0 + 0x108) = 0;
        *(u16 *)((s32)a0 + 0xA) = v0 + v1;
    }


INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A370C);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A3744);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A3798);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A395C);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A39D0);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A3A6C);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A3B08);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A3B18);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A3D60);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A3EA8);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A3EEC);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A3F10);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A3FB0);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A4008);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A4060);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A40CC);


extern s32 func_8012C658(s32 arg0, s32 arg1, s32 arg2);

void func_801A417C(s32 arg0) {
    s32 i;

    for (i = 0; i < 15; i++) {
        func_8012C658(0x31f, i, arg0);
    }
}


INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A41CC);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A4258);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A4328);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A43EC);



void func_801A4420(void *a0) {

    extern void (*D_801AFF34[])(void);
    D_801AFF34[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A445C);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A44C4);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A4570);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A46B8);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A46D4);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A46F0);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A4724);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A4A18);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A4AAC);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A4ACC);



void func_801A4E80(void *a0) {

    extern void (*D_801B014C[])(void);
    D_801B014C[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A4EBC);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A4FDC);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A5094);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A5194);



void func_801A53B8(void *a0) {

    extern void (*D_801B0160[])(void);
    D_801B0160[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A53F4);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A5414);



void func_801A5470(void *a0) {

    extern void (*D_801B0168[])(void);
    D_801B0168[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A54AC);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A54F0);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A5654);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A5698);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A5798);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A57E8);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A5AA0);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A5AC0);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A5AE0);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A5B00);



void func_801A5B20(void *a0) {

    extern void (*D_801B02C8[])(void);
    D_801B02C8[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A5B5C);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A5C44);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A5CE8);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A5D68);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A5E60);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A6184);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A6330);


/* func_801A63A8 — guard-then-free tail (cookbook §71 sibling shape:
 * src/ov_SC02_011/ov_SC02_011_jr_8017AE2C.c func_80144458 tail, and
 * src/ov_SC03_099/ov_SC03_099_jr_80140608.c:2432 func_80016714(x, 0x38)). */

extern void func_80016714(void *a0, s32 a1);
extern void func_8012C218(void *a0);

void func_801A63A8(void *arg0) {
    void *temp_a0;

    temp_a0 = *(void **)((char *)arg0 + 0xCC);
    if (temp_a0 != NULL) {
        func_80016714(temp_a0, 0x38);
    }
    func_8012C218(arg0);
}




void func_801A63EC(void *a0) {

    extern void (*D_801B0338[])(void);
    D_801B0338[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A6428);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A649C);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A64DC);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A6560);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A6610);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A66DC);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A67F8);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A6908);

extern void func_801A1E94(void);
void func_801A6A18(void) {
    func_801A1E94();
}


INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A6A38);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A6AD0);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A6BC0);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A6CA8);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A6D90);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A6DF4);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A6E78);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A6EF4);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A6F3C);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A6FD4);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A70D0);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A7184);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A7200);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A72DC);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A7358);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A7604);



void func_801A77CC(void *a0) {

    extern void (*D_801B0378[])(void);
    D_801B0378[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A7808);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A7864);

INCLUDE_RODATA("asm/md_SC07_004/nonmatchings/md_SC07_004", D_801A01E8);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A788C);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A7AF8);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A7B08);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A7C34);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A7C58);


void func_801A7CC8(void *a0) {
        *(s32 *)((char *)a0 + 0x1c) = 0x4;
        *(s16 *)((char *)a0 + 0x2) = 0x4;
    }


INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A7CDC);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A7D18);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A7D34);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A7E5C);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A7F84);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A8054);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A80C0);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A8228);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A8294);



void func_801A8404(void *a0) {

    extern void (*D_801B038C[])(void);
    D_801B038C[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A8440);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A8494);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A8528);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A8564);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A85A8);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A861C);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A8670);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A86B4);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A86F8);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A8738);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A876C);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A87C4);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A881C);


extern void func_8012AD44(s32 *a0, s16 a1);

void func_801A8884(s32 *a0) {
    a0[7] = 0x3;
    func_8012AD44(a0, 2);
}


INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A88AC);



void func_801A8954(void *a0) {

    extern void (*D_801B03B8[])(void);
    D_801B03B8[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A8990);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A8A64);



void func_801A8B28(void *a0) {

    extern void (*D_801B0400[])(void);
    D_801B0400[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A8B64);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A8C58);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A8CE0);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A8DCC);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A8E34);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A900C);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A90D8);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A9270);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A930C);



void func_801A933C(void *a0) {

    extern void (*D_801B0494[])(void);
    D_801B0494[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A9378);



void func_801A93B8(void *a0) {

    extern void (*D_801B05FC[])(void);
    D_801B05FC[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A93F4);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A9454);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A94A0);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A9674);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A9810);



void func_801A98CC(void *a0) {

    extern void (*D_801B072C[])(void);
    D_801B072C[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A9908);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A9954);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A99A4);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A9AAC);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A9ADC);



void func_801A9B04(void *a0) {

    extern void (*D_801B0768[])(void);
    D_801B0768[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A9B40);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A9B80);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A9C00);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A9CAC);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A9EB0);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A9F5C);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A9FA8);



void func_801A9FC8(void *a0) {

    extern void (*D_801B0780[])(void);
    D_801B0780[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AA004);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AA0B4);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AA160);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AA210);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AA2F8);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AA3CC);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AA4A8);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AA4EC);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AA540);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AA584);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AA60C);



void func_801AA730(void *a0) {

    extern void (*D_801B07C0[])(void);
    D_801B07C0[*(u16 *)((s32)a0 + 0x2)]();
}




void func_801AA76C(void *a0) {

    extern void (*D_801B07C8[])(void);
    D_801B07C8[*(u16 *)((s32)a0 + 0x2)]();
}




void func_801AA7A8(void *a0) {

    extern void (*D_801B07D0[])(void);
    D_801B07D0[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AA7E4);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AA91C);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AA9D4);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AAA6C);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AAB28);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AACD4);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AADA8);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AAF34);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AAF8C);


extern void func_801AB1A8(void);
    void func_801AB178(s32 *param) {
        if (*(u16 *)((char *)param + 0x2) == 0) {
            ((void (*)(void))func_801AB1A8)();
        }
    }


INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AB1A8);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AB21C);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AB41C);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AB54C);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AB5D4);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AB694);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AB748);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AB78C);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AB818);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AB8C0);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AB9AC);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801ABA74);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801ABBA4);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801ABC04);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801ABC8C);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801ABDA4);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801ABEE0);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801ABFF8);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AC0D4);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AC150);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AC234);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AC29C);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AC3C8);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AC47C);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AC54C);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AC59C);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AC6C0);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AC794);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AC8B8);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AC940);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AC9CC);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801ACA88);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801ACB2C);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801ACC24);



void func_801ACD10(void *a0) {

    extern void (*D_801B07D8[])(void);
    D_801B07D8[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801ACD4C);



void func_801ACDC8(void *a0) {

    extern void (*D_801B07E0[])(void);
    D_801B07E0[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801ACE04);



void func_801ACE20(void *a0) {

    extern void (*D_801B07E8[])(void);
    D_801B07E8[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801ACE5C);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AD068);



void func_801AD1E4(void *a0) {

    extern void (*D_801B07F4[])(void);
    D_801B07F4[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AD220);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AD294);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AD2CC);

INCLUDE_RODATA("asm/md_SC07_004/nonmatchings/md_SC07_004", D_801A021C);

INCLUDE_RODATA("asm/md_SC07_004/nonmatchings/md_SC07_004", D_801A0220);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AD31C);


void func_801AD4C0(void *a0) {
        *(s32 *)((char *)a0 + 0x1c) = 0x10;
        *(s16 *)((char *)a0 + 0x2) = 0x1;
    }


INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AD4D4);



void func_801AD520(void *a0) {

    extern void (*D_801B081C[])(void);
    D_801B081C[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AD55C);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AD5B4);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AD640);



void func_801AD6C4(void *a0) {

    extern void (*D_801B0830[])(void);
    D_801B0830[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AD700);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AD7EC);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AD914);



void func_801AD9D4(void *a0) {

    extern void (*D_801B0884[])(void);
    D_801B0884[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801ADA10);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801ADA9C);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801ADBB0);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801ADC40);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801ADD98);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801ADE1C);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801ADF5C);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AE060);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AE138);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AE220);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AE324);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AE3A4);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AE408);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AE520);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AE624);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AE6D4);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AE734);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AE82C);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AE8B0);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AE908);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AE990);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AEA40);

s32 func_801AEAAC(void) {

    extern u8 D_801F8EB8[];
    s32 a0;
    s32 v1;
    v1 = (s32)D_801F8EB8;
    for (a0 = 0; a0 < 0x20; a0++, v1 += 0x24) {
        if (*(u16 *)v1 == 0) {
            return v1;
        }
    }
    return 0;
}


INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AEAE4);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AEB04);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AEB94);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AEC38);


extern void func_801AF2EC(void *a0);
extern void func_801AF368(void *a0);
extern void func_8012931C(struct vec *a0);
extern void func_801292C8(u8 *a0);

void func_801AF1EC(void *a0) {
    if (*(u16 *)((s32)a0 + 0x2) == 0) {
        func_801AF2EC(a0);
        return;
    }

    if (*(s32 *)((s32)a0 + 0x1C) != 0) {
        *(s32 *)((s32)a0 + 0x1C) -= 1;
        func_8012931C((struct vec *)a0);

        if (*(s16 *)((s32)a0 + 0x32) == 0) {
            u16 t = *(u16 *)((s32)a0 + 0xA) + 0x1000;
            if (t >= 0x1001) {
                func_801292C8((u8 *)a0);
                return;
            }
        }
    } else {
        func_801292C8((u8 *)a0);
        return;
    }

    *(s32 *)((s32)a0 + 0x14) += *(s32 *)((s32)a0 + 0x34);
    *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x14) += *(u16 *)((s32)a0 + 0x30);
    *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x8) = *(u16 *)((s32)a0 + 0x6);
    *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0xA) = *(u16 *)((s32)a0 + 0xA);
    *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0xC) = *(u16 *)((s32)a0 + 0xE);
    func_801AF368((void *)*(s32 *)((s32)a0 + 0x20));
}


INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AF2EC);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AF368);




// @class: loose-typing
// @stuck: none — MATCH (99 ins). short* for param_2/param_3: gcc emits lh where sign is live (<<1 for signed div), lhu where truncated to short (arith result / direct copy)

extern int rand(void);
extern int func_801AF9C8(short *pos, int a1, int a2);

void func_801AF808(unsigned short *param_1, short *param_2, short *param_3,
                   unsigned int param_4, int param_5)
{
    int r;
    int d;
    short buf[4];
    int p;

    if ((*param_1 & (short)((1 << param_4) - 1)) == 0) {
        r = rand();
        d = param_3[0] << 1;
        buf[0] = (param_2[0] + (r % d)) - param_3[0];
        r = rand();
        d = param_3[1] << 1;
        buf[1] = (param_2[1] + (r % d)) - param_3[1];
        r = rand();
        d = param_3[2] << 1;
        buf[2] = (param_2[2] + (r % d)) - param_3[2];
        buf[3] = param_3[3];
        p = func_801AF9C8(buf, 0, param_5);
        if (p != 0) {
            *(short *)(*(int *)(p + 0x20) + 0x18) = param_2[3];
        }
    }
    *param_1 = *param_1 + 1;
}


INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AF994);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AF9C8);
