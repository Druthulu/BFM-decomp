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

INCLUDE_ASM("asm/md_MAIN_015/nonmatchings/md_MAIN_015", func_800CAF0C);

INCLUDE_ASM("asm/md_MAIN_015/nonmatchings/md_MAIN_015", func_800CAF9C);

INCLUDE_ASM("asm/md_MAIN_015/nonmatchings/md_MAIN_015", func_800CB140);

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

INCLUDE_ASM("asm/md_MAIN_015/nonmatchings/md_MAIN_015", func_800CB2E0);

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


INCLUDE_ASM("asm/md_MAIN_015/nonmatchings/md_MAIN_015", func_800CB4F0);

INCLUDE_ASM("asm/md_MAIN_015/nonmatchings/md_MAIN_015", func_800CB6A4);

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


INCLUDE_ASM("asm/md_MAIN_015/nonmatchings/md_MAIN_015", func_800CB88C);

INCLUDE_ASM("asm/md_MAIN_015/nonmatchings/md_MAIN_015", func_800CB930);

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

