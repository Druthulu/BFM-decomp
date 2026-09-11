void func_8017F768(s32 a0) {
    s32 s0 = a0;
    /* $s1 pin: without it the distance/angle pair allocates swapped ($s1<->$s2)
       AND `s1 = 0x800` floats out of the beqz delay slot. */
    s32 s1;
    /* NOT pinned: pinning $s2 makes local_alloc suggest the dying $18 for the
       `s2 >= 0x801` compare result, emitting `slti $s2,...` instead of the
       target's `slti $v0,$s2,0x801`. */
    s32 s2;
    /* $a0 pin: the target computes `andi $a0,$v0,0xFFF` then `addu $s1,$a0,$zero`
       and reuses the live $a0 as func_801898A4's first argument (no `move $a0,$s1`
       at the call). Coalescing kills that copy unless the value is born in $a0. */
    s32 angle;
    s32 ret;
    s16 pt[4];

    if (func_80148800((s32 *)&D_80126B58) & 3) {
        u8 t = (*(u8 *)(s0 + 5) + 1) & 1;
        *(u8 *)(s0 + 5) = t;
        *(s32 *)(s0 + 0x14) = D_8018E1E0[t];
    }

    pt[0] = D_80126940[0];
    pt[1] = 0;
    pt[2] = D_80126940[2];

    s2 = (s16)func_80013294((void *)&D_8018E1D0, (void *)pt);

    s1 = 0x800;
    if (s2 < 0x200) {
        *(s16 *)(s0 + 0x20) = 0x71;
        *(s16 *)(s0 + 0x22) = 0;
        *(s16 *)(s0 + 0x24) = 0;
        *(s16 *)(s0 + 0x2E) = 0;
        *(s16 *)(s0 + 0x30) = -0xC0;
        *(s16 *)(s0 + 0x32) = 0;
    } else {
        *(s16 *)(s0 + 0x22) = 0;

        angle = ratan2((s32)D_80126940[0] << 16, (s32)D_80126940[2] << 16) & 0xFFF;
        s1 = angle;

        *(s16 *)(s0 + 0x20) = 0x1C7;
        *(s16 *)(s0 + 0x30) = -0x10;
        *(s16 *)(s0 + 0x22) = 0;
        *(s16 *)(s0 + 0x24) = 0;
        *(s16 *)(s0 + 0x2E) = 0;
        /* +0x32 is stored ONCE PER ARM and, in this arm, ABOVE the inner if
           (§194-M: it lands in the bnez delay slot, so it dominates the branch
           and is NOT executed on the s2 >= 0x801 path). Writing it once after
           the outer if/else is what cross_jump then folds to 112 instructions. */
        *(s16 *)(s0 + 0x32) = 0;

        if (s2 >= 0x801) {
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

    D_801274EA = (s16)s1;
    ret = func_80012DBC((s32)D_801EF9F0, s1, 0x14, 1);
    D_801EF9F0 = (s16)ret;
    func_8017F92C(s0, (s16)ret, D_80126940);
}
