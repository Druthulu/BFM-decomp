/* func_801837B0 — ov_SC02_041, TU ov_SC02_041_jr_8017BEBC.c.
 *
 * Family of 4 (824 templatable ins): func_801837B0 / func_80186DD4 (ov_SC04_002) /
 * func_801861A4 (ov_SC04_005) / func_80182810 (ov_SC04_007).
 *
 * Draws the two triangles of an entity's ground marker: builds a 4-vertex gouraud packet on
 * the stack (verts 0x10, colours 0x30, code 0x40), whose colour ramp is derived from the s32
 * at a0+0x1C (*15, then >>1 for the second component, then -0x10 clamped-at-0 for the far
 * pair).  Bit 0 of the u16 at a0+0x70 picks which channel carries the bright value.  Then the
 * camera matrix cached at D_800AF630+0x18 is loaded and two rtpt+rtps+avsz4 groups run over a
 * sliding window of the SVECTORs at a0+0xDC..0x104 (stride 8), queueing the packet through
 * func_80017714 whenever the GTE flag masked with ~0x1000 is clear.
 *
 * DECLARATION SURFACE (whole-TU one-pass grep, D2):
 *   * D_800AF630   — TU line 53   `extern u8 D_800AF630[];`      (identical extern repeated, legal)
 *   * func_80017714— TU line 4324 `extern void func_80017714(void *);` (identical extern repeated)
 *   * func_801837B0— TU line 5235 `extern void func_801837B0(s32 a0);` — the definition below
 *     uses that exact prototype, so no SELF-axis rename is needed.
 *   * every type tag and every gte_ macro carries the _801837B0 suffix: this TU already defines
 *     gte_ldv0 twice (lines 2687 and 4332, different bodies) and gte_SetRotMatrix at 5033, all
 *     ABOVE the splice point at 5246, so unsuffixed names would collide/redefine.
 *
 * CODEGEN NOTES (what the .s pins):
 *   * ONE aggregate `pkt` holds verts + colours + code.  The code word MUST live inside the
 *     object handed to func_80017714 or gcc dead-stores it (a separate `s32 tag` local is
 *     eliminated and the frame comes out 8 short: 0x80 instead of 0x88).
 *   * `c` is s16 but `d` is s32 — that asymmetry IS in the target: after the -0x10 the `c < 0`
 *     test needs `sll $v1,$v1,16; bgez` (HImode) while the `d < 0` test is a bare `bgez $a3`
 *     (an `sra` by 17 already leaves 18 sign bits, so no re-extension is emitted).
 *   * `p`/`q` are a SECOND pair of s16 locals holding the value actually stored.  They produce
 *     the `addu $a1,$v1,$zero` / `addu $a2,$a3,$zero` copies in the head and after each -0x10,
 *     and they occupy $a1/$a2 — which is what pushes the D_800AF630 base out to $t0 and the
 *     reload register out to $t1, exactly as the target has them.  `q` must be s16, not s32: an
 *     s32 `q` is copy-propagated into `d` and the three `addu $a2,...` copies vanish.
 *   * The colour writes are CHAINED assignments; gcc expands `A = B = C = D = q` innermost-first,
 *     so the store order is D,C,B,A and exactly one QImode conversion temp is materialised per
 *     chain ($a0 for the first, $v0 reused for the rest).
 *   * The -0x10 on the second channel goes through a BLOCK-SCOPED `s32 e`, not `d -= 0x10`.
 *     Two separate effects, both required:
 *       - splitting `d` into `d` + `e` cuts REG_N_REFS(d) from 10 to 4, which drops d below p
 *         and q in global.c's allocno priority.  With `d -= 0x10` the ranking is d,c,p,q and the
 *         three registers come out permuted ($a1/$a2/$a3 = d/p/q instead of p/q/d) — §137.
 *       - scoping `e` INSIDE each arm (one pseudo per arm instead of one shared) is what fixes
 *         the last residual: a function-scope `e` leaves `addiu $a3,$a3,-0x10` scheduled one slot
 *         too early, ahead of the `addu $v0,$a2,$zero` chain temp.  That reorder was INVARIANT
 *         under every legal statement permutation (8 tried), i.e. it was never a source-order
 *         problem — it is the allocno/live-range split.
 */

extern u8 D_800AF630[];
extern void func_80017714(void *);

typedef struct { s16 vx, vy, vz, pad; } SV_801837B0;   /* 8 bytes */
typedef struct { u8 r, g, b, cd; } CV_801837B0;        /* 4 bytes */

typedef struct {
    SV_801837B0 v[4];    /* +0x00 : sxy0..3 (v[0].vz doubles as the otz slot) */
    CV_801837B0 rgb[4];  /* +0x20 */
    u32 code;            /* +0x30 */
    u32 pad;             /* +0x34 */
} PKT_801837B0;          /* 0x38 */

#define gte_ldv0_801837B0(r0) __asm__ volatile (  \
    "lwc2 $0, 0( %0 );"                          \
    "lwc2 $1, 4( %0 )"                           \
    :                                            \
    : "r"( r0 ) )

#define gte_ldv3_801837B0(r0, r1, r2) __asm__ volatile ( \
    "lwc2 $0, 0( %0 );"                          \
    "lwc2 $1, 4( %0 );"                          \
    "lwc2 $2, 0( %1 );"                          \
    "lwc2 $3, 4( %1 );"                          \
    "lwc2 $4, 0( %2 );"                          \
    "lwc2 $5, 4( %2 )"                           \
    :                                            \
    : "r"( r0 ), "r"( r1 ), "r"( r2 ) )

#define gte_rtps_801837B0() __asm__ volatile ("nop;nop;rtps")
#define gte_rtpt_801837B0() __asm__ volatile ("nop;nop;rtpt")
#define gte_avsz4_801837B0() __asm__ volatile ("nop;nop;avsz4")

#define gte_stsxy_801837B0(r0) __asm__ volatile ( \
    "swc2 $14, 0( %0 )"                          \
    :                                            \
    : "r"( r0 )                                  \
    : "memory" )

#define gte_stsxy3_801837B0(r0, r1, r2) __asm__ volatile ( \
    "swc2 $12, 0( %0 );"                         \
    "swc2 $13, 0( %1 );"                         \
    "swc2 $14, 0( %2 )"                          \
    :                                            \
    : "r"( r0 ), "r"( r1 ), "r"( r2 )            \
    : "memory" )

#define gte_stotz_801837B0(r0) __asm__ volatile ( \
    "swc2 $7, 0( %0 )"                           \
    :                                            \
    : "r"( r0 )                                  \
    : "memory" )

#define gte_stflg_801837B0(r0) __asm__ volatile ( \
    "cfc2 $12, $31;"                             \
    "nop;"                                       \
    "sw $12, 0( %0 )"                            \
    :                                            \
    : "r"( r0 )                                  \
    : "$12", "memory" )

#define gte_SetRotMatrix_801837B0(r0) __asm__ volatile ( \
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

#define gte_SetTransMatrix_801837B0(r0) __asm__ volatile ( \
    "lw $12, 20( %0 );"                                  \
    "lw $13, 24( %0 );"                                  \
    "ctc2 $12, $5;"                                      \
    "lw $14, 28( %0 );"                                  \
    "ctc2 $13, $6;"                                      \
    "ctc2 $14, $7"                                       \
    :                                                    \
    : "r"( r0 )                                          \
    : "$12", "$13", "$14" )

void func_801837B0(s32 a0)
{
    PKT_801837B0 pkt;   /* 0x10 */
    s32 flag1;          /* 0x48 */
    s32 flag2;          /* 0x4C */
    s32 otz;            /* 0x50 */
    u8 *base;
    s32 *m;
    s16 c, p, q;
    s32 d;

    c = *(s32 *)(a0 + 0x1C) * 15;
    base = D_800AF630;
    p = c;
    d = c >> 1;
    q = d;

    if ((*(u16 *)(a0 + 0x70) & 1) == 0) {
        pkt.rgb[0].b = pkt.rgb[1].b = p;
        pkt.rgb[0].r = pkt.rgb[1].r = pkt.rgb[0].g = pkt.rgb[1].g = q;
        c -= 0x10;
        p = c;
        {
            s32 e;          /* block-scoped: one pseudo per arm (§136/L1) */
            e = d - 0x10;
            q = e;
            if (c < 0) {
                p = 0;
            }
            if (e < 0) {
                q = 0;
            }
        }
        pkt.rgb[2].b = pkt.rgb[3].b = p;
        pkt.rgb[2].r = pkt.rgb[3].r = pkt.rgb[2].g = pkt.rgb[3].g = q;
    } else {
        pkt.rgb[0].r = pkt.rgb[1].r = p;
        pkt.rgb[0].g = pkt.rgb[1].g = pkt.rgb[0].b = pkt.rgb[1].b = q;
        c -= 0x10;
        p = c;
        {
            s32 e;          /* block-scoped: one pseudo per arm (§136/L1) */
            e = d - 0x10;
            q = e;
            if (c < 0) {
                p = 0;
            }
            if (e < 0) {
                q = 0;
            }
        }
        pkt.rgb[2].r = pkt.rgb[3].r = p;
        pkt.rgb[2].g = pkt.rgb[3].g = pkt.rgb[2].b = pkt.rgb[3].b = q;
    }

    pkt.code = 0x50000000;

    m = (s32 *)(base + 0x18);
    gte_SetRotMatrix_801837B0(m);
    gte_SetTransMatrix_801837B0(m);

    gte_ldv3_801837B0((SV_801837B0 *)(a0 + 0xFC), (SV_801837B0 *)(a0 + 0x104),
                      (SV_801837B0 *)(a0 + 0xEC));
    gte_rtpt_801837B0();
    gte_stflg_801837B0(&flag1);
    gte_stsxy3_801837B0(&pkt.v[0], &pkt.v[1], &pkt.v[2]);
    gte_ldv0_801837B0((SV_801837B0 *)(a0 + 0xF4));
    gte_rtps_801837B0();
    gte_stflg_801837B0(&flag2);
    flag1 = flag1 | flag2;
    gte_stsxy_801837B0(&pkt.v[3]);
    gte_avsz4_801837B0();
    gte_stotz_801837B0(&otz);
    if ((flag1 & 0xFFFFEFFF) == 0) {
        pkt.v[0].vz = (s16)otz;
        func_80017714(&pkt.v[0]);
    }

    gte_ldv3_801837B0((SV_801837B0 *)(a0 + 0xEC), (SV_801837B0 *)(a0 + 0xF4),
                      (SV_801837B0 *)(a0 + 0xDC));
    gte_rtpt_801837B0();
    gte_stflg_801837B0(&flag1);
    gte_stsxy3_801837B0(&pkt.v[0], &pkt.v[1], &pkt.v[2]);
    gte_ldv0_801837B0((SV_801837B0 *)(a0 + 0xE4));
    gte_rtps_801837B0();
    gte_stflg_801837B0(&flag2);
    flag1 = flag1 | flag2;
    gte_stsxy_801837B0(&pkt.v[3]);
    gte_avsz4_801837B0();
    gte_stotz_801837B0(&otz);
    if ((flag1 & 0xFFFFEFFF) == 0) {
        pkt.v[0].vz = (s16)otz;
        func_80017714(&pkt.v[0]);
    }
}
