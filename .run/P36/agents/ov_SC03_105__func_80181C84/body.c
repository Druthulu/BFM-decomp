void func_80181C84(s32 a0)
{
    /* LOAD-BEARING (P36 S104 e32, replacing the $s2/$v1 pins): case 7 and case 8 each carry their
     * OWN copy of the 0x34/0x1C/0x102/0xE0 tail (no shared label) -- the extra references raise the
     * entity's allocno_compare priority above `i` (global.c:594-607), so the entity takes $s1 and `i`
     * $s2; post-reload cross-jump (jump.c:2371) re-merges the two tails, so the bytes keep one copy.
     * `q` is declared inside each `if (p != 0)` block: a q shared by the two div loops is a global
     * allocno that conflicts with the unused-remainder pseudo of `0x1C0 / n` in $v1; a per-block q is
     * local and takes $v1 itself. */
    s32 s1;
    Local_80181C84 local;
    u8 *b58;
    u16 tE;
    u16 t34;
    u16 t34b;
    s32 i;
    s32 n;
    s32 r;
    s32 p;
    s32 tA;
    s32 t6;

    s1 = a0;
    /* LOAD-BEARING: `u8 *` base + *(s16 *)(b58 + 6), the TU:5099/7196 idiom -- this is what
     * parks &D_80126B58 in $s0 across the whole switch (prologue la, two `lh 0x6($s0)`). */
    b58 = (u8 *)&D_80126B58;

    switch (*(u16 *)(s1 + 0x34)) {
    case 0:
        *(s32 *)(s1 + 0x1C) = 0x40;
        /* LOAD-BEARING: read 0x34 into a temp BEFORE the 0xE0 read-modify-write, store it after.
         * Written inline, the lhu sinks below the lw and the +1 lands in the wrong register. */
        t34 = *(u16 *)(s1 + 0x34) + 1;
        *(s32 *)(s1 + 0xE0) = *(s32 *)(s1 + 0xE0) & ~0x10;
        *(u16 *)(s1 + 0x34) = t34;
    case 1:
        if (func_8012BEE8(s1) == 0) {
            return;
        }
        *(s16 *)(s1 + 0xA) = -0x102;
        *(s16 *)(s1 + 0xE) = -0x1C8;
        *(s32 *)(s1 + 0x1C) = 0x20;
        *(u16 *)(s1 + 0x6) = 0;
        *(s32 *)(s1 + 0x58) = ((s32)D_8018E2B8 | 0x40000000) | 0x20000000;
        *(u16 *)(s1 + 0x34) = *(u16 *)(s1 + 0x34) + 1;
        func_80184604(*(s16 *)(b58 + 6) > 0 ? 4 : 6);
        local.f0 = *(u16 *)(s1 + 0x6);
        local.f1 = *(u16 *)(s1 + 0xA);
        tE = *(u16 *)(s1 + 0xE);
        local.f3 = 0x170;
        local.f4 = 0x8000;
        local.f5 = 0;
        local.f6 = 0x7FFF;
        local.f7 = 0x80;
        local.f2 = tE;
        i = 0;
        do {
            local.f8 = i << 10;
            func_8012C51C(&local, s1);
            i++;
        } while (i < 4);
        break;
    case 2:
        if (func_8012BEE8(s1) != 0) {
            func_8018364C((void *)s1);
            /* LOAD-BEARING: the duplicated store (§224), not a ternary. As `<= 0 ? 4 : 3` the
             * shape is right but the result takes $v1; only the if/else lets it reuse the
             * dead compare's $v0. Polarity matters too: the DEFAULT (delay-slot) value is 3. */
            if (*(s16 *)(b58 + 6) <= 0) {
                *(u16 *)(s1 + 0x34) = 4;
            } else {
                *(u16 *)(s1 + 0x34) = 3;
            }
            func_8002D4C8(0xC2D, 0);
        }
        break;
    case 3:
        *(u16 *)(s1 + 0x102) = *(u16 *)(s1 + 0x102) + 0x20;
        if ((s16)*(u16 *)(s1 + 0x102) > 0x200) {
            *(u16 *)(s1 + 0x102) = 0x200;
            func_8013C9C4(D_8018AAA4);
            *(u16 *)(s1 + 0x34) = 5;
            *(s32 *)(s1 + 0x1C) = 0x40;
            func_8002D4C8(0xC06, 0);
            n = D_8018E88C[D_801BCBBC];
            for (i = 0; i < n; i++) {
                p = ((s32 (*)(void *, s16, s32))func_80183D38)((void *)s1, 0, 0);
                if (p != 0) {
                    s32 q;
                    r = rand();
                    q = 0x1C0 / n;
                    /* LOAD-BEARING: load 0x6 BEFORE storing 0xA (they may alias, so gcc will
                     * not hoist it afterwards), fold the +-0x40 into t6, and write the sum
                     * back THROUGH t6 so it keeps t6's register instead of taking a new one. */
                    tA = *(u16 *)(p + 0xA) - 0xE0;
                    t6 = *(u16 *)(p + 0x6) + 0x40;
                    *(u16 *)(p + 0xA) = tA;
                    t6 = t6 + (i * q + r % q);
                    *(u16 *)(p + 0x6) = t6;
                }
            }
        }
        break;
    case 4:
        *(u16 *)(s1 + 0x102) = *(u16 *)(s1 + 0x102) - 0x20;
        if ((s16)*(u16 *)(s1 + 0x102) < -0x200) {
            *(s16 *)(s1 + 0x102) = -0x200;
            func_8013C9C4(D_8018AAA4);
            *(u16 *)(s1 + 0x34) = 6;
            *(s32 *)(s1 + 0x1C) = 0x40;
            func_8002D4C8(0xC06, 0);
            n = D_8018E88C[D_801BCBBC];
            for (i = 0; i < n; i++) {
                p = ((s32 (*)(void *, s16, s32))func_80183D38)((void *)s1, 0, 0);
                if (p != 0) {
                    s32 q;
                    r = rand();
                    q = 0x1C0 / n;
                    /* LOAD-BEARING: load 0x6 BEFORE storing 0xA (they may alias, so gcc will
                     * not hoist it afterwards), fold the +-0x40 into t6, and write the sum
                     * back THROUGH t6 so it keeps t6's register instead of taking a new one. */
                    tA = *(u16 *)(p + 0xA) - 0xE0;
                    t6 = *(u16 *)(p + 0x6) - 0x40;
                    *(u16 *)(p + 0xA) = tA;
                    t6 = t6 - (i * q + r % q);
                    *(u16 *)(p + 0x6) = t6;
                }
            }
        }
        break;
    case 5:
    case 6:
        if (func_8012BEE8(s1) != 0) {
            *(u16 *)(s1 + 0x34) = *(u16 *)(s1 + 0x34) + 2;
        }
        break;
    case 7:
        *(u16 *)(s1 + 0x102) = *(u16 *)(s1 + 0x102) - 0x20;
        if ((s16)*(u16 *)(s1 + 0x102) < 0) {
            t34b = *(u16 *)(s1 + 0x34) + 1;
            *(s32 *)(s1 + 0x1C) = 0x10;
            *(u16 *)(s1 + 0x102) = 0;
            *(s32 *)(s1 + 0xE0) = *(s32 *)(s1 + 0xE0) | 0x10;
            *(u16 *)(s1 + 0x34) = t34b;
        }
        break;
    case 8:
        *(u16 *)(s1 + 0x102) = *(u16 *)(s1 + 0x102) + 0x20;
        if ((s16)*(u16 *)(s1 + 0x102) > 0) {
            t34b = *(u16 *)(s1 + 0x34) + 1;
            *(s32 *)(s1 + 0x1C) = 0x10;
            *(u16 *)(s1 + 0x102) = 0;
            *(s32 *)(s1 + 0xE0) = *(s32 *)(s1 + 0xE0) | 0x10;
            *(u16 *)(s1 + 0x34) = t34b;
        }
        break;
    case 9:
    case 10:
        if (func_8012BEE8(s1) != 0) {
            func_801843DC(s1);
            *(s32 *)(s1 + 0x1C) = 0x10;
            *(u16 *)(s1 + 0x34) = *(u16 *)(s1 + 0x34) + 1;
        }
        break;
    case 11:
        if (func_8012BEE8(s1) == 0) {
            return;
        }
        func_80183F0C((void *)s1);
        *(s32 *)(s1 + 0x4) = 0xFFF80000;
        *(s32 *)(s1 + 0x8) = 0xFE5E0000;
        *(s32 *)(s1 + 0xC) = 0xFE380000;
        *(s32 *)(s1 + 0x58) = ((s32)D_8018E288 | 0x40000000) | 0x20000000;
        return;
    }
    func_80183DA0(s1);
    func_801834A4(s1);
    func_801839A4(s1, 0x30);
    if (func_8018233C(s1) == 1) {
        func_801843DC(s1);
        *(s32 *)(s1 + 0xE0) = *(s32 *)(s1 + 0xE0) | 0x10;
    }
}
