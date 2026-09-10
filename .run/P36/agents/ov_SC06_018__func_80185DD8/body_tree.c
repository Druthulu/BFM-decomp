void func_80185DD8(s32 a0) {
    s32 r;
    s16 vecA[4];
    s16 vecB[4];
    s32 x, z;

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
    if (x < 0x105) {
        z = vecB[1];
        if (z >= 0) {
            if (z < 0xC9) {
                /* NEW LEVER (not yet in cookbook): a bare if/else-with-return here compiles
                 * to a value-converge merge (ONE shared `slti`+`bne` fed by both signs of z,
                 * ~91 ins) instead of the target's genuine PER-BRANCH duplicate compare
                 * (96 ins: `bltz`+`slti`+`beqz`+`j` in this arm, `negu`+`slti`+`bnez` in the
                 * else arm). A zero-emission `__asm__ __volatile__("":::"memory")` right
                 * before this `return` is a scheduling/combine barrier that blocks whatever
                 * RTL-level pass performs that merge, without adding a single byte itself --
                 * the compiled result is byte-exact target. Byte-proven via 9 probe variants
                 * (assignment-abs, ternary-condition, if/else, 2-independent-ifs, goto-labeled
                 * return) that ALL either fully merged or left a redundant extra sign-retest;
                 * only this barrier reproduces the target exactly. See match_one MATCH 96/96.
                 */
                __asm__ __volatile__("" ::: "memory");  // !FAKE: barrier memory — NEEDED DIFFERS (P36 rung B tus9)
                return;
            }
        } else {
            if (-z < 0xC9) {
                return;
            }
        }
    }
    func_8012C098((void *)a0);
}
