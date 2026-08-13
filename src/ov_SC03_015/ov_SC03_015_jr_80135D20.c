#include "common.h"
#include "../shared/engine_core.h"

/* ==== Phase-26 §8b carried decl layer (jr_isolate_all.py) ===================
 * The file-scope decl environment from earlier code regions of this object —
 * file-local types, col-0 decls, DEFINE_func macro externs, and each earlier
 * definition's implied prototype (types first, then decls in original order).
 * Decls emit no code => byte-neutral. See cookbook §8c. */
      /* 8-byte element, cmd @ +4 */
    /* list ptr @ +0x90 */
   /* size 8, alignment 1 -> unaligned copy */
DEFINE_func_80135D20()  /* dedup: shared engine-core @0x80135D20 (src/shared) */


// @class: struct
// @stuck: none — MATCH (289 ins). symcheck: only the cosmetic jtbl_801D81B8 floor (§8 carve).
//
// func_80135EB0 — h_seq family exemplar (x138 across the overlay fleet). Levers that made it:
//  1. m2 (the y-axis mask) MUST be the if/else form, NOT `m2=0x10; if (a8<=t3) m2=...`.
//     Both emit the same compact `bnez; li $s2,0x10` pair, but the pre-init form lets CSE carry
//     the D_8018BAFC pointer load into the (m1|m2)==0 block; the if/else form ends the CSE
//     extended-BB so the block reloads `lui/lw D_8018BAFC` (target does). Worth 2 ins + the whole
//     big-block register assignment.
//  2. Zero-byte `__asm__ __volatile__("")` fences in case 1 and case 2 (DIFFERENT templates, "" vs " ")
//     block gcc-2.7.2 cross_jump from folding those two bodies into case 6's second-call tail
//     (they are byte-identical to it; the target keeps all three copies). Worth 10 ins.
//  3. Zero-byte fences between the three big-block coordinate groups stop sched2 hoisting the next
//     group's `lhu` into the previous group's load-delay nop (restores 2 nops).
//  4. `D_801152AA = 0;` AFTER the h0 statement: it shortens the [6]-field temp's local-alloc live
//     range so c0 wins $v1 and the field temps take $v0/$a0 (target), not $v1/$v0.
//  5. case 4 reaches case 8's tail through a shared `L288` label using `w = x << 16` / `w >> 16`
//     so the shared block is exactly `sra $a1,$a1,16` — that is target's .L80136288. `w` pinned to
//     $a1 ($5); it never spans a jal so §74 does not apply.
//  6. arg1 copied into a $s3-pinned local — without it global-alloc gives arg1 $s2 and m2 $s3
//     (arg1 has more refs; target's priority order is arg0, sext-temp, m2, arg1).
//  7. `ret0:` sits between case 8 and case 10 and `done:`/`case 0:` after case 10 — that is the
//     target's basic-block order; reorg then produces the inline `move $v0,$zero` delay slots.

DEFINE_func_80135EB0()  /* dedup: shared engine-core @0x80135EB0 (src/shared) */


s32 func_80136334(void *arg0, s32 arg1, s32 arg2) {
    extern u8 D_801152A8[];
    extern s16 D_801152AA;
    extern s16 D_801152AC;
    extern s16 D_80126722;
    extern s16 D_80126724;
    register s32 a1v __asm__("$11");
    register s32 a2v __asm__("$12");
    register s32 n __asm__("$5");
    register s16 *b4 __asm__("$7");
    s32 d;
    s32 dx;
    s32 denom;
    s32 result;
    s32 frame_pad[2];
    (void)&frame_pad;
    __asm__("" : "=r"(a1v) : "0"(arg1));
    a2v = arg2;

    if (!(arg1 & 1)) {
        dx = (s16) arg2 - (*(s16 **)&D_8018BAFC)[2];
        d = dx;
        denom = -(*(s16 **)&D_8018BB08)[2];
    } else {
        denom = (*(s16 **)&D_8018BB08)[2];
        d = (*(s16 **)&D_8018BAFC)[2] - (s16) arg2;
        dx = -d;
    }
    n = -d;
    {
        register s16 *b8 __asm__("$6") = *(s16 **)&D_8018BB08;
        u16 *ac = *(u16 **)&D_8018BAFC;
        b4 = D_8018BB04;
        b4[0] = ac[0] + n * b8[0] / denom;
        b4[1] = ac[1] + n * b8[1] / denom;
        b4[2] = ac[2] + dx;
    }

    if (b4[0] < M2C_FIELD(arg0, s16 *, 4)) return 0;
    if (M2C_FIELD(arg0, s16 *, 6) < b4[0]) return 0;
    if (b4[1] < M2C_FIELD(arg0, s16 *, 8)) return 0;
    if (M2C_FIELD(arg0, s16 *, 0xA) < b4[1]) return 0;
    if (a1v & 0x8000) {
        u16 *b0 = *(u16 **)&D_8018BB00;
        b4[0] = b0[0];
        b4[1] = b0[1];
    }
    D_801152AA = 0;
    (*(s16 *)D_801152A8) = 0;
    if (a1v & 1) {
        D_8018BB04[2] = a2v + 2;
        __asm__ __volatile__("");
        D_801152AC = 0xFFF;
    } else {
        D_801152AC = -0xFFF;
        D_8018BB04[2] = a2v - 2;
    }
    __asm__ __volatile__("" :: "r"(a1v), "r"(a2v));
    (*(s16 *)D_80126720) = (M2C_FIELD(arg0, s16 *, 4) + M2C_FIELD(arg0, s16 *, 6)) >> 1;
    D_80126722 = (M2C_FIELD(arg0, s16 *, 8) + M2C_FIELD(arg0, s16 *, 0xA)) >> 1;
    result = 1;
    D_80126724 = (M2C_FIELD(arg0, s16 *, 0xC) + M2C_FIELD(arg0, s16 *, 0xE)) >> 1;
    return result;
}




// @class: regalloc-order — per-location family member of ov_SC01_077 exemplar func_801365B8 (x134).
// @stuck: none — MATCH expected; identical structure, only the 4 data ptrs differ (AC/B0/B4/B8 -> B64/68/6C/70).

// D_8018BAFC/68/70 file-scope `extern u8` holding pointers -> read via *(T**)&sym (§42c-2).
// D_8018BB04 file-scope `extern s16*` -> use directly. D_80126720 file-scope `extern u8[]`
// -> single store via *(s16*)D_80126720. D_801152A8/AA/AC, D_80126722/24 block-scope externs
// (siblings use block-scope; gcc-2.7.2 does not cross-conflict block-scope externs).
DEFINE_func_801365B8()  /* dedup: shared engine-core @0x801365B8 (src/shared) */



// @class: pointer-type — pointer-vs-array reconcile for func_80136824 (ov_SC01_077_a)
// D_8018BAFC/B0/B8 are file-scope `extern u8`, D_8018BB04 is `extern s32 []`; each HOLDS a
// pointer value that the target loads via lw then derefs. Read as pointer via *(T**)&sym.
// D_8018BB04 must be a SCALAR pointer (not s32[]) — as an array it decays and gcc CSEs the
// base address into a held reg (lui;addiu;lw 0(reg)) across the 3 reloads; as a scalar
// pointer it folds %lo (lui;lw %lo). Retype all 3 file-TU occurrences (byte-neutral: the
// siblings read it once via *(u16**)&sym == direct lw either way).

s32 func_80136824(s32 arg0, s32 arg1, s32 arg2) {
    extern u8 D_801152A8[];
    extern s16 D_801152AA;
    extern s16 D_801152AC;
    extern s16 D_80126722;
    extern s16 D_80126724;

    register u16 *ac __asm__("$4");
    register s16 *b8 __asm__("$6");
    register s16 *b4 __asm__("$9");
    register s32 r __asm__("$3");
    register s32 pos __asm__("$12");
    register s32 a1v __asm__("$5");
    s16 temp_v0;
    s16 temp_v1;
    s32 var_a3;
    s16 var_v0_3;
    s32 temp_a1;
    s32 var_t0;
    s32 var_v1;
    s16 *b4b;
    u16 *p;

    __asm__ ("" : "=r"(a1v) : "0"(arg1));
    pos = arg2;
    if (!(a1v & 1)) {
        var_t0 = (s16) arg2 - (*(s16 **)&D_8018BAFC)[1];
        var_v1 = var_t0;
        var_a3 = -(*(s16 **)&D_8018BB08)[1];
    } else {
        var_a3 = (*(s16 **)&D_8018BB08)[1];
        var_v1 = (*(s16 **)&D_8018BAFC)[1] - (s16) arg2;
        var_t0 = -var_v1;
    }
    b8 = (*(s16 **)&D_8018BB08);
    ac = (*(u16 **)&D_8018BAFC);
    b4 = D_8018BB04;
    temp_a1 = -var_v1;
    r = (temp_a1 * b8[0]) / var_a3;
    b4[0] = ac[0] + r;
    b4[1] = ac[1] + var_t0;
    r = (temp_a1 * b8[2]) / var_a3;
    temp_v0 = ac[2] + r;
    b4[2] = temp_v0;
    temp_v1 = b4[0];
    if (temp_v1 < M2C_FIELD(((void *)arg0), s16 *, 4)) {
        return 0;
    }
    if (M2C_FIELD(((void *)arg0), s16 *, 6) < temp_v1) {
        return 0;
    }
    if (temp_v0 < M2C_FIELD(((void *)arg0), s16 *, 0xC)) {
        return 0;
    }
    if (M2C_FIELD(((void *)arg0), s16 *, 0xE) < temp_v0) {
        return 0;
    }
    if (arg1 & 0x8000) {
        p = (*(u16 **)&D_8018BB00);
        b4[0] = (s16) p[0];
        b4[2] = (s16) p[2];
    }
    D_801152AC = 0;
    (*(s16 *)D_801152A8) = 0;
    if (arg1 & 1) {
        b4b = D_8018BB04;
        D_801152AA = 0xFFF;
        __asm__ __volatile__("");
        var_v0_3 = pos + 2;
    } else {
        b4b = D_8018BB04;
        D_801152AA = -0xFFF;
        __asm__ __volatile__("");
        var_v0_3 = pos - 2;
    }
    b4b[1] = var_v0_3;
    __asm__ __volatile__("" :: "r"(pos));
    (*(s16 *)D_80126720) = (s16) ((s32) (M2C_FIELD(((void *)arg0), s16 *, 4) + M2C_FIELD(((void *)arg0), s16 *, 6)) >> 1);
    D_80126722 = (s16) ((s32) (M2C_FIELD(((void *)arg0), s16 *, 8) + M2C_FIELD(((void *)arg0), s16 *, 0xA)) >> 1);
    D_80126724 = (s16) ((s32) (M2C_FIELD(((void *)arg0), s16 *, 0xC) + M2C_FIELD(((void *)arg0), s16 *, 0xE)) >> 1);
    return 1;
}


// @class: schedule
// @stuck: none — MATCH (76 ins, relocation-masked). Key lever: the D_80126720/22/24 tail is a
//   global-short RMW `+=`. Writing it via a cast `*(u16*)&SYM = *(u16*)&SYM + x` makes gcc CSE
//   the address into a base reg (base-reuse) for ALL three — but the target only base-reuses
//   D_80126720 (a SCHEDULER artifact: its addr-lui fills the load-delay slot after the pb4[4]
//   load, and since $v0 is live it lands in $a0, reused for load+store). D_80126722/24 use the
//   plain inline 2-lui form. Fix = DIRECT scalar RMW `SYM = SYM + x` (no &/cast) → inline %hi/%lo;
//   the scheduler alone forces base-reuse on #1. Also: `s16 D_80126724 = D_80126724 + int` emits
//   LHU (gcc-2.7.2 drops the sign-extend because the sum is truncated to 16b on the sh) — so the
//   canonical s16 decl is byte-safe here (no u16 retype needed, keeps the sign-sensitive callers).


extern s16 *D_8018BB04;   /* holds a pointer value (*(u16**)&D_8018BB04) */

s32 func_80136A94(s32 a0, s32 a1, s32 a2, s32 a3) {
    extern void ApplyMatrixSV(void *m, void *v0, void *v1);
    extern void ApplyRotMatrix(void *v0, void *v1);
    extern u16 D_80126722;
    extern s16 D_80126724;
    extern s16 D_801152AA;
    extern s16 D_801152AC;

    s32 out[4];
    u16 *pb4;

    if (a0) {
        ApplyMatrixSV((void *)a3, *(void **)&D_8018BB04, *(void **)&D_8018BB04);
        ApplyMatrixSV((void *)a3, (void *)D_80126720, (void *)D_80126720);
        ApplyRotMatrix((void *)D_801152A8, (void *)out);
        *(s16 *)D_801152A8 = out[0];
        D_801152AA = out[1];
        D_801152AC = out[2];
    }

    pb4 = *(u16 **)&D_8018BB04;
    *(s16 *)(a2)     = pb4[0] + *(s32 *)(a1 + 0x48);
    *(s16 *)(a2 + 2) = pb4[1] + *(s32 *)(a1 + 0x4C);
    *(s16 *)(a2 + 4) = pb4[2] + *(s32 *)(a1 + 0x50);

    *(u16 *)D_80126720 = *(u16 *)D_80126720 + *(s32 *)(a1 + 0x48);
    D_80126722 = D_80126722 + *(s32 *)(a1 + 0x4C);
    D_80126724 = D_80126724 + *(s32 *)(a1 + 0x50);
}



DEFINE_func_80136BC4()  /* dedup: shared engine-core @0x80136BC4 (src/shared) */

DEFINE_func_80136C1C()  /* dedup: shared engine-core @0x80136C1C (src/shared) */

DEFINE_func_80136C3C()  /* dedup: shared engine-core @0x80136C3C (src/shared) */

DEFINE_func_80136C44()  /* dedup: shared engine-core @0x80136C44 (src/shared) */

DEFINE_func_80136C4C()  /* dedup: shared engine-core @0x80136C4C (src/shared) */


DEFINE_func_80136C54()  /* dedup: shared engine-core @0x80136C54 (src/shared) */


// @class: struct
// @stuck: none — MATCH (28 ins). 10-byte 1-aligned struct copy (S10_80136C90{char s[10]}) from global D_801E83F0 into a stack buffer, then func_8001534C(0,&buf,0x78,0x10,0,0). gcc emits the block move as 2 unaligned words (lwl/lwr+swl/swr) + 2 bytes (lb/sb).


s32 func_80136C90()
{
    extern void func_8001534C(int, void *, int, int, int, int);
    extern S10_80136C90 D_801E83F0;

    S10_80136C90 buf = D_801E83F0;
    func_8001534C(0, &buf, 0x78, 0x10, 0, 0);
}



DEFINE_func_80136D00()  /* dedup: shared engine-core @0x80136D00 (src/shared) */

DEFINE_func_80136D08()  /* dedup: shared engine-core @0x80136D08 (src/shared) */

DEFINE_func_80136DFC()  /* dedup: shared engine-core @0x80136DFC (src/shared) */

DEFINE_func_80136EC4()  /* dedup: shared engine-core @0x80136EC4 (src/shared) */

DEFINE_func_80136ECC()  /* dedup: shared engine-core @0x80136ECC (src/shared) */

DEFINE_func_80136F3C()  /* dedup: shared engine-core @0x80136F3C (src/shared) */

DEFINE_func_80137030()  /* dedup: shared engine-core @0x80137030 (src/shared) */

DEFINE_func_80137178()  /* dedup: shared engine-core @0x80137178 (src/shared) */

DEFINE_func_801372B0()  /* dedup: shared engine-core @0x801372B0 (src/shared) */

DEFINE_func_801375EC()  /* dedup: shared engine-core @0x801375EC (src/shared) */

extern void func_801375EC(s32 a0, s16 a1);

// @class: schedule (arg-copy placement) — PIN-FREE
// match_one: MATCH (26 ins).  rtu: MATCH (26 ins) with NO //@EDIT and NO header edit.
//
// ---- RECONCILE 2026-08-01 (uc2 -> uc3) ---------------------------------------------------
// GATE ERROR was:
//   jr_80135D20.c:1412 conflicting types for func_80137614 || :1362 previous declaration
// :1362 is `DEFINE_func_801375EC()`, whose expansion (src/shared/engine_core.h:2819) carries
//   extern void func_80137614(s32 a0, s32 a1, s32 a2);
// and it is instantiated two lines ABOVE this function's INCLUDE_ASM splice point (:1364).
// :1412 is this draft's own definition.  So the conflicting symbol is func_80137614 ITSELF
// and the axis is the §73 RETURN type: the shared header says `void`, the target ends
// `addu $v0, $s0, $zero` and callers in other overlays consume the result
// (ov_SC03_099_jr_80178D40.c already declares it `extern s32 func_80137614(s32,s32,s32)`),
// so the definition MUST stay s32.  Re-voiding the definition is the decay loop: gcc-2.7.2
// silently drops the $v0 set and you get 25/26 ins, class LENGTH-DRIFT/-1.
//
// ESCAPE USED: §37/§124 ASM-LABEL ALIAS (escape #2).  The definition is given a distinct C
// identifier `aF80137614` with __asm__("func_80137614"), so it never collides with the
// header's `extern void func_80137614` while still emitting the canonical symbol.  Zero
// header edits, zero TU edits, blast radius 0 — this replaces uc2's //@EDIT §65b de-macroize
// of DEFINE_func_801375EC, which would have had to be repeated at all 138 sweep sites.
// The TU already uses this exact idiom 60-odd lines below
// (`void *aF801376E8(int a0, int a1) __asm__("func_801376E8");`), so it travels to siblings.
// The in-TU call from func_801375EC still binds to the header's extern declaration and
// resolves to the same symbol at link time; func_801375EC's own 10 instructions are unchanged.
//
// ---- CODEGEN (unchanged from uc2 — do not touch) -----------------------------------------
// Residual before the lever: 4 mismatched, the (sw $sN / addu $sN,$aX) prologue PAIRS mirrored —
// target births $s2<-a2 then $s3<-a1; the naive draft births $s3<-a1 then $s2<-a2 (parm order),
// and drags `sw $s3` above `sw $s2` with it.  Register ASSIGNMENT was already right in both, so
// this is NOT a regalloc problem.  Measured INERT: body statement order, extra plain locals,
// K&R parm-declaration order (incl. declaring a2 before a1 in the K&R decl block).
//
// LEVER — cookbook §67 (arg-copy PLACEMENT).  One zero-instruction launder of the a1 parameter
// pins WHERE its entry copy materialises; a2's copy then takes the earlier slot and the register
// saves fall back into ascending order.  DIRECTION MATTERS and is the opposite of the intuition:
// laundering a2 (the copy that must move EARLIER) is inert — launder the copy that must land
// LATER.  §67 rule 1 respected: the laundered local is NOT pinned.  A pinned variant
// (register s32 __asm__("$18") / __asm__("$19") on a2/a1) also MATCHes, but pins are strictly
// worse for the ×138 family sweep (§42e/§86 pin guard), so the pin-free single launder is banked.
//
// Shape copied from the matched next-door sibling DEFINE_func_8013767C() (engine_core.h),
// which is this function minus the 0xD8 mask and the +0x1C halfword store.

extern s32 func_801399A8(void);
extern void func_801377B4(s32 a0, s32 a1, s32 a2);

s32 aF80137614(s32 a0, s32 a1, s32 a2) __asm__("func_80137614");

DEFINE_func_80137614()  /* dedup: shared engine-core @0x80137614 (src/shared) */


DEFINE_func_8013767C()  /* dedup: shared engine-core @0x8013767C (src/shared) */

DEFINE_func_801376C8()  /* dedup: shared engine-core @0x801376C8 (src/shared) */


/* @class: plumbing (globals-around-two-calls)
 * @stuck: none — MATCH (51 ins).
 *
 * RECONCILE (§37/§124 ASM-LABEL ALIAS) — no TU / header edit required.
 *   Gate error: ov_SC01_077_jr_80135D20.c:1415: conflicting types for `func_801376E8'
 *               || previous declaration at :1368
 *   :1368 is DEFINE_func_801376C8(), the shared engine-core macro that carries
 *   `extern void func_801376E8(int a0, int a1);` — a VOID return. The target's last
 *   pre-epilogue instruction is `addu $v0, $s1, $zero`, i.e. it RETURNS &D_801269F0,
 *   so the definition MUST be non-void; a `void` definition makes gcc-2.7.2 merely warn
 *   and DROP the returned value, killing that instruction (LENGTH-DRIFT/-1, 50 ins).
 *   The conflict is on func_801376E8 ITSELF and is a pure RETURN-type disagreement
 *   (params already agree: int,int), so the §37/§124 alias applies verbatim:
 *   define under the C name aF801376E8 with __asm__("func_801376E8") so the C-level
 *   declaration never collides, while the emitted symbol is still func_801376E8.
 *   Codegen is untouched — an asm label renames the symbol, nothing else.
 *   (The earlier draft's `//@EDIT` widening of the shared extern to `void *` is a
 *   T2 fleet-shared edit; the alias is T0 draft-only. Cookbook §124: fix the reader,
 *   not the source.)
 *
 * Byte levers (unchanged from the passing draft):
 *  - `obj` local holding (s32)&D_801269F0: the address is CSEd ONCE into $s1 and reused
 *    for both jal args and the return (same idiom as the neighbouring func_80137B80).
 *  - D_80126A24 is s16 (`lh`) but D_80126A26 is u16 (`lhu`) with an explicit (s16) cast
 *    at the use site: gcc combines the cast's `sll 16; sra 16` with the `>>1` into
 *    `sll 16; sra 17`, which is exactly what the target emits. A plain s16 D_80126A26
 *    would give `lh; sra 1` instead.
 *  - D_80126A14 as u16[2] (`lhu` loads, `%lo(D_80126A14 + 0x2)` for element 1).
 */


extern void func_801377B4(s32 a0, s32 a1, s32 a2);
extern void func_80139BE0(s32 a0);

void *aF801376E8(int a0, int a1) __asm__("func_801376E8");

DEFINE_func_801376E8()  /* dedup: shared engine-core @0x801376E8 (src/shared) */


DEFINE_func_801377B4()  /* dedup: shared engine-core @0x801377B4 (src/shared) */

DEFINE_func_80137840()  /* dedup: shared engine-core @0x80137840 (src/shared) */


extern void func_80016714(void *a0, s32 a1);
extern void func_8013A860(void);

void func_801378F0(void) {

    extern u8 D_80127520[];
    extern u8 aD801269F0[] __asm__("D_801269F0"); /* §37 alias: TU canon is `extern int D_801269F0` */
    extern u8 D_80126A28[];
    extern u8 D_8018BB20[];
    s32 i;
    s32 si;
    s32 di;
    u8 *p;

    func_80016714(D_80127520, 0xBFC);
    i = 0;
    si = 0;
    p = aD801269F0;
    di = 0;
    do {
        func_80016714(p, 0x4C);
        *(u16 *)&D_80126A28[di]     = *(u16 *)&D_8018BB20[si];
        *(u16 *)&D_80126A28[di + 2] = *(u16 *)&D_8018BB20[si + 2];
        *(u16 *)&D_80126A28[di + 4] = *(u16 *)&D_8018BB20[si + 4];
        *(u16 *)&D_80126A28[di + 6] = *(u16 *)&D_8018BB20[si + 6];
        p += 0x4C;
        i += 1;
        si += 8;
        di += 0x4C;
    } while (i < 3);
    func_8013A860();
}


DEFINE_func_801379D8()  /* dedup: shared engine-core @0x801379D8 (src/shared) */

DEFINE_func_801379EC()  /* dedup: shared engine-core @0x801379EC (src/shared) */


// @class: regalloc-order (walker-family, §52/§52a) — PIN-FREE
// Role-swap ($s0<->$s2 between loop1 and loops2/3) is driven by DENSITY (K2), not pins:
//  - loop1 pointer has an extra ref (p != D_80127524 compare) -> wins $s0; index -> $s2
//  - loop2/3 index has >= pointer refs -> wins $s0; pointer -> $s2
// Separate per-loop pointer/index vars => separate pseudos => can take different regs.


DEFINE_func_801379FC()  /* dedup: shared engine-core @0x801379FC (src/shared) */



// @class: remat
// @stuck: target CSEs &D_801269F0 once for load+call arg; force via local pointer
extern s32 D_80127548[];
extern int D_8018BB6C;
extern int D_801269F0;
extern void func_80138BE0(int p);

void func_80137B80(void) {
    int *p = &D_801269F0;
    (*(int *)&D_80127548) = 0x24;
    if (*p != 0) {
        ((void (*)(int *))func_80138BE0)(p);
    }
    D_8018BB6C += 1;
}


DEFINE_func_80137BD8()  /* dedup: shared engine-core @0x80137BD8 (src/shared) */


// @class: plumbing
// @stuck: none — MATCH (51 ins). Three globals stored/loaded around 3 calls; &D_801269F0 held in $s1, arg1 in $s0 across calls; return reloads global D_800A5E60.

extern unsigned char D_80126A0E;
extern short D_80126A0A;
extern s16 D_801269F4;
extern int D_800A5E60;
extern int D_8018BB6C;
extern int D_801269F0;

extern void func_801392FC();
extern void func_80137DD4(s32 a0, u8 *a1, u8 *a2);
extern void func_80139680(s32 a0, u8 *a1);

int func_80137D08(int arg0, int arg1, short arg2)
{
    unsigned char buf[3];

    D_800A5E60 = arg0;
    D_80126A0A = arg2;
    ((void (*)(void *, int, int))func_801392FC)(&D_801269F0, D_80126A0E, arg1);
    if ((*(short *)&D_801269F4) == 7) {
        buf[0] = 0x39;
        buf[1] = 0xFF;
        buf[2] = 0x71;
        ((void (*)(void *, void *, int))func_80137DD4)(&D_801269F0, buf, arg1);
    } else if ((*(short *)&D_801269F4) == 3) {
        if (D_8018BB6C & 4) {
            ((void (*)(void *, int))func_80139680)(&D_801269F0, arg1);
        }
    }
    return D_800A5E60;
}


DEFINE_func_80137DD4()  /* dedup: shared engine-core @0x80137DD4 (src/shared) */

DEFINE_func_80137FD8()  /* dedup: shared engine-core @0x80137FD8 (src/shared) */


