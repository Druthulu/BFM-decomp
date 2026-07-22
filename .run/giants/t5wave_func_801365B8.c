// @class: schedule
// @stuck: none — MATCH (155/155). Two levers: (1) the three D_8012672x tail globals MUST be
//   declared `extern s16 D_x[];` (array => MEM_IN_STRUCT_P) so gcc-2.7.2's sched2 treats the
//   `sh` stores as possibly aliasing the `lh arg0[k]` loads and refuses to hoist loads across
//   them (scalar `extern s16 D_x;` lets it hoist => 29-off tail). (2) param 2 must be `u16`
//   (not s32/u16-cast): the narrow-promoted parm dies at the entry `andi`, so local-alloc
//   reuses $a1 for the AND dest (`andi $a1,$a1,1`); an s32 parm reads the $t2 copy into $v0.
//   Also: the D_80193B6{4,C} / D_80193B70 pointer globals are cached in locals ONLY AFTER the
//   entry if/else (gcc-2.7.2 has no GCSE, so the merge block reloads them; caching before the
//   if would keep them in regs and lose the 3 %hi/%lo reloads in the branch arms).
s32 func_801365B8(s16 *arg0, u16 arg1, s16 arg2) {
    extern s16 *D_80193B64;
    extern s16 *D_80193B68;
    extern s16 *D_80193B6C;
    extern s16 *D_80193B70;
    extern s16 D_801152A8;
    extern s16 D_801152AA;
    extern s16 D_801152AC;
    extern s16 D_80126720[];
    extern s16 D_80126722[];
    extern s16 D_80126724[];
    s16 *p64;
    s16 *p6C;
    s16 *p70;
    s32 d;
    s32 n;
    s32 dv;
    s16 x;

    if ((arg1 & 1) == 0) {
        d = arg2 - *D_80193B64;
        n = d;
        dv = -*D_80193B70;
    } else {
        dv = *D_80193B70;
        d = *D_80193B64 - arg2;
        n = -d;
    }
    p64 = D_80193B64;
    p6C = D_80193B6C;
    p70 = D_80193B70;
    p6C[0] = p64[0] + n;
    p6C[1] = p64[1] + (-d * p70[1]) / dv;
    x = p64[2] + (-d * p70[2]) / dv;
    p6C[2] = x;
    if (x < arg0[6]) {
        return 0;
    }
    if (arg0[7] < x) {
        return 0;
    }
    if (p6C[1] < arg0[4]) {
        return 0;
    }
    if (arg0[5] < p6C[1]) {
        return 0;
    }
    if (arg1 & 0x8000) {
        p6C[1] = D_80193B68[1];
        p6C[2] = D_80193B68[2];
    }
    D_801152AC = 0;
    D_801152AA = 0;
    if (arg1 & 1) {
        D_801152A8 = 0xFFF;
        D_80193B6C[0] = arg2 + 2;
    } else {
        D_801152A8 = -0xFFF;
        D_80193B6C[0] = arg2 - 2;
    }
    D_80126720[0] = (arg0[2] + arg0[3]) >> 1;
    D_80126722[0] = (arg0[4] + arg0[5]) >> 1;
    D_80126724[0] = (arg0[6] + arg0[7]) >> 1;
    return 1;
}
