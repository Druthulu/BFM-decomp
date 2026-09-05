/* func_800CF6D0 (md_MAIN_007, -O2) — builds SIX 0x18-byte "SPRT-with-own-tpage" primitives at the
 * D_800A5E60 prim-buffer cursor and addPrim()s each onto word[0] of the frame's ordering table
 * (D_800AA60C + D_800B9A02 * 0x4000), then republishes the advanced cursor.
 *
 * STATUS: NEAR — 249/249 instructions, 137 masked mismatches (rtu_match agrees). Everything
 * structural is byte-correct: length, frame (0x18, s0@8/s1@0xC/s2@0x10/s3@0x14) and the whole
 * callee-saved assignment ($v1=0xE1000089, $s0=0xE100008B then 0xE1000087, $s1=0xE1000086,
 * $s2=0xE100008D, $s3=0xE100008F, $t2=&D_800AA60C). Residual = intra-block SCHEDULE-REORDER
 * (see the bottom note).
 *
 * BYTE-PROVEN LEVERS (each measured here; the family exemplar is ov_SC01_000/func_8017DD04, §351):
 *  - The TAG word is a PLAIN CAST `*(u32*)p = (*(u32*)p & 0xFF000000) | (ot & 0xFFFFFF)` (§351).
 *    Spelling it as a P_TAG COMPONENT_REF grants /s, and cse's /s-write invalidation then KEEPS the
 *    D_800B9A02 index live across the store: the target re-loads `lhu D_800B9A02` for BOTH halves of
 *    every addPrim (12 loads), a /s tag store collapses that to 6.  Measured: -25 instructions
 *    (224 vs 249) with the bitfield spelling.
 *  - The OT WRITE must stay a P_TAG bitfield (§351) — that is what makes `D_800A5E60 = p` float into
 *    block 6's OT write (target idx 237-238).
 *  - BASE-SPLIT (§351): block 1's OT read goes off the RAW symbol `(s32)D_800AA60C + idx`
 *    (-> lui $at / addu / lw %lo), then `ob = D_800AA60C;` and every later reference through `ob`
 *    (-> addu $x,$idx,$t2 / lw 0($x)).  This is the target's exact asymmetry at idx 46-48 vs 57.
 *  - `(u16)D_800B9A02`, never `*(u16*)&D_800B9A02` (§351).
 *  - `arg0 = arg0 - 0xA0;` IN PLACE (§195-I): a second SET of the parameter pseudo kills cse's
 *    constant fold, so `arg0 + 0x100` stays `addiu $v1,$a0,0x100` instead of folding to
 *    `addiu $v1,$a0,0x60`. Without it the target's `addiu $a0,$a0,-0xA0` never appears.
 *  - The field stores are STRUCT MEMBERS, not casts: cast spelling loses 4-6 instructions
 *    (243 vs 249) by shedding callee-saved registers (§379/§351 — /s is a per-access dial).
 *  - `u32 pad[2]` — 8 bytes of unreferenced frame, the exemplar's trick: 4 saves = 0x10, the target
 *    frame is 0x18 and its saves start at 0x8.  Without it: frame 0x10 and 9 extra mismatches.
 *  - The `tpage` store FIRST in each block (before `len`): this is the only spelling found that
 *    hoists FIVE single-use tpage constants to the block top, giving the target's 4 callee-saved
 *    registers.  `len`-first (the boot.c -O0 twin's source order, func_8001212C) yields only 3 and
 *    247 instructions.  19 field orders were swept; this is the unique 249.
 *
 * MEASURED INERT (do not re-grind): register pins on the tpage constants ($16-$19 gives 249 but a
 * worse top order), pins on the masks (+4..+7 ins, the constant rematerialises), `__asm__("":"=r")`
 * re-ties on any tpage constant (best 155), `volatile` on the tag word / the OT accesses / a
 * `"memory"` fence, /s-denial on any subset of the halfword stores, a /s COMPONENT_REF on the
 * D_800B9A02 load (235 ins — it also revives the CSE the tag store must kill), `* 0x4000` for
 * `<< 14`, `p++` vs `p = p + 0x18`, `ob` assigned before/after block 1, `u32 mlo/mhi` locals,
 * swapping the `|` operands, and 19 field orders.  The plateau is EXACTLY 137 across all of them.
 *
 * RESIDUAL (class SCHEDULE-REORDER, gcc-2.7.2 sched1): in blocks 1/3/4/5/6 my schedule emits the
 * QImode field stores as a group, then floats `lhu D_800B9A02` + the `lw 0(p)` tag read up, then the
 * HImode stores; the target emits all 13 stores in source order with both loads after them.  Block 2
 * is byte-identical, so it is a tie-break/queue difference, not a dependence one: the cc1 `-dS` dump
 * shows every one of those stores at priority 2 with equal ref counts, so `rank_for_schedule` is
 * deciding on the last-scheduled-insn CLASS, which no C spelling reached.  Second residual: the two
 * masks are register-swapped ($t1<->$t3, 12 instructions) — a local-alloc density tie.
 * decomp-permuter (SCHEDULE-REORDER weights) reached 122 only by MOVING block 5's
 * `p->clut = 0x7880` into block 4, which is semantically wrong, so it is not carried here.
 */

typedef struct { u32 addr:24; u32 len:8; } P_TAG_800CF6D0;
typedef struct {
    u8 pad0, pad1, pad2, len;
    u32 tpage;
    u8 r0, g0, b0, code;
    s16 x0, y0;
    u8 u0, v0;
    u16 clut;
    s16 w, h;
} Sprt24_800CF6D0;

extern u8 *D_800A5E60;
extern u8 D_800AA60C[];
extern s16 D_800B9A02;

void func_800CF6D0(s32 arg0, s32 arg1)
{
    Sprt24_800CF6D0 *p;
    u8 *ob;
    u32 pad[2];

    p = (Sprt24_800CF6D0 *)D_800A5E60;
    arg0 = arg0 - 0xA0;
    arg1 = arg1 - 0x78;

    p->tpage = 0xE1000089;
    p->len = 5;
    p->code = 0x64;
    p->clut = 0x7940;
    p->b0 = 0x80;
    p->g0 = 0x80;
    p->r0 = 0x80;
    p->x0 = arg0;
    p->y0 = arg1;
    p->u0 = 0;
    p->v0 = 0;
    p->w = 0x100;
    p->h = 0x100;
    *(u32 *)p = (*(u32 *)p & 0xFF000000) | (*(u32 *)((s32)D_800AA60C + (((u16)D_800B9A02) << 14)) & 0xFFFFFF);
    ob = D_800AA60C;
    ((P_TAG_800CF6D0 *)((s32)ob + (((u16)D_800B9A02) << 14)))->addr = (u32)p;
    p = (Sprt24_800CF6D0 *)((u8 *)p + 0x18);

    p->tpage = 0xE100008B;
    p->len = 5;
    p->code = 0x64;
    p->clut = 0x7940;
    p->b0 = 0x80;
    p->g0 = 0x80;
    p->r0 = 0x80;
    p->x0 = arg0 + 0x100;
    p->y0 = arg1;
    p->u0 = 0;
    p->v0 = 0;
    p->w = 0x100;
    p->h = 0x100;
    *(u32 *)p = (*(u32 *)p & 0xFF000000) | (*(u32 *)((s32)ob + (((u16)D_800B9A02) << 14)) & 0xFFFFFF);
    ((P_TAG_800CF6D0 *)((s32)ob + (((u16)D_800B9A02) << 14)))->addr = (u32)p;
    p = (Sprt24_800CF6D0 *)((u8 *)p + 0x18);

    p->tpage = 0xE100008D;
    p->len = 5;
    p->code = 0x64;
    p->clut = 0x7940;
    p->b0 = 0x80;
    p->g0 = 0x80;
    p->r0 = 0x80;
    p->x0 = arg0 + 0x200;
    p->y0 = arg1;
    p->u0 = 0;
    p->v0 = 0;
    p->w = 0x100;
    p->h = 0x100;
    *(u32 *)p = (*(u32 *)p & 0xFF000000) | (*(u32 *)((s32)ob + (((u16)D_800B9A02) << 14)) & 0xFFFFFF);
    ((P_TAG_800CF6D0 *)((s32)ob + (((u16)D_800B9A02) << 14)))->addr = (u32)p;
    p = (Sprt24_800CF6D0 *)((u8 *)p + 0x18);

    p->tpage = 0xE100008F;
    p->len = 5;
    p->code = 0x64;
    p->clut = 0x7940;
    p->b0 = 0x80;
    p->g0 = 0x80;
    p->r0 = 0x80;
    p->x0 = arg0 + 0x300;
    p->y0 = arg1;
    p->u0 = 0;
    p->v0 = 0;
    p->w = 0x40;
    p->h = 0x100;
    *(u32 *)p = (*(u32 *)p & 0xFF000000) | (*(u32 *)((s32)ob + (((u16)D_800B9A02) << 14)) & 0xFFFFFF);
    ((P_TAG_800CF6D0 *)((s32)ob + (((u16)D_800B9A02) << 14)))->addr = (u32)p;
    p = (Sprt24_800CF6D0 *)((u8 *)p + 0x18);

    p->tpage = 0xE1000086;
    p->len = 5;
    p->code = 0x64;
    p->clut = 0x7880;
    p->b0 = 0x80;
    p->g0 = 0x80;
    p->r0 = 0x80;
    p->x0 = -0xA0;
    p->y0 = -0x78;
    p->u0 = 0x20;
    p->v0 = 0;
    p->w = 0xA0;
    p->h = 0x100;
    *(u32 *)p = (*(u32 *)p & 0xFF000000) | (*(u32 *)((s32)ob + (((u16)D_800B9A02) << 14)) & 0xFFFFFF);
    ((P_TAG_800CF6D0 *)((s32)ob + (((u16)D_800B9A02) << 14)))->addr = (u32)p;
    p = (Sprt24_800CF6D0 *)((u8 *)p + 0x18);

    p->tpage = 0xE1000087;
    p->len = 5;
    p->code = 0x64;
    p->clut = 0x7880;
    p->b0 = 0x80;
    p->g0 = 0x80;
    p->r0 = 0x80;
    p->x0 = 0;
    p->y0 = -0x78;
    p->u0 = 0x40;
    p->v0 = 0;
    p->w = 0xA0;
    p->h = 0x100;
    *(u32 *)p = (*(u32 *)p & 0xFF000000) | (*(u32 *)((s32)ob + (((u16)D_800B9A02) << 14)) & 0xFFFFFF);
    ((P_TAG_800CF6D0 *)((s32)ob + (((u16)D_800B9A02) << 14)))->addr = (u32)p;
    p = (Sprt24_800CF6D0 *)((u8 *)p + 0x18);

    D_800A5E60 = (u8 *)p;
}
