#include "common.h"

/* ==== Phase-26 §8b carried decl layer (jr_isolate_all.py) ===================
 * The file-scope decl environment from earlier code regions of this object —
 * file-local types, col-0 decls, DEFINE_func macro externs, and each earlier
 * definition's implied prototype (types first, then decls in original order).
 * Decls emit no code => byte-neutral. See cookbook §8c. */
extern void (*D_800D3598[])(void);
extern void func_800CEED0(void);
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
extern void func_800CEF04(void);
extern void func_8001A9F8(s32 a0);
extern s32 CdReadRequest(s32 *a0, void *a1, s32 a2, s32 a3);
extern s32 D_800AE858;
extern void func_800CEFBC(void);
extern s32 D_800B9A18;
extern s32 D_800EC6A0;
extern s32 D_800EC6A4;
extern unsigned char D_800DA48C[];
extern void func_800D1E58(void);
extern void func_800CFFEC(void);
extern void func_800CF010(void);
extern void func_800CF3E8(void);
extern s32 func_800CFC1C();
extern void func_800CF078(void);
extern s32 func_800149E0(s32);
extern s32 func_80014B10(s32);
extern void func_8002D4C8(s32, s32);
extern void func_800CFE00(void);
extern void func_800CF104(void);
extern void func_80059888(void *a0, s32 a1, s32 a2, s32 a3);
extern void func_800CF300(void);
extern void func_800146B0(s32);
extern void func_800118AC();
extern void func_800CF370(void);
extern s8 D_800D52BC[];
extern u16 D_800B99E6;
extern u16 D_800B99E8;
extern void func_800183E0(s32 a0);
extern void func_800CF3A4(void);
extern s32 D_800EC69C;
extern void func_800599B8();
extern void func_800CFB3C(u16 *arg0);
extern s32 func_800CFC1C(u16 *param_1);
extern void func_800599B8(u16 *, u16 *);
extern u16 D_800AF7BC;
extern u16 D_800AF7BE;
extern u16 D_800AF7C0;
extern void GsInitGraph2(s32 w, s32 h, s32 mode, s32 a3, s32 st);
extern void func_80053EEC(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80059234(s32 a0);
extern void func_80053218(void);
extern void func_800147B8(void);
extern u8 D_800AF6DC;
extern u8 D_800AF680;
/* ==== end §8b carried decl layer ==== */



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


#include "common.h"

extern s32 D_800EC9A4[];
extern s32 D_800EC9AC;
extern s32 D_800EC9B8;
extern s16 D_800EC9BC[];
extern s16 D_800EC9BE[];
extern s32 D_800EC9CC;
extern s32 D_800EC9E0;
extern s32 D_800EC9E4;
extern s32 D_800EC9F0;
extern s32 D_800EC9F4;
extern s32 D_800EC9F8;
extern u8 D_800EC9FC[];

struct S_D2394;
struct S_D2394B;
extern void func_800D2394(struct S_D2394 *t, s16 a1, s16 a2, s16 a3, s32 a4, struct S_D2394B *a5);
extern void func_800D2454();
extern void func_800D24D0();
extern s32 func_800D2704();
extern void func_800D298C();
extern void func_800D2AA0();
extern void func_800D2C0C();
extern void func_800D2C88();
extern void func_800D2D44();

extern void func_800468FC(void);
extern void func_8002D8D4(void);
extern void func_8002D8A8(void);
extern void func_8002D034(void);
extern void func_800189A8(void);
extern s32 func_80014CAC(s32 a0, s32 a1);
extern void func_80043830(s32 a0, s32 a1, s32 a2);
extern void func_80010A98(void);
extern void func_80059658(s32 a0);
extern void func_80059888(void *a0, s32 a1, s32 a2, s32 a3);
extern void func_80059FC0(u8 *a0);
extern s32 VSync(s32 a0);
extern void *SetDefDispEnv(void *a0, s32 a1, s32 a2, s32 a3, s32 a4);

void func_800D1E9C(void *arg0) {
    s32 sp18[30];
    s16 sp90[4];
    s16 sp98[8];
    s32 *p;
    s32 i;
    register s32 v0r __asm__("$2");

    p = (s32 *) arg0;
    D_800EC9F0 = 1;
    ((void (*)()) func_800D2394)(D_800EC9A4,
                                 p[1] ? (p[4] * 3) / 2 : p[4],
                                 p[5],
                                 p[1] ? (p[4] * 3) / 2 : p[4],
                                 p[5] + p[7],
                                 p);
    if (((s32 (*)()) func_800D2454)(D_800EC9FC, func_800D24D0, p) != 0) {
        func_800D2D44(0);
        func_800468FC();
        func_8002D8D4();
        func_800D2AA0(0);
        __asm__ __volatile__("");
        goto ret;
    }
    if (func_800D2704(D_800EC9A4, p) != 0) {
        func_800D2D44(0);
        func_800468FC();
        func_8002D8D4();
        func_800D2AA0(0);
        goto ret;
    }
    D_800EC9F4 = 0;
    D_800EC9F8 = 0;
    func_80059658(0);
    VSync(0);
    sp90[0] = 0;
    sp90[1] = 0;
    sp90[2] = p[1] ? (p[6] * 3) / 2 : p[6];
    sp90[3] = p[7] * 2;
    if (p[1] != 0) {
        func_80059888(sp90, 0, 0, 0);
        sp98[0] = 0x1E0;
        sp98[1] = 0;
        sp98[2] = 0xA0;
        sp98[3] = 0x1E0;
        func_80059888(sp98, 0xFF, 0xFF, 0xFF);
    } else {
        func_80059888(sp90, 0, 0, 0);
        sp98[0] = 0x140;
        sp98[1] = 0;
        sp98[2] = 0x140;
        sp98[3] = 0x1E0;
        func_80059888(sp98, 0xFF, 0xFF, 0xFF);
    }
    for (;;) {
        func_800D2C0C(D_800EC9A4[D_800EC9AC], p[1] ? 3 : 2);
        ((void (*)()) func_800D2C88)((&D_800EC9A4[3])[D_800EC9B8],
                                     ((*(s16 *) ((u8 *) D_800EC9A4 + 0x30) << 4) *
                                      ((*(s16 *) ((u8 *) D_800EC9A4 + 0x32) - 1) / 16 + 1)) >> 1);
        if (func_800D2704(D_800EC9A4, p) != 0) {
            func_800D2D44(0);
            func_800468FC();
            func_8002D8D4();
            goto after;
        }
        func_800D298C(D_800EC9A4, 0);
        VSync(0);
        i = (D_800EC9CC == 0);
        SetDefDispEnv(sp18,
                      D_800EC9BC[i * 4] -
                          (p[1] ? (p[4] * 3) / 2 : p[4]),
                      D_800EC9BE[i * 4] - p[5],
                      p[1] ? (p[6] * 3) / 2 : p[6],
                      p[7]);
        if (p[1] != 0) {
            *((u8 *) sp18 + 0x11) = p[1];
            *(s16 *) ((u8 *) sp18 + 4) = (*(s16 *) ((u8 *) sp18 + 4) * 2) / 3;
        }
        func_80059FC0((u8 *) sp18);
        func_80059658(1);
        if (D_800EC9F4 == 1) {
            goto done;
        }
        func_800189A8();
        if (D_800EC9F8 == 0) {
            if (D_800EC9E0 == 0) {
                if (func_80014CAC(0, 0x800) != 0) {
                    D_800EC9E0 = 1;
                    D_800EC9E4 = 0x10;
                    func_8002D8A8();
                }
            } else {
                D_800EC9E4 -= 1;
                if (D_800EC9E4 == 0) {
                    goto done;
                }
            }
        }
        func_8002D034();
    }
done:
    func_800D2D44(0);
    func_800468FC();
    func_8002D8D4();
    func_80043830(9, 0, 0);
after:
    func_800D2AA0(0);
    func_80059658(1);
ret:
    func_80010A98();
    v0r = 1;
    __asm__ __volatile__("" : : "r"(v0r));
}


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


INCLUDE_ASM("asm/md_MAIN_003/nonmatchings/md_MAIN_003_jr_800D1E18", func_800D24D0);

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


extern u8 D_800EC9E8[4];

extern s32 func_800435CC(s32 mode, void *buf, void *param);
extern s32 CdRead2(s32 count);

/* TU (src/md_MAIN_003/md_MAIN_003.c:1085) forward-declares this K&R-style as
 * `extern void func_800D2A24();` for its sole caller (func_800D2454, which
 * discards the return), so the definition here must be `void` to avoid
 * `conflicting types for 'func_800D2A24'` (cc1 exit 33). The body genuinely
 * sets $v0 to 1 or 0 on every exit path (asm: `addiu $v0,zero,1` /
 * `addu $v0,zero,zero`), and a plain `return <value>;` in a void function is
 * a pedwarn gcc-2.7.2 silently DISCARDS (loses those materializations,
 * closeness != 0 -- cookbook §43's void-return-value-drop). Absorbed at the
 * use site instead: a hard-`$2` register local set via a read-only
 * input-`__asm__` immediately before a bare `return;` on each exit forces
 * the same `li $v0,K` the s32-typed body would have emitted, without
 * widening the TU's declared return type. Putting the early-exit's v0-set
 * behind a `goto` (rather than inline in the `if` body) keeps that branch a
 * single instruction, matching the target's branch polarity -- inlining the
 * register-pin + asm barrier directly in the `if` block bloats it and flips
 * beqz/bnez (byte-verified: NEAR closeness 10 vs this MATCH closeness 0).
 */
void func_800D2A24(s32 a0) {
    u8 *p;
    s32 r;
    register s32 v0 __asm__("$2");

retry:
    p = D_800EC9E8;
    for (;;) {
        r = func_800435CC(2, (void *)a0, p);
        if (*p & 0x10) {
            goto ret1;
        }
        if (r != 0) {
            break;
        }
    }
    if (CdRead2(0x1C0) == 0) {
        goto retry;
    }
    v0 = 0;
    __asm__ __volatile__("" : : "r"(v0));
    return;

ret1:
    v0 = 1;
    __asm__ __volatile__("" : : "r"(v0));
    return;
}


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


INCLUDE_RODATA("asm/md_MAIN_003/nonmatchings/md_MAIN_003_jr_800D1E18", D_800CEDF8);

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


extern void func_8005C604();
extern s32 *D_800DB670;
extern s32 *D_800DB644;
extern s32 *D_800DB650;
extern s32 *D_800DB63C;
extern s32 *D_800DB648;
extern char D_800CEE58[];
extern char D_800CEE80[];
extern char D_800CEEB8[];

/* §8-ADDENDUM: the strings migrated into func_800D30D0.s ride in on the
 * INCLUDE_ASM stub; banking the function drops them, shifting every later
 * .rodata symbol.  Carry them as a file-scope __asm__ blob at the exact
 * source position the stub occupied (this TU's own D_800CEE1C house form). */
__asm__(
    ".section .rodata\n"
    ".align 2\n"
    ".globl D_800CEE58\n"
    "D_800CEE58:\n"
    ".asciz \"\\t DMA=(%d,%d), ADDR=(0x%08x->0x%08x)\\n\"\n"
    ".align 2\n"
    ".globl D_800CEE80\n"
    "D_800CEE80:\n"
    ".asciz \"\\t FIFO=(%d,%d),BUSY=%d,DREQ=(%d,%d),RGB24=%d,STP=%d\\n\"\n"
    ".align 2\n"
    ".globl D_800CEEB8\n"
    "D_800CEEB8:\n"
    ".asciz \"%s timeout:\\n\"\n"
    ".align 2\n"
    ".word 0x3C02800C\n"
    ".word 0x944299E4\n"
    ".section .text\n"
);

/* §37 asm-label alias: this TU already declares `extern void
 * func_800D30D0(char *a0);` twice (its two callers).  The body really does
 * return 0 in $v0, so define it under an alias -- the same lever the TU
 * already uses for aF800D2F88 -- instead of fighting the void prototype. */
s32 aF800D30D0(char *arg0) __asm__("func_800D30D0");

s32 aF800D30D0(char *arg0) {
    register s32 ret __asm__("$2");
    s32 s0;

    func_8005C604(D_800CEEB8, arg0);
    s0 = *(volatile s32 *)D_800DB670;
    func_8005C604(D_800CEE58,
        (*(volatile u32 *)D_800DB644 >> 24) & 1,
        (*(volatile u32 *)D_800DB650 >> 24) & 1,
        *D_800DB63C,
        *D_800DB648);
    func_8005C604(D_800CEE80,
        ((u32)~s0 >> 31),
        ((u32)s0 >> 30) & 1,
        ((u32)s0 >> 29) & 1,
        ((u32)s0 >> 28) & 1,
        ((u32)s0 >> 27) & 1,
        ((u32)s0 >> 25) & 1,
        ((u32)s0 >> 23) & 1);
    *D_800DB670 = 0x80000000;
    *D_800DB644 = 0;
    *D_800DB650 = 0;
    __asm__ volatile("" : "=r"(ret) : "0"(0));
    (void)*(volatile s32 *)D_800DB650;
    *D_800DB670 = 0x60000000;
    return ret;
}


INCLUDE_ASM("asm/md_MAIN_003/nonmatchings/md_MAIN_003_jr_800D1E18", D_800D3200);

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



