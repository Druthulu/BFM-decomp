void func_80184394(s32 a0)
{

    extern void (*D_801A71B4[])(void);
    extern u8 D_800AF648;
    struct {
        s16 v[3];    /* sp+0x10 */
        s16 pad1;    /* sp+0x16 */
        u16 sxy[2];  /* sp+0x18 */
        s32 z;       /* sp+0x1C */
        s32 flag;    /* sp+0x20 */
    } L;

    D_801A71B4[*(u16 *)(a0 + 0x2)]();

    if (*(u16 *)(a0 + 0x0) != 0) {
        if (*(s16 *)(a0 + 0x70) == 0 && func_8012C044(a0) != 0) {
            if (*(s32 *)(a0 + 0xCC) != 0) {
                func_8012C218(*(void **)(a0 + 0xCC));
            }
            if (*(s32 *)(a0 + 0xD0) != 0) {
                func_8012C218(*(void **)(a0 + 0xD0));
            }
            func_8012C098((void *)a0);
        } else {
            s16 v;

            v = *(s16 *)(a0 + 0xE2);
            if (v != 0) {
                v = v - 1;
                *(s16 *)(a0 + 0xE2) = v;
                if (v == 0) {
                    *(u16 *)(a0 + 0x5C) &= 0xBFFF;
                }
            }

            if ((*(s16 *)(a0 + 0x76) < 5) && ((rand() & 3) == 0)) {
                s32 iVar2 = ((s32 (*)(s32, s32))func_80143C74)(a0, 0);
                s32 r;

                if (iVar2 != 0) {
                    r = rand();
                    *(s32 *)(iVar2 + 0x10) = ((r & 0x7FF) - 0x400) << 8;
                    *(s32 *)(iVar2 + 0x14) = 0xFFF00000;
                    r = rand();
                    *(s32 *)(iVar2 + 0x18) = ((r & 0x7FF) - 0x400) << 8;
                    r = rand();
                    *(u16 *)(iVar2 + 0x6) -= 0x20;
                    *(u16 *)(iVar2 + 0x6) += (r & 0x3F);
                    *(s16 *)(iVar2 + 0xA) -= 0xC0;
                    r = rand();
                    *(u16 *)(iVar2 + 0xE) -= 0x20;
                    *(u16 *)(iVar2 + 0xE) += (r & 0x3F);
                }
            }

            if (*(u16 *)(a0 + 0x2) != 1 && *(u16 *)(a0 + 0x2) != 5) {
                *(s16 *)(a0 + 0x84) = 0xE;
            } else {
                if (*(s16 *)(a0 + 0x84) != 0) {
                    *(s16 *)(a0 + 0x84) = *(s16 *)(a0 + 0x84) - 1;
                } else {
                    *(s16 *)(a0 + 0x84) = 0xE;

                    L.v[0] = *(s32 *)(*(s32 *)(a0 + 0x20) + 0x48);
                    L.v[1] = *(s32 *)(*(s32 *)(a0 + 0x20) + 0x4C);
                    L.v[2] = *(s32 *)(*(s32 *)(a0 + 0x20) + 0x50);
                    { register void *r4 __asm__("$4"); r4 = &D_800AF648; func_8004914C(r4); }  // !FAKE: pin $4 — NEEDED DIFFERS (P36 rung B tus7)
                    { void *r4; r4 = &D_800AF648; func_800491AC(r4); }
                    RotTransPers((s32)L.v, (s32)L.sxy, &L.z, &L.flag);
                    if (L.flag >= 0 && (u32)((L.sxy[0] + 0xEF) & 0xFFFF) < 0x1DF
                                    && (u32)((L.sxy[1] + 0xB3) & 0xFFFF) < 0x167) {
                        s32 x = (s16)L.sxy[0];
                        s32 ax;
                        ax = x;
                        if (x < 0) {
                            ax = -x;
                        }
                        ax = ((0xF0 - ax) * 0x7F) / 0xF0;
                        x = (x + 0xF0) / 0x1E;
                        if (x == 0x10) {
                            x = 0xF;
                        }
                        x = x << 8;
                        {
                            s32 flg = 0x3000;
                            func_8002D4C8(0x8BF, ((ax | flg) | x) & 0xFFFF);
                        }
                    }
                }
            }
        }
    }
}
