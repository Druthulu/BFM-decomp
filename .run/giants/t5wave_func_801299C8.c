// @class: schedule
// @stuck: none — MATCH (158 ins, match_one relocation-masked)
//
// Levers that landed it (2 iterations, 56 mismatched -> MATCH):
//  1. §43 K&R s16-param definition: `void f(a0,a1,a2) s16 a0; s16 a1; u8 *a2;` reproduces the
//     in-place `sll $a0,$a0,16` zero-test on the arg reg + the raw-$a1 copy (`addu $a3,$a1,$zero`)
//     stashed in the jtbl branch delay slot and RE-extended per use in the case body.
//  2. §18 array-of-struct %lo-fold: three sibling extern arrays D_801D3BE0/1/2[] (a 4-row x 3-comp
//     RGB gradient table, stride 4) give `lui $at,%hi(sym); addu $at,$at,idx4; sb $v0,%lo(sym)($at)`
//     for the indexed case and plain `lui/sb %lo(sym+k)` for the constant-index case.
//  3. Switch CASE-ORDER = source order: the jump table dispatches case 1 to the FIRST emitted block,
//     so `case 1:` must be written before `case 0/2:` and `case 3/4:`.
//  4. THE residual (56 -> 0): the case-1 body must be written ROW-MAJOR (BE0[0],BE1[0],BE2[0],
//     BE0[4],BE1[4],BE2[4],...), i.e. the natural table fill. gcc-2.7.2's sched pass then REORDERS
//     the stores itself (BE0,BE1,BE5,BE8,BE4,BEC,BE9,BED,BE2,BE6,BEA,BEE) because the three arrays
//     are distinct declarations => provably non-aliasing. Writing the source in the target's STORE
//     order is the trap: it pins the b*255 / r*143 CSEs at their late store sites instead of letting
//     them hoist into $a0/$v1 at rows 0/1, and mis-schedules the D_801D5A30 load.
//  5. Shift signedness: `u32` component locals give `srl` for r*5>>3 and g*25>>1; an explicit
//     `(s32)(x * 255) >> 4` gives `sra` for the *255 / *143 / *45 terms (mixed within one block).

extern u8 D_801D5B2A;
extern u8 D_801D5A52;
extern u8 D_801D5A30;
extern u8 D_801D3BE0[];
extern u8 D_801D3BE1[];
extern u8 D_801D3BE2[];

void func_801299C8(arg0, arg1, arg2)
s16 arg0;
s16 arg1;
u8 *arg2;
{
    u32 r;
    u32 g;
    u32 b;
    s32 i;

    if (arg0 != 0) {
        switch (arg1) {
        case 1:
            r = D_801D5B2A;
            g = D_801D5A52;
            b = D_801D5A30;
            D_801D3BE0[0] = r * 5 >> 3;
            D_801D3BE1[0] = g << 3;
            D_801D3BE2[0] = (s32)(b * 255) >> 4;
            D_801D3BE0[4] = (s32)(r * 143) >> 4;
            D_801D3BE1[4] = g * 25 >> 1;
            D_801D3BE2[4] = (s32)(b * 255) >> 4;
            D_801D3BE0[8] = (s32)(r * 255) >> 4;
            D_801D3BE1[8] = (s32)(g * 255) >> 4;
            D_801D3BE2[8] = (s32)(b * 255) >> 4;
            D_801D3BE0[12] = (s32)(r * 143) >> 4;
            D_801D3BE1[12] = (s32)(g * 255) >> 4;
            D_801D3BE2[12] = (s32)(b * 45) >> 2;
            break;
        case 0:
        case 2:
            i = arg1 * 4;
            D_801D3BE0[i] = arg2[0x44] * D_801D5B2A >> 4;
            D_801D3BE1[i] = arg2[0x45] * D_801D5A52 >> 4;
            D_801D3BE2[i] = arg2[0x46] * D_801D5A30 >> 4;
            i = (arg1 + 1) * 4;
            D_801D3BE0[i] = arg2[0x47] * D_801D5B2A >> 4;
            D_801D3BE1[i] = arg2[0x48] * D_801D5A52 >> 4;
            D_801D3BE2[i] = arg2[0x49] * D_801D5A30 >> 4;
            break;
        case 3:
        case 4:
            arg2[0x20] = D_801D5B2A << 3;
            arg2[0x21] = D_801D5A52 << 3;
            arg2[0x22] = D_801D5A30 << 3;
            break;
        }
    }
}
