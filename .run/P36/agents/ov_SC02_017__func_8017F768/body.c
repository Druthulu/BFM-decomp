void func_8017F768(s32 a0) {
    s16 dir;
    s16 dist;
    s32 angle;
    s32 ret;
    s16 pt[4];

    if (func_80148800((s32 *)&D_80126B58) & 3) {
        u8 t = (*(u8 *)(a0 + 5) + 1) & 1;
        *(u8 *)(a0 + 5) = t;
        *(s32 *)(a0 + 0x14) = D_8018E1E0[t];
    }

    pt[0] = D_80126940[0];
    pt[1] = 0;
    pt[2] = D_80126940[2];

    dist = func_80013294((void *)&D_8018E1D0, (void *)pt);

    if (dist < 0x200) {
        dir = 0x800;
        *(s16 *)(a0 + 0x20) = 0x71;
        *(s16 *)(a0 + 0x22) = 0;
        *(s16 *)(a0 + 0x24) = 0;
        *(s16 *)(a0 + 0x2E) = 0;
        *(s16 *)(a0 + 0x30) = -0xC0;
        *(s16 *)(a0 + 0x32) = 0;
    } else {
        *(s16 *)(a0 + 0x22) = 0;

        angle = ratan2((s32)D_80126940[0] << 16, (s32)D_80126940[2] << 16) & 0xFFF;
        dir = angle;

        *(s16 *)(a0 + 0x20) = 0x1C7;
        *(s16 *)(a0 + 0x30) = -0x10;
        *(s16 *)(a0 + 0x22) = 0;
        *(s16 *)(a0 + 0x24) = 0;
        *(s16 *)(a0 + 0x2E) = 0;
        /* +0x32 is stored ONCE PER ARM and, in this arm, ABOVE the inner if
           (§194-M: it lands in the bnez delay slot, so it dominates the branch
           and is NOT executed on the dist >= 0x801 path). Writing it once after
           the outer if/else is what cross_jump then folds to 112 instructions. */
        *(s16 *)(a0 + 0x32) = 0;

        if (dist >= 0x801) {
            u16 tmp[4];
            tmp[0] = 0;
            tmp[1] = D_80126942;
            tmp[2] = 0x800;

            func_801898A4(angle, tmp, tmp);

            D_80126940[0] = (s16)tmp[0] >> 3;
            D_80126942 = (s16)tmp[1] >> 3;
            D_80126940[2] = (s16)tmp[2] >> 3;
        }
    }

    D_801274EA = dir;
    ret = func_80012DBC((s32)D_801EF9F0, dir, 0x14, 1);
    D_801EF9F0 = (s16)ret;
    func_8017F92C(a0, (s16)ret, D_80126940);
}
