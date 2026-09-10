void func_80181B00(s32 a0) {

    extern u8 D_800AF648;
    extern s32 D_801A9CD8;
    extern s32 D_8019C1B8;
    extern s32 D_8019C48C;
    extern u16 D_80126B62;
    /* sp+0x10 local block.  Frame is 0x38 = 0x10 outgoing args + 0x20 vars +
     * 8 saved regs ($s0,$ra), so the vars block is 12 bytes larger than the
     * fields this function actually touches -> trailing `unused[3]`. */
    struct {
        s16 v[3];      /* sp+0x10 */
        s16 pad0;      /* sp+0x16 */
        u16 sxy[2];    /* sp+0x18 */
        s32 z;         /* sp+0x1C */
        s32 flag;      /* sp+0x20 */
        s32 unused[1]; /* sp+0x24 */
    } L;
    s16 x;
    s32 y;

    if (*(s32 *)(a0 + 0x94) == 0xD) {
        L.v[0] = *(s32 *)(*(s32 *)(a0 + 0x20) + 0x48);
        L.v[1] = *(s32 *)(*(s32 *)(a0 + 0x20) + 0x4C);
        L.v[2] = *(s32 *)(*(s32 *)(a0 + 0x20) + 0x50);
        /* $a0-pinned scopes force the &D_800AF648 constant to be rematerialised
         * per call (cookbook §88a); otherwise CSE parks it in a callee-saved reg
         * and mis-seats every register in the function. */
        { register void *r4 __asm__("$4"); r4 = &D_800AF648; func_8004914C(r4); }  // !FAKE: pin $4 — NEEDED DIFFERS (P36 rung B tus9)
        { void *r4; r4 = &D_800AF648; func_800491AC(r4); }
        RotTransPers((s32)L.v, (s32)L.sxy, &L.z, &L.flag);
        if (L.flag >= 0 && (u32)((L.sxy[0] + 0x9F) & 0xFFFF) < 0x13F
                        && (u32)((L.sxy[1] + 0x77) & 0xFFFF) < 0xEF) {
            s32 vol = (s16)L.sxy[0];
            if (vol < 0) {
                vol = -vol;
            }
            vol = ((0xA0 - vol) * 127) / 160;
            func_8002D4C8(0x702, (vol | 0x1000) & 0xFFFF);
        }
    }

    if (func_8012BCCC(a0) <= 0x24000) {
        s16 c;
        c = *(u16 *)(a0 + 0x102) + 1;
        *(s16 *)(a0 + 0x102) = c;
        if (c >= 0x78) {
            if ((*(u16 *)(a0 + 0x100) & 0x2000) == 0) {
                ((void (*)(s32, s32))func_8012A828)(a0, (s32)&D_801A9CD8);
                *(s16 *)(a0 + 0x2) = 10;
                *(s16 *)(a0 + 0x102) = 0;
                *(s32 *)(a0 + 0x58) = (s32)&D_8019C1B8 | 0x40000000 | 0x20000000;
            }
        }
    }

    *(s16 *)(*(s32 *)(a0 + 0x20) + 0x12) += func_8012B8E4(a0, 0x10);
    *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) &= 0xFFF;

    x = *(s16 *)(a0 + 0xA);
    y = *(s16 *)&D_80126B62;
    if (x <= y - 0x100) {
        *(s16 *)(a0 + 0xA) = x + 0x8;
    } else if (x >= y - 0x80) {
        *(s16 *)(a0 + 0xA) = x - 0x8;
    }

    func_8012B1B4(a0, (s32)&D_8019C48C);
    func_8012CBCC(a0);
}
