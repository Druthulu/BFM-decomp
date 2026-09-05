#include "common.h"
/* =====================================================================================
 * S79 (this session) — RESULT UNCHANGED AT closeness 1/422; the residual is now EXPLAINED
 * AND THE ORPHAN SEARCH IS CLOSED.  ~200 byte-probes, all with the pinned cc1
 * (cpp -Iinclude | cc1 -quiet -O2 -G0 -mips1 -mcpu=3000 -mgas -msoft-float -fgnu-linker),
 * oracle = `vars=` off the .frame line (NOT the `(use (reg))` count — see INSTRUMENT below).
 *
 * THE FRAME ARITHMETIC IS EXACT AND LEAVES EXACTLY ONE ORPHAN TO BUY (§165-03):
 *   target .frame $sp,0x78  regs=10/0  args=16  =>  vars = 0x40 = 64
 *   64 = 0x20 (the ONE declared local, sp10) + 8*3 (the a0/a1/a2 reload spills at
 *        0x30/0x38/0x40, all referenced) + 8*1 (ONE never-referenced slot at 0x48).
 *   sp10 must be 0x1C..0x20 bytes: 0x18 puts the first spill at 0x28, 0x24 puts it at 0x38;
 *   only [0x1C,0x20] CEIL_ROUNDs frame_offset to the target's 0x30.  A declared pad can
 *   therefore NEVER buy the 8 bytes here — any pad lands before the spills and moves
 *   `sw $a0,0x30($sp)`.  (§162i1/§226/§333 are all inapplicable to this function.)
 *
 * WHY THE ORPHAN AND THE `lhu` ARE MUTUALLY EXCLUSIVE (the new, general result):
 *   `extendhisi2` in mips.md is an EXPAND that does force_not_mem at -O2, so EVERY
 *   `int x = <s16 mem>` is movhi + ashl16 + ashr16 and combine 3-way-merges it to `lh`.
 *   In a SINGLE-USE merge, newi2pat==0 so elim_i2/elim_i1 DROP both intermediates' death
 *   notes -> no orphan.  An orphan needs the HImode load's reg to carry a SECOND use, which
 *   forces the i3_subst_into_i2 path (newi2pat != 0 -> elim_i2 == 0) and strands the ashift
 *   intermediate.  `zero_extendhisi2` is a define_INSN that takes memory, so every unsigned
 *   promotion is one insn and can never orphan (14 u16/u32/s32/QI respellings measured: 0).
 *   => an orphan in this function REQUIRES an `lh`, and the target's idx-244 load is `lhu`.
 *
 * THE SITE CENSUS (why no other site can pay for it).  The target has 8 `lh`s
 *   (D_800C5328, D_800C532A, D_800A4646, D_800A46A2 x2, sp10.unk16, D_800A4EFA,
 *    ch->unk48, D_800A4EF6) and every one is SINGLE-USE, so each is a note-dropping
 *   3->1 merge.  The only two values in the whole body with a free narrow second use are
 *     - `vo->unk18` (mask + a QImode `(s8)` use) -> orphan only in the `lh` spelling, and
 *     - `n` (int uses + the `sh $s2,0x10($s0)` HImode store) -> `s16 n` costs +4 ins and
 *       TWO orphans (426 ins, near 395); an s16 shadow of n (nh/n pair, both directions)
 *       is 2 orphans / near 387.  Measured, not assumed.
 *
 * MEASURED-INERT THIS SESSION (do not re-try):
 *   * 100-variant local-retyping sweep (20 locals x 6 widths): only `n`->s16/s8 (2 orphans,
 *     near 395/397) and `b`->s8 (1 orphan, near 273) move `vars`; nothing is free.
 *   * splitting `(s8)u18` into its own s32 temp DOES buy the orphan and the exact 0x78 frame
 *     (vars=64, near 5) — but combine then re-derives the byte straight from memory as a
 *     second load `lb $v0,0x18($s1)`; 8 spellings (u32/s32/s16 base, <<1 vs *2, compound,
 *     `(u8)`/`&0xFFFF` launders) all keep the `lb`.  Best of that family: near 5.
 *   * `__asm__ __volatile__("" ::: "memory")` between the load and the use DOES block the
 *     3-way merge and restores `lhu` at zero instruction cost — near 22, frame 0x70, and
 *     the orphan dies with the merge.  Same for §148-C's zero-emission ref slider
 *     `__asm__ ("" :: "r"(u18))` placed BEFORE the expression (near 22, vars 56).
 *     Placed AFTER, the slider keeps the orphan but costs a `move` (423 ins, near 184).
 *     This is the tension in its sharpest form: the extra HImode use that BLOCKS the merge
 *     (giving `lhu`) is the same use that must SURVIVE the merge to strand the intermediate.
 *   * `?:`-accumulator respellings of the four selects (ch->unk48, ch->unk24, ch->unk4D,
 *     vv), s16 temps at every single-use `lh` site, un-hoisting the clear loop (index /
 *     pointer / 4 forms), and 6 zero-emission ref sliders at other sites: all vars=56.
 *   * volatile s16 local: vars=64 but near 192 (it is a DECLARED local, wrong stratum).
 *
 * INSTRUMENT CORRECTION (worth banking): §172's "count standalone `(use (reg))` in the
 *   .combine dump" UNDER-COUNTS.  A minimal §167-10 reproducer
 *   (`s16 c = A; if (c != 0) A = c - 1;`) emits `vars= 8` with ZERO `(use (reg))` insns —
 *   the stranded pseudo is simply absent from every post-combine dump while flow's stale
 *   `reg_n_refs` keeps it an allocno (`; ST_REGS or none` in -dl, §165-03).  Also: the
 *   naive grep counts hard-reg return USEs (`(use (reg/i:SI 2 v0))`) — 54 hits across
 *   src/800_b_2.c collapse to 11 real pseudo orphans.  USE `vars=` AS THE ORACLE.
 *
 * WHAT IS LEFT (for whoever picks this up): the 8 bytes are almost certainly NOT a combine
 *   orphan.  §172's producer 3 — a caller-save area, `assign_stack_local(SImode,4,0)`,
 *   allocated inside reload's loop (reload1.c:1445) and therefore AFTER the alter_reg slots
 *   (reload1.c:658) — lands exactly at 0x48 and MIPS_STACK_ALIGN rounds vars 0x3C -> 0x40,
 *   reproducing 64 with no instruction anywhere.  That is a register-allocation event, not a
 *   spelling one; the C axis for it (one more call-crossing value competing for the 9
 *   callee-saved regs this function already uses in full) was not found.  Next probe worth
 *   running: an A/B that adds one genuine call-crossing value and reads `vars` + the
 *   `.greg` "Spilling reg" lines, rather than any further respelling of the 0x18 read.
 * ===================================================================================== */
/* func_80032A74 - NEAR, closeness 1 / 422 ins (frame 0x78 exact, every immediate, every stack
 * offset, every branch target and 421 of 422 registers exact).  Residual: idx 244 `lh` vs `lhu`.
 *
 * ===================================================================================
 * THE LEVER THAT TOOK THIS FROM 12 -> 1 (new; not in the cookbook as of S77):
 *   HOIST A GLOBAL ARRAY'S BASE INTO A FILE-SCOPE-TYPED POINTER LOCAL ASSIGNED *BEFORE*
 *   THE LOOP.  That single move reproduces the target's `lui $t0/addiu $t0/addu` shape
 *   for three different symbols AND puts them all in $t0, with no asm launder and no
 *   register pin.  Mechanism, read out of the gcc-2.7.2 source (tools/reference/gcc-2.7.2):
 *
 *   1. local-alloc.c:472 - a pseudo is a LOCAL-ALLOC CANDIDATE only if
 *        `reg_basic_block[i] >= 0 && reg_n_deaths[i] == 1`
 *      i.e. it lives in ONE basic block and dies ONCE.  `&D_800A4C28[idx]` written inline
 *      makes a 2-ref, one-block pseudo -> local-alloc hands it the LOWEST free hard reg
 *      (find_free_reg scans regno 0..31; MIPS defines no REG_ALLOC_ORDER) -> $v1.
 *   2. Assigning the base to a local BEFORE the `for(;;)` makes it multi-block, so
 *      local-alloc skips it; global-alloc cannot place it either (all ten callee-saved
 *      registers are already taken and update_equiv_regs doubled its live length), so
 *      `reg_renumber < 0`.
 *   3. update_equiv_regs (local-alloc.c:1030) has already attached REG_EQUIV (symbol_ref)
 *      because the pseudo is set once from a constant -> reload1.c DELETES the initialising
 *      insn (zero cost, so the hoist is FREE) and reload.c substitutes the symbol at every
 *      use, reloading it into a SPILL register.  $t0 is this function's first spill reg
 *      (it is also what carries `lw $t0,0x30($sp)`, `addiu $t0,$zero,1`, `mflo $t0`) - which
 *      is exactly why the target shows the symbols and the parm reloads sharing $t0, and why
 *      `register s32 x __asm__("$8")` can NEVER reproduce it: a hard-reg user variable makes
 *      reload move every spill to $t1 (measured: +30 rows).
 *   4. `addu $s1,$v0,$t0` operand order comes from writing `idx * 0x48 + (s32)vB`, not
 *      `vB + idx * 0x48`.
 *   5. `const` on the two tables is LOAD-BEARING (dropping it costs 14 rows of scheduling
 *      around the mult/mflo pair) - the original declared them const.
 *
 * OTHER LEVERS RETAINED FROM THE PREVIOUS 408->12 RUN:
 *   - `vol` and `m` are ONE variable (both live in $a0 over disjoint ranges).
 *   - `register s32 base __asm__("$2")` on the 0x18-lerp base: without it the addu/addiu/subu
 *      chain lands in $v1 (+3 rows).
 *   - a zero-byte `__asm__ __volatile__("")` after `vo->unk04 = 0x6009F` stops sched1 hoisting
 *      the D_800A4EF6 `lh` above the three stores (-7 rows), and one after `ch->unk14 = t32`.
 *   - use the PARAMETERS directly (no `e = arg0` copies) so the reload spill slots stay
 *     0x30/0x38/0x40; the 8-byte clear loop is a POINTER loop with `i = 7;` FIRST (S211).
 *
 * ===================================================================================
 * THE ONE REMAINING ROW, and why it is a genuine wall for this spelling
 *   idx 244   mine `lh $v0,0x18($s1)`   target `lhu $v0,0x18($s1)`
 *
 * The target frame is 0x78: sp10 at 0x10-0x2F, the three parm spills at 0x30/0x38/0x40, and a
 * NEVER-REFERENCED 8-byte slot at 0x48.  The only producer of that slot reachable from C here
 * is a S172 combine USE-orphan, and the only site in this function that orphans is
 * `s16 u18 = vo->unk18` with BOTH an int (sign) promotion and a QImode use - which forces the
 * load to be `extendhisi2_internal` = `lh`.  Spelling the int use as `(u16)u18 & 0xFF00` gives
 * the target's `lhu` and is byte-identical in all 422 instructions - but the orphan vanishes,
 * the frame drops to 0x70 and 22 stack-offset rows break (that draft is kept at
 * .run/S77w/opus/scratch_func_80032A74/v2.c).  Measured dead ends for a substitute orphan
 * (each checked by counting standalone `(insn N P X (use (reg ...)))` in the cc1 `-dc` dump):
 *   - every u16/s16/s8/QImode respelling of the vo->unk18 site (14 forms) -> 0 orphans;
 *   - `s16 n` (D_800C5328/D_800C532A) -> 2 orphans but a `lhu`+`lh` DOUBLE LOAD, +4 ins;
 *   - an s16 temp at that site whose only uses are promotions -> folds, 0 orphans;
 *   - an s16 local for the func_8003F144 return -> 0 orphans.
 * Every other `lh` in the target (D_800A4646, D_800A46A2 x2, sp10.unk16, D_800A4EFA,
 * ch->unk48, D_800A4EF6) has a SINGLE consumer, and S172's rule is that a single-use load
 * 3-way-merges and orphans nothing.  A declared 8-byte dead local cannot substitute: expand-time
 * locals precede the reload spills and push $a0 from 0x30 to 0x38.
 */
/* func_80032A74 - NEAR, closeness 12 / 422 ins (length exact, frame exact).
 *
 * LEVERS PROVEN THIS SESSION (each byte-measured with tools/match_one.py; start 408 -> 12):
 *  1. FRAME +8 (vars 56 -> 64) = ONE combine USE-orphan (cookbook S172 producer 2).  The target's
 *     frame is  0x10..0x2F C24 local | 0x30/0x38/0x40 parm spills | 0x48 NEVER-REFERENCED.  A
 *     declared dead local CANNOT do it (expand-time locals precede reload spills - measured: it
 *     pushes a0 from 0x30 to 0x38), and neither can `asm("":: "m"(pad))` (mark_addressable puts it
 *     in the locals region too).  What does: an `s16` LOCAL read from memory and promoted to int
 *     TWICE, sited after a CODE_LABEL -> expand emits movhi + ashift/ashiftrt, combine merges them
 *     into one `lh` and orphans the HImode pseudo as `(insn (use (reg:SI N)))`, which alter_reg
 *     still gives an 8-byte slot.  Instrument: count standalone `(use (reg` insns in the .combine
 *     dump (tools/cc1_dumps.sh).  ZERO-extending (u16) temps merge cleanly and orphan NOTHING -
 *     the ashift/ashiftrt PAIR is the whole mechanism.  Single-use s16 temps also orphan nothing.
 *     COST: the only site available here is `vo->unk18`, where the target loads `lhu` - so idx 244
 *     is `lh` vs `lhu`, the one structural row left.  A 2-use `lh` site would be free; the only
 *     other one is `n` (D_800C5328) and typing it s16 costs +4 ins.
 *  2. `vol` AND `m` ARE ONE VARIABLE.  The target holds both in $a0 across disjoint ranges; two
 *     separate C variables give two allocnos ($v1 and $a1).  Merging them is what puts the whole
 *     volume chain in $a0.
 *  3. THE S153 LAUNDER'S REAL COST IS AN ALLOCNO, AND THE FIX IS A PIN ON A DEAD TEMP.  Removing
 *     the launder (plain `D_8007319E[pan]`) fixes m/$a0, the `li 0x100` delay-slot schedule and the
 *     D_800A4EF6 hoist all at once - but folds the address back to the 3-insn $at macro form (-2
 *     ins).  Keeping the launder, the symbol pseudo has priority log2(refs)*refs/live_length ~ 0.67
 *     and OUTRANKS the long-lived `vol` (~0.19), so it steals $a0 and pushes the whole chain to $a1
 *     (+17 rows).  `register s32 bp __asm__("$10")` parks it on a register nothing else wants:
 *     $a0 goes back to vol/m and reload keeps $t0.  Do NOT pin it to $8: reload then picks $t1 for
 *     every parm reload (measured +14 rows, net worse).  $9 costs 2 rows (the mflo temp at idx 272
 *     moves $t1 -> $t2); $10 costs none.
 *  4. A zero-byte `__asm__ __volatile__("")` after `vo->unk04 = 0x6009F;` stops sched1 hoisting the
 *     D_800A4EF6 `lh` above the three stores (-7 rows).
 *  5. S219: `vol *= 0x70; vol >>= 7;` (compound) vs `vol = (vol*0x70)>>7;` decides whether the
 *     `<<4` intermediate lands in $a0 or $v0 (-2 rows).
 *
 * REMAINING RESIDUAL (12), all REGISTER-NAMING, nothing structural:
 *   - 3 rows: the D_800A4C28 base is $v1, target $t0.
 *   - 8 rows: the laundered table base is $t1/$t2, target $t0 - and $t0 is unreachable because the
 *     same $t0 is reload's spill register for the three parm reloads; a hard-reg var there evicts
 *     reload.  In the target BOTH uses coexist, which means those symbol pseudos are NOT allocnos -
 *     they are reload rematerialisations of a reg_equiv_constant.  Every C spelling tried
 *     (array[i], &array[i], scalar `extern u16 D;` + `&D + off`, S195-H's struct-cast force_reg,
 *     const u16* local, S239 integer-space, one-table-two-index) folds to the $at macro form; only
 *     the launder produces the 4-insn shape, and the launder always creates an allocno.
 *   - 1 row: idx 244 `lh` vs `lhu` (see lever 1).
 */
typedef struct Slot {
    /* 0x00 */ s32 unk00;
    /* 0x04 */ s32 unk04;
    /* 0x08 */ u8 unk08[0xC];
    /* 0x14 */ s16 unk14;
    /* 0x16 */ u8 unk16[2];
    /* 0x18 */ s16 unk18;
    /* 0x1A */ u8 unk1A[0x26];
    /* 0x40 */ s32 unk40;
    /* 0x44 */ u8 unk44;
    /* 0x45 */ u8 unk45[3];
} Slot;
typedef struct {
    /* 0x00 */ u8 *unk00;
    /* 0x04 */ u8  pad04[2];
    /* 0x06 */ u8  unk06;
    /* 0x07 */ u8  unk07;
    /* 0x08 */ u8  unk08;
    /* 0x09 */ u8  pad09[3];
} A12; /* 0x0C */
typedef struct {
    /* 0x00 */ s32 unk00;
    /* 0x04 */ s16 unk04;
    /* 0x06 */ s16 unk06;
    /* 0x08 */ s16 unk08;
    /* 0x0A */ u8  unk0A;
    /* 0x0B */ u8  unk0B;
} B12; /* 0x0C */
typedef struct {
    /* 0x00 */ u8  pad00[4];
    /* 0x04 */ u8  unk04;
    /* 0x05 */ u8  pad05[11];
    /* 0x10 */ u16 unk10;
    /* 0x12 */ u16 unk12;
    /* 0x14 */ u8  pad14[2];
    /* 0x16 */ s16 unk16;
    /* 0x18 */ u8  pad18[8];
} C24; /* 0x20 */
typedef struct Rec14 {
    /* 0x00 */ u16 unk00;
    /* 0x02 */ u16 unk02;
    /* 0x04 */ u32 unk04;
    /* 0x08 */ u32 unk08;
    /* 0x0C */ u16 unk0C;
    /* 0x0E */ u16 unk0E;
    /* 0x10 */ u32 unk10;
} Rec14; /* 0x14 */
typedef struct Slot54 {
    /* 0x00 */ s16 unk00;
    /* 0x02 */ s16 unk02;
    /* 0x04 */ s16 unk04;
    /* 0x06 */ s16 unk06;
    /* 0x08 */ u16 unk08;
    /* 0x0A */ s8  unk0A;
} Slot54;

/* ---- views this function needs (new names, no TU collision) ---- */

/* the caller's 0x54 request slot (Slot54, seen past its declared tail) */
typedef struct {
    /* 0x00 */ u16 unk00;
    /* 0x02 */ u16 unk02;
    /* 0x04 */ u8  pad04[6];
    /* 0x0A */ u8  unk0A;
    /* 0x0B */ u8  pad0B[1];
    /* 0x0C */ u16 unk0C;
    /* 0x0E */ u8  unk0E[8];
} Req32A74;

/* the 0x14 record walked by this loop (Rec14, byte-resolved) */
typedef struct {
    /* 0x00 */ u16 unk00;
    /* 0x02 */ u16 unk02;
    /* 0x04 */ u16 unk04;
    /* 0x06 */ u8  unk06;
    /* 0x07 */ u8  unk07;
    /* 0x08 */ u8  unk08;
    /* 0x09 */ u8  unk09;
    /* 0x0A */ u8  unk0A;
    /* 0x0B */ u8  unk0B;
    /* 0x0C */ u8  pad0C[4];
    /* 0x10 */ s32 unk10;
} Rec32A74; /* 0x14 */

/* the 0x54 mixer channel at D_800A4988 (cf. Chan336A8) */
typedef struct {
    /* 0x00 */ s32 unk00;
    /* 0x04 */ s32 unk04;
    /* 0x08 */ u16 unk08;
    /* 0x0A */ u16 unk0A;
    /* 0x0C */ u16 unk0C;
    /* 0x0E */ u16 unk0E;
    /* 0x10 */ s16 unk10;
    /* 0x12 */ s16 unk12;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ u8  pad18[0xC];
    /* 0x24 */ s32 unk24;
    /* 0x28 */ u8  pad28[0xC];
    /* 0x34 */ u8  unk34;
    /* 0x35 */ u8  unk35;
    /* 0x36 */ u8  unk36;
    /* 0x37 */ u8  pad37[9];
    /* 0x40 */ s32 unk40;
    /* 0x44 */ s32 unk44;
    /* 0x48 */ s16 unk48;
    /* 0x4A */ s16 unk4A;
    /* 0x4C */ u8  unk4C;
    /* 0x4D */ u8  unk4D;
    /* 0x4E */ u8  unk4E;
    /* 0x4F */ u8  unk4F;
    /* 0x50 */ u8  pad50[2];
    /* 0x52 */ u8  unk52;
    /* 0x53 */ u8  unk53;
} Chan32A74; /* 0x54 */

/* the 0x48 voice at D_800A4C28 (Slot, byte-resolved) */
typedef struct {
    /* 0x00 */ s32 unk00;
    /* 0x04 */ s32 unk04;
    /* 0x08 */ u16 unk08;
    /* 0x0A */ u16 unk0A;
    /* 0x0C */ u16 unk0C;
    /* 0x0E */ u16 unk0E;
    /* 0x10 */ u8  pad10[4];
    /* 0x14 */ u16 unk14;
    /* 0x16 */ u8  pad16[2];
    /* 0x18 */ u16 unk18;
    /* 0x1A */ u8  pad1A[2];
    /* 0x1C */ s32 unk1C;
    /* 0x20 */ u8  pad20[0x1A];
    /* 0x3A */ u16 unk3A;
    /* 0x3C */ u16 unk3C;
    /* 0x3E */ u8  pad3E[2];
    /* 0x40 */ s32 unk40;
    /* 0x44 */ u8  unk44;
    /* 0x45 */ u8  unk45;
    /* 0x46 */ u8  pad46[2];
} Voice32A74; /* 0x48 */

extern s16 D_800C5328[];
extern s16 D_800C532A[];
extern s16 D_800A4646[];
extern A12 D_80064D44[];
extern B12 *D_8006A970[];
extern Slot D_800A4C28[];
extern u8 D_800A4988[];
extern s32 D_80073140[];
extern s16 D_800A46A2;
extern s16 D_800A4EF6;
extern s16 D_800A4EFA;
extern u8 D_800A4F19;
extern u8 D_800A4F1E;
extern u16 D_8006AA30[];
extern u16 D_8006AB30[];
extern u16 D_8006AB32[];
extern const u16 D_8007319E[];
extern const u16 D_800731A0[];
extern u16 D_8007321E;
extern u8 D_8006AED8[];

extern s16 func_8003F144(s32, s32, s32, C24 *);
extern s32 func_8003F380(s32, s32);
extern s32 func_80030CA4(u16);
extern void func_8002EFF8(s32, s32);
extern void func_8002F064(s32, s32);
extern void func_800316F8(void *);
extern void func_80033324(s32, s32);

void func_80032A74(Slot54 *arg0, s32 arg1, Rec14 *arg2, s32 flags) {
#define REQ ((Req32A74 *)arg0)
#define REC ((Rec32A74 *)arg2)
    C24 sp10;

    Chan32A74 *ch;
    Voice32A74 *vo;
    A12 *dd;
    B12 *q;
    u8 *cp;
    const u16 *tA;
    const u16 *tB;
    u8 *vB;
    s32 i2;
    u16 v;
    u32 vv;
    s32 idx;
    s32 w;
    s32 n;
    s32 flag;
    s32 h;
    s32 i;
    s32 b;
    s32 sub;
    u8 pan;
    u32 vol;
    u32 mp;
    u32 qq;
    s32 tb;
    u32 d;
    register s32 base __asm__("$2");
    u16 t16;
    s32 t8;
    s32 t32;

    tA = D_8007319E;
    tB = D_800731A0;
    vB = (u8 *)D_800A4C28;
    v = REQ->unk02;
    i = 7;
    cp = (u8 *)arg0 + 7;
    do {
        cp[0xE] = 0;
        i--;
        cp--;
    } while (i >= 0);
    REQ->unk0C = 0;

    for (;;) {
        b = REC->unk08;
        flag = 0;
        if ((b & 0x80) == 0) {
            dd = &D_80064D44[b];
            sub = REC->unk09;
            if (dd->unk06 != 0) {
                flag = (u32)sub < (u32)dd->unk07;
            }
            n = D_800C5328[b * 2];
            if (n < 0) {
                if (flag == 0) {
                    break;
                }
                n = D_800C532A[b * 2];
                if (n < 0) {
                    break;
                }
                if (sub >= D_800A4646[n * 12]) {
                    break;
                }
            }
        } else {
            n = 4;
        }
        if ((flags & 0x1000) && (flags & 0x7F) < 0x30U) {
            v >>= 1;
            flags = (flags & 0xFF80) | (0x2F - ((0x2F - (flags & 0x7F)) >> 1));
        }
        idx = func_80030CA4(v);
        if (idx != 0) {
            idx--;
            vo = (Voice32A74 *)(idx * 0x48 + (s32)vB);
            if ((b & 0x80) == 0) {
                q = &D_8006A970[n][REC->unk09];
                vo->unk1C = q->unk00;
                vo->unk18 = q->unk04;
                vo->unk3A = q->unk06;
                vo->unk3C = q->unk08;
            } else {
                if (func_8003F144(D_800A46A2, b & 0x7F, REC->unk09, &sp10) != 0) {
                    goto next;
                }
                h = func_8003F380(D_800A46A2, sp10.unk16);
                if (h < 0) {
                    goto next;
                }
                tb = sp10.unk04;
                vo->unk1C = h;
                vo->unk18 = tb << 8;
                vo->unk3A = sp10.unk10;
                vo->unk3C = sp10.unk12;
            }
            w = idx + 0x10;
            vo->unk00 = D_80073140[w];
            ch = (Chan32A74 *)(D_800A4988 + idx * 0x54);
            ch->unk4C = 0;
            ch->unk4A = 0x7FFF;
            if (REQ->unk00 & 0x80) {
                ch->unk4D = 0;
            } else {
                ch->unk4D = 1;
            }
            t16 = REC->unk02;
            ch->unk04 = 0;
            ch->unk08 = v;
            ch->unk0A = w;
            ch->unk00 = t16;
            t8 = REC->unk09;
            ch->unk0E = b;
            ch->unk36 = flag;
            ch->unk10 = n;
            ch->unk12 = 0;
            ch->unk0C = t8;
            t32 = REC->unk10;
            ch->unk4F = 0;
            ch->unk4E = 0x85;
            ch->unk14 = t32;
            __asm__ __volatile__("");
            vol = REC->unk06;
            if (D_800A4F1E != 0) {
                vol *= 0x70;
                vol >>= 7;
            }
            if (flags & 0x1000) {
                ch->unk48 = flags & 0x7F;
            } else {
                ch->unk48 = 0x7F;
            }
            ch->unk34 = vol & 0x7F;
            pan = REC->unk07;
            ch->unk35 = pan;
            if (flags & 0x8000) {
                ch->unk24 = REC->unk04 - 0x80;
            } else {
                ch->unk24 = REC->unk04;
            }
            ch->unk40 = (s32)func_80033324;
            ch->unk44 = arg1;
            if ((flags & 0x2000) && pan != 0) {
                if ((flags & 0x3000) == 0x3000) {
                    ch->unk53 = D_8006AED8[(u32)(flags & 0xF00) >> 8];
                } else {
                    ch->unk53 = flags & 0x7F;
                }
            } else {
                ch->unk53 = 0;
            }
            if (REC->unk02 == 0) {
                func_800316F8(ch);
            }
            {
                s16 u18 = vo->unk18;
                base = (u18 & 0xFF00) + (s8)u18 * 2;
            }
            base -= 0x3C00;
            d = ch->unk24;
            d -= base;
            if (d >= 0x5300) {
                vo->unk14 = 0x3FFF;
            } else {
                qq = D_8006AB30[d >> 8];
                qq = qq * (0x100 - (d & 0xFF));
                vo->unk14 = (qq + D_8006AB32[d >> 8] * (d & 0xFF)) >> 8;
            }
            vol = D_8006AA30[ch->unk34];
            mp = vol * D_800A4EFA;
            vol = mp >> 7;
            mp = vol * ch->unk48;
            vol = mp >> 7;
            if (pan != 0) {
                if (ch->unk53 != 0) {
                    pan += ch->unk53;
                    if (pan >= 0x42) {
                        pan -= 0x40;
                        if (pan >= 0x80) {
                            pan = 0x7F;
                        }
                    } else {
                        pan = 1;
                    }
                }
                if (D_800A4F19 != 0) {
                    vv = (vol * tA[pan]) >> 14;
                    vo->unk0A = vv;
                    vv = (vol * tB[0x7F - pan]) >> 14;
                    vo->unk08 = vv;
                } else {
                    vv = (vol * D_8007321E) >> 14;
                    vo->unk0A = vv;
                    vo->unk08 = vv;
                }
            } else {
                vv = vol;
                vo->unk08 = vv;
                vo->unk0A = vv;
            }
            ch->unk52 = pan;
            vo->unk0C = 0;
            vo->unk0E = 0;
            vo->unk04 = 0x6009F;
            __asm__ __volatile__("");
            if (D_800A4EF6 > REC->unk0A) {
                func_8002F064(1, vo->unk00);
            } else {
                func_8002F064(0, vo->unk00);
            }
            t16 = ch->unk0A;
            vo->unk45 = 0;
            vo->unk44 = 1;
            vo->unk40 = t16;
            if (REC->unk02 == 0) {
                func_8002EFF8(1, vo->unk00);
            }
            REQ->unk0C++;
            REQ->unk0E[idx] = 1;
        }
    next:
        if (REC->unk0B == 0) {
            break;
        }
        arg2++;
        v = REC->unk00;
    }
    if (REQ->unk0C == 0) {
        REQ->unk00 = 0;
    } else {
        REQ->unk0A = 4;
    }
}

#undef REQ
#undef REC
