void aF8017EF54(s32 a0)
{
    extern void func_8004914C(void *a0);
    extern void func_800491AC(void *a0);
    extern void func_8002D4C8(s32 a0, s32 a1);
    extern s32  RotTransPers(s32 a0, s32 a1, s32 *a2, s32 *a3);
    extern u8   D_800AF648;
    extern u8   D_800AF648_b __asm__("D_800AF648");
    extern void func_80181234(void);
    struct {
        s16 v[3];    /* sp+0x10 */
        s16 pad1;    /* sp+0x16 */
        u16 sxy[2];  /* sp+0x18 */
        s32 z;       /* sp+0x1C */
        s32 flag;    /* sp+0x20 */
    } L;

    if (*(u16 *)(a0 + 0x0) == 0) {
        return;
    }

    if (*(s16 *)(a0 + 0x84) == 0) {
        L.v[0] = *(s32 *)(*(s32 *)(a0 + 0x20) + 0x48);
        L.v[1] = *(s32 *)(*(s32 *)(a0 + 0x20) + 0x4C);
        L.v[2] = *(s32 *)(*(s32 *)(a0 + 0x20) + 0x50);
        func_8004914C(&D_800AF648);
        func_800491AC(&D_800AF648_b);
        RotTransPers((s32)L.v, (s32)L.sxy, &L.z, &L.flag);

        if (L.flag >= 0 && (u16)(L.sxy[0] + 0xEF) < 0x1DF
                        && (u16)(L.sxy[1] + 0xB3) < 0x167) {
            s32 sx = (s16)L.sxy[0];
            s32 av;

            av = (sx < 0) ? -sx : sx;
            av = ((0xF0 - av) * 0x7F) / 0xF0;
            sx = (sx + 0xF0) / 0x1E;
            if (sx == 0x10) {
                sx = 0xF;
            }
            sx = sx << 8;
            func_8002D4C8(0x849, (av | (0x3000 | sx)) & 0xFFFF);
        }
        *(s16 *)(a0 + 0x84) = 0xA;
    } else {
        (*(s16 *)(a0 + 0x84))--;
    }

    *(u16 *)(a0 + 0xFC) += 0x280;
    *(u16 *)(a0 + 0xFE) -= 0x280;
    ((void (*)(void *))func_80181234)((void *)a0);
}
