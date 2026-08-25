#include "common.h"

INCLUDE_ASM("asm/md_MAIN_026/nonmatchings/md_MAIN_026", func_800CAE0C);



void func_800CAE44(void *a0) {

    extern void (*D_800CBB10[])(void);
    *(u32 *)((s32)a0 + 0x44) |= 8;
    D_800CBB10[*(u8 *)((s32)a0 + 0x197)]();
}


extern void func_800CAEC0();
void func_800CAE88(void *a0) {
    func_800CAEC0(a0);
    *(u8 *)((s32)a0 + 0x197) += 1;
}


INCLUDE_ASM("asm/md_MAIN_026/nonmatchings/md_MAIN_026", func_800CAEC0);

INCLUDE_ASM("asm/md_MAIN_026/nonmatchings/md_MAIN_026", func_800CAF10);

INCLUDE_ASM("asm/md_MAIN_026/nonmatchings/md_MAIN_026", func_800CAF68);

INCLUDE_ASM("asm/md_MAIN_026/nonmatchings/md_MAIN_026", func_800CB010);

extern void func_800CB108(void);
void func_800CB078(void) {
    func_800CB108();
}


INCLUDE_ASM("asm/md_MAIN_026/nonmatchings/md_MAIN_026", func_800CB098);

INCLUDE_ASM("asm/md_MAIN_026/nonmatchings/md_MAIN_026", func_800CB108);


extern void func_800CB5D4(void);

void func_800CB134(void *arg0) {

    extern u8 D_80078EC1;
    extern void (*D_800CBB24[])(void);
    if (D_80078EC1 == 0x16) {
        u16 v0 = *(u16 *)((u8 *)arg0 + 2);
        D_800CBB24[v0]();
    } else {
        func_800CB5D4();
    }
}


INCLUDE_ASM("asm/md_MAIN_026/nonmatchings/md_MAIN_026", func_800CB190);

#include "common.h"

extern s32 func_80146E98();
extern void func_80146578(void);
extern void func_8001CD9C(int a0, void *a1);
extern void func_800233CC(void *, unsigned short);
extern void func_80146CA0(void *a0);
extern void func_80162CCC(void);

extern u8 D_800CBBD8;
extern u8 D_800CBBD9;
extern u8 D_800CBBDA;
extern u8 D_800CBBDB;
extern u8 D_800CBBDC;
extern u8 D_800CBBDD;
extern u8 D_800CBBDE;
extern u8 D_800CBBDF;

void func_800CB278(s32 param_1)
{
    register s32 p1    __asm__("$17");  /* $s1 */
    register s32 iVar1 __asm__("$16");  /* $s0 */
    register s32 base  __asm__("$18");  /* $s2 */
    register s32 ivar3 __asm__("$19");  /* $s3 */

    p1 = param_1;
    base = (s32)&D_800CBBD8;
    if (((s32 (*)(void))func_80146E98)() == 0) {
        return;
    }
    *(s32 *)(p1 + 0x20) = (iVar1 = ((s32 (*)(void))func_80146578)());
    ivar3 = iVar1;
    if (iVar1 != 0) {
        func_8001CD9C(iVar1, (void *)base);
        func_800233CC((void *)base, 0x80);
        *(s16 *)(iVar1 + 0x18) = 0;
        *(s16 *)(iVar1 + 0x1a) = 0;
        *(s16 *)(p1 + 0x60) = 0;
        D_800CBBDB = 0;
        D_800CBBDF = 0;
        if (*(s32 *)(p1 + 0x50) == 0) {
            *(u8 *)base = 0xFF;
            D_800CBBD9 = 0xFF;
            D_800CBBDA = 0xFF;
            D_800CBBDC = 0;
            D_800CBBDD = 0;
            D_800CBBDE = 0xFF;
            *(u32 *)(iVar1 + 4) = *(u32 *)(iVar1 + 4) | 0x50000000;
        } else {
            *(u8 *)base = 0;
            D_800CBBDA = 0xC0;
            D_800CBBD9 = 0;
            D_800CBBDC = 0;
            D_800CBBDD = 0;
            D_800CBBDE = 0x80;
            *(u32 *)(ivar3 + 4) = *(u32 *)(ivar3 + 4) | 0x50000000;
        }
        func_80146CA0((void *)p1);
    } else {
        ((void (*)(s32))func_80162CCC)(p1);
    }
}


INCLUDE_ASM("asm/md_MAIN_026/nonmatchings/md_MAIN_026", func_800CB3C0);

INCLUDE_ASM("asm/md_MAIN_026/nonmatchings/md_MAIN_026", func_800CB470);

extern void func_80162CCC(void);
void func_800CB5D4(void) {
    func_80162CCC();
}


INCLUDE_ASM("asm/md_MAIN_026/nonmatchings/md_MAIN_026", func_800CB5F4);


extern void func_800CB8A4(void);

void func_800CB62C(void *arg0) {

    extern u8 D_80078EC1;
    extern void (*D_800CBB48[])(void);
    if (D_80078EC1 == 0x16) {
        u16 v0 = *(u16 *)((u8 *)arg0 + 2);
        D_800CBB48[v0]();
    } else {
        func_800CB8A4();
    }
}


INCLUDE_ASM("asm/md_MAIN_026/nonmatchings/md_MAIN_026", func_800CB688);

INCLUDE_ASM("asm/md_MAIN_026/nonmatchings/md_MAIN_026", func_800CB6E8);

INCLUDE_ASM("asm/md_MAIN_026/nonmatchings/md_MAIN_026", func_800CB77C);

extern void func_80162CCC(void);
void func_800CB8A4(void) {
    func_80162CCC();
}


INCLUDE_ASM("asm/md_MAIN_026/nonmatchings/md_MAIN_026", func_800CB8C4);

INCLUDE_ASM("asm/md_MAIN_026/nonmatchings/md_MAIN_026", func_800CB900);
