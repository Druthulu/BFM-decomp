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


extern s16 D_800EC678;
extern s32 D_800EC67C;
extern s32 D_800EC680;
extern s32 D_800EC690;
extern s32 D_800EC694;
extern s32 D_800EC698;

extern s32 func_800149E0(s32);
extern s32 func_80014B10(s32);
extern void func_8002D4C8(s32, s32);
extern void func_800CFE00(void);
extern void func_800118AC(void);
extern void func_800CF3E8(void);

void func_800CF104(void) {
    s32 pad;

    pad = func_800149E0(0);
    func_80014B10(0);
    if (D_800EC690 == 1) goto blk1;
    if (D_800EC690 < 2) goto done;
    if (D_800EC690 == 2) goto blk2;
    if (D_800EC690 == 3) goto blk3;
    goto done;

blk1:
    D_800EC694 = (D_800EC698 & 0x1F) < 0x18;
    D_800EC698++;
    if (pad & 0x840) {
        func_8002D4C8(0xC6E, 0);
        D_800EC690++;
    } else {
        D_800EC67C++;
    }
    goto done;

blk3:
    func_800CFE00();
    D_800EC690 = 2;
    goto done;

blk2:
    if (pad & 0x4000) {
        func_8002D4C8(0x9C1, 0);
        D_800EC678++;
        if (D_800EC678 >= 2) {
            D_800EC678 = 0;
        }
        D_800EC67C = 0;
    } else if (pad & 0x1000) {
        func_8002D4C8(0x9C1, 0);
        D_800EC678--;
        if (D_800EC678 < 0) {
            D_800EC678 = 1;
        }
        D_800EC67C = 0;
    } else if (pad & 0x840) {
        func_8002D4C8(0x9C0, 0);
        D_800EC680 = D_800EC678;
        func_800118AC();
    }

done:
    func_800CF3E8();
    if (D_800EC67C >= 0x1C3) {
        D_800EC680 = 4;
        func_800118AC();
    }
}


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


extern void func_800599B8(u16 *, u16 *);

s32 func_800CFEB4(u16 *arg0)
{
    register u16 *s2 __asm__("$18");
    register u16 *s0 __asm__("$16");
    u16 sVar1;
    s32 ret;
    s32 flag;
    register s32 i __asm__("$9");
    u16 buf[4];
    s32 pad[2];

    __asm__("" : "=r"(s2) : "0"(arg0));
    sVar1 = *s2;
    ret = 0;
    if (sVar1 != 0xFF) {
        s0 = arg0 + 5;
        do {
            i = 0;
            if (sVar1 == 9) {
                register u16 *p __asm__("$8");
                s32 n;
                s32 base;
                s32 arg2;
                register s32 b __asm__("$7");
                register s32 g __asm__("$4");
                register s32 r __asm__("$6");
                register s32 x __asm__("$2");
                register s32 v __asm__("$2");
                register s32 y __asm__("$4");

                flag = 0;
                n = *(s16 *)(s0 - 1);
                base = *(s32 *)(s0 + 1);
                arg2 = base + n * 2;
                p = (u16 *)arg2;
                if (n > 0) {
                    do {
                        v = *p;
                        b = v & 0x1F;
                        g = v & 0x3E0;
                        r = v & 0x7C00;
                        if (b != 0) b -= 1;
                        if (g != 0) g -= 0x20;
                        x = b | g;
                        if (r != 0) r -= 0x400;
                        y = x | r;
                        if ((y & 0xFFFF) != 0) flag = 1;
                        *p = y;

                        p++;
                    } while (++i < *(s16 *)(s0 - 1));
                }
                if (flag != 0) {
                    buf[0] = s0[-3];
                    buf[1] = s0[-2];
                    buf[2] = s0[-1];
                    buf[3] = s0[0];
                    func_800599B8(buf, (u16 *)arg2);
                }
                ret |= flag;
            }
            s2 += 8;
            sVar1 = *s2;
            s0 += 8;
        } while (sVar1 != 0xFF);
    }
    (void)&pad;
    return ret;
}


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


/* func_800D0100 - VERBATIM-ASM BANK (cookbook sec 265, file-scope form #1).
 * -O0 body (addu $fp,$sp,$zero prologue, per-statement scheduling, every delay slot
 * a nop) stranded inside md_MAIN_003's -O2 object (sec 261: 116 functions across the
 * tree are this class; nothing under src/md_* globs -O0 yet). Same family as the
 * already-banked func_800D0440/func_800D05B4/func_800D06BC/func_800D09A0 in this
 * exact TU (same $s0 = D_800AF630 far-base idiom, same ra/fp/s0(/s1) save set).
 *
 * Recovered C semantics for the eventual real -O0-object decomp:
 *
 *     void (*fn)(void) = D_800D363C[*(u16 *)((u8 *)D_800AF630 + 0xA3B4)];
 *     fn();
 *
 * S69 provenance: a prior real-C draft (`register u8 *p = D_800AF630; D_800D363C[*(u16*)
 * (p+0xA3B4)]();`) reported MATCH under match_one's --auto-o0 (it force-compiles a
 * standalone C draft at -O0 on seeing the target's frame-pointer prologue), but
 * tools/recover_integration.py's real-cc1 probe against the actual TU (compiled -O2,
 * per this object's Makefile globs) came back DIFF 15/29 mismatched -- exactly the
 * §261 "shown an -O2 compile of its own C" failure mode: no C draft can bank this
 * function inside md_MAIN_003.c's -O2 object. This file-scope verbatim body is
 * opt-level-independent (cc1 passes the string through untouched per §265), so it
 * reproduces the target bytes regardless of the TU's compile flags. No C externs
 * shipped (link-time resolution).
 */
__asm__(".text\n.align 2\n.globl func_800D0100\n.ent\tfunc_800D0100\n"
"func_800D0100:\n.frame $sp,32,$31\n.mask 0xC0030000,-16\n.fmask 0,0\n"
".set\tnoreorder\n"
"addiu $sp, $sp, -32\n"
"sw $ra, 28($sp)\n"
"sw $fp, 24($sp)\n"
"sw $s1, 20($sp)\n"
"sw $s0, 16($sp)\n"
"addu $fp, $sp, $zero\n"
"lui $s0, %hi(D_800AF630)\n"
"addiu $s0, $s0, %lo(D_800AF630)\n"
"lui $at, 1\n"
"addu $at, $s0, $at\n"
"lhu $v0, -23628($at)\n"
"nop\n"
"addu $v1, $v0, $zero\n"
"sll $v0, $v1, 2\n"
"lui $v1, %hi(D_800D363C)\n"
"addiu $v1, $v1, %lo(D_800D363C)\n"
"addu $v0, $v0, $v1\n"
"lw $s1, 0($v0)\n"
"nop\n"
"jalr $s1\n"
"nop\n"
"addu $sp, $fp, $zero\n"
"lw $ra, 28($sp)\n"
"lw $fp, 24($sp)\n"
"lw $s1, 20($sp)\n"
"lw $s0, 16($sp)\n"
"addiu $sp, $sp, 32\n"
"jr $ra\n"
"nop\n"
".set\treorder\n.end\tfunc_800D0100\n");


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


__asm__(".text\n.align 2\n.globl func_800D0204\n.ent\tfunc_800D0204\n"
"func_800D0204:\n.frame $sp,24,$31\n.mask 0xC0000000,-8\n.fmask 0,0\n"
".set\tnoreorder\n"
"addiu $sp, $sp, -24\n"
"sw $ra, 20($sp)\n"
"sw $fp, 16($sp)\n"
"addu $fp, $sp, $zero\n"
"lui $v0, %hi(D_800EC8B0)\n"
"lw $v0, %lo(D_800EC8B0)($v0)\n"
"nop\n"
"beqz $v0, .L800D0248\n"
"nop\n"
"jal func_800D1E58\n"
"nop\n"
"jal func_800D0D6C\n"
"nop\n"
"jal func_800118AC\n"
"nop\n"
"j .L800D0250\n"
"nop\n"
".L800D0248:\n"
"jal func_800118AC\n"
"nop\n"
".L800D0250:\n"
"addu $sp, $fp, $zero\n"
"lw $ra, 20($sp)\n"
"lw $fp, 16($sp)\n"
"addiu $sp, $sp, 24\n"
"jr $ra\n"
"nop\n"
".set\treorder\n.end\tfunc_800D0204\n");


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


/* func_800D05B4 - VERBATIM-ASM BANK (cookbook sec 265, file-scope form #1).
 * -O0 body (addu $fp,$sp,$zero prologue) stranded inside md_MAIN_003's -O2 object
 * (sec 261/6 -- nothing under src/md_ globs -O0 yet). Recovered C semantics for the
 * eventual real decomp (register u8 *s0 = D_800AF630):
 *
 *     func_8001C044();
 *     func_80015310();
 *     s0[0xA3E1] = 0;
 *     D_800EC890 = 0;
 *     D_800EC8A0 = 1;
 *     func_800183E0((s32)&D_800D4E6C);
 *     func_800183E0((s32)&D_800D52BC);
 *     D_800EC894 = 0;
 *     D_800EC88C = -1;
 *     *(u16 *)(s0 + 0xA3B8) = 0;
 *     func_800118AC();
 *
 * Siblings func_800D0440/func_800D06BC/func_800D09A0 (same TU) are the same shape
 * banked the same way; frame/mask (48/0xC0010000,-16) matches the ra/fp/s0 save set
 * used throughout this file's verbatim-asm blocks. No C externs shipped (link-time
 * resolution).
 */
__asm__(".text\n.align 2\n.globl func_800D05B4\n.ent\tfunc_800D05B4\n"
"func_800D05B4:\n.frame $sp,48,$31\n.mask 0xC0010000,-16\n.fmask 0,0\n"
".set\tnoreorder\n"
"addiu $sp, $sp, -48\n"
"sw $ra, 40($sp)\n"
"sw $fp, 36($sp)\n"
"sw $s0, 32($sp)\n"
"addu $fp, $sp, $zero\n"
"lui $s0, %hi(D_800AF630)\n"
"addiu $s0, $s0, %lo(D_800AF630)\n"
"jal func_8001C044\n"
"nop\n"
"jal func_80015310\n"
"nop\n"
"lui $at, 1\n"
"addu $at, $s0, $at\n"
"sb $zero, -23583($at)\n"
"lui $at, %hi(D_800EC890)\n"
"sw $zero, %lo(D_800EC890)($at)\n"
"addiu $v0, $zero, 1\n"
"lui $at, %hi(D_800EC8A0)\n"
"sw $v0, %lo(D_800EC8A0)($at)\n"
"lui $a0, %hi(D_800D4E6C)\n"
"addiu $a0, $a0, %lo(D_800D4E6C)\n"
"jal func_800183E0\n"
"nop\n"
"lui $a0, %hi(D_800D52BC)\n"
"addiu $a0, $a0, %lo(D_800D52BC)\n"
"jal func_800183E0\n"
"nop\n"
"lui $at, %hi(D_800EC894)\n"
"sh $zero, %lo(D_800EC894)($at)\n"
"addiu $v0, $zero, -1\n"
"lui $at, %hi(D_800EC88C)\n"
"sw $v0, %lo(D_800EC88C)($at)\n"
"lui $at, 1\n"
"addu $at, $s0, $at\n"
"sh $zero, -23624($at)\n"
"jal func_800118AC\n"
"nop\n"
"addu $sp, $fp, $zero\n"
"lw $ra, 40($sp)\n"
"lw $fp, 36($sp)\n"
"lw $s0, 32($sp)\n"
"addiu $sp, $sp, 48\n"
"jr $ra\n"
"nop\n"
".set\treorder\n.end\tfunc_800D05B4\n");


/* func_800D0664 - VERBATIM-ASM BANK (cookbook sec 265, file-scope form #1).
 * -O0 body (addu $fp,$sp,$zero prologue, nop in every delay slot) stranded inside
 * md_MAIN_003's -O2 object (sec 261/6 -- this subseg has no -O0 glob; the _o0c/_o0d
 * objects start at 0x1f74, past this function's 0x186c). No -O2 C can ever emit this
 * prologue, so C drafting cannot converge here -- a prior attempt scored match_one
 * MATCH only because the oracle auto-detected -O0, which the real object never uses.
 * This body sidesteps that entirely: cc1 passes the string through untouched, so it is
 * opt-level-independent -- VERIFIED, not assumed: match_one scores MATCH 22/22 both at
 * -O0 (auto) AND under --no-auto-o0 (forced -O2, the level this object really uses).
 * match_one still prints its 'CANNOT BANK until the function lives in an -O0 object'
 * NOTE here, but that heuristic keys only on (target has -O0 prologue) + (subseg builds
 * -O2) and is blind to the draft's FORM; it describes the C lane, not this one. The
 * gated-green counterexamples are in this very file: func_800D0440, func_800D05B4 and
 * func_800D06BC are all -O0 bodies banked verbatim inside this -O2 subseg.
 * Recovered C semantics for the eventual real decomp:
 *
 *     register u8 *s0 = D_800AF630;   // hoisted base, never read (sec 6 idiom)
 *     func_80015310();
 *     func_800183E0((s32)&D_800D93FC);
 *     func_800118AC();
 *
 * Immediate siblings func_800D05B4 (above) and func_800D06BC (below) are the same
 * shape banked the same way; frame/mask (40/0xC0010000,-16) derived the same way they
 * were -- frame 0x28=40, lowest saved reg $s0 at 0x18=24, 24-40 = -16; save set
 * ra/fp/s0 = 0xC0010000. All immediates decimal (maspsx rejects hex in __asm__
 * strings). No C externs shipped (link-time resolution, sec 265 / sec 236-1).
 */
__asm__(".text\n.align 2\n.globl func_800D0664\n.ent\tfunc_800D0664\n"
"func_800D0664:\n.frame $sp,40,$31\n.mask 0xC0010000,-16\n.fmask 0,0\n"
".set\tnoreorder\n"
"addiu $sp, $sp, -40\n"
"sw $ra, 32($sp)\n"
"sw $fp, 28($sp)\n"
"sw $s0, 24($sp)\n"
"addu $fp, $sp, $zero\n"
"lui $s0, %hi(D_800AF630)\n"
"addiu $s0, $s0, %lo(D_800AF630)\n"
"jal func_80015310\n"
"nop\n"
"lui $a0, %hi(D_800D93FC)\n"
"addiu $a0, $a0, %lo(D_800D93FC)\n"
"jal func_800183E0\n"
"nop\n"
"jal func_800118AC\n"
"nop\n"
"addu $sp, $fp, $zero\n"
"lw $ra, 32($sp)\n"
"lw $fp, 28($sp)\n"
"lw $s0, 24($sp)\n"
"addiu $sp, $sp, 40\n"
"jr $ra\n"
"nop\n"
".set\treorder\n.end\tfunc_800D0664\n");


/* func_800D06BC - VERBATIM-ASM BANK (cookbook sec 265, file-scope form #1).
 * -O0 body (addu $fp,$sp,$zero prologue) stranded inside md_MAIN_003's -O2 object
 * (sec 261/6 -- nothing under src/md_ globs -O0 yet). Recovered C semantics for the
 * eventual real decomp:
 *
 *     D_800EC890 += 4;
 *     if (D_800EC890 >= 128) {
 *         D_800EC890 = 128;
 *         func_800118AC();
 *     }
 *
 * Sibling func_800D09A0 (same TU, few lines below) is the same shape banked the same
 * way; frame/mask (32/0xC0010000,-16) copied from it. All immediates decimal
 * (maspsx rejects hex in __asm__ strings). No C externs shipped (link-time resolution).
 */
__asm__(".text\n.align 2\n.globl func_800D06BC\n.ent\tfunc_800D06BC\n"
"func_800D06BC:\n.frame $sp,32,$31\n.mask 0xC0010000,-16\n.fmask 0,0\n"
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
"lui $v0, %hi(D_800EC890)\n"
"lw $v0, %lo(D_800EC890)($v0)\n"
"nop\n"
"addiu $v1, $v0, 4\n"
"lui $at, %hi(D_800EC890)\n"
"sw $v1, %lo(D_800EC890)($at)\n"
"lui $v0, %hi(D_800EC890)\n"
"lw $v0, %lo(D_800EC890)($v0)\n"
"nop\n"
"slti $v1, $v0, 128\n"
"bnez $v1, .L800D0724\n"
"nop\n"
"addiu $v0, $zero, 128\n"
"lui $at, %hi(D_800EC890)\n"
"sw $v0, %lo(D_800EC890)($at)\n"
"jal func_800118AC\n"
"nop\n"
".L800D0724:\n"
"addu $sp, $fp, $zero\n"
"lw $ra, 24($sp)\n"
"lw $fp, 20($sp)\n"
"lw $s0, 16($sp)\n"
"addiu $sp, $sp, 32\n"
"jr $ra\n"
"nop\n"
".set\treorder\n.end\tfunc_800D06BC\n");


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


/* func_800D0A7C - VERBATIM-ASM BANK (cookbook sec 265, file-scope form #1).
 * -O0 body (addu $fp,$sp,$zero prologue) stranded inside md_MAIN_003's -O2 object
 * (sec 261/6 -- nothing under src/md_ globs -O0 yet). Recovered C semantics for the
 * eventual real decomp:
 *
 *     D_800EC890 -= 4;
 *     if (D_800EC890 < 0) {
 *         D_800EC890 = 0;
 *         func_800146B0(1);
 *         *(s32 *)((u8 *)D_800AF630 + 0xA3E8) = 2;
 *         func_800118AC();
 *     } else {
 *         func_800D12D0();
 *     }
 *
 * Siblings func_800D06BC / func_800D09A0 (same TU) are the same shape banked the same
 * way; frame/mask (32/0xC0010000,-16) copied from them. All immediates decimal
 * (maspsx rejects hex in __asm__ strings). No C externs shipped (link-time resolution).
 */
__asm__(".text\n.align 2\n.globl func_800D0A7C\n.ent\tfunc_800D0A7C\n"
"func_800D0A7C:\n.frame $sp,32,$31\n.mask 0xC0010000,-16\n.fmask 0,0\n"
".set\tnoreorder\n"
"addiu $sp, $sp, -32\n"
"sw $ra, 24($sp)\n"
"sw $fp, 20($sp)\n"
"sw $s0, 16($sp)\n"
"addu $fp, $sp, $zero\n"
"lui $s0, %hi(D_800AF630)\n"
"addiu $s0, $s0, %lo(D_800AF630)\n"
"lui $v0, %hi(D_800EC890)\n"
"lw $v0, %lo(D_800EC890)($v0)\n"
"nop\n"
"addiu $v1, $v0, -4\n"
"lui $at, %hi(D_800EC890)\n"
"sw $v1, %lo(D_800EC890)($at)\n"
"lui $v0, %hi(D_800EC890)\n"
"lw $v0, %lo(D_800EC890)($v0)\n"
"nop\n"
"bgez $v0, .L800D0AF8\n"
"nop\n"
"lui $at, %hi(D_800EC890)\n"
"sw $zero, %lo(D_800EC890)($at)\n"
"addiu $a0, $zero, 1\n"
"jal func_800146B0\n"
"nop\n"
"addiu $v0, $zero, 2\n"
"lui $at, 1\n"
"addu $at, $s0, $at\n"
"sw $v0, -23576($at)\n"
"jal func_800118AC\n"
"nop\n"
"j .L800D0B00\n"
"nop\n"
".L800D0AF8:\n"
"jal func_800D12D0\n"
"nop\n"
".L800D0B00:\n"
"addu $sp, $fp, $zero\n"
"lw $ra, 24($sp)\n"
"lw $fp, 20($sp)\n"
"lw $s0, 16($sp)\n"
"addiu $sp, $sp, 32\n"
"jr $ra\n"
"nop\n"
".set\treorder\n.end\tfunc_800D0A7C\n");


/* func_800D0B1C - VERBATIM-ASM BANK (cookbook sec 265, file-scope form #1).
 * -O0 body (addu $fp,$sp,$zero prologue / 21F0A003, a nop in every delay slot,
 * per-statement li) stranded inside md_MAIN_003's -O2 object (sec 261: nothing
 * under src/md_* globs -O0 yet). Sec 261a addendum (d) names this TU explicitly:
 * the fleet's TERMINAL state for an -O0 function stranded in an -O2 TU is the
 * sec 265 verbatim-asm block IN THIS TU, not (yet) the sec 18/sec 261 _o0 carve.
 * Same family and same save set (ra/fp/s0, frame 32, mask 0xC0010000,-16) as the
 * already-banked func_800D0174 / func_800D0204 / func_800D0440 / func_800D06BC /
 * func_800D09A0 / func_800D0A7C in this exact file.
 *
 * Three prior wave agents each reported match_one MATCH 77/77 for the real C body
 * below (match_one force-compiles -O0 on seeing the frame-pointer prologue) and
 * each was rejected by the whole-binary gate: tools/recover_integration.py's
 * real-cc1 probe DIFFs 49/77 because the object's own CC1FLAGS are -O2. That is
 * exactly sec 261's "shown an -O2 compile of its own C" failure mode - no C source
 * can bank this function while md_MAIN_003.c compiles -O2. A raw __asm__ body is
 * opt-level-independent (cc1 passes the string through untouched), so it emits the
 * target bytes regardless of the TU's compile flags.
 *
 * Recovered C semantics for the eventual real -O0-object decomp:
 *
 *     register u8 *s0 = D_800AF630;       // sec 127 far-base hi/lo pair
 *     func_800183E0((s32)&D_800D4E6C);
 *     switch (D_800EC894) {               // extern s16 D_800EC894 (lh)
 *     case 0: *(u16 *)(s0 + 0xA3B6) = 1; *(u16 *)(s0 + 0xA3B8) = 2; break;
 *     case 1: *(u16 *)(s0 + 0xA3B6) = 1; *(u16 *)(s0 + 0xA3B8) = 0; break;
 *     case 2: *(u16 *)(s0 + 0xA3B6) = 1; *(u16 *)(s0 + 0xA3B8) = 1; break;
 *     case 4: *(u16 *)(s0 + 0xA3B6) = 1; *(u16 *)(s0 + 0xA3B8) = 4; break;
 *     }
 *
 * All immediates decimal (maspsx rejects hex inside __asm__ strings); -0x5C4A =
 * -23626, -0x5C48 = -23624, lui $at,(0x10000>>16) = lui $at,1. No C externs
 * shipped (link-time resolution, per sec 265 / sec 236-1).
 */
__asm__(".text\n.align 2\n.globl func_800D0B1C\n.ent\tfunc_800D0B1C\n"
"func_800D0B1C:\n.frame $sp,32,$31\n.mask 0xC0010000,-16\n.fmask 0,0\n"
".set\tnoreorder\n"
"addiu $sp, $sp, -32\n"
"sw $ra, 24($sp)\n"
"sw $fp, 20($sp)\n"
"sw $s0, 16($sp)\n"
"addu $fp, $sp, $zero\n"
"lui $s0, %hi(D_800AF630)\n"
"addiu $s0, $s0, %lo(D_800AF630)\n"
"lui $a0, %hi(D_800D4E6C)\n"
"addiu $a0, $a0, %lo(D_800D4E6C)\n"
"jal func_800183E0\n"
"nop\n"
"lui $v0, %hi(D_800EC894)\n"
"lh $v0, %lo(D_800EC894)($v0)\n"
"addiu $v1, $zero, 1\n"
"beq $v0, $v1, .L800D0BC0\n"
"nop\n"
"slti $v1, $v0, 2\n"
"beqz $v1, .L800D0B78\n"
"nop\n"
"beqz $v0, .L800D0B98\n"
"nop\n"
"j .L800D0C34\n"
"nop\n"
".L800D0B78:\n"
"addiu $v1, $zero, 2\n"
"beq $v0, $v1, .L800D0BE4\n"
"nop\n"
"addiu $v1, $zero, 4\n"
"beq $v0, $v1, .L800D0C0C\n"
"nop\n"
"j .L800D0C34\n"
"nop\n"
".L800D0B98:\n"
"addiu $v0, $zero, 1\n"
"lui $at, 1\n"
"addu $at, $s0, $at\n"
"sh $v0, -23626($at)\n"
"addiu $v0, $zero, 2\n"
"lui $at, 1\n"
"addu $at, $s0, $at\n"
"sh $v0, -23624($at)\n"
"j .L800D0C34\n"
"nop\n"
".L800D0BC0:\n"
"addiu $v0, $zero, 1\n"
"lui $at, 1\n"
"addu $at, $s0, $at\n"
"sh $v0, -23626($at)\n"
"lui $at, 1\n"
"addu $at, $s0, $at\n"
"sh $zero, -23624($at)\n"
"j .L800D0C34\n"
"nop\n"
".L800D0BE4:\n"
"addiu $v0, $zero, 1\n"
"lui $at, 1\n"
"addu $at, $s0, $at\n"
"sh $v0, -23626($at)\n"
"addiu $v0, $zero, 1\n"
"lui $at, 1\n"
"addu $at, $s0, $at\n"
"sh $v0, -23624($at)\n"
"j .L800D0C34\n"
"nop\n"
".L800D0C0C:\n"
"addiu $v0, $zero, 1\n"
"lui $at, 1\n"
"addu $at, $s0, $at\n"
"sh $v0, -23626($at)\n"
"addiu $v0, $zero, 4\n"
"lui $at, 1\n"
"addu $at, $s0, $at\n"
"sh $v0, -23624($at)\n"
"j .L800D0C34\n"
"nop\n"
".L800D0C34:\n"
"addu $sp, $fp, $zero\n"
"lw $ra, 24($sp)\n"
"lw $fp, 20($sp)\n"
"lw $s0, 16($sp)\n"
"addiu $sp, $sp, 32\n"
"jr $ra\n"
"nop\n"
".set\treorder\n.end\tfunc_800D0B1C\n");


INCLUDE_ASM("asm/md_MAIN_003/nonmatchings/md_MAIN_003", func_800D0C50);
