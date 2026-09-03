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
