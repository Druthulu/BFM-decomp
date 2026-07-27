/* func_8017DC1C @ ov_SC07_006 (subseg ov_SC07_006_jr_8017BEBC) — behemoth #8, 1,518 ins.
 *
 * GATE: .venv/bin/python tools/match_one.py func_8017DC1C \
 *         --c .run/giants/s21_func_8017DC1C_b1.c \
 *         --asm-subdir asm/ov_SC07_006/nonmatchings/ov_SC07_006_jr_8017BEBC
 *       => MATCH (1518 ins)          [pin-free; run through the §77 probe copy,
 *                                     see "PROBE" below — SVECTOR2 is a SHARED type]
 *
 * NOT BANKED. match_one masks jal/HI16/LO16 and never links. Independently checked
 * here (the three things match_one is blind to):
 *   §81  0 `jr $vX` — no jump table, NO carve chain needed. (`jr $ra` only.)
 *   §84  0 `%lo(SYM+N)` in the emitted asm — no derived offsets.
 *   §87  all 64 D_ symbols resolve as dlabels in asm/ov_SC07_006/data/tail.data.s.
 *
 * PROBE (§77): SVECTOR2 lives in src/shared/engine_types.h, which match_one cannot see
 * (-Iinclude only). Gate through:
 *   { echo '#include "common.h"';
 *     echo '#include "../src/shared/engine_types.h"';
 *     cat this_file; } > probe.c
 * The include is deliberately NOT in this file: the real TU
 * src/ov_SC07_006/ov_SC07_006_jr_8017BEBC.c already reaches engine_types.h via
 * `#include "../shared/engine_core.h"`, so adding it here would be a double include.
 *
 * ------------------------------------------------------------------ what it is
 * A morph/keyframe blender. 25 statements, each interpolating one model's vertex
 * block from keyframe `b` toward keyframe `a` by the 1.12 fixed-point factor `t`.
 * ZERO `jal`: the 25 statements are 25 expansions of ONE `static inline` helper.
 *
 * ------------------------------------------------------------------ the levers
 * L1  `static inline`, NOT a macro and NOT an out-of-line static. THE structural
 *     lever, and it is triple-witnessed by the bytes:
 *       (a) 0 jal, 25 byte-identical 60-ins bodies;
 *       (b) FRAME. gcc-2.7.2 gives each inline expansion its OWN copy of the
 *           callee frame (integrate.c allocates DECL_FRAME_SIZE per expansion).
 *           Measured: 1 body = 24, 2 expansions = 48, 25 expansions = 600 = 0x258
 *           — the target's exact `addiu $sp,$sp,-0x258`. The frame is FREE; it is
 *           not a padding hack. A macro would have given 24 for the whole function.
 *       (c) the `addu $a3,$a2,$zero` in the same-symbol blocks (1,2,3,4,8,9,10,11,
 *           15,16) is integrate.c's copy_to_mode_reg of the SECOND argument after
 *           cse folded the two identical global loads into one register.
 * L2  the body assigns the two pointer PARAMS to LOCALS (`pb = b; pa = a;`) and
 *     walks the locals. Incrementing the params directly loses BOTH preheader
 *     moves (`addu $t2,$a3,$zero` / `addu $t0,$a2,$zero`): with the params readonly
 *     the arg reg and the loop biv are one pseudo and combine folds the copy into
 *     the load. 2 moves x 25 blocks = 50 ins.
 * L3  `i = o->n;` is read BEFORE the two copies. Source order here survives into
 *     the schedule: the target fills the `lw $t3,0x10($a1)` load-delay with the
 *     `pb` copy and the `beqz` delay with the `pa` copy. With the copies first,
 *     the count load needs a `nop` AND the reorg pass steals the `pb` copy into
 *     the `j` delay slot (which the target leaves as `nop`).
 * L4  increment order `d++; pb++; pa++;` — the reverse of the read order.
 *     loop.c PREPENDS each biv to loop_iv_list, so the preheader giv-init order
 *     (`$a3=pa+4`, `$a2=pb+4`, `$a1=d+4`) is the reverse of the increment order.
 *     All 6 permutations measured; this is the only one that puts the three
 *     `+4` givs in the target's registers. See the report's table.
 * L5  the else-branch is INDEX arithmetic, not a mask: `(u32 *)&o->dst + (o->dst >> 2)`
 *     gives `srl 2; sll 2; addiu 0xC; addu` — 4 separate insns. `o->dst & ~3`
 *     would collapse to a single `andi 0xfffc`. `dst` must be UNSIGNED (`srl`, not `sra`).
 * L6  `o->mode == 1` is a literal and stays one: an EQUALITY test has no `slti`
 *     form on MIPS, so the 1 is always materialised (`addiu $vX,$zero,1`). The
 *     §78/`slti` literal-position law does NOT apply to `==` — do not "fix" this
 *     into a variable.
 *
 * Drop-one ablations (all on the b1 base, all measured) — see s21_8017DC1C_report.md.
 */
/* ---- the object ---------------------------------------------------------- *
 * mode == 1 : `dst` (+0x0C) is a POINTER to the vertex block.
 * otherwise : the vertex block is INLINE and `dst` is a byte count; the data
 *             starts at ((u32 *)&o->dst)[o->dst >> 2].
 * `n` (+0x10) is the vertex count either way.                                 */
typedef struct {
    s32 unk0;   /* 0x00 */
    s32 mode;   /* 0x04 */
    s32 unk8;   /* 0x08 */
    u32 dst;    /* 0x0C */
    s32 n;      /* 0x10 */
} Morph_8017DC1C;

/* ---- per-overlay globals (ov_SC07_006 tail.data) ------------------------- *
 * Every one of these is an initialised POINTER word in asm/ov_SC07_006/data/
 * tail.data.s (e.g. D_801BF4F4 = .word D_801AD4DC, D_801C1E14 = .word D_801BFD0C).
 * None of them is declared anywhere in the tree today — these spellings are free
 * choices and establish the canon.                                            */
extern Morph_8017DC1C *D_801BF4F4;
extern Morph_8017DC1C *D_801BF4F8;
extern Morph_8017DC1C *D_801BF4FC;
extern Morph_8017DC1C *D_801BF500;
extern Morph_8017DC1C *D_801BF504;
extern Morph_8017DC1C *D_801BF508;
extern Morph_8017DC1C *D_801BF50C;
extern Morph_8017DC1C *D_801BF510;
extern Morph_8017DC1C *D_801BF514;
extern Morph_8017DC1C *D_801BF518;
extern Morph_8017DC1C *D_801BF51C;
extern Morph_8017DC1C *D_801BF520;
extern Morph_8017DC1C *D_801BF524;
extern Morph_8017DC1C *D_801BF528;
extern Morph_8017DC1C *D_801BF52C;
extern Morph_8017DC1C *D_801BF530;
extern Morph_8017DC1C *D_801BF534;
extern Morph_8017DC1C *D_801BF538;
extern Morph_8017DC1C *D_801BF650;
extern Morph_8017DC1C *D_801BF65C;
extern Morph_8017DC1C *D_801BF660;
extern Morph_8017DC1C *D_801BF684;
extern Morph_8017DC1C *D_801BF6A4;
extern Morph_8017DC1C *D_801BF6A8;
extern Morph_8017DC1C *D_801BF6AC;

extern SVECTOR2 *D_801C1E14;
extern SVECTOR2 *D_801C1E18;
extern SVECTOR2 *D_801C1E1C;
extern SVECTOR2 *D_801C1E20;
extern SVECTOR2 *D_801C1E24;
extern SVECTOR2 *D_801C1E28;
extern SVECTOR2 *D_801C1E2C;
extern SVECTOR2 *D_801C1E30;
extern SVECTOR2 *D_801C1E34;
extern SVECTOR2 *D_801C1E38;
extern SVECTOR2 *D_801C1E3C;
extern SVECTOR2 *D_801C1E40;
extern SVECTOR2 *D_801C1E44;
extern SVECTOR2 *D_801C1E48;
extern SVECTOR2 *D_801C1E4C;
extern SVECTOR2 *D_801C1E50;
extern SVECTOR2 *D_801C1E54;
extern SVECTOR2 *D_801C1E58;
extern SVECTOR2 *D_801C1E60;
extern SVECTOR2 *D_801C1E64;
extern SVECTOR2 *D_801C1E68;
extern SVECTOR2 *D_801C1E6C;
extern SVECTOR2 *D_801C1E70;
extern SVECTOR2 *D_801C1E74;
extern SVECTOR2 *D_801C1E78;
extern SVECTOR2 *D_801C1E7C;
extern SVECTOR2 *D_801C1E80;
extern SVECTOR2 *D_801C1E84;
extern SVECTOR2 *D_801C1E88;
extern SVECTOR2 *D_801C1E8C;
extern SVECTOR2 *D_801C1E90;
extern SVECTOR2 *D_801C1E94;
extern SVECTOR2 *D_801C1E98;
extern SVECTOR2 *D_801C1E9C;
extern SVECTOR2 *D_801C1EA0;
extern SVECTOR2 *D_801C1EA4;
extern SVECTOR2 *D_801C1EA8;
extern SVECTOR2 *D_801C1EAC;
extern SVECTOR2 *D_801C1EB0;


/* MUST be `inline` — see L1. 25 expansions == 1518 ins, 0 jal, frame 25*24=0x258. */
static inline void morph_lerp(Morph_8017DC1C *o, SVECTOR2 *b, SVECTOR2 *a, s32 t)
{
    SVECTOR2 *d;
    SVECTOR2 *pa;
    SVECTOR2 *pb;
    s32 i;

    if (o->mode == 1) {
        d = (SVECTOR2 *)o->dst;
    } else {
        d = (SVECTOR2 *)((u32 *)&o->dst + (o->dst >> 2));
    }
    i = o->n;                       /* L3: before the copies */
    pb = b;                         /* L2 */
    pa = a;                         /* L2 */
    for (; i != 0; i--) {
        d->vx = pb->vx + (((pa->vx - pb->vx) * t) >> 12);
        d->vy = pb->vy + (((pa->vy - pb->vy) * t) >> 12);
        d->vz = pb->vz + (((pa->vz - pb->vz) * t) >> 12);
        pa++;
        pb++;
        d++;
    }
}

void func_8017DC1C(s32 t)
{
    morph_lerp(D_801BF4F4, D_801C1E14, D_801C1E18, t);
    morph_lerp(D_801BF4F8, D_801C1E1C, D_801C1E1C, t);
    morph_lerp(D_801BF4FC, D_801C1E20, D_801C1E20, t);
    morph_lerp(D_801BF500, D_801C1E24, D_801C1E24, t);
    morph_lerp(D_801BF504, D_801C1E28, D_801C1E28, t);
    morph_lerp(D_801BF508, D_801C1E40, D_801C1E50, t);
    morph_lerp(D_801BF50C, D_801C1E44, D_801C1E54, t);
    morph_lerp(D_801BF510, D_801C1E48, D_801C1E58, t);
    morph_lerp(D_801BF514, D_801C1E4C, D_801C1E4C, t);
    morph_lerp(D_801BF518, D_801C1E60, D_801C1E60, t);
    morph_lerp(D_801BF51C, D_801C1E64, D_801C1E64, t);
    morph_lerp(D_801BF520, D_801C1E68, D_801C1E68, t);
    morph_lerp(D_801BF524, D_801C1E80, D_801C1E90, t);
    morph_lerp(D_801BF528, D_801C1E84, D_801C1E94, t);
    morph_lerp(D_801BF52C, D_801C1E88, D_801C1E98, t);
    morph_lerp(D_801BF530, D_801C1E8C, D_801C1E8C, t);
    morph_lerp(D_801BF534, D_801C1E9C, D_801C1E9C, t);
    morph_lerp(D_801BF538, D_801C1EA0, D_801C1EA4, t);
    morph_lerp(D_801BF650, D_801C1EA4, D_801C1EA8, t);
    morph_lerp(D_801BF65C, D_801C1E2C, D_801C1E38, t);
    morph_lerp(D_801BF660, D_801C1E30, D_801C1E3C, t);
    morph_lerp(D_801BF684, D_801C1EAC, D_801C1E34, t);
    morph_lerp(D_801BF6A4, D_801C1E6C, D_801C1E78, t);
    morph_lerp(D_801BF6A8, D_801C1E70, D_801C1E7C, t);
    morph_lerp(D_801BF6AC, D_801C1E74, D_801C1EB0, t);
}
