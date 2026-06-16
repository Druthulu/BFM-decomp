#include "common.h"

/* func_800CEDFC:
 *   v1 = D_800B99F0 (u16, lhu)
 *   if ((u32)v1 < 0x14)  [sltiu, beqz]
 *       D_800D3430[v1]()   ; function-pointer table, sll v1,2 -> word index
 *   return (void)
 *
 * The frame (sw ra; addiu sp,-0x18) is allocated because of the indirect call.
 */
extern u16 D_800B99F0;
extern void (*D_800D3430[])(void);

void func_800CEDFC(void) {
    u16 idx = D_800B99F0;
    if (idx < 0x14) {
        D_800D3430[idx]();
    }
}

extern u16 D_800B99F6;
extern void (*D_800D3480[])(void);

void func_800CEE40(void) {
    if (D_800B99F6 < 2) {
        D_800D3480[D_800B99F6]();
    }
}

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
void func_800CEE84(void) {
    func_80029344();
    D_80127084 = 0;
    D_80114E78 = 0;
    if (D_800B9A00 != 0) {
        D_80127084 = 1;
    }
    func_8001B324();
    func_8002AEF8();
    func_80029254();
    func_800CFBBC();
    func_80011DCC();
    func_80010AE0(0x3E0);
    func_80011C10();
}

extern s32 func_800D0488(s32);
extern void func_80011A3C(void);

void func_800CEF04(void) {
    if (func_800D0488(1)) {
        func_80011A3C();
    }
}

extern void func_8001B324(void);
extern void func_80011A3C(void);

void func_800CEF34(void) {
    func_8001B324();
    func_80011A3C();
}

INCLUDE_ASM("asm/resident/nonmatchings/resident", func_800CEF5C);

extern void func_80011A3C(void);

void func_800CEFB0(void) {
    func_80011A3C();
}

INCLUDE_ASM("asm/resident/nonmatchings/resident", func_800CEFD0);

INCLUDE_ASM("asm/resident/nonmatchings/resident", func_800CF104);

INCLUDE_ASM("asm/resident/nonmatchings/resident", func_800CF238);

/* func_800CF370:
 *   jal func_8001A9F8(0)
 *   jal func_80011B7C(0xF)
 *   return (void)
 */
extern void func_8001A9F8(s32);
extern void func_80011B7C(s32);

void func_800CF370(void) {
    func_8001A9F8(0);
    func_80011B7C(0xF);
}

extern void func_80011A3C(void);

void func_800CF398(void) {
    func_80011A3C();
}

INCLUDE_ASM("asm/resident/nonmatchings/resident", func_800CF3B8);

extern s32 D_80114E78;
extern u8 D_800AF218;
extern s32 func_8001ABBC(s32 arg0, s32 arg1, u8 *arg2, s32 arg3, s32 arg4);
extern void func_80011C10(void);

void func_800CF47C(void) {
    if (D_80114E78 != 0) {
        if (func_8001ABBC(0, 0, &D_800AF218, 0, 0) == 0) {
            return;
        }
        D_80114E78 = 0;
    }
    func_80011C10();
}

extern u16 D_800B99FC;
extern void (*D_800D3490[])(void);

void func_800CF4D4(void) {
    D_800D3490[D_800B99FC]();
}

extern u8 D_800B9A11;
extern s32 D_80127084;
extern s16 D_801152BA;
extern void func_80014928(void);
extern void func_8001C0C8(void);
extern void func_80015310(void);
extern void func_8001B384(void);
extern void func_80011CFC(void);
extern void func_80011D54(s32 arg0);

void func_800CF510(void) {
    func_80014928();
    D_800B9A11 = 1;
    func_8001C0C8();
    func_80015310();
    func_8001B384();
    D_801152BA = 0;
    if (D_80127084 != 0) {
        func_80011CFC();
    } else {
        func_80011D54(3);
    }
}

INCLUDE_ASM("asm/resident/nonmatchings/resident", func_800CF584);

/* func_800CF5D4
 * BUG IN PRIOR DRAFT: func_800D0488() was called with NO argument. The asm keeps
 * the masked value (D_80078EC0 & 0x7F) in $a0 across the `beqz a0` test and the
 * `jal func_800D0488` (nop delay slot leaves a0 untouched), so it IS the argument.
 * func_800D0488 is `s32 func_800D0488(s32)` (it does `addiu a0,a0,-1` — see the
 * already-matched callers func_800CEF04 / func_800CEF34).
 *
 * asm trace:
 *   lw v0, D_80127084 ; beqz v0 -> exit            => if (D_80127084 != 0) {
 *   lbu v0, D_80078EC0 ; andi a0, v0, 0x7F
 *   beqz a0 -> .L800CF610 (the call)               =>   if (m == 0 ||
 *   jal func_800D0488 ; beqz v0 -> exit            =>       func_800D0488(m) != 0)
 *   .L800CF610: jal func_80011CFC                  =>     func_80011CFC();   }
 */
extern s32 D_80127084;
extern u8 D_80078EC0;
extern s32 func_800D0488(s32 arg0);
extern void func_80011CFC(void);

void func_800CF5D4(void) {
    s32 m;

    if (D_80127084 != 0) {
        m = D_80078EC0 & 0x7F;
        if (m == 0 || func_800D0488(m) != 0) {
            func_80011CFC();
        }
    }
}

INCLUDE_ASM("asm/resident/nonmatchings/resident", func_800CF628);

extern s32 D_80114E94;
extern s16 currentLocationId;
extern void func_800191A8(void);
extern s32 func_800CFE60(void);
extern void func_800CFDA4(void);
extern void func_80011CFC(void);

void func_800CF714(void) {
    func_800191A8();
    if (func_800CFE60() != 0) {
        func_800CFDA4();
        currentLocationId = D_80114E94;
        func_80011CFC();
    }
}

extern s32 func_80128218(void);
extern s32 func_800D0214(s32);
extern s32 D_80127084;
extern s32 D_80114E98;

void func_800CF764(void) {
    if (func_800D0214(func_80128218())) {
        D_80127084 = 0;
        D_80114E98 = 1;
    }
}

extern s32 D_80127084;
extern s32 D_80114E98;
extern void func_800191A8(void);
extern s32 func_8001AF04(void);
extern s32 func_800CFE60(void);
extern void func_800CFDA4(void);

void func_800CF7A4(void) {
    func_800191A8();
    if (func_8001AF04() == 2) {
        return;
    }
    if (func_800CFE60() == 0) {
        return;
    }
    func_800CFDA4();
    D_80127084 = 0;
    D_80114E98 = 1;
}

void func_800CF804(void) {
    D_80127084 = 1;
}

void func_800CF818(void) {
    D_80114E78 = 1;
}

extern s16 D_800B9A0E;
void func_800CF82C(void) {
    D_800B9A0E = 1;
}

void func_800CF840(void) {
    D_800B9A0E = 2;
}

extern u8 D_800AE6BF;
s32 func_800CF854(void) {
    return D_800AE6BF != 0;
}

extern s16 currentLocationId;
extern u16 D_80126B58;
extern s32 func_800CF8B4(void);

s32 func_800CF864(void) {
    if (currentLocationId == 0x3069) {
        return 1;
    }
    if (D_80126B58 == 0x1A) {
        return 1;
    }
    return func_800CF8B4();
}

extern u16 D_800B99F0;

s32 func_800CF8B4(void) {
    return D_800B99F0 == 9;
}

extern u16 D_800B99F0;

s32 func_800CF8CC(void) {
    return D_800B99F0 == 0xA;
}

INCLUDE_ASM("asm/resident/nonmatchings/resident", func_800CF8E4);

extern u8 D_800AE890;
extern void *D_80072C74;
extern int CdReadRequest(void *dst, void *src, int arg2, int arg3);
extern void func_80011A3C(void);

void func_800CF94C(void) {
    if (CdReadRequest(&D_800AE890, D_80072C74, 0, 0) != 0) {
        func_80011A3C();
    }
}

INCLUDE_ASM("asm/resident/nonmatchings/resident", func_800CF990);

INCLUDE_ASM("asm/resident/nonmatchings/resident", func_800CFAD0);

extern u16 D_80114E70;

void func_800CFBBC(void) {
    D_80114E70 = 0;
}

/* func_800CFBCC — trivial two-halfword setter.
 *   addiu v0,zero,0x1 ; sh v0,D_80114E70 ; sh a0,D_80114E74 ; jr ra
 *
 * D_80114E70 is the SAME global already matched as `u16` in src/resident/resident.c
 * (func_800CFBBC sets D_80114E70 = 0). Both stores are `sh` (halfword) so the global /
 * arg signedness does NOT change the emitted store — width is fixed at 16. Kept u16 to
 * mirror the proven type. Stores are in source order (E70 first, E74 second), with the
 * `1` materialised once into v0.
 *
 * Self-contained per drafts3 rules: NO #include; typedef inlined.
 */
extern u16 D_80114E70;
extern u16 D_80114E74;

void func_800CFBCC(u16 arg0) {
    D_80114E70 = 1;
    D_80114E74 = arg0;
}

INCLUDE_ASM("asm/resident/nonmatchings/resident", func_800CFBE8);

/* func_800CFBF8 — dispatch on func_800CFC5C(currentLocationId).
 *
 * The asm is a LINEAR compare chain (beq 1; bne 2; bne 3; beq 4), NOT a jr
 * through a jump table — so this is an if/else-if chain, not a `switch`
 * (a `switch` over the dense set {1,2,3,4} makes gcc-2.7.2 emit a jtbl;
 * the prior `switch` draft failed for exactly this reason).
 *
 * result==1 -> 0x1010   (asm: beq a0,1 -> the shared 0x1010 block)
 * result==2 -> 0x1052
 * result==3 -> 0x1077
 * result==4 -> 0x1094
 * default   -> 0x1010   (gcc cross-jumps this into the case-1 block: both reach
 *                        L800CFC48 / v0=0x1010, one by branch, one by fall-through)
 *
 * currentLocationId is s16 (matched in resident.c); the `lh` sign-extends it
 * into the s32 argument.  func_800CFC5C returns s32 (compared against 1..4).
 * All returns are plain positive constants -> s32 return type.
 */
extern s16 currentLocationId;
extern s32 func_800CFC5C(s32);

s32 func_800CFBF8(void) {
    s32 r = func_800CFC5C(currentLocationId);

    if (r == 1) {
        return 0x1010;
    }
    if (r == 2) {
        return 0x1052;
    }
    if (r == 3) {
        return 0x1077;
    }
    if (r == 4) {
        return 0x1094;
    }
    return 0x1010;
}

INCLUDE_ASM("asm/resident/nonmatchings/resident", func_800CFC5C);

extern s32 D_800D34AC[];
extern void func_800191D4(s32 arg0);

void func_800CFD68(s32 arg0) {
    func_800191D4(D_800D34AC[arg0 & 0xFFFF0FFF] & 0xFFF);
}

extern s16 currentLocationId;
extern s32 D_800D34AC[];
extern void func_800191BC(s32 arg0);

void func_800CFDA4(void) {
    func_800191BC(D_800D34AC[currentLocationId & 0xFFFF0FFF] & 0xFFF);
}

/* func_800CFDE8
 * The index expression `D_800D34AC[arg0 & 0xFFFF0FFF] & 0xFFF` is the proven idiom
 * already byte-matched in func_800CFD68 / func_800CFDA4 (D_800D34AC is `s32[]`).
 * The `& 0xFFF` result is compared `>= 0` (asm keeps a redundant `bltz` — gcc-2.7.2
 * -O2 does not prove the masked value non-negative), then an 8-byte record of
 * cdFileLocTable is checked and its address passed.
 *
 * BUG IN PRIOR DRAFT: func_8001ABBC's 3rd parameter was typed `CdFileLoc *`; the
 * proven convention (func_800CF47C, func_800CF3B8) declares it `u8 *`. Match that and
 * pass the record address as a u8*. Everything else (struct stride 8 -> sll 3, word0
 * != 0 check, arg vector 2,0,&rec,0,0 with the 5th on the stack) was already correct.
 *
 * asm trace:
 *   and a0, a0, 0xFFFF0FFF ; sll a0,2 ; lw v0, D_800D34AC[a0]
 *   andi v0, 0xFFF ; bltz v0 -> exit                 => if (idx >= 0 &&
 *   sll v1, v0, 3 ; lw v0, cdFileLocTable[idx].word0
 *   beqz v0 -> exit                                  =>     rec->word0 != 0) {
 *   a0=2 ; sw zero,0x10(sp) ; a1=0 ; a2=&rec ; a3=0
 *   jal func_8001ABBC                                =>   func_8001ABBC(2,0,&rec,0,0); }
 */
typedef struct {
    s32 word0;
    s32 word4;
} CdFileLoc;

extern s32 D_800D34AC[];
extern CdFileLoc cdFileLocTable[];
extern s32 func_8001ABBC(s32 arg0, s32 arg1, u8 *arg2, s32 arg3, s32 arg4);

void func_800CFDE8(s32 arg0) {
    s32 idx = D_800D34AC[arg0 & 0xFFFF0FFF] & 0xFFF;
    if (idx >= 0 && cdFileLocTable[idx].word0 != 0) {
        func_8001ABBC(2, 0, (u8 *)&cdFileLocTable[idx], 0, 0);
    }
}

INCLUDE_ASM("asm/resident/nonmatchings/resident", func_800CFE60);

INCLUDE_ASM("asm/resident/nonmatchings/resident", func_800D00E4);

INCLUDE_ASM("asm/resident/nonmatchings/resident", func_800D0214);

extern s32 D_800D375C;

void func_800D02C0(s32 arg0) {
    D_800D375C = arg0;
}

INCLUDE_ASM("asm/resident/nonmatchings/resident", func_800D02D0);

INCLUDE_ASM("asm/resident/nonmatchings/resident", func_800D0488);

INCLUDE_ASM("asm/resident/nonmatchings/resident", func_800D0588);

INCLUDE_ASM("asm/resident/nonmatchings/resident", func_800D05E8);

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

INCLUDE_ASM("asm/resident/nonmatchings/resident", func_800D06E8);

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

INCLUDE_ASM("asm/resident/nonmatchings/resident", func_800D0CE0);

INCLUDE_ASM("asm/resident/nonmatchings/resident", func_800D0D7C);

INCLUDE_ASM("asm/resident/nonmatchings/resident", func_800D0E30);

INCLUDE_ASM("asm/resident/nonmatchings/resident", func_800D0EC4);

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

INCLUDE_ASM("asm/resident/nonmatchings/resident", func_800D0F8C);

extern void func_800291A0(s32 arg0, s32 arg1);

void func_800D0FE0(s32 arg0) {
    func_800291A0(arg0, 0);
}

extern s32 func_800291DC(s32);

s16 func_800D1000(s32 arg0) {
    return func_800291DC(arg0 * 2 - 0x4A);
}

INCLUDE_ASM("asm/resident/nonmatchings/resident", func_800D1028);

extern s32 D_8010EDE8[];

s32 func_800D1054(s32 arg0) {
    return D_8010EDE8[(arg0 & 0xFF) * 3];
}

// ANALYSIS: andi a0,0xff (u8 idx); index = idx*0xC; return lh at D_8010EDEC + idx*0xC.
// Array of 0xC-byte records, s16 field at offset 0.
extern s16 D_8010EDEC;

s16 func_800D1078(u8 arg0) {
    return *(s16 *)((u8 *)&D_8010EDEC + arg0 * 0xC);
}

// ANALYSIS: t = func_800291B4(); return (s16)func_800D10C8(t & 0xff);
// andi a0,v0,0xff lands in the jal delay slot (arg to func_800D10C8).
// sll/sra 16 => sign-extend the s16 return to s32.
extern s32 func_800291B4(void);
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

INCLUDE_ASM("asm/resident/nonmatchings/resident", func_800D10EC);

INCLUDE_ASM("asm/resident/nonmatchings/resident", func_800D11F0);

INCLUDE_ASM("asm/resident/nonmatchings/resident", func_800D128C);

INCLUDE_ASM("asm/resident/nonmatchings/resident", func_800D1658);

extern u16 D_80078E50;
u16 func_800D1714(void) {
    return D_80078E50;
}

extern s32 D_800AE6B0;
void func_800D1724(s32 arg0) {
    D_800AE6B0 = arg0;
}

extern s32 D_800AE6A8;

void func_800D1734(s32 arg0) {
    D_800AE6A8 = arg0;
}

extern s32 D_800AE6AC;

void func_800D1744(s32 arg0) {
    D_800AE6AC = arg0;
}

INCLUDE_ASM("asm/resident/nonmatchings/resident", func_800D1754);

INCLUDE_ASM("asm/resident/nonmatchings/resident", func_800D17B8);

INCLUDE_ASM("asm/resident/nonmatchings/resident", func_800D185C);

// ANALYSIS: idx = D_800AE6BC (u8, lbu — hoisted to the very top, before the frame).
// Copy the 3-word function-pointer array D_801141BC into a LOCAL stack array (sp+0x10),
// fully unrolled (lw v1/a0/a1 from 0/4/8, sw to 0x10/0x14/0x18 — a 12-byte struct copy),
// then call local[idx](&D_800AE6A8):  sll idx,2; addu sp,idx; lw 0x10(...); jalr.
// Frame -0x28 (ra@0x20, the 0xC-byte local array @0x10).
//
// PRIOR DRAFT was structurally close (same idea). Refinements for the byte form:
//  - The runtime index idx forces gcc to materialise the WHOLE table on the stack and
//    index the LOCAL (it can't prove idx), giving the copy+index seen in the asm. Modeling
//    D_801141BC as a 3-element fn-ptr array and copying it into an identical local array,
//    then indexing the local, is the faithful source.
//  - idx is read FIRST (the lbu floats to the top with no deps).
//  - The call passes &D_800AE6A8 (lui/addiu of the symbol address) as the single arg.
//
// The fn pointers take one pointer arg (the call site passes &D_800AE6A8). Use a struct
// wrapper so the whole-array assignment `local = D_801141BC` is a clean aggregate copy
// (3 words) and `local.fn[idx](...)` is the indexed call.

typedef struct {
    void (*fn[3])(void *);
} FnTbl3;

extern u8 D_800AE6BC;
extern FnTbl3 D_801141BC;
extern s32 D_800AE6A8;

void func_800D18DC(void) {
    u8 idx = D_800AE6BC;
    FnTbl3 local = D_801141BC;
    local.fn[idx](&D_800AE6A8);
}

/* ANALYSIS (asm 0x4C):
 *   s0 = arg0 (saved in func_800D1F58's delay slot)
 *   func_800D1F58();                    // void, no args set -> a0 still holds arg0 (incidental)
 *   func_801285D4();                    // void, nop in delay slot
 *   v0 = (u8)field 0x14  (lbu)
 *   a0 = arg0
 *   field 0x15 = 0       (sb)
 *   v0 = v0 + 1
 *   field 0x14 = (u8)v0  (sb, in jal delay slot)
 *   func_800D1984(arg0);
 *   return 0;            // addu v0,zero,zero -> plain s32 0
 *
 * field0x14 read with lbu (u8), the +1 result stored back with sb (so the store
 * truncates to 8 bits naturally). field0x15 is a u8 store of 0. The store order
 * in asm is: sb 0x15 (=0), then sb 0x14 (=field+1) -- but the 0x14 store sits in
 * the func_800D1984 delay slot. Writing field0x15=0 first then field0x14++ keeps
 * gcc's natural schedule (the 0x14 store hoists into the call delay slot).
 */

typedef struct {
    u8 pad[0x14];
    u8 f14;   /* 0x14 */
    u8 f15;   /* 0x15 */
} S800D1938;

extern void func_800D1F58(void);
extern void func_801285D4(void);
extern void func_800D1984(S800D1938 *arg0);

s32 func_800D1938(S800D1938 *arg0) {
    func_800D1F58();
    func_801285D4();
    arg0->f15 = 0;
    arg0->f14 = arg0->f14 + 1;
    func_800D1984(arg0);
    return 0;
}

INCLUDE_ASM("asm/resident/nonmatchings/resident", func_800D1984);

extern s8 D_800B9A10;

s32 func_800D19DC(void) {
    D_800B9A10 = 1;
    return 1;
}

INCLUDE_ASM("asm/resident/nonmatchings/resident", func_800D19F0);

// ANALYSIS (re-derived):
//   s0 = arg0 (struct ptr, callee-saved: live across 4 calls)
//   func_80029124(0x119, 0)
//   func_8002D4C8(4, 0x448)
//   func_8002D4C8(4, 0x449)
//   func_8002D4C8(4, 0x8ED)
//   D_800B9A10 = 0                    sb  (u8)  -- STORE 1
//   v0 = arg0->[0x14]                 lbu (u8)  -- LOAD (hoisted between store 1 & 2)
//   arg0->[0x15] = 0                  sb  (u8)  -- STORE 2
//   arg0->[0x14] = v0 + 1             sb  (u8)  -- STORE 3
//   return 0
//
// STORE ORDER (cookbook T2): the asm keeps stores in source order
//   D_800B9A10(0x14? no -> global), [0x15], [0x14].  The lbu of [0x14] is HOISTED early
//   (gcc loads the increment input ahead of the [0x15] store) but the THREE stores stay
//   in source order: global, +0x15, +0x14.  So write them in that exact order.
//
// Widths: D_800B9A10 sb => declared `s8` in resident.c (func_800D1BAC) -> COPY it ;
//   fields +0x14/+0x15 sb/lbu => u8.
// Return type s32 (plain addu v0,zero,zero).
extern void func_80029124(s32 arg0, s32 arg1);
extern void func_8002D4C8(s32 arg0, s32 arg1);
extern s8 D_800B9A10;

s32 func_800D1B10(u8 *arg0) {
    func_80029124(0x119, 0);
    func_8002D4C8(4, 0x448);
    func_8002D4C8(4, 0x449);
    func_8002D4C8(4, 0x8ED);
    D_800B9A10 = 0;
    arg0[0x15] = 0;
    arg0[0x14] = arg0[0x14] + 1;
    return 0;
}

INCLUDE_ASM("asm/resident/nonmatchings/resident", func_800D1B80);

extern void func_800D1BF8(void);

s32 DsMix(void) {
    func_800D1BF8();
    return 1;
}

INCLUDE_ASM("asm/resident/nonmatchings/resident", func_800D1BF8);

/* func_800D1D24:
 *   v0 = D_80078E50 (u16)
 *   a0 = D_800B9A0A (u16, old value)
 *   D_800B9A11 = 1
 *   currentLocationId = v0
 *   D_800B9A0C = a0          (old D_800B9A0A)
 *   D_800B9A0A = v0 & 0xF000
 *   func_8001C0C8(); func_80015310(); func_80129258(); func_801378F0();
 */
extern u16 D_80078E50;
extern u16 D_800B9A0A;
extern u8  D_800B9A11;
extern s16 currentLocationId;
extern s16 D_800B9A0C;
extern void func_8001C0C8(void);
extern void func_80015310(void);
extern void func_80129258(void);
extern void func_801378F0(void);

void func_800D1D24(void) {
    u16 v0 = D_80078E50;
    u16 old = D_800B9A0A;
    D_800B9A11 = 1;
    currentLocationId = v0;
    D_800B9A0C = old;
    D_800B9A0A = v0 & 0xF000;
    func_8001C0C8();
    func_80015310();
    func_80129258();
    func_801378F0();
}

extern u16 D_80078E50;

s32 func_800D1D94(void) {
    return (s32)((D_80078E50 & 0xF000) << 16) >> 16;
}

INCLUDE_ASM("asm/resident/nonmatchings/resident", func_800D1DB0);

void func_800D1E20(void) {
}

INCLUDE_ASM("asm/resident/nonmatchings/resident", func_800D1E28);

INCLUDE_ASM("asm/resident/nonmatchings/resident", func_800D1EBC);

extern u16 D_80078EB4;
extern u16 D_80078EB8;
extern s32 D_80078E8C;
extern s32 D_8011DB14;
extern s32 D_8011DB1C;
extern s32 D_80128150;

void func_800D1F58(void) {
    D_8011DB14 = D_80078EB4;
    D_8011DB1C = D_80078EB8;
    D_80128150 = D_80078E8C;
}

/* func_800D1F90 — the inverse of the matched func_800D1F58 (resident.c:673).
 *
 *   D_80078EB4 (u16) = (u16)D_8011DB14 (s32)   -> lw v0; sh v0
 *   D_80078EB8 (u16) = (u16)D_8011DB1C (s32)   -> lw v1; sh v1
 *   D_80078E8C (s32) =       D_80128150 (s32)  -> lw a0; sw a0
 *
 * The three source loads are independent, so gcc's r3000 scheduler hoists all
 * three lw's ahead of the three stores (matches the asm: lw,lw,lw,sh,sh,sw).
 * Types COPIED verbatim from the matched func_800D1F58 so the load widths agree:
 * D_80078EB4/B8 are u16, the rest s32.  sh truncates the s32 source naturally.
 */
extern u16 D_80078EB4;
extern u16 D_80078EB8;
extern s32 D_80078E8C;
extern s32 D_8011DB14;
extern s32 D_8011DB1C;
extern s32 D_80128150;

void func_800D1F90(void) {
    D_80078EB4 = D_8011DB14;
    D_80078EB8 = D_8011DB1C;
    D_80078E8C = D_80128150;
}

INCLUDE_ASM("asm/resident/nonmatchings/resident", func_800D1FC8);

INCLUDE_ASM("asm/resident/nonmatchings/resident", func_800D20C0);

INCLUDE_ASM("asm/resident/nonmatchings/resident", func_800D21C4);

// func_800D222C — allocate via func_801465C0(arg0); on success initialise via
// func_8001CB6C(p, arg1, 0, 0), store arg2 byte at p[0x27], return p; on NULL return 0.
//
// FIX vs prior draft: BRANCH POLARITY (cookbook §2 T4). The asm is
//     bnez s0,.L800D2260   ; branch TO the call/init path
//     j .L800D2278 ; addu v0,zero,zero   ; the FALL-THROUGH is `return 0`
// so the success path is the branched-to block and `return 0` falls through. The
// matching source therefore writes `if (p != 0) { ...; return p; } return 0;`
// (the prior `if (p == 0) return 0;` produced the inverse beqz).
//
// Arg note: a0 for func_8001CB6C is the alloc result (asm `addu a0,s0,zero` in the
// bnez delay slot) — i.e. p is its first argument.

extern u8 *func_801465C0(s32);
extern void func_8001CB6C(u8 *, s32, s32, s32);

u8 *func_800D222C(s32 arg0, s32 arg1, s32 arg2) {
    u8 *p = func_801465C0(arg0);
    if (p != 0) {
        func_8001CB6C(p, arg1, 0, 0);
        p[0x27] = arg2;
        return p;
    }
    return 0;
}

INCLUDE_ASM("asm/resident/nonmatchings/resident", func_800D2294);

typedef struct {
    /* 0x00 */ s32 f0;
    /* 0x04 */ s32 f4;
    /* 0x08 */ s32 f8;
    /* 0x0C */ s32 fC;
    /* 0x10 */ s32 f10;
    /* 0x14 */ s32 f14;
    /* 0x18 */ s32 f18;
} S800D22E4;

void func_800D22E4(S800D22E4 *p) {
    p->f4 += p->f10;
    p->f8 += p->f14;
    p->fC += p->f18;
}

// ANALYSIS: leaf-ish fn taking a struct* (a0=s3). Loads s32 at +0x2C, masks
// with 0x3FFFFFFF, extracts three signed bitfields via <<16>>19 / <<22>>19
// (signed /8-style scaled extracts), squares two of them, calls
// func_80047D3C(s1f^2 + s2f^2) -> r1, then ratan2(s0f,(s16)r1) -> r2 (stored
// negated at +0x12), then ratan2(s1f,s2f) -> r3 stored at +0x16, +0x1A=0.
// Risk: exact shift/extract idiom + mult/mflo ordering + the negate-in-delay-slot.

extern s32 func_80047D3C(s32 arg0);
extern s32 ratan2(s32 y, s32 x);

void func_800D2318(s32 *p) {
    s32 raw = p[0xB];                 /* *(s32*)((u8*)p + 0x2C) */
    u32 masked = (u32)raw & 0x3FFFFFFF;   /* u32 -> srl on the >> below (matches asm) */
    s32 s1f = (s32)(((masked >> 14) & 0xFFC0) << 16) >> 19;
    s32 s2f = (s32)(raw << 22) >> 19;
    s32 s0f = (s32)(((masked >> 4) & 0xFFC0) << 16) >> 19;
    s32 r1 = func_80047D3C(s1f * s1f + s2f * s2f);

    *(s16 *)((u8 *)p + 0x12) = -ratan2(s0f, (s16)r1);
    *(s16 *)((u8 *)p + 0x16) = ratan2(s1f, s2f);
    *(s16 *)((u8 *)p + 0x1A) = 0;
}

INCLUDE_ASM("asm/resident/nonmatchings/resident", func_800D23D0);

void func_800D2460(void) {
}

extern void func_80016714(void *, s32);
extern u8 D_80115110[];
extern s32 D_8012751C;
extern s32 D_8011DB20;

void func_800D2468(void) {
    func_80016714(D_80115110, 0xC4);
    D_8012751C = 0;
    D_8011DB20 = 0;
}

INCLUDE_ASM("asm/resident/nonmatchings/resident", func_800D24A0);

extern void (*D_8011DB24)(void);

void func_800D25FC(void) {
    D_8011DB24();
}

extern u8 D_800B9A13;
extern void func_8002D4C8(s32 arg0, s32 arg1);

void func_800D2624(void) {
    D_800B9A13 = 0;
    func_8002D4C8(0x15, 0);
}

INCLUDE_ASM("asm/resident/nonmatchings/resident", func_800D2650);

INCLUDE_ASM("asm/resident/nonmatchings/resident", func_800D27DC);

INCLUDE_ASM("asm/resident/nonmatchings/resident", func_800D29F8);

INCLUDE_ASM("asm/resident/nonmatchings/resident", func_800D2CA8);

INCLUDE_ASM("asm/resident/nonmatchings/resident", func_800D2D10);

/* func_800D2DAC(arg0):
 *   func_8016EDEC(func_800D3238, 0x1000000);   ; a0=&func_800D3238, a1=0x1000000
 *   func_800167B8(0);                          ; a0=0 (delay slot)
 *   arg0[0x15]++;                              ; lbu/addiu/sb at +0x15 (u8)
 *   return 0;                                  ; addu v0,zero,zero
 *
 * Mirrors the already-matched func_800D2F48 (call; func_800167B8(0); arg0[0x15]++;
 * return 0). The first arg to func_8016EDEC is a FUNCTION ADDRESS (func_800D3238),
 * so it materialises as lui/addiu %hi/%lo — declare the param as a generic pointer
 * so passing the function name decays to &func_800D3238 with no cast.
 */
extern void func_800D3238(void *arg0);
extern void func_8016EDEC(void *arg0, s32 arg1);
extern void func_800167B8(s32 arg0);

s32 func_800D2DAC(u8 *arg0) {
    func_8016EDEC(func_800D3238, 0x1000000);
    func_800167B8(0);
    arg0[0x15]++;
    return 0;
}

// func_800D2DFC: byte-identical twin of the ALREADY-MATCHED func_800D319C /
// func_800D2EE8 in src/resident/resident.c, differing ONLY in the argument
// (a0 = 0 here vs a0 = 4 there):
//     jal func_800167F0          ; delay slot: addu a0,zero,zero  -> a0 = 0
//     andi v0,v0,0xffff          ; zero-extend the u16 return
//     sltu v0,zero,v0            ; v0 = (0 < v0) = (v0 != 0)
//     return                     ; plain s32 return
//
// FIX vs BOTH prior failed drafts: they declared func_800167F0 as a WIDER type
// (s32/int) and wrote an explicit (u16) cast to "force" the andi. That is wrong
// for THIS binary — the proven matched twins (func_800D319C / func_800D2EE8) declare
// func_800167F0 returning **u16** with NO cast and `!= 0`; gcc still emits the
// andi 0xffff as the natural zero-extend of the u16 return before the sltu. Copy
// that exact form; only the arg changes from 4 to 0.
extern u16 func_800167F0(s32 arg0);

s32 func_800D2DFC(void) {
    return func_800167F0(0) != 0;
}

INCLUDE_ASM("asm/resident/nonmatchings/resident", func_800D2E20);

INCLUDE_ASM("asm/resident/nonmatchings/resident", func_800D2E6C);

// ANALYSIS: identical asm shape to the ALREADY-MATCHED func_800D319C in
// src/resident/resident.c:
//     jal func_800167F0 (a0=4); andi v0,v0,0xffff; sltu v0,zero,v0; return.
// The proven matched form declares func_800167F0 as returning u16 (so the
// andi 0xffff is the natural zero-extend of the return) and writes `!= 0`
// (sltu zero,v0 = "0 < v0" = v0 != 0). The prior draft declared it s32 and
// added an explicit (u16) cast; copy the proven u16-return form instead.
extern u16 func_800167F0(s32 arg0);

s32 func_800D2EE8(void) {
    return func_800167F0(4) != 0;
}

extern void (*D_800D39C4[])(void);

void func_800D2F0C(u8 *arg0) {
    D_800D39C4[arg0[0x15]]();
}

extern void func_800D33B8(void);
extern void func_800167B8(s32 arg0);

s32 func_800D2F48(u8 *arg0) {
    func_800D33B8();
    func_800167B8(0);
    arg0[0x15]++;
    return 0;
}

// ANALYSIS: byte-identical asm SHAPE to the ALREADY-MATCHED twins func_800D319C and
// func_800D2EE8 in src/resident/resident.c:
//     jal func_800167F0 (a0=0); andi v0,v0,0xffff; sltu v0,zero,v0; jr ra
// The ONLY difference vs the twins is a0 = 0 here (they pass 4).
//
// PRIOR-DRAFT BUG: it declared func_800167F0 as `s32` and wrote `(u16)func_800167F0(0) != 0`.
// The proven matched form declares the callee as RETURNING u16 — then the `andi v0,0xffff`
// is the NATURAL zero-extend of the u16 return value (no explicit (u16) cast), and
// `!= 0` lowers to `sltu v0,zero,v0` (0 < v0). With an s32 return + explicit cast, gcc
// schedules the andi differently / can drop it. Copy the twins verbatim.
extern u16 func_800167F0(s32 arg0);

s32 func_800D2F8C(void) {
    return func_800167F0(0) != 0;
}

extern void (*D_800D39F0[])(void);

void func_800D2FB0(u8 *arg0) {
    D_800D39F0[arg0[0x15]]();
}

// ANALYSIS: jal func_800D33E0() (void — the delay-slot `addu s0,a0,zero` SAVES the
// incoming a0 across the call, it is NOT an argument to the call; ref source declares
// func_800D33E0(void)). a0 = struct/byte-base pointer kept in s0.
// Then: read u8 field 0x15; store s32 0xA at 0x28; field_0x15 = v+1; return 0.
// Mirrors the matched func_800D3104 shape (read field, store const, write field back, ret 0),
// only differing by the leading call + a sw(0x28)=0xA instead of sb(0x19)=0xA.
//
// PRIOR-DRAFT BUG: it passed arg0 to func_800D33E0 (`func_800D33E0(arg0)`), but the asm
// shows a0 merely COPIED to the callee-saved s0 in the jal delay slot — the call takes no
// args. Declaring it (void) and keeping arg0 live in a local emits the exact `addu s0,a0,$0`.
extern void func_800D33E0(void);

typedef struct {
    u8 pad00[0x15];
    u8 field_0x15;   /* 0x15 */
    u8 pad16[0x12];
    s32 field_0x28;  /* 0x28 */
} Struct800D2FEC;

s32 func_800D2FEC(Struct800D2FEC *a0) {
    func_800D33E0();
    a0->field_0x28 = 0xA;
    a0->field_0x15 = a0->field_0x15 + 1;
    return 0;
}

INCLUDE_ASM("asm/resident/nonmatchings/resident", func_800D302C);

extern void func_800D1EBC(void);

void func_800D30A8(void) {
    func_800D1EBC();
}

extern void (*D_800D3A8C[])(void);

void func_800D30C8(void *arg0) {
    D_800D3A8C[*(u8 *)((u8 *)arg0 + 0x15)]();
}

/* func_800D3104: a0 is a struct pointer.
 *   lbu v0, 0x15(a0)        -> read u8 at +0x15
 *   addiu v1, zero, 0xA     -> 10
 *   sb v1, 0x19(a0)         -> store 10 at +0x19
 *   addiu v0, v0, 1         -> +1
 *   sb v0, 0x15(a0)         -> store back at +0x15
 *   return 0
 */
typedef struct {
    u8 pad15[0x15];
    u8 field_0x15;
    u8 pad16[0x3];
    u8 field_0x19;
} Struct800D3104;

s32 func_800D3104(Struct800D3104 *a0) {
    u8 v = a0->field_0x15;
    a0->field_0x19 = 0xA;
    a0->field_0x15 = v + 1;
    return 0;
}

// func_800D3120 (byte-identical to the also-unmatched func_800D2E6C):
// countdown trigger on a u8 field at +0x19 of arg0 (kept in s0).
//   v1 = arg0->field_0x19          ; lbu (u8)
//   v0 = v1 + 0xFF                  ; addiu v0,v1,0xFF  <-- IMMEDIATE 0x00FF, +255
//   bnez v1, .L800D3184            ; if (v1 != 0) skip the work
//     sb v0,0x19(s0)               ; (delay slot) store the wrapped value UNCONDITIONALLY
//   ; v1 == 0 -> do the work:
//     func_8002D4C8(0x1C, 0); func_8001BFD0(); func_8002D4C8(0x1D, 0);
//     func_800D0C48(1); func_800167B8(4);
//     arg0->field_0x15++           ; lbu/addiu 1/sb  (u8)
//  .L800D3184: return 0
//
// FIX vs BOTH prior drafts: they wrote `p->field_0x19-- == 0`. A u8 post-decrement
// promotes to int, so `-1` is emitted as `addiu v0,v1,0xFFFF` (immediate 0xFFFF) —
// but the asm shows `addiu v0,v1,0xFF` (immediate 0x00FF = +255). gcc renders the
// constant as a positive +0xFF, which only happens when the source ADDS 0xFF, not
// subtracts 1. So write `v + 0xFF` (the byte-wrapping decrement) explicitly and test
// the OLD value `v` for the branch. Stored via sb so the byte result == v-1 mod 256.
// func_800D0C48 is u16-arg per resident.c:440; the others match resident.c sigs.
extern void func_8002D4C8(s32 arg0, s32 arg1);
extern void func_8001BFD0(void);
extern void func_800D0C48(u16 arg0);
extern void func_800167B8(s32 arg0);

typedef struct {
    u8 pad00[0x15];    /* 0x00..0x14 */
    u8 field_0x15;     /* 0x15 */
    u8 pad16[0x3];     /* 0x16..0x18 */
    u8 field_0x19;     /* 0x19 */
} Struct800D3120;

s32 func_800D3120(Struct800D3120 *arg0) {
    u8 v = arg0->field_0x19;
    arg0->field_0x19 = v + 0xFF;
    if (v == 0) {
        func_8002D4C8(0x1C, 0);
        func_8001BFD0();
        func_8002D4C8(0x1D, 0);
        func_800D0C48(1);
        func_800167B8(4);
        arg0->field_0x15++;
    }
    return 0;
}

extern u16 func_800167F0(s32 arg0);

s32 func_800D319C(void) {
    return func_800167F0(4) != 0;
}

extern void (*D_800D3920[])(void);

void func_800D31C0(u8 *arg0) {
    D_800D3920[arg0[0x15]]();
}

extern void (*D_800D3928[])(void);

void func_800D31FC(u8 *arg0) {
    D_800D3928[arg0[0x15]]();
}

// ANALYSIS: idx = *(u8*)(arg+0x214); fp = D_800D3A98[idx]; fp(arg).
// Function-pointer table dispatch; a0 (arg) preserved into the jalr.
extern void (*D_800D3A98[])();

void func_800D3238(void *arg0) {
    D_800D3A98[*(u8 *)((u8 *)arg0 + 0x214)](arg0);
}

extern s32 func_8013767C(s32);

void func_800D3274(u8 *arg0) {
    s32 w = *(s32 *)(arg0 + 0x198);
    if (w != 0) {
        *(s32 *)(arg0 + 0x198) = func_8013767C(w);
        *(u8 *)(arg0 + 0x214) = *(u8 *)(arg0 + 0x214) + 1;
    } else {
        *(u8 *)(arg0 + 0x214) = *(u8 *)(arg0 + 0x214) + 2;
    }
}

extern s32 func_801399F0(s32);
extern void func_80139914(s32);

void func_800D32D4(void *arg0) {
    if (func_801399F0(*(s32 *)((u8 *)arg0 + 0x198)) != 0) {
        func_80139914(*(s32 *)((u8 *)arg0 + 0x198));
        *(u8 *)((u8 *)arg0 + 0x214) += 1;
    }
}

extern void func_8016F0E4(void);

void func_800D3328(void) {
    func_8016F0E4();
}

extern void (*D_800D3AA4[])(void);

void func_800D3348(u8 *arg0) {
    D_800D3AA4[*(u8 *)(arg0 + 0x214)]();
}

void func_800D3384(u8 *arg0) {
    *(u8 *)(arg0 + 0x214) += 1;
}

extern void func_8016F0E4(void);

void func_800D3398(void) {
    func_8016F0E4();
}

/* func_800D33B8 — exact mirror of the already-MATCHED func_800D33E0
 * (src/resident/resident.c:827), differing only in the global it passes
 * (&D_800D3AAC here vs &D_800D3AB0 there). func_8016EE40 takes (u8*, s32).
 * asm: lui/addiu a0=&D_800D3AAC ; jal func_8016EE40 ; lui a1=0x1000000 (delay). */
extern u8 D_800D3AAC;
extern void func_8016EE40(u8 *arg0, s32 arg1);

void func_800D33B8(void) {
    func_8016EE40(&D_800D3AAC, 0x1000000);
}

extern u8 D_800D3AB0;
extern void func_8016EE40(u8 *arg0, s32 arg1);

void func_800D33E0(void) {
    func_8016EE40(&D_800D3AB0, 0x1000000);
}

