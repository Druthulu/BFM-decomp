// @class: regalloc-order
// @stuck: none — MATCH (99 ins, match_one masked)
//
// Levers used (all C-level, no pins / no asm barriers):
//  * loop 1 = pointer-walk IV (`p = D_8011D030; p++`)  -> the `la` hoisted into $s0 before the loop.
//  * loop 2 = BYTE-OFFSET IV re-added to the symbol INSIDE the loop
//        `Ent *e = (Ent *)(off + (s32)D_8011D030); ... off += 0x58;`
//    Writing `D_8011D030[i]` instead makes gcc split the address into THREE separate pointer
//    givs (one per field offset) -> +9 instructions.  The `off + (s32)base` form keeps ONE
//    base and reproduces the target's per-iteration `lui/addiu/addu $a1,$a2,$v0`.
//  * per-ARM local `s32 v` (declared inside each if-arm, NOT function scope): a function-scope
//    temp becomes one global allocno spanning all three arms -> the whole loop's regs shift up
//    by one ($a0/$a1/$a2/$a3 instead of $v0/$a0/$a1/$a2).  Per-arm locals give the target's
//    $v0/$v1/$a0/$a1/$a2 assignment and the in-place `sll $v0,$v0,16 / sra $v0,$v0,16`.
//  * arm A's THIRD group needs its OWN temp `w` (separate from `v`): the `o->flags |= 1`
//    read-modify-write is live across the sign-extend, so `w` must not share `v`'s quantity —
//    with one shared temp the flags store schedules BEFORE the sll/sra (4-instruction residual).
//  * arm B's first group caches `s = o->sub` in the `else if` test so it reuses the test's
//    `lw $v1,0x34($a0)` (the later two groups reload through `o->sub` because the intervening
//    `sw` invalidates it) -> reproduces the target's nop-in-the-load-delay-slot.
//  * u16 field load + `(s16)` cast at the s32 store = `lhu` + `sll/sra` (the field is unsigned;
//    a `short` field would emit `lh` and no shift pair).
typedef unsigned char  u8;
typedef unsigned short u16;
typedef short          s16;
typedef int            s32;
typedef unsigned int   u32;

typedef struct Sub {
    /* 0x00 */ s32 pad00[5];
    /* 0x14 */ s32 f14;
    /* 0x18 */ s32 f18;
    /* 0x1C */ s32 f1C;
} Sub;

typedef struct Obj {
    /* 0x00 */ u16 state;
    /* 0x02 */ u16 pad02[3];
    /* 0x08 */ u16 x;
    /* 0x0A */ u16 y;
    /* 0x0C */ u16 z;
    /* 0x0E */ u16 pad0E[15];
    /* 0x2C */ u16 flags;
    /* 0x2E */ u16 pad2E[3];
    /* 0x34 */ Sub *sub;
    /* 0x38 */ s32 pad38[4];
    /* 0x48 */ s32 f48;
    /* 0x4C */ s32 f4C;
    /* 0x50 */ s32 f50;
    /* 0x54 */ s32 pad54;
} Obj;

typedef struct Ent {
    /* 0x00 */ u16 f0;
    /* 0x02 */ u16 pad02[2];
    /* 0x06 */ u16 f6;
    /* 0x08 */ u16 pad08;
    /* 0x0A */ u16 fA;
    /* 0x0C */ u16 pad0C;
    /* 0x0E */ u16 fE;
    /* 0x10 */ u8  pad10[0x10];
    /* 0x20 */ Obj *obj;
    /* 0x24 */ u8  pad24[0x34];
} Ent;

extern Ent D_8011D030[];
extern void (**D_80126728)(Ent *);

void func_80165CA0(void)
{
    Ent *p;
    Obj *o;
    Sub *s;
    s32 i;
    s32 off;

    i = 0;
    p = D_8011D030;
    do {
        if (p->f0 != 0) {
            D_80126728[p->f0](p);
        }
        i = i + 1;
        p = p + 1;
    } while (i < 0x1e);

    i = 0;
    off = 0;
    do {
        Ent *e = (Ent *)(off + (s32)D_8011D030);
        o = e->obj;
        if (o != 0) {
            if (o->state == 1) {
                s32 v;
                s32 w;
                v = e->f6;
                o->x = v;
                o->f48 = (s16)v;
                v = e->fA;
                o->y = v;
                o->f4C = (s16)v;
                w = e->fE;
                o->z = w;
                o->flags |= 1;
                o->f50 = (s16)w;
            } else if ((s = o->sub) != 0) {
                s32 v;
                v = e->f6;
                o->x = v;
                s->f14 = (s16)v;
                v = e->fA;
                o->y = v;
                o->sub->f18 = (s16)v;
                v = e->fE;
                o->z = v;
                o->sub->f1C = (s16)v;
            } else {
                o->x = e->f6;
                o->y = e->fA;
                o->z = e->fE;
            }
        }
        i = i + 1;
        off = off + 0x58;
    } while (i < 0x1e);
}
