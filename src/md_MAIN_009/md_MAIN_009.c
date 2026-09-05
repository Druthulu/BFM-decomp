#include "common.h"


extern void (*D_800CDD08[])(void);

void func_800CD384(void) {
    register s32 idx __asm__("$2");
    __asm__ __volatile__("" : : "r"(idx));
    D_800CDD08[idx]();
}


INCLUDE_RODATA("asm/md_MAIN_009/nonmatchings/md_MAIN_009", D_800CD348);

extern s32 func_8001B244(s32);
extern void func_8001AD38(const char*);
extern void func_800116A0(void);

extern s32 D_800CDD2C;
extern s32 D_800CDD34;

const char D_800CD34C[] = "C:\\TIMPACK\\OPDEMO0.PAT";

void func_800CD3B8(void) {
    if (func_8001B244(0x8E) == 0) {
        return;
    }

    func_8001AD38(D_800CD34C);
    D_800CDD2C = 0;
    D_800CDD34 = 0;
    func_800116A0();
}


extern s32 D_800CDD2C;
extern s32 D_800CDD34;

extern void func_800CD674(s32, s32, s32);
extern void func_800116A0(void);

void func_800CD408(void) {
    s32 a1 = D_800CDD2C;
    s32 a2 = D_800CDD34;
    func_800CD674(0, a1, a2);

    a2 = D_800CDD34;
    a2 += 8;
    D_800CDD34 = a2;

    if (a2 < 0x80) {
        // skip
    } else {
        func_800116A0();
    }
}


extern s32 D_800CDD2C;
extern s32 D_800CDD34;
extern void func_800CD674(s32, s32, s32);
extern void func_800116A0(void);

void func_800CD464(void) {
    func_800CD674(0, D_800CDD2C, D_800CDD34);
    D_800CDD2C--;
    if (D_800CDD2C >= -0x10F) {
        return;
    }
    D_800CDD2C = -0x110;
    func_800116A0();
}


extern s32 D_800CDD2C;
extern s32 D_800CDD34;

void func_800CD674(s32, s32, s32);
void func_800116A0(void);

void func_800CD4C8(void) {
    func_800CD674(0, D_800CDD2C, D_800CDD34);

    D_800CDD34 -= 8;
    if (D_800CDD34 <= 0) {
        func_800116A0();
    }
}


const u32 D_800CD364[] = { 0x545C3A43, 0x41504D49, 0x4F5C4B43, 0x4D454450, 0x502E314F, 0x65005441, 0x3C02800C, 0x9442AE04 };

/* func_8001AD38 is declared by the TU at file scope as (const char*) — spelled like the TU (§376) */
extern s32 D_800CDD34;
extern void func_800116A0(void);

void func_800CD520(void) {
    func_8001AD38((const char *)D_800CD364);
    D_800CDD34 = 0;
    func_800116A0();
}


extern s32 D_800CDD30;
extern s32 D_800CDD34;
extern void func_800CD92C(s32, s32, s32);
extern void func_800116A0(void);

void func_800CD558(void) {
    func_800CD92C(-0x400, 0, D_800CDD34);
    D_800CDD30 = -0x340;
    D_800CDD34 += 8;
    if (D_800CDD34 >= 0x80) {
        func_800116A0();
    }
}


extern s32 D_800CDD30;
extern s32 D_800CDD34;
extern void func_800CD92C(s32 a0, s32 a1, s32 a2);
extern void func_800116A0(void);

void func_800CD5B8(void) {
    func_800CD92C(D_800CDD30, 0, D_800CDD34);
    D_800CDD30++;
    if (D_800CDD30 >= 0x141) {
        func_800116A0();
    }
}


extern s32 D_800CDD30;
extern s32 D_800CDD34;

void func_800CD92C(s32, s32, s32);
void func_800116A0(void);

void func_800CD614(void) {
    s32 v0;
    
    func_800CD92C(D_800CDD30, 0, D_800CDD34);
    v0 = D_800CDD34 - 8;
    D_800CDD34 = v0;
    if (v0 > 0) {
        return;
    }
    func_800116A0();
}


void func_800CD66C(void) {
}

/* func_800CD674 - md_MAIN_009 (-O2). Builds four 0x18-byte "SPRT + own tpage"
 * primitives (a 2x2 grid of 0xA0 x 0x100 tiles, len = 5 words) at the
 * D_800A71D0 prim-buffer cursor and open-codes the PSY-Q addPrim() P_TAG
 * 24-bit RMW pair onto OT word [0] of the frame's table
 * (D_800ABA24 + D_800BAE22 * 0x4000), then republishes the advanced cursor.
 * Same family as boot's func_8001212C (-O0) and src/800.c func_80016450 (-O2).
 *
 * LEVERS (each byte-measured by removing it and re-scoring):
 *  1. THE FIELD STORES MUST BE NON-STRUCT LVALUES.  gcc-2.7.2 true_dependence
 *     drops the store->load edge when the store is MEM_IN_STRUCT_P with a
 *     varying address and mode != QImode, so with a `Sprt24 *p` struct the five
 *     `sh` stores (clut/x0/y0/w/h) SINK past the `lhu D_800BAE22` while the
 *     `sb`/`sw` ones stay -- the target's block is pure source order.  Writing
 *     every field through `*(T *)(p + off)` restores the false edge for all 13
 *     and the whole store block lands exactly.  (struct form: 102 mismatched;
 *     flat form: 6.)  Cf. cookbook 340 -- the alias oracle chooses the order.
 *  2. `p->r0 = p->g0 = p->b0 = c` chained: emits 0xA, 0x9, 0x8 (descending).
 *  3. `y + 0x100` INLINE for prims 3/4, NOT `y += 0x100`: the accumulate form
 *     gives a1's def a longer chain and sched2 hoists `addiu a1,-0x78` to the
 *     head of the prologue (16 mismatched -> 7).
 *  4. HALF1 inlines the OT address (folded lui/%lo in prim 1, register form
 *     after cse binds &D_800ABA24 in $t2); HALF2 binds it to `ot` (needed
 *     twice) -- the 800.c-lever-3 hybrid.  Binding both halves costs the
 *     $t2 materialisation; inlining both costs 3 ins/prim.
 *  5. `otv = *ot;` SPLITS the half-2 RMW so the OT read precedes the
 *     `D_800A71D0 = p` publish and the OT write follows it -- that is what puts
 *     `lui $at/sw $v0,%lo(D_800A71D0)` in the last `lw`'s shadow (7 -> 2).
 *  6. Pins: $t2/$t3 mask order needs m24/mff pinned ($9/$11); `ot` pinned adds
 *     the 5th callee-saved register (unpinned = 172 ins, frame 0x18 not 0x20);
 *     `pm` ($t0) holds prims 1-2's masked-p across prim 2's store block.
 *
 *  7. THE $a3/$t1 SPLIT OF PRIMS 3/4's MASKED-p (closed 2 -> MATCH, P32 T5x):
 *     the target's prim-4 mask lands in $t1 = m24's own register, which
 *     local-alloc hands out ONLY through qty_phys_sugg (local-alloc.c
 *     combine_regs:1806-1817): a hard reg appearing as an input of the insn
 *     that SETS a pseudo is recorded as that pseudo's suggestion and tried
 *     first (block_alloc:1470-1477, before the priority-ordered pass) -- it
 *     wins only if the hard reg is free over the qty's whole range, i.e. the
 *     pseudo must be BORN at the `and` where $9 dies.  A pseudo shared by
 *     prims 3 and 4 "dies in 2 places" -> local_alloc:471 excludes it
 *     (reg_n_deaths != 1) -> global-alloc, where it conflicts with 9 -> $a3
 *     for both (the old closeness-2 state).  So prim 4's `pm2` must be a
 *     fresh single-death pseudo.  BUT giving prim 3 a fresh single-SET
 *     pseudo too regresses to 31: sched.c adjust_priority (2511-2545) boosts
 *     a ready `birthing_insn_p` SET (dest live, reg_n_sets == 1) to
 *     max_priority, so the backward list scheduler glues prim 3's `and` to
 *     its `or`; the `and` no longer fills the load-delay gap after prim 3's
 *     second `lhu`, `ori $s1,0x97` takes that gap, `lui $s1` the next, and
 *     `ori $s4,0x96` the next -- the whole prologue/prim-2 cascade.  The fix
 *     is a SECOND SET of `pm3` that flow cannot delete and that costs zero
 *     bytes: the trailing `__asm__ volatile("" : "=r"(pm3))` (REG_UNUSED
 *     output, emits only #APP/#NO_APP after the last `sw`).  reg_n_sets
 *     becomes 2 (no boost, the `and` keeps the gap) and pm3 goes to
 *     global-alloc -> $a3 like before; prim 4's `pm2` stays single-set and is
 *     born at the `and` -> local qty with suggestion 9 -> $t1.  Re-setting
 *     pm2 in the asm instead is WRONG (the volatile asm "uses and clobbers
 *     all hard registers", so 9 is live again over the extended qty and the
 *     mask falls to $a1: v5/v6 measured 2 with $a1).
 *
 *   Levers measured INERT by the T3 agent (do not repeat): statement order
 *   for x/y/tpr/pm (36 positions), zero-byte fences at all 70 statement
 *   slots, re-ties on p/y/c/tpr/m24/mff, pm2 declared plain/register/pinned
 *   $4/$6/$7/$9, `ot` pinned to 13 different registers, arg types
 *   s16/s32/u8, `p = p + 0x18` vs `p += 0x18`, x2/y2 explicit temps,
 *   D_800A71D0 published as `p + 0x18` / before the last OT store, and
 *   -fno-schedule-insns[2] attribution.  S83 hand probes: three fresh-temp
 *   shapes for prim 4 alone (31/44/44), permuter_ils plateau at the pair.
 */

extern u8 *D_800A71D0;
extern u32 D_800ABA24[];
extern u16 D_800BAE22;

void func_800CD674(s32 x, s32 y, s32 c) {
    u8 *p;
    register u32 tp0 __asm__("$3") = 0xE1000086;
    register u32 *ot __asm__("$7");
    register u32 m24 __asm__("$9") = 0x00FFFFFF;
    register u32 mff __asm__("$11") = 0xFF000000;
    register u32 tpr __asm__("$17");
    register u32 pm __asm__("$8");
    u32 pm2;
    u32 pm3;
    register u32 otv __asm__("$3");

    p = (u8 *)D_800A71D0;
    tpr = 0xE1000087;
    x -= 0xA0;
    y -= 0x78;

    *(u8  *)(p + 0x3) = 5;
    *(u32 *)(p + 0x4) = tp0;
    *(u8  *)(p + 0xB) = 0x64;
    *(u16 *)(p + 0x12) = 0x7800;
    *(u8 *)(p + 0x8) = *(u8 *)(p + 0x9) = *(u8 *)(p + 0xA) = c;
    *(s16 *)(p + 0xC) = x;
    *(s16 *)(p + 0xE) = y;
    *(u8  *)(p + 0x10) = 0;
    *(u8  *)(p + 0x11) = 0;
    *(s16 *)(p + 0x14) = 0xA0;
    *(s16 *)(p + 0x16) = 0x100;
    ot = (u32 *)((u8 *)D_800ABA24 + (D_800BAE22 << 14));
    *(u32 *)p = (*(u32 *)p & mff) | (*ot & m24);
    ot = (u32 *)((u8 *)D_800ABA24 + (D_800BAE22 << 14));
    pm = (u32)p & m24;
    otv = *ot;
    p += 0x18;
    *ot = (otv & mff) | pm;

    *(u8  *)(p + 0x3) = 5;
    *(u32 *)(p + 0x4) = tpr;
    tpr = 0xE1000097;
    *(u8  *)(p + 0xB) = 0x64;
    *(u16 *)(p + 0x12) = 0x7800;
    *(u8 *)(p + 0x8) = *(u8 *)(p + 0x9) = *(u8 *)(p + 0xA) = c;
    *(s16 *)(p + 0xC) = x + 0xA0;
    *(s16 *)(p + 0xE) = y;
    *(u8  *)(p + 0x10) = 0x20;
    *(u8  *)(p + 0x11) = 0;
    *(s16 *)(p + 0x14) = 0xA0;
    *(s16 *)(p + 0x16) = 0x100;
    ot = (u32 *)((u8 *)D_800ABA24 + (D_800BAE22 << 14));
    *(u32 *)p = (*(u32 *)p & mff) | (*ot & m24);
    ot = (u32 *)((u8 *)D_800ABA24 + (D_800BAE22 << 14));
    pm = (u32)p & m24;
    otv = *ot;
    p += 0x18;
    *ot = (otv & mff) | pm;

    *(u8  *)(p + 0x3) = 5;
    *(u32 *)(p + 0x4) = 0xE1000096;
    *(u8  *)(p + 0xB) = 0x64;
    *(u16 *)(p + 0x12) = 0x7800;
    *(u8 *)(p + 0x8) = *(u8 *)(p + 0x9) = *(u8 *)(p + 0xA) = c;
    *(s16 *)(p + 0xC) = x;
    *(s16 *)(p + 0xE) = y + 0x100;
    *(u8  *)(p + 0x10) = 0;
    *(u8  *)(p + 0x11) = 0;
    *(s16 *)(p + 0x14) = 0xA0;
    *(s16 *)(p + 0x16) = 0x100;
    ot = (u32 *)((u8 *)D_800ABA24 + (D_800BAE22 << 14));
    *(u32 *)p = (*(u32 *)p & mff) | (*ot & m24);
    ot = (u32 *)((u8 *)D_800ABA24 + (D_800BAE22 << 14));
    pm3 = (u32)p & m24;
    otv = *ot;
    p += 0x18;
    *ot = (otv & mff) | pm3;

    *(u8  *)(p + 0x3) = 5;
    *(u32 *)(p + 0x4) = tpr;
    *(u8  *)(p + 0xB) = 0x64;
    *(u16 *)(p + 0x12) = 0x7800;
    *(u8 *)(p + 0x8) = *(u8 *)(p + 0x9) = *(u8 *)(p + 0xA) = c;
    *(s16 *)(p + 0xC) = x + 0xA0;
    *(s16 *)(p + 0xE) = y + 0x100;
    *(u8  *)(p + 0x10) = 0x20;
    *(u8  *)(p + 0x11) = 0;
    *(s16 *)(p + 0x14) = 0xA0;
    *(s16 *)(p + 0x16) = 0x100;
    ot = (u32 *)((u8 *)D_800ABA24 + (D_800BAE22 << 14));
    *(u32 *)p = (*(u32 *)p & mff) | (*ot & m24);
    ot = (u32 *)((u8 *)D_800ABA24 + (D_800BAE22 << 14));
    pm2 = (u32)p & m24;
    otv = *ot;
    p += 0x18;
    D_800A71D0 = p;
    *ot = (otv & mff) | pm2;
    __asm__ volatile("" : "=r"(pm3));
}


INCLUDE_ASM("asm/md_MAIN_009/nonmatchings/md_MAIN_009", func_800CD92C);
