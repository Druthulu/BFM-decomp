#include "common.h"

INCLUDE_ASM("asm/nonmatchings/800c3", InitHeap);

INCLUDE_ASM("asm/nonmatchings/800c3", FlushCache);

INCLUDE_ASM("asm/nonmatchings/800c3", func_8005CE38);

INCLUDE_ASM("asm/nonmatchings/800c3", _96_remove);

INCLUDE_ASM("asm/nonmatchings/800c3", DeliverEvent);

INCLUDE_ASM("asm/nonmatchings/800c3", OpenEvent);

INCLUDE_ASM("asm/nonmatchings/800c3", CloseEvent);

INCLUDE_ASM("asm/nonmatchings/800c3", WaitEvent);

INCLUDE_ASM("asm/nonmatchings/800c3", TestEvent);

INCLUDE_ASM("asm/nonmatchings/800c3", EnableEvent);

INCLUDE_ASM("asm/nonmatchings/800c3", DisableEvent);

INCLUDE_ASM("asm/nonmatchings/800c3", ReturnFromException);

INCLUDE_ASM("asm/nonmatchings/800c3", ResetEntryInt);

INCLUDE_ASM("asm/nonmatchings/800c3", HookEntryInt);

INCLUDE_ASM("asm/nonmatchings/800c3", func_8005CF08);

INCLUDE_ASM("asm/nonmatchings/800c3", func_8005CF18);

INCLUDE_ASM("asm/nonmatchings/800c3", read);

INCLUDE_ASM("asm/nonmatchings/800c3", write);

INCLUDE_ASM("asm/nonmatchings/800c3", ChangeClearPAD);

INCLUDE_ASM("asm/nonmatchings/800c3", ChangeClearRCnt);


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

INCLUDE_ASM("asm/nonmatchings/800c3", GetRCnt);

INCLUDE_ASM("asm/nonmatchings/800c3", StartRCnt);

INCLUDE_ASM("asm/nonmatchings/800c3", StopRCnt);

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

INCLUDE_ASM("asm/nonmatchings/800c3", func_8005D0D8);

INCLUDE_ASM("asm/nonmatchings/800c3", func_8005D0F8);

INCLUDE_ASM("asm/nonmatchings/800c3", func_8005D118);

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

INCLUDE_ASM("asm/nonmatchings/800c3", func_8005D244);

INCLUDE_ASM("asm/nonmatchings/800c3", func_8005D33C);

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

INCLUDE_ASM("asm/nonmatchings/800c3", func_8005D4F0);

INCLUDE_ASM("asm/nonmatchings/800c3", func_8005D538);

INCLUDE_ASM("asm/nonmatchings/800c3", func_8005D588);

INCLUDE_ASM("asm/nonmatchings/800c3", func_8005D6A0);

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

INCLUDE_ASM("asm/nonmatchings/800c3", func_8005D734);

INCLUDE_ASM("asm/nonmatchings/800c3", func_8005D8A0);

INCLUDE_ASM("asm/nonmatchings/800c3", func_8005D8B4);

INCLUDE_ASM("asm/nonmatchings/800c3", func_8005D980);

INCLUDE_ASM("asm/nonmatchings/800c3", func_8005D9C4);

INCLUDE_ASM("asm/nonmatchings/800c3", func_8005DBD8);

INCLUDE_ASM("asm/nonmatchings/800c3", func_8005DCA0);

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

INCLUDE_ASM("asm/nonmatchings/800c3", SysEnqIntRP);

INCLUDE_ASM("asm/nonmatchings/800c3", SysDeqIntRP);

INCLUDE_ASM("asm/nonmatchings/800c3", func_8005E188);

INCLUDE_ASM("asm/nonmatchings/800c3", func_8005E194);

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

INCLUDE_ASM("asm/nonmatchings/800c3", func_8005E804);


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

INCLUDE_ASM("asm/nonmatchings/800c3", func_8005E980);

INCLUDE_ASM("asm/nonmatchings/800c3", func_8005E9D4);

INCLUDE_ASM("asm/nonmatchings/800c3", func_8005EA34);

INCLUDE_ASM("asm/nonmatchings/800c3", func_8005EA54);

INCLUDE_ASM("asm/nonmatchings/800c3", func_8005EA68);

INCLUDE_ASM("asm/nonmatchings/800c3", func_8005EA88);

INCLUDE_ASM("asm/nonmatchings/800c3", func_8005EAA8);

INCLUDE_ASM("asm/nonmatchings/800c3", func_8005EAC8);

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

INCLUDE_ASM("asm/nonmatchings/800c3", func_8005EB28);

INCLUDE_ASM("asm/nonmatchings/800c3", func_8005EC00);

INCLUDE_ASM("asm/nonmatchings/800c3", func_8005ECC0);

INCLUDE_ASM("asm/nonmatchings/800c3", func_8005ED4C);

INCLUDE_ASM("asm/nonmatchings/800c3", func_8005F0C8);

INCLUDE_ASM("asm/nonmatchings/800c3", func_8005F228);

INCLUDE_ASM("asm/nonmatchings/800c3", func_8005F290);

INCLUDE_ASM("asm/nonmatchings/800c3", func_8005F384);

INCLUDE_ASM("asm/nonmatchings/800c3", func_8005F394);

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

INCLUDE_ASM("asm/nonmatchings/800c3", func_8005F728);


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

INCLUDE_ASM("asm/nonmatchings/800c3", func_8005FBA8);


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
