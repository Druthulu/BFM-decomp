/*
 * func_8012E364  (ov_SC01_077, 0x8012E364, 67 ins, gcc-2.7.2 -O2)
 * STATUS: NEAR (match_one: 67/67 ins, 22 masked-positional mismatches; aligned edit-dist ~39).
 *
 * Semantics are fully recovered and the whole function matches EXCEPT one residual:
 * a gcc-2.7.2 register-allocation / instruction-schedule tie-break in the /144 division
 * block.  The target loads D_801D9498 LATE into $v1 (reusing the register that held the
 * dividend-sign, freed once the divresult lands in $a0), which also emits a load-delay nop.
 * cc1 here instead HOISTS that pure global load into the mult shadow (into free $a0),
 * pushing divresult to $v0 and mfhi to $a1 -- and that register choice then cascades
 * different register names through the entire tail.
 *
 * Levers already applied (each byte-verified to fix its region):
 *   - __asm__("":::"memory") after the unk5C=0 store  -> forces unk5C first, frees the
 *     bnez delay slot for the multiplier-%hi lui + the split multiplier reload (first 17
 *     ins now match exactly, incl. `move a2,a0`, D_80126CE0 in $a0).
 *   - register k10 __asm__("$7"), live across the div block -> gcc keeps 0x1000 in $a3,
 *     fills the blez delay slot with `addiu a3,$zero,0x1000`, and reuses it for both the
 *     D_801D949C store and the `+0x1000` add (tail 0x1000-hoist matches target).
 *   - register p __asm__("$6") = arg0 -> keeps the pointer in $a2 (the `move a2,a0`).
 *   - raw-offset pointer casts -> conservative aliasing so the unk1C store precedes the
 *     D_801D9498 load (matches target's mult-shadow contents).
 *   - `*(volatile s32*)&D_801D9498` for the single div-block read -> this pushed divresult
 *     into $a0 and mfhi into $t0 (both matching target); its cost is a %hi/%lo unfold on
 *     that one load and D_801D9498 landing in $a1 instead of $v1.
 *
 * Residual is the documented regalloc/schedule tie-break hard class (cookbook §5/§10;
 * sibling func_80015A74's hoisted-const-vs-init survived 6648 permuter iters). Pins on the
 * div-block value ($v1) or the divresult ($a0) don't help: gcc-2.7.2 reserves a named
 * register variable for its whole scope, which dislodges D_80126CE0/the dividend that also
 * need $v1/$a0 in the first half. Next lever: the register-permuter over the div-block
 * regalloc, seeded from this draft.
 *
 * Clean semantic form (no levers), for reference / permuter seeding:
 *   arg->unk5C = 0;
 *   if (D_80126CE0 == 0) { D_801D9498 = 0x1000; D_801D949C = 0x1000; }
 *   arg->unk1C += 1;
 *   D_801D9498 -= (D_801D9498 - ((0x90 - D_80126CE0) << 12) / 144) / 4;   // skip if ==0
 *   old = D_801D949C; D_801D949C = 0x1000;
 *   D_801D9498 = D_801D9498 - old + 0x1000;
 *   arg->unk20->unk2C |= 0x10;
 *   v = abs(D_801D9498);
 *   arg->unk20->unk1C = v; arg->unk20->unk18 = v; arg->unk20->unk1A = 0x1000;
 */
typedef signed char s8;
typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;
typedef signed int s32;
typedef unsigned int u32;

struct Sub {
    u8 pad00[0x18];
    s16 unk18;
    s16 unk1A;
    s16 unk1C;
    u8 pad1E[0x2C - 0x1E];
    u16 unk2C;
};

extern s16 D_80126CE0;
extern s32 D_801D9498;
extern s32 D_801D949C;

void func_8012E364(void *arg0) {
    s32 temp_v0;
    s32 temp_v1;
    s32 a1;
    struct Sub *sub;
    s32 var;
    s32 var_v0;
    s32 var_v0_2;
    s32 dr;
    s32 d9498;
    register s32 k10 __asm__("$7");
    register u8 *p __asm__("$6");

    p = (u8 *)arg0;
    *(s16 *)(p + 0x5C) = 0;
    __asm__("" ::: "memory");
    if (D_80126CE0 == 0) {
        D_801D9498 = 0x1000;
        D_801D949C = 0x1000;
    }
    *(s32 *)(p + 0x1C) = *(s32 *)(p + 0x1C) + 1;
    k10 = 0x1000;
    dr = ((0x90 - D_80126CE0) << 12) / 144;
    d9498 = *(volatile s32 *)&D_801D9498;
    temp_v0 = d9498 - dr;
    if (temp_v0 > 0) {
        var_v0 = d9498 - (temp_v0 >> 2);
        goto block_8;
    }
    var_v0_2 = -temp_v0;
    if (temp_v0 < 0) {
        if (var_v0_2 < 0) {
            var_v0_2 += 3;
        }
        var_v0 = d9498 + (var_v0_2 >> 2);
block_8:
        D_801D9498 = var_v0;
    }
    a1 = D_801D949C;
    sub = *(struct Sub **)(p + 0x20);
    D_801D949C = k10;
    temp_v1 = D_801D9498 - a1 + k10;
    D_801D9498 = temp_v1;
    sub->unk2C |= 0x10;
    sub = *(struct Sub **)(p + 0x20);
    var = temp_v1;
    if (temp_v1 < 0) {
        var = -var;
    }
    sub->unk1C = var;
    sub->unk18 = var;
    (*(struct Sub **)(p + 0x20))->unk1A = 0x1000;
}
