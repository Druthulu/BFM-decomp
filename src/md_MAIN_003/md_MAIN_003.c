#include "common.h"

extern void (*D_800D3598[])(void);

void func_800CEED0(void) {
    register s32 idx __asm__("$2");
    __asm__ __volatile__("" : : "r"(idx));
    D_800D3598[idx]();
}


#include "common.h"

extern u8 D_800B9A11;
extern s32 D_800EC694;
extern s32 D_800EC68C;
extern s16 D_800EC678;
extern s32 D_800EC67C;
extern s32 D_800EC680;
extern s32 D_800EC690;
extern s32 D_800EC698;
extern s32 D_800EC688;
extern s32 D_800EC684;
extern u8 D_800DA48C[];

extern void func_8001C044(void);
extern void func_80015310(void);
extern void func_8002D858(void);
extern s32 func_800D1E18(void);
extern void func_800CFB3C();
extern void func_800118AC(void);

void func_800CEF04(void) {
    D_800B9A11 = 1;
    func_8001C044();
    func_80015310();
    func_8002D858();
    D_800EC694 = 1;
    D_800EC68C = 0x80;
    D_800EC678 = 0;
    D_800EC67C = 0;
    D_800EC680 = 0;
    D_800EC690 = 0;
    D_800EC698 = 0;
    D_800EC688 = 0xFF;
    D_800EC684 = func_800D1E18();
    func_800CFB3C((s32) &D_800DA48C);
    func_800118AC();
    func_800118AC();
}


extern void func_8001A9F8(s32 a0);
extern s32 CdReadRequest(s32 *a0, void *a1, s32 a2, s32 a3);
extern s32 D_800AE858;
extern void func_80015310(void);
extern void func_800118AC(void);

void func_800CEFBC(void) {
    func_8001A9F8(0);
    if (CdReadRequest(&D_800AE858, (void *)0x80164E20, 0, 0)) {
        func_80015310();
        func_800118AC();
    }
}


extern s32 D_800EC684;
extern s32 D_800B9A18;
extern s32 D_800EC6A0;
extern s32 D_800EC6A4;
extern unsigned char D_800DA48C[];

extern void func_800D1E58(void);
extern void func_800CFFEC(void);
extern void func_800CFB3C();
extern void func_800118AC(void);

void func_800CF010(void) {
    if (D_800EC684 != 0) {
        func_800D1E58();
    }
    func_800CFFEC();
    D_800B9A18 = 0;
    D_800EC6A0 = 0;
    func_800CFB3C((s32)&D_800DA48C);
    D_800EC6A4 = 1;
    func_800118AC();
}


extern s32 D_800EC6A0;
extern s32 D_800EC6A4;
extern s32 D_800EC690;
extern u8 D_800DA48C[];
extern void func_800CF3E8(void);
extern s32 func_800CFC1C();
extern void func_800118AC(void);

void func_800CF078(void) {
    func_800CF3E8();
    if (D_800EC6A0 == 0) {
        if (func_800CFC1C(D_800DA48C) == 0) {
            D_800EC6A0 = 1;
        }
        if (D_800EC6A0 == 0) {
            return;
        }
    }
    if (D_800EC6A4 == 0) {
        return;
    }
    D_800EC690 = 1;
    func_800118AC();
}


INCLUDE_ASM("asm/md_MAIN_003/nonmatchings/md_MAIN_003", func_800CF104);

extern void func_800CF3E8(void);
extern void func_80059888(void *a0, s32 a1, s32 a2, s32 a3);
extern void func_800118AC(void);
extern s32 D_800EC68C;

void func_800CF300(void) {
    s16 sp10[4];

    func_800CF3E8();
    D_800EC68C -= 4;
    if (D_800EC68C < 0) {
        sp10[2] = 0x280;
        sp10[0] = 0;
        sp10[1] = 0;
        sp10[3] = 0x1E0;
        func_80059888(&sp10[0], 0, 0, 0);
        func_800118AC();
    }
}


extern void func_800146B0(s32);
extern void func_800118AC();
extern s32 D_800B9A18;

void func_800CF370(void) {
    func_800146B0(1);
    D_800B9A18 = 2;
    func_800118AC();
}


// Tier 1 (transcription) draft for func_800CF3A4 — md_MAIN_003
//
// NOTE ON TASK METADATA: the task handed to this agent claimed 437 instructions
// and pointed at .run/s46/snap_casc2/asm/md_MAIN_003/nonmatchings/md_MAIN_003/func_800CF3A4.s
// (a path that does not exist — that snapshot's md_MAIN_003 dir only contains
// func_800CF3E8.s and func_800D12D0.s). The live, in-tree, verified-immutable asm
// (asm/md_MAIN_003/nonmatchings/md_MAIN_003/func_800CF3A4.s) shows this function is
// genuinely tiny: "nonmatching func_800CF3A4, 0x44" — 0x44 bytes = 17 words including
// both delay-slot nops, i.e. 15 real instructions. This draft transcribes that real,
// on-disk function. See the STOPPING RULE report for the discrepancy.

extern s8 D_800D52BC[];
extern s32 D_800EC680;
extern u16 D_800B99E6;
extern u16 D_800B99E8;

extern void func_800183E0(s32 a0);

void func_800CF3A4(void) {
    func_800183E0((s32) &D_800D52BC);
    D_800B99E6 = 1;
    D_800B99E8 = (u16) D_800EC680;
}


INCLUDE_ASM("asm/md_MAIN_003/nonmatchings/md_MAIN_003", func_800CF3E8);

extern s32 D_800EC69C;
extern void func_800599B8();

void func_800CFB3C(u16 *arg0)
{
    register u16 *s1 __asm__("$17");
    register u16 *s0 __asm__("$16");
    register s32 fill __asm__("$18");
    register s32 i __asm__("$5");
    u16 sVar1;
    u16 buf[4];
    s32 pad[2];

    __asm__("" : "=r"(s1) : "0"(arg0));
    __asm__ volatile("" : : "r"(s1));
    sVar1 = *s1;
    D_800EC69C = 0;
    if (sVar1 != 0xFF) {
        fill = 0x7FFF;
        s0 = arg0 + 5;
        do {
            if (sVar1 == 9) {
                u16 *p = (u16 *)(*(s32 *)(s0 + 1) + *(s16 *)(s0 - 1) * 2);
                i = 0;
                if (*(s16 *)(s0 - 1) > 0) {
                    do {
                        *p = fill;
                        p++;
                        i++;
                    } while (i < *(s16 *)(s0 - 1));
                }
                {
                    s32 n;
                    s32 base;
                    s32 arg2;
                    n = *(s16 *)(s0 - 1);
                    base = *(s32 *)(s0 + 1);
                    buf[0] = s0[-3];
                    buf[1] = s0[-2];
                    buf[2] = s0[-1];
                    arg2 = base + n * 2;
                    buf[3] = s0[0];
                    func_800599B8(buf, arg2);
                }
            }
            s1 += 8;
            sVar1 = *s1;
            s0 += 8;
        } while (sVar1 != 0xFF);
    }
    (void)&pad;
}








extern void func_800599B8();

s32 func_800CFC1C(u16 *param_1)
{
    extern s32 D_800EC69C;

    u8 buf[0x10];
    register u16 *cursor __asm__("$18");
    register s32 uVar13 __asm__("$16");
    register u16 *psVar14 __asm__("$17");
    register s32 uVar16 __asm__("$19");
    register u32 mask __asm__("$20");
    register u16 *puVar9 __asm__("$11");
    register u16 *puVar10 __asm__("$12");
    register s32 iVar11 __asm__("$13");
    u16 tag;
    u32 result;
    u16 stored;
    s32 gate;
    register u32 acc __asm__("$2");
    register u32 uVar5 __asm__("$7");
    register u32 uVar7 __asm__("$6");
    register u32 uVar1 __asm__("$4");
    register u32 uVar6 __asm__("$3");
    register u32 uVar8 __asm__("$8");
    register u32 uVar3 __asm__("$10");

    cursor = param_1;
    uVar16 = 0;
    D_800EC69C = D_800EC69C + 1;
    gate = D_800EC69C < 2;
    if (gate) {
        return (u16 *)gate;
    }
    __asm__ __volatile__("" : "=r"(cursor) : "0"(cursor));
    tag = *(u16 *)cursor;
    D_800EC69C = 0;
    if (tag != 0xff) {
        mask = -0x8000;
        psVar14 = param_1 + 5;
        do {
            iVar11 = 0;
            if (tag == 9) {
                uVar13 = 0;
                puVar10 = *(u16 **)(psVar14 + 1);
                {
                    register s32 boff __asm__("$2") = (s32)((s16 *)psVar14)[-1] * 2;
                    register u16 *pi __asm__("$5");
                    pi = (u16 *)((s32)puVar10 + boff);
                    __asm__ __volatile__("" : "=r"(pi) : "0"(pi));
                    puVar9 = pi;
                }
                if (0 < (s32)((s16 *)psVar14)[-1]) {
                    do {
                        register u32 pix __asm__("$2");
                        register u32 out __asm__("$9");
                        pix = (u32)*puVar9;
                        out = (u32)*puVar10;
                        uVar5 = pix & 0x1f;
                        uVar7 = pix & 0x3e0;
                        uVar1 = pix & 0x7c00;
                        uVar6 = out & 0x1f;
                        uVar8 = out & 0x3e0;
                        uVar3 = out & 0x7c00;
                        if (uVar5 != uVar6) {
                            register s32 c __asm__("$2");
                            uVar13 = 1;
                            if ((s32)uVar5 < (s32)uVar6) uVar5 = uVar5 + 1;
                            c = (s32)uVar6 < (s32)uVar5;
                            if (c) uVar5 = uVar5 - 1;
                        }
                        if (uVar7 != uVar8) {
                            register s32 c __asm__("$2");
                            uVar13 = 1;
                            if ((s32)uVar7 < (s32)uVar8) uVar7 = uVar7 + 0x20;
                            c = (s32)uVar8 < (s32)uVar7;
                            if (c) uVar7 = uVar7 - 0x20;
                        }
                        if (uVar1 != uVar3) {
                            register s32 c __asm__("$2");
                            uVar13 = 1;
                            if ((s32)uVar1 < (s32)uVar3) uVar1 = uVar1 + 0x400;
                            c = (s32)uVar3 < (s32)uVar1;
                            if (c) uVar1 = uVar1 - 0x400;
                        }
                        acc = uVar5 | uVar7;
                        result = acc | uVar1 | (out & mask);
                        stored = result;
                        if ((stored & 0xFFFF) == 0 && out != 0) {
                            stored = result | 0x8000;
                        }
                        *puVar9 = stored;
                        puVar9 = puVar9 + 1;
                        iVar11 = iVar11 + 1;
                        puVar10 = puVar10 + 1;
                    } while (iVar11 < (s32)((s16 *)psVar14)[-1]);
                }
                if (uVar13 != 0) {
                    register u8 *argp __asm__("$4");
                    argp = buf;
                    *(u16 *)(buf + 0) = psVar14[-3];
                    __asm__ __volatile__("" ::: "memory");
                    *(u16 *)(buf + 2) = psVar14[-2];
                    __asm__ __volatile__("" ::: "memory");
                    *(u16 *)(buf + 4) = psVar14[-1];
                    __asm__ __volatile__("" ::: "memory");
                    *(u16 *)(buf + 6) = psVar14[0];
                    func_800599B8(argp);
                }
                uVar16 = uVar16 | uVar13;
            }
            cursor = cursor + 8;
            psVar14 = psVar14 + 8;
            tag = *(u16 *)cursor;
        } while (tag != 0xff);
    }
    return (u16 *)uVar16;
}


extern s16 D_800EC678;
extern void func_800599B8(u16 *, u16 *);

void func_800CFE00(void) {
    u16 sp10[8];
    u16 *addr1;
    u16 *addr2;
    s32 v;
    s32 t;

    v = D_800EC678;
    sp10[0] = 0;
    sp10[1] = 0x1E0;
    sp10[2] = 0x100;
    sp10[3] = 1;
    sp10[4] = 0x280;
    sp10[5] = 0x24;
    sp10[6] = 0x140;
    sp10[7] = 0x1B8;
    t = v << 4;
    t += v;
    t <<= 2;
    t += v;
    t <<= 3;
    t -= v;
    t <<= 4;
    t += v;
    t <<= 5;
    addr1 = (u16 *)(t + 0x80120014);
    addr2 = (u16 *)(t + 0x80120220);
    func_800599B8(sp10, addr1);
    func_800599B8(&sp10[4], addr2);
}


INCLUDE_ASM("asm/md_MAIN_003/nonmatchings/md_MAIN_003", func_800CFEB4);

extern u16 D_800AF7BC;
extern u16 D_800AF7BE;
extern u16 D_800AF7C0;
extern void GsInitGraph2(s32 w, s32 h, s32 mode, s32 a3, s32 st);
extern void func_80053EEC(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80059234(s32 a0);
extern void func_80053218(void);
extern void func_800147B8(void);
extern void func_80059888(void *a0, s32 a1, s32 a2, s32 a3);
extern u8 D_800AF6DC;
extern u8 D_800AF680;

void func_800CFFEC(void) {
    s16 sp18[4];
    s16 sp20[4];
    s16 sp28[4];

    D_800AF7BC = 0x280;
    D_800AF7BE = 0x1E0;
    D_800AF7C0 = 1;
    GsInitGraph2(0x280, 0x1E0, 5, 0, 0);
    func_80053EEC(0, 0, 0, 0);
    func_80059234(1);
    func_80053218();
    func_800147B8();

    sp18[0] = 0;
    sp18[1] = 0;
    sp18[2] = 0x280;
    sp18[3] = 0x14;
    func_80059888(sp18, 0, 0, 0);

    sp20[0] = 0;
    sp20[1] = 0x14;
    sp20[2] = 0x280;
    sp20[3] = 0x1B8;
    func_80059888(sp20, 0xFF, 0xFF, 0xFF);

    sp28[0] = 0;
    sp28[1] = 0x1CC;
    sp28[2] = 0x280;
    sp28[3] = 0x14;
    func_80059888(sp28, 0, 0, 0);

    D_800AF6DC = 0;
    D_800AF680 = 0;
}


INCLUDE_ASM("asm/md_MAIN_003/nonmatchings/md_MAIN_003", func_800D0100);

__asm__(".text\n.align 2\n.globl func_800D0174\n.ent\tfunc_800D0174\n"
"func_800D0174:\n.frame $sp,32,$31\n.mask 0xC0010000,-16\n.fmask 0,0\n"
".set\tnoreorder\n"
"addiu $sp, $sp, -32\n"
"sw $ra, 24($sp)\n"
"sw $fp, 20($sp)\n"
"sw $s0, 16($sp)\n"
"addu $fp, $sp, $zero\n"
"lui $s0, %hi(D_800AF630)\n"
"addiu $s0, $s0, %lo(D_800AF630)\n"
"addiu $v0, $zero, 1\n"
"lui $at, 1\n"
"addu $at, $s0, $at\n"
"sb $v0, -23583($at)\n"
"jal func_8001C044\n"
"nop\n"
"jal func_80015310\n"
"nop\n"
"jal func_8002D858\n"
"nop\n"
"lui $a0, %hi(D_800D93FC)\n"
"addiu $a0, $a0, %lo(D_800D93FC)\n"
"jal func_800183E0\n"
"nop\n"
"lui $at, %hi(D_800EC894)\n"
"sh $zero, %lo(D_800EC894)($at)\n"
"jal func_800D1E18\n"
"nop\n"
"lui $at, %hi(D_800EC8B0)\n"
"sw $v0, %lo(D_800EC8B0)($at)\n"
"jal func_800118AC\n"
"nop\n"
"addu $sp, $fp, $zero\n"
"lw $ra, 24($sp)\n"
"lw $fp, 20($sp)\n"
"lw $s0, 16($sp)\n"
"addiu $sp, $sp, 32\n"
"jr $ra\n"
"nop\n"
".set\treorder\n.end\tfunc_800D0174\n");


INCLUDE_ASM("asm/md_MAIN_003/nonmatchings/md_MAIN_003", func_800D0204);

INCLUDE_ASM("asm/md_MAIN_003/nonmatchings/md_MAIN_003", func_800D0268);

__asm__(".text\n.align 2\n.globl func_800D0440\n.ent\tfunc_800D0440\n"
"func_800D0440:\n.frame $sp,40,$31\n.mask 0xC0010000,-16\n.fmask 0,0\n"
".set\tnoreorder\n"
"addiu $sp, $sp, -40\n"
"sw $ra, 32($sp)\n"
"sw $fp, 28($sp)\n"
"sw $s0, 24($sp)\n"
"addu $fp, $sp, $zero\n"
"lui $s0, %hi(D_800AF630)\n"
"addiu $s0, $s0, %lo(D_800AF630)\n"
"addiu $a0, $zero, 4\n"
"jal func_800167F0\n"
"nop\n"
"andi $v1, $v0, 65535\n"
"beqz $v1, .L800D0590\n"
"nop\n"
"lui $v0, %hi(D_800EC894)\n"
"lh $v0, %lo(D_800EC894)($v0)\n"
"addiu $v1, $zero, 1\n"
"beq $v0, $v1, .L800D04EC\n"
"nop\n"
"slti $v1, $v0, 2\n"
"beqz $v1, .L800D04A4\n"
"nop\n"
"beqz $v0, .L800D04C4\n"
"nop\n"
"j .L800D0560\n"
"nop\n"
".L800D04A4:\n"
"addiu $v1, $zero, 2\n"
"beq $v0, $v1, .L800D0510\n"
"nop\n"
"addiu $v1, $zero, 4\n"
"beq $v0, $v1, .L800D0538\n"
"nop\n"
"j .L800D0560\n"
"nop\n"
".L800D04C4:\n"
"addiu $v0, $zero, 1\n"
"lui $at, 1\n"
"addu $at, $s0, $at\n"
"sh $v0, -23626($at)\n"
"addiu $v0, $zero, 2\n"
"lui $at, 1\n"
"addu $at, $s0, $at\n"
"sh $v0, -23624($at)\n"
"j .L800D0560\n"
"nop\n"
".L800D04EC:\n"
"addiu $v0, $zero, 1\n"
"lui $at, 1\n"
"addu $at, $s0, $at\n"
"sh $v0, -23626($at)\n"
"lui $at, 1\n"
"addu $at, $s0, $at\n"
"sh $zero, -23624($at)\n"
"j .L800D0560\n"
"nop\n"
".L800D0510:\n"
"addiu $v0, $zero, 1\n"
"lui $at, 1\n"
"addu $at, $s0, $at\n"
"sh $v0, -23626($at)\n"
"addiu $v0, $zero, 1\n"
"lui $at, 1\n"
"addu $at, $s0, $at\n"
"sh $v0, -23624($at)\n"
"j .L800D0560\n"
"nop\n"
".L800D0538:\n"
"addiu $v0, $zero, 1\n"
"lui $at, 1\n"
"addu $at, $s0, $at\n"
"sh $v0, -23626($at)\n"
"addiu $v0, $zero, 4\n"
"lui $at, 1\n"
"addu $at, $s0, $at\n"
"sh $v0, -23624($at)\n"
"j .L800D0560\n"
"nop\n"
".L800D0560:\n"
"sh $zero, 16($fp)\n"
"sh $zero, 18($fp)\n"
"addiu $v0, $zero, 320\n"
"sh $v0, 20($fp)\n"
"addiu $v0, $zero, 480\n"
"sh $v0, 22($fp)\n"
"addiu $a0, $fp, 16\n"
"addu $a1, $zero, $zero\n"
"addu $a2, $zero, $zero\n"
"addu $a3, $zero, $zero\n"
"jal func_80059888\n"
"nop\n"
".L800D0590:\n"
"jal func_800D0D6C\n"
"nop\n"
"addu $sp, $fp, $zero\n"
"lw $ra, 32($sp)\n"
"lw $fp, 28($sp)\n"
"lw $s0, 24($sp)\n"
"addiu $sp, $sp, 40\n"
"jr $ra\n"
"nop\n"
".set\treorder\n.end\tfunc_800D0440\n");


INCLUDE_ASM("asm/md_MAIN_003/nonmatchings/md_MAIN_003", func_800D05B4);

INCLUDE_ASM("asm/md_MAIN_003/nonmatchings/md_MAIN_003", func_800D0664);

INCLUDE_ASM("asm/md_MAIN_003/nonmatchings/md_MAIN_003", func_800D06BC);

INCLUDE_ASM("asm/md_MAIN_003/nonmatchings/md_MAIN_003", func_800D0740);

__asm__(".text\n.align 2\n.globl func_800D09A0\n.ent\tfunc_800D09A0\n"
"func_800D09A0:\n.frame $sp,32,$31\n.mask 0xC0010000,-16\n.fmask 0,0\n"
".set\tnoreorder\n"
"addiu $sp, $sp, -32\n"
"sw $ra, 24($sp)\n"
"sw $fp, 20($sp)\n"
"sw $s0, 16($sp)\n"
"addu $fp, $sp, $zero\n"
"lui $s0, %hi(D_800AF630)\n"
"addiu $s0, $s0, %lo(D_800AF630)\n"
"jal func_800D12D0\n"
"nop\n"
"lui $v0, %hi(D_800EC898)\n"
"lhu $v0, %lo(D_800EC898)($v0)\n"
"nop\n"
"addiu $v1, $v0, 1\n"
"addu $v0, $v1, $zero\n"
"lui $at, %hi(D_800EC898)\n"
"sh $v0, %lo(D_800EC898)($at)\n"
"lui $v0, %hi(D_800EC898)\n"
"lhu $v0, %lo(D_800EC898)($v0)\n"
"nop\n"
"andi $v1, $v0, 4\n"
"sll $a0, $v1, 16\n"
"sra $v0, $a0, 16\n"
"beqz $v0, .L800D0A24\n"
"nop\n"
"lui $v0, %hi(D_800EC894)\n"
"lh $v0, %lo(D_800EC894)($v0)\n"
"nop\n"
"addu $a0, $v0, $zero\n"
"addiu $a1, $zero, 1\n"
"jal func_800D1D14\n"
"nop\n"
"j .L800D0A40\n"
"nop\n"
".L800D0A24:\n"
"lui $v0, %hi(D_800EC894)\n"
"lh $v0, %lo(D_800EC894)($v0)\n"
"nop\n"
"addu $a0, $v0, $zero\n"
"addu $a1, $zero, $zero\n"
"jal func_800D1D14\n"
"nop\n"
".L800D0A40:\n"
"lui $v0, %hi(D_800EC898)\n"
"lh $v0, %lo(D_800EC898)($v0)\n"
"nop\n"
"slti $v1, $v0, 33\n"
"bnez $v1, .L800D0A60\n"
"nop\n"
"jal func_800118AC\n"
"nop\n"
".L800D0A60:\n"
"addu $sp, $fp, $zero\n"
"lw $ra, 24($sp)\n"
"lw $fp, 20($sp)\n"
"lw $s0, 16($sp)\n"
"addiu $sp, $sp, 32\n"
"jr $ra\n"
"nop\n"
".set\treorder\n.end\tfunc_800D09A0\n");


INCLUDE_ASM("asm/md_MAIN_003/nonmatchings/md_MAIN_003", func_800D0A7C);

INCLUDE_ASM("asm/md_MAIN_003/nonmatchings/md_MAIN_003", func_800D0B1C);

INCLUDE_ASM("asm/md_MAIN_003/nonmatchings/md_MAIN_003", func_800D0C50);

INCLUDE_ASM("asm/md_MAIN_003/nonmatchings/md_MAIN_003", func_800D0D6C);

INCLUDE_ASM("asm/md_MAIN_003/nonmatchings/md_MAIN_003", func_800D12D0);

__asm__(".text\n.align 2\n.globl func_800D1D14\n.ent\tfunc_800D1D14\n"
"func_800D1D14:\n.frame $sp,32,$31\n.mask 0xC0010000,-16\n.fmask 0,0\n"
".set\tnoreorder\n"
"addiu $sp, $sp, -32\n"
"sw $ra, 28($sp)\n"
"sw $fp, 24($sp)\n"
"addu $fp, $sp, $zero\n"
"sw $a0, 32($fp)\n"
"sw $a1, 36($fp)\n"
"lw $v0, 36($fp)\n"
"nop\n"
"bnez $v0, .L800D1D88\n"
"nop\n"
"lw $v0, 32($fp)\n"
"nop\n"
"addu $v1, $v0, $zero\n"
"sll $v0, $v1, 2\n"
"lui $a0, %hi(D_800D3630)\n"
"addiu $a0, $a0, %lo(D_800D3630)\n"
"addu $v1, $v0, $a0\n"
"lh $v0, 0($v1)\n"
"sw $zero, 16($sp)\n"
"sw $zero, 20($sp)\n"
"addu $a0, $v0, $zero\n"
"lui $a1, %hi(D_800D3618)\n"
"addiu $a1, $a1, %lo(D_800D3618)\n"
"addu $a2, $zero, $zero\n"
"addu $a3, $zero, $zero\n"
"jal func_8001534C\n"
"nop\n"
"j .L800D1E00\n"
"nop\n"
".L800D1D88:\n"
"lw $v0, 32($fp)\n"
"nop\n"
"addu $v1, $v0, $zero\n"
"sll $v0, $v1, 2\n"
"lui $a0, %hi(D_800D3630)\n"
"addiu $a0, $a0, %lo(D_800D3630)\n"
"addu $v1, $v0, $a0\n"
"lh $v0, 0($v1)\n"
"lw $v1, 32($fp)\n"
"nop\n"
"addu $a0, $v1, $zero\n"
"sll $v1, $a0, 2\n"
"lui $a0, %hi(D_800D3624)\n"
"addiu $a0, $a0, %lo(D_800D3624)\n"
"addu $v1, $v1, $a0\n"
"lw $a0, 32($fp)\n"
"lui $a1, %hi(D_800D3620)\n"
"addiu $a1, $a1, %lo(D_800D3620)\n"
"addu $a0, $a0, $a1\n"
"lbu $a1, 0($a0)\n"
"nop\n"
"sll $a0, $a1, 16\n"
"sra $a3, $a0, 16\n"
"sw $zero, 16($sp)\n"
"sw $zero, 20($sp)\n"
"addu $a0, $v0, $zero\n"
"lw $a1, 0($v1)\n"
"addiu $a2, $zero, 80\n"
"jal func_8001534C\n"
"nop\n"
".L800D1E00:\n"
"addu $sp, $fp, $zero\n"
"lw $ra, 28($sp)\n"
"lw $fp, 24($sp)\n"
"addiu $sp, $sp, 32\n"
"jr $ra\n"
"nop\n"
".set\treorder\n.end\tfunc_800D1D14\n");


typedef struct {
    s32 unk00; /* +0x00 */
    s32 unk04; /* +0x04 */
    s32 unk08; /* +0x08 */
    s32 unk0C; /* +0x0C */
    s32 unk10; /* +0x10 */
    s32 unk14; /* +0x14 */
    s32 unk18; /* +0x18 */
    s32 unk1C; /* +0x1C */
} D_800D942C_entry; /* 0x20 bytes */

extern D_800D942C_entry D_800D942C[];
extern u8 D_800EC9FC[];

extern s32 func_8001BFA0(void);
extern s32 CdSearchFile(void *fp, void *name);

s32 func_800D1E18(void) {
    return CdSearchFile(D_800EC9FC, (void *) D_800D942C[func_8001BFA0()].unk00) != 0;
}




extern D_800D942C_entry D_800D942C[];
extern s32 D_800EC9E0;
extern void func_800D1E9C(void *arg0);
extern void func_8001BFB0(void);

void func_800D1E58(void) {
    D_800EC9E0 = 0;
    func_800D1E9C(&D_800D942C[func_8001BFA0()]);
    func_8001BFB0();
}


INCLUDE_ASM("asm/md_MAIN_003/nonmatchings/md_MAIN_003", func_800D1E9C);

extern s32 D_800D9470;
extern s32 D_800D9474;
extern s32 D_800D9478;
extern s32 D_800D947C;
extern s32 D_800D9480;

typedef struct S_D2394 {
    s32 f0;
    s32 f4;
    s32 f8;
    s32 fC;
    s32 f10;
    s32 f14;
    s16 f18;
    s16 f1A;
    s16 f1C;
    s16 f1E;
    s16 f20;
    s16 f22;
    s16 f24;
    s16 f26;
    s32 f28;
    s16 f2C;
    s16 f2E;
    s16 f30;
    s16 f32;
    s32 f34;
    s32 f38;
} S_D2394;

typedef struct S_D2394B {
    s32 f0;
    s32 f4;
} S_D2394B;

void func_800D2394(S_D2394 *t, s16 a1, s16 a2, s16 a3, s32 a4, S_D2394B *a5) {
    if (D_800D9480 == 1) {
        t->f8 = 0;
        t->f14 = 0;
        t->f28 = 0;
        t->f34 = 0;
        D_800D9480 = 0;
        t->f0 = D_800D9470;
        t->f4 = D_800D9474;
        t->fC = D_800D9478;
        t->f10 = D_800D947C;
    }
    t->f18 = a1;
    t->f1A = a2;
    t->f20 = a3;
    t->f22 = a4;
    t->f30 = (a5->f4 != 0) ? 0x18 : 0x10;
    t->f38 = a5->f4;
    if (t->f28 == 0) {
        t->f2C = a1;
        t->f2E = a2;
    } else {
        t->f2C = a3;
        t->f2E = a4;
    }
}


#include "common.h"

extern void func_800D2AA0();
extern void func_800D2D44();
extern void StSetRing(s32 a0, s32 a1);
extern void StSetStream();
extern s32 D_800D946C;
extern void func_800D2A24();

void func_800D2454(s32 a0, s32 a1, s32 *a2) {
    func_800D2AA0(0);
    func_800D2D44(a1);
    StSetRing(D_800D946C, 0x20);
    StSetStream(a2[1], a2[2], -1, 0, 0);
    func_800D2A24(a0);
}


INCLUDE_ASM("asm/md_MAIN_003/nonmatchings/md_MAIN_003", func_800D24D0);

extern s32 func_800D27A0();
extern void func_800D3234(s32 a0, s32 a1);
extern void StFreeRing(s32 a0);

s32 func_800D2704(s32 a0, s32 a1) {
    s32 *ptr;
    s32 cnt;
    s32 ring;
    s32 a1s;
    ptr = (s32 *)a0;
    a1s = a1;
    cnt = 0x20;
    do {
        ring = func_800D27A0((s32)ptr, a1s);
        if (ring == 0) {
            cnt--;
        } else {
            ptr[2] = (ptr[2] == 0);
            func_800D3234(ring, ptr[ptr[2]]);
            StFreeRing(ring);
            return 0;
        }
    } while (cnt != 0);
    return 1;
}


extern s32 D_800EC9F4;
extern s32 D_800EC9F8;
extern s32 D_800D9484;
extern s32 D_800D9488;

struct UnkS1 { s32 pad0; s32 f4; s32 pad8; s32 fC; s32 pad10; s32 pad14; s32 f18; u32 f1C; };

s32 func_800D27A0(void* arg0, struct UnkS1* arg1) {
    s32 sp10[2];
    u16 sp18[4];
    s32 ret;
    s32 i;

    for (i = 0x8000; i != 0; i--) {
        if (StGetNext(&sp10[0], &sp10[1]) == 0) {
            goto found;
        }
    }
    return 0;
found:
    if (*(u32*)(sp10[1] + 8) >= arg1->fC) {
        D_800EC9F4 = 1;
    }
    if (*(u32*)(sp10[1] + 8) >= arg1->fC - 15) {
        D_800EC9F8 = 1;
    } else {
        D_800EC9F8 = 0;
    }
    if (D_800D9484 != *(u16*)(sp10[1] + 0x10) || D_800D9488 != *(u16*)(sp10[1] + 0x12)) {
        u16 cur1;
        u16 cur2;
        sp18[0] = 0;
        sp18[1] = 0;
        sp18[2] = arg1->f4 != 0 ? (arg1->f18 * 3) / 2 : *(u16*)&arg1->f18;
        sp18[3] = arg1->f1C * 2;
        if (arg1->f4 != 0) {
            func_80059888(sp18, 0, 0, 0);
        } else {
            func_80059888(sp18, 0x40, 0x40, 0x40);
        }
        cur1 = *(u16*)(sp10[1] + 0x10);
        cur2 = *(u16*)(sp10[1] + 0x12);
        D_800D9484 = cur1;
        D_800D9488 = cur2;
    }
    {
        u16 t = arg1->f4 != 0 ? (D_800D9484 * 3) / 2 : *(u16*)&D_800D9484;
        u16 g;
        ret = sp10[0];
        g = *(u16*)&D_800D9488;
        *(u16*)(arg0 + 0x24) = t;
        *(u16*)(arg0 + 0x1C) = t;
        *(u16*)(arg0 + 0x26) = g;
        *(u16*)(arg0 + 0x1E) = g;
        *(u16*)(arg0 + 0x32) = g;
    }
    return ret;
}


typedef struct {
    s8 pad00[0x18];
    u16 u18[2];
    s8 pad1C[0xC];
    s32 f28;
    u16 u2C;
    u16 u2E;
    s32 pad30;
    s32 f34;
} St;

void func_800D298C(St *a0) {
    volatile s32 cnt;
    s32 flag;
    s32 cond;
    s32 t;

    cond = a0->f34;
    cnt = 0x8000;
    if (cond == 0) {
        flag = 1;
        do {
            cnt = cnt - 1;
            if (cnt == 0) {
                t = a0->f28;
                a0->f34 = flag;
                a0->f28 = (t == 0);
                a0->u2C = *(u16 *)((s8 *)a0 + (a0->f28 << 3) + 0x18);
                a0->u2E = *(u16 *)((s8 *)a0 + (a0->f28 << 3) + 0x1A);
            }
        } while (a0->f34 == 0);
    }
    a0->f34 = 0;
}


INCLUDE_ASM("asm/md_MAIN_003/nonmatchings/md_MAIN_003", func_800D2A24);

void func_800D2AA0(u8 *a0) {
    if (a0 == 0) {
        ResetCallback();
    }
    func_800D2D68(a0);
}


extern s32 D_800DB530[];
extern s32 D_800DB570[];
extern s32 D_800DB5B4[];

void *func_800D2AD8(void *a0) {
    s32 i;
    s32 *d;
    s32 *s;

    d = (s32 *) a0;
    s = D_800DB530;
    for (i = 15; i != -1; i--) {
        *d++ = *s++;
    }
    d = (s32 *) ((s32) a0 + 0x40);
    s = D_800DB570;
    for (i = 15; i != -1; i--) {
        *d++ = *s++;
    }
    d = (s32 *) ((s32) a0 + 0x80);
    s = D_800DB5B4;
    for (i = 31; i != -1; i--) {
        *d++ = *s++;
    }
    return a0;
}


extern s32 D_800DB530[];
extern s32 D_800DB570[];
extern s32 D_800DB52C;
extern s32 D_800DB5B0;

extern void func_800D2E64();

void *func_800D2B64(void *arg0) {
    register void *base asm("$16");
    s32 *dst;
    s32 i;

    base = arg0;

    dst = D_800DB530;
    i = 15;
    do {
        *dst++ = *(s32 *) arg0;
        arg0 = (char *) arg0 + 4;
    } while (--i != -1);

    dst = D_800DB570;
    arg0 = (char *) base + 0x40;
    i = 15;
    do {
        *dst++ = *(s32 *) arg0;
        arg0 = (char *) arg0 + 4;
    } while (--i != -1);

    func_800D2E64((s32) &D_800DB52C, 0x20);
    func_800D2E64((s32) &D_800DB5B0, 0x20);
    return base;
}


u16 func_800D2C00(s32 *a0) {
    return *(u16*)((s32)a0 + 0x0);
}


extern void func_800D2E64();

void func_800D2C0C(s32 *a0, s32 a1) {
    if (a1 & 1) {
        *a0 &= 0xF7FFFFFF;
    } else {
        *a0 |= 0x8000000;
    }
    if (a1 & 2) {
        *a0 |= 0x2000000;
    } else {
        *a0 &= 0xFDFFFFFF;
    }
    func_800D2E64(a0, *(u16 *)a0);
}


extern void func_800D2EF8();
void func_800D2C88(void) {
    func_800D2EF8();
}


extern void func_800D2F88(s32 a0, s32 a1);
extern s32 func_800D30B8(void);

s32 func_800D2CA8(s32 a0, s32 a1) {
    s32 var;
    if (a0 == 0) {
        var = ((s32 (*)())func_800D2F88)();
    } else {
        var = (((u32 (*)(void))func_800D30B8)() >> 29) & 1;
    }
    return var;
}


extern u32 func_800D3020();
extern s32 func_800D30B8(void);

s32 func_800D2CE4(s32 *a0) {
    if (a0 != 0) {
        return (((u32 (*)(void))func_800D30B8)() >> 24) & 1;
    } else {
        return func_800D3020();
    }
}


extern void DMACallback(s32, s32);

void func_800D2D20(s32 a0) {
    DMACallback(0, a0);
}


extern void DMACallback(s32 chan, s32 addr);

void func_800D2D44(s32 arg0) {
    DMACallback(1, arg0);
}


INCLUDE_RODATA("asm/md_MAIN_003/nonmatchings/md_MAIN_003", D_800CEDF8);

__asm__(
    ".section .rodata\n"
    ".align 2\n"
    ".globl D_800CEE1C\n"
    "D_800CEE1C:\n"
    ".asciz \"MDEC_rest:bad option(%d)\\n\"\n"
    ".align 2\n"
    ".section .text\n"
);

extern void func_800D2E64();
extern void func_8005C604();
extern volatile s32 *aD800DB670 __asm__("D_800DB670");
extern volatile s32 *aD800DB644 __asm__("D_800DB644");
extern volatile s32 *aD800DB650 __asm__("D_800DB650");
extern s32 D_800DB52C;
extern s32 D_800DB5B0;
extern char D_800CEE1C[];

void func_800D2D68(s32 arg0) {
    s32 dummy;
    switch (arg0) {
    case 0:
        *aD800DB670 = 0x80000000;
        *aD800DB644 = 0;
        *aD800DB650 = 0;
        *aD800DB670 = 0x60000000;
        func_800D2E64((s32)&D_800DB52C, 0x20);
        func_800D2E64((s32)&D_800DB5B0, 0x20);
        break;
    case 1:
        *aD800DB670 = 0x80000000;
        *aD800DB644 = 0;
        *aD800DB650 = 0;
        dummy = *aD800DB650;
        *aD800DB670 = 0x60000000;
        break;
    default:
        func_8005C604(D_800CEE1C, arg0);
        break;
    }
}


extern s32 *D_800DB674;
extern s32 *D_800DB63C;
extern s32 *D_800DB640;
extern s32 *D_800DB66C;
extern s32 *D_800DB644;
extern void func_800D2F88(s32 a0, s32 a1);

void func_800D2E64(s32 a0, s32 a1) {
    u32 s0;
    s32 s1;
    s1 = a0;
    s0 = (u32)a1;
    func_800D2F88(a0, a1);
    s0 = (s0 >> 5) << 16;
    *D_800DB674 |= 0x88;
    *D_800DB63C = s1 + 4;
    *D_800DB640 = s0 | 0x20;
    *D_800DB66C = *(s32 *)s1;
    *D_800DB644 = 0x1000201;
}


extern s32 *D_800DB674;
extern s32 *D_800DB650;
extern s32 *D_800DB648;
extern s32 *D_800DB64C;
extern u32 func_800D3020();

void func_800D2EF8(s32 a0, s32 a1) {
    s32 s1;
    u32 s0;
    s1 = a0;
    s0 = (u32)a1;
    func_800D3020();
    s0 >>= 5;
    *D_800DB674 |= 0x88;
    *D_800DB650 = 0;
    *D_800DB648 = s1;
    *D_800DB64C = (s32)(s0 << 16) | 0x20;
    *D_800DB650 = 0x1000200;
}


extern s32 *D_800DB670;
extern void func_800D30D0(char *a0);

u32 aF800D2F88(void) __asm__("func_800D2F88");
u32 aF800D2F88(void)
{
    volatile int count = 0x100000;
    while (*(*(u32 **)&D_800DB670) & 0x20000000) {
        if (--count == -1) {
            func_800D30D0("MDEC_in_sync");
            return -1;
        }
    }
    return 0;
}


extern s32 *D_800DB650;
extern void func_800D30D0(char *a0);

u32 func_800D3020(void)
{
    volatile int count = 0x100000;
    while (*(*(u32 * *)&D_800DB650) & 0x1000000) {
        if (--count == -1) {
            func_800D30D0("MDEC_out_sync");
            return -1;
        }
    }
    return 0;
}


extern s32 *D_800DB670;
s32 func_800D30B8(void) {
    return *D_800DB670;
}


INCLUDE_ASM("asm/md_MAIN_003/nonmatchings/md_MAIN_003", func_800D30D0);

INCLUDE_ASM("asm/md_MAIN_003/nonmatchings/md_MAIN_003", D_800D3200);

extern s32 D_800D3200;  /* dup-def demoted: a sibling .s still emits it (S61) */

__asm__(".text\n.align 2\n.globl func_800D3204\n.ent\tfunc_800D3204\n"
"func_800D3204:\n.frame $sp,0,$31\n.mask 0x00000000,0\n.fmask 0,0\n"
".set\tnoreorder\n.set\tnoat\n"
"lui $t0, %hi(D_800D3200)\n"
"addiu $t0, $t0, %lo(D_800D3200)\n"
"addi $at, $a0, -1\n"
"blez $at, .L800D3224\n"
"lw $v0, 0($t0)\n"
"sll $at, $a0, 1\n"
"jr $ra\n"
"sw $at, 0($t0)\n"
".L800D3224:\n"
"lui $at, (0xFFFFFF >> 16)\n"
"ori $at, $at, (0xFFFFFF & 0xFFFF)\n"
"jr $ra\n"
"sw $at, 0($t0)\n"
".end func_800D3204\n");


__asm__(
    ".set\tnoreorder\n"
    ".set\tnoat\n"
    ".section\t.text\n"
    ".align\t2\n"
    ".globl\tfunc_800D3234\n"
    ".type\tfunc_800D3234, @function\n"
    ".ent\tfunc_800D3234\n"
    "func_800D3234:\n"
    "lui $t0, %hi(D_800D3200)\n"
    "addiu $t0, $t0, %lo(D_800D3200)\n"
    "lui $a2, %hi(D_800DBE78)\n"
    "addiu $a2, $a2, %lo(D_800DBE78)\n"
    "lui $a3, %hi(D_800EBE78)\n"
    "addiu $a3, $a3, %lo(D_800EBE78)\n"
    "bnez $a0, .L800D328C\n"
    "lw $t1, 0($t0)\n"
    "lui $t0, %hi(D_800D3574)\n"
    "addiu $t0, $t0, %lo(D_800D3574)\n"
    "lw $a0, 0($t0)\n"
    "lw $a1, 4($t0)\n"
    "lw $v0, 8($t0)\n"
    "lw $v1, 12($t0)\n"
    "lw $t4, 16($t0)\n"
    "lw $t5, 20($t0)\n"
    "lw $t7, 24($t0)\n"
    "lw $t8, 28($t0)\n"
    "lw $t9, 32($t0)\n"
    "add $t1, $t1, $t1\n"
    "bgez $zero, .L800D3404\n"
    "add $t6, $a1, $t1\n"
    ".L800D328C:\n"
    "add $t5, $zero, $zero\n"
    "add $t7, $zero, $zero\n"
    "add $t8, $zero, $zero\n"
    "add $t9, $zero, $zero\n"
    "add $t1, $t1, $t1\n"
    "add $t6, $a1, $t1\n"
    "lhu $t0, 0($a0)\n"
    "lhu $t1, 2($a0)\n"
    "lhu $t4, 4($a0)\n"
    "lhu $t2, 6($a0)\n"
    "lhu $v0, 8($a0)\n"
    "lhu $v1, 10($a0)\n"
    "addi $t2, $t2, -3\n"
    "bltz $t2, .L800D32CC\n"
    "sll $t4, $t4, 10\n"
    "addi $t5, $zero, 1\n"
    ".L800D32CC:\n"
    "addi $a0, $a0, 12\n"
    "sll $v0, $v0, 16\n"
    "or $v0, $v0, $v1\n"
    "or $v1, $zero, $zero\n"
    "sh $t0, 0($a1)\n"
    "sh $t1, 2($a1)\n"
    "addi $a1, $a1, 2\n"
    ".L800D32E8:\n"
    "beqz $t5, .L800D33C0\n"
    "srl $t0, $v0, 22\n"
    "xori $at, $t0, 1023\n"
    "beqz $at, .L800D350C\n"
    "addi $a1, $a1, 2\n"
    "addi $at, $t5, -3\n"
    "bltz $at, .L800D330C\n"
    "addi $at, $a2, -1024\n"
    "addi $at, $at, -1024\n"
    ".L800D330C:\n"
    "srl $t0, $v0, 24\n"
    "sll $t0, $t0, 2\n"
    "add $t0, $t0, $at\n"
    "lhu $t1, 0($t0)\n"
    "lhu $t2, 2($t0)\n"
    "and $t0, $zero, $zero\n"
    "beqz $t2, .L800D3350\n"
    "sllv $v0, $v0, $t1\n"
    "addi $at, $zero, 32\n"
    "sub $at, $at, $t2\n"
    "srlv $t0, $v0, $at\n"
    "bltz $v0, .L800D334C\n"
    "sllv $v0, $v0, $t2\n"
    "addi $t3, $zero, -1\n"
    "srlv $t3, $t3, $at\n"
    "sub $t0, $t0, $t3\n"
    ".L800D334C:\n"
    "add $v1, $v1, $t2\n"
    ".L800D3350:\n"
    "add $v1, $v1, $t1\n"
    "andi $at, $v1, 16\n"
    "beqz $at, .L800D3370\n"
    "andi $v1, $v1, 15\n"
    "lhu $t1, 0($a0)\n"
    "addi $a0, $a0, 2\n"
    "sllv $t1, $t1, $v1\n"
    "or $v0, $v0, $t1\n"
    ".L800D3370:\n"
    "addi $at, $t5, -2\n"
    "bgtz $at, .L800D3398\n"
    "add $t1, $t9, $t0\n"
    "beqz $at, .L800D3390\n"
    "add $t1, $t8, $t0\n"
    "add $t1, $t7, $t0\n"
    "bgez $zero, .L800D339C\n"
    "add $t7, $t7, $t0\n"
    ".L800D3390:\n"
    "bgez $zero, .L800D339C\n"
    "add $t8, $t8, $t0\n"
    ".L800D3398:\n"
    "add $t9, $t9, $t0\n"
    ".L800D339C:\n"
    "sll $t1, $t1, 2\n"
    "andi $t1, $t1, 1023\n"
    "or $t1, $t4, $t1\n"
    "addi $t5, $t5, 1\n"
    "addi $at, $t5, -7\n"
    "bnez $at, .L800D33F8\n"
    "sh $t1, 0($a1)\n"
    "bgez $zero, .L800D33F8\n"
    "addi $t5, $t5, -6\n"
    ".L800D33C0:\n"
    "xori $at, $t0, 511\n"
    "beqz $at, .L800D350C\n"
    "addi $a1, $a1, 2\n"
    "sll $v0, $v0, 10\n"
    "addi $v1, $v1, 10\n"
    "andi $at, $v1, 16\n"
    "beqz $at, .L800D33F0\n"
    "andi $v1, $v1, 15\n"
    "lhu $t1, 0($a0)\n"
    "addi $a0, $a0, 2\n"
    "sllv $t1, $t1, $v1\n"
    "or $v0, $v0, $t1\n"
    ".L800D33F0:\n"
    "or $t0, $t4, $t0\n"
    "sh $t0, 0($a1)\n"
    ".L800D33F8:\n"
    "subu $at, $a1, $t6\n"
    "bgez $at, .L800D3540\n"
    "addi $a1, $a1, 2\n"
    ".L800D3404:\n"
    "srl $t0, $v0, 19\n"
    "sll $t0, $t0, 3\n"
    "add $t0, $t0, $a2\n"
    "lw $t1, 0($t0)\n"
    "nop\n"
    "bnez $t1, .L800D3460\n"
    "andi $at, $t1, 255\n"
    "sll $v0, $v0, 8\n"
    "addi $v1, $v1, 8\n"
    "andi $at, $v1, 16\n"
    "beqz $at, .L800D3444\n"
    "andi $v1, $v1, 15\n"
    "lhu $t0, 0($a0)\n"
    "addi $a0, $a0, 2\n"
    "sllv $t0, $t0, $v1\n"
    "or $v0, $v0, $t0\n"
    ".L800D3444:\n"
    "srl $t0, $v0, 23\n"
    "sll $t0, $t0, 2\n"
    "add $t0, $t0, $a3\n"
    "lw $t1, 0($t0)\n"
    "add $t3, $zero, $zero\n"
    "bgez $zero, .L800D3464\n"
    "andi $at, $t1, 255\n"
    ".L800D3460:\n"
    "lw $t3, 4($t0)\n"
    ".L800D3464:\n"
    "sllv $v0, $v0, $at\n"
    "add $v1, $v1, $at\n"
    "andi $at, $v1, 16\n"
    "beqz $at, .L800D3488\n"
    "andi $v1, $v1, 15\n"
    "lhu $t0, 0($a0)\n"
    "addi $a0, $a0, 2\n"
    "sllv $t0, $t0, $v1\n"
    "or $v0, $v0, $t0\n"
    ".L800D3488:\n"
    "srl $t1, $t1, 16\n"
    "xori $at, $t1, 31775\n"
    "beqz $at, .L800D34E8\n"
    "xori $at, $t1, 65024\n"
    "beqz $at, .L800D32E8\n"
    "sh $t1, 0($a1)\n"
    "beqz $t3, .L800D3404\n"
    "addi $a1, $a1, 2\n"
    "andi $t2, $t3, 65535\n"
    "xori $at, $t2, 31775\n"
    "beqz $at, .L800D34E8\n"
    "xori $at, $t2, 65024\n"
    "beqz $at, .L800D32E8\n"
    "sh $t2, 0($a1)\n"
    "srl $t2, $t3, 16\n"
    "beqz $t2, .L800D3404\n"
    "addi $a1, $a1, 2\n"
    "xori $at, $t2, 31775\n"
    "beqz $at, .L800D34E8\n"
    "xori $at, $t2, 65024\n"
    "beqz $at, .L800D32E8\n"
    "sh $t2, 0($a1)\n"
    "bgez $zero, .L800D3404\n"
    "addi $a1, $a1, 2\n"
    ".L800D34E8:\n"
    "srl $t0, $v0, 16\n"
    "sh $t0, 0($a1)\n"
    "addi $a1, $a1, 2\n"
    "lhu $t0, 0($a0)\n"
    "addi $a0, $a0, 2\n"
    "sll $v0, $v0, 16\n"
    "sllv $t0, $t0, $v1\n"
    "bgez $zero, .L800D3404\n"
    "or $v0, $v0, $t0\n"
    ".L800D350C:\n"
    "ori $t0, $zero, 65024\n"
    "addi $v0, $zero, 64\n"
    ".L800D3514:\n"
    "sh $t0, 0($a1)\n"
    "addi $a1, $a1, 2\n"
    "bnez $v0, .L800D3514\n"
    "addi $v0, $v0, -1\n"
    "mfc0 $t1, $12\n"
    "nop\n"
    "lui $at, 2\n"
    "or $t1, $t1, $at\n"
    "mtc0 $t1, $12\n"
    "jr $ra\n"
    "add $v0, $zero, $zero\n"
    ".L800D3540:\n"
    "lui $t0, %hi(D_800D3574)\n"
    "addiu $t0, $t0, %lo(D_800D3574)\n"
    "sw $a0, 0($t0)\n"
    "sw $a1, 4($t0)\n"
    "sw $v0, 8($t0)\n"
    "sw $v1, 12($t0)\n"
    "sw $t4, 16($t0)\n"
    "sw $t5, 20($t0)\n"
    "sw $t7, 24($t0)\n"
    "sw $t8, 28($t0)\n"
    "sw $t9, 32($t0)\n"
    "jr $ra\n"
    "addi $v0, $zero, 1\n"
    ".set\treorder\n"
    ".set\tat\n"
    ".end\tfunc_800D3234\n"
    ".size\tfunc_800D3234, .-func_800D3234\n"
);

