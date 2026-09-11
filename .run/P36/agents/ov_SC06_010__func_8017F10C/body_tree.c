void func_8017F10C(s32 a0, s32 a1)
{
    extern void func_8004914C(void *a0);
    extern void func_800491AC(void *a0);
    extern void func_8002D4C8(s32 a0, s32 a1);
    extern s32  RotTransPers(s32 a0, s32 a1, s32 *a2, s32 *a3);
    extern u8   D_800AF648;
    extern u16  D_80126B66;

    struct {
        s16 v[3];    /* sp+0x10 */
        s16 pad1;    /* sp+0x16 */
        u16 sxy[2];  /* sp+0x18 */
        s32 z;       /* sp+0x1C */
        s32 flag;    /* sp+0x20 */
    } L;

    register s32 sid __asm__("$18");  // !FAKE: pin $18 — NEEDED DIFFERS (P36 rung B tus7)
    void *snd = &D_800AF648;

    L.v[0] = *(s32 *)(*(s32 *)(a0 + 0x20) + 0x48);
    L.v[1] = *(s32 *)(*(s32 *)(a0 + 0x20) + 0x4C);
    L.v[2] = *(s32 *)(*(s32 *)(a0 + 0x20) + 0x50);
    sid = a1;
    func_8004914C(snd);
    func_800491AC(snd);
    RotTransPers((s32)L.v, (s32)L.sxy, &L.z, &L.flag);

    if (L.flag >= 0 && (u32)((L.sxy[0] + 0xEF) & 0xFFFF) < 0x1DF
                    && (u32)((L.sxy[1] + 0xB3) & 0xFFFF) < 0x167) {
        s32 x = (s16)L.sxy[0];
        s32 t = *(s16 *)(a0 + 0xE) - 0x680;
        s32 d = *(s16 *)&D_80126B66 - t;

        if ((u32)d < 0x901) {
            d = (d * 0x7F) / 0x900;
            x = (x + 0xF0) / 0x1E;
            if (x == 0x10) {
                x = 0xF;
            }
            x = x << 8;
            {
                s32 flg = 0x3000;
                func_8002D4C8(sid & 0xFFFF, ((d | flg) | x) & 0xFFFF);
            }
        }
    }
}
