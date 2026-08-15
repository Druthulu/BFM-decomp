#include "common.h"
#include "psyq/libcd.h"
#include "shared/clearTbl40.h"  /* dedup group I0: func_80037004 / func_80037334 share one body */

INCLUDE_ASM("asm/nonmatchings/800", func_800123F0);

INCLUDE_ASM("asm/nonmatchings/800", func_80012558);

INCLUDE_ASM("asm/nonmatchings/800", func_800126C4);

INCLUDE_ASM("asm/nonmatchings/800", func_8001282C);


extern void func_80014070(void* a0, void* a1);
extern void func_800128EC(void* a0, void* a1);

void func_800128B4(void* a0)
{
    s32 local_buffer[3];

    func_80014070(a0, local_buffer);
    func_800128EC(local_buffer, a0);
}

INCLUDE_ASM("asm/nonmatchings/800", func_800128EC);

INCLUDE_ASM("asm/nonmatchings/800", func_800129CC);

INCLUDE_ASM("asm/nonmatchings/800", func_80012A60);

s32 func_80012AB0(s32 arg0, s32 arg1) {
    return (arg0 - arg1) & 0xFFF;
}

INCLUDE_ASM("asm/nonmatchings/800", func_80012ABC);

INCLUDE_ASM("asm/nonmatchings/800", func_80012B04);

INCLUDE_ASM("asm/nonmatchings/800", func_80012B58);

INCLUDE_ASM("asm/nonmatchings/800", func_80012C6C);

INCLUDE_ASM("asm/nonmatchings/800", func_80012CB8);

INCLUDE_ASM("asm/nonmatchings/800", func_80012D0C);

INCLUDE_ASM("asm/nonmatchings/800", func_80012DBC);

INCLUDE_ASM("asm/nonmatchings/800", func_80012E0C);

INCLUDE_ASM("asm/nonmatchings/800", func_80012E6C);

INCLUDE_ASM("asm/nonmatchings/800", func_80012F74);

INCLUDE_ASM("asm/nonmatchings/800", func_80012FC8);

INCLUDE_ASM("asm/nonmatchings/800", func_80013028);

INCLUDE_ASM("asm/nonmatchings/800", func_800130D0);

INCLUDE_ASM("asm/nonmatchings/800", func_8001311C);

INCLUDE_ASM("asm/nonmatchings/800", func_80013154);


extern s32 func_80013228(s32 *a0, s32 *a1);
extern s32 func_80047D3C(s32 a0);

s32 func_80013200(s32 *a0, s32 *a1) {
    return func_80047D3C(func_80013228(a0, a1));
}


extern void Square0(s32 *a0, s32 *a1);

s32 func_80013228(s32 *a0, s32 *a1) {
    s32 diff[3];
    s32 result[3];

    diff[0] = a0[0] - a1[0];
    diff[1] = a0[1] - a1[1];
    diff[2] = a0[2] - a1[2];

    Square0(diff, result);

    return result[0] + result[1] + result[2];
}


extern s32 func_80047D3C(s32 a0);

typedef struct {
    s16 vx, vy, vz, pad;
} SVECTOR_80013294;

s32 func_80013294(SVECTOR_80013294 *a0, SVECTOR_80013294 *a1) {
    return func_80047D3C(func_800132BC(a0, a1));
}


extern void Square0(s32 *a0, s32 *a1);

typedef struct {
    s16 vx, vy, vz, pad;
} SVECTOR;

s32 func_800132BC(SVECTOR *a0, SVECTOR *a1) {
    s32 diff[3];
    s32 result[3];

    diff[0] = a0->vx - a1->vx;
    diff[1] = a0->vy - a1->vy;
    diff[2] = a0->vz - a1->vz;

    Square0(diff, result);

    return result[0] + result[1] + result[2];
}


extern s32 func_80047D3C(s32 a0);

void func_80013328(s32 *a0, s32 *a1) {
    s32 result;
    result = func_80013350(a0, a1);
    func_80047D3C(result);
}


extern void Square0(s32 *a0, s32 *a1);

s32 func_80013350(s32 *a0, s32 *a1) {
    s32 diff[3];
    s32 result[3];

    diff[0] = *(s16 *)((u8 *)a0 + 2) - *(s16 *)((u8 *)a1 + 2);
    diff[1] = *(s16 *)((u8 *)a0 + 6) - *(s16 *)((u8 *)a1 + 6);
    diff[2] = *(s16 *)((u8 *)a0 + 10) - *(s16 *)((u8 *)a1 + 10);

    Square0(diff, result);

    return result[0] + result[1] + result[2];
}


extern s32 func_80047D3C(s32 a0);

s32 func_800133BC(void) {
    s32 result = func_800133E4();
    return func_80047D3C(result);
}


extern void Square0(s32 *a0, s32 *a1);

s32 func_800133E4(s16 *a0, s16 *a1) {
    s32 diff[3];
    s32 result[3];

    diff[0] = a0[0] - a1[1];
    diff[1] = a0[1] - a1[3];
    diff[2] = a0[2] - a1[5];

    Square0(diff, result);

    return result[0] + result[1] + result[2];
}


extern s32 func_80013478(void);
extern s32 func_80047D3C(s32 a0);

s32 func_80013450(void) {
    s32 result = func_80013478();
    return func_80047D3C(result);
}

INCLUDE_ASM("asm/nonmatchings/800", func_80013478);

INCLUDE_ASM("asm/nonmatchings/800", func_800134FC);

INCLUDE_ASM("asm/nonmatchings/800", func_80013694);

INCLUDE_ASM("asm/nonmatchings/800", func_8001382C);

INCLUDE_ASM("asm/nonmatchings/800", func_800139C8);

INCLUDE_ASM("asm/nonmatchings/800", func_80013B64);

INCLUDE_ASM("asm/nonmatchings/800", func_80013CFC);

INCLUDE_ASM("asm/nonmatchings/800", func_80013E94);

INCLUDE_ASM("asm/nonmatchings/800", func_80013ED0);


void func_80013F3C(void *ptr) {
    s16 *p = (s16 *)ptr;
    p[0] = 0x1000;
    p[1] = 0;
    p[2] = 0;
    p[3] = 0;
    p[4] = 0x1000;
    p[5] = 0;
    p[6] = 0;
    p[7] = 0;
    p[8] = 0x1000;
}


void func_80013F68(s16 *a0) {
    s16 v0;

    v0 = -0x1000;
    a0[2] = v0;
    v0 = 0x1000;
    a0[0] = 0;
    a0[1] = 0;
    a0[3] = 0;
    a0[4] = v0;
    a0[5] = 0;
    a0[6] = v0;
    a0[7] = 0;
    a0[8] = 0;
}

INCLUDE_ASM("asm/nonmatchings/800", func_80013F98);

INCLUDE_ASM("asm/nonmatchings/800", func_80013FBC);

INCLUDE_ASM("asm/nonmatchings/800", func_80013FE0);

INCLUDE_ASM("asm/nonmatchings/800", func_80014004);

INCLUDE_ASM("asm/nonmatchings/800", func_80014028);

INCLUDE_ASM("asm/nonmatchings/800", func_8001404C);

INCLUDE_ASM("asm/nonmatchings/800", func_80014070);

INCLUDE_ASM("asm/nonmatchings/800", func_80014094);

INCLUDE_ASM("asm/nonmatchings/800", func_800140B8);

INCLUDE_ASM("asm/nonmatchings/800", func_80014128);

INCLUDE_ASM("asm/nonmatchings/800", func_80014148);


typedef struct { u8 b[8]; } Blk8;

extern void ApplyMatrixSV(void *a0, void *a1, void *a2);

void func_80014168(void *a0, void *a1) {
    Blk8 local;

    local = *(Blk8 *)a1;
    ApplyMatrixSV(a0, &local, a1);
}

INCLUDE_ASM("asm/nonmatchings/800", func_800141AC);


extern void func_80059234(s32);
extern void func_800594CC(s32);
extern void func_80059658(s32);
extern void func_80016714(void *a0, s32 a1);
extern void func_800142C8(void);
extern u8 D_800BA118;

void func_800141F0(void) {
    func_80059234(0);
    func_800594CC(0);
    func_80059658(0);
    func_80016714(&D_800BA118, 0x98);
    func_800142C8();
}

INCLUDE_ASM("asm/nonmatchings/800", func_80014238);


extern void func_80029044(void);
extern void func_8002906C(void);
extern void func_80029094(void);
extern void func_80029218(void);
extern void func_8001903C(void);
extern void func_80018FC8(void);
extern void func_8001B324(void);
extern void func_80028FDC(s32);
extern void func_80029020(s32);
extern void func_80028DBC(s32);
extern void func_80028E00(s32);

void func_800142C8(void) {
    func_80029044();
    func_8002906C();
    func_80029094();
    func_80029218();
    func_8001903C();
    func_80018FC8();
    func_8001B324();
    func_80028FDC(0x7);
    func_80029020(0x7);
    func_80028DBC(0);
    func_80028E00(0);
}


extern void func_80029044(void);
extern void func_8002906C(void);
extern void func_80029094(void);
extern void func_80028FDC(s32);
extern void func_80029020(s32);
extern void func_80028DBC(s32);
extern void func_80028E00(s32);
extern void func_80029274(void);

void func_80014338(void) {
    func_80029044();
    func_8002906C();
    func_80029094();
    func_80028FDC(0x7);
    func_80029020(0x7);
    func_80028DBC(0);
    func_80028E00(0);
    func_80029274();
}

INCLUDE_ASM("asm/nonmatchings/800", func_80014390);

INCLUDE_ASM("asm/nonmatchings/800", func_800143AC);

INCLUDE_ASM("asm/nonmatchings/800", func_80014444);

INCLUDE_ASM("asm/nonmatchings/800", func_800144D4);

void func_80014554(void) {
}

void func_8001455C(void) {
}

INCLUDE_ASM("asm/nonmatchings/800", func_80014564);

INCLUDE_ASM("asm/nonmatchings/800", func_80014588);

INCLUDE_ASM("asm/nonmatchings/800", func_800145EC);

INCLUDE_ASM("asm/nonmatchings/800", func_800146B0);


extern void func_80059888(void *a0, s32 a1, s32 a2, s32 a3);

void func_80014774(void) {
    s16 local[4];

    local[0] = 0;
    local[1] = 0;
    local[2] = 0x280;
    local[3] = 0x1E0;

    func_80059888((void *)local, 0, 0, 0);
}

INCLUDE_ASM("asm/nonmatchings/800", func_800147B8);


extern void func_8005CF08(void);
extern void InitHeap(void *a0, s32 a1);
extern void func_8005CF18(void);

void func_80014928(void) {
    func_8005CF08();
    InitHeap((void *)0x801FF800, 0x800);
    func_8005CF18();
}


extern void func_80014998(void);
extern u8 D_800AF7C4;
extern u8 D_800AF7C3;
extern u8 D_800AF7C2;

void func_80014960(void) {
    D_800AF7C4 = 0;
    D_800AF7C3 = 0;
    D_800AF7C2 = 0;
    func_80014998();
}

INCLUDE_ASM("asm/nonmatchings/800", func_80014998);

INCLUDE_ASM("asm/nonmatchings/800", func_800149E0);

INCLUDE_ASM("asm/nonmatchings/800", func_80014B10);


extern u16 D_80078DDA;

u16 func_80014BFC(u32 a0) {
    u32 offset;
    a0 &= 0xFF;
    offset = a0 * 76;
    return *(u16*)((u32)&D_80078DDA + offset);
}


extern u8 D_80078D98;

u8 func_80014C28(u32 a0) {
    u32 offset;
    a0 &= 0xFF;
    offset = a0 * 76;
    offset = offset + (u32)&D_80078D98;
    return *(u8*)(offset);
}

INCLUDE_ASM("asm/nonmatchings/800", func_80014C54);

INCLUDE_ASM("asm/nonmatchings/800", func_80014CAC);


extern u8 D_80078D98;

u8 func_80014CF8(u32 a0, u32 a1) {
    u32 offset;
    a0 &= 0xFF;
    offset = a0 * 76;
    offset = offset + (u32)&D_80078D98;
    a1 &= 0xFF;
    offset = offset + a1;
    return *(u8*)(offset + 0x32);
}


extern u8 D_80078D98;

u8 func_80014D30(u32 a0, u32 a1) {
    u32 v0;
    a0 = a0 & 0xFF;
    v0 = a0 << 2;
    v0 = v0 + a0;
    v0 = v0 << 2;
    v0 = v0 - a0;
    v0 = v0 << 2;
    v0 = v0 + (u32)&D_80078D98;
    a1 = a1 & 0xFF;
    v0 = v0 + a1;
    return *(u8*)(v0 + 0x42);
}


extern u8 D_80078DCA;

u16 func_80014D68(u32 a0) {
    u32 offset;
    a0 &= 0xFF;
    offset = a0 * 76;
    offset = offset + (u32)&D_80078DCA;
    return *(u16*)offset;
}


extern u8 D_80078DD2;

s32 func_80014D94(s32 a0) {
    a0 &= 0xFF;
    return *(u16*)((u32)&D_80078DD2 + (a0 * 76));
}


extern u8 D_80078D98;

u8 func_80014DC0(u32 a0) {
    u32 offset;
    a0 &= 0xFF;
    offset = a0 * 76;
    offset = offset + (u32)&D_80078D98;
    return *(u8*)offset;
}


extern u8 D_80078D98;

u8 func_80014DEC(s32 a0, s32 a1) {
    register s32 v0 __asm__("$2");
    a0 = a0 & 0xFF;
    v0 = (a0 << 2) + a0;
    v0 = (v0 << 2) - a0;
    v0 = v0 << 2;
    v0 = v0 + (s32)&D_80078D98;
    a1 = a1 & 0xFF;
    v0 = v0 + a1;
    return *(u8 *)(v0 + 0x32);
}


extern s32 func_80015018(s32 a0);
extern s32 func_80014ED4(s32 a0);

s32 func_80014E24(s32 a0, s32 a1, s32 a2) {
    u16 result;
    s32 tmp;

    /* a0's masked-byte value is genuinely consumed as an argument to BOTH callees below
     * (their bodies happen to ignore it, but the caller must still materialize it) --
     * the opaque asm keeps gcc-2.7.2 from folding this into a per-branch recompute or
     * eliding it outright, which is what a plain "a0 &= 0xFF;" statement does when a0
     * is otherwise unused. See matching-cookbook.md L2916 (opaque asm-COPY) for the
     * precedent: a real, non-hard-reg opcode asm is used only when no pure-C spelling
     * reproduces the target's single, pre-branch materialization. */
    __asm__("andi %0, %1, 0xff" : "=r"(tmp) : "r"(a0));

    a1 &= 0xFF;

    if (a1 == 1) {
        result = func_80015018(tmp);
    } else {
        result = func_80014ED4(tmp);
    }

    result &= 0xFFFF;

    // Check if all bits of a2 are set in result
    return (u32)(((u32)result & (u32)a2) ^ (u32)a2) < 1;
}


extern s32 func_80015018(s32 a0);
extern s32 func_80014ED4(s32 a0);

s32 func_80014E80(s32 a0, s32 a1) {
    s32 result;
    a0 = a0 & 0xFF;
    if (a0 == 1) {
        result = func_80015018(0);
    } else {
        result = func_80014ED4(0);
    }
    result = result & 0xFFFF;
    result = result & a1;
    return (result != 0) ? 1 : 0;
}

INCLUDE_ASM("asm/nonmatchings/800", func_80014ED4);

INCLUDE_ASM("asm/nonmatchings/800", func_80015018);

INCLUDE_ASM("asm/nonmatchings/800", func_80015118);

void func_8001513C(void) {
}

INCLUDE_ASM("asm/nonmatchings/800", func_80015144);

INCLUDE_ASM("asm/nonmatchings/800", func_80015208);

INCLUDE_ASM("asm/nonmatchings/800", func_800152F4);

INCLUDE_ASM("asm/nonmatchings/800", func_80015310);

INCLUDE_ASM("asm/nonmatchings/800", func_8001534C);


void func_800153A4(void *a0, s32 a1, s16 a2, s16 a3, u8 arg4, u8 arg5) {
    *(s16 *)(a0 + 0) = 1;
    *(s16 *)(a0 + 2) = a2;
    *(s16 *)(a0 + 4) = a3;
    *(s32 *)(a0 + 8) = a1;
    *(u8 *)(a0 + 12) = arg4;
    *(u8 *)(a0 + 13) = arg5;
}

INCLUDE_ASM("asm/nonmatchings/800", func_800153CC);


void func_80015424(void *a0, s32 a1, s16 a2, s16 a3, s8 a4, s8 a5) {
    *(s16 *)a0 = 2;
    *(s16 *)(a0 + 2) = a2;
    *(s16 *)(a0 + 4) = a3;
    *(s32 *)(a0 + 8) = a1;
    *(s8 *)(a0 + 0xC) = a4;
    *(s8 *)(a0 + 0xD) = a5;
}

INCLUDE_ASM("asm/nonmatchings/800", func_8001544C);

INCLUDE_ASM("asm/nonmatchings/800", func_80015498);

INCLUDE_ASM("asm/nonmatchings/800", func_80015608);

INCLUDE_ASM("asm/nonmatchings/800", func_80015760);

INCLUDE_ASM("asm/nonmatchings/800", func_80015908);

INCLUDE_ASM("asm/nonmatchings/800", func_80015954);

INCLUDE_ASM("asm/nonmatchings/800", func_80015978);

INCLUDE_ASM("asm/nonmatchings/800", func_8001599C);

INCLUDE_ASM("asm/nonmatchings/800", func_800159C0);

INCLUDE_ASM("asm/nonmatchings/800", func_800159E4);

INCLUDE_ASM("asm/nonmatchings/800", func_80015A08);

INCLUDE_ASM("asm/nonmatchings/800", func_80015A2C);

INCLUDE_ASM("asm/nonmatchings/800", func_80015A50);

#ifdef NON_MATCHING
/* uint -> packed BCD (9 digits, ÷ powers of 10). All idioms match under the pinned
 * triple (divu+break div-by-zero via --expand-div, multu 0xCCCCCCCD + srl 3 for ÷10);
 * residual diff is a loop-setup instruction-scheduling permutation (li counter vs the
 * hoisted magic constant) — a decomp-permuter target. See docs/matching-cookbook.md. */
u32 func_80015A74(u32 param_1) {
    u32 result;
    s32 i;
    u32 divisor;

    divisor = 1000000000;
    result = 0;
    for (i = 9; i >= 0; i--) {
        result = (result << 4) | (param_1 / divisor);
        param_1 = param_1 % divisor;
        divisor = divisor / 10;
    }
    return result;
}
#else
INCLUDE_ASM("asm/nonmatchings/800", func_80015A74);
#endif

INCLUDE_ASM("asm/nonmatchings/800", func_80015AD0);

INCLUDE_ASM("asm/nonmatchings/800", func_80015B6C);


/* func_80015D4C — allocate an 0x18-byte flat-shaded quad GPU packet, fill its
 * tag/color/code bytes and the four (x,y) corners from (a0,a1,a2,a3) =
 * (x, y, w, h), then link it into the current double-buffer's OT at depth
 * arg7 via the open-coded PSY-Q `addPrim` RMW pair, and (only when arg8 < 4)
 * notify func_80016638.
 *
 * Sibling idiom: src/md_SC07_004/md_SC07_004.c func_801AADA8 (MATCHED) —
 * the addPrim pair over D_800A651C[bidx].a in ARRAY_REF form, and the
 * func_80016638(&D_800A6518[bidx*20], depth, flag) call form.
 *
 * SECOND-PASS FIXES (this file was NEAR/40 before; both were required):
 *
 *  1. BRANCH POLARITY WAS INVERTED.  The target is
 *         sltiu $t2, $s0, 0x4   ;  beqz $t2, <skip>
 *     i.e. the 0x2A code byte is written and func_80016638 is called when
 *     arg8 < 4, not when arg8 >= 4.  The first pass wrote `arg8 >= 4`, which
 *     emits the same sltiu but `bnez` — a real semantic difference that the
 *     instruction-shape diff hid inside the 40-instruction register cascade.
 *
 *  2. tag0 PINNED TO $4 ($a0) — the load-bearing regalloc fix.  Residual was
 *     a *uniform +1 register-slot shift*: target allocates the call-clobbered
 *     pseudo set {a0,a1,a2,a3,t0,t1,t2,t3}, the draft allocated
 *     {v1,a0,a1,a2,a3,t0,t1,t2}.  Root cause: gcc's sched1 placed the tag
 *     load (`lw <tag0>, 0(p)`) *after* the last use of the x+w temp, so tag0
 *     could reuse $v1; the target schedules the tag load 14 insns earlier, so
 *     the two live ranges overlap and tag0 must take $a0, pushing every later
 *     pseudo up one slot.
 *     Statement-order (lever A) is INERT here — sweeping the `tag0 = *(u32*)p`
 *     statement through all 6 legal source positions between the p[7]
 *     conditional and the addPrim pair gave 40 mismatched every time; sched1
 *     normalises the DAG regardless of source position.  The register pin is
 *     what changes the allocation, and pinning tag0 (the value whose slot
 *     *causes* the cascade) is the right handle — this is exactly the lever
 *     func_801AADA8's own header documents ("tag0 ... pinned to $4 ($a0) —
 *     needed to reproduce the target's exact a2/a3/t0/t1 register picks for
 *     the addPrim RMW pair").
 *     Pin sweep, for the record: $4 -> MATCH, $5 -> 9, $6 -> 16, $7 -> 16,
 *     $8 -> 31.  Note the first pass pinned temp_v0 instead ($8) and got a
 *     spurious extra move — pinning the *consumer* of the cascade rather than
 *     its cause (cookbook §175 lever B: pin the interloper, not the value you
 *     care about; here the interloper is the tag word aliasing $v1).
 *
 * vx/vy stay pinned to $18/$17 ($s2/$s1) from the first pass — the target's
 * `addu $s2,$s3,$zero` / `addu $s1,$s4,$zero` corner-copy pair.
 *
 * Symbol audit (§174 law 1c, done after MATCH): every symbol re-checked
 * against the target .s relocation lines — jal func_80010A08, jal
 * func_80016638, %hi/%lo(D_800B9A02) via lhu (u16, not s16), %hi/%lo
 * (D_800A651C) via lw, %lo(D_800A6518) via addiu (address-of).  Store sides
 * verified: `sw $a0,0($t0)` is the packet tag, `sw $v0,0($a1)` is the OT slot.
 * src/800.c declares none of these, so no TU-declaration conflict (law 2/3).
 */
typedef struct { s32 a; s32 b[4]; } OtBlk_80016450;

extern void *func_80010A08(s32 a0);
extern u16 D_800B9A02;
extern u8 D_800A6518[];
extern void func_80016638(void *a0, s32 a1, s32 a2);

void func_80015D4C(s32 a0, s32 a1, s32 a2, s32 a3, u8 arg4, u8 arg5, u8 arg6, u16 arg7, u16 arg8)
{
    extern OtBlk_80016450 D_800A651C[];   /* block scope: engine_core.h's DEFINE_ macros declare this symbol scalar in their own bodies */
    void *temp_v0;
    register s16 vx __asm__("$18");
    register s16 vy __asm__("$17");
    register u32 tag0 __asm__("$4");
    s32 depth4;

    temp_v0 = func_80010A08(0x18);
    *(u8 *)((u8 *)temp_v0 + 3) = 5;
    *(u8 *)((u8 *)temp_v0 + 7) = 0x28;
    vx = a0;
    vy = a1;
    if (arg8 < 4) {
        *(u8 *)((u8 *)temp_v0 + 7) = 0x2A;
    }

    *(u8 *)((u8 *)temp_v0 + 4) = arg4;
    *(u8 *)((u8 *)temp_v0 + 5) = arg5;
    *(u8 *)((u8 *)temp_v0 + 6) = arg6;
    *(s16 *)((u8 *)temp_v0 + 8) = vx;
    *(s16 *)((u8 *)temp_v0 + 0xA) = vy;
    *(s16 *)((u8 *)temp_v0 + 0xC) = a0 + a2;
    *(s16 *)((u8 *)temp_v0 + 0xE) = vy;
    *(s16 *)((u8 *)temp_v0 + 0x10) = vx;
    tag0 = *(u32 *)temp_v0;
    *(s16 *)((u8 *)temp_v0 + 0x12) = a1 + a3;
    *(s16 *)((u8 *)temp_v0 + 0x14) = a0 + a2;
    *(s16 *)((u8 *)temp_v0 + 0x16) = a1 + a3;

    depth4 = arg7 * 4;
    *(u32 *)temp_v0 = (tag0 & 0xFF000000) |
        (*(u32 *)(depth4 + D_800A651C[D_800B9A02].a) & 0xFFFFFF);
    *(u32 *)(depth4 + D_800A651C[D_800B9A02].a) =
        (*(u32 *)(depth4 + D_800A651C[D_800B9A02].a) & 0xFF000000) |
        ((u32)temp_v0 & 0xFFFFFF);
    if (arg8 < 4) {
        func_80016638(&D_800A6518[D_800B9A02 * 20], arg7, arg8);
    }
}

INCLUDE_ASM("asm/nonmatchings/800", func_80015F04);

INCLUDE_ASM("asm/nonmatchings/800", func_80016110);

INCLUDE_ASM("asm/nonmatchings/800", func_80016224);


/* func_80016450 — main/800: allocate a 0x18-byte flat semi-transparent quad
 * (POLY_F4, code 0x2A) covering the whole 320x240 screen at brightness a0,
 * PSY-Q addPrim() it onto one of two OT tables selected by (u16)a1, then hand
 * the owning env block to func_80016638.
 *
 * @class: (was regalloc-order / sched)
 * @stuck: none — MATCH, 122/122 instructions, byte-exact under match_one, and
 *   all 27 relocations hand-checked one-to-one against asm/nonmatchings/800/
 *   func_80016450.s (same offsets, same symbols, same order): func_80010A08,
 *   6x D_800B9A02, 2x D_800A651C, D_800A6518, 2x D_800AE7BC, D_800AE7B8,
 *   func_80016638.  Destination TU src/800.c already declares
 *   `extern void func_80016450(s32 a0, s32 a1);` (L680) — adopted verbatim.
 *   No other file-scope decl of any symbol used here exists in the
 *   preprocessed TU, so these externs merge silently.
 *
 * ---------------------------------------------------------------------------
 * WHAT THIS FUNCTION ACTUALLY IS
 *
 * The and-0xFF000000 / and-0x00FFFFFF / or triple is the libgpu P_TAG 24-bit
 * `addr` BITFIELD, i.e. the PSY-Q macro pair
 *     addPrim(ot, p) == setaddr(p, getaddr(ot)), setaddr(ot, p)
 * The macro argument `ot` is textually duplicated, which is why D_800B9A02 and
 * the OT-base load are each emitted TWICE per branch.  Recognising that is what
 * fixes the instruction count; the rest is register/schedule steering.
 *
 * ---------------------------------------------------------------------------
 * LEVERS (each byte-verified by removing it and re-scoring)
 *
 *  1. CHAINED ASSIGNMENT reproduces the reversed store pairs.
 *     `p->x0 = p->x2 = K` emits sh K,0x10 THEN sh K,0x8 and keeps K in ONE
 *     constant register across both stores.  Same for `p->r0=p->g0=p->b0=a0`.
 *     (Inherited from the first pass — natural source order gives four separate
 *     constant registers and the wrong store order.)
 *
 *  2. `*(u32 *)p`, NOT `p->tag`.  A struct-member store does NOT kill a plain
 *     global's CSE in gcc-2.7.2, so `p->tag` cached D_800B9A02/D_800A651C and
 *     produced 110 ins instead of 122.  A non-MEM_IN_STRUCT_P store kills
 *     everything and reproduces all six reloads exactly.  (First pass.)
 *
 *  3. ⚠ THE ONE THAT UNSTUCK THE 23-MISMATCH RESIDUAL — DO NOT bind the OT slot
 *     address to a function-scope local used in BOTH addPrim halves.  The first
 *     pass wrote `ot = <addr>; …*ot…; ot = <addr>; *ot = …;` in each arm.  One
 *     pseudo with two def/use pairs = ONE live range spanning the whole arm, so
 *     local-alloc gives it a DEDICATED register ($t0) and shifts every other
 *     temp one slot down.  The target instead computes the address into a
 *     register that DIES on the same insn (`addu $v0,$a2,$v0` in the first half,
 *     `addu $a2,$a2,$v0` in the second).  The fix is the HYBRID shape used by
 *     the sibling match func_80185944 (src/ov_SC03_119/..._jr_8017FB84.c):
 *       - first half: the address expression FULLY INLINED (no local at all);
 *       - second half: its own short-lived binding.
 *     This alone rebuilt the whole `addu/lw` shape (23 -> the register-name
 *     residual below).  Note the first pass had measured "fully inlining" (45)
 *     and "splitting it in two" (44) as WORSE — because it applied each to BOTH
 *     halves.  It is the ASYMMETRY that matches.
 *
 *  4. OPERAND ORDER IS SOURCE ORDER: `i4 + D_800A651C[…].a`, not
 *     `D_800A651C[…].a + i4`.  gcc-2.7.2 emits `addu $v0,$a2,$v0` from the
 *     former and `addu $v0,$v0,$a2` from the latter.  (13 -> ...)
 *
 *  5. SELF-ACCUMULATE TO REUSE THE DYING REGISTER.  The second half's
 *     `addu $a2,$a2,$v0` writes the OT address back into the SAME register that
 *     held idx*4.  A fresh local can never produce that (gcc will not clobber a
 *     still-named pinned value), but `i4 += D_800A651C[…].a;` — reusing the
 *     variable as its own accumulator — does, exactly.  9 -> 6.
 *
 *  6. THE ELSE ARM'S LAST 6 WERE A SCHEDULE SWAP, NOT ALLOCATION.  Target fills
 *     the `lhu D_800B9A02` load-delay slot with the tag load `lw $v1,0($t1)`
 *     and the `lw %lo(D_800AE7BC)` slot with `lui $a0,0xff00`; we had them
 *     exactly swapped, which also flipped D_800B9A02 $a0<->$v1.  This is
 *     gcc-2.7.2 sched.c's BIRTHING BOOST on a single-SET destination (the boost
 *     sinks the load to just before its consumer, and `potential_hazard` breaks
 *     the tie in the load's favour, so it is picked first = placed LAST).
 *     Cure = the func_80185944 recipe, both halves needed:
 *       (a) PIN the tag value (`register u32 pv __asm__("$3")`), and
 *       (b) give `pv` a SECOND SET with a zero-byte
 *           `__asm__ __volatile__("" : "=r"(pv));`  — REG_N_SETS != 1 kills the
 *           boost.  A plain C reassignment does NOT work (cse/flow removes it).
 *     PLACEMENT MATTERS: the dead asm must sit immediately after `pv`'s last
 *     use INSIDE the arm.  Putting it after the func_80016638 call (as the
 *     sibling does, where the call is in the same block) makes gcc keep $v1
 *     live across the jal here and costs +3 instructions (125 ins, 53 diff).
 *     6 -> 0.
 *
 *  PIN-TRIM LOG (all re-scored; three pins are the verified minimum):
 *    drop `m24` $a3 pin (then arm)   — MATCH   (kept as plain `register`)
 *    drop `mFF` $t0 pin (then arm)   — MATCH   (kept as plain `register`)
 *    drop `m24` $a2 pin (else arm)   — MATCH   (kept as plain `register`)
 *    all three dropped together      — MATCH   <= this file
 *    replace the mask LOCALS with bare literals — 3 mismatched (the locals are
 *      load-bearing: a literal is re-materialised per use and reschedules)
 *    drop `i4` $a2 pin               — 2 mismatched
 *    drop `pv` $a0 pin (then arm)    — 4 mismatched
 *    drop `pv` $v1 pin (else arm)    — 7 mismatched
 *    pin `p` to $t1                  — 123 ins, 113 mismatched (never pin p)
 */

/* engine_types.h-style OT block: 0x14 stride, the OT base pointer at +0 */

/* 0x18-byte POLY_F4 */
typedef struct {
    u8  addr[3];
    u8  len;
    u8  r0, g0, b0, code;
    s16 x0, y0;
    s16 x1, y1;
    s16 x2, y2;
    s16 x3, y3;
} F4_80016450;

extern void *func_80010A08(s32);
extern void func_80016638(void *a0, s32 a1, s32 a2);

extern u16 D_800B9A02;
extern u8 D_800A6518[];
extern OtBlk_80016450 D_800AE7BC[];
extern u8 D_800AE7B8[];

void func_80016450(s32 a0, s32 a1)
{
    extern OtBlk_80016450 D_800A651C[];   /* block scope: engine_core.h's DEFINE_ macros declare this symbol scalar inside their own bodies */
    F4_80016450 *p;
    u32 *ot;
    s32 idx;

    p = (F4_80016450 *)func_80010A08(0x18);

    p->len = 5;
    p->code = 0x2A;
    p->r0 = p->g0 = p->b0 = a0;
    p->x0 = p->x2 = -160;
    p->x1 = p->x3 = 160;
    p->y0 = p->y1 = -120;
    p->y2 = p->y3 = 120;
    idx = a1 & 0xFFFF;
    if (idx != 0) {
        register u32 m24 = 0x00FFFFFF;
        register u32 mFF = 0xFF000000;
        register s32 i4 __asm__("$6") = idx * 4;
        register u32 pv __asm__("$4");
        pv = *(u32 *)p;
        *(u32 *)p = (pv & mFF) | (*(u32 *)(i4 + D_800A651C[D_800B9A02].a) & m24);
        i4 += D_800A651C[D_800B9A02].a;
        *(u32 *)i4 = (*(u32 *)i4 & mFF) | ((u32)p & m24);
        func_80016638(&D_800A6518[D_800B9A02 * 20], idx, 1);
    } else {
        register u32 m24 = 0x00FFFFFF;
        register u32 pv __asm__("$3");
        pv = *(u32 *)p;
        *(u32 *)p = (pv & 0xFF000000) | (*(u32 *)D_800AE7BC[D_800B9A02].a & m24);
        __asm__ __volatile__("" : "=r"(pv));   /* zero-byte 2nd SET: kills the sched1 birthing boost */
        ot = (u32 *)D_800AE7BC[D_800B9A02].a;
        *ot = (*ot & 0xFF000000) | ((u32)p & m24);
        func_80016638(&D_800AE7B8[D_800B9A02 * 20], 0, 1);
    }
}

INCLUDE_ASM("asm/nonmatchings/800", func_80016638);


void func_800166E8(void *a0, s32 a1) {
    s32 local_buffer[2];
    register s32 v0 __asm__("$2");
    register s32 v1 __asm__("$3");

    __asm__ volatile("");  // Barrier to force stack allocation first

    if (a1 == 0)
        goto skip;

    v0 = a1 - 1;
    v1 = -1;

    do {
        *(u8 *)a0 = 0;
        v0--;
        a0 = (void *)((s32)a0 + 1);
    } while (v0 != v1);

skip:
    return;
}

#ifdef NON_MATCHING
/* bzero(p, n): n<4 byte path; else align-to-4 -> word-fill (sw) -> remainder bytes.
 * Logically correct and instruction-identical to the target EXCEPT gcc 2.7.2 emits a
 * phantom empty 16-byte stack frame here (target is frameless) — that one frame
 * prologue/epilogue is the entire residual. A decomp-permuter candidate (structural
 * permutation can flip frame allocation). See docs/matching-cookbook.md §4. */
void func_80016714(s8 *a0, s32 a1) {
    s32 v1;

    if (a1 < 4) {
        a1 = a1 - 1;
        if (a1 != -1) {
            do {
                *a0 = 0;
                a1 -= 1;
                a0 += 1;
            } while (a1 != -1);
        }
    } else {
        v1 = (s32)a0;
        if (((s32)a0 & 3) != 0) {
            do {
                *a0 = 0;
                a0 += 1;
                v1 += 1;
                a1 -= 1;
            } while ((v1 & 3) != 0);
        }
        v1 = (a1 >> 2) - 1;
        if (v1 != -1) {
            do {
                *(s32 *)a0 = 0;
                v1 -= 1;
                a0 += 4;
            } while (v1 != -1);
        }
        a1 = (a1 & 3) - 1;
        if (a1 != -1) {
            do {
                *a0 = 0;
                a1 -= 1;
                a0 += 1;
            } while (a1 != -1);
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/800", func_80016714);
#endif


extern void func_80016224(s32 a0, s32 a1);
extern u16 D_800AF7CE;

void func_800167B8(s32 a0) {
    a0 = ((u16)a0) < 4U ? 0xFF : 0x00;
    D_800AF7CE = 0;
    func_80016224(a0, 0);
}

INCLUDE_ASM("asm/nonmatchings/800", func_800167F0);

extern u16 D_800AF7CE;
void func_800168B4(void) {
    D_800AF7CE = 0;
}

INCLUDE_ASM("asm/nonmatchings/800", func_800168C4);


extern u16 D_800AF7CE;
extern void func_80016450(s32 a0, s32 a1);

void func_80016940(s32 a0) {
    s32 param = (((u32)a0 & 0xFFFF) < 4) ? 0xFF : 0x00;
    D_800AF7CE = 0;
    func_80016450(param, 0);
}

INCLUDE_ASM("asm/nonmatchings/800", func_80016978);

INCLUDE_ASM("asm/nonmatchings/800", func_80016A3C);

INCLUDE_ASM("asm/nonmatchings/800", func_80016A5C);

INCLUDE_ASM("asm/nonmatchings/800", func_80016A7C);

INCLUDE_ASM("asm/nonmatchings/800", func_80016B60);

INCLUDE_ASM("asm/nonmatchings/800", func_80016C28);

INCLUDE_ASM("asm/nonmatchings/800", func_80016D78);

INCLUDE_ASM("asm/nonmatchings/800", func_80016EB0);

INCLUDE_ASM("asm/nonmatchings/800", func_80016ED4);

INCLUDE_ASM("asm/nonmatchings/800", func_80016EF8);


/* ---- PsyQ GTE inline macros (same spelling as the matched ov_SC03_* TUs) ---- */
#define gte_ldv0(r0) __asm__ volatile (          \
    "lwc2 $0, 0( %0 );"                          \
    "lwc2 $1, 4( %0 )"                           \
    :                                            \
    : "r"( r0 ) )

#define gte_ldv3(r0, r1, r2) __asm__ volatile (  \
    "lwc2 $0, 0( %0 );"                          \
    "lwc2 $1, 4( %0 );"                          \
    "lwc2 $2, 0( %1 );"                          \
    "lwc2 $3, 4( %1 );"                          \
    "lwc2 $4, 0( %2 );"                          \
    "lwc2 $5, 4( %2 )"                           \
    :                                            \
    : "r"( r0 ), "r"( r1 ), "r"( r2 ) )

#define gte_rtps() __asm__ volatile ("nop;nop;rtps")
#define gte_rtpt() __asm__ volatile ("nop;nop;rtpt")
#define gte_avsz4() __asm__ volatile ("nop;nop;avsz4")

#define gte_stsxy(r0) __asm__ volatile (         \
    "swc2 $14, 0( %0 )"                          \
    :                                            \
    : "r"( r0 )                                  \
    : "memory" )

#define gte_stsxy3(r0, r1, r2) __asm__ volatile ( \
    "swc2 $12, 0( %0 );"                         \
    "swc2 $13, 0( %1 );"                         \
    "swc2 $14, 0( %2 )"                          \
    :                                            \
    : "r"( r0 ), "r"( r1 ), "r"( r2 )            \
    : "memory" )

#define gte_stflg(r0) __asm__ volatile (         \
    "cfc2 $12, $31;"                             \
    "nop;"                                       \
    "sw $12, 0( %0 )"                            \
    :                                            \
    : "r"( r0 )                                  \
    : "$12", "memory" )

#define gte_stotz(r0) __asm__ volatile (         \
    "swc2 $7, 0( %0 )"                           \
    :                                            \
    : "r"( r0 )                                  \
    : "memory" )

/* ---- types ---- */
typedef struct {
    /* 0x0 */ u32 xy;
    /* 0x4 */ s16 z;
    /* 0x6 */ s16 pad;
} V16F18;   /* 8 bytes */

typedef union {
    u32 w;
    u16 h[2];
} UV16F18;

typedef struct {
    /* 0x00 */ V16F18   v[4];
    /* 0x20 */ UV16F18  uv[4];
    /* 0x30 */ u32      rgbc;
    /* 0x34 */ u32      attr;
    /* 0x38 */ u8       clut;
} S16F18;

typedef struct {
    /* 0x00 */ u32 tag;
    /* 0x04 */ u32 rgbc;
    /* 0x08 */ u32 xy0;
    /* 0x0C */ u8  u0;
    /* 0x0D */ u8  v0;
    /* 0x0E */ u16 clut;
    /* 0x10 */ u32 xy1;
    /* 0x14 */ u8  u1;
    /* 0x15 */ u8  v1;
    /* 0x16 */ u16 tpage;
    /* 0x18 */ u32 xy2;
    /* 0x1C */ u8  u2;
    /* 0x1D */ u8  v2;
    /* 0x1E */ u16 pad0;
    /* 0x20 */ u32 xy3;
    /* 0x24 */ u8  u3;
    /* 0x25 */ u8  v3;
    /* 0x26 */ u16 pad1;
} FT4_16F18;

extern void *func_80010A08(s32);
extern void SetPolyFT4(FT4_16F18 *);
extern void func_80017E8C(s32);
extern s32 GetTPage(s32, s32, s32, s32);
extern s32 GetClut(s32, s32);
extern void func_80018194(void *, s32, u32);

void func_80016F18(S16F18 *arg0, s32 arg1, s32 arg2)
{
    s32 flag;
    s32 flag2;
    s32 otz;
    FT4_16F18 *p;
    u32 t;
    u32 c;

    p = (FT4_16F18 *)func_80010A08(0x28);
    p->rgbc = arg0->rgbc;
    SetPolyFT4(p);

    if (arg1 != 0) {
        func_80017E8C(arg1);
        gte_ldv3(&arg0->v[0], &arg0->v[1], &arg0->v[2]);
        gte_rtpt();
        gte_stflg(&flag);
        gte_stsxy3(&p->xy0, &p->xy1, &p->xy2);
        gte_ldv0(&arg0->v[3]);
        gte_rtps();
        gte_stflg(&flag2);
        flag |= flag2;
        gte_stsxy(&p->xy3);
        gte_avsz4();
        gte_stotz(&otz);
    } else {
        p->xy0 = arg0->v[0].xy;
        p->xy1 = arg0->v[1].xy;
        p->xy2 = arg0->v[2].xy;
        p->xy3 = arg0->v[3].xy;
        flag = 0;
        otz = arg0->v[0].z;
    }

    t = arg0->uv[0].w;
    p->u0 = t;
    p->v0 = t >> 16;
    t = arg0->uv[1].w;
    p->u1 = t;
    p->v1 = t >> 16;
    t = arg0->uv[2].w;
    p->u2 = t;
    p->v2 = t >> 16;
    t = arg0->uv[3].w;
    p->u3 = t;
    p->v3 = t >> 16;

    if (arg2 != 0) {
        p->tpage = GetTPage(2, (arg0->attr >> 28) & 3,
                            (arg0->uv[0].h[0] >> 2) & 0x3FC0, 0);
    } else {
        p->tpage = GetTPage(0, (arg0->attr >> 28) & 3,
                            (arg0->uv[0].h[0] >> 2) & 0x3FC0,
                            arg0->uv[0].h[1] & 0xFF00);
    }

    c = arg0->clut;
    p->clut = GetClut(c < 0xE0 ? 0x160 : 0x100, c | 0x100);

    if ((flag & ~0x1000) == 0) {
        func_80018194((void *)p, otz, (u32)arg0->attr);
    }
}

INCLUDE_ASM("asm/nonmatchings/800", func_80017168);

INCLUDE_ASM("asm/nonmatchings/800", func_80017254);

INCLUDE_ASM("asm/nonmatchings/800", func_80017274);

INCLUDE_ASM("asm/nonmatchings/800", func_80017294);

INCLUDE_ASM("asm/nonmatchings/800", func_8001739C);

INCLUDE_ASM("asm/nonmatchings/800", func_800173BC);

INCLUDE_ASM("asm/nonmatchings/800", func_800173DC);

INCLUDE_ASM("asm/nonmatchings/800", func_800174DC);

INCLUDE_ASM("asm/nonmatchings/800", func_800174FC);

INCLUDE_ASM("asm/nonmatchings/800", func_8001751C);

INCLUDE_ASM("asm/nonmatchings/800", func_800176F0);

INCLUDE_ASM("asm/nonmatchings/800", func_80017714);

INCLUDE_ASM("asm/nonmatchings/800", func_80017738);

INCLUDE_ASM("asm/nonmatchings/800", func_80017758);

INCLUDE_ASM("asm/nonmatchings/800", func_80017778);

INCLUDE_ASM("asm/nonmatchings/800", func_800178C8);

INCLUDE_ASM("asm/nonmatchings/800", func_800178EC);

INCLUDE_ASM("asm/nonmatchings/800", func_80017910);


/* func_80017930 — src/800.c (main, -O2).
 *
 * Builds one POLY_GT4 (0x34 bytes) from a 0x48-byte "sprite/quad descriptor":
 *   0x00..0x1F  four SVECTORs (v0..v3)
 *   0x20..0x2F  four packed u/v words (u in bits 0..15, v in bits 16..31)
 *   0x30..0x3F  four rgb+code words
 *   0x40        flag/tpage word (bits 24-25 = tp, bits 28-29 = abr)
 *   0x44        clut index byte
 * arg1 != 0 -> run the GTE (RTPT on v0..v2, RTPS on v3, AVSZ4 -> otz);
 * arg1 == 0 -> copy the xy pairs straight through and use v0.vz as otz.
 * Finally GetTPage/GetClut and hand the prim to func_8001820C (arg2 != 0) or func_80018194.
 */

extern void *func_80010A08(s32 size);
extern void SetPolyGT4(void *p);
extern void func_80017E8C(s32 arg0);
extern s32 GetTPage(s32 tp, s32 abr, s32 x, s32 y);
extern s32 GetClut(s32 x, s32 y);
extern void func_8001820C(void *p, s32 otz, u32 flags);
extern void func_80018194(void *p, s32 otz, u32 flags);

typedef struct {
    s16 vx, vy, vz, pad;
} SV_80017930;

typedef struct {
    SV_80017930 v[4]; /* 0x00 */
    u32 uv[4];        /* 0x20 */
    u32 rgb[4];       /* 0x30 */
    u32 flags;        /* 0x40 */
    u8 clut;          /* 0x44 */
} Src_80017930;

typedef struct {
    u32 tag;    /* 0x00 */
    u32 rgb0;   /* 0x04 */
    s16 x0, y0; /* 0x08 */
    u8 u0, v0;  /* 0x0C */
    u16 clut;   /* 0x0E */
    u32 rgb1;   /* 0x10 */
    s16 x1, y1; /* 0x14 */
    u8 u1, v1;  /* 0x18 */
    u16 tpage;  /* 0x1A */
    u32 rgb2;   /* 0x1C */
    s16 x2, y2; /* 0x20 */
    u8 u2, v2;  /* 0x24 */
    u16 pad2;   /* 0x26 */
    u32 rgb3;   /* 0x28 */
    s16 x3, y3; /* 0x2C */
    u8 u3, v3;  /* 0x30 */
    u16 pad3;   /* 0x32 */
} GT4_80017930; /* 0x34 */

#define gte_ldv0(r0) __asm__ volatile (          \
    "lwc2 $0, 0( %0 );"                          \
    "lwc2 $1, 4( %0 )"                           \
    :                                            \
    : "r"( r0 ) )

#define gte_ldv3(r0, r1, r2) __asm__ volatile (  \
    "lwc2 $0, 0( %0 );"                          \
    "lwc2 $1, 4( %0 );"                          \
    "lwc2 $2, 0( %1 );"                          \
    "lwc2 $3, 4( %1 );"                          \
    "lwc2 $4, 0( %2 );"                          \
    "lwc2 $5, 4( %2 )"                           \
    :                                            \
    : "r"( r0 ), "r"( r1 ), "r"( r2 ) )

#define gte_rtps() __asm__ volatile ("nop;nop;rtps")
#define gte_rtpt() __asm__ volatile ("nop;nop;rtpt")
#define gte_avsz4() __asm__ volatile ("nop;nop;avsz4")

#define gte_stsxy(r0) __asm__ volatile (         \
    "swc2 $14, 0( %0 )"                          \
    :                                            \
    : "r"( r0 )                                  \
    : "memory" )

#define gte_stsxy3(r0, r1, r2) __asm__ volatile ( \
    "swc2 $12, 0( %0 );"                         \
    "swc2 $13, 0( %1 );"                         \
    "swc2 $14, 0( %2 )"                          \
    :                                            \
    : "r"( r0 ), "r"( r1 ), "r"( r2 )            \
    : "memory" )

#define gte_stotz(r0) __asm__ volatile (         \
    "swc2 $7, 0( %0 )"                           \
    :                                            \
    : "r"( r0 )                                  \
    : "memory" )

#define gte_stflg(r0) __asm__ volatile (         \
    "cfc2 $12, $31;"                             \
    "nop;"                                       \
    "sw $12, 0( %0 )"                            \
    :                                            \
    : "r"( r0 )                                  \
    : "$12", "memory" )

void func_80017930(Src_80017930 *arg0, s32 arg1, s32 arg2)
{
    s32 flag1;
    s32 flag2;
    s32 otz;
    GT4_80017930 *p;
    u32 w;
    u32 f;
    u32 c;

    p = (GT4_80017930 *)func_80010A08(0x34);
    p->rgb0 = arg0->rgb[0];
    p->rgb1 = arg0->rgb[1];
    p->rgb2 = arg0->rgb[2];
    p->rgb3 = arg0->rgb[3];
    SetPolyGT4(p);

    if (arg1 != 0) {
        func_80017E8C(arg1);
        gte_ldv3(&arg0->v[0], &arg0->v[1], &arg0->v[2]);
        gte_rtpt();
        gte_stflg(&flag1);
        gte_stsxy3(&p->x0, &p->x1, &p->x2);
        gte_ldv0(&arg0->v[3]);
        gte_rtps();
        gte_stflg(&flag2);
        flag1 |= flag2;
        gte_stsxy(&p->x3);
        gte_avsz4();
        gte_stotz(&otz);
    } else {
        *(u32 *)&p->x0 = *(u32 *)&arg0->v[0];
        *(u32 *)&p->x1 = *(u32 *)&arg0->v[1];
        *(u32 *)&p->x2 = *(u32 *)&arg0->v[2];
        *(u32 *)&p->x3 = *(u32 *)&arg0->v[3];
        flag1 = 0;
        otz = arg0->v[0].vz;
    }

    w = arg0->uv[0];
    p->u0 = w;
    p->v0 = w >> 16;
    w = arg0->uv[1];
    p->u1 = w;
    p->v1 = w >> 16;
    w = arg0->uv[2];
    p->u2 = w;
    p->v2 = w >> 16;
    w = arg0->uv[3];
    p->u3 = w;
    p->v3 = w >> 16;

    f = arg0->flags;
    p->tpage = GetTPage((f >> 24) & 3, (f >> 28) & 3,
                        (*(u16 *)&arg0->uv[0] >> 2) & 0x3FC0,
                        *((u16 *)&arg0->uv[0] + 1) & 0xFF00);

    c = arg0->clut;
    p->clut = GetClut(c < 0xE0 ? 0x160 : 0x100, c | 0x100);

    if ((flag1 & ~0x1000) == 0) {
        if (arg2 != 0) {
            func_8001820C(p, otz, arg0->flags);
        } else {
            func_80018194(p, otz, arg0->flags);
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/800", func_80017B98);


void func_80017D98(void *a0)
{
    s16 val = 0x1000;
    s16 *p = (s16 *)a0;
    p[0] = val;
    p[1] = 0;
    p[2] = 0;
    p[3] = 0;
    p[4] = val;
    p[5] = 0;
    p[6] = 0;
    p[7] = 0;
    p[8] = val;
}

INCLUDE_ASM("asm/nonmatchings/800", func_80017DC4);


extern void func_8004978C(s16 *a0, void *a1);
extern void func_80048EAC(void *a0, void *a1);

void func_80017DF8(s16 *a0, void *a1) {
    s16 temp[16];
    func_8004978C(a0, temp);
    func_80048EAC(temp, a1);
}


extern void func_80049CAC(s32 a0, s32 a1);
extern void func_80048EAC(void *a0, void *a1);

void func_80017E30(s32 a0, s32 a1) {
    s32 local_buf[8]; /* 0x20 bytes at sp+0x10 */

    func_80049CAC(a0, (s32)local_buf);
    func_80048EAC(local_buf, (void *)a1);
}

INCLUDE_ASM("asm/nonmatchings/800", func_80017E68);

INCLUDE_ASM("asm/nonmatchings/800", func_80017E8C);

INCLUDE_ASM("asm/nonmatchings/800", func_80017F14);

INCLUDE_ASM("asm/nonmatchings/800", func_80018094);

INCLUDE_ASM("asm/nonmatchings/800", func_80018194);

INCLUDE_ASM("asm/nonmatchings/800", func_8001820C);

INCLUDE_ASM("asm/nonmatchings/800", func_80018384);

INCLUDE_ASM("asm/nonmatchings/800", func_800183E0);

INCLUDE_ASM("asm/nonmatchings/800", func_80018450);

INCLUDE_ASM("asm/nonmatchings/800", func_800184F0);

INCLUDE_ASM("asm/nonmatchings/800", func_80018714);

/* LZSS streaming sector decompressor (resumable coroutine state machine).
 * Decodes up to 0x800 input bytes per call out of an LZSS stream into a 0x400-byte
 * scratchpad ring (lzss_ringBuffer @ 0x1F800000) and to lzss_outPtr. lzss_state is the
 * resume point (0=idle/done, 1=fresh, 2=token loop, 3=have code low byte, 4=advance bit).
 * Returns 1 if the input sector was consumed mid-stream (resume next call), 0 at the
 * stream terminator (back-ref offset 0) or when idle. */
/* MATCHED — asm-differ score 0, full-binary SHA1 green (Phase 7, session F, 2026-06-15).
 * Five constructs below are LOAD-BEARING for the byte-for-byte match against gcc 2.7.2 -O2; a
 * future reader who "cleans them up" WILL break the match. Each is annotated inline and the
 * compiler-internal root cause is in docs/matching-cookbook.md §10 (+ §5a). All five were
 * ground-truthed against the pinned gcc-2.7.2 source (reorg.c, jump.c, local-alloc.c). */
extern u8 lzss_curMask;        /* 0x800747A0 */
extern u8 lzss_curToken;       /* 0x800747A4 */
extern u8 *lzss_outPtr;        /* 0x800747AC */
extern u32 lzss_ringIndex;     /* 0x800747B0 */
extern u16 lzss_partialCode;   /* 0x800747B4 */
extern u32 lzss_state;         /* 0x800C7D24 */

s32 LzssDecodeSector(u8 *src) {
    s32 count = 0x800;
    u32 ringIdx = lzss_ringIndex;
    u8 mask = lzss_curMask;
    u8 token = lzss_curToken;
    u8 *out = lzss_outPtr;
    u16 code = lzss_partialCode;
    u8 *ring = (u8 *)0x1F800000;   /* scratchpad ring; original uses the literal (lui 0x1f80), not the symbol */
    u32 readIdx;
    s32 len;
    u8 b;
    u8 nb;   /* low-byte (state-3) source byte */
    u8 cb;
    u8 nh;   /* LOAD-BEARING #1 (residual A): a SEPARATE high-byte source var, NOT a reuse of `nb`.
              * `nb` is shared between the low- and high-byte paths; reusing it couples their
              * register allocation, so any high-byte reshaping shoves `nb` out of $v1. A distinct
              * `nh` decouples them. Cookbook §10/A. */
    s32 newState;
    s32 result; /* return-1 value carried in $v0 from each save predecessor (state-3/state-4) */

    /* LOAD-BEARING #2 (residual B3): NO `default:` case and NO statement after the switch. The
     * switch's own range check (`sltiu $v0,state,5; beqz $v0,<epilogue>`) is the ONLY state>=5
     * guard; the `beqz` REUSES the sltiu result ($v0==0 when state>=5) as the return-0 value by
     * threading straight to `jr ra`. An explicit `if(state>=5)return 0;`, a `default:`, or a
     * trailing `return 0;` each makes gcc emit a separate `move $v0,$zero` (+1 insn / wrong branch
     * target). Falling off the end here is deliberate (and matches the original). Cookbook §10/B3. */
    switch (lzss_state) {
    case 0:
        goto term_ret;
    case 1:
        ringIdx = 1;
        mask = 1;
        token = *src++;
        count--;
    case 2:
        for (;;) {
            if (token & mask) {
                b = *src++;
                ring[ringIdx] = b;
                ringIdx = (ringIdx + 1) & 0x3FF;
                count--;
                *out++ = b;
            } else {
                nb = *src++;
                count--;
                code = (code & 0xFF00) | nb;
                if (count != 0) {
                    goto have_low;
                }
                /* LOAD-BEARING #3 (residual B): `result` is set in the state-3 PREDECESSOR (here,
                 * before `goto save`), not inside the shared `save:` tail. This makes gcc emit a
                 * distinct `li $v0,1` per return site instead of cross-jumping/sinking one copy into
                 * the tail's branch delay slot (reorg.c fill_simple_delay_slots). Cookbook §10/B. */
                result = 1;
                newState = 3;
                goto save;
    have_low:
    case 3:
                nh = *src++;
                count--;
                /* LOAD-BEARING #1 (residual A), cont.: operand order `(code & 0xFF) | (nh << 8)`,
                 * NOT `(nh<<8)|(code&0xFF)`. gcc local-alloc.c combine_regs ties a commutative OR's
                 * result to the FIRST RTL operand that dies; writing `code & 0xFF` first ties the
                 * result to $v0 (the target reg) → `or $v0,$v0,$v1`. Cookbook §10/A. */
                code = (code & 0xFF) | (nh << 8);
                readIdx = code & 0x3FF;
                if (readIdx == 0) {
                    lzss_state = 0;
                term_ret:
                    return 0;
                }
                len = (code >> 10) + 2;
                while (len != 0) {
                    cb = ring[readIdx];
                    readIdx = (readIdx + 1) & 0x3FF;
                    ring[ringIdx] = cb;
                    ringIdx = (ringIdx + 1) & 0x3FF;
                    *out++ = cb;
                    len--;
                }
            }
            if (count != 0) {
                goto next_bit;
            }
            result = 1;     /* state-4 save predecessor — see LOAD-BEARING #3 */
            newState = 4;
        save:
            lzss_state = newState;
            lzss_ringIndex = ringIdx;
            lzss_curMask = mask;
            lzss_curToken = token;
            lzss_outPtr = out;
            lzss_partialCode = code;
            return result;
    next_bit:
    case 4:
            if (mask == 0x80) {
                mask = 1;
                token = *src++;
                count--;
                if (count == 0) {
                    /* state-2 reload save. The original keeps this as a SEPARATE copy of the 6
                     * stores (not shared with `save:`). Two more load-bearing constructs: */
                    register s32 r __asm__("$2");
                    /* LOAD-BEARING #4 (residual B, state-2): an explicit $v0 local pinned early by a
                     * read-only input-asm. This forces `li $v0,1` to materialise BEFORE the stores
                     * (the target schedules the return value first; gcc otherwise, since `li $v0,1`'s
                     * only use is the shared epilogue, defers it to just before `jr ra`). Cookbook §10/B. */
                    r = 1;
                    __asm__ __volatile__("" : : "r"(r));
                    newState = 2;
                    lzss_state = newState;
                    lzss_ringIndex = ringIdx;
                    lzss_curMask = mask;
                    lzss_curToken = token;
                    lzss_outPtr = out;
                    lzss_partialCode = code;
                    /* LOAD-BEARING #5 (the cross-jump barrier): a zero-byte volatile asm. gcc 2.7.2
                     * -O2 jump.c find_cross_jump would otherwise MERGE this save with the identical
                     * `save:` tail (→111 insns); an ASM_INPUT node makes it bail (lose=1) so both
                     * survive (→122, the correct count). No -fno-crossjumping before gcc 3.3. Cookbook §5a. */
                    __asm__ __volatile__("" ::: "memory");
                    return r;
                }
            } else {
                mask <<= 1;
            }
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/800", func_80018918);

INCLUDE_ASM("asm/nonmatchings/800", func_800189A8);


extern u8 D_80078D98;
extern u32 D_800AE610;
extern s32 D_800A5E78;
extern u8 D_80062BAC;
extern u8 D_80062BB4;
extern u8 D_80062BBC;
extern u8 D_80062BBD;
extern u8 D_800747B8;
extern u8 D_800747B9;

extern s32 func_8005D184(s32);
extern s32 func_8005D244(s32, s32, s32);
extern void func_8005D4B8(s32, void*);
extern void func_8005D538(s32, void*, s32);
extern s32 func_80028D58(void);
extern void func_80018F88(void*);
extern void func_80018FC8(void);

s32 func_80018A20(s32 arg0) {
    u8* p;
    s32 chan;

    p = (u8*)((u32)&D_80078D98 + arg0 * 76);

    switch (arg0) {
    case 0:
        chan = 0;
        break;
    case 1:
        chan = 16;
        break;
    }

    switch (func_8005D184(chan)) {
    case 0:
        if (arg0 == 0) {
            if (D_800AE610++ >= 10) {
                D_800AE610 = 0;
                D_800A5E78 = 0;
            }
        }
        /* fallthrough */
    case 1:
        func_80018F88(p);
        return 0;

    case 2:
        if (arg0 != 0) {
            return 1;
        }
        D_800AE610 = 0;
        if (func_8005D244(chan, 2, 0) != 0) {
            return 1;
        }
        if (func_80028D58() == 0) {
            if (p[0x4A] | p[0x4B]) {
                D_80062BBD = 1;
            } else {
                D_80062BBD = 0;
            }
            p[0x4B] = 0;
            p[0x4A] = 0;
        } else {
            func_80018FC8();
        }
        func_8005D538(chan, &D_80062BBC, 2);
        func_8005D4B8(chan, &D_80062BAC);
        return 1;

    case 6:
        if (arg0 != 0) {
            return 1;
        }
        D_800AE610 = 0;
        if (func_8005D244(chan, 2, 0) == 0) {
            return 1;
        }
        if (func_80028D58() == 0) {
            D_800747B8 = p[0x4A];
            D_800747B9 = p[0x4B];
            p[0x4B] = 0;
            p[0x4A] = 0;
        } else {
            func_80018FC8();
        }
        func_8005D538(chan, &D_800747B8, 2);
        func_8005D4B8(chan, &D_80062BB4);
        return 1;
    }
}

INCLUDE_ASM("asm/nonmatchings/800", func_80018C64);


extern void func_80016714(void *a0, s32 a1);
extern void func_80018F20(s32 param_1);
extern u8 D_80078DE4;

void func_80018CE8(u8 *p) {
    s32 i;

    if (p == &D_80078DE4) {
        func_80016714(p, 0x4C);
        return;
    }
    switch (*p) {
    case 'A':
        for (i = 0; i < 2; i++) {
            (p + i)[0x42] = (p + i)[0x32];
            (p + i)[0x3A] = (p + i)[0x2A] & ((p + i)[0x2A] ^ (p + i)[0x32]);
            (p + i)[0x32] = (p + i)[0x2A];
        }
        return;
    case 'S':
        for (i = 0; i < 2; i++) {
            (p + i)[0x42] = (p + i)[0x32];
            (p + i)[0x3A] = (p + i)[0x2A] & ((p + i)[0x2A] ^ (p + i)[0x32]);
            (p + i)[0x32] = (p + i)[0x2A];
        }
        for (; i < 8; i++) {
            (p + i)[0x42] = (p + i)[0x32];
            (p + i)[0x32] = (p + i)[0x2A];
        }
        func_80018F20((s32) p);
        return;
    case 's':
        for (i = 0; i < 2; i++) {
            (p + i)[0x42] = (p + i)[0x32];
            (p + i)[0x3A] = (p + i)[0x2A] & ((p + i)[0x2A] ^ (p + i)[0x32]);
            (p + i)[0x32] = (p + i)[0x2A];
        }
        for (; i < 8; i++) {
            (p + i)[0x42] = (p + i)[0x32];
            (p + i)[0x32] = (p + i)[0x2A];
        }
        func_80018F20((s32) p);
        return;
    }
    func_80016714(p, 0x4C);
}

INCLUDE_ASM("asm/nonmatchings/800", func_80018E78);

INCLUDE_ASM("asm/nonmatchings/800", func_80018E9C);

void func_80018F20(s32 param_1) {
    u32 uVar3;
    s32 iVar2;
    u32 uVar1;

    uVar3 = 2;
    do {
        iVar2 = param_1 + uVar3;
        uVar1 = *(u8 *)(iVar2 + 0x32);
        if (uVar1 - 0x51 < 0x5f) {
            *(u8 *)(iVar2 + 0x32) = 0x80;
        } else if ((uVar1 & 0xff) < 8) {
            *(u8 *)(iVar2 + 0x32) = 0;
        } else if ((uVar1 & 0xff) >= 0xf8) {
            *(u8 *)(iVar2 + 0x32) = 0xff;
        }
        uVar3 = uVar3 + 1;
    } while (uVar3 < 8);
}

INCLUDE_ASM("asm/nonmatchings/800", func_80018F88);

INCLUDE_ASM("asm/nonmatchings/800", func_80018FC8);

extern s32 D_800747C8;
void func_80019018(void) {
    D_800747C8 = 0;
}

INCLUDE_ASM("asm/nonmatchings/800", func_80019028);


extern void func_80016714(void *a0, s32 a1);
extern s32 D_800747C0;

void func_8001903C(void) {
    func_80016714(&D_800747C0, 8);
}

INCLUDE_ASM("asm/nonmatchings/800", func_80019064);

INCLUDE_ASM("asm/nonmatchings/800", func_800190AC);

extern s32 D_800747C0;
s32 func_80019198(void) {
    return D_800747C0;
}

INCLUDE_ASM("asm/nonmatchings/800", func_800191A8);

INCLUDE_ASM("asm/nonmatchings/800", func_800191BC);

INCLUDE_ASM("asm/nonmatchings/800", func_800191D4);

INCLUDE_ASM("asm/nonmatchings/800", func_8001923C);

INCLUDE_ASM("asm/nonmatchings/800", func_8001931C);

extern s32 debugBinPresent;
s32 func_80019378(void) {
    return debugBinPresent;
}

extern s32 debugBinPresent;
void func_80019388(s32 arg0) {
    debugBinPresent = arg0;
}

extern s32 D_800747D4;
s32 func_80019398(void) {
    return D_800747D4;
}

extern s32 D_800747D4;
void func_800193A8(s32 arg0) {
    D_800747D4 = arg0;
}

INCLUDE_ASM("asm/nonmatchings/800", func_800193B8);

#ifdef NON_MATCHING
extern void LoaderResetReadState(void);
extern int VSync(int mode);
extern CdlFILE D_80063058;
extern char cdpath_DEBUG_BIN[];
extern u8 D_80062C38;     /* path table entry[0].file (CdlFILE), entries stride 0x30; names at -0x14 */
extern u8 D_80062C68;     /* path entry[1].file.pos (CdlLOC), the 8 .CD files, stride 0x30 */
extern s32 debugBinPresent;
extern s32 D_800747D4;
extern s32 D_80063074;
extern s32 D_800747D8;
extern u8 cdFileLocTable[]; /* out: {CdlLOC pos; u32 size} per sub-file, 8B stride */
extern u8 D_800AE834;       /* cdFileLocTable + 4 (the size field) */
extern s32 listCdBuffer;    /* LIST.CD content: 8B records {value; size} */
extern u8 D_80180004;       /* listCdBuffer + 4 (the size field) */
/* file-loader directory resolver (boot @0x800101fc): probe \DEBUG.BIN;1, resolve the 21
 * CdPathTable entries via CdSearchFile, read LIST.CD (0xE40 B) into listCdBuffer, then build
 * cdFileLocTable (CdlLOC+size per sub-file) over the 8 .CD files. Phase 3 T2.
 * NON_MATCHING: logically faithful, structurally close (138 vs 133 ins) but not byte-exact.
 * Residual is register allocation / loop-invariant hoisting — the target keeps &D_80063058,
 * &D_80062C38, &D_80062C68 in callee-saved regs and derives the name arg as (base - 0x14)
 * rather than a separate symbol; a multi-iteration / decomp-permuter target for a later pass. */
void LoaderInitFileTable(void) {
    CdlFILE *res;
    int tries;
    int pathOff;
    int pathN;
    int base;
    int n;
    int fileIdx;
    int bufIdx;
    int j;
    int outer;
    int locOff;
    int dstOff;
    int srcOff;
    int *pCount;
    int *pOff;
    CdlLOC *p;

    LoaderResetReadState();
    tries = 0;
    do {
        res = CdSearchFile(&D_80063058, cdpath_DEBUG_BIN);
        tries++;
        if (res != (CdlFILE *)-1) {
            break;
        }
    } while (tries < 0x10);
    pathN = 0;
    pathOff = 0;
    debugBinPresent = (res != (CdlFILE *)0);
    D_800747D4 = 1;
    D_80063074 = 0;
    D_800747D8 = 0;
    do {
        do {
            res = CdSearchFile((CdlFILE *)(&D_80062C38 + pathOff), (char *)(&D_80062C38 - 0x14 + pathOff));
        } while ((u32)((int)res + 1) < 2);
        pathN++;
        pathOff += 0x30;
    } while (pathN < 0x15);
    do {
        fileIdx = 0;
        n = CdReadRequest(&D_80062C38, &listCdBuffer, 0xE40, 0);
        if (n != 0) {
            break;
        }
        VSync(0);
    } while (1);
    bufIdx = 0;
    outer = 0;
    locOff = 0;
    pCount = &listCdBuffer;
    do {
        base = CdPosToInt((CdlLOC *)(&D_80062C68 + locOff));
        n = *pCount;
        pCount += 2;
        bufIdx++;
        j = 0;
        if (n > 0) {
            dstOff = fileIdx * 8;
            p = (CdlLOC *)(cdFileLocTable + dstOff);
            srcOff = bufIdx * 8;
            pOff = &listCdBuffer + bufIdx * 2;
            do {
                if (*pOff != 0) {
                    CdIntToPos(*pOff + base, p);
                    *(s32 *)(&D_800AE834 + dstOff) = *(s32 *)(&D_80180004 + srcOff);
                }
                pOff += 2;
                srcOff += 8;
                pCount += 2;
                bufIdx++;
                p += 2;
                dstOff += 8;
                j++;
                fileIdx++;
            } while (j < n);
        }
        outer++;
        locOff += 0x30;
    } while (outer < 8);
}
#else
INCLUDE_ASM("asm/nonmatchings/800", LoaderInitFileTable);
#endif

INCLUDE_ASM("asm/nonmatchings/800", func_80019930);

extern s32 cdReq_sink;
extern s32 cdReq_curSector;
extern s32 D_800BA1B4;
extern s32 D_800747F0;
extern s32 D_800747F4;
extern s32 cdReq_state;
extern s32 D_800AE6F8;
extern s32 D_800AE6FC;
extern s32 D_800AE700;
extern s32 cdReq_wordsRemaining;
extern s32 cdReq_drainPhase;
extern u8 D_800AE798;
extern u8 D_800AE799;
extern s32 D_800AE70C;
void LoaderResetReadState(void) {
    cdReq_sink = 0x80010000;
    cdReq_curSector = 0;
    D_800BA1B4 = 0;
    D_800747F0 = 0;
    D_800747F4 = 0;
    cdReq_state = 0;
    D_800AE6F8 = 0;
    D_800AE6FC = 0;
    D_800AE700 = 0;
    cdReq_wordsRemaining = 1;
    cdReq_drainPhase = 0;
    D_800AE798 = 0;
    D_800AE799 = 0;
    D_800AE70C = 0;
}

INCLUDE_ASM("asm/nonmatchings/800", func_80019A10);

extern s32 CdQueueBusy(void);
extern void CdReadStateMachine(int);
extern s32 cdReq_curSector;
extern void *cdReq_dest;
extern s32 cdReq_size;
extern void *cdReq_cdlFile;
extern s32 cdReq_result;
extern s32 D_800AE720;
extern s32 D_800AE724;
/* Read-request dispatcher (Phase 3 T2). Refuse while CdQueueBusy(); dedup on the request's
 * start sector (*cdlFile) vs the in-flight cdReq_curSector; stash dest/size/cdlFile/mode into
 * the control block, set the "first read" flag D_800AE720 = (mode == 0), drive the state
 * machine, return cdReq_result. */
s32 CdReadRequest(int *cdlFile, void *dest, s32 size, s32 mode) {
    s32 sector;
    if (CdQueueBusy() != 0) {
        return 0;
    }
    if (cdReq_curSector == 0) {
        sector = *cdlFile;
    } else {
        sector = *cdlFile;
        if (sector != cdReq_curSector) {
            return 0;
        }
    }
    cdReq_dest = dest;
    cdReq_size = size;
    cdReq_cdlFile = cdlFile;
    D_800AE724 = mode;
    D_800AE720 = 0;
    cdReq_curSector = sector;
    if (mode == 0) {
        D_800AE720 = 1;
    }
    CdReadStateMachine(0);
    return cdReq_result;
}

#ifdef NON_MATCHING
/* libcd low-level command API (the loader uses raw CdControl, NOT the PsyQ CdRead() wrapper;
 * not in psyq/libcd.h yet). */
extern int   CdControl(u8 com, u8 *param, u8 *result);
extern int   CdSync(int mode, u8 *result);
extern void  CdFlush(void);
extern void *CdReadyCallback(void *func);
extern void  CdReadSectorReadyCB(char);        /* the CdlReadN data-ready callback @0x8001A338 */
extern void  start(void);                       /* EXE entry — used as the idle "sink" sentinel */
extern int   func_8002FD14(int buf, int len);   /* per-sector consumer (drains the queued list) */
extern void  func_8001A0FC(void);
extern int   func_8001A114(void);

/* cdReq_* async-read control block (Phase 3 T2); the D_800AE* are its unnamed members. */
extern int     cdReq_state;
extern int     cdReq_retry;
extern int     cdReq_result;        /* return-by-global: 0 = still busy, 1 = done */
extern u8      cdReq_cdResult;      /* CdControl status byte (bit 0x10 = error) */
extern void   *cdReq_cdlFile;       /* seek target (a CdlLOC*) */
extern int     cdReq_posInt;
extern int     cdReq_timeout;
extern int     cdReq_size;          /* bytes to read */
extern void   *cdReq_dest;          /* read destination */
extern s32     cdReq_sink;          /* sector sink address (dest while reading, &start idle) */
extern int     cdReq_wordsRemaining;
extern int     cdReq_drainPhase;    /* 0 = reading, 1 = drained, 2 = finished */
extern void   *cdReq_savedReadyCB;  /* prior CdReadyCallback, restored on stop */
extern int     cdReq_curSector;
extern u8      D_800AE740;          /* CdlSetmode mode-byte buffer (0xA0) */
extern int     D_800AE6E8;          /* CdSync result scratch */
extern int     D_800AE6F8;
extern s32     D_800AE70C;          /* last/idle CdlLOC (held as a word) */
extern int     D_800AE71C;          /* count of queued sectors to drain (state 7) */
extern int     D_800AE724;          /* base of the queued {ptr,len} sector list */
extern int     D_800AE6FC;
extern int     D_800AE700;
extern u8      D_800AE798;
extern u8      D_800AE799;

/* Hand-rolled polled async CD reader: one state step per call, switch(cdReq_state). Sequence
 *   SetMode(0xA0) -> SeekL(+CdPosToInt) -> ReadN(+CdReadSectorReadyCB sector drain) -> Pause/Flush.
 * Progress is returned via cdReq_result (0 busy / 1 done). The game does NOT use PsyQ CdRead()/
 * CdReadSync(). pauseAfterSeek != 0 stops after the seek (state 8) instead of reading.
 * Provenance: static trace, Phase 3 T2 (verified).
 * NON_MATCHING: logically faithful to the Ghidra decompile; not byte-exact — a large switch state
 * machine whose register allocation + jump-table placement are a later byte-match pass. */
void CdReadStateMachine(int pauseAfterSeek) {
    int n;
    int i;
    int off;

    switch (cdReq_state) {
    case 0:
        cdReq_retry = 0;
        D_800AE71C = 0;
        D_800AE70C = 0;
        D_800AE740 = 0xA0;
        CdControl(0x0E, &D_800AE740, &cdReq_cdResult);             /* CdlSetmode */
        if ((cdReq_cdResult & 0x10) == 0) {
            cdReq_state++;
            goto state1;
        }
        break;
    case 1:
    state1:
        D_800AE6E8 = CdSync(1, &cdReq_cdResult);
        if (D_800AE6E8 == 0) { cdReq_result = 0; return; }
        if (D_800AE6E8 == 5) { cdReq_state = 0; cdReq_result = 0; return; }
        if (D_800AE6E8 != 2) { cdReq_result = 0; return; }
        cdReq_retry = 0;
        cdReq_state++;
        D_800AE6E8 = 2;
    state2:
        if (cdReq_retry + 1 < 3) {
            cdReq_retry++;
            cdReq_result = 0;
            return;
        }
        cdReq_state++;
        cdReq_retry = 0;
        cdReq_result = 0;
        return;
    case 2:
        goto state2;
    case 3:
        CdControl(0x15, (u8 *)cdReq_cdlFile, &cdReq_cdResult);    /* CdlSeekL */
        if ((cdReq_cdResult & 0x10) == 0) {
            cdReq_timeout = 0;
            cdReq_posInt = CdPosToInt((CdlLOC *)cdReq_cdlFile);
            cdReq_state++;
            goto state4;
        }
        break;
    case 4:
    state4:
        D_800AE6E8 = CdSync(1, &cdReq_cdResult);
        if (D_800AE6E8 == 5) {
            cdReq_retry++;
        flushRetry:
            CdFlush();
            cdReq_state = 3;
            cdReq_result = 0;
            return;
        }
        if (D_800AE6E8 == 0) { cdReq_result = 0; return; }
        if (D_800AE6E8 != 2) {
            cdReq_result = 0;
            cdReq_timeout++;
            if (cdReq_timeout < 0xB5) { cdReq_result = 0; return; }
            goto flushRetry;
        }
        if (pauseAfterSeek == 0) {
            cdReq_state++;
            goto state5;
        }
        CdControl(0x09, (u8 *)0, &cdReq_cdResult);                /* CdlPause */
        if ((cdReq_cdResult & 0x10) == 0) {
            cdReq_state = 8;
            D_800AE70C = *(s32 *)cdReq_cdlFile;
            cdReq_result = 0;
            return;
        }
        break;
    case 5:
    state5:
        cdReq_drainPhase = 0;
        if (cdReq_size < 1) {
            D_800AE6F8 = 0;
        } else {
            int bytes = cdReq_size + 3;
            D_800AE6F8 = 3;
            if (bytes < 0) bytes = cdReq_size + 6;                /* round-up word count, neg-safe */
            cdReq_wordsRemaining = bytes >> 2;
            D_800AE798 = 1;
            cdReq_sink = (s32)cdReq_dest;
        }
        cdReq_savedReadyCB = CdReadyCallback(CdReadSectorReadyCB);
        CdControl(0x06, (u8 *)0, &cdReq_cdResult);                /* CdlReadN */
        if ((cdReq_cdResult & 0x10) == 0) {
            cdReq_retry = 0;
            cdReq_state++;
            goto state6;
        }
        break;
    case 6:
    state6:
        if (cdReq_drainPhase != 1) {
            if (cdReq_drainPhase == 2) {
                CdReadyCallback(cdReq_savedReadyCB);
                cdReq_state = 0;
                cdReq_result = 0;
                return;
            }
            cdReq_retry++;
            if (cdReq_retry > 299) {
                CdReadyCallback(cdReq_savedReadyCB);
                cdReq_state = 0;
                CdFlush();
                cdReq_result = 0;
                return;
            }
            cdReq_result = 0;
            return;
        }
        CdReadyCallback(cdReq_savedReadyCB);
        CdControl(0x09, (u8 *)0, &cdReq_cdResult);                /* CdlPause */
        if ((cdReq_cdResult & 0x10) == 0) {
            cdReq_state += (D_800AE71C == 0) ? 2 : 1;             /* -> 8 (no drain) or 7 (drain) */
            cdReq_result = 0;
            return;
        }
        break;
    case 7:
        n = 0;
        if (D_800AE71C > 0) {
            off = 0;
            do {
                do {
                    i = func_8002FD14(*(int *)(D_800AE724 + off),
                                      *(int *)(D_800AE724 + off + 4));
                } while (i == 0);
                n++;
                off = n * 8;
            } while (n < D_800AE71C);
        }
        cdReq_state++;
        cdReq_result = 0;
        return;
    case 8:
        D_800AE6E8 = CdSync(1, &cdReq_cdResult);
        if (D_800AE6E8 == 2) {
            cdReq_sink = (s32)start;
            cdReq_state = 0;
            D_800AE6F8 = 0;
            D_800AE6FC = 0;
            D_800AE700 = 0;
            cdReq_curSector = 0;
            D_800AE70C = 0;
            cdReq_wordsRemaining = 1;
            cdReq_drainPhase = 0;
            D_800AE798 = 0;
            D_800AE799 = 0;
            cdReq_result = 1;
            return;
        }
        if (D_800AE6E8 != 5) { cdReq_result = 0; return; }
        CdFlush();
        CdControl(0x09, (u8 *)0, &cdReq_cdResult);                /* CdlPause */
        if ((cdReq_cdResult & 0x10) == 0) { cdReq_result = 0; return; }
        break;
    case 9:
        func_8001A0FC();
        cdReq_state++;
        /* fall through to state 10 */
    case 10:
        D_800AE6E8 = func_8001A114();
        if (D_800AE6E8 != 0) {
            cdReq_state = 0;
            cdReq_result = 0;
            return;
        }
        cdReq_result = 0;
        return;
    default:
        goto setDefault;
    }
    cdReq_state = 9;
setDefault:
    cdReq_result = 0;
    return;
}
#else
INCLUDE_ASM("asm/nonmatchings/800", CdReadStateMachine);
#endif

INCLUDE_ASM("asm/nonmatchings/800", func_8001A0FC);

INCLUDE_ASM("asm/nonmatchings/800", func_8001A114);

#ifdef NON_MATCHING
typedef struct { short x, y, w, h; } RECT;          /* libgpu RECT (VRAM rectangle) */
extern int   CdGetSector(void *madr, int nsector);
extern void  LoadImage(RECT *rect, u32 *data);      /* libgpu VRAM upload */
extern int   func_8002FC64(int nbytes, u32 *src);   /* stage/copy a payload run */
extern int   func_8002FB08(int entry);              /* kick off a queued list entry */
extern void  func_8002FDC8(void);                   /* finalize the queued transfer */
extern void  func_80018714(void);                   /* reset LZSS sector state */

/* shared cdReq_ control block (see CdReadStateMachine) + this callback's members */
extern int   cdReq_posInt;
extern int   cdReq_size;
extern int   cdReq_wordsRemaining;
extern int   cdReq_drainPhase;
extern void *cdReq_dest;
extern s32   cdReq_sink;
extern u32   lzss_sectorStagingBuf[];  /* 0x80079A70 — PAC header lands here ([0] = 'PAC' magic) */
extern u8    cdReq_sectorHdrBuf[];     /* sub-header scratch (3 words -> CdPosToInt) */
extern u8    D_80079A74;               /* PAC type */
extern u8    D_80079A75;               /* PAC flags -> D_800AE798 */
extern int   D_80079A78;               /* PAC sub-count (textures) */
extern int   D_80079A7C;               /* PAC payload size (bytes) */
extern int   D_800AE6F8;               /* load phase (PAC-type dispatcher state) */
extern u8    D_800AE798;               /* saved PAC flags (nonzero = more sectors follow) */
extern int   D_800AE704;               /* texture sector index (0..3, round-robin) */
extern short D_800AE710, D_800AE712;   /* VRAM dst x,y of the current tile (a RECT @0xAE710) */
extern short D_800AE714, D_800AE716;   /* tile w,h (0x20 x 0x20) */
extern u8    D_800AE758[];             /* 64-byte present bitmask (which tiles are sent) */
extern u8    D_800AE79A, D_800AE79B;   /* bit / byte cursor into the bitmask */
extern RECT *D_800AE718;               /* current texture-rect pointer (PAC type 6) */
extern int   D_800AE71C;               /* queued-entry count */
extern int   D_800AE720;               /* "transfer already in progress" guard */
extern int   D_800AE724;               /* base of the queued {ptr,len} list */
extern void *D_80072C80;               /* a fixed destination pointer (PAC type 7) */
extern u32   D_8007A280[];             /* texture RECT array (read from CD) */
extern u32   D_8007A310[];             /* texture pixel data (read from CD) */

/* CdReadyCallback for CdReadStateMachine (registered in its state 5). Per CD data-ready interrupt,
 * drain one sector and dispatch on the load phase D_800AE6F8: parse the PAC header, then per PAC
 * type either upload tiles to VRAM (LoadImage), copy raw sectors to cdReq_sink, or decompress via
 * LzssDecodeSector (this is its ONLY caller). reason: 1 = data-ready, 5 = end/error.
 * Provenance: static trace, Phase 3 T2/T4 (verified).
 * NON_MATCHING: faithful translation of the Ghidra decompile — logically faithful, not byte-verified
 * (large interrupt callback; register allocation + jump-table placement are a later byte-match pass). */
void CdReadSectorReadyCB(char reason) {
    void *dst;
    int pos;
    int i, n;

    if (reason != 1) goto endReason;
    CdGetSector(cdReq_sectorHdrBuf, 3);
    pos = CdPosToInt((CdlLOC *)cdReq_sectorHdrBuf);
    if (pos != cdReq_posInt) {                  /* sector out of order -> abort the drain */
        if (D_800AE6F8 == 4) func_8002FDC8();
        cdReq_drainPhase = 2;
        return;
    }
    cdReq_posInt = pos + 1;
    switch (D_800AE6F8) {
    case 0:                                      /* expect a PAC header */
        CdGetSector(lzss_sectorStagingBuf, 4);
        if (lzss_sectorStagingBuf[0] != 0x434150) goto abortDrain;   /* "PAC" magic? */
        D_800AE798 = D_80079A75;
        switch (D_80079A74) {                    /* PAC type */
        case 0:
        case 5:                                  /* tiled texture: scan the present-bitmask */
            D_800AE704 = 0;
            CdGetSector(D_800AE758, 0x10);
            D_800AE716 = 0x20; D_800AE714 = 0x20;
            D_800AE712 = 0; D_800AE710 = 0;
            D_800AE79A = 1; D_800AE79B = 0;
            while (D_800AE79B < 0x40) {
                if ((D_800AE79A & D_800AE758[D_800AE79B]) != 0) goto tilePhase;
                if (D_800AE79A == 0x80) { D_800AE79A = 1; D_800AE79B++; }
                else                     D_800AE79A <<= 1;
                D_800AE710 += 0x20;
                if (D_800AE710 > 0x3FF) { D_800AE710 = 0; D_800AE712 += 0x20; }
            }
            D_800AE6F8 = (D_800AE798 == 0) ? 0 : 2;
        tilePhase:
            D_800AE6F8++;
            break;
        case 1:
            dst = cdReq_dest;
            goto setSink;
        case 2:
            if (D_800AE720 != 0) goto phaseDone;
            dst = *(void **)(D_800AE71C * 8 + D_800AE724 + 4);
            goto setSink;
        case 3:
            if (D_800AE720 != 0) goto phaseDone;
            do { i = func_8002FB08(*(int *)(D_800AE71C * 8 + D_800AE724)); } while (i == 0);
            D_800AE6F8 = 4;
            cdReq_wordsRemaining = D_80079A7C - 0x800;
            break;
        case 4:
            D_800AE6F8 = 5;
            cdReq_wordsRemaining = (D_80079A7C - 0x7FD) >> 2;
            cdReq_sink = (s32)cdReq_dest;
            func_80018714();
            break;
        case 6:                                  /* multiple TIMs: LoadImage each */
            CdGetSector(D_8007A280, 0x1FC);
            n = D_80079A78;
            {
                u32 *p = D_8007A310;
                i = 0;
                D_800AE718 = (RECT *)D_8007A280;
                if (n > 0) {
                    do {
                        LoadImage(D_800AE718, p);
                        i++;
                        p += D_800AE718->w / 2;
                        D_800AE718++;
                    } while (i < n);
                }
            }
            goto sectorDone;
        case 7:
            dst = D_80072C80;
            if (cdReq_size < 0) goto phaseDone;
        setSink:
            D_800AE6F8 = 3;
            cdReq_wordsRemaining = (D_80079A7C - 0x7FD) >> 2;
            cdReq_sink = dst;
            break;
        case 8:
            D_800AE6F8 = 6;
            cdReq_wordsRemaining = (D_80079A7C - 0x7FD) >> 2;
            break;
        }
        break;
    case 1:                                      /* stream tile pixels to VRAM */
        i = D_800AE704 * 0x200;
        CdGetSector(&lzss_sectorStagingBuf[i], 0x200);
        LoadImage((RECT *)&D_800AE710, &lzss_sectorStagingBuf[i]);
        D_800AE704 = (D_800AE704 + 1) & 3;
        do {
            if (D_800AE79A == 0x80) { D_800AE79A = 1; D_800AE79B++; }
            else                     D_800AE79A <<= 1;
            if (D_800AE79B > 0x3F) goto sectorDone;
            D_800AE710 += 0x20;
            if (D_800AE710 > 0x3FF) { D_800AE710 = 0; D_800AE712 += 0x20; }
        } while ((D_800AE79A & D_800AE758[D_800AE79B]) == 0);
        break;
    case 3:                                      /* raw copy to cdReq_sink */
        if (cdReq_wordsRemaining < 0x201) {
            CdGetSector((void *)cdReq_sink, cdReq_wordsRemaining);
        sectorDone:
            D_800AE6F8 = (D_800AE798 == 0) ? 0 : 2;
        } else {
            CdGetSector((void *)cdReq_sink, 0x200);
            cdReq_wordsRemaining -= 0x200;
            cdReq_sink += 0x800;
        }
        break;
    case 4:                                      /* staged copy via func_8002FC64 */
        if (cdReq_wordsRemaining < 0x801) {
            n = cdReq_wordsRemaining + 3;
            if (n < 0) n = cdReq_wordsRemaining + 6;
            CdGetSector(lzss_sectorStagingBuf, n >> 2);
            if (func_8002FC64(cdReq_wordsRemaining, lzss_sectorStagingBuf) == 0) {
            stageFail:
                func_8002FDC8();
                D_800AE6F8 = 7;
            } else {
                D_800AE71C++;
                if (D_800AE798 != 0) goto phaseDone;
                D_800AE6F8 = 0;
            }
        } else {
            CdGetSector(lzss_sectorStagingBuf, 0x200);
            i = func_8002FC64(0x800, lzss_sectorStagingBuf);
            cdReq_sink += 0x800;
            cdReq_wordsRemaining -= 0x800;
            if (i == 0) goto stageFail;
        }
        break;
    case 5:                                      /* LZSS decompress one sector */
        CdGetSector(lzss_sectorStagingBuf, 0x200);
        if (LzssDecodeSector(lzss_sectorStagingBuf) == 0) goto sectorDone;
        break;
    case 6:                                      /* countdown the remaining words */
        cdReq_wordsRemaining -= 0x200;
        if (cdReq_wordsRemaining < 1) {
            if (D_800AE798 != 0) goto phaseDone;
            D_800AE6F8 = 0;
        }
        break;
    }
    if (D_800AE6F8 == 2) {
    phaseDone:                                   /* (reached by the switch above or by goto) */
        D_800AE6F8 = 2;
        cdReq_drainPhase = 1;
    } else if (D_800AE6F8 == 7) {
        cdReq_drainPhase = 2;
    }
endReason:
    if (reason == 5) {
        if (D_800AE6F8 == 4) func_8002FDC8();
    abortDrain:
        cdReq_drainPhase = 2;
    }
    return;
}
#else
INCLUDE_ASM("asm/nonmatchings/800", CdReadSectorReadyCB);
#endif

INCLUDE_ASM("asm/nonmatchings/800", func_8001A9D8);

INCLUDE_ASM("asm/nonmatchings/800", func_8001A9F8);

extern s32 cdReq_curSector;
s32 func_8001AA78(void) {
    return cdReq_curSector;
}

extern s32 cdReq_curSector;
void func_8001AA88(s32 arg0) {
    cdReq_curSector = arg0;
}

void func_8001AA98(void) {
}


extern void func_8001ABBC(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);

void func_8001AAA0(s32 arg0) {
    func_8001ABBC(1, arg0, 0, 0, 0);
}

INCLUDE_ASM("asm/nonmatchings/800", func_8001AAD0);

void func_8001ABB4(void) {
}

INCLUDE_ASM("asm/nonmatchings/800", func_8001ABBC);


extern s32 D_800747F0;
extern s32 D_800747F4;
extern s32 D_800747E4;
extern s32 D_800747E8;
extern s32 D_800C6D2C;
extern s32 D_800AE6E4;
extern s32 D_800BA318;
extern s32 D_800A6550;
extern s32 D_800BA1B4;
extern s32 D_800AE640;
extern s32 D_800A6430;
extern s32 resLoad_lastId;
extern s32 resLoad_loadedFileIdx;
extern u8 resourceIdMap[];
extern u8 D_8006313C;
extern void func_8002D4C8(int arg0, int arg1);

s32 func_8001ACF0(s32 arg0, s32 arg1, s32 *arg2, s32 arg3, s32 arg4) {
    D_800747F0 = arg0;

    switch (arg0) {
    case 0: {
        s32 tmp;
        D_800C6D2C = arg1;
        D_800AE6E4 = (s32)arg2;
        D_800BA318 = arg3;
        D_800A6550 = arg4;
        tmp = *arg2;
        D_800BA1B4 = 1;
        D_800747F4 = tmp;
        break;
    }

    case 1: {
        s16 v;
        D_800BA1B4 = 2;
        if (arg1 == resLoad_lastId) {
            return 1;
        }
        if (*(s16 *)(resourceIdMap + arg1 * 6) == resLoad_loadedFileIdx) {
            v = *(s16 *)(&D_8006313C + arg1 * 6);
            if (v != 0) {
                func_8002D4C8((u16)v, 0);
                resLoad_lastId = arg1;
            }
            return 1;
        }
        D_800AE640 = arg1;
        D_800747F4 = arg1;
        break;
    }

    case 2: {
        s32 tmp;
        D_800AE6E4 = (s32)arg2;
        tmp = *arg2;
        D_800BA1B4 = 4;
        D_800747F4 = tmp;
        break;
    }

    case 3:
        D_800A6430 = arg1;
        D_800AE6E4 = (s32)arg2;
        D_800747F4 = arg1;
        D_800BA1B4 = 5;
        D_800747E4 = 0;
        D_800747E8 = 1;
        break;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/800", func_8001AE90);


extern s32 D_800BA1B4;

s32 func_8001AF04(void) {
    s32 value = D_800BA1B4;
    if (value == 0) {
        return 0;
    }
    if (value == 3) {
        return 1;
    }
    return 2;
}

INCLUDE_ASM("asm/nonmatchings/800", func_8001AF34);

INCLUDE_ASM("asm/nonmatchings/800", func_8001B0D4);

extern s32 D_800747E8;
s32 func_8001B22C(void) {
    return D_800747E8;
}


extern s32 resLoad_curId;
extern s32 resLoad_result;
extern void func_8001B26C(void);

s32 func_8001B23C(s32 a0) {
    resLoad_curId = a0;
    func_8001B26C();
    return resLoad_result;
}

INCLUDE_ASM("asm/nonmatchings/800", func_8001B26C);


extern void func_8001B34C(void);
extern s32 resLoad_state;

void func_8001B324(void) {
    resLoad_state = 0;
    func_8001B34C();
}


extern s32 resLoad_lastId;
extern s32 resLoad_loadedFileIdx;
extern s32 D_800A2B70;
extern s32 D_800BA0FC;

void func_8001B34C(void) {
    resLoad_lastId = 0;
    resLoad_loadedFileIdx = 0;
    D_800A2B70 = 0;
    D_800BA0FC = 0;
}

extern s32 resLoad_lastId;
s32 func_8001B374(void) {
    return resLoad_lastId;
}

extern s32 resLoad_state;
void func_8001B384(void) {
    resLoad_state = 0;
}


extern s32 resLoad_curId;
extern s32 resLoad_result;
extern void ResourceLoadStateMachine(void);

s32 func_8001B394(s32 a0) {
    resLoad_curId = a0;
    ResourceLoadStateMachine();
    return resLoad_result;
}

#ifdef NON_MATCHING
extern int func_8001A114(void);
extern void func_8001B710(void);
extern void func_8002D4C8(int arg0, int arg1);
extern void func_80036D58(int arg0);
extern int StreamLoadStateMachine(int arg0, void *loc, int n);
extern s32 CdQueueBusy(void);          /* defined later in this file */
extern s32 ResourceGetCdLoc(s16 arg0); /* defined later in this file */
extern s32 resLoad_state;
extern s32 resLoad_curId;
extern s32 resLoad_lastId;
extern s32 resLoad_loadedFileIdx;
extern s32 resLoad_result;
extern s32 cdReq_curSector;
extern u8 resourceIdMap[]; /* 6B entries {s16 fileIdx; s16 D_8006313A; s16 D_8006313C} */
extern u8 D_8006313A;
extern u8 D_8006313C;
extern u8 cdFileLocTable[];
extern s32 D_800AE6F4;
extern s32 D_800AE70C;
/* loads a resource by resLoad_curId via resourceIdMap; load-once cache
 * (resLoad_lastId/resLoad_loadedFileIdx). field0<0 -> non-CD path func_80036D58; else
 * ResourceGetCdLoc -> StreamLoadStateMachine -> func_8002D4C8 post-process. Polled on
 * resLoad_state; done flag resLoad_result. Phase 3 T3.
 * NON_MATCHING: logically faithful (Ghidra-derived), body close but not byte-exact. Residuals:
 * (1) block placement — the target lays state blocks 0->1->2->3 in order under a top beq-chain
 * dispatch (order 1,0,2,3); this nested-if emits the state-2/3 block inline. (2) frame 0x38 vs
 * 0x28 (~16B reserved locals the original keeps). (3) func_8002D4C8 arg is field2 & 0xFFFF.
 * A switch() risks a rodata jump table (target has none). A later structural / permuter pass. */
void ResourceLoadStateMachine(void) {
    int result;

    result = 0;
    if (resLoad_state != 1) {
        if (resLoad_state != 0) {
            if (resLoad_state == 2) {
                D_800AE6F4 = 0;
                D_800AE70C = 0;
                resLoad_state = 3;
            } else if (resLoad_state != 3) {
                goto done;
            }
            if (func_8001A114() != 0) {
                resLoad_state = 0;
            }
            goto done;
        }
        if (resLoad_curId == resLoad_lastId) {
            resLoad_result = 1;
            return;
        }
        if (*(s16 *)(resourceIdMap + resLoad_curId * 6) == resLoad_loadedFileIdx &&
            *(s16 *)(&D_8006313C + resLoad_curId * 6) != 0) {
            func_8002D4C8(*(s16 *)(&D_8006313C + resLoad_curId * 6), 0);
            resLoad_lastId = resLoad_curId;
            resLoad_result = 1;
            return;
        }
        if (CdQueueBusy() != 0) {
            goto done;
        }
        if (*(s16 *)(resourceIdMap + resLoad_curId * 6) < 0) {
            func_80036D58(*(s16 *)(&D_8006313A + resLoad_curId * 6));
            resLoad_result = 1;
            return;
        }
        if (ResourceGetCdLoc((s16)resLoad_curId) == 0) {
            resLoad_result = 1;
            return;
        }
        if (cdReq_curSector != 0 &&
            *(s32 *)(cdFileLocTable + *(s16 *)(resourceIdMap + resLoad_curId * 6) * 8) != cdReq_curSector) {
            goto done;
        }
        cdReq_curSector = *(s32 *)(cdFileLocTable + *(s16 *)(resourceIdMap + resLoad_curId * 6) * 8);
        resLoad_state++;
    }
    result = StreamLoadStateMachine(*(s16 *)(&D_8006313A + resLoad_curId * 6),
                                    cdFileLocTable + *(s16 *)(resourceIdMap + resLoad_curId * 6) * 8, 0x10);
    if (result == 2) {
        resLoad_state++;
        result = 0;
    }
done:
    if (result != 0) {
        resLoad_loadedFileIdx = *(s16 *)(resourceIdMap + resLoad_curId * 6);
        if (*(s16 *)(&D_8006313C + resLoad_curId * 6) > 0) {
            func_8002D4C8(*(s16 *)(&D_8006313C + resLoad_curId * 6), 0);
            resLoad_lastId = resLoad_curId;
            if (resLoad_curId == 0x3D) {
                func_8001B710();
            }
        }
        resLoad_state = 0;
        cdReq_curSector = 0;
    }
    resLoad_result = result;
}
#else
INCLUDE_ASM("asm/nonmatchings/800", ResourceLoadStateMachine);
#endif

INCLUDE_ASM("asm/nonmatchings/800", func_8001B710);

extern u8 resourceIdMap[];
extern u8 cdFileLocTable[];
s32 ResourceGetCdLoc(s16 arg0) {
    s32 idx = *(s16 *)(resourceIdMap + arg0 * 6);
    return *(s32 *)(cdFileLocTable + idx * 8);
}

INCLUDE_ASM("asm/nonmatchings/800", func_8001B7C4);

extern s32 D_800747FC;
void func_8001B85C(void) {
    D_800747FC = 0;
}

INCLUDE_ASM("asm/nonmatchings/800", func_8001B86C);


extern void func_8001BC6C(s32 a0, s32 a1);
extern u8 D_800630E8[];

void func_8001BA84(void) {
    s32 addr = (s32)&D_800630E8;

    func_8001BC6C(addr, 0x80);
    func_8001BC6C(addr + 8, 0x80);
    func_8001BC6C(addr + 16, 0x80);
    func_8001BC6C(addr + 24, 0x80);
}

INCLUDE_ASM("asm/nonmatchings/800", func_8001BADC);

INCLUDE_ASM("asm/nonmatchings/800", func_8001BB60);

INCLUDE_ASM("asm/nonmatchings/800", func_8001BBBC);

INCLUDE_ASM("asm/nonmatchings/800", func_8001BC6C);

INCLUDE_ASM("asm/nonmatchings/800", SsGetMute);

INCLUDE_ASM("asm/nonmatchings/800", func_8001BDA0);

extern s32 D_800747EC;
void func_8001BE20(void) {
    D_800747EC = 0;
}

INCLUDE_ASM("asm/nonmatchings/800", func_8001BE30);

extern s32 D_80063074;
s32 func_8001BFA0(void) {
    return D_80063074 & 0x1;
}

INCLUDE_ASM("asm/nonmatchings/800", func_8001BFB0);

INCLUDE_ASM("asm/nonmatchings/800", func_8001BFD0);

extern s32 D_800747D8;
s32 func_8001BFE8(void) {
    return D_800747D8;
}

INCLUDE_ASM("asm/nonmatchings/800", func_8001BFF8);


extern u8 D_800B9A11;
extern void func_8001F9F8(void);
extern void func_8001D1C4(void);

void func_8001C00C(void) {
    if (D_800B9A11 != 1) {
        func_8001F9F8();
        func_8001D1C4();
    }
}

INCLUDE_ASM("asm/nonmatchings/800", func_8001C044);

INCLUDE_ASM("asm/nonmatchings/800", func_8001C0C8);

INCLUDE_ASM("asm/nonmatchings/800", func_8001C14C);


extern void func_80054514(s32 a0, s32 a1);

void func_8001C1E4(void* a0, s32 a1) {
    s32 local_buf[8];

    *(s32 *)(a0 + 0x78) = a1 + 0x30;
    *(s32 *)(a0 + 0x30) = 0;

    func_80054514((s32)(a0 + 0x30), (s32)local_buf);
}

INCLUDE_ASM("asm/nonmatchings/800", func_8001C214);


extern void func_8001C9D0(void);
extern void func_80052D90(s32 a0, void *a1);
extern void func_80054514(s32 a0, s32 a1);

void func_8001C2C4(s32 a0) {
    s32 stack_buf[8];
    s32 *s1;

    func_8001C9D0();

    s1 = (s32 *)(a0 + 0x30);

    *(s16 *)(a0 + 0x0) = 1;
    *(s16 *)(a0 + 0x2) = 0;
    func_80052D90(0, s1);

    func_80054514((s32)s1, (s32)stack_buf);

    *(s32 *)(a0 + 0x24) = 0;
}

INCLUDE_ASM("asm/nonmatchings/800", func_8001C320);


extern void func_8001C9D0(void);
extern void func_80052D90(s32 a0, void *a1);
extern void func_80054514(s32 a0, s32 a1);

void func_8001C448(s32 a0) {
    s32 local_10[8];
    s32 s0_val = a0;
    s32 s1_val;

    func_8001C9D0();

    s1_val = s0_val + 0x30;
    *(s16 *)s0_val = 1;
    *(s16 *)(s0_val + 0x2) = 1;

    func_80052D90(0, (void *)s1_val);
    func_80054514(s1_val, (s32)&local_10[0]);

    *(s32 *)(s0_val + 0x24) = 0;
}

INCLUDE_ASM("asm/nonmatchings/800", func_8001C4A4);


extern void func_8001C9D0(void);
extern void func_80052D90(s32 a0, void *a1);
extern void func_80054514(s32 a0, s32 a1);

void func_8001C558(s32 a0) {
    u8 local_var[32];

    func_8001C9D0();
    *(s16 *)(a0 + 0x0) = 1;
    *(s16 *)(a0 + 0x2) = 7;
    func_80052D90(0, (void *)(a0 + 0x30));
    func_80054514((s32)(a0 + 0x30), (s32)&local_var[0]);
    *(s32 *)(a0 + 0x24) = 0;
}

INCLUDE_ASM("asm/nonmatchings/800", func_8001C5B8);


extern void func_8001C9D0(void);
extern void func_80052D90(s32 a0, void *a1);
extern void func_80054514(s32 a0, s32 a1);

void func_8001C6E4(void *a0) {
    s32 sp_buf[8];

    ((void (*)(void *))func_8001C9D0)(a0);

    *(s16 *)a0 = 1;
    *(s16 *)((s32)a0 + 2) = 8;

    func_80052D90(0, (void *)((s32)a0 + 0x30));
    func_80054514((s32)a0 + 0x30, (s32)sp_buf);

    *(s32 *)((s32)a0 + 0x24) = 0;
}

INCLUDE_ASM("asm/nonmatchings/800", func_8001C744);


extern void func_8001C9D0(void);
extern void func_80052D90(s32 a0, void *a1);
extern void func_80054514(s32 a0, s32 a1);

void func_8001C7B0(void *arg0) {
    s32 local_s1;
    u8 local_array[0x20];

    ((void (*)(void *))func_8001C9D0)(arg0);

    local_s1 = (s32)((char *)arg0 + 0x30);

    *(s16 *)((char *)arg0 + 0x0) = 1;
    *(s16 *)((char *)arg0 + 0x2) = 2;

    func_80052D90(0, (void *)local_s1);

    func_80054514(local_s1, (s32)local_array);

    *(s32 *)((char *)arg0 + 0x24) = 0;
}

INCLUDE_ASM("asm/nonmatchings/800", func_8001C810);


extern void func_8001C9D0(void);
extern void func_80052D90(s32 a0, void *a1);
extern void func_80054514(s32 a0, s32 a1);

void func_8001C8C4(s32 a0) {
    s32 local_10[4];
    s32 local_20[4];

    ((void (*)(s32))func_8001C9D0)(a0);
    *(s16 *)(a0 + 0x0) = 1;
    *(s16 *)(a0 + 0x2) = 5;
    func_80052D90(0, (void *)(a0 + 0x30));
    func_80054514(a0 + 0x30, (s32)local_10);
    *(s32 *)(a0 + 0x24) = 0;
}


extern void GsMapModelingData(unsigned long *p);

void func_8001C924(void *a0, s32 *a1) {
    s32 *s0;
    s32 v0;

    s0 = a1;
    *(s32 **)(a0 + 0x24) = s0;

    v0 = *s0;
    while (v0 != 0) {
        s32 tmp = *s0;
        s0++;
        GsMapModelingData((unsigned long *)((u32)tmp + 4));
        v0 = *s0;
    }
}


extern void GsMapModelingData(unsigned long *p);

void func_8001C97C(s32 *a0) {
    s32 *ptr = a0;
    s32 val;

    val = *ptr;
    if (val != 0) {
        do {
            s32 item = *ptr;
            ptr++;
            GsMapModelingData((unsigned long *)(item + 4));
            val = *ptr;
        } while (val != 0);
    }
}

INCLUDE_ASM("asm/nonmatchings/800", func_8001C9D0);

INCLUDE_ASM("asm/nonmatchings/800", func_8001CA1C);

INCLUDE_ASM("asm/nonmatchings/800", func_8001CA88);


extern void func_8001CF48(s32 a0);

void func_8001CB00(s32 a0, void *a1, s32 a2, s32 a3) {
    func_8001CF48(a0);
    *(s16 *)(a0 + 0x2) = 1;
    *(s16 *)(a0 + 0x28) = (s16)a2;
    *(s16 *)(a0 + 0x2A) = (s16)a3;
    *(s32 *)(a0 + 0x20) = (s32)a1;
    *(s32 *)(a0 + 0x4) = 0x8000000;
    *(s16 *)(a0 + 0x2C) = 0;
}

INCLUDE_ASM("asm/nonmatchings/800", func_8001CB6C);


extern void func_8001CF48(s32 a0);

void func_8001CBDC(s32 a0, void *a1, s32 a2, s32 a3) {
    func_8001CF48(a0);
    *(s16 *)(a0 + 0x2) = 0;
    *(s16 *)(a0 + 0x28) = (s16)a2;
    *(s16 *)(a0 + 0x2A) = (s16)a3;
    *(s32 *)(a0 + 0x20) = (s32)a1;
    *(s16 *)(a0 + 0x2C) = 0;
}


extern void func_8001CF48(s32 a0);

void func_8001CC3C(s32 a0, void *a1, s32 a2, s32 a3) {
    func_8001CF48(a0);
    *(s16 *)(a0 + 0x2) = 3;
    *(s16 *)(a0 + 0x28) = (s16)a2;
    *(s16 *)(a0 + 0x2A) = (s16)a3;
    *(s32 *)(a0 + 0x20) = (s32)a1;
    *(s16 *)(a0 + 0x2C) = 0;
}


extern void func_8001CF48(s32 a0);

void func_8001CCA0(s32 a0, s32 a1, s32 a2, s32 a3) {
    func_8001CF48(a0);
    *(s16 *)(a0 + 0x2) = 0x9;
    *(s16 *)(a0 + 0x28) = (s16)a2;
    *(s16 *)(a0 + 0x2A) = (s16)a3;
    *(s32 *)(a0 + 0x20) = a1;
    *(s16 *)(a0 + 0x2C) = 0;
}


extern void func_8001CF48(s32);

void func_8001CD04(s32 a0, s32 a1)
{
    func_8001CF48(a0);
    *(s16*)(a0 + 0x2) = 4;
    *(s32*)(a0 + 0x20) = a1;
    *(s16*)(a0 + 0xE) = 0;
    *(s16*)(a0 + 0x1E) = 0;
    *(s16*)(a0 + 0x2C) = 0;
}


extern void func_8001CF48(s32 a0);

void func_8001CD50(s32 a0, s32 a1) {
    s32 s0 = a0;
    s32 s1 = a1;
    func_8001CF48(s0);
    *(s16 *)((u8 *)s0 + 0x2) = 5;
    *(s32 *)((u8 *)s0 + 0x20) = s1;
    *(s16 *)((u8 *)s0 + 0xE) = 0;
    *(s16 *)((u8 *)s0 + 0x1E) = 0;
    *(s16 *)((u8 *)s0 + 0x2C) = 0;
}


extern void func_8001CF48(s32 a0);

void func_8001CD9C(s32 a0, s32 a1) {
    func_8001CF48(a0);
    *(s16 *)(a0 + 0x2) = 6;
    *(s32 *)(a0 + 0x20) = a1;
    *(s16 *)(a0 + 0xE) = 0;
    *(s16 *)(a0 + 0x1E) = 0;
    *(s16 *)(a0 + 0x2C) = 0;
}


extern void func_8001CF48(s32 a0);

void func_8001CDE8(s32 a0, s32 a1) {
    func_8001CF48(a0);
    *(s16 *)(a0 + 0x2) = 0x7;
    *(s32 *)(a0 + 0x20) = a1;
}


extern void func_8001CF48(s32 a0);

void func_8001CE28(s32 a0, s32 a1) {
    func_8001CF48(a0);
    *(s16 *)(a0 + 0x2) = 0x8;
    *(s32 *)(a0 + 0x20) = a1;
}


extern void func_8001CF48(s32 a0);

void func_8001CE68(s32 a0, s32 a1) {
    func_8001CF48(a0);
    *(s16 *)(a0 + 0x2) = 0x8;
    *(u8 *)(a0 + 0x27) = 0xBA;
    *(s32 *)(a0 + 0x4) |= 0x400000;
    *(s32 *)(a0 + 0x20) = a1;
}


extern void func_8001CF48(s32 a0);

void func_8001CEC0(s32 a0, s32 a1) {
    func_8001CF48(a0);
    *(s16 *)(a0 + 0x2) = 0xA;
    *(s32 *)(a0 + 0x20) = a1;
}


extern void func_8001CF48(s32 a0);

void func_8001CF00(s32 a0) {
    s32 s0 = a0;
    func_8001CF48(a0);
    *(s16 *)(s0 + 0x2) = 0xB;
}

INCLUDE_ASM("asm/nonmatchings/800", func_8001CF30);

INCLUDE_ASM("asm/nonmatchings/800", func_8001CF48);

INCLUDE_ASM("asm/nonmatchings/800", func_8001CFB8);

INCLUDE_ASM("asm/nonmatchings/800", func_8001CFDC);

INCLUDE_ASM("asm/nonmatchings/800", func_8001D050);

INCLUDE_ASM("asm/nonmatchings/800", func_8001D074);

void func_8001D0E8(s32 arg0, s32 arg1, s32 arg2) {
    *(s16 *)(arg0 + 0x28) = arg1;
    *(s16 *)(arg0 + 0x2A) = arg2;
}

INCLUDE_ASM("asm/nonmatchings/800", func_8001D0F4);

INCLUDE_ASM("asm/nonmatchings/800", func_8001D130);

INCLUDE_ASM("asm/nonmatchings/800", func_8001D150);

INCLUDE_ASM("asm/nonmatchings/800", func_8001D16C);

INCLUDE_ASM("asm/nonmatchings/800", func_8001D1C4);

INCLUDE_ASM("asm/nonmatchings/800", func_8001D388);

INCLUDE_ASM("asm/nonmatchings/800", func_8001D3FC);

INCLUDE_ASM("asm/nonmatchings/800", func_8001D70C);

INCLUDE_ASM("asm/nonmatchings/800", func_8001D8C4);

INCLUDE_ASM("asm/nonmatchings/800", func_8001DA34);

INCLUDE_ASM("asm/nonmatchings/800", func_8001E094);

INCLUDE_ASM("asm/nonmatchings/800", func_8001E378);

INCLUDE_ASM("asm/nonmatchings/800", func_8001E668);


extern u16 D_800B9A02;
extern u8 D_800A6518[];
extern s32 func_80052460(s32 a0, s32 a1, s32 a2);

void func_8001E7E0(u8 *arg0)
{
    s32 buf[9];
    u16 ox, oy;
    u8 *otp;
    u8 *p;
    u32 attr;
    u32 pri;
    s32 shift;
    s32 mode;
    u32 sx, sy;
    u16 vx, vy;
    s32 vv;
    u16 tv;
    s32 tpage;
    u16 id;

    pri = *(u16 *)(arg0 + 0x2C) & 0x3FFF;
    if (pri < 0x1000) {
        p = *(u8 **)(arg0 + 0x20);
        ox = *(u16 *)(arg0 + 0x8);
        oy = *(u16 *)(arg0 + 0xA);
        attr = *(u32 *)(arg0 + 0x4);
        mode = (attr >> 24) & 3;
        shift = 2 - mode;
        otp = &D_800A6518[(u16)D_800B9A02 * 20];
        do {
            id = *(u16 *)p;
            sx = *(u16 *)(arg0 + 0x28) + (*(s16 *)(p + 4) >> shift);
            vx = sx;
            sy = *(u16 *)(arg0 + 0x2A) + *(u16 *)(p + 6);
            vy = sy;
            if (attr & 0x40000000) {
                tpage = (mode << 7) | (((attr >> 28) & 3) << 5) | ((sy & 0x100) >> 4) |
                        ((sx & 0x3C0) >> 6) | ((sy & 0x200) << 2);
            } else {
                tpage = (mode << 7) | (1 << 5) | ((sy & 0x100) >> 4) |
                        ((sx & 0x3C0) >> 6) | ((sy & 0x200) << 2);
            }
            buf[0] = attr;
            *(s16 *)((u8 *)buf + 0x04) =
                *(u16 *)(p + 8) + (ox + *(u16 *)(arg0 + 0x2E));
            *(s16 *)((u8 *)buf + 0x06) =
                *(u16 *)(p + 10) + (oy + *(u16 *)(arg0 + 0x30));
            *(s16 *)((u8 *)buf + 0x08) = *(u8 *)(p + 2);
            *(s16 *)((u8 *)buf + 0x0A) = *(u8 *)(p + 3);
            *(s16 *)((u8 *)buf + 0x0C) = tpage;
            *(u8 *)((u8 *)buf + 0x0E) = (vx - ((tpage & 0xF) << 6)) << shift;
            vv = vy;
            if (tpage & 0x10) {
                tv = vv - 0x100;
                *(u8 *)((u8 *)buf + 0x0F) = tv;
            } else {
                tv = vv;
                *(u8 *)((u8 *)buf + 0x0F) = tv;
            }
            *(s16 *)((u8 *)buf + 0x10) =
                (*(u8 *)(arg0 + 0x27) < 0xE0) ? 0x160 : 0x100;
            p += 12;
            *(s16 *)((u8 *)buf + 0x12) = *(u8 *)(arg0 + 0x27) + 0x100;
            *(u8 *)((u8 *)buf + 0x16) = 0x80;
            *(u8 *)((u8 *)buf + 0x15) = 0x80;
            *(u8 *)((u8 *)buf + 0x14) = 0x80;
            func_80052460((s32)buf, (s32)otp, (u16)pri);
        } while ((id & 0xFF) != 0xFF);
    }
}

INCLUDE_ASM("asm/nonmatchings/800", func_8001EA14);

INCLUDE_ASM("asm/nonmatchings/800", func_8001EFE0);


/* func_8001F730 — rotate the four corners of a POLY_FT4-shaped primitive
 * (x/y pairs at +0x08, +0x10, +0x18, +0x20) about a u16 centre point (a1)
 * using the rotation matrix built by func_80020DA4(a0, &m).
 * Fully unrolled in the source: gcc-2.7.2 -O2 does not unroll loops. */

extern void func_80020DA4(s32 a0, s32 a1);

#define SRM_8001F730(r0) __asm__ volatile (              \
    "lw $12, 0( %0 );"                                   \
    "lw $13, 4( %0 );"                                   \
    "ctc2 $12, $0;"                                      \
    "ctc2 $13, $1;"                                      \
    "lw $12, 8( %0 );"                                   \
    "lw $13, 12( %0 );"                                  \
    "lw $14, 16( %0 );"                                  \
    "ctc2 $12, $2;"                                      \
    "ctc2 $13, $3;"                                      \
    "ctc2 $14, $4"                                       \
    :                                                    \
    : "r"( r0 )                                          \
    : "$12", "$13", "$14" )

#define LDV0_8001F730(r0) __asm__ volatile (             \
    "lwc2 $0, 0( %0 );"                                  \
    "lwc2 $1, 4( %0 )"                                   \
    :                                                    \
    : "r"( r0 )                                          \
    : "memory" )

#define RTV0_8001F730() __asm__ volatile (               \
    "nop;"                                               \
    "nop;"                                               \
    "mvmva 1, 0, 0, 3, 0"                                \
    : : : "memory" )

#define STLVNL_8001F730(r0) __asm__ volatile (           \
    "swc2 $25, 0( %0 );"                                 \
    "swc2 $26, 4( %0 );"                                 \
    "swc2 $27, 8( %0 )"                                  \
    :                                                    \
    : "r"( r0 )                                          \
    : "memory" )

void func_8001F730(s32 a0, void *a1, void *a2)
{
    s32  matrix[8];   /* sp+0x10 */
    s16  sv[4][4];    /* sp+0x30 */
    s32  out[4][4];   /* sp+0x50 */
    u16 *c = (u16 *)a1;
    u8  *p = (u8 *)a2;

    func_80020DA4(a0, (s32)matrix);
    SRM_8001F730(matrix);

    sv[0][0] = *(u16 *)(p + 0x08) - c[0];
    sv[0][1] = *(u16 *)(p + 0x0A) - c[1];
    sv[0][2] = 0;
    sv[1][0] = *(u16 *)(p + 0x10) - c[0];
    sv[1][1] = *(u16 *)(p + 0x12) - c[1];
    sv[1][2] = 0;
    sv[2][0] = *(u16 *)(p + 0x18) - c[0];
    sv[2][1] = *(u16 *)(p + 0x1A) - c[1];
    sv[2][2] = 0;
    sv[3][0] = *(u16 *)(p + 0x20) - c[0];
    sv[3][1] = *(u16 *)(p + 0x22) - c[1];
    sv[3][2] = 0;

    LDV0_8001F730(sv[0]);
    RTV0_8001F730();
    STLVNL_8001F730(out[0]);

    LDV0_8001F730(sv[1]);
    RTV0_8001F730();
    STLVNL_8001F730(out[1]);

    LDV0_8001F730(sv[2]);
    RTV0_8001F730();
    STLVNL_8001F730(out[2]);

    LDV0_8001F730(sv[3]);
    RTV0_8001F730();
    STLVNL_8001F730(out[3]);

    *(u16 *)(p + 0x08) = c[0] + out[0][0];
    *(u16 *)(p + 0x0A) = c[1] + out[0][1];
    *(u16 *)(p + 0x10) = c[0] + out[1][0];
    *(u16 *)(p + 0x12) = c[1] + out[1][1];
    *(u16 *)(p + 0x18) = c[0] + out[2][0];
    *(u16 *)(p + 0x1A) = c[1] + out[2][1];
    *(u16 *)(p + 0x20) = c[0] + out[3][0];
    *(u16 *)(p + 0x22) = c[1] + out[3][1];
}

void func_8001F974(void) {
}

INCLUDE_ASM("asm/nonmatchings/800", func_8001F97C);

INCLUDE_ASM("asm/nonmatchings/800", func_8001F9F8);

INCLUDE_ASM("asm/nonmatchings/800", func_8001FB8C);

INCLUDE_ASM("asm/nonmatchings/800", func_8001FC08);

INCLUDE_ASM("asm/nonmatchings/800", func_80020248);

INCLUDE_ASM("asm/nonmatchings/800", func_80020598);

INCLUDE_ASM("asm/nonmatchings/800", func_80020A28);

INCLUDE_ASM("asm/nonmatchings/800", func_80020DA4);

INCLUDE_ASM("asm/nonmatchings/800", func_80020F34);


extern void func_80028620(s32 a0, void *a1);

void func_80021008(void *a0)
{
    void *s0 = a0;
    func_80028620(0, s0);
    func_80028620(1, (u8 *)s0 + 0x10);
    func_80028620(2, (u8 *)s0 + 0x20);
}


extern void func_80028620(s32 a0, void *a1);
extern u8 D_800A5E88;

void func_80021050(void) {
    u8 *s0 = &D_800A5E88;
    func_80028620(0, s0);
    func_80028620(1, s0 + 0x10);
    func_80028620(2, s0 + 0x20);
}

INCLUDE_ASM("asm/nonmatchings/800", func_8002109C);


extern s16 D_800AE7E0;
extern s16 D_800AE7E2;
extern s16 D_800AE7E4;

extern void func_80053AF8(s32 a0, s32 a1, s32 a2);

void func_80021120(s32 *arg0) {
    func_80053AF8(D_800AE7E0, D_800AE7E2, D_800AE7E4);
    *arg0 = *arg0 + 1;
}

INCLUDE_ASM("asm/nonmatchings/800", func_80021174);

INCLUDE_ASM("asm/nonmatchings/800", func_80021284);

INCLUDE_ASM("asm/nonmatchings/800", func_800215F4);

INCLUDE_ASM("asm/nonmatchings/800", func_80021D38);

INCLUDE_ASM("asm/nonmatchings/800", func_800221A8);

INCLUDE_ASM("asm/nonmatchings/800", func_800226C0);

INCLUDE_ASM("asm/nonmatchings/800", func_80023138);

INCLUDE_ASM("asm/nonmatchings/800", func_800233CC);

INCLUDE_ASM("asm/nonmatchings/800", func_800234E4);


typedef struct { u32 addr : 24; u32 len : 8; } PTag_80023570;

extern u8 D_800A6610[];
extern u16 D_800B9A02;
extern u8 *D_800A5E60;
extern s32 GetTPage(s32, s32, s32, s32);
extern s32 func_8005A600(s32, s32, s32, s32, s32);

void func_80023570(s32 arg0)
{
    u32 *ot;
    register u32 flags __asm__("$5");
    u16 idx;
    PTag_80023570 *slot2;
    u8 *cur;
    u8 *nxt;

    {
        register u8 *rec0 __asm__("$8");
        register u8 *p __asm__("$7");
        register u16 addX __asm__("$14");
        register u16 addY __asm__("$13");
        register u8 code __asm__("$11");
        register u32 tagconst __asm__("$15");
        register u32 *slot __asm__("$10");
        register u32 maskAddr __asm__("$9");
        register u32 maskLen __asm__("$12");
        register u8 *rec3 __asm__("$6");
        register u8 *q __asm__("$4");
        register u32 sc __asm__("$2");
        u8 last;
        u32 x, y;
        u16 t16;

        rec0 = *(u8 **)(arg0 + 0x20);
        sc = (u32)(u16)D_800B9A02;
        p = D_800A5E60;
        flags = *(u32 *)(arg0 + 4);
        addX = *(u16 *)(arg0 + 8);
        addY = *(u16 *)(arg0 + 0xA);
        idx = *(u16 *)(arg0 + 0x2C);
        ot = (u32 *)(D_800A6610 + (sc << 14));
        code = (flags & 0x40000000) ? 0x62 : 0x60;
        tagconst = 0x03000000;
        sc = idx << 2;
        slot = (u32 *)(sc + (u32)ot);
        maskAddr = 0x00FFFFFF;
        maskLen = 0xFF000000;
        rec3 = rec0 + 3;
        q = p + 0xE;

        do {
            q[-7] = code;
            *(u32 *)p = tagconst;
            q[-0xA] = rec0[0];
            q[-9] = rec3[-2];
            q[-8] = rec3[-1];
            *(u16 *)(q - 6) = addX + *(u16 *)(rec3 + 1);
            cur = D_800A5E60;
            *(u16 *)(q - 4) = addY + *(u16 *)(rec3 + 3);
            t16 = *(u16 *)(rec3 + 5);
            rec0 += 0xC;
            *(u16 *)(q - 2) = t16;
            t16 = *(u16 *)(rec3 + 7);
            nxt = cur + 0x10;
            D_800A5E60 = nxt;
            *(u16 *)(q) = t16;
            q += 0x10;

            x = *(u32 *)p;
            y = *slot;
            x = x & maskLen;
            y = y & maskAddr;
            x = x | y;
            *(u32 *)p = x;
            x = (u32)p & maskAddr;
            p += 0x10;
            y = *slot;
            y = y & maskLen;
            y = y | x;
            *slot = y;

            last = rec3[0];
            rec3 += 0xC;
        } while (last == 0);
    }

    if (flags & 0x40000000) {
        s32 tp;

        D_800A5E60 = cur + 0x1C;
        tp = GetTPage(2, (flags >> 28) & 3, 0x280, 0);
        func_8005A600((s32)nxt, 0, 0, (u16)tp, 0);

        slot2 = (PTag_80023570 *)(((u32)idx << 2) + (u32)ot);
        ((PTag_80023570 *)nxt)->addr = slot2->addr;
        slot2->addr = (u32)nxt;
    }
}

INCLUDE_ASM("asm/nonmatchings/800", func_8002374C);

INCLUDE_ASM("asm/nonmatchings/800", func_80023BF0);

INCLUDE_ASM("asm/nonmatchings/800", func_80024054);

INCLUDE_ASM("asm/nonmatchings/800", func_800241C0);

INCLUDE_ASM("asm/nonmatchings/800", func_800242D0);

INCLUDE_ASM("asm/nonmatchings/800", func_800243EC);

INCLUDE_ASM("asm/nonmatchings/800", func_80024448);

INCLUDE_ASM("asm/nonmatchings/800", func_800249F0);


/* ---- PsyQ GTE inline macros (the subset this routine uses) --------------- */
#define gte_ldv0(r0) __asm__ volatile (          \
    "lwc2 $0, 0( %0 );"                          \
    "lwc2 $1, 4( %0 )"                           \
    :                                            \
    : "r"( r0 ) )

#define gte_ldv3(r0, r1, r2) __asm__ volatile (  \
    "lwc2 $0, 0( %0 );"                          \
    "lwc2 $1, 4( %0 );"                          \
    "lwc2 $2, 0( %1 );"                          \
    "lwc2 $3, 4( %1 );"                          \
    "lwc2 $4, 0( %2 );"                          \
    "lwc2 $5, 4( %2 )"                           \
    :                                            \
    : "r"( r0 ), "r"( r1 ), "r"( r2 ) )

#define gte_ldrgb(r0) __asm__ volatile (         \
    "lwc2 $6, 0( %0 )"                           \
    :                                            \
    : "r"( r0 ) )

#define gte_rtps()  __asm__ volatile ("nop;nop;rtps")
#define gte_rtpt()  __asm__ volatile ("nop;nop;rtpt")
#define gte_nclip() __asm__ volatile ("nop;nop;nclip")
#define gte_avsz4() __asm__ volatile ("nop;nop;avsz4")
#define gte_nccs()  __asm__ volatile ("nop;nop;nccs")

#define gte_stsxy3_f4(r0) __asm__ volatile (     \
    "swc2 $12, 8( %0 );"                         \
    "swc2 $13, 12( %0 );"                        \
    "swc2 $14, 16( %0 )"                         \
    :                                            \
    : "r"( r0 )                                  \
    : "memory" )

#define gte_stsxy(r0) __asm__ volatile (         \
    "swc2 $14, 0( %0 )"                          \
    :                                            \
    : "r"( r0 )                                  \
    : "memory" )

#define gte_strgb(r0) __asm__ volatile (         \
    "swc2 $22, 0( %0 )"                          \
    :                                            \
    : "r"( r0 )                                  \
    : "memory" )

#define gte_stopz(r0) __asm__ volatile (         \
    "swc2 $24, 0( %0 )"                          \
    :                                            \
    : "r"( r0 )                                  \
    : "memory" )

#define gte_stotz(r0) __asm__ volatile (         \
    "swc2 $7, 0( %0 )"                           \
    :                                            \
    : "r"( r0 )                                  \
    : "memory" )

#define gte_stflg(r0) __asm__ volatile (         \
    "cfc2 $12, $31;"                             \
    "nop;"                                       \
    "sw $12, 0( %0 )"                            \
    :                                            \
    : "r"( r0 )                                  \
    : "$12", "memory" )

/* ---- types --------------------------------------------------------------- */
typedef struct {
    s16 vx, vy, vz, pad;
} SVECTOR_80024BC0;

typedef struct {
    u32 tag;                    /* 0x00 */
    u8  r0, g0, b0, code;       /* 0x04 */
    s16 x0, y0;                 /* 0x08 */
    s16 x1, y1;                 /* 0x0C */
    s16 x2, y2;                 /* 0x10 */
    s16 x3, y3;                 /* 0x14 */
} POLY_F4;                      /* 0x18 */

typedef struct {
    u32 tag;                    /* 0x00 */
    u32 code0;                  /* 0x04 */
} DR_MODE;                      /* 0x08 */

typedef struct {
    s32 unk00;                  /* 0x00 */
    u32 rgb;                    /* 0x04 */
    u16 n0;                     /* 0x08 */
    u16 v0;                     /* 0x0A */
    u16 v1;                     /* 0x0C */
    u16 v2;                     /* 0x0E */
    u16 v3;                     /* 0x10 */
    u16 pad;                    /* 0x12 */
} Face;                         /* 0x14 */

extern s32 D_800A2B78;

POLY_F4 *func_80024BC0(Face *f, SVECTOR_80024BC0 *sv, SVECTOR_80024BC0 *nv, POLY_F4 *poly0,
                       s32 n, s32 shift, u32 *ot)
{
    POLY_F4 *poly = poly0;
    s32 flag;
    s32 otz;
    u32 *p;

    if (n != 0) {
    do {
        gte_ldv3(&sv[f->v0], &sv[f->v1], &sv[f->v2]);
        gte_rtpt();
        gte_stflg(&flag);
        if ((flag & 0xFFFFEFFF) == 0) {
            gte_nclip();
            gte_stopz(&otz);
            if (otz > 0) {
                gte_stsxy3_f4(poly);
                gte_ldv0(&sv[f->v3]);
                gte_rtps();
                gte_stflg(&flag);
                if ((flag & 0xFFFFEFFF) == 0) {
                    gte_stsxy(&poly->x3);
                    gte_avsz4();
                    gte_stotz(&otz);
                    gte_ldrgb(&f->rgb);
                    gte_ldv0(&nv[f->n0]);
                    gte_nccs();
                    gte_strgb(&poly->r0);
                    p = &ot[otz >> shift];
                    poly->tag = (*p & 0x00FFFFFF) | 0x05000000;
                    *p = (u32)poly & 0x00FFFFFF;
                    poly++;
                    if (D_800A2B78 != 0 && (poly[-1].code & 2) != 0) {
                        s32 z = otz;
                        *((u8 *)poly + 3) = 1;
                        p = &ot[z >> shift];
                        *(u32 *)((u8 *)poly + 4) =
                            0xE100000A | ((D_800A2B78 & 3) << 5);
                        poly->tag = (*p & 0x00FFFFFF) | 0x01000000;
                        *p = (u32)poly & 0x00FFFFFF;
                        poly = (POLY_F4 *)((u8 *)poly + 8);
                    }
                }
            }
        }
        n--;
        f++;
    } while (n != 0);
    }
    return poly;
}


/* ---- PsyQ inline_c.h GTE macros ---- */
#define gte_ldv3(r0, r1, r2) __asm__ volatile ( \
    "lwc2 $0, 0( %0 );"                         \
    "lwc2 $1, 4( %0 );"                         \
    "lwc2 $2, 0( %1 );"                         \
    "lwc2 $3, 4( %1 );"                         \
    "lwc2 $4, 0( %2 );"                         \
    "lwc2 $5, 4( %2 )"                          \
    :                                           \
    : "r"( r0 ), "r"( r1 ), "r"( r2 ) )

#define gte_ldv0(r0) __asm__ volatile (         \
    "lwc2 $0, 0( %0 );"                         \
    "lwc2 $1, 4( %0 )"                          \
    :                                           \
    : "r"( r0 ) )

#define gte_ldrgb(r0) __asm__ volatile (        \
    "lwc2 $6, 0( %0 )"                          \
    :                                           \
    : "r"( r0 ) )

#define gte_rtpt()  __asm__ volatile ("nop;nop;rtpt")
#define gte_nclip() __asm__ volatile ("nop;nop;nclip")
#define gte_avsz3() __asm__ volatile ("nop;nop;avsz3")
#define gte_nccs()  __asm__ volatile ("nop;nop;nccs")

#define gte_stflg(r0) __asm__ volatile (        \
    "cfc2 $12, $31;"                            \
    "nop;"                                      \
    "sw   $12, 0( %0 )"                         \
    :                                           \
    : "r"( r0 )                                 \
    : "$12", "memory" )

#define gte_stopz(r0) __asm__ volatile (        \
    "swc2 $24, 0( %0 )"                         \
    :                                           \
    : "r"( r0 )                                 \
    : "memory" )

#define gte_stotz(r0) __asm__ volatile (        \
    "swc2 $7, 0( %0 )"                          \
    :                                           \
    : "r"( r0 )                                 \
    : "memory" )

#define gte_strgb(r0) __asm__ volatile (        \
    "swc2 $22, 0( %0 )"                         \
    :                                           \
    : "r"( r0 )                                 \
    : "memory" )

#define gte_stsxy3_g3(r0) __asm__ volatile (    \
    "swc2 $12,  8( %0 );"                       \
    "swc2 $13, 16( %0 );"                       \
    "swc2 $14, 24( %0 )"                        \
    :                                           \
    : "r"( r0 )                                 \
    : "memory" )

typedef struct {
    u32 pad0;
    u32 rgb0;
    u32 rgb1;
    u32 rgb2;
    u16 n0;
    u16 v0;
    u16 v1;
    u16 v2;
} TmdG3;

extern s32 D_800A2B78;

u8 *func_80024DE8(TmdG3 *prim, u8 *vtx, u8 *nrm, u8 *pkt, s32 n, s32 shift, u32 *ot)
{
    s32 flag;
    s32 z;
    u32 *otp;

    if (n != 0) {
        /* Identity no-op (emits nothing). It must sit in the loop PREHEADER (inside the
           `if (n != 0)`), not before the guard branch.
           Why: loop.c `record_initial`/`valid_initial_value_p` otherwise take the biv's
           initial value to be the raw incoming hard reg $a3, so the `pkt + 4` giv is
           emitted as `addiu giv,$a3,4`.  That keeps $a3 live past the parameter copy, so
           the pkt pseudo CONFLICTS with $a3 and can never live there (costing an extra
           `move`).  An asm_operands src makes valid_initial_value_p reject it, the giv is
           computed from the pseudo, and pkt keeps $a3.
           In the preheader it also stays clear of reorg's backward delay-slot scan, which
           breaks on any asm and would otherwise lose `addu $t5,$a0,$zero` from the guard's
           delay slot. */
        __asm__("" : "=r"(pkt) : "0"(pkt));
        do {
            gte_ldv3(vtx + prim->v0 * 8, vtx + prim->v1 * 8, vtx + prim->v2 * 8);
            gte_rtpt();
            gte_stflg(&flag);
            if ((flag & ~0x1000) == 0) {
                gte_nclip();
                gte_stopz(&z);
                if (z > 0) {
                    gte_stsxy3_g3(pkt);
                    gte_avsz3();
                    gte_stotz(&z);
                    gte_ldv0(nrm + prim->n0 * 8);
                    gte_ldrgb(&prim->rgb0);
                    gte_nccs();
                    gte_strgb(pkt + 4);
                    gte_ldrgb(&prim->rgb1);
                    gte_nccs();
                    gte_strgb(pkt + 0xC);
                    gte_ldrgb(&prim->rgb2);
                    gte_nccs();
                    gte_strgb(pkt + 0x14);
                    pkt[7] = (pkt[7] & 2) | 0x30;
                    otp = ot + (z >> shift);
                    *(u32 *)pkt = (*otp & 0xFFFFFF) | 0x6000000;
                    *otp = (u32)pkt & 0xFFFFFF;
                    pkt += 0x1C;
                    if (D_800A2B78 != 0) {
                        if (pkt[7 - 0x1C] & 2) {
                            otp = ot + (z >> shift);
                            pkt[3] = 1;
                            *(u32 *)(pkt + 4) = ((D_800A2B78 & 3) << 5) | 0xE100000A;
                            *(u32 *)pkt = (*otp & 0xFFFFFF) | 0x1000000;
                            *otp = (u32)pkt & 0xFFFFFF;
                            pkt += 8;
                        }
                    }
                }
            }
            n--;
            prim++;
        } while (n != 0);
    }
    return pkt;
}


/* ------------------------------------------------------------------ *
 * func_80025000 — gouraud-quad (POLY_G4) transform + light + OT link.
 * GTE inline-asm dialect copied from the proven ov_SC03_099 TUs.
 * ------------------------------------------------------------------ */

#define gte_ldv0(r0) __asm__ volatile (          \
    "lwc2 $0, 0( %0 );"                          \
    "lwc2 $1, 4( %0 )"                           \
    :                                            \
    : "r"( r0 ) )

#define gte_ldv3(r0, r1, r2) __asm__ volatile (  \
    "lwc2 $0, 0( %0 );"                          \
    "lwc2 $1, 4( %0 );"                          \
    "lwc2 $2, 0( %1 );"                          \
    "lwc2 $3, 4( %1 );"                          \
    "lwc2 $4, 0( %2 );"                          \
    "lwc2 $5, 4( %2 )"                           \
    :                                            \
    : "r"( r0 ), "r"( r1 ), "r"( r2 ) )

#define gte_ldrgb(r0) __asm__ volatile (         \
    "lwc2 $6, 0( %0 )"                           \
    :                                            \
    : "r"( r0 ) )

#define gte_rtps()  __asm__ volatile ("nop;nop;rtps")
#define gte_rtpt()  __asm__ volatile ("nop;nop;rtpt")
#define gte_nclip() __asm__ volatile ("nop;nop;nclip")
#define gte_avsz4() __asm__ volatile ("nop;nop;avsz4")
#define gte_nccs()  __asm__ volatile ("nop;nop;nccs")

#define gte_stflg(r0) __asm__ volatile (         \
    "cfc2 $12, $31;"                             \
    "nop;"                                       \
    "sw $12, 0( %0 )"                            \
    :                                            \
    : "r"( r0 )                                  \
    : "$12", "memory" )

#define gte_stopz(r0) __asm__ volatile (         \
    "swc2 $24, 0( %0 )"                          \
    :                                            \
    : "r"( r0 )                                  \
    : "memory" )

#define gte_stotz(r0) __asm__ volatile (         \
    "swc2 $7, 0( %0 )"                           \
    :                                            \
    : "r"( r0 )                                  \
    : "memory" )

#define gte_stsxy(r0) __asm__ volatile (         \
    "swc2 $14, 0( %0 )"                          \
    :                                            \
    : "r"( r0 )                                  \
    : "memory" )

#define gte_stsxy3_g4(r0) __asm__ volatile (     \
    "swc2 $12, 8( %0 );"                         \
    "swc2 $13, 16( %0 );"                        \
    "swc2 $14, 24( %0 )"                         \
    :                                            \
    : "r"( r0 )                                  \
    : "memory" )

#define gte_strgb(r0) __asm__ volatile (         \
    "swc2 $22, 0( %0 )"                          \
    :                                            \
    : "r"( r0 )                                  \
    : "memory" )

typedef struct { s16 vx, vy, vz, pad; } SVEC_80025000;    /* 0x08 */
typedef struct { u8  r, g, b, code; }   RGBC;    /* 0x04 */

typedef struct {            /* 0x20 — source quad description */
    u32  unk0;
    RGBC c0;
    RGBC c1;
    RGBC c2;
    RGBC c3;
    u16  n;
    u16  v0;
    u16  v1;
    u16  v2;
    u16  v3;
    u16  unk1E;
} SRCQ;

typedef struct {            /* 0x24 — POLY_G4 */
    u32  tag;
    RGBC c0;
    u32  xy0;
    RGBC c1;
    u32  xy1;
    RGBC c2;
    u32  xy2;
    RGBC c3;
    u32  xy3;
} PG4;

typedef struct { u32 tag; u32 code0; } DRM;      /* 0x08 */

extern s32 D_800A2B78;

PG4 *func_80025000(SRCQ *p, SVEC_80025000 *verts, SVEC_80025000 *norms, PG4 *poly0, s32 n,
                   s32 shift, u32 *ot)
{
    struct { s32 flag; s32 z; } g;
    u32 *otp;
    PG4 *prim;
    PG4 *poly = poly0;
    

    while (n != 0) {
        gte_ldv3(&verts[p->v0], &verts[p->v1], &verts[p->v2]);
        gte_rtpt();
        gte_stflg(&g.flag);
        if ((g.flag & 0xFFFFEFFF) == 0) {
            gte_nclip();
            gte_stopz(&g.z);
            if (g.z > 0) {
                gte_stsxy3_g4(poly);
                gte_ldv0(&verts[p->v3]);
                gte_rtps();
                gte_stflg(&g.flag);
                if ((g.flag & 0xFFFFEFFF) == 0) {
                    gte_stsxy(&poly->xy3);
                    gte_avsz4();
                    gte_stotz(&g.z);

                    gte_ldv0(&norms[p->n]);
                    gte_ldrgb(&p->c0);
                    gte_nccs();
                    gte_strgb(&poly->c0);
                    gte_ldrgb(&p->c1);
                    gte_nccs();
                    gte_strgb(&poly->c1);
                    gte_ldrgb(&p->c2);
                    gte_nccs();
                    gte_strgb(&poly->c2);
                    gte_ldrgb(&p->c3);
                    gte_nccs();
                    gte_strgb(&poly->c3);

                    poly->c0.code = (poly->c0.code & 2) | 0x38;

                    otp = &ot[g.z >> shift];
                    poly->tag = (*otp & 0xFFFFFF) | 0x08000000;
                    *otp = (u32)poly & 0xFFFFFF;

                    prim = poly;
                    poly = (PG4 *)((u8 *)poly + 0x24);

                    if (D_800A2B78 != 0) {
                        if ((prim->c0.code & 2) != 0) {
                            otp = &ot[g.z >> shift];
                            ((u8 *)poly)[3] = 1;
                            ((DRM *)poly)->code0 =
                                0xE100000A | ((D_800A2B78 & 3) << 5);
                            ((DRM *)poly)->tag = (*otp & 0xFFFFFF) | 0x01000000;
                            *otp = (u32)poly & 0xFFFFFF;
                            poly = (PG4 *)((u8 *)poly + 8);
                        }
                    }
                }
            }
        }
        n--;
        p++;
    }
    return poly;
}


/* --- PsyQ inline_c.h GTE macros (verbatim bodies, project spelling) --- */
#define gte_ldv3(r0, r1, r2) __asm__ volatile (  \
    "lwc2 $0, 0( %0 );"                          \
    "lwc2 $1, 4( %0 );"                          \
    "lwc2 $2, 0( %1 );"                          \
    "lwc2 $3, 4( %1 );"                          \
    "lwc2 $4, 0( %2 );"                          \
    "lwc2 $5, 4( %2 )"                           \
    :                                            \
    : "r"( r0 ), "r"( r1 ), "r"( r2 ) )

#define gte_ldrgb(r0) __asm__ volatile (         \
    "lwc2 $6, 0( %0 )"                           \
    :                                            \
    : "r"( r0 ) )

#define gte_rtpt()  __asm__ volatile ("nop;nop;rtpt")
#define gte_nclip() __asm__ volatile ("nop;nop;nclip")
#define gte_avsz3() __asm__ volatile ("nop;nop;avsz3")
#define gte_ncct()  __asm__ volatile ("nop;nop;ncct")

#define gte_stflg(r0) __asm__ volatile (         \
    "cfc2 $12, $31;"                             \
    "nop;"                                       \
    "sw $12, 0( %0 )"                            \
    :                                            \
    : "r"( r0 )                                  \
    : "$12", "memory" )

#define gte_stopz(r0) __asm__ volatile (         \
    "swc2 $24, 0( %0 )"                          \
    :                                            \
    : "r"( r0 )                                  \
    : "memory" )

#define gte_stotz(r0) __asm__ volatile (         \
    "swc2 $7, 0( %0 )"                           \
    :                                            \
    : "r"( r0 )                                  \
    : "memory" )

#define gte_stsz3(r0, r1, r2) __asm__ volatile ( \
    "swc2 $17, 0( %0 );"                         \
    "swc2 $18, 0( %1 );"                         \
    "swc2 $19, 0( %2 )"                          \
    :                                            \
    : "r"( r0 ), "r"( r1 ), "r"( r2 )            \
    : "memory" )

#define gte_stsxy3_g3(r0) __asm__ volatile (     \
    "swc2 $12, 8( %0 );"                         \
    "swc2 $13, 16( %0 );"                        \
    "swc2 $14, 24( %0 )"                         \
    :                                            \
    : "r"( r0 )                                  \
    : "memory" )

#define gte_strgb3_g3(r0) __asm__ volatile (     \
    "swc2 $20, 4( %0 );"                         \
    "swc2 $21, 12( %0 );"                        \
    "swc2 $22, 20( %0 )"                         \
    :                                            \
    : "r"( r0 )                                  \
    : "memory" )

extern s32 D_80078D88[];
extern s32 D_800A2B78;

typedef struct { s16 vx, vy, vz, pad; } Vec8;
typedef struct {
    u32 unk0;
    u32 rgbc;
    u16 n0, v0, n1, v1, n2, v2;
} Prim;

u8 *func_8002528C(Prim *pr, Vec8 *vtx, Vec8 *nrm, void *arg3, s32 n, s32 shift, u32 *ot)
{
    struct { s32 flag, opz, sz1, sz2, sz3; } g;
    u8 *pk = (u8 *)arg3;
    u32 *otp;
    s32 z;

    if (n != 0) {
        do {
            gte_ldv3(&vtx[pr->v0], &vtx[pr->v1], &vtx[pr->v2]);
            gte_rtpt();
            gte_stflg(&g.flag);
            if (!(g.flag & ~0x1000)) {
                gte_nclip();
                gte_stopz(&g.opz);
                if (g.opz > 0) {
                    gte_stsxy3_g3(pk);
                    if (D_80078D88[0] & 0x8000) {
                        gte_stsz3(&g.sz1, &g.sz2, &g.sz3);
                        if (g.sz1 > g.sz2) {
                            z = g.sz1;
                            if (z < g.sz3) {
                                z = g.sz3;
                            }
                        } else {
                            z = g.sz2;
                            if (z < g.sz3) {
                                z = g.sz3;
                            }
                        }
                        g.opz = z >> 2;
                    } else {
                        gte_avsz3();
                        gte_stotz(&g.opz);
                    }
                    gte_ldrgb(&pr->rgbc);
                    gte_ldv3(&nrm[pr->n0], &nrm[pr->n1], &nrm[pr->n2]);
                    gte_ncct();
                    gte_strgb3_g3(pk);
                    otp = &ot[g.opz >> shift];
                    *(u32 *)pk = (*otp & 0xFFFFFF) | 0x6000000;
                    *otp = (u32)pk & 0xFFFFFF;
                    pk += 0x1C;
                    if (D_800A2B78 != 0 && (pk[-0x15] & 2)) {
                        otp = &ot[g.opz >> shift];
                        pk[3] = 1;
                        *(u32 *)(pk + 4) = 0xE100000A | ((D_800A2B78 & 3) << 5);
                        *(u32 *)pk = (*otp & 0xFFFFFF) | 0x1000000;
                        *otp = (u32)pk & 0xFFFFFF;
                        pk += 8;
                    }
                }
            }
            n--;
            pr++;
        } while (n != 0);
    }
    return pk;
}


/* func_80025504 - POLY_G4 mesh transform + OT insert (GTE, PsyQ inline macros).
 *
 * Two non-obvious constructs are REQUIRED for the byte match (both emit ZERO
 * instructions); do not "clean them up":
 *
 *  1) __asm__("" : "=r"(poly) : "0"(poly));
 *     loop.c:3509 valid_initial_value_p() accepts a HARD reg as a biv's initial
 *     value when no call intervenes, so gcc would emit the poly+4 giv init as
 *     `addiu giv,$a3,4` reading the INCOMING $a3.  That keeps hard $a3 live past
 *     the param copy, so the poly pseudo CONFLICTS with $7 (see .greg
 *     "75 conflicts: ... 7"), loses the copy-preference, and gcc emits a spurious
 *     `move t1,$a3`.  Re-tying poly through an empty asm makes the biv init_set
 *     src an ASM_OPERANDS -> valid_initial_value_p() fails -> the pseudo is used,
 *     $a3 dies at the param copy, poly gets $a3, the copy folds away.
 *
 *  2) register GFace *p0 __asm__("$4") = prim;  +  fp = p0;
 *     prim needs the OPPOSITE treatment: its giv init must read the hard $a0
 *     (`addiu $t1,$a0,0x14`), but its copy `addu $t6,$a0,$zero` must schedule
 *     AFTER the three stack-arg loads.  Assigning through an $a0-pinned local
 *     gives the copy a late LUID while keeping (reg 4) as the biv's initial value.
 */

/* ---- PsyQ-style inline GTE macros (inline_c.h shapes) ---------------------- */
#define gte_ldv0(r0)  __asm__ volatile("lwc2 $0, 0(%0);lwc2 $1, 4(%0)" : : "r"(r0))
#define gte_ldv3(r0, r1, r2) __asm__ volatile(                              \
    "lwc2 $0, 0(%0);lwc2 $1, 4(%0);"                                        \
    "lwc2 $2, 0(%1);lwc2 $3, 4(%1);"                                        \
    "lwc2 $4, 0(%2);lwc2 $5, 4(%2)" : : "r"(r0), "r"(r1), "r"(r2))
#define gte_ldrgb(r0) __asm__ volatile("lwc2 $6, 0(%0)" : : "r"(r0))

#define gte_rtpt()  __asm__ volatile("nop;nop;cop2 0x0280030")
#define gte_rtps()  __asm__ volatile("nop;nop;cop2 0x0180001")
#define gte_nclip() __asm__ volatile("nop;nop;cop2 0x1400006")
#define gte_avsz4() __asm__ volatile("nop;nop;cop2 0x168002e")
#define gte_ncct()  __asm__ volatile("nop;nop;cop2 0x118043f")
#define gte_nccs()  __asm__ volatile("nop;nop;cop2 0x108041b")

#define gte_stflg(r0) __asm__ volatile("cfc2 $12, $31;nop;sw $12, 0(%0)" : : "r"(r0) : "$12", "memory")
#define gte_stopz(r0) __asm__ volatile("swc2 $24, 0(%0)" : : "r"(r0) : "memory")
#define gte_stotz(r0) __asm__ volatile("swc2 $7, 0(%0)" : : "r"(r0) : "memory")
#define gte_stsxy2(r0) __asm__ volatile("swc2 $14, 0(%0)" : : "r"(r0) : "memory")
#define gte_strgb2(r0) __asm__ volatile("swc2 $22, 0(%0)" : : "r"(r0) : "memory")
#define gte_stsxy3_g4(r0) __asm__ volatile(                                 \
    "swc2 $12, 8(%0);swc2 $13, 16(%0);swc2 $14, 24(%0)" : : "r"(r0) : "memory")
#define gte_strgb3_g4(r0) __asm__ volatile(                                 \
    "swc2 $20, 4(%0);swc2 $21, 12(%0);swc2 $22, 20(%0)" : : "r"(r0) : "memory")
#define gte_stsz4(r0, r1, r2, r3) __asm__ volatile(                         \
    "swc2 $16, 0(%0);swc2 $17, 0(%1);swc2 $18, 0(%2);swc2 $19, 0(%3)"       \
    : : "r"(r0), "r"(r1), "r"(r2), "r"(r3) : "memory")

/* ---- local types ----------------------------------------------------------- */
typedef struct {
    s16 vx, vy, vz, pad;
} GVec8; /* 0x08 */

typedef struct {
    s32 unk0;
    u32 rgb;
    u16 n0, v0;
    u16 n1, v1;
    u16 n2, v2;
    u16 n3, v3;
} GFace; /* 0x18 */

typedef struct {
    u32 tag;
    u8 r0, g0, b0, code;
    u32 xy0;
    u32 rgb1;
    u32 xy1;
    u32 rgb2;
    u32 xy2;
    u32 rgb3;
    u32 xy3;
} GPolyG4; /* 0x24 */

typedef struct {
    u8 addr0, addr1, addr2, len;
    u32 code0;
} GDrMode; /* 0x08 */

extern s32 D_80078D88[];
extern s32 D_800A2B78;

void *func_80025504(GFace *prim, GVec8 *vtx, GVec8 *nrm, GPolyG4 *poly, s32 n, s32 shift,
                    u32 *ot)
{
    s32 flag;
    s32 p;
    s32 sz0, sz1, sz2, sz3;
    s32 zmax, ztmp;
    u32 *op;
    GDrMode *dm;
    GFace *fp;
    register GFace *p0 __asm__("$4") = prim;

    __asm__("" : "=r"(poly) : "0"(poly));
    fp = p0;
    for (; n != 0; n--, fp++) {
            gte_ldv3(&vtx[fp->v0], &vtx[fp->v1], &vtx[fp->v2]);
            gte_rtpt();
            gte_stflg(&flag);
            if (flag & 0xffffefff) {
                continue;
            }
            gte_nclip();
            gte_stopz(&p);
            if (p <= 0) {
                continue;
            }
            gte_stsxy3_g4(poly);
            gte_ldv0(&vtx[fp->v3]);
            gte_rtps();
            gte_stflg(&flag);
            if (flag & 0xffffefff) {
                continue;
            }
            gte_stsxy2(&poly->xy3);
            if (D_80078D88[0] & 0x8000) {
                gte_stsz4(&sz0, &sz1, &sz2, &sz3);
                zmax = sz2;
                if (zmax < sz3) {
                    zmax = sz3;
                }
                ztmp = sz0;
                if (ztmp < sz1) {
                    ztmp = sz1;
                }
                if (ztmp < zmax) {
                    ztmp = zmax;
                }
                p = ztmp >> 2;
            } else {
                gte_avsz4();
                gte_stotz(&p);
            }
            gte_ldrgb(&fp->rgb);
            gte_ldv3(&nrm[fp->n0], &nrm[fp->n1], &nrm[fp->n2]);
            gte_ncct();
            gte_strgb3_g4(poly);
            gte_ldv0(&nrm[fp->n3]);
            gte_nccs();
            gte_strgb2(&poly->rgb3);

            op = &ot[p >> shift];
            poly->tag = (*op & 0xffffff) | 0x08000000;
            *op = (u32)poly & 0xffffff;
            poly++;
            if (D_800A2B78 != 0) {
                if (poly[-1].code & 2) {
                    dm = (GDrMode *)poly;
                    op = &ot[p >> shift];
                    dm->len = 1;
                    dm->code0 = 0xe100000a | ((D_800A2B78 & 3) << 5);
                    *(u32 *)dm = (*op & 0xffffff) | 0x01000000;
                    *op = (u32)dm & 0xffffff;
                    poly = (GPolyG4 *)((u8 *)dm + 8);
                }
            }
    }
    return poly;
}


/* ---- PsyQ inline GTE macros ------------------------------------------------
 * Raw `.word` forms: include/gte_macros.inc is not on the standalone match_one
 * assembler path, so the cop2 opcodes are spelled as their encoded words, taken
 * verbatim from the target .s:
 *     rtpt 0x4A280030 · nclip 0x4B400006 · avsz3 0x4B58002D · nccs 0x4B08041B
 * Everything else is the stock PSY-Q 4.7 inline_c.h text (gte_stflg's $12 scratch
 * is exactly the target's `cfc2 $t4,$31`).
 * --------------------------------------------------------------------------- */
#define gte_ldv0(r0) __asm__ volatile (                  \
    "lwc2 $0, 0( %0 );"                                  \
    "lwc2 $1, 4( %0 )"                                   \
    :                                                    \
    : "r"( r0 ) )
#define gte_ldv3(r0, r1, r2) __asm__ volatile (          \
    "lwc2 $0, 0( %0 );"                                  \
    "lwc2 $1, 4( %0 );"                                  \
    "lwc2 $2, 0( %1 );"                                  \
    "lwc2 $3, 4( %1 );"                                  \
    "lwc2 $4, 0( %2 );"                                  \
    "lwc2 $5, 4( %2 )"                                   \
    :                                                    \
    : "r"( r0 ), "r"( r1 ), "r"( r2 ) )
#define gte_ldrgb(r0) __asm__ volatile (                 \
    "lwc2 $6, 0( %0 )"                                   \
    :                                                    \
    : "r"( r0 ) )
#define gte_rtpt()  __asm__ volatile ("nop;nop;.word 0x4A280030")
#define gte_nclip() __asm__ volatile ("nop;nop;.word 0x4B400006")
#define gte_avsz3() __asm__ volatile ("nop;nop;.word 0x4B58002D")
#define gte_nccs()  __asm__ volatile ("nop;nop;.word 0x4B08041B")
#define gte_stflg(r0) __asm__ volatile (                 \
    "cfc2 $12, $31;"                                     \
    "nop;"                                               \
    "sw $12, 0( %0 )"                                    \
    :                                                    \
    : "r"( r0 )                                          \
    : "$12", "memory" )
#define gte_stopz(r0) __asm__ volatile (                 \
    "swc2 $24, 0( %0 )"                                  \
    :                                                    \
    : "r"( r0 )                                          \
    : "memory" )
#define gte_stotz(r0) __asm__ volatile (                 \
    "swc2 $7, 0( %0 )"                                   \
    :                                                    \
    : "r"( r0 )                                          \
    : "memory" )
#define gte_strgb(r0) __asm__ volatile (                 \
    "swc2 $22, 0( %0 )"                                  \
    :                                                    \
    : "r"( r0 )                                          \
    : "memory" )
#define gte_stsxy3_g3(r0) __asm__ volatile (             \
    "swc2 $12, 8( %0 );"                                 \
    "swc2 $13, 16( %0 );"                                \
    "swc2 $14, 24( %0 )"                                 \
    :                                                    \
    : "r"( r0 )                                          \
    : "memory" )

/* 8-byte SVECTOR: vertex / normal table entry (index scaled by 8 => sll 3). */
typedef struct {
    s16 vx, vy, vz, pad;
} SVEC8_80025818;

/* 0x1C POLY_G3 packet (tag + 6 words => tag length nibble 0x06). */
typedef struct {
    u32 tag;
    u8  r0, g0, b0, code;
    s16 x0, y0;
    u8  r1, g1, b1, pad1;
    s16 x1, y1;
    u8  r2, g2, b2, pad2;
    s16 x2, y2;
} PG3;

/* 0x1C TMD gouraud-3 (3 colours, no texture) primitive record. */
typedef struct {
    u32 hdr;
    u32 rgb0;
    u32 rgb1;
    u32 rgb2;
    u16 n0, v0;
    u16 n1, v1;
    u16 n2, v2;
} TPRIM_80025818;

extern s32 D_800A2B78;

PG3 *func_80025818(TPRIM_80025818 *prim, SVEC8_80025818 *vtx, SVEC8_80025818 *nrm, PG3 *poly,
                   s32 n, s32 shift, u32 *ot)
{
    s32 otz;
    s32 flag;
    u32 *otp;

    if (n != 0) {
        /* Zero-instruction launder of the `poly` biv's initial value.
         * Without it, loop.c's record_initial (loop.c:3454-3511) takes the biv's
         * initial value straight from the parameter copy `poly = $a3`, so the GIV
         * preheader init is emitted as `giv = (hard $a3) + 4`.  That keeps hard
         * $a3 live to the preheader, which makes the `poly` pseudo CONFLICT with
         * $a3 (dump: `75 conflicts: ... 7`), so $a3 goes to the GIV and `poly`
         * needs an extra `move`.  An asm_operands SET_SRC fails
         * valid_initial_value_p, so bl->initial_value stays the pseudo and $a3
         * stays free for `poly` -- byte-exact, 135 -> 134 instructions.
         * It MUST sit below the `n != 0` guard: above it the #APP/#NO_APP pair
         * blocks the `prim` parameter copy from hopping into the beqz delay slot
         * (cookbook RC-11). */
        __asm__ ("" : "=r"(poly) : "0"(poly));
        do {
            gte_ldv3(&vtx[prim->v0], &vtx[prim->v1], &vtx[prim->v2]);
            gte_rtpt();
            gte_stflg(&flag);
            if ((flag & ~0x1000) == 0) {
                gte_nclip();
                gte_stopz(&otz);
                if (otz > 0) {
                    gte_stsxy3_g3(poly);
                    gte_avsz3();
                    gte_stotz(&otz);
                    gte_ldv0(&nrm[prim->n0]);
                    gte_ldrgb(&prim->rgb0);
                    gte_nccs();
                    gte_strgb(&poly->r0);
                    gte_ldrgb(&prim->rgb1);
                    gte_nccs();
                    gte_strgb(&poly->r1);
                    gte_ldrgb(&prim->rgb2);
                    gte_nccs();
                    gte_strgb(&poly->r2);
                    poly->code = (poly->code & 2) | 0x30;
                    otp = ot + (otz >> shift);
                    *(u32 *)poly = (*otp & 0xFFFFFF) | 0x06000000;
                    *otp = (u32)poly & 0xFFFFFF;
                    poly++;
                    if (D_800A2B78 != 0) {
                        if (poly[-1].code & 2) {
                            /* 2-word DR_MODE packet chained in front of the G3 */
                            otp = ot + (otz >> shift);
                            *((u8 *)poly + 3) = 1;
                            *(u32 *)((u8 *)poly + 4) =
                                0xE100000A | ((D_800A2B78 & 3) << 5);
                            *(u32 *)poly = (*otp & 0xFFFFFF) | 0x01000000;
                            *otp = (u32)poly & 0xFFFFFF;
                            poly = (PG3 *)((u8 *)poly + 8);
                        }
                    }
                }
            }
            n--;
            prim++;
        } while (n != 0);
    }
    return poly;
}


/* func_80025A30 (main / src/800.c) -- TMD "quad, flat normal, gradation" emitter.
 * Per prim (stride 0x24): RTPT 3 verts -> flag/nclip cull -> RTPS 4th vert -> AVSZ4 -> 4x NCCS
 * (one shared normal, 4 base colours) -> POLY_G4 (code 0x38) -> OT insert (len 8).
 * If D_800A2B78 != 0 and the poly kept its bit-1 flag, a second 2-word 0xE100000A draw-mode
 * packet (len 1) is appended and linked into the same OT slot.
 *
 * MATCH 163/163. Two non-obvious levers (both were byte-decisive):
 *  1. ONE `pkt` pointer, not pkt+q. loop.c strength-reduces it into biv $a3 + giv($a3+4)=$t1;
 *     that is where the -0x21 / -0x1D style offsets come from. Writing an explicit `q = pkt+4`
 *     variable instead makes gcc build a THIRD register (giv q+3) -> +4 insns. Same for `prim`:
 *     one pointer -> biv $t3 + giv($a0+0x10)=$t2. (cookbook loop.md L1)
 *  2. The zero-byte `__asm__("" : "=r"(pkt) : "0"(pkt))` in the preheader. Without it loop.c's
 *     record_initial/valid_initial_value_p takes the biv's initial value from the HARD reg $a3
 *     (`addiu giv, a3, 4` reads hard a3 in the preheader), which keeps hard $a3 live past the
 *     param copy -> the pkt pseudo CONFLICTS with $a3 and can never be granted it: gcc then
 *     emits biv=$t1 / giv=$a3 plus an extra `move t1,a3` (164 ins, whole-loop register swap).
 *     A set whose SET_SRC is an asm_operands makes the initial value "complex" (loop.c:3509),
 *     so the giv init reads the PSEUDO, hard $a3 dies at the copy, and the biv wins $a3.
 *     It must sit INSIDE `if (n != 0)` so it lands in the preheader: an early `return` instead
 *     plants a CODE_LABEL that halts record_initial's backward scan for EVERY biv, which also
 *     robs `prim` of its hard-$a0 initial value (`addiu t2,t3,16` != `addiu t2,a0,0x10`).
 *  3. `o = &ot[z >> shift];` must precede `pkt[3] = 1;` -- the scheduler cannot hoist the
 *     `lw z` above an aliasing `sb`, so source order decides those 4 instructions (§175 lever A).
 *
 * PsyQ inline_c.h GTE macro bodies (same spelling as the matched
 * ov_SC01_000 renderer in src/ov_SC03_099/ov_SC03_099_jr_8017BEBC.c). */

#define gte_ldv0(r0) __asm__ volatile (          \
    "lwc2 $0, 0( %0 );"                          \
    "lwc2 $1, 4( %0 )"                           \
    :                                            \
    : "r"( r0 ) )

#define gte_ldv3(r0, r1, r2) __asm__ volatile (  \
    "lwc2 $0, 0( %0 );"                          \
    "lwc2 $1, 4( %0 );"                          \
    "lwc2 $2, 0( %1 );"                          \
    "lwc2 $3, 4( %1 );"                          \
    "lwc2 $4, 0( %2 );"                          \
    "lwc2 $5, 4( %2 )"                           \
    :                                            \
    : "r"( r0 ), "r"( r1 ), "r"( r2 ) )

#define gte_ldrgb(r0) __asm__ volatile (         \
    "lwc2 $6, 0( %0 )"                           \
    :                                            \
    : "r"( r0 ) )

#define gte_rtps()  __asm__ volatile ("nop;nop;rtps")
#define gte_rtpt()  __asm__ volatile ("nop;nop;rtpt")
#define gte_nclip() __asm__ volatile ("nop;nop;nclip")
#define gte_avsz4() __asm__ volatile ("nop;nop;avsz4")
#define gte_nccs()  __asm__ volatile ("nop;nop;nccs")

#define gte_stflg(r0) __asm__ volatile (         \
    "cfc2 $12, $31;"                             \
    "nop;"                                       \
    "sw $12, 0( %0 )"                            \
    :                                            \
    : "r"( r0 )                                  \
    : "$12", "memory" )

#define gte_stopz(r0) __asm__ volatile (         \
    "swc2 $24, 0( %0 )"                          \
    :                                            \
    : "r"( r0 )                                  \
    : "memory" )

#define gte_stotz(r0) __asm__ volatile (         \
    "swc2 $7, 0( %0 )"                           \
    :                                            \
    : "r"( r0 )                                  \
    : "memory" )

#define gte_stsxy(r0) __asm__ volatile (         \
    "swc2 $14, 0( %0 )"                          \
    :                                            \
    : "r"( r0 )                                  \
    : "memory" )

#define gte_strgb(r0) __asm__ volatile (         \
    "swc2 $22, 0( %0 )"                          \
    :                                            \
    : "r"( r0 )                                  \
    : "memory" )

#define gte_stsxy3_g4(r0) __asm__ volatile (     \
    "swc2 $12, 8( %0 );"                         \
    "swc2 $13, 16( %0 );"                        \
    "swc2 $14, 24( %0 )"                         \
    :                                            \
    : "r"( r0 )                                  \
    : "memory" )

extern s32 D_800A2B78;

u8 *func_80025A30(u8 *prim, u8 *vtx, u8 *nrm, u8 *pkt, s32 n, s32 shift, u32 *ot)
{
    long flag;
    long z;
    u32 *o;

    if (n != 0) {
    __asm__ volatile ("" : "=r"(pkt) : "0"(pkt));
    for (; n != 0; n--, prim += 0x24) {
        gte_ldv3(vtx + (*(u16 *)(prim + 0x16) << 3),
                 vtx + (*(u16 *)(prim + 0x1A) << 3),
                 vtx + (*(u16 *)(prim + 0x1E) << 3));
        gte_rtpt();
        gte_stflg(&flag);
        if (flag & 0xFFFFEFFF) {
            continue;
        }
        gte_nclip();
        gte_stopz(&z);
        if (z <= 0) {
            continue;
        }
        gte_stsxy3_g4(pkt);
        gte_ldv0(vtx + (*(u16 *)(prim + 0x22) << 3));
        gte_rtps();
        gte_stflg(&flag);
        if (flag & 0xFFFFEFFF) {
            continue;
        }
        gte_stsxy(pkt + 0x20);
        gte_avsz4();
        gte_stotz(&z);

        gte_ldv0(nrm + (*(u16 *)(prim + 0x14) << 3));
        gte_ldrgb(prim + 0x4);
        gte_nccs();
        gte_strgb(pkt + 0x4);
        gte_ldrgb(prim + 0x8);
        gte_nccs();
        gte_strgb(pkt + 0xC);
        gte_ldrgb(prim + 0xC);
        gte_nccs();
        gte_strgb(pkt + 0x14);
        gte_ldrgb(prim + 0x10);
        gte_nccs();
        gte_strgb(pkt + 0x1C);

        pkt[7] = (pkt[7] & 2) | 0x38;

        o = &ot[z >> shift];
        *(u32 *)pkt = (*o & 0xFFFFFF) | 0x08000000;
        *o = (u32)pkt & 0xFFFFFF;
        pkt += 0x24;

        if (D_800A2B78 == 0) {
            continue;
        }
        if ((pkt[-0x1D] & 2) == 0) {
            continue;
        }
        o = &ot[z >> shift];
        pkt[3] = 1;
        *(u32 *)(pkt + 4) = ((D_800A2B78 & 3) << 5) | 0xE100000A;
        *(u32 *)pkt = (*o & 0xFFFFFF) | 0x01000000;
        *o = (u32)pkt & 0xFFFFFF;
        pkt += 8;
    }
    }
    return pkt;
}


/* Handwritten GTE polygon-transform loop (cookbook: handwritten inline-asm wrapper form).
 * The whole body is written in asm because the original is hand-written assembly: the
 * loop-carried values live in $t1/$t2/$t3/$t5/$t6/$t7/$t8/$t9 (gcc-2.7.2 would never
 * allocate caller-saved temporaries that way), and the two `lw 0x10($sp)` copies plus the
 * duplicated `sra $v0,$v1,2` on both arms of the min() are hand-scheduled.
 *
 * maspsx notes: `.set noreorder` must be the FIRST line so maspsx stops auto-filling
 * branch-delay slots / load-delay nops (we write every nop ourselves, exactly as in the
 * target), and `.set reorder` must be the LAST so the compiler-emitted `j $31` still gets
 * its delay-slot nop. All memory offsets are DECIMAL: maspsx int()s them.
 */

extern u32 D_8006387C;
extern s32 D_80078D88[];

void *func_80025CBC(void *prims, void *scr, void *cols, void *packets,
                    s32 count, s32 otshift, u32 *ot)
{
    __asm__ __volatile__(
        ".set\tnoreorder\n"
        "addiu $sp, $sp, -32\n"
        "lw $11, 48($sp)\n"
        "sw $17, 28($sp)\n"
        "lui $17, %hi(D_8006387C)\n"
        "addiu $17, $17, %lo(D_8006387C)\n"
        "sw $16, 24($sp)\n"
        "lw $16, 52($sp)\n"
        "lw $25, 56($sp)\n"
        "lwc2 $6, 0($17)\n"
        "beq $11, $0, .LfnEnd\n"
        "addu $2, $7, $0\n"
        "addiu $14, $sp, 4\n"
        "addiu $24, $sp, 8\n"
        "addiu $15, $sp, 12\n"
        "lui $13, 255\n"
        "ori $13, $13, 65535\n"
        "addiu $9, $4, 16\n"
        "addiu $10, $7, 4\n"
        ".LfnLoop:\n"
        "lhu $4, 2($9)\n"
        "lhu $3, 4($9)\n"
        "lhu $2, 6($9)\n"
        "sll $4, $4, 3\n"
        "addu $4, $5, $4\n"
        "sll $3, $3, 3\n"
        "addu $3, $5, $3\n"
        "sll $2, $2, 3\n"
        "addu $2, $5, $2\n"
        "lwc2 $0, 0($4)\n"
        "lwc2 $1, 4($4)\n"
        "lwc2 $2, 0($3)\n"
        "lwc2 $3, 4($3)\n"
        "lwc2 $4, 0($2)\n"
        "lwc2 $5, 4($2)\n"
        "nop\n"
        "nop\n"
        "rtpt\n"
        "lw $2, -12($9)\n"
        "nop\n"
        "sw $2, 8($10)\n"
        "lw $2, -8($9)\n"
        "nop\n"
        "sw $2, 16($10)\n"
        "lw $2, -4($9)\n"
        "nop\n"
        "sw $2, 24($10)\n"
        "cfc2 $12, $31\n"
        "nop\n"
        "sw $12, 0($sp)\n"
        "lw $2, 0($sp)\n"
        "addiu $3, $0, -4097\n"
        "and $2, $2, $3\n"
        "bne $2, $0, .LfnNext\n"
        "nop\n"
        "nop\n"
        "nop\n"
        "nclip\n"
        "swc2 $24, 0($14)\n"
        "lw $2, 4($sp)\n"
        "nop\n"
        "blez $2, .LfnNext\n"
        "nop\n"
        "swc2 $12, 8($7)\n"
        "swc2 $13, 16($7)\n"
        "swc2 $14, 24($7)\n"
        "lui $2, %hi(D_80078D88)\n"
        "lw $2, %lo(D_80078D88)($2)\n"
        "nop\n"
        "andi $2, $2, 32768\n"
        "beq $2, $0, .LfnAvsz\n"
        "addiu $2, $sp, 16\n"
        "swc2 $17, 0($24)\n"
        "swc2 $18, 0($15)\n"
        "swc2 $19, 0($2)\n"
        "lw $8, 8($sp)\n"
        "lw $3, 12($sp)\n"
        "nop\n"
        "slt $2, $3, $8\n"
        "beq $2, $0, .LfnMinB\n"
        "nop\n"
        "lw $4, 16($sp)\n"
        "j .LfnMinJ\n"
        "addu $3, $8, $0\n"
        ".LfnMinB:\n"
        "lw $4, 16($sp)\n"
        ".LfnMinJ:\n"
        "nop\n"
        "slt $2, $3, $4\n"
        "beq $2, $0, .LfnMinC\n"
        "sra $2, $3, 2\n"
        "addu $3, $4, $0\n"
        "sra $2, $3, 2\n"
        ".LfnMinC:\n"
        "j .LfnJoin\n"
        "sw $2, 4($sp)\n"
        ".LfnAvsz:\n"
        "nop\n"
        "nop\n"
        "avsz3\n"
        "swc2 $7, 0($14)\n"
        ".LfnJoin:\n"
        "lhu $2, 0($9)\n"
        "nop\n"
        "sll $2, $2, 3\n"
        "addu $2, $6, $2\n"
        "lwc2 $0, 0($2)\n"
        "lwc2 $1, 4($2)\n"
        "nop\n"
        "nop\n"
        "nccs\n"
        "swc2 $22, 0($10)\n"
        "lw $4, 4($sp)\n"
        "addiu $10, $10, 32\n"
        "srav $4, $4, $16\n"
        "sll $4, $4, 2\n"
        "addu $4, $25, $4\n"
        "lw $3, 0($4)\n"
        "lui $2, 1792\n"
        "and $3, $3, $13\n"
        "or $3, $3, $2\n"
        "and $2, $7, $13\n"
        "sw $3, 0($7)\n"
        "addiu $7, $7, 32\n"
        "sw $2, 0($4)\n"
        ".LfnNext:\n"
        "addiu $11, $11, -1\n"
        "bne $11, $0, .LfnLoop\n"
        "addiu $9, $9, 24\n"
        "addu $2, $7, $0\n"
        ".LfnEnd:\n"
        "lw $17, 28($sp)\n"
        "lw $16, 24($sp)\n"
        "addiu $sp, $sp, 32\n"
        ".set\treorder\n"
    );
}


/* func_80025EB8 — POLY_FT4 (0x28) mesh emitter, main / src/800.c   [MATCH 156/156]
 *
 * Per prim (0x20 bytes): RTPT the first 3 verts -> GTE flag cull -> NCLIP cull ->
 * RTPS the 4th vert -> flag cull -> depth (max(sz0..sz3)>>2 when D_80078D88 & 0x8000,
 * else AVSZ4) -> NCCS colour from the prim's normal -> OT insert (tag code 0x09).
 * Returns the advanced packet pointer.
 *
 * GTE ops are verbatim PsyQ inline_c.h macro bodies, spelled with the project gas
 * macros from include/gte_macros.inc (pulled in by common.h) — same idiom as the
 * already-matched func_8017BEBC family in the overlays.
 *
 * TWO NON-OBVIOUS LEVERS (both cost zero bytes, both were the whole residual):
 *
 * 1. `D_80078D88` is declared as an ARRAY, not a scalar.  gcc-2.7.2 alias.c refuses
 *    to reorder two memory refs only if they can conflict; its rule exempts a
 *    MEM_IN_STRUCT_P ref with a varying address from a NON-struct ref with a constant
 *    address.  With `extern s32 D_80078D88;` the global load is a plain scalar at a
 *    symbol_ref, so sched1 hoisted `lui/lw D_80078D88` above the `pkt->uv3` store and
 *    swallowed both load-delay nops (-2 insns).  An ARRAY_REF sets MEM_IN_STRUCT_P on
 *    the load, the exemption no longer applies, the pair is ordered, and the two nops
 *    come back exactly as in the target.
 *
 * 2. The packet cursor is a LOCAL (`pkt`) seeded from the parameter (`pkt0`), not the
 *    parameter itself.  loop.c's record_initial() takes the biv's initial_value from
 *    its last pre-loop set: with the parameter used directly that set is
 *    `(set P (reg:SI 7 a3))`, so the +4 giv's preheader init is emitted against the
 *    HARD register — which keeps $a3 live into the preheader and makes it CONFLICT
 *    with P (`;; 75 conflicts: ... 7` in .greg).  P then can never be granted $a3, so
 *    it took $t2, the giv took $a3, and the dead param copy `move t2,a3` survived
 *    (+1 insn, and every packet reference register-swapped).  Seeding a local makes
 *    initial_value a pseudo, $a3 dies at the param copy, the conflict disappears and
 *    the copy preference puts the cursor back in $a3.
 */

#define gte_ldrgb(r0) __asm__ volatile (          \
    "lwc2 $6, 0( %0 )"                            \
    :                                             \
    : "r"( r0 ) )

#define gte_ldv0(r0) __asm__ volatile (           \
    "lwc2 $0, 0( %0 );"                           \
    "lwc2 $1, 4( %0 )"                            \
    :                                             \
    : "r"( r0 ) )

#define gte_ldv3(r0, r1, r2) __asm__ volatile (   \
    "lwc2 $0, 0( %0 );"                           \
    "lwc2 $1, 4( %0 );"                           \
    "lwc2 $2, 0( %1 );"                           \
    "lwc2 $3, 4( %1 );"                           \
    "lwc2 $4, 0( %2 );"                           \
    "lwc2 $5, 4( %2 )"                            \
    :                                             \
    : "r"( r0 ), "r"( r1 ), "r"( r2 ) )

#define gte_rtps()  __asm__ volatile ("nop;nop;rtps")
#define gte_rtpt()  __asm__ volatile ("nop;nop;rtpt")
#define gte_nclip() __asm__ volatile ("nop;nop;nclip")
#define gte_avsz4() __asm__ volatile ("nop;nop;avsz4")
#define gte_nccs()  __asm__ volatile ("nop;nop;nccs")

#define gte_stflg(r0) __asm__ volatile (          \
    "cfc2 $12, $31;"                              \
    "nop;"                                        \
    "sw $12, 0( %0 )"                             \
    :                                             \
    : "r"( r0 )                                   \
    : "$12", "memory" )

#define gte_stopz(r0) __asm__ volatile (          \
    "swc2 $24, 0( %0 )"                           \
    :                                             \
    : "r"( r0 )                                   \
    : "memory" )

#define gte_stotz(r0) __asm__ volatile (          \
    "swc2 $7, 0( %0 )"                            \
    :                                             \
    : "r"( r0 )                                   \
    : "memory" )

#define gte_stsxy(r0) __asm__ volatile (          \
    "swc2 $14, 0( %0 )"                           \
    :                                             \
    : "r"( r0 )                                   \
    : "memory" )

#define gte_stsxy3_ft4(r0) __asm__ volatile (     \
    "swc2 $12, 8( %0 );"                          \
    "swc2 $13, 16( %0 );"                         \
    "swc2 $14, 24( %0 )"                          \
    :                                             \
    : "r"( r0 )                                   \
    : "memory" )

#define gte_stsz4(r0, r1, r2, r3) __asm__ volatile ( \
    "swc2 $16, 0( %0 );"                          \
    "swc2 $17, 0( %1 );"                          \
    "swc2 $18, 0( %2 );"                          \
    "swc2 $19, 0( %3 )"                           \
    :                                             \
    : "r"( r0 ), "r"( r1 ), "r"( r2 ), "r"( r3 ) )

#define gte_strgb2(r0) __asm__ volatile (         \
    "swc2 $22, 0( %0 )"                           \
    :                                             \
    : "r"( r0 )                                   \
    : "memory" )

typedef struct { s16 vx, vy, vz, pad; } SVEC8_80025EB8;

typedef struct {
    u32 pad0;  /* 0x00 */
    u32 uv0;   /* 0x04 */
    u32 uv1;   /* 0x08 */
    u32 uv2;   /* 0x0C */
    u32 uv3;   /* 0x10 */
    u16 n0;    /* 0x14 */
    u16 v0;    /* 0x16 */
    u16 v1;    /* 0x18 */
    u16 v2;    /* 0x1A */
    u16 v3;    /* 0x1C */
    u16 pad1;  /* 0x1E */
} Prim20;

typedef struct {           /* libgpu POLY_FT4, 0x28 bytes */
    u32 tag;   /* 0x00 */
    u32 rgb;   /* 0x04 */
    u32 xy0;   /* 0x08 */
    u32 uv0;   /* 0x0C */
    u32 xy1;   /* 0x10 */
    u32 uv1;   /* 0x14 */
    u32 xy2;   /* 0x18 */
    u32 uv2;   /* 0x1C */
    u32 xy3;   /* 0x20 */
    u32 uv3;   /* 0x24 */
} Ft4;

extern u32 D_80063880;
extern s32 D_80078D88[];

u32 *func_80025EB8(Prim20 *prim, SVEC8_80025EB8 *verts, SVEC8_80025EB8 *norms, Ft4 *pkt0,
                   s32 n, s32 shift, u32 *ot)
{
    struct { long flag, otz, sz0, sz1, sz2, sz3; } g;
    s32 a, b;
    u32 *otp;
    Ft4 *pkt;

    pkt = pkt0;
    gte_ldrgb(&D_80063880);

    while (n != 0) {
        gte_ldv3(&verts[prim->v0], &verts[prim->v1], &verts[prim->v2]);
        gte_rtpt();
        pkt->uv0 = prim->uv0;
        pkt->uv1 = prim->uv1;
        pkt->uv2 = prim->uv2;
        gte_stflg(&g.flag);
        if (!(g.flag & 0xFFFFEFFF)) {
            gte_nclip();
            gte_stopz(&g.otz);
            if (g.otz > 0) {
                gte_stsxy3_ft4(pkt);
                gte_ldv0(&verts[prim->v3]);
                gte_rtps();
                gte_stflg(&g.flag);
                if (!(g.flag & 0xFFFFEFFF)) {
                    gte_stsxy(&pkt->xy3);
                    pkt->uv3 = prim->uv3;
                    if (D_80078D88[0] & 0x8000) {
                        gte_stsz4(&g.sz0, &g.sz1, &g.sz2, &g.sz3);
                        a = g.sz2;
                        if (a < g.sz3) a = g.sz3;
                        b = g.sz0;
                        if (b < g.sz1) b = g.sz1;
                        if (b < a) b = a;
                        g.otz = b >> 2;
                    } else {
                        gte_avsz4();
                        gte_stotz(&g.otz);
                    }
                    gte_ldv0(&norms[prim->n0]);
                    gte_nccs();
                    gte_strgb2(&pkt->rgb);
                    otp = &ot[g.otz >> shift];
                    pkt->tag = (*otp & 0xFFFFFF) | 0x09000000;
                    *otp = (u32)pkt & 0xFFFFFF;
                    pkt++;
                }
            }
        }
        n--;
        prim++;
    }

    return (u32 *)pkt;
}

INCLUDE_ASM("asm/nonmatchings/800", func_80026128);


/* func_800262D8 — main/800 — GT4 quad emitter with per-vertex normal-colour lighting.
 * GTE ops spelled as verbatim PsyQ inline_c.h macro bodies (project gas macros from
 * include/gte_macros.inc, pulled in via common.h -> include_asm.h -> macro.inc). */

#define gte_ldrgb(r0) __asm__ volatile (          \
    "lwc2 $6, 0( %0 )"                            \
    :                                             \
    : "r"( r0 ) )

#define gte_ldv0(r0) __asm__ volatile (           \
    "lwc2 $0, 0( %0 );"                           \
    "lwc2 $1, 4( %0 )"                            \
    :                                             \
    : "r"( r0 ) )

#define gte_ldv3(r0, r1, r2) __asm__ volatile (   \
    "lwc2 $0, 0( %0 );"                           \
    "lwc2 $1, 4( %0 );"                           \
    "lwc2 $2, 0( %1 );"                           \
    "lwc2 $3, 4( %1 );"                           \
    "lwc2 $4, 0( %2 );"                           \
    "lwc2 $5, 4( %2 )"                            \
    :                                             \
    : "r"( r0 ), "r"( r1 ), "r"( r2 ) )

#define gte_rtps()  __asm__ volatile ("nop;nop;rtps")
#define gte_rtpt()  __asm__ volatile ("nop;nop;rtpt")
#define gte_nclip() __asm__ volatile ("nop;nop;nclip")
#define gte_avsz4() __asm__ volatile ("nop;nop;avsz4")
#define gte_ncct()  __asm__ volatile ("nop;nop;ncct")
#define gte_nccs()  __asm__ volatile ("nop;nop;nccs")

#define gte_stflg(r0) __asm__ volatile (          \
    "cfc2 $12, $31;"                              \
    "nop;"                                        \
    "sw $12, 0( %0 )"                             \
    :                                             \
    : "r"( r0 )                                   \
    : "$12", "memory" )

#define gte_stopz(r0) __asm__ volatile (          \
    "swc2 $24, 0( %0 )"                           \
    :                                             \
    : "r"( r0 )                                   \
    : "memory" )

#define gte_stotz(r0) __asm__ volatile (          \
    "swc2 $7, 0( %0 )"                            \
    :                                             \
    : "r"( r0 )                                   \
    : "memory" )

#define gte_stsxy(r0) __asm__ volatile (          \
    "swc2 $14, 0( %0 )"                           \
    :                                             \
    : "r"( r0 )                                   \
    : "memory" )

#define gte_stsxy3_gt4(r0) __asm__ volatile (     \
    "swc2 $12, 8( %0 );"                          \
    "swc2 $13, 20( %0 );"                         \
    "swc2 $14, 32( %0 )"                          \
    :                                             \
    : "r"( r0 )                                   \
    : "memory" )

#define gte_strgb(r0) __asm__ volatile (          \
    "swc2 $22, 0( %0 )"                           \
    :                                             \
    : "r"( r0 )                                   \
    : "memory" )

#define gte_strgb3(r0, r1, r2) __asm__ volatile ( \
    "swc2 $20, 0( %0 );"                          \
    "swc2 $21, 0( %1 );"                          \
    "swc2 $22, 0( %2 )"                           \
    :                                             \
    : "r"( r0 ), "r"( r1 ), "r"( r2 )             \
    : "memory" )

typedef struct { s16 vx, vy, vz, pad; } SVEC8_800262D8;          /* 0x08 */

typedef struct {                                        /* 0x24 */
    u32 unk00;
    u32 uv0;
    u32 uv1;
    u32 uv2;
    u32 uv3;
    u16 n0, v0;
    u16 n1, v1;
    u16 n2, v2;
    u16 n3, v3;
} FaceGT4;

typedef struct {                                        /* 0x34 */
    u32 tag;
    u32 rgb0, xy0, uv0;
    u32 rgb1, xy1, uv1;
    u32 rgb2, xy2, uv2;
    u32 rgb3, xy3, uv3;
} PktGT4;

extern u32 D_80063888;

/* NOTE (§RC-10 preference cascade): `pkt` MUST be a body-local copy of the 4th
 * parameter. If the loop's biv IS the parameter pseudo, loop.c's record_initial
 * takes the biv's initial value straight from the incoming HARD reg, so the
 * preheader giv is emitted as `(set giv (plus (reg $a3) 0x28))` — that keeps $a3
 * live to the preheader (biv pseudo CONFLICTS with $7) and hands the giv the $7
 * set_preference. Result: giv->$a3, pkt->$t1 + a spurious `move t1,a3` (144 ins).
 * With the local copy the initial value is a PSEUDO: $a3 dies at the param copy,
 * pkt takes $a3 by preference, the giv falls to $t1, and the move disappears. */
PktGT4 *func_800262D8(FaceGT4 *face, SVEC8_800262D8 *vtx, SVEC8_800262D8 *nrm, PktGT4 *arg3,
                      s32 count, s32 shift, u32 *ot)
{
    long flag;
    long otz;
    u32 *otp;
    PktGT4 *pkt = arg3;

    gte_ldrgb(&D_80063888);

    while (count != 0) {
        gte_ldv3(&vtx[face->v0], &vtx[face->v1], &vtx[face->v2]);
        gte_rtpt();
        pkt->uv0 = face->uv0;
        pkt->uv1 = face->uv1;
        pkt->uv2 = face->uv2;
        gte_stflg(&flag);
        if (!(flag & ~0x1000)) {
            gte_nclip();
            gte_stopz(&otz);
            if (otz > 0) {
                gte_stsxy3_gt4(pkt);
                gte_ldv0(&vtx[face->v3]);
                gte_rtps();
                pkt->uv3 = face->uv3;
                gte_stflg(&flag);
                if (!(flag & ~0x1000)) {
                    gte_stsxy(&pkt->xy3);
                    gte_avsz4();
                    gte_stotz(&otz);
                    gte_ldv3(&nrm[face->n0], &nrm[face->n1], &nrm[face->n2]);
                    gte_ncct();
                    otp = &ot[otz >> shift];
                    pkt->tag = (*otp & 0x00FFFFFF) | 0x0C000000;
                    gte_strgb3(&pkt->rgb0, &pkt->rgb1, &pkt->rgb2);
                    gte_ldv0(&nrm[face->n3]);
                    gte_nccs();
                    gte_strgb(&pkt->rgb3);
                    *otp = (u32)pkt & 0x00FFFFFF;
                    pkt++;
                }
            }
        }
        face++;
        count--;
    }
    return pkt;
}

INCLUDE_ASM("asm/nonmatchings/800", func_80026514);

INCLUDE_ASM("asm/nonmatchings/800", func_800268D0);

INCLUDE_ASM("asm/nonmatchings/800", func_80026D64);

INCLUDE_ASM("asm/nonmatchings/800", func_80027058);


/* func_80027200 — HANDWRITTEN assembly (splat marks it "Handwritten function").
 * The register discipline (loop counter in $t3, live args in $a0/$a1/$a3, no
 * callee-saved registers at all, raw GTE cop2 ops with hand-placed latency nops)
 * is not reachable from gcc-2.7.2 codegen, so the body is reproduced verbatim as
 * a single .set noreorder asm block.  gcc supplies only the `jr $ra` + delay nop.
 */

extern s32 D_800A2B78;

void func_80027200(void)
{
    __asm__ __volatile__(
        ".set\tnoreorder\n"
        
        "addiu $sp, $sp, -0x8\n"
        "lw    $t3, 24($sp)\n"
        "lw    $t8, 28($sp)\n"
        "lw    $t7, 32($sp)\n"
        "beq   $t3, $zero, 3f\n"
        "addu  $v0, $a3, $zero\n"
        "addiu $t6, $zero, -0x1001\n"
        "addiu $t5, $sp, 0x4\n"
        "lui   $t2, 0xFF\n"
        "ori   $t2, $t2, 0xFFFF\n"
        "addiu $t1, $a0, 0x4\n"
        "addiu $t0, $a3, 0x4\n"
        "1:\n"
        "lhu   $a0, 6($t1)\n"
        "lhu   $v1, 8($t1)\n"
        "lhu   $v0, 10($t1)\n"
        "sll   $a0, $a0, 3\n"
        "addu  $a0, $a1, $a0\n"
        "sll   $v1, $v1, 3\n"
        "addu  $v1, $a1, $v1\n"
        "sll   $v0, $v0, 3\n"
        "addu  $v0, $a1, $v0\n"
        "lwc2  $0, 0($a0)\n"
        "lwc2  $1, 4($a0)\n"
        "lwc2  $2, 0($v1)\n"
        "lwc2  $3, 4($v1)\n"
        "lwc2  $4, 0($v0)\n"
        "lwc2  $5, 4($v0)\n"
        "nop\n"
        "nop\n"
        "rtpt\n"
        "cfc2  $t4, $31\n"
        "nop\n"
        "sw    $t4, 0($sp)\n"
        "lw    $v0, 0($sp)\n"
        "nop\n"
        "and   $v0, $v0, $t6\n"
        "bne   $v0, $zero, 2f\n"
        "nop\n"
        "nop\n"
        "nop\n"
        "nclip\n"
        "swc2  $24, 0($t5)\n"
        "lw    $v0, 4($sp)\n"
        "nop\n"
        "blez  $v0, 2f\n"
        "nop\n"
        "swc2  $12, 8($a3)\n"
        "swc2  $13, 12($a3)\n"
        "swc2  $14, 16($a3)\n"
        "lhu   $v0, 12($t1)\n"
        "nop\n"
        "sll   $v0, $v0, 3\n"
        "addu  $v0, $a1, $v0\n"
        "lwc2  $0, 0($v0)\n"
        "lwc2  $1, 4($v0)\n"
        "nop\n"
        "nop\n"
        "rtps\n"
        "cfc2  $t4, $31\n"
        "nop\n"
        "sw    $t4, 0($sp)\n"
        "lw    $v0, 0($sp)\n"
        "nop\n"
        "and   $v0, $v0, $t6\n"
        "bne   $v0, $zero, 2f\n"
        "addiu $v0, $a3, 0x14\n"
        "swc2  $14, 0($v0)\n"
        "nop\n"
        "nop\n"
        "avsz4\n"
        "swc2  $7, 0($t5)\n"
        "lw    $v0, 0($t1)\n"
        "nop\n"
        "sw    $v0, 0($t0)\n"
        "lw    $v0, 4($sp)\n"
        "addiu $t0, $t0, 0x18\n"
        "srav  $v0, $v0, $t8\n"
        "sll   $v0, $v0, 2\n"
        "addu  $a2, $t7, $v0\n"
        "lw    $v1, 0($a2)\n"
        "lui   $v0, 0x500\n"
        "and   $v1, $v1, $t2\n"
        "or    $v1, $v1, $v0\n"
        "and   $v0, $a3, $t2\n"
        "sw    $v1, 0($a3)\n"
        "sw    $v0, 0($a2)\n"
        "lui   $v0, %hi(D_800A2B78)\n"
        "lw    $v0, %lo(D_800A2B78)($v0)\n"
        "nop\n"
        "beq   $v0, $zero, 2f\n"
        "addiu $a3, $a3, 0x18\n"
        "lbu   $v0, -21($t0)\n"
        "nop\n"
        "andi  $v0, $v0, 0x2\n"
        "beq   $v0, $zero, 2f\n"
        "lui   $a0, 0xE100\n"
        "ori   $a0, $a0, 0xA\n"
        "lw    $v1, 4($sp)\n"
        "addiu $v0, $zero, 0x1\n"
        "sb    $v0, -1($t0)\n"
        "lui   $v0, %hi(D_800A2B78)\n"
        "lw    $v0, %lo(D_800A2B78)($v0)\n"
        "srav  $v1, $v1, $t8\n"
        "sll   $v1, $v1, 2\n"
        "addu  $a2, $t7, $v1\n"
        "andi  $v0, $v0, 0x3\n"
        "sll   $v0, $v0, 5\n"
        "or    $v0, $v0, $a0\n"
        "sw    $v0, 0($t0)\n"
        "addiu $t0, $t0, 0x8\n"
        "lw    $v1, 0($a2)\n"
        "lui   $v0, 0x100\n"
        "and   $v1, $v1, $t2\n"
        "or    $v1, $v1, $v0\n"
        "and   $v0, $a3, $t2\n"
        "sw    $v1, 0($a3)\n"
        "addiu $a3, $a3, 0x8\n"
        "sw    $v0, 0($a2)\n"
        "2:\n"
        "addiu $t3, $t3, -0x1\n"
        "bne   $t3, $zero, 1b\n"
        "addiu $t1, $t1, 0x14\n"
        "addu  $v0, $a3, $zero\n"
        "3:\n"
        "addiu $sp, $sp, 0x8\n"
        
        ".set\treorder\n"
    );
}

INCLUDE_ASM("asm/nonmatchings/800", func_800273F4);


/* ---- PsyQ inline GTE macros (inline_c.h forms) ------------------------- */
#define gte_ldv0(r0) __asm__ volatile (          \
    "lwc2 $0, 0( %0 );"                          \
    "lwc2 $1, 4( %0 )"                           \
    :: "r"(r0))

#define gte_ldv3(r0, r1, r2) __asm__ volatile (  \
    "lwc2 $0, 0( %0 );"                          \
    "lwc2 $1, 4( %0 );"                          \
    "lwc2 $2, 0( %1 );"                          \
    "lwc2 $3, 4( %1 );"                          \
    "lwc2 $4, 0( %2 );"                          \
    "lwc2 $5, 4( %2 )"                           \
    :: "r"(r0), "r"(r1), "r"(r2))

#define gte_rtps()  __asm__ volatile ("nop;nop;.word 0x4a180001")
#define gte_rtpt()  __asm__ volatile ("nop;nop;.word 0x4a280030")
#define gte_nclip() __asm__ volatile ("nop;nop;.word 0x4b400006")
#define gte_avsz4() __asm__ volatile ("nop;nop;.word 0x4b68002e")

#define gte_stflg(r0) __asm__ volatile (         \
    "cfc2 $12, $31;"                             \
    "nop;"                                       \
    "sw $12, 0( %0 )"                            \
    :: "r"(r0) : "$12", "memory")

#define gte_stsxy2(r0) __asm__ volatile (        \
    "swc2 $14, 0( %0 )"                          \
    :: "r"(r0) : "memory")

#define gte_stsxy3_g4(r0) __asm__ volatile (     \
    "swc2 $12, 8( %0 );"                         \
    "swc2 $13, 16( %0 );"                        \
    "swc2 $14, 24( %0 )"                         \
    :: "r"(r0) : "memory")

#define gte_stotz(r0) __asm__ volatile (         \
    "swc2 $7, 0( %0 )"                           \
    :: "r"(r0) : "memory")

#define gte_stopz(r0) __asm__ volatile (         \
    "swc2 $24, 0( %0 )"                          \
    :: "r"(r0) : "memory")

/* ---- data ------------------------------------------------------------- */
extern s32 D_800A2B78;

typedef struct {
    s16 vx, vy, vz, pad;
} SVEC_800275BC;                        /* 8 bytes */

typedef struct {               /* TMD G4 flat-normal primitive, 0x20 bytes */
    u32 tag;                   /* 0x00 */
    u32 c0;                    /* 0x04 */
    u32 c1;                    /* 0x08 */
    u32 c2;                    /* 0x0C */
    u32 c3;                    /* 0x10 */
    u16 n0;                    /* 0x14 */
    u16 v0;                    /* 0x16 */
    u16 v1;                    /* 0x18 */
    u16 v2;                    /* 0x1A */
    u16 v3;                    /* 0x1C */
    u16 pad;                   /* 0x1E */
} TPRIM_800275BC;

void *func_800275BC(TPRIM_800275BC *prim, SVEC_800275BC *vp, void *nrm, u8 *pk, s32 n,
                    s32 shift, u32 *ot)
{
    s32 flag;
    s32 otz;
    u32 *op;

    if (n == 0) {
        return pk;
    }

    do {
        gte_ldv3(&vp[prim->v0], &vp[prim->v1], &vp[prim->v2]);
        gte_rtpt();
        gte_stflg(&flag);
        if ((flag & 0xFFFFEFFF) == 0) {
            gte_nclip();
            gte_stopz(&otz);
            if (otz > 0) {
                gte_stsxy3_g4(pk);
                gte_ldv0(&vp[prim->v3]);
                gte_rtps();
                gte_stflg(&flag);
                if ((flag & 0xFFFFEFFF) == 0) {
                    gte_stsxy2(pk + 0x20);
                    gte_avsz4();
                    gte_stotz(&otz);
                    *(u32 *)(pk + 0x04) = prim->c0;
                    *(u32 *)(pk + 0x0C) = prim->c1;
                    *(u32 *)(pk + 0x14) = prim->c2;
                    *(u32 *)(pk + 0x1C) = prim->c3;
                    *(u8 *)(pk + 7) = (*(u8 *)(pk + 7) & 2) | 0x38;
                    op = &ot[otz >> shift];
                    *(u32 *)pk = (*op & 0xFFFFFF) | 0x08000000;
                    *op = (u32)pk & 0xFFFFFF;
                    pk += 0x24;
                    if (D_800A2B78 != 0) {
                        if (*(u8 *)(pk - 0x1D) & 2) {
                            op = &ot[otz >> shift];
                            *(u8 *)(pk + 3) = 1;
                            *(u32 *)(pk + 4) =
                                ((D_800A2B78 & 3) << 5) | 0xE100000A;
                            *(u32 *)pk = (*op & 0xFFFFFF) | 0x01000000;
                            *op = (u32)pk & 0xFFFFFF;
                            pk += 8;
                        }
                    }
                }
            }
        }
        prim++;
    } while (--n != 0);
    return pk;
}


/* GTE inline-asm idioms, verbatim PsyQ inline_c.h macro bodies (see cookbook §-GTE and e.g.
 * src/ov_SC01_000/ov_SC01_000_jr_8017BEBC.c for the established shape of this idiom family).
 * NOTE gte_stsxy3_gt3: the target stores SXY0/1/2 at 8/16/24 off ONE base register ($a3, the
 * POLY_GT3 being built), not off three separate pointers -- that is the PsyQ `_gt3` variant.
 * Using the 3-pointer gte_stsxy3 costs three extra `addiu` and was the first agent's length drift. */

#define gte_ldv3(r0, r1, r2) __asm__ volatile (  \
    "lwc2 $0, 0( %0 );"                          \
    "lwc2 $1, 4( %0 );"                          \
    "lwc2 $2, 0( %1 );"                          \
    "lwc2 $3, 4( %1 );"                          \
    "lwc2 $4, 0( %2 );"                          \
    "lwc2 $5, 4( %2 )"                           \
    :                                            \
    : "r"( r0 ), "r"( r1 ), "r"( r2 ) )

#define gte_rtpt() __asm__ volatile ("nop;nop;rtpt")
#define gte_nclip() __asm__ volatile ("nop;nop;nclip")

#define gte_stflg(r0) __asm__ volatile (         \
    "cfc2 $12, $31;"                             \
    "nop;"                                       \
    "sw $12, 0( %0 )"                            \
    :                                            \
    : "r"( r0 )                                  \
    : "$12", "memory" )

#define gte_stopz(r0) __asm__ volatile (         \
    "swc2 $24, 0( %0 )"                          \
    :                                            \
    : "r"( r0 )                                  \
    : "memory" )

#define gte_stsxy3_gt3(r0) __asm__ volatile (    \
    "swc2 $12, 8( %0 );"                         \
    "swc2 $13, 16( %0 );"                        \
    "swc2 $14, 24( %0 )"                         \
    :                                            \
    : "r"( r0 )                                  \
    : "memory" )

#define gte_stsz3(r0, r1, r2) __asm__ volatile ( \
    "swc2 $17, 0( %0 );"                         \
    "swc2 $18, 0( %1 );"                         \
    "swc2 $19, 0( %2 )"                          \
    :                                            \
    : "r"( r0 ), "r"( r1 ), "r"( r2 )            \
    : "memory" )

#define gte_avsz3() __asm__ volatile ("nop;nop;avsz3")

#define gte_stotz(r0) __asm__ volatile (         \
    "swc2 $7, 0( %0 )"                           \
    :                                            \
    : "r"( r0 )                                  \
    : "memory" )

extern s32 D_80078D88[];

typedef struct { s16 vx, vy, vz, pad; } SVECTOR800277DC;

void *func_800277DC(void *a0, SVECTOR800277DC *a1, void *a2, u8 *a3,
                     s32 count, s32 shift, s32 *ot)
{
    /* The five GTE scratch slots MUST be ONE array, not five scalars.  gcc-2.7.2 assigns a
     * stack slot at the point each addressable local's address is first taken, NOT in
     * declaration order; hoisting &otz/&sz0/&sz1 into pre-loop pointer temps (needed to put
     * their three `addiu $sp` ahead of the mask/t0/t1 setup, see below) therefore stole slot 0
     * from `flag` and shifted the whole frame.  One array pins the layout:
     *   st[0]=flag @sp+0   st[1]=otz @sp+4   st[2]=sz0 @sp+8   st[3]=sz1 @sp+0xC  st[4]=sz2 @sp+0x10
     * &st[0] folds to plain $sp, which is why `flag` is touched as 0($sp) with no address reg. */
    s32 st[5];
    /* t0/t1 pins ARE load-bearing (unpinning them re-drifts to 124 ins): they reproduce the
     * hand-budgeted src/dst induction-variable allocation so every field offset stays a direct
     * displacement off $t0 / $t1.  cnt/mask/shiftAmt/otp need no pin -- gcc lands them on
     * $t2/$t3/$t9/$t8 on its own, and pinning `otp` to $24 actively BREAKS the match (below). */
    register u8 *t0 __asm__("$8");
    register u8 *t1 __asm__("$9");
    s32 cnt;
    s32 mask;
    s32 shiftAmt;
    s32 *otp;
    s32 *potz, *psz0, *psz1;
    s32 idx0, idx1, idx2;
    s32 idx;
    s32 m;

    cnt = count;
    shiftAmt = shift;
    otp = ot;

    if (cnt == 0) {
        return a3;
    }

    /* Explicit pre-loop pointer temps, ordered ahead of mask/t0/t1: loop-invariant motion
     * APPENDS hoisted insns after the preheader's own statements, so leaving these implicit
     * emitted them last (`lui/ori, addiu t0, addiu t1, addiu sp+4/8/0xC`) -- the target is the
     * reverse order. */
    potz = &st[1];
    psz0 = &st[2];
    psz1 = &st[3];
    mask = 0xFFFFFF;
    t0 = (u8 *)a0 + 3;
    t1 = a3 + 4;

    do {
        idx0 = *(u16 *)(t0 + 0x11);
        idx1 = *(u16 *)(t0 + 0x13);
        idx2 = *(u16 *)(t0 + 0x15);

        gte_ldv3(&a1[idx0], &a1[idx1], &a1[idx2]);
        gte_rtpt();

        *(u32 *)(t1 + 8)    = *(u32 *)(t0 + 1);
        *(u32 *)(t1 + 0x10) = *(u32 *)(t0 + 5);
        *(u32 *)(t1 + 0x18) = *(u32 *)(t0 + 9);

        gte_stflg(&st[0]);
        if (!(st[0] & ~0x1000)) {
            gte_nclip();
            gte_stopz(potz);
            if (st[1] > 0) {
                gte_stsxy3_gt3(a3);

                if (D_80078D88[0] & 0x8000) {
                    gte_stsz3(psz0, psz1, &st[4]);
                    /* `m` must NOT be the address-taken otz slot: assigning otz in each arm
                     * makes gcc spill to sp+4 three times.  The target keeps the running max
                     * in $v1 and stores ONCE, so the max needs a plain (non-addressable) temp.
                     * `st[2] > st[3]` (not `st[3] < st[2]`) is what loads sz0 first and emits
                     * `slt $v0, $v1, $a2`. */
                    if (st[2] > st[3]) {
                        m = st[2];
                        if (m < st[4]) m = st[4];
                    } else {
                        m = st[3];
                        if (m < st[4]) m = st[4];
                    }
                    st[1] = m >> 2;
                } else {
                    gte_avsz3();
                    gte_stotz(potz);
                }

                *(u32 *)t1 = (*(u32 *)(t0 + 0xD) & mask) | ((u32)t0[0] << 24);
                t1 += 0x20;

                idx = st[1] >> shiftAmt;
                {
                    u32 old = (u32)a3 & mask;
                    /* `s32 *p = otp + idx;` -- writing `otp[idx]` inline emits the address
                     * plus with the SCALED INDEX first (`addu $a0,$a0,$t8`); an explicit
                     * pointer temp emits it base-first (`addu $a0,$t8,$a0`) like the target.
                     * The second half of that fix is that `otp` must be an ordinary pseudo:
                     * with `register s32 *otp __asm__("$24")` local-alloc will not tie the
                     * dying index register to the address destination and the chain lands in
                     * $v0 instead of $a0.  Base-first + unpinned base = the last instruction. */
                    s32 *p = otp + idx;
                    *(u32 *)a3 = (*p & mask) | 0x7000000;
                    a3 += 0x20;
                    *p = old;
                }
            }
        }

        t0 += 0x1C;
    } while (--cnt);

    return a3;
}


/* ---- PsyQ inline GTE macros (inline_c.h style) ---- */
#define gte_ldv3(r0, r1, r2) __asm__ __volatile__ ( \
    "lwc2 $0, 0( %0 );"  \
    "lwc2 $1, 4( %0 );"  \
    "lwc2 $2, 0( %1 );"  \
    "lwc2 $3, 4( %1 );"  \
    "lwc2 $4, 0( %2 );"  \
    "lwc2 $5, 4( %2 )"   \
    :                    \
    : "r"( r0 ), "r"( r1 ), "r"( r2 ) )

#define gte_ldv0(r0) __asm__ __volatile__ ( \
    "lwc2 $0, 0( %0 );"  \
    "lwc2 $1, 4( %0 )"   \
    :                    \
    : "r"( r0 ) )

#define gte_rtpt() __asm__ __volatile__ ("nop;nop;rtpt")
#define gte_rtps() __asm__ __volatile__ ("nop;nop;rtps")
#define gte_nclip() __asm__ __volatile__ ("nop;nop;nclip")
#define gte_avsz4() __asm__ __volatile__ ("nop;nop;avsz4")

#define gte_stflg(r0) __asm__ __volatile__ ( \
    "cfc2 $12, $31;"     \
    "nop;"               \
    "sw $12, 0( %0 )"    \
    :                    \
    : "r"( r0 )          \
    : "$12", "memory" )

#define gte_stopz(r0) __asm__ __volatile__ ( \
    "swc2 $24, 0( %0 )"  \
    :                    \
    : "r"( r0 )          \
    : "memory" )

#define gte_stotz(r0) __asm__ __volatile__ ( \
    "swc2 $7, 0( %0 )"   \
    :                    \
    : "r"( r0 )          \
    : "memory" )

#define gte_stsxy(r0) __asm__ __volatile__ ( \
    "swc2 $14, 0( %0 )"  \
    :                    \
    : "r"( r0 )          \
    : "memory" )

#define gte_stsxy3_g4(r0) __asm__ __volatile__ ( \
    "swc2 $12, 8( %0 );"  \
    "swc2 $13, 16( %0 );" \
    "swc2 $14, 24( %0 )"  \
    :                     \
    : "r"( r0 )           \
    : "memory" )

#define gte_stsz4(r0, r1, r2, r3) __asm__ __volatile__ ( \
    "swc2 $16, 0( %0 );" \
    "swc2 $17, 0( %1 );" \
    "swc2 $18, 0( %2 );" \
    "swc2 $19, 0( %3 )"  \
    :                    \
    : "r"( r0 ), "r"( r1 ), "r"( r2 ), "r"( r3 ) \
    : "memory" )

typedef struct {
    s16 vx, vy, vz, pad;
} Vtx8;

typedef struct {
    u8  pad0;
    u8  pad1;
    u8  pad2;
    u8  code;   /* +0x03 */
    u32 rgb1;   /* +0x04 */
    u32 rgb2;   /* +0x08 */
    u32 rgb3;   /* +0x0C */
    u32 term;   /* +0x10 */
    u32 rgb0;   /* +0x14 */
    u16 i0;     /* +0x18 */
    u16 i1;     /* +0x1A */
    u16 i2;     /* +0x1C */
    u16 i3;     /* +0x1E */
} SrcQ;

typedef struct {
    u32 tag;    /* +0x00 */
    u32 rgb0;   /* +0x04 */
    u32 xy0;    /* +0x08 */
    u32 rgb1;   /* +0x0C */
    u32 xy1;    /* +0x10 */
    u32 rgb2;   /* +0x14 */
    u32 xy2;    /* +0x18 */
    u32 rgb3;   /* +0x1C */
    u32 xy3;    /* +0x20 */
    u32 term;   /* +0x24 */
} LineG4;

extern s32 D_80078D88[];

LineG4 *func_800279AC(SrcQ *src, Vtx8 *vb, s32 unused, LineG4 *prim, s32 n, s32 shift, u32 *ot)
{
    s32 flag;
    s32 otz;

    /* cookbook §21 zero-byte re-tie: without it loop.c's record_initial takes the biv's
     * initial value straight from the parameter COPY (set prim (reg $a3)), so the +4 giv is
     * emitted as (plus (reg $a3) 4) -- $a3 then stays live past the copy, conflicts with the
     * prim pseudo, and prim/giv land in $t1/$a3 (target: $a3/$t1). The re-tie makes the
     * pre-loop set non-invariant so the giv is derived from the PSEUDO and prim coalesces
     * into $a3. Emits nothing. */
    __asm__ ("" : "=r"(prim) : "0"(prim));
    for (; n != 0; n--, src++) {
        gte_ldv3(&vb[src->i0], &vb[src->i1], &vb[src->i2]);
        gte_rtpt();
        prim->rgb1 = src->rgb1;
        prim->rgb2 = src->rgb2;
        prim->rgb3 = src->rgb3;
        gte_stflg(&flag);
        if (flag & 0xFFFFEFFF) {
            continue;
        }
        gte_nclip();
        gte_stopz(&otz);
        if (otz <= 0) {
            continue;
        }
        gte_stsxy3_g4(prim);
        gte_ldv0(&vb[src->i3]);
        gte_rtps();
        gte_stflg(&flag);
        if (flag & 0xFFFFEFFF) {
            continue;
        }
        gte_stsxy(&prim->xy3);
        prim->term = src->term;
        /* §5a zero-byte barrier: else sched2 hoists the D_80078D88 load above this store and
         * eats the two load-delay nops the target keeps (the -2 length drift). */
        __asm__ __volatile__ ("" : : : "memory");
        if (D_80078D88[0] & 0x8000) {
            s32 sz[4];
            s32 m, k;
            gte_stsz4(&sz[0], &sz[1], &sz[2], &sz[3]);
            m = sz[2];
            if (m < sz[3]) {
                m = sz[3];
            }
            k = sz[0];
            if (k < sz[1]) {
                k = sz[1];
            }
            if (k < m) {
                k = m;
            }
            otz = k >> 2;
        } else {
            gte_avsz4();
            gte_stotz(&otz);
        }
        prim->rgb0 = (src->rgb0 & 0xFFFFFF) | ((u32)src->code << 24);
        /* §5a zero-byte barrier: keeps the rgb0 store ahead of the OT-link block instead of
         * letting sched2 interleave the `otz` reload into the rgb0 chain. */
        __asm__ __volatile__ ("" : : : "memory");
        {
            u32 *p = &ot[otz >> shift];
            prim->tag = (*p & 0xFFFFFF) | 0x09000000;
            *p = (u32)prim & 0xFFFFFF;
        }
        prim++;
    }
    return prim;
}

INCLUDE_ASM("asm/nonmatchings/800", func_80027BF0);

INCLUDE_ASM("asm/nonmatchings/800", func_80027C10);


/* ---- PsyQ inline GTE macros (same spellings as the matched ov_SC03_006 body) ---- */

#define gte_ldv3(r0, r1, r2) __asm__ volatile (  \
    "lwc2 $0, 0( %0 );"                          \
    "lwc2 $1, 4( %0 );"                          \
    "lwc2 $2, 0( %1 );"                          \
    "lwc2 $3, 4( %1 );"                          \
    "lwc2 $4, 0( %2 );"                          \
    "lwc2 $5, 4( %2 )"                           \
    :                                            \
    : "r"( r0 ), "r"( r1 ), "r"( r2 ) )

#define gte_ldrgb(r0) __asm__ volatile (         \
    "lwc2 $6, 0( %0 )"                           \
    :                                            \
    : "r"( r0 ) )

#define gte_rtpt()  __asm__ volatile ("nop;nop;rtpt")
#define gte_nclip() __asm__ volatile ("nop;nop;nclip")
#define gte_ncct()  __asm__ volatile ("nop;nop;ncct")

#define gte_stflg(r0) __asm__ volatile (         \
    "cfc2 $12, $31;"                             \
    "nop;"                                       \
    "sw $12, 0( %0 )"                            \
    :                                            \
    : "r"( r0 )                                  \
    : "$12", "memory" )

#define gte_stopz(r0) __asm__ volatile (         \
    "swc2 $24, 0( %0 )"                          \
    :                                            \
    : "r"( r0 )                                  \
    : "memory" )

#define gte_stsz3(r0, r1, r2) __asm__ volatile ( \
    "swc2 $17, 0( %0 );"                         \
    "swc2 $18, 0( %1 );"                         \
    "swc2 $19, 0( %2 )"                          \
    :                                            \
    : "r"( r0 ), "r"( r1 ), "r"( r2 )            \
    : "memory" )

#define gte_stsxy3_g3(r0) __asm__ volatile (     \
    "swc2 $12, 8( %0 );"                         \
    "swc2 $13, 16( %0 );"                        \
    "swc2 $14, 24( %0 )"                         \
    :                                            \
    : "r"( r0 )                                  \
    : "memory" )

#define gte_strgb3_g3(r0) __asm__ volatile (     \
    "swc2 $20, 4( %0 );"                         \
    "swc2 $21, 12( %0 );"                        \
    "swc2 $22, 20( %0 )"                         \
    :                                            \
    : "r"( r0 )                                  \
    : "memory" )

typedef struct { s16 vx, vy, vz, pad; } SVEC2;      /* 0x08 */

typedef struct {                                     /* 0x14 */
    u32 w0;      /* 0x00 */
    u32 rgb;     /* 0x04 */
    u16 n0;      /* 0x08 */
    u16 v0;      /* 0x0A */
    u16 n1;      /* 0x0C */
    u16 v1;      /* 0x0E */
    u16 n2;      /* 0x10 */
    u16 v2;      /* 0x12 */
} Face2;

typedef struct {                                     /* 0x1C */
    u32 tag;
    u32 rgb0;
    s16 x0, y0;
    u32 rgb1;
    s16 x1, y1;
    u32 rgb2;
    s16 x2, y2;
} G3P;

extern s16 D_800C7C74;
extern void func_80028200(s32 a0, s32 a1, s32 a2, s32 a3, s32 stack_arg);

G3P *func_80027D20(Face2 *f, SVEC2 *verts, SVEC2 *norms, G3P *prims,
                   s32 count, s32 shift, s32 ot)
{
    struct { s32 flag, opz, sz0, sz1, sz2; } g;
    G3P *prim;
    s32 z;
    s32 w;
    s32 i;

    prim = &prims[D_800C7C74];

    for (i = count; i != 0; i--, f++, prim += 2) {
        gte_ldv3(&verts[f->v0], &verts[f->v1], &verts[f->v2]);
        gte_rtpt();
        gte_stflg(&g.flag);
        if (!(g.flag & ~0x1000)) {
            gte_nclip();
            gte_stopz(&g.opz);
            if (g.opz > 0) {
                gte_stsxy3_g3(prim);
                gte_stsz3(&g.sz0, &g.sz1, &g.sz2);
                if (g.sz0 < g.sz1) { w = g.sz2; z = g.sz0; } else { w = g.sz2; z = g.sz1; }
                if (w < z) z = w;
                g.opz = (z >> 2) - 1;
                if (g.opz < 0) {
                    g.opz = 0;
                }
                gte_ldrgb(&f->rgb);
                gte_ldv3(&norms[f->n0], &norms[f->n1], &norms[f->n2]);
                gte_ncct();
                gte_strgb3_g3(prim);
                func_80028200(ot, g.opz, shift, (s32)prim, 0x06000000);
            }
        }
    }

    return prim;
}

INCLUDE_ASM("asm/nonmatchings/800", func_80027F4C);


void func_80028200(s32 a0, s32 a1, s32 a2, s32 a3, s32 stack_arg) {
    s32 mask;
    s32 shifted_index;
    s32 *array_ptr;
    s32 loaded;
    s32 masked_a3;

    mask = 0xFFFFFF;
    shifted_index = (a1 >> a2) << 2;
    array_ptr = (s32 *)(a0 + shifted_index);
    loaded = *array_ptr;

    loaded = (loaded & mask) | stack_arg;
    *(s32 *)a3 = loaded;

    masked_a3 = (a3 & mask);
    *array_ptr = masked_a3;
}

void func_80028234(void) {
}

INCLUDE_ASM("asm/nonmatchings/800", func_8002823C);

void func_800282FC(void) {
}

INCLUDE_ASM("asm/nonmatchings/800", func_80028304);

INCLUDE_ASM("asm/nonmatchings/800", func_80028394);


extern void func_80028620(s32, void *);
extern u8 D_800A5E94;
extern u8 D_800A5E95;
extern u8 D_800A5E96;
extern u8 D_800A5E88;

void func_80028428(s32 a0, s32 a1, s32 a2, s32 a3) {
    s32 offset;

    a0 &= 0xFFFF;
    if ((u16)a0 >= 3) {
        return;
    }

    offset = a0 << 4;

    *(u8 *)((s32)&D_800A5E94 + offset) = (u8)a1;
    *(u8 *)((s32)&D_800A5E95 + offset) = (u8)a2;
    *(u8 *)((s32)&D_800A5E96 + offset) = (u8)a3;

    func_80028620(a0, (void *)((s32)&D_800A5E88 + offset));
}

INCLUDE_ASM("asm/nonmatchings/800", func_80028488);

INCLUDE_ASM("asm/nonmatchings/800", func_8002850C);


extern u8 D_800A5E94;
extern u8 D_800A5E95;
extern u8 D_800A5E96;
extern u8 D_800A5E88;
extern void func_80028620(s32, void *);

void func_80028558(s32 a0, s32 a1, s32 a2, s32 a3) {
    s32 v0;

    a0 &= 0xFFFF;
    v0 = a0 << 4;

    *(u8 *)((u32)&D_800A5E94 + v0) = a1;
    *(u8 *)((u32)&D_800A5E95 + v0) = a2;
    *(u8 *)((u32)&D_800A5E96 + v0) = a3;

    func_80028620(a0, (u8 *)&D_800A5E88 + v0);
}

INCLUDE_ASM("asm/nonmatchings/800", SsUtReverbOff);


extern s16 D_800C6D18;
extern s32 D_800C6D1C;
extern s8 D_800C6D20;
extern s8 D_800C6D22;

extern void GsSetFogParam(s32 *param);
extern void func_800538EC(s32 param);

void func_800285CC(void) {
    s32 *fog = (s32 *)&D_800C6D18;
    *(s16 *)fog = -0x106;
    D_800C6D1C = 0x1F40000;
    D_800C6D20 = 0;
    D_800C6D22 = 0;
    GsSetFogParam(fog);
    func_800538EC(1);
}

INCLUDE_ASM("asm/nonmatchings/800", func_80028620);

INCLUDE_ASM("asm/nonmatchings/800", func_80028694);

void func_80028A30(void) {
}

void func_80028A38(void) {
}

void func_80028A40(void) {
}

INCLUDE_ASM("asm/nonmatchings/800", func_80028A48);

INCLUDE_ASM("asm/nonmatchings/800", func_80028C50);

INCLUDE_ASM("asm/nonmatchings/800", func_80028D58);

INCLUDE_ASM("asm/nonmatchings/800", func_80028D78);

INCLUDE_ASM("asm/nonmatchings/800", func_80028D9C);

INCLUDE_ASM("asm/nonmatchings/800", func_80028DBC);

INCLUDE_ASM("asm/nonmatchings/800", func_80028DE0);

INCLUDE_ASM("asm/nonmatchings/800", func_80028E00);

INCLUDE_ASM("asm/nonmatchings/800", func_80028E24);

INCLUDE_ASM("asm/nonmatchings/800", func_80028E44);

INCLUDE_ASM("asm/nonmatchings/800", func_80028E68);

INCLUDE_ASM("asm/nonmatchings/800", func_80028E88);

INCLUDE_ASM("asm/nonmatchings/800", func_80028EAC);

INCLUDE_ASM("asm/nonmatchings/800", func_80028ECC);

INCLUDE_ASM("asm/nonmatchings/800", func_80028EF0);

INCLUDE_ASM("asm/nonmatchings/800", func_80028F10);

INCLUDE_ASM("asm/nonmatchings/800", func_80028F34);

INCLUDE_ASM("asm/nonmatchings/800", func_80028F54);

INCLUDE_ASM("asm/nonmatchings/800", func_80028F78);

INCLUDE_ASM("asm/nonmatchings/800", func_80028F98);

INCLUDE_ASM("asm/nonmatchings/800", func_80028FBC);

INCLUDE_ASM("asm/nonmatchings/800", func_80028FDC);

INCLUDE_ASM("asm/nonmatchings/800", func_80029000);

INCLUDE_ASM("asm/nonmatchings/800", func_80029020);


extern u8 D_800AE648[];

void func_80029044(void) {
    register s32 v1 __asm__("$3");

    v1 = 0;

    do {
        D_800AE648[v1] = 0;
        v1 += 1;
    } while ((u32)v1 < 0x40);
}


extern u8 D_800BA1B8[];

void func_8002906C(void) {
    register s32 v1 __asm__("$3");

    v1 = 0;
    do {
        D_800BA1B8[v1] = 0;
        v1 += 1;
    } while ((u32)v1 < 0x100);
}


extern void func_80016714(void *a0, s32 a1);
extern u8 D_800BA2B8[];

void func_80029094(void) {
    func_80016714(D_800BA2B8, 0x60);
}

INCLUDE_ASM("asm/nonmatchings/800", func_800290BC);

INCLUDE_ASM("asm/nonmatchings/800", func_800290E0);

INCLUDE_ASM("asm/nonmatchings/800", func_80029104);

INCLUDE_ASM("asm/nonmatchings/800", func_80029124);

INCLUDE_ASM("asm/nonmatchings/800", func_80029178);

INCLUDE_ASM("asm/nonmatchings/800", func_800291A0);

INCLUDE_ASM("asm/nonmatchings/800", func_800291B4);

INCLUDE_ASM("asm/nonmatchings/800", func_800291C8);

INCLUDE_ASM("asm/nonmatchings/800", func_800291DC);

INCLUDE_ASM("asm/nonmatchings/800", func_800291F0);

INCLUDE_ASM("asm/nonmatchings/800", func_80029204);


extern s32 D_800AE6A8;
extern void func_80016714(void *a0, s32 a1);

void func_80029218(void) {
    func_80016714(&D_800AE6A8, 0x3C);
}

INCLUDE_ASM("asm/nonmatchings/800", func_80029240);

extern s32 D_80075838;
void func_80029254(void) {
    D_80075838 = 0;
}

extern s32 D_80075838;
s32 func_80029264(void) {
    return D_80075838;
}

INCLUDE_ASM("asm/nonmatchings/800", func_80029274);


extern void func_80029344(void);
extern s32 D_80078E90;

void func_8002931C(s32 a0) {
    D_80078E90 = a0;
    func_80029344();
}

INCLUDE_ASM("asm/nonmatchings/800", func_80029344);


extern void func_80016714(void *a0, s32 a1);
extern u16 D_800A6588[];

void func_8002941C(void) {
    func_80016714(D_800A6588, 0x2);
}

INCLUDE_ASM("asm/nonmatchings/800", func_80029444);

extern s32 D_80078E80;
s32 func_80029504(void) {
    return D_80078E80;
}

extern s32 D_80078E80;
void func_80029514(s32 arg0) {
    D_80078E80 = arg0;
}

INCLUDE_ASM("asm/nonmatchings/800", func_80029524);

extern s32 D_80078E84;
s32 func_8002953C(void) {
    return D_80078E84;
}

extern s32 D_80078E84;
void func_8002954C(s32 arg0) {
    D_80078E84 = arg0;
}

INCLUDE_ASM("asm/nonmatchings/800", func_8002955C);

extern s32 D_80078E88;
s32 func_8002957C(void) {
    return D_80078E88;
}

extern s32 D_80078E88;
void func_8002958C(s32 arg0) {
    D_80078E88 = arg0;
}


extern void func_8002A544(s32);
extern s32 D_80078E88;

void func_8002959C(void) {
    func_8002A544(0x32);
    D_80078E88 = D_80078E88 + 1;
}

INCLUDE_ASM("asm/nonmatchings/800", func_800295D4);


extern void func_80029344(void);
extern s32 D_80078E90;

void func_80029664(void) {
    D_80078E90 = 0x528;
    func_80029344();
}

INCLUDE_ASM("asm/nonmatchings/800", func_80029690);

INCLUDE_ASM("asm/nonmatchings/800", func_800296F8);

INCLUDE_ASM("asm/nonmatchings/800", func_80029774);

INCLUDE_ASM("asm/nonmatchings/800", func_800298BC);

INCLUDE_ASM("asm/nonmatchings/800", func_8002992C);

INCLUDE_ASM("asm/nonmatchings/800", func_80029A58);

INCLUDE_ASM("asm/nonmatchings/800", func_80029A94);

INCLUDE_ASM("asm/nonmatchings/800", func_80029AAC);


extern s32 func_80029E30(void);
extern s32 func_80029CD4(s32);

s32 func_80029AF4(void) {
    s32 s0;

    s0 = func_80029E30();
    s0 = s0 * (func_80029CD4(0x28) + 0xC8);
    return s0 / 100;
}

INCLUDE_ASM("asm/nonmatchings/800", func_80029B4C);

INCLUDE_ASM("asm/nonmatchings/800", func_80029BC8);

INCLUDE_ASM("asm/nonmatchings/800", func_80029C44);


extern s32 rand(void);

s32 func_80029CD4(s32 a0) {
    if (a0 == 0)
        return 0;
    return rand() % a0;
}

INCLUDE_ASM("asm/nonmatchings/800", func_80029D3C);

INCLUDE_ASM("asm/nonmatchings/800", func_80029DB4);


extern s32 func_8002A76C(void);
extern s32 func_8002A2B0(void);

s32 func_80029E30(void) {
    register s32 v1 __asm__("$3");
    s32 a, b, sum, v0, sign;

    a = func_8002A76C();
    b = func_8002A2B0();

    // Load magic constant directly into v1
    __asm__("lui %0, 0x51eb; ori %0, %0, 0x851f" : "=r"(v1));

    sum = a + b;

    // Compute sum * 175 via shifts
    v0 = sum << 1;      // sum * 2
    v0 = v0 + sum;      // sum * 3
    v0 = v0 << 2;       // sum * 12
    v0 = v0 - sum;      // sum * 11
    v0 = v0 << 4;       // sum * 176
    v0 = v0 - sum;      // sum * 175

    // Multiply by magic constant
    __asm__ __volatile__("mult %0, %1" : : "r"(v0), "r"(v1) : "hi", "lo");

    // Sign of v0 for division correction (happens in parallel)
    sign = v0 >> 31;

    // Get high word of multiplication into a hard-pinned $a0, scoped
    // narrowly so the pin doesn't bleed backward and swallow v1's
    // (magic-constant) live range into the same physical register.
    {
        register s32 a0 __asm__("$4");
        __asm__ __volatile__("mfhi %0" : "=r"(a0) : : "hi", "lo");
        // Final result: (high >> 5) - sign
        v1 = a0 >> 5;
    }
    return v1 - sign;
}

INCLUDE_ASM("asm/nonmatchings/800", func_80029E94);

INCLUDE_ASM("asm/nonmatchings/800", func_80029EC0);

INCLUDE_ASM("asm/nonmatchings/800", func_80029ED4);

extern s32 D_80078F08;
s32 func_80029FD4(void) {
    return D_80078F08;
}

INCLUDE_ASM("asm/nonmatchings/800", func_80029FE4);


extern s32 func_8002A088(s32);

s32 func_8002A04C(s32 a0) {
    s32 v0 = *(s32 *)(a0 + 0x78);

    if (v0) {
        return func_8002A088(*(s16 *)(v0 + 0x2E));
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/800", func_8002A088);

INCLUDE_ASM("asm/nonmatchings/800", func_8002A108);


extern s32 func_8002A26C(void);
extern s32 func_8002AA00(s32 a0);
extern s32 func_8002A27C(void);
extern s32 func_8002A28C(void);

s32 func_8002A1B4(void) {
    s32 temp;
    s32 check;
    s32 val1;
    s32 val2;
    s32 s0_val;

    temp = func_8002A26C();
    check = func_8002AA00(temp + 1);

    if (check == 0) {
        return 0;
    }

    val1 = func_8002A27C();
    val2 = func_8002A28C();
    s0_val = val1 ^ val2;

    if (s0_val == 0) {
        return 1;
    }

    return 0;
}


extern s32 func_8002A28C(void);
extern s32 func_8002A27C(void);

s32 func_8002A200(void) {
    s32 val_28C = func_8002A28C();
    s32 val_27C = func_8002A27C();
    return (val_27C >= val_28C) ? 1 : 0;
}


extern s32 D_80078EE4;
extern s32 D_80078EE8;

void func_8002A234(void) {
    s32 v1 = D_80078EE4 + 1;
    if (v1 >= 0x1F) {
        v1 = 0x1E;
    }
    D_80078EE4 = v1;
    D_80078EE8 = 0;
}

extern s32 D_80078EE4;
s32 func_8002A26C(void) {
    return D_80078EE4;
}

extern s32 D_80078EE8;
s32 func_8002A27C(void) {
    return D_80078EE8;
}

INCLUDE_ASM("asm/nonmatchings/800", func_8002A28C);

INCLUDE_ASM("asm/nonmatchings/800", func_8002A2B0);

INCLUDE_ASM("asm/nonmatchings/800", func_8002A2D4);

INCLUDE_ASM("asm/nonmatchings/800", func_8002A354);


extern s32 func_8002AA00(s32);
extern s32 func_8002A4D8(void);

s32 func_8002A400(void) {
    s32 a, b;

    a = func_8002A4B8();
    b = func_8002AA00(a + 1);

    if (!b) {
        return 0;
    }

    a = func_8002A4C8();
    a ^= func_8002A4D8();

    if (a == 0) {
        return 1;
    }
    return 0;
}


extern s32 func_8002A4D8(void);
extern s32 func_8002A4C8(void);

s32 func_8002A44C(void) {
    s32 result1 = func_8002A4D8();
    s32 result2 = func_8002A4C8();
    return !(result2 < result1);
}


extern s32 D_80078EEC;
extern s32 D_80078EF0;

void func_8002A480(void) {
    s32 v0 = D_80078EEC;
    s32 v1 = v0 + 1;
    if (v1 >= 0x1F) {
        v1 = 0x1E;
    }
    D_80078EEC = v1;
    D_80078EF0 = 0;
}

extern s32 D_80078EEC;
s32 func_8002A4B8(void) {
    return D_80078EEC;
}

extern s32 D_80078EF0;
s32 func_8002A4C8(void) {
    return D_80078EF0;
}

INCLUDE_ASM("asm/nonmatchings/800", func_8002A4D8);

INCLUDE_ASM("asm/nonmatchings/800", func_8002A4FC);

INCLUDE_ASM("asm/nonmatchings/800", func_8002A520);

INCLUDE_ASM("asm/nonmatchings/800", func_8002A544);

INCLUDE_ASM("asm/nonmatchings/800", func_8002A5C4);


extern s32 func_8002A728(void);
extern s32 func_8002A738(void);
extern s32 func_8002A748(void);
extern s32 func_8002AA00(s32 a0);

s32 func_8002A670(void) {
    s32 s0;

    if (func_8002AA00(func_8002A728() + 1) != 0) {
        s0 = func_8002A738();
        return s0 == func_8002A748();
    } else {
        return 0;
    }
}


extern s32 func_8002A748(void);

s32 func_8002A6BC(void) {
    s32 a = func_8002A748();
    s32 b = func_8002A738();
    return !(b < a);
}


extern s32 D_80078EFC;
extern s32 D_80078F00;

void func_8002A6F0(void) {
    register s32 loaded asm("$2");  // $v0
    register s32 result asm("$3");  // $v1

    loaded = D_80078EFC;
    result = loaded + 1;
    if (result >= 0x1F) {
        result = 0x1E;
    }
    D_80078EFC = result;
    D_80078F00 = 0;
}

extern s32 D_80078EFC;
s32 func_8002A728(void) {
    return D_80078EFC;
}

extern s32 D_80078F00;
s32 func_8002A738(void) {
    return D_80078F00;
}

INCLUDE_ASM("asm/nonmatchings/800", func_8002A748);

INCLUDE_ASM("asm/nonmatchings/800", func_8002A76C);

INCLUDE_ASM("asm/nonmatchings/800", func_8002A790);

INCLUDE_ASM("asm/nonmatchings/800", func_8002A7B4);

INCLUDE_ASM("asm/nonmatchings/800", func_8002A834);


extern s32 func_8002A998(void);
extern s32 func_8002A9A8(void);
extern s32 func_8002A9B8(void);
extern s32 func_8002AA00(s32);

s32 func_8002A8E0(void) {
    s32 s0, v0;

    v0 = func_8002AA00(func_8002A998() + 1);
    if (!v0) {
        return 0;
    }

    s0 = func_8002A9A8();
    s0 = s0 ^ func_8002A9B8();
    if (s0 == 0) {
        return 1;
    }
    return 0;
}


extern s32 func_8002A9B8(void);

s32 func_8002A92C(void) {
    s32 val1 = func_8002A9B8();
    s32 val2 = func_8002A9A8();
    s32 cmp = (val2 < val1) ? 1 : 0;
    return cmp ^ 1;
}


extern s32 D_80078EF4;
extern s32 D_80078EF8;

void func_8002A960(void) {
    s32 v1 = D_80078EF4 + 1;
    if (v1 >= 0x1F) {
        v1 = 0x1E;
    }
    D_80078EF4 = v1;
    D_80078EF8 = 0;
}

extern s32 D_80078EF4;
s32 func_8002A998(void) {
    return D_80078EF4;
}

extern s32 D_80078EF8;
s32 func_8002A9A8(void) {
    return D_80078EF8;
}

INCLUDE_ASM("asm/nonmatchings/800", func_8002A9B8);

INCLUDE_ASM("asm/nonmatchings/800", func_8002A9DC);

INCLUDE_ASM("asm/nonmatchings/800", func_8002AA00);

INCLUDE_ASM("asm/nonmatchings/800", func_8002AA3C);

void func_8002AAAC(void) {
}

INCLUDE_ASM("asm/nonmatchings/800", func_8002AAB4);

INCLUDE_ASM("asm/nonmatchings/800", func_8002AB64);

INCLUDE_ASM("asm/nonmatchings/800", func_8002AC00);

INCLUDE_ASM("asm/nonmatchings/800", func_8002AC98);

INCLUDE_ASM("asm/nonmatchings/800", func_8002AE60);

INCLUDE_ASM("asm/nonmatchings/800", func_8002AED0);

INCLUDE_ASM("asm/nonmatchings/800", func_8002AEE4);

extern s32 D_800760C8;
void func_8002AEF8(void) {
    D_800760C8 = 0;
}

s32 func_8002AF08(void) {
    return D_800760C8;
}


extern s32 D_800760AC;
extern s32 D_8007609C;
extern s32 D_800760A0;
extern s32 D_800760A4;
extern s32 D_800760A8;

void func_8002AF18(void) {
    D_800760AC = 0;
    D_8007609C = 0;
    D_800760A0 = 0;
    D_800760A4 = 0;
    D_800760A8 = 0;
}

INCLUDE_ASM("asm/nonmatchings/800", func_8002AF48);

extern s32 D_80075A40;
s32 func_8002AF60(void) {
    return D_80075A40;
}

INCLUDE_ASM("asm/nonmatchings/800", func_8002AF70);


typedef struct {
    u32 a, b, c, d;
} Blk16;

typedef struct {
    u32 a, b, c;
} Blk12;

extern Blk16 D_80075CC0[];

void func_8002B00C(void *dest) {
    Blk16 *d = (Blk16 *)dest;
    Blk16 *s = D_80075CC0;
    Blk16 *end = s + (0x2D0 / 0x10);

    do {
        *d = *s;
        s++;
        d++;
    } while (s != end);

    *(Blk12 *)d = *(Blk12 *)s;
}


u16 func_8002B064(u8 *a0) {
    u32 sum = 0;
    s32 a1 = (s32)a0 + 0x70;

    do {
        sum += *a0;
        a0++;
    } while ((s32)a0 < a1);

    return sum & 0xFFFF;
}


u16 func_8002B08C(s32 a0) {
    s32 v1 = 0;
    s32 a1 = a0 + 0x300;

    do {
        v1 += *(u8 *)a0;
        a0++;
    } while (a0 < a1);

    return v1 & 0xFFFF;
}

INCLUDE_ASM("asm/nonmatchings/800", func_8002B0B4);

/* DEFERRED: SaveLoadRoutine (0x8002B154) — Phase 7 (session G), per Drew, to Q#5.
 * Original intent: the save / PS1 memory-card handler. Referenced by saveHeaderTemplate
 *   (0x80072DF0) via THREE entry-point pointers: 0x8002B154 / 0x8002B1AC / 0x8002BEA4.
 *   Dispatch branches on (selector & 7) (case 0 -> +1 counter; 1 -> 7; 2 -> 0x1E; 3 -> 0x23).
 * Why deferred (NOT a clean state machine like the 3 CD loaders drafted this session):
 *   - splat emits ONE 1139-instruction stub spanning 0x8002B154-0x8002C31C with a SINGLE `jr $ra`
 *     => it is effectively one large MULTI-ENTRY function (the 3 saveHeaderTemplate entries share a
 *     return; the caller passes args in $s0/$s3) — awkward to express in C at all.
 *   - Ghidra mis-analyses it: get_code(0x8002B154) returns only a tiny fragment using unaff_s0/
 *     unaff_s3 (caller-set regs), so there is no faithful whole-function decompile to translate.
 *   - It is the save-data/memcard format, explicitly Phase-3 Q#5 "format still TBD" — a different
 *     subsystem from the file/overlay loader cluster (which IS drafted: CdReadStateMachine,
 *     CdReadSectorReadyCB, StreamLoadStateMachine here + the matched CdReadRequest/CdQueueBusy/…).
 *   - External helpers it calls (uncharacterised): func_800603BC (x20), func_80060614, func_8006023C,
 *     func_80060D9C, func_80060AE0, func_8005FFB4, func_8005FD58, func_80061114/524, func_80016714(bzero).
 * Re-enable / revisit when Q#5 (save/memcard format) is studied: FIRST fix the Ghidra function
 *   boundary (make 0x8002B154 span the whole 1139 ins, or model the 3 entry points), re-decompile,
 *   characterise the func_80060xxx memcard helpers, THEN draft. A wrong faithful-looking draft here
 *   would be worse than this honest stub (P9/G3). The default build is byte-identical via this stub. */
INCLUDE_ASM("asm/nonmatchings/800", SaveLoadRoutine);

INCLUDE_ASM("asm/nonmatchings/800", func_8002C320);

INCLUDE_ASM("asm/nonmatchings/800", func_8002C3B0);

INCLUDE_ASM("asm/nonmatchings/800", func_8002C410);


extern s16 D_800C5328[];
extern s16 D_800C532A[];

void func_8002C8BC(void) {
    register s32 a0 __asm__("$4");
    register s32 v1 __asm__("$3");

    a0 = -1;
    v1 = 0;

    do {
        *(s16 *)((u8 *)D_800C5328 + v1) = a0;
        *(s16 *)((u8 *)D_800C532A + v1) = a0;
        v1 += 4;
    } while ((u32)v1 < 0x1E4);
}

INCLUDE_ASM("asm/nonmatchings/800", func_8002C8F4);

INCLUDE_ASM("asm/nonmatchings/800", func_8002CC4C);

INCLUDE_ASM("asm/nonmatchings/800", func_8002CCB4);

INCLUDE_ASM("asm/nonmatchings/800", func_8002CCD8);

INCLUDE_ASM("asm/nonmatchings/800", func_8002CDD8);

INCLUDE_ASM("asm/nonmatchings/800", func_8002CFE4);

INCLUDE_ASM("asm/nonmatchings/800", func_8002D034);


extern void func_8003B45C(s32 *);

extern s32 D_800A4ECC;
extern s32 D_800A4ED0;
extern u16 D_800A4ED4;
extern u16 D_800A4ED6;

void func_8002D1F0(s32 arg0) {
    s32 *v1 = &D_800A4ECC;
    *v1 = 1;
    D_800A4ED0 = (s16)arg0;
    D_800A4ED4 = 0;
    D_800A4ED6 = 0;
    func_8003B45C(v1);
}


extern s32 D_800A4ECC;
extern u16 D_8006ADD8[];
extern u16 D_800A4E74;
extern u16 D_800A4ED4;
extern u16 D_800A4ED6;
extern void func_8003B45C(s32 *a0);

void func_8002D240(s32 a0) {
    s32 index = (a0 << 16) >> 15;
    s32 *p = &D_800A4ECC;
    u16 value = *(u16 *)((u8 *)D_8006ADD8 + index);

    *p = 0x6;
    D_800A4E74 = (u16)a0;
    D_800A4ED4 = value;
    D_800A4ED6 = value;

    func_8003B45C(p);
}

INCLUDE_ASM("asm/nonmatchings/800", func_8002D29C);

INCLUDE_ASM("asm/nonmatchings/800", func_8002D320);

extern u8 D_800A46BA;
u8 func_8002D4B8(void) {
    return D_800A46BA;
}

INCLUDE_ASM("asm/nonmatchings/800", func_8002D4C8);

INCLUDE_ASM("asm/nonmatchings/800", func_8002D59C);

INCLUDE_ASM("asm/nonmatchings/800", func_8002D678);

INCLUDE_ASM("asm/nonmatchings/800", func_8002D6D8);

void func_8002D7F4(void) {
}

extern s32 D_800A4E7C;
void func_8002D7FC(s32 arg0) {
    D_800A4E7C = arg0;
}

INCLUDE_ASM("asm/nonmatchings/800", func_8002D80C);

extern s16 D_8006A990;
void func_8002D834(void) {
    D_8006A990 = 0;
}

INCLUDE_ASM("asm/nonmatchings/800", func_8002D844);

INCLUDE_ASM("asm/nonmatchings/800", func_8002D858);

INCLUDE_ASM("asm/nonmatchings/800", func_8002D8A8);

INCLUDE_ASM("asm/nonmatchings/800", func_8002D8D4);

INCLUDE_ASM("asm/nonmatchings/800", func_8002D904);

INCLUDE_ASM("asm/nonmatchings/800", func_8002DC68);


extern u8 D_8006A980;
extern s16 D_8006A982;
extern u8 D_8006A984;
extern s8 D_800A4F17;
extern u8 D_800A4F18;
extern s16 D_800A4EFC;

extern void func_8002DC68(s32 a0, s32 a1);
extern void func_8002E138(s32 a0, s32 a1, s32 a2);
extern void func_80030F80(void);
extern void func_8002D320(void);
extern void func_80031BE0(void);

void func_8002DF80(void) {
    u8 v1;

    v1 = D_8006A980;
    if ((v1 & 0x7) != 0) {
        if ((v1 & 0x1) != 0 && (v1 & 0x2) != 0) {
            func_8002DC68(0x719, 0);
            D_8006A980 &= 0xF8;
        }

        if ((D_8006A980 & 0x7) != 0) {
            s16 val = D_8006A982;
            s32 a0;

            if (val <= 0) {
                a0 = 0x710;
            } else if (val >= 4) {
                a0 = 0x712;
            } else {
                a0 = 0x711;
            }

            func_8002DC68(a0, 0);
            D_8006A982 = 0;
            D_8006A980 &= 0xF8;
        }
    }

    v1 = D_8006A980;
    if ((v1 & 0x8) != 0) {
        u8 a1 = D_8006A984;

        if (a1 != 0) {
            func_8002DC68(0xA75, a1 | 0x1000);
            D_8006A984 = 0;
            D_8006A980 |= 0x10;
        } else {
            u8 v0;

            D_8006A980 = v1 & 0xEF;
            D_800A4F17 = 1;
            func_8002E138(4, 0xA75, 0);
            v0 = D_800A4F18;
            D_800A4F17 = v0;

            if (v0 != 0) {
                s16 v0s = D_800A4EFC;

                if (v0s != 0) {
                    D_800A4EFC = v0s - 1;
                }

                func_80030F80();
                func_8002D320();
                func_80031BE0();
                D_800A4F18 = 0;
                D_800A4F17 = 0;
            }
        }

        D_8006A980 &= 0xF7;
    }
}

INCLUDE_ASM("asm/nonmatchings/800", func_8002E138);

INCLUDE_ASM("asm/nonmatchings/800", func_8002E5BC);

INCLUDE_ASM("asm/nonmatchings/800", func_8002E5F8);

INCLUDE_ASM("asm/nonmatchings/800", func_8002E638);

INCLUDE_ASM("asm/nonmatchings/800", func_8002E700);

INCLUDE_ASM("asm/nonmatchings/800", func_8002E79C);

INCLUDE_ASM("asm/nonmatchings/800", func_8002E818);

INCLUDE_ASM("asm/nonmatchings/800", func_8002E8DC);

INCLUDE_ASM("asm/nonmatchings/800", func_8002E94C);

INCLUDE_ASM("asm/nonmatchings/800", func_8002EA10);


extern u16   D_800A4E8E;
extern s16   D_800A4E86;
extern void func_80038308(s16 a0);

void func_8002EAB0(void) {
    register u16 *s0 __asm__("$16");
    u16 v0;

    s0 = &D_800A4E8E;
    v0 = *s0;
    if ((v0 & 0x10) != 0) {
        func_80038308(D_800A4E86);
        v0 = *s0;
        v0 = (v0 | 0x9) & 0xFFEF;
        *s0 = v0;
    }
}

INCLUDE_ASM("asm/nonmatchings/800", func_8002EB10);


extern void func_80036D58(int arg0);
extern void func_80038308(s16 arg0);
extern u16 D_800A4E8E;
extern s16 D_800A4E86;

void func_8002EBAC(void) {
    u16 v0;

    func_80036D58(0);

    if (D_800A4E8E & 0x10) {
        func_80038308(D_800A4E86);

        v0 = D_800A4E8E;
        v0 |= 0x9;
        v0 &= 0xFFEF;
        D_800A4E8E = v0;
    }
}


extern u16 D_800A4E8E;
extern s16 D_800A4E86;
extern u16 D_800A4E8C;
extern u16 D_800A4F20;
extern u16 D_800A4F22;
extern u16 D_800A4E8A;
extern u16 D_80068B66[][8];
extern u16 D_800A4EA2;
extern s16 D_800A4E9A;
extern u16 D_800A4EA0;

extern s32 func_8003836C(s32 a0);
extern void func_800383A4(s16 a0);
extern void func_800384A8(s16 a0);
extern void func_800385C0(s16 a0);

void func_8002EC10(void) {
    u16 v0;
    s16 *s0;

    D_800A4F20 = 0;
    D_800A4F22 = 0;
    D_800A4E8A = 0;

    if (D_800A4E8E & 4) {
        if ((s16)func_8003836C(D_800A4E86) && (D_80068B66[D_800A4E8C][0] & 1)) {
            if (D_800A4EA2 & 4) {
                func_800385C0(D_800A4E9A);
                D_800A4EA2 &= 0xFEE8;
            }

            func_800383A4(D_800A4E86);

            v0 = D_800A4E8E;
            D_800A4E8E = v0 & 0xFFFD;
            D_800A4EA2 = v0 & 0xFFFD;
            D_800A4E9A = D_800A4E86;
            D_800A4EA0 = D_800A4E8C;
            D_800A4E8E = v0 & 0xFEF9;
            return;
        }

        s0 = &D_800A4E86;
        if ((s16)func_8003836C(*s0)) {
            func_800384A8(*s0);
        }

        D_800A4E8E &= 0xFEE8;
        func_800385C0(*s0);
    }
}


extern void func_8002EC10(void);
extern void func_800385C0(s16);
extern u16 D_800A4EA2;
extern s16 D_800A4E9A;

void func_8002ED90(void) {
    u16* ptr;

    func_8002EC10();

    ptr = &D_800A4EA2;
    if (*ptr & 0x4) {
        func_800385C0(D_800A4E9A);
        *ptr = 0;
    }
}

INCLUDE_ASM("asm/nonmatchings/800", func_8002EDE4);

INCLUDE_ASM("asm/nonmatchings/800", func_8002EE64);


extern void func_80036EE8(void);
extern void func_8002EC10(void);

void func_8002EE90(void) {
    func_80036EE8();
    func_8002EC10();
}

INCLUDE_ASM("asm/nonmatchings/800", func_8002EEB8);

INCLUDE_ASM("asm/nonmatchings/800", func_8002EED8);


extern void func_80034844(void);
extern void func_80031B7C(void);

void func_8002EFD0(void)
{
    func_80034844();
    func_80031B7C();
}


extern s32 D_800A2B98;
extern s32 D_800C7D20;

void func_8002EFF8(s32 a0, s32 a1)
{
    register s32 v0 __asm__("$2");
    register s32 v1 __asm__("$3");
    register s32 a0_tmp __asm__("$4");

    v0 = 1;

    if (a0 == v0) {
        v0 = ~a1;
        v1 = D_800A2B98;
        a0_tmp = D_800C7D20;
        v1 = v1 & v0;
        a0_tmp = a0_tmp | a1;
        D_800A2B98 = v1;
        D_800C7D20 = a0_tmp;
    } else {
        v0 = ~a1;
        v1 = D_800C7D20;
        a0_tmp = D_800A2B98;
        v1 = v1 & v0;
        a0_tmp = a0_tmp | a1;
        D_800C7D20 = v1;
        D_800A2B98 = a0_tmp;
    }
}


extern s32 D_800A2BA0;
extern s32 D_800C7D2C;

void func_8002F064(s32 a0, s32 a1) {
    register s32 v0 __asm__("$2");
    register s32 v1 __asm__("$3");
    register s32 out_a0 __asm__("$4");

    if (a0 == 1) {
        v0 = ~a1;
        v1 = D_800A2BA0;
        out_a0 = D_800C7D2C;
        v1 = v1 & v0;
        out_a0 = out_a0 | a1;
        D_800A2BA0 = v1;
        D_800C7D2C = out_a0;
    } else {
        v0 = ~a1;
        v1 = D_800C7D2C;
        out_a0 = D_800A2BA0;
        v1 = v1 & v0;
        out_a0 = out_a0 | a1;
        D_800C7D2C = v1;
        D_800A2BA0 = out_a0;
    }
}

INCLUDE_ASM("asm/nonmatchings/800", func_8002F0D0);


extern s32 D_800A64B0;

void *func_8002F0F4(void) {
    s32 *ptr = (s32 *)&D_800A64B0;
    s32 i = 0;

    while (i < 8) {
        s32 val = *ptr;
        if (val == 0) {
            return (void *)ptr;
        }
        i++;
        ptr = (s32 *)((s32)ptr + 0xC);
    }

    return 0;
}

INCLUDE_ASM("asm/nonmatchings/800", func_8002F12C);

INCLUDE_ASM("asm/nonmatchings/800", func_8002F150);

INCLUDE_ASM("asm/nonmatchings/800", func_8002F1CC);

INCLUDE_ASM("asm/nonmatchings/800", func_8002F248);

INCLUDE_ASM("asm/nonmatchings/800", func_8002F4E4);

INCLUDE_ASM("asm/nonmatchings/800", func_8002F5C8);


extern s16 D_800A4EF0;
extern void func_80031D70(void);

void func_8002F620(void) {
    D_800A4EF0 = 0;
    func_80031D70();
}

extern s16 D_800A4EF0;
s16 func_8002F648(void) {
    return D_800A4EF0;
}

INCLUDE_ASM("asm/nonmatchings/800", func_8002F658);

INCLUDE_ASM("asm/nonmatchings/800", func_8002F67C);

INCLUDE_ASM("asm/nonmatchings/800", func_8002F714);

INCLUDE_ASM("asm/nonmatchings/800", func_8002F80C);

INCLUDE_ASM("asm/nonmatchings/800", func_8002FA3C);


extern s16 D_800A46CC;

void func_8002FAE0(void) {
    D_800A46CC = 0;
    func_8002C8BC();
}

INCLUDE_ASM("asm/nonmatchings/800", func_8002FB08);

INCLUDE_ASM("asm/nonmatchings/800", func_8002FC64);

INCLUDE_ASM("asm/nonmatchings/800", func_8002FD14);

INCLUDE_ASM("asm/nonmatchings/800", func_8002FDC8);

INCLUDE_ASM("asm/nonmatchings/800", func_8002FDE8);

INCLUDE_ASM("asm/nonmatchings/800", func_8002FF0C);

INCLUDE_ASM("asm/nonmatchings/800", func_800301A4);

INCLUDE_ASM("asm/nonmatchings/800", func_800301C8);

INCLUDE_ASM("asm/nonmatchings/800", func_80030470);

INCLUDE_ASM("asm/nonmatchings/800", func_800304C8);

INCLUDE_ASM("asm/nonmatchings/800", func_80030538);

INCLUDE_ASM("asm/nonmatchings/800", func_80030634);

INCLUDE_ASM("asm/nonmatchings/800", func_80030730);

INCLUDE_ASM("asm/nonmatchings/800", func_80030A14);

INCLUDE_ASM("asm/nonmatchings/800", func_80030CA4);

INCLUDE_ASM("asm/nonmatchings/800", func_80030D80);

INCLUDE_ASM("asm/nonmatchings/800", func_80030F80);

INCLUDE_ASM("asm/nonmatchings/800", func_800314DC);

INCLUDE_ASM("asm/nonmatchings/800", func_800316F8);

INCLUDE_ASM("asm/nonmatchings/800", func_80031988);

INCLUDE_ASM("asm/nonmatchings/800", func_80031A98);


extern u8 D_800A49D2[];

void func_80031B7C() {
    register s32 a0 asm("$4") = 0;
    register u8 a2 asm("$6") = 1;
    register u16 a1 asm("$5") = 0x7FFF;
    register u8 *v1 asm("$3");

    v1 = D_800A49D2;

    do {
        if (v1[4] && !v1[2] && v1[3]) {
            v1[2] = a2;
            *(u16 *)v1 = a1;
        }
        v1 += 0x54;
        a0++;
    } while (a0 < 8);
}

INCLUDE_ASM("asm/nonmatchings/800", func_80031BE0);

INCLUDE_ASM("asm/nonmatchings/800", func_80031CC8);

INCLUDE_ASM("asm/nonmatchings/800", func_80031D70);

INCLUDE_ASM("asm/nonmatchings/800", func_80031DEC);

INCLUDE_ASM("asm/nonmatchings/800", func_80031E94);

INCLUDE_ASM("asm/nonmatchings/800", func_80031F14);

INCLUDE_ASM("asm/nonmatchings/800", func_80031FC8);


/* 0x14-byte record, indexed by p[3]. D_80068304 and D_800A4EE8->unk14 are both
 * arrays of pointers to arrays of these. */
typedef struct Rec14 {
    /* 0x00 */ u16 unk00;
    /* 0x02 */ u16 unk02;
    /* 0x04 */ u32 unk04;
    /* 0x08 */ u32 unk08;
    /* 0x0C */ u16 unk0C;
    /* 0x0E */ u16 unk0E;
    /* 0x10 */ u32 unk10;
} Rec14; /* 0x14 */

/* slot record inside D_800A46E8 (stride 0x54) */
typedef struct Slot54 {
    /* 0x00 */ s16 unk00;
    /* 0x02 */ s16 unk02;
    /* 0x04 */ s16 unk04;
    /* 0x06 */ s16 unk06;
    /* 0x08 */ u16 unk08;
    /* 0x0A */ s8  unk0A;
} Slot54;

typedef struct Owner4EE8 {
    /* 0x00 */ u8 pad00[0x14];
    /* 0x14 */ Rec14 **unk14;
} Owner4EE8;

extern Rec14 *D_80068304[];
extern Owner4EE8 *D_800A4EE8;
extern s16 D_800A4EF0;
extern u16 D_800A46E8[];
extern s8 D_800A4F17;

extern s32 func_800331D4(s32);
extern s32 func_8003310C(s32);
extern void func_800335B8(s32, s32);
extern void func_8003324C(s32);
extern void func_80032A74(Slot54 *, s32, Rec14 *, s32);

s32 func_80032048(u32 arg0, u8 *p, u32 flags) {
    Rec14 *rec;
    Slot54 *e;
    s32 idx;
    s32 ret;
    u32 x;
    u32 y;
    u32 v;
    u8 old;
    u8 b1;
    u8 b2;
    u32 b3;
    u32 b0;

    y = arg0 >> 16;
    b1 = p[1];
    b2 = p[2];
    b3 = p[3];

    if (b1 == 0) {
        rec = &D_80068304[b2][b3];
    } else {
        if (D_800A4EF0 != b1) {
            return 0;
        }
        if (D_800A4EE8 == 0) {
            return 0;
        }
        rec = D_800A4EE8->unk14[b2];
        rec += b3;
    }

    old = *(u8 *)&D_800A4F17;
    *(u8 *)&D_800A4F17 = 1;

    ret = 0;
    v = rec->unk00;
    if ((u16)flags == 0xFFFF) {
        flags = 0;
        x = (u16)y;
        y = 0;
    } else {
        x = arg0;
    }

    idx = func_800331D4(x);
    if (idx == 0) {
        if (flags & 0x4000) {
            if ((flags & 0x3000) == 0) {
                goto done;
            }
        } else if (flags & 0x1000) {
            if ((flags & 0x7F) < 0x30) {
                v >>= 1;
            }
        }
        idx = func_8003310C(v);
        if (idx == 0) {
            goto done;
        }
        ret = idx;
        idx = ret - 1;
        e = (Slot54 *)((u8 *)D_800A46E8 + idx * 0x54);
    } else {
        if (flags & 0x4000) {
            func_800335B8(idx - 1, (u16)flags);
            goto done;
        }
        idx--;
        e = (Slot54 *)((u8 *)D_800A46E8 + idx * 0x54);
        if (e->unk08 != 0) {
            goto done;
        }
        ret = idx + 1;
        func_8003324C((u16)idx);
    }

    b0 = p[0];
    e->unk04 = x;
    e->unk06 = y;
    e->unk02 = v;
    e->unk00 = (b0 & 0xC0) | 1;
    e->unk08 = rec->unk0C;
    e->unk0A = 5;
    func_80032A74(e, idx, rec, (u16)flags);

done:
    *(u8 *)&D_800A4F17 = old;
    return ret;
}

INCLUDE_ASM("asm/nonmatchings/800", func_800322A8);

INCLUDE_ASM("asm/nonmatchings/800", func_800324A4);

INCLUDE_ASM("asm/nonmatchings/800", func_80032774);

INCLUDE_ASM("asm/nonmatchings/800", func_80032A74);

INCLUDE_ASM("asm/nonmatchings/800", func_8003310C);

INCLUDE_ASM("asm/nonmatchings/800", func_800331D4);

INCLUDE_ASM("asm/nonmatchings/800", func_8003324C);

INCLUDE_ASM("asm/nonmatchings/800", func_80033324);

INCLUDE_ASM("asm/nonmatchings/800", func_80033398);

INCLUDE_ASM("asm/nonmatchings/800", func_8003350C);

INCLUDE_ASM("asm/nonmatchings/800", func_800335B8);

INCLUDE_ASM("asm/nonmatchings/800", func_800336A8);

INCLUDE_ASM("asm/nonmatchings/800", func_8003388C);

INCLUDE_ASM("asm/nonmatchings/800", func_800342E8);

INCLUDE_ASM("asm/nonmatchings/800", func_80034314);

INCLUDE_ASM("asm/nonmatchings/800", func_80034650);

INCLUDE_ASM("asm/nonmatchings/800", func_800346D0);

INCLUDE_ASM("asm/nonmatchings/800", func_800347C8);


extern u16 D_800A46E8[];

void func_80034844(void)
{
    register u8 *a0 __asm__("$4") = (u8 *)D_800A46E8;
    register int a1 __asm__("$5") = 0;
    register int t0 __asm__("$8") = 0x5;
    register int a3 __asm__("$7") = 0x1;
    register int a2 __asm__("$6") = 0x220;
    register u8 *v1 __asm__("$3") = (u8 *)D_800A46E8 + 0x1A;

    while (a1 < 8) {
        if (*(u16 *)a0 == t0) {
            u8 b = *(u8 *)(v1 + 0x1D);
            if ((b & 0x2) == 0) {
                *(u8 *)(v1 - 0x4) = a3;
                *(u16 *)v1 = a2;
            }
        }
        a1++;
        v1 += 0x54;
        a0 += 0x54;
    }
}

INCLUDE_ASM("asm/nonmatchings/800", func_800348A8);

INCLUDE_ASM("asm/nonmatchings/800", func_8003491C);


extern s8 D_800A4F17;

void func_80034A54(s32 a0) {
    s32 self = a0;
    u8 v0 = *(u8 *)(self + 0x37);

    if ((v0 & 0x1) != 0) {
        s8 *p = &D_800A4F17;
        s8 old = *p;
        *p = 1;
        *(u8 *)(self + 0x32) = 1;
        *(s16 *)(self + 0x2E) = 0x3FF;
        *(s16 *)(self + 0x30) = 0xFFF;
        *p = old;
    }
}


extern s8 D_800A4F17;

void func_80034A9C(void *a0) {
    register void *a1 __asm__("$5") = a0;
    u8 *v1;
    u8 old;

    if (*(u16 *)((u8 *)a1 + 0x30) == 0x3FFF) {
        return;
    }
    v1 = (u8 *)&D_800A4F17;
    old = *v1;
    *v1 = 1;
    *(s8 *)((u8 *)a1 + 0x32) = 1;
    *(s16 *)((u8 *)a1 + 0x2E) = 0x3FF;
    *(s16 *)((u8 *)a1 + 0x30) = 0x3FFF;
    *v1 = old;
}


extern s8 D_800A4F17;

void func_80034AE0(void *a0)
{
    s8 *v1;
    s8 orig;

    v1 = &D_800A4F17;
    orig = *v1;
    *v1 = 1;
    *(s8 *)(a0 + 0x2A) = 1;
    *(s16 *)(a0 + 0x26) = 0x3FF;
    *(s16 *)(a0 + 0x28) = 0;
    *v1 = orig;
}


extern s8 D_800A4F17;

void func_80034B0C(s32 a0) {
    s8 *p = &D_800A4F17;
    s8 old = *p;
    *p = 1;
    *(u8 *)(a0 + 0x2A) = 1;
    *(s16 *)(a0 + 0x26) = 0x3FF;
    *(s16 *)(a0 + 0x28) = 0x3FFF;
    *p = old;
}

INCLUDE_ASM("asm/nonmatchings/800", func_80034B3C);

extern s32 D_8006AEF8;
extern s32 D_8006AEFC;
extern u8 D_80076214;
extern u8 D_8007620C;
/* CD read-queue status: head==tail (D_8006AEF8/FC equal) => idle; flags D_80076214 (a
 * pending/error byte) and D_8007620C (bit7/bit5) classify the busy/result state.
 * Returns 0=idle done, 8=had pending, 2/4/1=busy variants. */
s32 CdQueueBusy(void) {
    if (D_8006AEF8 != D_8006AEFC) {
        if (D_80076214 == 0) {
            if (D_8007620C & 0x80) {
                return 2;
            }
            if (D_8007620C & 0x20) {
                return 4;
            }
            return 1;
        }
    } else {
        D_8007620C = 0;
        if (D_80076214 == 0) {
            return 0;
        }
    }
    D_80076214 = 0;
    return 8;
}

INCLUDE_ASM("asm/nonmatchings/800", func_80034C24);

INCLUDE_ASM("asm/nonmatchings/800", func_80034CF0);

INCLUDE_ASM("asm/nonmatchings/800", func_80034DFC);


extern u8 D_8006AEF5;
extern s32 D_8006AEF8;
extern s32 D_8006AEFC;
extern u8 D_80076118[];
extern u8 D_80076138[];
extern s32 D_80076114;
extern u8 D_8007620C;

void func_8003500C(void) {
    if (D_8006AEF5 != 0) {
        return;
    }

    if (D_8006AEFC != D_8006AEF8) {
        s32 idx = D_8006AEF8;
        u8 *self = D_80076118 + idx * 0x30;

        if (self[0] != 0) {
            register s32 (*fn8)(void *) __asm__("$3") = *(s32 (**)(void *))(self + 8);
            register s32 type __asm__("$2") = self[4];

            D_80076114 = type;
            if (fn8(self) == 0) {
                return;
            }

            {
                register s32 (*fn1C)(s32) __asm__("$6") = *(s32 (**)(s32))(self + 0x1C);
                register s32 type2 __asm__("$5") = self[4];

                D_80076114 = type2;
                if (fn1C != NULL) {
                    fn1C(*(s32 *)(D_80076138 + D_8006AEF8 * 0x30));
                }
            }

            self[0] = 0;
            self[1] = 0;
            D_8006AEF8 += 1;
            if ((u32)D_8006AEF8 >= 4) {
                D_8006AEF8 = 0;
            }
            if (D_8006AEF8 == D_8006AEFC) {
                D_80076114 = 0;
            }
            return;
        } else {
            if (self[1] != 0 && self[7] == 0) {
                s32 (*fn24)(void *) = *(s32 (**)(void *))(self + 0x24);

                if (fn24 != NULL) {
                    fn24(self);
                }
                if (self[2] != 0) {
                    return;
                }
            }

            self[1] = 0;
            D_8006AEF8 += 1;
            if ((u32)D_8006AEF8 >= 4) {
                D_8006AEF8 = 0;
            }
            if (D_8006AEF8 == D_8006AEFC) {
                D_80076114 = 0;
            } else {
                D_80076114 = 1;
            }
            return;
        }
    } else {
        D_8007620C = 0;
    }
}

INCLUDE_ASM("asm/nonmatchings/800", func_800351E8);


extern s32 D_80076218;

extern void func_8003C498(s32);
extern void SpuWrite(s32, s32);

void func_80035210(s32 a0, s32 a1)
{
    register s32 v1 __asm__("$3");

    v1 = D_80076218;
    func_8003C498(v1);
    SpuWrite(a0, a1);
    v1 = D_80076218;
    D_80076218 = v1 + a1;
}

INCLUDE_ASM("asm/nonmatchings/800", func_80035270);

INCLUDE_ASM("asm/nonmatchings/800", func_800359B0);

INCLUDE_ASM("asm/nonmatchings/800", func_80035C4C);

INCLUDE_ASM("asm/nonmatchings/800", func_8003602C);

INCLUDE_ASM("asm/nonmatchings/800", func_80036130);

INCLUDE_ASM("asm/nonmatchings/800", func_800361CC);


extern void *CdReadyCallback(void *func);
extern void *streamLoad_savedReadyCB;
extern u8    streamLoad_cbActive;

void func_8003621C(void) {
    if (streamLoad_cbActive != 0) {
        CdReadyCallback(streamLoad_savedReadyCB);
        streamLoad_savedReadyCB = 0;
        streamLoad_cbActive = 0;
    }
}

INCLUDE_ASM("asm/nonmatchings/800", func_80036260);

#ifdef NON_MATCHING
extern int   CdControl(u8 com, u8 *param, u8 *result);
extern int   CdSync(int mode, u8 *result);
extern u32   CdMode(void);
extern void  CdFlush(void);
extern void *CdReadyCallback(void *func);
extern void  func_800377D8(void);   /* this loader's CdlReadN ready-callback */
extern void  func_80036260(void);   /* sub-handler passed to func_80037CD8 */
extern void  func_8002EC10(void);
extern void  func_80037334(void);
extern void  func_80037358(int posInt);
extern void  func_80037144(int idx);
extern int   func_80037CD8(void *arg);
extern int   func_8003750C(void);
extern int   func_800374CC(int *out);
extern int   func_8003775C(void);
extern void  func_80037D74(void);
extern void *func_80037368(int *out);

extern int   streamLoad_state;          /* 0x8006AF00 */
extern void *streamLoad_savedReadyCB;
extern u8    streamLoad_cbActive;
extern int   D_800A4F28;            /* tick / timeout counter */
extern int   D_800A4F2C;            /* CdMode-derived retry budget */
extern int   D_800A4F30;            /* remaining sub-stream repeat count (from param_3) */
extern int   D_800A4F34;            /* last sector position (stall detection) */
extern int   D_800A4F38;            /* end/abort flag */
extern int   D_800A6544;
extern u16   D_800A4E8E;            /* 16-bit status flags */
extern u8    D_8006AEF4;            /* 8-bit status flags */
extern u8    D_80068B60[];          /* per-resource descriptor table (0x10 stride) */

/* Second CD loader, DISTINCT from CdReadStateMachine: an 18-state machine (streamLoad_state) with
 * its OWN ready-callback (func_800377D8). Runs SetMode(0xA0)/SeekL/ReadN with retry + CdMode
 * handling, looping param_3 (D_800A4F30) times over sub-streams. Returns 0 = busy, 1 = done,
 * 2 = error/abort. Driven by ResourceLoadStateMachine. Provenance: static trace, Phase 3 T4 (fn id
 * verified; full semantics partial).
 * NON_MATCHING: faithful translation of the Ghidra decompile — logically faithful, not byte-verified. */
int StreamLoadStateMachine(int param_1, void *param_2, int param_3) {  /* param_2 is a CdlLOC* */
    short sVar1;
    int iVar4;
    u32 uVar2;
    char *pcVar3;
    u8 local_28[8];
    u8 local_20[8];
    int local_18;
    int local_14;

    sVar1 = *(short *)(D_80068B60 + (param_1 - 0x100) * 0x10);
    D_800A4F28++;
    switch (streamLoad_state) {
    case 0:
        D_800A4F38 = 0;
        D_800A6544 = 0;
        D_800A4F30 = param_3;
        func_8002EC10();
        streamLoad_state++;
        D_800A4E8E &= 0xFFDF;
        return 0;
    case 1:
        func_80037334();
        iVar4 = CdPosToInt((CdlLOC *)param_2);
        func_80037358(iVar4);
        func_80037144(sVar1);
        streamLoad_state++;
        /* fall through */
    case 2:
        local_14 = CdSync(1, local_20);
        if (local_14 != 5 && local_14 != 2) return 0;
        uVar2 = CdMode();
        D_800A4F2C = ((uVar2 & 0x80) == 0) ? 3 : 0;
        streamLoad_state++;
        /* fall through */
    case 3:
        local_28[0] = 0xA0;
        iVar4 = CdControl(0x0E, local_28, local_20);     /* CdlSetmode */
        if (iVar4 == 0) {
            if ((local_20[0] & 0x10) != 0) { func_80037334(); streamLoad_state = 0; return 2; }
            return 0;
        }
        D_800A4F28 = 0;
        streamLoad_state++;
        /* fall through */
    case 4:
        iVar4 = CdSync(1, local_20);
        if (iVar4 != 5) {
            if (iVar4 == 2) {
                streamLoad_state++;
                local_14 = 2;
            modeWait:
                if (D_800A4F2C != 0) { D_800A4F2C--; return 0; }
                streamLoad_state++;
                goto issueSeek;
            }
            if (D_800A4F28 < 0x3D) return 0;
        }
        streamLoad_state = 3;
        return 0;
    case 5:
        goto modeWait;
    case 6:
    issueSeek:
        iVar4 = func_80037CD8((void *)func_80036260);
        if (iVar4 == 0) return 0;
        streamLoad_state = 7;
        /* fall through */
    case 7:
        iVar4 = func_8003750C();
        if (iVar4 == 0) return 0;
        streamLoad_state++;
        /* fall through */
    case 8:
        local_14 = CdSync(1, local_20);
        if (local_14 != 5 && local_14 != 2) return 0;
        streamLoad_state++;
        /* fall through */
    case 9:
        D_800A4F28 = 0;
        iVar4 = CdControl(0x15, (u8 *)param_2, local_20);      /* CdlSeekL */
        if (iVar4 == 0) return 0;
        streamLoad_state++;
        /* fall through */
    case 10:
        local_14 = CdSync(1, local_20);
        if (local_14 == 5) {
            iVar4 = CdControl(0x01, (u8 *)0, local_20);        /* CdlNop */
            if (iVar4 == 0) { streamLoad_state = 9; return 0; }
            if ((local_20[0] & 0x10) != 0) {
                func_80037334();
                D_8006AEF4 &= 0xFD;
                streamLoad_state = 0;
                return 2;
            }
            streamLoad_state = 9;
            return 0;
        }
        if (local_14 != 2) {
            if (D_800A4F28 < 0x12D) return 0;
            CdFlush();
            streamLoad_state = 9;
            return 2;
        }
        streamLoad_state++;
        local_14 = 2;
        /* fall through */
    case 0xB:
        D_800A4F28 = 0;
        iVar4 = CdControl(0x06, (u8 *)param_2, local_20);      /* CdlReadN */
        if (iVar4 != 0) {
            if (streamLoad_cbActive == 0)
                streamLoad_savedReadyCB = CdReadyCallback((void *)func_800377D8);
            else
                CdReadyCallback((void *)func_800377D8);
            streamLoad_state++;
            streamLoad_cbActive = 1;
            return 0;
        }
        if ((local_20[0] & 0x10) == 0) return 0;
        D_8006AEF4 &= 0xFD;
        func_80037334();
        streamLoad_state = 0;
        return 2;
    case 0xC:
        iVar4 = func_800374CC(&local_18);
        if (iVar4 == 0) {
            if (local_18 != D_800A4F34) { D_800A4F34 = local_18; D_800A4F28 = 0; }
            if (D_800A4F28 > 300) {
                if (streamLoad_cbActive != 0) {
                    CdReadyCallback(streamLoad_savedReadyCB);
                    streamLoad_savedReadyCB = 0;
                    streamLoad_cbActive = 0;
                }
                streamLoad_state++;
            }
            return 0;
        }
        if (streamLoad_cbActive != 0) {
            CdReadyCallback(streamLoad_savedReadyCB);
            streamLoad_savedReadyCB = 0;
            streamLoad_cbActive = 0;
        }
        streamLoad_state++;
        /* fall through */
    case 0xD:
        iVar4 = func_8003775C();
        if (iVar4 == 0) return 0;
        func_80037D74();
        streamLoad_state++;
        return 0;
    case 0xE:
        pcVar3 = (char *)func_80037368(&local_14);
        if (local_14 != 1) { streamLoad_state = 0x11; return 0; }
        if (*pcVar3 != 1) {
            if (*pcVar3 == 2) { streamLoad_state = 0x11; D_800A4F38 = 1; return 0; }
            if (D_800A4F30 != 0) {
                if (D_800A4F30 - 1 == 0) { streamLoad_state = 0x11; D_800A4F30 = 0; return 0; }
                streamLoad_state = 1;
                D_800A4F30--;
                return 0;
            }
            streamLoad_state = 1;
            return 0;
        }
        streamLoad_state++;
        break;                                                 /* -> CdlPause (post-switch) */
    case 0xF:
        break;                                                 /* -> CdlPause (post-switch) */
    case 0x10:
        iVar4 = CdSync(1, local_20);
        if (iVar4 != 5 && iVar4 != 2) return 0;
        if (D_800A4F38 == 0) { streamLoad_state = 0; return 1; }
        streamLoad_state = 0;
        D_800A4F38 = 0;
        return 2;
    case 0x11:
        iVar4 = CdControl(0x09, (u8 *)0, local_20);            /* CdlPause */
        if (iVar4 != 0) { streamLoad_state = 0x10; return 0; }
        return 0;
    default:
        return 0;
    }
    /* shared tail for states 0xE (advance) and 0xF: pause, then wait for it */
    iVar4 = CdControl(0x09, (u8 *)0, local_20);                /* CdlPause */
    if (iVar4 != 0) { streamLoad_state++; return 0; }
    if ((local_20[0] & 0x10) != 0) { streamLoad_state = 0; return 1; }
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/800", StreamLoadStateMachine);
#endif

INCLUDE_ASM("asm/nonmatchings/800", func_80036AF8);

INCLUDE_ASM("asm/nonmatchings/800", func_80036D24);

INCLUDE_ASM("asm/nonmatchings/800", func_80036D58);


extern u8 D_800A4F1A;
extern s32 D_800C6D28;
extern void func_80036F18(void);

void func_80036EB4(void) {
    if (!D_800A4F1A) {
        func_80036F18();
        D_800C6D28 = 0;
    }
}


extern u8 D_800A4F1A;
extern s32 D_800C6D28;
extern void func_80036F18(void);

void func_80036EE8(void) {
    func_80036F18();
    D_800C6D28 = 0;
    D_800A4F1A = 0;
}

INCLUDE_ASM("asm/nonmatchings/800", func_80036F18);

INCLUDE_ASM("asm/nonmatchings/800", func_80036F98);

INCLUDE_ASM("asm/nonmatchings/800", func_80036FB0);

CLEAR_TBL40(func_80037004)  /* dedup I0: shared body (src/shared/clearTbl40.h) */

INCLUDE_ASM("asm/nonmatchings/800", func_80037028);

INCLUDE_ASM("asm/nonmatchings/800", func_80037144);

CLEAR_TBL40(func_80037334)  /* dedup I0: shared body (src/shared/clearTbl40.h) */

extern s32 D_8007623C;
void func_80037358(int posInt) {
    D_8007623C = posInt;
}


extern u8 D_80076251;   /* Law 2: exact form from src/shared/clearTbl40.h */
extern u8 D_80076220[];
extern u8 D_80076250[];

void *func_80037368(int *out) {
    int count = 0;
    u8 *ptr = D_80076220;
    int i;

    for (i = 0; i < 0x50; i += 0x10) {
        *ptr = 0;
        ptr++;

        if ((&D_80076251)[i] != 0) {
            D_80076220[count] = D_80076250[i];
            count++;
        }
    }

    *out = count;
    return D_80076220;
}

INCLUDE_ASM("asm/nonmatchings/800", func_800373D0);

INCLUDE_ASM("asm/nonmatchings/800", func_800374CC);


typedef struct {
    s16 unk00;
    s16 unk02;
    s16 unk04;
    s16 unk06;
    s16 unk08;
    s16 unk0A;
    s16 unk0C;
    s16 unk0E;
    u8  unk10;
    u8  unk11;
    u8  unk12;
    u8  unk13;
    s32 unk14;
} Rsc24;                       /* 0x18 */

typedef struct {
    s32 unk00;
    u8  unk04;
    u8  unk05;
    u8  unk06;
    u8  unk07;
    u8  unk08;
    u8  unk09;
    u8  unk0A;
    u8  unk0B;
    s32 unk0C;
} Rsc16;                      /* 0x10 */

typedef struct {
    u8  unk00;
    u8  unk01[11];
} Rsc12;                      /* 0x0C */

extern s32  D_8007629C;
extern u8   D_8006AEF4;
extern u8   D_80076298;
extern Rsc16 D_80076248[];    /* .unk09 = D_80076251, .unk0A = D_80076252 */
extern Rsc12 D_80064D4A[];
extern Rsc24  D_800A4640[];
extern s16  D_800C5328[];
extern s16  D_800C532A[];

extern s32  func_8003C4F0(s32);
extern void func_800415A8(s32);
extern void func_80031A98(void);

s32 func_8003750C(void) {
    s32 i;
    s32 val;
    s32 k;
    s32 h;

    switch (D_8007629C) {
    case 0:
        if (D_8006AEF4 & 2) {
            return 0;
        }
        D_8006AEF4 |= 2;
        D_8007629C = 1;
        /* fallthrough */
    case 1:
        if (D_8006AEF4 & 1) {
            if (func_8003C4F0(0) == 0) {
                return 0;
            }
        }
        D_8007629C = D_8007629C + 1;
        /* fallthrough */
    case 2:
        for (i = 0; i < 5; i++) {
            if (D_80076248[i].unk09 == 0) {
                continue;
            }
            val = D_80076248[i].unk00;
            k = D_80076248[i].unk0A;
            if (val & 0x6000) {
                continue;
            }
            h = D_800A4640[k].unk04;
            if (h != 0 && h != D_80064D4A[val].unk00) {
                D_800C532A[D_800A4640[k].unk08 * 2] = -1;
                D_800A4640[k].unk04 = 0;
                D_800A4640[k].unk08 = 0;
            }
            if (D_800A4640[k].unk10 != 0) {
                continue;
            }
            D_800A4640[k].unk10 = 1;
            D_800C5328[D_800A4640[k].unk00 * 2] = -1;
            if (D_800A4640[i].unk02 >= 0) {
                func_800415A8(D_800A4640[i].unk02);
                D_800A4640[i].unk02 = -1;
            }
            func_80031A98();
        }
        D_8007629C = 0;
        D_80076298 = 0;
        return 1;
    default:
        return 0;
    }
}

INCLUDE_ASM("asm/nonmatchings/800", func_8003775C);

INCLUDE_ASM("asm/nonmatchings/800", func_800377D8);

extern s32 D_800BA0F8;
void func_80037CC8(void) {
    D_800BA0F8 = 0;
}

INCLUDE_ASM("asm/nonmatchings/800", func_80037CD8);

INCLUDE_ASM("asm/nonmatchings/800", func_80037D74);

INCLUDE_ASM("asm/nonmatchings/800", func_80037D98);

INCLUDE_ASM("asm/nonmatchings/800", func_80037EA0);

INCLUDE_ASM("asm/nonmatchings/800", func_80037F3C);

INCLUDE_ASM("asm/nonmatchings/800", func_80037FC4);

INCLUDE_ASM("asm/nonmatchings/800", func_8003819C);


extern u8 D_800B9CF0[];

s32 func_800381E4(s32 a0, s32 a1) {
    s32 v0;

    a1 = (a1 << 16) >> 13;
    v0 = (a0 << 7) - a0;
    v0 = v0 << 2;
    a1 = a1 + v0;
    return D_800B9CF0[a1];
}

INCLUDE_ASM("asm/nonmatchings/800", func_80038210);

INCLUDE_ASM("asm/nonmatchings/800", func_80038308);

INCLUDE_ASM("asm/nonmatchings/800", func_8003834C);


extern u8 D_800B9ED3[];
extern u8 D_800B9ED2[];

s32 func_8003836C(s32 a0) {
    s32 index;
    u8 val;
    index = a0 * 127;
    index = index * 4;
    val = D_800B9ED3[index];
    if (val == 0) {
        return 0;
    }
    return D_800B9ED2[index];
}

INCLUDE_ASM("asm/nonmatchings/800", func_800383A4);

INCLUDE_ASM("asm/nonmatchings/800", func_800384A8);

INCLUDE_ASM("asm/nonmatchings/800", func_800385C0);


extern u8 D_800B9E92[];

void func_80038638(s32 a0, s32 a1) {
    u8 *ptr;
    s32 offset;
    offset = a0 * 127;
    offset = offset * 4;
    ptr = D_800B9E92 + offset;
    *(ptr + a1) |= 1;
}


extern u8 D_800B9E92[];

void func_80038668(s32 a0, s32 a1) {
    s32 offset = ((a0 << 7) - a0) << 2;
    char *baseptr = (char *)D_800B9E92 + offset;
    *(baseptr + a1) &= 0xFE;
}

INCLUDE_ASM("asm/nonmatchings/800", func_80038698);

INCLUDE_ASM("asm/nonmatchings/800", func_800387C0);

INCLUDE_ASM("asm/nonmatchings/800", func_80038838);

INCLUDE_ASM("asm/nonmatchings/800", func_800388E8);

INCLUDE_ASM("asm/nonmatchings/800", func_80038908);

INCLUDE_ASM("asm/nonmatchings/800", func_80038958);


extern u8 *D_800762B0;
extern u8 D_800762B4[];

s32 func_80038A00(void) {
    u8 *ptr1 = D_800762B0;
    u8 *ptr2 = D_800762B4;
    s32 i = 0;

    while (i < 0x10) {
        if (*ptr1 == 0x2 && *ptr2 == 0) {
            return i;
        }
        i++;
        ptr1++;
        ptr2++;
    }
    return -1;
}

INCLUDE_ASM("asm/nonmatchings/800", func_80038A58);

INCLUDE_ASM("asm/nonmatchings/800", func_80038FC4);

INCLUDE_ASM("asm/nonmatchings/800", func_80038FFC);

INCLUDE_ASM("asm/nonmatchings/800", func_8003916C);

INCLUDE_ASM("asm/nonmatchings/800", func_800391D4);

void func_80039300(void) {
}

INCLUDE_ASM("asm/nonmatchings/800", func_80039308);

INCLUDE_ASM("asm/nonmatchings/800", func_80039B20);

INCLUDE_ASM("asm/nonmatchings/800", func_80039C5C);

INCLUDE_ASM("asm/nonmatchings/800", func_80039C70);

INCLUDE_ASM("asm/nonmatchings/800", func_80039DEC);

INCLUDE_ASM("asm/nonmatchings/800", func_80039F14);

INCLUDE_ASM("asm/nonmatchings/800", func_80039F50);

INCLUDE_ASM("asm/nonmatchings/800", func_8003A098);

INCLUDE_ASM("asm/nonmatchings/800", func_8003A0D0);

INCLUDE_ASM("asm/nonmatchings/800", func_8003A0E4);


typedef struct {
    /* 0x000 */ u8 *ptr;
    /* 0x004 */ u8 pad_004[0x1D0 - 0x004];
    /* 0x1D0 */ s32 unk1D0;
    /* 0x1D4 */ u8 pad_1D4[0x1E4 - 0x1D4];
    /* 0x1E4 */ s16 unk1E4;
    /* 0x1E6 */ s16 unk1E6;
    /* 0x1E8 */ u8 pad_1E8[0x1F9 - 0x1E8];
    /* 0x1F9 */ u8 unk1F9;
} func_8003A234_Ctx;

void func_8003A234(func_8003A234_Ctx *a0) {
    u8 *a2 = a0->ptr;
    u8 v1;

    a0->ptr = a2 + 1;
    v1 = *a2;

    switch (v1) {
    case 0x20:
        a0->ptr = a2 + 3;
        break;

    case '/':
        a0->ptr = a2 + 2;
        a0->unk1F9 = 1;
        break;

    case 'Q':
        {
            register s32 num __asm__("$4");
            s32 den;
            s32 b3;
            s32 b4;
            s32 q;

            a0->ptr = a2 + 2;
            den = a2[1];
            if (den != 3) {
                a0->unk1F9 = 1;
                break;
            }
            num = 0x3938700;
            a0->ptr = a2 + 3;
            den = a2[2];
            a0->ptr = a2 + 4;
            b3 = a2[3];
            a0->ptr = a2 + 5;
            b4 = a2[4];
            den = den << 16;
            den += b3 << 8;
            den += b4;
            q = num / den;
            a0->unk1E4 = (s16)q;
            a0->unk1D0 = q * a0->unk1E6;
        }
        break;

    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 'T':
    case 0x58:
    case 0x59:
    case 0x7F:
        {
            register u8 *p __asm__("$3") = a0->ptr;
            u8 *np = p + 1;
            a0->ptr = np;
            {
                register s32 byte __asm__("$5") = p[0];
                a0->ptr = np + byte;
            }
        }
        break;

    case 0:
        a0->ptr = a2 + 2;
        {
            register s32 b1 __asm__("$5") = a2[1];
            if (b1 != 2) {
                a0->unk1F9 = 1;
                break;
            }
        }
        a0->ptr = a2 + 4;
        break;

    default:
        a0->unk1F9 = 1;
        break;
    }
}

INCLUDE_ASM("asm/nonmatchings/800", func_8003A3D8);

INCLUDE_ASM("asm/nonmatchings/800", func_8003A404);

INCLUDE_ASM("asm/nonmatchings/800", func_8003A424);
