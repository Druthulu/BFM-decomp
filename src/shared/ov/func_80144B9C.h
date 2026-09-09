/* Shared -O0 body for the whale func_80144B9C (reach-134, byte-identical across all 134
 * overlays). Included by each overlay's ov_<ov>_o0b.c (compiled -O0 via the Makefile).
 * Self-contained: only common.h types + the local externs/typedefs below. */

/* ============================================================================
 * func_80144B9C  (ov_SC01_077, vram 0x80144B9C) -- 770 ins, the single biggest
 * byte-weight lever in the T7 batch.
 *
 * OUTCOME: MATCH (770 ins), banked as compiled -O0 C, whole-binary byte-gated
 * (ov_SC01_077 == d19c9580).  reach-134 (byte-identical in all 134 overlays) ->
 * ~+1.6% byte-weight when propagated x134.  The crack was the memcpy (see below).
 *
 * >>> THIS IS AN -O0 FUNCTION <<<  prologue sig 21F0A003 (frame pointer $fp),
 * every local reloaded before each use, unfilled load-delay nops.  It sits at
 * 0x80144B9C -- ABOVE the already-split -O0 cluster (0x8013B568..0x8013C98C in
 * ov_SC01_077_o0.c), so it is a SECOND -O0 region in the -O2 "after" segment.
 * The standard match_one.py compiles -O2 (only 458/770); an -O0 clone verified it
 * (.run/t7b/work/func_80144B9C/match_o0.py).  Banked via a 2nd per-file -O0 split:
 * config/splat.ov_SC01_077.yaml carves the o0b subseg + the Makefile forces
 * CC1FLAGS=-O0 on build/src/ov_SC01_077/ov_SC01_077_o0b.o (ov_SC01_077_o0.o precedent).
 *
 * -O0 IDIOMS CRACKED (cookbook-worthy):
 *  1. Far-global $s0 base (boot.c GameModeDispatch precedent): `register u8 *p =
 *     D_800AF630;` -> $s0 held across all calls; globals at p+0xA3D8/0xA3DA/0xA3DC
 *     (currentLocationId etc.) assemble via the +0x10000/-0x5Cxx split automatically.
 *  2. STRUCT-MEMBER FOLD: at -O0, `struct->field` folds to `lw off(reg)`, but
 *     `*(T*)(base+const)` AND array `b[k]` both MATERIALIZE an extra `addu`.  All
 *     bases (p10/p14/p18/p1C/hdr/ent) must be struct pointers with exact offsets.
 *     p10->f20 is a pointer-to-struct field: `p10->f20->f12` folds to `sh 0x12(reg)`.
 *  3. Chained store `a->x = a->y = a->z = SRC;` reproduces the -O0 shared-value
 *     multi-store (one load, base addresses computed left-to-right, stored C..A).
 *  4. Loop counter `for(i=0;i<8;i++)` (i++ NOT i=i+1): i++ emits the extra
 *     `addiu v1,v0,1; addu v0,v1,0; sh v0` copy the target has; i=i+1 omits it.
 *  5. Branch polarity read off the OPCODE: first if is `if (p18->f8 == 0)` (full-
 *     init in the fall-through arm) to get `bnez ...,else`, not Ghidra's `!= 0`.
 *
 * THE CRACK (the last 2 insns) -- STRUCT ASSIGN, not an explicit memcpy() call.
 * The target marshals the memcpy args through temp pseudos (src ent->$v0, dst
 * &D_80078E50->$v1, then `addu $a0,$v1 ; addu $a1,$v0`), which an explicit
 * `memcpy(&D_80078E50, ent, 0x24)` does NOT emit.  That precompute is the signature
 * of gcc's emit_block_move -> emit_library_call(memcpy): the original C was
 *     D_80078E50 = *ent;     (sizeof(ENT) == 0x24)
 * gcc-2.7.2 -O0 expands a >MOVE_RATIO-word struct copy to a memcpy library call whose
 * args go through copy_to_mode_reg (pseudos) then into $a0/$a1 = the 2 `addu` moves.
 * memcpy is named at 0x8005C324 via symbols.resident.txt (overlays only; main keeps
 * its own MEMCPY.o symbol).  Reusable -O0 idiom: struct-assign for the precompute form.
 * ============================================================================ */


/* func_80144B9C — -O0 function (prologue sig 21F0A003). Struct-base idiom: at -O0 struct member
 * access folds to lw off(reg) but raw casts / array-index materialize an extra addu, so the bases
 * are struct pointers. Far-global $s0 base p=D_800AF630 (boot.c GameModeDispatch precedent):
 * globals p+0xA3D8.. via the +0x10000/-0x5Cxx split. */

typedef struct { u8 _0[0x12]; u16 f12; } F20T;

typedef struct {                 /* D_80126B58 */
    u8   _0[6]; u16 f6;
    u8   _8[2]; u16 fA;
    u8   _C[2]; u16 fE;
    u8   _10[0x10];
    F20T *f20;                   /* 0x20 pointer field */
    u8   _24[0x29]; u8 f4D;
    u8   _4E[0x3A];
    u16  f88, f8A, f8C; u8 _8E[2]; u16 f90, f92, f94;
    u8   _96[0x1A]; s32 fB0;
    u8   _B4[0x18]; s32 fCC;
    u8   _D0[0x84];
    u16  f154, f156, f158; u8 _15A[2]; u16 f15C, f15E, f160;
    u8   _162[0x36]; s32 f198, f19C;
    u8   _1A0[0x48]; s32 f1E8;
    u8   _1EC[4]; s32 f1F0;
} P10;

typedef struct { u8 _0[0x3A]; u16 f3A; u8 _3C[2]; u16 f3E; } P14;   /* D_80078E78 */

typedef struct {                 /* D_800AE6A8 */
    u8   _0[4]; s32 f4; s32 f8; s32 fC;
    u8   _10[4]; u8 f14; u8 _15; u8 f16; u8 _17; u8 f18;
    u8   _19[3]; s32 f1C;
    u16  f20, f22, f24, f26;
} P18;

typedef struct { u8 _0[0xA0]; u8 fA0; } P1C;                        /* D_80126948 */

typedef struct {                 /* table entry (ent), D_80078E50-shaped */
    u8   _0[3]; u8 f3; u8 _4[4]; s32 f8; s32 fC;
    u16  f10, f12, f14, f16;
    void (*f18)(void); u8 _1C[4]; void (*f20)(void);
} ENT;

typedef struct {                 /* func_801457A4 buffer (hdr) */
    s16 f0, f2, f4, f6, f8, fA;
    u8  fC, fD, fE, _F;
    s16 f10, f12, f14; u8 f16, f17, f18, _19;
    s16 f1A, f1C, f1E; u8 f20, f21, f22, _23;
    u16 f24, f26; u32 f28, f2C, f30, f34;
    u16 f38, f3A, f3C, f3E;
    u8  f40[12];
    u32 f4C, f50, f54, f58, f5C, f60, f64;
    u8  _68[0x20];
    u32 f88, f8C, f90, f94, f98, f9C, fA0, fA4, fA8;
    u8  _AC[8];
    u32 fB4, fB8, fBC, fC0, fC4, fC8;
    u8  _CC[8];
    u32 fD4, fD8;
} HDR;

extern u8 D_800AF630[];
extern u8 D_80126B58[];
extern u8 D_80078E78[];
extern u8 D_800AE6A8[];
extern u8 D_80126948[];
extern ENT D_80078E50;
extern u8 D_8010F5C8[];
extern u8 D_80126DB0[];
extern u8 D_801151F0[];
extern s32 D_8011DB14;
extern s32 D_8011DB1C;
extern s32 D_80128150;
extern s16 D_80126DB6;
extern s32 D_800A5E88, D_800A5E8C, D_800A5E90;
extern u8  D_800A5E94, D_800A5E95, D_800A5E96;
extern s32 D_800A5E98, D_800A5E9C, D_800A5EA0;
extern u8  D_800A5EA4, D_800A5EA5, D_800A5EA6;
extern s32 D_800A5EA8, D_800A5EAC, D_800A5EB0;
extern u8  D_800A5EB4, D_800A5EB5, D_800A5EB6;
extern s16 D_800B9AAC, D_800B9B00;
extern s32 D_800B9AC4, D_800B9B18, D_800B9AC8, D_800B9B1C;
extern s16 D_800B9AB2, D_800B9B06, D_800B9AB6, D_800B9B0A;
extern u8  D_800B9ABC, D_800B9ABD, D_800B9ABE, D_800B9B10, D_800B9B11, D_800B9B12;
extern u8  D_800B9ABF, D_800B9AC0, D_800B9AC1, D_800B9B13, D_800B9B14, D_800B9B15;
extern s32 D_80126728, D_8011DB08, D_80126AEC;
extern s32 D_801274C8, D_801274CC, D_801274D0, D_801274D4, D_801270B8, D_80127520;
extern s32 D_801151D8, D_8011DB28, D_801151D4;

extern void *func_801457A4(s32 a0);
extern void func_80019018(void);
extern void func_80018E78(void);
extern void func_8002AB64(void);
extern void func_80015978(void *a0, void *a1);
extern void func_8012A1BC(void);
extern void func_8002850C(s32 a0, s32 a1, s32 a2);
extern void func_80028620(s32 a0, void *a1);
extern void func_80129398(void);
extern void func_8012944C(void);
extern void func_801336E8(s32 a0, s32 a1, s32 a2);
extern void func_8013B83C(s32 a0, s32 a1, s32 a2);
extern void func_8013B568(s32 a0);
extern void func_800D02C0(s32 a0);
extern void func_80011E84(s32 a0);
extern void func_8013D3D4(s32 a0, s32 a1);
extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8005C324(void *a0, ENT *a1, s32 a2);
extern s32 func_800CF854(void);
extern void func_8001C14C(void);
extern void func_8012A110(void);

void func_80144B9C(void) {
    P10 *p10 = (P10 *)D_80126B58;
    P14 *p14 = (P14 *)D_80078E78;
    register u8 *p = D_800AF630;
    P18 *p18 = (P18 *)D_800AE6A8;
    P1C *p1C = (P1C *)D_80126948;
    HDR *hdr;
    ENT *ent;
    s32 tbl;
    s16 i;
    void (*calltmp)(void);
    s32 flag;

    func_80019018();
    func_80018E78();
    if (p18->f8 == 0) {
        hdr = (HDR *)func_801457A4(*(s16 *)(p + 0xA3D8));
        p18->f16 = 0;
        flag = 1;
        D_8011DB14 = p14->f3A;
        D_8011DB1C = p14->f3E;
        D_80128150 = 100;
        func_8002AB64();
    } else {
        hdr = (HDR *)func_801457A4(*(s16 *)(p + 0xA3D8));
        flag = 0;
    }
    p18->f1C = hdr->fC8;
    tbl = hdr->fC8;
    if (p18->f16 == 0xFF) {
        ent = &D_80078E50;
    } else {
        ent = (ENT *)*(s32 *)(p18->f16 * 4 + tbl);
    }
    p18->fC = ent->f8;
    p18->f14 = 0;
    p10->f4D = 0;
    if (ent->fC != (s32)D_8010F5C8) {
        p10->f198 = ent->fC;
    }
    if (*(s16 *)(p + 0xA3DA) == 0x1000 && *(s16 *)(p + 0xA3DC) == 0x1000) {
        p10->f6 = p10->f88 = p10->f90 = p18->f20;
        p10->fA = p10->f8A = p10->f92 = p18->f22;
        p10->fE = p10->f8C = p10->f94 = p18->f24;
        p10->f20->f12 = p18->f26;
        p18->f18 = 0;
    } else {
        p10->f6 = p10->f88 = p10->f90 = ent->f10;
        p10->fA = p10->f8A = p10->f92 = ent->f12;
        p10->fE = p10->f8C = p10->f94 = ent->f14;
        p10->f20->f12 = ent->f16;
    }
    p10->f154 = p10->f15C = p10->f6;
    p10->f156 = p10->f15E = p10->fA;
    p10->f158 = p10->f160 = p10->fE;
    func_80015978((void *)((s32)p10 + 4), D_80126DB0);
    D_80126DB6 = p10->f20->f12;
    if (*(s16 *)(p + 0xA3DA) == 0x1000 &&
        (*(s16 *)(p + 0xA3DC) == 0x1000 || *(s16 *)(p + 0xA3DC) == 0x2000) && flag == 0) {
        ent->f18();
        func_8012A1BC();
    } else {
        if (*(s16 *)(p + 0xA3DA) == 0x1000 && *(s16 *)(p + 0xA3DC) == 0x3000) {
            p1C->fA0 = ent->f3;
        } else {
            p1C->fA0 = 0;
        }
        ent->f18();
    }
    if (*(s16 *)(p + 0xA3D8) == 0x3069) {
        p1C->fA0 = ent->f3;
    }
    D_801151D4 = (s32)p1C;
    func_8002850C(hdr->f0, hdr->f2, hdr->f4);
    D_800A5E88 = hdr->f6;
    D_800A5E8C = hdr->f8;
    D_800A5E90 = hdr->fA;
    D_800A5E94 = hdr->fC;
    D_800A5E95 = hdr->fD;
    D_800A5E96 = hdr->fE;
    func_80028620(0, &D_800A5E88);
    D_800A5E98 = hdr->f10;
    D_800A5E9C = hdr->f12;
    D_800A5EA0 = hdr->f14;
    D_800A5EA4 = hdr->f16;
    D_800A5EA5 = hdr->f17;
    D_800A5EA6 = hdr->f18;
    func_80028620(1, &D_800A5E98);
    D_800A5EA8 = hdr->f1A;
    D_800A5EAC = hdr->f1C;
    D_800A5EB0 = hdr->f1E;
    D_800A5EB4 = hdr->f20;
    D_800A5EB5 = hdr->f21;
    D_800A5EB6 = hdr->f22;
    func_80028620(2, &D_800A5EA8);
    func_80129398();
    D_800B9AAC = hdr->f24;
    D_800B9B00 = hdr->f26;
    D_800B9AC4 = hdr->f28;
    D_800B9B18 = hdr->f2C;
    D_800B9AC8 = hdr->f30;
    D_800B9B1C = hdr->f34;
    D_800B9AB2 = hdr->f38;
    D_800B9B06 = hdr->f3A;
    D_800B9AB6 = hdr->f3C;
    D_800B9B0A = hdr->f3E;
    D_800B9ABC = hdr->f40[0];
    D_800B9ABD = hdr->f40[1];
    D_800B9ABE = hdr->f40[2];
    D_800B9B10 = hdr->f40[3];
    D_800B9B11 = hdr->f40[4];
    D_800B9B12 = hdr->f40[5];
    D_800B9ABF = hdr->f40[6];
    D_800B9AC0 = hdr->f40[7];
    D_800B9AC1 = hdr->f40[8];
    D_800B9B13 = hdr->f40[9];
    D_800B9B14 = hdr->f40[10];
    D_800B9B15 = hdr->f40[11];
    func_8012944C();
    p10->fB0 = hdr->f4C;
    p10->fCC = hdr->f50;
    p10->f1E8 = hdr->f54;
    p10->f1F0 = hdr->f58;
    D_80126728 = hdr->f5C;
    D_8011DB08 = hdr->f60;
    D_80126AEC = hdr->f64;
    p10->f19C = (s32)hdr + 0x68;
    func_801336E8(hdr->f88, hdr->f8C, hdr->f90);
    func_8013B83C(hdr->f94, hdr->f98, hdr->f9C);
    func_8013B568(hdr->fA8);
    func_800D02C0(hdr->fD4);
    func_80011E84(hdr->fD8);
    for (i = 0; i < 8; i++) {
        D_801151F0[i] = *(u8 *)((s32)hdr + i + 0xAC);
    }
    D_801274C8 = hdr->fB4;
    D_801274CC = hdr->fB8;
    D_801274D0 = hdr->fBC;
    D_801274D4 = hdr->fC0;
    D_801270B8 = hdr->fC4;
    D_80127520 = hdr->fC4;
    D_801151D8 = 0;
    D_8011DB28 = 0;
    calltmp = ent->f20;
    calltmp();
    func_8013D3D4(hdr->fA0, hdr->fA4);
    func_8002D4C8(0x1E, 0);
    if (p18->f8 == 0) {
        D_80078E50 = *ent;
    }
    p18->f4 = (s32)&D_80078E50;
    p18->f8 = p18->f8 & 0x7F000000;
    if (func_800CF854() != 0) {
        func_8001C14C();
        func_8012A110();
    }
}

