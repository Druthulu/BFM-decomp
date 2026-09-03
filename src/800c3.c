#include "common.h"

__asm__(".text\n.align 2\n.globl InitHeap\n.ent\tInitHeap\n"
        "InitHeap:\n.frame $sp,0,$31\n"
        ".set\tnoreorder\n"
        "addiu $t2, $zero, 0xA0\n"
        "jr $t2\n"
        "addiu $t1, $zero, 0x39\n"
        "nop\n"
        ".set\treorder\n.end\tInitHeap\n");


__asm__(".text\n.align 2\n.globl FlushCache\n.ent\tFlushCache\n"
        "FlushCache:\n.frame $sp,0,$31\n"
        ".set\tnoreorder\n"
        "addiu $t2, $zero, 160\n"
        "jr $t2\n"
        "addiu $t1, $zero, 68\n"
        "nop\n"
        ".set\treorder\n.end\tFlushCache\n");


__asm__(".text\n.align 2\n.globl func_8005CE38\n.ent\tfunc_8005CE38\n"
        "func_8005CE38:\n.frame $sp,0,$31\n"
        ".set\tnoreorder\n"
        "addiu $t2, $zero, 0xA0\n"
        "jr $t2\n"
        "addiu $t1, $zero, 0x49\n"
        "nop\n"
        ".word 0x21007350\n"
        ".word 0x004236AD\n"
        ".set\treorder\n.end\tfunc_8005CE38\n");

__asm__(".text\n.align 2\n.globl _96_remove\n.ent\t_96_remove\n"
        "_96_remove:\n.frame $sp,0,$31\n"
        ".set\tnoreorder\n"
        "addiu $t2, $zero, 160\n"
        "jr $t2\n"
        "addiu $t1, $zero, 114\n"
        "nop\n"
        "nop\n"
        "nop\n"
        ".set\treorder\n.end\t_96_remove\n");

asm(
    ".section .text\n"
    ".globl DeliverEvent\n"
    ".set noreorder\n"
    "DeliverEvent:\n"
    "addiu $t2, $zero, 176\n"
    "jr $t2\n"
    "addiu $t1, $zero, 7\n"
    "nop\n"
    ".set reorder\n"
);

__asm__(".text\n.align 2\n.globl OpenEvent\n.ent\tOpenEvent\n"
        "OpenEvent:\n.frame $sp,0,$31\n"
        ".set\tnoreorder\n"
        "addiu $t2, $zero, 0xB0\n"
        "jr $t2\n"
        "addiu $t1, $zero, 0x8\n"
        "nop\n"
        ".set\treorder\n.end\tOpenEvent\n");

__asm__(".text\n.align 2\n.globl CloseEvent\n.ent\tCloseEvent\n"
        "CloseEvent:\n.frame $sp,0,$31\n"
        ".set\tnoreorder\n"
        "addiu $t2, $zero, 0xB0\n"
        "jr $t2\n"
        "addiu $t1, $zero, 0x9\n"
        "nop\n"
        ".set\treorder\n.end\tCloseEvent\n");

__asm__(
    ".text\n"
    ".align 2\n"
    ".globl WaitEvent\n"
    ".ent\tWaitEvent\n"
    "WaitEvent:\n"
    ".frame $sp, 0, $31\n"
    ".mask 0x00000000, 0\n"
    ".fmask 0x00000000, 0\n"
    ".set\tnoreorder\n"
    "addiu $t2, $0, 176\n"
    "jr    $t2\n"
    "addiu $t1, $0, 10\n"
    ".set\treorder\n"
    ".end\tWaitEvent\n"
    "nop\n"
);

__asm__(".text\n.align 2\n.globl TestEvent\n.ent\tTestEvent\n"
        "TestEvent:\n.frame $sp,0,$31\n"
        ".set\tnoreorder\n"
        "addiu $t2, $zero, 0xB0\n"
        "jr $t2\n"
        "addiu $t1, $zero, 0xB\n"
        "nop\n"
        ".set\treorder\n.end\tTestEvent\n");

__asm__(".text\n.align 2\n.globl EnableEvent\n.ent\tEnableEvent\n"
        "EnableEvent:\n.frame $sp,0,$31\n"
        ".set\tnoreorder\n"
        "addiu $t2, $zero, 176\n"
        "jr $t2\n"
        "addiu $t1, $zero, 12\n"
        "nop\n"
        ".set\treorder\n.end\tEnableEvent\n");

__asm__(
    ".text\n"
    ".align 2\n"
    ".globl DisableEvent\n"
    ".ent\tDisableEvent\n"
    "DisableEvent:\n"
    ".frame $sp,0,$31\n"
    ".set\tnoreorder\n"
    "addiu $10, $0, 176\n"
    "jr $10\n"
    "addiu $9, $0, 13\n"
    "nop\n"
    ".set\treorder\n"
    ".end\tDisableEvent\n"
);


__asm__(
    ".text\n"
    ".align 2\n"
    ".globl ReturnFromException\n"
    ".ent\tReturnFromException\n"
    "ReturnFromException:\n"
    ".frame $sp, 0, $31\n"
    ".mask 0x00000000, 0\n"
    ".fmask 0x00000000, 0\n"
    ".set\tnoreorder\n"
    "addiu $t2, $zero, 176\n"
    "jr    $t2\n"
    "addiu $t1, $zero, 23\n"
    ".set\treorder\n"
    ".end\tReturnFromException\n"
    "nop\n"
);

/* §295 kernel-trap trampoline: A/B/C dispatch vector in $t2, syscall # in the jr delay slot;
 * unreachable from C (§179-C) -> file-scope verbatim asm (§265 form 1). Pad nop is load-bearing (stride 0x10). */
__asm__(".text\n.align 2\n.globl ResetEntryInt\n.ent\tResetEntryInt\n"
        "ResetEntryInt:\n.frame $sp,0,$31\n.mask 0x00000000,0\n.fmask 0x00000000,0\n"
        ".set\tnoreorder\n"
        "addiu $t2, $zero, 176\n"
        "jr $t2\n"
        "addiu $t1, $zero, 24\n"
        "nop\n"
        ".set\treorder\n.end\tResetEntryInt\n");

/* §295 kernel-trap trampoline: A/B/C dispatch vector in $t2, syscall # in the jr delay slot;
 * unreachable from C (§179-C) -> file-scope verbatim asm (§265 form 1). Pad nop is load-bearing (stride 0x10). */
__asm__(".text\n.align 2\n.globl HookEntryInt\n.ent\tHookEntryInt\n"
        "HookEntryInt:\n.frame $sp,0,$31\n.mask 0x00000000,0\n.fmask 0x00000000,0\n"
        ".set\tnoreorder\n"
        "addiu $t2, $zero, 176\n"
        "jr $t2\n"
        "addiu $t1, $zero, 25\n"
        "nop\n"
        ".set\treorder\n.end\tHookEntryInt\n");

void func_8005CF08(void) {
    __asm__ volatile(
        "addiu $a0, $zero, 0x1\n\t"
        "syscall"
    );
}

void func_8005CF18() {
    __asm__ __volatile__(
        ".set\tnoreorder\n"
        "addiu $a0, $zero, 2\n"
        "syscall 0\n"
        ".set\treorder\n"
    );
}

/* §295 kernel-trap trampoline: A/B/C dispatch vector in $t2, syscall # in the jr delay slot;
 * unreachable from C (§179-C) -> file-scope verbatim asm (§265 form 1). Pad nop is load-bearing (stride 0x10). */
__asm__(".text\n.align 2\n.globl read\n.ent\tread\n"
        "read:\n.frame $sp,0,$31\n.mask 0x00000000,0\n.fmask 0x00000000,0\n"
        ".set\tnoreorder\n"
        "addiu $t2, $zero, 176\n"
        "jr $t2\n"
        "addiu $t1, $zero, 52\n"
        "nop\n"
        ".set\treorder\n.end\tread\n");

__asm__(".text\n.align 2\n.globl write\n.ent\twrite\n"
        "write:\n.frame $sp,0,$31\n"
        ".set\tnoreorder\n"
        "addiu $t2, $zero, 0xB0\n"
        "jr $t2\n"
        "addiu $t1, $zero, 0x35\n"
        "nop\n"
        ".set\treorder\n.end\twrite\n");

__asm__(".text\n.align 2\n.globl ChangeClearPAD\n.ent\tChangeClearPAD\n"
        "ChangeClearPAD:\n.frame $sp,0,$31\n"
        ".set\tnoreorder\n"
        "addiu $10, $0, 0xB0\n"
        "jr $10\n"
        "addiu $9, $0, 0x5B\n"
        ".set\treorder\n.end\tChangeClearPAD\n"
        "nop\n");

__asm__(".text\n.align 2\n.globl ChangeClearRCnt\n.ent\tChangeClearRCnt\n"
        "ChangeClearRCnt:\n.frame $sp,0,$31\n"
        ".set\tnoreorder\n"
        "addiu $t2, $zero, 0xC0\n"
        "jr $t2\n"
        "addiu $t1, $zero, 0xA\n"
        "nop\n"
        ".set\treorder\n.end\tChangeClearRCnt\n");


extern u32 D_80072938;

s32 SetRCnt(s32 a0, s16 a1, s32 a2) {
    register s32 t0 __asm__("$8");
    register s32 a3 __asm__("$7");
    register s32 a0p __asm__("$4");
    u32 v1;

    t0 = a0 & 0xFFFF;

    if (t0 >= 3) {
        return 0;
    }

    a3 = 0x48;
    v1 = (t0 << 4) + *(u32*)&D_80072938;

    *(u16*)(v1 + 4) = 0;
    {
        s32 lt2 = t0 < 2U;
        *(u16*)(v1 + 8) = a1;
        __asm__ __volatile__("" : : "r"(lt2));
        if (lt2) {
            if (a2 & 0x10) {
                a3 = 0x49;
            }
            if (!(a2 & 0x1)) {
                a3 |= 0x100;
            }
        } else if (t0 == 2U) {
            if (!(a2 & 0x1)) {
                a3 = 0x248;
            }
        }
    }

    if (a2 & 0x1000) {
        a3 |= 0x10;
    }

    {
        register s32 ret __asm__("$2");
        ret = 1;
        __asm__ __volatile__("" : : "r"(ret));
        a0p = *(s32*)&D_80072938;
        v1 = t0 << 4;
        v1 = v1 + (u32)a0p;
        *(u16*)(v1 + 4) = a3;
        return ret;
    }
}

extern u32 D_80072938;

s32 GetRCnt(s32 spec) {
    register s32 v1 __asm__("$3");
    s32 ret;

    v1 = spec & 0xFFFF;
    if (v1 < 3) {
        v1 = (v1 << 4) + D_80072938;
        ret = *(u16 *) v1;
    } else {
        ret = 0;
    }
    return ret;
}

extern s32 D_80072934;
extern s32 D_8007293C[];

s32 StartRCnt(s32 spec) {
    s32 t;

    t = spec & 0xFFFF;
    *(s32 *)(D_80072934 + 4) |= D_8007293C[t];
    return t < 3;
}

__asm__(".text\n.align 2\n.globl StopRCnt\n.ent\tStopRCnt\n"
        "StopRCnt:\n.frame $sp,0,$31\n"
        ".set\tnoreorder\n"
        "andi $a0, $a0, 65535\n"
        "sll $a0, $a0, 2\n"
        "lui $a1, %hi(D_80072934)\n"
        "lw $a1, %lo(D_80072934)($a1)\n"
        "lui $v0, %hi(D_8007293C)\n"
        "addu $v0, $v0, $a0\n"
        "lw $v0, %lo(D_8007293C)($v0)\n"
        "lw $v1, 4($a1)\n"
        "nor $v0, $zero, $v0\n"
        "and $v1, $v1, $v0\n"
        "addiu $v0, $zero, 1\n"
        "jr $ra\n"
        "sw $v1, 4($a1)\n"
        ".set\treorder\n.end\tStopRCnt\n");

extern u32 D_80072938;

s32 ResetRCnt(s32 spec) {
    s32 v1 = spec & 0xFFFF;
    if (v1 >= 3) {
        return 0;
    }
    *(u16 *)((v1 << 4) + *(u32 *)&D_80072938) = 0;
    return 1;
}

__asm__(".word 0x00000000");

extern s32 func_8005D8A0(void);

void func_8005D0D8(void) {
    func_8005D8A0();
}

extern void func_8005D8B4(void);

void func_8005D0F8(void) {
    func_8005D8B4();
}

extern void func_8005D980(void);

void func_8005D118(void) {
    func_8005D980();
}

extern s32 D_800729A8;
extern s32 D_80072990;

s32 func_8005D138(s32 arg0) {
    if (D_800729A8 != 0) {
        return *(u8 *)(D_80072990 + (arg0 >> 4) * 0xF0 + 0xE8) == 8;
    }
    return 0;
}


extern void* (*D_80072970)(void);

s32 func_8005D184(s32 arg0) {
    void* v0;
    register s32 v1 __asm__("$3");

    v0 = D_80072970();

    if ((*(u32*)((u8*)v0 + 0x34) & 0xFFFF0000) != 0) {
        goto do_switch;
    }
    if ((u32)v0 == *(u32*)((u8*)v0 + 0x10)) {
        goto check30;
    }
    if (*(u8*)((u8*)v0 + 0x38) != 0) {
        goto do_switch;
    }
check30:
    if (*(u8*)*(u32*)((u8*)v0 + 0x30) == 0) {
        goto return_byte;
    }

do_switch:
    v1 = *(u8*)((u8*)v0 + 0x49);

    if (v1 == 3) {
        goto return_one;
    }
    if (v1 < 4) {
        if (v1 == 2) {
            goto return_one;
        }
        goto return_byte;
    }
    if (v1 == 6) {
        goto return_four;
    }
    goto return_byte;

return_one:
    return 1;

return_four:
    return 4;

return_byte:
    return *(u8*)((u8*)v0 + 0x49);
}

extern void* (*D_80072970)(void);

s32 func_8005D244(s32 arg0, s32 arg1, s32 arg2) {
    void *p;

    p = (*D_80072970)();
    switch (arg1) {
    case 1:
        return *(u8 *)((char *)p + 0xE8);
    case 2:
        return *(u16 *)((char *)p + 0xE6);
    case 3:
        return *(u8 *)((char *)p + 0xE4);
    case 4:
        if (arg2 < 0) {
            return *(u8 *)((char *)p + 0xE3);
        }
        if (arg2 < *(u8 *)((char *)p + 0xE3)) {
            return *(u16 *)(*(u32 *)p + arg2 * 2);
        }
        return 0;
    case 100:
        return *(u32 *)((char *)p + 0x4C);
    default:
        return 0;
    }
}


__asm__(
    ".set\tnoreorder\n"
    ".set noreorder\n"
    "\t.globl\tfunc_8005D33C\n"
    "func_8005D33C:\n"
    "lui $v0, %hi(D_80072970)\n"
    "lw $v0, %lo(D_80072970)($v0)\n"
    "addiu $sp, $sp, -32\n"
    "sw $s0, 16($sp)\n"
    "addu $s0, $a1, $zero\n"
    "sw $s1, 20($sp)\n"
    "sw $ra, 24($sp)\n"
    "jalr $v0\n"
    "addu $s1, $a2, $zero\n"
    "bgez $s0, 1f\n"
    "addu $v1, $v0, $zero\n"
    "lbu $v0, 233($v1)\n"
    "j 4f\n"
    "nop\n"
    "1:\n"
    "lbu $v0, 233($v1)\n"
    "nop\n"
    "slt $v0, $s0, $v0\n"
    "beqz $v0, 3f\n"
    "sll $v0, $s0, 2\n"
    "lw $v1, 4($v1)\n"
    "addu $v0, $v0, $s0\n"
    "addiu $a2, $s1, -1\n"
    "addu $v1, $v1, $v0\n"
    "sltiu $v0, $a2, 5\n"
    "beqz $v0, 3f\n"
    "sll $v0, $a2, 2\n"
    "lui $at, %hi(jtbl_800744A0)\n"
    "addu $at, $at, $v0\n"
    "lw $v0, %lo(jtbl_800744A0)($at)\n"
    "nop\n"
    "jr $v0\n"
    "nop\n"
    "lbu $v0, 0($v1)\n"
    "j 4f\n"
    "nop\n"
    "lbu $v0, 1($v1)\n"
    "j 4f\n"
    "nop\n"
    "lbu $v0, 2($v1)\n"
    "j 4f\n"
    "nop\n"
    "lbu $v0, 3($v1)\n"
    "j 4f\n"
    "nop\n"
    "lbu $v0, 4($v1)\n"
    "j 4f\n"
    "nop\n"
    "3:\n"
    "addu $v0, $zero, $zero\n"
    "4:\n"
    "lw $ra, 24($sp)\n"
    "lw $s1, 20($sp)\n"
    "lw $s0, 16($sp)\n"
    "jr $ra\n"
    "addiu $sp, $sp, 32\n"
    ".set reorder\n"
);

extern void* (*D_80072970)(void);

__asm__(
    "\t.set\tnoreorder\n"
    ".set noreorder\n"
    "\t.globl\tfunc_8005D410\n"
    "func_8005D410:\n"
    "lui $v0, %hi(D_80072970)\n"
    "lw $v0, %lo(D_80072970)($v0)\n"
    "addiu $sp, $sp, -32\n"
    "sw $s0, 16($sp)\n"
    "addu $s0, $a1, $zero\n"
    "sw $s1, 20($sp)\n"
    "sw $ra, 24($sp)\n"
    "jalr $v0\n"
    "addu $s1, $a2, $zero\n"
    "bgez $s0, 1f\n"
    "addu $v1, $v0, $zero\n"
    "lbu $v0, 234($v1)\n"
    "j 4f\n"
    "nop\n"
    "1:\n"
    "lbu $v0, 234($v1)\n"
    "nop\n"
    "slt $v0, $s0, $v0\n"
    "beq $v0, $zero, 3f\n"
    "sll $v0, $s0, 3\n"
    "lw $v1, 8($v1)\n"
    "bgez $s1, 2f\n"
    "addu $v1, $v1, $v0\n"
    "lbu $v0, 0($v1)\n"
    "j 4f\n"
    "nop\n"
    "2:\n"
    "lbu $v0, 0($v1)\n"
    "nop\n"
    "slt $v0, $s1, $v0\n"
    "beq $v0, $zero, 4f\n"
    "addu $v0, $zero, $zero\n"
    "lw $v0, 4($v1)\n"
    "nop\n"
    "addu $v0, $v0, $s1\n"
    "lbu $v0, 0($v0)\n"
    "j 4f\n"
    "nop\n"
    "3:\n"
    "addu $v0, $zero, $zero\n"
    "4:\n"
    "lw $ra, 24($sp)\n"
    "lw $s1, 20($sp)\n"
    "lw $s0, 16($sp)\n"
    "jr $ra\n"
    "addiu $sp, $sp, 32\n"
    ".set reorder\n"
);

__asm__(
    "\t.set\tnoreorder\n"
    ".set noreorder\n"
    "\t.globl\tfunc_8005D4B8\n"
    "func_8005D4B8:\n"
    "lui $v0, %hi(D_80072970)\n"
    "lw $v0, %lo(D_80072970)($v0)\n"
    "addiu $sp, $sp, -24\n"
    "sw $s0, 16($sp)\n"
    "sw $ra, 20($sp)\n"
    "jalr $v0\n"
    "addu $s0, $a1, $zero\n"
    "addu $a0, $v0, $zero\n"
    "jal func_8005E79C\n"
    "addu $a1, $s0, $zero\n"
    "lw $ra, 20($sp)\n"
    "lw $s0, 16($sp)\n"
    "jr $ra\n"
    "addiu $sp, $sp, 24\n"
    ".set reorder\n"
);

__asm__(
    "\t.set\tnoreorder\n"
    ".set noreorder\n"
    "\t.globl\tfunc_8005D4F0\n"
    "func_8005D4F0:\n"
    "lui $v0, %hi(D_80072970)\n"
    "lw $v0, %lo(D_80072970)($v0)\n"
    "addiu $sp, $sp, -32\n"
    "sw $s0, 16($sp)\n"
    "addu $s0, $a1, $zero\n"
    "sw $s1, 20($sp)\n"
    "sw $ra, 24($sp)\n"
    "jalr $v0\n"
    "addu $s1, $a2, $zero\n"
    "addu $a0, $v0, $zero\n"
    "andi $a1, $s0, 255\n"
    "jal func_8005E8E8\n"
    "andi $a2, $s1, 255\n"
    "lw $ra, 24($sp)\n"
    "lw $s1, 20($sp)\n"
    "lw $s0, 16($sp)\n"
    "jr $ra\n"
    "addiu $sp, $sp, 32\n"
    ".set reorder\n"
);

__asm__(
    "\t.set\tnoreorder\n"
    ".set noreorder\n"
    "\t.globl\tfunc_8005D538\n"
    "func_8005D538:\n"
    "lui $v0, %hi(D_80072970)\n"
    "lw $v0, %lo(D_80072970)($v0)\n"
    "addiu $sp, $sp, -32\n"
    "sw $s0, 16($sp)\n"
    "addu $s0, $a1, $zero\n"
    "sw $s1, 20($sp)\n"
    "sw $ra, 24($sp)\n"
    "jalr $v0\n"
    "addu $s1, $a2, $zero\n"
    "addu $a0, $v0, $zero\n"
    "addu $a1, $s0, $zero\n"
    "jal func_8005E188\n"
    "addu $a2, $s1, $zero\n"
    "lw $ra, 24($sp)\n"
    "lw $s1, 20($sp)\n"
    "lw $s0, 16($sp)\n"
    "jr $ra\n"
    "addiu $sp, $sp, 32\n"
    "nop\n"
    "nop\n"
    ".set reorder\n"
);


__asm__(
    "    .set noat\n"
    "    .set noreorder\n"
    "    .section .text\n"
    "    .globl func_8005D588\n"
    "func_8005D588:\n"
    ".word 0x3C038007\n"
    ".word 0x8C6329B0\n"
    ".word 0x3C028007\n"
    ".word 0x8C4229AC\n"
    ".word 0x27BDFFE0\n"
    ".word 0xAFB00010\n"
    ".word 0x00808021\n"
    ".word 0xAFBF001C\n"
    ".word 0xAFB20018\n"
    ".word 0xAFB10014\n"
    ".word 0x00031840\n"
    ".word 0x2C420001\n"
    ".word 0x00628825\n"
    ".word 0x12300031\n"
    ".word 0x32020001\n"
    ".word 0x3C018007\n"
    ".word 0xAC202994\n"
    ".word 0x10400012\n"
    ".word 0x24020001\n"
    ".word 0x3C128008\n"
    ".word 0x26528998\n"
    ".word 0x8E420000\n"
    ".word 0x3C018007\n"
    ".word 0xAC2029AC\n"
    ".word 0x28420096\n"
    ".word 0x14400008\n"
    ".word 0x00000000\n"
    ".word 0x3C048007\n"
    ".word 0x8C842990\n"
    ".word 0x3C028007\n"
    ".word 0x8C422960\n"
    ".word 0x00000000\n"
    ".word 0x0040F809\n"
    ".word 0x00000000\n"
    ".word 0x08017588\n"
    ".word 0xAE400000\n"
    ".word 0x3C018007\n"
    ".word 0xAC2229AC\n"
    ".word 0x32020002\n"
    ".word 0x10400012\n"
    ".word 0x24030001\n"
    ".word 0x3C108008\n"
    ".word 0x2610899C\n"
    ".word 0x8E020000\n"
    ".word 0x3C018007\n"
    ".word 0xAC2329B0\n"
    ".word 0x28420096\n"
    ".word 0x14400008\n"
    ".word 0x00000000\n"
    ".word 0x3C048007\n"
    ".word 0x8C842990\n"
    ".word 0x3C028007\n"
    ".word 0x8C422960\n"
    ".word 0x00000000\n"
    ".word 0x0040F809\n"
    ".word 0x248400F0\n"
    ".word 0x0801759E\n"
    ".word 0xAE000000\n"
    ".word 0x3C018007\n"
    ".word 0xAC2029B0\n"
    ".word 0x24020001\n"
    ".word 0x3C018007\n"
    ".word 0xAC222994\n"
    ".word 0x02201021\n"
    ".word 0x8FBF001C\n"
    ".word 0x8FB20018\n"
    ".word 0x8FB10014\n"
    ".word 0x8FB00010\n"
    ".word 0x03E00008\n"
    ".word 0x27BD0020\n"
    "    .set reorder\n"
    "    .set at\n"
);

void func_8005D6A0(void) {
    extern s32 D_8007898C;
    extern void func_8005D734(void);
    extern void func_8005D6CC(void);
    s32 *base = (s32 *)&D_8007898C;
    __asm__ __volatile__("" : "=r"(base) : "0"(base));
    *(s32 *)((s32)base + 0x0) = (s32)func_8005D734;
    *(s32 *)((s32)base + 0x4) = (s32)func_8005D6CC;
    *(s32 *)((s32)base - 0x4) = 0;
    *(s32 *)((s32)base + 0x8) = 0;
}

extern s32 *D_800729BC;
extern void (*D_80072984)(void);

s32 func_8005D6CC(void) {
    s32 *ptr = D_800729BC;

    if ((*(s32 *)((s8 *)ptr + 4) & 1) == 0) {
        return 0;
    }
    if ((*ptr & 1) == 0) {
        return 0;
    }
    if (D_80072984 != NULL) {
        (*D_80072984)();
    }
    return 1;
}

/* func_8005D734 — cookbook §265 VERBATIM-ASM bank (file-scope form), generated by
 * tools/asm_verbatim.py from asm/nonmatchings/800c3/func_8005D734.s.
 * Byte-equivalent to the INCLUDE_ASM stub by construction; the function is NOT
 * decompiled (§265 ACCOUNTING). Immediates/offsets are decimal for maspsx (§383).
 */
__asm__(
    ".text\n"
    ".align\t2\n"
    ".globl\tfunc_8005D734\n"
    ".ent\tfunc_8005D734\n"
    "func_8005D734:\n"
    ".frame\t$sp,24,$31\n"
    ".mask\t0x80000000,-4\n"
    ".fmask\t0,0\n"
    ".set\tnoreorder\n"
    "addiu $sp,$sp,-24\n"
    "lui $v1,%hi(D_800729AC)\n"
    "lw $v1,%lo(D_800729AC)($v1)\n"
    "addiu $v0,$zero,1\n"
    "sw $ra,16($sp)\n"
    "lui $at,%hi(D_800729C4)\n"
    "beqz $v1,.L8005D774\n"
    " sw $v0,%lo(D_800729C4)($at)\n"
    "lui $a0,%hi(D_80078998)\n"
    "addiu $a0,$a0,%lo(D_80078998)\n"
    "lw $v1,0($a0)\n"
    "nop\n"
    "slti $v0,$v1,150\n"
    "beqz $v0,.L8005D774\n"
    " addiu $v0,$v1,1\n"
    "sw $v0,0($a0)\n"
    ".L8005D774:\n"
    "lui $v0,%hi(D_800729B0)\n"
    "lw $v0,%lo(D_800729B0)($v0)\n"
    "nop\n"
    "bnez $v0,.L8005D7A8\n"
    " nop\n"
    "lui $a0,%hi(D_8007899C)\n"
    "addiu $a0,$a0,%lo(D_8007899C)\n"
    "lw $v1,0($a0)\n"
    "nop\n"
    "slti $v0,$v1,150\n"
    "beqz $v0,.L8005D7A8\n"
    " addiu $v0,$v1,1\n"
    "sw $v0,0($a0)\n"
    ".L8005D7A8:\n"
    "lui $v0,%hi(D_80072994)\n"
    "lw $v0,%lo(D_80072994)($v0)\n"
    "nop\n"
    "beqz $v0,.L8005D890\n"
    " nop\n"
    "lui $v1,%hi(D_800729AC)\n"
    "lw $v1,%lo(D_800729AC)($v1)\n"
    "lui $v0,%hi(D_800729B0)\n"
    "lw $v0,%lo(D_800729B0)($v0)\n"
    "nop\n"
    "slt $v0,$v0,$v1\n"
    "bnez $v0,.L8005D890\n"
    " sll $a0,$v1,4\n"
    "subu $a0,$a0,$v1\n"
    "lui $v0,%hi(D_80072990)\n"
    "lw $v0,%lo(D_80072990)($v0)\n"
    "sll $a0,$a0,4\n"
    "lui $at,%hi(D_800729A0)\n"
    "sw $zero,%lo(D_800729A0)($at)\n"
    "lui $at,%hi(D_8007299C)\n"
    "sw $v1,%lo(D_8007299C)($at)\n"
    "jal func_8005D9C4\n"
    " addu $a0,$v0,$a0\n"
    "bnez $v0,.L8005D820\n"
    " nop\n"
    "lui $v0,%hi(D_8007295C)\n"
    "lw $v0,%lo(D_8007295C)($v0)\n"
    "nop\n"
    "jalr $v0\n"
    " ori $a0,$zero,65535\n"
    ".L8005D820:\n"
    "lui $v1,%hi(D_8007299C)\n"
    "lw $v1,%lo(D_8007299C)($v1)\n"
    "lui $v0,%hi(D_800729B0)\n"
    "lw $v0,%lo(D_800729B0)($v0)\n"
    "lui $at,%hi(D_800729A4)\n"
    "sw $zero,%lo(D_800729A4)($at)\n"
    "slt $v0,$v0,$v1\n"
    "bnez $v0,.L8005D880\n"
    " nop\n"
    ".L8005D844:\n"
    "sll $a0,$v1,4\n"
    "subu $a0,$a0,$v1\n"
    "lui $v0,%hi(D_80072990)\n"
    "lw $v0,%lo(D_80072990)($v0)\n"
    "sll $a0,$a0,4\n"
    "jal func_8005DBD8\n"
    " addu $a0,$v0,$a0\n"
    "lui $v1,%hi(D_8007299C)\n"
    "lw $v1,%lo(D_8007299C)($v1)\n"
    "lui $v0,%hi(D_800729B0)\n"
    "lw $v0,%lo(D_800729B0)($v0)\n"
    "nop\n"
    "slt $v0,$v0,$v1\n"
    "beqz $v0,.L8005D844\n"
    " nop\n"
    ".L8005D880:\n"
    "lui $v1,%hi(D_800729C0)\n"
    "lw $v1,%lo(D_800729C0)($v1)\n"
    "addiu $v0,$zero,136\n"
    "sh $v0,14($v1)\n"
    ".L8005D890:\n"
    "lw $ra,16($sp)\n"
    "addu $v0,$zero,$zero\n"
    "jr $ra\n"
    " addiu $sp,$sp,24\n"
    ".set\treorder\n"
    ".end\tfunc_8005D734\n"
);

extern s32 D_800729C4;

asm(
    ".section .text\n"
    ".set noreorder\n"
    "func_8005D8A0:\n"
    "lui $v0, %hi(D_800729C4)\n"
    "lw $v0, %lo(D_800729C4)($v0)\n"
    "lui $at, %hi(D_800729C4)\n"
    "jr $ra\n"
    "sw $zero, %lo(D_800729C4)($at)\n"
    ".set reorder\n");

s32 func_8005D8A0(void);


__asm__(
    ".globl func_8005D8B4\n"
    "func_8005D8B4:\n"
    "addiu $sp,$sp,-24\n"
    "sw $ra,20($sp)\n"
    "sw $s0,16($sp)\n"
    "lui $at,%hi(D_80072994)\n"
    ".reloc ., R_MIPS_26, func_8005CF08\n"
    ".word 0x0c000000\n"
    "sw $zero,%lo(D_80072994)($at)\n"
    "addiu $a0,$zero,2\n"
    "lui $s0,%hi(D_80078988)\n"
    "addiu $s0,$s0,%lo(D_80078988)\n"
    ".reloc ., R_MIPS_26, SysDeqIntRP\n"
    ".word 0x0c000000\n"
    "addu $a1,$s0,$zero\n"
    "addiu $a0,$zero,2\n"
    ".reloc ., R_MIPS_26, SysEnqIntRP\n"
    ".word 0x0c000000\n"
    "addu $a1,$s0,$zero\n"
    "addiu $a0,$zero,3\n"
    "lui $v1,%hi(D_800729BC)\n"
    "lw $v1,%lo(D_800729BC)($v1)\n"
    "addiu $v0,$zero,-2\n"
    "sw $v0,0($v1)\n"
    "lw $v0,4($v1)\n"
    "addu $a1,$zero,$zero\n"
    "ori $v0,$v0,1\n"
    ".reloc ., R_MIPS_26, ChangeClearRCnt\n"
    ".word 0x0c000000\n"
    "sw $v0,4($v1)\n"
    ".reloc ., R_MIPS_26, func_8005CF18\n"
    ".word 0x0c000000\n"
    "nop\n"
    "lui $a0,%hi(D_80072990)\n"
    "lw $a0,%lo(D_80072990)($a0)\n"
    "lui $v0,%hi(D_80072960)\n"
    "lw $v0,%lo(D_80072960)($v0)\n"
    "nop\n"
    ".word 0x0040f809\n"
    "nop\n"
    "lui $a0,%hi(D_80072990)\n"
    "lw $a0,%lo(D_80072990)($a0)\n"
    "lui $v0,%hi(D_80072960)\n"
    "lw $v0,%lo(D_80072960)($v0)\n"
    "nop\n"
    ".word 0x0040f809\n"
    "addiu $a0,$a0,240\n"
    "lui $v0,%hi(D_80078998)\n"
    "addiu $v0,$v0,%lo(D_80078998)\n"
    "sw $zero,4($v0)\n"
    "sw $zero,0($v0)\n"
    "addiu $v0,$zero,1\n"
    "lui $at,%hi(D_80072994)\n"
    "sw $v0,%lo(D_80072994)($at)\n"
    ".word 0x8fbf0014\n"
    ".word 0x8fb00010\n"
    ".word 0x03e00008\n"
    "addiu $sp,$sp,24\n"
);

extern void func_8005CF08(void);
extern void func_8005CF18(void);
extern s32 ChangeClearRCnt(s32 intr, s32 mode);
extern s32 SysDeqIntRP(s32 priority, void *intr);
extern unsigned char D_80078988[];

void func_8005D980(void)
{
    func_8005CF08();
    ChangeClearRCnt(3, 1);
    SysDeqIntRP(2, &D_80078988);
    func_8005CF18();
}

INCLUDE_ASM("asm/nonmatchings/800c3", func_8005D9C4);

extern s32 D_800729A0;
extern s32 (*D_800729E0[])();
extern s32 (*D_8007295C)();

s32 func_8005E0AC(void);
void func_8005FBA8(s32 a0);

void func_8005DBD8(void) {
    s32 (*fp)();
    register s32 idx __asm__("$3");
    register s32 ret __asm__("$4");
    register s32 *p __asm__("$5");

    p = &D_800729A0;
    idx = p[0];
    fp = D_800729E0[idx];
    p[0] = idx + 1;
    ret = fp();
    if (ret >= 0) {
        if (D_800729A0 != 0) {
            func_8005FBA8(0x3C);
            if (func_8005E0AC() == 0) {
                (*D_8007295C)(-3);
            }
        }
        if (D_800729A0 >= 5) {
            D_800729A0 = D_800729A0 - 1;
        }
        return;
    }
    (*D_8007295C)(ret);
}


extern s32 *D_800729BC;
extern s32 *D_800729C0;
extern volatile s32 D_80078F24;
extern volatile s32 D_800C5320;

s32 func_8005FBC8(void);

s32 func_8005DCA0(s32 ctx, s32 cmd) {
    u8 tmp;
    s32 first;
    u16 t;
    s32 hw;
    u16 status;
    s32 c;
    u16 *port;

    if (cmd < 0) {
        tmp = *(u8 *)D_800729C0;
        *(u8 *)(ctx + 0x44) = 0xFF;
        *(u8 *)(ctx + 0x45) = 1;
        *(u8 *)*(s32 *)(ctx + 0x40) = ~cmd;
        first = tmp;
        if ((*(volatile u16 *)((s8 *)D_800729C0 + 0x4) & 1) == 0) {
            do {} while ((*(volatile u16 *)((s8 *)D_800729C0 + 0x4) & 1) == 0);
        }
        while (func_8005FBC8() == 0) {}
        {
            register u8 nv __asm__("$2");
            nv = ~cmd;
            *(u8 *)D_800729C0 = nv;
        }
        return first;
    }
    t = 0x88;
    c = *(u8 *)*(s32 *)(ctx + 0x3C);
    if ((c >> 4) == 8 && *(u8 *)(ctx + 0x44) >= 9) {
        t = 0x22;
    }
    port = (u16 *)0x1F801120;
    __asm__("" : "=r"(port) : "0"(port));
    hw = *port;
    status = *(volatile u16 *)((s8 *)D_800729C0 + 0x4);
    D_800C5320 = 0x1AE;
    D_80078F24 = hw;
    if ((status & 2) == 0) {
        do {} while ((*(volatile u16 *)((s8 *)D_800729C0 + 0x4) & 2) == 0);
    }
    {
        s32 *ptr = D_800729BC;
        tmp = *(u8 *)D_800729C0;
        *(u16 *)((s8 *)D_800729C0 + 0xE) = t;
        first = tmp;
        if ((*ptr & 0x80) == 0) {
            do {
                if (func_8005FBC8() != 0) {
                    goto err;
                }
            } while ((*D_800729BC & 0x80) == 0);
        }
    }
    *(u8 *)D_800729C0 = cmd;
    *(u8 *)(ctx + 0x45) += 1;
    *(u8 *)(*(s32 *)(ctx + 0x3C) + *(u8 *)(ctx + 0x44)) = first;
    {
        register u8 inc __asm__("$2");
        inc = *(u8 *)(ctx + 0x44);
        inc += 1;
        *(u8 *)(ctx + 0x44) = inc;
    }
    return first;
err:
    return -20;
}

INCLUDE_ASM("asm/nonmatchings/800c3", func_8005DE78);


extern s32 *D_800729BC;
extern s32 *D_800729C0;

s32 func_8005FBC8(void);

s32 func_8005E0AC(void) {
    s32 *ptr1 = D_800729BC;
    s32 *ptr2;
    u16 v1_val;

    {
        register s32 *pre_ptr2 __asm__("$4") = D_800729C0;
        *ptr1 = -0x81;
        if ((*(u16 *)((s8 *)pre_ptr2 + 0x4) & 0x80) != 0) {
            do {
                if (func_8005FBC8() != 0) {
                    return 0;
                }
            } while ((*(u16 *)((s8 *)D_800729C0 + 0x4) & 0x80) != 0);
        }
    }

    ptr2 = D_800729C0;
    v1_val = *(u16 *)((s8 *)ptr2 + 0xA);
    *(u16 *)((s8 *)ptr2 + 0xA) = v1_val | 0x10;
    return 1;
}


extern s32 *D_800729C0;

__asm__(
    ".text\n"
    ".align\t2\n"
    ".globl\tfunc_8005E13C\n"
    ".ent\tfunc_8005E13C\n"
    "func_8005E13C:\n"
    ".set\tnoreorder\n"
    "lui   $v1, %hi(D_800729C0)\n"
    "lw    $v1, %lo(D_800729C0)($v1)\n"
    "nop\n"
    "1:\n"
    "lhu   $v0, 4($v1)\n"
    "nop\n"
    "andi  $v0, $v0, 0x2\n"
    "beqz  $v0, 1b\n"
    "nop\n"
    "jr    $ra\n"
    "nop\n"
    ".set\treorder\n"
    ".end\tfunc_8005E13C\n"
    "nop\n"
);

/* §295 kernel-trap trampoline: A/B/C dispatch vector in $t2, syscall # in the jr delay slot;
 * unreachable from C (§179-C) -> file-scope verbatim asm (§265 form 1). Pad nop is load-bearing (stride 0x10). */
__asm__(".text\n.align 2\n.globl SysEnqIntRP\n.ent\tSysEnqIntRP\n"
        "SysEnqIntRP:\n.frame $sp,0,$31\n.mask 0x00000000,0\n.fmask 0x00000000,0\n"
        ".set\tnoreorder\n"
        "addiu $t2, $zero, 192\n"
        "jr $t2\n"
        "addiu $t1, $zero, 2\n"
        "nop\n"
        ".set\treorder\n.end\tSysEnqIntRP\n");

__asm__(
    ".text\n"
    ".align\t2\n"
    ".globl\tSysDeqIntRP\n"
    ".ent\tSysDeqIntRP\n"
    "SysDeqIntRP:\n"
    ".set\tnoreorder\n"
    "addiu $t2, $zero, 192\n"
    "jr $t2\n"
    "addiu $t1, $zero, 3\n"
    ".set\treorder\n"
    ".end\tSysDeqIntRP\n"
    "nop\n"
);

void func_8005E188(s32 arg0, s32 arg1, s8 arg2) {
    *(s32*)(arg0 + 0x28) = arg1;
    *(u8*)(arg0 + 0x34) = arg2;
}

void func_8005E194(void *arg0, u8 arg1, u32 arg2, u8 arg3) {
    *(u8 *)((u8 *)arg0 + 0x36) = arg1;
    *(u32 *)((u8 *)arg0 + 0x2C) = arg2;
    *(u8 *)((u8 *)arg0 + 0x35) = arg3;
}

extern void func_8005EA54();
extern void func_8005EA68(void *arg0, s32 arg1);
extern void func_8005EAA8(void *arg0, s32 arg1);

void func_8005E1A4(void *arg0) {
    switch (*(u8 *)((u8 *)arg0 + 0x46)) {
    case 2:
        func_8005EA54(arg0);
        break;
    case 3:
        func_8005EA68(arg0, *(u8 *)((u8 *)arg0 + 0xE4));
        break;
    case 4:
        func_8005EAA8(arg0, *(u8 *)((u8 *)arg0 + 0x47));
        break;
    }
}

__asm__(
    "\t.set\tnoreorder\n"
    ".set noreorder\n"
    "\t.globl\tfunc_8005E228\n"
    "func_8005E228:\n"
    "addiu $sp, $sp, -24\n"
    "sw $s0, 16($sp)\n"
    "addu $s0, $a0, $zero\n"
    "sw $ra, 20($sp)\n"
    "lbu $v1, 70($s0)\n"
    "addiu $v0, $zero, 3\n"
    "beq $v1, $v0, .L8005E2B4\n"
    "slti $v0, $v1, 4\n"
    "beqz $v0, .L8005E260\n"
    "addiu $v0, $zero, 2\n"
    "beq $v1, $v0, .L8005E274\n"
    "addiu $v0, $zero, 1\n"
    "j .L8005E364\n"
    "nop\n"
    ".L8005E260:\n"
    "addiu $v0, $zero, 4\n"
    "beq $v1, $v0, .L8005E2D8\n"
    "addiu $v0, $zero, 1\n"
    "j .L8005E364\n"
    "nop\n"
    ".L8005E274:\n"
    "lw $v0, 60($s0)\n"
    "lw $v1, 60($s0)\n"
    "lbu $v0, 3($v0)\n"
    "nop\n"
    "sb $v0, 227($s0)\n"
    "lbu $v0, 4($v1)\n"
    "lw $v1, 60($s0)\n"
    "sh $zero, 230($s0)\n"
    "sb $v0, 228($s0)\n"
    "lbu $v0, 5($v1)\n"
    "lw $v1, 60($s0)\n"
    "sb $v0, 233($s0)\n"
    "lbu $v0, 6($v1)\n"
    "sw $zero, 236($s0)\n"
    "j .L8005E360\n"
    "sb $v0, 234($s0)\n"
    ".L8005E2B4:\n"
    "lw $v0, 60($s0)\n"
    "nop\n"
    "lbu $v1, 4($v0)\n"
    "lbu $v0, 5($v0)\n"
    "sb $zero, 71($s0)\n"
    "sll $v1, $v1, 8\n"
    "addu $v0, $v0, $v1\n"
    "j .L8005E360\n"
    "sh $v0, 230($s0)\n"
    ".L8005E2D8:\n"
    "lw $a0, 236($s0)\n"
    "lbu $v0, 71($s0)\n"
    "lw $v1, 60($s0)\n"
    "addiu $v0, $v0, 1\n"
    "lbu $v1, 4($v1)\n"
    "addiu $a0, $a0, 8\n"
    "sb $v0, 71($s0)\n"
    "addiu $v1, $v1, 3\n"
    "andi $v1, $v1, 0x1FC\n"
    "addu $a0, $a0, $v1\n"
    "lbu $v1, 234($s0)\n"
    "andi $v0, $v0, 0xFF\n"
    "sltu $v0,$v0,$v1\n"
    "beqz $v0, .L8005E31C\n"
    "sw $a0, 236($s0)\n"
    ".L8005E314:\n"
    "j .L8005E364\n"
    "addu $v0, $zero, $zero\n"
    ".L8005E31C:\n"
    "jal func_8005E374\n"
    "addu $a0, $s0, $zero\n"
    "slti $v0, $v0, 0x81\n"
    "bnez $v0, .L8005E344\n"
    "addu $a0, $s0, $zero\n"
    "addiu $v0, $zero, 0xFE\n"
    "sb $v0, 70($s0)\n"
    "addiu $v0, $zero, 2\n"
    "j .L8005E314\n"
    "sb $v0, 73($s0)\n"
    ".L8005E344:\n"
    "addiu $v0, $zero, 0xFF\n"
    "addiu $a1, $s0, 0x63\n"
    "jal func_8005E3AC\n"
    "sb $v0, 70($s0)\n"
    "addiu $v0, $zero, 2\n"
    "j .L8005E314\n"
    "sb $v0, 70($s0)\n"
    ".L8005E360:\n"
    "addiu $v0, $zero, 1\n"
    ".L8005E364:\n"
    "lw $ra, 20($sp)\n"
    "lw $s0, 16($sp)\n"
    "jr $ra\n"
    "addiu $sp, $sp, 24\n"
    ".set reorder\n"
);


s32 func_8005E374(u8 *a0) {
    s32 t = ((a0[0xE3] + 1) / 2) * 4;
    s32 m = (((a0[0xE9] * 5) + 3) & 0xFFC) + 4;
    return t + m + *(u32 *)(a0 + 0xEC);
}

__asm__(
    "\t.set\tnoreorder\n"
    ".set noreorder\n"
    "\t.globl\tfunc_8005E3AC\n"
    "func_8005E3AC:\n"
    "addiu $sp, $sp, -32\n"
    "sw $s0, 16($sp)\n"
    "addu $s0, $a0, $zero\n"
    "sw $s1, 20($sp)\n"
    "addu $s1, $a1, $zero\n"
    "beqz $s1, .L8005E3F4\n"
    "sw $ra, 24($sp)\n"
    "lw $v0, 4($s0)\n"
    "nop\n"
    "bnez $v0, .L8005E46C\n"
    "addu $v0, $zero, $zero\n"
    "lui $v0, %hi(D_80072978)\n"
    "lw $v0, %lo(D_80072978)($v0)\n"
    "nop\n"
    "jalr $v0\n"
    "nop\n"
    "beqz $v0, .L8005E3FC\n"
    "addiu $v0, $zero, 1\n"
    ".L8005E3F4:\n"
    "j .L8005E46C\n"
    "addu $v0, $zero, $zero\n"
    ".L8005E3FC:\n"
    "addiu $v1, $zero, 4\n"
    "addiu $a1, $s1, 3\n"
    "sra $a1, $a1, 2\n"
    "sb $v1, 73($s0)\n"
    "addiu $v1, $zero, 1\n"
    "sb $v1, 70($s0)\n"
    "lui $v1, %hi(func_8005E480)\n"
    "addiu $v1, $v1, %lo(func_8005E480)\n"
    "sw $v1, 20($s0)\n"
    "lbu $v1, 227($s0)\n"
    "lui $a0, %hi(func_8005E528)\n"
    "addiu $a0, $a0, %lo(func_8005E528)\n"
    "sw $a0, 24($s0)\n"
    "lbu $a0, 233($s0)\n"
    "sll $a1, $a1, 2\n"
    "sw $a1, 0($s0)\n"
    "sb $zero, 71($s0)\n"
    "addiu $v1, $v1, 1\n"
    "sra $v1, $v1, 1\n"
    "sll $v1, $v1, 2\n"
    "addu $a1, $a1, $v1\n"
    "sll $v1, $a0, 2\n"
    "addu $v1, $v1, $a0\n"
    "addiu $v1, $v1, 3\n"
    "andi $v1, $v1, 0xFFC\n"
    "sw $a1, 4($s0)\n"
    "addu $a1, $a1, $v1\n"
    "sw $a1, 8($s0)\n"
    ".L8005E46C:\n"
    "lw $ra, 24($sp)\n"
    "lw $s1, 20($sp)\n"
    "lw $s0, 16($sp)\n"
    "jr $ra\n"
    "addiu $sp, $sp, 32\n"
    ".set reorder\n"
);

extern void func_8005EA68(void *arg0, s32 arg1);
extern void func_8005EA88(void *arg0, s32 arg1);
extern void func_8005EAA8(void *arg0, s32 arg1);
extern void func_8005EAC8(void);

void func_8005E480(void *arg0) {
    switch (*(u8 *)((s32)arg0 + 0x46)) {
    case 2:
        func_8005EA68(arg0, *(u8 *)((s32)arg0 + 0x47));
        break;
    case 3:
        func_8005EA88(arg0, *(u8 *)((s32)arg0 + 0x47));
        break;
    case 4:
        if (*(u8 *)((s32)arg0 + 0x48) == 0) {
            func_8005EAA8(arg0, *(u8 *)((s32)arg0 + 0x47));
        } else {
            func_8005EAC8();
        }
        break;
    }
}


typedef struct Entry {
    /* 0x00 */ u8 b0;
    /* 0x01 */ u8 unk1[3];
    /* 0x04 */ u8 *p4;
} Entry; /* size 8 */

typedef struct Ctx {
    /* 0x00 */ s16 *p00;
    /* 0x04 */ u8 *p04;
    /* 0x08 */ Entry *p08;
    /* 0x0C */ u8 unk0C[0x3C - 0x0C];
    /* 0x3C */ u8 *p3C;
    /* 0x40 */ u8 unk40[0x46 - 0x40];
    /* 0x46 */ u8 b46;
    /* 0x47 */ u8 b47;
    /* 0x48 */ u8 b48;
    /* 0x49 */ u8 b49;
    /* 0x4A */ u8 unk4A[0xE3 - 0x4A];
    /* 0xE3 */ u8 bE3;
    /* 0xE4 */ u8 unkE4[0xE9 - 0xE4];
    /* 0xE9 */ u8 bE9;
    /* 0xEA */ u8 bEA;
} Ctx;

extern u8 *D_800789A8;

s32 func_8005E528(Ctx *s) {
    Entry *e;
    u8 *src;
    u8 *p;
    u8 **gp;
    u8 *g;
    s32 t;
    register u8 *q __asm__("$4");
    s32 n;

    switch (s->b46) {
    case 2:
        s->p00[s->b47] = (s->p3C[4] << 8) + s->p3C[5];
        if (++s->b47 < s->bE3) {
            return 0;
        }
        s->b47 = 0;
        break;

    case 3:
        p = &s->p04[s->b47 * 5];
        q = s->p3C;
        p[0] = q[4];
        p[1] = s->p3C[5] & 0x7F;
        p[2] = s->p3C[6];
        p[3] = s->p3C[7];
        t = s->p3C[5];
        p[4] = t >> 7;
        if (++s->b47 < s->bE9) {
            return 0;
        }
        s->b47 = 0;
        s->b48 = 0;
        break;

    case 4:
        e = &s->p08[s->b47];
        if (s->b48 == 0) {
            e->b0 = s->b48 = s->p3C[4];
            n = 3;
            src = s->p3C + 5;
            if (s->b47 == 0) {
                p = (u8 *)&s->p08[s->bEA];
            } else {
                p = e[-1].p4 + ((e[-1].b0 + 3) & 0x1FC);
            }
            e->p4 = p;
            D_800789A8 = p;
        } else {
            n = 6;
            src = s->p3C + 2;
        }
        for (n--; n != -1; n--) {
            if (s->b48 == 0) goto adv;
            gp = &D_800789A8;
            g = *gp;
            *g++ = *src++;
            *gp = g;
            s->b48--;
        }
        if (s->b48 == 0) goto adv;
    ret0:
        return 0;
    adv:
        if (++s->b47 >= s->bEA) {
            s->b49 = 6;
            s->b46 = 0xFE;
            return 0;
        }
        s->b48 = 0;
        goto ret0;
    }
    return 1;
}

__asm__(
    "\t.set\tnoreorder\n"
    ".set noreorder\n"
    "\t.globl\tfunc_8005E79C\n"
    "func_8005E79C:\n"
    "addiu $sp, $sp, -32\n"
    "sw $s0, 16($sp)\n"
    "addu $s0, $a0, $zero\n"
    "sw $s1, 20($sp)\n"
    "lui $v0, %hi(D_80072978)\n"
    "lw $v0, %lo(D_80072978)($v0)\n"
    "sw $ra, 24($sp)\n"
    "jalr $v0\n"
    "addu $s1, $a1, $zero\n"
    "bnez $v0, 1f\n"
    "addu $v0, $zero, $zero\n"
    "addiu $v0, $zero, 1\n"
    "addiu $v1, $zero, 1\n"
    "sb $v1, 70($s0)\n"
    "lui $v1, %hi(func_8005E804)\n"
    "addiu $v1, $v1, %lo(func_8005E804)\n"
    "sw $v1, 20($s0)\n"
    "lui $v1, %hi(func_8005E820)\n"
    "addiu $v1, $v1, %lo(func_8005E820)\n"
    "sw $s1, 32($s0)\n"
    "sw $v1, 24($s0)\n"
    "1:\n"
    "lw $ra, 24($sp)\n"
    "lw $s1, 20($sp)\n"
    "lw $s0, 16($sp)\n"
    "jr $ra\n"
    "addiu $sp, $sp, 32\n"
    ".set reorder\n"
);

void func_8005E804(u8 *arg0) {
    u32 v1;

    v1 = *(u32 *)(arg0 + 0x20);
    *(u8 *)(arg0 + 0x36) = 0x4D;
    *(u8 *)(arg0 + 0x35) = 6;
    *(u32 *)(arg0 + 0x2C) = v1;
}


s32 func_8005E820(void *a0)
{
    u8 v0;
    u8 *a1;
    s32 a3;
    s32 v1;
    s32 t1;
    s32 t2;
    s32 t3;
    s32 t0;

    v0 = *(u8 *)((u8 *)a0 + 0xE9);
    t0 = 0;
    if (v0 == 0) {
        *(u8 *)((u8 *)a0 + 0x46) = 0xFE;
        return 0;
    }

    t3 = 0xFF;
    t2 = 0;

    do {
        a1 = *(u8 **)((u8 *)a0 + 0x20);
        a3 = 0;

        for (v1 = 5; v1 >= 0; v1--) {
            if (*a1++ == t0) {
                a3++;
            }
        }

        t1 = *(u8 *)(t2 + (u32)*(u8 **)((u8 *)a0 + 0x4) + 2);
        a1 = *(u8 **)((u8 *)a0 + 0x20);
        if (t1 == 0) {
            t1 = 1;
        }
        for (v1 = 0; v1 < 6; v1++) {
            if (*a1++ == t0) {
                if (a3 < t1) {
                    ((u8 *)a0)[v1 + 0x5D] = t3;
                    a3--;
                } else {
                    ((u8 *)a0)[v1 + 0x5D] = t0;
                }
            }
        }

        t2 += 5;
    } while (*(u8 *)((u8 *)a0 + 0xE9) > ++t0);

    *(u8 *)((u8 *)a0 + 0x46) = 0xFE;
    return 0;
}

__asm__(
    "\t.set\tnoreorder\n"
    ".set noreorder\n"
    "\t.globl\tfunc_8005E8E8\n"
    "func_8005E8E8:\n"
    "addiu $sp, $sp, -40\n"
    "sw $s0, 16($sp)\n"
    "addu $s0, $a0, $zero\n"
    "sw $s1, 20($sp)\n"
    "addu $s1, $a1, $zero\n"
    "sw $s2, 24($sp)\n"
    "addu $s2, $a2, $zero\n"
    "sw $s3, 28($sp)\n"
    "lui $v0, %hi(D_80072978)\n"
    "lw $v0, %lo(D_80072978)($v0)\n"
    "sw $ra, 32($sp)\n"
    "jalr $v0\n"
    "addu $s3, $s1, $zero\n"
    "bnez $v0, 1f\n"
    "addu $v0, $zero, $zero\n"
    "addiu $v0, $zero, 1\n"
    "lbu $a0, 228($s0)\n"
    "addiu $v1, $zero, 1\n"
    "sb $v1, 70($s0)\n"
    "lui $v1, %hi(func_8005E980)\n"
    "addiu $v1, $v1, %lo(func_8005E980)\n"
    "sw $v1, 20($s0)\n"
    "lui $v1, %hi(func_8005E9D4)\n"
    "addiu $v1, $v1, %lo(func_8005E9D4)\n"
    "sw $v1, 24($s0)\n"
    "andi $v1, $s3, 0xFF\n"
    "sb $s1, 81($s0)\n"
    "sb $s2, 82($s0)\n"
    "xor $v1, $v1, $a0\n"
    "sltiu $v1, $v1, 1\n"
    "sb $v1, 83($s0)\n"
    "1:\n"
    "lw $ra, 32($sp)\n"
    "lw $s3, 28($sp)\n"
    "lw $s2, 24($sp)\n"
    "lw $s1, 20($sp)\n"
    "lw $s0, 16($sp)\n"
    "jr $ra\n"
    "addiu $sp, $sp, 40\n"
    ".set reorder\n"
);

void func_8005E980(void)
{
    register u8 *s __asm__("$4");
    s32 v = s[0x46];
    switch (v) {
    case 2:
        s[0x36] = 0x44;
        *(u32 *)(s + 0x2C) = (u32)(s + 0x51);
        s[0x35] = v;
        break;
    case 3:
        s[0x36] = 0x4D;
        *(u32 *)(s + 0x2C) = (u32)(s + 0x5D);
        s[0x35] = 6;
        break;
    }
}

extern void (*D_80072960)(void);

s32 func_8005E9D4(s32 a0)
{
    if (*(u8 *)((u8 *)a0 + 0x53) != 0) {
        if (*(u8 *)((u8 *)a0 + 0x46) == 2) {
            return 1;
        }
        *(u8 *)((u8 *)a0 + 0x46) = 0xFE;
        return 0;
    }
    D_80072960();
    return 0;
}

extern void func_8005EA34(void *arg0, s32 arg1);

void func_8005EA34(void *arg0, s32 arg1) {
    *(u8 *)((u8 *)arg0 + 0x36) = 0x43;
    *(s32 *)((u8 *)arg0 + 0x2C) = (s32)((u8 *)arg0 + 0x24);
    *(u8 *)((u8 *)arg0 + 0x24) = arg1;
    *(u8 *)((u8 *)arg0 + 0x35) = 1;
}


void func_8005EA54(void *arg0) {
    *(u8 *)((u8 *)arg0 + 0x36) = 0x45;
    *(s32 *)((u8 *)arg0 + 0x2C) = 0;
    *(u8 *)((u8 *)arg0 + 0x35) = 0;
}

void func_8005EA68(void *arg0, s32 arg1) {
    *(u8 *)((u8 *)arg0 + 0x36) = 0x4C;
    *(s32 *)((u8 *)arg0 + 0x2C) = (s32)((u8 *)arg0 + 0x24);
    *(u8 *)((u8 *)arg0 + 0x24) = arg1;
    *(u8 *)((u8 *)arg0 + 0x35) = 1;
}

void func_8005EA88(void *arg0, s32 arg1) {
    *(u8 *)((u8 *)arg0 + 0x36) = 0x46;
    *(s32 *)((u8 *)arg0 + 0x2C) = (s32)((u8 *)arg0 + 0x24);
    *(u8 *)((u8 *)arg0 + 0x24) = arg1;
    *(u8 *)((u8 *)arg0 + 0x35) = 1;
}

void func_8005EAA8(void *arg0, s32 arg1) {
    *(u8 *)((u8 *)arg0 + 0x36) = 0x47;
    *(s32 *)((u8 *)arg0 + 0x2C) = (s32)((u8 *)arg0 + 0x24);
    *(u8 *)((u8 *)arg0 + 0x24) = arg1;
    *(u8 *)((u8 *)arg0 + 0x35) = 1;
}

__asm__(
    ".text\n"
    ".align\t2\n"
    ".globl\tfunc_8005EAC8\n"
    ".ent\tfunc_8005EAC8\n"
    "func_8005EAC8:\n"
    ".set\tnoreorder\n"
    "addiu $v0, $zero, 75\n"
    "sb    $v0, 54($a0)\n"
    "sw    $zero, 44($a0)\n"
    "jr    $ra\n"
    "sb    $zero, 53($a0)\n"
    "nop\n"
    "nop\n"
    "nop\n"
    ".end\tfunc_8005EAC8\n");

__asm__(
    ".text\n"
    ".align\t2\n"
    ".globl\tfunc_8005EAE8\n"
    ".ent\tfunc_8005EAE8\n"
    "func_8005EAE8:\n"
        ".set\tnoreorder\n"
        "addiu $sp, $sp, -24\n"
        "sw    $s0, 16($sp)\n"
        "lui   $v0, %hi(D_80072974)\n"
        "lw    $v0, %lo(D_80072974)($v0)\n"
        "sw    $ra, 20($sp)\n"
        "jalr  $v0\n"
        "addu  $s0, $a0, $zero\n"
        "addu  $a0, $s0, $zero\n"
        "lui   $at, %hi(D_800729DC)\n"
        "sw    $v0, %lo(D_800729DC)($at)\n"
        "jal   func_8005DCA0\n"
        "addiu $a1, $zero, -2\n"
        "lw    $ra, 20($sp)\n"
        "lw    $s0, 16($sp)\n"
        "jr    $ra\n"
        "addiu $sp, $sp, 24\n"
        ".set\treorder\n"
    ".end\tfunc_8005EAE8\n");

/*
 * func_8005EB28 -- the target's epilogue restores TWO callee-saved registers
 * ($ra and $s0) yet still ends in a bare `jr $ra` / `addiu $sp,$sp,0x18`
 * delay-slot pair. Per cookbook §188 (gcc-2.7.2 mips.c:5081/5174/5204,
 * mips_epilogue_delay_slots): cc1 offers the epilogue a delay slot ONLY when
 * mask == RA_MASK && fmask == 0 (i.e. only $ra saved) -- with $s0 also saved,
 * that branch is structurally unreachable, so NO C source can make cc1 emit
 * this tail under the project's pinned `as -O1` (confirmed here with
 * tools/oracle_reorder.py: bypass+`as -O2` on the ordinary-C draft gives 0
 * diffs, i.e. the C was already right and only the assembler's schedule pass
 * was missing). This is the §265 "no -O2 C can ever match" class, form 1:
 * the whole body is transcribed verbatim as a raw __asm__ block so gcc passes
 * it through untouched. See src/md_MAIN_003/md_MAIN_003.c:524 (func_800D0440)
 * for the precedent this follows.
 */
__asm__(".text\n.align 2\n.globl func_8005EB28\n.ent\tfunc_8005EB28\n"
"func_8005EB28:\n.frame $sp,24,$31\n.mask 0x80010000,-4\n.fmask 0,0\n"
".set\tnoreorder\n"
"lui   $v1, %hi(D_8007299C)\n"
"lw    $v1, %lo(D_8007299C)($v1)\n"
"lui   $v0, %hi(D_800729AC)\n"
"lw    $v0, %lo(D_800729AC)($v0)\n"
"addiu $sp, $sp, -24\n"
"sw    $s0, 16($sp)\n"
"addu  $s0, $a0, $zero\n"
"bne   $v1, $v0, .L8005EB88\n"
" sw   $ra, 20($sp)\n"
"lui   $v0, %hi(D_80072998)\n"
"lw    $v0, %lo(D_80072998)($v0)\n"
"nop\n"
"beqz  $v0, .L8005EB88\n"
" nop\n"
"lui   $v0, %hi(D_8007298C)\n"
"lw    $v0, %lo(D_8007298C)($v0)\n"
"nop\n"
"jalr  $v0\n"
" nop\n"
"lui   $v0, %hi(D_80072988)\n"
"lw    $v0, %lo(D_80072988)($v0)\n"
"nop\n"
"jalr  $v0\n"
" nop\n"
".L8005EB88:\n"
"lui   $v0, %hi(D_800729DC)\n"
"lw    $v0, %lo(D_800729DC)($v0)\n"
"nop\n"
"beqz  $v0, .L8005EBCC\n"
" nop\n"
"lw    $a0, 12($s0)\n"
"lui   $v0, %hi(D_80072974)\n"
"lw    $v0, %lo(D_80072974)($v0)\n"
"nop\n"
"jalr  $v0\n"
" nop\n"
"lw    $a0, 12($s0)\n"
"lui   $v0, %hi(D_80072974)\n"
"lw    $v0, %lo(D_80072974)($v0)\n"
"nop\n"
"jalr  $v0\n"
" addiu $a0, $a0, 240\n"
".L8005EBCC:\n"
"lbu   $v0, 54($s0)\n"
"nop\n"
"bnez  $v0, .L8005EBE4\n"
" addu $a0, $s0, $zero\n"
"j     .L8005EBE8\n"
" addiu $a1, $zero, 66\n"
".L8005EBE4:\n"
"lbu   $a1, 54($s0)\n"
".L8005EBE8:\n"
"jal   func_8005DE78\n"
" nop\n"
"lw    $ra, 20($sp)\n"
"lw    $s0, 16($sp)\n"
"jr    $ra\n"
" addiu $sp, $sp, 24\n"
".set\treorder\n.end\tfunc_8005EB28\n");

/*
 * func_8005EC00 -- same wall as func_8005EB28 (src/800c3.c:1338): the target
 * restores TWO callee-saved registers ($ra and $s0) yet the epilogue still
 * ends in a bare `jr $ra` / `addiu $sp,$sp,0x18` delay-slot pair. Per
 * cookbook §188 (gcc-2.7.2 mips.c:5081/5174/5204, mips_epilogue_delay_slots):
 * cc1 offers the epilogue a delay slot ONLY when mask == RA_MASK && fmask==0
 * (only $ra saved) -- with $s0 also saved that branch is structurally
 * unreachable, so no C source can make cc1 emit this tail under the
 * project's pinned `as -O1`. Banked verbatim per §265 (file-scope raw
 * __asm__ form; decimal immediates -- maspsx rejects hex inside the string).
 *
 * Recovered C semantics (for the eventual real decomp; NOT compiled here --
 * §265 says ship no C externs with the file-scope form):
 *   s32 func_8005EC00(void *arg0) {
 *       s32 v1, v0, a1;
 *       if (D_800729DC != 0) {
 *           (*D_80072974)((void *)(*(s32 *)((char *)arg0 + 0xC) + 0x1E0));
 *           (*D_80072974)((void *)(*(s32 *)((char *)arg0 + 0xC) + 0x2D0));
 *       }
 *       a1 = 0;
 *       if (*(u8 *)((char *)arg0 + 0x36) == 0) {
 *           a1 = D_800729A8;
 *       }
 *       v1 = func_8005DE78(arg0, a1);
 *       if (v1 < 0) {
 *           return v1;
 *       }
 *       v0 = v1 & 0xF0;
 *       if (v0 == 0) {
 *           return -9;
 *       }
 *       v0 = (v1 & 0xF) * 2;
 *       D_800729D4 = v0;
 *       if (v0 == 0) {
 *           D_800729D4 = 0x20;
 *       }
 *       return 0;
 *   }
 */
__asm__(".text\n.align 2\n.globl func_8005EC00\n.ent\tfunc_8005EC00\n"
"func_8005EC00:\n.frame $sp,24,$31\n.mask 0x80010000,-4\n.fmask 0,0\n"
".set\tnoreorder\n"
"lui   $v0, %hi(D_800729DC)\n"
"lw    $v0, %lo(D_800729DC)($v0)\n"
"addiu $sp, $sp, -24\n"
"sw    $s0, 16($sp)\n"
"addu  $s0, $a0, $zero\n"
"beqz  $v0, .L8005EC4C\n"
" sw   $ra, 20($sp)\n"
"lw    $a0, 12($s0)\n"
"lui   $v0, %hi(D_80072974)\n"
"lw    $v0, %lo(D_80072974)($v0)\n"
"nop\n"
"jalr  $v0\n"
" addiu $a0, $a0, 480\n"
"lw    $a0, 12($s0)\n"
"lui   $v0, %hi(D_80072974)\n"
"lw    $v0, %lo(D_80072974)($v0)\n"
"nop\n"
"jalr  $v0\n"
" addiu $a0, $a0, 720\n"
".L8005EC4C:\n"
"lbu   $v0, 54($s0)\n"
"nop\n"
"bnez  $v0, .L8005EC64\n"
" addu $a1, $zero, $zero\n"
"lui   $a1, %hi(D_800729A8)\n"
"lw    $a1, %lo(D_800729A8)($a1)\n"
".L8005EC64:\n"
"jal   func_8005DE78\n"
" addu $a0, $s0, $zero\n"
"addu  $v1, $v0, $zero\n"
"bltz  $v1, .L8005ECB0\n"
" nop\n"
"andi  $v0, $v1, 240\n"
"bnez  $v0, .L8005EC8C\n"
" andi $v0, $v1, 15\n"
"j     .L8005ECB0\n"
" addiu $v0, $zero, -9\n"
".L8005EC8C:\n"
"sll   $v0, $v0, 1\n"
"lui   $at, %hi(D_800729D4)\n"
"sw    $v0, %lo(D_800729D4)($at)\n"
"bnez  $v0, .L8005ECB0\n"
" addu $v0, $zero, $zero\n"
"addiu $v0, $zero, 32\n"
"lui   $at, %hi(D_800729D4)\n"
"sw    $v0, %lo(D_800729D4)($at)\n"
"addu  $v0, $zero, $zero\n"
".L8005ECB0:\n"
"lw    $ra, 20($sp)\n"
"lw    $s0, 16($sp)\n"
"jr    $ra\n"
" addiu $sp, $sp, 24\n"
".set\treorder\n.end\tfunc_8005EC00\n");

INCLUDE_ASM("asm/nonmatchings/800c3", func_8005ECC0);

/* func_8005ED4C — cookbook §265 VERBATIM-ASM bank (file-scope form), generated by
 * tools/asm_verbatim.py from asm/nonmatchings/800c3/func_8005ED4C.s.
 * Byte-equivalent to the INCLUDE_ASM stub by construction; the function is NOT
 * decompiled (§265 ACCOUNTING). Immediates/offsets are decimal for maspsx (§383).
 */
__asm__(
    ".text\n"
    ".align\t2\n"
    ".globl\tfunc_8005ED4C\n"
    ".ent\tfunc_8005ED4C\n"
    "func_8005ED4C:\n"
    ".frame\t$sp,48,$31\n"
    ".mask\t0x803F0000,-4\n"
    ".fmask\t0,0\n"
    ".set\tnoreorder\n"
    "addiu $sp,$sp,-48\n"
    "sw $s1,20($sp)\n"
    "addu $s1,$a0,$zero\n"
    "lui $v0,%hi(D_80072968)\n"
    "lw $v0,%lo(D_80072968)($v0)\n"
    "sw $ra,40($sp)\n"
    "sw $s5,36($sp)\n"
    "sw $s4,32($sp)\n"
    "sw $s3,28($sp)\n"
    "sw $s2,24($sp)\n"
    "jalr $v0\n"
    " sw $s0,16($sp)\n"
    "lui $v0,%hi(D_800729A8)\n"
    "lw $v0,%lo(D_800729A8)($v0)\n"
    "nop\n"
    "beqz $v0,.L8005EDB8\n"
    " addu $s4,$zero,$zero\n"
    "lw $v0,60($s1)\n"
    "nop\n"
    "lbu $v0,0($v0)\n"
    "addiu $v1,$zero,8\n"
    "sra $v0,$v0,4\n"
    "bne $v0,$v1,.L8005EDB8\n"
    " nop\n"
    "lbu $v0,54($s1)\n"
    "nop\n"
    "sltiu $s4,$v0,1\n"
    ".L8005EDB8:\n"
    "beqz $s4,.L8005EE54\n"
    " nop\n"
    "addiu $s0,$zero,-1\n"
    "addiu $s2,$zero,-240\n"
    ".L8005EDC8:\n"
    "lui $v0,%hi(D_800729D4)\n"
    "lw $v0,%lo(D_800729D4)($v0)\n"
    "nop\n"
    "addiu $v0,$v0,-1\n"
    "lui $at,%hi(D_800729D4)\n"
    "blez $v0,.L8005EE54\n"
    " sw $v0,%lo(D_800729D4)($at)\n"
    "bltz $s0,.L8005EE04\n"
    " nop\n"
    "lw $a0,12($s1)\n"
    "lui $v0,%hi(D_80072968)\n"
    "lw $v0,%lo(D_80072968)($v0)\n"
    "nop\n"
    "jalr $v0\n"
    " addu $a0,$a0,$s2\n"
    ".L8005EE04:\n"
    "addu $a0,$s1,$zero\n"
    "lui $v0,%hi(D_80072964)\n"
    "lw $v0,%lo(D_80072964)($v0)\n"
    "nop\n"
    "jalr $v0\n"
    " addiu $a1,$zero,1\n"
    "addu $a0,$s1,$zero\n"
    "jal func_8005DE78\n"
    " andi $a1,$v0,255\n"
    "bltz $v0,.L8005F0A4\n"
    " nop\n"
    "jal func_8005FBA8\n"
    " addiu $a0,$zero,60\n"
    "jal func_8005E0AC\n"
    " nop\n"
    "beqz $v0,.L8005EFC8\n"
    " addiu $s0,$s0,1\n"
    "slti $v0,$s0,4\n"
    "bnez $v0,.L8005EDC8\n"
    " addiu $s2,$s2,240\n"
    ".L8005EE54:\n"
    "lui $v1,%hi(D_8007299C)\n"
    "lw $v1,%lo(D_8007299C)($v1)\n"
    "lui $v0,%hi(D_800729D4)\n"
    "lw $v0,%lo(D_800729D4)($v0)\n"
    "nop\n"
    "slti $v0,$v0,2\n"
    "bnez $v0,.L8005F040\n"
    " sltiu $a0,$v1,1\n"
    "lui $v1,%hi(D_800729B4)\n"
    "addiu $v1,$v1,%lo(D_800729B4)\n"
    "sll $v0,$a0,2\n"
    "addu $s0,$v0,$v1\n"
    "sll $v0,$a0,4\n"
    "subu $v0,$v0,$a0\n"
    "sll $s2,$v0,4\n"
    "addiu $s5,$zero,3\n"
    ".L8005EE94:\n"
    "lw $a0,0($s0)\n"
    "nop\n"
    "bltz $a0,.L8005F040\n"
    " nop\n"
    "blez $a0,.L8005EEE0\n"
    " sll $v0,$a0,4\n"
    "lui $v1,%hi(D_80072990)\n"
    "lw $v1,%lo(D_80072990)($v1)\n"
    "subu $v0,$v0,$a0\n"
    "addu $v1,$s2,$v1\n"
    "lw $v1,12($v1)\n"
    "sll $v0,$v0,4\n"
    "addu $v1,$v1,$v0\n"
    "addiu $s3,$v1,-240\n"
    "lui $v0,%hi(D_8007297C)\n"
    "lw $v0,%lo(D_8007297C)($v0)\n"
    "nop\n"
    "jalr $v0\n"
    " addu $a0,$s3,$zero\n"
    ".L8005EEE0:\n"
    "lw $v1,0($s0)\n"
    "nop\n"
    "beq $v1,$s5,.L8005EF28\n"
    " nop\n"
    "slti $v0,$v1,4\n"
    "beqz $v0,.L8005EF14\n"
    " slti $v0,$v1,2\n"
    "beqz $v0,.L8005EF88\n"
    " addu $a0,$s1,$zero\n"
    "bltz $v1,.L8005EF88\n"
    " nop\n"
    "j .L8005EF44\n"
    " nop\n"
    ".L8005EF14:\n"
    "addiu $v0,$zero,4\n"
    "bne $v1,$v0,.L8005EF88\n"
    " addu $a0,$s1,$zero\n"
    "j .L8005EF88\n"
    " sw $s5,0($s0)\n"
    ".L8005EF28:\n"
    "lui $v0,%hi(D_8007297C)\n"
    "lw $v0,%lo(D_8007297C)($v0)\n"
    "nop\n"
    "jalr $v0\n"
    " addiu $a0,$s3,-240\n"
    "j .L8005EF80\n"
    " addiu $v0,$zero,1\n"
    ".L8005EF44:\n"
    "lui $v0,%hi(D_80072990)\n"
    "lw $v0,%lo(D_80072990)($v0)\n"
    "nop\n"
    "addu $s3,$v0,$s2\n"
    "lui $v0,%hi(D_8007297C)\n"
    "lw $v0,%lo(D_8007297C)($v0)\n"
    "nop\n"
    "jalr $v0\n"
    " addu $a0,$s3,$zero\n"
    "lui $v0,%hi(D_80072980)\n"
    "lw $v0,%lo(D_80072980)($v0)\n"
    "nop\n"
    "jalr $v0\n"
    " addu $a0,$s3,$zero\n"
    "addiu $v0,$zero,-1\n"
    ".L8005EF80:\n"
    "sw $v0,0($s0)\n"
    "addu $a0,$s1,$zero\n"
    ".L8005EF88:\n"
    "lui $v0,%hi(D_80072964)\n"
    "lw $v0,%lo(D_80072964)($v0)\n"
    "nop\n"
    "jalr $v0\n"
    " addu $a1,$s4,$zero\n"
    "addu $a0,$s1,$zero\n"
    "jal func_8005DCA0\n"
    " andi $a1,$v0,255\n"
    "bltz $v0,.L8005F0A4\n"
    " nop\n"
    "jal func_8005FBA8\n"
    " addiu $a0,$zero,60\n"
    "jal func_8005E0AC\n"
    " nop\n"
    "bnez $v0,.L8005EFD0\n"
    " nop\n"
    ".L8005EFC8:\n"
    "j .L8005F0A4\n"
    " addiu $v0,$zero,-3\n"
    ".L8005EFD0:\n"
    "lui $v0,%hi(D_800729D4)\n"
    "lw $v0,%lo(D_800729D4)($v0)\n"
    "nop\n"
    "addiu $v0,$v0,-1\n"
    "lui $at,%hi(D_800729D4)\n"
    "sw $v0,%lo(D_800729D4)($at)\n"
    "slti $v0,$v0,2\n"
    "beqz $v0,.L8005EE94\n"
    " nop\n"
    "j .L8005F040\n"
    " nop\n"
    ".L8005EFFC:\n"
    "addu $a0,$s1,$zero\n"
    "lui $v0,%hi(D_80072964)\n"
    "lw $v0,%lo(D_80072964)($v0)\n"
    "nop\n"
    "jalr $v0\n"
    " addu $a1,$s4,$zero\n"
    "addu $a0,$s1,$zero\n"
    "jal func_8005DCA0\n"
    " andi $a1,$v0,255\n"
    "bltz $v0,.L8005F0A4\n"
    " nop\n"
    "jal func_8005FBA8\n"
    " addiu $a0,$zero,60\n"
    "jal func_8005E0AC\n"
    " nop\n"
    "beqz $v0,.L8005F0A4\n"
    " addiu $v0,$zero,-3\n"
    ".L8005F040:\n"
    "lui $v0,%hi(D_800729D4)\n"
    "lw $v0,%lo(D_800729D4)($v0)\n"
    "nop\n"
    "addiu $v0,$v0,-1\n"
    "lui $at,%hi(D_800729D4)\n"
    "bgtz $v0,.L8005EFFC\n"
    " sw $v0,%lo(D_800729D4)($at)\n"
    "jal func_8005E13C\n"
    " nop\n"
    "lbu $v1,68($s1)\n"
    "nop\n"
    "addiu $v0,$v1,1\n"
    "sb $v0,68($s1)\n"
    "lui $v0,%hi(D_800729D8)\n"
    "lw $v0,%lo(D_800729D8)($v0)\n"
    "lw $a0,60($s1)\n"
    "lbu $v0,0($v0)\n"
    "addu $v1,$v1,$a0\n"
    "sb $v0,0($v1)\n"
    "lui $v0,%hi(D_8007295C)\n"
    "lw $v0,%lo(D_8007295C)($v0)\n"
    "nop\n"
    "jalr $v0\n"
    " addu $a0,$zero,$zero\n"
    "addu $v0,$zero,$zero\n"
    ".L8005F0A4:\n"
    "lw $ra,40($sp)\n"
    "lw $s5,36($sp)\n"
    "lw $s4,32($sp)\n"
    "lw $s3,28($sp)\n"
    "lw $s2,24($sp)\n"
    "lw $s1,20($sp)\n"
    "lw $s0,16($sp)\n"
    "jr $ra\n"
    " addiu $sp,$sp,48\n"
    ".set\treorder\n"
    ".end\tfunc_8005ED4C\n"
);

INCLUDE_ASM("asm/nonmatchings/800c3", func_8005F0C8);

void func_8005F228(void *arg0) {
    u8 *p;
    s32 i;

    if (*(u8 *)((u8 *)arg0 + 0x49) == 0) {
        return;
    }
    p = (u8 *)arg0 + 0x5D;
    *(u8 *)((u8 *)arg0 + 0x49) = 0;
    *(u8 *)((u8 *)arg0 + 0x46) = 0;
    *(u16 *)((u8 *)arg0 + 0xE6) = 0;
    *(u32 *)((u8 *)arg0 + 0x14) = 0;
    *(u32 *)((u8 *)arg0 + 0x18) = 0;
    *(u8 *)((u8 *)arg0 + 0xE3) = 0;
    *(u8 *)((u8 *)arg0 + 0xE4) = 0;
    *(u16 *)((u8 *)arg0 + 0xE6) = 0;
    *(u8 *)((u8 *)arg0 + 0xE9) = 0;
    *(u8 *)((u8 *)arg0 + 0xEA) = 0;
    *(u32 *)((u8 *)arg0 + 0x00) = 0;
    *(u32 *)((u8 *)arg0 + 0x04) = 0;
    *(u32 *)((u8 *)arg0 + 0x08) = 0;
    for (i = 0; i < 6; i++) {
        *p++ = 0xFF;
    }
}

INCLUDE_ASM("asm/nonmatchings/800c3", func_8005F290);

void func_8005F384(void *arg0) {
    u8 temp;

    temp = *(u8 *)((u8 *)arg0 + 0x36);
    *(u8 *)((u8 *)arg0 + 0x36) = 0;
    *(u8 *)((u8 *)arg0 + 0x37) = temp;
}

s32 func_8005F394(u8 *arg0) {
    s32 idx = arg0[0x45] - 3;
    s32 base;

    switch (arg0[0x36]) {
    case 0:
        if (idx < 6 && *(arg0 + idx + 0x57) == 0) {
            return 0;
        }
        if (idx >= arg0[0x34]) {
            return 0;
        }
        base = *(s32 *)(arg0 + 0x28);
    load_it:
        return *(u8 *)(base + idx);
    case 0x4D:
        if (idx >= arg0[0x35]) {
            return 0xFF;
        }
        base = *(s32 *)(arg0 + 0x2C);
        goto load_it;
    default: {
        u8 val;
        if (idx >= arg0[0x35]) {
            return 0;
        }
        val = *(u8 *)(*(s32 *)(arg0 + 0x2C) + idx);
        __asm__ __volatile__("" ::: "memory");
        return val;
    }
    }
}

/* func_8005F450 — cookbook §265 VERBATIM-ASM bank (file-scope form), generated by
 * tools/asm_verbatim.py from asm/nonmatchings/800c3/func_8005F450.s.
 * Byte-equivalent to the INCLUDE_ASM stub by construction; the function is NOT
 * decompiled (§265 ACCOUNTING). Immediates/offsets are decimal for maspsx (§383).
 */
__asm__(
    ".text\n"
    ".align\t2\n"
    ".globl\tfunc_8005F450\n"
    ".ent\tfunc_8005F450\n"
    "func_8005F450:\n"
    ".frame\t$sp,24,$31\n"
    ".mask\t0x80010000,0\n"
    ".fmask\t0,0\n"
    ".set\tnoreorder\n"
    "addiu $sp,$sp,-24\n"
    "sw $s0,16($sp)\n"
    "addu $s0,$a0,$zero\n"
    "addiu $a0,$s0,87\n"
    "sw $ra,20($sp)\n"
    "jal func_8005C2C8\n"
    " addiu $a1,$zero,6\n"
    "lhu $v0,230($s0)\n"
    "nop\n"
    "beqz $v0,.L8005F5C8\n"
    " nop\n"
    "lw $v0,40($s0)\n"
    "nop\n"
    "beqz $v0,.L8005F5C8\n"
    " nop\n"
    "lbu $v0,52($s0)\n"
    "nop\n"
    "sltiu $v0,$v0,7\n"
    "beqz $v0,.L8005F4A4\n"
    " addiu $t1,$zero,6\n"
    "lbu $t1,52($s0)\n"
    ".L8005F4A4:\n"
    "lbu $v0,233($s0)\n"
    "nop\n"
    "beqz $v0,.L8005F6BC\n"
    " addu $t0,$zero,$zero\n"
    "addiu $t3,$zero,1\n"
    "addu $t2,$zero,$zero\n"
    ".L8005F4BC:\n"
    "lw $v0,4($s0)\n"
    "addu $a2,$zero,$zero\n"
    "addu $v0,$t2,$v0\n"
    "lbu $v0,2($v0)\n"
    "nop\n"
    "beqz $v0,.L8005F4DC\n"
    " addiu $a3,$zero,1\n"
    "addiu $a3,$zero,255\n"
    ".L8005F4DC:\n"
    "addiu $a1,$s0,93\n"
    "lw $a0,40($s0)\n"
    "beqz $t1,.L8005F524\n"
    " addu $v1,$zero,$zero\n"
    ".L8005F4EC:\n"
    "lbu $v0,0($a1)\n"
    "nop\n"
    "bne $v0,$t0,.L8005F510\n"
    " nop\n"
    "lbu $v0,0($a0)\n"
    "nop\n"
    "and $v0,$v0,$a3\n"
    "bnez $v0,.L8005F564\n"
    " nop\n"
    ".L8005F510:\n"
    "addiu $a1,$a1,1\n"
    "addiu $v1,$v1,1\n"
    "slt $v0,$v1,$t1\n"
    "bnez $v0,.L8005F4EC\n"
    " addiu $a0,$a0,1\n"
    ".L8005F524:\n"
    "beqz $a2,.L8005F5AC\n"
    " nop\n"
    "lw $v0,4($s0)\n"
    "nop\n"
    "addu $v0,$t2,$v0\n"
    "lbu $v1,3($v0)\n"
    "lui $v0,%hi(D_800729A4)\n"
    "lw $v0,%lo(D_800729A4)($v0)\n"
    "nop\n"
    "addu $v1,$v0,$v1\n"
    "slti $v0,$v1,61\n"
    "beqz $v0,.L8005F56C\n"
    " nop\n"
    "lui $at,%hi(D_800729A4)\n"
    "j .L8005F570\n"
    " sw $v1,%lo(D_800729A4)($at)\n"
    ".L8005F564:\n"
    "j .L8005F524\n"
    " addiu $a2,$zero,1\n"
    ".L8005F56C:\n"
    "addu $a2,$zero,$zero\n"
    ".L8005F570:\n"
    "beqz $a2,.L8005F5AC\n"
    " nop\n"
    "addiu $a1,$s0,93\n"
    "addiu $a0,$s0,87\n"
    "beqz $t1,.L8005F5AC\n"
    " addu $v1,$zero,$zero\n"
    ".L8005F588:\n"
    "lbu $v0,0($a1)\n"
    "nop\n"
    "bne $v0,$t0,.L8005F59C\n"
    " addiu $a1,$a1,1\n"
    "sb $t3,0($a0)\n"
    ".L8005F59C:\n"
    "addiu $v1,$v1,1\n"
    "slt $v0,$v1,$t1\n"
    "bnez $v0,.L8005F588\n"
    " addiu $a0,$a0,1\n"
    ".L8005F5AC:\n"
    "lbu $v0,233($s0)\n"
    "addiu $t0,$t0,1\n"
    "slt $v0,$t0,$v0\n"
    "bnez $v0,.L8005F4BC\n"
    " addiu $t2,$t2,5\n"
    "j .L8005F6BC\n"
    " nop\n"
    ".L8005F5C8:\n"
    "lbu $v1,232($s0)\n"
    "nop\n"
    "addiu $v0,$v1,-4\n"
    "sltiu $v0,$v0,2\n"
    "bnez $v0,.L8005F5E8\n"
    " addiu $v0,$zero,7\n"
    "bne $v1,$v0,.L8005F67C\n"
    " nop\n"
    ".L8005F5E8:\n"
    "lhu $v0,230($s0)\n"
    "nop\n"
    "bnez $v0,.L8005F67C\n"
    " nop\n"
    "lbu $v0,52($s0)\n"
    "nop\n"
    "sltiu $v0,$v0,2\n"
    "bnez $v0,.L8005F67C\n"
    " addiu $v1,$zero,64\n"
    "lw $a0,40($s0)\n"
    "nop\n"
    "lbu $v0,0($a0)\n"
    "nop\n"
    "andi $v0,$v0,192\n"
    "bne $v0,$v1,.L8005F6BC\n"
    " nop\n"
    "lbu $v0,1($a0)\n"
    "nop\n"
    "andi $v0,$v0,1\n"
    "beqz $v0,.L8005F6BC\n"
    " nop\n"
    "lui $v0,%hi(D_800729A4)\n"
    "lw $v0,%lo(D_800729A4)($v0)\n"
    "nop\n"
    "addiu $v0,$v0,10\n"
    "slti $v0,$v0,61\n"
    "beqz $v0,.L8005F6BC\n"
    " addiu $v0,$zero,1\n"
    "sb $v0,88($s0)\n"
    "sb $v0,87($s0)\n"
    "lui $v0,%hi(D_800729A4)\n"
    "lw $v0,%lo(D_800729A4)($v0)\n"
    "nop\n"
    "addiu $v0,$v0,10\n"
    "lui $at,%hi(D_800729A4)\n"
    "j .L8005F6BC\n"
    " sw $v0,%lo(D_800729A4)($at)\n"
    ".L8005F67C:\n"
    "lbu $v1,232($s0)\n"
    "addiu $v0,$zero,3\n"
    "bne $v1,$v0,.L8005F694\n"
    " addiu $v0,$zero,1\n"
    "j .L8005F6BC\n"
    " sb $v0,87($s0)\n"
    ".L8005F694:\n"
    "lhu $v0,230($s0)\n"
    "nop\n"
    "bnez $v0,.L8005F6BC\n"
    " addiu $v0,$zero,1\n"
    "addiu $v1,$zero,5\n"
    "addiu $a0,$s0,5\n"
    ".L8005F6AC:\n"
    "sb $v0,87($a0)\n"
    "addiu $v1,$v1,-1\n"
    "bgez $v1,.L8005F6AC\n"
    " addiu $a0,$a0,-1\n"
    ".L8005F6BC:\n"
    "lw $ra,20($sp)\n"
    "lw $s0,16($sp)\n"
    "jr $ra\n"
    " addiu $sp,$sp,24\n"
    ".set\treorder\n"
    ".end\tfunc_8005F450\n"
);


extern u8 D_80078A48;

s32 func_8005F6CC(void *a0)
{
    s32 i;
    s32 ret;
    u8 *p;
    s32 res;

    i = 0;
    ret = 0x10;
    p = &D_80078A48;
    do {
        if (a0 == p) {
            res = ret;
            goto done;
        }
        ret += 0x10;
        i++;
        p += 0xF0;
    } while (i < 2);
    res = 0xFF;
done:
    return res;
}

extern u8 D_80078A48;

s32 func_8005F704(s32 arg0) {
    s32 var_v0 = (s32)&D_80078A48;
    if (arg0 & 0xF0) {
        var_v0 += 0xF0;
    }
    return var_v0;
}

__asm__(".word 0x00000000\n");


__asm__(
    ".text\n"
    ".align\t2\n"
    ".globl\tfunc_8005F728\n"
    ".ent\tfunc_8005F728\n"
    "func_8005F728:\n"
    ".set\tnoreorder\n"
    "lui   $v0, %hi(func_8005F75C)\n"
    "addiu $v0, $v0, %lo(func_8005F75C)\n"
    "lui   $at, %hi(D_80072974)\n"
    "sw    $v0, %lo(D_80072974)($at)\n"
    "lui   $v0, %hi(func_8005FB70)\n"
    "addiu $v0, $v0, %lo(func_8005FB70)\n"
    "lui   $at, %hi(D_80072978)\n"
    "sw    $v0, %lo(D_80072978)($at)\n"
    "lui   $v0, %hi(func_8005F830)\n"
    "addiu $v0, $v0, %lo(func_8005F830)\n"
    "lui   $at, %hi(D_8007297C)\n"
    "jr    $ra\n"
    "sw    $v0, %lo(D_8007297C)($at)\n"
    ".set\treorder\n"
    ".end\tfunc_8005F728\n"
);


extern void func_8005EA34(void *arg0, s32 arg1);
extern void func_8005E1A4(void *arg0);

s32 func_8005F75C(void *arg0) {
    void *v0;
    s32 v1;

    v0 = M2C_FIELD(arg0, void **, 0x3C);
    if (M2C_FIELD(v0, u8 *, 0x0) == 0xF3) {
        if (M2C_FIELD(arg0, u8 *, 0xE8) == 0) {
            goto L8005F7E8;
        }
    }

    v1 = M2C_FIELD(arg0, u8 *, 0x46);
    if (v1 == 1) {
        goto L8005F7D8;
    }
    __asm__ volatile("" ::: "memory");
    if (v1 < 2) {
        if (v1 == 0) {
            goto L8005F820;
        }
        goto L8005F7F8;
    }
    if (v1 == 0xFE) {
        goto L8005F7E8;
    }
    __asm__ volatile("" ::: "memory");
    if (v1 == 0xFF) {
        goto L8005F820;
    }
    goto L8005F7F8;

L8005F7D8:
    func_8005EA34(arg0, 1);
    goto L8005F820;

L8005F7E8:
    func_8005EA34(arg0, 0);
    goto L8005F820;

L8005F7F8:
    {
        void (*fp)(void *) = M2C_FIELD(arg0, void (**)(void *), 0x14);
        if (fp != NULL) {
            fp(arg0);
            goto L8005F820;
        }
    }
    func_8005E1A4(arg0);

L8005F820:
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/800c3", func_8005F830);

/* func_8005FA94 — cookbook §265 VERBATIM-ASM bank (file-scope form), generated by
 * tools/asm_verbatim.py from asm/nonmatchings/800c3/func_8005FA94.s.
 * Byte-equivalent to the INCLUDE_ASM stub by construction; the function is NOT
 * decompiled (§265 ACCOUNTING). Immediates/offsets are decimal for maspsx (§383).
 */
__asm__(
    ".text\n"
    ".align\t2\n"
    ".globl\tfunc_8005FA94\n"
    ".ent\tfunc_8005FA94\n"
    "func_8005FA94:\n"
    ".frame\t$sp,24,$31\n"
    ".mask\t0x80010000,0\n"
    ".fmask\t0,0\n"
    ".set\tnoreorder\n"
    "addiu $sp,$sp,-24\n"
    "sw $s0,16($sp)\n"
    "addu $s0,$a0,$zero\n"
    "sw $ra,20($sp)\n"
    "lw $v0,76($s0)\n"
    "lbu $v1,70($s0)\n"
    "addiu $v0,$v0,1\n"
    "beqz $v1,.L8005FB2C\n"
    " sw $v0,76($s0)\n"
    "addiu $v0,$zero,1\n"
    "bne $v1,$v0,.L8005FAEC\n"
    " nop\n"
    "lbu $v1,74($s0)\n"
    "nop\n"
    "sltiu $v0,$v1,2\n"
    "bnez $v0,.L8005FB00\n"
    " addiu $v0,$v1,1\n"
    "addiu $v0,$zero,2\n"
    "sb $v0,73($s0)\n"
    "addiu $v0,$zero,255\n"
    "j .L8005FB60\n"
    " sb $v0,70($s0)\n"
    ".L8005FAEC:\n"
    "lbu $v1,74($s0)\n"
    "nop\n"
    "sltiu $v0,$v1,4\n"
    "beqz $v0,.L8005FB08\n"
    " addiu $v0,$v1,1\n"
    ".L8005FB00:\n"
    "j .L8005FB60\n"
    " sb $v0,74($s0)\n"
    ".L8005FB08:\n"
    "lbu $v0,73($s0)\n"
    "nop\n"
    "beqz $v0,.L8005FB2C\n"
    " nop\n"
    "lui $v0,%hi(D_80072960)\n"
    "lw $v0,%lo(D_80072960)($v0)\n"
    "nop\n"
    "jalr $v0\n"
    " addu $a0,$s0,$zero\n"
    ".L8005FB2C:\n"
    "lw $v0,60($s0)\n"
    "nop\n"
    "lbu $v1,0($v0)\n"
    "addiu $v0,$zero,243\n"
    "beq $v1,$v0,.L8005FB60\n"
    " addiu $v1,$zero,255\n"
    "lw $v0,48($s0)\n"
    "nop\n"
    "sb $v1,0($v0)\n"
    "lw $v0,48($s0)\n"
    "nop\n"
    "sb $zero,1($v0)\n"
    "sb $zero,232($s0)\n"
    ".L8005FB60:\n"
    "lw $ra,20($sp)\n"
    "lw $s0,16($sp)\n"
    "jr $ra\n"
    " addiu $sp,$sp,24\n"
    ".set\treorder\n"
    ".end\tfunc_8005FA94\n"
);

s32 func_8005FB70(void *arg0) {
    register s32 ff __asm__("$2");

    if (*(u16 *)((u8 *)arg0 + 0xE6) == 0) {
        return 1;
    }
    ff = 0xFF;
    __asm__ __volatile__("" : "=r"(ff) : "0"(ff));
    if (*(u8 *)((u8 *)arg0 + 0x46) == ff) {
        return 0;
    }
    return 1;
}

__asm__(".nop\n.nop\n.nop");

__asm__(
    ".text\n"
    ".align\t2\n"
    ".globl\tfunc_8005FBA8\n"
    ".ent\tfunc_8005FBA8\n"
    "func_8005FBA8:\n"
    ".set\tnoreorder\n"
    "lui   $v0, 0x1F80\n"
    "ori   $v0, $v0, 0x1120\n"
    "lhu   $v0, 0($v0)\n"
    "lui   $at, %hi(D_800C5320)\n"
    "sw    $a0, %lo(D_800C5320)($at)\n"
    "lui   $at, %hi(D_80078F24)\n"
    "jr    $ra\n"
    "sw    $v0, %lo(D_80078F24)($at)\n"
    ".set\treorder\n"
    ".end\tfunc_8005FBA8\n"
);


extern volatile s32 D_80078F24;
extern volatile s32 D_800C5320;

s32 func_8005FBC8(void) {
    u16 val1;
    s32 a0;
    u16 status;

    val1 = *(volatile u16*)0x1F801120;
    a0 = val1;

    if ((u32)a0 < (u32)D_80078F24) {
        if (*(volatile u16*)0x1F801128 != 0) {
            a0 += *(volatile u16*)0x1F801128;
        } else {
            a0 += 0x10000;
        }
    }

    status = *(volatile u16*)0x1F801124;

    if (status & 0x200) {
        return (u32)(a0 - D_80078F24) >= (u32)D_800C5320;
    } else {
        return ((u32)(a0 - D_80078F24) >> 3) >= (u32)D_800C5320;
    }
}
