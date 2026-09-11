void func_801A3B18(s32 param_1)
{
    Mtx32_801A3B18 mtx;   /* sp+0x10 */
    SVec_801A3B18 sv;     /* sp+0x30 */
    SVec_801A3B18 sv2;    /* sp+0x38 */
    s32 vec[4];           /* sp+0x40 */
    s32 flag;             /* sp+0x50 */
    s32 v0;
    s32 amt;
    s32 d;
    s32 e;
    s32 ang;
    s32 mag;
    s32 *p;
    /* D_800AE620 is the shared 32-byte matrix global; this TU already declares it
     * later as `extern Mtx32_801A90D8 D_800AE620;` (md_SC07_004.c:1569). Declared
     * here at BLOCK scope on purpose: a second file-scope spelling is a hard
     * `conflicting types` error in gcc-2.7.2, while a block-scope one is only a
     * warning — and re-typedef'ing Mtx32_801A90D8 above line 1565 would break the
     * definition that already lives there. */
    extern s32 D_800AE620[8];

    mtx = *(Mtx32_801A3B18 *)&D_800AE620;

    RotMatrixY(*(s16 *)(*(s32 *)(param_1 + 0x20) + 0x12), &mtx);

    mtx.t[0] = *(s16 *)(param_1 + 0x6);
    mtx.t[1] = *(s16 *)(param_1 + 0xA);
    mtx.t[2] = *(s16 *)(param_1 + 0xE);
    func_8004914C(&mtx);
    func_800491AC(&mtx);

    sv.vy = 0;
    sv.vx = 0;
    sv.vz = 0x80;
    RotTransSV((s32)&sv, (s32)&sv, &flag);

    sv2.vx = (u16)D_80126B5E;
    sv2.vy = (u16)D_80126B62;
    sv2.vz = (u16)D_80126B66;

    p = D_80126B58;
    d = func_8012B70C((s16 *)&sv, (s16 *)&sv2) -
        *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x12);
    e = d & 0xFFF;
    ang = e + 0;
    if (e >= 0x800) {
        ang = e | 0xF000;
    }
    mag = ang + 0;
    if ((s16)ang < 0) {
        mag = -ang;
    }

    v0 = ((s32 (*)(s32))func_8012BE54)(param_1);

    if (func_8014CB8C() == 0 && v0 <= 0x23FFF && (s16)mag < 0x200 &&
        func_8017267C(p) == 0) {
        if (D_801F8864 > -0x1E0000) {
            D_801F8864 -= 0xC000;
        }
    } else {
        if (D_801F8864 < 0) {
            D_801F8864 += 0x10000;
            if (D_801F8864 > 0) {
                D_801F8864 = 0;
            }
        }
    }

    amt = D_801F8864;
    if (amt != 0) {
        vec[1] = 0;
        vec[0] = 0;
        vec[2] = amt;
        ApplyRotMatrixLV(vec, vec);
        p[1] += vec[0];
        p[3] += vec[2];
    }
}
