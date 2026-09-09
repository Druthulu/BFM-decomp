#include "common.h"
#include "../shared/engine_prelude.h"

#include "../shared/ov/func_80128158.h"

#include "../shared/ov/func_80128178.h"

#include "../shared/ov/func_80128198.h"

#include "../shared/ov/func_801281B8.h"

#include "../shared/ov/func_801281D8.h"

#include "../shared/ov/func_801281F8.h"


extern s32 D_8018D4F8;

s32 func_80128218(void) {
    return D_8018D4F8;
}


#include "../shared/ov/func_80128228.h"

#include "../shared/ov/func_80128248.h"

#include "../shared/ov/func_80128268.h"


extern u16 D_800B99F6;
extern void (*D_8017F510[])(void);

#include "../shared/ov/func_80128288__804a056f.h"


#include "../shared/ov/func_801282CC.h"

#include "../shared/ov/func_801282EC.h"

#include "../shared/ov/func_8012832C.h"

#include "../shared/ov/func_80128420.h"

#include "../shared/ov/func_801284B8.h"

#include "../shared/ov/func_801284F0.h"

#include "../shared/ov/func_8012853C.h"

#include "../shared/ov/func_80128564.h"

#include "../shared/ov/func_801285D4.h"


extern s32 func_800D18DC(void);
extern void func_8014607C(void);
extern void func_801287B8(void);
extern s32 func_80011A3C(void);
extern s32 D_8018E67C;

#include "../shared/ov/func_801285E4__22637e5f.h"


#include "../shared/ov/func_80128678.h"


// @class: other
// @stuck: none — MATCH (handwritten full inline-asm scratchpad-stack-switch wrapper w/ branch)
/*
 * HANDWRITTEN scratchpad-stack-switch dispatcher (same idiom as func_80128564 /
 * the func_8014ED28 family): repoints $sp into the D-cache scratchpad stack held
 * at *(0x1F8003FC), calls func_800D19F0, stashes its $v0 result through D_8018E67C,
 * restores $sp, then dispatches on the stored value:
 *   if (D_8018E67C != 0)  { func_8001903C(); func_80018FC8(); }
 *   else                  { func_8014607C(); <scratchpad-switch> func_801287B8(); }
 * Manipulating $sp is not expressible in C; full inline asm (manages its own frame).
 *
 * NOTE (maspsx --aspsx-version=2.56): the inline ".set noreorder" is written with a
 * SPACE, so maspsx's own is_reorder tracker stays True and it auto-fills EVERY
 * jal/j/branch delay slot with a nop (GNU as honors noreorder and adds none). So do
 * NOT write explicit delay-slot nops after jal/j/bne — that yields a double nop.
 * bnez is written as `bne $v0,$zero` so maspsx recognizes it (bnez isn't in its
 * branch set). The load-delay nop after `lw $v0,%lo(...)($v0)` is auto-inserted too.
 * %hi/%lo escaped as %%hi/%%lo (bare % is an operand placeholder).
 */
#include "../shared/ov/func_80128714__34914b60.h"




// @class: remat
// @stuck: none — MATCH (62 ins). D_8018FAB8 read needed the address REMATERIALIZED
//   (lui;addiu;lw 0(reg), not the folded lui;lw %lo) AND pinned to $a0. volatile forces the
//   remat; register __asm__("$4") forces the a0 allocation (gcc otherwise picks v0). Both levers
//   required — pin-alone folds, volatile-alone lands in v0.

extern s32 D_80126B58;
extern s32 D_8018FAB8;
extern u16 D_800B99DA;
extern u8 D_800B9A64;

extern void func_80129CF8(void);
extern void func_8017849C(void);
extern void func_8014FDF4(struct S8014FDF4 *a0);
extern s32 func_801505FC(s32 a0);
extern void func_801508B4(void *a0);
extern void func_80165E90(void);
extern void func_801627E8(void);
extern void func_80162B1C(void);
extern void func_80165CA0(void);
extern void func_80129010(void);
extern void func_8013CA14(void);
extern void func_800190AC(void);
extern void func_8012956C(void);
extern void func_8016E95C(void);
extern void func_801754A8(void);
extern void func_8013BC7C(void);
extern void func_8013BCDC(void);
extern void func_801379FC(void);
extern void func_8001212C(void);

#include "../shared/ov/func_801287B8__96084aee.h"



extern void func_8001ABBC(s32 a0, s32 a1, void *a2, s32 a3, s32 sp10);
extern s32 D_8018D4F8;
extern u8 D_800AEFD0;

s32 func_801288B0(void) {
    func_8001ABBC(0, 0, &D_800AEFD0, D_8018D4F8, 0);
}



// @class: remat
// @stuck: none — MATCH. &D_800C7C60 CSE'd once via pointer local `p` so the same reg feeds the *p=0x60 store AND arg5; writing D_800C7C60=0x60 directly would emit a 2nd address materialization (+1 ins). Mirrors matched sibling func_80128998.

extern int D_800C7C60;
extern int *D_800C7C64;
extern int D_800A2E20;
extern int D_800AF558;
extern int D_8018D4F8;

extern void func_8001ABBC(s32 a0, s32 a1, void *a2, s32 a3, s32 sp10);

#include "../shared/ov/func_801288E8__d532bf22.h"




// @class: remat
// @stuck: none — MATCH (pointer-var forces single materialization of &D_800C7C60, reused as store base + arg5)

extern void func_8001ABBC(s32 a0, s32 a1, void *a2, s32 a3, s32 sp10);
extern int D_800C7C60;
extern int *D_800C7C64;
extern int D_800A2E20;
extern u8 D_800AF560;
extern s32 D_8018D4F8;

#include "../shared/ov/func_80128940__6a0ce359.h"




// @class: remat
// @stuck: none — MATCH. &D_800C7C60 must be CSE'd once (pointer local `p`) so the same reg feeds the *p=13 store AND arg5; writing D_800C7C60=13 directly emits a 2nd address materialization (+1 ins).

extern int D_800C7C60;
extern int *D_800C7C64;
extern int D_800A2E20;
extern int D_800AECB0;
extern s32 D_8018D4F8;

extern void func_8001ABBC(s32 a0, s32 a1, void *a2, s32 a3, s32 sp10);

#include "../shared/ov/func_80128998__cd2af414.h"



extern s32 D_8018D4F8;
extern u8 D_800AECB8;
extern void func_8001ABBC(s32 a0, s32 a1, void *a2, s32 a3, s32 a4);

s32 func_801289F0(void) {
    func_8001ABBC(0, 0, &D_800AECB8, D_8018D4F8, 0);
}


extern void func_80011B7C(int);
extern void func_80011C10(void);
extern u16 D_800B99F6;
extern s16 D_800B9A00;
extern M2C_UNK (*D_8017F24C)();
extern s16 (*D_8017F250)();

#include "../shared/ov/func_80128A28__badd0159.h"


extern u16 D_800B99F6;
extern M2C_UNK (*D_8017F258)();
extern s32 (*D_8017F25C)();
extern s32 D_8018E678;

#include "../shared/ov/func_80128AF4__79334e07.h"


#include "../shared/ov/func_80128C14.h"



extern CdFileLoc_80128C98 cdFileLocTable[];
extern void func_8001ABBC(s32 a0, s32 a1, void *a2, s32 a3, s32 a4);

#include "../shared/ov/func_80128C98__363b5a0e.h"




extern CdFileLoc cdFileLocTable[];
extern void func_8001ABBC(s32 a0, s32 a1, void *a2, s32 a3, s32 a4);

#include "../shared/ov/func_80128CFC__120c5b53.h"


#include "../shared/ov/func_80128D60.h"

#include "../shared/ov/func_80128DB4.h"

#include "../shared/ov/func_80128EA8.h"

#include "../shared/ov/func_80128ED8.h"

extern M2C_UNK D_8018D4FC;

#include "../shared/ov/func_80128FAC__205d953e.h"


#include "../shared/ov/func_80129010.h"

#include "../shared/ov/func_801290DC.h"

#include "../shared/ov/func_8012913C.h"

#include "../shared/ov/func_801291C0.h"

#include "../shared/ov/func_80129220.h"

#include "../shared/ov/func_80129248.h"

#include "../shared/ov/func_80129258.h"

#include "../shared/ov/func_8012927C.h"

#include "../shared/ov/func_801292C8.h"

#include "../shared/ov/func_8012931C.h"

#include "../shared/ov/func_80129350.h"

#include "../shared/ov/func_80129374.h"

#include "../shared/ov/func_80129398.h"

#include "../shared/ov/func_80129428.h"

#include "../shared/ov/func_8012943C.h"

#include "../shared/ov/func_8012944C.h"




extern s32 D_8018E67C;

extern void func_801299C8();
extern void func_80015B6C(s32, s16, s32, s16, s32, s32, s32, s32, s32, s32);
extern void GsSortBg(s32 *, void *, u16, s32 *);
extern void GsSortFastBg(s32 *, void *, u16, s32 *);

#include "../shared/ov/func_8012956C__3fa9093d.h"


#include "../shared/ov/func_801298F4.h"


// @class: schedule
// @stuck: none — MATCH (158 ins, match_one relocation-masked)
//
// Levers that landed it (2 iterations, 56 mismatched -> MATCH):
//  1. §43 K&R s16-param definition: `void f(a0,a1,a2) s16 a0; s16 a1; u8 *a2;` reproduces the
//     in-place `sll $a0,$a0,16` zero-test on the arg reg + the raw-$a1 copy (`addu $a3,$a1,$zero`)
//     stashed in the jtbl branch delay slot and RE-extended per use in the case body.
//  2. §18 array-of-struct %lo-fold: three sibling extern arrays D_8018E680/1/2[] (a 4-row x 3-comp
//     RGB gradient table, stride 4) give `lui $at,%hi(sym); addu $at,$at,idx4; sb $v0,%lo(sym)($at)`
//     for the indexed case and plain `lui/sb %lo(sym+k)` for the constant-index case.
//  3. Switch CASE-ORDER = source order: the jump table dispatches case 1 to the FIRST emitted block,
//     so `case 1:` must be written before `case 0/2:` and `case 3/4:`.
//  4. THE residual (56 -> 0): the case-1 body must be written ROW-MAJOR (BE0[0],BE1[0],BE2[0],
//     BE0[4],BE1[4],BE2[4],...), i.e. the natural table fill. gcc-2.7.2's sched pass then REORDERS
//     the stores itself (BE0,BE1,BE5,BE8,BE4,BEC,BE9,BED,BE2,BE6,BEA,BEE) because the three arrays
//     are distinct declarations => provably non-aliasing. Writing the source in the target's STORE
//     order is the trap: it pins the b*255 / r*143 CSEs at their late store sites instead of letting
//     them hoist into $a0/$v1 at rows 0/1, and mis-schedules the D_8018F9B8 load.
//  5. Shift signedness: `u32` component locals give `srl` for r*5>>3 and g*25>>1; an explicit
//     `(s32)(x * 255) >> 4` gives `sra` for the *255 / *143 / *45 terms (mixed within one block).

extern u8 D_8018FAB2;
extern u8 D_8018F9DA;
extern u8 D_8018F9B8;
extern u8 D_8018E680[];
extern u8 D_8018E681[];
extern u8 D_8018E682[];

#include "../shared/ov/func_801299C8__f9a41b0d.h"

#include "../shared/ov/func_80129C40.h"

#include "../shared/ov/func_80129CF8.h"

#include "../shared/ov/func_80129FF4.h"

#include "../shared/ov/func_8012A018.h"


#include "../shared/ov/func_8012A048.h"

#include "../shared/ov/func_8012A094.h"

#include "../shared/ov/func_8012A0E0.h"

#include "../shared/ov/func_8012A100.h"

#include "../shared/ov/func_8012A110.h"



// @class: regalloc-order
// @stuck: none — MATCH (78 ins, relocation-masked). Register pins ($2-$5 reused for
//   the D_x200-x20C words then the D_x220-x226 halfwords; $6-$10 held across for the
//   D_x228/x22A/x294/x298/x29A tail) force the frameless 9-deep allocation the default
//   -O2 pre-reload scheduler otherwise blows to a 3-reg spill (all 720 stmt orders spill
//   without the pins). A single zero-byte scheduling/memory barrier after the 4 word
//   stores stops gcc hoisting the first 8-byte block copy above them.




#include "../shared/ov/func_8012A1BC.h"


#include "../shared/ov/func_8012A2F4.h"

#include "../shared/ov/func_8012A304.h"









#include "../shared/ov/func_8012A328.h"


#include "../shared/ov/func_8012A418.h"





#include "../shared/ov/func_8012A464.h"


#include "../shared/ov/func_8012A4BC.h"

extern void func_8012A598(void *a0);
#include "../shared/ov/func_8012A568.h"


#include "../shared/ov/func_8012A598.h"

#include "../shared/ov/func_8012A5F8.h"

#include "../shared/ov/func_8012A62C.h"

#include "../shared/ov/func_8012A68C.h"

#include "../shared/ov/func_8012A6D0.h"

#include "../shared/ov/func_8012A758.h"

#include "../shared/ov/func_8012A79C.h"

#include "../shared/ov/func_8012A7D4.h"

#include "../shared/ov/func_8012A828.h"

#include "../shared/ov/func_8012A860.h"

#include "../shared/ov/func_8012A8B0.h"

#include "../shared/ov/func_8012A8E8.h"

#include "../shared/ov/func_8012A908.h"

#include "../shared/ov/func_8012A988.h"


extern void func_8012AAAC(void *arg0);

#include "../shared/ov/func_8012AAAC__8ccde920.h"


extern void func_8012AAAC();
extern M2C_UNK D_8017F5A4;

#include "../shared/ov/func_8012ACA0__1d7a3eb2.h"
