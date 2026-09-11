void func_80180B24(s32 s0)
{
    /* BLOCK scope on purpose (house style, TU l.5019/5156): the TU defines
     * `void func_80183BD0(s32 a0)` at ~l.7238 and its earlier block-scope `(u8 *a0)` externs
     * sit in limbo; a FILE-scope decl here would let gcc-2.7.2's pushdecl merge that
     * prototype into the global (different_binding_level) and the definition then errors
     * `conflicting types for func_80183BD0` -- measured on a spliced-TU cc1 run. */
    extern void func_80183BD0(u8 *a0);
    struct Ent_80180B24 *p;
    s32 a;
    s32 ta;
    s32 tb;
    s32 tc;
    s32 s1;
    s32 s3;
    s16 x;
    s16 y;
    s16 buf[3];

    p = (struct Ent_80180B24 *)s0;
    s3 = (s32)&aB58_80180B24[0];
    if (*(u16 *)(s0 + 0x34) == 4) {
        s1 = aFC4C[D_801EFD20];
        x = *(u16 *)(*(s32 *)(s1 + 0x20) + 0x12) & 0xFFF;
        if (x >= 0x800) {
            x |= 0xF000;
        }
        func_80183880((s32)s0);
        y = *(u16 *)(*(s32 *)(s1 + 0x20) + 0x12) & 0xFFF;
        if (y >= 0x800) {
            y |= 0xF000;
        }
        if ((x < -0x200 && -0x201 < y) || (-0x200 < x && y < -0x1FF)) {
            func_8002D4C8(0x9C3, 0);
        }
        if (((s32 (*)(u8 *))func_8012BEE8)((u8 *)s0) != 0) {
            buf[0] = *(u16 *)(s3 + 6);
            buf[1] = *(u16 *)(s3 + 0xA) - 0x50;
            buf[2] = *(u16 *)(s3 + 0xE);
            func_80183BD0((u8 *)s0);
            func_80183564((s32)s0, buf);
            *(u16 *)(s0 + 0xE0) = 0x10;
            *(u16 *)(s0 + 0x34) = 0;
        }
        return;
    }
    if (((s32 (*)(int, int))func_801833D4)((int)s0, 0) != 0) {
        switch (*(u16 *)(s0 + 0x34)) {
        case 0:
            /* §49-variant/§30#3: zero-byte re-ties set reg_n_sets=2, killing sched1's
             * birthing_insn_p LAUNCH_PRIORITY boost that glued each add to its store;
             * yields the target's load*3 / add*3 / store*3 order. */
            ta = *(u16 *)(s0 + 0xF4) + 1;
            tb = *(u16 *)(s0 + 0xF2) + 1;
            __asm__("" : "=r"(ta) : "0"(ta));  // !FAKE: launder — NEEDED DIFFERS (P36 rung B t3_tus1)
            __asm__("" : "=r"(tb) : "0"(tb));  // !FAKE: launder — NEEDED DIFFERS (P36 rung B t3_tus1)
            *(u16 *)(s0 + 0xF4) = ta;
            *(u16 *)(s0 + 0xF2) = tb;
            *(u16 *)(s0 + 0x34) = *(u16 *)(s0 + 0x34) + 1;
            func_8002D4C8(0x992, 0);
            break;
        case 1:
            /* struct-member spelling (MEM_IN_STRUCT_P) on the s0 fields defeats the false
             * alias against the D_801EFD40 store. */
            D_801EFD40 = D_801EFD40 & 0xFFFE;
            a = p->unkF4 + 1;
            p->unkF4 = a + (p->unkF2 & 1);
            tc = p->unk34 + 1;
            __asm__("" : "=r"(tc) : "0"(tc));  // !FAKE: launder — NEEDED DIFFERS (P36 rung B t3_tus1)
            p->unk34 = tc;
            break;
        case 2:
            if (*(s16 *)(s0 + 0x76) == 0) {
                func_80180E80((u8 *)s0);
                return;
            }
            *(u16 *)(s0 + 0xF4) = 0;
            func_80183BAC((u8 *)s0);
            *(u16 *)(s0 + 0x34) = 3;
            break;
        case 3:
            ((void (*)(s32))func_801837C4)(s0);
            func_80183BAC((u8 *)s0);
            *(s32 *)(s0 + 0x1C) = 0x80;
            *(u16 *)(s0 + 0x100) = 0;
            *(u16 *)(s0 + 0x34) = 4;
            return;
        }
        func_80183564((s32)s0, (s16 *)(D_80194470 + (*(s16 *)(s0 + 0xF4) * 8)));
        *(u16 *)(s0 + 0xE0) = 0x10;
    } else {
        /* store 0xE0 in BOTH arms: cross_jump merges the sh at the join, and the s16 local
         * yields the un-coalesced addu $v1,$v0,$zero that stops reorg stealing the decrement. */
        s16 v0 = *(s16 *)(s0 + 0xE0);
        if (v0 != 0) {
            *(s16 *)(s0 + 0xE0) = v0 - 1;
        } else {
            func_80183A28((u8 *)s0);
            *(s16 *)(s0 + 0xE0) = 0x10;
        }
        if (*(u16 *)(s0 + 0x34) == 0) {
            u16 flag = D_801EFD40;
            if (!(flag & 1)) {
                s1 = aFC4C[D_801EFD20];
                if ((u16)(((*(u16 *)(s0 + 0x106) & 0xFFF) -
                           (*(u16 *)(*(s32 *)(s1 + 0x20) + 0x12) & 0xFFF)) - 0x180) >= 0xD01) {
                    D_801EFD40 = flag | 1;
                    func_8002D4C8(0x7E3, 0);
                }
            }
        }
    }
}
