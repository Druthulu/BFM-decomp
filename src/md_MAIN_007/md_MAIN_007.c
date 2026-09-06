#include "common.h"

extern u16 D_800B99E4;
extern u8 D_800CFABF;
extern u8 D_800CFAC4[];
extern u8 D_800CFAD4[];
extern void (*D_800CFADC[])(void);
extern s32 D_800D1364;
extern u8 D_800AF630[];
extern void func_8001534C(int, void *, int, int, int, int);

void func_800CEE2C(void) {
    u8 *base = D_800AF630;
    u8 *p;
    u8 v1;
    u16 idx;

    p = &D_800CFABF;
    v1 = *(u8 *)&D_800B99E4;
    v1 += 0x30;
    *p = v1;
    func_8001534C(1, p - 0xB, 0x60, 0x64, 0, 0);

    if (D_800D1364) {
        func_8001534C(2, D_800CFAC4, 0x60, 0x70, 0, 0);
    } else {
        func_8001534C(3, D_800CFAD4, 0x60, 0x70, 0, 0);
    }

    idx = *(u16 *)(base + 0xA3B4);
    if (idx < 4) {
        D_800CFADC[idx]();
    }
}


extern void func_8001C044(void);
extern void func_80015310(void);
extern void func_800183E0(void *a0);
extern void func_800167B8(s32 a0);
extern void func_800118AC(void);

extern s8 D_800B9A11;
extern s32 D_800D1364;
extern u16 D_800B99E8;
extern s32 D_800D130C;

void func_800CEEFC(void) {
    D_800B9A11 = 1;
    func_8001C044();
    func_80015310();
    D_800D1364 = 0;
    func_800183E0(&D_800D130C);
    func_800167B8(0);
    D_800B99E8 = 0;
    func_800118AC();
}




void func_800CEF60(void) {
    extern s32 func_800167F0(s32 a0);
    extern void func_800118AC(void);

    if (func_800167F0(0) & 0xFFFF) {
        func_800118AC();
    }
}


void func_800CEF94(void) {
    extern s32 func_80014CAC(s32 a0, s32 a1);
    extern void func_800167B8(s32 a0);
    extern void func_800118AC(void);
    extern u16 D_800B99E8;

    u16 counter = D_800B99E8;
    counter++;
    D_800B99E8 = counter;

    if ((s16)counter < 0x81) {
        s32 result = func_80014CAC(0, 0x800);
        if ((result << 16) == 0) {
            goto end;
        }
    }
    func_800167B8(4);
    func_800118AC();
end:;
}


extern s32 func_800167F0(s32 a0);
extern u16 D_800B99E6;

void func_800CEFF8(void) {
    if (func_800167F0(0x4) & 0xFFFF) {
        D_800B99E6 = 1;
    }
}



extern u16 D_800B99E4;
extern void (*D_800D133C[])(void);

void func_800CF02C(void) {
    D_800D133C[D_800B99E4]();
}


INCLUDE_RODATA("asm/md_MAIN_007/nonmatchings/md_MAIN_007", D_800CEDF8);

extern void func_8001AA98(void *a0);
extern s32 D_800D1368;
extern s32 D_800D1370;
extern s32 D_800D1374;
extern void func_800167B8(s32 a0);
extern void func_800118AC(void);
const char D_800CEDFC[] = "C:\\TIMPACK\\OPDEMO0.PAT";  /* §304: the stub .s was the only owner of this rodata block */

void func_800CF068(void) {
    func_8001AA98((void *)D_800CEDFC);
    D_800D1368 = 0;
    D_800D1370 = 0;
    D_800D1374 = 0;
    func_800167B8(0);
    func_800118AC();
}



extern s32 D_800D1374;   /* the target reads it with lw (real-TU diff), not lhu */
extern void (*D_800D1344[])(void);

void func_800CF0B8(void) {
    D_800D1344[D_800D1374]();
}


extern s32 D_800D1368;
extern s32 D_800D1374;
extern void func_800CF408(s32 a0, s32 a1);
extern s32 func_800167F0(s32 a0);

void func_800CF0F4(void) {
    func_800CF408(0, D_800D1368);

    if (func_800167F0(0) & 0xFFFF) {
        D_800D1374++;
    }
}


extern s32 D_800D1368;
extern s32 D_800D1374;
extern void func_800CF408(s32 a0, s32 a1);
extern void func_800167B8(s32 a0);

void func_800CF148(void) {
    // Redeclare with correct calling semantics
    extern s32 func_800CF3B0(void);
    
    if (func_800CF3B0()) {
        return;
    }
    
    func_800CF408(0, D_800D1368);
    
    D_800D1368--;
    if (D_800D1368 < -0x10F) {
        func_800167B8(0x4);
        D_800D1368 = -0x110;
        D_800D1374++;
    }
}


extern s32 D_800D1368;
extern s32 D_800D1374;
extern void func_800CF408(s32 a0, s32 a1);
extern s32 func_800167F0(s32 a0);

void func_800CF1CC(void) {
    func_800CF408(0, D_800D1368);

    if ((func_800167F0(4) & 0xFFFF) != 0) {
        D_800D1374++;
    }
}


extern void func_8001AA98(void *a0);
extern s32 D_800D1374;
extern void func_800167B8(s32 a0);

const char D_800CEE14[] = "C:\\TIMPACK\\OPDEMO1.PAT";

void func_800CF220(void) {
    func_8001AA98((void *)D_800CEE14);
    func_800167B8(0);
    D_800D1374++;
}


extern s32 func_800167F0(s32 a0);
extern void func_800CF6D0(s32 a0, u32 a1);
extern s32 D_800D136C;
extern s32 D_800D1374;

void func_800CF268(void) {
    func_800CF6D0(-0x400, 0);
    if (func_800167F0(0) & 0xFFFF) {
        D_800D136C = -0x340;
        D_800D1374++;
    }
}


extern void func_800CF6D0(s32 a0, u32 a1);
extern void func_800167B8(s32 a0);
extern s32 D_800D136C;
extern s32 D_800D1374;

void func_800CF2BC(void) {
    if (func_800CF3B0() != 0) {
        return;
    }
    func_800CF6D0(D_800D136C++, 0);
    if (D_800D136C < 0x141) {
        return;
    }
    func_800167B8(4);
    D_800D1374++;
}


extern s32 D_800D136C;
extern s32 D_800D1374;
extern void func_800CF6D0(s32 a0, u32 a1);
extern s32 func_800167F0(s32 a0);

void func_800CF33C(void) {
    func_800CF6D0(D_800D136C, 0);
    if ((func_800167F0(4) & 0xFFFF) != 0) {
        D_800D1374++;
    }
}


extern s32 func_800CF3B0();

void func_800CF390(void *a0, void *a1, void *a2) {
    func_800CF3B0(a0, a1, a2);
}


extern s32 func_800149E0(s32);
extern u16 D_800B99E6;

s32 func_800CF3B0(void *a0, void *a1, void *a2) {
    s32 result0 = func_800149E0(0);
    s32 result1 = func_800149E0(1);
    s32 combined = result0 | result1;

    if ((combined & 0x800) != 0) {
        D_800B99E6 = 1;
        return 1;
    }
    return 0;
}


INCLUDE_ASM("asm/md_MAIN_007/nonmatchings/md_MAIN_007", func_800CF408);

/* func_800CF6D0 — md_MAIN_007 (-O2). Builds six 0x18-byte "SPRT with its own tpage" primitives
 * (tag / 0xE10000xx draw-mode word / rgb+code 0x64 / xy / uv+clut / wh) at the D_800A5E60 prim
 * cursor and addPrim()s each onto OT word [0] of the frame's ordering table
 * (D_800AA60C + D_800B9A02 * 0x4000), then republishes the advanced cursor.  Four 256-wide tiles
 * at (arg0-0xA0 + 0x100*i, arg1-0x78) plus a fixed 2 x (0xA0 x 0x100) backdrop.
 * Twin: md_MAIN_009/func_800CD92C (banked, §501-H) — same shape, same prologue weave.
 *
 * MATCH 249/249, match_one AND rtu_match (real TU), ZERO register pins (P32 T5x, Fable).
 * The prior 137-plateau's residual ("sched1 rank_for_schedule class tie") was misattributed —
 * read from the -dS/-dR/-df dumps and the 2.7.2 source it is three separate mechanisms:
 *
 *  1. sched2 (NOT sched1) split the field stores around the `lhu D_800B9A02`: sched.c:838-845
 *     true_dependence exempts a /s (struct-member) store at a VARYING address in NON-QImode from
 *     conflicting with a non-/s FIXED-address read, so `p->clut/x0/y0/w/h/tpage` were ready one
 *     clock before the lhu, won schedule_select's potential-hazard rule (store > load > ALU) and
 *     then blocked the loads for a cycle ("blocking insn ... for 1 cycles").  QImode /s stores get
 *     no exemption, hence the QI-before/HI-after grouping.  CAST stores (`*(u16 *)(p + 0x12)`)
 *     are not /s, conflict with the lhu, and all 13 stay before it in source (LUID) order.
 *  2. The OT write MUST be a /s access (the P_TAG bitfield, §351): only the same exemption lets
 *     `D_800A5E60 = p` (non-/s, fixed) float above block 6's OT write (target idx 243-244).
 *  3. `la D_800AA60C` -> $t2 and 0xFF000000 -> $t3 is a local-alloc qty_compare tie decided by
 *     FLOW's ref count: `ob` must be assigned BEFORE block 1 and used in block 1's tag-side read
 *     too (13 refs, like the twin's compiler-made `la` pseudo).  combine then folds the symbol
 *     back into that first use (3-insn merge, the la def is re-emitted as newi2pat), giving the
 *     target's raw-symbol `lui $at/addu/lw %lo` for read 1 and `addu ..,$t2` for the other 11 —
 *     but flow counted 13 refs before combine ran (combine.c never adjusts reg_n_refs), so la
 *     (13 refs, life 171) outranks mhi (13 refs, life 183).  `ob` assigned AFTER the first read
 *     (the T3 draft) is 12 refs and loses by 1.2% -> the 24-row $t2/$t3 swap.
 *     Side effect: the folded first-read sum temp (r90) survives the merge with reg_n_refs = 2
 *     (combine.c:2313/2336 only zero it for a deleted i2; here the la def is newi2pat), is in no
 *     insn, so reload1.c alter_reg gives it a 4-byte slot -> the 8-byte-rounded `vars= 8` that IS
 *     the target's 0x18 frame.  So the T3 draft's `u32 pad[2]` must go (with it: frame 0x20).
 *  Everything else is the twin's byte-proven shape: the multi-set tag RMW `t = *p; t &= FF00;
 *  t |= v; *p = t` (no birthing boost -> the tag load fills the lhu->sll gap and the tpage
 *  constants float to the top, §501-H), `v` computed BEFORE `t &= 0xFF000000`, the double mask
 *  `(ot & m24) & m24` (m24 = 19 refs -> $t1), `x0 = arg0 + 0x100` as an expression (the last one
 *  ties into $a0), chained `*(p+8) = *(p+9) = *(p+0xA) = 0x80` (stores 0xA, 9, 8).
 *  TU spelling: the TU declares `extern void func_800CF6D0(s32 a0, u32 a1);` — define it so.
 */
extern u8 *D_800A5E60;
extern u8 D_800AA60C[];
extern s16 D_800B9A02;

void func_800CF6D0(s32 arg0, u32 arg1) {
    u8 *p;
    typedef struct { u32 addr:24; u32 len:8; } P_TAG;
    u8 *ob;
    u32 m24;

    p = D_800A5E60;
    arg0 -= 0xA0;
    arg1 -= 0x78;
    ob = D_800AA60C;

    *(u8 *)(p + 0x3) = 5;
    *(u32 *)(p + 0x4) = 0xE1000089;
    *(u8 *)(p + 0xB) = 0x64;
    *(u16 *)(p + 0x12) = 0x7940;
    *(u8 *)(p + 0x8) = *(u8 *)(p + 0x9) = *(u8 *)(p + 0xA) = 0x80;
    *(s16 *)(p + 0xC) = arg0;
    *(s16 *)(p + 0xE) = arg1;
    *(u8 *)(p + 0x10) = 0;
    *(u8 *)(p + 0x11) = 0;
    *(s16 *)(p + 0x14) = 0x100;
    *(s16 *)(p + 0x16) = 0x100;
    m24 = 0xFFFFFF;
    {
        u32 v = (*(u32 *)((s32)ob + (((u16)D_800B9A02) << 14)) & m24) & m24;
        u32 t = *(u32 *)p;
        t &= 0xFF000000;
        t |= v;
        *(u32 *)p = t;
    }
    ((P_TAG *)(u32 *)((s32)ob + (((u16)D_800B9A02) << 14)))->addr = (u32)p;
    p += 0x18;

    *(u8 *)(p + 0x3) = 5;
    *(u32 *)(p + 0x4) = 0xE100008B;
    *(u8 *)(p + 0xB) = 0x64;
    *(u16 *)(p + 0x12) = 0x7940;
    *(u8 *)(p + 0x8) = *(u8 *)(p + 0x9) = *(u8 *)(p + 0xA) = 0x80;
    *(s16 *)(p + 0xC) = arg0 + 0x100;
    *(s16 *)(p + 0xE) = arg1;
    *(u8 *)(p + 0x10) = 0;
    *(u8 *)(p + 0x11) = 0;
    *(s16 *)(p + 0x14) = 0x100;
    *(s16 *)(p + 0x16) = 0x100;
    {
        u32 v = (*(u32 *)((s32)ob + (((u16)D_800B9A02) << 14)) & m24) & m24;
        u32 t = *(u32 *)p;
        t &= 0xFF000000;
        t |= v;
        *(u32 *)p = t;
    }
    ((P_TAG *)(u32 *)((s32)ob + (((u16)D_800B9A02) << 14)))->addr = (u32)p;
    p += 0x18;

    *(u8 *)(p + 0x3) = 5;
    *(u32 *)(p + 0x4) = 0xE100008D;
    *(u8 *)(p + 0xB) = 0x64;
    *(u16 *)(p + 0x12) = 0x7940;
    *(u8 *)(p + 0x8) = *(u8 *)(p + 0x9) = *(u8 *)(p + 0xA) = 0x80;
    *(s16 *)(p + 0xC) = arg0 + 0x200;
    *(s16 *)(p + 0xE) = arg1;
    *(u8 *)(p + 0x10) = 0;
    *(u8 *)(p + 0x11) = 0;
    *(s16 *)(p + 0x14) = 0x100;
    *(s16 *)(p + 0x16) = 0x100;
    {
        u32 v = (*(u32 *)((s32)ob + (((u16)D_800B9A02) << 14)) & m24) & m24;
        u32 t = *(u32 *)p;
        t &= 0xFF000000;
        t |= v;
        *(u32 *)p = t;
    }
    ((P_TAG *)(u32 *)((s32)ob + (((u16)D_800B9A02) << 14)))->addr = (u32)p;
    p += 0x18;

    *(u8 *)(p + 0x3) = 5;
    *(u32 *)(p + 0x4) = 0xE100008F;
    *(u8 *)(p + 0xB) = 0x64;
    *(u16 *)(p + 0x12) = 0x7940;
    *(u8 *)(p + 0x8) = *(u8 *)(p + 0x9) = *(u8 *)(p + 0xA) = 0x80;
    *(s16 *)(p + 0xC) = arg0 + 0x300;
    *(s16 *)(p + 0xE) = arg1;
    *(u8 *)(p + 0x10) = 0;
    *(u8 *)(p + 0x11) = 0;
    *(s16 *)(p + 0x14) = 0x40;
    *(s16 *)(p + 0x16) = 0x100;
    {
        u32 v = (*(u32 *)((s32)ob + (((u16)D_800B9A02) << 14)) & m24) & m24;
        u32 t = *(u32 *)p;
        t &= 0xFF000000;
        t |= v;
        *(u32 *)p = t;
    }
    ((P_TAG *)(u32 *)((s32)ob + (((u16)D_800B9A02) << 14)))->addr = (u32)p;
    p += 0x18;

    *(u8 *)(p + 0x3) = 5;
    *(u32 *)(p + 0x4) = 0xE1000086;
    *(u8 *)(p + 0xB) = 0x64;
    *(u16 *)(p + 0x12) = 0x7880;
    *(u8 *)(p + 0x8) = *(u8 *)(p + 0x9) = *(u8 *)(p + 0xA) = 0x80;
    *(s16 *)(p + 0xC) = -0xA0;
    *(s16 *)(p + 0xE) = -0x78;
    *(u8 *)(p + 0x10) = 0x20;
    *(u8 *)(p + 0x11) = 0;
    *(s16 *)(p + 0x14) = 0xA0;
    *(s16 *)(p + 0x16) = 0x100;
    {
        u32 v = (*(u32 *)((s32)ob + (((u16)D_800B9A02) << 14)) & m24) & m24;
        u32 t = *(u32 *)p;
        t &= 0xFF000000;
        t |= v;
        *(u32 *)p = t;
    }
    ((P_TAG *)(u32 *)((s32)ob + (((u16)D_800B9A02) << 14)))->addr = (u32)p;
    p += 0x18;

    *(u8 *)(p + 0x3) = 5;
    *(u32 *)(p + 0x4) = 0xE1000087;
    *(u8 *)(p + 0xB) = 0x64;
    *(u16 *)(p + 0x12) = 0x7880;
    *(u8 *)(p + 0x8) = *(u8 *)(p + 0x9) = *(u8 *)(p + 0xA) = 0x80;
    *(s16 *)(p + 0xC) = 0;
    *(s16 *)(p + 0xE) = -0x78;
    *(u8 *)(p + 0x10) = 0x40;
    *(u8 *)(p + 0x11) = 0;
    *(s16 *)(p + 0x14) = 0xA0;
    *(s16 *)(p + 0x16) = 0x100;
    {
        u32 v = (*(u32 *)((s32)ob + (((u16)D_800B9A02) << 14)) & m24) & m24;
        u32 t = *(u32 *)p;
        t &= 0xFF000000;
        t |= v;
        *(u32 *)p = t;
    }
    ((P_TAG *)(u32 *)((s32)ob + (((u16)D_800B9A02) << 14)))->addr = (u32)p;
    p += 0x18;

    D_800A5E60 = p;
}

