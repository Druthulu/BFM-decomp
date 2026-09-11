s32 impl_801833D4(s32 a0, s32 a1)
{
    /* $a1 is call-saved across func_801852BC/func_801853D0/func_80185648 until its one use
       far below; gcc puts its param->hardreg move in the branch's delay slot rather than up
       front. The copy is a STATEMENT after the first load, not the declaration's initialiser:
       an initialiser sits right after the parameter copy, cse retargets that copy
       (cse.c:7454-7480) and sched1 never moves it (sched.c:3188-3205); after a real insn,
       combine folds the parameter copy into it and it is scheduled like any other insn
       (P36 S104 e11, the $19 pin removed). */
    s32 r1;
    u16 s0;
    s32 obj;
    s32 s4;
    /* v[2..4] is a 3-word (vel-like x/y/z) struct passed by address to func_800484EC; the
       real local apparently has 2 leading words of other data ahead of it in the frame (its
       address-taken struct forces gcc to reserve stack starting 2 words earlier than our x
       field) -- v[0]/v[1] are unused padding needed only to reproduce the frame layout. */
    s32 v[5];

    s0 = D_801EFD20;
    s4 = 0;
    r1 = a1;
    obj = aFC4C[s0];

    if (D_801EFD40 & 0x4) {
        func_801852BC(s0);
        func_801853D0(s0);
        func_80185648(s0);

        v[3] = 0;
        v[2] = 0;
        if (D_801EFD40 & 0x20) {
            v[4] = 0xFFD80000;
        } else {
            v[4] = 0xFFEC0000;
        }

        func_800484EC(*(s32 *)(obj + 0x20) + 0x34, (s32)&v[2], (s32)&v[2]);

        *(s32 *)(obj + 0x4) += v[2];
        *(s32 *)(obj + 0x8) += v[3];
        *(s32 *)(obj + 0xC) += v[4];

        *(u16 *)(*(s32 *)(obj + 0x20) + 0x14) =
            *(u16 *)(*(s32 *)(obj + 0x20) + 0x14) + r1;
        func_80183BF0(a0);

        *(u16 *)(*(s32 *)(obj + 0x20) + 0x10) =
            *(u16 *)(a0 + 0xFE) + *(u16 *)(a0 + 0x102);

        if (func_801836D4((void *)a0, (void *)obj) != 0) {
            s4 = 1;
        } else {
            if (D_801EFD40 & 0x20) {
                s0 = 0x40;
            } else {
                s0 = 0x20;
            }
            func_80185960(*(s16 *)(a0 + 0x106), (u16 *)(*(s32 *)(obj + 0x20) + 0x12), s0);
            func_80185960(*(s16 *)(a0 + 0x100), (u16 *)(a0 + 0xFE), s0);
        }
    }

    return s4;
}
