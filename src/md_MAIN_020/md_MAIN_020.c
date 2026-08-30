#include "common.h"

extern s32 func_800183E0(s32 *a0);
void func_800CAE0C(void) {

    extern s32 D_800CB294;
    func_800183E0(&D_800CB294);
}




void func_800CAE34(void *a0) {

    extern void (*D_800CB260[])(void);
    *(u32 *)((s32)a0 + 0x44) |= 8;
    D_800CB260[*(u8 *)((s32)a0 + 0x197)]();
}


extern void func_800CAEB0();
void func_800CAE78(void *a0) {
    func_800CAEB0(a0);
    *(u8 *)((s32)a0 + 0x197) += 1;
}


extern void func_801599A4(void *a0);
extern s32 func_80165910();
extern void func_801655E4(s32 a0);
extern void func_8016629C(void *a0);
void func_800CAEB0(void *a0) {
    func_801599A4(a0);
    func_800CAF6C(a0);
    if (func_80165910(a0) == 0) {
        func_801655E4((s32)a0);
    }
    func_8016629C(a0);
    *(u8 *)((s32)a0 + 0x197) += 1;
}


void func_800CAF10(void) {
}

extern void func_80154A74(s32 a0, s32 a1);

void func_800CAF18(s32 a0) {
    func_80154A74(a0, 0x11);
}


extern void func_80147078(s32 *a0, s16 a1);
extern void func_800CAFFC();
void func_800CAF38(s32 *a0) {
    func_80147078(a0, 31);
    ((void (*)(void *))func_800CAFFC)(a0);
}


extern void func_80147078(s32 *a0, s16 a1);
extern void func_800CAFA0(void *a0);
void func_800CAF6C(s32 *a0) {
    func_80147078(a0, 31);
    func_800CAFA0(a0);
}




void func_800CAFA0(void *a0) {

    extern void (*D_800CB26C[])(void);
    D_800CB26C[*(u16 *)((s32)a0 + 0x2)]();
}


extern void func_800CAFFC();
void func_800CAFDC(void) {
    func_800CAFFC();
}


    extern void func_801474EC(void *a0);
    extern s32 func_800CB17C(struct S *a0);
    extern void func_80146CA0(void *a0);
    void func_800CAFFC(void *a0) {
        func_801474EC(a0);
        func_800CB17C((struct S *)a0);
        func_80146CA0(a0);
    }


void func_800CB034(void *a0) {
    extern u16 func_80148800(s32 *a0);
    extern s32 func_80165A20(s32 a0);
    extern void func_801599A4(void *a0);
    extern void func_80159B3C(void *a0);
    extern void func_80154274(s32 *a0, s32 a1);
    extern s32 func_80148AFC(void *a0);
    extern void func_80146DE8(s32 *a0, s32 a1, s32 a2, s32 a3);
    extern void func_80147A84(s32 a0);
    extern void func_801473EC(s32 *a0);
    extern void func_80148038(s32 a0, s32 a1);
    extern void func_80147460(s32 a0);
    extern void func_8016151C(void *a0);
    extern s32 func_801615C4(void *a0, s32 a1);
    extern s32 D_80078EC8;
    extern s32 D_800CB234[];

    s32 s0 = (s32)a0;

    if ((func_80148800((s32 *)a0) & 0x20) || D_80078EC8 == 0) {
        func_80165A20(s0);
        func_801599A4((void *)s0);
        func_80159B3C((void *)s0);
        return;
    }
    if (*(u16 *)((s32)s0 + 0xB8) & 0x8000) {
        func_80154274((s32 *)s0, (s32)&D_800CB234);
    }
    if (func_80148AFC((void *)s0) & 0xFF) {
        func_80146DE8((s32 *)s0, 0, 0, -0x80000);
    } else {
        func_80146DE8((s32 *)s0, 0, 0, 0);
    }
    func_80147A84(s0);
    func_801473EC((s32 *)s0);
    func_80148038(s0, 0x30000);
    func_80147460(s0);
    if (((s32 (*)(void *))func_8016151C)((void *)s0) == 0) {
        return;
    }
    *(u16 *)((s32)s0 + 0xA) = *(u16 *)((s32)s0 + 0xA) + 8;
    func_801615C4((void *)s0, 0);
    func_800CB17C((struct S *)s0);
}


extern void func_8012A2F4(s32 a0);
extern void func_80154A74(s32 a0, s32 a1);
void func_800CB148(s32 a0) {
    func_8012A2F4(a0);
    func_80154A74(a0, 0x11);
}


__asm__(".text\n.align 2\n.globl func_800CB17C\n.ent\tfunc_800CB17C\n"
        "func_800CB17C:\n.frame $sp,24,$31\n.mask 0x80010000,-8\n.fmask 0,0\n"
        ".set\tnoreorder\n"
        "addiu $sp,$sp,-24\n"
        "sw $s0,16($sp)\n"
        "addu $s0,$a0,$zero\n"
        "sw $ra,20($sp)\n"
        "lh $a0,10($s0)\n"
        "jal func_8012A304\n"
        "addiu $a1,$zero,128\n"
        "addu $a0,$s0,$zero\n"
        "jal func_801477E8\n"
        "lui $a1,65512\n"
        "lui $a1,%hi(D_800CB1F4)\n"
        "addiu $a1,$a1,%lo(D_800CB1F4)\n"
        "jal func_80154274\n"
        "addu $a0,$s0,$zero\n"
        "jal func_80147324\n"
        "addiu $a0,$zero,1146\n"
        "addu $a0,$s0,$zero\n"
        "jal func_8014C010\n"
        "addiu $a1,$zero,2\n"
        "jal func_801483E8\n"
        "addu $a0,$s0,$zero\n"
        "lui $a0,%hi(D_80062BD0)\n"
        "addiu $a0,$a0,%lo(D_80062BD0)\n"
        "jal func_80019064\n"
        "nop\n"
        "lw $ra,20($sp)\n"
        "lw $s0,16($sp)\n"
        "addiu $sp,$sp,24\n"
        "jr $ra\n"
        "nop\n"
        ".set\treorder\n"
        ".end\tfunc_800CB17C\n");

