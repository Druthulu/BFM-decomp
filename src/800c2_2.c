#include "common.h"

INCLUDE_ASM("asm/nonmatchings/800c2_2", func_80062388);

INCLUDE_ASM("asm/nonmatchings/800c2_2", func_80062394);

__asm__(
    ".text\n"
    ".align 2\n"
    ".globl func_800623A4\n"
    ".ent\tfunc_800623A4\n"
    "func_800623A4:\n"
    ".frame $sp,40,$31\n"
    ".mask 0x001F0000,-16\n"
    ".fmask 0,0\n"
    ".set\tnoreorder\n"
    "addiu $sp, $sp, -40\n"
    "sw $s0, 16($sp)\n"
    "addu $s0, $a0, $zero\n"
    "sw $s1, 20($sp)\n"
    "addu $s1, $a1, $zero\n"
    "sw $s2, 24($sp)\n"
    "addu $s2, $a2, $zero\n"
    "sw $s3, 28($sp)\n"
    "sw $ra, 32($sp)\n"
    "jal func_80062768\n"
    "addu $s3, $a3, $zero\n"
    "jal func_8005CF08\n"
    "nop\n"
    "jal func_800626F0\n"
    "nop\n"
    "jal func_8005CF18\n"
    "nop\n"
    "jal ChangeClearPAD\n"
    "addu $a0, $zero, $zero\n"
    "jal func_8006252C\n"
    "nop\n"
    "addu $a0, $s0, $zero\n"
    "addu $a1, $s1, $zero\n"
    "addu $a2, $s2, $zero\n"
    "jal PAD_init2\n"
    "addu $a3, $s3, $zero\n"
    "addiu $v0, $zero, 1\n"
    "lui $at, %hi(D_80072A24)\n"
    "sw $v0, %lo(D_80072A24)($at)\n"
    "lw $ra, 32($sp)\n"
    "lw $s3, 28($sp)\n"
    "lw $s2, 24($sp)\n"
    "lw $s1, 20($sp)\n"
    "lw $s0, 16($sp)\n"
    "jr $ra\n"
    "addiu $sp, $sp, 40\n"
    ".set\treorder\n"
    ".end\tfunc_800623A4\n"
);


__asm__(
    ".text\n"
    ".align 2\n"
    ".globl func_80062434\n"
    ".ent\tfunc_80062434\n"
    "func_80062434:\n"
    ".frame $sp,40,$31\n"
    ".mask 0x001F0000,-16\n"
    ".fmask 0,0\n"
    ".set\tnoreorder\n"
    "addiu $sp, $sp, -40\n"
    "sw $s0, 16($sp)\n"
    "addu $s0, $a0, $zero\n"
    "sw $s1, 20($sp)\n"
    "addu $s1, $a1, $zero\n"
    "sw $s2, 24($sp)\n"
    "addu $s2, $a2, $zero\n"
    "sw $s3, 28($sp)\n"
    "sw $ra, 32($sp)\n"
    "jal func_80062768\n"
    "addu $s3, $a3, $zero\n"
    "jal func_8005CF08\n"
    "nop\n"
    "jal func_800626F0\n"
    "nop\n"
    "jal func_8005CF18\n"
    "nop\n"
    "jal ChangeClearPAD\n"
    "addu $a0, $zero, $zero\n"
    "jal func_8006252C\n"
    "nop\n"
    "addu $a0, $s0, $zero\n"
    "addu $a1, $s1, $zero\n"
    "addu $a2, $s2, $zero\n"
    "jal InitPAD2\n"
    "addu $a3, $s3, $zero\n"
    "addiu $v0, $zero, 1\n"
    "lui $at, %hi(D_80072A24)\n"
    "sw $v0, %lo(D_80072A24)($at)\n"
    "lw $ra, 32($sp)\n"
    "lw $s3, 28($sp)\n"
    "lw $s2, 24($sp)\n"
    "lw $s1, 20($sp)\n"
    "lw $s0, 16($sp)\n"
    "jr $ra\n"
    "addiu $sp, $sp, 40\n"
    ".set\treorder\n"
    ".end\tfunc_80062434\n"
);

INCLUDE_ASM("asm/nonmatchings/800c2_2", func_800624C4);

extern void func_800626DC(void);
extern void StopPAD2(void);
extern s32 func_800625A4(void);
extern s32 D_80072A24;

void func_800624F4(void)
{
    func_800626DC();
    StopPAD2();
    func_800625A4();
    D_80072A24 = 0;
}

__asm__(
    ".text\n"
    ".align\t2\n"
    ".globl\tfunc_8006252C\n"
    ".ent\tfunc_8006252C\n"
    "func_8006252C:\n"
    ".set\tnoreorder\n"
    "addiu\t$sp, $sp, -24\n"
    "sw\t$ra, 20($sp)\n"
    "jal\tfunc_8005CF08\n"
    "sw\t$s0, 16($sp)\n"
    "li\t$a0, 1\n"
    "lui\t$v1, %hi(D_80078D0C)\n"
    "addiu\t$v1, $v1, %lo(D_80078D0C)\n"
    "addiu\t$s0, $v1, -4\n"
    "lui\t$v0, %hi(func_800625DC)\n"
    "addiu\t$v0, $v0, %lo(func_800625DC)\n"
    "sw\t$v0, 0($v1)\n"
    "lui\t$v0, %hi(func_80062644)\n"
    "addiu\t$v0, $v0, %lo(func_80062644)\n"
    "sw\t$v0, 4($v1)\n"
    "lui\t$at, %hi(D_80078D08)\n"
    "sw\t$zero, %lo(D_80078D08)($at)\n"
    "lui\t$at, %hi(D_80078D14)\n"
    "sw\t$zero, %lo(D_80078D14)($at)\n"
    "jal\tSysDeqIntRP\n"
    "addu\t$a1, $s0, $zero\n"
    "li\t$a0, 1\n"
    "jal\tSysEnqIntRP\n"
    "addu\t$a1, $s0, $zero\n"
    "jal\tfunc_8005CF18\n"
    "nop\n"
    "li\t$v0, 1\n"
    "lw\t$ra, 20($sp)\n"
    "lw\t$s0, 16($sp)\n"
    "jr\t$ra\n"
    "addiu\t$sp, $sp, 24\n"
    ".set\treorder\n"
    ".end\tfunc_8006252C\n"
);

extern void func_8005CF08(void);
extern void func_8005CF18(void);
extern s32 SysDeqIntRP(s32 priority, void *intr);
extern unsigned char D_80078D08[];

s32 func_800625A4(void) {
    func_8005CF08();
    SysDeqIntRP(1, &D_80078D08);
    func_8005CF18();
    return 1;
}

extern u8 *D_80072A28;

s32 func_800625DC(void) {
    volatile s32 i;
    s32 frame_pad[2];

    (void)&frame_pad;
    *(u16 *)(D_80072A28 + 10) = 0;
    i = 10;
    if (--i != -1) {
        do {
        } while (--i != -1);
    }
    return 0;
}

s32 func_80062644(void) {
    extern s32 *D_80072A2C;
    s32 *p = D_80072A2C;

    if ((p[1] & 1) == 0) {
        return 0;
    }
    if ((p[0] & 1) != 0) {
        return 1;
    }
    if ((p[0] & 1) != 0) {
        return 1;
    }
    return 0;
}

__asm__(".word 0x00000000\n");
