#include "common.h"

/* ==== Phase-26 §8b carried decl layer (jr_isolate_all.py) ===================
 * The file-scope decl environment from earlier code regions of this object —
 * file-local types, col-0 decls, DEFINE_func macro externs, and each earlier
 * definition's implied prototype (types first, then decls in original order).
 * Decls emit no code => byte-neutral. See cookbook §8c. */
typedef struct {
    s32 word0;
    s32 word4;
} CdFileLoc;
typedef struct { u32 addr : 24; u32 len : 8; } P_TAG_800CFAD0;
typedef struct { u8 b0, b1, b2, b3; } BYTES_800CFAD0;
extern u16 D_800B99F0;
extern void (*D_800D3430[])(void);
extern void func_800CEDFC(void);
extern u16 D_800B99F6;
extern void (*D_800D3480[])(void);
extern void func_800CEE40(void);
extern s16 D_800B9A00;
extern s32 D_80127084;
extern s32 D_80114E78;
extern void func_80029344(void);
extern void func_8001B324(void);
extern void func_8002AEF8(void);
extern void func_80029254(void);
extern void func_800CFBBC(void);
extern void func_80011DCC(void);
extern void func_80010AE0(s32);
extern void func_80011C10(void);
extern void func_800CEE84(void);
extern s32 func_800D0488(s32 arg0);
extern void func_80011A3C(void);
extern void func_800CEF04(void);
extern void func_800CEF34(void);
extern void func_8001C0C8(void);
extern u8  D_800B9A12;
extern s8  D_800B9A10;
extern u8  D_800B9A17;
extern s16 D_800B9A0E;
extern void func_800CEF5C(void);
extern void func_800CEFB0(void);
extern void func_800CEFD0(void);
extern s32 D_80114E98;
extern s32 D_80114E9C;
extern void (*D_800D3488[])(void);
extern u8  D_800AF630[];
extern s32 D_800A651C[];
extern void func_8001B85C(void);
extern s32  func_8001B86C(s32);
extern void func_80011B7C(s32);
extern void func_800596F4(s32);
extern void VSync(s32);
extern s32  func_80059CF4(s32);
extern void func_8001AF34(void);
extern void func_800CF104(void);
extern void func_80128158(void);
extern void VSync(s32 arg0);
extern void func_80011B7C(s32 arg0);
extern void func_800596F4(s32 arg0);
extern s32 func_80059CF4(s32 arg0);
extern void func_800CF238(void);
extern void func_8001A9F8(s32);
extern void func_800CF370(void);
extern void func_800CF398(void);
extern void func_80015310(void);
extern void func_800CF3B8(void);
extern u8 D_800AF218;
extern s32 func_8001ABBC(s32 arg0, s32 arg1, u8 *arg2, s32 arg3, s32 arg4);
extern void func_800CF47C(void);
extern u16 D_800B99FC;
extern void (*D_800D3490[])(void);
extern void func_800CF4D4(void);
extern u8 D_800B9A11;
extern s16 D_801152BA;
extern void func_80014928(void);
extern void func_8001B384(void);
extern void func_80011CFC(void);
extern void func_80011D54(s32 arg0);
extern void func_800CF510(void);
extern u8 D_80078EC1;
extern s32 func_800D02D0(s32 arg0);
extern void func_800CF584(void);
extern u8 D_80078EC0;
extern void func_800CF5D4(void);
extern s16 currentLocationId;
extern s32 D_80114E94;
extern s32 func_800CFC5C(s32 arg0);
extern s32 func_800CFBF8(void);
extern s32 func_800CFD68(s32 arg0);
extern void func_800CF628(void);
extern void func_800191A8(void);
extern s32 func_800CFE60(void);
extern void func_800CFDA4(void);
extern void func_800CF714(void);
extern s32 func_80128218(void);
extern s32 func_800D0214(s32);
extern void func_800CF764(void);
extern s32 func_8001AF04(void);
extern void func_800CF7A4(void);
extern void func_800CF804(void);
extern void func_800CF818(void);
extern void func_800CF82C(void);
extern void func_800CF840(void);
extern u8 D_800AE6BF;
extern s32 func_800CF854(void);
extern u16 D_80126B58;
extern s32 func_800CF8B4(void);
extern s32 func_800CF864(void);
extern s32 func_800CF8CC(void);
extern s32 func_800D1714(void);
extern void func_800CFDE8(s32 arg0);
extern void func_800CF8E4(void);
extern u8 D_800AE890;
extern void *D_80072C74;
extern int CdReadRequest(void *dst, void *src, int arg2, int arg3);
extern void func_800CF94C(void);
extern s16 D_80114E74;
extern s16 D_800D3408[];
extern CdFileLoc cdFileLocTable[];
extern u16 D_800AF7B8;
extern void func_800167B8(s32 arg0);
extern void func_800CFAD0(void);
extern u16 func_800167F0(s32 arg0);
extern void func_800CF990(void);
extern s16 D_80114E70;
extern void func_800CFBCC(u16 arg0);
extern s32 func_800CFBE8(void);
extern s32 func_800CFC5C(s32);
extern s32 D_800D34AC[];
extern void func_800191D4(s32 arg0);
extern void func_800191BC(s32 arg0);
/* ==== end §8b carried decl layer ==== */


/* func_800D00E4 — BANKED (S74). SUPERSEDES the note that stood here, which read
 * "left as INCLUDE_ASM — genuine structural mismatch ... Recovering it needs the
 * external jtbl wired in, out of scope here." The body was never the problem: a plain
 * C switch DOES synthesise cc1's own table, and that is exactly right — the fix is the
 * §8a/§8f CARVE, which binds the tail range 0x450e0..0x451ac to build/src/resident/
 * resident.o(.rodata) so cc1's table lands at jtbl_80113ED8's own address. The
 * accompanying #if 0 reference copy is dropped: the live body below is the same code.
 */
void func_800D00E4(s32 arg0) {
    extern u8 D_800CA23C;
    extern u8 D_800C8448;
    extern u8 D_800CA84C;
    extern u8 D_800CA3E4;
    extern u8 D_800CA344;
    extern u8 D_800C83AC;
    extern u8 D_800C9A30;
    extern u8 D_800C9158;
    extern u8 D_800C9310;
    extern u8 D_800C83A0;
    extern u8 D_800C8058;
    extern u8 D_800CADE8;
    extern u8 D_800C8500;
    extern u8 D_800C8514;
    extern u8 D_800C9140;
    extern void func_8002F5C8(u8 *arg0);
    u8 *p;
    switch (arg0 - 1) {                                /* jtbl_80113ED8 */
    case 0:  p = &D_800CA23C; break;
    case 1:  p = &D_800C8448; break;
    case 2:  p = &D_800CA84C; break;
    case 3:  p = &D_800CA3E4; break;
    case 4:  p = &D_800CA344; break;
    case 5:  p = &D_800C83AC; break;
    case 6:  p = &D_800C9A30; break;
    case 7:  p = &D_800C9158; break;
    case 8:  p = &D_800C9310; break;
    case 9:  p = &D_800C83A0; break;
    case 10: p = &D_800C8058; break;
    case 11: p = &D_800CADE8; break;
    case 12: p = &D_800C8500; break;
    case 13: p = &D_800C8514; break;
    case 14: p = &D_800C9140; break;
    default: return;
    }
    func_8002F5C8(p);
}




s32 func_800D0214(s32 arg0) {
    extern s16 currentLocationId;
    extern s32 D_800C7C60;
    extern s32 *D_800C7C64;
    extern s32 D_800A2E20;
    extern s32 D_800D34AC[];
    extern s16 D_800D34AE[];
    extern CdFileLoc cdFileLocTable[];
    extern s32 CdReadRequest(void *, void *, s32, s32);

    s32 mask = ~0xF000;
    s32 idx = currentLocationId & mask;
    s32 raw = D_800D34AC[idx];
    s32 val = D_800D34AE[idx * 2];
    s32 *p = &D_800C7C60;
    s32 id;

    __asm__("" ::: "memory");  // !FAKE: barrier memory — NEEDED DIFFERS (P36 rung B tus10)
    D_800C7C64 = &D_800A2E20;
    *p = val;

    id = raw & 0xFFF;
    if (id >= 0 && cdFileLocTable[id].word0 != 0) {
        return CdReadRequest(&cdFileLocTable[id], arg0, 0, p);
    }
    return 1;
}


extern s32 (*D_800D375C)(s32);

void func_800D02C0(s32 arg0) {
    D_800D375C = (s32 (*)(s32))arg0;
}

/* The draft's standalone `typedef struct { s32 word0; s32 word4; } CdFileLoc;` is
 * STRIPPED in-TU (§321 / §8e splice-reconcile): resident.c already provides that
 * typedef at file scope (line ~681) and a second definition is `conflicting types
 * for CdFileLoc' + `conflicting types for cdFileLocTable'. Byte-neutral — a typedef
 * emits no code and the struct layout is identical. */
/* func_800D02D0 — a 30-slot jump-table remap of (arg0 - 1), then a CD file request.
 *
 *   addiu a0,a0,-1 ; sltiu v0,a0,0x1E ; beqz v0,.L03EC   => switch (arg0 - 1), 30 slots
 *   sll v0,a0,2 ; lw v0,jtbl_80113F14[n] ; jr v0            (slot 13 and everything
 *   each case: `j .L03F0` + `addiu a0,zero,K` in the         >= 30 land on the default)
 *   delay slot ; .L03EC: addiu a0,zero,-1                => default: n = -1;
 *
 *   .L03F0: sll a1,a0,3   => 8-byte stride. D_800D3764 and D_800D3768 are the two words
 *   of ONE 8-byte record but are reached through two independent HI16/LO16 pairs, so each
 *   is declared as its own CdFileLoc[] — that is what reproduces the relocations.
 *
 *   lw v1,D_800D3768[n] ; la v0,D_800A2E20 ; sw v0,D_800C7C64
 *   la v0,D_800C7C60 ; bltz a0,.L045C ; sw v1,0(v0)      => D_800C7C60 = D_800D3768[n].word0
 *   lw a2,D_800D3764[n] ; sw v0,0x10(sp) ; la v0,cdFileLocTable ; a0=0 ; a1=0
 *   lw a3,D_80072C78 ; sll a2,a2,3 ; jal func_8001ABBC ; addu a2,a2,v0
 *   .L045C: s0 = 1 ; .L0460: if (s0 != 0) func_8001B384(); return s0;
 *
 * `&D_800C7C60` is materialised into $v0 once and used BOTH as the store base and as the
 * 5th (stacked) argument, so it is pinned to $2; a plain `s32 *` local lets gcc
 * re-materialise the `la` at the call site.
 *
 * ============================================================================
 * WHY THE PRIOR match_one-MATCH DRAFT WAS REJECTED BY THE WHOLE-BINARY GATE.
 * Two independent defects, both C-reachable. The pack's guess ("residual is outside the
 * function — the §8e JTBL_PADS class, no C edit reaches it") was wrong on both counts.
 *
 * (1) INTEGRATION — `conflicting types for 'CdFileLoc'`. The prior draft re-declared
 *     `typedef struct { s32 word0; s32 word4; } CdFileLoc;` at file scope, but
 *     resident.c already defines that anonymous-struct typedef (~line 678). Two
 *     anonymous structs are two distinct types to gcc-2.7.2, so the duplicate is a HARD
 *     error (§321). Moving it to BLOCK scope does NOT help here (§321 dial 1 fails for
 *     this TU): the shadowed type then makes the draft's own
 *     `extern CdFileLoc cdFileLocTable[];` conflict with the file-scope decl at line 930
 *     — `conflicting types for 'cdFileLocTable'`, also fatal. The only formulation that
 *     compiles is §321 dial 2: define NO type, and lean on the TU's file-scope typedef
 *     and its file-scope `cdFileLocTable` decl (both sit above this splice point). That
 *     is also this file's house style (func_800D0214, func_800CFE60, func_800D0588):
 *     externs inside the body, `u8 *` as func_8001ABBC's 3rd parameter, struct-stride
 *     indexing rather than a hand-rolled `<< 3`.
 *     Consequence: this draft CANNOT compile standalone under match_one, which only
 *     prepends common.h. Verify it with the real TU instead:
 *       tools/recover_integration.py --draft-dir <d> --binary resident --probe-only
 *     -> `MATCH 110 ins`. (A standalone-only copy carrying the typedef is kept at
 *     scratch_func_800D02D0/standalone.c; it reports match_one MATCH, closeness 0.)
 *
 * (2) THE JUMP TABLE ITSELF WAS A DIFFERENT PERMUTATION — and match_one is blind to it.
 *     match_one/blocker_probe compare .text; a switch's table is .rodata. gcc-2.7.2
 *     emits case BODIES in SOURCE order and the table entry for case i points at case
 *     i's body, so the case VALUES and the case ORDER are two independent degrees of
 *     freedom, and .text pins only the second one. The prior draft listed cases in
 *     ascending order 0..29 with values 1,3,2,0,4,... — that reproduces the .text block
 *     order exactly (110/110 instructions) while emitting an IDENTITY table
 *     [1,2,3,...,13,default,14,...] where jtbl_80113F14 is permuted
 *     [1,8,7,9,0,10,3,2,19,22,20,6,4,default,12,...]. Byte-verified both ways by
 *     compiling each draft and mapping .rdata `.word $Lnn` back to .text label order.
 *     The fix is to recover the labels from the TABLE, not from the block order: read
 *     jtbl_80113F14[i] -> block address -> that block's delay-slot constant, which gives
 *     `case i: n = K;`, then EMIT the cases sorted by block address so the bodies keep
 *     their .text order. That is the ordering below, and it reproduces both halves.
 * ============================================================================
 */
s32 func_800D02D0(s32 arg0) {
    extern CdFileLoc cdFileLocTable[];
    extern CdFileLoc D_800D3768[];
    extern CdFileLoc D_800D3764[];
    extern s32 D_800C7C60;
    extern s32 *D_800C7C64;
    extern s32 D_80072C78;
    extern s32 D_800A2E20;
    extern s32 func_8001ABBC(s32 arg0, s32 arg1, u8 *arg2, s32 arg3, s32 arg4);
    extern void func_8001B384(void);

    register s32 *p __asm__("$2");  // !FAKE: pin $2 — NEEDED DIFFERS (P36 rung B tus10)
    s32 ret;

    arg0 = arg0 - 1;
    switch (arg0) {
    case 4: arg0 = 1; break;
    case 0: arg0 = 3; break;
    case 7: arg0 = 2; break;
    case 6: arg0 = 0; break;
    case 12: arg0 = 4; break;
    case 16: arg0 = 5; break;
    case 11: arg0 = 6; break;
    case 2: arg0 = 7; break;
    case 1: arg0 = 9; break;
    case 3: arg0 = 10; break;
    case 5: arg0 = 11; break;
    case 17: arg0 = 12; break;
    case 14: arg0 = 8; break;
    case 21: arg0 = 13; break;
    case 23: arg0 = 14; break;
    case 20: arg0 = 15; break;
    case 19: arg0 = 16; break;
    case 18: arg0 = 17; break;
    case 25: arg0 = 18; break;
    case 8: arg0 = 19; break;
    case 10: arg0 = 20; break;
    case 15: arg0 = 21; break;
    case 9: arg0 = 22; break;
    case 22: arg0 = 23; break;
    case 24: arg0 = 24; break;
    case 26: arg0 = 25; break;
    case 27: arg0 = 26; break;
    case 28: arg0 = 27; break;
    case 29: arg0 = 28; break;
    default: arg0 = -1; break;
    }

    p = &D_800A2E20;
    D_800C7C64 = p;
    p = &D_800C7C60;
    *p = D_800D3768[arg0].word0;
    if (arg0 >= 0) {
        ret = func_8001ABBC(0, 0, (u8 *)&cdFileLocTable[D_800D3764[arg0].word0], D_80072C78, (s32)p);
    } else {
        ret = 1;
    }
    if (ret != 0) {
        func_8001B384();
    }
    return ret;
}


/* draft's standalone `CdFileLoc` typedef STRIPPED in-TU (§321): resident.c already
 * provides it at file scope; a second definition is `conflicting types'. Byte-neutral. */
s32 func_800D0488(s32 arg0) {
    extern s32 D_800C7C60;
    extern s32 *D_800C7C64;
    extern s32 D_800A2E20;
    extern s32 D_800D3850[];
    extern s32 D_800D384C[];
    extern s32 D_80072C7C;
    extern CdFileLoc cdFileLocTable[];
    extern s32 func_8001ABBC(s32 arg0, s32 arg1, u8 *arg2, s32 arg3, s32 arg4);
    extern void func_8001B384(void);

    s32 val;
    s32 res;
    s32 z = 0;
    s32 n = arg0;
    s32 *p;

    switch (n) {
    case 1: n = 0; break;
    case 2: n = 1; break;
    case 3: n = 2; break;
    case 4: n = 3; break;
    case 5: n = 4; break;
    case 6: n = 5; break;
    default: n = -1; break;
    }

    val = D_800D3850[n * 2];
    __asm__("");  // !FAKE: barrier — NEEDED DIFFERS (P36 rung B tus10)
    D_800C7C64 = &D_800A2E20;
    p = &D_800C7C60;
    *p = val;

    if (n >= 0) {
        res = func_8001ABBC(z, 0, (u8 *)&cdFileLocTable[D_800D384C[n * 2]], D_80072C7C, (s32)p);
    } else {
        res = 1;
    }

    if (res != 0) {
        func_8001B384();
    }
    return res;
}


// ANALYSIS: no prior draft existed. Trace:
//   a0 = currentLocationId (s16, lh -> signed); r = func_800D05E8(a0)
//   beqz v0 -> .L800D05C4 ; (delay) a0 = 1     => fall-through is r != 0
//     r != 0:  sw zero,0x10(sp)(5th arg); a1=r; a2=0; a3=0; a0=1
//              result = func_8001ABBC(1, r, 0, 0, 0)
//     r == 0:  result = 1
//   beqz v0 -> .L800D05D8  (result==0 skips the store)
//     D_8012704C = 0
//
// Branch polarity (cookbook T4): the r!=0 arm is the FALL-THROUGH, so write
//   if (r != 0) { result = call; } else { result = 1; }
// The `a0 = 1` (func_8001ABBC's 1st arg) is hoisted into the beqz delay slot by
// gcc -- emitting it as a plain constant arg is correct.
// func_8001ABBC signature copied from the already-matched func_800CF47C / func_800CFDE8
// in resident.c: s32 func_8001ABBC(s32, s32, u8 *, s32, s32). r passed as arg1 (s32).
// currentLocationId is s16 (resident.c). func_800D05E8 result reused both as the
// `beqz` test and as arg1 -> declare it s32-returning, arg s32.
extern s16 currentLocationId;
extern s32 func_800D05E8(s32 arg0);
extern s32 func_8001ABBC(s32 arg0, s32 arg1, u8 *arg2, s32 arg3, s32 arg4);
extern s32 D_8012704C;

void func_800D0588(void) {
    s32 r = func_800D05E8(currentLocationId);
    s32 result;

    if (r != 0) {
        result = func_8001ABBC(1, r, 0, 0, 0);
    } else {
        result = 1;
    }
    if (result != 0) {
        D_8012704C = 0;
    }
}

/* func_800D05E8
 *   addiu sp,-0x18 ; sw ra,0x14 ; jal func_80029504 ; sw s0,0x10 (delay)
 *   lw v1, D_800D375C ; beqz v1 -> .L0618 ; s0 = 0 (delay)
 *   jalr v1 ; a0 = v0 (delay)  ; s0 = v0
 *   .L0618: v0 = s0 ; epilogue ; return s0
 * func_80029504() is called first; D_800D375C is an optional s32(*)(s32) hook fed
 * that result. The return value lives in callee-saved s0 (frame saves ra + s0).
 * Discriminating C shape (vs the count-16 near miss): declare `ret = 0;` BEFORE
 * `r = func_80029504();` and gate with `if (D_800D375C)` (implicit nonzero test) so
 * gcc-2.7.2 -O2 allocates `ret` to s0 and emits the s0 save/restore (matches D0CE0).
 */
extern s32 func_80029504(void);
extern s32 (*D_800D375C)(s32);

s32 func_800D05E8(s32 arg0) {
    s32 ret = 0;
    s32 r = func_80029504();
    if (D_800D375C) {
        ret = D_800D375C(r);
    }
    return ret;
}

extern void func_800D065C(void);
extern s32 D_8011529C;

void func_800D0630(void) {
    func_800D065C();
    D_8011529C = -1;
}

extern s32 D_801151F8;
extern s32 D_80126AE8;
extern s32 D_80127500;
extern s32 D_8012704C;
extern s32 D_801201F0;
extern s32 D_80127050;

void func_800D065C(void) {
    D_801151F8 = 0;
    D_80126AE8 = 0;
    D_80127500 = 0;
    D_8012704C = 0;
    D_801201F0 = 0;
    D_80127050 = 0;
}

extern s32 D_801151F8;
extern s32 D_80126AE8;
extern s32 D_80127500;
extern s32 D_8012704C;
extern s32 D_801201F0;
extern s32 D_80127050;

void func_800D0694(void) {
    D_801151F8 = 0;
    D_80126AE8 = 0;
    D_80127500 = 0;
    D_8012704C = 0;
    D_801201F0 = 0;
    D_80127050 = 0;
}

extern s32 D_801151F8;
extern s32 D_80127500;

void func_800D06CC(void) {
    D_801151F8 = 3;
    D_80127500 = 3;
}

/* func_800D06E8 -- two independent state machines driven by currentLocationId (344 ins).
 *
 * SHAPE: both currentLocationId dispatches are gcc-2.7.2 expand_case DECISION TREES
 * (switch; adjacent case values merge into range nodes, balance_case_nodes roots both
 * on [0x1077,0x1078] -> `slti 0x1079` first).  The D_80127500 dispatch is a 3-value
 * tree; the D_801151F8 dispatch has 5 consecutive cases -> `sltiu 5` + jtbl_80113FA4.
 * The s0 and D_800A2B70 arms are switches (if-chains cost ~10 ins); if/else arms (not
 * assign-then-test) keep `s1=` out of the two jal delay slots.
 *
 * §162k1 (QImode): mips.h has WORD_REGISTER_OPERATIONS + LOAD_EXTEND_OP=ZERO_EXTEND but
 * NO PROMOTE_MODE, so `u8 c` is a genuine QImode pseudo.  `c == 1` is a QImode compare ->
 * no cmpqi -> convert_to_mode(SImode) = the `andi $v1,$a0,0xFF`, and combine cannot fold
 * it into the lbu (the pseudo has a second use).  The second use must NOT re-widen:
 * `(u32)(c-3)` is SImode arithmetic (a second andi, cse-tied to the first); `(u8)(c - 3)`
 * is QImode -> expand_binop has no subqi3 -> widen_operand(no_extend=1) hands it a
 * PARADOXICAL SUBREG (optabs.c:299) = `addiu $v0,$a0,-3` on the RAW register, and
 * combine.c:9246's "A - C1 vs C2" rule drops the QI truncation before the sltiu.
 *
 * Expand-time subtarget reuse: in `s1 = (cmp) ^ 1` the XOR passes s1's pseudo down as the
 * subtarget and do_store_flag expands `r - 0x64` straight INTO it (addiu $s1 / sltiu $v0,$s1).
 * An explicit flag temp makes the subtraction and the flag share the temp's pseudo ->
 * the target's `addiu $v0,$v1,-0x64 ; sltiu $v0,$v0,0x1E ; xori $s1,$v0,1`.
 *
 * D_80078E78: this TU file-scope-defines `Struct80078E78` as {u8 pad[0x34]; s16} for
 * func_800D10EC, but AFTER this function's address slot -- so that name is neither visible
 * here nor redefinable (gcc-2.7.2 rejects even a byte-identical typedef redefinition).
 * A BLOCK-SCOPED typedef under a different tag + a block-scoped `extern` for the object is
 * only a pedwarn ("type mismatch with previous external decl") and compiles the real TU clean.
 * The local pointer `p = &D_80078E78` is what pins the address in the callee-saved $s2.
 */

extern s16 currentLocationId;
extern s32 func_80029504(void);
extern void func_8002D4C8(s32 arg0, s32 arg1);
extern s32 func_8001AAA0(s32 arg0);
extern s32 D_800A2B70;
extern s32 D_800BA0FC;
extern s32 D_8011529C;
extern s32 D_80114EA0;
extern s32 D_801151F8;
extern s32 D_801201F0;
extern s32 D_80126AE8;
extern s32 D_80127050;
extern s32 D_80127500;
extern s32 resLoad_lastId;

void func_800D06E8(void) {
    typedef struct {
        u8 pad00[0x36];
        u8 field_0x36;
        u8 field_0x37;
    } Blk80078E78;
    extern Blk80078E78 D_80078E78;
    Blk80078E78 *p = &D_80078E78;
    s32 s0;
    s32 s1;
    s32 r;
    s32 t;
    u8 c;

    switch (D_80127500) {
    case 0:
        switch (currentLocationId) {
        case 0x1010:
        case 0x1011:
        case 0x1077:
        case 0x1078:
        case 0x1094:
        case 0x1095:
            r = func_80029504();
            if ((u32)(r - 0x460) < 0x32) {
                s1 = 0;
            } else {
                t = (u32)(r - 0x64) < 0x1E;
                s1 = t ^ 1;
            }
            if (s1 == 0) {
                D_800A2B70 = 0;
            }
            c = p->field_0x37;
            s0 = 0;
            if (c == 1) {
                s0 = 1;
            } else if ((u8)(c - 3) < 2) {
                s0 = 2;
            }
            if (D_800A2B70 != 0) {
                D_80127500 += 1;
                break;
            }
            if (s1 == 0) {
                break;
            }
            if (s0 == D_8011529C) {
                break;
            }
            D_8011529C = s0;
            if (D_80127050 != 0) {
                D_80127050 = 0;
                break;
            }
            switch (s0) {
            case 1:
                func_8002D4C8(0x518, 0);
                break;
            case 2:
                func_8002D4C8(0x517, 0);
                break;
            default:
                goto sw1_end;
            }
            D_800A2B70 = s0;
            D_800BA0FC = 0;
            D_80127500 += 1;
            break;
        case 0x3014:
        case 0x301C:
            if (p->field_0x37 != D_8011529C) {
                D_8011529C = p->field_0x37;
                if (p->field_0x37 == 4) {
                    func_8002D4C8(0x683, 0);
                } else if (p->field_0x37 == 0) {
                    func_8002D4C8(0xD, 0x683);
                }
            }
            break;
        }
        break;
    case 1:
        D_800BA0FC += 1;
        if ((u32)D_800BA0FC >= 0x97) {
            switch (D_800A2B70) {
            case 1:
                func_8002D4C8(0xD, 0x518);
                break;
            case 2:
                func_8002D4C8(0xD, 0x517);
                break;
            }
            D_800A2B70 = 0;
            D_80127500 = 0;
        }
        break;
    case 2:
        D_801201F0 -= 1;
        if (D_801201F0 == 0) {
            func_8002D4C8(0xD, 0x683);
            D_80127500 = 0;
        }
        break;
    }

sw1_end:
    switch (D_801151F8) {
    case 0:
        switch (currentLocationId) {
        case 0x1010:
        case 0x1011:
        case 0x1077:
        case 0x1078:
        case 0x1094:
        case 0x1095:
            r = func_80029504();
            if ((u32)(r - 0x460) < 0x32) {
                s1 = 0x89;
            } else if ((u32)(r - 0x384) < 0x6E) {
                s1 = 0x65;
            } else if ((u32)(r - 0x64) < 0x1E) {
                s1 = 0x28;
            } else {
                s1 = 0x10;
                if (p->field_0x36 == 1) {
                    s1 = 0xF;
                }
            }
            break;
        case 0x1052:
        case 0x1053:
            s1 = 0x27;
            break;
        case 0x3014:
        case 0x301C:
        case 0x301E:
        case 0x3023:
            s1 = 0xA;
            if (p->field_0x37 == 4) {
                s1 = 0x3C;
            }
            break;
        }
        if (s1 != resLoad_lastId) {
            D_80114EA0 = s1;
            D_80126AE8 = 0x3C;
            resLoad_lastId = 0;
            D_801151F8 += 1;
            func_8002D4C8(1, 2);
        }
        break;
    case 1:
        D_80126AE8 -= 1;
        if (D_80126AE8 == 0) {
            D_801151F8 += 1;
        }
        break;
    case 2:
        switch (D_80114EA0) {
        case 0xA:
            func_8002D4C8(0x10C, 0);
            break;
        case 0xF:
            func_8001AAA0(0xF);
            break;
        case 0x10:
            func_8001AAA0(0x10);
            break;
        case 0x3C:
            func_8002D4C8(0x13B, 0);
            break;
        }
        D_801151F8 = 0;
        resLoad_lastId = D_80114EA0;
        break;
    case 3:
    case 4:
        break;
    }
}


extern s32 resLoad_lastId;
extern void func_8002D4C8(s32 arg0, s32 arg1);

void func_800D0C48(u16 arg0) {
    func_8002D4C8(1, arg0);
    resLoad_lastId = 0;
}

// func_800D0C74: mirror of the matched func_800D0C48 idiom.
//   andi a1, a0, 0xFFFF      -> caller arg0 is u16, zero-extended into a1
//   jal func_8002D4C8 (delay: addiu a0,zero,1)  -> func_8002D4C8(1, arg0)
//   jal func_8001B34C (delay: nop)              -> no args
//   return (void). The frame (sw ra) exists because of the calls.
// FIX vs prior draft: declare func_8002D4C8 as (s32,s32) and make the CALLER's
// arg0 the u16 (the andi comes from truncating arg0 at the u16 param of THIS fn),
// exactly like the already-matched func_800D0C48.
extern void func_8002D4C8(s32 arg0, s32 arg1);
extern void func_8001B34C(void);

void func_800D0C74(u16 arg0) {
    func_8002D4C8(1, arg0);
    func_8001B34C();
}

// ANALYSIS: sibling of the matched func_800D0C48 (resident.c:378). The prior draft
// FAILED because it called func_8002D4C8(1) with ONE arg, but the asm shows
//   andi a1, a0, 0xFFFF      ; a1 = (u16)arg0  -> the 2nd argument
//   jal  func_8002D4C8       ; a0 = 1 (delay slot)
// i.e. func_8002D4C8(1, arg0). func_8002D4C8 is declared as (s32,s32) in resident.c.
// Passing the u16 param produces the andi a1,a0,0xFFFF zero-extension automatically.
// Then resLoad_lastId=0; D_801151F8=3; D_80127500=3 (3 materialized once in v0).

extern void func_8002D4C8(s32 arg0, s32 arg1);
extern s32 resLoad_lastId;
extern s32 D_801151F8;
extern s32 D_80127500;

void func_800D0CA0(u16 arg0) {
    func_8002D4C8(1, arg0);
    resLoad_lastId = 0;
    D_801151F8 = 3;
    D_80127500 = 3;
}

// func_800D0CE0 — optional hook, gate, then clear a block of globals + record id.
//
// asm trace:
//   jal func_80029504 / sw s0,0x10(sp)               => r = func_80029504();
//   lw v1, D_800D375C                                => fp = D_800D375C
//   beqz v1, .L0D10 / addu s0,zero,zero (delay: s0=0)=> s0 = 0; if (fp != 0) {
//   jalr v1 / addu a0,v0,zero (delay: a0=r)          =>   s0 = (*fp)(r);
//   addu s0, v0, zero                                => }
// .L0D10:
//   jal func_8001AAA0(s0)                            => t = func_8001AAA0(s0)
//   bnez v0, .L0D28 / addiu v0,zero,1 (delay: v0=1)  => if (t != 0) goto success(v0=1)
//   j .L0D68 / addu v0,zero,zero (delay: v0=0)       => else return 0;
// .L0D28 (success, v0 preset to 1):
//   sw zero, D_8012704C                              \
//   sw zero, D_801151F8                               |
//   sw zero, D_80126AE8                               |  8 stores in this exact source
//   sw zero, D_80127500                               |  order; D_8012704C is written
//   sw zero, D_8012704C   (DUPLICATE)                 |  TWICE (a redundant store the
//   sw zero, D_801201F0                               |  2.7.2 -O2 keeps — its dead-store
//   sw zero, D_80127050                               |  elimination doesn't disambiguate
//   sw s0,   resLoad_lastId                          /   distinct global memory).
//   -> falls through, returns v0 = 1
//
// BRANCH POLARITY: success is the bnez TARGET with v0=1 in the delay slot and the
// return-0 is the fall-through (v0=0 in the j delay). That is exactly:
//     if (func_8001AAA0(s0) == 0) return 0;  <stores>  return 1;
// (success/main return written LAST so it is the fall-through into the epilogue.)
//
// D_800D375C is an s32(*)(s32) function pointer here (jalr after the lw); its arg is
// func_80029504()'s return.  All cleared globals are s32 (proven in func_800D065C).
extern s32 func_80029504(void);
extern s32 (*D_800D375C)(s32);
extern s32 func_8001AAA0(s32);
extern s32 D_8012704C;
extern s32 D_801151F8;
extern s32 D_80126AE8;
extern s32 D_80127500;
extern s32 D_801201F0;
extern s32 D_80127050;
extern s32 resLoad_lastId;

s32 func_800D0CE0(void) {
    s32 s0;
    s32 r;

    r = func_80029504();
    s0 = 0;
    if (D_800D375C != 0) {
        s0 = D_800D375C(r);
    }
    if (func_8001AAA0(s0)) {
        D_8012704C = 0;
        D_801151F8 = 0;
        D_80126AE8 = 0;
        D_80127500 = 0;
        D_8012704C = 0;
        D_801201F0 = 0;
        D_80127050 = 0;
        resLoad_lastId = s0;
        return 1;
    }
    return 0;
}








/* Packed BCD-ish clock word: low byte = minutes (mod 0x3C), high byte = hours
 * (mod 0x18), held in the two consecutive bytes D_80078EB0 / D_80078EB1.
 * Returns the signed 16-bit packed difference "now - (arg0:arg1)".
 *
 * Matching notes (residual levers, see docs/gcc-2.7.2-map/regalloc.md):
 *  - RC-12 ($0-ADD OPAQUE COPY): the target keeps the packed read live in $a3
 *    while a second, opaque copy lives in $a2 (compares read $a2, the &0xFF00
 *    terms read $a3), and likewise $t0 vs $a0 for the hour. A plain C copy is
 *    dissolved by cse/canon; `x = y + zr` with zr pinned to $0 emits the
 *    byte-identical `addu rD,rS,$zero` that neither cse nor combine can remove.
 *    This is also why `andi $v0,$a2,0xFF` survives: combine cannot see through
 *    the opaque copy to fold the low byte back to the D_80078EB0 lbu.
 *  - The 8-byte frame is a phantom: the target reserves `vars= 8` but never
 *    touches the stack. An unused 8-byte local reproduces it (get_frame_size()
 *    is set at expand and never shrinks). Its presence is load-bearing beyond
 *    the two sp insns -- it also lets dbr steal `subu $v0,$t0,$v1` into the
 *    second branch's delay slot and keeps the `sra` out of the jr slot.
 *  - Conditions are spelled `>=` (not `<`): gcc branches on the inverted
 *    compare to the else-label, which is what puts the 0x3C/0x18 arms second.
 */
s32 func_800D0D7C(s32 arg0, s32 arg1) {
    extern u8 D_80078EB0;
    extern u8 D_80078EB1;
    register s32 zr __asm__("$0");  // !FAKE: pin $0 — NEEDED DIFFERS (P36 rung B tus10)
    u32 now;
    u32 r;
    s32 h;
    u32 dead[2];

    now = D_80078EB0 | (D_80078EB1 << 8);
    r = now + zr;
    h = arg0 + zr;
    if ((r & 0xFF) >= ((u32)arg1 & 0xFF)) {
        r = ((r - arg1) & 0xFF) | (now & 0xFF00);
    } else {
        r = ((0x3C - (arg1 - r)) & 0xFF) | (now & 0xFF00);
        h = arg0 + 1;
    }

    if (((r & 0xFFFF) >> 8) >= ((u32)h & 0xFF)) {
        r = ((((r & 0xFFFF) >> 8) - h) << 8) | (r & 0xFF);
    } else {
        r = ((0x18 - (h - ((r & 0xFFFF) >> 8))) << 8) | (r & 0xFF);
    }
    return (s16)r;
}


s16 func_800D0E30(u8 *p) {
    extern u8 D_80078EB0;
    extern u8 D_80078EB1;
    u8 dummy[16];
    u32 hi;
    u32 lo;
    register u32 b __asm__("$5");  // !FAKE: pin $5 — NEEDED DIFFERS (P36 rung B tus10)
    register u32 t2 __asm__("$2");  // !FAKE: pin $2 — NEEDED DIFFERS (P36 rung B tus10)
    register u32 t3 __asm__("$3");  // !FAKE: pin $3 — NEEDED DIFFERS (P36 rung B tus10)
    u32 h;

    hi = (u8)(p[1] - D_80078EB1);
    lo = (u8)(p[0] - D_80078EB0);
    p = (u8 *)((hi << 8) | lo);

    b = (u32)p + 0;
    if ((b & 0xFF) >= 0x3C) {
        t3 = (b + 0x3C) & 0xFF;
        t2 = ((u32)p & 0xFF00) - 0x100;
        b = t2 | t3;
    }
    t2 = b & 0xFFFF;
    h = t2 >> 8;
    if (h >= 0x18) {
        t2 = (h + 0x18) << 8;
        t3 = b & 0xFF;
        b = t2 | t3;
    }
    return (s16)b;
}


// func_800D0EC4 — scan func_800291B4(i) over i in [0x2F, 0x3A]; return first i whose
//   (result & 0xFF) == 0, else 0.
//
// asm trace:
//   s0 = 0x2F                                        => i = 0x2F
// .L800D0ED4 (loop top):
//   jal func_800291B4(i)                             => r = func_800291B4(i)
//   andi v0, v0, 0xFF                                => r & 0xFF   (forced andi)
//   beqz v0, .exit / addu v0,s0,zero (delay: v0=i)   => if ((r&0xFF)==0) return i;
//   addiu s0, s0, 1                                  => i++
//   sltiu v0, s0, 0x3B                               => (u32)i < 0x3B   (unsigned, sltiu)
//   bnez v0, .L800D0ED4 / addu v0,zero,zero (v0=0)   => loop while in range; fall off -> 0
//
// CALLEE RETURN TYPE: func_800291B4 loads a byte (lbu). To force the `andi v0,0xFF`
// at THIS call site it MUST be declared returning a type wider than u8 (s32) with an
// explicit `& 0xFF`; declaring it u8 would let gcc drop the andi. (Matches the proven
// pattern: func_800291B4 reads D_800BA1B8[a0] via lbu.)
extern s32 func_800291B4();

s32 func_800D0EC4(void) {
    s32 i;

    for (i = 0x2F; (u32)i < 0x3B; i++) {
        if ((func_800291B4(i) & 0xFF) == 0) {
            return i;
        }
    }
    return 0;
}

extern s16 D_80078EAC;
extern void func_800291A0(s32, s32);
extern void func_800291C8(s32, s32);

void func_800D0F0C(s32 arg0, s32 arg1) {
    func_800291A0(arg0, arg1 & 0xFF);
    func_800291C8((arg0 << 1) - 0x4A, D_80078EAC);
}

// ANALYSIS: a0 masked to u8, passed to func_800D0F8C. Result in callee-saved s0
// (live across 2nd call). If result != 0: call func_800D0FE0(result), return result.
// Else return 0. beqz s0 with v0 preset to 0 in delay slot; nonzero path is fall-through.
extern s32 func_800D0F8C(u8 arg0);
extern void func_800D0FE0(s32 arg0);

s32 func_800D0F4C(u8 arg0) {
    s32 v0 = func_800D0F8C(arg0);
    if (v0 != 0) {
        func_800D0FE0(v0);
        return v0;
    }
    return 0;
}

/* func_800D0F8C - scan indices 0x2F..0x3A; return the first whose
 * (func_800291B4(i) & 0xFF) equals (arg0 & 0xFF); return 0 if none.
 * Loop counter is u32 so gcc emits sltiu (unsigned range test 0x3B).
 */
extern s32 func_800291B4();

s32 func_800D0F8C(u8 arg0) {
    u32 i;
    for (i = 0x2F; i < 0x3B; i++) {
        if ((func_800291B4(i) & 0xFF) == arg0) {
            return i;
        }
    }
    return 0;
}

extern void func_800291A0(s32 arg0, s32 arg1);

void func_800D0FE0(s32 arg0) {
    func_800291A0(arg0, 0);
}

extern s32 func_800291DC(s32);

s16 func_800D1000(s32 arg0) {
    return func_800291DC(arg0 * 2 - 0x4A);
}

// ANALYSIS: byte-for-byte structural twin of the ALREADY-MATCHED func_800D109C
//   (src/resident/resident.c:549). asm:
//     jal func_800291B4 (void)
//     jal func_800D1078        ; andi a0,v0,0xff in the delay slot (arg = result & 0xff)
//     sll v0,16 / sra v0,16    ; sign-extend the s16 result to s32
//   The sll/sra AFTER the call means gcc did NOT prove the value already
//   sign-extended -> the callee must be declared s32-returning here (NOT s16) so
//   the explicit (s16) cast materialises the sll/sra. If func_800D1078 were
//   declared s16-returning, gcc would prove the value extended and DROP the
//   sll/sra. Mirror func_800D109C exactly: callee s32-returning, explicit (s16)
//   cast, function returns s32. (func_800D1078 is elsewhere matched as s16(u8),
//   but at THIS call site we must locally over-declare its return width to s32 to
//   force the visible sign-extension -- same trick as the func_800D2EE8 twin.)
extern s32 func_800291B4();
extern s32 func_800D1078(u8);

s32 func_800D1028(void) {
    return (s16)func_800D1078(func_800291B4() & 0xff);
}

extern s32 D_8010EDE8[];

s32 func_800D1054(s32 arg0) {
    return D_8010EDE8[(arg0 & 0xFF) * 3];
}

// ANALYSIS: andi a0,0xff (u8 idx); index = idx*0xC; return lh at D_8010EDEC + idx*0xC.
// Array of 0xC-byte records, s16 field at offset 0.
extern s16 D_8010EDEC;

s32 func_800D1078(u8 arg0) {
    return *(s16 *)((u8 *)&D_8010EDEC + arg0 * 0xC);
}

// ANALYSIS: t = func_800291B4(); return (s16)func_800D10C8(t & 0xff);
// andi a0,v0,0xff lands in the jal delay slot (arg to func_800D10C8).
// sll/sra 16 => sign-extend the s16 return to s32.
extern s32 func_800291B4();
extern s32 func_800D10C8(s32);

s32 func_800D109C(void) {
    return (s16)func_800D10C8(func_800291B4() & 0xff);
}

// ANALYSIS: direct twin of the ALREADY-MATCHED func_800D1078 (resident.c:539):
//     extern s16 D_8010EDEC;  return *(s16*)((u8*)&D_8010EDEC + arg0*0xC);
// The only differences here:
//   (1) base is D_8010EDEE (the +2 field of the same 0xC-byte record table; D_8010EDEC
//       and D_8010EDEE are adjacent .short at the table head — verified in tail.data.s),
//   (2) the parameter is s32 (not u8): the function opens with `andi a0,a0,0xFF`, so the
//       mask is EXPLICIT in source (a u8 param would need no andi), and
//   (3) the prototype is `extern s32 func_800D10C8(s32)` (resident.c:547) -> s32 return.
//
// Index arithmetic: (arg0 & 0xFF) * 0xC -> gcc emits sll1 + addu (=*3) + sll2 (=*12).
// The load is `lh` (s16, sign-extended); with no trailing sll16/sra16 the sign-extended
// value is returned directly as s32. PRIOR DRAFT used a struct-array + s16 return; this
// uses the proven byte-pointer idiom + the declared s32 return instead.

extern s16 D_8010EDEE;

s32 func_800D10C8(s32 arg0) {
    return *(s16 *)((u8 *)&D_8010EDEE + (arg0 & 0xFF) * 0xC);
}

// func_800D10EC — loop over 0xC entries; per-entry slot test then schedule.
//   s5 = &D_80078E78 hoisted loop-invariant (LICM), read as `lh 0x34(s5)` inside.
//   s4 = 32-bit loop counter; (s16)s4 used in the body and the bottom loop test.
//
// asm trace per iteration:
//   s1 = (s16)i;  s3 = s1 + 0x2F
//   v1 = func_800291B4(s3) & 0xFF
//   if (v1 == 0) continue;
//   s2 = v1 * 0xC                                       (record stride 0xC)
//   s0 = D_8010EDF0[s2]   (lbu, record byte +0)
//   if (s0 == 0) continue;
//   j = (s16)i * 2 + 0x14
//   v0 = (s16)func_800291DC(j)                           (callee s32, re-extended (s16))
//   if (D_80078E78.field_0x34 - v0 < s0) continue;       (lh 0x34(s5); subu; slt signed)
//   func_800291A0(s3, D_8010EDF1[s2]);                   (lbu record byte +1)
//   func_800291C8(j, D_80078EAC);                        (lh s16 global)
//   loop test: (s16)i < 0xC
//
// FIX 1 (LICM hoist): prior used `*(s16*)(D_80078E78 + 0x34)` over a `u8[]`, which gcc did
// NOT hoist (re-emitted lui+lh every iteration -> 62 ins, no s5, frame 0x28). Taking the
// symbol address into a LOCAL POINTER before the loop (`S *p = &D_80078E78;` then
// `p->field_0x34`) makes gcc-2.7.2 keep &D_80078E78 in the saved reg s5 (lui+addiu in
// prologue), giving the target's 65-ins / frame-0x30 shape. (A plain typed-global field
// read `D_80078E78.field_0x34` was NOT enough — gcc still re-luied it; the explicit local
// pointer is what forces the hoist.)
//
// FIX 2 (instruction scheduling): the subtraction `field - (s16)callret` left a 2-insn swap:
// the target interleaves `sll v0,v0,16 ; lh v1,0x34(s5) ; sra v0,v0,16` (field load BETWEEN
// the sign-extension halves), mine did `lh ; sll ; sra`. Computing the sign-extended call
// result into an s32 temp FIRST (`s32 r=(s16)func_800291DC(j);`) and the field into a second
// temp (`s32 f=p->field_0x34;`) before `f - r` makes gcc emit the sext RTL before the field
// load -> the scheduler then fills with `sll;lh;sra` exactly. (Inlining either operand, or a
// `s16` temp, kept the wrong order; the s32-temp-of-(s16)-cast was the unlock.)
//
// func_800291B4 is K&R-called with an arg (asm passes s3) though resident.c:600 prototypes it
// `(void)`; func_800291DC is the proven `s32 func_800291DC(s32)`.
extern s32 func_800291B4();
extern s32 func_800291DC(s32);
extern void func_800291A0(s32, s32);
extern void func_800291C8(s32, s32);

typedef struct {
    u8 pad00[0x34];
    s16 field_0x34;    /* 0x34 */
} Struct80078E78;
extern Struct80078E78 D_80078E78;

extern u8 D_8010EDF0;
extern u8 D_8010EDF1;
extern s16 D_80078EAC;

void func_800D10EC(void) {
    s16 i;
    Struct80078E78 *p = &D_80078E78;

    for (i = 0; i < 0xC; i++) {
        s32 v1;
        s32 idx;
        s32 s0;
        s32 j;

        v1 = func_800291B4(i + 0x2F) & 0xFF;
        if (v1 == 0) {
            continue;
        }
        idx = v1 * 0xC;
        s0 = (&D_8010EDF0)[idx];
        if (s0 == 0) {
            continue;
        }
        j = i * 2 + 0x14;
        {
            s32 r = (s16)func_800291DC(j);   /* sign-extend FIRST (sll/sra scheduled early) */
            s32 f = p->field_0x34;            /* then load the field (lh between sll and sra) */
            if (f - r < s0) {
                continue;
            }
        }
        func_800291A0(i + 0x2F, (&D_8010EDF1)[idx]);
        func_800291C8(j, D_80078EAC);
    }
}


/* ANALYSIS (asm 0x9C):
 *   s1 = arg0 & 0xFF                          // andi
 *   s2 = s1 + 0x2F
 *   s0 = func_800291B4(s2) & 0xFF             // a0=s2 set before jal -> takes an arg here;
 *                                             //   andi v0,0xff -> callee return WIDER than u8 (s32)
 *   if (s0 == 0) return 0;                    // bnez s0,.work / else j ret0 (v0=0)
 *   v0 = (s16)func_800291DC(s1*2 + 0x14);     // sll16/sra16 -> s16; arg = (s1<<1)+0x14
 *   r = (s16)func_800D128C(s0, (s16)((u16)D_80078EAC - v0));
 *   if (r > 0) func_800291A0(s2, 0);          // blez r -> skip; i.e. (r > 0) does the call
 *   return r;
 *
 * D_80078EAC is loaded with `lhu` here (u16) -> declare u16 to avoid an `lh`+andi.
 * func_800291B4 takes an arg in THIS function (a0=s2 set), unlike its void use in
 * func_800D109C -- self-contained draft, so declare it with the arg locally.
 * The first call's arg (s1*2) is materialised in the bnez delay slot; the +0x14 in
 * the func_800291DC delay slot -- the single expression (s1*2 + 0x14) reproduces both.
 */

extern s32 func_800291B4();
extern s32 func_800291DC(s32 arg0);
extern s16 D_80078EAC;
extern s32 func_800D128C(s32 arg0, s32 arg1);
extern void func_800291A0(s32 arg0, s32 arg1);

s32 func_800D11F0(s32 arg0) {
    s32 s1 = arg0 & 0xFF;
    s32 s2 = s1 + 0x2F;
    s32 s0 = func_800291B4(s2) & 0xFF;
    s32 v0;
    s32 r;

    if (s0 == 0) {
        return 0;
    }

    v0 = (s16)func_800291DC(s1 * 2 + 0x14);
    r = (s16)func_800D128C(s0, (s16)((u16)D_80078EAC - v0));
    if (r > 0) {
        func_800291A0(s2, 0);
    }
    return r;
}
