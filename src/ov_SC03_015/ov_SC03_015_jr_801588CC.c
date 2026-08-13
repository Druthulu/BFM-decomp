#include "common.h"
#include "../shared/engine_core.h"


/* ==== Phase-26 §8b carried decl layer (jr_isolate_all.py) ===================
 * The file-scope decl environment from earlier code regions of this object —
 * file-local types, col-0 decls, DEFINE_func macro externs, and each earlier
 * definition's implied prototype (types first, then decls in original order).
 * Decls emit no code => byte-neutral. See cookbook §8c. */
DEFINE_func_801588CC()  /* dedup: shared engine-core @0x801588CC (src/shared) */


DEFINE_func_80158AB4()  /* dedup: shared engine-core @0x80158AB4 (src/shared) */

DEFINE_func_80158AE4()  /* dedup: shared engine-core @0x80158AE4 (src/shared) */



extern void func_80146CA0(void *a0);
extern s32 func_801472C8(struct S *a0);
extern void func_80147324(s32 a0);
extern void func_801474D8(s32 *a0);
extern void func_801474EC(s32 *a0);
extern void func_80154274(s32 *a0, s32 a1);
extern void func_80154A74(s32 a0, s32 a1);
extern M2C_UNK D_800D58D8;
extern s32 D_801E96D8;

void func_80158BB0(void *arg0) {
    if (D_801E96D8 == 0) {
        D_801E96D8 = 1;
    }
    func_80147324(0x456);
    func_80154274(arg0, &D_800D58D8);
    func_80154A74(arg0, 0x16);
    M2C_FIELD(arg0, s32 *, 0x234) = 0xE30000;
    M2C_FIELD(M2C_FIELD(arg0, void **, 0x20), s16 *, 0x10) = 0;
    func_801474EC(arg0);
    func_801474D8(arg0);
    func_801472C8(arg0);
    func_80146CA0(arg0);
}


DEFINE_func_80158C40()  /* dedup: shared engine-core @0x80158C40 (src/shared) */

DEFINE_func_80158CD8()  /* dedup: shared engine-core @0x80158CD8 (src/shared) */

DEFINE_func_80158D60()  /* dedup: shared engine-core @0x80158D60 (src/shared) */

DEFINE_func_80158E24()  /* dedup: shared engine-core @0x80158E24 (src/shared) */


// @class: other
// @stuck: none — MATCH (signed %11 magic + word-array %lo fold; ((void (*)(int))func_80146CA0)(param_1) reuses $a0 for the 0x198 store in its jal delay slot)

extern s32 D_801E96E4;
extern s32 D_8018D8DC[];

extern int rand(void);
extern s32 func_8013767C(s32 a0);
extern void func_80146CA0(void *a0);

void func_80158F00(int param_1) {
    int *self = (int *)param_1;
    struct Actor *act = (struct Actor *)self[0x20 / 4];
    int gate = D_801E96E4;

    act->timer = (u16)((act->timer + 0x16) & 0xfff);

    if (gate == 0) {
        s32 r = rand();
        *(s32 *)(param_1 + 0x198) = func_8013767C(D_8018D8DC[r % 0xb]);
        ((void (*)(int))func_80146CA0)(param_1);
    }
}



// @class: plumbing
// @stuck: none — MATCH (51 ins). Key: func_801594E8 takes a 2nd arg = sVar1 (the (short)func_80159464
//        return). $a1 is set by sra BEFORE the beqz and stays live into the jal, so the value is used
//        twice (branch test + arg2) — that 2nd use is what keeps the sll;sra (gcc folds sll;sra;beqz
//        -> sll;beqz otherwise). Also: branch-polarity invert (!=0 -> 594E8 fall-through, else 767C);
//        func_8013767C arg is &(*(u8 *)&D_80110C3C) (lui%hi+addiu%lo, not a literal). Ghidra missed the 2nd arg.

extern s32 D_801E96E8;
extern u8 D_80110C3C[];

extern u16 func_80148800(s32 *a0);
extern s32 func_801399F0(s32);
extern void func_80139914(s32);
extern s32 func_80159464(void);
extern void func_801594E8(s32, s32);
extern void func_80146C98(s32 *a0, s16 a1);
extern s32 func_8013767C(s32 a0);
extern void func_80146CA0(void *a0);

void func_80158FA4(s32 param_1)
{
    s32 v0;
    s16 sVar1;

    v0 = *(s32 *)(param_1 + 0x20);
    *(u16 *)(v0 + 0x12) = (*(u16 *)(v0 + 0x12) + 0x16) & 0xfff;
    if (((s32 (*)(void))func_80148800)() & 0xf0) {
        D_801E96E8 = 1;
    }
    if (func_801399F0(*(s32 *)(param_1 + 0x198)) != 0) {
        func_80139914(*(s32 *)(param_1 + 0x198));
        *(s32 *)(param_1 + 0x198) = 0;
        sVar1 = ((s32 (*)(s32))func_80159464)(param_1);
        if (sVar1 != 0) {
            func_801594E8(param_1, sVar1);
            ((void (*)(s32, s32))func_80146C98)(param_1, 0xc);
        } else {
            *(s32 *)(param_1 + 0x198) = ((s32 (*)(u8 *))func_8013767C)(&(*(u8 *)&D_80110C3C));
            ((void (*)(s32))func_80146CA0)(param_1);
        }
    }
}


DEFINE_func_80159070()  /* dedup: shared engine-core @0x80159070 (src/shared) */

DEFINE_func_80159120()  /* dedup: shared engine-core @0x80159120 (src/shared) */

DEFINE_func_801592CC()  /* dedup: shared engine-core @0x801592CC (src/shared) */


extern void func_80145BF8(void);
extern void func_80146CA0(void *a0);
extern u8 D_800AE6BD;
extern s32 D_801E96D8;
extern s32 D_801E96E0;

void func_8015934C(void *arg0) {
    void *temp_v1;

    if (D_801E96D8 == 4) {
        D_801E96D8 = 5;
    }
    if (D_801E96E0 != 0) {
        func_80145BF8();
        func_80146CA0(arg0);
        D_800AE6BD += 1;
    }
    temp_v1 = M2C_FIELD(arg0, void **, 0x20);
    M2C_FIELD(temp_v1, u16 *, 0x12) = (u16) ((M2C_FIELD(temp_v1, u16 *, 0x12) + 0x16) & 0xFFF);
}


DEFINE_func_801593E4()  /* dedup: shared engine-core @0x801593E4 (src/shared) */

DEFINE_func_80159404()  /* dedup: shared engine-core @0x80159404 (src/shared) */

DEFINE_func_80159434()  /* dedup: shared engine-core @0x80159434 (src/shared) */


extern s16 currentLocationId;
extern s32 func_80029A94(s32);

extern Entry D_8018D944[];

s32 func_80159464(void) {
    Entry *e;

    e = D_8018D944;
    while (e->id != 0) {
        if (currentLocationId == e->id) {
            return e->val;
        }
        e++;
    }
    if (func_80029A94(1) != 0) {
        goto ret0;
    }
    if (func_80029A94(0) != 0) {
        goto ret0;
    }
    return -1;
ret0:
    return 0;
}


DEFINE_func_801594E8()  /* dedup: shared engine-core @0x801594E8 (src/shared) */



DEFINE_func_80159698()  /* dedup: shared engine-core @0x80159698 (src/shared) */


DEFINE_func_801596D4()  /* dedup: shared engine-core @0x801596D4 (src/shared) */


// @class: iv-combine
// @stuck: none — MATCH (97 ins). Recipe: $s0=base=&(*(u8 *)&D_800AF630) hoisted at top; loop1 = for(p=base+0x65A8;
//   p<base+0x9DA8;p+=0xe) p[1]|=... (the +4 field-offset store folds into the reduced IV -> gcc emits the
//   -4 loop-inversion guard + reuses END for END+4). BOTHER: loop2 needs ab=&D_800AFAE8 POST-guard as a
//   shared base for A=ab+1,B=ab+0x22 -> a for-loop hoists it PRE-guard (fold or perm); the fix is a manual
//   guarded do-while `if(base+0x2A8<base+0x65A8){ ... do{}while(q<inline base+0x65AC);}` with a DISTINCT loop
//   var (q, not p) so loop1's biv-elim survives, an INLINE while-bound (frees the delay slot for the OR
//   const), and the OR const HOISTED to a var declared first so it fills the guard delay slot (a3) and A/B
//   fall into a2/a1. Barrier after the two 0x7fff stores fixes their vs the loop-guard-low ordering.


DEFINE_func_801596F0()  /* dedup: shared engine-core @0x801596F0 (src/shared) */


DEFINE_func_80159874()  /* dedup: shared engine-core @0x80159874 (src/shared) */

DEFINE_func_8015987C()  /* dedup: shared engine-core @0x8015987C (src/shared) */

DEFINE_func_801598BC()  /* dedup: shared engine-core @0x801598BC (src/shared) */

DEFINE_func_801598E0()  /* dedup: shared engine-core @0x801598E0 (src/shared) */


DEFINE_func_80159968()  /* dedup: shared engine-core @0x80159968 (src/shared) */




DEFINE_func_801599A4()  /* dedup: shared engine-core @0x801599A4 (src/shared) */


DEFINE_func_801599E0()  /* dedup: shared engine-core @0x801599E0 (src/shared) */

DEFINE_func_80159A18()  /* dedup: shared engine-core @0x80159A18 (src/shared) */


// @class: struct
// Redraft of the DECAYED backlog draft. The stored seed took `void *param_1` and then
// dereferenced it (`param_1[0xdd]`) — gcc-2.7.2 rejects that ("void value not ignored
// as it ought to be"), so the seed no longer compiles at all. Fix: retype the parameter
// as `unsigned char *`, which keeps every pointer offset byte-scaled (as void* arith did)
// while making the byte load legal.
// Structure preserved from the seed: the two return-tests are kept STRUCTURALLY
// DIFFERENT (positive `if(==) goto mask;` per branch, not `if(!=) return;`) so gcc's
// cross-jump pass cannot tail-merge them; and the outer test is inverted (`if(d != 1)`)
// so the ==4/return path is the inline fall-through and the d==1 / p[2] path becomes the
// forward beq-target block — matching the target block order.
// Typedefs are BLOCK-SCOPE so the match travels to the sibling overlays.

extern void (*D_8018DCAC[])(unsigned char *);

extern void func_80150B28(int param_1);
extern void func_80158638(unsigned char *);
extern void func_8015126C(unsigned short *);
extern void func_8014900C(int *a0);

void func_80159A20(unsigned char *param_1)
{
    typedef unsigned short u16;
    typedef unsigned int u32;
    typedef int s32;
    typedef unsigned char u8;

    ((s32 (*)(void))func_80150B28)();
    func_80158638(param_1);
    ((void (*)(u8 *))func_8015126C)(param_1);
    ((void (*)(u8 *))func_8014900C)(param_1);
    D_8018DCAC[*(u16 *)param_1 & 0x7fff](param_1);
    *(u32 *)(param_1 + 0x44) |= 0x8000000;
    switch (*(u16 *)param_1) {
    case 2:
    case 3:
    case 0xb:
    case 0xc:
        goto mask;
    default:
        return;
    case 0x19:
        if (param_1[0xdd] != 1) {
            if (param_1[0xdd] == 4) {
                goto mask;
            }
            return;
        }
        if (*(u16 *)(param_1 + 2) == 3) {
            goto mask;
        }
        return;
    }
mask:
    *(u32 *)(param_1 + 0x44) &= 0xf7ffffff;
}

DEFINE_func_80159B08()  /* dedup: shared engine-core @0x80159B08 (src/shared) */

DEFINE_func_80159B3C()  /* dedup: shared engine-core @0x80159B3C (src/shared) */


DEFINE_func_80159B70()  /* dedup: shared engine-core @0x80159B70 (src/shared) */


DEFINE_func_80159BAC()  /* dedup: shared engine-core @0x80159BAC (src/shared) */


// @class: schedule
// @stuck: none — MATCH (40 ins). Duplicate func_80154A74(arg0,K) into BOTH branch arms (not a
//         single shared-join call): forces gcc to cross-jump the jal while keeping per-arm
//         `addu $a0,$s0` setup + a `nop` join delay slot, matching the 40-ins layout. Branch
//         polarity: write `if (flag & 0x200 != 0){5,0x1C} else {4,0x11}` to get the `beqz`.

extern void func_80146DB8(s32 *a0, s32 *a1);
extern void func_80154150(s32 a0, s32 a1);
extern void func_80154A74(s32 a0, s32 a1);
extern void func_801553C0(s32 a0);
extern void func_801553A8(s32 *a0);
extern s32 func_80172590(u8 *a0);
extern void func_80146CA0(void *a0);

extern unsigned char D_8018DB6C;

void func_80159BE4(s32 arg0)
{
    int v;

    ((void (*)(int, void *))func_80146DB8)(arg0, &D_8018DB6C);
    if ((*(unsigned int *)(arg0 + 0x44) & 0x200) != 0) {
        func_80154150(arg0, 5);
        func_80154A74(arg0, 0x1C);
    } else {
        func_80154150(arg0, 4);
        func_80154A74(arg0, 0x11);
    }
    *(int *)(arg0 + 0x234) = 0;
    *(int *)(arg0 + 0x238) = 0;
    func_801553C0(arg0);
    ((void (*)(int))func_801553A8)(arg0);
    ((void (*)(int))func_80172590)(arg0);
    ((void (*)(int))func_80146CA0)(arg0);
}


