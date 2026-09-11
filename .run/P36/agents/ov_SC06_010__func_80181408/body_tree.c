void aF8017EF54(s32 a0)
{
    extern void func_8004914C(void *a0);
    extern void func_800491AC(void *a0);
    extern void func_8002D4C8(s32 a0, s32 a1);
    extern s32  RotTransPers(s32 a0, s32 a1, s32 *a2, s32 *a3);
    extern u8   D_800AF648;
    extern void func_80181234(void);
    struct {
        s16 v[3];    /* sp+0x10 */
        s16 pad1;    /* sp+0x16 */
        u16 sxy[2];  /* sp+0x18 */
        s32 z;       /* sp+0x1C */
        s32 flag;    /* sp+0x20 */
        s32 pad2[2]; /* sp+0x24 -- dead, sizes the frame */
    } L;

    s32 v1;
    s32 cool;
    s32 old;

    if (*(u16 *)(a0 + 0x0) == 0) {
        return;
    }

    old = *(s16 *)(a0 + 0x84);
    v1 = old;
    if (old != 0) {
        goto L_dec;
    }

    L.v[0] = *(s32 *)(*(s32 *)(a0 + 0x20) + 0x48);
    L.v[1] = *(s32 *)(*(s32 *)(a0 + 0x20) + 0x4C);
    L.v[2] = *(s32 *)(*(s32 *)(a0 + 0x20) + 0x50);
    { register void *r4 __asm__("$4"); r4 = &D_800AF648; func_8004914C(r4); }  // !FAKE: pin $4 — NEEDED DIFFERS (P36 rung B tus7)
    { void *r4; r4 = &D_800AF648; func_800491AC(r4); }
    RotTransPers((s32)L.v, (s32)L.sxy, &L.z, &L.flag);

    if (L.flag < 0) {
        cool = 0xA;
        goto L_join;
    }
    if ((u32)((L.sxy[0] + 0xEF) & 0xFFFF) >= 0x1DF) {
        cool = 0xA;
        goto L_join;
    }
    if ((u32)((L.sxy[1] + 0xB3) & 0xFFFF) >= 0x167) {
        goto L_snd_skip;
    }

    {
        s32 sx = (s16)L.sxy[0];
        s32 av;

        av = sx;
        if (sx < 0) {
            av = -sx;
        }
        av = ((0xF0 - av) * 0x7F) / 0xF0;
        sx = (sx + 0xF0) / 0x1E;
        if (sx == 0x10) {
            sx = 0xF;
        }
        sx = sx << 8;
        func_8002D4C8(0x849, (av | (0x3000 | sx)) & 0xFFFF);
    }

L_snd_skip:
    cool = 0xA;
    goto L_join;

L_dec:
    cool = v1 - 1;

L_join:
    *(s16 *)(a0 + 0x84) = cool;
    __asm__ __volatile__("" ::: "memory");  // !FAKE: barrier memory — NEEDED DIFFERS (P36 rung B tus7)

    {
        s32 p = a0;
        *(u16 *)(p + 0xFC) = *(u16 *)(p + 0xFC) + 0x280;
        *(u16 *)(p + 0xFE) = *(u16 *)(p + 0xFE) - 0x280;
        ((void (*)(void *))func_80181234)((void *)p);
    }
}
