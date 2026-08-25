#include "common.h"

extern s32 func_800183E0(s32 *a0);
void func_800CAE0C(void) {

    extern s32 D_800CB2D4;
    func_800183E0(&D_800CB2D4);
}




void func_800CAE34(void *a0) {

    extern void (*D_800CB29C[])(void);
    *(u32 *)((s32)a0 + 0x44) |= 8;
    D_800CB29C[*(u8 *)((s32)a0 + 0x197)]();
}


extern s32 func_80161104(void);
extern void func_800CAEC0(u8 *a0);
void func_800CAE78(u8 *a0) {
    if (func_80161104()) {
        func_800CAEC0(a0);
        *(u8 *)(a0 + 0x197) = *(u8 *)(a0 + 0x197) + 1;
    }
}


INCLUDE_ASM("asm/md_MAIN_032/nonmatchings/md_MAIN_032", func_800CAEC0);

void func_800CAF60(void *a0) {
    extern void func_80147A84(s32 a0);
    extern void func_801473EC(s32 *a0);
    extern void func_80148038(s32 a0, s32 a1);
    extern void func_80147460(s32 a0);
    extern s32  func_80161418(void *a0);
    extern s32  func_80155FD4(s32 a0, s32 a1);

    *(u32 *)((u8 *)a0 + 0x44) |= 2;
    func_80147A84((s32)a0);
    func_801473EC((s32 *)a0);
    func_80148038((s32)a0, 0x20000);
    func_80147460((s32)a0);
    if (func_80161418(a0) == 0) {
        func_80155FD4((s32)a0, *(u8 *)((u8 *)a0 + 0x1AA));
    }
}


void func_800CAFD0(void *a0) {
    extern u8 D_8011F9D0[];
    extern void func_80162CCC();
    s32 i;
    u8 *ptr;

    for (i = 0; i < 0x14; i++) {
        ptr = D_8011F9D0 + (i * 0x68);
        if (*(u16 *)ptr == 0x18) {
            func_80162CCC(ptr);
        }
    }

    *(u32 *)((s32)a0 + 0x44) &= ~2;
}



extern void func_800CB24C(void);

void func_800CB054(void *arg0) {

    extern u8 D_80078EC1;
    extern void (*D_800CB2A8[])(void);
    if (D_80078EC1 == 0x9) {
        u16 v0 = *(u16 *)((u8 *)arg0 + 2);
        D_800CB2A8[v0]();
    } else {
        func_800CB24C();
    }
}


INCLUDE_ASM("asm/md_MAIN_032/nonmatchings/md_MAIN_032", func_800CB0B0);

#include "common.h"

typedef struct { s32 w[4]; } func_800CB188_Blk16;

extern void func_80149374(s32 a0, s32 a1);

void func_800CB188(void *arg0) {
    extern u16 D_800B99DA;
    s32 s0;
    s32 s1;
    s32 v0;
    s32 v1;

    s0 = *(s32 *)((s32)arg0 + 0x4C);
    s1 = *(s32 *)((s32)arg0 + 0x20);
    *(s32 *)((s32)arg0 + 0xC) = 0;
    *(s32 *)((s32)arg0 + 0x8) = 0;
    *(s32 *)((s32)arg0 + 0x4) = 0;
    func_80149374(s0, (s32)arg0 + 4);
    v0 = *(s32 *)(s0 + 0x20);
    *(func_800CB188_Blk16 *)(s1 + 0x34) = *(func_800CB188_Blk16 *)(v0 + 0x34);
    *(func_800CB188_Blk16 *)(s1 + 0x44) = *(func_800CB188_Blk16 *)(v0 + 0x44);
    v1 = *(s32 *)(s1 + 4) & 0x7FFFFFFF;
    *(s32 *)(s1 + 4) = v1;
    if (D_800B99DA & 1) {
        *(s32 *)(s1 + 4) = v1 | 0x80000000;
    }
}


extern void func_80162CCC(void);
void func_800CB24C(void) {
    func_80162CCC();
}

