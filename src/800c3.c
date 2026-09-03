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


INCLUDE_ASM("asm/nonmatchings/800c3", func_8005D33C);

extern void* (*D_80072970)(void);

INCLUDE_ASM("asm/nonmatchings/800c3", func_8005D410);

INCLUDE_ASM("asm/nonmatchings/800c3", func_8005D4B8);

INCLUDE_ASM("asm/nonmatchings/800c3", func_8005D4F0);

INCLUDE_ASM("asm/nonmatchings/800c3", func_8005D538);


INCLUDE_ASM("asm/nonmatchings/800c3", func_8005D588);

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
INCLUDE_ASM("asm/nonmatchings/800c3", func_8005D734);

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


INCLUDE_ASM("asm/nonmatchings/800c3", func_8005D8B4);

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

INCLUDE_ASM("asm/nonmatchings/800c3", func_8005E13C);

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

INCLUDE_ASM("asm/nonmatchings/800c3", func_8005E228);


s32 func_8005E374(u8 *a0) {
    s32 t = ((a0[0xE3] + 1) / 2) * 4;
    s32 m = (((a0[0xE9] * 5) + 3) & 0xFFC) + 4;
    return t + m + *(u32 *)(a0 + 0xEC);
}

INCLUDE_ASM("asm/nonmatchings/800c3", func_8005E3AC);

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

INCLUDE_ASM("asm/nonmatchings/800c3", func_8005E79C);

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

INCLUDE_ASM("asm/nonmatchings/800c3", func_8005E8E8);

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

INCLUDE_ASM("asm/nonmatchings/800c3", func_8005EAC8);

INCLUDE_ASM("asm/nonmatchings/800c3", func_8005EAE8);

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
INCLUDE_ASM("asm/nonmatchings/800c3", func_8005EB28);

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
INCLUDE_ASM("asm/nonmatchings/800c3", func_8005EC00);

INCLUDE_ASM("asm/nonmatchings/800c3", func_8005ECC0);

/* func_8005ED4C — cookbook §265 VERBATIM-ASM bank (file-scope form), generated by
 * tools/asm_verbatim.py from asm/nonmatchings/800c3/func_8005ED4C.s.
 * Byte-equivalent to the INCLUDE_ASM stub by construction; the function is NOT
 * decompiled (§265 ACCOUNTING). Immediates/offsets are decimal for maspsx (§383).
 */
INCLUDE_ASM("asm/nonmatchings/800c3", func_8005ED4C);

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
INCLUDE_ASM("asm/nonmatchings/800c3", func_8005F450);


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
INCLUDE_ASM("asm/nonmatchings/800c3", func_8005FA94);

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
