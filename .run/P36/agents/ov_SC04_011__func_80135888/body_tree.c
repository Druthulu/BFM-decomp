s32 func_80135888(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 pad_[8];
    register s32 m __asm__("$2");  // !FAKE: pin $2 — NEEDED DIFFERS (P36 rung B t3_tus1)
    s32 sp;
    register s32 p1   __asm__("$17");  // !FAKE: pin $17 — NEEDED DIFFERS (P36 rung B t3_tus1)
    s32 mode;
    register s32 p0   __asm__("$19");  // !FAKE: pin $19 — NEEDED DIFFERS (P36 rung B t3_tus1)
    s32 base;
    register s32 p3   __asm__("$21");  // !FAKE: pin $21 — NEEDED DIFFERS (P36 rung B t3_tus1)

    p0 = arg0;
    p1 = arg1;
    p3 = arg3;

    switch (((s32 (*)(void *, s32, s16 *, s16 *))func_80135480)((void *)arg0, arg1, (s16 *)arg2, (s16 *)arg3)) {
    case 0:
        return 0;
    case 1:
        base = p0 + 0x34;
        m = p1 & 0xFFFFFFF;
        sp = m | 0x80000000;
        mode = 0;
        break;
    case 2:
        base = p0 + 0x34;
        m = p1 & 0xFFFFFFF;
        sp = m | 0x80000000;
        mode = 1;
        break;
    case 3:
        base = p0 + 0x34;
        sp = (s32)&D_801EDA64;
        mode = 0;
        break;
    case 4:
        base = (s32)&D_801EDA44;
        sp = (s32)&D_801EDA64;
        mode = 1;
        break;
    }

    if (p1 < 0) {
        if (func_80135EB0(sp, 0) != 0) {
            func_80136A94(mode, p0, p3, base);
            return 1;
        }
        sp = *(s32 *)sp;
        __asm__ __volatile__("");  // !FAKE: barrier — NEEDED DIFFERS (P36 rung B t3_tus1)
        while (sp != 0) {
            if (func_80135EB0(sp, 0) != 0) {
hit:
                func_80136A94(mode, p0, p3, base);
                return 1;
            }
            sp = *(s32 *)sp;
        }
        return 0;
    }
    {
        u16 *pb = (*(u16 * *)&D_801909C0);
        u16 *pa = (*(u16 * *)&D_801909BC);
        s16 *pc = (*(s16 * *)&D_801909C8);
        pc[0] = pb[0] - pa[0];
        pc[1] = pb[1] - pa[1];
        pc[2] = pb[2] - pa[2];
        if (func_80134A74(0, (s16)pa[0], (s16)pa[2], sp) == 0) {
            return 0;
        }
    }
    goto hit;
}
