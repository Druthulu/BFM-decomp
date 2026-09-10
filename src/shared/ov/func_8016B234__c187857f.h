/* func_8016B234 — shared body (overlay slot 0x80128158, h_exact c187857f). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_8016B234(s32 param_1) {

    extern u8 D_800AF648;
    extern u8 D_801823DC;
    short input[3];
    Prim_B234 prim;
    struct { s16 xy[2]; s32 sp1c; s32 flag; } out;
    void *dp;
    u32 uVar1; /* the projected screen Y, then the UV column index */
    s16 iVar2;
    s32 X, Y0, Y1, base, ni;
    s16 xtmp;
    s32 sxy;
    s32 hh;

    dp = &D_800AF648;
    func_8004914C(dp);
    func_800491AC(dp);
    input[0] = *(u16 *)(param_1 + 6);
    input[1] = *(u16 *)(param_1 + 0xA);
    input[2] = *(u16 *)(param_1 + 0xE);
    RotTransPers((s32)input, (s32)out.xy, &out.sp1c, &out.flag);
    if ((out.flag & 0xffffefff) == 0) {
        sxy = *(s32 *)out.xy;
        prim.a04 = 0x10;
        X = *(u16 *)(param_1 + 0x2a) + sxy;
        uVar1 = (u16)out.xy[1];
        prim.ax = prim.cx = X;
        prim.bx = prim.dx = X + 8;
        Y0 = uVar1 - *(u16 *)(param_1 + 0x26);
        prim.ay = prim.by = Y0;
        hh = *(u16 *)(param_1 + 0x26);
        prim.v0 = prim.v1 = 0x1d0;
        prim.v2 = prim.v3 = 0x1d8;
        prim.cy = prim.dy = uVar1 + hh;
        prim.r = prim.g = prim.b = *(u8 *)(param_1 + 0x24);
        prim.code = (&D_801823DC)[*(s32 *)(param_1 + 0x2c)];
        if (*(s16 *)(param_1 + 0x26) < 5) {
            prim.tag = 0;
        } else {
            prim.tag = 0x50000000;
        }
        uVar1 = *(u16 *)(param_1 + 0x30);
        iVar2 = 0;
        if (0 < *(s16 *)(param_1 + 0x28) + 1) {
            do {
                base = ((uVar1 + 1) & 0xf) << 3;
                prim.u0 = prim.u2 = base + 0x620;
                prim.u1 = prim.u3 = base + 0x628;
                func_80016ED4(&prim);
                uVar1 = (s32)(uVar1 << 0x10) >> 0x14;
                iVar2 = iVar2 + 1;
                xtmp = prim.ax;
                prim.cx = prim.ax = xtmp - 8;
                prim.bx = prim.dx = xtmp;
            } while ((s16)iVar2 < *(s16 *)(param_1 + 0x28) + 1);
        }
    }
}
