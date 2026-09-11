void func_80185DD8(s32 a0) {
    s32 r;
    s16 vecA[4];
    s16 vecB[4];
    s32 x;

    if ((*(u32 *)(a0 + 0xE0) & 0x40) == 0) {
        s32 ret = ((s32 (*)(s32))func_8012BE54)(a0);
        if (ret <= 0x63FFF) {
            if (func_8012BEE8(a0) != 0) {
                s32 t;
                s32 rr;

                t = func_8012B8A4((s16 *)a0);
                *(u32 *)(a0 + 0xE8) = (t + 0x800) & 0xFFF;
                rr = rand();
                *(s32 *)(a0 + 0x1C) = rr % 0x40 + 0x40;
            }
        }
    }

    r = func_8012B608((s32) * (s16 *)(*(s32 *)(a0 + 0x20) + 0x12), *(s32 *)(a0 + 0xE8), 8);
    *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) = *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) + r;

    *(u32 *)(a0 + 0xE0) &= 0xFFFFFFBF;
    func_8012B178(a0, 0xFFF8D000);

    if (func_8018765C(a0) == 0) {
        func_801877E4(a0);
    }

    vecA[0] = *(s16 *)(a0 + 0x6);
    vecA[1] = *(s16 *)(a0 + 0xA);
    vecA[2] = *(s16 *)(a0 + 0xE);
    ((s32 (*)(void *, void *))func_8012EFB8)(vecA, vecB);

    x = vecB[0];
    if (x < 0) {
        x = -x;
    }
    /* |z| tested per sign inside the jump context: each arm of the ?: is its own compare-and-branch,
     * so the two `slti 201` tails are not one value-converged abs (the x test above is). */
    if (x >= 0x105 || (vecB[1] >= 0 ? vecB[1] >= 0xC9 : -vecB[1] >= 0xC9)) {
        func_8012C098((void *)a0);
    }
}
